/**
  ******************************************************************************
  * @file    py32f032_ll_system.h
  * @author  MCU Application Team
  * @brief   Header file of SYSTEM LL module.
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
#ifndef PY32F032_LL_SYSTEM_H
#define PY32F032_LL_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f0xx.h"

/** @addtogroup PY32F032_LL_Driver
  * @{
  */

#if defined (FLASH) || defined (SYSCFG) || defined (DBGMCU) || defined (VREFBUF)

/** @defgroup SYSTEM_LL SYSTEM
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Private_Constants SYSTEM Private Constants
  * @{
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Exported_Constants SYSTEM Exported Constants
  * @{
  */

/** @defgroup SYSTEM_LL_EC_REMAP SYSCFG REMAP
  * @{
  */
#define LL_SYSCFG_REMAP_FLASH               0x00000000U                                           /*!< Main Flash memory mapped at 0x00000000 */
#define LL_SYSCFG_REMAP_SYSTEMFLASH         SYSCFG_CFGR1_MEM_MODE_0                               /*!< System Flash memory mapped at 0x00000000 */
#define LL_SYSCFG_REMAP_SRAM                (SYSCFG_CFGR1_MEM_MODE_1 | SYSCFG_CFGR1_MEM_MODE_0)   /*!< Embedded SRAM mapped at 0x00000000 */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_TIMBREAK SYSCFG TIMER BREAK
  * @{
  */

#if defined(SYSCFG_CFGR2_PVDL)
#define LL_SYSCFG_TIMBREAK_PVD             SYSCFG_CFGR2_PVDL  /*!< Enables and locks the PVD connection 
                                                                   with TIM1/16/17 Break Input 
                                                                   and also the PVDE and PLS bits of the Power Control Interface */
#endif

#if defined(SYSCFG_CFGR2_CLL)
#define LL_SYSCFG_TIMBREAK_LOCKUP          SYSCFG_CFGR2_CLL   /*!< Enables and locks the LOCKUP output of CortexM0 
                                                                   with Break Input of TIM1/16/17                             */
#endif
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_DMA_MAP DMA MAP
  * @{
  */
#define LL_SYSCFG_DMA_MAP_ADC               0x00000000U
#define LL_SYSCFG_DMA_MAP_SPI1_RX           0x00000003U
#define LL_SYSCFG_DMA_MAP_SPI1_TX           0x00000004U
#define LL_SYSCFG_DMA_MAP_SPI2_RX           0x00000005U
#define LL_SYSCFG_DMA_MAP_SPI2_TX           0x00000006U
#define LL_SYSCFG_DMA_MAP_USART1_RX         0x00000007U
#define LL_SYSCFG_DMA_MAP_USART1_TX         0x00000008U
#define LL_SYSCFG_DMA_MAP_UART1_RX          0x0000000BU
#define LL_SYSCFG_DMA_MAP_UART1_TX          0x0000000CU
#define LL_SYSCFG_DMA_MAP_LPUART1_RX        0x0000000DU
#define LL_SYSCFG_DMA_MAP_LPUART1_TX        0x0000000EU
#define LL_SYSCFG_DMA_MAP_I2C1_RX           0x0000000FU
#define LL_SYSCFG_DMA_MAP_I2C1_TX           0x00000010U
#define LL_SYSCFG_DMA_MAP_TIM1_CH1          0x00000013U
#define LL_SYSCFG_DMA_MAP_TIM1_CH2          0x00000014U
#define LL_SYSCFG_DMA_MAP_TIM1_CH3          0x00000015U
#define LL_SYSCFG_DMA_MAP_TIM1_CH4          0x00000016U
#define LL_SYSCFG_DMA_MAP_TIM1_COM          0x00000017U
#define LL_SYSCFG_DMA_MAP_TIM1_TRG          0x00000018U
#define LL_SYSCFG_DMA_MAP_TIM1_UP           0x00000019U
#define LL_SYSCFG_DMA_MAP_TIM3_CH1          0x00000020U
#define LL_SYSCFG_DMA_MAP_TIM3_CH2          0x00000021U
#define LL_SYSCFG_DMA_MAP_TIM3_CH3          0x00000022U
#define LL_SYSCFG_DMA_MAP_TIM3_CH4          0x00000023U
#define LL_SYSCFG_DMA_MAP_TIM3_UP           0x00000024U
#define LL_SYSCFG_DMA_MAP_TIM3_TRG          0x00000025U
#define LL_SYSCFG_DMA_MAP_TIM16_CH1         0x0000002DU
#define LL_SYSCFG_DMA_MAP_TIM16_UP          0x0000002EU
#define LL_SYSCFG_DMA_MAP_TIM17_CH1         0x0000002FU
#define LL_SYSCFG_DMA_MAP_TIM17_UP          0x00000030U
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_GPIO_PORT GPIO PORT
  * @{
  */
#define LL_SYSCFG_GPIO_PORTA              0x00000000U
#define LL_SYSCFG_GPIO_PORTB              0x00000001U
#define LL_SYSCFG_GPIO_PORTF              0x00000002U
/**
  * @}
  */
  
/** @defgroup SYSTEM_LL_EC_GPIO_PIN GPIO PIN
  * @{
  */
#define LL_SYSCFG_GPIO_PIN_0              0x00000001U
#define LL_SYSCFG_GPIO_PIN_1              0x00000002U
#define LL_SYSCFG_GPIO_PIN_2              0x00000004U
#define LL_SYSCFG_GPIO_PIN_3              0x00000008U
#define LL_SYSCFG_GPIO_PIN_4              0x00000010U
#define LL_SYSCFG_GPIO_PIN_5              0x00000020U
#define LL_SYSCFG_GPIO_PIN_6              0x00000040U
#define LL_SYSCFG_GPIO_PIN_7              0x00000080U
#define LL_SYSCFG_GPIO_PIN_8              0x00000100U
#define LL_SYSCFG_GPIO_PIN_9              0x00000200U
#define LL_SYSCFG_GPIO_PIN_10             0x00000400U
#define LL_SYSCFG_GPIO_PIN_11             0x00000800U
#define LL_SYSCFG_GPIO_PIN_12             0x00001000U
#define LL_SYSCFG_GPIO_PIN_13             0x00002000U
#define LL_SYSCFG_GPIO_PIN_14             0x00004000U
#define LL_SYSCFG_GPIO_PIN_15             0x00008000U
/**
  * @}
  */


  
/** @defgroup SYSTEM_LL_GPIO_SEL GPIO SEL
  * @{
  */
#define LL_SYSCFG_GPIO_SEL_FASTIO          0x00000000U 
#define LL_SYSCFG_GPIO_SEL_AHB             SYSCFG_CFGR1_GPIO_AHB_SEL
/**
  * @}
  */

/** @defgroup SYSCFG_LL_EHS  PIN EHS
  * @{
  */
#define LL_SYSCFG_EHS_PA15      SYSCFG_IOCFG_PA_EHS
#define LL_SYSCFG_EHS_PB3       SYSCFG_IOCFG_PB_EHS_0
#define LL_SYSCFG_EHS_PB4       SYSCFG_IOCFG_PB_EHS_1
#define LL_SYSCFG_EHS_PB5       SYSCFG_IOCFG_PB_EHS_2

/**
  * @}
  */

/** @defgroup SYSCFG_LL_PU_IIC I2C PIN PULL-UP
  * @{
  */
#define LL_SYSCFG_PU_IIC_PB7    SYSCFG_IOCFG_PB_PU_EIIC_0
#define LL_SYSCFG_PU_IIC_PB8    SYSCFG_IOCFG_PB_PU_EIIC_1
/**
  * @}
  */
  
#if defined(VREFBUF)
/** @defgroup SYSCFG_LL_VREFBUF_VoltageScale VREFBUF Voltage Scale
  * @{
  */
#define LL_VREFBUF_Voltage_1P024V         0x00000000UL                                                    /* Vrefbuf 1.024V */  
#define LL_VREFBUF_Voltage_1P5V           VREFBUF_CR_VREFBUF_OUT_SEL_0                                    /* Vrefbuf 1.5V */  
#define LL_VREFBUF_Voltage_2P048V         VREFBUF_CR_VREFBUF_OUT_SEL_1                                    /* Vrefbuf 2.048V */  
/**
  * @}
  */
#endif
  
/** @defgroup SYSTEM_LL_EC_LATENCY FLASH LATENCY
  * @{
  */
#define LL_FLASH_LATENCY_0                 0x00000000UL                                  /*!< FLASH Zero wait state */
#define LL_FLASH_LATENCY_1                 FLASH_ACR_LATENCY_0                           /*!< FLASH One wait state */
#define LL_FLASH_LATENCY_2                 FLASH_ACR_LATENCY_1                           /*!< FLASH Two wait state */
#define LL_FLASH_LATENCY_3                 (FLASH_ACR_LATENCY_0 | FLASH_ACR_LATENCY_1)   /*!< FLASH Four wait state */
/**
  * @}
  */
  
/** @defgroup SYSTEM_LL_EC_STOP_IP  DBGMCU STOP IP
  * @{
  */
#if defined(DBGMCU_APB_FZ1_DBG_TIM1_STOP)
#define LL_DBGMCU_APB1_GRP1_TIM1_STOP                  DBGMCU_APB_FZ1_DBG_TIM1_STOP
#endif

#if defined(DBGMCU_APB_FZ1_DBG_TIM3_STOP)
#define LL_DBGMCU_APB1_GRP1_TIM3_STOP                  DBGMCU_APB_FZ1_DBG_TIM3_STOP
#endif

#if defined(DBGMCU_APB_FZ1_DBG_RTC_STOP)
#define LL_DBGMCU_APB1_GRP1_RTC_STOP                   DBGMCU_APB_FZ1_DBG_RTC_STOP
#endif
  
#if defined(DBGMCU_APB_FZ1_DBG_WWDG_STOP)
#define LL_DBGMCU_APB1_GRP1_WWDG_STOP                  DBGMCU_APB_FZ1_DBG_WWDG_STOP
#endif
  
#if defined(DBGMCU_APB_FZ1_DBG_IWDG_STOP)
#define LL_DBGMCU_APB1_GRP1_IWDG_STOP                  DBGMCU_APB_FZ1_DBG_IWDG_STOP
#endif

#if defined(DBGMCU_APB_FZ1_DBG_LPTIM1_STOP)
#define LL_DBGMCU_APB1_GRP1_LPTIM1_STOP                DBGMCU_APB_FZ1_DBG_LPTIM1_STOP
#endif
  
#if defined(DBGMCU_APB_FZ2_DBG_TIM14_STOP)
#define LL_DBGMCU_APB1_GRP2_TIM14_STOP                 DBGMCU_APB_FZ2_DBG_TIM14_STOP
#endif

#if defined(DBGMCU_APB_FZ2_DBG_TIM16_STOP)
#define LL_DBGMCU_APB1_GRP2_TIM16_STOP                 DBGMCU_APB_FZ2_DBG_TIM16_STOP
#endif

#if defined(DBGMCU_APB_FZ2_DBG_TIM17_STOP)
#define LL_DBGMCU_APB1_GRP2_TIM17_STOP                 DBGMCU_APB_FZ2_DBG_TIM17_STOP
#endif

/**
  * @}
  */

/**
  * @}
  */
/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Exported_Functions SYSTEM Exported Functions
  * @{
  */

/** @defgroup SYSTEM_LL_EF_SYSCFG SYSCFG
  * @{
  */

/**
  * @brief  Set FASTIO or AHB to access the GPIO register control
  * @rmtoll SYSCFG_CFGR1 GPIO_AHB_SEL      LL_SYSCFG_SetGPIOAccess
  * @param  GPIOSel This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_GPIO_SEL_FASTIO
  *         @arg @ref LL_SYSCFG_GPIO_SEL_AHB
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetGPIOAccess(uint32_t GPIOSel)
{
  MODIFY_REG(SYSCFG->CFGR1, SYSCFG_CFGR1_GPIO_AHB_SEL, GPIOSel);
}

/**
  * @brief  Get FASTIO or AHB to access the GPIO register control
  * @rmtoll SYSCFG_CFGR1 GPIO_AHB_SEL      LL_SYSCFG_GetGPIOAccess
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_GPIO_SEL_FASTIO
  *         @arg @ref LL_SYSCFG_GPIO_SEL_AHB
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetGPIOAccess(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_GPIO_AHB_SEL));
}  

/**
  * @brief  Set memory mapping at address 0x00000000
  * @rmtoll SYSCFG_CFGR1 MEM_MODE      LL_SYSCFG_SetRemapMemory
  * @param  Memory This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_REMAP_FLASH
  *         @arg @ref LL_SYSCFG_REMAP_SYSTEMFLASH
  *         @arg @ref LL_SYSCFG_REMAP_SRAM
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetRemapMemory(uint32_t Memory)
{
  MODIFY_REG(SYSCFG->CFGR1, SYSCFG_CFGR1_MEM_MODE, Memory);
}

/**
  * @brief  Get memory mapping at address 0x00000000
  * @rmtoll SYSCFG_CFGR1 MEM_MODE      LL_SYSCFG_GetRemapMemory
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_REMAP_FLASH
  *         @arg @ref LL_SYSCFG_REMAP_SYSTEMFLASH
  *         @arg @ref LL_SYSCFG_REMAP_SRAM
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetRemapMemory(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_MEM_MODE));
}

/**
  * @brief  Set connections to TIM1/16/17 Break inputs
  * @rmtoll SYSCFG_CFGR2 CLL           LL_SYSCFG_SetTIMBreakInputs\n
  *         SYSCFG_CFGR2 PVDL          LL_SYSCFG_SetTIMBreakInputs
  * @param  Break This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_TIMBREAK_PVD
  *         @arg @ref LL_SYSCFG_TIMBREAK_LOCKUP
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetTIMBreakInputs(uint32_t Break)
{
  MODIFY_REG(SYSCFG->CFGR2, SYSCFG_CFGR2_CLL | SYSCFG_CFGR2_PVDL, Break);
}

/**
  * @brief  Get connections to TIM1/16/17 Break inputs
  * @rmtoll SYSCFG_CFGR2 CLL           LL_SYSCFG_GetTIMBreakInputs\n
  *         SYSCFG_CFGR2 PVDL          LL_SYSCFG_GetTIMBreakInputs
  * @retval Returned value can be can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_TIMBREAK_PVD
  *         @arg @ref LL_SYSCFG_TIMBREAK_LOCKUP
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetTIMBreakInputs(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_CLL | SYSCFG_CFGR2_PVDL));
}

/**
  * @brief  Enable GPIO Filter
  * @note   Depending on devices and packages, some IOs may not be available.
  *         Refer to device datasheet for IOs availability.
  * @param  GPIOPort This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_GPIO_PORTA
  *         @arg @ref LL_SYSCFG_GPIO_PORTB
  *         @arg @ref LL_SYSCFG_GPIO_PORTF
  * @param  GPIOPin This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_GPIO_PIN_0
  *         @arg @ref LL_SYSCFG_GPIO_PIN_1
  *         @arg @ref LL_SYSCFG_GPIO_PIN_2
  *         @arg @ref LL_SYSCFG_GPIO_PIN_3
  *         @arg @ref LL_SYSCFG_GPIO_PIN_4
  *         @arg @ref LL_SYSCFG_GPIO_PIN_5
  *         @arg @ref LL_SYSCFG_GPIO_PIN_6
  *         @arg @ref LL_SYSCFG_GPIO_PIN_7
  *         @arg @ref LL_SYSCFG_GPIO_PIN_8
  *         @arg @ref LL_SYSCFG_GPIO_PIN_9
  *         @arg @ref LL_SYSCFG_GPIO_PIN_10
  *         @arg @ref LL_SYSCFG_GPIO_PIN_11
  *         @arg @ref LL_SYSCFG_GPIO_PIN_12
  *         @arg @ref LL_SYSCFG_GPIO_PIN_13
  *         @arg @ref LL_SYSCFG_GPIO_PIN_14
  *         @arg @ref LL_SYSCFG_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableGPIOFilter(uint32_t GPIOPort, uint32_t GPIOPin)
{
  if(GPIOPort == LL_SYSCFG_GPIO_PORTA)
  {
    SET_BIT(SYSCFG->PA_ENS, GPIOPin);
  }
  else if(GPIOPort == LL_SYSCFG_GPIO_PORTB)
  {
    SET_BIT(SYSCFG->PB_ENS, GPIOPin);
  }
  else if(GPIOPort == LL_SYSCFG_GPIO_PORTF)
  {    
    SET_BIT(SYSCFG->PF_ENS, GPIOPin);
  }
  else
  {
    
  }
}

/**
  * @brief  Disable GPIO Filter
  * @note   Depending on devices and packages, some IOs may not be available.
  *         Refer to device datasheet for IOs availability.
  * @param  GPIOPort This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_GPIO_PORTA
  *         @arg @ref LL_SYSCFG_GPIO_PORTB
  *         @arg @ref LL_SYSCFG_GPIO_PORTF
  * @param  GPIOPin This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_GPIO_PIN_0
  *         @arg @ref LL_SYSCFG_GPIO_PIN_1
  *         @arg @ref LL_SYSCFG_GPIO_PIN_2
  *         @arg @ref LL_SYSCFG_GPIO_PIN_3
  *         @arg @ref LL_SYSCFG_GPIO_PIN_4
  *         @arg @ref LL_SYSCFG_GPIO_PIN_5
  *         @arg @ref LL_SYSCFG_GPIO_PIN_6
  *         @arg @ref LL_SYSCFG_GPIO_PIN_7
  *         @arg @ref LL_SYSCFG_GPIO_PIN_8
  *         @arg @ref LL_SYSCFG_GPIO_PIN_9
  *         @arg @ref LL_SYSCFG_GPIO_PIN_10
  *         @arg @ref LL_SYSCFG_GPIO_PIN_11
  *         @arg @ref LL_SYSCFG_GPIO_PIN_12
  *         @arg @ref LL_SYSCFG_GPIO_PIN_13
  *         @arg @ref LL_SYSCFG_GPIO_PIN_14
  *         @arg @ref LL_SYSCFG_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableGPIOFilter(uint32_t GPIOPort, uint32_t GPIOPin)
{
  if(GPIOPort == LL_SYSCFG_GPIO_PORTA)
  {
    CLEAR_BIT(SYSCFG->PA_ENS, GPIOPin);
  }
  else if(GPIOPort == LL_SYSCFG_GPIO_PORTB)
  {
    CLEAR_BIT(SYSCFG->PB_ENS, GPIOPin);
  }
  else if(GPIOPort == LL_SYSCFG_GPIO_PORTF)
  {    
    CLEAR_BIT(SYSCFG->PF_ENS, GPIOPin);
  }
  else
  {
    
  }
}

/**
  * @brief  Check if GPIO Filter is enabled
  * @param  GPIOPort This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_GPIO_PORTA
  *         @arg @ref LL_SYSCFG_GPIO_PORTB
  *         @arg @ref LL_SYSCFG_GPIO_PORTF
  * @param  GPIOPin This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_GPIO_PIN_0
  *         @arg @ref LL_SYSCFG_GPIO_PIN_1
  *         @arg @ref LL_SYSCFG_GPIO_PIN_2
  *         @arg @ref LL_SYSCFG_GPIO_PIN_3
  *         @arg @ref LL_SYSCFG_GPIO_PIN_4
  *         @arg @ref LL_SYSCFG_GPIO_PIN_5
  *         @arg @ref LL_SYSCFG_GPIO_PIN_6
  *         @arg @ref LL_SYSCFG_GPIO_PIN_7
  *         @arg @ref LL_SYSCFG_GPIO_PIN_8
  *         @arg @ref LL_SYSCFG_GPIO_PIN_9
  *         @arg @ref LL_SYSCFG_GPIO_PIN_10
  *         @arg @ref LL_SYSCFG_GPIO_PIN_11
  *         @arg @ref LL_SYSCFG_GPIO_PIN_12
  *         @arg @ref LL_SYSCFG_GPIO_PIN_13
  *         @arg @ref LL_SYSCFG_GPIO_PIN_14
  *         @arg @ref LL_SYSCFG_GPIO_PIN_15
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledGPIOFilter(uint32_t GPIOPort, uint32_t GPIOPin)
{
  uint32_t temp = 0;
  
  if(GPIOPort == LL_SYSCFG_GPIO_PORTA)
  {
    temp = READ_BIT(SYSCFG->PA_ENS, GPIOPin);
  }
  else if(GPIOPort == LL_SYSCFG_GPIO_PORTB)
  {
    temp = READ_BIT(SYSCFG->PB_ENS, GPIOPin);
  }
  else if(GPIOPort == LL_SYSCFG_GPIO_PORTF)
  {    
    temp = READ_BIT(SYSCFG->PF_ENS, GPIOPin);
  }
  else
  {
    
  }
  
  return ((temp == (GPIOPin)) ? 1U:0U);
}

/**
  * @brief  Enable I2C pin pull-up.
  * @param  PORT_Pin specifies the pin
  *         This parameter can be any combination of the following values:
  *            @arg LL_SYSCFG_PU_IIC_PB7
  *            @arg LL_SYSCFG_PU_IIC_PB8
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableI2CPinPullUp(uint32_t PORT_Pin)
{
  SET_BIT(SYSCFG->IOCFG, PORT_Pin);
}

/**
  * @brief  Disable I2C pin pull-up.
  * @param  PORT_Pin specifies the pin
  *         This parameter can be any combination of the following values:
  *            @arg LL_SYSCFG_PU_IIC_PB7
  *            @arg LL_SYSCFG_PU_IIC_PB8
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableI2CPinPullUp(uint32_t PORT_Pin)
{
  CLEAR_BIT(SYSCFG->IOCFG, PORT_Pin);
}

/**
  * @brief  Check if I2C pin pull-up is enabled
  * @param  PORT_Pin specifies the pin
  *         This parameter can be one of the following values:
  *            @arg LL_SYSCFG_PU_IIC_PB7
  *            @arg LL_SYSCFG_PU_IIC_PB8
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledI2CPinPullUp(uint32_t PORT_Pin)
{
  return ((READ_BIT(SYSCFG->IOCFG, PORT_Pin) == (PORT_Pin)) ? 1UL : 0UL);
}

/**
  * @brief  Enable EHS
  * @param  PORT_Pin specifies the pin
  *         This parameter can be any combination of the following values:
  *            @arg LL_SYSCFG_EHS_PA15
  *            @arg LL_SYSCFG_EHS_PB3
  *            @arg LL_SYSCFG_EHS_PB4
  *            @arg LL_SYSCFG_EHS_PB5
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableEHS(uint32_t PORT_Pin)
{
  SET_BIT(SYSCFG->IOCFG, PORT_Pin);
}

/**
  * @brief  Disable EHS
  * @param  PORT_Pin specifies the pin
  *         This parameter can be any combination of the following values:
  *            @arg LL_SYSCFG_EHS_PA15
  *            @arg LL_SYSCFG_EHS_PB3
  *            @arg LL_SYSCFG_EHS_PB4
  *            @arg LL_SYSCFG_EHS_PB5
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableEHS(uint32_t PORT_Pin)
{
  CLEAR_BIT(SYSCFG->IOCFG, PORT_Pin);
}

/**
  * @brief  Check if EHS is enabled
  * @param  PORT_Pin specifies the pin
  *         This parameter can be one of the following values:
  *            @arg LL_SYSCFG_EHS_PA15
  *            @arg LL_SYSCFG_EHS_PB3
  *            @arg LL_SYSCFG_EHS_PB4
  *            @arg LL_SYSCFG_EHS_PB5
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledEHS(uint32_t PORT_Pin)
{
  return ((READ_BIT(SYSCFG->IOCFG, PORT_Pin) == (PORT_Pin)) ? 1UL : 0UL);
}

/**
  * @brief  Enable IIC1 Filter
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableIIC1Filter()
{
  SET_BIT(SYSCFG->IOCFG, SYSCFG_IOCFG_I2C1_FILTEN);
}

/**
  * @brief  Disable IIC1 Filter
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableIIC1Filter()
{
  CLEAR_BIT(SYSCFG->IOCFG, SYSCFG_IOCFG_I2C1_FILTEN);
}

/**
  * @brief  Check if IIC1 Filter is enabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledIIC1Filter()
{
  return ((READ_BIT(SYSCFG->IOCFG, SYSCFG_IOCFG_I2C1_FILTEN) == (SYSCFG_IOCFG_I2C1_FILTEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable GPIO Analog2
  * @note   Depending on devices and packages, some IOs may not be available.
  *         Refer to device datasheet for IOs availability.
  * @param  GPIOPort This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_GPIO_PORTA
  * @param  GPIOPin This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_GPIO_PIN_9
  *         @arg @ref LL_SYSCFG_GPIO_PIN_10
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableGPIOAnalog2(uint32_t GPIOPort, uint32_t GPIOPin) 
{
  if(GPIOPort == LL_SYSCFG_GPIO_PORTA)
  {
    SET_BIT(SYSCFG->PA_ANA2EN, GPIOPin);
  }
  else
  {
    
  }
}

/**
  * @brief  Disable GPIO Filter
  * @note   Depending on devices and packages, some IOs may not be available.
  *         Refer to device datasheet for IOs availability.
  * @param  GPIOPort This parameter can be a one of the following values:
  *         @arg @ref LL_SYSCFG_GPIO_PORTA
  * @param  GPIOPin This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_GPIO_PIN_9
  *         @arg @ref LL_SYSCFG_GPIO_PIN_10
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableGPIOAnalog2(uint32_t GPIOPort, uint32_t GPIOPin) 
{
  if(GPIOPort == LL_SYSCFG_GPIO_PORTA)
  {
    CLEAR_BIT(SYSCFG->PA_ANA2EN, GPIOPin);
  }
  else
  {
    
  }
}

/**
  * @brief  Check if GPIO Analog2 is enabled
  * @note   Depending on devices and packages, some IOs may not be available.
  *         Refer to device datasheet for IOs availability.
  * @param  GPIOPort This parameter can be a one of the following values:
  *         @arg @ref LL_SYSCFG_GPIO_PORTA
  * @param  GPIOPin This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_GPIO_PIN_9
  *         @arg @ref LL_SYSCFG_GPIO_PIN_10
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledGPIOAnalog2(uint32_t GPIOPort, uint32_t GPIOPin) 
{
  uint32_t temp = 0;
  
  if(GPIOPort == LL_SYSCFG_GPIO_PORTA)
  {
    temp = READ_BIT(SYSCFG->PA_ANA2EN, GPIOPin);
  }
  else
  {
    
  }
  
  return ((temp == (GPIOPin)) ? 1U:0U);
}


/** @defgroup SYSTEM_LL_EF_FLASH FLASH
  * @{
  */

/**
  * @brief  Set FLASH Latency
  * @rmtoll FLASH_ACR    LATENCY       LL_FLASH_SetLatency
  * @param  Latency This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_LATENCY_0
  *         @arg @ref LL_FLASH_LATENCY_1
  *         @arg @ref LL_FLASH_LATENCY_2
  *         @arg @ref LL_FLASH_LATENCY_3
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetLatency(uint32_t Latency)
{
  MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, Latency);
}

/**
  * @brief  Get FLASH Latency
  * @rmtoll FLASH_ACR    LATENCY       LL_FLASH_GetLatency
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_LATENCY_0
  *         @arg @ref LL_FLASH_LATENCY_1
  *         @arg @ref LL_FLASH_LATENCY_2
  *         @arg @ref LL_FLASH_LATENCY_3
  */
__STATIC_INLINE uint32_t LL_FLASH_GetLatency(void)
{
  return (uint32_t)(READ_BIT(FLASH->ACR, FLASH_ACR_LATENCY));
}

/**
  * @}
  */

/** @defgroup SYSTEM_LL_EF_DBGMCU DBGMCU
  * @{
  */

/**
  * @brief  Return the identifier
  * @retval Values between Min_Data=0x00 and Max_Data=0xFFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_DBGMCU_GetRevisionID(void)
{
  return (uint32_t)(READ_BIT(DBGMCU->IDCODE, DBGMCU_IDCODE_DBG_ID));
}

/**
  * @brief  Enable the Debug Module during SLEEP mode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_EnableDBGSleepMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP);
}

/**
  * @brief  Disable the Debug Module during SLEEP mode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_DisableDBGSleepMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP);
}

/**
  * @brief  Indicate if enable the Debug Module during SLEEP mode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_IsEnabledDBGSleepMode(void)
{
  return ((READ_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP) == (DBGMCU_CR_DBG_SLEEP)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the Debug Module during STOP mode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_EnableDBGStopMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Disable the Debug Module during STOP mode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_DisableDBGStopMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Indicate if enable the Debug Module during STOP mode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_IsEnabledDBGStopMode(void)
{
  return ((READ_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP) == (DBGMCU_CR_DBG_STOP)) ? 1UL : 0UL);
}

/**
  * @brief  Freeze APB1 peripherals (group1 peripherals)
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM3_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_RTC_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_WWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_IWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_LPTIM1_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP1_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->APBFZ1, Periphs);
}

/**
  * @brief  Unfreeze APB1 peripherals (group1 peripherals)
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM3_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_RTC_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_WWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_IWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_LPTIM1_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP1_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->APBFZ1, Periphs);
}

/**
  * @brief  Indicate if Freeze APB1 peripherals (group1 peripherals)
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @param  Periphs This parameter can be one of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM3_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_RTC_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_WWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_IWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_LPTIM1_STOP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_APB1_GRP1_IsFreezePeriph(uint32_t Periphs)
{
  return ((READ_BIT(DBGMCU->APBFZ1, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Freeze APB1 peripherals(group2 peripherals)
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM14_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM16_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM17_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP2_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->APBFZ2, Periphs);
}

/**
  * @brief  Unfreeze APB1 peripherals(group2 peripherals)
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM14_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM16_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM17_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP2_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->APBFZ2, Periphs);
}

/**
  * @brief  Indicate if Freeze APB1 peripherals (group2 peripherals)
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @param  Periphs This parameter can be one of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM14_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM16_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_TIM17_STOP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_APB1_GRP2_IsFreezePeriph(uint32_t Periphs)
{
  return ((READ_BIT(DBGMCU->APBFZ2, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @}
  */
/** @defgroup SYSTEM_LL_EF_VREFBUF VREFBUF
  * @{
  */
#if defined(VREFBUF)

/**
  * @brief  Enable the Internal Voltage Reference buffer (VREFBUF).
  * @retval None
  */
__STATIC_INLINE void LL_VREFBUF_Enable(void)
{
  SET_BIT(VREFBUF->CR, VREFBUF_CR_VREFBUF_EN);
}

/**
  * @brief  Disable the Internal Voltage Reference buffer (VREFBUF).
  * @retval None
  */
__STATIC_INLINE void LL_VREFBUF_Disable(void)
{
  CLEAR_BIT(VREFBUF->CR, VREFBUF_CR_VREFBUF_EN);
}

/**
  * @brief  Check if enable the Internal Voltage Reference buffer (VREFBUF).
  * @retval None
  */
__STATIC_INLINE uint32_t LL_VREFBUF_IsEnabled(void)
{
  return ((READ_BIT(VREFBUF->CR, VREFBUF_CR_VREFBUF_EN) == (VREFBUF_CR_VREFBUF_EN)) ? 1UL : 0UL);
}

/**
  * @brief  Configure the Internal Voltage Reference buffer (VREFBUF).
  * @param  Voltage specifies the vrebuf voltage level
  *         This parameter can be any combination of the following values:
  *            @arg LL_VREFBUF_Voltage_1P024V
  *            @arg LL_VREFBUF_Voltage_1P5V  
  *            @arg LL_VREFBUF_Voltage_2P048V
  * @retval None
  */
__STATIC_INLINE void LL_VREFBUF_SetVrefbufVoltage(uint32_t Voltage)
{
  MODIFY_REG(VREFBUF->CR, VREFBUF_CR_VREFBUF_OUT_SEL, Voltage);
}

/**
  * @brief  Get the Internal Voltage Reference buffer (VREFBUF).
  * @retval Returned value can be one of the following values:
  *            @arg LL_VREFBUF_Voltage_1P024V
  *            @arg LL_VREFBUF_Voltage_1P5V  
  *            @arg LL_VREFBUF_Voltage_2P048V 
  */
__STATIC_INLINE uint32_t LL_VREFBUF_GetVrefbufVoltage(void)
{
  return (uint32_t)(READ_BIT(VREFBUF->CR, VREFBUF_CR_VREFBUF_OUT_SEL));
}

#endif /* VREFBUF */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#endif /* defined (FLASH) || defined (SYSCFG) || defined (DBGMCU) || defined (VREFBUF) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* PY32F032_LL_SYSTEM_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
