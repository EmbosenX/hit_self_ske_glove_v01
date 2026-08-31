/**
  ******************************************************************************
  * @file    usart.h
  * @brief   USART1 驱动头文件
  ******************************************************************************
  */
#ifndef __USART_H
#define __USART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "py32f0xx_hal.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "main.h"
#include "py32f032_hal_sci.h"
/* 外设句柄声明 */
extern UART_HandleTypeDef husart1;
extern DMA_HandleTypeDef  hdma_usart1_tx;
extern SCI_HandleTypeDef hsci;
extern SemaphoreHandle_t xRxNewDataSem;
/* 对外接口 */
void Usart_Init(void);
int Usart_SendDMA(const uint8_t *data, uint16_t len, uint32_t timeout);
uint16_t Usart_Read(uint8_t *data, uint16_t maxLen);
void Usart_DmaTx_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* __USART_H */



