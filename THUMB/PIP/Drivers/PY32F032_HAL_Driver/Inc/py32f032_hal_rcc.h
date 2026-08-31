/**
  ******************************************************************************
  * @file    py32f032_hal_rcc.h
  * @author  MCU Application Team
  * @brief   Header file of RCC HAL module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PY32F032_HAL_RCC_H
#define __PY32F032_HAL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f032_hal_def.h"

/** @addtogroup PY32F032_HAL_Driver
  * @{
  */

/** @addtogroup RCC
  * @{
  */

/* Private constants ---------------------------------------------------------*/
/** @addtogroup RCC_Private_Constants
  * @{
  */

/** @defgroup RCC_Timeout RCC Timeout
  * @{
  */

/* Disable Backup domain write protection state change timeout */
#define RCC_DBP_TIMEOUT_VALUE          100U    /* 100 ms */
/* LSE state change timeout */
#if defined(RCC_LSE_SUPPORT)
#define RCC_LSE_TIMEOUT_VALUE          LSE_STARTUP_TIMEOUT
#endif
#define CLOCKSWITCH_TIMEOUT_VALUE      5000    /* 5 s    */
#if defined(RCC_HSE_SUPPORT)
#define HSE_TIMEOUT_VALUE              HSE_STARTUP_TIMEOUT
#endif
#define HSI_TIMEOUT_VALUE              2U      /* 2 ms (minimum Tick + 1) */
#define LSI_TIMEOUT_VALUE              2U      /* 2 ms (minimum Tick + 1) */
#if defined(RCC_PLL_SUPPORT)
#define PLL_TIMEOUT_VALUE              2U      /* 2 ms (minimum Tick + 1) */
#endif
#define AHB_24MHZ                     (24000000U)
#define AHB_48MHZ                     (48000000U)
#define AHB_72MHZ                     (72000000U)
/**
  * @}
  */

  
/* Defines used for Flags */
#define CR_REG_INDEX              1U
#define BDCR_REG_INDEX            2U
#define CSR_REG_INDEX             3U

#define RCC_FLAG_MASK             0x1FU

/* Define used for IS_RCC_CLOCKTYPE() */
#define RCC_CLOCKTYPE_ALL              (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK)  /*!< All clocktype to configure */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @addtogroup RCC_Private_Macros RCC Private Macros 
  * @{
  */
#if defined(RCC_HSE_SUPPORT) && defined(RCC_LSE_SUPPORT) 
#define IS_RCC_OSCILLATORTYPE(__OSCILLATOR__) (((__OSCILLATOR__) == RCC_OSCILLATORTYPE_NONE)                           || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSE) == RCC_OSCILLATORTYPE_HSE) || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSI) == RCC_OSCILLATORTYPE_HSI) || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSI) == RCC_OSCILLATORTYPE_LSI) || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSE) == RCC_OSCILLATORTYPE_LSE))
#elif defined(RCC_HSE_SUPPORT)
#define IS_RCC_OSCILLATORTYPE(__OSCILLATOR__) (((__OSCILLATOR__) == RCC_OSCILLATORTYPE_NONE)                           || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSE) == RCC_OSCILLATORTYPE_HSE) || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSI) == RCC_OSCILLATORTYPE_HSI) || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSI) == RCC_OSCILLATORTYPE_LSI))
#elif defined(RCC_LSE_SUPPORT)
#define IS_RCC_OSCILLATORTYPE(__OSCILLATOR__) (((__OSCILLATOR__) == RCC_OSCILLATORTYPE_NONE)                           || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSI) == RCC_OSCILLATORTYPE_HSI) || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSI) == RCC_OSCILLATORTYPE_LSI) || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSE) == RCC_OSCILLATORTYPE_LSE))
#else
#define IS_RCC_OSCILLATORTYPE(__OSCILLATOR__) (((__OSCILLATOR__) == RCC_OSCILLATORTYPE_NONE)                           || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSI) == RCC_OSCILLATORTYPE_HSI) || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSI) == RCC_OSCILLATORTYPE_LSI))
#endif

#if defined(RCC_HSE_SUPPORT)
#define IS_RCC_HSE(__HSE__)          (((__HSE__) == RCC_HSE_OFF) || ((__HSE__) == RCC_HSE_ON) || \
                                      ((__HSE__) == RCC_HSE_BYPASS))

#define IS_RCC_HSE_FREQ(__FREQ__)    (((__FREQ__) == RCC_HSE_4_6MHz) || ((__FREQ__) == RCC_HSE_6_8MHz))
#endif

#if defined(RCC_LSE_SUPPORT)
#define IS_RCC_LSE(__LSE__)          (((__LSE__) == RCC_LSE_OFF) || ((__LSE__) == RCC_LSE_ON) || \
                                      ((__LSE__) == RCC_LSE_BYPASS))
#endif

#if defined(RCC_PLL_SUPPORT)
#define IS_RCC_PLL(__PLL__)                           (((__PLL__) == RCC_PLL_NONE) || ((__PLL__) == RCC_PLL_OFF) || \
                                                       ((__PLL__) == RCC_PLL_ON))

#define IS_RCC_PLL_MUL(__MUL__)                       ((__MUL__) <= RCC_PLL_MUL18)

#define IS_RCC_PLL_DIV(__DIV__)                        (((__DIV__) == RCC_PLL_DIV1)  || ((__DIV__) == RCC_PLL_DIV2))

#if defined(RCC_HSE_SUPPORT)
#define IS_RCC_PLLSOURCE(__SOURCE__)                  (((__SOURCE__) == RCC_PLLSOURCE_HSI) || \
                                                       ((__SOURCE__) == RCC_PLLSOURCE_HSE))
#else
#define IS_RCC_PLLSOURCE(__SOURCE__)                  ((__SOURCE__) == RCC_PLLSOURCE_HSI)
#endif
#endif

#define IS_RCC_HSI(__HSI__)          (((__HSI__) == RCC_HSI_OFF) || ((__HSI__) == RCC_HSI_ON))
/*
#define IS_RCC_HSI_CALIBRATION_VALUE(__VALUE__) (((__VALUE__) == RCC_HSICALIBRATION_8MHz)     || \
                                                 ((__VALUE__) == RCC_HSICALIBRATION_24MHz)    || \
                                                 ((__VALUE__) == RCC_HSICALIBRATION_48MHz)    || \
                                                 ((__VALUE__) == RCC_HSICALIBRATION_64MHz)    || \
                                                 ((__VALUE__) == RCC_HSICALIBRATION_72MHz))
*/
#define IS_RCC_HSI_CALIBRATION_VALUE(__VALUE__) (((__VALUE__) == RCC_HSICALIBRATION_8MHz))

#define IS_RCC_HSIDIV(__DIV__)            (((__DIV__) == RCC_HSI_DIV1)  || ((__DIV__) == RCC_HSI_DIV2) || \
                                           ((__DIV__) == RCC_HSI_DIV4)  || ((__DIV__) == RCC_HSI_DIV8) || \
                                           ((__DIV__) == RCC_HSI_DIV16) || ((__DIV__) == RCC_HSI_DIV32)|| \
                                           ((__DIV__) == RCC_HSI_DIV64) || ((__DIV__) == RCC_HSI_DIV128))
                                         
#define IS_RCC_LSI(__LSI__)               (((__LSI__) == RCC_LSI_OFF) || ((__LSI__) == RCC_LSI_ON))

#define IS_RCC_CLOCKTYPE(__CLK__)         ((((__CLK__) & RCC_CLOCKTYPE_ALL) != 0x00UL) && (((__CLK__) & ~RCC_CLOCKTYPE_ALL) == 0x00UL))

#if defined(RCC_PLL_SUPPORT) && defined(RCC_HSE_SUPPORT) && defined(RCC_LSE_SUPPORT)
#define IS_RCC_SYSCLKSOURCE(__SOURCE__)   (((__SOURCE__) == RCC_SYSCLKSOURCE_HSISYS) || \
                                            ((__SOURCE__) == RCC_SYSCLKSOURCE_HSE)   || \
                                            ((__SOURCE__) == RCC_SYSCLKSOURCE_LSE)   || \
                                            ((__SOURCE__) == RCC_SYSCLKSOURCE_PLLCLK)   || \
                                            ((__SOURCE__) == RCC_SYSCLKSOURCE_LSI))
#elif defined(RCC_PLL_SUPPORT) && defined(RCC_HSE_SUPPORT)
#define IS_RCC_SYSCLKSOURCE(__SOURCE__)   (((__SOURCE__) == RCC_SYSCLKSOURCE_HSISYS) || \
                                            ((__SOURCE__) == RCC_SYSCLKSOURCE_HSE)   || \
                                            ((__SOURCE__) == RCC_SYSCLKSOURCE_PLLCLK)   || \
                                            ((__SOURCE__) == RCC_SYSCLKSOURCE_LSI))
#elif defined(RCC_PLL_SUPPORT) && defined(RCC_LSE_SUPPORT)
#define IS_RCC_SYSCLKSOURCE(__SOURCE__)   (((__SOURCE__) == RCC_SYSCLKSOURCE_HSISYS) || \
                                            ((__SOURCE__) == RCC_SYSCLKSOURCE_LSE)   || \
                                            ((__SOURCE__) == RCC_SYSCLKSOURCE_PLLCLK)   || \
                                            ((__SOURCE__) == RCC_SYSCLKSOURCE_LSI))
#elif defined(RCC_HSE_SUPPORT) && defined(RCC_LSE_SUPPORT)
#define IS_RCC_SYSCLKSOURCE(__SOURCE__)   (((__SOURCE__) == RCC_SYSCLKSOURCE_HSISYS) || \
                                            ((__SOURCE__) == RCC_SYSCLKSOURCE_HSE)   || \
                                            ((__SOURCE__) == RCC_SYSCLKSOURCE_LSE)   || \
                                            ((__SOURCE__) == RCC_SYSCLKSOURCE_LSI))
#elif defined(RCC_HSE_SUPPORT)
#define IS_RCC_SYSCLKSOURCE(__SOURCE__)   (((__SOURCE__) == RCC_SYSCLKSOURCE_HSISYS) || \
                                            ((__SOURCE__) == RCC_SYSCLKSOURCE_HSE)   || \
                                            ((__SOURCE__) == RCC_SYSCLKSOURCE_LSI))
#elif defined(RCC_LSE_SUPPORT)
#define IS_RCC_SYSCLKSOURCE(__SOURCE__)   (((__SOURCE__) == RCC_SYSCLKSOURCE_HSISYS) || \
                                            ((__SOURCE__) == RCC_SYSCLKSOURCE_LSE)   || \
                                            ((__SOURCE__) == RCC_SYSCLKSOURCE_LSI))
#else
#define IS_RCC_SYSCLKSOURCE(__SOURCE__)   (((__SOURCE__) == RCC_SYSCLKSOURCE_HSISYS) || \
                                            ((__SOURCE__) == RCC_SYSCLKSOURCE_LSI))
#endif

#define IS_RCC_HCLK(__HCLK__)             (((__HCLK__) == RCC_SYSCLK_DIV1)   || ((__HCLK__) == RCC_SYSCLK_DIV2)   || \
                                           ((__HCLK__) == RCC_SYSCLK_DIV4)   || ((__HCLK__) == RCC_SYSCLK_DIV8)   || \
                                           ((__HCLK__) == RCC_SYSCLK_DIV16)  || ((__HCLK__) == RCC_SYSCLK_DIV64)  || \
                                           ((__HCLK__) == RCC_SYSCLK_DIV128) || ((__HCLK__) == RCC_SYSCLK_DIV256) || \
                                           ((__HCLK__) == RCC_SYSCLK_DIV512))

#define IS_RCC_PCLK(__PCLK__)             (((__PCLK__) == RCC_HCLK_DIV1) || ((__PCLK__) == RCC_HCLK_DIV2) || \
                                           ((__PCLK__) == RCC_HCLK_DIV4) || ((__PCLK__) == RCC_HCLK_DIV8) || \
                                           ((__PCLK__) == RCC_HCLK_DIV16))
#if defined(RCC_HSE_SUPPORT) && defined(RCC_LSE_SUPPORT)
#define IS_RCC_RTCCLKSOURCE(__SOURCE__)   (((__SOURCE__) == RCC_RTCCLKSOURCE_NONE)       || \
                                           ((__SOURCE__) == RCC_RTCCLKSOURCE_LSE)        || \
                                           ((__SOURCE__) == RCC_RTCCLKSOURCE_LSI)        || \
                                           ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV32)  || \
                                           ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV128) || \
                                           ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV8))
#elif defined(RCC_HSE_SUPPORT)
#define IS_RCC_RTCCLKSOURCE(__SOURCE__)   (((__SOURCE__) == RCC_RTCCLKSOURCE_NONE)       || \
                                           ((__SOURCE__) == RCC_RTCCLKSOURCE_LSI)        || \
                                           ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV32)  || \
                                           ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV128) || \
                                           ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV8))
#elif defined(RCC_LSE_SUPPORT)
#define IS_RCC_RTCCLKSOURCE(__SOURCE__)   (((__SOURCE__) == RCC_RTCCLKSOURCE_NONE)       || \
                                           ((__SOURCE__) == RCC_RTCCLKSOURCE_LSE)        || \
                                           ((__SOURCE__) == RCC_RTCCLKSOURCE_LSI))
#else
#define IS_RCC_RTCCLKSOURCE(__SOURCE__)   (((__SOURCE__) == RCC_RTCCLKSOURCE_NONE)       || \
                                           ((__SOURCE__) == RCC_RTCCLKSOURCE_LSI))
#endif

#define IS_RCC_MCO(__MCOX__)              (((__MCOX__) == RCC_MCO1) || \
                                           ((__MCOX__) == RCC_MCO2) || \
                                           ((__MCOX__) == RCC_MCO3) || \
                                           ((__MCOX__) == RCC_MCO4) || \
                                           ((__MCOX__) == RCC_MCO5) || \
                                           ((__MCOX__) == RCC_MCO6) || \
                                           ((__MCOX__) == RCC_MCO7))

#if defined(RCC_PLL_SUPPORT) && defined(RCC_HSE_SUPPORT) && defined(RCC_LSE_SUPPORT)
#define IS_RCC_MCOSOURCE(__SOURCE__) (((__SOURCE__) == RCC_MCOSOURCE_NOCLOCK)   || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_SYSCLK)   || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HSI10M)   || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HSI)      || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HSE)      || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_PLL)      || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_LSI)      || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_LSE)      || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HCLK)     || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_PCLK)     || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HCLK_UNGATE) || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_PCLK_UNGATE))
#elif defined(RCC_PLL_SUPPORT) && defined(RCC_HSE_SUPPORT)
#define IS_RCC_MCOSOURCE(__SOURCE__) (((__SOURCE__) == RCC_MCOSOURCE_NOCLOCK)   || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_SYSCLK)   || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HSI10M)   || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HSI)      || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HSE)      || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_PLL)      || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_LSI)      || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HCLK)     || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_PCLK)     || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HCLK_UNGATE) || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_PCLK_UNGATE))
#elif defined(RCC_PLL_SUPPORT) && defined(RCC_LSE_SUPPORT)
#define IS_RCC_MCOSOURCE(__SOURCE__) (((__SOURCE__) == RCC_MCOSOURCE_NOCLOCK)   || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_SYSCLK)   || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HSI10M)   || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HSI)      || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_PLL)      || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_LSI)      || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_LSE)      || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HCLK)     || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_PCLK)     || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HCLK_UNGATE) || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_PCLK_UNGATE))
#elif defined(RCC_HSE_SUPPORT) && defined(RCC_LSE_SUPPORT)
#define IS_RCC_MCOSOURCE(__SOURCE__) (((__SOURCE__) == RCC_MCOSOURCE_NOCLOCK)   || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_SYSCLK)   || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HSI10M)   || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HSI)      || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HSE)      || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_LSI)      || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_LSE)      || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HCLK)     || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_PCLK)     || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HCLK_UNGATE) || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_PCLK_UNGATE))
#elif defined(RCC_HSE_SUPPORT)
#define IS_RCC_MCOSOURCE(__SOURCE__) (((__SOURCE__) == RCC_MCOSOURCE_NOCLOCK)   || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_SYSCLK)   || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HSI10M)   || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HSI)      || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HSE)      || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_LSI)      || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HCLK)     || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_PCLK)     || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HCLK_UNGATE) || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_PCLK_UNGATE))
#elif defined(RCC_LSE_SUPPORT)
#define IS_RCC_MCOSOURCE(__SOURCE__) (((__SOURCE__) == RCC_MCOSOURCE_NOCLOCK)   || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_SYSCLK)   || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HSI10M)   || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HSI)      || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_LSI)      || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_LSE)      || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HCLK)     || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_PCLK)     || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HCLK_UNGATE) || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_PCLK_UNGATE))
#else
#define IS_RCC_MCOSOURCE(__SOURCE__) (((__SOURCE__) == RCC_MCOSOURCE_NOCLOCK)   || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_SYSCLK)   || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HSI10M)   || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HSI)      || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_LSI)      || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HCLK)     || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_PCLK)     || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HCLK_UNGATE) || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_PCLK_UNGATE))
#endif

#define IS_RCC_MCODIV(__DIV__)        (((__DIV__) == RCC_MCODIV_1) || ((__DIV__) == RCC_MCODIV_2)   || \
                                       ((__DIV__) == RCC_MCODIV_4) || ((__DIV__) == RCC_MCODIV_8)   || \
                                       ((__DIV__) == RCC_MCODIV_16)|| ((__DIV__) == RCC_MCODIV_32)  || \
                                       ((__DIV__) == RCC_MCODIV_64)|| ((__DIV__) == RCC_MCODIV_128) || \
                                       ((__DIV__) == RCC_MCODIV_256))
#if defined(RCC_LSE_SUPPORT)
#define IS_RCC_LSE_DRIVE(__DRIVE__)   (((__DRIVE__) == RCC_LSEDRIVE_LOW)      || \
                                       ((__DRIVE__) == RCC_LSEDRIVE_MEDIUM)   || \
                                       ((__DRIVE__) == RCC_LSEDRIVE_HIGH))
#endif
/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup RCC_Exported_Types RCC Exported Types
  * @{
  */
#if defined(RCC_PLL_SUPPORT)
/**
  * @brief  RCC PLL configuration structure definition
  */
typedef struct
{
  uint32_t PLLState;      /*!< PLLState: The new state of the PLL.
                              This parameter can be a value of @ref RCC_PLL_Config */

  uint32_t PLLSource;     /*!< PLLSource: PLL entry clock source.
                              This parameter must be a value of @ref RCC_PLL_Clock_Source */

  uint32_t PLLMUL;        /*!< PLLMUL: Multiplication factor for PLL VCO input clock
                              This parameter must be a value of @ref RCC_PLL_Multiplication_Factor */

  uint32_t PLLDiv;        /*!< The division factor of the PLL.
                              This parameter must be a value of @ref RCC_PLL_Div */
} RCC_PLLInitTypeDef;
#endif
/**
  * @brief  RCC Internal/External Oscillator (HSE, HSI, LSE and LSI) configuration structure definition
  */
typedef struct
{
  uint32_t OscillatorType;       /*!< The oscillators to be configured.
                                      This parameter can be a value of @ref RCC_Oscillator_Type                   */
#if defined(RCC_HSE_SUPPORT)
  uint32_t HSEState;             /*!< The new state of the HSE.
                                      This parameter can be a value of @ref RCC_HSE_Config                        */

  uint32_t HSEFreq;              /*!< The frequency range of the HSE.
                                      This parameter can be a value of @ref RCC_HSE_Freq                          */
#endif
#if defined(RCC_LSE_SUPPORT)
  uint32_t LSEState;             /*!< The new state of the LSE.
                                      This parameter can be a value of @ref RCC_LSE_Config                        */

  uint32_t LSEDriver;            /*!< The driver factor of the LSE.
                                      This parameter can be a value of @ref RCC_LSE_Driver                        */
#endif
  uint32_t HSIState;             /*!< The new state of the HSI.
                                      This parameter can be a value of @ref RCC_HSI_Config                        */

  uint32_t HSIDiv;               /*!< The division factor of the HSI.
                                      This parameter can be a value of @ref RCC_HSI_Div                           */

  uint32_t HSICalibrationValue;  /*!< The calibration trimming value.(default is RCC_HSICALIBRATION_8MHz)
                                      This parameter can be a value of @ref RCC_HSI_Calibration */

  uint32_t LSIState;             /*!< The new state of the LSI.
                                      This parameter can be a value of @ref RCC_LSI_Config                        */
#if defined(RCC_PLL_SUPPORT)
  RCC_PLLInitTypeDef PLL;         /*!< PLL structure parameters */
#endif
} RCC_OscInitTypeDef;

/**
  * @brief  RCC System, AHB and APB busses clock configuration structure definition
  */
typedef struct
{
  uint32_t ClockType;             /*!< The clock to be configured.
                                       This parameter can be a combination of @ref RCC_System_Clock_Type      */

  uint32_t SYSCLKSource;          /*!< The clock source used as system clock (SYSCLK).
                                       This parameter can be a value of @ref RCC_System_Clock_Source    */

  uint32_t AHBCLKDivider;         /*!< The AHB clock (HCLK) divider. This clock is derived from the system clock (SYSCLK).
                                       This parameter can be a value of @ref RCC_AHB_Clock_Source       */

  uint32_t APBCLKDivider;         /*!< The APB clock (PCLK) divider. This clock is derived from the AHB clock (HCLK).
                                       This parameter can be a value of @ref RCC_APB_Clock_Source */


} RCC_ClkInitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RCC_Exported_Constants RCC Exported Constants
  * @{
  */
#if defined(RCC_PLL_SUPPORT)
/** @defgroup RCC_PLL_Clock_Source PLL Clock Source
  * @{
  */
#define RCC_PLLSOURCE_HSI           0x00000000U                        /*!< HSI clock selected as PLL entry clock source */
#if defined(RCC_HSE_SUPPORT)
#define RCC_PLLSOURCE_HSE           RCC_PLLCFGR_PLLSRC                 /*!< HSE clock selected as PLL entry clock source */
#endif
/**
  * @}
  */

/** @defgroup RCC_PLL_Multiplication_Factor PLL Multiplication Factor
  * @{
  */
#define RCC_PLL_MUL2                    0x00000000U
#define RCC_PLL_MUL3                    RCC_PLLCFGR_PLLMUL_0
#define RCC_PLL_MUL4                    RCC_PLLCFGR_PLLMUL_1
#define RCC_PLL_MUL5                    (RCC_PLLCFGR_PLLMUL_1 | RCC_PLLCFGR_PLLMUL_0)
#define RCC_PLL_MUL6                    RCC_PLLCFGR_PLLMUL_2
#define RCC_PLL_MUL7                    (RCC_PLLCFGR_PLLMUL_2 | RCC_PLLCFGR_PLLMUL_0)
#define RCC_PLL_MUL8                    (RCC_PLLCFGR_PLLMUL_2 | RCC_PLLCFGR_PLLMUL_1)
#define RCC_PLL_MUL9                    (RCC_PLLCFGR_PLLMUL_2 | RCC_PLLCFGR_PLLMUL_1 | RCC_PLLCFGR_PLLMUL_0)
#define RCC_PLL_MUL10                   RCC_PLLCFGR_PLLMUL_3
#define RCC_PLL_MUL11                   (RCC_PLLCFGR_PLLMUL_3 | RCC_PLLCFGR_PLLMUL_0)
#define RCC_PLL_MUL12                   (RCC_PLLCFGR_PLLMUL_3 | RCC_PLLCFGR_PLLMUL_1)
#define RCC_PLL_MUL13                   (RCC_PLLCFGR_PLLMUL_3 | RCC_PLLCFGR_PLLMUL_1 | RCC_PLLCFGR_PLLMUL_0)
#define RCC_PLL_MUL14                   (RCC_PLLCFGR_PLLMUL_3 | RCC_PLLCFGR_PLLMUL_2)
#define RCC_PLL_MUL15                   (RCC_PLLCFGR_PLLMUL_3 | RCC_PLLCFGR_PLLMUL_2 | RCC_PLLCFGR_PLLMUL_0)
#define RCC_PLL_MUL16                   (RCC_PLLCFGR_PLLMUL_3 | RCC_PLLCFGR_PLLMUL_2 | RCC_PLLCFGR_PLLMUL_1)
#define RCC_PLL_MUL17                   (RCC_PLLCFGR_PLLMUL_3 | RCC_PLLCFGR_PLLMUL_2 | RCC_PLLCFGR_PLLMUL_1 | RCC_PLLCFGR_PLLMUL_0)
#define RCC_PLL_MUL18                   RCC_PLLCFGR_PLLMUL_4
/**
  * @}
  */

/** @defgroup RCC_PLL_Config PLL Config
  * @{
  */
#define RCC_PLL_NONE                      0x00000000U  /*!< PLL is not configured */
#define RCC_PLL_OFF                       0x00000001U  /*!< PLL deactivation */
#define RCC_PLL_ON                        0x00000002U  /*!< PLL activation */
/**
  * @}
  */

/** @defgroup RCC_PLL_Div PLL Div
  * @{
  */
#define RCC_PLL_DIV1                      0x00000000U    /*!< PLL clock is not divided */
#define RCC_PLL_DIV2                      RCC_CR_PLLDIV  /*!< PLL clock is divided by 2 */
/**
  * @}
  */
#endif
/** @defgroup RCC_Oscillator_Type Oscillator Type
  * @{
  */
#define RCC_OSCILLATORTYPE_NONE        0x00000000U   /*!< Oscillator configuration unchanged */
#if defined(RCC_HSE_SUPPORT)
#define RCC_OSCILLATORTYPE_HSE         0x00000001U   /*!< HSE to configure */
#endif
#define RCC_OSCILLATORTYPE_HSI         0x00000002U   /*!< HSI to configure */
#if defined(RCC_LSE_SUPPORT)
#define RCC_OSCILLATORTYPE_LSE         0x00000004U   /*!< LSE to configure */
#endif
#define RCC_OSCILLATORTYPE_LSI         0x00000008U   /*!< LSI to configure */
/**
  * @}
  */

#if defined(RCC_HSE_SUPPORT)
/** @defgroup RCC_HSE_Config HSE Config
  * @{
  */
#define RCC_HSE_OFF                    0x00000000U                                /*!< HSE clock deactivation */
#define RCC_HSE_ON                     RCC_CR_HSEON                               /*!< HSE clock activation */
#define RCC_HSE_BYPASS                 ((uint32_t)(RCC_CR_HSEBYP | RCC_CR_HSEON)) /*!< External clock source for HSE clock */
/**
  * @}
  */

/** @defgroup RCC_HSE_Freq HSE Config
  * @{
  */
#define RCC_HSE_4_8MHz                 0x00000000U                                  /*!< HSE low drive capability */
#define RCC_HSE_8_16MHz                RCC_ECSCR_HSE_DRV_0                          /*!< HSE medium drive capability */
#define RCC_HSE_16_24MHz               RCC_ECSCR_HSE_DRV_1                          /*!< HSE hign drive capability */
#define RCC_HSE_24_32MHz               RCC_ECSCR_HSE_DRV                            /*!< HSE very high drive capability */
/**
  * @}
  */

/** @defgroup RCC_HSE_STARTUP HSE settling time Config
  * @{
  */
#define RCC_HSE_STARTUP_NONE         (RCC_ECSCR_HSE_RDYSEL_1 | RCC_ECSCR_HSE_RDYSEL_0)
#define RCC_HSE_STARTUP_LOW          RCC_ECSCR_HSE_RDYSEL_0
#define RCC_HSE_STARTUP_MEDIUM       0x00000000U
#define RCC_HSE_STARTUP_HIGH         RCC_ECSCR_HSE_RDYSEL_1
/**
  * @}
  */
#endif

#if defined(RCC_LSE_SUPPORT)
/** @defgroup RCC_LSE_Config LSE Config
  * @{
  */
#define RCC_LSE_OFF                    0x00000000U                                    /*!< LSE clock deactivation */
#define RCC_LSE_ON                     RCC_BDCR_LSEON                                 /*!< LSE clock activation */
#define RCC_LSE_BYPASS                 ((uint32_t)(RCC_BDCR_LSEBYP | RCC_BDCR_LSEON)) /*!< External clock source for LSE clock */
/**
  * @}
  */

/** @defgroup RCC_LSE_Driver LSE Config
  * @{
  */
#define RCC_LSEDRIVE_LOW                 RCC_ECSCR_LSE_DRIVER_0                               /*!< LSE low drive capability */
#define RCC_LSEDRIVE_MEDIUM              RCC_ECSCR_LSE_DRIVER_1                               /*!< LSE medium drive capability */
#define RCC_LSEDRIVE_HIGH                (RCC_ECSCR_LSE_DRIVER_1 | RCC_ECSCR_LSE_DRIVER_0)    /*!< LSE high drive capability */
/**
  * @}
  */

/** @defgroup RCC_LSE_STARTUP LSE settling time Config
  * @{
  */
#define RCC_LSE_STARTUP_NONE         (RCC_ECSCR_LSE_STARTUP_1 | RCC_ECSCR_LSE_STARTUP_0)
#define RCC_LSE_STARTUP_LOW          RCC_ECSCR_LSE_STARTUP_0
#define RCC_LSE_STARTUP_MEDIUM       0x00000000U
#define RCC_LSE_STARTUP_HIGH         RCC_ECSCR_LSE_STARTUP_1
/**
  * @}
  */
#endif
/** @defgroup RCC_HSI_Config HSI Config
  * @{
  */
#define RCC_HSI_OFF                    0x00000000U            /*!< HSI clock deactivation */
#define RCC_HSI_ON                     RCC_CR_HSION           /*!< HSI clock activation */
/**
  * @}
  */


/** @defgroup RCC_HSI_Calibration HSI Calibration
* @{
*/
#define RCC_HSICALIBRATION_8MHz        ((0x0<<16) | ((*(uint32_t *)(0x1FFF1100)) & 0xFFFF))  /*!< 8MHz  HSI calibration trimming value    */
/* #define RCC_HSICALIBRATION_24MHz       ((0x2<<16) | ((*(uint32_t *)(0x1FFF110C)) & 0xFFFF)) */ /*!< 24MHz HSI calibration trimming value    */
/* #define RCC_HSICALIBRATION_48MHz       ((0x4<<16) | ((*(uint32_t *)(0x1FFF1110)) & 0xFFFF)) */ /*!< 48MHz HSI calibration trimming value    */
/* #define RCC_HSICALIBRATION_64MHz       ((0x6<<16) | ((*(uint32_t *)(0x1FFF1114)) & 0xFFFF)) */ /*!< 64MHz HSI calibration trimming value    */
/* #define RCC_HSICALIBRATION_72MHz       ((0x7<<16) | ((*(uint32_t *)(0x1FFF1118)) & 0xFFFF)) */ /*!< 72MHz HSI calibration trimming value    */
/**
  * @}
  */
  
/** @defgroup RCC_HSI_Div HSI Div
  * @{
  */
#define RCC_HSI_DIV1                   0x00000000U                                        /*!< HSI clock is not divided */
#define RCC_HSI_DIV2                   RCC_CR_HSIDIV_0                                    /*!< HSI clock is divided by 2 */
#define RCC_HSI_DIV4                   RCC_CR_HSIDIV_1                                    /*!< HSI clock is divided by 4 */
#define RCC_HSI_DIV8                   (RCC_CR_HSIDIV_1|RCC_CR_HSIDIV_0)                  /*!< HSI clock is divided by 8 */
#define RCC_HSI_DIV16                  RCC_CR_HSIDIV_2                                    /*!< HSI clock is divided by 16 */
#define RCC_HSI_DIV32                  (RCC_CR_HSIDIV_2|RCC_CR_HSIDIV_0)                  /*!< HSI clock is divided by 32 */
#define RCC_HSI_DIV64                  (RCC_CR_HSIDIV_2|RCC_CR_HSIDIV_1)                  /*!< HSI clock is divided by 64 */
#define RCC_HSI_DIV128                 (RCC_CR_HSIDIV_2|RCC_CR_HSIDIV_1|RCC_CR_HSIDIV_0)  /*!< HSI clock is divided by 128 */
/**
  * @}
  */

/** @defgroup RCC_LSI_Config LSI Config
  * @{
  */
#define RCC_LSI_OFF                    0x00000000U            /*!< LSI clock deactivation */
#define RCC_LSI_ON                     RCC_CSR_LSION          /*!< LSI clock activation */
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Type System Clock Type
  * @{
  */
#define RCC_CLOCKTYPE_SYSCLK           0x00000001U  /*!< SYSCLK to configure */
#define RCC_CLOCKTYPE_HCLK             0x00000002U  /*!< HCLK to configure */
#define RCC_CLOCKTYPE_PCLK             0x00000004U  /*!< PCLK to configure */
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Source System Clock Source
  * @{
  */
#define RCC_SYSCLKSOURCE_HSISYS   RCC_CFGR_SW_HSISYS         /*!< HSISYS used as system clock */
#if defined(RCC_HSE_SUPPORT)
#define RCC_SYSCLKSOURCE_HSE      RCC_CFGR_SW_HSE            /*!< HSE used as system clock */
#endif
#if defined(RCC_PLL_SUPPORT)
#define RCC_SYSCLKSOURCE_PLLCLK   RCC_CFGR_SW_PLL            /*!< PLL used as system clock */
#endif
#define RCC_SYSCLKSOURCE_LSI      RCC_CFGR_SW_LSI            /*!< LSI used as system clock */
#if defined(RCC_LSE_SUPPORT)
#define RCC_SYSCLKSOURCE_LSE      RCC_CFGR_SW_LSE            /*!< LSE used as system clock */
#endif
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Source_Status System Clock Source Status
  * @{
  */
#define RCC_SYSCLKSOURCE_STATUS_HSISYS   RCC_CFGR_SWS_HSISYS         /*!< HSISYS used as system clock */
#if defined(RCC_HSE_SUPPORT)
#define RCC_SYSCLKSOURCE_STATUS_HSE      RCC_CFGR_SWS_HSE            /*!< HSE used as system clock */
#endif
#if defined(RCC_PLL_SUPPORT)
#define RCC_SYSCLKSOURCE_STATUS_PLLCLK   RCC_CFGR_SWS_PLL            /*!< PLL used as system clock */
#endif
#define RCC_SYSCLKSOURCE_STATUS_LSI      RCC_CFGR_SWS_LSI            /*!< LSI used as system clock */
#if defined(RCC_LSE_SUPPORT)
#define RCC_SYSCLKSOURCE_STATUS_LSE      RCC_CFGR_SWS_LSE            /*!< LSE used as system clock */
#endif
/**
  * @}
  */

/** @defgroup RCC_AHB_Clock_Source AHB Clock Source
  * @{
  */
#define RCC_SYSCLK_DIV1                0x00000000U                                                             /*!< SYSCLK not divided */
#define RCC_SYSCLK_DIV2                RCC_CFGR_HPRE_3                                                         /*!< SYSCLK divided by 2 */
#define RCC_SYSCLK_DIV4                (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_0)                                     /*!< SYSCLK divided by 4 */
#define RCC_SYSCLK_DIV8                (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_1)                                     /*!< SYSCLK divided by 8 */
#define RCC_SYSCLK_DIV16               (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_1 | RCC_CFGR_HPRE_0)                   /*!< SYSCLK divided by 16 */
#define RCC_SYSCLK_DIV64               (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_2)                                     /*!< SYSCLK divided by 64 */
#define RCC_SYSCLK_DIV128              (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_0)                   /*!< SYSCLK divided by 128 */
#define RCC_SYSCLK_DIV256              (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_1)                   /*!< SYSCLK divided by 256 */
#define RCC_SYSCLK_DIV512              (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_1 | RCC_CFGR_HPRE_0) /*!< SYSCLK divided by 512 */
/**
  * @}
  */

/** @defgroup RCC_APB_Clock_Source APB Clock Source
  * @{
  */
#define RCC_HCLK_DIV1                  0x00000000U                                           /*!< HCLK not divided */
#define RCC_HCLK_DIV2                  RCC_CFGR_PPRE_2                                       /*!< HCLK divided by 2 */
#define RCC_HCLK_DIV4                  (RCC_CFGR_PPRE_2 | RCC_CFGR_PPRE_0)                   /*!< HCLK divided by 4 */
#define RCC_HCLK_DIV8                  (RCC_CFGR_PPRE_2 | RCC_CFGR_PPRE_1)                   /*!< HCLK divided by 8 */
#define RCC_HCLK_DIV16                 (RCC_CFGR_PPRE_2 | RCC_CFGR_PPRE_1 | RCC_CFGR_PPRE_0) /*!< HCLK divided by 16 */
/**
  * @}
  */

#if defined(RCC_BDCR_RTCSEL)
/** @defgroup RCC_RTC_Clock_Source RTC Clock Source
  * @{
  */
#define RCC_RTCCLKSOURCE_NONE          0x00000000U                                                         /*!< No clock configured for RTC */
#if defined(RCC_LSE_SUPPORT)
#define RCC_RTCCLKSOURCE_LSE           RCC_BDCR_RTCSEL_0                                                   /*!< LSE oscillator clock used as RTC clock */
#endif
#define RCC_RTCCLKSOURCE_LSI           RCC_BDCR_RTCSEL_1                                                   /*!< LSI oscillator clock used as RTC clock */
#if defined(RCC_HSE_SUPPORT)
#define RCC_RTCCLKSOURCE_HSE_DIV32     (                            RCC_BDCR_RTCSEL_1 | RCC_BDCR_RTCSEL_0) /*!< HSE oscillator clock divided by 32 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV128    (RCC_BDCR_RTC_HSEDIV_SEL_0 | RCC_BDCR_RTCSEL_1 | RCC_BDCR_RTCSEL_0) /*!< HSE oscillator clock divided by 128 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV8      (RCC_BDCR_RTC_HSEDIV_SEL_1 | RCC_BDCR_RTCSEL_1 | RCC_BDCR_RTCSEL_0) /*!< HSE oscillator clock divided by 8 used as RTC clock */
#endif
/**
  * @}
  */
#endif

/** @defgroup RCC_IWDG_Clock_Source IWDG Clock Source
  * @{
  */
#define RCC_IWDGCLKSOURCE_LSI            0x00000000U              /*!< LSI oscillator clock used as IWDG clock */
#if defined(RCC_LSE_SUPPORT)
#define RCC_IWDGCLKSOURCE_LSE            RCC_BDCR_IWDGSEL         /*!< LSE oscillator clock used as IWDG clock */
#endif
/**
  * @}
  */

/** @defgroup RCC_MCO_Index MCO Index
  * @{
  */
#define RCC_MCO                        0x00000000U
#define RCC_MCO1                       RCC_MCO                /*!< Configure PA08 as the clock output. */
#define RCC_MCO2                       0x00000001U            /*!< Configure PA01 as the clock output. */
#define RCC_MCO3                       0x00000002U            /*!< Configure PA05 as the clock output. */
#define RCC_MCO4                       0x00000003U            /*!< Configure PA09 as the clock output. */
#define RCC_MCO5                       0x00000004U            /*!< Configure PA13 as the clock output. */
#define RCC_MCO6                       0x00000005U            /*!< Configure PA14 as the clock output. */
#define RCC_MCO7                       0x00000006U            /*!< Configure PF02 as the clock output. */
/**
  * @}
  */

/** @defgroup RCC_MCO_Clock_Source MCO Clock Source
  * @{
  */
#define RCC_MCOSOURCE_NOCLOCK         0x00000000U                                                 /*!< MCO output disabled, no clock on MCO */
#define RCC_MCOSOURCE_SYSCLK          RCC_CFGR_MCOSEL_0                                           /*!< SYSCLK selection as MCO source */
#define RCC_MCOSOURCE_HSI10M          RCC_CFGR_MCOSEL_1                                           /*!< HSI10M selection as MCO source */
#define RCC_MCOSOURCE_HSI             (RCC_CFGR_MCOSEL_1 | RCC_CFGR_MCOSEL_0)                     /*!< HSI selection as MCO source */
#if defined(RCC_HSE_SUPPORT)
#define RCC_MCOSOURCE_HSE             RCC_CFGR_MCOSEL_2                                           /*!< HSE selection as MCO source */
#endif
#if defined(RCC_PLL_SUPPORT)
#define RCC_MCOSOURCE_PLL             (RCC_CFGR_MCOSEL_2 | RCC_CFGR_MCOSEL_0)                     /*!< PLL selection as MCO source */
#endif
#define RCC_MCOSOURCE_LSI             (RCC_CFGR_MCOSEL_2 | RCC_CFGR_MCOSEL_1)                     /*!< LSI selection as MCO source */
#if defined(RCC_LSE_SUPPORT)
#define RCC_MCOSOURCE_LSE             (RCC_CFGR_MCOSEL_2 | RCC_CFGR_MCOSEL_1 | RCC_CFGR_MCOSEL_0) /*!< LSE selection as MCO source */
#endif
#define RCC_MCOSOURCE_HCLK            RCC_CFGR_MCOSEL_3                                           /*!< HCLK selection as MCO source */
#define RCC_MCOSOURCE_PCLK            (RCC_CFGR_MCOSEL_3 | RCC_CFGR_MCOSEL_0)                     /*!< PCLK selection as MCO source */
#define RCC_MCOSOURCE_HCLK_UNGATE     (RCC_CFGR_MCOSEL_3 | RCC_CFGR_MCOSEL_1)                     /*!< HCLK without gate selected as MCO source */
#define RCC_MCOSOURCE_PCLK_UNGATE     (RCC_CFGR_MCOSEL_3 | RCC_CFGR_MCOSEL_1 | RCC_CFGR_MCOSEL_0) /*!< PCLK without gate selected as MCO source */
/**
  * @}
  */

/** @defgroup RCC_MCO_Clock_Prescaler MCO Clock Prescaler
  * @{
  */
#define RCC_MCODIV_1                   0x00000000U                                                                     /*!< MCO not divided */
#define RCC_MCODIV_2                   (RCC_CFGR_MCOPRE_3)                                                             /*!< MCO divided by 2 */
#define RCC_MCODIV_4                   (RCC_CFGR_MCOPRE_3 | RCC_CFGR_MCOPRE_0)                                         /*!< MCO divided by 4 */
#define RCC_MCODIV_8                   (RCC_CFGR_MCOPRE_3 | RCC_CFGR_MCOPRE_1)                                         /*!< MCO divided by 8 */
#define RCC_MCODIV_16                  (RCC_CFGR_MCOPRE_3 | RCC_CFGR_MCOPRE_1 | RCC_CFGR_MCOPRE_0)                     /*!< MCO divided by 16 */
#define RCC_MCODIV_32                  (RCC_CFGR_MCOPRE_3 | RCC_CFGR_MCOPRE_2)                                         /*!< MCO divided by 32 */
#define RCC_MCODIV_64                  (RCC_CFGR_MCOPRE_3 | RCC_CFGR_MCOPRE_2 | RCC_CFGR_MCOPRE_0)                     /*!< MCO divided by 64 */
#define RCC_MCODIV_128                 (RCC_CFGR_MCOPRE_3 | RCC_CFGR_MCOPRE_2 | RCC_CFGR_MCOPRE_1)                     /*!< MCO divided by 128 */
#define RCC_MCODIV_256                 (RCC_CFGR_MCOPRE_3 | RCC_CFGR_MCOPRE_2 | RCC_CFGR_MCOPRE_1 | RCC_CFGR_MCOPRE_0) /*!< MCO divided by 256 */
/**
  * @}
  */

/** @defgroup RCC_Interrupt Interrupts
  * @{
  */
#define RCC_IT_LSIRDY                    ((uint32_t)RCC_CIFR_LSIRDYF)   /*!< LSI Ready Interrupt flag */
#if defined(RCC_LSE_SUPPORT)
#define RCC_IT_LSERDY                    ((uint32_t)RCC_CIFR_LSERDYF)   /*!< LSE Ready Interrupt flag */
#endif
#define RCC_IT_HSIRDY                    ((uint32_t)RCC_CIFR_HSIRDYF)   /*!< HSI Ready Interrupt flag */
#if defined(RCC_HSE_SUPPORT)
#define RCC_IT_HSERDY                    ((uint32_t)RCC_CIFR_HSERDYF)   /*!< HSE Ready Interrupt flag */
#endif
#if defined(RCC_PLL_SUPPORT)
#define RCC_IT_PLLRDY                    ((uint32_t)RCC_CIFR_PLLRDYF)   /*!< PLL Ready Interrupt flag */
#endif
#if defined(RCC_HSE_SUPPORT)
#define RCC_IT_CSS                       ((uint32_t)RCC_CIFR_CSSF)      /*!< Clock Security System Interrupt flag */
#endif
#if defined(RCC_LSE_SUPPORT)
#define RCC_IT_LSECSS                    ((uint32_t)RCC_CIFR_LSECSSF)   /*!< LSE Clock Security System Interrupt flag */
#endif
/**
  * @}
  */

/** @defgroup RCC_Flag Flags
  *        Elements values convention: XXXYYYYYb
  *           - YYYYY  : Flag position in the register
  *           - XXX  : Register index
  *                 - 001: CR register
  *                 - 010: BDCR register
  *                 - 011: CSR register
  * @{
  */
/* Flags in the CR register */
#define RCC_FLAG_HSIRDY                  ((uint8_t)((CR_REG_INDEX << 5U) | RCC_CR_HSIRDY_Pos)) /*!< Internal High Speed clock ready flag */
#if defined(RCC_HSE_SUPPORT)
#define RCC_FLAG_HSERDY                  ((uint8_t)((CR_REG_INDEX << 5U) | RCC_CR_HSERDY_Pos)) /*!< External High Speed clock ready flag */
#endif
#if defined(RCC_PLL_SUPPORT)
#define RCC_FLAG_PLLRDY                  ((uint8_t)((CR_REG_INDEX << 5U) | RCC_CR_PLLRDY_Pos)) /*!< PLL clock ready flag */
#endif

/* Flags in the BDCR register */
#if defined(RCC_LSE_SUPPORT)
#define RCC_FLAG_LSERDY                  ((uint8_t)((BDCR_REG_INDEX << 5U) | RCC_BDCR_LSERDY_Pos))  /*!< External Low Speed oscillator Ready */
#define RCC_FLAG_LSECSSD                 ((uint8_t)((BDCR_REG_INDEX << 5U) | RCC_BDCR_LSECSSD_Pos)) /*!< LSE Clock Security System Interrupt flag */
#endif

/* Flags in the CSR register */
#define RCC_FLAG_LSIRDY                  ((uint8_t)((CSR_REG_INDEX << 5U) | RCC_CSR_LSIRDY_Pos))   /*!< Internal Low Speed oscillator Ready */
#define RCC_FLAG_OBLRST                  ((uint8_t)((CSR_REG_INDEX << 5U) | RCC_CSR_OBLRSTF_Pos))  /*!< Option byte loader reset flag */
#define RCC_FLAG_PINRST                  ((uint8_t)((CSR_REG_INDEX << 5U) | RCC_CSR_PINRSTF_Pos))  /*!< PIN reset flag reset flag*/
#define RCC_FLAG_PWRRST                  ((uint8_t)((CSR_REG_INDEX << 5U) | RCC_CSR_PWRRSTF_Pos))  /*!< BOR, POR, or PDR reset flag reset flag*/
#define RCC_FLAG_SFTRST                  ((uint8_t)((CSR_REG_INDEX << 5U) | RCC_CSR_SFTRSTF_Pos))  /*!< Software Reset flag */
#define RCC_FLAG_IWDGRST                 ((uint8_t)((CSR_REG_INDEX << 5U) | RCC_CSR_IWDGRSTF_Pos)) /*!< Independent Watchdog reset flag */
#define RCC_FLAG_WWDGRST                 ((uint8_t)((CSR_REG_INDEX << 5U) | RCC_CSR_WWDGRSTF_Pos)) /*!< Window watchdog reset flag */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @defgroup RCC_Exported_Macros RCC Exported Macros
  * @{
  */

/** @defgroup RCC_AHB_Peripheral_Clock_Enable_Disable AHB Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#define __HAL_RCC_DMA1_CLK_ENABLE()           do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHBENR, RCC_AHBENR_DMAEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHBENR, RCC_AHBENR_DMAEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

#define __HAL_RCC_FLASH_CLK_ENABLE()           do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHBENR, RCC_AHBENR_FLASHEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHBENR, RCC_AHBENR_FLASHEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

#define __HAL_RCC_SRAM_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHBENR, RCC_AHBENR_SRAMEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHBENR, RCC_AHBENR_SRAMEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)
#define __HAL_RCC_CRC_CLK_ENABLE()             do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHBENR, RCC_AHBENR_CRCEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHBENR, RCC_AHBENR_CRCEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

#define __HAL_RCC_DMA1_CLK_DISABLE()           CLEAR_BIT(RCC->AHBENR, RCC_AHBENR_DMAEN)
#define __HAL_RCC_FLASH_CLK_DISABLE()          CLEAR_BIT(RCC->AHBENR, RCC_AHBENR_FLASHEN)
#define __HAL_RCC_SRAM_CLK_DISABLE()           CLEAR_BIT(RCC->AHBENR, RCC_AHBENR_SRAMEN)
#define __HAL_RCC_CRC_CLK_DISABLE()            CLEAR_BIT(RCC->AHBENR, RCC_AHBENR_CRCEN)

/**
  * @}
  */

/** @defgroup RCC_IOPORT_Clock_Enable_Disable IOPORT Clock Enable Disable
  * @brief  Enable or disable the IO Ports clock.
  * @note   After reset, the IO ports clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_GPIOA_CLK_ENABLE()           do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOAEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOAEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

#define __HAL_RCC_GPIOB_CLK_ENABLE()           do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOBEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOBEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

#define __HAL_RCC_GPIOF_CLK_ENABLE()           do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOFEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOFEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

#define __HAL_RCC_GPIOA_CLK_DISABLE()          CLEAR_BIT(RCC->IOPENR, RCC_IOPENR_GPIOAEN)
#define __HAL_RCC_GPIOB_CLK_DISABLE()          CLEAR_BIT(RCC->IOPENR, RCC_IOPENR_GPIOBEN)
#define __HAL_RCC_GPIOF_CLK_DISABLE()          CLEAR_BIT(RCC->IOPENR, RCC_IOPENR_GPIOFEN)

/**
  * @}
  */

/** @defgroup RCC_APB1_Clock_Enable_Disable APB1 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB1 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_TIM3_CLK_ENABLE()             do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APBENR1, RCC_APBENR1_TIM3EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_TIM3EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

#define __HAL_RCC_RTCAPB_CLK_ENABLE()          do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APBENR1, RCC_APBENR1_RTCAPBEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_RTCAPBEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

#define __HAL_RCC_WWDG_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APBENR1, RCC_APBENR1_WWDGEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_WWDGEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

#define __HAL_RCC_SPI2_CLK_ENABLE()          do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APBENR1, RCC_APBENR1_SPI2EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_SPI2EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

#define __HAL_RCC_UART1_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APBENR1, RCC_APBENR1_UART1EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_UART1EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

#define __HAL_RCC_LPUART1_CLK_ENABLE()          do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APBENR1, RCC_APBENR1_LPUART1EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_LPUART1EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

#define __HAL_RCC_I2C1_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APBENR1, RCC_APBENR1_I2C1EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_I2C1EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

#define __HAL_RCC_OPA1_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APBENR1, RCC_APBENR1_OPA1EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_OPA1EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

#define __HAL_RCC_OPA2_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APBENR1, RCC_APBENR1_OPA2EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_OPA2EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

#define __HAL_RCC_DBGMCU_CLK_ENABLE()             do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APBENR1, RCC_APBENR1_DBGEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_DBGEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

#define __HAL_RCC_PWR_CLK_ENABLE()             do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APBENR1, RCC_APBENR1_PWREN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_PWREN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

#define __HAL_RCC_LPTIM1_CLK_ENABLE()             do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APBENR1, RCC_APBENR1_LPTIM1EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_LPTIM1EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

/**
  * @}
  */

/** @defgroup RCC_APB2_Clock_Enable_Disable APB2 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB2 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_SYSCFG_CLK_ENABLE()          do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APBENR2, RCC_APBENR2_SYSCFGEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APBENR2, RCC_APBENR2_SYSCFGEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

#define __HAL_RCC_TIM1_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APBENR2, RCC_APBENR2_TIM1EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM1EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

#define __HAL_RCC_SPI1_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APBENR2, RCC_APBENR2_SPI1EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APBENR2, RCC_APBENR2_SPI1EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

#define __HAL_RCC_USART1_CLK_ENABLE()          do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APBENR2, RCC_APBENR2_USART1EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APBENR2, RCC_APBENR2_USART1EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

#define __HAL_RCC_TIM14_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APBENR2, RCC_APBENR2_TIM14EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM14EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

#define __HAL_RCC_TIM16_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APBENR2, RCC_APBENR2_TIM16EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM16EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

#define __HAL_RCC_TIM17_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APBENR2, RCC_APBENR2_TIM17EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM17EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

#define __HAL_RCC_ADC_CLK_ENABLE()           do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APBENR2, RCC_APBENR2_ADCEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APBENR2, RCC_APBENR2_ADCEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

#define __HAL_RCC_COMP1_CLK_ENABLE()           do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APBENR2, RCC_APBENR2_COMP1EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APBENR2, RCC_APBENR2_COMP1EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

#define __HAL_RCC_COMP2_CLK_ENABLE()           do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APBENR2, RCC_APBENR2_COMP2EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APBENR2, RCC_APBENR2_COMP2EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

#define __HAL_RCC_VREFBUF_CLK_ENABLE()           do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APBENR2, RCC_APBENR2_VREFBUFEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APBENR2, RCC_APBENR2_VREFBUFEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0U)

#define __HAL_RCC_TIM3_CLK_DISABLE()           CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_TIM3EN)
#define __HAL_RCC_RTCAPB_CLK_DISABLE()         CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_RTCAPBEN)
#define __HAL_RCC_WWDG_CLK_DISABLE()           CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_WWDGEN)
#define __HAL_RCC_SPI2_CLK_DISABLE()           CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_SPI2EN)
#define __HAL_RCC_UART1_CLK_DISABLE()          CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_UART1EN)
#define __HAL_RCC_LPUART1_CLK_DISABLE()        CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_LPUART1EN)
#define __HAL_RCC_I2C1_CLK_DISABLE()           CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_I2C1EN)
#define __HAL_RCC_OPA1_CLK_DISABLE()           CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_OPA1EN)
#define __HAL_RCC_OPA2_CLK_DISABLE()           CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_OPA2EN)
#define __HAL_RCC_DBGMCU_CLK_DISABLE()         CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_DBGEN)
#define __HAL_RCC_PWR_CLK_DISABLE()            CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_PWREN)
#define __HAL_RCC_LPTIM1_CLK_DISABLE()         CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_LPTIM1EN)

#define __HAL_RCC_SYSCFG_CLK_DISABLE()         CLEAR_BIT(RCC->APBENR2, RCC_APBENR2_SYSCFGEN)
#define __HAL_RCC_TIM1_CLK_DISABLE()           CLEAR_BIT(RCC->APBENR2, RCC_APBENR2_TIM1EN)
#define __HAL_RCC_SPI1_CLK_DISABLE()           CLEAR_BIT(RCC->APBENR2, RCC_APBENR2_SPI1EN)
#define __HAL_RCC_USART1_CLK_DISABLE()         CLEAR_BIT(RCC->APBENR2, RCC_APBENR2_USART1EN)
#define __HAL_RCC_TIM14_CLK_DISABLE()          CLEAR_BIT(RCC->APBENR2, RCC_APBENR2_TIM14EN)
#define __HAL_RCC_TIM16_CLK_DISABLE()          CLEAR_BIT(RCC->APBENR2, RCC_APBENR2_TIM16EN)
#define __HAL_RCC_TIM17_CLK_DISABLE()          CLEAR_BIT(RCC->APBENR2, RCC_APBENR2_TIM17EN)
#define __HAL_RCC_ADC_CLK_DISABLE()            CLEAR_BIT(RCC->APBENR2, RCC_APBENR2_ADCEN)
#define __HAL_RCC_COMP1_CLK_DISABLE()          CLEAR_BIT(RCC->APBENR2, RCC_APBENR2_COMP1EN)
#define __HAL_RCC_COMP2_CLK_DISABLE()          CLEAR_BIT(RCC->APBENR2, RCC_APBENR2_COMP2EN)
#define __HAL_RCC_VREFBUF_CLK_DISABLE()        CLEAR_BIT(RCC->APBENR2, RCC_APBENR2_VREFBUFEN)
/**
  * @}
  */

/** @defgroup RCC_AHB_Peripheral_Clock_Enabled_Disabled_Status AHB Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the AHB peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#define __HAL_RCC_DMA1_IS_CLK_ENABLED()        (READ_BIT(RCC->AHBENR, RCC_AHBENR_DMAEN)   != RESET)
#define __HAL_RCC_FLASH_IS_CLK_ENABLED()       (READ_BIT(RCC->AHBENR, RCC_AHBENR_FLASHEN) != RESET)
#define __HAL_RCC_SRAM_IS_CLK_ENABLED()        (READ_BIT(RCC->AHBENR, RCC_AHBENR_SRAMEN)  != RESET)
#define __HAL_RCC_CRC_IS_CLK_ENABLED()         (READ_BIT(RCC->AHBENR, RCC_AHBENR_CRCEN)   != RESET)

#define __HAL_RCC_DMA1_IS_CLK_DISABLED()       (READ_BIT(RCC->AHBENR, RCC_AHBENR_DMAEN)   == RESET)
#define __HAL_RCC_FLASH_IS_CLK_DISABLED()      (READ_BIT(RCC->AHBENR, RCC_AHBENR_FLASHEN) == RESET)
#define __HAL_RCC_SRAM_IS_CLK_DISABLED()       (READ_BIT(RCC->AHBENR, RCC_AHBENR_SRAMEN)  == RESET)
#define __HAL_RCC_CRC_IS_CLK_DISABLED()        (READ_BIT(RCC->AHBENR, RCC_AHBENR_CRCEN)   == RESET)
/**
  * @}
  */

/** @defgroup RCC_IOPORT_Clock_Enabled_Disabled_Status IOPORT Clock Enabled or Disabled Status
  * @brief  Check whether the IO Port clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#define __HAL_RCC_GPIOA_IS_CLK_ENABLED()       (READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOAEN) != RESET)
#define __HAL_RCC_GPIOB_IS_CLK_ENABLED()       (READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOBEN) != RESET)
#define __HAL_RCC_GPIOF_IS_CLK_ENABLED()       (READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOFEN) != RESET)

#define __HAL_RCC_GPIOA_IS_CLK_DISABLED()      (READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOAEN) == RESET)
#define __HAL_RCC_GPIOB_IS_CLK_DISABLED()      (READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOBEN) == RESET)
#define __HAL_RCC_GPIOF_IS_CLK_DISABLED()      (READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOFEN) == RESET)

/**
  * @}
  */

/** @defgroup RCC_APB1_Clock_Enabled_Disabled_Status APB1 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the APB1 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#define __HAL_RCC_TIM3_IS_CLK_ENABLED()        (READ_BIT(RCC->APBENR1, RCC_APBENR1_TIM3EN)  != 0U)
#define __HAL_RCC_RTCAPB_IS_CLK_ENABLED()      (READ_BIT(RCC->APBENR1, RCC_APBENR1_RTCAPBEN) != 0U)
#define __HAL_RCC_WWDG_IS_CLK_ENABLED()        (READ_BIT(RCC->APBENR1, RCC_APBENR1_WWDGEN)   != 0U)
#define __HAL_RCC_SPI2_IS_CLK_ENABLED()        (READ_BIT(RCC->APBENR1, RCC_APBENR1_SPI2EN)   != 0U)
#define __HAL_RCC_UART1_IS_CLK_ENABLED()       (READ_BIT(RCC->APBENR1, RCC_APBENR1_UART1EN)  != 0U)
#define __HAL_RCC_LPUART1_IS_CLK_ENABLED()     (READ_BIT(RCC->APBENR1, RCC_APBENR1_LPUART1EN)!= 0U)
#define __HAL_RCC_I2C1_IS_CLK_ENABLED()        (READ_BIT(RCC->APBENR1, RCC_APBENR1_I2C1EN)    != 0U)
#define __HAL_RCC_OPA1_IS_CLK_ENABLED()        (READ_BIT(RCC->APBENR1, RCC_APBENR1_OPA1EN)   != 0U)
#define __HAL_RCC_OPA2_IS_CLK_ENABLED()        (READ_BIT(RCC->APBENR1, RCC_APBENR1_OPA2EN)   != 0U)
#define __HAL_RCC_DBGMCU_IS_CLK_ENABLED()      (READ_BIT(RCC->APBENR1, RCC_APBENR1_DBGEN)    != 0U)
#define __HAL_RCC_PWR_IS_CLK_ENABLED()         (READ_BIT(RCC->APBENR1, RCC_APBENR1_PWREN)    != 0U)
#define __HAL_RCC_LPTIM1_IS_CLK_ENABLED()      (READ_BIT(RCC->APBENR1, RCC_APBENR1_LPTIM1EN) != 0U)

#define __HAL_RCC_TIM3_IS_CLK_DISABLED()        (READ_BIT(RCC->APBENR1, RCC_APBENR1_TIM3EN)  == 0U)
#define __HAL_RCC_RTCAPB_IS_CLK_DISABLED()      (READ_BIT(RCC->APBENR1, RCC_APBENR1_RTCAPBEN) == 0U)
#define __HAL_RCC_WWDG_IS_CLK_DISABLED()        (READ_BIT(RCC->APBENR1, RCC_APBENR1_WWDGEN)   == 0U)
#define __HAL_RCC_SPI2_IS_CLK_DISABLED()        (READ_BIT(RCC->APBENR1, RCC_APBENR1_SPI2EN)   == 0U)
#define __HAL_RCC_UART1_IS_CLK_DISABLED()       (READ_BIT(RCC->APBENR1, RCC_APBENR1_UART1EN)  == 0U)
#define __HAL_RCC_LPUART1_IS_CLK_DISABLED()     (READ_BIT(RCC->APBENR1, RCC_APBENR1_LPUART1EN)== 0U)
#define __HAL_RCC_I2C1_IS_CLK_DISABLED()        (READ_BIT(RCC->APBENR1, RCC_APBENR1_I2C1EN)   == 0U)
#define __HAL_RCC_OPA1_IS_CLK_DISABLED()        (READ_BIT(RCC->APBENR1, RCC_APBENR1_OPA1EN)   == 0U)
#define __HAL_RCC_OPA2_IS_CLK_DISABLED()        (READ_BIT(RCC->APBENR1, RCC_APBENR1_OPA2EN)   == 0U)
#define __HAL_RCC_DBGMCU_IS_CLK_DISABLED()      (READ_BIT(RCC->APBENR1, RCC_APBENR1_DBGEN)    == 0U)
#define __HAL_RCC_PWR_IS_CLK_DISABLED()         (READ_BIT(RCC->APBENR1, RCC_APBENR1_PWREN)    == 0U)
#define __HAL_RCC_LPTIM1_IS_CLK_DISABLED()      (READ_BIT(RCC->APBENR1, RCC_APBENR1_LPTIM1EN) == 0U)

/**
  * @}
  */

/** @defgroup RCC_APB2_Clock_Enabled_Disabled_Status APB2 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the APB2 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#define __HAL_RCC_SYSCFG_IS_CLK_ENABLED()      (READ_BIT(RCC->APBENR2, RCC_APBENR2_SYSCFGEN) != 0U)
#define __HAL_RCC_TIM1_IS_CLK_ENABLED()        (READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM1EN)   != 0U)
#define __HAL_RCC_SPI1_IS_CLK_ENABLED()        (READ_BIT(RCC->APBENR2, RCC_APBENR2_SPI1EN)   != 0U)
#define __HAL_RCC_USART1_IS_CLK_ENABLED()      (READ_BIT(RCC->APBENR2, RCC_APBENR2_USART1EN) != 0U)
#define __HAL_RCC_TIM14_IS_CLK_ENABLED()       (READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM14EN)  != 0U)
#define __HAL_RCC_TIM16_IS_CLK_ENABLED()       (READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM16EN)  != 0U)
#define __HAL_RCC_TIM17_IS_CLK_ENABLED()       (READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM17EN)  != 0U)
#define __HAL_RCC_ADC_IS_CLK_ENABLED()         (READ_BIT(RCC->APBENR2, RCC_APBENR2_ADCEN)    != 0U)
#define __HAL_RCC_COMP1_IS_CLK_ENABLED()       (READ_BIT(RCC->APBENR2, RCC_APBENR2_COMP1EN)  != 0U)
#define __HAL_RCC_COMP2_IS_CLK_ENABLED()       (READ_BIT(RCC->APBENR2, RCC_APBENR2_COMP2EN)  != 0U)
#define __HAL_RCC_VREFBUF_IS_CLK_ENABLED()     (READ_BIT(RCC->APBENR2, RCC_APBENR2_VREFBUFEN)!= 0U)

#define __HAL_RCC_SYSCFG_IS_CLK_DISABLED()      (READ_BIT(RCC->APBENR2, RCC_APBENR2_SYSCFGEN) == 0U)
#define __HAL_RCC_TIM1_IS_CLK_DISABLED()        (READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM1EN)   == 0U)
#define __HAL_RCC_SPI1_IS_CLK_DISABLED()        (READ_BIT(RCC->APBENR2, RCC_APBENR2_SPI1EN)   == 0U)
#define __HAL_RCC_USART1_IS_CLK_DISABLED()      (READ_BIT(RCC->APBENR2, RCC_APBENR2_USART1EN) == 0U)
#define __HAL_RCC_TIM14_IS_CLK_DISABLED()       (READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM14EN)  == 0U)
#define __HAL_RCC_TIM16_IS_CLK_DISABLED()       (READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM16EN)  == 0U)
#define __HAL_RCC_TIM17_IS_CLK_DISABLED()       (READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM17EN)  == 0U)
#define __HAL_RCC_ADC_IS_CLK_DISABLED()         (READ_BIT(RCC->APBENR2, RCC_APBENR2_ADCEN)    == 0U)
#define __HAL_RCC_COMP1_IS_CLK_DISABLED()       (READ_BIT(RCC->APBENR2, RCC_APBENR2_COMP1EN)  == 0U)
#define __HAL_RCC_COMP2_IS_CLK_DISABLED()       (READ_BIT(RCC->APBENR2, RCC_APBENR2_COMP2EN)  == 0U)
#define __HAL_RCC_VREFBUF_IS_CLK_DISABLED()     (READ_BIT(RCC->APBENR2, RCC_APBENR2_VREFBUFEN)== 0U)

/**
  * @}
  */

/** @defgroup RCC_AHB_Force_Release_Reset AHB Peripheral Force Release Reset
  * @brief  Force or release AHB1 peripheral reset.
  * @{
  */
#define __HAL_RCC_AHB_FORCE_RESET()            WRITE_REG(RCC->AHBRSTR, 0xFFFFFFFFU)
#define __HAL_RCC_CRC_FORCE_RESET()            SET_BIT(RCC->AHBRSTR, RCC_AHBRSTR_CRCRST)
#define __HAL_RCC_DMA1_FORCE_RESET()           SET_BIT(RCC->AHBRSTR, RCC_AHBRSTR_DMARST)

#define __HAL_RCC_AHB_RELEASE_RESET()          WRITE_REG(RCC->AHBRSTR, 0x00000000U)
#define __HAL_RCC_CRC_RELEASE_RESET()          CLEAR_BIT(RCC->AHBRSTR, RCC_AHBRSTR_CRCRST)
#define __HAL_RCC_DMA1_RELEASE_RESET()         CLEAR_BIT(RCC->AHBRSTR, RCC_AHBRSTR_DMARST)
/**
  * @}
  */

/** @defgroup RCC_IOPORT_Force_Release_Reset IOPORT Force Release Reset
  * @brief  Force or release IO Port reset.
  * @{
  */
#define __HAL_RCC_IOP_FORCE_RESET()            WRITE_REG(RCC->IOPRSTR, 0xFFFFFFFFU)
#define __HAL_RCC_GPIOA_FORCE_RESET()          SET_BIT(RCC->IOPRSTR, RCC_IOPRSTR_GPIOARST)
#define __HAL_RCC_GPIOB_FORCE_RESET()          SET_BIT(RCC->IOPRSTR, RCC_IOPRSTR_GPIOBRST)
#define __HAL_RCC_GPIOF_FORCE_RESET()          SET_BIT(RCC->IOPRSTR, RCC_IOPRSTR_GPIOFRST)

#define __HAL_RCC_IOP_RELEASE_RESET()          WRITE_REG(RCC->IOPRSTR, 0x00000000U)
#define __HAL_RCC_GPIOA_RELEASE_RESET()        CLEAR_BIT(RCC->IOPRSTR, RCC_IOPRSTR_GPIOARST)
#define __HAL_RCC_GPIOB_RELEASE_RESET()        CLEAR_BIT(RCC->IOPRSTR, RCC_IOPRSTR_GPIOBRST)
#define __HAL_RCC_GPIOF_RELEASE_RESET()        CLEAR_BIT(RCC->IOPRSTR, RCC_IOPRSTR_GPIOFRST)
/**
  * @}
  */

/** @defgroup RCC_APB1_Force_Release_Reset APB1 Peripheral Force Release Reset
  * @brief  Force or release APB1 peripheral reset.
  * @{
  */
#define __HAL_RCC_APB1_FORCE_RESET()           WRITE_REG(RCC->APBRSTR1, 0xFFFFFFFFU)
#define __HAL_RCC_TIM3_FORCE_RESET()           SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_TIM3RST)
#define __HAL_RCC_RTCAPB_FORCE_RESET()         SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_RTCAPBRST)
#define __HAL_RCC_WWDG_FORCE_RESET()           SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_WWDGRST)
#define __HAL_RCC_SPI2_FORCE_RESET()           SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_SPI2RST)
#define __HAL_RCC_UART1_FORCE_RESET()          SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_UART1RST)
#define __HAL_RCC_LPUART1_FORCE_RESET()        SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_LPUART1RST)
#define __HAL_RCC_I2C1_FORCE_RESET()           SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_I2C1RST)
#define __HAL_RCC_OPA1_FORCE_RESET()           SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_OPA1RST)
#define __HAL_RCC_OPA2_FORCE_RESET()           SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_OPA2RST)
#define __HAL_RCC_DBGMCU_FORCE_RESET()         SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_DBGRST)
#define __HAL_RCC_PWR_FORCE_RESET()            SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_PWRRST)
#define __HAL_RCC_LPTIM1_FORCE_RESET()         SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_LPTIM1RST)

#define __HAL_RCC_APB1_RELEASE_RESET()           WRITE_REG(RCC->APBRSTR1, 0x00000000U)
#define __HAL_RCC_TIM3_RELEASE_RESET()           CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_TIM3RST)
#define __HAL_RCC_RTCAPB_RELEASE_RESET()         CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_RTCAPBRST)
#define __HAL_RCC_WWDG_RELEASE_RESET()           CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_WWDGRST)
#define __HAL_RCC_SPI2_RELEASE_RESET()           CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_SPI2RST)
#define __HAL_RCC_UART1_RELEASE_RESET()          CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_UART1RST)
#define __HAL_RCC_LPUART1_RELEASE_RESET()        CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_LPUART1RST)
#define __HAL_RCC_I2C1_RELEASE_RESET()           CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_I2C1RST)
#define __HAL_RCC_OPA1_RELEASE_RESET()           CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_OPA1RST)
#define __HAL_RCC_OPA2_RELEASE_RESET()           CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_OPA2RST)
#define __HAL_RCC_DBGMCU_RELEASE_RESET()         CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_DBGRST)
#define __HAL_RCC_PWR_RELEASE_RESET()            CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_PWRRST)
#define __HAL_RCC_LPTIM1_RELEASE_RESET()         CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_LPTIM1RST)
/**
  * @}
  */

/** @defgroup RCC_APB2_Force_Release_Reset APB2 Peripheral Force Release Reset
  * @brief  Force or release APB2 peripheral reset.
  * @{
  */
#define __HAL_RCC_APB2_FORCE_RESET()           WRITE_REG(RCC->APBRSTR2, 0xFFFFFFFFU)
#define __HAL_RCC_SYSCFG_FORCE_RESET()         SET_BIT(RCC->APBRSTR2, RCC_APBRSTR2_SYSCFGRST)
#define __HAL_RCC_TIM1_FORCE_RESET()           SET_BIT(RCC->APBRSTR2, RCC_APBRSTR2_TIM1RST)
#define __HAL_RCC_SPI1_FORCE_RESET()           SET_BIT(RCC->APBRSTR2, RCC_APBRSTR2_SPI1RST)
#define __HAL_RCC_USART1_FORCE_RESET()         SET_BIT(RCC->APBRSTR2, RCC_APBRSTR2_USART1RST)
#define __HAL_RCC_TIM14_FORCE_RESET()          SET_BIT(RCC->APBRSTR2, RCC_APBRSTR2_TIM14RST)
#define __HAL_RCC_TIM16_FORCE_RESET()          SET_BIT(RCC->APBRSTR2, RCC_APBRSTR2_TIM16RST)
#define __HAL_RCC_TIM17_FORCE_RESET()          SET_BIT(RCC->APBRSTR2, RCC_APBRSTR2_TIM17RST)
#define __HAL_RCC_ADC_FORCE_RESET()            SET_BIT(RCC->APBRSTR2, RCC_APBRSTR2_ADCRST)
#define __HAL_RCC_COMP1_FORCE_RESET()          SET_BIT(RCC->APBRSTR2, RCC_APBRSTR2_COMP1RST)
#define __HAL_RCC_COMP2_FORCE_RESET()          SET_BIT(RCC->APBRSTR2, RCC_APBRSTR2_COMP2RST)
#define __HAL_RCC_VREFBUF_FORCE_RESET()        SET_BIT(RCC->APBRSTR2, RCC_APBRSTR2_VREFBUFRST)

#define __HAL_RCC_APB2_RELEASE_RESET()           WRITE_REG(RCC->APBRSTR2, 0x00000000U)
#define __HAL_RCC_SYSCFG_RELEASE_RESET()         CLEAR_BIT(RCC->APBRSTR2, RCC_APBRSTR2_SYSCFGRST)
#define __HAL_RCC_TIM1_RELEASE_RESET()           CLEAR_BIT(RCC->APBRSTR2, RCC_APBRSTR2_TIM1RST)
#define __HAL_RCC_SPI1_RELEASE_RESET()           CLEAR_BIT(RCC->APBRSTR2, RCC_APBRSTR2_SPI1RST)
#define __HAL_RCC_USART1_RELEASE_RESET()         CLEAR_BIT(RCC->APBRSTR2, RCC_APBRSTR2_USART1RST)
#define __HAL_RCC_TIM14_RELEASE_RESET()          CLEAR_BIT(RCC->APBRSTR2, RCC_APBRSTR2_TIM14RST)
#define __HAL_RCC_TIM16_RELEASE_RESET()          CLEAR_BIT(RCC->APBRSTR2, RCC_APBRSTR2_TIM16RST)
#define __HAL_RCC_TIM17_RELEASE_RESET()          CLEAR_BIT(RCC->APBRSTR2, RCC_APBRSTR2_TIM17RST)
#define __HAL_RCC_ADC_RELEASE_RESET()            CLEAR_BIT(RCC->APBRSTR2, RCC_APBRSTR2_ADCRST)
#define __HAL_RCC_COMP1_RELEASE_RESET()          CLEAR_BIT(RCC->APBRSTR2, RCC_APBRSTR2_COMP1RST)
#define __HAL_RCC_COMP2_RELEASE_RESET()          CLEAR_BIT(RCC->APBRSTR2, RCC_APBRSTR2_COMP2RST)
#define __HAL_RCC_VREFBUF_RELEASE_RESET()        CLEAR_BIT(RCC->APBRSTR2, RCC_APBRSTR2_VREFBUFRST)

//#define __HAL_RCC_APB2_RELEASE_RESET()         WRITE_REG(RCC->APBRSTR2, 0x00U)
/**
  * @}
  */

/** @defgroup RCC_Backup_Domain_Reset RCC Backup Domain Reset
  * @{
  */

/** @brief  Macros to force or release the Backup domain reset.
  * @note   This function resets the RTC peripheral (including the backup registers)
  *         and the RTC clock source selection in RCC_BDCR register.
  * @retval None
  */
#define __HAL_RCC_BACKUPRESET_FORCE()   SET_BIT(RCC->BDCR, RCC_BDCR_BDRST)

#define __HAL_RCC_BACKUPRESET_RELEASE() CLEAR_BIT(RCC->BDCR, RCC_BDCR_BDRST)

/**
  * @}
  */
#if defined(RTC)
/** @defgroup RCC_RTC_Clock_Configuration RCC RTC Clock Configuration
  * @{
  */

/** @brief  Macros to enable or disable the RTC clock.
  * @note   As the RTC is in the Backup domain and write access is denied to
  *         this domain after reset, you have to enable write access using
  *         HAL_PWR_EnableBkUpAccess() function before to configure the RTC
  *         (to be done once after reset).
  * @note   These macros must be used after the RTC clock source was selected.
  * @retval None
  */
#define __HAL_RCC_RTC_ENABLE()         SET_BIT(RCC->BDCR, RCC_BDCR_RTCEN)

#define __HAL_RCC_RTC_DISABLE()        CLEAR_BIT(RCC->BDCR, RCC_BDCR_RTCEN)

/**
  * @}
  */
#endif
/** @defgroup RCC_Clock_Configuration RCC Clock Configuration
  * @{
  */

/** @brief  Macros to enable the Internal High Speed oscillator (HSI).
  * @note   The HSI is stopped by hardware when entering STOP and STANDBY modes.
  *         It is used (enabled by hardware) as system clock source after startup
  *         from Reset, wakeup from STOP and STANDBY mode, or in case of failure
  *         of the HSE used directly or indirectly as system clock (if the Clock
  *         Security System CSS is enabled).
  * @note   After enabling the HSI, the application software should wait on HSIRDY
  *         flag to be set indicating that HSI clock is stable and can be used as
  *         system clock source.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
#define __HAL_RCC_HSI_ENABLE()  SET_BIT(RCC->CR, RCC_CR_HSION)

/** @brief  Macros to disable the Internal High Speed oscillator (HSI).
  * @note   HSI can not be stopped if it is used as system clock source. In this case,
  *         you have to select another source of the system clock then stop the HSI.
  * @note   When the HSI is stopped, HSIRDY flag goes low after 6 HSI oscillator
  *         clock cycles.
  * @retval None
  */
#define __HAL_RCC_HSI_DISABLE() CLEAR_BIT(RCC->CR, RCC_CR_HSION)

/** @brief  Macro to adjust the Internal High Speed oscillator (HSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI RC.
  * @param  __HSICALIBRATIONVALUE__ specifies the calibration trimming value
  *         (default is RCC_HSICALIBRATION_24MHz).
  *         This parameter can be a value of @ref RCC_HSI_Calibration. 
  * @retval None
  */
#define __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(__HSICALIBRATIONVALUE__) \
                  MODIFY_REG(RCC->ICSCR, (RCC_ICSCR_HSI_FS_CR_Msk|RCC_ICSCR_HSI_TC_TRIMCR|RCC_ICSCR_HSI_ABS_TRIMCR), (uint32_t)(__HSICALIBRATIONVALUE__))

/** @brief  Macro to configure the HSISYS clock.
  * @param  __HSIDIV__ specifies the HSI division factor.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_HSI_DIV1   HSI clock source is divided by 1
  *            @arg @ref RCC_HSI_DIV2   HSI clock source is divided by 2
  *            @arg @ref RCC_HSI_DIV4   HSI clock source is divided by 4
  *            @arg @ref RCC_HSI_DIV8   HSI clock source is divided by 8
  *            @arg @ref RCC_HSI_DIV16  HSI clock source is divided by 16
  *            @arg @ref RCC_HSI_DIV32  HSI clock source is divided by 32
  *            @arg @ref RCC_HSI_DIV64  HSI clock source is divided by 64
  *            @arg @ref RCC_HSI_DIV128 HSI clock source is divided by 128
  */
#define __HAL_RCC_HSI_CONFIG(__HSIDIV__) \
                 MODIFY_REG(RCC->CR, RCC_CR_HSIDIV, (__HSIDIV__))

/**
  * @brief    Macros to enable or disable the force of the Internal High Speed oscillator (HSI)
  *           in STOP mode to be quickly available as kernel clock for USARTs and I2Cs.
  * @note     Keeping the HSI ON in STOP mode allows to avoid slowing down the communication
  *           speed because of the HSI startup time.
  * @note     The enable of this function has not effect on the HSION bit.
  *           This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
#define __HAL_RCC_HSISTOP_ENABLE()     SET_BIT(RCC->CR, RCC_CR_HSIKERON)

#define __HAL_RCC_HSISTOP_DISABLE()    CLEAR_BIT(RCC->CR, RCC_CR_HSIKERON)

/** @brief  Macros to enable or disable the Internal Low Speed oscillator (LSI).
  * @note   After enabling the LSI, the application software should wait on
  *         LSIRDY flag to be set indicating that LSI clock is stable and can
  *         be used to clock the IWDG and/or the RTC.
  * @note   LSI can not be disabled if the IWDG is running.
  * @note   When the LSI is stopped, LSIRDY flag goes low after 6 LSI oscillator
  *         clock cycles.
  * @retval None
  */
#define __HAL_RCC_LSI_ENABLE()         SET_BIT(RCC->CSR, RCC_CSR_LSION)

#define __HAL_RCC_LSI_DISABLE()        CLEAR_BIT(RCC->CSR, RCC_CSR_LSION)

/** @brief  Macros to enable or disable the NRST filter function.
  * @retval None
  */
#define __HAL_RCC_NRST_FILTER_ENABLE()         CLEAR_BIT(RCC->CSR, RCC_CSR_NRST_FLTDIS)

#define __HAL_RCC_NRST_FILTER_DISABLE()        SET_BIT(RCC->CSR, RCC_CSR_NRST_FLTDIS)

#if defined(RCC_HSE_SUPPORT)
/**
  * @brief  Macro to configure the External High Speed oscillator (HSE).
  * @note   Transition HSE Bypass to HSE On and HSE On to HSE Bypass are not
  *         supported by this macro. User should request a transition to HSE Off
  *         first and then HSE On or HSE Bypass.
  * @note   After enabling the HSE (RCC_HSE_ON or RCC_HSE_Bypass), the application
  *         software should wait on HSERDY flag to be set indicating that HSE clock
  *         is stable and can be used to clock the system clock.
  * @note   HSE state can not be changed if it is used directly as system clock. 
  *         In this case, you have to select another source
  *         of the system clock then change the HSE state (ex. disable it).
  * @note   The HSE is stopped by hardware when entering STOP and STANDBY modes.
  * @note   This function reset the CSSON bit, so if the clock security system(CSS)
  *         was previously enabled you have to enable it again after calling this
  *         function.
  * @param  __STATE__  specifies the new state of the HSE.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_HSE_OFF  Turn OFF the HSE oscillator, HSERDY flag goes low after
  *                              6 HSE oscillator clock cycles.
  *            @arg @ref RCC_HSE_ON  Turn ON the HSE oscillator.
  *            @arg @ref RCC_HSE_BYPASS  HSE oscillator bypassed with external clock.
  * @retval None
  */
#define __HAL_RCC_HSE_CONFIG(__STATE__)                      \
                    do {                                     \
                      if((__STATE__) == RCC_HSE_ON)          \
                      {                                      \
                        SET_BIT(RCC->CR, RCC_CR_HSEON);      \
                      }                                      \
                      else if((__STATE__) == RCC_HSE_BYPASS) \
                      {                                      \
                        SET_BIT(RCC->CR, RCC_CR_HSEBYP);     \
                        SET_BIT(RCC->CR, RCC_CR_HSEON);      \
                      }                                      \
                      else                                   \
                      {                                      \
                        CLEAR_BIT(RCC->CR, RCC_CR_HSEON);    \
                        CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);   \
                      }                                      \
                    } while(0U)

/**
  * @brief  Macro to configure the HSE frequency range.
  * @param  __FREQ__ specifies the HSE frequency range.
  *          This parameter can be one of the following values:
                 @arg @ref RCC_HSE_4_8MHz
  *              @arg @ref RCC_HSE_8_16MHz
  *              @arg @ref RCC_HSE_16_24MHz
  *              @arg @ref RCC_HSE_24_32MHz
  */
#define __HAL_RCC_HSE_FREQ_CONFIG(__FREQ__)    MODIFY_REG(RCC->ECSCR, RCC_ECSCR_HSE_DRV, (__FREQ__))

/**
  * @brief    Macros to enable or disable the analog filtering of the External High Speed oscillator (HSE).
  * @retval None
  */
#define __HAL_RCC_HSE_FILTER_ENABLE()     CLEAR_BIT(RCC->ECSCR, RCC_ECSCR_HSE_FILT_ENB)

#define __HAL_RCC_HSE_FILTER_DISABLE()    SET_BIT(RCC->ECSCR, RCC_ECSCR_HSE_FILT_ENB)

/** @brief  Macro to configure the HSE settling time.
  * @param  __TIME__ specifies the HSE settling time.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_HSE_STARTUP_NONE     Direct output regardless of stabilization time.
  *            @arg @ref RCC_HSE_STARTUP_LOW      It is output after 2048 HSE clock cycles. 
                                                  If HSEBYP is set, it is output after 1024 clock cycles.
  *            @arg @ref RCC_HSE_STARTUP_MEDIUM   It is output after 4096 HSE clock cycles.
                                                  If HSEBYP is set, it is output after 2048 clock cycles.
  *            @arg @ref RCC_HSE_STARTUP_HIGH     It is output after 8192 HSE clock cycles.
                                                  If HSEBYP is set, it is output after 4096 clock cycles.
  */
#define __HAL_RCC_HSE_STARTUP_DELAY(__TIME__)   MODIFY_REG(RCC->ECSCR, RCC_ECSCR_HSE_RDYSEL ,(__TIME__))
#endif

#if defined(RCC_LSE_SUPPORT)
/**
  * @brief  Macro to configure the External Low Speed oscillator (LSE).
  * @note   Transitions LSE Bypass to LSE On and LSE On to LSE Bypass are not
  *         supported by this macro. User should request a transition to LSE Off
  *         first and then LSE On or LSE Bypass.
  * @note   As the LSE is in the Backup domain and write access is denied to
  *         this domain after reset, you have to enable write access using
  *         HAL_PWR_EnableBkUpAccess() function before to configure the LSE
  *         (to be done once after reset).
  * @note   After enabling the LSE (RCC_LSE_ON or RCC_LSE_BYPASS), the application
  *         software should wait on LSERDY flag to be set indicating that LSE clock
  *         is stable and can be used to clock the RTC.
  * @param  __STATE__  specifies the new state of the LSE.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_LSE_OFF  Turn OFF the LSE oscillator, LSERDY flag goes low after
  *                              6 LSE oscillator clock cycles.
  *            @arg @ref RCC_LSE_ON  Turn ON the LSE oscillator.
  *            @arg @ref RCC_LSE_BYPASS  LSE oscillator bypassed with external clock.
  * @retval None
  */
#define __HAL_RCC_LSE_CONFIG(__STATE__)                        \
                    do {                                       \
                      if((__STATE__) == RCC_LSE_ON)            \
                      {                                        \
                        SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);    \
                      }                                        \
                      else if((__STATE__) == RCC_LSE_BYPASS)   \
                      {                                        \
                        SET_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);   \
                        SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);    \
                      }                                        \
                      else                                     \
                      {                                        \
                        CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEON);  \
                        CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEBYP); \
                      }                                        \
                    } while(0U)

/** @brief  Macro to configure the LSE settling time.
  * @param  __TIME__ specifies the LSE settling time.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LSE_STARTUP_NONE     Direct output regardless of stabilization time.
  *            @arg @ref RCC_LSE_STARTUP_LOW      It is output after 2048 LSE clock cycles. 
                                                  If LSEBYP is set, it is output after 1024 clock cycles.
  *            @arg @ref RCC_LSE_STARTUP_MEDIUM   It is output after 4096 LSE clock cycles.
                                                  If LSEBYP is set, it is output after 2048 clock cycles.
  *            @arg @ref RCC_LSE_STARTUP_HIGH     It is output after 8192 LSE clock cycles.
                                                  If LSEBYP is set, it is output after 4096 clock cycles.
  */
#define __HAL_RCC_LSE_STARTUP_DELAY(__TIME__)   MODIFY_REG(RCC->ECSCR, RCC_ECSCR_LSE_STARTUP ,(__TIME__))
#endif
/**
  * @}
  */

#if defined(RCC_PLL_SUPPORT)
/** @defgroup RCC_PLL_Configuration PLL Configuration
  * @{
  */

/** @brief Macro to enable the main PLL.
  * @note   After enabling the main PLL, the application software should wait on
  *         PLLRDY flag to be set indicating that PLL clock is stable and can
  *         be used as system clock source.
  * @note   The main PLL is disabled by hardware when entering STOP and STANDBY modes.
  */
#define __HAL_RCC_PLL_ENABLE()          SET_BIT(RCC->CR, RCC_CR_PLLON)

/** @brief Macro to disable the main PLL.
  * @note   The main PLL can not be disabled if it is used as system clock source
  */
#define __HAL_RCC_PLL_DISABLE()         CLEAR_BIT(RCC->CR, RCC_CR_PLLON)

/** @brief Macro to configure the main PLL clock source and multiplication factors.
  * @note   This function must be used only when the main PLL is disabled.
  *
  * @param  __RCC_PLLSOURCE__ specifies the PLL entry clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_PLLSOURCE_HSI HSI oscillator clock selected as PLL clock entry
  *            @arg @ref RCC_PLLSOURCE_HSE HSE oscillator clock selected as PLL clock entry
  * @param  __PLLMUL__ specifies the multiplication factor for PLL VCO output clock
  *          This parameter can be one of the following values:
  *             @arg @ref RCC_PLL_MUL2    PLLVCO = PLL clock entry x 2
  *             @arg @ref RCC_PLL_MUL3    PLLVCO = PLL clock entry x 3
  *                       ......
  *             @arg @ref RCC_PLL_MUL17   PLLVCO = PLL clock entry x 17
  *             @arg @ref RCC_PLL_MUL18   PLLVCO = PLL clock entry x 18
  * @param  __PLLDIV__ specifies the PLL division factor.
  *          This parameter can be one of the following values:
  *             @arg @ref RCC_PLL_DIV1    PLL clock is divided by 1
  *             @arg @ref RCC_PLL_DIV2    PLL clock is divided by 2
  */
#define __HAL_RCC_PLL_CONFIG(__RCC_PLLSOURCE__, __PLLMUL__, __PLLDIV__)                                                 \
          do{                                                                                                           \
            MODIFY_REG(RCC->PLLCFGR, (RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLMUL),((__RCC_PLLSOURCE__) | (__PLLMUL__) ));  \
            MODIFY_REG(RCC->CR, RCC_CR_PLLDIV, __PLLDIV__);                                                             \
          }while(0)

/** @brief  Get oscillator clock selected as PLL input clock
  * @retval The clock source used for PLL entry. The returned value can be one
  *         of the following:
  *             @arg @ref RCC_PLLSOURCE_HSI  HSI oscillator clock selected as PLL input clock
  *             @arg @ref RCC_PLLSOURCE_HSE  HSE oscillator clock selected as PLL input clock
  */
#define __HAL_RCC_GET_PLL_OSCSOURCE() ((uint32_t)(READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC)))

/**
  * @}
  */
#endif
#if defined(RTC)
/** @addtogroup RCC_RTC_Clock_Configuration
  * @{
  */

/** @brief  Macros to configure the RTC clock (RTCCLK).
  * @note   As the RTC clock configuration bits are in the Backup domain and write
  *         access is denied to this domain after reset, you have to enable write
  *         access using the Power Backup Access macro before to configure
  *         the RTC clock source (to be done once after reset).
  * @note   Once the RTC clock is configured it cannot be changed unless the
  *         Backup domain is reset using __HAL_RCC_BACKUPRESET_FORCE() macro, or by
  *         a Power On Reset (POR).
  *
  * @param  __RTC_CLKSOURCE__  specifies the RTC clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_RTCCLKSOURCE_NONE No clock selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_LSE  LSE selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_LSI  LSI selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_HSE_DIV32   HSE clock divided by 32 selected
  *            @arg @ref RCC_RTCCLKSOURCE_HSE_DIV128  HSE clock divided by 128 selected
  *            @arg @ref RCC_RTCCLKSOURCE_HSE_DIV8    HSE clock divided by 8 selecte
  *
  * @note   If the LSE or LSI is used as RTC clock source, the RTC continues to
  *         work in STOP and STANDBY modes, and can be used as wakeup source.
  *         However, when the HSE clock is used as RTC clock source, the RTC
  *         cannot be used in STOP and STANDBY modes.
  * @note   The maximum input clock frequency for RTC is 1MHz (when using HSE as
  *         RTC clock source).
  * @retval None
  */
#define __HAL_RCC_RTC_CONFIG(__RTC_CLKSOURCE__)  \
                  MODIFY_REG( RCC->BDCR, (RCC_BDCR_RTCSEL | RCC_BDCR_RTC_HSEDIV_SEL), (__RTC_CLKSOURCE__))


/** @brief Macro to get the RTC clock source.
  * @retval The returned value can be one of the following:
  *            @arg @ref RCC_RTCCLKSOURCE_NONE No clock selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_LSE  LSE selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_LSI  LSI selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_HSE_DIV32   HSE clock divided by 32 selected
  *            @arg @ref RCC_RTCCLKSOURCE_HSE_DIV128  HSE clock divided by 128 selected
  *            @arg @ref RCC_RTCCLKSOURCE_HSE_DIV8    HSE clock divided by 8 selecte
  */
#define  __HAL_RCC_GET_RTC_SOURCE() ((uint32_t)(READ_BIT(RCC->BDCR, (RCC_BDCR_RTCSEL | RCC_BDCR_RTC_HSEDIV_SEL))))
/**
  * @}
  */
#endif

/** @addtogroup RCC_Clock_Configuration
  * @{
  */
/**
  * @brief  Macro to configure the system clock source.
  * @param  __SYSCLKSOURCE__ specifies the system clock source.
  *          This parameter can be one of the following values:
  *              @arg @ref RCC_SYSCLKSOURCE_HSISYS HSI oscillator is used as system clock source.
  *              @arg @ref RCC_SYSCLKSOURCE_HSE HSE oscillator is used as system clock source.
  *              @arg @ref RCC_SYSCLKSOURCE_LSI LSI oscillator is used as system clock source.
  *              @arg @ref RCC_SYSCLKSOURCE_LSE LSE oscillator is used as system clock source.
  *              @arg @ref RCC_SYSCLKSOURCE_PLLCLK PLL oscillator is used as system clock source.
  * @note   Depending on devices and packages, some clocks may not be available.
  *         Refer to device datasheet for clocks availability.
  * @retval None
  */
#define __HAL_RCC_SYSCLK_CONFIG(__SYSCLKSOURCE__) \
                  MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, (__SYSCLKSOURCE__))

/** @brief  Macro to get the clock source used as system clock.
  * @retval The clock source used as system clock. The returned value can be one
  *         of the following:
  *              @arg @ref RCC_SYSCLKSOURCE_STATUS_HSISYS HSI used as system clock.
  *              @arg @ref RCC_SYSCLKSOURCE_STATUS_HSE HSE used as system clock.
  *              @arg @ref RCC_SYSCLKSOURCE_STATUS_PLLCLK PLL used as system clock.
  *              @arg @ref RCC_SYSCLKSOURCE_STATUS_LSI LSI used as system clock source.
  *              @arg @ref RCC_SYSCLKSOURCE_STATUS_LSE LSE used as system clock source.
  * @note   Depending on devices and packages, some clocks may not be available.
  *         Refer to device datasheet for clocks availability.
  */
#define __HAL_RCC_GET_SYSCLK_SOURCE()         (RCC->CFGR & RCC_CFGR_SWS)
#if defined(RCC_LSE_SUPPORT)
/**
  * @brief  Macro to configure the External Low Speed oscillator (LSE) drive capability.
  * @note   As the LSE is in the Backup domain and write access is denied to
  *         this domain after reset, you have to enable write access using
  *         HAL_PWR_EnableBkUpAccess() function before to configure the LSE
  *         (to be done once after reset).
  * @param  __LSEDRIVE__ specifies the new state of the LSE drive capability.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LSEDRIVE_LOW LSE oscillator low drive capability.
  *            @arg @ref RCC_LSEDRIVE_MEDIUM LSE oscillator medium low drive capability.
  *            @arg @ref RCC_LSEDRIVE_HIGH LSE oscillator high drive capability.
  * @retval None
  */
#define __HAL_RCC_LSEDRIVE_CONFIG(__LSEDRIVE__) \
                  MODIFY_REG(RCC->ECSCR, RCC_ECSCR_LSE_DRIVER, (uint32_t)(__LSEDRIVE__))
#endif
/** @brief  Macro to configure the MCO clock.
  * @param  __MCOCLKSOURCE__ specifies the MCO clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCOSOURCE_NOCLOCK     MCO output disabled
  *            @arg @ref RCC_MCOSOURCE_SYSCLK      System  clock selected as MCO source
  *            @arg @ref RCC_MCOSOURCE_HSI10M      HSI10M clock selected as MCO source
  *            @arg @ref RCC_MCOSOURCE_HSI         HSI clock selected as MCO source
  *            @arg @ref RCC_MCOSOURCE_HSE         HSE clock selected as MCO sourcee
  *            @arg @ref RCC_MCOSOURCE_PLL         PLL clock selected as MCO sourcee
  *            @arg @ref RCC_MCOSOURCE_LSI         LSI clock selected as MCO source
  *            @arg @ref RCC_MCOSOURCE_LSE         LSE clock selected as MCO source
  *            @arg @ref RCC_MCOSOURCE_HCLK        HCLK selection as MCO source
  *            @arg @ref RCC_MCOSOURCE_PCLK        PCLK selection as MCO source
  *            @arg @ref RCC_MCOSOURCE_HCLK_UNGATE HCLK without gate selected as MCO source
  *            @arg @ref RCC_MCOSOURCE_PCLK_UNGATE PCLK without gate selected as MCO source
  * @note   Depending on devices and packages, some clocks may not be available.
  *         Refer to device datasheet for clocks availability.
  * @param  __MCODIV__ specifies the MCO clock prescaler.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCODIV_1   MCO clock source is divided by 1
  *            @arg @ref RCC_MCODIV_2   MCO clock source is divided by 2
  *            @arg @ref RCC_MCODIV_4   MCO clock source is divided by 4
  *            @arg @ref RCC_MCODIV_8   MCO clock source is divided by 8
  *            @arg @ref RCC_MCODIV_16  MCO clock source is divided by 16
  *            @arg @ref RCC_MCODIV_32  MCO clock source is divided by 32
  *            @arg @ref RCC_MCODIV_64  MCO clock source is divided by 64
  *            @arg @ref RCC_MCODIV_128 MCO clock source is divided by 128
  *            @arg @ref RCC_MCODIV_256 MCO clock source is divided by 256
  */
#define __HAL_RCC_MCO_CONFIG(__MCOCLKSOURCE__, __MCODIV__) \
                 MODIFY_REG(RCC->CFGR, (RCC_CFGR_MCOSEL | RCC_CFGR_MCOPRE), ((__MCOCLKSOURCE__) | (__MCODIV__)))
/**
  * @}
  */

/** @defgroup RCC_Flags_Interrupts_Management Flags Interrupts Management
  * @brief macros to manage the specified RCC Flags and interrupts.
  * @{
  */

/** @brief  Enable RCC interrupt.
  * @param  __INTERRUPT__ specifies the RCC interrupt sources to be enabled.
  *         This parameter can be any combination of the following values:
  *            @arg @ref RCC_IT_LSIRDY LSI ready interrupt
  *            @arg @ref RCC_IT_LSERDY LSE ready interrupt
  *            @arg @ref RCC_IT_HSIRDY HSI ready interrupt
  *            @arg @ref RCC_IT_HSERDY HSE ready interrupt
  *            @arg @ref RCC_IT_PLLRDY PLL ready interrupt
  * @note   Depending on devices and packages, some clocks may not be available.
  *         Refer to device datasheet for clocks availability.
  * @retval None
  */
#define __HAL_RCC_ENABLE_IT(__INTERRUPT__) SET_BIT(RCC->CIER, (__INTERRUPT__))

/** @brief Disable RCC interrupt.
  * @param  __INTERRUPT__ specifies the RCC interrupt sources to be disabled.
  *         This parameter can be any combination of the following values:
  *            @arg @ref RCC_IT_LSIRDY LSI ready interrupt
  *            @arg @ref RCC_IT_LSERDY LSE ready interrupt
  *            @arg @ref RCC_IT_HSIRDY HSI ready interrupt
  *            @arg @ref RCC_IT_HSERDY HSE ready interrupt
  *            @arg @ref RCC_IT_PLLRDY PLL ready interrupt
  * @note   Depending on devices and packages, some clocks may not be available.
  *         Refer to device datasheet for clocks availability.
  * @retval None
  */
#define __HAL_RCC_DISABLE_IT(__INTERRUPT__) CLEAR_BIT(RCC->CIER, (__INTERRUPT__))

/** @brief  Clear RCC interrupt pending bits.
  * @param  __INTERRUPT__ specifies the interrupt pending bit to clear.
  *         This parameter can be any combination of the following values:
  *            @arg @ref RCC_IT_LSIRDY LSI ready interrupt
  *            @arg @ref RCC_IT_LSERDY LSE ready interrupt
  *            @arg @ref RCC_IT_HSIRDY HSI ready interrupt
  *            @arg @ref RCC_IT_HSERDY HSE ready interrupt
  *            @arg @ref RCC_IT_PLLRDY PLL ready interrupt
  *            @arg @ref RCC_IT_CSS     HSE Clock security system interrupt
  *            @arg @ref RCC_IT_LSECSS  LSE Clock security system interrupt
  * @note   Depending on devices and packages, some clocks may not be available.
  *         Refer to device datasheet for clocks availability.
  * @retval None
  */
#define __HAL_RCC_CLEAR_IT(__INTERRUPT__) (RCC->CICR = (__INTERRUPT__))

/** @brief  Check whether the RCC interrupt has occurred or not.
  * @param  __INTERRUPT__ specifies the RCC interrupt source to check.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_IT_LSIRDY LSI ready interrupt
  *            @arg @ref RCC_IT_LSERDY LSE ready interrupt
  *            @arg @ref RCC_IT_HSIRDY HSI ready interrupt
  *            @arg @ref RCC_IT_HSERDY HSE ready interrupt
  *            @arg @ref RCC_IT_PLLRDY PLL ready interrupt
  *            @arg @ref RCC_IT_CSS     HSE Clock security system interrupt
  *            @arg @ref RCC_IT_LSECSS  LSE Clock security system interrupt
  * @note   Depending on devices and packages, some clocks may not be available.
  *         Refer to device datasheet for clocks availability.
  * @retval The new state of __INTERRUPT__ (TRUE or FALSE).
  */
#define __HAL_RCC_GET_IT(__INTERRUPT__) ((RCC->CIFR & (__INTERRUPT__)) == (__INTERRUPT__))

/** @brief  Set RMVF bit to clear the reset flags.
  *         The reset flags are: RCC_FLAG_OBLRST, RCC_FLAG_PINRST, RCC_FLAG_PORRST,
  *         RCC_FLAG_SFTRST, RCC_FLAG_IWDGRST, RCC_FLAG_BORRST.
  * @note   Depending on the device and software package, some flag bits may not be available.
  *         Refer to the device data sheet for flag bit availability.
  * @retval None
  */
#define __HAL_RCC_CLEAR_RESET_FLAGS() (RCC->CSR |= RCC_CSR_RMVF)

/** @brief  Check whether the selected RCC flag is set or not.
  * @param  __FLAG__ specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_FLAG_HSIRDY HSI oscillator clock ready
  *            @arg @ref RCC_FLAG_HSERDY HSE oscillator clock ready
  *            @arg @ref RCC_FLAG_PLLRDY HSE oscillator clock ready
  *            @arg @ref RCC_FLAG_LSERDY LSE oscillator clock ready
  *            @arg @ref RCC_FLAG_LSECSSD
  *            @arg @ref RCC_FLAG_LSIRDY LSI oscillator clock ready
  *            @arg @ref RCC_FLAG_OBLRST OBLRST reset
  *            @arg @ref RCC_FLAG_PINRST Pin reset
  *            @arg @ref RCC_FLAG_PWRRST BOR, POR, or PDR reset
  *            @arg @ref RCC_FLAG_SFTRST Software reset
  *            @arg @ref RCC_FLAG_IWDGRST Independent Watchdog reset
  *            @arg @ref RCC_FLAG_WWDGRST Window Watchdog reset
  * @note   Depending on the device and software package, some flag bits may not be available.
  *         Refer to the device data sheet for flag bit availability.
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_RCC_GET_FLAG(__FLAG__) (((((((__FLAG__) >> 5U) == CR_REG_INDEX) ? RCC->CR :                  \
                                        ((((__FLAG__) >> 5U) == BDCR_REG_INDEX) ? RCC->BDCR :              \
                                        ((((__FLAG__) >> 5U) == CSR_REG_INDEX) ? RCC->CSR : RCC->CIFR))) & \
                                          (1U << ((__FLAG__) & RCC_FLAG_MASK))) != RESET) \
                                            ? 1U : 0U)

/**
  * @}
  */

/**
  * @}
  */

/* Include RCC HAL Extended module */
#include "py32f032_hal_rcc_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @addtogroup RCC_Exported_Functions
  * @{
  */


/** @addtogroup RCC_Exported_Functions_Group1
  * @{
  */

/* Initialization and de-initialization functions  ******************************/
HAL_StatusTypeDef HAL_RCC_DeInit(void);
HAL_StatusTypeDef HAL_RCC_OscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
HAL_StatusTypeDef HAL_RCC_ClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t FLatency);

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group2
  * @{
  */

/* Peripheral Control functions  ************************************************/
void              HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv);
#if defined(RCC_HSE_SUPPORT)
void              HAL_RCC_EnableCSS(void);
#endif
#if defined(RCC_LSE_SUPPORT)
void              HAL_RCC_EnableLSECSS(void);
void              HAL_RCC_DisableLSECSS(void);
void              HAL_RCC_LSECSSCallback(void);
#endif
uint32_t          HAL_RCC_GetSysClockFreq(void);
uint32_t          HAL_RCC_GetHCLKFreq(void);
uint32_t          HAL_RCC_GetPCLKFreq(void);
void              HAL_RCC_GetOscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
void              HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t *pFLatency);
/* LSE & HSE CSS NMI IRQ handler */
void              HAL_RCC_NMI_IRQHandler(void);
#if defined(RCC_HSE_SUPPORT)
/* User Callbacks in non blocking mode (IT mode) */
void              HAL_RCC_CSSCallback(void);
#endif

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __PY32F032_HAL_RCC_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
