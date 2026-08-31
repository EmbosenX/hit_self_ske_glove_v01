/**
 *******************************************************************************
 * @file  usb/usb_dev_cdc/source/main.c
 * @brief Example CDC device.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-10-31       CDT             Add USB core ID select function
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2025, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "main.h"
#include "ev_hc32f460_lqfp100_v2.h"
#include "app_sample_task.h"
#include "app_usart_task.h"

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
/**
 * @addtogroup HC32F460_DDL_Applications
 * @{
 */
/* unlock/lock peripheral */
#define EXAMPLE_PERIPH_WE               (LL_PERIPH_GPIO | LL_PERIPH_EFM | LL_PERIPH_FCG | \
                                         LL_PERIPH_PWC_CLK_RMU | LL_PERIPH_SRAM)
#define EXAMPLE_PERIPH_WP               (LL_PERIPH_EFM | LL_PERIPH_FCG | LL_PERIPH_SRAM)

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

/*******************************************************************************
 * @brief  主函数
 ******************************************************************************/
int32_t main(void)
{
    /* Unlock peripherals or registers */
    LL_PERIPH_WE(EXAMPLE_PERIPH_WE);
    BSP_RC_CLK_Init();

		__set_PRIMASK(1);  	
		/************************ 创建静态任务 ************************/
		APP_Sample_TaskCreate();
		APP_Usart_TaskCreate();
		/* 启动调度，开始执行任务 */
		vTaskStartScheduler();
    for (;;) {
    }
}


/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
