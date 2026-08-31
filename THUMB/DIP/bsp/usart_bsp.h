/**
 ******************************************************************************
 * @file    usart_bsp.h
 * @brief   USART串口BSP驱动头文件
 ******************************************************************************
 */

#ifndef __USART_BSP_H__
#define __USART_BSP_H__

#include <stdint.h>
#include "hc32_ll.h"

/******************************************************************************
 * 配置项：已适配 PA11-RX / PA12-TX / USART1
 ******************************************************************************/
/* 串口号与波特率 */
#define USART_BSP_UNIT                  (CM_USART1)
#define USART_BSP_BAUDRATE              (921600UL)
#define USART_BSP_MAX_FRAME_LEN         (768U)

/* RX引脚：PA11 */
#define USART_BSP_RX_PORT               (GPIO_PORT_A)
#define USART_BSP_RX_PIN                (GPIO_PIN_12)
#define USART_BSP_RX_FUNC               (GPIO_FUNC_33)   /* USART1_RX */

/* TX引脚：PA12 */
#define USART_BSP_TX_PORT               (GPIO_PORT_A)
#define USART_BSP_TX_PIN                (GPIO_PIN_11)
#define USART_BSP_TX_FUNC               (GPIO_FUNC_32)   /* USART1_TX */

/* 接收超时时长（单位：比特位） */
#define USART_BSP_TIMEOUT_BITS          (2000U)

/******************************************************************************
 * 对外接口函数
 ******************************************************************************/
/**
 * @brief  初始化USART+DMA+超时定时器
 */
void USART_BSP_Init(void);

/**
 * @brief  DMA方式发送一帧数据（非阻塞）
 * @param  pu8Data 发送数据指针
 * @param  u16Len  数据长度
 * @retval LL_OK=成功，其他=失败
 */
int32_t USART_BSP_Send(const uint8_t *pu8Data, uint16_t u16Len);

/**
 * @brief  查询是否收到完整一帧
 * @retval 1=有完整帧，0=无
 */
uint8_t USART_BSP_IsRxFrameDone(void);

/**
 * @brief  获取接收到的一帧数据
 * @param  pu8Buf     输出缓冲区
 * @param  u16BufLen  缓冲区大小
 * @retval 实际接收长度
 */
uint16_t USART_BSP_GetRxFrame(uint8_t *pu8Buf, uint16_t u16BufLen);

/**
 * @brief  清除接收完成标志，开启下一次接收
 */
void USART_BSP_ClearRxFlag(void);

/******************************************************************************
 * 弱回调函数：应用层可重写，在中断上下文执行
 ******************************************************************************/
/**
 * @brief  接收一帧完成回调（弱定义）
 * @param  u16Len  本次接收数据长度
 */
void USART_BSP_RxCpltCallback(uint16_t u16Len);

/**
 * @brief  发送完成回调（弱定义）
 */
void USART_BSP_TxCpltCallback(void);

#endif /* __USART_BSP_H__ */


