/**
  ******************************************************************************
  * @file    py32f032_hal_lpuart_ex.c
  * @author  MCU Application Team
  * @brief   LPUART HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Universal Asynchronous Receiver Transmitter Peripheral (LPUART).
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State and Errors functions
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
#include "py32f032_hal_lpuart_ex.h"

/** @addtogroup PY32F032_HAL_Driver
  * @{
  */

/** @defgroup LPUARTEx LPUARTEx
  * @brief HAL LPUART module driver
  * @{
  */

#ifdef HAL_LPUART_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @defgroup LPUARTEx_Private_Functions LPUARTEx Private Functions
  * @{
  */
static void LPUARTEx_Wakeup_AddressConfig(LPUART_HandleTypeDef *hlpuart, LPUART_WakeUpTypeDef WakeUpSelection);
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @addtogroup LPUARTEx_Private_Functions
  * @{
  */

/**
  * @brief Initialize the RS485 Driver enable feature according to the specified
  *         parameters in the LPUART_InitTypeDef and creates the associated handle.
  * @param hlpuart            LPUART handle.
  * @param Polarity         Select the driver enable polarity.
  *          This parameter can be one of the following values:
  *          @arg @ref LPUART_DE_POLARITY_HIGH DE signal is active high
  *          @arg @ref LPUART_DE_POLARITY_LOW  DE signal is active low
  * @param AssertionTime    Driver Enable assertion time:
  *       5-bit value defining the time between the activation of the DE (Driver Enable)
  *       signal and the beginning of the start bit. It is expressed in sample time
  *       units (1/8 or 1/16 bit time, depending on the oversampling rate)
  * @param DeassertionTime  Driver Enable deassertion time:
  *       5-bit value defining the time between the end of the last stop bit, in a
  *       transmitted message, and the de-activation of the DE (Driver Enable) signal.
  *       It is expressed in sample time units (1/8 or 1/16 bit time, depending on the
  *       oversampling rate).
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RS485Ex_Init(LPUART_HandleTypeDef *hlpuart, uint32_t Polarity, uint32_t AssertionTime,
                                   uint32_t DeassertionTime)
{
  uint32_t temp;

  /* Check the LPUART handle allocation */
  if (hlpuart == NULL)
  {
    return HAL_ERROR;
  }
  /* Check the Driver Enable LPUART instance */
  assert_param(IS_LPUART_DRIVER_ENABLE_INSTANCE(hlpuart->Instance));

  /* Check the Driver Enable polarity */
  assert_param(IS_LPUART_DE_POLARITY(Polarity));

  /* Check the Driver Enable assertion time */
  assert_param(IS_LPUART_ASSERTIONTIME(AssertionTime));

  /* Check the Driver Enable deassertion time */
  assert_param(IS_LPUART_DEASSERTIONTIME(DeassertionTime));

  if (hlpuart->gState == HAL_LPUART_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hlpuart->Lock = HAL_UNLOCKED;

#if (USE_HAL_LPUART_REGISTER_CALLBACKS == 1)
    LPUART_InitCallbacksToDefault(hlpuart);

    if (hlpuart->MspInitCallback == NULL)
    {
      hlpuart->MspInitCallback = HAL_LPUART_MspInit;
    }

    /* Init the low level hardware */
    hlpuart->MspInitCallback(hlpuart);
#else
    /* Init the low level hardware : GPIO, CLOCK, CORTEX */
    HAL_LPUART_MspInit(hlpuart);
#endif /* (USE_HAL_LPUART_REGISTER_CALLBACKS) */
  }

  hlpuart->gState = HAL_LPUART_STATE_BUSY;

  /* Disable the Peripheral */
  __HAL_LPUART_DISABLE(hlpuart);

  /* Set the LPUART Communication parameters */
  if (LPUART_SetConfig(hlpuart) == HAL_ERROR)
  {
    return HAL_ERROR;
  }

  if (hlpuart->AdvancedInit.AdvFeatureInit != LPUART_ADVFEATURE_NO_INIT)
  {
    LPUART_AdvFeatureConfig(hlpuart);
  }

  /* Enable the Driver Enable mode by setting the DEM bit in the CR3 register */
  SET_BIT(hlpuart->Instance->CR3, LPUART_CR3_DEM);

  /* Set the Driver Enable polarity */
  MODIFY_REG(hlpuart->Instance->CR3, LPUART_CR3_DEP, Polarity);

  /* Set the Driver Enable assertion and deassertion times */
  temp = (AssertionTime << LPUART_CR1_DEAT_ADDRESS_LSB_POS);
  temp |= (DeassertionTime << LPUART_CR1_DEDT_ADDRESS_LSB_POS);
  MODIFY_REG(hlpuart->Instance->CR1, (LPUART_CR1_DEDT | LPUART_CR1_DEAT), temp);

  /* Enable the Peripheral */
  __HAL_LPUART_ENABLE(hlpuart);

  /* TEACK and/or REACK to check before moving hlpuart->gState and hlpuart->RxState to Ready */
  return (LPUART_CheckIdleState(hlpuart));
}

/**
  * @}
  */

/** @defgroup LPUARTEx_Exported_Functions_Group2 IO operation functions
  *  @brief Extended functions
  *
@verbatim
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================
    This subsection provides a set of Wakeup related callback functions.

    (#) Wakeup from Stop mode Callback:
        (+) HAL_LPUARTEx_WakeupCallback()

@endverbatim
  * @{
  */

/**
  * @brief LPUART wakeup from Stop mode callback.
  * @param hlpuart LPUART handle.
  * @retval None
  */
__weak void HAL_LPUARTEx_WakeupCallback(LPUART_HandleTypeDef *hlpuart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hlpuart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_LPUARTEx_WakeupCallback can be implemented in the user file.
   */
}

/**
  * @}
  */

/** @defgroup LPUARTEx_Exported_Functions_Group3 Peripheral Control functions
  * @brief    Extended Peripheral Control functions
  *
@verbatim
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================
    [..] This section provides the following functions:
     (+) HAL_MultiProcessorEx_AddressLength_Set() API optionally sets the LPUART node address
         detection length to more than 4 bits for multiprocessor address mark wake up.
     (+) HAL_LPUARTEx_StopModeWakeUpSourceConfig() API defines the wake-up from stop mode
         trigger: address match, Start Bit detection or RXNE bit status.
     (+) HAL_LPUARTEx_EnableStopMode() API enables the LPUART to wake up the MCU from stop mode
     (+) HAL_LPUARTEx_DisableStopMode() API disables the above functionality

@endverbatim
  * @{
  */

/**
  * @brief By default in multiprocessor mode, when the wake up method is set
  *        to address mark, the LPUART handles only 4-bit long addresses detection;
  *        this API allows to enable longer addresses detection (6-, 7- or 8-bit
  *        long).
  * @note  Addresses detection lengths are: 6-bit address detection in 7-bit data mode,
  *        7-bit address detection in 8-bit data mode, 8-bit address detection in 9-bit data mode.
  * @param hlpuart         LPUART handle.
  * @param AddressLength This parameter can be one of the following values:
  *          @arg @ref LPUART_ADDRESS_DETECT_4B 4-bit long address
  *          @arg @ref LPUART_ADDRESS_DETECT_7B 6-, 7- or 8-bit long address
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_MultiProcessorEx_AddressLength_Set(LPUART_HandleTypeDef *hlpuart, uint32_t AddressLength)
{
  /* Check the LPUART handle allocation */
  if (hlpuart == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the address length parameter */
  assert_param(IS_LPUART_ADDRESSLENGTH_DETECT(AddressLength));

  hlpuart->gState = HAL_LPUART_STATE_BUSY;

  /* Disable the Peripheral */
  __HAL_LPUART_DISABLE(hlpuart);

  /* Set the address length */
  MODIFY_REG(hlpuart->Instance->CR2, LPUART_CR2_ADDM7, AddressLength);

  /* Enable the Peripheral */
  __HAL_LPUART_ENABLE(hlpuart);

  /* TEACK and/or REACK to check before moving hlpuart->gState to Ready */
  return (LPUART_CheckIdleState(hlpuart));
}

/**
  * @brief Set Wakeup from Stop mode interrupt flag selection.
  * @note It is the application responsibility to enable the interrupt used as
  *       lpuart_wkup interrupt source before entering low-power mode.
  * @param hlpuart           LPUART handle.
  * @param WakeUpSelection Address match, Start Bit detection or RXNE/RXFNE bit status.
  *          This parameter can be one of the following values:
  *          @arg @ref LPUART_WAKEUP_ON_ADDRESS
  *          @arg @ref LPUART_WAKEUP_ON_STARTBIT
  *          @arg @ref LPUART_WAKEUP_ON_READDATA_NONEMPTY
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPUARTEx_StopModeWakeUpSourceConfig(LPUART_HandleTypeDef *hlpuart, LPUART_WakeUpTypeDef WakeUpSelection)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t tickstart;

  /* check the wake-up from stop mode LPUART instance */
  assert_param(IS_LPUART_WAKEUP_FROMSTOP_INSTANCE(hlpuart->Instance));
  /* check the wake-up selection parameter */
  assert_param(IS_LPUART_WAKEUP_SELECTION(WakeUpSelection.WakeUpEvent));

  /* Process Locked */
  __HAL_LOCK(hlpuart);

  hlpuart->gState = HAL_LPUART_STATE_BUSY;

  /* Disable the Peripheral */
  __HAL_LPUART_DISABLE(hlpuart);

  /* Set the wake-up selection scheme */
  MODIFY_REG(hlpuart->Instance->CR3, LPUART_CR3_WUS, WakeUpSelection.WakeUpEvent);

  if (WakeUpSelection.WakeUpEvent == LPUART_WAKEUP_ON_ADDRESS)
  {
    LPUARTEx_Wakeup_AddressConfig(hlpuart, WakeUpSelection);
  }

  /* Enable the Peripheral */
  __HAL_LPUART_ENABLE(hlpuart);

  /* Init tickstart for timeout management */
  tickstart = HAL_GetTick();

  /* Wait until REACK flag is set */
  if (LPUART_WaitOnFlagUntilTimeout(hlpuart, LPUART_ISR_REACK, RESET, tickstart, HAL_LPUART_TIMEOUT_VALUE) != HAL_OK)
  {
    status = HAL_TIMEOUT;
  }
  else
  {
    /* Initialize the LPUART State */
    hlpuart->gState = HAL_LPUART_STATE_READY;
  }

  /* Process Unlocked */
  __HAL_UNLOCK(hlpuart);

  return status;
}

/**
  * @brief Enable LPUART Stop Mode.
  * @note The LPUART is able to wake up the MCU from Stop 1 mode as long as LPUART clock is HSI or LSE.
  * @param hlpuart LPUART handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPUARTEx_EnableStopMode(LPUART_HandleTypeDef *hlpuart)
{
  /* Process Locked */
  __HAL_LOCK(hlpuart);

  /* Set UESM bit */
  SET_BIT(hlpuart->Instance->CR1, LPUART_CR1_UESM);

  /* Process Unlocked */
  __HAL_UNLOCK(hlpuart);

  return HAL_OK;
}

/**
  * @brief Disable LPUART Stop Mode.
  * @param hlpuart LPUART handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPUARTEx_DisableStopMode(LPUART_HandleTypeDef *hlpuart)
{
  /* Process Locked */
  __HAL_LOCK(hlpuart);

  /* Clear UESM bit */
  CLEAR_BIT(hlpuart->Instance->CR1, LPUART_CR1_UESM);

  /* Process Unlocked */
  __HAL_UNLOCK(hlpuart);

  return HAL_OK;
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup LPUARTEx_Private_Functions
  * @{
  */

/**
  * @brief Initialize the LPUART wake-up from stop mode parameters when triggered by address detection.
  * @param hlpuart           LPUART handle.
  * @param WakeUpSelection LPUART wake up from stop mode parameters.
  * @retval None
  */
static void LPUARTEx_Wakeup_AddressConfig(LPUART_HandleTypeDef *hlpuart, LPUART_WakeUpTypeDef WakeUpSelection)
{
  assert_param(IS_LPUART_ADDRESSLENGTH_DETECT(WakeUpSelection.AddressLength));

  /* Set the LPUART address length */
  MODIFY_REG(hlpuart->Instance->CR2, LPUART_CR2_ADDM7, WakeUpSelection.AddressLength);

  /* Set the LPUART address node */
  MODIFY_REG(hlpuart->Instance->CR2, LPUART_CR2_ADD, ((uint32_t)WakeUpSelection.Address << LPUART_CR2_ADDRESS_LSB_POS));
}


/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup LPUART_Exported_Functions LPUART Exported Functions
  * @{
  */

/** @defgroup LPUART_Exported_Functions_Group1 Initialization and de-initialization functions
  *  @brief   Initialization and Configuration functions
  * @{
  */

/**
  * @}
  */
#endif /* HAL_LPUART_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT PUYA *****END OF FILE****/
