/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */


/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */
/**
  * @brief  微秒级忙等延时（while循环阻塞CPU）
  * @param  us: 延时微秒数，建议单调用不超过1000us
  * @note   适配 48MHz 系统主频，O0/O1优化等级
  */
void delay_us(uint32_t us)
{
    volatile uint32_t loop_cnt;
    // 48MHz 下经验值：1μs 约对应 12 次空循环（可根据实际效果微调）
    const uint32_t cycles_per_us = 12;

    while (us--)
    {
        loop_cnt = cycles_per_us;
        while (loop_cnt--);
    }
}

/**
  * @brief  毫秒级忙等延时（while循环阻塞CPU）
  * @param  ms: 延时毫秒数
  */
void delay_ms(uint32_t ms)
{
    while (ms--)
    {
        delay_us(1000);
    }
}

/* USER CODE END 1 */



/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
