/**
 ******************************************************************************
 * @file    adc.h
 * @brief   PY32F032 ADC+PGA采集驱动头文件
 *          - 2路内置PGA采集：PA9→OPA1、PB8→OPA2
 *          - 单通道软件轮询采集模式，无DMA、无中断
 *          - ADC 12位分辨率，支持软件校准
 *          - PGA增益档位：2/4/8/16倍可调
 ******************************************************************************
 */

#ifndef __ADC_H
#define __ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "py32f0xx_hal.h"
#include "main.h"
#include "gpio.h"
/* ============================================================
 *  驱动配置宏
 * ============================================================ */
#define ADC_POLL_TIMEOUT_MS       2000    /* 单次转换轮询超时时间，单位ms */

/* ============================================================
 *  类型定义
 * ============================================================ */

/**
 * @brief  ADC采集通道索引
 */
typedef enum {
    ADC_CH_PGA1 = 0,    /* 通道0：PGA1，对应PA9输入 */
    ADC_CH_PGA2 = 1,    /* 通道1：PGA2，对应PB8输入 */
		ADC_CH_END
} AdcChannel_t;

/* ============================================================
 *  公开接口
 * ============================================================ */
/**
 * @brief  ADC+PGA驱动初始化
 */
void Adc_Init(void);
uint16_t Adc_GetRawValue(AdcChannel_t ch);
/**
  * @brief  轮询读取双路OPA的ADC采样值
  * @param  adc_opa1: 存放OPA1采样结果
  * @param  adc_opa2: 存放OPA2采样结果
  * @retval HAL状态
  */
HAL_StatusTypeDef ADC_ReadDualOPA(uint16_t *adc_opa1, uint16_t *adc_opa2);
#ifdef __cplusplus
}
#endif

#endif /* __ADC_H */


