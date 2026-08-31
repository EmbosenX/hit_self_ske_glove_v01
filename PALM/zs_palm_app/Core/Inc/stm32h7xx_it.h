/* ==================== 用户代码开始 ==================== */
/**
  ******************************************************************************
  * @file    stm32h7xx_it.h
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* ==================== 用户代码结束 ==================== */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32H7xx_IT_H
#define __STM32H7xx_IT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Private includes ----------------------------------------------------------*/
/* ==================== 用户代码开始 ==================== */

/* ==================== 用户代码结束 ==================== */

/* Exported types ------------------------------------------------------------*/
/* ==================== 用户代码开始 ==================== */

/* ==================== 用户代码结束 ==================== */

/* Exported constants --------------------------------------------------------*/
/* ==================== 用户代码开始 ==================== */

/* ==================== 用户代码结束 ==================== */

/* Exported macro ------------------------------------------------------------*/
/* ==================== 用户代码开始 ==================== */

/* ==================== 用户代码结束 ==================== */

/* ==================== 导出函数 ==================== */
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void DebugMon_Handler(void);
void SysTick_Handler(void);
void DMA1_Stream0_IRQHandler(void);
void DMA1_Stream1_IRQHandler(void);
void DMA1_Stream2_IRQHandler(void);
void DMA1_Stream3_IRQHandler(void);
void DMA1_Stream4_IRQHandler(void);
void DMA1_Stream5_IRQHandler(void);
void DMA1_Stream6_IRQHandler(void);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
void DMA1_Stream7_IRQHandler(void);
void UART4_IRQHandler(void);
void UART5_IRQHandler(void);
void DMA2_Stream0_IRQHandler(void);
void DMA2_Stream1_IRQHandler(void);
void DMA2_Stream2_IRQHandler(void);
void DMA2_Stream3_IRQHandler(void);
void UART7_IRQHandler(void);
void OTG_FS_IRQHandler(void);
void CRS_IRQHandler(void);
/* ==================== 用户代码开始 ==================== */

/* ==================== 用户代码结束 ==================== */

#ifdef __cplusplus
}
#endif

#endif /* __STM32H7xx_IT_H */
