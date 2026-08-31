/* ==================== 用户代码开始 ==================== */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* ==================== 用户代码开始 ==================== */

/* ==================== 用户代码结束 ==================== */

/* ==================== 用户代码开始 ==================== */

typedef enum
{
    RED = 0U,
    GREEN = 1U,
    BLUE = 2U,

} rgb_t;

/* ==================== 用户代码结束 ==================== */

void MX_GPIO_Init(void);

/* ==================== 用户代码开始 ==================== */
void RGB_led_set(rgb_t led,  GPIO_PinState enable);
void RGB_led_Toggle(rgb_t led);
/* ==================== 用户代码结束 ==================== */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

