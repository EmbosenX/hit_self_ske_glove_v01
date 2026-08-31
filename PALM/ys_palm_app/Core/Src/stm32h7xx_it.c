/* ==================== 用户代码开始 ==================== */
/**
  ******************************************************************************
  * @file    stm32h7xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32h7xx_it.h"
#include "FreeRTOS.h"
#include "task.h"
/* Private includes ----------------------------------------------------------*/
/* ==================== 用户代码开始 ==================== */
/* ==================== 用户代码结束 ==================== */

/* ==================== 私有类型定义 ==================== */
/* ==================== 用户代码开始 ==================== */

/* ==================== 用户代码结束 ==================== */

/* ==================== 私有宏定义 ==================== */
/* ==================== 用户代码开始 ==================== */

/* ==================== 用户代码结束 ==================== */

/* ==================== 私有宏定义 ==================== */
/* ==================== 用户代码开始 ==================== */

/* ==================== 用户代码结束 ==================== */

/* ==================== 私有变量 ==================== */
/* ==================== 用户代码开始 ==================== */

/* ==================== 用户代码结束 ==================== */

/* ==================== 私有函数声明 ==================== */
/* ==================== 用户代码开始 ==================== */

/* ==================== 用户代码结束 ==================== */

/* Private user code ---------------------------------------------------------*/
/* ==================== 用户代码开始 ==================== */

/* ==================== 用户代码结束 ==================== */

/* External variables --------------------------------------------------------*/
extern PCD_HandleTypeDef hpcd_USB_OTG_FS;
extern DMA_HandleTypeDef hdma_uart4_rx;
extern DMA_HandleTypeDef hdma_uart4_tx;
extern DMA_HandleTypeDef hdma_uart5_rx;
extern DMA_HandleTypeDef hdma_uart5_tx;
extern DMA_HandleTypeDef hdma_uart7_rx;
extern DMA_HandleTypeDef hdma_uart7_tx;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern DMA_HandleTypeDef hdma_usart3_tx;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart7;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
/* ==================== 用户代码开始 ==================== */

/* ==================== 用户代码结束 ==================== */

/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
  /* ==================== 用户代码开始 ==================== */
   while (1)
  {
  }
  /* ==================== 用户代码结束 ==================== */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
  while (1)
  {
    /* ==================== 用户代码开始 ==================== */
    /* ==================== 用户代码结束 ==================== */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
  while (1)
  {
    /* ==================== 用户代码开始 ==================== */
    /* ==================== 用户代码结束 ==================== */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
  while (1)
  {
    /* ==================== 用户代码开始 ==================== */
    /* ==================== 用户代码结束 ==================== */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
  while (1)
  {
    /* ==================== 用户代码开始 ==================== */
    /* ==================== 用户代码结束 ==================== */
  }
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
  HAL_IncTick();
#if (INCLUDE_xTaskGetSchedulerState == 1 )
  if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
  {
#endif /* INCLUDE_xTaskGetSchedulerState */
  xPortSysTickHandler();
#if (INCLUDE_xTaskGetSchedulerState == 1 )
  }
#endif /* INCLUDE_xTaskGetSchedulerState */
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
}

/******************************************************************************/
/* STM32H7xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32h7xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 stream0 global interrupt.
  */
void DMA1_Stream0_IRQHandler(void)
{
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
  HAL_DMA_IRQHandler(&hdma_uart4_rx);
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
}

/**
  * @brief This function handles DMA1 stream1 global interrupt.
  */
void DMA1_Stream1_IRQHandler(void)
{
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
  HAL_DMA_IRQHandler(&hdma_uart4_tx);
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
}

/**
  * @brief This function handles DMA1 stream2 global interrupt.
  */
void DMA1_Stream2_IRQHandler(void)
{
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
  HAL_DMA_IRQHandler(&hdma_uart5_rx);
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
}

/**
  * @brief This function handles DMA1 stream3 global interrupt.
  */
void DMA1_Stream3_IRQHandler(void)
{
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
  HAL_DMA_IRQHandler(&hdma_uart5_tx);
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
}

/**
  * @brief This function handles DMA1 stream4 global interrupt.
  */
void DMA1_Stream4_IRQHandler(void)
{
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
  HAL_DMA_IRQHandler(&hdma_uart7_rx);
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
}

/**
  * @brief This function handles DMA1 stream5 global interrupt.
  */
void DMA1_Stream5_IRQHandler(void)
{
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
  HAL_DMA_IRQHandler(&hdma_uart7_tx);
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
}

/**
  * @brief This function handles DMA1 stream6 global interrupt.
  */
void DMA1_Stream6_IRQHandler(void)
{
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
  HAL_DMA_IRQHandler(&hdma_usart1_rx);
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
  HAL_UART_IRQHandler(&huart1);
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
}

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
  HAL_UART_IRQHandler(&huart2);
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
}

/**
  * @brief This function handles USART3 global interrupt.
  */
void USART3_IRQHandler(void)
{
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
  HAL_UART_IRQHandler(&huart3);
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
}

/**
  * @brief This function handles DMA1 stream7 global interrupt.
  */
void DMA1_Stream7_IRQHandler(void)
{
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
  HAL_DMA_IRQHandler(&hdma_usart1_tx);
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
}

/**
  * @brief This function handles UART4 global interrupt.
  */
void UART4_IRQHandler(void)
{
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
  HAL_UART_IRQHandler(&huart4);
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
}

/**
  * @brief This function handles UART5 global interrupt.
  */
void UART5_IRQHandler(void)
{
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
  HAL_UART_IRQHandler(&huart5);
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
}

/**
  * @brief This function handles DMA2 stream0 global interrupt.
  */
void DMA2_Stream0_IRQHandler(void)
{
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
  HAL_DMA_IRQHandler(&hdma_usart2_rx);
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
}

/**
  * @brief This function handles DMA2 stream1 global interrupt.
  */
void DMA2_Stream1_IRQHandler(void)
{
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
  HAL_DMA_IRQHandler(&hdma_usart2_tx);
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
}

/**
  * @brief This function handles DMA2 stream2 global interrupt.
  */
void DMA2_Stream2_IRQHandler(void)
{
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
  HAL_DMA_IRQHandler(&hdma_usart3_rx);
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
}

/**
  * @brief This function handles DMA2 stream3 global interrupt.
  */
void DMA2_Stream3_IRQHandler(void)
{
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
  HAL_DMA_IRQHandler(&hdma_usart3_tx);
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
}

/**
  * @brief This function handles UART7 global interrupt.
  */
void UART7_IRQHandler(void)
{
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
  HAL_UART_IRQHandler(&huart7);
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
}

/**
  * @brief This function handles USB On The Go FS global interrupt.
  */
void OTG_FS_IRQHandler(void)
{
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
  HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS);
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
}

/**
  * @brief This function handles CRS global interrupt.
  */
void CRS_IRQHandler(void)
{
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
  HAL_RCCEx_CRS_IRQHandler();
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */
}

/* ==================== 用户代码开始 ==================== */

/* ==================== 用户代码结束 ==================== */
