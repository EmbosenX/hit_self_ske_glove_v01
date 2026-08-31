/**
  ******************************************************************************
  * @file    py32f032_hal_opa.h
  * @author  MCU Application Team
  * @brief   Header file of OPA HAL module.
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
#ifndef PY32F032_HAL_OPA_H
#define PY32F032_HAL_OPA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f032_hal_def.h"

/** @addtogroup PY32F032_HAL_Driver
  * @{
  */

/** @addtogroup OPA
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup OPA_Exported_Types OPA Exported Types
  * @{
  */

/**
  * @brief  OPA Init structure definition
  */

typedef struct
{
  uint32_t Mode;                        /*!< Specifies the OPA mode
                                             This parameter must be a value of @ref OPA_Mode
                                             mode is either Standalone, PGA */

  FunctionalState ExternalOutput;       /*!< Specifies the configuration of the External output to IO.
                                             This parameter can be ENABLE or DISABLE
                                             Note: When this output is Disable, regular output to I/O is Disabled */

  uint32_t PgaGain;                     /*!< Specifies the gain in PGA mode
                                             i.e. when mode is OPA_PGA_MODE.
                                             This parameter must be a value of @ref OPA_PgaGain
                                             (2, 4, 8, 16, 32 or 64) for positive gain & (-1, -3 ,-7, -15, -31 or -63) for negative gain */

  uint32_t BiasVoltage;                 /*!< Specifies the Bias Voltage   
                                            This parameter must be a value of @ref OPA_BiasVoltage */


} OPA_InitTypeDef;

/**
  * @brief  HAL State structures definition
  */

typedef enum
{
  HAL_OPA_STATE_RESET               = 0x00000000UL, /*!< OPA is not yet Initialized          */

  HAL_OPA_STATE_READY               = 0x00000001UL, /*!< OPA is initialized and ready for use */

  HAL_OPA_STATE_BUSY                = 0x00000004UL, /*!< OPA is enabled and running in normal mode */

} HAL_OPA_StateTypeDef;

/**
  * @brief OPA Handle Structure definition
  */
#if (USE_HAL_OPA_REGISTER_CALLBACKS == 1)
typedef struct __OPA_HandleTypeDef
#else
typedef struct
#endif
{
  OPA_TypeDef       *Instance;                    /*!< OPA instance's registers base address   */
  OPA_InitTypeDef   Init;                         /*!< OPA required parameters */
  HAL_StatusTypeDef Status;                         /*!< OPA peripheral status   */
  HAL_LockTypeDef   Lock;                           /*!< Locking object          */
  __IO HAL_OPA_StateTypeDef  State;               /*!< OPA communication state */

#if (USE_HAL_OPA_REGISTER_CALLBACKS == 1)
  void (* MspInitCallback)(struct __OPA_HandleTypeDef *hopa);
  void (* MspDeInitCallback)(struct __OPA_HandleTypeDef *hopa);
#endif /* USE_HAL_OPA_REGISTER_CALLBACKS */

} OPA_HandleTypeDef;

/**
  * @}
  */
#if (USE_HAL_OPA_REGISTER_CALLBACKS == 1)
/**
  * @brief  HAL OPA Callback ID enumeration definition
  */
typedef enum
{
  HAL_OPA_MSPINIT_CB_ID                     = 0x01UL,  /*!< OPA MspInit Callback ID           */
  HAL_OPA_MSPDEINIT_CB_ID                   = 0x02UL,  /*!< OPA MspDeInit Callback ID         */
  HAL_OPA_ALL_CB_ID                          = 0x03UL   /*!< OPA All ID                        */
} HAL_OPA_CallbackIDTypeDef;

/**
  * @brief  HAL OPA Callback pointer definition
  */
typedef void (*pOPA_CallbackTypeDef)(OPA_HandleTypeDef *hopa);
#endif /* USE_HAL_OPA_REGISTER_CALLBACKS */


/* Exported constants --------------------------------------------------------*/
/** @defgroup OPA_Exported_Constants OPA Exported Constants
  * @{
  */
/** @defgroup OPA_Mode OPA Mode
  * @{
  */
#define OPA_STANDALONE_MODE            (0x00000000UL)         /*!< standalone mode */
#define OPA_PGA_MODE                   OPA_OCR_OPA_VMSEL_0    /*!< PGA mode */
/* #define OPA_FOLLOWER_MODE              OPA_OCR_OPA_VMSEL_1 */   /*!< follower mode */
/**
  * @}
  */

/** @defgroup OPA_PgaGain OPA Pga Gain
  * @{
  */
#define OPA_PGA_GAIN_2           (0x00000000UL)                                                                                             /*!< PGA gain could be 2  */
#define OPA_PGA_GAIN_4           (                                                                           OPA_OCR_OPA_PGA_GAIN_0)        /*!< PGA gain could be 4  */
#define OPA_PGA_GAIN_8           (                                                  OPA_OCR_OPA_PGA_GAIN_1                         )        /*!< PGA gain could be 8  */
#define OPA_PGA_GAIN_16          (                                                  OPA_OCR_OPA_PGA_GAIN_1 | OPA_OCR_OPA_PGA_GAIN_0)        /*!< PGA gain could be 16 */
/* #define OPA_PGA_GAIN_32          (                         OPA_OCR_OPA_PGA_GAIN_2                                                  ) */  /*!< PGA gain could be 32 */
/* #define OPA_PGA_GAIN_64          (                         OPA_OCR_OPA_PGA_GAIN_2                          | OPA_OCR_OPA_PGA_GAIN_0) */  /*!< PGA gain could be 64 */
#define OPA_PGA_GAIN_MINUS_1     (OPA_OCR_OPA_PGA_GAIN_3                                                                           )        /*!< PGA gain could be -1  */
#define OPA_PGA_GAIN_MINUS_3     (OPA_OCR_OPA_PGA_GAIN_3                                                   | OPA_OCR_OPA_PGA_GAIN_0)        /*!< PGA gain could be -3  */
#define OPA_PGA_GAIN_MINUS_7     (OPA_OCR_OPA_PGA_GAIN_3                          | OPA_OCR_OPA_PGA_GAIN_1                         )        /*!< PGA gain could be -7  */
#define OPA_PGA_GAIN_MINUS_15    (OPA_OCR_OPA_PGA_GAIN_3                          | OPA_OCR_OPA_PGA_GAIN_1 | OPA_OCR_OPA_PGA_GAIN_0)        /*!< PGA gain could be -15 */
/* #define OPA_PGA_GAIN_MINUS_31    (OPA_OCR_OPA_PGA_GAIN_3 | OPA_OCR_OPA_PGA_GAIN_2                                                  ) */  /*!< PGA gain could be -31 */
/* #define OPA_PGA_GAIN_MINUS_63    (OPA_OCR_OPA_PGA_GAIN_3 | OPA_OCR_OPA_PGA_GAIN_2 |                          OPA_OCR_OPA_PGA_GAIN_0) */  /*!< PGA gain could be -63 */
/**
  * @}
  */

/** @defgroup OPA_BiasVoltage OPA Bias Voltage
  * @{
  */
#define OPA_BIASVOLTAGE_VCC_DIV2       (OPA_OCR_OPA_VBIAS_0 )              
                                                                    
#define OPA_BIASVOLTAGE_VCC_DIV5       (OPA_OCR_OPA_VBIAS_1 )     

#define OPA_BIASVOLTAGE_DISABLE        (0x00000000)    
/**
  * @}
  */

/**
  * @}
  */


/* Private constants ---------------------------------------------------------*/
/** @defgroup OPA_Private_Constants OPA Private Constants
  * @brief   OPA Private constants and defines
  * @{
  */

/**
  * @}
  */


/* Private macro -------------------------------------------------------------*/

/** @defgroup OPA_Private_Macros OPA Private Macros
  * @{
  */
#if defined(OPA_FOLLOWER_MODE)
#define IS_OPA_FUNCTIONAL_NORMALMODE(MODE) (((MODE) == OPA_STANDALONE_MODE) || \
                                               ((MODE) == OPA_PGA_MODE) || \
                                               ((MODE) == OPA_FOLLOWER_MODE))
#else
#define IS_OPA_FUNCTIONAL_NORMALMODE(MODE) (((MODE) == OPA_STANDALONE_MODE) || \
                                               ((MODE) == OPA_PGA_MODE))
#endif

#if defined(OPA_PGA_GAIN_32)
#define IS_OPA_PGA_GAIN(GAIN)   (((GAIN) == OPA_PGA_GAIN_2)   || \
                                 ((GAIN) == OPA_PGA_GAIN_4)   || \
                                 ((GAIN) == OPA_PGA_GAIN_8)   || \
                                 ((GAIN) == OPA_PGA_GAIN_16) || \
                                 ((GAIN) == OPA_PGA_GAIN_32) || \
                                 ((GAIN) == OPA_PGA_GAIN_64)   || \
                                 ((GAIN) == OPA_PGA_GAIN_MINUS_1)   || \
                                 ((GAIN) == OPA_PGA_GAIN_MINUS_3) || \
                                 ((GAIN) == OPA_PGA_GAIN_MINUS_7) || \
                                 ((GAIN) == OPA_PGA_GAIN_MINUS_15)   || \
                                 ((GAIN) == OPA_PGA_GAIN_MINUS_31) || \
                                 ((GAIN) == OPA_PGA_GAIN_MINUS_63))
#else
#define IS_OPA_PGA_GAIN(GAIN)   (((GAIN) == OPA_PGA_GAIN_2)   || \
                                 ((GAIN) == OPA_PGA_GAIN_4)   || \
                                 ((GAIN) == OPA_PGA_GAIN_8)   || \
                                 ((GAIN) == OPA_PGA_GAIN_16) || \
                                 ((GAIN) == OPA_PGA_GAIN_MINUS_1)   || \
                                 ((GAIN) == OPA_PGA_GAIN_MINUS_3) || \
                                 ((GAIN) == OPA_PGA_GAIN_MINUS_7) || \
                                 ((GAIN) == OPA_PGA_GAIN_MINUS_15))
#endif

/**
  * @}
  */


/* Exported macros -----------------------------------------------------------*/
/** @defgroup OPA_Exported_Macros OPA Exported Macros
  * @{
  */

/** @brief Reset OPA handle state
  * @param  __HANDLE__ OPA handle.
  * @retval None
  */
#define __HAL_OPA_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_OPA_STATE_RESET)

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup OPA_Exported_Functions OPA Exported Functions
  * @{
  */

/** @defgroup OPA_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */

/* Initialization/de-initialization functions  **********************************/
HAL_StatusTypeDef HAL_OPA_Init(OPA_HandleTypeDef *hopa);
HAL_StatusTypeDef HAL_OPA_DeInit(OPA_HandleTypeDef *hopa);
void HAL_OPA_MspInit(OPA_HandleTypeDef *hopa);
void HAL_OPA_MspDeInit(OPA_HandleTypeDef *hopa);
/**
  * @}
  */


/** @defgroup OPA_Exported_Functions_Group2 Input and Output operation functions
  * @{
  */

/* I/O operation functions  *****************************************************/
HAL_StatusTypeDef HAL_OPA_Start(OPA_HandleTypeDef *hopa);
HAL_StatusTypeDef HAL_OPA_Stop(OPA_HandleTypeDef *hopa);

/**
  * @}
  */

/** @defgroup OPA_Exported_Functions_Group3 Peripheral Control functions
  * @{
  */

/* Peripheral Control functions  ************************************************/
#if (USE_HAL_OPA_REGISTER_CALLBACKS == 1)
/* OPA callback registering/unregistering */
HAL_StatusTypeDef HAL_OPA_RegisterCallback(OPA_HandleTypeDef *hopa, HAL_OPA_CallbackIDTypeDef CallbackId,
                                             pOPA_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_OPA_UnRegisterCallback(OPA_HandleTypeDef *hopa, HAL_OPA_CallbackIDTypeDef CallbackId);
#endif /* USE_HAL_OPA_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @defgroup OPA_Exported_Functions_Group4 Peripheral State functions
  * @{
  */

/* Peripheral State functions  **************************************************/
HAL_OPA_StateTypeDef HAL_OPA_GetState(OPA_HandleTypeDef *hopa);

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

#endif /* PY32F032_HAL_OPA_H */

