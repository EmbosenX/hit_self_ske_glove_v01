/**
  ******************************************************************************
  * @file   py32f032_hal_pwr_ex.c
  * @author  MCU Application Team
  * @brief   Extended PWR HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of PWR extension peripheral:           
  *           + Peripheral Extended features functions
  *         
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

/* Includes ------------------------------------------------------------------*/
#include "py32f0xx_hal.h"

/** @addtogroup PY32F032_HAL_Driver
  * @{
  */

/** @defgroup PWREx PWREx
  * @brief PWR HAL module driver
  * @{
  */

#ifdef HAL_PWR_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup PWREx_TimeOut_Value PWR Extended Flag Setting Time Out Value
  * @{
  */
#define PWR_FLAG_SETTING_DELAY_US                      50UL   /*!< Time out value for MR_RDY and LPRUN_RUN_SWF flags setting */
/**
  * @}
  */
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @defgroup PWREx_Exported_Functions PWREx Exported Functions
  *  @{
  */

/** @defgroup PWREx_Exported_Functions_Group1 Peripheral Extended features functions 
  *  @brief Peripheral Extended features functions 
  *

  * @{
  */

/**
  * @brief Config wakeup from stop mode, enable flash delay time.
  * @param  DelayTime: Specifies the delay time before FLASH control
  *          This parameter can be one of the following values:
  *            - @arg PWR_WAKEUP_FLASH_DELAY_3US: Wake up from the STOP mode, Delay 3us enable flash
  *            - @arg PWR_WAKEUP_FLASH_DELAY_5US: Wake up from the STOP mode, Delay 5us enable flash
  *            - @arg PWR_WAKEUP_FLASH_DELAY_1US: Wake up from the STOP mode, Delay 1us enable flash
  *            - @arg PWR_WAKEUP_FLASH_DELAY_0US: Wake up from the STOP mode, Enable flash immediately
  * @retval None
  */
void HAL_PWREx_SetWakeupFlashDelay(uint32_t DelayTime)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_FLS_SLPTIME, DelayTime);
}

/**
  * @brief Get wakeup from stop mode, enable flash delay time.
  * @retval Config Flash wakeup delay time.
  *            - @arg PWR_WAKEUP_FLASH_DELAY_3US: Wake up from the STOP mode, Delay 3us enable flash
  *            - @arg PWR_WAKEUP_FLASH_DELAY_5US: Wake up from the STOP mode, Delay 5us enable flash
  *            - @arg PWR_WAKEUP_FLASH_DELAY_1US: Wake up from the STOP mode, Delay 1us enable flash
  *            - @arg PWR_WAKEUP_FLASH_DELAY_0US: Wake up from the STOP mode, Enable flash immediately
  */
uint32_t HAL_PWREx_GetWakeupFlashDelay(void)
{
  return (PWR->CR1 & PWR_CR1_FLS_SLPTIME);
}

/**
  * @brief When wakeup from stop mode,HSI and Main Regulator start at the same time.
  * @retval None
  */
void HAL_PWREx_DisableHSIWakeupWait(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_HSION_CTRL);
}

/**
  * @brief When wakeup from stop mode,HSI enable After Main Regulator stable.
  * @retval None
  */
void HAL_PWREx_EnableHSIWakeupWait(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_HSION_CTRL);
}

/**
  * @brief When wakeup from stop mode to low power run mode, MSI and Flash start at the same time.
  * @retval None
  */
void HAL_PWREx_DisableFlashWakeupWait(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_FLSSLP_CTRL);
}

/**
  * @brief When wakeup from stop mode to low power run mode, Flash starts counting only after MSI stabilizes.
  * @retval None
  */
void HAL_PWREx_EnableFlashWakeupWait(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_FLSSLP_CTRL);
}

/**
  * @brief Config Voltage of MR.
  * @param  Voltage: Specifies the Voltage of MR
  *          This parameter can be one of the following values:
  *            - @arg PWR_MR_VOLTAGE_MEDIUM_LOW: Medium low voltage
  *            - @arg PWR_MR_VOLTAGE_LOW:        Low voltage
  * @retval None
  */
void HAL_PWREx_SetMrVoltageMode(uint32_t Voltage)
{
  __IO uint32_t wait_loop_index = 0;

  MODIFY_REG(PWR->CR1, PWR_CR1_MR_VSEL, Voltage);

  wait_loop_index = 10 * (SystemCoreClock / 1000000U);

  while(wait_loop_index != 0U)
  {
    wait_loop_index--;
  }
}

/**
  * @brief Return Voltage of MR.
  * @retval  The configured voltage for the MR.
  *          The returned value can be one of the following:
  *            - @arg PWR_MR_VOLTAGE_MEDIUM_LOW: Medium low voltage
  *            - @arg PWR_MR_VOLTAGE_LOW:        Low voltage
  */
uint32_t HAL_PWREx_GetMrVoltageMode(void)
{
  return(PWR->CR1 & PWR_CR1_MR_VSEL);
}

/**
  * @brief Config Voltage of LPR.
  * @param  Voltage: Specifies the Voltage of LPR
  *          This parameter can be one of the following values:
  *            - @arg PWR_LPR_VOLTAGE_HIGH:       High voltage
  *            - @arg PWR_LPR_VOLTAGE_MEDIUM:     Medium voltage
  *            - @arg PWR_LPR_VOLTAGE_MEDIUM_LOW: Medium low voltage
  * @retval None
  */
void HAL_PWREx_SetLprVoltageMode(uint32_t Voltage)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_LPR_VSEL, Voltage);
}

/**
  * @brief Return Voltage of LPR.
  * @retval  The configured voltage for the LPR.
  *          The returned value can be one of the following:
  *            - @arg PWR_LPR_VOLTAGE_HIGH:       High voltage
  *            - @arg PWR_LPR_VOLTAGE_MEDIUM:     Medium voltage
  *            - @arg PWR_LPR_VOLTAGE_MEDIUM_LOW: Medium low voltage
  */
uint32_t HAL_PWREx_GetLprVoltageMode(void)
{
  return(PWR->CR1 & PWR_CR1_LPR_VSEL);
}

/**
  * @brief Config Voltage of DLPR.
  * @param  Voltage: Specifies the Voltage of DLPR
  *          This parameter can be one of the following values:
  *            - @arg PWR_DLPR_VOLTAGE_HIGH:       High voltage
  *            - @arg PWR_DLPR_VOLTAGE_MEDIUM:     Medium voltage
  *            - @arg PWR_DLPR_VOLTAGE_MEDIUM_LOW: Medium low voltage
  * @retval None
  */
void HAL_PWREx_SetDlprVoltageMode(uint32_t Voltage)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_DLPR_VSEL, Voltage);
}

/**
  * @brief Return Voltage of DLPR.
  * @retval  The configured voltage for the DLPR.
  *          The returned value can be one of the following:
  *            - @arg PWR_DLPR_VOLTAGE_HIGH:       High voltage
  *            - @arg PWR_DLPR_VOLTAGE_MEDIUM:     Medium voltage
  *            - @arg PWR_DLPR_VOLTAGE_MEDIUM_LOW: Medium low voltage
  */
uint32_t HAL_PWREx_GetDlprVoltageMode(void)
{
  return(PWR->CR1 & PWR_CR1_DLPR_VSEL);
}

/**
  * @brief Config Voltage Regulator mode.
  * @param  VRMode: Specifies the mode of Voltage Regulator
  *          This parameter can be one of the following values:
  *            - @arg PWR_VOLTAGE_REGULATOR_MODE_MR:   Voltage Regulator selects MR mode
  *            - @arg PWR_VOLTAGE_REGULATOR_MODE_LPR:  Voltage Regulator selects LPR mode
  *            - @arg PWR_VOLTAGE_REGULATOR_MODE_DLPR: Voltage Regulator selects DLPR mode
  * @retval None
  */
void HAL_PWREx_SetVoltageRegulatorMode(uint32_t VRMode)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_VR_MODE, VRMode);
}

/**
  * @brief Return Voltage Regulator mode.
  * @retval  The configured mode for the Voltage Regulator.
  *          The returned value can be one of the following:
  *            - @arg PWR_VOLTAGE_REGULATOR_MODE_MR:   Voltage Regulator selects MR mode
  *            - @arg PWR_VOLTAGE_REGULATOR_MODE_LPR:  Voltage Regulator selects LPR mode
  *            - @arg PWR_VOLTAGE_REGULATOR_MODE_DLPR: Voltage Regulator selects DLPR mode
  */
uint32_t HAL_PWREx_GetVoltageRegulatorMode(void)
{
  return(PWR->CR1 & PWR_CR1_VR_MODE);
}

/**
  * @brief Enter Low-power Run mode
  * @note  In Low-power Run mode, all I/O pins keep the same state as in Run mode.
  * @retval None
  */
void HAL_PWREx_EnableLowPowerRunMode(void)
{
  /* LPRUN mode */
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, PWR_MODE_LPRUN);
}

/**
  * @brief Exit Low-power Run mode.
  * @note  Before HAL_PWREx_DisableLowPowerRunMode() completion, the function checks that
  *        MR_RDY and LPRUN_RUN_SWF have been properly set (otherwise, 
  *        HAL_PWREx_DisableLowPowerRunMode returns HAL_TIMEOUT status). 
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_PWREx_DisableLowPowerRunMode(void)
{
  uint32_t wait_loop_index;

  /* Voltage Regulator selects MR mode */
  HAL_PWREx_SetVoltageRegulatorMode(PWR_VOLTAGE_REGULATOR_MODE_MR);
  
  /* RUN mode */
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, PWR_MODE_RUN);

  /* Wait until MR_RDY is set */
  wait_loop_index = (PWR_FLAG_SETTING_DELAY_US * (SystemCoreClock / 1000000U));
  while ((__HAL_PWR_GET_FLAG(PWR_FLAG_MR_RDY) == 0U) && (wait_loop_index != 0U))
  {
    wait_loop_index--;
  }
  
  /* Wait until LPRUN_RUN_SWF is set */
  wait_loop_index = (PWR_FLAG_SETTING_DELAY_US * (SystemCoreClock / 1000000U));
  while ((__HAL_PWR_GET_FLAG(PWR_FLAG_LPRUN_RUN_RDY) == 0U) && (wait_loop_index != 0U))
  {
    wait_loop_index--;
  }
  
  if ((__HAL_PWR_GET_FLAG(PWR_FLAG_MR_RDY) == 0U) || (__HAL_PWR_GET_FLAG(PWR_FLAG_LPRUN_RUN_RDY) == 0U))
  {
    return HAL_TIMEOUT;
  }

  return HAL_OK;
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_PWR_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
