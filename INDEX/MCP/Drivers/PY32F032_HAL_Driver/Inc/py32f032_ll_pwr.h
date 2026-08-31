/**
  ******************************************************************************
  * @file    py32f032_ll_pwr.h
  * @author  MCU Application Team
  * @brief   Header file of PWR LL module.
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
#ifndef PY32F032_LL_PWR_H
#define PY32F032_LL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f0xx.h"

/** @addtogroup PY32F032_LL_Driver
  * @{
  */

#if defined(PWR)

/** @defgroup PWR_LL PWR
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Constants PWR Exported Constants
  * @{
  */
/** @defgroup PWR_LL_EC_WAKEUP_HSION_MODE WAKEUP HSI ON MODE
  * @{
  */
#define LL_PWR_STOPWAKEUP_HSION_AFTER_MR       PWR_CR1_HSION_CTRL  /* Wake up from the STOP mode, after the MR becomes stable, enable HSI */
#define LL_PWR_STOPWAKEUP_HSION_IMMEDIATE      0x00000000U         /* Wake up from the STOP mode, Enable HSI immediately */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_FLASH_MODE WAKEUP FLASH ON MODE
  * @{
  */
#define LL_PWR_STOPWAKEUP_FLASHON_AFTER_HSI     0x00000000U          /* Wake up from the STOP mode, after the HSI stable, enable Flash */
#define LL_PWR_STOPWAKEUP_FLASHON_IMMEDIATE     PWR_CR1_FLSSLP_CTRL  /* Wake up from the STOP mode, Enable Flash immediately */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_FLASH_DELAY WAKEUP FLASH DELAY
  * @{
  */
#define LL_PWR_STOPWAKEUP_FLASH_DELAY_3US      (0x00000000U)                                     /* Wake up from the STOP mode, Delay 3us enable flash*/
#define LL_PWR_STOPWAKEUP_FLASH_DELAY_5US      (                        PWR_CR1_FLS_SLPTIME_0)   /* Wake up from the STOP mode, Delay 5us enable flash*/
#define LL_PWR_STOPWAKEUP_FLASH_DELAY_1US      (PWR_CR1_FLS_SLPTIME_1                        )   /* Wake up from the STOP mode, Delay 1us enable flash*/
#define LL_PWR_STOPWAKEUP_FLASH_DELAY_0US      (PWR_CR1_FLS_SLPTIME_1 | PWR_CR1_FLS_SLPTIME_0)   /* Wake up from the STOP mode, Delay 0us enable flash*/
/**
  * @}
  */

/** @defgroup PWR_LL_EC_VOLTAGE_REGULATOR_MODE Voltage Regulator Mode
  * @{
  */  
#define LL_PWR_VOLTAGE_REGULATOR_MODE_MR        0x00000000U            /* MR mode */
#define LL_PWR_VOLTAGE_REGULATOR_MODE_LPR       PWR_CR1_VR_MODE_0      /* LPR mode */
#define LL_PWR_VOLTAGE_REGULATOR_MODE_DLPR      PWR_CR1_VR_MODE_1      /* DLPR mode */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_DLPR_Voltage_Mode DLPR Voltage Mode
  * @{
  */
#define LL_PWR_DLPR_VOLTAGE_HIGH         0x00000000                                   /*!< DLPR voltage mode selects high mode */
#define LL_PWR_DLPR_VOLTAGE_MEDIUM       PWR_CR1_DLPR_VSEL_0                          /*!< DLPR voltage mode selects medium mode */
#define LL_PWR_DLPR_VOLTAGE_MEDIUM_LOW   PWR_CR1_DLPR_VSEL_1                          /*!< DLPR voltage mode selects medium low mode */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_LPR_Voltage_Mode LPR Voltage Mode
  * @{
  */
#define LL_PWR_LPR_VOLTAGE_HIGH         0x00000000                                  /*!< LPR voltage mode selects high mode */
#define LL_PWR_LPR_VOLTAGE_MEDIUM       PWR_CR1_LPR_VSEL_0                          /*!< LPR voltage mode selects medium mode */
#define LL_PWR_LPR_VOLTAGE_MEDIUM_LOW   PWR_CR1_LPR_VSEL_1                          /*!< LPR voltage mode selects low mode */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_MR_Voltage_Mode MR Voltage Mode
  * @{
  */
#define LL_PWR_MR_VOLTAGE_MEDIUM_LOW    0x00000000                                /*!< MR voltage mode selects medium low mode */
#define LL_PWR_MR_VOLTAGE_LOW           PWR_CR1_MR_VSEL_0                         /*!< MR voltage mode selects low mode */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_MODE_PWR MODE PWR
  * @{
  */
#define LL_PWR_MODE_RUN                 0x00000000
#define LL_PWR_MODE_LOWPOWERRUN         PWR_CR1_LPMS
/**
  * @}
  */


/** @defgroup PWR_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_PWR_ReadReg function
  * @{
  */
 
#define LL_PWR_SR_PVDO                    PWR_SR_PVDO
#define LL_PWR_SR_MR_RDY                  PWR_SR_MR_RDY
#define LL_PWR_SR_LPRUN2RUN_RDY           PWR_SR_LPRUN2RUN_RDY
/**
  * @}
  */

/** @defgroup PWR_LL_EC_PVDLEVEL Power Voltage Detector Level
  * @{
  */
#define LL_PWR_PVDLEVEL_0      (0x00000000)                                       /*!< Voltage threshold detected by PVD 1.8 V */
#define LL_PWR_PVDLEVEL_1      (                                  PWR_CR2_PVDT_0) /*!< Voltage threshold detected by PVD 2.0 V */
#define LL_PWR_PVDLEVEL_2      (                 PWR_CR2_PVDT_1                 ) /*!< Voltage threshold detected by PVD 2.2 V */
#define LL_PWR_PVDLEVEL_3      (                 PWR_CR2_PVDT_1 | PWR_CR2_PVDT_0) /*!< Voltage threshold detected by PVD 2.4 V */
#define LL_PWR_PVDLEVEL_4      (PWR_CR2_PVDT_2                                  ) /*!< Voltage threshold detected by PVD 2.6 V */
#define LL_PWR_PVDLEVEL_5      (PWR_CR2_PVDT_2                  | PWR_CR2_PVDT_0) /*!< Voltage threshold detected by PVD 2.8 V */
#define LL_PWR_PVDLEVEL_6      (PWR_CR2_PVDT_2 | PWR_CR2_PVDT_1                 ) /*!< Voltage threshold detected by PVD 3.0 V */
#define LL_PWR_PVDLEVEL_7      (PWR_CR2_PVDT_2 | PWR_CR2_PVDT_1 | PWR_CR2_PVDT_0) /*!< Voltage threshold detected by PVD 3.2 V */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_PVDFILTER PVDFILTER
  * @{
  */
#define LL_PWR_PVD_FILTER_1CLOCK          (0x00000000u)                                                   /*!< PVD filter 1    clock */
#define LL_PWR_PVD_FILTER_2CLOCK          (                                          PWR_CR2_FLT_TIME_0)  /*!< PVD filter 2    clock */
#define LL_PWR_PVD_FILTER_4CLOCK          (                     PWR_CR2_FLT_TIME_1                     )  /*!< PVD filter 2    clock */
#define LL_PWR_PVD_FILTER_16CLOCK         (                     PWR_CR2_FLT_TIME_1 | PWR_CR2_FLT_TIME_0)  /*!< PVD filter 4    clock */
#define LL_PWR_PVD_FILTER_64CLOCK         (PWR_CR2_FLT_TIME_2                                          )  /*!< PVD filter 16   clock */
#define LL_PWR_PVD_FILTER_128CLOCK        (PWR_CR2_FLT_TIME_2                      | PWR_CR2_FLT_TIME_0)  /*!< PVD filter 128  clock */
#define LL_PWR_PVD_FILTER_1024CLOCK       (PWR_CR2_FLT_TIME_2 | PWR_CR2_FLT_TIME_1                     )  /*!< PVD filter 1024 clock */
/**
  * @}
  */


/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Macros PWR Exported Macros
  * @{
  */

/** @defgroup PWR_LL_EM_WRITE_READ Common write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in PWR register
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_PWR_WriteReg(__REG__, __VALUE__) WRITE_REG(PWR->__REG__, (__VALUE__))

/**
  * @brief  Read a value in PWR register
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_PWR_ReadReg(__REG__) READ_REG(PWR->__REG__)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Functions PWR Exported Functions
  * @{
  */

/** @defgroup PWR_LL_EF_Configuration Configuration
  * @{
  */
/**
  * @brief  Set the HSI turn on mode after wake up 
  * @rmtoll CR1           HSION_CTRL          LL_PWR_SetStopWakeUpHSIOnMode
  * @param  HsiOnMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_STOPWAKEUP_HSION_AFTER_MR
  *         @arg @ref LL_PWR_STOPWAKEUP_HSION_IMMEDIATE
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetStopWakeUpHSIOnMode(uint32_t HsiOnMode)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_HSION_CTRL, HsiOnMode);
}

/**
  * @brief  Get the HSI turn on mode after wake up
  * @rmtoll CR1          HSION_CTRL          LL_PWR_GetStopWakeUpHSIOnMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_STOPWAKEUP_HSION_AFTER_MR
  *         @arg @ref LL_PWR_STOPWAKEUP_HSION_IMMEDIATE
  */
__STATIC_INLINE uint32_t LL_PWR_GetStopWakeUpHSIOnMode(void)
{
  return (uint32_t)(READ_BIT(PWR->CR1, PWR_CR1_HSION_CTRL));
}

/**
  * @brief  Set the FLASH turn on mode after wake up 
  * @rmtoll CR1           FLSSLP_CTRL          LL_PWR_SetStopWakeUpFlashOnMode
  * @param  FlashOnMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_STOPWAKEUP_FLASHON_AFTER_HSI
  *         @arg @ref LL_PWR_STOPWAKEUP_FLASHON_IMMEDIATE
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetStopWakeUpFlashOnMode(uint32_t FlashOnMode)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_FLSSLP_CTRL, FlashOnMode);
}

/**
  * @brief  Get the FLASH turn on mode after wake up
  * @rmtoll CR1          FLSSLP_CTRL          LL_PWR_GetStopWakeUpFlashOnMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_STOPWAKEUP_FLASHON_AFTER_HSI
  *         @arg @ref LL_PWR_STOPWAKEUP_FLASHON_IMMEDIATE
  */
__STATIC_INLINE uint32_t LL_PWR_GetStopWakeUpFlashOnMode(void)
{
  return (uint32_t)(READ_BIT(PWR->CR1, PWR_CR1_FLSSLP_CTRL));
}

/**
  * @brief  Set DLPR Voltage
  * @rmtoll CR1          PWR_CR1_DLPR_VSEL          LL_PWR_SetDlprVoltageMode
  * @param  Voltage This parameter can be one of the following values:
  *         @arg @ref LL_PWR_DLPR_VOLTAGE_MEDIUM_LOW : Medium low voltage
  *         @arg @ref LL_PWR_DLPR_VOLTAGE_MEDIUM :     Medium voltage
  *         @arg @ref LL_PWR_DLPR_VOLTAGE_HIGH :       High voltage
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetDlprVoltageMode(uint32_t Voltage)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_DLPR_VSEL, Voltage);
}

/**
  * @brief  Get DLPR Voltage
  * @rmtoll CR1          PWR_CR1_DLPR_VSEL          LL_PWR_GetDlprVoltageMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_DLPR_VOLTAGE_MEDIUM_LOW : Medium low voltage
  *         @arg @ref LL_PWR_DLPR_VOLTAGE_MEDIUM :     Medium voltage
  *         @arg @ref LL_PWR_DLPR_VOLTAGE_HIGH :       High voltage
  */
__STATIC_INLINE uint32_t LL_PWR_GetDlprVoltageMode(void)
{
  return (uint32_t)(READ_BIT(PWR->CR1, PWR_CR1_DLPR_VSEL));
}

/**
  * @brief  Set LPR Voltage
  * @rmtoll CR1          PWR_CR1_LPR_VSEL          LL_PWR_SetLprVoltageMode
  * @param  Voltage This parameter can be one of the following values:
  *         @arg @ref LL_PWR_LPR_VOLTAGE_MEDIUM_LOW : Medium Low voltage
  *         @arg @ref LL_PWR_LPR_VOLTAGE_MEDIUM :     Medium voltage
  *         @arg @ref LL_PWR_LPR_VOLTAGE_HIGH :       High voltage
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetLprVoltageMode(uint32_t Voltage)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_LPR_VSEL, Voltage);
}

/**
  * @brief  Get LPR Voltage
  * @rmtoll CR1          PWR_CR1_LPR_VSEL          LL_PWR_GetLprVoltageMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_LPR_VOLTAGE_MEDIUM_LOW :  Medium Low voltage
  *         @arg @ref LL_PWR_LPR_VOLTAGE_MEDIUM :     Medium voltage
  *         @arg @ref LL_PWR_LPR_VOLTAGE_HIGH :       High voltage
  */
__STATIC_INLINE uint32_t LL_PWR_GetLprVoltageMode(void)
{
  return (uint32_t)(READ_BIT(PWR->CR1, PWR_CR1_LPR_VSEL));
}

/**
  * @brief  Set MR Voltage
  * @rmtoll CR1          PWR_CR1_MR_VSEL          LL_PWR_SetMrVoltageMode
  * @param  Voltage This parameter can be one of the following values:
  *         @arg @ref LL_PWR_MR_VOLTAGE_MEDIUM_LOW : Meidum Low voltage
  *         @arg @ref LL_PWR_MR_VOLTAGE_LOW : Low voltage
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetMrVoltageMode(uint32_t Voltage)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_MR_VSEL, Voltage);
}

/**
  * @brief  Get MR Voltage
  * @rmtoll CR1          PWR_CR1_MR_VSEL          LL_PWR_GetMrVoltageMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_MR_VOLTAGE_MEDIUM_LOW : Meidum Low voltage
  *         @arg @ref LL_PWR_MR_VOLTAGE_LOW : Low voltage
  */
__STATIC_INLINE uint32_t LL_PWR_GetMrVoltageMode(void)
{
  return (uint32_t)(READ_BIT(PWR->CR1, PWR_CR1_MR_VSEL));
}

/**
  * @brief  Set the flash delay time after wake up 
  * @rmtoll CR1          FLS_SLPTIME          LL_PWR_SetStopWakeUpFlashDelay
  * @param  FlashDelay This parameter can be one of the following values:
  *         @arg @ref LL_PWR_STOPWAKEUP_FLASH_DELAY_3US
  *         @arg @ref LL_PWR_STOPWAKEUP_FLASH_DELAY_5US
  *         @arg @ref LL_PWR_STOPWAKEUP_FLASH_DELAY_1US
  *         @arg @ref LL_PWR_STOPWAKEUP_FLASH_DELAY_0US
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetStopWakeUpFlashDelay(uint32_t FlashDelay)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_FLS_SLPTIME, FlashDelay);
}

/**
  * @brief  Get the flash delay time after wake up 
  * @rmtoll CR          FLS_SLPTIME          LL_PWR_GetStopWakeUpFlashDelay
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_STOPWAKEUP_FLASH_DELAY_3US
  *         @arg @ref LL_PWR_STOPWAKEUP_FLASH_DELAY_5US
  *         @arg @ref LL_PWR_STOPWAKEUP_FLASH_DELAY_1US
  *         @arg @ref LL_PWR_STOPWAKEUP_FLASH_DELAY_0US
  */
__STATIC_INLINE uint32_t LL_PWR_GetStopWakeUpFlashDelay(void)
{
  return (uint32_t)(READ_BIT(PWR->CR1, PWR_CR1_FLS_SLPTIME));
}

/**
  * @brief  Set Voltage Regulator mode 
  * @rmtoll CR1          VR_MODE          LL_PWR_SetVoltageRegulatorMode
  * @param  VRMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_VOLTAGE_REGULATOR_MODE_MR :   Voltage Regulator selects MR mode
  *         @arg @ref LL_PWR_VOLTAGE_REGULATOR_MODE_LPR :  Voltage Regulator selects LPR mode
  *         @arg @ref LL_PWR_VOLTAGE_REGULATOR_MODE_DLPR : Voltage Regulator selects DLPR mode
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetVoltageRegulatorMode(uint32_t VRMode)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_VR_MODE, VRMode);
}

/**
  * @brief  Get the flash delay time after wake up 
  * @rmtoll CR1          VR_MODE          LL_PWR_GetVoltageRegulatorMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_VOLTAGE_REGULATOR_MODE_MR :   Voltage Regulator selects MR mode
  *         @arg @ref LL_PWR_VOLTAGE_REGULATOR_MODE_LPR :  Voltage Regulator selects LPR mode
  *         @arg @ref LL_PWR_VOLTAGE_REGULATOR_MODE_DLPR : Voltage Regulator selects DLPR mode
  */
__STATIC_INLINE uint32_t LL_PWR_GetVoltageRegulatorMode(void)
{
  return (uint32_t)(READ_BIT(PWR->CR1, PWR_CR1_VR_MODE));
}

/**
  * @brief  Enable access to the backup domain
  * @rmtoll CR1    DBP       LL_PWR_EnableBkUpAccess
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableBkUpAccess(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_DBP);
}

/**
  * @brief  Disable access to the backup domain
  * @rmtoll CR1    DBP       LL_PWR_DisableBkUpAccess
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableBkUpAccess(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_DBP);
}

/**
  * @brief  Check if the backup domain is enabled
  * @rmtoll CR1    DBP       LL_PWR_IsEnabledBkUpAccess
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBkUpAccess(void)
{
  return (READ_BIT(PWR->CR1, PWR_CR1_DBP) == (PWR_CR1_DBP));
}

/**
  * @brief  Set Low-Power mode
  * @rmtoll CR1          LPMS          LL_PWR_SetPowerMode
  * @param  LowPowerMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_MODE_RUN
  *         @arg @ref LL_PWR_MODE_LOWPOWERRUN
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPowerMode(uint32_t LowPowerMode)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, LowPowerMode);
}

/**
  * @brief  Get Low-Power mode
  * @rmtoll CR1          LPMS          LL_PWR_GetPowerMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_MODE_RUN
  *         @arg @ref LL_PWR_MODE_LOWPOWERRUN
  */
__STATIC_INLINE uint32_t LL_PWR_GetPowerMode(void)
{
  return (uint32_t)(READ_BIT(PWR->CR1, PWR_CR1_LPMS));
}

/**
  * @}
  */

/** @defgroup PWR_LL_EF_PVD_Management PVD_Management
  * @{
  */

/**
  * @brief  Configure the voltage threshold detected by the Power Voltage Detector
  * @rmtoll CR2    PVDT       LL_PWR_SetPVDLevel
  * @param  PVDLevel This parameter can be one of the following values:
  *         @arg @ref LL_PWR_PVDLEVEL_0
  *         @arg @ref LL_PWR_PVDLEVEL_1
  *         @arg @ref LL_PWR_PVDLEVEL_2
  *         @arg @ref LL_PWR_PVDLEVEL_3
  *         @arg @ref LL_PWR_PVDLEVEL_4
  *         @arg @ref LL_PWR_PVDLEVEL_5
  *         @arg @ref LL_PWR_PVDLEVEL_6
  *         @arg @ref LL_PWR_PVDLEVEL_7
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPVDLevel(uint32_t PVDLevel)
{
  MODIFY_REG(PWR->CR2, PWR_CR2_PVDT, PVDLevel);
}

/**
  * @brief  Get the voltage threshold detection
  * @rmtoll CR2    PVDT       LL_PWR_GetPVDLevel
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_PVDLEVEL_0
  *         @arg @ref LL_PWR_PVDLEVEL_1
  *         @arg @ref LL_PWR_PVDLEVEL_2
  *         @arg @ref LL_PWR_PVDLEVEL_3
  *         @arg @ref LL_PWR_PVDLEVEL_4
  *         @arg @ref LL_PWR_PVDLEVEL_5
  *         @arg @ref LL_PWR_PVDLEVEL_6
  *         @arg @ref LL_PWR_PVDLEVEL_7
  */
__STATIC_INLINE uint32_t LL_PWR_GetPVDLevel(void)
{
  return (uint32_t)(READ_BIT(PWR->CR2, PWR_CR2_PVDT));
}

/**
  * @brief  Enable Power Voltage Detector
  * @rmtoll CR2    PVDE       LL_PWR_EnablePVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnablePVD(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_PVDE);
}

/**
  * @brief  Disable Power Voltage Detector
  * @rmtoll CR2    PVDE       LL_PWR_DisablePVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisablePVD(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_PVDE);
}

/**
  * @brief  Check if Power Voltage Detector is enabled
  * @rmtoll CR2    PVDE       LL_PWR_IsEnabledPVD
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPVD(void)
{
  return (READ_BIT(PWR->CR2, PWR_CR2_PVDE) == (PWR_CR2_PVDE));
}

/**
  * @brief  Enable PVD Filter
  * @rmtoll CR2          FLTEN          LL_PWR_EnablePVDFilter
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnablePVDFilter(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_FLTEN);
}

/**
  * @brief  Disable PVD Filter
  * @rmtoll CR2          FLTEN          LL_PWR_DisablePVDFilter
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisablePVDFilter(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_FLTEN);
}

/**
  * @brief  Check if PVD Filter is enabled
  * @rmtoll CSR          FLTEN          LL_PWR_IsEnabledPVDFilter
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPVDFilter(void)
{
  return (READ_BIT(PWR->CR2, PWR_CR2_FLTEN) == (PWR_CR2_FLTEN));
}

/**
  * @brief  Enable PVD digital output synchronous filter
  * @rmtoll CR2          PVD_OUT_SEL          LL_PWR_EnablePVDOutputSynchronousFilter
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnablePVDOutputSynchronousFilter(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_PVD_OUT_SEL);
}

/**
  * @brief  Disable PVD digital output synchronous filter
  * @rmtoll CR2          PVD_OUT_SEL          LL_PWR_DisablePVDOutputSynchronousFilter
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisablePVDOutputSynchronousFilter(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_PVD_OUT_SEL);
}

/**
  * @brief  Check if PVD digital output synchronous filter is enabled
  * @rmtoll CR2          PVD_OUT_SEL          LL_PWR_IsEnabledPVDOutputSynchronousFilter
  * @retval None
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPVDOutputSynchronousFilter(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_PVD_OUT_SEL) == (PWR_CR2_PVD_OUT_SEL)) ? 1UL : 0UL);
}

/**
  * @brief  PVD detection power supply selection
  * @rmtoll CR2          FLT_TIME          LL_PWR_SetPVDFilter
  * @param  PVDFilter This parameter can be one of the following values:
  *         @arg @ref LL_PWR_PVD_FILTER_1CLOCK
  *         @arg @ref LL_PWR_PVD_FILTER_2CLOCK
  *         @arg @ref LL_PWR_PVD_FILTER_4CLOCK
  *         @arg @ref LL_PWR_PVD_FILTER_16CLOCK
  *         @arg @ref LL_PWR_PVD_FILTER_64CLOCK
  *         @arg @ref LL_PWR_PVD_FILTER_128CLOCK
  *         @arg @ref LL_PWR_PVD_FILTER_1024CLOCK
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPVDFilter(uint32_t PVDFilter)
{
  MODIFY_REG(PWR->CR2, PWR_CR2_FLT_TIME, PVDFilter);
}

/**
  * @brief  Get PVD detection power supply 
  * @rmtoll CSR          FLT_CTRL          LL_PWR_GetPVDFilter
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_PVD_FILTER_1CLOCK
  *         @arg @ref LL_PWR_PVD_FILTER_2CLOCK
  *         @arg @ref LL_PWR_PVD_FILTER_4CLOCK
  *         @arg @ref LL_PWR_PVD_FILTER_16CLOCK
  *         @arg @ref LL_PWR_PVD_FILTER_64CLOCK
  *         @arg @ref LL_PWR_PVD_FILTER_128CLOCK
  *         @arg @ref LL_PWR_PVD_FILTER_1024CLOCK
  */
__STATIC_INLINE uint32_t LL_PWR_GetPVDFilter(void)
{
  return (uint32_t)(READ_BIT(PWR->CR2, PWR_CR2_FLT_TIME));
}
/**
  * @}
  */

/** @defgroup PWR_LL_EF_FLAG_Management FLAG_Management
  * @{
  */


/**
  * @}
  */

/** @defgroup PWR_LL_EF_FLAG_Management FLAG_Management
  * @{
  */


/**
  * @brief  Indicate whether or not the main regulator is ready
  * @rmtoll SR          MR_RDY        LL_PWR_IsActiveFlag_MR_RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_MR_RDY(void)
{
  uint32_t temp;
  temp = READ_BIT(PWR->SR, PWR_SR_MR_RDY);

  return ((temp == (PWR_SR_MR_RDY))?1U:0U);
}

/**
  * @brief  Indicate whether or not the core is in run mode
  * @rmtoll SR          PWR_SR_LPRUN2RUN_RDY        LL_PWR_IsActiveFlag_LPRUN2RUN_RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_LPRUN2RUN_RDY(void)
{
  uint32_t temp;
  temp = READ_BIT(PWR->SR, PWR_SR_LPRUN2RUN_RDY);

  return ((temp == (PWR_SR_LPRUN2RUN_RDY))?1U:0U);
}

/**
  * @brief  Indicate whether VDD voltage is below or above the selected PVD threshold
  * @rmtoll SR          PVDO          LL_PWR_IsActiveFlag_PVDO
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_PVDO(void)
{
 uint32_t temp;
 temp = READ_BIT(PWR->SR, PWR_SR_PVDO);

 return ((temp == (PWR_SR_PVDO))?1U:0U);

}

/**
  * @}
  */

/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup PWR_LL_EF_Init De-initialization function
  * @{
  */
ErrorStatus LL_PWR_DeInit(void);
/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/**
  * @}
  */

#endif /* defined(PWR) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* PY32F032_LL_PWR_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
