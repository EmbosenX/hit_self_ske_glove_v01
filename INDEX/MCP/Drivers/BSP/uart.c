/**
  ******************************************************************************
  * @file    uart.c
  * @brief   UART1 驱动实现 (DMA发送 + RXNE中断单帧接收 + FreeRTOS)
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

/* ===================== 单帧接收缓冲区（只保留最新一帧） ===================== */
#define UART_RX_FRAME_SIZE    350U
static uint8_t  s_rxCurBuf[UART_RX_FRAME_SIZE];    /* 中断当前正在接收的帧 */
static uint16_t s_rxCurLen = 0;                     /* 当前帧已接收长度 */
static uint8_t  s_rxReadyBuf[UART_RX_FRAME_SIZE];   /* 已收完整帧，任务读这个 */
static volatile uint16_t s_rxReadyLen = 0;          /* 已完成帧长度 */

/* ===================== 帧状态机 ===================== */
#define FRAME_HEAD_BYTE   0x3C
#define FRAME_TAIL_BYTE   0x3E
#define FRAME_MATCH_CNT   2

typedef enum
{
    STATE_WAIT_HEAD = 0,
    STATE_IN_FRAME,
    STATE_WAIT_TAIL
} FrameState_t;

/* ===================== 内部静态函数声明 ===================== */
void APP_ErrorHandler(void);

/**
  * @brief  UART1 外设初始化入口
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

    __HAL_UART_ENABLE_IT(&UartHandle, UART_IT_RXNE);

    xUartTxDoneSem = xSemaphoreCreateBinaryStatic(&xUartTxDoneSemBuffer);
    xSemaphoreGive(xUartTxDoneSem);

    xUartTxMutex = xSemaphoreCreateMutexStatic(&xUartTxMutexBuffer);

    xUartRxNewDataSem = xSemaphoreCreateBinaryStatic(&xUartRxNewDataSemBuffer);
}

/**
  * @brief UART MSP Initialization
  */
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(huart->Instance == UART1)
    {
        __HAL_RCC_UART1_CLK_ENABLE();
        __HAL_RCC_DMA1_CLK_ENABLE();
        __HAL_RCC_GPIOF_CLK_ENABLE();

        /**UART1 GPIO Configuration
        PF0     ------> UART1_TX
        PF1     ------> UART1_RX
        */
        GPIO_InitStruct.Pin       = GPIO_PIN_0 | GPIO_PIN_1;
        GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull      = GPIO_PULLUP;
        GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF9_UART1;
        HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

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
        HAL_DMA_ChannelMap(&hdma_uart_tx, DMA_CHANNEL_MAP_UART1_TX);
        __HAL_LINKDMA(huart, hdmatx, hdma_uart_tx);

        HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);

        HAL_NVIC_SetPriority(UART1_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(UART1_IRQn);
    }
}

/**
  * @brief  DMA 阻塞发送数据
  */
int Uart_SendDMA(const uint8_t *data, uint16_t len, uint32_t timeout)
{
    BaseType_t ret;

    if (data == NULL || len == 0)
    {
        return -1;
    }

    if (xSemaphoreTake(xUartTxMutex, timeout) != pdTRUE)
    {
        return -1;
    }

    xSemaphoreTake(xUartTxDoneSem, 0);

    if (HAL_UART_Transmit_DMA(&UartHandle, (uint8_t *)data, len) != HAL_OK)
    {
        xSemaphoreGive(xUartTxMutex);
        return -1;
    }

    ret = xSemaphoreTake(xUartTxDoneSem, timeout);
    xSemaphoreGive(xUartTxMutex);

    return (ret == pdTRUE) ? 0 : -1;
}

/**
  * @brief  读取最新一帧数据（任务上下文调用）
  * @note   读完后清空就绪标志，下次收到新帧才会再次返回数据
  */
uint16_t Uart_Read(uint8_t *data, uint16_t maxLen)
{
    uint16_t len;
    uint32_t primask;

    primask = __get_PRIMASK();
    __set_PRIMASK(1);

    len = s_rxReadyLen;
    if (len > maxLen)
    {
        len = maxLen;
    }
    memcpy(data, s_rxReadyBuf, len);
    s_rxReadyLen = 0;   /* 读完即清空，避免重复处理同一帧 */

    __set_PRIMASK(primask);

    return len;
}

/**
  * @brief  UART1 全局中断服务函数
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
            /* 状态1：等待连续2个帧头 */
            case STATE_WAIT_HEAD:
                if (rxByte == FRAME_HEAD_BYTE)
                {
                    s_matchCnt++;
                    if (s_matchCnt >= FRAME_MATCH_CNT)
                    {
                        /* 匹配到帧头，开始新帧，写入2个帧头字节 */
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

            /* 状态2：帧内数据接收 */
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

            /* 状态3：等待第2个帧尾 */
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
                        /* 完整帧收完，拷贝到就绪缓冲区（关中断已保证，这里就是中断上下文） */
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
  * @brief  TX DMA 中断服务函数
  */
void DMA1_Channel2_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_uart_tx);
}

/**
  * @brief  发送完成回调
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


