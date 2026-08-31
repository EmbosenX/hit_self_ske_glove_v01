/**
  ******************************************************************************
  * @file    py32f032_hal_rcc_ex.h
  * @author  MCU Application Team
  * @brief   Header file of RCC HAL Extended module.
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
#ifndef __PY32F032_HAL_RCC_EX_H
#define __PY32F032_HAL_RCC_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f032_hal_def.h"

/** @addtogroup PY32F032_HAL_Driver
  * @{
  */

/** @addtogroup RCCEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup RCCEx_Exported_Types RCCEx Exported Types
  * @{
  */

/**
  * @brief  RCC extended clocks structure definition
  */
typedef struct
{
  uint32_t PeriphClockSelection;   /*!< The Extended Clock to be configured.
                                        This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */
#if defined(RCC_BDCR_RTCSEL)
  uint32_t RtcClockSelection;      /*!< Specifies RTC clock source.
                                        This parameter can be a value of @ref RCC_RTC_Clock_Source */
#endif
  
#if defined(RCC_BDCR_IWDGSEL)
  uint32_t IwdgClockSelection;    /*!< Specifies IWDG clock source
                                        This parameter can be a value of @ref RCCEx_IWDG_Clock_Source */
#endif
  
#if defined(RCC_CCIPR_PVDSEL)
  uint32_t PvdDetectClockSelection;    /*!< Specifies PVD detect clock source.
                                        This parameter can be a value of @ref RCCEx_PVD_Detect_Clock_Source */
#endif
  
#if defined(RCC_CCIPR_COMP1SEL)
  uint32_t Comp1ClockSelection;    /*!< Specifies COMP1 clock source.
                                        This parameter can be a value of @ref RCCEx_COMP1_Clock_Source */
#endif

#if defined(RCC_CCIPR_COMP2SEL)
  uint32_t Comp2ClockSelection;    /*!< Specifies COMP2 clock source.
                                        This parameter can be a value of @ref RCCEx_COMP2_Clock_Source */
#endif

#if defined(RCC_CCIPR_LPUART1SEL)
  uint32_t Lpuart1ClockSelection;    /*!< Specifies LPUART1 clock source.
                                        This parameter can be a value of @ref RCCEx_LPUART1_Clock_Source */
#endif

#if defined(RCC_CCIPR_LPTIM1SEL)
  uint32_t Lptim1ClockSelection;    /*!< Specifies LPTIM1 clock source.
                                        This parameter can be a value of @ref RCCEx_LPTIM1_Clock_Source */
#endif

#if defined(RCC_CCIPR_TIM1SEL)
  uint32_t Tim1ClockSelection;    /*!< Specifies TIM1 clock source.
                                        This parameter can be a value of @ref RCCEx_TIM1_Clock_Source */
#endif

#if defined(RCC_CCIPR_TIM17SEL)
  uint32_t Tim17ClockSelection;    /*!< Specifies TIM17 clock source.
                                        This parameter can be a value of @ref RCCEx_TIM17_Clock_Source */
#endif

#if defined(RCC_CCIPR_ADCSEL)
  uint32_t AdcClockSelection;    /*!< Specifies ADC clock source.
                                        This parameter can be a value of @ref RCCEx_ADC_Clock_Source */
#endif
} RCC_PeriphCLKInitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Constants RCCEx Exported Constants
  * @{
  */
/** @defgroup RCCEx_LSC_Clock_Source Low Speed Clock Source
  * @{
  */
#define RCC_LSCSOURCE_LSI             0x00000000U           /*!< LSI selection for low speed clock output */
#if defined(RCC_LSE_SUPPORT)
#define RCC_LSCSOURCE_LSE             RCC_BDCR_LSCSEL       /*!< LSE selection for low speed clock output */
#endif
/**
  * @}
  */

/** @defgroup RCCEx_Periph_Clock_Selection Periph Clock Selection
  * @{
  */
#if defined(RCC_BDCR_RTCSEL)
#define RCC_PERIPHCLK_RTC              0x00000001U
#endif /* RCC_BDCR_RTCSEL */

#if defined(RCC_BDCR_IWDGSEL)
#define RCC_PERIPHCLK_IWDG             0x00000002U
#endif /* RCC_BDCR_IWDGSEL */

#if defined(RCC_CCIPR_PVDSEL)
#define RCC_PERIPHCLK_PVD              0x00000004U
#endif /* RCC_CCIPR_PVDSEL */

#if defined(RCC_CCIPR_COMP1SEL)
#define RCC_PERIPHCLK_COMP1            0x00000008U
#endif /* RCC_CCIPR_COMP1SEL */

#if defined(RCC_CCIPR_COMP2SEL)
#define RCC_PERIPHCLK_COMP2            0x00000010U
#endif /* RCC_CCIPR_COMP2SEL */

#if defined(RCC_CCIPR_LPUART1SEL)
#define RCC_PERIPHCLK_LPUART1          0x00000020U
#endif /* RCC_CCIPR_LPUART1SEL */

#if defined(RCC_CCIPR_LPTIM1SEL)
#define RCC_PERIPHCLK_LPTIM1           0x00000040U
#endif /* RCC_CCIPR_LPTIM1SEL */

#if defined(RCC_CCIPR_TIM1SEL)
#define RCC_PERIPHCLK_TIM1             0x00000080U
#endif /* RCC_CCIPR_TIM1SEL */

#if defined(RCC_CCIPR_TIM17SEL)
#define RCC_PERIPHCLK_TIM17            0x00000100U
#endif /* RCC_CCIPR_TIM17SEL */

#if defined(RCC_CCIPR_ADCSEL)
#define RCC_PERIPHCLK_ADC              0x00000200U
#endif /* RCC_CCIPR_ADCSEL */
/**
  * @}
  */

#if defined(RCC_BDCR_IWDGSEL)
/** @defgroup RCCEx_IWDG_Clock_Source IWDG Clock Source
  * @{
  */
#define RCC_IWDGCLKSOURCE_LSI         0x00000000U            /*!< LSI clock selected as IWDG clock */
#if defined(RCC_LSE_SUPPORT)
#define RCC_IWDGCLKSOURCE_LSE        RCC_BDCR_IWDGSEL       /*!< LSE clock selected as IWDG clock */
#endif
/**
  * @}
  */
#endif /* RCC_CCIPR_IWDGSEL */

/** @defgroup RCCEx_PVD_Detect_Clock_Source PVD Detect Clock Source
  * @{
  */
#define RCC_PVDDETECTCLKSOURCE_PCLK    0x00000000U
#define RCC_PVDDETECTCLKSOURCE_LSC     RCC_CCIPR_PVDSEL
/**
  * @}
  */

#if defined(RCC_CCIPR_COMP1SEL)
/** @defgroup RCCEx_COMP1_Clock_Source COMP1 Clock Source
  * @{
  */
#define RCC_COMP1CLKSOURCE_PCLK        0x00000000U                                      /*!< APB clock selected as COMP1 clock */
#define RCC_COMP1CLKSOURCE_LSC         RCC_CCIPR_COMP1SEL                               /*!< LSC clock selected as COMP1 clock */
/**
  * @}
  */
#endif /* RCC_CCIPR_COMP1SEL */

#if defined(RCC_CCIPR_COMP2SEL)
/** @defgroup RCCEx_COMP2_Clock_Source COMP2 Clock Source
  * @{
  */
#define RCC_COMP2CLKSOURCE_PCLK        0x00000000U                                      /*!< APB clock selected as COMP2 clock */
#define RCC_COMP2CLKSOURCE_LSC         RCC_CCIPR_COMP2SEL                               /*!< LSC clock selected as COMP2 clock */
/**
  * @}
  */
#endif /* RCC_CCIPR_COMP2SEL */

/** @defgroup RCCEx_LPUART1_Clock_Source LPUART1 Clock Source
  * @{
  */
#define RCC_LPUART1CLKSOURCE_PCLK      0x00000000U
#define RCC_LPUART1CLKSOURCE_SYSCLK    RCC_CCIPR_LPUART1SEL_0
#define RCC_LPUART1CLKSOURCE_LSI       RCC_CCIPR_LPUART1SEL_1
#define RCC_LPUART1CLKSOURCE_LSE       (RCC_CCIPR_LPUART1SEL_0 | RCC_CCIPR_LPUART1SEL_1)
/**
  * @}
  */

/** @defgroup RCCEx_LPTIM1_Clock_Source LPTIM1 Clock Source
  * @{
  */
#define RCC_LPTIM1CLKSOURCE_PCLK       0x00000000U
#define RCC_LPTIM1CLKSOURCE_LSI        RCC_CCIPR_LPTIM1SEL_0
#define RCC_LPTIM1CLKSOURCE_LSE        RCC_CCIPR_LPTIM1SEL
/**
  * @}
  */

/** @defgroup RCCEx_TIM1_Clock_Source TIM1 Clock Source
  * @{
  */
#define RCC_TIM1CLKSOURCE_PCLK       0x00000000U
#if defined(RCC_PLL_SUPPORT)
#define RCC_TIM1CLKSOURCE_PLL        RCC_CCIPR_TIM1SEL
#endif
/**
  * @}
  */
  
/** @defgroup RCCEx_TIM17_Clock_Source TIM17 Clock Source
  * @{
  */
#define RCC_TIM17CLKSOURCE_PCLK       0x00000000U
#if defined(RCC_PLL_SUPPORT)
#define RCC_TIM17CLKSOURCE_PLL        RCC_CCIPR_TIM17SEL
#endif
/**
  * @}
  */

/** @defgroup RCCEx_ADC_Clock_Source ADC Clock Source
  * @{
  */
#define RCC_ADCCLKSOURCE_SYSCLK        0x00000000U
#if defined(RCC_PLL_SUPPORT)
#define RCC_ADCCLKSOURCE_PLL           RCC_CCIPR_ADCSEL_0
#endif
#define RCC_ADCCLKSOURCE_HSI           RCC_CCIPR_ADCSEL_1
/**
  * @}
  */

/** @defgroup RCCEx_PVD_Detect_Clock_Source PVD Detect Clock Source
  * @{
  */
#define RCC_PVDDETECTCLKSOURCE_PCLK    0x00000000U
#define RCC_PVDDETECTCLKSOURCE_LSC     RCC_CCIPR_PVDSEL
/**
  * @}
  */

/** @defgroup RCCEx_TIM_PCLK_Frequency_Control TIM PCLK Frequency Control
  * @{
  */
#define RCC_TIMPCLK_MUL2       0x00000000U               /*!< TIMER PCLK is twice the system PCLK, but the frequency will not exceed HCLK */
#define RCC_TIMPCLK_MUL1       RCC_CCIPR_TIMCLK_CTRL      /*!< TIMER PCLK is the system PCLK */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Macros RCCEx Exported Macros
 * @{
 */

/** @brief  Macro to configure the PVD detect clock.
  * @param  __PVDDETECTCLKSOURCE__ specifies the CAN clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_PVDDETECTCLKSOURCE_PCLK  PCLK clock selected as PVD detect clock
  *            @arg @ref RCC_PVDDETECTCLKSOURCE_LSC   LSC clock selected as PVD detect clock
*/
#define __HAL_RCC_PVD_CONFIG(__PVDDETECTCLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_PVDSEL, (uint32_t)(__PVDDETECTCLKSOURCE__))

/** @brief  Macro to get the PVD detect clock.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_PVDDETECTCLKSOURCE_PCLK  PCLK clock selected as PVD detect clock
  *            @arg @ref RCC_PVDDETECTCLKSOURCE_LSC   LSC clock selected as PVD detect clock
  */
#define __HAL_RCC_GET_PVD_DETECT_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_PVDSEL)))

#if defined(RCC_CCIPR_COMP1SEL)
/** @brief  Macro to configure the COMP1 clock (COMP1CLK).
  *
  * @param  __COMP1_CLKSOURCE__ specifies the COMP1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_COMP1CLKSOURCE_PCLK   PCLK selected as COMP1 clock
  *            @arg @ref RCC_COMP1CLKSOURCE_LSC    LSC selected as COMP1 clock
  */
#define __HAL_RCC_COMP1_CONFIG(__COMP1_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_COMP1SEL, (uint32_t)(__COMP1_CLKSOURCE__))

/** @brief  Macro to get the COMP1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_COMP1CLKSOURCE_PCLK   PCLK selected as COMP1 clock
  *            @arg @ref RCC_COMP1CLKSOURCE_LSC    LSC selected as COMP1 clock
  */
#define __HAL_RCC_GET_COMP1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_COMP1SEL)))
#endif /* RCC_CCIPR_COMP1SEL */

#if defined(RCC_CCIPR_COMP2SEL)
/** @brief  Macro to configure the COMP2 clock (COMP2CLK).
  *
  * @param  __COMP2_CLKSOURCE__ specifies the COMP2 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_COMP2CLKSOURCE_PCLK   PCLK selected as COMP2 clock
  *            @arg @ref RCC_COMP2CLKSOURCE_LSC  LSC selected as COMP2 clock
  */
#define __HAL_RCC_COMP2_CONFIG(__COMP2_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_COMP2SEL, (uint32_t)(__COMP2_CLKSOURCE__))

/** @brief  Macro to get the COMP2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_COMP2CLKSOURCE_PCLK   PCLK selected as COMP2 clock
  *            @arg @ref RCC_COMP2CLKSOURCE_LSC  LSC selected as COMP2 clock
  */
#define __HAL_RCC_GET_COMP2_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_COMP2SEL)))
#endif /* RCC_CCIPR_COMP2SEL */

#if defined(RCC_BDCR_IWDGSEL)
/** @brief  Macro to configure the IWDG clock (IWDGCLK).
  *
  * @param  __IWDG_CLKSOURCE__ specifies the IWDG clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_IWDGCLKSOURCE_LSI  LSI  selected as IWDG clock
  *            @arg @ref RCC_IWDGCLKSOURCE_LSE  LSE  selected as IWDG clock
  * @note   Depending on devices and packages, some clocks may not be available.
  *         Refer to device datasheet for clocks availability.
  */
#define __HAL_RCC_IWDG_CONFIG(__IWDG_CLKSOURCE__) \
                  MODIFY_REG(RCC->BDCR, RCC_BDCR_IWDGSEL, (uint32_t)(__IWDG_CLKSOURCE__))

/** @brief  Macro to get the IWDG clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_IWDGCLKSOURCE_LSI  LSI selected as IWDG clock
  *            @arg @ref RCC_IWDGCLKSOURCE_LSE  LSE selected as IWDG clock
  * @note   Depending on devices and packages, some clocks may not be available.
  *         Refer to device datasheet for clocks availability.
  */
#define __HAL_RCC_GET_IWDG_SOURCE() ((uint32_t)(READ_BIT(RCC->BDCR, RCC_BDCR_IWDGSEL)))
#endif /* RCC_CCIPR_IWDGSEL */

/** @brief  Macro to configure the TIMER PCLK frequency control.
  * @param  __TIMPCLK_MUL__ TIMPCLK multiple frequency factor.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_TIMPCLK_MUL2 TIMER PCLK is twice the system PCLK, but the frequency will not exceed HCLK
  *            @arg @ref RCC_TIMPCLK_MUL1 TIMER PCLK is the system PCLK
  */
#define __HAL_RCC_TIMPCLK_CONFIG(__TIMPCLK_MUL__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_TIMCLK_CTRL, (uint32_t)(__TIMPCLK_MUL__))

/** @brief  Macro to get the TIMPCLK multiple frequency factor.
  * @retval The multiple frequency factor can be one of the following values:
  *            @arg @ref RCC_TIMPCLK_MUL2 TIMER PCLK is twice the system PCLK, but the frequency will not exceed HCLK
  *            @arg @ref RCC_TIMPCLK_MUL1 TIMER PCLK is the system PCLK
  */
#define __HAL_RCC_GET_TIMPCLK_MUL() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_TIMCLK_CTRL)))

/** @brief  Macro to configure the LPUART1 clock (LPUART1CLK).
  *
  * @param  __LPUART1_CLKSOURCE__ specifies the LPUART1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPUART1CLKSOURCE_PCLK    PCLK selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_SYSCLK  SYSCLK selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_LSI     HSI selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_LSE     LSE selected as LPUART1 clock
  * @retval None
  */
#define __HAL_RCC_LPUART1_CONFIG(__LPUART1_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_LPUART1SEL, (__LPUART1_CLKSOURCE__))

/** @brief  Macro to get the LPUART1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPUART1CLKSOURCE_PCLK    PCLK selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_SYSCLK  SYSCLK selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_LSI     HSI selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_LSE     LSE selected as LPUART1 clock
  */
#define __HAL_RCC_GET_LPUART1_SOURCE() (READ_BIT(RCC->CCIPR, RCC_CCIPR_LPUART1SEL))

/** @brief  Macro to configure the LPTIM1 clock (LPTIM1CLK).
  *
  * @param  __LPTIM1_CLKSOURCE__ specifies the LPTIM1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPTIM1CLKSOURCE_PCLK  PCLK selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSI  HSI selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSE  LSE selected as LPTIM1 clock
  * @retval None
  */
#define __HAL_RCC_LPTIM1_CONFIG(__LPTIM1_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_LPTIM1SEL, (__LPTIM1_CLKSOURCE__))

/** @brief  Macro to get the LPTIM1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPTIM1CLKSOURCE_PCLK  PCLK selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSI  HSI selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSE  LSE selected as LPTIM1 clock
  */
#define __HAL_RCC_GET_LPTIM1_SOURCE() (READ_BIT(RCC->CCIPR, RCC_CCIPR_LPTIM1SEL))

/** @brief  Macro to configure the TIM1 clock (TIM1CLK).
  *
  * @param  __TIM1_CLKSOURCE__ specifies the TIM1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_TIM1CLKSOURCE_PCLK  PCLK selected as TIM1 clock
  *            @arg @ref RCC_TIM1CLKSOURCE_PLL   PLL selected as TIM1 clock
  * @retval None
  */
#define __HAL_RCC_TIM1_CONFIG(__TIM1_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_TIM1SEL, (__TIM1_CLKSOURCE__))

/** @brief  Macro to get the TIM1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_TIM1CLKSOURCE_PCLK  PCLK selected as TIM1 clock
  *            @arg @ref RCC_TIM1CLKSOURCE_PLL   PLL selected as TIM1 clock
  */
#define __HAL_RCC_GET_TIM1_SOURCE() (READ_BIT(RCC->CCIPR, RCC_CCIPR_TIM1SEL))

/** @brief  Macro to configure the TIM17 clock (TIM17CLK).
  *
  * @param  __TIM17_CLKSOURCE__ specifies the TIM17 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_TIM17CLKSOURCE_PCLK  PCLK selected as TIM17 clock
  *            @arg @ref RCC_TIM17CLKSOURCE_PLL   PLL selected as TIM17 clock
  * @retval None
  */
#define __HAL_RCC_TIM17_CONFIG(__TIM17_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_TIM17SEL, (__TIM17_CLKSOURCE__))

/** @brief  Macro to get the TIM17 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_TIM17CLKSOURCE_PCLK  PCLK selected as TIM17 clock
  *            @arg @ref RCC_TIM17CLKSOURCE_PLL   PLL selected as TIM17 clock
  */
#define __HAL_RCC_GET_TIM17_SOURCE() (READ_BIT(RCC->CCIPR, RCC_CCIPR_TIM17SEL))

/** @brief  Macro to configure the ADC clock (ADCCLK).
  *
  * @param  __ADC_CLKSOURCE__ specifies the ADC clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_ADCCLKSOURCE_SYSCLK  SYSCLK selected as ADC clock
  *            @arg @ref RCC_ADCCLKSOURCE_PLL  PLL selected as ADC clock
  *            @arg @ref RCC_ADCCLKSOURCE_HSI  HSI selected as ADC clock
  * @retval None
  */
#define __HAL_RCC_ADC_CONFIG(__ADC_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_ADCSEL, (__ADC_CLKSOURCE__))

/** @brief  Macro to get the ADC clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_ADCCLKSOURCE_SYSCLK  SYSCLK selected as ADC clock
  *            @arg @ref RCC_ADCCLKSOURCE_PLL  PLL selected as ADC clock
  *            @arg @ref RCC_ADCCLKSOURCE_HSI  HSI selected as ADC clock
  */
#define __HAL_RCC_GET_ADC_SOURCE() (READ_BIT(RCC->CCIPR, RCC_CCIPR_ADCSEL))

/** @defgroup RCCEx_Flags_Interrupts_Management Flags Interrupts Management
  * @brief macros to manage the specified RCC Flags and interrupts.
  * @{
  */



/**
  * @}
  */


/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup RCCEx_Exported_Functions
  * @{
  */

/** @addtogroup RCCEx_Exported_Functions_Group1
  * @{
  */

HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);
void              HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);
uint32_t          HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk);

/**
  * @}
  */

/** @addtogroup RCCEx_Exported_Functions_Group2
  * @{
  */
void HAL_RCCEx_SetLSCSource(uint32_t LSCSource);
uint32_t HAL_RCCEx_GetLSCSource(void);
/**
  * @}
  */


/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup RCCEx_Private_Macros RCCEx Private Macros
  * @{
  */
#if defined(RCC_LSE_SUPPORT)
#define IS_RCC_LSCSOURCE(__SOURCE__) (((__SOURCE__) == RCC_LSCSOURCE_LSI) || \
                                      ((__SOURCE__) == RCC_LSCSOURCE_LSE))
#else
#define IS_RCC_LSCSOURCE(__SOURCE__) ((__SOURCE__) == RCC_LSCSOURCE_LSI)
#endif
#if defined(RCC_LSE_SUPPORT)
#define IS_RCC_IWDGCLKSOURCE(__IWDGCLK__)  (((__IWDGCLK__) == RCC_IWDGCLKSOURCE_LSI) || ((__IWDGCLK__) == RCC_IWDGCLKSOURCE_LSE))
#else
#define IS_RCC_IWDGCLKSOURCE(__IWDGCLK__)  (((__IWDGCLK__) == RCC_IWDGCLKSOURCE_LSI))
#endif

#define IS_RCC_PVDDETECTCLKSOURCE(__PVDDETECTCLK__)  (((__PVDDETECTCLK__) == RCC_PVDDETECTCLKSOURCE_PCLK) || ((__PVDDETECTCLK__) == RCC_PVDDETECTCLKSOURCE_LSC))

#define IS_RCC_COMP1CLKSOURCE(__COMP1CLK__)  (((__COMP1CLK__) == RCC_COMP1CLKSOURCE_PCLK) || ((__COMP1CLK__) == RCC_COMP1CLKSOURCE_LSC))

#define IS_RCC_COMP2CLKSOURCE(__COMP2CLK__)  (((__COMP2CLK__) == RCC_COMP2CLKSOURCE_PCLK) || ((__COMP2CLK__) == RCC_COMP2CLKSOURCE_LSC))

#if defined(RCC_LSE_SUPPORT) 
#define IS_RCC_LPUART1CLKSOURCE(__LPUART1CLK__) (((__LPUART1CLK__) == RCC_LPUART1CLKSOURCE_PCLK) || ((__LPUART1CLK__) == RCC_LPUART1CLKSOURCE_SYSCLK) || \
                                                 ((__LPUART1CLK__) == RCC_LPUART1CLKSOURCE_LSI)  || ((__LPUART1CLK__) == RCC_LPUART1CLKSOURCE_LSE))
#else
#define IS_RCC_LPUART1CLKSOURCE(__LPUART1CLK__) (((__LPUART1CLK__) == RCC_LPUART1CLKSOURCE_PCLK) || ((__LPUART1CLK__) == RCC_LPUART1CLKSOURCE_SYSCLK) || \
                                                 ((__LPUART1CLK__) == RCC_LPUART1CLKSOURCE_LSI))
#endif
#if defined(RCC_LSE_SUPPORT) 
#define IS_RCC_LPTIM1CLKSOURCE(__LPTIM1CLK__)  (((__LPTIM1CLK__) == RCC_LPTIM1CLKSOURCE_PCLK) || ((__LPTIM1CLK__) == RCC_LPTIM1CLKSOURCE_LSI) || \
                                                ((__LPTIM1CLK__) == RCC_LPTIM1CLKSOURCE_LSE))
#else
#define IS_RCC_LPTIM1CLKSOURCE(__LPTIM1CLK__)  (((__LPTIM1CLK__) == RCC_LPTIM1CLKSOURCE_PCLK) || ((__LPTIM1CLK__) == RCC_LPTIM1CLKSOURCE_LSI))
#endif
#if defined(RCC_PLL_SUPPORT)
#define IS_RCC_TIM1CLKSOURCE(__TIM1CLK__)  (((__TIM1CLK__) == RCC_TIM1CLKSOURCE_PCLK) || ((__TIM1CLK__) == RCC_TIM1CLKSOURCE_PLL))
#else
#define IS_RCC_TIM1CLKSOURCE(__TIM1CLK__)  (((__TIM1CLK__) == RCC_TIM1CLKSOURCE_PCLK))
#endif

#if defined(RCC_PLL_SUPPORT)
#define IS_RCC_TIM17CLKSOURCE(__TIM17CLK__)  (((__TIM17CLK__) == RCC_TIM17CLKSOURCE_PCLK) || ((__TIM17CLK__) == RCC_TIM17CLKSOURCE_PLL))
#else
#define IS_RCC_TIM17CLKSOURCE(__TIM17CLK__)  (((__TIM17CLK__) == RCC_TIM17CLKSOURCE_PCLK))
#endif

#if defined(RCC_PLL_SUPPORT)
#define IS_RCC_ADCCLKSOURCE(__ADCCLK__) (((__ADCCLK__) == RCC_ADCCLKSOURCE_SYSCLK)  || ((__ADCCLK__) == RCC_ADCCLKSOURCE_PLL)   || \
                                         ((__ADCCLK__) == RCC_ADCCLKSOURCE_HSI))
#else
#define IS_RCC_ADCCLKSOURCE(__ADCCLK__) (((__ADCCLK__) == RCC_ADCCLKSOURCE_SYSCLK)   || \
                                         ((__ADCCLK__) == RCC_ADCCLKSOURCE_HSI))
#endif
#define IS_RCC_PERIPHCLOCK(__SELECTION__)  \
  ((((__SELECTION__) & RCC_PERIPHCLK_RTC)     == RCC_PERIPHCLK_RTC)     || \
   (((__SELECTION__) & RCC_PERIPHCLK_IWDG)    == RCC_PERIPHCLK_IWDG)    || \
   (((__SELECTION__) & RCC_PERIPHCLK_PVD)     == RCC_PERIPHCLK_PVD)     || \
   (((__SELECTION__) & RCC_PERIPHCLK_COMP1)   == RCC_PERIPHCLK_COMP1)   || \
   (((__SELECTION__) & RCC_PERIPHCLK_COMP2)   == RCC_PERIPHCLK_COMP2)   || \
   (((__SELECTION__) & RCC_PERIPHCLK_LPUART1) == RCC_PERIPHCLK_LPUART1) || \
   (((__SELECTION__) & RCC_PERIPHCLK_LPTIM1)  == RCC_PERIPHCLK_LPTIM1)  || \
   (((__SELECTION__) & RCC_PERIPHCLK_TIM1)    == RCC_PERIPHCLK_TIM1)    || \
   (((__SELECTION__) & RCC_PERIPHCLK_TIM17)   == RCC_PERIPHCLK_TIM17)   || \
   (((__SELECTION__) & RCC_PERIPHCLK_ADC)     == RCC_PERIPHCLK_ADC))

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

#endif /* __PY32F032_HAL_RCC_EX_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
