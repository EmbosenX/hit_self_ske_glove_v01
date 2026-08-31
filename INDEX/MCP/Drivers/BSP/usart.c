/**
  ******************************************************************************
  * @file    usart.c
  * @brief   USART1 驱动实现 (DMA发送 + RXNE中断接收环形缓冲 + FreeRTOS)
  ******************************************************************************
  */

#include "usart.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include <string.h>

/* ===================== 外设句柄 ===================== */
SCI_HandleTypeDef hsci;
DMA_HandleTypeDef hdma_sci_tx;  /* 仅TX使用DMA，RX使用普通中断 */

/* ===================== FreeRTOS 静态同步对象 ===================== */
/* 发送完成同步信号量 */
static SemaphoreHandle_t xTxDoneSem;
static StaticSemaphore_t xTxDoneSemBuffer;
/* 发送多任务互斥锁 */
static SemaphoreHandle_t xTxMutex;
static StaticSemaphore_t xTxMutexBuffer;
/* 接收新数据通知信号量 */
SemaphoreHandle_t xRxNewDataSem;
static StaticSemaphore_t xRxNewDataSemBuffer;

/* ===================== 接收环形缓冲区 ===================== */
#define RX_BUF_SIZE     16    /* 接收缓冲区总大小 */
static uint8_t  s_rxBuf[RX_BUF_SIZE];
static uint16_t s_rxWrite = 0;  /* 写指针（RXNE中断中更新） */
static uint16_t s_rxRead  = 0;  /* 读指针（任务读取接口更新） */

/* ===================== 外部函数声明 ===================== */
void APP_ErrorHandler(void);

/**
  * @brief  USART1 外设参数初始化
  */
void Usart_Init(void)
{
    /* 1. SCI外设基础参数配置 */
    hsci.Instance                    = USART1;
    hsci.Init.BaudRate               = 921600;
    hsci.Init.WordLength             = SCI_WORDLENGTH_8B;
    hsci.Init.StopBits               = SCI_STOPBITS_1;
    hsci.Init.Parity                 = SCI_PARITY_NONE;
    hsci.Init.Mode                   = SCI_MODE_TX_RX;
    hsci.Init.HwFlowCtl              = SCI_HWCONTROL_NONE;
    hsci.Init.OverSampling           = SCI_OVERSAMPLING_16;
    hsci.AdvancedInit.AdvFeatureInit = SCI_ADVFEATURE_NO_INIT;

    if (HAL_SCI_Init(&hsci) != HAL_OK)
    {
        APP_ErrorHandler();
    }

    /* 2. 开启接收非空中断，逐字节接收数据 */
    //__HAL_SCI_ENABLE_IT(&hsci, SCI_IT_RXNE);

    /* 3. 创建FreeRTOS静态同步对象 */
    xTxDoneSem = xSemaphoreCreateBinaryStatic(&xTxDoneSemBuffer);
    xSemaphoreGive(xTxDoneSem);  /* 初始置位，确保首次发送可正常等待 */

    xTxMutex = xSemaphoreCreateMutexStatic(&xTxMutexBuffer);

    xRxNewDataSem = xSemaphoreCreateBinaryStatic(&xRxNewDataSemBuffer);
}

/**
  * @brief SCI MSP 初始化回调：GPIO、时钟、TX DMA、中断配置
  */
void HAL_SCI_MspInit(SCI_HandleTypeDef* hsci)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    if (hsci->Instance == USART1)
    {
        /* 开启外设时钟 */
        __HAL_RCC_USART1_CLK_ENABLE();
        __HAL_RCC_DMA1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();

        /* USART1 GPIO 配置
           PA2 ------> USART1_TX
           PA3 ------> USART1_RX */
        GPIO_InitStruct.Pin       = GPIO_PIN_2 | GPIO_PIN_3;
        GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull      = GPIO_PULLUP;
        GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF1_USART1;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        /* ---------- TX DMA 配置：DMA1_Channel1 普通模式 ---------- */
        hdma_sci_tx.Instance                 = DMA1_Channel1;
        hdma_sci_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
        hdma_sci_tx.Init.PeriphInc           = DMA_PADDR_FIX;
        hdma_sci_tx.Init.MemInc              = DMA_MADDR_INC;
        hdma_sci_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_sci_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
        hdma_sci_tx.Init.Mode                = DMA_NORMAL;
        hdma_sci_tx.Init.Priority            = DMA_PRIORITY_0;
        hdma_sci_tx.Init.TransMode           = DMA_TRANSFER_SINGLE;
        if (HAL_DMA_Init(&hdma_sci_tx) != HAL_OK)
        {
            APP_ErrorHandler();
        }
        /* DMA通道映射与句柄关联 */
        HAL_DMA_ChannelMap(&hdma_sci_tx, DMA_CHANNEL_MAP_USART1_TX);
        __HAL_LINKDMA(hsci, hdmatx, hdma_sci_tx);

        /* 中断优先级配置 */
        HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

        HAL_NVIC_SetPriority(USART1_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(USART1_IRQn);
    }
}

/**
  * @brief  DMA阻塞发送数据（任务上下文调用，多任务安全）
  * @param  data: 发送数据首地址
  * @param  len:  发送字节数
  * @param  timeout: 超时时间（系统节拍数，可用pdMS_TO_TICKS转换）
  * @retval 0-成功, -1-失败/超时
  */
int Usart_SendDMA(const uint8_t *data, uint16_t len, uint32_t timeout)
{
    BaseType_t ret;

    if (data == NULL || len == 0)
    {
        return -1;
    }

    /* 获取发送互斥锁，支持多任务并发调用 */
    if (xSemaphoreTake(xTxMutex, timeout) != pdTRUE)
    {
        return -1;
    }

    /* 清空发送完成信号量，准备等待 */
    xSemaphoreTake(xTxDoneSem, 0);

    /* 启动DMA发送 */
    if (HAL_SCI_Transmit_DMA(&hsci, (uint8_t *)data, len) != HAL_OK)
    {
        xSemaphoreGive(xTxMutex);
        return -1;
    }

    /* 阻塞等待发送完成 */
    ret = xSemaphoreTake(xTxDoneSem, timeout);
    xSemaphoreGive(xTxMutex);

    return (ret == pdTRUE) ? 0 : -1;
}

/**
  * @brief  读取接收到的数据（任务上下文调用）
  * @param  data: 接收数据存储地址
  * @param  maxLen: 最大读取字节数
  * @retval 实际读取到的字节数
  */
uint16_t Usart_Read(uint8_t *data, uint16_t maxLen)
{
    uint16_t readLen = 0;

    /* 从环形缓冲区拷贝数据，直到读空或达到最大长度 */
    while (s_rxWrite != s_rxRead && readLen < maxLen)
    {
        data[readLen++] = s_rxBuf[s_rxRead];
        s_rxRead = (s_rxRead + 1) % RX_BUF_SIZE;
    }

    return readLen;
}

void USART1_IRQHandler(void)
{
    /* ========== 1. RXNE 逐字节接收 + 帧匹配 ========== */
    if (__HAL_SCI_GET_FLAG(&hsci, SCI_FLAG_RXNE) != RESET)
    {

    }

    /* ========== 2. 清除溢出错误，复位状态机 ========== */
    if (__HAL_SCI_GET_FLAG(&hsci, SCI_FLAG_ORE) != RESET)
    {
        __HAL_SCI_CLEAR_OREFLAG(&hsci);
    }

    /* ========== 3. HAL 通用处理：发送、其他错误等 ========== */
    HAL_SCI_IRQHandler(&hsci);
}
/**
  * @brief  TX DMA 通道1中断服务函数
  */
void DMA1_Channel1_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_sci_tx);
}

/**
  * @brief  SCI发送完成回调函数
  */
void HAL_SCI_TxCpltCallback(SCI_HandleTypeDef *hsci)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if (hsci->Instance == USART1)
    {
        xSemaphoreGiveFromISR(xTxDoneSem, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}


