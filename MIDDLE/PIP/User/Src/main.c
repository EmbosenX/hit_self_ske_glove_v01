/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 Puya Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by Puya under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "app_usart_task.h"
#include "app_sample_task.h"
/* ==================== 私有宏定义 ==================== */
/* ==================== 私有变量 ==================== */
/* Private user code ---------------------------------------------------------*/
/* ==================== 私有宏定义 ==================== */
/* ==================== 私有函数声明 ==================== */
static void APP_SystemClockConfig(void);

/*******************************************************************************
 * FreeRTOS 静态分配系统回调（必需）
 ******************************************************************************/
/* 空闲任务：静态控制块 + 任务栈 */
static StaticTask_t xIdleTaskTCB;
static StackType_t  uxIdleTaskStack[128];  /* 空闲任务栈很小，128Word足够 */
/* 定时器服务任务：静态控制块 + 任务栈 */
static StaticTask_t xTimerTaskTCB;
static StackType_t  uxTimerTaskStack[256]; /* 定时器任务栈，可按需调整 */
/**
 * @brief  为空闲任务提供静态内存（FreeRTOS内核回调，无需手动调用）
 */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
                                   StackType_t **ppxIdleTaskStackBuffer,
                                   uint32_t *pulIdleTaskStackSize)
{
    *ppxIdleTaskTCBBuffer   = &xIdleTaskTCB;
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;
    *pulIdleTaskStackSize   = sizeof(uxIdleTaskStack) / sizeof(StackType_t);
}
/**
 * @brief  为定时器服务任务提供静态内存（FreeRTOS内核回调，无需手动调用）
 */
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
                                    StackType_t **ppxTimerTaskStackBuffer,
                                    uint32_t *pulTimerTaskStackSize)
{
    *ppxTimerTaskTCBBuffer   = &xTimerTaskTCB;
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;
    *pulTimerTaskStackSize   = sizeof(uxTimerTaskStack) / sizeof(StackType_t);
}

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick. */
  HAL_Init();
  
  /* System clock configuration */
  APP_SystemClockConfig();
	__set_PRIMASK(1);  	
	/************************ 创建静态任务 ************************/
	APP_Sample_TaskCreate();
	APP_Usart_TaskCreate();
	/* 启动调度，开始执行任务 */
	vTaskStartScheduler();
  /* infinite loop */
  while (1)
  {
  }
}
/**
  * @brief  System clock configuration function
  * @param  None
  * @retval None
  */
static void APP_SystemClockConfig(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /* Oscillator configuration */
  RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSI; /* Select oscillator HSI, LSI */
#if defined(RCC_HSE_SUPPORT)
  RCC_OscInitStruct.OscillatorType      |= RCC_OSCILLATORTYPE_HSE; /* Select oscillator HSE */
#endif /* RCC_HSE_SUPPORT */
#if defined(RCC_LSE_SUPPORT)
  RCC_OscInitStruct.OscillatorType      |= RCC_OSCILLATORTYPE_LSE; /* Select oscillator LSE */
#endif /* RCC_LSE_SUPPORT */
  RCC_OscInitStruct.HSIState            = RCC_HSI_ON;              /* Enable HSI */
  RCC_OscInitStruct.HSIDiv              = RCC_HSI_DIV1;            /* HSI 1 frequency division */
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_8MHz; /* Configure HSI clock 8MHz */
#if defined(RCC_HSE_SUPPORT)
  RCC_OscInitStruct.HSEState            = RCC_HSE_OFF;             /* Close HSE */
  /*RCC_OscInitStruct.HSEFreq             = RCC_HSE_24_32MHz;*/
#endif /* RCC_HSE_SUPPORT */
  RCC_OscInitStruct.LSIState            = RCC_LSI_OFF;             /* Close LSI */
#if defined(RCC_LSE_SUPPORT)
  RCC_OscInitStruct.LSEState            = RCC_LSE_OFF;             /* Close LSE */
  /*RCC_OscInitStruct.LSEDriver           = RCC_LSEDRIVE_MEDIUM;*/
#endif /* RCC_LSE_SUPPORT */
#if defined(RCC_PLL_SUPPORT)
  RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_ON;             /* Close PLL */
  RCC_OscInitStruct.PLL.PLLSource       = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL          = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL.PLLDiv          = RCC_PLL_DIV1;
#endif /* RCC_PLL_SUPPORT */
  /* Configure oscillator */
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  /* Clock source configuration */
  RCC_ClkInitStruct.ClockType     = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK; /* Choose to configure clock HCLK, SYSCLK, PCLK */
  RCC_ClkInitStruct.SYSCLKSource  = RCC_CFGR_SW_PLL; /* Select HSISYS as the system clock */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;         /* AHB clock 1 division */
  RCC_ClkInitStruct.APBCLKDivider = RCC_HCLK_DIV1;           /* APB clock 1 division */
  /* Configure clock source */
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    APP_ErrorHandler();
  }
}
/**
  * @brief  Error executing function.
  * @param  None
  * @retval None
  */
void APP_ErrorHandler(void)
{
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* Users can add their own printing information as needed,
     for example: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
