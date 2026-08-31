/**
  ******************************************************************************
  * @file    py32f032_hal_opa.c
  * @author  MCU Application Team
  * @brief   OPA HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Power Controller (OPA) peripheral:
  *           + Initialization/de-initialization functions
  *           + Peripheral Control functions 
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

#ifdef HAL_OPA_MODULE_ENABLED

/** @defgroup OPA OPA
  * @brief OPA HAL module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup OPA_Private_Define OPA Private Define
  * @{
  */
/* CSR register reset value */
#define OPA_CSR_RESET_VALUE             (0x00000000UL)

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/

/** @defgroup OPA_Exported_Functions OPA Exported Functions
  * @{
  */

/** @defgroup OPA_Exported_Functions_Group1 Initialization and de-initialization functions
  *  @brief    Initialization and Configuration functions
  *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization  functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the OPA according to the specified
  *         parameters in the OPA_InitTypeDef and initialize the associated handle.
  * @param  hopa OPA handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OPA_Init(OPA_HandleTypeDef *hopa)
{
  HAL_StatusTypeDef status = HAL_OK;
  FlagStatus opa1clkchanged = RESET;

  /* Check the OPA handle allocation and lock status */
  /* Init not allowed if calibration is ongoing */
  if (hopa == NULL)
  {
    return HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_OPA_ALL_INSTANCE(hopa->Instance));

    /* Set OPA parameters */
    assert_param(IS_OPA_FUNCTIONAL_NORMALMODE(hopa->Init.Mode));

#if (USE_HAL_OPA_REGISTER_CALLBACKS == 1)
    if (hopa->State == HAL_OPA_STATE_RESET)
    {
      if (hopa->MspInitCallback == NULL)
      {
        hopa->MspInitCallback               = HAL_OPA_MspInit;
      }
    }
#endif /* USE_HAL_OPA_REGISTER_CALLBACKS */

    assert_param(IS_FUNCTIONAL_STATE(hopa->Init.ExternalOutput));

    if ((hopa->Init.Mode) == OPA_PGA_MODE)
    {
      assert_param(IS_OPA_PGA_GAIN(hopa->Init.PgaGain));
    }

    /* Init SYSCFG and the low level hardware to access opa */
    __HAL_RCC_SYSCFG_CLK_ENABLE();

    if (hopa->State == HAL_OPA_STATE_RESET)
    {
      /* Allocate lock resource and initialize it */
      hopa->Lock = HAL_UNLOCKED;
    }

#if (USE_HAL_OPA_REGISTER_CALLBACKS == 1)
    hopa->MspInitCallback(hopa);
#else
    /* Call MSP init function */
    HAL_OPA_MspInit(hopa);
#endif /* USE_HAL_OPA_REGISTER_CALLBACKS */

    /* Set OPA parameters */
    /*     Set  bits according to hopa->hopa->Init.Mode value                                 */
    /*     Set  bits according to hopa->hopa->Init.PgaGain value                              */

    MODIFY_REG(hopa->Instance->OCR,OPA_OCR_OPA_VMSEL,hopa->Init.Mode);

    if (hopa->Init.Mode == OPA_PGA_MODE)
    {
      MODIFY_REG(hopa->Instance->OCR,OPA_OCR_OPA_PGA_GAIN,hopa->Init.PgaGain);

      if((hopa->Init.PgaGain & OPA_OCR_OPA_PGA_GAIN_3)!=0)
      {
        if (__HAL_RCC_OPA1_IS_CLK_DISABLED() != 0U)
        {
          __HAL_RCC_OPA1_CLK_ENABLE();
          opa1clkchanged = SET;
        }
        
        MODIFY_REG(OPA1->OCR, OPA_OCR_OPA_VBIAS,hopa->Init.BiasVoltage);

        SET_BIT(hopa->Instance->OCR,OPA_OCR_OPA_VBSEL);

        /* Restore clock configuration if changed */
        if (opa1clkchanged == SET)
        {
          __HAL_RCC_OPA1_CLK_DISABLE();
        } 
      }
      else
      {
        CLEAR_BIT(hopa->Instance->OCR,OPA_OCR_OPA_VBSEL);
      }
    }
    else
    {
      CLEAR_BIT(hopa->Instance->OCR,OPA_OCR_OPA_VBSEL);
    }
   
    if(hopa->Init.ExternalOutput == ENABLE)
    {
      SET_BIT(hopa->Instance->OCR,OPA_OCR_OPA_EXTOEN);
    }
    else
    {
      CLEAR_BIT(hopa->Instance->OCR,OPA_OCR_OPA_EXTOEN);     
    }
    

    /* Update the OPA state*/
    if (hopa->State == HAL_OPA_STATE_RESET)
    {
      /* From RESET state to READY State */
      hopa->State = HAL_OPA_STATE_READY;
    }
    /* else: remain in READY or BUSY state (no update) */

    return status;
  }
}


/**
  * @brief  DeInitializes the OPA peripheral
  * @param  hopa OPA handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OPA_DeInit(OPA_HandleTypeDef *hopa)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the OPA handle allocation */
  /* DeInit not allowed if calibration is ongoing */
  if (hopa == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_OPA_ALL_INSTANCE(hopa->Instance));

    /* Set OPA_OCR register to reset value */
    WRITE_REG(hopa->Instance->OCR, OPA_CSR_RESET_VALUE);

    /* DeInit the low level hardware: GPIO, CLOCK and NVIC */
    /* When OPA is locked, unlocking can be achieved thanks to */
    /* __HAL_RCC_SYSCFG_CLK_DISABLE() call within HAL_OPA_MspDeInit */
    /* Note that __HAL_RCC_SYSCFG_CLK_DISABLE() also disables comparator */

#if (USE_HAL_OPA_REGISTER_CALLBACKS == 1)
    if (hopa->MspDeInitCallback == NULL)
    {
      hopa->MspDeInitCallback = HAL_OPA_MspDeInit;
    }
    /* DeInit the low level hardware */
    hopa->MspDeInitCallback(hopa);
#else
    HAL_OPA_MspDeInit(hopa);
#endif /* USE_HAL_OPA_REGISTER_CALLBACKS */

    hopa->State = HAL_OPA_STATE_RESET;

    /* Process unlocked */
    __HAL_UNLOCK(hopa);
  }

  return status;
}

/**
  * @brief  Initialize the OPA MSP.
  * @param  hopa OPA handle
  * @retval None
  */
__weak void HAL_OPA_MspInit(OPA_HandleTypeDef *hopa)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hopa);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_OPA_MspInit could be implemented in the user file
   */

  /* Example */
}

/**
  * @brief  DeInitialize OPA MSP.
  * @param  hopa OPA handle
  * @retval None
  */
__weak void HAL_OPA_MspDeInit(OPA_HandleTypeDef *hopa)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hopa);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_OPA_MspDeInit could be implemented in the user file
   */

}

/**
  * @}
  */


/** @defgroup OPA_Exported_Functions_Group2 Input and Output operation functions
  *  @brief   Data transfers functions
  *
@verbatim
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to manage the OPA data
    transfers.

@endverbatim
  * @{
  */

/**
  * @brief  Start the opa
  * @param  hopa OPA handle
  * @retval HAL status
  */

HAL_StatusTypeDef HAL_OPA_Start(OPA_HandleTypeDef *hopa)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the OPA handle allocation */
  /* Check if OPA locked */
  if (hopa == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_OPA_ALL_INSTANCE(hopa->Instance));

    if (hopa->State == HAL_OPA_STATE_READY)
    {
      /* Enable the selected opa */
      SET_BIT(hopa->Instance->CR, OPA_CR_OPAEN);

      /* Update the OPA state*/
      /* From HAL_OPA_STATE_READY to HAL_OPA_STATE_BUSY */
      hopa->State = HAL_OPA_STATE_BUSY;
    }
    else
    {
      status = HAL_ERROR;
    }


  }
  return status;
}

/**
  * @brief  Stop the opa
  * @param  hopa OPA handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OPA_Stop(OPA_HandleTypeDef *hopa)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the OPA handle allocation */
  if (hopa == NULL)
  {
    status = HAL_ERROR;
  }

  else
  {
    /* Check the parameter */
    assert_param(IS_OPA_ALL_INSTANCE(hopa->Instance));

    if (hopa->State == HAL_OPA_STATE_BUSY)
    {
      /* Disable the selected opa */
      CLEAR_BIT(hopa->Instance->CR, OPA_CR_OPAEN);

      /* Update the OPA state*/
      /* From  HAL_OPA_STATE_BUSY to HAL_OPA_STATE_READY*/
      hopa->State = HAL_OPA_STATE_READY;
    }
    else
    {
      status = HAL_ERROR;
    }
  }
  return status;
}


/**
  * @}
  */




/** @defgroup OPA_Exported_Functions_Group4 Peripheral State functions
  *  @brief   Peripheral State functions
  *
@verbatim
 ===============================================================================
                      ##### Peripheral State functions #####
 ===============================================================================
    [..]
    This subsection permit to get in run-time the status of the peripheral
    and the data flow.

@endverbatim
  * @{
  */

/**
  * @brief  Return the OPA state
  * @param  hopa OPA handle
  * @retval HAL state
  */
HAL_OPA_StateTypeDef HAL_OPA_GetState(OPA_HandleTypeDef *hopa)
{
  /* Check the OPA handle allocation */
  if (hopa == NULL)
  {
    return HAL_OPA_STATE_RESET;
  }

  /* Check the parameter */
  assert_param(IS_OPA_ALL_INSTANCE(hopa->Instance));

  return hopa->State;
}



#if (USE_HAL_OPA_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a User OPA Callback
  *         To be used instead of the weak (surcharged) predefined callback
  * @param hopa : OPA handle
  * @param CallbackID : ID of the callback to be registered
  *        This parameter can be one of the following values:
  *          @arg @ref HAL_OPA_MSPINIT_CB_ID       OPA MspInit callback ID
  *          @arg @ref HAL_OPA_MSPDEINIT_CB_ID     OPA MspDeInit callback ID
  * @param pCallback : pointer to the Callback function
  * @retval status
  */
HAL_StatusTypeDef HAL_OPA_RegisterCallback(OPA_HandleTypeDef *hopa, HAL_OPA_CallbackIDTypeDef CallbackId,
                                             pOPA_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hopa);

  if (hopa->State == HAL_OPA_STATE_READY)
  {
    switch (CallbackId)
    {
      case HAL_OPA_MSPINIT_CB_ID :
        hopa->MspInitCallback = pCallback;
        break;
      case HAL_OPA_MSPDEINIT_CB_ID :
        hopa->MspDeInitCallback = pCallback;
        break;
      default :
        /* update return status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if (hopa->State == HAL_OPA_STATE_RESET)
  {
    switch (CallbackId)
    {
      case HAL_OPA_MSPINIT_CB_ID :
        hopa->MspInitCallback = pCallback;
        break;
      case HAL_OPA_MSPDEINIT_CB_ID :
        hopa->MspDeInitCallback = pCallback;
        break;
      default :
        /* update return status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* update return status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hopa);
  return status;
}

/**
  * @brief  Unregister a User OPA Callback
  *         OPA Callback is redirected to the weak (surcharged) predefined callback
  * @param hopa : OPA handle
  * @param CallbackID : ID of the callback to be unregistered
  *        This parameter can be one of the following values:
  *          @arg @ref HAL_OPA_MSPINIT_CB_ID              OPA MSP Init Callback ID
  *          @arg @ref HAL_OPA_MSPDEINIT_CB_ID            OPA MSP DeInit Callback ID
  *          @arg @ref HAL_OPA_ALL_CB_ID                   OPA All Callbacks
  * @retval status
  */

HAL_StatusTypeDef HAL_OPA_UnRegisterCallback(OPA_HandleTypeDef *hopa, HAL_OPA_CallbackIDTypeDef CallbackId)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process locked */
  __HAL_LOCK(hopa);

  if (hopa->State == HAL_OPA_STATE_READY)
  {
    switch (CallbackId)
    {
      case HAL_OPA_MSPINIT_CB_ID :
        hopa->MspInitCallback = HAL_OPA_MspInit;
        break;
      case HAL_OPA_MSPDEINIT_CB_ID :
        hopa->MspDeInitCallback = HAL_OPA_MspDeInit;
        break;
      case HAL_OPA_ALL_CB_ID :
        hopa->MspInitCallback = HAL_OPA_MspInit;
        hopa->MspDeInitCallback = HAL_OPA_MspDeInit;
        break;
      default :
        /* update return status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if (hopa->State == HAL_OPA_STATE_RESET)
  {
    switch (CallbackId)
    {
      case HAL_OPA_MSPINIT_CB_ID :
        hopa->MspInitCallback = HAL_OPA_MspInit;
        break;
      case HAL_OPA_MSPDEINIT_CB_ID :
        hopa->MspDeInitCallback = HAL_OPA_MspDeInit;
        break;
      default :
        /* update return status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* update return status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hopa);
  return status;
}

#endif /* USE_HAL_OPA_REGISTER_CALLBACKS */

/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_OPA_MODULE_ENABLED */
/**
  * @}
  */



