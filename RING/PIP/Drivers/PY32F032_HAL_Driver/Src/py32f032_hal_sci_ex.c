/**
  ******************************************************************************
  * @file    py32f032_hal_sci_ex.c
  * @author  MCU Application Team
  * @brief   SCI HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Universal Asynchronous Receiver Transmitter Peripheral (SCI).
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
#include "py32f032_hal_sci.h"

/** @addtogroup PY32F032_HAL_Driver
  * @{
  */

/** @defgroup SCIEx SCIEx
  * @brief HAL SCI module driver
  * @{
  */
#ifdef HAL_SCI_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/

/** @defgroup SCIEx_Exported_Functions_Group1 IO operation functions
  * @brief Extended SCI Wakeup functions
  *
@verbatim
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================
    This subsection provides a set of Wake up related callback functions.

    (#) Wakeup Callback:
        (+) HAL_SCIEx_WakeupCallback()

@endverbatim
  * @{
  */

/**
  * @brief  SCI wake up callback.
  * @param  hsci SCI handle.
  * @retval None
  */
__weak void HAL_SCIEx_WakeupCallback(SCI_HandleTypeDef *hsci)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hsci);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SCIEx_WakeupCallback can be implemented in the user file.
   */
}

/**
  * @}
  */

/** @defgroup SCIEx_Exported_Functions_Group2 Peripheral Control functions
  * @brief    Extended Peripheral Control functions
  *
@verbatim
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================
@endverbatim
  * @{
  */

/**
  * @brief Receive an amount of data in blocking mode till either the expected number of data
  *        is received or an IDLE event occurs.
  * @note  HAL_OK is returned if reception is completed (expected number of data has been received)
  *        or if reception is stopped after IDLE event (less than the expected number of data has been received)
  *        In this case, RxLen output parameter indicates number of data available in reception buffer.
  * @note  When SCI parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
  *        the received data is handled as a set of uint16_t. In this case, Size must indicate the number
  *        of uint16_t available through pData.
  * @param hsci    SCI handle.
  * @param pData   Pointer to data buffer (uint8_t or uint16_t data elements).
  * @param Size    Amount of data elements (uint8_t or uint16_t or uint32_t) to be received.
  * @param RxLen   Number of data elements finally received
  *                (could be lower than Size, in case reception ends on IDLE event)
  * @param Timeout Timeout duration expressed in ms (covers the whole reception sequence).
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SCIEx_ReceiveToIdle(SCI_HandleTypeDef *hsci, uint8_t *pData, uint32_t Size, uint16_t *RxLen,
                                           uint32_t Timeout)
{
  uint8_t  *pdata8bits;
  uint16_t *pdata16bits;
  uint16_t uhMask;
  uint32_t tickstart;

  /* Check that a Rx process is not already ongoing */
  if (hsci->RxState == HAL_SCI_STATE_READY)
  {
    if ((pData == NULL) || (Size == 0U))
    {
      return  HAL_ERROR;
    }

    hsci->ErrorCode = HAL_SCI_ERROR_NONE;
    hsci->RxState = HAL_SCI_STATE_BUSY_RX;
    hsci->ReceptionType = HAL_SCI_RECEPTION_TOIDLE;
    hsci->RxEventType = HAL_SCI_RXEVENT_TC;

    /* Init tickstart for timeout management */
    tickstart = HAL_GetTick();

    hsci->RxXferSize  = Size;
    hsci->RxXferCount = Size;

    /* Computation of SCI mask to apply to RDR register */
    SCI_MASK_COMPUTATION(hsci);
    uhMask = hsci->Mask;

    /* In case of 9bits/No Parity transfer, pRxData needs to be handled as a uint16_t pointer */
    if ((hsci->Init.WordLength == SCI_WORDLENGTH_9B) && (hsci->Init.Parity == SCI_PARITY_NONE))
    {
      pdata8bits  = NULL;
      pdata16bits = (uint16_t *) pData;
    }
    else
    {
      pdata8bits  = pData;
      pdata16bits = NULL;
    }

    /* Initialize output number of received elements */
    *RxLen = 0U;

    /* as long as data have to be received */
    while (hsci->RxXferCount > 0U)
    {
      /* Check if IDLE flag is set */
      if (__HAL_SCI_GET_FLAG(hsci, SCI_FLAG_IDLE))
      {
        /* Clear IDLE flag in SR */
        __HAL_SCI_CLEAR_IDLEFLAG(hsci);

        /* If Set, but no data ever received, clear flag without exiting loop */
        /* If Set, and data has already been received, this means Idle Event is valid : End reception */
        if (*RxLen > 0U)
        {
          hsci->RxEventType = HAL_SCI_RXEVENT_IDLE;
          hsci->RxState = HAL_SCI_STATE_READY;

          return HAL_OK;
        }
      }

      /* Check if RXNE flag is set */
      if (__HAL_SCI_GET_FLAG(hsci, SCI_FLAG_RXNE))
      {
        if (pdata8bits == NULL)
        {
          *pdata16bits = (uint16_t)(hsci->Instance->DR & uhMask);
          pdata16bits++;
        }
        else
        {
          *pdata8bits = (uint8_t)(hsci->Instance->DR & (uint8_t)uhMask);
          pdata8bits++;
        }
        /* Increment number of received elements */
        *RxLen += 1U;
        hsci->RxXferCount--;
      }

      /* Check for the Timeout */
      if (Timeout != HAL_MAX_DELAY)
      {
        if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
        {
          hsci->RxState = HAL_SCI_STATE_READY;

          return HAL_TIMEOUT;
        }
      }
    }

    /* Set number of received elements in output parameter : RxLen */
    *RxLen = hsci->RxXferSize - hsci->RxXferCount;
    /* At end of Rx process, restore hsci->RxState to Ready */
    hsci->RxState = HAL_SCI_STATE_READY;

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief Receive an amount of data in interrupt mode till either the expected number of data
  *        is received or an IDLE event occurs.
  * @note  Reception is initiated by this function call. Further progress of reception is achieved thanks
  *        to SCI interrupts raised by RXNE and IDLE events. Callback is called at end of reception indicating
  *        number of received data elements.
  * @note  When SCI parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
  *        the received data is handled as a set of uint16_t. In this case, Size must indicate the number
  *        of uint16_t available through pData.
  * @param hsci SCI handle.
  * @param pData Pointer to data buffer (uint8_t or uint16_t data elements).
  * @param Size  Amount of data elements (uint8_t or uint16_t or uint32_t) to be received.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SCIEx_ReceiveToIdle_IT(SCI_HandleTypeDef *hsci, uint8_t *pData, uint32_t Size)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check that a Rx process is not already ongoing */
  if (hsci->RxState == HAL_SCI_STATE_READY)
  {
    if ((pData == NULL) || (Size == 0U))
    {
      return HAL_ERROR;
    }

    /* Set Reception type to reception till IDLE Event*/
    hsci->ReceptionType = HAL_SCI_RECEPTION_TOIDLE;
    hsci->RxEventType = HAL_SCI_RXEVENT_TC;

    (void)SCI_Start_Receive_IT(hsci, pData, Size);

    if (hsci->ReceptionType == HAL_SCI_RECEPTION_TOIDLE)
    {
      __HAL_SCI_CLEAR_IDLEFLAG(hsci);
      ATOMIC_SET_BIT(hsci->Instance->CR1, USART_CR1_IDLEIE);
    }
    else
    {
      /* In case of errors already pending when reception is started,
         Interrupts may have already been raised and lead to reception abortion.
         (Overrun error for instance).
         In such case Reception Type has been reset to HAL_SCI_RECEPTION_STANDARD. */
      status = HAL_ERROR;
    }

    return status;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief Receive an amount of data in DMA mode till either the expected number
  *        of data is received or an IDLE event occurs.
  * @note  Reception is initiated by this function call. Further progress of reception is achieved thanks
  *        to DMA services, transferring automatically received data elements in user reception buffer and
  *        calling registered callbacks at half/end of reception. SCI IDLE events are also used to consider
  *        reception phase as ended. In all cases, callback execution will indicate number of received data elements.
  * @note  When the SCI parity is enabled (PCE = 1), the received data contain
  *        the parity bit (MSB position).
  * @note  When hsci parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
  *        the received data is handled as a set of uint16_t. In this case, Size must indicate the number
  *        of uint16_t available through pData.
  * @param hsci  SCI handle.
  * @param pData Pointer to data buffer (uint8_t or uint16_t data elements).
  * @param Size  Amount of data elements (uint8_t or uint16_t or uint32_t) to be received.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SCIEx_ReceiveToIdle_DMA(SCI_HandleTypeDef *hsci, uint8_t *pData, uint32_t Size)
{
  HAL_StatusTypeDef status;

  /* Check that a Rx process is not already ongoing */
  if (hsci->RxState == HAL_SCI_STATE_READY)
  {
    if ((pData == NULL) || (Size == 0U))
    {
      return HAL_ERROR;
    }

    /* Set Reception type to reception till IDLE Event*/
    hsci->ReceptionType = HAL_SCI_RECEPTION_TOIDLE;
    hsci->RxEventType = HAL_SCI_RXEVENT_TC;

    status = SCI_Start_Receive_DMA(hsci, pData, Size);

    /* Check Rx process has been successfully started */
    if (status == HAL_OK)
    {
      if (hsci->ReceptionType == HAL_SCI_RECEPTION_TOIDLE)
      {
        __HAL_SCI_CLEAR_IDLEFLAG(hsci);
        SET_BIT(hsci->Instance->CR1, USART_CR1_IDLEIE);
      }
      else
      {
        /* In case of errors already pending when reception is started,
           Interrupts may have already been raised and lead to reception abortion.
           (Overrun error for instance).
           In such case Reception Type has been reset to HAL_SCI_RECEPTION_STANDARD. */
        status = HAL_ERROR;
      }
    }

    return status;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief Provide Rx Event type that has lead to RxEvent callback execution.
  * @note  When HAL_SCIEx_ReceiveToIdle_IT() or HAL_SCIEx_ReceiveToIdle_DMA() API are called, progress
  *        of reception process is provided to application through calls of Rx Event callback (either default one
  *        HAL_SCIEx_RxEventCallback() or user registered one). As several types of events could occur (IDLE event,
  *        Half Transfer, or Transfer Complete), this function allows to retrieve the Rx Event type that has lead
  *        to Rx Event callback execution.
  * @note  This function is expected to be called within the user implementation of Rx Event Callback,
  *        in order to provide the accurate value :
  *        In Interrupt Mode :
  *           - HAL_SCI_RXEVENT_TC : when Reception has been completed (expected nb of data has been received)
  *           - HAL_SCI_RXEVENT_IDLE : when Idle event occurred prior reception has been completed (nb of
  *             received data is lower than expected one)
  *        In DMA Mode :
  *           - HAL_SCI_RXEVENT_TC : when Reception has been completed (expected nb of data has been received)
  *           - HAL_SCI_RXEVENT_HT : when half of expected nb of data has been received
  *           - HAL_SCI_RXEVENT_IDLE : when Idle event occurred prior reception has been completed (nb of
  *             received data is lower than expected one).
  *        In DMA mode, RxEvent callback could be called several times;
  *        When DMA is configured in Normal Mode, HT event does not stop Reception process;
  *        When DMA is configured in Circular Mode, HT, TC or IDLE events don't stop Reception process;
  * @param  hsci SCI handle.
  * @retval Rx Event Type (return vale will be a value of @ref SCI_RxEvent_Type_Values)
  */
HAL_SCI_RxEventTypeTypeDef HAL_SCIEx_GetRxEventType(const SCI_HandleTypeDef *hsci)
{
  /* Return Rx Event type value, as stored in SCI handle */
  return (hsci->RxEventType);
}

/**
  * @}
  */

#endif /* HAL_SCI_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
