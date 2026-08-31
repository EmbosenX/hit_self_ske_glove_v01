/**
  ******************************************************************************
  * @file    py32f032_ll_opa.h
  * @author  MCU Application Team
  * @brief   Header file of OPA LL module.
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
#ifndef __PY32F032_LL_OPA_H
#define __PY32F032_LL_OPA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f0xx.h"

/** @addtogroup PY32F032_LL_Driver
  * @{
  */

#if defined(OPA1) || defined(OPA2) 

/** @defgroup OPA_LL OPA
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/** @defgroup OPA_LL_Private_Constants OPA Private Constants
  * @{
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup OPA_LL_Private_Macros OPA Private Macros
  * @{
  */
  
/**
  * @}
  */


/* Exported types ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)


#endif /* USE_FULL_LL_DRIVER */

/* Exported constants --------------------------------------------------------*/
/** @defgroup OPA_LL_Exported_Constants OPA Exported Constants
  * @{
  */

/** @defgroup OPA_LL_EC_FUNCTIONAL_MODE OPA functional mode
  * @{
  */
#define LL_OPA_MODE_STANDALONE        (0x00000000UL)                                                /*!< OPA functional mode, OPA operation in standalone */
#define LL_OPA_MODE_PGA               (OPA_OCR_OPA_VMSEL_0)                                         /*!< OPA functional mode, OPA operation in PGA */
/* #define LL_OPA_MODE_FOLLOWER          (OPA_OCR_OPA_VMSEL_1 | OPA_OCR_OPA_VMSEL_0)   */           /*!< OPA functional mode, OPA operation in follower */

/**
  * @}
  */

/** @defgroup OPA_LL_EC_MODE_PGA_GAIN OPA PGA gain (relevant when OPA is in functional mode PGA)
  * @{
  */
#define LL_OPA_PGA_GAIN_2             (0x00000000UL)                                                                                             /*!< OPA PGA gain 2   */
#define LL_OPA_PGA_GAIN_4             (                                                                           OPA_OCR_OPA_PGA_GAIN_0)        /*!< OPA PGA gain 4   */
#define LL_OPA_PGA_GAIN_8             (                                                  OPA_OCR_OPA_PGA_GAIN_1                         )        /*!< OPA PGA gain 8   */
#define LL_OPA_PGA_GAIN_16            (                                                  OPA_OCR_OPA_PGA_GAIN_1 | OPA_OCR_OPA_PGA_GAIN_0)        /*!< OPA PGA gain 16  */
/* #define LL_OPA_PGA_GAIN_32            (                         OPA_OCR_OPA_PGA_GAIN_2                                                  ) */  /*!< OPA PGA gain 32  */
/* #define LL_OPA_PGA_GAIN_64            (                         OPA_OCR_OPA_PGA_GAIN_2 |                          OPA_OCR_OPA_PGA_GAIN_0) */  /*!< OPA PGA gain 64  */
#define LL_OPA_PGA_GAIN_MINUS_1       (OPA_OCR_OPA_PGA_GAIN_3                                                                           )        /*!< OPA PGA gain -1  */
#define LL_OPA_PGA_GAIN_MINUS_3       (OPA_OCR_OPA_PGA_GAIN_3                                                   | OPA_OCR_OPA_PGA_GAIN_0)        /*!< OPA PGA gain -3  */
#define LL_OPA_PGA_GAIN_MINUS_7       (OPA_OCR_OPA_PGA_GAIN_3                          | OPA_OCR_OPA_PGA_GAIN_1                         )        /*!< OPA PGA gain -7  */
#define LL_OPA_PGA_GAIN_MINUS_15      (OPA_OCR_OPA_PGA_GAIN_3                          | OPA_OCR_OPA_PGA_GAIN_1 | OPA_OCR_OPA_PGA_GAIN_0)        /*!< OPA PGA gain -15 */
/* #define LL_OPA_PGA_GAIN_MINUS_31      (OPA_OCR_OPA_PGA_GAIN_3 | OPA_OCR_OPA_PGA_GAIN_2                                                  ) */  /*!< OPA PGA gain -31 */
/* #define LL_OPA_PGA_GAIN_MINUS_63      (OPA_OCR_OPA_PGA_GAIN_3 | OPA_OCR_OPA_PGA_GAIN_2 |                          OPA_OCR_OPA_PGA_GAIN_0) */  /*!< OPA PGA gain -63 */
/**
  * @}
  */

/** @defgroup OPA_LL_EC_INPUT_NONINVERTING OPA input non-inverting
  * @{
  */
#define LL_OPA_BIASVOLTAGE_VCC_2    OPA_OCR_OPA_VBIAS_0           /*!< Bias Voltage 1/2VCC */
#define LL_OPA_BIASVOLTAGE_VCC_5    OPA_OCR_OPA_VBIAS_1           /*!< Bias Voltage 1/5VCC */
/**
  * @}
  */

 
/**
  * @}
  */
/* Exported functions --------------------------------------------------------*/
/** @defgroup OPA_LL_Exported_Functions OPA Exported Functions
  * @{
  */

/** @defgroup OPA_LL_EF_CONFIGURATION_OPA_INSTANCE Configuration of OPA hierarchical scope: OPA instance
  * @{
  */

/**
  * @brief  Set OPA functional mode by setting internal connections.
  *         OPA operation in standalone, follower, ...
  * @rmtoll CSR      OPA_VMSEL          LL_OPA_SetFunctionalMode
  * @param  OPAx OPA instance
  * @param  FunctionalMode This parameter can be one of the following values:
  *         @arg @ref LL_OPA_MODE_STANDALONE
  *         @arg @ref LL_OPA_MODE_PGA
  *         @arg @ref LL_OPA_MODE_FOLLOWER
  * @retval None
  */
__STATIC_INLINE void LL_OPA_SetFunctionalMode(OPA_TypeDef *OPAx, uint32_t FunctionalMode)
{
  MODIFY_REG(OPAx->OCR, OPA_OCR_OPA_VMSEL , FunctionalMode);
}

/**
  * @brief  Get OPA functional mode from setting of internal connections.
  *         OPA operation in standalone, follower, ...
  * @rmtoll OCR      OPA_VMSEL          LL_OPA_GetFunctionalMode
  * @param  OPAx OPA instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPA_MODE_STANDALONE
  *         @arg @ref LL_OPA_MODE_PGA
  *         @arg @ref LL_OPA_MODE_FOLLOWER
  */
__STATIC_INLINE uint32_t LL_OPA_GetFunctionalMode(OPA_TypeDef *OPAx)
{
  return (uint32_t)(READ_BIT(OPAx->OCR, OPA_OCR_OPA_VMSEL));
}

/**
  * @brief  Set OPA PGA gain.
  * @note   Preliminarily, OPA must be set in mode PGA
  *         using function @ref LL_OPA_SetFunctionalMode().
  * @rmtoll OCR      OPA_PGA_GAIN         LL_OPA_SetPGAGain
  * @param  OPAx OPA instance
  * @param  PGAGain This parameter can be one of the following values:
  *         @arg @ref LL_OPA_PGA_GAIN_2
  *         @arg @ref LL_OPA_PGA_GAIN_4
  *         @arg @ref LL_OPA_PGA_GAIN_8
  *         @arg @ref LL_OPA_PGA_GAIN_16
  *         @arg @ref LL_OPA_PGA_GAIN_32
  *         @arg @ref LL_OPA_PGA_GAIN_64
  *         @arg @ref LL_OPA_PGA_GAIN_MINUS_1
  *         @arg @ref LL_OPA_PGA_GAIN_MINUS_3
  *         @arg @ref LL_OPA_PGA_GAIN_MINUS_7
  *         @arg @ref LL_OPA_PGA_GAIN_MINUS_15
  *         @arg @ref LL_OPA_PGA_GAIN_MINUS_31
  *         @arg @ref LL_OPA_PGA_GAIN_MINUS_63
  * @retval None
  */
__STATIC_INLINE void LL_OPA_SetPGAGain(OPA_TypeDef *OPAx, uint32_t PGAGain)
{
  MODIFY_REG(OPAx->OCR,OPA_OCR_OPA_PGA_GAIN, PGAGain);
}

/**
  * @brief  Get OPA PGA gain.
  * @note   Preliminarily, OPA must be set in mode PGA
  *         using function @ref LL_OPA_SetFunctionalMode().
  * @rmtoll OCR      OPA_PGA_GAIN         LL_OPA_GetPGAGain
  * @param  OPAx OPA instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPA_PGA_GAIN_2
  *         @arg @ref LL_OPA_PGA_GAIN_4
  *         @arg @ref LL_OPA_PGA_GAIN_8
  *         @arg @ref LL_OPA_PGA_GAIN_16
  *         @arg @ref LL_OPA_PGA_GAIN_32
  *         @arg @ref LL_OPA_PGA_GAIN_64
  *         @arg @ref LL_OPA_PGA_GAIN_MINUS_1
  *         @arg @ref LL_OPA_PGA_GAIN_MINUS_3
  *         @arg @ref LL_OPA_PGA_GAIN_MINUS_7
  *         @arg @ref LL_OPA_PGA_GAIN_MINUS_15
  *         @arg @ref LL_OPA_PGA_GAIN_MINUS_31
  *         @arg @ref LL_OPA_PGA_GAIN_MINUS_63
  */
__STATIC_INLINE uint32_t LL_OPA_GetPGAGain(OPA_TypeDef *OPAx)
{
  return (uint32_t)(READ_BIT(OPAx->OCR, OPA_OCR_OPA_PGA_GAIN));
}

/**
  * @brief  Enable the OPA.
  * @rmtoll CR      OPAEN            LL_OPA_Enable
  * @param  OPAx OPA instance
  * @retval None
  */
__STATIC_INLINE void LL_OPA_Enable(OPA_TypeDef *OPAx)
{
  SET_BIT(OPAx->CR, OPA_CR_OPAEN);
}

/**
  * @brief  Disable the OPA.
  * @rmtoll CR      OPAEN            LL_OPA_Disable
  * @param  OPAx OPA instance
  * @retval None
  */
__STATIC_INLINE void LL_OPA_Disable(OPA_TypeDef *OPAx)
{
  CLEAR_BIT(OPAx->CR, OPA_CR_OPAEN);
}

/**
  * @brief  Get the OPA Enable state.
  * @rmtoll CR      OPAEN            LL_OPA_IsEnabled
  * @param  OPAx OPA instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_OPA_IsEnabled(OPA_TypeDef *OPAx)
{
  return ((READ_BIT(OPAx->CR, OPA_CR_OPAEN) == (OPA_CR_OPAEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable OPA output connected to IO.
  * @rmtoll OCR      OPA_EXTOEN     LL_OPA_EnableExternalOutput
  * @param  OPAx OPA instance
  * @retval None
  */
__STATIC_INLINE void LL_OPA_EnableExternalOutput(OPA_TypeDef *OPAx)
{
  SET_BIT(OPAx->OCR, OPA_OCR_OPA_EXTOEN);
}

/**
  * @brief  Disable OPA output connected to IO.
  * @rmtoll OCR      OPA_EXTOEN     LL_OPA_DisableExternalOutput
  * @param  OPAx OPA instance
  * @retval None
  */
__STATIC_INLINE void LL_OPA_DisableExternalOutput(OPA_TypeDef *OPAx)
{
  CLEAR_BIT(OPAx->OCR, OPA_OCR_OPA_EXTOEN);
}

/**
  * @brief  Check if OPA output connected to IO is enabled
  * @rmtoll OCR      OPA_EXTOEN     LL_OPA_IsEnabledExternaldOutput
  * @param  OPAx OPA instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_OPA_IsEnabledExternaldOutput(OPA_TypeDef *OPAx)
{
  return ((READ_BIT(OPAx->OCR, OPA_OCR_OPA_EXTOEN) == (OPA_OCR_OPA_EXTOEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable OPA Bias
  * @rmtoll OCR      OPA_VBSEL     LL_OPA_EnableBiasSelection
  * @param  OPAx OPA instance
  * @retval None
  */
__STATIC_INLINE void LL_OPA_EnableBiasSelection(OPA_TypeDef *OPAx)
{
  SET_BIT(OPAx->OCR, OPA_OCR_OPA_VBSEL);
}

/**
  * @brief  Disable OPA Bias
  * @rmtoll OCR      OPA_VBSEL     LL_OPA_DisableBiasSelection
  * @param  OPAx OPA instance
  * @retval None
  */
__STATIC_INLINE void LL_OPA_DisableBiasSelection(OPA_TypeDef *OPAx)
{
  CLEAR_BIT(OPAx->OCR, OPA_OCR_OPA_VBSEL);
}

/**
  * @brief  Check if OPA Bias enabled
  * @rmtoll OCR      OPA_VBSEL     LL_OPA_IsEnabledBiasSelection
  * @param  OPAx OPA instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_OPA_IsEnabledBiasSelection(OPA_TypeDef *OPAx)
{
  return ((READ_BIT(OPAx->OCR, OPA_OCR_OPA_VBSEL) == (OPA_OCR_OPA_VBSEL)) ? 1UL : 0UL);
}

/**
  * @brief  Set OPA Bias Voltage.
  * @rmtoll OCR      OPA_VBIAS         LL_OPA_SetBiasVoltage
  * @param  OPAx OPA instance
  * @param  BiasVoltage This parameter can be one of the following values:
  *         @arg @ref LL_OPA_BIASVOLTAGE_VCC_2
  *         @arg @ref LL_OPA_BIASVOLTAGE_VCC_5
  * @retval None
  */
__STATIC_INLINE void LL_OPA_SetBiasVoltage(OPA_TypeDef *OPAx, uint32_t BiasVoltage)
{
  MODIFY_REG(OPA1->OCR,OPA_OCR_OPA_VBIAS, BiasVoltage);
}

/**
  * @brief  Get OPA Bias Voltage.
  * @rmtoll OCR      OPA_VBIAS         LL_OPA_GetBiasVoltage
  * @param  OPAx OPA instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPA_BIASVOLTAGE_VCC_2
  *         @arg @ref LL_OPA_BIASVOLTAGE_VCC_5
  */
__STATIC_INLINE uint32_t LL_OPA_GetBiasVoltage(OPA_TypeDef *OPAx)
{
  return (uint32_t)(READ_BIT(OPA1->OCR, OPA_OCR_OPA_VBIAS));
}

/**
  * @}
  */


#if defined(USE_FULL_LL_DRIVER)
/** @defgroup OPA_LL_EF_Init Initialization and de-initialization functions
  * @{
  */
ErrorStatus LL_OPA_DeInit(OPA_TypeDef *OPAx);
/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/**
  * @}
  */

/**
  * @}
  */

#endif /* OPA */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __PY32F032_LL_OPA_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
