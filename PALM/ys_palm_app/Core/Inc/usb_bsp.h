/**
 ******************************************************************************
 * @file    usb_bsp.h
 * @brief   USB设备端BSP驱动头文件
 ******************************************************************************
 */

#ifndef __USB_BSP_H__
#define __USB_BSP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "cmsis_os2.h"
#include <stdint.h>

/* 单次最大发送长度，支持2KB级数据包 */
#define USB_CDC_MAX_TX_LEN    2048U

uint8_t UsbCdc_IsEnumerated(void);
uint8_t UsbCdc_IsVbusPresent(void);
/**
  * @brief  USB CDC BSP初始化（创建同步信号量）
  */
void UsbCdc_Init(void);

/**
  * @brief  USB CDC阻塞发送不定长数据包
  * @param  data 发送数据首地址
  * @param  len  发送字节数，最大2048
  * @retval HAL_OK：发送成功；HAL_ERROR：参数错误/发送失败
  */
HAL_StatusTypeDef UsbCdc_Send(uint8_t *data, uint16_t len);

/**
  * @brief  从接收队列读取单字节（任务上下文调用）
  * @param  pByte   输出字节指针
  * @param  timeout 超时时间，osWaitForever为永久等待
  * @retval osOK：读取成功；其他：超时/参数错误
  */
osStatus_t UsbCdc_ReadByte(uint8_t *pByte, uint32_t timeout);

/**
  * @brief  USB接收数据处理（在CDC接收回调中调用，中断上下文）
  */
void UsbCdc_RxHandler(uint8_t *buf, uint32_t len);

/**
  * @brief  USB发送完成回调处理（在CDC发送完成回调中调用）
  */
void UsbCdc_TxCpltHandler(void);

uint16_t usart_crc16(const uint8_t *data, uint16_t size);
#ifdef __cplusplus
}
#endif

#endif /* __USB_BSP_H__ */

