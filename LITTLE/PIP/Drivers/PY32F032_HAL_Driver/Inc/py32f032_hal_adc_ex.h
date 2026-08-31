/**
  ******************************************************************************
  * @file    py32f032_hal_adc_ex.h
  * @author  MCU Application Team
  * @brief   Header file of ADC HAL extended module.
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
#ifndef PY32F032_HAL_ADC_EX_H
#define PY32F032_HAL_ADC_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f032_hal_def.h"

/** @addtogroup PY32F032_HAL_Driver
  * @{
  */

/** @addtogroup ADCEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup ADCEx_Exported_Types ADC Extended Exported Types
  * @{
  */
/**
  * @brief  Structure definition of ADC group injected and ADC channel affected to ADC group injected
  * @note   Parameters of this structure are shared within 2 scopes:
  *          - Scope channel: InjectedChannel, InjectedRank, InjectedSamplingTime ,
  *          - Scope ADC group injected (affects all channels of injected group): InjectedNbrOfConversion,
  *            InjectedDiscontinuousConvMode,
  *            AutoInjectedConv, ExternalTrigInjecConv, ExternalTrigInjecConvEdge,
  * @note   The setting of these parameters by function HAL_ADCEx_InjectedConfigChannel() is conditioned to ADC state.
  *         ADC state can be either:
  *          - For parameters 'InjectedDiscontinuousConvMode': ADC enabled
  *            without conversion on going on injected group.
  *          - For parameters 'InjectedSamplingTime','AutoInjectedConv': ADC enabled without conversion on going on regular and
  *            injected groups.
  *          - For parameters 'InjectedChannel', 'InjectedRank', 'InjectedNbrOfConversion', 'ExternalTrigInjecConv',
  *            'ExternalTrigInjecConvEdge': ADC enabled and while conversion on going
  *            on ADC groups regular and injected.
  *         If ADC is not in the appropriate state to modify some parameters, these parameters setting is bypassed
  *         without error reporting (as it can be the expected behavior in case of intended action to update another
  *         parameter (which fulfills the ADC state condition) on the fly).
  */
typedef struct
{
  uint32_t InjectedChannel;               /*!< Specifies the channel to configure into ADC group injected.
                                               This parameter can be a value of @ref ADC_HAL_EC_CHANNEL
                                               Note: Depending on devices and ADC instances, some channels may not be
                                                     available on device package pins. Refer to device datasheet for
                                                     channels availability. */

  uint32_t InjectedRank;                  /*!< Specifies the rank in the ADC group injected sequencer.
                                               This parameter must be a value of @ref ADC_INJ_SEQ_RANKS.
                                               Note: to disable a channel or change order of conversion sequencer,
                                                     rank containing a previous channel setting can be overwritten by
                                                     the new channel setting (or parameter number of conversions
                                                     adjusted) */

  uint32_t InjectedSamplingTime;          /*!< Sampling time value to be set for the selected channel.
                                               Unit: ADC clock cycles.
                                               Conversion time is the addition of sampling time and processing time
                                               (12.5 ADC clock cycles at ADC resolution 12 bits, 10.5 cycles at 10 bits,
                                               8.5 cycles at 8 bits, 6.5 cycles at 6 bits).
                                               This parameter can be a value of @ref ADC_HAL_EC_CHANNEL_SAMPLINGTIME.
                                               Caution: This parameter applies to a channel that can be used in a
                                                        regular and/or injected group. It overwrites the last setting.
                                               Note: In case of usage of internal measurement channels (VrefInt, ...),
                                                     sampling time constraints must be respected (sampling time can be
                                                     adjusted in function of ADC clock frequency and sampling time
                                                     setting). Refer to device datasheet for timings values. */


  uint32_t InjectedNbrOfConversion;       /*!< Specifies the number of ranks that will be converted within the ADC group
                                               injected sequencer.
                                               To use the injected group sequencer and convert several ranks, parameter
                                               'ScanConvMode' must be enabled.
                                               This parameter must be a number between Min_Data = 1 and Max_Data = 4.
                                               Caution: this setting impacts the entire injected group. Therefore,
                                               call of HAL_ADCEx_InjectedConfigChannel() to configure a channel on
                                               injected group can impact the configuration of other channels previously
                                               set. */

  FunctionalState InjectedDiscontinuousConvMode; /*!< Specifies whether the conversions sequence of ADC group injected
                                               is performed in Complete-sequence/Discontinuous-sequence
                                               (main sequence subdivided in successive parts).
                                               Discontinuous mode is used only if sequencer is enabled (parameter
                                               'ScanConvMode'). If sequencer is disabled, this parameter is discarded.
                                               Discontinuous mode can be enabled only if continuous mode is disabled.
                                               This parameter can be set to ENABLE or DISABLE.
                                               Note: This parameter must be modified when ADC is disabled (before ADC
                                               start conversion or after ADC stop conversion).
                                               Note: For injected group, discontinuous mode converts the sequence
                                               channel by channel (discontinuous length fixed to 1 rank).
                                               Caution: this setting impacts the entire injected group. Therefore,
                                                        call of HAL_ADCEx_InjectedConfigChannel() to
                                                        configure a channel on injected group can impact the
                                                        configuration of other channels previously set. */

  FunctionalState AutoInjectedConv;       /*!< Enables or disables the selected ADC group injected automatic conversion
                                               after regular one
                                               This parameter can be set to ENABLE or DISABLE.
                                               Note: To use Automatic injected conversion, discontinuous mode must
                                                     be disabled ('DiscontinuousConvMode' and
                                                     'InjectedDiscontinuousConvMode' set to DISABLE)
                                               Note: To use Automatic injected conversion, injected group external
                                                     triggers must be disabled ('ExternalTrigInjecConv' set to
                                                     ADC_INJECTED_SOFTWARE_START)
                                               Note: In case of DMA used with regular group: if DMA configured in
                                                     normal mode (single shot) JAUTO will be stopped upon DMA transfer
                                                     complete.
                                                     To maintain JAUTO always enabled, DMA must be configured in
                                                     circular mode.
                                               Caution: this setting impacts the entire injected group. Therefore,
                                                        call of HAL_ADCEx_InjectedConfigChannel() to configure a channel
                                                        on injected group can impact the configuration of other channels
                                                        previously set. */

  uint32_t ExternalTrigInjecConv;         /*!< Selects the external event used to trigger the conversion start of
                                               injected group.
                                               If set to ADC_INJECTED_SOFTWARE_START, external triggers are disabled
                                               and software trigger is used instead.
                                               This parameter can be a value of
                                               @ref ADC_injected_external_trigger_source.
                                               Caution: this setting impacts the entire injected group. Therefore,
                                                        call of HAL_ADCEx_InjectedConfigChannel() to configure a channel
                                                        on injected group can impact the configuration of other channels
                                                        previously set. */

  uint32_t ExternalTrigInjecConvEdge;     /*!< Selects the external trigger edge of injected group.
                                               This parameter can be a value of @ref ADC_injected_external_trigger_edge.
                                               If trigger source is set to ADC_INJECTED_SOFTWARE_START, this parameter
                                               is discarded.
                                               Caution: this setting impacts the entire injected group. Therefore,
                                                        call of HAL_ADCEx_InjectedConfigChannel() to
                                                        configure a channel on injected group can impact the
                                                        configuration of other channels previously set. */

} ADC_InjectionConfTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup ADCEx_Exported_Constants ADC Extended Exported Constants
  * @{
  */

/** @defgroup ADC_injected_external_trigger_source ADC group injected trigger source
  * @{
  */
/* ADC group regular trigger sources for all ADC instances */
#define ADC_INJECTED_SOFTWARE_START          (LL_ADC_INJ_TRIG_SOFTWARE)            /*!< ADC group injected conversion
                                           trigger software start */

#define ADC_EXTERNALTRIGINJEC_T1_TRGO        (LL_ADC_INJ_TRIG_EXT_TIM1_TRGO   )  
#define ADC_EXTERNALTRIGINJEC_T1_CC1         (LL_ADC_INJ_TRIG_EXT_TIM1_CH1    )  
#define ADC_EXTERNALTRIGINJEC_T1_CC2         (LL_ADC_INJ_TRIG_EXT_TIM1_CH2    )  
#define ADC_EXTERNALTRIGINJEC_T1_CC3         (LL_ADC_INJ_TRIG_EXT_TIM1_CH3    )  
#define ADC_EXTERNALTRIGINJEC_T1_CC4         (LL_ADC_INJ_TRIG_EXT_TIM1_CH4    )  
#define ADC_EXTERNALTRIGINJEC_T1_CC5         (LL_ADC_INJ_TRIG_EXT_TIM1_CH5   )  
#define ADC_EXTERNALTRIGINJEC_T1_CC6         (LL_ADC_INJ_TRIG_EXT_TIM1_CH6    )  
#define ADC_EXTERNALTRIGINJEC_T3_CC1         (LL_ADC_INJ_TRIG_EXT_TIM3_CH1    )  
#define ADC_EXTERNALTRIGINJEC_T3_TRGO        (LL_ADC_INJ_TRIG_EXT_TIM3_TRGO   )    
#define ADC_EXTERNALTRIGINJEC_EXT_IT11       (LL_ADC_INJ_TRIG_EXT_EXTI_LINE11 )  
#define ADC_EXTERNALTRIGINJEC_EXT_IT15       (LL_ADC_INJ_TRIG_EXT_EXTI_LINE15 )  

/**
  * @}
  */

/** @defgroup ADC_injected_external_trigger_edge ADC group injected trigger edge (when external trigger is selected)
  * @{
  */
#define ADC_EXTERNALTRIGINJECCONV_EDGE_NONE           (0x00000000UL)        /*!< Injected conversions trigger
                                                      disabled (SW start)*/
#define ADC_EXTERNALTRIGINJECCONV_EDGE_RISING         (ADC_JSQR_JEXTEN_0)   /*!< Injected conversions trigger
                                                      polarity set to rising edge */
#define ADC_EXTERNALTRIGINJECCONV_EDGE_FALLING        (ADC_JSQR_JEXTEN_1)   /*!< Injected conversions trigger
                                                      polarity set to falling edge */
#define ADC_EXTERNALTRIGINJECCONV_EDGE_RISINGFALLING  (ADC_JSQR_JEXTEN)     /*!< Injected conversions trigger
                                                      polarity set to both rising and falling edges */
/**
  * @}
  */


/** @defgroup ADC_HAL_EC_CALIBRATION_NUMBER  calibration number
  * @{
  */
#define ADC_CALIBRATION_NUMBER_1        (LL_ADC_CALIBRATION_NUMBER_1 )
#define ADC_CALIBRATION_NUMBER_2        (LL_ADC_CALIBRATION_NUMBER_2 )
#define ADC_CALIBRATION_NUMBER_4        (LL_ADC_CALIBRATION_NUMBER_4 )
#define ADC_CALIBRATION_NUMBER_8        (LL_ADC_CALIBRATION_NUMBER_8 )
#define ADC_CALIBRATION_NUMBER_16       (LL_ADC_CALIBRATION_NUMBER_16)
#define ADC_CALIBRATION_NUMBER_32       (LL_ADC_CALIBRATION_NUMBER_32)

/**
  * @}
  */

/** @defgroup ADC_INJ_SEQ_RANKS  ADC group injected - Sequencer ranks
  * @{
  */
#define ADC_INJECTED_RANK_1                (LL_ADC_INJ_RANK_1) /*!< ADC group injected sequencer rank 1 */
#define ADC_INJECTED_RANK_2                (LL_ADC_INJ_RANK_2) /*!< ADC group injected sequencer rank 2 */
#define ADC_INJECTED_RANK_3                (LL_ADC_INJ_RANK_3) /*!< ADC group injected sequencer rank 3 */
#define ADC_INJECTED_RANK_4                (LL_ADC_INJ_RANK_4) /*!< ADC group injected sequencer rank 4 */
/**
  * @}
  */

/** @defgroup ADC_HAL_EC_GROUPS  ADC instance - Groups
  * @{
  */
#define ADC_REGULAR_GROUP                  (LL_ADC_GROUP_REGULAR)          /*!< ADC group regular (available on
                                                                                all mcu devices) */
#define ADC_INJECTED_GROUP                 (LL_ADC_GROUP_INJECTED)         /*!< ADC group injected (not available on
                                                                                all mcu devices) */
#define ADC_REGULAR_INJECTED_GROUP         (LL_ADC_GROUP_REGULAR_INJECTED) /*!< ADC both groups regular and injected */
/**
  * @}
  */

/** @defgroup ADC_CFGR_fields ADCx CFGR fields
  * @{
  */
#define ADC_CFGR_FIELDS    (ADC_CFGR_AWDCH  | ADC_CFGR_JAUTO   | ADC_CFGR_JAWDEN |\
                            ADC_CFGR_AWDEN  | ADC_CFGR_AWDSGL  | \
                            ADC_CFGR_JDISCEN | ADC_CFGR_DISCNUM | ADC_CFGR_DISCEN  |\
                            ADC_CFGR_AUTDLY  | ADC_CFGR_CONT    | ADC_CFGR_OVRMOD  |\
                            ADC_CFGR_EXTEN   | ADC_CFGR_EXTSEL  | ADC_CFGR_ALIGN   |\
                            ADC_CFGR_RES     | ADC_CFGR_DMACFG  | ADC_CFGR_DMAEN   )
/**
  * @}
  */

/** @defgroup ADC_SMPR1_fields ADCx SMPR1 fields
  * @{
  */
#define ADC_SMPR1_FIELDS    (ADC_SMPR1_SMP9 | ADC_SMPR1_SMP8 | ADC_SMPR1_SMP7 |\
                             ADC_SMPR1_SMP6 | ADC_SMPR1_SMP5 | ADC_SMPR1_SMP4 |\
                             ADC_SMPR1_SMP3 | ADC_SMPR1_SMP2 | ADC_SMPR1_SMP1 |\
                             ADC_SMPR1_SMP0)
/**
  * @}
  */

/** @defgroup ADC_CFGR_fields_2 ADCx CFGR sub fields
  * @{
  */
/* ADC_CFGR fields of parameters that can be updated when no conversion
   (neither regular nor injected) is on-going  */
#define ADC_CFGR_FIELDS_2  ((ADC_CFGR_DMACFG | ADC_CFGR_AUTDLY))
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/** @defgroup ADCEx_Private_Macro_internal_HAL_driver ADC Extended Private Macros
  * @{
  */
/* Macro reserved for internal HAL driver usage, not intended to be used in   */
/* code of final user.                                                        */

/**
  * @brief Test if conversion trigger of injected group is software start
  *        or external trigger.
  * @param __HANDLE__ ADC handle.
  * @retval SET (software start) or RESET (external trigger).
  */
#define ADC_IS_SOFTWARE_START_INJECTED(__HANDLE__)                             \
  (((__HANDLE__)->Instance->JSQR & ADC_JSQR_JEXTEN) == 0UL)

/**
  * @brief Set the selected injected Channel rank.
  * @param __CHANNELNB__ Channel number.
  * @param __RANKNB__ Rank number.
  * @retval None
  */
#define ADC_JSQR_RK(__CHANNELNB__, __RANKNB__) \
  ((((__CHANNELNB__) & ADC_CHANNEL_ID_NUMBER_MASK) >> ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS) \
   << ((__RANKNB__) & ADC_INJ_RANK_ID_JSQR_MASK))

/**
  * @brief Configure ADC discontinuous conversion mode for injected group
  * @param __INJECT_DISCONTINUOUS_MODE__ Injected discontinuous mode.
  * @retval None
  */
#define ADC_CFGR_INJECT_DISCCONTINUOUS(__INJECT_DISCONTINUOUS_MODE__) \
  ((__INJECT_DISCONTINUOUS_MODE__) <<  ADC_CFGR_JDISCEN_Pos)

/**
  * @brief Configure ADC discontinuous conversion mode for regular group
  * @param __REG_DISCONTINUOUS_MODE__ Regular discontinuous mode.
  * @retval None
  */
#define ADC_CFGR_REG_DISCONTINUOUS(__REG_DISCONTINUOUS_MODE__) \
  ((__REG_DISCONTINUOUS_MODE__) << ADC_CFGR_DISCEN_Pos)

/**
  * @brief Configure the number of discontinuous conversions for regular group.
  * @param __NBR_DISCONTINUOUS_CONV__ Number of discontinuous conversions.
  * @retval None
  */
#define ADC_CFGR_DISCONTINUOUS_NUM(__NBR_DISCONTINUOUS_CONV__) \
  (((__NBR_DISCONTINUOUS_CONV__) - 1UL) << ADC_CFGR_DISCNUM_Pos)

/**
  * @brief Configure the ADC auto delay mode.
  * @param __AUTOWAIT__ Auto delay bit enable or disable.
  * @retval None
  */
#define ADC_CFGR_AUTOWAIT(__AUTOWAIT__) ((__AUTOWAIT__) << ADC_CFGR_AUTDLY_Pos)

/**
  * @brief Configure ADC continuous conversion mode.
  * @param __CONTINUOUS_MODE__ Continuous mode.
  * @retval None
  */
#define ADC_CFGR_CONTINUOUS(__CONTINUOUS_MODE__) ((__CONTINUOUS_MODE__) << ADC_CFGR_CONT_Pos)

/**
  * @brief Configure the ADC DMA continuous request.
  * @param __DMACONTREQ_MODE__ DMA continuous request mode.
  * @retval None
  */
#define ADC_CFGR_DMACONTREQ(__DMACONTREQ_MODE__) ((__DMACONTREQ_MODE__) <<  ADC_CFGR_DMACFG_Pos)

/**
  * @brief Shift the offset with respect to the selected ADC resolution.
  * @note   Offset has to be left-aligned on bit 11, the LSB (right bits) are set to 0.
  *         If resolution 12 bits, no shift.
  *         If resolution 10 bits, shift of 2 ranks on the left.
  *         If resolution 8 bits, shift of 4 ranks on the left.
  *         If resolution 6 bits, shift of 6 ranks on the left.
  *         Therefore, shift = (12 - resolution) = 12 - (12- (((RES[1:0]) >> 3)*2)).
  * @param __HANDLE__ ADC handle
  * @param __OFFSET__ Value to be shifted
  * @retval None
  */
#define ADC_OFFSET_SHIFT_RESOLUTION(__HANDLE__, __OFFSET__) \
  ((__OFFSET__) << ((((__HANDLE__)->Instance->CFGR & ADC_CFGR_RES) >> 3UL) * 2UL))

/**
  * @brief Shift the AWD threshold with respect to the selected ADC resolution.
  * @note  Thresholds have to be left-aligned on bit 11, the LSB (right bits) are set to 0.
  *        If resolution 12 bits, no shift.
  *        If resolution 10 bits, shift of 2 ranks on the left.
  *        If resolution 8 bits, shift of 4 ranks on the left.
  *        If resolution 6 bits, shift of 6 ranks on the left.
  *        Therefore, shift = (12 - resolution) = 12 - (12- (((RES[1:0]) >> 3)*2)).
  * @param __HANDLE__ ADC handle
  * @param __THRESHOLD__ Value to be shifted
  * @retval None
  */
#define ADC_AWDTHRESHOLD_SHIFT_RESOLUTION(__HANDLE__, __THRESHOLD__) \
  ((__THRESHOLD__) << ((((__HANDLE__)->Instance->CFGR & ADC_CFGR_RES) >> 3UL) * 2UL))

/**
  * @brief Clear Common Control Register.
  * @param __HANDLE__ ADC handle.
  * @retval None
  */
#define ADC_CLEAR_COMMON_CONTROL_REGISTER(__HANDLE__) CLEAR_BIT(__LL_ADC_COMMON_INSTANCE((__HANDLE__)->Instance)->CCR, \
                                                                ADC_CCR_CKMODE   | \
                                                                ADC_CCR_PRESC    | \
                                                                ADC_CCR_VREFINT_EN | \
                                                                ADC_CCR_TSEN     | \
                                                                ADC_CCR_VREFSEL)

/**
  * @brief Verify the ADC instance connected to the temperature sensor.
  * @param __HANDLE__ ADC handle.
  * @retval SET (ADC instance is valid) or RESET (ADC instance is invalid)
  */
#define ADC_TEMPERATURE_SENSOR_INSTANCE(__HANDLE__) \
  ((((__HANDLE__)->Instance) == ADC1))


/**
  * @brief Verify the ADC instance connected to the internal voltage reference VREFINT.
  * @param __HANDLE__ ADC handle.
  * @retval SET (ADC instance is valid) or RESET (ADC instance is invalid)
  */
#define ADC_VREFINT_INSTANCE(__HANDLE__)  (((__HANDLE__)->Instance) == ADC1)

/**
  * @brief Verify the length of scheduled injected conversions group.
  * @param __LENGTH__ number of programmed conversions.
  * @retval SET (__LENGTH__ is within the maximum number of possible programmable injected conversions)
  *         or RESET (__LENGTH__ is null or too large)
  */
#define IS_ADC_INJECTED_NB_CONV(__LENGTH__) (((__LENGTH__) >= (1U)) && ((__LENGTH__) <= (4U)))

/**
  * @brief Verify the ADC channel setting.
  * @param __HANDLE__ ADC handle.
  * @param __CHANNEL__ programmed ADC channel.
  * @retval SET (__CHANNEL__ is valid) or RESET (__CHANNEL__ is invalid)
  */
#define IS_ADC_CHANNEL(__HANDLE__, __CHANNEL__)         ( ((__CHANNEL__) == ADC_CHANNEL_0)                || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_1)                || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_2)                || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_3)                || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_4)                || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_5)                || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_6)                || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_7)                || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_8)                || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_9)                || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_10)               || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_11)               || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_12)               || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_13)               || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_14)               || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_TEMPSENSOR)       || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_VREFINT)          || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_1_3VCCA)          || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_OPA1)             || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_OPA2) )

/**
  * @brief Verify the ADC number of calibrations.
  * @param __CALNUM__ programmed setting the number of calibrations.
  * @retval SET (__CALNUM__ is valid) or RESET (__CALNUM__ is invalid)
  */
#define IS_ADC_CALIBRATION_NUMBER(__CALNUM__)     (((__CALNUM__) == ADC_CALIBRATION_NUMBER_1 )  || \
                                                   ((__CALNUM__) == ADC_CALIBRATION_NUMBER_2 )  || \
                                                   ((__CALNUM__) == ADC_CALIBRATION_NUMBER_4 )  || \
                                                   ((__CALNUM__) == ADC_CALIBRATION_NUMBER_8 )  || \
                                                   ((__CALNUM__) == ADC_CALIBRATION_NUMBER_16)  || \
                                                   ((__CALNUM__) == ADC_CALIBRATION_NUMBER_32)  )

/**
  * @brief Verify the ADC injected channel setting.
  * @param __CHANNEL__ programmed ADC injected channel.
  * @retval SET (__CHANNEL__ is valid) or RESET (__CHANNEL__ is invalid)
  */
#define IS_ADC_INJECTED_RANK(__CHANNEL__) (((__CHANNEL__) == ADC_INJECTED_RANK_1) || \
                                           ((__CHANNEL__) == ADC_INJECTED_RANK_2) || \
                                           ((__CHANNEL__) == ADC_INJECTED_RANK_3) || \
                                           ((__CHANNEL__) == ADC_INJECTED_RANK_4)   )

/**
  * @brief Verify the ADC injected conversions external trigger.
  * @param __HANDLE__ ADC handle.
  * @param __INJTRIG__ programmed ADC injected conversions external trigger.
  * @retval SET (__INJTRIG__ is a valid value) or RESET (__INJTRIG__ is invalid)
  */
#define IS_ADC_EXTTRIGINJEC(__HANDLE__, __INJTRIG__)  (((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T1_TRGO   )       || \
                                                       ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T1_CC1    )       || \
                                                       ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T1_CC2    )       || \
                                                       ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T1_CC3    )       || \
                                                       ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T1_CC4    )       || \
                                                       ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T1_CC5   )       || \
                                                       ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T1_CC6    )       || \
                                                       ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T3_CC1   )       || \
                                                       ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T3_TRGO   )       || \
                                                       ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_EXT_IT11  )       || \
                                                       ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_EXT_IT15  )       || \
                                                       ((__INJTRIG__) == ADC_INJECTED_SOFTWARE_START)          )

/**
  * @brief Verify the ADC edge trigger setting for injected group.
  * @param __EDGE__ programmed ADC edge trigger setting.
  * @retval SET (__EDGE__ is a valid value) or RESET (__EDGE__ is invalid)
  */
#define IS_ADC_EXTTRIGINJEC_EDGE(__EDGE__) (((__EDGE__) == ADC_EXTERNALTRIGINJECCONV_EDGE_NONE)         || \
                                            ((__EDGE__) == ADC_EXTERNALTRIGINJECCONV_EDGE_RISING)       || \
                                            ((__EDGE__) == ADC_EXTERNALTRIGINJECCONV_EDGE_FALLING)      || \
                                            ((__EDGE__) == ADC_EXTERNALTRIGINJECCONV_EDGE_RISINGFALLING) )

/**
  * @brief Verify the ADC analog watchdog mode setting.
  * @param __WATCHDOG_MODE__ programmed ADC analog watchdog mode setting.
  * @retval SET (__WATCHDOG_MODE__ is valid) or RESET (__WATCHDOG_MODE__ is invalid)
  */
#define IS_ADC_ANALOG_WATCHDOG_MODE(__WATCHDOG_MODE__) (((__WATCHDOG_MODE__) == ADC_ANALOGWATCHDOG_NONE)            || \
                                                        ((__WATCHDOG_MODE__) == ADC_ANALOGWATCHDOG_SINGLE_REG)      || \
                                                        ((__WATCHDOG_MODE__) == ADC_ANALOGWATCHDOG_SINGLE_INJEC)    || \
                                                        ((__WATCHDOG_MODE__) == ADC_ANALOGWATCHDOG_SINGLE_REGINJEC) || \
                                                        ((__WATCHDOG_MODE__) == ADC_ANALOGWATCHDOG_ALL_REG)         || \
                                                        ((__WATCHDOG_MODE__) == ADC_ANALOGWATCHDOG_ALL_INJEC)       || \
                                                        ((__WATCHDOG_MODE__) == ADC_ANALOGWATCHDOG_ALL_REGINJEC)      )

/**
  * @brief Verify the ADC analog watchdog filtering setting.
  * @param __FILTERING_MODE__ programmed ADC analog watchdog mode setting.
  * @retval SET (__FILTERING_MODE__ is valid) or RESET (__FILTERING_MODE__ is invalid)
  */
#define IS_ADC_ANALOG_WATCHDOG_FILTERING_MODE(__FILTERING_MODE__) \
  (((__FILTERING_MODE__) == ADC_AWD_FILTERING_NONE)            || \
   ((__FILTERING_MODE__) == ADC_AWD_FILTERING_2SAMPLES)        || \
   ((__FILTERING_MODE__) == ADC_AWD_FILTERING_3SAMPLES)        || \
   ((__FILTERING_MODE__) == ADC_AWD_FILTERING_4SAMPLES)        || \
   ((__FILTERING_MODE__) == ADC_AWD_FILTERING_5SAMPLES)        || \
   ((__FILTERING_MODE__) == ADC_AWD_FILTERING_6SAMPLES)        || \
   ((__FILTERING_MODE__) == ADC_AWD_FILTERING_7SAMPLES)        || \
   ((__FILTERING_MODE__) == ADC_AWD_FILTERING_8SAMPLES)           )

/**
  * @brief Verify the ADC conversion (regular or injected or both).
  * @param __CONVERSION__ ADC conversion group.
  * @retval SET (__CONVERSION__ is valid) or RESET (__CONVERSION__ is invalid)
  */
#define IS_ADC_CONVERSION_GROUP(__CONVERSION__) (((__CONVERSION__) == ADC_REGULAR_GROUP)         || \
                                                 ((__CONVERSION__) == ADC_INJECTED_GROUP)        || \
                                                 ((__CONVERSION__) == ADC_REGULAR_INJECTED_GROUP)  )

/**
  * @brief Verify the ADC event type.
  * @param __EVENT__ ADC event.
  * @retval SET (__EVENT__ is valid) or RESET (__EVENT__ is invalid)
  */
#define IS_ADC_EVENT_TYPE(__EVENT__) (((__EVENT__) == ADC_EOSMP_EVENT)  || \
                                      ((__EVENT__) == ADC_OVR_EVENT)    || \
                                      ((__EVENT__) == ADC_AWD_EVENT))


/**
  * @brief Verify the DFSDM mode configuration.
  * @param __HANDLE__ ADC handle.
  * @note When DMSDFM configuration is not supported, the macro systematically reports SET. For
  *      this reason, the input parameter is the ADC handle and not the configuration parameter
  *      directly.
  * @retval SET (DFSDM mode configuration is valid) or RESET (DFSDM mode configuration is invalid)
  */
#define IS_ADC_DFSDMCFG_MODE(__HANDLE__) (SET)

/**
  * @brief Return the DFSDM configuration mode.
  * @param __HANDLE__ ADC handle.
  * @note When DMSDFM configuration is not supported, the macro systematically reports 0x0 (i.e disabled).
  *       For this reason, the input parameter is the ADC handle and not the configuration parameter
  *       directly.
  * @retval DFSDM configuration mode
  */
#define ADC_CFGR_DFSDM(__HANDLE__) (0x0UL)

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup ADCEx_Exported_Functions
  * @{
  */

/** @addtogroup ADCEx_Exported_Functions_Group1
  * @{
  */
/* IO operation functions *****************************************************/

/* ADC calibration */
HAL_StatusTypeDef HAL_ADCEx_Calibration_Start(ADC_HandleTypeDef *hadc, uint32_t CalNum);
HAL_StatusTypeDef HAL_ADCEx_Calibration_GetStatus(ADC_HandleTypeDef* hadc);

/* Blocking mode: Polling */
HAL_StatusTypeDef       HAL_ADCEx_InjectedStart(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef       HAL_ADCEx_InjectedStop(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef       HAL_ADCEx_InjectedPollForConversion(ADC_HandleTypeDef *hadc, uint32_t Timeout);

/* Non-blocking mode: Interruption */
HAL_StatusTypeDef       HAL_ADCEx_InjectedStart_IT(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef       HAL_ADCEx_InjectedStop_IT(ADC_HandleTypeDef *hadc);

/* ADC retrieve conversion value intended to be used with polling or interruption */
uint32_t                HAL_ADCEx_InjectedGetValue(const ADC_HandleTypeDef *hadc, uint32_t InjectedRank);

/* ADC IRQHandler and Callbacks used in non-blocking modes (Interruption) */
void                    HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc);
void                    HAL_ADCEx_EndOfSamplingCallback(ADC_HandleTypeDef *hadc);

/**
  * @}
  */

/** @addtogroup ADCEx_Exported_Functions_Group2
  * @{
  */
/* Peripheral Control functions ***********************************************/
HAL_StatusTypeDef       HAL_ADCEx_InjectedConfigChannel(ADC_HandleTypeDef *hadc,
                                                        const ADC_InjectionConfTypeDef *pConfigInjected);

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

#endif /* PY32F032_HAL_ADC_EX_H */
