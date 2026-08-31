/**
 ******************************************************************************
 * @file    adc_bat.h
 * @brief   源文件
 ******************************************************************************
 */
#ifndef __ADC_BAT_H__
#define __ADC_BAT_H__

#include "hc32_ll.h"
#include "FreeRTOS.h"
#include "task.h"

/* ==================== 功能接口 ==================== */
void ADC_BAT_Init(void);

/**
 * @brief 单次ADC原始采样
 * @retval ADC原始12bit数值 0~4095
 */
uint16_t BAT_ADC_SingleSample(void);

/**
 * @brief 多次采样均值滤波
 * @param u8SampleCnt 采样次数
 * @retval ADC均值
 */
uint16_t BAT_ADC_ReadAvg(uint8_t u8SampleCnt);

/**
 * @brief 获取电池电压 mV
 * @retval 电池电压（单位mV）
 */
uint16_t BAT_GetVoltage_mV(void);

#endif


