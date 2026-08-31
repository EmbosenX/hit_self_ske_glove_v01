/**
 ******************************************************************************
 * @file    usart_bsp.c
 * @brief   USART串口BSP驱动，实现DMA收发和空闲中断接收
 ******************************************************************************
 */

#include "usart_bsp.h"
#include <string.h>
#include "FreeRTOS.h"
#include "cmsis_compiler.h"

/* 帧解析状态机状态定义 */
#define PARSE_STATE_WAIT_HEAD1  0U
#define PARSE_STATE_WAIT_HEAD2  1U
#define PARSE_STATE_RECV_DATA   2U
#define PARSE_STATE_WAIT_TAIL1  3U

/* DMA接收原始缓冲区 */
static uint8_t s_rx_buf1[USART_RX_DMA_BUF_SIZE];
static uint8_t s_rx_buf2[USART_RX_DMA_BUF_SIZE];
static uint8_t s_rx_buf3[USART_RX_DMA_BUF_SIZE];
static uint8_t s_rx_buf4[USART_RX_DMA_BUF_SIZE];
static uint8_t s_rx_buf5[USART_RX_DMA_BUF_SIZE];
static uint8_t s_rx_buf7[USART_RX_DMA_BUF_SIZE];

/* 备份缓冲区（保留兼容） */
static uint8_t s_rx_buf[USART_BSP_NUM][USART_RX_DMA_BUF_SIZE];

/* 信号量静态控制块 */
static StaticSemaphore_t s_tx_sem_cb[USART_BSP_NUM];
static StaticSemaphore_t s_rx_sem_cb[USART_BSP_NUM];

static usart_bsp_t s_usart_table[USART_BSP_NUM] =
{
    [USART_BSP_IDX_1] = { &huart1, s_rx_buf1, 0, NULL, NULL, 0, 0, 0, {0}, {{0},0}, 0 },
    [USART_BSP_IDX_2] = { &huart2, s_rx_buf2, 0, NULL, NULL, 0, 0, 0, {0}, {{0},0}, 0 },
    [USART_BSP_IDX_3] = { &huart3, s_rx_buf3, 0, NULL, NULL, 0, 0, 0, {0}, {{0},0}, 0 },
    [USART_BSP_IDX_4] = { &huart4, s_rx_buf4, 0, NULL, NULL, 0, 0, 0, {0}, {{0},0}, 0 },
    [USART_BSP_IDX_5] = { &huart5, s_rx_buf5, 0, NULL, NULL, 0, 0, 0, {0}, {{0},0}, 0 },
    [USART_BSP_IDX_7] = { &huart7, s_rx_buf7, 0, NULL, NULL, 0, 0, 0, {0}, {{0},0}, 0 },
};
static uint8_t usart_find_idx(UART_HandleTypeDef *huart)
{
    for (uint8_t i = 0; i < USART_BSP_NUM; i++)
    {
        if (s_usart_table[i].huart->Instance == huart->Instance)
        {
            return i;
        }
    }
    return USART_BSP_NUM;
}

void UsartBsp_Init(void)
{
    for (uint8_t i = 0; i < USART_BSP_NUM; i++)
    {
        /* 发送同步二进制信号量 */
        osSemaphoreAttr_t sem_attr_tx = {0};
        sem_attr_tx.cb_mem  = &s_tx_sem_cb[i];
        sem_attr_tx.cb_size = sizeof(StaticSemaphore_t);
        s_usart_table[i].tx_sem = osSemaphoreNew(1U, 0U, &sem_attr_tx);

        /* 新帧通知二进制信号量：初始无信号，新帧到来释放一次 */
        osSemaphoreAttr_t sem_attr_rx = {0};
        sem_attr_rx.cb_mem  = &s_rx_sem_cb[i];
        sem_attr_rx.cb_size = sizeof(StaticSemaphore_t);
        s_usart_table[i].rx_sem = osSemaphoreNew(1U, 0U, &sem_attr_rx);

        s_usart_table[i].tx_busy = 0U;
        s_usart_table[i].new_frame_flag = 0U;

        /* 初始化帧解析状态机 */
        s_usart_table[i].parse_state = PARSE_STATE_WAIT_HEAD1;
        s_usart_table[i].frame_wr_idx = 0U;
        memset(s_usart_table[i].frame_buf, 0, sizeof(s_usart_table[i].frame_buf));
        memset(&s_usart_table[i].latest_frame, 0, sizeof(usart_frame_t));

        /* 启动DMA空闲接收 */
        HAL_UARTEx_ReceiveToIdle_DMA(s_usart_table[i].huart,
                                      s_usart_table[i].rx_buf,
                                      USART_RX_DMA_BUF_SIZE);
        __HAL_DMA_DISABLE_IT(s_usart_table[i].huart->hdmarx, DMA_IT_HT);
    }
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    uint8_t idx = usart_find_idx(huart);
    if (idx >= USART_BSP_NUM) return;

    usart_bsp_t *p = &s_usart_table[idx];
    uint8_t *p_data = p->rx_buf;

    /* 1. STM32H7 必加：无效化DCache */
    SCB_InvalidateDCache_by_Addr((uint32_t *)p->rx_buf, Size);

    /* 2. 逐字节状态机解析帧头帧尾 */
    for (uint16_t i = 0; i < Size; i++)
    {
        uint8_t byte = p_data[i];

        switch (p->parse_state)
        {
            case PARSE_STATE_WAIT_HEAD1:
                if (byte == 0x3C)
                {
                    p->frame_wr_idx = 0U;
                    if (p->frame_wr_idx < USART_FRAME_MAX_PAYLOAD)
                    {
                        p->frame_buf[p->frame_wr_idx++] = byte;
                    }
                    p->parse_state = PARSE_STATE_WAIT_HEAD2;
                }
                break;

            case PARSE_STATE_WAIT_HEAD2:
                if (byte == 0x3C)
                {
                    if (p->frame_wr_idx < USART_FRAME_MAX_PAYLOAD)
                    {
                        p->frame_buf[p->frame_wr_idx++] = byte;
                    }
                    p->parse_state = PARSE_STATE_RECV_DATA;
                }
                else
                {
                    p->frame_wr_idx = 0U;
                    p->parse_state = PARSE_STATE_WAIT_HEAD1;
                }
                break;

            case PARSE_STATE_RECV_DATA:
                if (byte == 0x3E)
                {
                    if (p->frame_wr_idx < USART_FRAME_MAX_PAYLOAD)
                    {
                        p->frame_buf[p->frame_wr_idx++] = byte;
                    }
                    else
                    {
                        p->parse_state = PARSE_STATE_WAIT_HEAD1;
                        p->frame_wr_idx = 0U;
                        break;
                    }
                    p->parse_state = PARSE_STATE_WAIT_TAIL1;
                }
                else
                {
                    if (p->frame_wr_idx < USART_FRAME_MAX_PAYLOAD)
                    {
                        p->frame_buf[p->frame_wr_idx++] = byte;
                    }
                    else
                    {
                        p->parse_state = PARSE_STATE_WAIT_HEAD1;
                        p->frame_wr_idx = 0U;
                    }
                }
                break;

            case PARSE_STATE_WAIT_TAIL1:
                if (byte == 0x3E)
                {
                    if (p->frame_wr_idx < USART_FRAME_MAX_PAYLOAD)
                    {
                        p->frame_buf[p->frame_wr_idx++] = byte;
                    }

                    /* ========== 核心：覆盖写入最新帧 ========== */
                    memcpy(p->latest_frame.data, p->frame_buf, p->frame_wr_idx);
                    p->latest_frame.len = p->frame_wr_idx;
                    p->new_frame_flag = 1U;

                    /* 释放信号量，通知任务有新帧（二进制信号量自动去重） */
                    osSemaphoreRelease(p->rx_sem);
                    /* 重置状态机，准备下一帧 */
                    p->parse_state = PARSE_STATE_WAIT_HEAD1;
                    p->frame_wr_idx = 0U;
                }
                else
                {
                    if (p->frame_wr_idx < USART_FRAME_MAX_PAYLOAD)
                    {
                        p->frame_buf[p->frame_wr_idx++] = byte;
                        p->parse_state = PARSE_STATE_RECV_DATA;
                    }
                    else
                    {
                        p->parse_state = PARSE_STATE_WAIT_HEAD1;
                        p->frame_wr_idx = 0U;
                    }
                }
                break;

            default:
                p->parse_state = PARSE_STATE_WAIT_HEAD1;
                p->frame_wr_idx = 0U;
                break;
        }
    }
		/* 重启DMA下一轮接收 */
		HAL_UARTEx_ReceiveToIdle_DMA(huart,
																	p->rx_buf,
																	USART_RX_DMA_BUF_SIZE);
		__HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);
    p->rx_frame_len = Size;
}

osStatus_t UsartBsp_ReadLatestFrame(uint8_t idx, usart_frame_t *pFrame, uint32_t timeout)
{
    if (idx >= USART_BSP_NUM || pFrame == NULL)
    {
        return osErrorParameter;
    }

    usart_bsp_t *p = &s_usart_table[idx];
    osStatus_t ret;

    /* 阻塞等待新帧通知 */
    ret = osSemaphoreAcquire(p->rx_sem, timeout);
    if (ret != osOK)
    {
        return ret;
    }

    /* 关中断保护：避免读取过程中被中断更新导致数据撕裂 */
    uint32_t primask = __get_PRIMASK();
    __disable_irq();

    memcpy(pFrame, &p->latest_frame, sizeof(usart_frame_t));
    p->new_frame_flag = 0U;

    __set_PRIMASK(primask);

    return osOK;
}

uint8_t UsartBsp_HasNewFrame(uint8_t idx)
{
    if (idx >= USART_BSP_NUM)
    {
        return 0U;
    }
    return s_usart_table[idx].new_frame_flag;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    uint8_t idx = usart_find_idx(huart);
    if (idx >= USART_BSP_NUM) return;

    s_usart_table[idx].tx_busy = 0U;
    osSemaphoreRelease(s_usart_table[idx].tx_sem);
}

HAL_StatusTypeDef UsartBsp_Send(uint8_t idx, const uint8_t *data, uint16_t len)
{
    if (idx >= USART_BSP_NUM || data == NULL || len == 0U)
    {
        return HAL_ERROR;
    }

    usart_bsp_t *p = &s_usart_table[idx];

    if (p->tx_busy)
    {
        osSemaphoreAcquire(p->tx_sem, osWaitForever);
    }
    p->tx_busy = 1U;
    /* ========== 核心修复：刷写 DCache，把 Cache 数据同步到物理内存 ========== */
    SCB_CleanDCache_by_Addr((uint32_t *)data, len);
    HAL_StatusTypeDef ret = HAL_UART_Transmit_DMA(p->huart, data, len);
    if (ret != HAL_OK)
    {
        p->tx_busy = 0U;
        return ret;
    }
    osSemaphoreAcquire(p->tx_sem, osWaitForever);
    return HAL_OK;
}

uint8_t* pGetUsartBuff(uint8_t idx)
{
    return s_rx_buf[idx];
}

usart_bsp_t* pGetUsartTable(uint8_t idx)
{
    return &s_usart_table[idx];
}

uint16_t finger_data_tx_frame(uint8_t AREA,uint8_t *pTxBuff)
{
		const tac_data_cfg_t* pTacData = GetTacDataCfg();
		uint16_t length=0, length_data=0;
	  uint16_t CRC16=0;
	
		switch(AREA)
		{
				case TAC_AREA_THUMB_DIP:break;
				case TAC_AREA_THUMB_MCP:break;
				case TAC_AREA_INDEX_DIP:break;
				case TAC_AREA_INDEX_PIP:break;
				case TAC_AREA_INDEX_MCP:break;
				case TAC_AREA_MIDDLE_DIP:break;
				case TAC_AREA_MIDDLE_PIP:break;
				case TAC_AREA_MIDDLE_MCP:break;
				case TAC_AREA_RING_DIP:break;
				case TAC_AREA_RING_PIP:break;
				case TAC_AREA_RING_MCP:break;
				case TAC_AREA_LITTLE_DIP:break;
				case TAC_AREA_LITTLE_PIP:break;
				case TAC_AREA_LITTLE_MCP:break;
				case TAC_AREA_PALM1:
						pTxBuff[0] = 0X3C;
						pTxBuff[1] = 0X3C;
						pTxBuff[2] = 0X02;
						pTxBuff[3] = 0X00;
						length_data = 4+sizeof(pTacData->palm1);
						pTxBuff[4] = (length_data>>0)&0xff;
						pTxBuff[5] = (length_data>>8)&0xff;
						pTxBuff[6] = 0x61;
						pTxBuff[7] = 0X01;
						pTxBuff[8] = TAC_COL_PALM1_END - TAC_COL_PALM1_START + 1U;
						pTxBuff[9] = TAC_ROW_PALM1_END - TAC_ROW_PALM1_START + 1U;
						memcpy(&pTxBuff[10],pTacData->palm1,sizeof(pTacData->palm1));
						CRC16 = usart_crc16(&pTxBuff[6],length_data);
						pTxBuff[10+sizeof(pTacData->palm1)] = (CRC16>>0)&0xff;
						pTxBuff[11+sizeof(pTacData->palm1)] = (CRC16>>8)&0xff;
						pTxBuff[12+sizeof(pTacData->palm1)] = 0x3E;
						pTxBuff[13+sizeof(pTacData->palm1)] = 0x3E;
						length = 14+sizeof(pTacData->palm1);
						break;
				case TAC_AREA_PALM2:break;
				default:break;
		}
		return length;
}


