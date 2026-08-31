/**
  ******************************************************************************
  * @file   py32f032_hal_pwr.h
  * @author  MCU Application Team
  * @brief   Header file of PWR HAL module.
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
#ifndef __PY32F032_HAL_PWR_H
#define __PY32F032_HAL_PWR_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f032_hal_def.h"

/** @addtogroup PY32F032_HAL_Driver
  * @{
  */

/** @addtogroup PWR
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup PWR_Exported_Types PWR Exported Types
  * @{
  */ 

/**
  * @brief  PWR PVD configuration structure definition
  */
typedef struct
{
  uint32_t PVDLevel;   /*!< PVDLevel: Specifies the PVD detection level.
                            This parameter can be a value of @ref PWR_PVD_detection_level */
    
  uint32_t PVDFilter;  /*!< PVDFilter: Specifies the PVD Filter.
                            This parameter can be a value of @ref PWR_PVD_Filter */

  uint32_t Mode;       /*!< Mode: Specifies the operating mode for the selected pins.
                            This parameter can be a value of @ref PWR_PVD_Mode */

  uint32_t PVDOutputSelect;  /*!< PVDOutSelect: Specifies output selection of the PVD.
                            This parameter can be a value of @ref PWR_PVD_Output_Select */
}PWR_PVDTypeDef;


/**
  * @}
  */


/* Internal constants --------------------------------------------------------*/

/** @addtogroup PWR_Private_Constants
  * @{
  */ 

#define PWR_EXTI_LINE_PVD  ((uint32_t)0x00010000)  /*!< External interrupt line 16 Connected to the PVD EXTI Line */

/**
  * @}
  */

 
/* Exported constants --------------------------------------------------------*/

/** @defgroup PWR_Exported_Constants PWR Exported Constants
  * @{
  */ 

/** @defgroup PWR_PVD_detection_level PWR PVD detection level
  * @{
  */
#define PWR_PVDLEVEL_0                  0x00000000                                            /* 1.8v */
#define PWR_PVDLEVEL_1                  (                                  PWR_CR2_PVDT_0)    /* 2.0v */
#define PWR_PVDLEVEL_2                  (                 PWR_CR2_PVDT_1                 )    /* 2.2v */
#define PWR_PVDLEVEL_3                  (                 PWR_CR2_PVDT_1 | PWR_CR2_PVDT_0)    /* 2.4v */
#define PWR_PVDLEVEL_4                  (PWR_CR2_PVDT_2                                  )    /* 2.6v */
#define PWR_PVDLEVEL_5                  (PWR_CR2_PVDT_2                  | PWR_CR2_PVDT_0)    /* 2.8v */
#define PWR_PVDLEVEL_6                  (PWR_CR2_PVDT_2 | PWR_CR2_PVDT_1                 )    /* 3.0v */
#define PWR_PVDLEVEL_7                  (PWR_CR2_PVDT_2 | PWR_CR2_PVDT_1 | PWR_CR2_PVDT_0)    /* 3.2v */
                                                          
/**
  * @}
  */
  
/** @defgroup PWR_PVD_Filter PWR PVD Filter
  * @{
  */
#define PWR_PVD_FILTER_NONE               0x00000000U
#define PWR_PVD_FILTER_1CLOCK             (PWR_CR2_FLTEN)
#define PWR_PVD_FILTER_2CLOCK             (PWR_CR2_FLTEN | PWR_CR2_FLT_TIME_0)
#define PWR_PVD_FILTER_4CLOCK             (PWR_CR2_FLTEN | PWR_CR2_FLT_TIME_1)
#define PWR_PVD_FILTER_16CLOCK            (PWR_CR2_FLTEN | PWR_CR2_FLT_TIME_0 | PWR_CR2_FLT_TIME_1)
#define PWR_PVD_FILTER_64CLOCK            (PWR_CR2_FLTEN | PWR_CR2_FLT_TIME_2)
#define PWR_PVD_FILTER_128CLOCK           (PWR_CR2_FLTEN | PWR_CR2_FLT_TIME_0 | PWR_CR2_FLT_TIME_2)
#define PWR_PVD_FILTER_1024CLOCK          (PWR_CR2_FLTEN | PWR_CR2_FLT_TIME_1 | PWR_CR2_FLT_TIME_2)  
/**
  * @}
  */

/** @defgroup PWR_PVD_Output_Select PWR PVD Output Select
  * @{
  */
#define PWR_PVD_OUT_NOT_SYN_FILTER        0x00000000U
#define PWR_PVD_OUT_SYN_FILTER            (PWR_CR2_PVD_OUT_SEL)
/**
  * @}
  */

/** @defgroup PWR_PVD_Mode PWR PVD Mode
  * @{
  */
#define PWR_PVD_MODE_NORMAL                 0x00000000U   /*!< basic mode is used */
#define PWR_PVD_MODE_IT_RISING              0x00010001U   /*!< External Interrupt Mode with Rising edge trigger detection */
#define PWR_PVD_MODE_IT_FALLING             0x00010002U   /*!< External Interrupt Mode with Falling edge trigger detection */
#define PWR_PVD_MODE_IT_RISING_FALLING      0x00010003U   /*!< External Interrupt Mode with Rising/Falling edge trigger detection */
#define PWR_PVD_MODE_EVENT_RISING           0x00020001U   /*!< Event Mode with Rising edge trigger detection */
#define PWR_PVD_MODE_EVENT_FALLING          0x00020002U   /*!< Event Mode with Falling edge trigger detection */
#define PWR_PVD_MODE_EVENT_RISING_FALLING   0x00020003U   /*!< Event Mode with Rising/Falling edge trigger detection */

/**
  * @}
  */

/** @defgroup PWR_Regulator_state_in_SLEEP_STOP_mode PWR Regulator state in STOP mode
  * @{
  */
#define PWR_MAINREGULATOR_ON                        0x00000000U       
#define PWR_LOWPOWERREGULATOR_ON                    PWR_CR1_VR_MODE_0    /*!< Regulator in low-power mode */
#define PWR_DEEPLOWPOWERREGULATOR_ON                PWR_CR1_VR_MODE_1    /*!< Regulator in deep-low-power mode */

/**
  * @}
  */

/** @defgroup PWR_SLEEP_mode_entry PWR SLEEP mode entry
  * @{
  */
#define PWR_SLEEPENTRY_WFI              ((uint8_t)0x01)
#define PWR_SLEEPENTRY_WFE              ((uint8_t)0x02)

/**
  * @}
  */

/** @defgroup PWR_STOP_mode_entry PWR STOP mode entry
  * @{
  */
#define PWR_STOPENTRY_WFI               ((uint8_t)0x01)
#define PWR_STOPENTRY_WFE               ((uint8_t)0x02)

/**
  * @}
  */

/** @defgroup PWR_STANDBY_mode_entry PWR STOP mode entry
  * @{
  */
#define PWR_STANDBYENTRY_WFI               ((uint8_t)0x01)
#define PWR_STANDBYENTRY_WFE               ((uint8_t)0x02)

/**
  * @}
  */

/** @defgroup PWR_Flag PWR Flag
  * @{
  */
#define PWR_FLAG_MR_RDY                 PWR_SR_MR_RDY
#define PWR_FLAG_LPRUN_RUN_RDY          PWR_SR_LPRUN2RUN_RDY
#define PWR_FLAG_PVDO                   PWR_SR_PVDO
/**
  * @}
  */

/** @defgroup PWR_Mode PWR Mode
  * @{
  */
#define PWR_MODE_RUN               0x00000000
#define PWR_MODE_LPRUN             PWR_CR1_LPMS

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup PWR_Exported_Macros  PWR Exported Macros
  * @{
  */
/** @brief  Check whether or not a specific PWR flag is set.
  * @param  __FLAG__: specifies the flag to check.
  *           This parameter can be one of the following values:
  *            @arg @ref PWR_FLAG_MR_RDY MR ready flag. Indicates whether or not the
  *                 MR is ready.
  *            @arg @ref PWR_FLAG_LPRUN_RUN_RDY The flag for switching between LPRUN and RUN.
  *            @arg @ref PWR_FLAG_PVDO Power Voltage Detector Output. Indicates whether VCC voltage is
  *                  below or above the selected PVD threshold.
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_PWR_GET_FLAG(__FLAG__) ((PWR->SR & (__FLAG__)) == (__FLAG__))

/**
  * @brief Enable interrupt on PVD Exti Line 16.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_IT()      SET_BIT(EXTI->IMR, PWR_EXTI_LINE_PVD)

/**
  * @brief Disable interrupt on PVD Exti Line 16. 
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_IT()     CLEAR_BIT(EXTI->IMR, PWR_EXTI_LINE_PVD)

/**
  * @brief Enable event on PVD Exti Line 16.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_EVENT()   SET_BIT(EXTI->EMR, PWR_EXTI_LINE_PVD)

/**
  * @brief Disable event on PVD Exti Line 16.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_EVENT()  CLEAR_BIT(EXTI->EMR, PWR_EXTI_LINE_PVD)


/**
  * @brief  PVD EXTI line configuration: set falling edge trigger.  
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE()  SET_BIT(EXTI->FTSR, PWR_EXTI_LINE_PVD)


/**
  * @brief Disable the PVD Extended Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE()  CLEAR_BIT(EXTI->FTSR, PWR_EXTI_LINE_PVD)


/**
  * @brief  PVD EXTI line configuration: set rising edge trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE()   SET_BIT(EXTI->RTSR, PWR_EXTI_LINE_PVD)

/**
  * @brief Disable the PVD Extended Interrupt Rising Trigger.
  * This parameter can be:
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE()  CLEAR_BIT(EXTI->RTSR, PWR_EXTI_LINE_PVD)

/**
  * @brief  PVD EXTI line configuration: set rising & falling edge trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_RISING_FALLING_EDGE()   __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE();__HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE();

/**
  * @brief Disable the PVD Extended Interrupt Rising & Falling Trigger.
  * This parameter can be:
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_RISING_FALLING_EDGE()  __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE();__HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE();



/**
  * @brief Check whether the specified PVD EXTI interrupt flag is set or not.
  * @retval EXTI PVD Line Status.
  */
#define __HAL_PWR_PVD_EXTI_GET_FLAG()       (EXTI->PR & (PWR_EXTI_LINE_PVD))

/**
  * @brief Clear the PVD EXTI flag.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_CLEAR_FLAG()     (EXTI->PR = (PWR_EXTI_LINE_PVD))

/**
  * @brief Generate a Software interrupt on selected EXTI line.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_GENERATE_SWIT()  SET_BIT(EXTI->SWIER, PWR_EXTI_LINE_PVD)
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/** @defgroup PWR_Private_Macros PWR Private Macros
  * @{
  */
#define IS_PWR_PVD_LEVEL(LEVEL) (((LEVEL) == PWR_PVDLEVEL_0) || ((LEVEL) == PWR_PVDLEVEL_1)|| \
                                 ((LEVEL) == PWR_PVDLEVEL_2) || ((LEVEL) == PWR_PVDLEVEL_3)|| \
                                 ((LEVEL) == PWR_PVDLEVEL_4) || ((LEVEL) == PWR_PVDLEVEL_5)|| \
                                 ((LEVEL) == PWR_PVDLEVEL_6) || ((LEVEL) == PWR_PVDLEVEL_7))


#define IS_PWR_PVD_MODE(MODE) (((MODE) == PWR_PVD_MODE_IT_RISING)|| ((MODE) == PWR_PVD_MODE_IT_FALLING) || \
                              ((MODE) == PWR_PVD_MODE_IT_RISING_FALLING) || ((MODE) == PWR_PVD_MODE_EVENT_RISING) || \
                              ((MODE) == PWR_PVD_MODE_EVENT_FALLING) || ((MODE) == PWR_PVD_MODE_EVENT_RISING_FALLING) || \
                              ((MODE) == PWR_PVD_MODE_NORMAL)) 
                              
#define IS_PWR_PVD_FILTER(FILTER) (((FILTER) == PWR_PVD_FILTER_NONE) || ((FILTER) == PWR_PVD_FILTER_1CLOCK)|| \
                                 ((FILTER) == PWR_PVD_FILTER_2CLOCK) || ((FILTER) == PWR_PVD_FILTER_4CLOCK)|| \
                                 ((FILTER) == PWR_PVD_FILTER_16CLOCK) || ((FILTER) == PWR_PVD_FILTER_64CLOCK)|| \
                                 ((FILTER) == PWR_PVD_FILTER_128CLOCK) || ((FILTER) == PWR_PVD_FILTER_1024CLOCK))

#define IS_PWR_PVD_OUTPUT_SELECT(OUTPUT) (((OUTPUT) == PWR_PVD_OUT_NOT_SYN_FILTER) || \
                                          ((OUTPUT) == PWR_PVD_OUT_SYN_FILTER))


#define IS_PWR_REGULATOR(REGULATOR) (((REGULATOR) == PWR_MAINREGULATOR_ON) || \
                                     ((REGULATOR) == PWR_LOWPOWERREGULATOR_ON) || \
                                     ((REGULATOR) == PWR_DEEPLOWPOWERREGULATOR_ON))

#define IS_PWR_SLEEP_ENTRY(ENTRY) (((ENTRY) == PWR_SLEEPENTRY_WFI) || ((ENTRY) == PWR_SLEEPENTRY_WFE))

#define IS_PWR_STOP_ENTRY(ENTRY) (((ENTRY) == PWR_STOPENTRY_WFI) || ((ENTRY) == PWR_STOPENTRY_WFE))

/**
  * @}
  */

/* Include PWR HAL Extension module */
#include "py32f032_hal_pwr_ex.h"


/* Exported functions --------------------------------------------------------*/

/** @addtogroup PWR_Exported_Functions PWR Exported Functions
  * @{
  */
  
/** @addtogroup PWR_Exported_Functions_Group1 Initialization and de-initialization functions 
  * @{
  */

/* Initialization and de-initialization functions *******************************/
void HAL_PWR_DeInit(void);
void HAL_PWR_EnableBkUpAccess(void);
void HAL_PWR_DisableBkUpAccess(void);

/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group2 Peripheral Control functions 
  * @{
  */

/* Peripheral Control functions  ************************************************/
void HAL_PWR_ConfigPVD(PWR_PVDTypeDef *sConfigPVD);
void HAL_PWR_EnablePVD(void);
void HAL_PWR_DisablePVD(void);


/* Low Power modes configuration functions ************************************/
void HAL_PWR_EnterSLEEPMode(uint32_t Regulator, uint8_t SLEEPEntry);
void HAL_PWR_EnterSTOPMode(uint32_t Regulator, uint8_t STOPEntry);

void HAL_PWR_EnableSleepOnExit(void);
void HAL_PWR_DisableSleepOnExit(void);
void HAL_PWR_EnableSEVOnPend(void);
void HAL_PWR_DisableSEVOnPend(void);

void HAL_PWR_PVD_IRQHandler(void);
void HAL_PWR_PVDCallback(void);
/**
  * @}
  */

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


#endif /* __PY32F032_HAL_PWR_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
