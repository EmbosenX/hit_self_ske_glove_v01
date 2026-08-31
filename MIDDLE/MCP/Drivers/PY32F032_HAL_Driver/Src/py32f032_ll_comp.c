/**
  ******************************************************************************
  * @file    py32f032_ll_comp.c
  * @author  MCU Application Team
  * @brief   COMP LL module driver.
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
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "py32f032_ll_comp.h"
#include "py32f032_ll_bus.h"

#ifdef  USE_FULL_ASSERT
#include "py32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

/** @addtogroup PY32F032_LL_Driver
  * @{
  */

#if defined(COMP1) || defined(COMP2)

/** @addtogroup COMP_LL COMP
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/** @addtogroup COMP_LL_Private_Macros
  * @{
  */

/* Check of parameters for configuration of COMP hierarchical scope:          */
/* COMP instance.                                                             */

#define IS_LL_COMP_POWER_MODE(__POWER_MODE__)                                  \
  (   ((__POWER_MODE__) == LL_COMP_POWERMODE_HIGHSPEED)                        \
   || ((__POWER_MODE__) == LL_COMP_POWERMODE_MEDIUMSPEED)                      \
  )

/** @defgroup COMP_LL_EC_INPUT_MINUS Comparator inputs - Input minus (input inverting) selection
  * @{
  */

#define IS_LL_COMP_INPUT_PLUS(__COMP_INSTANCE__, __INPUT_PLUS__)               \
  (   ((__INPUT_PLUS__) == LL_COMP_INPUT_PLUS_IO0)                             \
   || ((__INPUT_PLUS__) == LL_COMP_INPUT_PLUS_IO1)                             \
   || ((__INPUT_PLUS__) == LL_COMP_INPUT_PLUS_IO2)                             \
   || ((__INPUT_PLUS__) == LL_COMP_INPUT_PLUS_IO3)                             \
   || ((__INPUT_PLUS__) == LL_COMP_INPUT_PLUS_COMP1_OPA1)                      \
   || ((__INPUT_PLUS__) == LL_COMP_INPUT_PLUS_COMP1_OPA2)                      \
   || ((__INPUT_PLUS__) == LL_COMP_INPUT_PLUS_COMP2_OPA1)                      \
   || ((__INPUT_PLUS__) == LL_COMP_INPUT_PLUS_COMP2_OPA2)                      \
  )

#define IS_LL_COMP_INPUT_MINUS(__COMP_INSTANCE__, __INPUT_MINUS__)             \
  (   ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_COMP1_IO0)                     \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_COMP1_IO1)                     \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_COMP1_OPA1)                    \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_COMP1_VREFCMP)                 \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_COMP1_TS_VIN)                  \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_COMP1_VREFINT)                 \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_COMP1_VREFBUF)                 \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_COMP1_OPA2)                    \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_COMP2_IO0)                     \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_COMP2_IO1)                     \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_COMP2_IO2)                     \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_COMP2_VREFCMP)                 \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_COMP2_TS_VIN)                  \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_COMP2_VREFINT)                 \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_COMP2_VREFBUF)                 \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_COMP2_OPA1)                    \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_COMP2_OPA2)                    \
  )

#define IS_LL_COMP_INPUT_HYSTERESIS(__INPUT_HYSTERESIS__)                      \
  (   ((__INPUT_HYSTERESIS__) == LL_COMP_HYSTERESIS_DISABLE)                   \
   || ((__INPUT_HYSTERESIS__) == LL_COMP_HYSTERESIS_ENABLE)                    \
  )

#define IS_LL_COMP_OUTPUT_POLARITY(__POLARITY__)                               \
  (   ((__POLARITY__) == LL_COMP_OUTPUTPOL_NONINVERTED)                        \
   || ((__POLARITY__) == LL_COMP_OUTPUTPOL_INVERTED)                           \
  )

#define IS_LL_COMP_OUTPUT_BLANKSEL_SOURCE(__BLANKSEL_SOURCE__)                \
  (   ((__BLANKSEL_SOURCE__) == LL_COMP_BLANKINGSRC_NONE)                     \
   || ((__BLANKSEL_SOURCE__) == LL_COMP_BLANKINGSRC_TIM1_OC4)                 \
   || ((__BLANKSEL_SOURCE__) == LL_COMP_BLANKINGSRC_TIM1_OC5)                 \
   || ((__BLANKSEL_SOURCE__) == LL_COMP_BLANKINGSRC_TIM3_OC3)                 \
  )

/**
  * @}
  */


/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup COMP_LL_Exported_Functions
  * @{
  */

/** @addtogroup COMP_LL_EF_Init
  * @{
  */

/**
  * @brief  De-initialize registers of the selected COMP instance
  *         to their default reset values.
  * @param  COMPx COMP instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: COMP registers are de-initialized
  *          - ERROR: COMP registers are not de-initialized
  */
ErrorStatus LL_COMP_DeInit(COMP_TypeDef *COMPx)
{
  ErrorStatus status = SUCCESS;

  /* Check the parameters */
  assert_param(IS_COMP_ALL_INSTANCE(COMPx));
  
  /* Note: Hardware constraint (refer to description of this function):       */
  /*       COMP instance must not be locked.                                  */
  if (LL_COMP_IsLocked(COMPx) == 0U)
  {
    LL_COMP_WriteReg(COMPx, CSR, 0x00000000U);
    LL_COMP_WriteReg(COMPx, FR, 0x00000000U);
  }
  else
  {
    /* Comparator instance is locked: de-initialization by software is         */
    /* not possible.                                                           */
    /* The only way to unlock the comparator is a device hardware reset.       */
    status = ERROR;
  }
  
  return status;
}

/**
  * @brief  Initialize some features of COMP instance.
  * @note   This function configures features of the selected COMP instance.
  *         Some features are also available at scope COMP common instance
  *         (common to several COMP instances).
  *         Refer to functions having argument "COMPxy_COMMON" as parameter.
  * @param  COMPx COMP instance
  * @param  COMP_InitStruct Pointer to a @ref LL_COMP_InitTypeDef structure
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: COMP registers are initialized
  *          - ERROR: COMP registers are not initialized
  */
ErrorStatus LL_COMP_Init(COMP_TypeDef *COMPx, LL_COMP_InitTypeDef *COMP_InitStruct)
{
  ErrorStatus status = SUCCESS;

  /* Check the parameters */
  assert_param(IS_COMP_ALL_INSTANCE(COMPx));
  assert_param(IS_LL_COMP_POWER_MODE(COMP_InitStruct->PowerMode));
  assert_param(IS_LL_COMP_INPUT_PLUS(COMPx, COMP_InitStruct->InputPlus));
  assert_param(IS_LL_COMP_INPUT_MINUS(COMPx, COMP_InitStruct->InputMinus));
  assert_param(IS_LL_COMP_INPUT_HYSTERESIS(COMP_InitStruct->InputHysteresis));
  assert_param(IS_LL_COMP_OUTPUT_POLARITY(COMP_InitStruct->OutputPolarity));
  assert_param(IS_LL_COMP_OUTPUT_BLANKSEL_SOURCE(COMP_InitStruct->OutputBlankingSource));

  /* Note: Hardware constraint (refer to description of this function)        */
  /*       COMP instance must not be locked.                                  */
  if (LL_COMP_IsLocked(COMPx) == 0U)
  {
    MODIFY_REG(COMPx->CSR,
               COMP_CSR_PWRMODE
               | COMP_CSR_INPSEL
               | COMP_CSR_INMSEL
               | COMP_CSR_POLARITY
               | COMP_CSR_HYST
               | COMP_CSR_BLANKSEL
               ,
               COMP_InitStruct->PowerMode
               | COMP_InitStruct->InputPlus
               | COMP_InitStruct->InputMinus
               | COMP_InitStruct->OutputPolarity
               | COMP_InitStruct->InputHysteresis
               | COMP_InitStruct->OutputBlankingSource
               );
    
    if (COMP_InitStruct->DigitalFilter == 0)
    {
      /* Disable digital filter */
      CLEAR_BIT(COMPx->FR, COMP_FR_FLTEN);
    }
    else
    {
      WRITE_REG(COMPx->FR, (COMP_FR_FLTEN | (COMP_InitStruct->DigitalFilter << COMP_FR_FLTCNT_Pos)));
    }
  }
  else
  {
    /* Initialization error: COMP instance is locked.                         */
    status = ERROR;
  }

  return status;
}

/**
  * @brief Set each @ref LL_COMP_InitTypeDef field to default value.
  * @param COMP_InitStruct Pointer to a @ref LL_COMP_InitTypeDef structure
  *                        whose fields will be set to default values.
  * @retval None
  */
void LL_COMP_StructInit(LL_COMP_InitTypeDef *COMP_InitStruct)
{
  /* Set COMP_InitStruct fields to default values  */
  COMP_InitStruct->PowerMode            = LL_COMP_POWERMODE_MEDIUMSPEED;
  COMP_InitStruct->InputPlus            = LL_COMP_INPUT_PLUS_IO0;
  COMP_InitStruct->InputMinus           = LL_COMP_INPUT_MINUS_COMP1_IO0;
  COMP_InitStruct->InputHysteresis      = LL_COMP_HYSTERESIS_DISABLE;
  COMP_InitStruct->OutputPolarity       = LL_COMP_OUTPUTPOL_NONINVERTED;
  COMP_InitStruct->OutputBlankingSource = LL_COMP_BLANKINGSRC_NONE;
  COMP_InitStruct->DigitalFilter        = 0;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* COMP1 || COMP2 */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */


/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
