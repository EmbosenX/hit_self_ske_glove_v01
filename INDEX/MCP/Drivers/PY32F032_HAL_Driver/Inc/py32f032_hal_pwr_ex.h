/**
  ******************************************************************************
  * @file   py32f032_hal_pwr_ex.h
  * @author  MCU Application Team
  * @brief   Header file of PWR HAL Extension module.
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
#ifndef __PY32F032_HAL_PWR_EX_H
#define __PY32F032_HAL_PWR_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f032_hal_def.h"

/** @addtogroup PY32F032_HAL_Driver
  * @{
  */

/** @addtogroup PWREx
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 

/* Exported constants --------------------------------------------------------*/
/** @defgroup PWREx_Exported_Constants PWREx Exported Constants
  * @{
  */
/** @defgroup PWREx_VOLTAGE_REGULATOR_MODE PWREx Voltage Regulator Mode
  * @{
  */  
#define PWR_VOLTAGE_REGULATOR_MODE_MR        0x00000000U            /* MR mode */
#define PWR_VOLTAGE_REGULATOR_MODE_LPR       PWR_CR1_VR_MODE_0      /* LPR mode */
#define PWR_VOLTAGE_REGULATOR_MODE_DLPR      PWR_CR1_VR_MODE_1      /* DLPR mode */
/**
  * @}
  */

/** @defgroup PWREx_MR_Voltage_Mode PWREx MR Voltage Mode
  * @{
  */
#define PWR_MR_VOLTAGE_LOW                PWR_CR1_MR_VSEL_0                         /*!< MR voltage mode selects low mode */
#define PWR_MR_VOLTAGE_MEDIUM_LOW         0x00000000U                               /*!< MR voltage mode selects medium low mode */
/* #define PWR_MR_VOLTAGE_MEDIUM             PWR_CR1_MR_VSEL_1    */                /*!< MR voltage mode selects medium mode */
/* #define PWR_MR_VOLTAGE_HIGH               PWR_CR1_MR_VSEL      */                /*!< MR voltage mode selects high mode */
/**
  * @}
  */
  
/** @defgroup PWREx_LPR_Voltage_Mode PWREx LPR Voltage Mode
  * @{
  */
#define PWR_LPR_VOLTAGE_HIGH          0x00000000                          /*!< LPR voltage mode selects high mode */
#define PWR_LPR_VOLTAGE_MEDIUM        PWR_CR1_LPR_VSEL_0                  /*!< LPR voltage mode selects medium  mode */
#define PWR_LPR_VOLTAGE_MEDIUM_LOW    PWR_CR1_LPR_VSEL_1                  /*!< LPR voltage mode selects medium low mode */
/* #define PWR_LPR_VOLTAGE_LOW           PWR_CR1_LPR_VSEL       */        /*!< LPR voltage mode selects low mode */
/**
  * @}
  */
  
/** @defgroup PWREx_DLPR_Voltage_Mode PWREx DLPR Voltage Mode
  * @{
  */
#define PWR_DLPR_VOLTAGE_HIGH         0x00000000                                   /*!< DLPR voltage mode selects high mode */
#define PWR_DLPR_VOLTAGE_MEDIUM       PWR_CR1_DLPR_VSEL_0                          /*!< DLPR voltage mode selects medium mode */
#define PWR_DLPR_VOLTAGE_MEDIUM_LOW   PWR_CR1_DLPR_VSEL_1                          /*!< DLPR voltage mode selects medium low mode */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup PWREx_Exported_Macros PWREx Exported Macros
  *  @{
  */

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup PWREx_Private_Constants PWREx Private Constants
  * @{
  */

/** @defgroup PWR_FLASH_WAKEUP_DELAY Flash wakeup delay time
  * @{
  */  
#define PWR_WAKEUP_FLASH_DELAY_3US  0x00000000U
#define PWR_WAKEUP_FLASH_DELAY_5US  PWR_CR1_FLS_SLPTIME_0
#define PWR_WAKEUP_FLASH_DELAY_1US  PWR_CR1_FLS_SLPTIME_1
#define PWR_WAKEUP_FLASH_DELAY_0US  (PWR_CR1_FLS_SLPTIME_1 | PWR_CR1_FLS_SLPTIME_0)

 /**
  * @}
  */

/** @defgroup PWR_MRREADY_WAKEUP_DELAY standby wakeup MR ready delay time
  * @{
  */  
#define PWR_WAKEUP_MRREADY_DELAY_0US   0x00000000U
#define PWR_WAKEUP_MRREADY_DELAY_5US   PWR_CR1_STDBY_MRRDY_WAIT_0
#define PWR_WAKEUP_MRREADY_DELAY_10US  PWR_CR1_STDBY_MRRDY_WAIT_1
#define PWR_WAKEUP_MRREADY_DELAY_20US  (PWR_CR1_STDBY_MRRDY_WAIT_1 | PWR_CR1_STDBY_MRRDY_WAIT_0)

 /**
  * @}
  */


/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup PWREx_Private_Macros PWREx Private Macros
  * @{
  */


/**
  * @}
  */

/* Exported Functions --------------------------------------------------------*/
/** @defgroup PWREx_Exported_Functions PWREx Exported Functions
  *  @{
  */

/** @addtogroup PWREx_Exported_Functions_Group1
  * @{
  */
void HAL_PWREx_SetWakeupFlashDelay(uint32_t DelayTime);
uint32_t HAL_PWREx_GetWakeupFlashDelay(void);
void HAL_PWREx_SetWakeupMrReadyDelay(uint32_t DelayTime);
uint32_t HAL_PWREx_GetWakeupMrReadyDelay(void);
void HAL_PWREx_DisableHSIWakeupWait(void);
void HAL_PWREx_EnableHSIWakeupWait(void);
void HAL_PWREx_DisableFlashWakeupWait(void);
void HAL_PWREx_EnableFlashWakeupWait(void);
void HAL_PWREx_EnablePowerOnLoad(void);
void HAL_PWREx_DisablePowerOnLoad(void);
void HAL_PWREx_SetMrVoltageMode(uint32_t Voltage);
uint32_t HAL_PWREx_GetMrVoltageMode(void);
void HAL_PWREx_SetLprVoltageMode(uint32_t Voltage);
uint32_t HAL_PWREx_GetLprVoltageMode(void);
void HAL_PWREx_SetDlprVoltageMode(uint32_t Voltage);
uint32_t HAL_PWREx_GetDlprVoltageMode(void);
void HAL_PWREx_SetVoltageRegulatorMode(uint32_t VRMode);
uint32_t HAL_PWREx_GetVoltageRegulatorMode(void);
void HAL_PWREx_EnableLowPowerRunMode(void);
HAL_StatusTypeDef HAL_PWREx_DisableLowPowerRunMode(void);
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


#endif /* __PY32F032_HAL_PWR_EX_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
