/**
  ******************************************************************************
  * @file    uart.c
  * @brief   UART1 驱动实现 (DMA发送 + RXNE中断接收帧匹配 + FreeRTOS)
  * @pin     PF0 ------> UART1_TX
  *          PF1 ------> UART1_RX
  ******************************************************************************
  */
#include "uart.h"
#include <string.h>

/* ===================== 外设句柄 ===================== */
UART_HandleTypeDef UartHandle;
DMA_HandleTypeDef hdma_uart_tx;

/* ===================== FreeRTOS 静态同步对象 ===================== */
static SemaphoreHandle_t xUartTxDoneSem;
static StaticSemaphore_t xUartTxDoneSemBuffer;
static SemaphoreHandle_t xUartTxMutex;
static StaticSemaphore_t xUartTxMutexBuffer;

SemaphoreHandle_t xUartRxNewDataSem;
static StaticSemaphore_t xUartRxNewDataSemBuffer;

/* ===================== 接收双缓冲（当前接收缓冲 + 就绪缓冲） ===================== */
#define UART_RX_FRAME_SIZE    384U
static uint8_t  s_rxCurBuf[UART_RX_FRAME_SIZE];    /* 当前接收缓冲区（中断中写入） */
static uint16_t s_rxCurLen = 0;                     /* 当前接收缓冲区已接收长度 */
static uint8_t  s_rxReadyBuf[UART_RX_FRAME_SIZE];   /* 就绪缓冲区（帧匹配完成后拷贝至此） */
static volatile uint16_t s_rxReadyLen = 0;          /* 就绪缓冲区数据长度 */

/* ===================== 帧匹配参数 ===================== */
#define FRAME_HEAD_BYTE   0x3C
#define FRAME_TAIL_BYTE   0x3E
#define FRAME_MATCH_CNT   2

typedef enum
{
    STATE_WAIT_HEAD = 0,
    STATE_IN_FRAME,
    STATE_WAIT_TAIL
} FrameState_t;

/* ===================== 外部函数声明 ===================== */
void APP_ErrorHandler(void);

/**
  * @brief  UART1 外设参数初始化
  */
void Uart_Init(void)
{
    UartHandle.Instance             = UART1;
    UartHandle.Init.BaudRate        = 921600;
    UartHandle.Init.WordLength      = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits        = UART_STOPBITS_1;
    UartHandle.Init.Parity          = UART_PARITY_NONE;
    UartHandle.Init.MsbFirst        = UART_MSB_FIRST_DISABLE;
    if (HAL_UART_Init(&UartHandle) != HAL_OK)
    {
        APP_ErrorHandler();
    }

    /* 开启接收非空中断，逐字节接收 */
    __HAL_UART_ENABLE_IT(&UartHandle, UART_IT_RXNE);

    /* 创建发送完成信号量（初始置位） */
    xUartTxDoneSem = xSemaphoreCreateBinaryStatic(&xUartTxDoneSemBuffer);
    xSemaphoreGive(xUartTxDoneSem);

    /* 创建发送互斥锁，支持多任务并发调用 */
    xUartTxMutex = xSemaphoreCreateMutexStatic(&xUartTxMutexBuffer);

    /* 创建接收新数据通知信号量 */
    xUartRxNewDataSem = xSemaphoreCreateBinaryStatic(&xUartRxNewDataSemBuffer);
}

/**
  * @brief UART MSP 初始化回调：GPIO、时钟、TX DMA、中断配置
  */
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(huart->Instance == UART1)
    {
        /* 开启外设时钟 */
        __HAL_RCC_UART1_CLK_ENABLE();
        __HAL_RCC_DMA1_CLK_ENABLE();
        __HAL_RCC_GPIOF_CLK_ENABLE();

        /* UART1 GPIO 配置
           PF0 ------> UART1_TX
           PF1 ------> UART1_RX */
        GPIO_InitStruct.Pin       = GPIO_PIN_0 | GPIO_PIN_1;
        GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull      = GPIO_PULLUP;
        GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF9_UART1;
        HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

        /* TX DMA 配置：DMA1_Channel2 普通模式 */
        hdma_uart_tx.Instance                 = DMA1_Channel2;
        hdma_uart_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
        hdma_uart_tx.Init.PeriphInc           = DMA_PADDR_FIX;
        hdma_uart_tx.Init.MemInc              = DMA_MADDR_INC;
        hdma_uart_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_uart_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
        hdma_uart_tx.Init.Mode                = DMA_NORMAL;
        hdma_uart_tx.Init.Priority            = DMA_PRIORITY_0;
        hdma_uart_tx.Init.TransMode           = DMA_TRANSFER_SINGLE;
        if (HAL_DMA_Init(&hdma_uart_tx) != HAL_OK)
        {
            APP_ErrorHandler();
        }
        /* DMA通道映射与句柄关联 */
        HAL_DMA_ChannelMap(&hdma_uart_tx, DMA_CHANNEL_MAP_UART1_TX);
        __HAL_LINKDMA(huart, hdmatx, hdma_uart_tx);

        /* 中断优先级配置 */
        HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);

        HAL_NVIC_SetPriority(UART1_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(UART1_IRQn);
    }
}

/**
  * @brief  DMA阻塞发送数据（任务上下文调用，多任务安全）
  * @param  data: 发送数据首地址
  * @param  len:  发送字节数
  * @param  timeout: 超时时间（系统节拍数）
  * @retval 0-成功, -1-失败/超时
  */
int Uart_SendDMA(const uint8_t *data, uint16_t len, uint32_t timeout)
{
    BaseType_t ret;

    if (data == NULL || len == 0)
    {
        return -1;
    }

    /* 获取发送互斥锁 */
    if (xSemaphoreTake(xUartTxMutex, timeout) != pdTRUE)
    {
        return -1;
    }

    /* 清空发送完成信号量，准备等待 */
    xSemaphoreTake(xUartTxDoneSem, 0);

    /* 启动DMA发送 */
    if (HAL_UART_Transmit_DMA(&UartHandle, (uint8_t *)data, len) != HAL_OK)
    {
        xSemaphoreGive(xUartTxMutex);
        return -1;
    }

    /* 阻塞等待发送完成 */
    ret = xSemaphoreTake(xUartTxDoneSem, timeout);
    xSemaphoreGive(xUartTxMutex);

    return (ret == pdTRUE) ? 0 : -1;
}

/**
  * @brief  读取接收到的一帧数据（任务上下文调用）
  * @param  data: 接收数据存储地址
  * @param  maxLen: 最大读取字节数
  * @retval 实际读取到的字节数
  * @note   调用关中断保证与中断中的就绪缓冲区访问互斥
  */
uint16_t Uart_Read(uint8_t *data, uint16_t maxLen)
{
    uint16_t len;
    uint32_t primask;

    /* 关中断，保护就绪缓冲区 */
    primask = __get_PRIMASK();
    __set_PRIMASK(1);

    len = s_rxReadyLen;
    if (len > maxLen)
    {
        len = maxLen;
    }
    memcpy(data, s_rxReadyBuf, len);
    s_rxReadyLen = 0;   /* 读取后清空就绪标志，等待下一帧 */

    __set_PRIMASK(primask);

    return len;
}

/**
  * @brief  UART1 中断服务函数：RXNE逐字节接收 + 帧头帧尾匹配
  */
void UART1_IRQHandler(void)
{
    static FrameState_t s_state = STATE_WAIT_HEAD;
    static uint8_t s_matchCnt = 0;

    if (__HAL_UART_GET_FLAG(&UartHandle, UART_FLAG_RXNE) != RESET)
    {
        uint8_t rxByte = (uint8_t)(UartHandle.Instance->DR);

        switch (s_state)
        {
            /* 状态1：等待帧头（需连续匹配2个0x3C） */
            case STATE_WAIT_HEAD:
                if (rxByte == FRAME_HEAD_BYTE)
                {
                    s_matchCnt++;
                    if (s_matchCnt >= FRAME_MATCH_CNT)
                    {
                        /* 帧头匹配成功，清空当前缓冲区并写入帧头，进入接收状态 */
                        s_rxCurLen = 0;
                        if (s_rxCurLen < UART_RX_FRAME_SIZE)
                            s_rxCurBuf[s_rxCurLen++] = FRAME_HEAD_BYTE;
                        if (s_rxCurLen < UART_RX_FRAME_SIZE)
                            s_rxCurBuf[s_rxCurLen++] = FRAME_HEAD_BYTE;
                        s_state = STATE_IN_FRAME;
                        s_matchCnt = 0;
                    }
                }
                else
                {
                    s_matchCnt = 0;
                }
                break;

            /* 状态2：帧数据接收中 */
            case STATE_IN_FRAME:
                if (s_rxCurLen < UART_RX_FRAME_SIZE)
                {
                    s_rxCurBuf[s_rxCurLen++] = rxByte;
                }
                if (rxByte == FRAME_TAIL_BYTE)
                {
                    s_state = STATE_WAIT_TAIL;
                    s_matchCnt = 1;
                }
                break;

            /* 状态3：等待帧尾（需连续匹配2个0x3E） */
            case STATE_WAIT_TAIL:
                if (s_rxCurLen < UART_RX_FRAME_SIZE)
                {
                    s_rxCurBuf[s_rxCurLen++] = rxByte;
                }
                if (rxByte == FRAME_TAIL_BYTE)
                {
                    s_matchCnt++;
                    if (s_matchCnt >= FRAME_MATCH_CNT)
                    {
                        /* 帧尾匹配成功，将当前缓冲拷贝到就绪缓冲，通知任务 */
                        memcpy(s_rxReadyBuf, s_rxCurBuf, s_rxCurLen);
                        s_rxReadyLen = s_rxCurLen;

                        s_state = STATE_WAIT_HEAD;
                        s_matchCnt = 0;

                        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
                        xSemaphoreGiveFromISR(xUartRxNewDataSem, &xHigherPriorityTaskWoken);
                        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
                    }
                }
                else
                {
                    s_state = STATE_IN_FRAME;
                    s_matchCnt = 0;
                }
                break;

            default:
                s_state = STATE_WAIT_HEAD;
                s_matchCnt = 0;
                break;
        }
    }

    /* 清除溢出错误 */
    if (__HAL_UART_GET_FLAG(&UartHandle, UART_FLAG_ORE) != RESET)
    {
        __HAL_UART_CLEAR_FLAG(&UartHandle, UART_FLAG_ORE);
    }

    HAL_UART_IRQHandler(&UartHandle);
}

/**
  * @brief  TX DMA 通道2中断服务函数
  */
void DMA1_Channel2_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_uart_tx);
}

/**
  * @brief  UART发送完成回调函数
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    if (huart->Instance == UART1)
    {
        xSemaphoreGiveFromISR(xUartTxDoneSem, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}
