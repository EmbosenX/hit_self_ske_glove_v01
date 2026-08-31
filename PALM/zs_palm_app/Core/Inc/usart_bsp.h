/**
 ******************************************************************************
 * @file    usart_bsp.h
 * @brief   USART串口BSP驱动头文件
 ******************************************************************************
 */

#ifndef __USART_BSP_H__
#define __USART_BSP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "usart.h"
#include "cmsis_os2.h"
#include "app_tac_config.h"
#include "usb_bsp.h"

/* 串口索引定义 */
#define USART_BSP_IDX_1       0U
#define USART_BSP_IDX_2       1U
#define USART_BSP_IDX_3       2U
#define USART_BSP_IDX_4       3U
#define USART_BSP_IDX_5       4U
#define USART_BSP_IDX_7       5U
#define USART_BSP_NUM         6U

/* 接收缓冲区大小（DMA循环缓冲区） */
#define USART_RX_DMA_BUF_SIZE 1024U

/* 单帧最大长度（含帧头帧尾） */
#define USART_FRAME_MAX_PAYLOAD  512U

/* 串口帧结构体 */
typedef struct
{
    uint8_t  data[USART_FRAME_MAX_PAYLOAD];
    uint16_t len;
} usart_frame_t;

/* 串口信息表 */
typedef struct
{
    UART_HandleTypeDef   *huart;         /* 串口句柄 */
    uint8_t              *rx_buf;        /* DMA原始接收缓冲区 */
    uint16_t             rx_frame_len;   /* 单次空闲接收总字节数（调试用） */
    osSemaphoreId_t      tx_sem;         /* 发送完成同步信号量 */
    osSemaphoreId_t      rx_sem;         /* 新帧通知信号量（二进制） */
    uint8_t              tx_busy;        /* 发送忙标志 */

    /* 帧解析状态机 */
    uint8_t              parse_state;
    uint16_t             frame_wr_idx;
    uint8_t              frame_buf[USART_FRAME_MAX_PAYLOAD]; /* 解析临时缓冲 */

    /* 最新帧缓存（永远保留最新一帧，覆盖式写入） */
    usart_frame_t        latest_frame;
    volatile uint8_t     new_frame_flag; /* 新帧就绪标志 */
} usart_bsp_t;

/**
  * @brief  串口BSP初始化
  */
void UsartBsp_Init(void);

/**
  * @brief  串口DMA阻塞发送
  */
HAL_StatusTypeDef UsartBsp_Send(uint8_t idx, const uint8_t *data, uint16_t len);

/**
  * @brief  阻塞等待并读取最新一帧数据
  * @param  idx     串口索引
  * @param  pFrame  输出帧数据指针
  * @param  timeout 超时时间，osWaitForever永久等待
  * @retval osOK成功读取到新帧，osErrorTimeout超时
  */
osStatus_t UsartBsp_ReadLatestFrame(uint8_t idx, usart_frame_t *pFrame, uint32_t timeout);

/**
  * @brief  非阻塞查询是否有新帧
  * @retval 1有新帧，0无新帧
  */
uint8_t UsartBsp_HasNewFrame(uint8_t idx);

uint8_t* pGetUsartBuff(uint8_t idx);
usart_bsp_t* pGetUsartTable(uint8_t idx);

uint16_t finger_data_tx_frame(uint8_t AREA,uint8_t *pTxBuff);
#ifdef __cplusplus
}
#endif

#endif /* __USART_BSP_H__ */


