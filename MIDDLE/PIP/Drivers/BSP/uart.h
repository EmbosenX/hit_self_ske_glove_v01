/**
  ******************************************************************************
  * @file    uart.h
  * @brief   UART1 驱动头文件 (PF0-RX / PF1-TX)
  ******************************************************************************
  */
#ifndef __UART_H
#define __UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "py32f0xx_hal.h"
#include "FreeRTOS.h"
#include "semphr.h"

/* 外设句柄声明 */
extern UART_HandleTypeDef UartHandle;
extern DMA_HandleTypeDef hdma_uart1_tx;
extern SemaphoreHandle_t xUartRxNewDataSem;

/* 对外接口 */
void Uart_Init(void);
int Uart_SendDMA(const uint8_t *data, uint16_t len, uint32_t timeout);
uint16_t Uart_Read(uint8_t *data, uint16_t maxLen);

/* 中断服务函数声明 */
void UART1_IRQHandler(void);
void DMA1_Channel2_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* __UART_H */


