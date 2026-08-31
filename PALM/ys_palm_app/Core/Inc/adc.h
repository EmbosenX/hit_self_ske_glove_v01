/* ==================== 用户代码开始 ==================== */
/**
  ******************************************************************************
  * @file    adc.h
  * @brief   This file contains all the function prototypes for
  *          the adc.c file
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
#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* ==================== 用户代码开始 ==================== */

/* ==================== 用户代码结束 ==================== */

extern ADC_HandleTypeDef hadc1;

/* ==================== 用户代码开始 ==================== */

/* ==================== 用户代码结束 ==================== */

void MX_ADC1_Init(void);

/* ==================== 用户代码开始 ==================== */
int32_t AdcPollingSample(uint16_t *pu16AdcVal);
/* ==================== 用户代码结束 ==================== */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */

