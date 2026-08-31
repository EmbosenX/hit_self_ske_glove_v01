/**
  ******************************************************************************
  * @file    py32f032_hal_pwr.c
  * @author  MCU Application Team
  * @brief   PWR HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Power Controller (PWR) peripheral:
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

/** @defgroup PWR PWR
  * @brief    PWR HAL module driver
  * @{
  */

#ifdef HAL_PWR_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @defgroup PWR_Private_Constants PWR Private Constants
  * @{
  */
  
/** @defgroup PWR_PVD_Mode_Mask PWR PVD Mode Mask
  * @{
  */ 
#define PVD_MODE_IT               0x00010000U
#define PVD_MODE_EVT              0x00020000U
#define PVD_RISING_EDGE           0x00000001U
#define PVD_FALLING_EDGE          0x00000002U
/**
  * @}
  */
  
/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/** @defgroup PWR_Exported_Functions PWR Exported Functions
  * @{
  */

/** @defgroup PWR_Exported_Functions_Group1 Initialization and de-initialization functions 
  *  @brief   Initialization and de-initialization functions
  *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]
      After reset, the backup domain (RTC registers, RTC backup data
      registers) is protected against possible unwanted
      write accesses.
      To enable access to the RTC Domain and RTC registers, proceed as follows:
        (+) Enable the Power Controller (PWR) APB1 interface clock using the
            __HAL_RCC_PWR_CLK_ENABLE() macro.
        (+) Enable access to RTC domain using the HAL_PWR_EnableBkUpAccess() function.

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the PWR peripheral registers to their default reset values.  
  * @retval None
  */
void HAL_PWR_DeInit(void)
{
 __HAL_RCC_PWR_FORCE_RESET();
 __HAL_RCC_PWR_RELEASE_RESET();
}

/**
  * @brief  Enables access to the backup domain (RTC registers, RTC
  *         backup data registers ).
  * @retval None
  */
void HAL_PWR_EnableBkUpAccess(void)
{
  /* Enable access to RTC and backup registers */
  SET_BIT(PWR->CR1, PWR_CR1_DBP);
}

/**
  * @brief  Disables access to the backup domain (RTC registers, RTC
  *         backup data registers).
  * @retval None
  */
void HAL_PWR_DisableBkUpAccess(void)
{
  /* Disable access to RTC and backup registers */
  CLEAR_BIT(PWR->CR1, PWR_CR1_DBP);
}

/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group2 Peripheral Control functions 
  * @brief    Low Power modes configuration functions
  *
@verbatim
 ===============================================================================
                 ##### Peripheral Control functions #####
 ===============================================================================
     
    *** PVD configuration ***
    =========================
    [..]
      (+) The PVD is used to monitor the VDD power supply by comparing it to a
          threshold selected by the PVD Level (PVDT[2:0] bits in the PWR_CR2).

      (+) A PVDO flag is available to indicate if VDD/VDDA is higher or lower
          than the PVD threshold. This event is internally connected to the EXTI
          line16 and can generate an interrupt if enabled. This is done through
          __HAL_PWR_PVD_EXTI_ENABLE_IT() macro.
      (+) The PVD is stopped in Standby mode.


    *** Low Power modes configuration ***
    =====================================
     [..]
      The device features 3 low-power modes:
      (+) Sleep mode: CPU clock off, all peripherals including Cortex-M0+ core peripherals like 
                      NVIC, SysTick, etc. are kept running
      (+) Stop mode: All clocks are stopped
  
  
   *** Sleep mode ***
   ==================
    [..]
      (+) Entry:
          The Sleep mode is entered by using the HAL_PWR_EnterSLEEPMode(PWR_SLEEPENTRY_WFx)
              functions with
          (++) PWR_SLEEPENTRY_WFI: enter SLEEP mode with WFI instruction
          (++) PWR_SLEEPENTRY_WFE: enter SLEEP mode with WFE instruction
     
      (+) Exit:
        (++) WFI entry mode, Any peripheral interrupt acknowledged by the nested vectored interrupt
             controller (NVIC) can wake up the device from Sleep mode.
        (++) WFE entry mode, Any wakeup event can wake up the device from Sleep mode.
           (+++) Any peripheral interrupt w/o NVIC configuration & SEVONPEND bit set in the Cortex (HAL_PWR_EnableSEVOnPend)
           (+++) Any EXTI Line (Internal or External) configured in Event mode

   *** Stop mode ***
   =================
    [..]

      (+) Entry:
           The Stop mode is entered using the HAL_PWR_EnterSTOPMode(PWR_REGULATOR_VALUE, PWR_SLEEPENTRY_WFx )
             function with:
          (++) PWR_REGULATOR_VALUE= PWR_DEEPLOWPOWERREGULATOR_ON: Deep Low Power regulator ON.
          (++) PWR_SLEEPENTRY_WFx= PWR_SLEEPENTRY_WFI: enter STOP mode with WFI instruction
          (++) PWR_SLEEPENTRY_WFx= PWR_SLEEPENTRY_WFE: enter STOP mode with WFE instruction
      (+) Exit:
          (++) WFI entry mode, Any EXTI Line (Internal or External) configured in Interrupt mode with NVIC configured
          (++) WFE entry mode, Any EXTI Line (Internal or External) configured in Event mode.


   *** Auto-wakeup (AWU) from low-power mode ***
       =============================================
       [..]
        
       (+) The MCU can be woken up from low-power mode by an RTC Alarm event, 
           without depending on an external interrupt (Auto-wakeup mode).
   
       (+) RTC auto-wakeup (AWU) from the Stop modes

           (++) To wake up from the Stop mode with an RTC alarm event, it is necessary to 
                configure the RTC to generate the RTC alarm using the HAL_RTC_SetAlarm_IT() function.

   *** PWR Workarounds linked to Silicon Limitation ***
       ====================================================
        
@endverbatim
  * @{
  */

/**
  * @brief  Configures the voltage threshold detected by the Power Voltage Detector(PVD).
  * @param  sConfigPVD: pointer to an PWR_PVDTypeDef structure that contains the configuration
  *         information for the PVD.
  * @note   Refer to the electrical characteristics of your device datasheet for
  *         more details about the voltage threshold corresponding to each
  *         detection level.
  * @retval None
  */
void HAL_PWR_ConfigPVD(PWR_PVDTypeDef *sConfigPVD)
{
  /* Check the parameters */
  assert_param(IS_PWR_PVD_LEVEL(sConfigPVD->PVDLevel));
  assert_param(IS_PWR_PVD_MODE(sConfigPVD->Mode));
  assert_param(IS_PWR_PVD_FILTER(sConfigPVD->PVDFilter));
  assert_param(IS_PWR_PVD_OUTPUT_SELECT(sConfigPVD->PVDOutputSelect)); 

  /* Set PVDT[2:0] and PVD_OUT_SEL bits according to PVDLevel value */
  MODIFY_REG(PWR->CR2, PWR_CR2_PVDT | PWR_CR2_PVD_OUT_SEL, sConfigPVD->PVDLevel | sConfigPVD->PVDOutputSelect);
  
  if(sConfigPVD->PVDOutputSelect == PWR_PVD_OUT_SYN_FILTER)
  {
    MODIFY_REG(PWR->CR2, (PWR_CR2_FLTEN | PWR_CR2_FLT_TIME), sConfigPVD->PVDFilter);
  }
  else
  {
    CLEAR_BIT(PWR->CR2, PWR_CR2_FLTEN);
  }
  
  /* Clear any previous config. Keep it clear if no event or IT mode is selected */
  __HAL_PWR_PVD_EXTI_DISABLE_EVENT();
  __HAL_PWR_PVD_EXTI_DISABLE_IT();
  __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE(); 
  __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE();

  /* Configure interrupt mode */
  if((sConfigPVD->Mode & PVD_MODE_IT) == PVD_MODE_IT)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_IT();
  }
  
  /* Configure event mode */
  if((sConfigPVD->Mode & PVD_MODE_EVT) == PVD_MODE_EVT)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_EVENT();
  }
  
  /* Configure the edge */
  if((sConfigPVD->Mode & PVD_RISING_EDGE) == PVD_RISING_EDGE)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE();
  }
  
  if((sConfigPVD->Mode & PVD_FALLING_EDGE) == PVD_FALLING_EDGE)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE();
  }
}

/**
  * @brief  Enables the Power Voltage Detector(PVD).
  * @retval None
  */
void HAL_PWR_EnablePVD(void)
{
  /* Enable the power voltage detector */
  SET_BIT(PWR->CR2, PWR_CR2_PVDE);
}

/**
  * @brief  Disables the Power Voltage Detector(PVD).
  * @retval None
  */
void HAL_PWR_DisablePVD(void)
{
  /* Disable the power voltage detector */
  CLEAR_BIT(PWR->CR2, PWR_CR2_PVDE);
}

/**
  * @brief Enter Sleep or Low-power Sleep mode.
  * @note  In Sleep/Low-power Sleep mode, all I/O pins keep the same state as in Run mode.
  * @param Regulator: Specifies the regulator state in Sleep/Low-power Sleep mode.
  *          This parameter can be one of the following values:
  *            @arg @ref PWR_MAINREGULATOR_ON Sleep mode (regulator in main mode)
  *            @arg @ref PWR_LOWPOWERREGULATOR_ON Low-power Sleep mode
  * @note  Low-power Sleep mode is entered from Low-power Run mode.
  *        Additionally, the system clock source must be set to MSISYS.
  * @note  When exiting Low-power Sleep mode, the MCU is in Low-power Run mode. To move in
  *        Run mode, the user must resort to HAL_PWREx_DisableLowPowerRunMode() API.
  * @param SLEEPEntry: Specifies if Sleep mode is entered with WFI or WFE instruction.
  *           This parameter can be one of the following values:
  *            @arg @ref PWR_SLEEPENTRY_WFI enter Sleep or Low-power Sleep mode with WFI instruction
  *            @arg @ref PWR_SLEEPENTRY_WFE enter Sleep or Low-power Sleep mode with WFE instruction
  * @note  When WFI entry is used, tick interrupt have to be disabled if not desired as
  *        the interrupt wake up source.
  * @retval None
  */
void HAL_PWR_EnterSLEEPMode(uint32_t Regulator, uint8_t SLEEPEntry)
{
  /* Check the parameters */
  assert_param(IS_PWR_REGULATOR(Regulator));
  assert_param(IS_PWR_SLEEP_ENTRY(SLEEPEntry));

  /* Set Regulator parameter */
  if (Regulator == PWR_MAINREGULATOR_ON)
  {
    /* If in low-power run mode at this point, exit it */
    if ((HAL_IS_BIT_SET(PWR->SR, PWR_SR_MR_RDY) == 0U) || (READ_BIT(PWR->CR1, PWR_CR1_LPMS) != 0U))
    {
      (void)HAL_PWREx_DisableLowPowerRunMode();
    }
    /* Regulator now in main mode. */
  }
  else
  {
    HAL_PWREx_EnableLowPowerRunMode();
  }

  MODIFY_REG(PWR->CR1, PWR_CR1_VR_MODE, Regulator);

  /* Clear SLEEPDEEP bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  /* Select SLEEP mode entry -------------------------------------------------*/
  if(SLEEPEntry == PWR_SLEEPENTRY_WFI)
  {
    /* Request Wait For Interrupt */
    __WFI();
  }
  else
  {
    /* Request Wait For Event */
    __SEV();
    __WFE();
    __WFE();
  }
}

/**
  * @brief  Enter the whole system to Stop mode.
  * @param  Regulator : Specifies the regulator state in Stop mode.
  *                     This parameter can be one of the following values :
  *                     @arg @ref PWR_DEEPLOWPOWERREGULATOR_ON
  * @param  StopEntry : Specifies if Stop mode is entered with WFI or WFE
  *                     instruction.
  *                     This parameter can be one of the following values :
  *            @arg PWR_STOPENTRY_WFI              : Enter STOP mode with WFI instruction.
  *            @arg PWR_STOPENTRY_WFE              : Enter STOP mode with WFE instruction and
  *                                                  clear of pending events before.
  * @retval None.
  */
void HAL_PWR_EnterSTOPMode(uint32_t Regulator, uint8_t StopEntry)
{
  /* Check the parameter */
  assert_param(IS_PWR_REGULATOR(Regulator));
  assert_param(IS_PWR_STOP_ENTRY(StopEntry));

  /* Only Deep Lowpower */
  UNUSED(Regulator);

  /* Select DeepLowPower mode */
  MODIFY_REG(PWR->CR1, PWR_CR1_VR_MODE, PWR_DEEPLOWPOWERREGULATOR_ON);

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  /* Select Stop mode entry */
  if (StopEntry == PWR_STOPENTRY_WFI)
  {
    /* Wait For Interrupt Request */
    __WFI();
  }
  else
  {
    /* Request Wait For Event */
    __SEV();
    __WFE();
    __WFE();
  }

  /* Reset SLEEPDEEP bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));
}


/**
  * @brief Indicates Sleep-On-Exit when returning from Handler mode to Thread mode. 
  * @note Set SLEEPONEXIT bit of SCR register. When this bit is set, the processor 
  *       re-enters SLEEP mode when an interruption handling is over.
  *       Setting this bit is useful when the processor is expected to run only on
  *       interruptions handling.         
  * @retval None
  */
void HAL_PWR_EnableSleepOnExit(void)
{
  /* Set SLEEPONEXIT bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPONEXIT_Msk));
}

/**
  * @brief Disables Sleep-On-Exit feature when returning from Handler mode to Thread mode. 
  * @note Clears SLEEPONEXIT bit of SCR register. When this bit is set, the processor 
  *       re-enters SLEEP mode when an interruption handling is over.          
  * @retval None
  */
void HAL_PWR_DisableSleepOnExit(void)
{
  /* Clear SLEEPONEXIT bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPONEXIT_Msk));
}

/**
  * @brief Enables CORTEX M0+ SEVONPEND bit. 
  * @note Sets SEVONPEND bit of SCR register. When this bit is set, this causes 
  *       WFE to wake up when an interrupt moves from inactive to pended.
  * @retval None
  */
void HAL_PWR_EnableSEVOnPend(void)
{
  /* Set SEVONPEND bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SEVONPEND_Msk));
}

/**
  * @brief Disables CORTEX M0+ SEVONPEND bit. 
  * @note Clears SEVONPEND bit of SCR register. When this bit is set, this causes 
  *       WFE to wake up when an interrupt moves from inactive to pended.         
  * @retval None
  */
void HAL_PWR_DisableSEVOnPend(void)
{
  /* Clear SEVONPEND bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SEVONPEND_Msk));
}

/**
  * @brief  This function handles the PWR PVD interrupt request.
  * @note   This API should be called under the PVD_IRQHandler().
  * @retval None
  */
void HAL_PWR_PVD_IRQHandler(void)
{
  /* Check PWR exti flag */
  if(__HAL_PWR_PVD_EXTI_GET_FLAG() != RESET)
  {
    /* PWR PVD interrupt user callback */
    HAL_PWR_PVDCallback();

    /* Clear PWR Exti pending bit */
    __HAL_PWR_PVD_EXTI_CLEAR_FLAG();
  }
}

/**
  * @brief  PWR PVD interrupt callback
  * @retval None
  */
__weak void HAL_PWR_PVDCallback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PWR_PVDCallback could be implemented in the user file
   */ 
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
