/**
  ******************************************************************************
  * @file    py32f0xx_hal.h
  * @author  MCU Application Team
  * @brief   This file contains all the functions prototypes for the HAL
  *          module driver.
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
#ifndef __PY32F0XX_HAL_H
#define __PY32F0XX_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f032_hal_conf.h"

/** @addtogroup PY32F032_HAL_Driver
  * @{
  */

/** @addtogroup HAL
  * @{
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup HAL_Exported_Constants HAL Exported Constants
  * @{
  */

/** @defgroup HAL_TICK_FREQ Tick Frequency
  * @{
  */
typedef enum
{
  HAL_TICK_FREQ_10HZ         = 100U,
  HAL_TICK_FREQ_100HZ        = 10U,
  HAL_TICK_FREQ_1KHZ         = 1U,
  HAL_TICK_FREQ_DEFAULT      = HAL_TICK_FREQ_1KHZ
} HAL_TickFreqTypeDef;
/**
  * @}
  */

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/
/** @addtogroup HAL_Exported_Variables
  * @{
  */
extern uint32_t uwTickPrio;
extern uint32_t uwTickFreq;
/**
  * @}
  */

/** @defgroup SYSCFG_Exported_Constants SYSCFG Exported Constants
  * @{
  */

/** @defgroup SYSCFG_BootMode Boot Mode
  * @{
  */
#define SYSCFG_BOOT_MAINFLASH            0x00000000U                      /*!< Main Flash memory mapped at 0x0000 0000   */
#define SYSCFG_BOOT_SYSTEMFLASH          SYSCFG_CFGR1_MEM_MODE_0          /*!< System Flash memory mapped at 0x0000 0000 */
#define SYSCFG_BOOT_SRAM                 (SYSCFG_CFGR1_MEM_MODE_1 | SYSCFG_CFGR1_MEM_MODE_0)  /*!< Embedded SRAM mapped at 0x0000 0000 */
/**
  * @}
  */

/** @defgroup SYSTEM_GPIO_FASTIO_SEL GPIO Fast IO  Select
  * @{
  */
#define SYSCFG_GPIO_FASTIO_SEL   0x00000000U
#define SYSCFG_GPIO_AHB_SEL      SYSCFG_CFGR1_GPIO_AHB_SEL
/**
  * @}
  */

/** @defgroup SYSCFG_Break Break
  * @{
  */
#define SYSCFG_BREAK_PVD               SYSCFG_CFGR2_PVDL   /*!< Enables and locks the PVD connection with TIM1/16/17 Break Input and also the PVDE bits of the Power Control Interface */
#define SYSCFG_BREAK_LOCKUP            SYSCFG_CFGR2_CLL    /*!< Enables and locks the LOCKUP output of CortexM0+ with Break Input of TIM1/16/17 */
/**
  * @}
  */

/** @defgroup SYSCFG_PU_IIC I2C PIN PULL-UP
  * @{
  */
#define SYSCFG_PU_IIC_PB7    SYSCFG_IOCFG_PB_PU_EIIC_0
#define SYSCFG_PU_IIC_PB8    SYSCFG_IOCFG_PB_PU_EIIC_1
/**
  * @}
  */

/** @defgroup SYSCFG_LED_EHS LED Pin High Driver Single
  * @{
  */
#define SYSCFG_EHS_PA15      SYSCFG_IOCFG_PA_EHS
#define SYSCFG_EHS_PB3       SYSCFG_IOCFG_PB_EHS_0
#define SYSCFG_EHS_PB4       SYSCFG_IOCFG_PB_EHS_1
#define SYSCFG_EHS_PB5       SYSCFG_IOCFG_PB_EHS_2

/**
  * @}
  */

#if defined(VREFBUF)
/** @defgroup SYSCFG_VREFBUF_VoltageScale VREFBUF Voltage Scale
  * @{
  */
#define SYSCFG_VREFBUF_1P024V         (VREFBUF_CR_VREFBUF_EN)                                                                   /* Vrefbuf 1.024V */  
#define SYSCFG_VREFBUF_1P5V           (VREFBUF_CR_VREFBUF_EN | VREFBUF_CR_VREFBUF_OUT_SEL_0)                                    /* Vrefbuf 1.5V */  
#define SYSCFG_VREFBUF_2P048V         (VREFBUF_CR_VREFBUF_EN | VREFBUF_CR_VREFBUF_OUT_SEL_1)                                    /* Vrefbuf 2.048V */  
/**
  * @}
  */
#endif

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup HAL_Exported_Macros HAL Exported Macros
  * @{
  */

/** @defgroup HAL_Freeze_Unfreeze_Peripherals HAL Freeze Unfreeze Peripherals
  * @brief  Freeze/Unfreeze Peripherals in Debug mode
  * @{
  */
#if defined(DBGMCU_APB_FZ1_DBG_TIM1_STOP)
#define __HAL_DBGMCU_FREEZE_TIM1_STOP()            (DBGMCU->APBFZ1 |= (DBGMCU_APB_FZ1_DBG_TIM1_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM1_STOP()          (DBGMCU->APBFZ1 &= ~(DBGMCU_APB_FZ1_DBG_TIM1_STOP))
#endif /* DBGMCU_APB_FZ_DBG_TIM1_STOP */

#if defined(DBGMCU_APB_FZ1_DBG_TIM3_STOP)
#define __HAL_DBGMCU_FREEZE_TIM3_STOP()            (DBGMCU->APBFZ1 |= (DBGMCU_APB_FZ1_DBG_TIM3_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM3_STOP()          (DBGMCU->APBFZ1 &= ~(DBGMCU_APB_FZ1_DBG_TIM3_STOP))
#endif /* DBGMCU_APB_FZ_DBG_TIM3_STOP */

#if defined(DBGMCU_APB_FZ1_DBG_RTC_STOP)
#define __HAL_DBGMCU_FREEZE_RTC_STOP()            (DBGMCU->APBFZ1 |= (DBGMCU_APB_FZ1_DBG_RTC_STOP))
#define __HAL_DBGMCU_UNFREEZE_RTC_STOP()          (DBGMCU->APBFZ1 &= ~(DBGMCU_APB_FZ1_DBG_RTC_STOP))
#endif /* DBGMCU_APB_FZ_DBG_RTC_STOP */

#if defined(DBGMCU_APB_FZ1_DBG_IWDG_STOP)
#define __HAL_DBGMCU_FREEZE_IWDG_STOP()            (DBGMCU->APBFZ1 |= (DBGMCU_APB_FZ1_DBG_IWDG_STOP))
#define __HAL_DBGMCU_UNFREEZE_IWDG_STOP()          (DBGMCU->APBFZ1 &= ~(DBGMCU_APB_FZ1_DBG_IWDG_STOP))
#endif /* DBGMCU_APB_FZ_DBG_IWDG_STOP */

#if defined(DBGMCU_APB_FZ1_DBG_WWDG_STOP)
#define __HAL_DBGMCU_FREEZE_WWDG_STOP()            (DBGMCU->APBFZ1 |= (DBGMCU_APB_FZ1_DBG_WWDG_STOP))
#define __HAL_DBGMCU_UNFREEZE_WWDG_STOP()          (DBGMCU->APBFZ1 &= ~(DBGMCU_APB_FZ1_DBG_WWDG_STOP))
#endif /* DBGMCU_APB_FZ_DBG_WWDG_STOP */

#if defined(DBGMCU_APB_FZ1_DBG_LPTIM1_STOP)
#define __HAL_DBGMCU_FREEZE_LPTIM1_STOP()            (DBGMCU->APBFZ1 |= (DBGMCU_APB_FZ1_DBG_LPTIM1_STOP))
#define __HAL_DBGMCU_UNFREEZE_LPTIM1_STOP()          (DBGMCU->APBFZ1 &= ~(DBGMCU_APB_FZ1_DBG_LPTIM1_STOP))
#endif /* DBGMCU_APB_FZ_DBG_LPTIM1_STOP */

#if defined(DBGMCU_APB_FZ2_DBG_TIM14_STOP)
#define __HAL_DBGMCU_FREEZE_TIM14_STOP()            (DBGMCU->APBFZ2 |= (DBGMCU_APB_FZ2_DBG_TIM14_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM14_STOP()          (DBGMCU->APBFZ2 &= ~(DBGMCU_APB_FZ2_DBG_TIM14_STOP))
#endif /* DBGMCU_APB_FZ_DBG_TIM14_STOP */

#if defined(DBGMCU_APB_FZ2_DBG_TIM16_STOP)
#define __HAL_DBGMCU_FREEZE_TIM16_STOP()            (DBGMCU->APBFZ2 |= (DBGMCU_APB_FZ2_DBG_TIM16_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM16_STOP()          (DBGMCU->APBFZ2 &= ~(DBGMCU_APB_FZ2_DBG_TIM16_STOP))
#endif /* DBGMCU_APB_FZ_DBG_TIM16_STOP */

#if defined(DBGMCU_APB_FZ2_DBG_TIM17_STOP)
#define __HAL_DBGMCU_FREEZE_TIM17_STOP()            (DBGMCU->APBFZ2 |= (DBGMCU_APB_FZ2_DBG_TIM17_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM17_STOP()          (DBGMCU->APBFZ2 &= ~(DBGMCU_APB_FZ2_DBG_TIM17_STOP))
#endif /* DBGMCU_APB_FZ_DBG_TIM17_STOP */

/**
  * @}
  */

/** @defgroup SYSCFG_Exported_Macros SYSCFG Exported Macros
  * @{
  */

/** @brief  SYSCFG Break Cortex-M0+ Lockup lock.
  *         Enables and locks the connection of Cortex-M0+ LOCKUP (Hardfault) output to TIM1/16/17 Break input
  * @note   The selected configuration is locked and can be unlocked only by system reset.
  */
#define __HAL_SYSCFG_BREAK_LOCKUP_LOCK()        SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_CLL)

#if defined(SYSCFG_CFGR2_PVDL)
/** @brief  SYSCFG Break PVD lock.
  *         Enables and locks the PVD connection with TIM1/16/17 Break input, as well as the PVDE in the PWR_CR register
  * @note   The selected configuration is locked and can be unlocked only by system reset
  */
#define __HAL_SYSCFG_BREAK_PVD_LOCK()           SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_PVDL)
#endif

/** @brief  Enable CPU AHB bus Access To GPIO Register.
  * @note   The default configuration is CPU FASTIO after reset.
  */
#if defined(SYSCFG_CFGR1_GPIO_AHB_SEL)
#define __HAL_SYSCFG_GPIO_AHB()                 SET_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_GPIO_AHB_SEL)
#endif

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup HAL_Private_Macros HAL Private Macros
  * @{
  */
#define IS_TICKFREQ(FREQ) (((FREQ) == HAL_TICK_FREQ_10HZ)  || \
                           ((FREQ) == HAL_TICK_FREQ_100HZ) || \
                           ((FREQ) == HAL_TICK_FREQ_1KHZ))
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @addtogroup HAL_Exported_Functions
  * @{
  */

/** @addtogroup HAL_Exported_Functions_Group1
  * @{
  */

/* Initialization and de-initialization functions  ******************************/
HAL_StatusTypeDef HAL_Init(void);
HAL_StatusTypeDef HAL_DeInit(void);
void HAL_MspInit(void);
void HAL_MspDeInit(void);
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority);
/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group2
  * @{
  */
/* Peripheral Control functions  ************************************************/
void HAL_IncTick(void);
void HAL_Delay(uint32_t Delay);
uint32_t HAL_GetTick(void);
uint32_t HAL_GetTickPrio(void);
HAL_StatusTypeDef HAL_SetTickFreq(uint32_t Freq);
uint32_t HAL_GetTickFreq(void);
void HAL_SuspendTick(void);
void HAL_ResumeTick(void);
uint32_t HAL_GetHalVersion(void);
uint32_t HAL_GetDBGID(void);
/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group3
  * @{
  */
/* HAL Debug functions  *********************************************************/
#if defined(DBGMCU_CR_DBG_SLEEP)
void HAL_DBGMCU_EnableDBGMCUSleepMode(void);
void HAL_DBGMCU_DisableDBGMCUSleepMode(void);
#endif
#if defined(DBGMCU_CR_DBG_STOP)
void HAL_DBGMCU_EnableDBGMCUStopMode(void);
void HAL_DBGMCU_DisableDBGMCUStopMode(void);
#endif
/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group4
  * @{
  */
/* SYSCFG configuration functions  **********************************************/
void HAL_SYSCFG_SetRemapMemory(uint32_t Memory);
uint32_t HAL_SYSCFG_GetRemapMemory(void);
void HAL_SYSCFG_EnableGPIOAnalog2(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin);
void HAL_SYSCFG_DisableGPIOAnalog2(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin);
void HAL_SYSCFG_EnableI2CPinPullUp(uint32_t PORT_Pin);
void HAL_SYSCFG_DisableI2CPinPullUp(uint32_t PORT_Pin);
void HAL_SYSCFG_EnableIIC1Filter(void);
void HAL_SYSCFG_DisableIIC1Filter(void);
#if defined(VREFBUF)
void HAL_SYSCFG_EnableVREFBUF(void);
void HAL_SYSCFG_DisableVREFBUF(void);
void HAL_SYSCFG_VREFBUFConfig(uint32_t Vrefbuf);
#endif

/**
  * @}
  */

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @defgroup HAL_Private_Variables HAL Private Variables
  * @{
  */
/**
  * @}
  */
/* Private constants ---------------------------------------------------------*/
/** @defgroup HAL_Private_Constants HAL Private Constants
  * @{
  */
/**
  * @}
  */
/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __PY32F0XX_HAL_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
