/**
  ******************************************************************************
  * @file    py32f032_hal_sci_ex.h
  * @author  MCU Application Team
  * @brief   Header file of SCI HAL module.
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
#ifndef __PY32F032_HAL_SCI_EX_H
#define __PY32F032_HAL_SCI_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f032_hal_def.h"

/** @addtogroup PY32F032_HAL_Driver
  * @{
  */

/** @addtogroup SCIEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup SCIEx_Exported_Types SCIEx Exported Types
  * @{
  */

/**
  * @brief  SCI wake up from stop mode parameters
  */
typedef struct
{
  uint16_t AddressLength;      /*!< Specifies whether the address is 4 long. */

  uint8_t Address;             /*!< SCI node address (4-bit long). */
} SCI_WakeUpTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup SCIEx_Exported_Constants SCIEx Exported Constants
  * @{
  */

/** @defgroup SCIEx_Word_Length SCIEx Word Length
  * @{
  */
#define SCI_WORDLENGTH_8B          0x00000000U    /*!< 8-bit long SCI frame */
#define SCI_WORDLENGTH_9B          USART_CR1_M    /*!< 9-bit long SCI frame */
/**
  * @}
  */

/**
  * @}
  */
 
/* Exported macros -----------------------------------------------------------*/
/** @defgroup SCIEx_Exported_Macros SCIEx Exported Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup SCIEx_Exported_Functions_Group2
  * @{
  */
void HAL_SCIEx_WakeupCallback(SCI_HandleTypeDef *hsci);

/**
  * @}
  */

/** @addtogroup SCIEx_Exported_Functions
  * @{
  */

/* Peripheral Control functions  **********************************************/
HAL_StatusTypeDef HAL_SCIEx_ReceiveToIdle(SCI_HandleTypeDef *hsci, uint8_t *pData, uint32_t Size, uint16_t *RxLen, \
                                           uint32_t Timeout);
HAL_StatusTypeDef HAL_SCIEx_ReceiveToIdle_IT(SCI_HandleTypeDef *hsci, uint8_t *pData, uint32_t Size);
HAL_StatusTypeDef HAL_SCIEx_ReceiveToIdle_DMA(SCI_HandleTypeDef *hsci, uint8_t *pData, uint32_t Size);

HAL_SCI_RxEventTypeTypeDef HAL_SCIEx_GetRxEventType(const SCI_HandleTypeDef *hsci);


/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup SCIEx_Private_Macros SCIEx Private Macros
  * @{
  */

/** @brief  Compute the SCI mask to apply to retrieve the received data
  *         according to the word length and to the parity bits activation.
  * @note   If PCE = 1, the parity bit is not included in the data extracted
  *         by the reception API().
  *         This masking operation is not carried out in the case of
  *         DMA transfers.
  * @param  __HANDLE__ specifies the SCI Handle.
  * @retval None, the mask to apply to SCI RDR register is stored in (__HANDLE__)->Mask field.
  */
#define SCI_MASK_COMPUTATION(__HANDLE__)                              \
  do {                                                                \
    if ((__HANDLE__)->Init.WordLength == SCI_WORDLENGTH_9B)           \
    {                                                                 \
      if ((__HANDLE__)->Init.Parity == SCI_PARITY_NONE)               \
      {                                                               \
        (__HANDLE__)->Mask = 0x01FFU;                                 \
      }                                                               \
      else                                                            \
      {                                                               \
        (__HANDLE__)->Mask = 0x00FFU;                                 \
      }                                                               \
    }                                                                 \
    else if ((__HANDLE__)->Init.WordLength == SCI_WORDLENGTH_8B)      \
    {                                                                 \
      if ((__HANDLE__)->Init.Parity == SCI_PARITY_NONE)               \
      {                                                               \
        (__HANDLE__)->Mask = 0x00FFU;                                 \
      }                                                               \
      else                                                            \
      {                                                               \
        (__HANDLE__)->Mask = 0x007FU;                                 \
      }                                                               \
    }                                                                 \
    else                                                              \
    {                                                                 \
      (__HANDLE__)->Mask = 0x0000U;                                   \
    }                                                                 \
  } while(0U)

/**
  * @brief Ensure that SCI frame length is valid.
  * @param __LENGTH__ SCI frame length.
  * @retval SET (__LENGTH__ is valid) or RESET (__LENGTH__ is invalid)
  */
#define IS_SCI_WORD_LENGTH(__LENGTH__) (((__LENGTH__) == SCI_WORDLENGTH_8B) || \
                                        ((__LENGTH__) == SCI_WORDLENGTH_9B))

/**S
  * @brief Ensure that SCI LINK frame length is valid.
  * @param __LENGTH__ SCI LINK frame length.
  * @retval SET (__LENGTH__ is valid) or RESET (__LENGTH__ is invalid)
  */
#define IS_SCI_LIN_WORD_LENGTH(__LENGTH__) (((__LENGTH__) == SCI_WORDLENGTH_8B))
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

#endif /* __PY32F032_HAL_SCI_EX_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
