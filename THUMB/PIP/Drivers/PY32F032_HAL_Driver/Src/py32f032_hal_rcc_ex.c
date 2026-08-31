/**
  ******************************************************************************
  * @file    py32f032_hal_rcc_ex.c
  * @author  MCU Application Team
  * @brief   Extended RCC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities RCC extended peripheral:
  *           + Extended Peripheral Control functions
  *           + Extended Clock management functions
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

/** @defgroup RCCEx RCCEx
  * @brief RCC Extended HAL module driver
  * @{
  */

#ifdef HAL_RCC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
#if defined(RCC_PLL_SUPPORT)
static uint32_t RCCEx_GetPLLClockFreq(void);
#endif
/* Exported functions --------------------------------------------------------*/

/** @defgroup RCCEx_Exported_Functions RCCEx Exported Functions
  * @{
  */

/** @defgroup RCCEx_Exported_Functions_Group1 Extended Peripheral Control functions
 *  @brief  Extended Peripheral Control functions
 *
@verbatim
 ===============================================================================
                ##### Extended Peripheral Control functions  #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the RCC Clocks
    frequencies.
    [..]
    (@) Important note: Care must be taken when @ref HAL_RCCEx_PeriphCLKConfig() is used to
        select the RTC clock source; in this case the Backup domain will be reset in
        order to modify the RTC Clock source, as consequence RTC registers (including
        the backup registers) and RCC_BDCR register are set to their reset values.

@endverbatim
  * @{
  */
/**
  * @brief  Initialize the RCC extended peripherals clocks according to the specified
  *         parameters in the @ref RCC_PeriphCLKInitTypeDef.
  * @param  PeriphClkInit  pointer to a @ref RCC_PeriphCLKInitTypeDef structure that
  *         contains a field PeriphClockSelection which can be a combination of the following values:
  *            @arg @ref RCC_PERIPHCLK_RTC  
  *            @arg @ref RCC_PERIPHCLK_IWDG 
  *            @arg @ref RCC_PERIPHCLK_PVD
  *            @arg @ref RCC_PERIPHCLK_COMP1
  *            @arg @ref RCC_PERIPHCLK_COMP2
  *            @arg @ref RCC_PERIPHCLK_LPUART1
  *            @arg @ref RCC_PERIPHCLK_LPTIM1
  *            @arg @ref RCC_PERIPHCLK_TIM1
  *            @arg @ref RCC_PERIPHCLK_TIM17
  *            @arg @ref RCC_PERIPHCLK_ADC
  * @note   (1) Peripherals maybe not available on some devices
  * @note   Care must be taken when @ref HAL_RCCEx_PeriphCLKConfig() is used to select
  *         the RTC clock source: in this case the access to Backup domain is enabled.
  *
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
#if defined(RCC_BDCR_RTCSEL)
  uint32_t tickstart = 0U, temp_reg = 0U;
  FlagStatus       pwrclkchanged = RESET;
#endif
  /* Check the parameters */
  assert_param(IS_RCC_PERIPHCLOCK(PeriphClkInit->PeriphClockSelection));
#if defined(RCC_BDCR_RTCSEL)
  /*------------------------------- RTC Configuration ------------------------*/
  if ((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_RTC) == RCC_PERIPHCLK_RTC))
  {
    /* check for RTC Parameters used to output RTCCLK */
    assert_param(IS_RCC_RTCCLKSOURCE(PeriphClkInit->RtcClockSelection));

    /* As soon as function is called to change RTC clock source, activation of the
       power domain is done. */
    /* Requires to enable write access to Backup Domain of necessary */
    if (__HAL_RCC_PWR_IS_CLK_DISABLED())
    {
      __HAL_RCC_PWR_CLK_ENABLE();
      pwrclkchanged = SET;
    }

    if (HAL_IS_BIT_CLR(PWR->CR1, PWR_CR1_DBP))
    {
      /* Enable write access to Backup domain */
      SET_BIT(PWR->CR1, PWR_CR1_DBP);

      /* Wait for Backup domain Write protection disable */
      tickstart = HAL_GetTick();

      while (HAL_IS_BIT_CLR(PWR->CR1, PWR_CR1_DBP))
      {
        if ((HAL_GetTick() - tickstart) > RCC_DBP_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }

    /* Reset the Backup domain only if the RTC Clock source selection is modified from reset value */
    temp_reg = (RCC->BDCR & RCC_BDCR_RTCSEL);
    if ((temp_reg != 0x00000000U) && (temp_reg != (PeriphClkInit->RtcClockSelection & RCC_BDCR_RTCSEL)))
    {
#if defined(RCC_HSE_SUPPORT)
      /* Store the content of BDCR register before the reset of Backup Domain */
      temp_reg = (RCC->BDCR & ~(RCC_BDCR_RTCSEL | RCC_BDCR_RTC_HSEDIV_SEL));
#else
      /* Store the content of BDCR register before the reset of Backup Domain */
      temp_reg = (RCC->BDCR & ~(RCC_BDCR_RTCSEL));
#endif
      /* RTC Clock selection can be changed only if the Backup Domain is reset */
      __HAL_RCC_BACKUPRESET_FORCE();
      __HAL_RCC_BACKUPRESET_RELEASE();
      /* Restore the Content of BDCR register */
      RCC->BDCR = temp_reg;

#if defined(RCC_LSE_SUPPORT)
      /* Wait for LSERDY if LSE was enabled */
      if (HAL_IS_BIT_SET(temp_reg, RCC_BDCR_LSEON))
      {
        /* Get Start Tick */
        tickstart = HAL_GetTick();

        /* Wait till LSE is ready */
        while (__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) == RESET)
        {
          if ((HAL_GetTick() - tickstart) > RCC_LSE_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
#endif
    }
    __HAL_RCC_RTC_CONFIG(PeriphClkInit->RtcClockSelection);

    /* Require to disable power clock if necessary */
    if (pwrclkchanged == SET)
    {
      __HAL_RCC_PWR_CLK_DISABLE();
    }
  }
#endif /*RCC_BDCR_RTCSEL*/

#if defined(RCC_BDCR_IWDGSEL)
  /*------------------------------- IWDG Configuration ------------------------*/
  if ((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_IWDG) == RCC_PERIPHCLK_IWDG))
  {
    /* check for IWDG Parameters used to output IWDGCLK */
    assert_param(IS_RCC_IWDGCLKSOURCE(PeriphClkInit->IwdgClockSelection));

    FlagStatus       pwrclkchanged = RESET;

    /* As soon as function is called to change RTC clock source, activation of the
       power domain is done. */
    /* Requires to enable write access to Backup Domain of necessary */
    if (__HAL_RCC_PWR_IS_CLK_DISABLED())
    {
      __HAL_RCC_PWR_CLK_ENABLE();
      pwrclkchanged = SET;
    }

    if (HAL_IS_BIT_CLR(PWR->CR1, PWR_CR1_DBP))
    {
      /* Enable write access to Backup domain */
      SET_BIT(PWR->CR1, PWR_CR1_DBP);

      /* Wait for Backup domain Write protection disable */
      tickstart = HAL_GetTick();

      while (HAL_IS_BIT_CLR(PWR->CR1, PWR_CR1_DBP))
      {
        if ((HAL_GetTick() - tickstart) > RCC_DBP_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }

    __HAL_RCC_IWDG_CONFIG(PeriphClkInit->IwdgClockSelection);

    /* Require to disable power clock if necessary */
    if (pwrclkchanged == SET)
    {
      __HAL_RCC_PWR_CLK_DISABLE();
    }
  }
#endif /*RCC_BDCR_IWDGSEL*/
  
  /*------------------------------ PVD clock Configuration ------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_PVD) == RCC_PERIPHCLK_PVD)
  {
    /* Check the parameters */
    assert_param(IS_RCC_PVDDETECTCLKSOURCE(PeriphClkInit->PvdDetectClockSelection));

    /* Configure the PVD detect clock source */
    __HAL_RCC_PVD_CONFIG(PeriphClkInit->PvdDetectClockSelection);
  }
  
#if defined(RCC_CCIPR_COMP1SEL)
  /*-------------------------- COMP1 clock source configuration -------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_COMP1) == RCC_PERIPHCLK_COMP1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_COMP1CLKSOURCE(PeriphClkInit->Comp1ClockSelection));

    /* Configure the COMP1 clock source */
    __HAL_RCC_COMP1_CONFIG(PeriphClkInit->Comp1ClockSelection);
  }
#endif /* RCC_CCIPR_COMP1SEL */

#if defined(RCC_CCIPR_COMP2SEL)
  /*-------------------------- COMP2 clock source configuration -------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_COMP2) == RCC_PERIPHCLK_COMP2)
  {
    /* Check the parameters */
    assert_param(IS_RCC_COMP2CLKSOURCE(PeriphClkInit->Comp2ClockSelection));

    /* Configure the COMP2 clock source */
    __HAL_RCC_COMP2_CONFIG(PeriphClkInit->Comp2ClockSelection);
  }
#endif /* RCC_CCIPR_COMP2SEL */
  
  /*------------------------------ LPUART1 clock Configuration ------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPUART1) == RCC_PERIPHCLK_LPUART1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_LPUART1CLKSOURCE(PeriphClkInit->Lpuart1ClockSelection));

    /* Configure the LPUART1 clock source */
    __HAL_RCC_LPUART1_CONFIG(PeriphClkInit->Lpuart1ClockSelection);
  }
  
  /*------------------------------ LPTIM1 clock Configuration ------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPTIM1) == RCC_PERIPHCLK_LPTIM1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_LPTIM1CLKSOURCE(PeriphClkInit->Lptim1ClockSelection));

    /* Configure the LPTIM1 clock source */
    __HAL_RCC_LPTIM1_CONFIG(PeriphClkInit->Lptim1ClockSelection);
  }
  
  /*------------------------------ TIM1 clock Configuration ------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_TIM1) == RCC_PERIPHCLK_TIM1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_TIM1CLKSOURCE(PeriphClkInit->Tim1ClockSelection));

    /* Configure the TIM1 clock source */
    __HAL_RCC_TIM1_CONFIG(PeriphClkInit->Tim1ClockSelection);
  }
  
  /*------------------------------ TIM17 clock Configuration ------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_TIM17) == RCC_PERIPHCLK_TIM17)
  {
    /* Check the parameters */
    assert_param(IS_RCC_TIM17CLKSOURCE(PeriphClkInit->Tim17ClockSelection));

    /* Configure the TIM17 clock source */
    __HAL_RCC_TIM17_CONFIG(PeriphClkInit->Tim17ClockSelection);
  }
  
  /*------------------------------ ADC clock Configuration ------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_ADC) == RCC_PERIPHCLK_ADC)
  {
    /* Check the parameters */
    assert_param(IS_RCC_ADCCLKSOURCE(PeriphClkInit->AdcClockSelection));

    /* Configure the ADC clock source */
    __HAL_RCC_ADC_CONFIG(PeriphClkInit->AdcClockSelection);
  }
  
  return HAL_OK;
}

/**
  * @brief  Get the RCC_ClkInitStruct according to the internal RCC configuration registers.
  * @param  PeriphClkInit pointer to an RCC_PeriphCLKInitTypeDef structure that
  *         returns the configuration information for the Extended Peripherals
  *         clocks: COMP1, COMP2, RTC, IWDG ...
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripheral availability.
  * @retval None
  */
void HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  /* Set all possible values for the extended clock type parameter------------*/
  PeriphClkInit->PeriphClockSelection = 0;
#if defined(RCC_BDCR_RTCSEL)
  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_RTC;
  /* Get the RTC clock source ------------------------------------------------*/
  PeriphClkInit->RtcClockSelection    = __HAL_RCC_GET_RTC_SOURCE();
#endif /* RCC_BDCR_RTCSEL */
  
#if defined(RCC_BDCR_IWDGSEL)
  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_IWDG;
  /* Get the IWDG clock source ---------------------------------------------*/
  PeriphClkInit->IwdgClockSelection = __HAL_RCC_GET_IWDG_SOURCE();
#endif /* RCC_BDCR_IWDGSEL */
  
#if defined(RCC_CCIPR_PVDSEL)
  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_PVD;
  /* Get the PVD clock source ---------------------------------------------*/
  PeriphClkInit->PvdDetectClockSelection = __HAL_RCC_GET_PVD_DETECT_SOURCE();
#endif /* RCC_CCIPR_PVDSEL */
  
#if defined(RCC_CCIPR_COMP1SEL)
  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_COMP1;
  /* Get the COMP1 clock source --------------------------------------------*/
  PeriphClkInit->Comp1ClockSelection  = __HAL_RCC_GET_COMP1_SOURCE();
#endif /* RCC_CCIPR_COMP1SEL */

#if defined(RCC_CCIPR_COMP2SEL)
  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_COMP2;
  /* Get the COMP2 clock source ---------------------------------------------*/
  PeriphClkInit->Comp2ClockSelection  = __HAL_RCC_GET_COMP2_SOURCE();
#endif /* RCC_CCIPR_COMP2SEL */

#if defined(RCC_CCIPR_LPUART1SEL)
  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_LPUART1;
  /* Get the LPUART1 clock source ---------------------------------------------*/
  PeriphClkInit->Lpuart1ClockSelection = __HAL_RCC_GET_LPUART1_SOURCE();
#endif /* RCC_CCIPR_LPUART1SEL */

#if defined(RCC_CCIPR_LPTIM1SEL)
  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_LPTIM1;
  /* Get the LPTIM1 clock source ---------------------------------------------*/
  PeriphClkInit->Lptim1ClockSelection = __HAL_RCC_GET_LPTIM1_SOURCE();
#endif /* RCC_CCIPR_LPTIM1SEL */

#if defined(RCC_CCIPR_TIM1SEL)
  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_TIM1;
  /* Get the TIM1 clock source ---------------------------------------------*/
  PeriphClkInit->Tim1ClockSelection   = __HAL_RCC_GET_TIM1_SOURCE();
#endif /* RCC_CCIPR_TIM1SEL */

#if defined(RCC_CCIPR_TIM17SEL)
  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_TIM17;
  /* Get the TIM17 clock source ---------------------------------------------*/
  PeriphClkInit->Tim17ClockSelection   = __HAL_RCC_GET_TIM17_SOURCE();
#endif /* RCC_CCIPR_TIM17SEL */

#if defined(RCC_CCIPR_ADCSEL)
  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_ADC;
  /* Get the ADC clock source ---------------------------------------------*/
  PeriphClkInit->AdcClockSelection   = __HAL_RCC_GET_ADC_SOURCE();
#endif /* RCC_CCIPR_ADCSEL */
}

/**
  * @brief  Return the peripheral clock frequency for peripherals with clock source
  * @note   Return 0 if peripheral clock identifier not managed by this API
  * @param  PeriphClk  Peripheral clock identifier
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_PERIPHCLK_RTC     RTC peripheral clock
  *            @arg @ref RCC_PERIPHCLK_IWDG    IWDG peripheral clock
  *            @arg @ref RCC_PERIPHCLK_PVD     PVD peripheral clock
  *            @arg @ref RCC_PERIPHCLK_COMP1   COMP1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_COMP2   COMP2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPUART1 LPUART1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPTIM1  LPTIM1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_TIM1    TIM1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_TIM17   TIM17 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_ADC     ADC peripheral clock
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripheral availability.
  * @retval Frequency in Hz
  */
uint32_t HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk)
{
  uint32_t srcclk = 0U, frequency = 0U, hsiIndex = 0U;
  
  const uint32_t hsiValue[8] = {8000000,0,24000000,0,48000000,0,64000000,72000000};
#if defined(RCC_PLL_SUPPORT)
  uint32_t plldiv = 0U;
  const uint8_t  pllDivValue[2]  = {1,2};
#endif
  /* Check the parameters */
  assert_param(IS_RCC_PERIPHCLOCK(PeriphClk));

#if defined(RCC_BDCR_RTCSEL)
  if (PeriphClk == RCC_PERIPHCLK_RTC)
  {
    /* Get the current RTC source */
    srcclk = __HAL_RCC_GET_RTC_SOURCE();

    /* Check if LSI is ready and if RTC clock selection is LSI */
    if ((HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIRDY)) && (srcclk == RCC_RTCCLKSOURCE_LSI))
    {
      frequency = LSI_VALUE;
    }
#if defined(RCC_LSE_SUPPORT)
    /* Check if LSE is ready and if RTC clock selection is LSE */
    else if ((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY)) && (srcclk == RCC_RTCCLKSOURCE_LSE))
    {
      frequency = LSE_VALUE;
    }
#endif
#if defined(RCC_HSE_SUPPORT)
    /* Check if HSE is ready  and if RTC clock selection is HSE_DIV32*/
    else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSERDY)) &&(srcclk == RCC_RTCCLKSOURCE_HSE_DIV32))
    {
      frequency = HSE_VALUE / 32U;
    }
    /* Check if HSE is ready  and if RTC clock selection is HSE_DIV128*/
    else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSERDY)) &&(srcclk == RCC_RTCCLKSOURCE_HSE_DIV128))
    {
      frequency = HSE_VALUE / 128U;
    }
    /* Check if HSE is ready  and if RTC clock selection is HSE_DIV8*/
    else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSERDY)) &&(srcclk == RCC_RTCCLKSOURCE_HSE_DIV8))
    {
      frequency = HSE_VALUE / 8U;
    }
#endif
    /* Clock not enabled for RTC*/
    else
    {
      /* Nothing to do as frequency already initialized to 0U */
    }
  }
  else
  {
#endif
    /* Other external peripheral clock source than RTC */

    switch (PeriphClk)
    {
#if defined(RCC_BDCR_IWDGSEL)
    case RCC_PERIPHCLK_IWDG:
      /* Get the current IWDG source */
      srcclk = __HAL_RCC_GET_IWDG_SOURCE();

      if ((HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIRDY)) && (srcclk == RCC_IWDGCLKSOURCE_LSI))
      {
        frequency = LSI_VALUE;
      }
#if defined(RCC_LSE_SUPPORT)
      else if ((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY)) && (srcclk == RCC_IWDGCLKSOURCE_LSE))
      {
        frequency = LSE_VALUE;
      }
#endif
      /* Clock not enabled for IWDG */
      else
      {
        /* Nothing to do as frequency already initialized to 0U */
      }
      break;
#endif /* RCC_BDCR_IWDGSEL */
      
    case RCC_PERIPHCLK_PVD:
      /* Get the current PVD source */
      srcclk = __HAL_RCC_GET_PVD_DETECT_SOURCE();
      
      if (srcclk == RCC_PVDDETECTCLKSOURCE_PCLK)
      {
        frequency = HAL_RCC_GetPCLKFreq();
      }
      else if (srcclk == RCC_PVDDETECTCLKSOURCE_LSC)
      {
        if ((HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIRDY)) && (HAL_IS_BIT_CLR(RCC->BDCR, RCC_BDCR_LSCSEL)))
        {
          frequency = LSI_VALUE;
        }
#if defined(RCC_LSE_SUPPORT)
        else if ((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY)) && (HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSCSEL)))
        {
          frequency = LSE_VALUE;
        }
#endif
        else
        {
          /* nothing to do: frequency already initialized to 0 */
        }
      }
      /* Clock not enabled for PVD */
      else
      {
        /* nothing to do: frequency already initialized to 0 */
      }
      break;
      
#if defined(RCC_CCIPR_COMP1SEL)
    case RCC_PERIPHCLK_COMP1:
      /* Get the current COMP1 source */
      srcclk = __HAL_RCC_GET_COMP1_SOURCE();

      if (srcclk == RCC_COMP1CLKSOURCE_PCLK)
      {
        frequency = HAL_RCC_GetPCLKFreq();
      }
      else if ((HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIRDY)) && (HAL_IS_BIT_CLR(RCC->BDCR, RCC_BDCR_LSCSEL)) \
                && (srcclk == RCC_COMP1CLKSOURCE_LSC))
      {
        frequency = LSI_VALUE;
      }
#if defined(RCC_LSE_SUPPORT)
      else if ((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY)) && (HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSCSEL)) \
                && (srcclk == RCC_COMP1CLKSOURCE_LSC))
      {
        frequency = LSE_VALUE;
      }
#endif
      /* Clock not enabled for COMP1 */
      else
      {
        /* Nothing to do as frequency already initialized to 0U */
      }
      break;
#endif

#if defined(RCC_CCIPR_COMP2SEL)
    case RCC_PERIPHCLK_COMP2:
      /* Get the current COMP2 source */
      srcclk = __HAL_RCC_GET_COMP2_SOURCE();

      if (srcclk == RCC_COMP2CLKSOURCE_PCLK)
      {
        frequency = HAL_RCC_GetPCLKFreq();
      }
      else if ((HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIRDY)) && (HAL_IS_BIT_CLR(RCC->BDCR, RCC_BDCR_LSCSEL)) \
                && (srcclk == RCC_COMP2CLKSOURCE_LSC))
      {
        frequency = LSI_VALUE;
      }
#if defined(RCC_LSE_SUPPORT)
      else if ((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY)) && (HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSCSEL)) \
                && (srcclk == RCC_COMP2CLKSOURCE_LSC))
      {
        frequency = LSE_VALUE;
      }
#endif
      /* Clock not enabled for COMP2 */
      else
      {
        /* Nothing to do as frequency already initialized to 0U */
      }
      break;
#endif

    case RCC_PERIPHCLK_LPUART1:
      /* Get the current LPUART1 source */
      srcclk = __HAL_RCC_GET_LPUART1_SOURCE();
      
      if (srcclk == RCC_LPUART1CLKSOURCE_PCLK)
      {
        frequency = HAL_RCC_GetPCLKFreq();
      }
      else if (srcclk == RCC_LPUART1CLKSOURCE_SYSCLK)
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
      else if ((HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIRDY)) && (srcclk == RCC_LPUART1CLKSOURCE_LSI))
      {
        frequency = LSI_VALUE;
      }
#if defined(RCC_LSE_SUPPORT)
      else if ((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY)) && (srcclk == RCC_LPUART1CLKSOURCE_LSE))
      {
        frequency = LSE_VALUE;
      }
#endif
      /* Clock not enabled for LPUART1 */
      else
      {
        /* nothing to do: frequency already initialized to 0 */
      }
      break;
    
    case RCC_PERIPHCLK_LPTIM1:
      /* Get the current LPTIM1 source */
      srcclk = __HAL_RCC_GET_LPTIM1_SOURCE();
      
      if (srcclk == RCC_LPTIM1CLKSOURCE_PCLK)
      {
        frequency = HAL_RCC_GetPCLKFreq();
      }
      else if ((HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIRDY)) && (srcclk == RCC_LPTIM1CLKSOURCE_LSI))
      {
        frequency = LSI_VALUE;
      }
#if defined(RCC_LSE_SUPPORT)
      else if ((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY)) && (srcclk == RCC_LPTIM1CLKSOURCE_LSE))
      {
        frequency = LSE_VALUE;
      }
#endif
      /* Clock not enabled for LPTIM1 */
      else
      {
        /* nothing to do: frequency already initialized to 0 */
      }
      break;
    
    case RCC_PERIPHCLK_TIM1:
      /* Get the current TIM1 source */
      srcclk = __HAL_RCC_GET_TIM1_SOURCE();
      
      if (srcclk == RCC_TIM1CLKSOURCE_PCLK)
      {
        if ((READ_BIT(RCC->CFGR, RCC_CFGR_PPRE) != RCC_HCLK_DIV1) && (__HAL_RCC_GET_TIMPCLK_MUL() != RCC_TIMPCLK_MUL1))
        {
          frequency = (HAL_RCC_GetPCLKFreq() * 0x2);
        }
        else
        {
          frequency = HAL_RCC_GetPCLKFreq();
        }
      }
#if defined(RCC_PLL_SUPPORT)
      else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_PLLRDY)) && (srcclk == RCC_TIM1CLKSOURCE_PLL))
      {
        frequency = RCCEx_GetPLLClockFreq();
      }
#endif
      /* Clock not enabled for TIM1 */
      else
      {
        /* nothing to do: frequency already initialized to 0 */
      }
      break;
    
    case RCC_PERIPHCLK_TIM17:
      /* Get the current TIM17 source */
      srcclk = __HAL_RCC_GET_TIM17_SOURCE();
      
      if (srcclk == RCC_TIM17CLKSOURCE_PCLK)
      {
        if ((READ_BIT(RCC->CFGR, RCC_CFGR_PPRE) != RCC_HCLK_DIV1) && (__HAL_RCC_GET_TIMPCLK_MUL() != RCC_TIMPCLK_MUL1))
        {
          frequency = (HAL_RCC_GetPCLKFreq() * 0x2);
        }
        else
        {
          frequency = HAL_RCC_GetPCLKFreq();
        }
      }
#if defined(RCC_PLL_SUPPORT)
      else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_PLLRDY)) && (srcclk == RCC_TIM17CLKSOURCE_PLL))
      {
        frequency = RCCEx_GetPLLClockFreq();
      }
#endif
      /* Clock not enabled for TIM1 */
      else
      {
        /* nothing to do: frequency already initialized to 0 */
      }
      break;
    
    case RCC_PERIPHCLK_ADC:
      /* Get the current ADC source */
      srcclk = __HAL_RCC_GET_ADC_SOURCE();
      
      if (srcclk == RCC_ADCCLKSOURCE_SYSCLK)
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
#if defined(RCC_PLL_SUPPORT)
      else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_PLLRDY)) && (srcclk == RCC_ADCCLKSOURCE_PLL))
      {
        plldiv = pllDivValue[((RCC->CR & RCC_CR_PLLDIV)>>RCC_CR_PLLDIV_Pos)];
        frequency = RCCEx_GetPLLClockFreq() / plldiv;
      }
#endif
      else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_ADCCLKSOURCE_HSI))
      {
        hsiIndex = (RCC->ICSCR & RCC_ICSCR_HSI_FS_CR_Msk) >> RCC_ICSCR_HSI_FS_CR_Pos;
        frequency = hsiValue[hsiIndex];
      }
      /* Clock not enabled for ADC */
      else
      {
        /* nothing to do: frequency already initialized to 0 */
      }
      break;
    default:
      break;
    }
#if defined(RCC_BDCR_RTCSEL)
  }
#endif
  return (frequency);
}

/**
  * @}
  */

/** @defgroup RCCEx_Exported_Functions_Group2 Extended Clock management functions
 *  @brief  Extended Clock management functions
 *
@verbatim
 ===============================================================================
                ##### Extended clock management functions  #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the
    activation or deactivation of LSE CSS, Low speed clock output and
    clock after wake-up from STOP mode.
@endverbatim
  * @{
  */

/**
  * @brief  Set the Low Speed clock source.
  * @param  LSCSource  specifies the Low Speed clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LSCSOURCE_LSI  LSI clock selected as LSC source
  *            @arg @ref RCC_LSCSOURCE_LSE  LSE clock selected as LSC source
  * @retval None
  */
void HAL_RCCEx_SetLSCSource(uint32_t LSCSource)
{
  FlagStatus       pwrclkchanged = RESET;
  FlagStatus       backupchanged = RESET;
  
  /* Check the parameters */
  assert_param(IS_RCC_LSCSOURCE(LSCSource));

  /* Update LSCSEL clock source in Backup Domain control register */
  if (__HAL_RCC_PWR_IS_CLK_DISABLED())
  {
    __HAL_RCC_PWR_CLK_ENABLE();
    pwrclkchanged = SET;
  }
  if (HAL_IS_BIT_CLR(PWR->CR1, PWR_CR1_DBP))
  {

    HAL_PWR_EnableBkUpAccess();
    backupchanged = SET;
  }

  MODIFY_REG(RCC->BDCR, RCC_BDCR_LSCSEL, LSCSource);

  if (backupchanged == SET)
  {
    HAL_PWR_DisableBkUpAccess();
  }
  if (pwrclkchanged == SET)
  {
    __HAL_RCC_PWR_CLK_DISABLE();
  }
}

/**
  * @brief  Get the Low Speed clock source.
  * @retval Returned value can be one of the following values:
  *         @arg @ref RCC_LSCSOURCE_LSI
  *         @arg @ref RCC_LSCSOURCE_LSE
  */
uint32_t HAL_RCCEx_GetLSCSource(void)
{
  uint32_t         LSCSource;

  LSCSource = READ_BIT(RCC->BDCR, RCC_BDCR_LSCSEL);

  return LSCSource;
}
#if defined(RCC_PLL_SUPPORT)
/**
  * @brief  Returns the PLL clock frequencies.
  * @note   The function returns values based on HSE_VALUE or HSI_VALUE multiplied by the PLL
  *         factors.
  * @note   This function can be used by the user application to compute the
  *         baud-rate for the communication peripherals or configure other parameters.
  * @retval Frequency in Hz
  */
static uint32_t RCCEx_GetPLLClockFreq(void)
{
  uint32_t pllsource = 0, pllmul = 0, pllvco = 0, hsiIndex = 0;
  const uint32_t hsiValue[8] = {8000000,8000000,16000000,22120000,24000000,48000000,64000000,8000000};
  const uint8_t pllMulValue[17] = {2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
    
  pllsource = READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC);
  pllmul = pllMulValue[((RCC->PLLCFGR & RCC_PLLCFGR_PLLMUL)>>RCC_PLLCFGR_PLLMUL_Pos)] ;

  switch (pllsource)
  {
#if defined(RCC_HSE_SUPPORT)
  case RCC_PLLSOURCE_HSE:  /* HSE used as PLL clock source */
    pllvco = (HSE_VALUE * pllmul);
    break;
#endif
  case RCC_PLLSOURCE_HSI:  /* HSI used as PLL clock source */
  default:
    hsiIndex = (RCC->ICSCR & RCC_ICSCR_HSI_FS_CR_Msk) >> RCC_ICSCR_HSI_FS_CR_Pos;
    
    /* HSI used as PLL clock source : PLLCLK = HSI * PLLMUL */
    pllvco = (uint32_t)(hsiValue[hsiIndex] * pllmul);
    break;
  }

  return pllvco;
}
#endif
/**
  * @}
  */


/**
  * @}
  */

#endif /* HAL_RCC_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
