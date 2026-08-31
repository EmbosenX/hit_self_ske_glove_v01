/**
  ******************************************************************************
  * @file    py32f032_hal_adc.h
  * @author  MCU Application Team
  * @brief   Header file of ADC HAL module.
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
#ifndef PY32F032_HAL_ADC_H
#define PY32F032_HAL_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/
#include "py32f032_hal_def.h"

/* Include low level driver */
#include "py32f032_ll_adc.h"

/** @addtogroup PY32F032_HAL_Driver
  * @{
  */

/** @addtogroup ADC
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup ADC_Exported_Types ADC Exported Types
  * @{
  */

/**
  * @brief  Structure definition of ADC instance and ADC group regular.
  * @note   Parameters of this structure are shared within 2 scopes:
  *          - Scope entire ADC (affects ADC groups regular and injected): ClockPrescaler, Resolution, DataAlign,
  *            ScanConvMode, EOCSelection, LowPowerAutoWait.
  *          - Scope ADC group regular: ContinuousConvMode, NbrOfConversion, DiscontinuousConvMode, NbrOfDiscConversion,
  *            ExternalTrigConv, ExternalTrigConvEdge, DMAContinuousRequests, Overrun,
  *            SamplingMode.
  * @note   The setting of these parameters by function HAL_ADC_Init() is conditioned to ADC state.
  *         ADC state can be either:
  *          - For all parameters: ADC disabled
  *          - For all parameters except 'LowPowerAutoWait', 'DMAContinuousRequests': ADC enabled
  *            without conversion on going on group regular.
  *          - For parameters 'LowPowerAutoWait' and 'DMAContinuousRequests': ADC enabled without conversion on going
  *            on groups regular and injected.
  *         If ADC is not in the appropriate state to modify some parameters, these parameters setting is bypassed
  *         without error reporting (as it can be the expected behavior in case of intended action to update another
  *         parameter (which fulfills the ADC state condition) on the fly).
  */
typedef struct
{
  uint32_t ClockPrescaler;        /*!< Select ADC clock source (synchronous clock derived from APB clock or asynchronous
                                       clock derived from system clock or PLL (Refer to reference manual for list of
                                       clocks available)) and clock prescaler.
                                       This parameter can be a value of @ref ADC_HAL_EC_COMMON_CLOCK_SOURCE. */
  uint32_t Resolution;            /*!< Configure the ADC resolution.
                                       This parameter can be a value of @ref ADC_HAL_EC_RESOLUTION */

  uint32_t DataAlign;             /*!< Specify ADC data alignment in conversion data register (right or left).
                                       Refer to reference manual for alignments formats versus resolutions.
                                       This parameter can be a value of @ref ADC_HAL_EC_DATA_ALIGN */

  uint32_t ScanConvMode;          /*!< Configure the sequencer of ADC groups regular and injected.
                                       This parameter can be associated to parameter 'DiscontinuousConvMode' to have
                                       main sequence subdivided in successive parts.
                                       If disabled: Conversion is performed in single mode (one channel converted, the
                                                    one defined in rank 1). Parameters 'NbrOfConversion' and
                                                    'InjectedNbrOfConversion' are discarded (equivalent to set to 1).
                                       If enabled:  Conversions are performed in sequence mode (multiple ranks defined
                                                    by 'NbrOfConversion' or 'InjectedNbrOfConversion' and rank of each
                                                    channel in sequencer). Scan direction is upward: from rank 1 to
                                                    rank 'n'.
                                       This parameter can be a value of @ref ADC_Scan_mode */

  uint32_t EOCSelection;          /*!< Specify which EOC (End Of Conversion) flag is used for conversion by polling and
                                       interruption: end of unitary conversion or end of sequence conversions.
                                       This parameter can be a value of @ref ADC_EOCSelection. */

  FunctionalState LowPowerAutoWait; /*!< Select the dynamic low power Auto Delay: new conversion start only when the
                                       previous conversion (for ADC group regular) or previous sequence (for ADC group
                                       injected) has been retrieved by user software, using function HAL_ADC_GetValue()
                                       or HAL_ADCEx_InjectedGetValue().
                                       This feature automatically adapts the frequency of ADC conversions triggers to
                                       the speed of the system that reads the data. Moreover, this avoids risk of
                                       overrun for low frequency applications.
                                       This parameter can be set to ENABLE or DISABLE.
                                       Note: It is not recommended to use with interruption or DMA (HAL_ADC_Start_IT(),
                                             HAL_ADC_Start_DMA()) since these modes have to clear immediately the EOC
                                             flag (by CPU to free the IRQ pending event or by DMA).
                                             Auto wait will work but fort a very short time, discarding its intended
                                             benefit (except specific case of high load of CPU or DMA transfers which
                                             can justify usage of auto wait).
                                             Do use with polling: 1. Start conversion with HAL_ADC_Start(), 2. Later on,
                                             when ADC conversion data is needed:
                                             use HAL_ADC_PollForConversion() to ensure that conversion is completed and
                                             HAL_ADC_GetValue() to retrieve conversion result and trig another
                                             conversion start. (in case of usage of ADC group injected, use the
                                             equivalent functions HAL_ADCExInjected_Start(),
                                             HAL_ADCEx_InjectedGetValue(), ...). */

  FunctionalState ContinuousConvMode; /*!< Specify whether the conversion is performed in single mode (one conversion)
                                           or continuous mode for ADC group regular, after the first ADC conversion
                                           start trigger occurred (software start or external trigger). This parameter
                                           can be set to ENABLE or DISABLE. */

  uint32_t NbrOfConversion;       /*!< Specify the number of ranks that will be converted within the regular group
                                       sequencer.
                                       This parameter is dependent on ScanConvMode:
                                        - sequencer configured to fully configurable:
                                          Number of ranks in the scan sequence is configurable using this parameter.
                                          Note: After the first call of 'HAL_ADC_Init()', each rank corresponding to
                                                parameter "NbrOfConversion" must be set using 'HAL_ADC_ConfigChannel()'.
                                                Afterwards, when all needed sequencer ranks are set, parameter
                                                'NbrOfConversion' can be updated without modifying configuration of
                                                sequencer ranks (sequencer ranks above 'NbrOfConversion' are discarded).
                                        - sequencer configured to not fully configurable:
                                          Number of ranks in the scan sequence is defined by number of channels set in
                                          the sequence. This parameter is discarded.
                                       This parameter must be a number between Min_Data = 1 and Max_Data = 8.
                                       Note: This parameter must be modified when no conversion is on going on regular
                                             group (ADC disabled, or ADC enabled without continuous mode or external
                                             trigger that could launch a conversion). */

  FunctionalState DiscontinuousConvMode; /*!< Specify whether the conversions sequence of ADC group regular is performed
                                              in Complete-sequence/Discontinuous-sequence (main sequence subdivided in
                                              successive parts).
                                              Discontinuous mode is used only if sequencer is enabled (parameter
                                              'ScanConvMode'). If sequencer is disabled, this parameter is discarded.
                                              Discontinuous mode can be enabled only if continuous mode is disabled.
                                              If continuous mode is enabled, this parameter setting is discarded.
                                              This parameter can be set to ENABLE or DISABLE.
                                              Note: On this mcu series, ADC group regular number of discontinuous
                                                    ranks increment is fixed to one-by-one. */

  uint32_t NbrOfDiscConversion;   /*!< Specifies the number of discontinuous conversions in which the main sequence
                                       of ADC group regular (parameter NbrOfConversion) will be subdivided.
                                       If parameter 'DiscontinuousConvMode' is disabled, this parameter is discarded.
                                       This parameter must be a number between Min_Data = 1 and Max_Data = 8. */

  uint32_t ExternalTrigConv;      /*!< Select the external event source used to trigger ADC group regular conversion
                                       start.
                                       If set to ADC_SOFTWARE_START, external triggers are disabled and software trigger
                                       is used instead.
                                       This parameter can be a value of @ref ADC_regular_external_trigger_source.
                                       Caution: external trigger source is common to all ADC instances. */
                                      
  FunctionalState DMAContinuousRequests; /*!< Specify whether the DMA requests are performed in one shot mode (DMA
                                              transfer stops when number of conversions is reached) or in continuous
                                              mode (DMA transfer unlimited, whatever number of conversions).
                                              This parameter can be set to ENABLE or DISABLE.
                                              Note: In continuous mode, DMA must be configured in circular mode.
                                                    Otherwise an overrun will be triggered when DMA buffer maximum
                                                    pointer is reached. */

  uint32_t Overrun;               /*!< Select the behavior in case of overrun: data overwritten or preserved (default).
                                       This parameter applies to ADC group regular only.
                                       This parameter can be a value of @ref ADC_HAL_EC_REG_OVR_DATA_BEHAVIOR.
                                       Note: In case of overrun set to data preserved and usage with programming model
                                             with interruption (HAL_Start_IT()): ADC IRQ handler has to clear end of
                                             conversion flags, this induces the release of the preserved data. If
                                             needed, this data can be saved in function HAL_ADC_ConvCpltCallback(),
                                             placed in user program code (called before end of conversion flags clear)
                                       Note: Error reporting with respect to the conversion mode:
                                             - Usage with ADC conversion by polling for event or interruption: Error is
                                               reported only if overrun is set to data preserved. If overrun is set to
                                               data overwritten, user can willingly not read all the converted data,
                                               this is not considered as an erroneous case.
                                             - Usage with ADC conversion by DMA: Error is reported whatever overrun
                                               setting (DMA is expected to process all data from data register). */                                     

  uint32_t ExternalTrigConvEdge;  /*!< Select the external event edge used to trigger ADC group regular conversion start
                                       If trigger source is set to ADC_SOFTWARE_START, this parameter is discarded.
                                       This parameter can be a value of @ref ADC_regular_external_trigger_edge */

} ADC_InitTypeDef;

/**
  * @brief  Structure definition of ADC channel for regular group
  */
typedef struct
{
  uint32_t Channel;                /*!< Specify the channel to configure into ADC regular group.
                                        This parameter can be a value of @ref ADC_HAL_EC_CHANNEL
                                        Note: Depending on devices and ADC instances, some channels may not be available
                                              on device package pins. Refer to device datasheet for channels
                                              availability. */

  uint32_t Rank;                   /*!< Specify the rank in the regular group sequencer.
                                        This parameter can be a value of @ref ADC_HAL_EC_REG_SEQ_RANKS
                                        Note: to disable a channel or change order of conversion sequencer, rank
                                        containing a previous channel setting can be overwritten by the new channel
                                        setting (or parameter number of conversions adjusted) */

  uint32_t SamplingTime;           /*!< Sampling time value to be set for the selected channel.
                                        Unit: ADC clock cycles
                                        Conversion time is the addition of sampling time and processing time
                                        (12.5 ADC clock cycles at ADC resolution 12 bits, 10.5 cycles at 10 bits,
                                        8.5 cycles at 8 bits, 6.5 cycles at 6 bits).
                                        This parameter can be a value of @ref ADC_HAL_EC_CHANNEL_SAMPLINGTIME
                                        Caution: This parameter applies to a channel that can be used into regular
                                                 and/or injected group. It overwrites the last setting.
                                        Note: In case of usage of internal measurement channels (VrefInt, ...),
                                              sampling time constraints must be respected (sampling time can be adjusted
                                              in function of ADC clock frequency and sampling time setting).
                                              Refer to device datasheet for timings values. */

} ADC_ChannelConfTypeDef;

/**
  * @brief  Structure definition of ADC analog watchdog
  * @note   The setting of these parameters by function HAL_ADC_AnalogWDGConfig() is conditioned to ADC state.
  *         ADC state can be either:
  *          - For all parameters except 'HighThreshold', 'LowThreshold': ADC disabled or ADC enabled without conversion
               on going on ADC groups regular and injected.
  *          - For parameters 'HighThreshold', 'LowThreshold': ADC enabled with conversion on going on regular and
               injected groups.
  */
typedef struct
{
  uint32_t WatchdogMode;      /*!< Configure the ADC analog watchdog mode: single/all/none channels.
                                   For Analog Watchdog 1: Configure the ADC analog watchdog mode: single channel or all
                                                          channels, ADC groups regular and-or injected.
                                   This parameter can be a value of @ref ADC_analog_watchdog_mode. */

  uint32_t Channel;           /*!< Select which ADC channel to monitor by analog watchdog.
                                   For Analog Watchdog 1: this parameter has an effect only if parameter 'WatchdogMode'
                                                          is configured on single channel (only 1 channel can be
                                                          monitored).
                                   This parameter can be a value of @ref ADC_HAL_EC_CHANNEL. */

  FunctionalState ITMode;     /*!< Specify whether the analog watchdog is configured in interrupt or polling mode.
                                   This parameter can be set to ENABLE or DISABLE */

  uint32_t HighThreshold;     /*!< Configure the ADC analog watchdog High threshold value.
                                   Depending of ADC resolution selected (12, 10, 8 or 6 bits), this parameter must be a
                                   number between Min_Data = 0x000 and Max_Data = 0xFFF, 0x3FF, 0xFF or 0x3F
                                   respectively. */

  uint32_t LowThreshold;      /*!< Configures the ADC analog watchdog Low threshold value.
                                   Depending of ADC resolution selected (12, 10, 8 or 6 bits), this parameter must be a
                                   number between Min_Data = 0x000 and Max_Data = 0xFFF, 0x3FF, 0xFF or 0x3F
                                   respectively. */

  uint32_t FilteringConfig;   /*!< Specify whether filtering should be use and the number of samples to consider.
                                   Before setting flag or raising interrupt, analog watchdog can wait to have several
                                   consecutive out-of-window samples. This parameter allows to configure this number.
                                   This parameter only applies to Analog watchdog 1. For others, use value
                                   ADC_AWD_FILTERING_NONE.
                                   This parameter can be a value of @ref ADC_analog_watchdog_filtering_config. */
} ADC_AnalogWDGConfTypeDef;

/**
  * @brief  ADC group injected contexts queue configuration
  * @note   Structure intended to be used only through structure "ADC_HandleTypeDef"
  */
typedef struct
{
  uint32_t ContextQueue;                 /*!< Injected channel configuration context: build-up over each
                                              HAL_ADCEx_InjectedConfigChannel() call to finally initialize
                                              JSQR register at HAL_ADCEx_InjectedConfigChannel() last call */

  uint32_t ChannelCount;                 /*!< Number of channels in the injected sequence */
} ADC_InjectionConfigTypeDef;

/** @defgroup ADC_States ADC States
  * @{
  */

/**
  * @brief  HAL ADC state machine: ADC states definition (bitfields)
  * @note   ADC state machine is managed by bitfields, state must be compared
  *         with bit by bit.
  *         For example:
  *           " if ((HAL_ADC_GetState(hadc1) & HAL_ADC_STATE_REG_BUSY) != 0UL) "
  *           " if ((HAL_ADC_GetState(hadc1) & HAL_ADC_STATE_AWD) != 0UL) "
  */
/* States of ADC global scope */
#define HAL_ADC_STATE_RESET             (0x00000000UL)   /*!< ADC not yet initialized or disabled */
#define HAL_ADC_STATE_READY             (0x00000001UL)   /*!< ADC peripheral ready for use */
#define HAL_ADC_STATE_BUSY_INTERNAL     (0x00000002UL)   /*!< ADC is busy due to an internal process (initialization,
                                                              calibration, ...) */
#define HAL_ADC_STATE_TIMEOUT           (0x00000004UL)   /*!< TimeOut occurrence */

/* States of ADC errors */
#define HAL_ADC_STATE_ERROR_INTERNAL    (0x00000010UL)   /*!< Internal error occurrence */
#define HAL_ADC_STATE_ERROR_CONFIG      (0x00000020UL)   /*!< Configuration error occurrence */
#define HAL_ADC_STATE_ERROR_DMA         (0x00000040UL)   /*!< DMA error occurrence */

/* States of ADC group regular */
#define HAL_ADC_STATE_REG_BUSY          (0x00000100UL)   /*!< A conversion on ADC group regular is ongoing or can occur
                                                              (either by continuous mode, external trigger, low power
                                                              auto power-on (if feature available), multimode ADC master
                                                              control (if feature available)) */
#define HAL_ADC_STATE_REG_EOC           (0x00000200UL)   /*!< Conversion data available on group regular */
#define HAL_ADC_STATE_REG_EOSMP         (0x00000400UL)   /*!< Not available on this mcu series: End Of Sampling flag
                                                              raised  */
#define HAL_ADC_STATE_REG_OVR           (0x00000800UL)   /*!< Overrun occurrence */                                                              

/* States of ADC group injected */
#define HAL_ADC_STATE_INJ_BUSY          (0x00001000UL)   /*!< A conversion on ADC group injected is ongoing or can occur
                                                              (either by auto-injection mode, external trigger, low
                                                              power auto power-on (if feature available), multimode
                                                              ADC master control (if feature available)) */
#define HAL_ADC_STATE_INJ_EOC           (0x00002000UL)   /*!< Conversion data available on group injected */

/* States of ADC analog watchdogs */
#define HAL_ADC_STATE_AWD               (0x00010000UL)   /*!< Out-of-window occurrence of ADC analog watchdog */

/**
  * @}
  */

/**
  * @brief  ADC handle Structure definition
  */
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
typedef struct __ADC_HandleTypeDef
#else
typedef struct
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */
{
  ADC_TypeDef                   *Instance;                     /*!< Register base address */
  ADC_InitTypeDef               Init;                          /*!< ADC initialization parameters and regular
                                                                    conversions setting */
  DMA_HandleTypeDef             *DMA_Handle;                   /*!< Pointer DMA Handler */
  HAL_LockTypeDef               Lock;                          /*!< ADC locking object */
  __IO uint32_t                 State;                         /*!< ADC communication state (bitmap of ADC states) */
  __IO uint32_t                 ErrorCode;                     /*!< ADC Error code */
  ADC_InjectionConfigTypeDef    InjectionConfig ;              /*!< ADC injected channel configuration build-up
                                                                  structure */
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
  void (* ConvCpltCallback)(struct __ADC_HandleTypeDef *hadc);              /*!< ADC conversion complete callback */
  void (* ConvHalfBlockCpltCallback)(struct __ADC_HandleTypeDef *hadc);     /*!< ADC conversion DMA halfblock-transfer
                                                                                 callback */
  void (* LevelOutOfWindowCallback)(struct __ADC_HandleTypeDef *hadc);      /*!< ADC analog watchdog callback */
  void (* ErrorCallback)(struct __ADC_HandleTypeDef *hadc);                 /*!< ADC error callback */
  void (* InjectedConvCpltCallback)(struct __ADC_HandleTypeDef *hadc);      /*!< ADC group injected conversion complete
                                                                                 callback */
  void (* EndOfSamplingCallback)(struct __ADC_HandleTypeDef *hadc);         /*!< ADC end of sampling callback */
  void (* MspInitCallback)(struct __ADC_HandleTypeDef *hadc);               /*!< ADC Msp Init callback */
  void (* MspDeInitCallback)(struct __ADC_HandleTypeDef *hadc);             /*!< ADC Msp DeInit callback */
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */
} ADC_HandleTypeDef;

#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
/**
  * @brief  HAL ADC Callback ID enumeration definition
  */
typedef enum
{
  HAL_ADC_CONVERSION_COMPLETE_CB_ID     = 0x00U,  /*!< ADC conversion complete callback ID */
  HAL_ADC_CONVERSION_HALFBLOCK_CB_ID    = 0x01U,  /*!< ADC conversion DMA halfblock-transfer callback ID */
  HAL_ADC_LEVEL_OUT_OF_WINDOW_1_CB_ID   = 0x02U,  /*!< ADC analog watchdog 1 callback ID */
  HAL_ADC_ERROR_CB_ID                   = 0x03U,  /*!< ADC error callback ID */
  HAL_ADC_INJ_CONVERSION_COMPLETE_CB_ID = 0x04U,  /*!< ADC group injected conversion complete callback ID */
  HAL_ADC_END_OF_SAMPLING_CB_ID         = 0x07U,  /*!< ADC end of sampling callback ID */
  HAL_ADC_MSPINIT_CB_ID                 = 0x08U,  /*!< ADC Msp Init callback ID          */
  HAL_ADC_MSPDEINIT_CB_ID               = 0x09U   /*!< ADC Msp DeInit callback ID        */
} HAL_ADC_CallbackIDTypeDef;

/**
  * @brief  HAL ADC Callback pointer definition
  */
typedef  void (*pADC_CallbackTypeDef)(ADC_HandleTypeDef *hadc); /*!< pointer to a ADC callback function */

#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */

/**
  * @}
  */


/* Exported constants --------------------------------------------------------*/

/** @defgroup ADC_Exported_Constants ADC Exported Constants
  * @{
  */

/** @defgroup ADC_Error_Code ADC Error Code
  * @{
  */
#define HAL_ADC_ERROR_NONE              (0x00U)   /*!< No error                                    */
#define HAL_ADC_ERROR_INTERNAL          (0x01U)   /*!< ADC peripheral internal error (problem of clocking,
                                                       enable/disable, erroneous state, ...)       */
#define HAL_ADC_ERROR_DMA               (0x02U)   /*!< DMA transfer error                          */
#define HAL_ADC_ERROR_OVR               (0x04U)   /*!< Overrun error                               */
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
#define HAL_ADC_ERROR_INVALID_CALLBACK  (0x10U)   /*!< Invalid Callback error */
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup ADC_HAL_EC_COMMON_CLOCK_SOURCE  ADC common - Clock source
  * @{
  */

#define ADC_CLOCK_SYNC_PCLK_DIV2           (ADC_CCR_CKMODE_0)  /*!< ADC synchronous clock from AHB clock
                                           without prescaler by 2 */
#define ADC_CLOCK_SYNC_PCLK_DIV4           (ADC_CCR_CKMODE_1)  /*!< ADC synchronous clock from AHB clock
                                           with prescaler division by 4 */
#define ADC_CLOCK_SYNC_PCLK_DIV1           (ADC_CCR_CKMODE_1 | ADC_CCR_CKMODE_0)  /*!< ADC synchronous clock from AHB clock
                                           with prescaler division  */
#define ADC_CLOCK_ASYNC_DIV1               (0x00000000UL)      /*!< ADC asynchronous clock without
                                           prescaler */
#define ADC_CLOCK_ASYNC_DIV2               (ADC_CCR_PRESC_0)      /*!< ADC asynchronous clock with prescaler
                                           division by 2   */
#define ADC_CLOCK_ASYNC_DIV4               (ADC_CCR_PRESC_1)      /*!< ADC asynchronous clock with prescaler
                                           division by 4   */
#define ADC_CLOCK_ASYNC_DIV6               (ADC_CCR_PRESC_1 | ADC_CCR_PRESC_0)      /*!< ADC asynchronous clock with prescaler
                                           division by 6   */
#define ADC_CLOCK_ASYNC_DIV8               (ADC_CCR_PRESC_2)      /*!< ADC asynchronous clock with prescaler
                                           division by 8   */
#define ADC_CLOCK_ASYNC_DIV10              (ADC_CCR_PRESC_2 | ADC_CCR_PRESC_0)     /*!< ADC asynchronous clock with prescaler
                                           division by 10  */
#define ADC_CLOCK_ASYNC_DIV12              (ADC_CCR_PRESC_2 | ADC_CCR_PRESC_1)     /*!< ADC asynchronous clock with prescaler
                                           division by 12  */
#define ADC_CLOCK_ASYNC_DIV16              (ADC_CCR_PRESC_2 | ADC_CCR_PRESC_1 | ADC_CCR_PRESC_0)     /*!< ADC asynchronous clock with prescaler
                                           division by 16  */
#define ADC_CLOCK_ASYNC_DIV32              (ADC_CCR_PRESC_3)     /*!< ADC asynchronous clock with prescaler
                                           division by 32  */
#define ADC_CLOCK_ASYNC_DIV64              (ADC_CCR_PRESC_3 | ADC_CCR_PRESC_0)     /*!< ADC asynchronous clock with prescaler
                                           division by 64  */
#define ADC_CLOCK_ASYNC_DIV128             (ADC_CCR_PRESC_3 | ADC_CCR_PRESC_1)    /*!< ADC asynchronous clock with prescaler
                                           division by 128 */
#define ADC_CLOCK_ASYNC_DIV256             (ADC_CCR_PRESC_3 | ADC_CCR_PRESC_1 | ADC_CCR_PRESC_0)    /*!< ADC asynchronous clock with prescaler
                                           division by 256 */
/**
  * @}
  */

/** @defgroup ADC_HAL_EC_RESOLUTION  ADC instance - Resolution
  * @{
  */
#define ADC_RESOLUTION_12B                 (LL_ADC_RESOLUTION_12B)  /*!< ADC resolution 12 bits */
#define ADC_RESOLUTION_10B                 (LL_ADC_RESOLUTION_10B)  /*!< ADC resolution 10 bits */
#define ADC_RESOLUTION_8B                  (LL_ADC_RESOLUTION_8B)   /*!< ADC resolution  8 bits */
#define ADC_RESOLUTION_6B                  (LL_ADC_RESOLUTION_6B)   /*!< ADC resolution  6 bits */
/**
  * @}
  */

/** @defgroup ADC_VrefBuf ADC VrefBuf
  * @{
  */  
#define ADC_VREFBUF_VCCA                   (0x00000000U)                  /*!< VREFBUF VCCA   */
#define ADC_VREFBUF_1P024V                 SYSCFG_VREFBUF_1P024V          /* Vrefbuf 1.024V */  
#define ADC_VREFBUF_1P5V                   SYSCFG_VREFBUF_1P5V            /* Vrefbuf 1.5V */  
#define ADC_VREFBUF_2P048V                 SYSCFG_VREFBUF_2P048V          /* Vrefbuf 2.048V */  
/**
  * @}
  */

/** @defgroup ADC_HAL_EC_DATA_ALIGN ADC conversion data alignment
  * @{
  */
#define ADC_DATAALIGN_RIGHT                (LL_ADC_DATA_ALIGN_RIGHT) /*!< ADC conversion data alignment: right aligned
                                           (alignment on data register LSB bit 0)*/
#define ADC_DATAALIGN_LEFT                 (LL_ADC_DATA_ALIGN_LEFT)  /*!< ADC conversion data alignment: left aligned
                                           (alignment on data register MSB bit 15)*/
/**
  * @}
  */

/** @defgroup ADC_Scan_mode ADC sequencer scan mode
  * @{
  */
#define ADC_SCAN_DISABLE         (0x00000000UL)       /*!< Scan mode disabled */
#define ADC_SCAN_ENABLE          (0x00000001UL)       /*!< Scan mode enabled  */
/**
  * @}
  */

/** @defgroup ADC_regular_external_trigger_source ADC group regular trigger source
  * @{
  */
#define ADC_SOFTWARE_START               (LL_ADC_REG_TRIG_SOFTWARE       )
#define ADC_EXTERNALTRIG_T1_TRGO         (LL_ADC_REG_TRIG_EXT_TIM1_TRGO  )
#define ADC_EXTERNALTRIG_T1_CC1          (LL_ADC_REG_TRIG_EXT_TIM1_CH1   )
#define ADC_EXTERNALTRIG_T1_CC2          (LL_ADC_REG_TRIG_EXT_TIM1_CH2   )
#define ADC_EXTERNALTRIG_T1_CC3          (LL_ADC_REG_TRIG_EXT_TIM1_CH3   )
#define ADC_EXTERNALTRIG_T1_CC4          (LL_ADC_REG_TRIG_EXT_TIM1_CH4   )
#define ADC_EXTERNALTRIG_T1_CC5          (LL_ADC_REG_TRIG_EXT_TIM1_CH5   )
#define ADC_EXTERNALTRIG_T1_CC6          (LL_ADC_REG_TRIG_EXT_TIM1_CH6   )
#define ADC_EXTERNALTRIG_T3_CC1          (LL_ADC_REG_TRIG_EXT_TIM3_CH1   )
#define ADC_EXTERNALTRIG_T3_TRGO         (LL_ADC_REG_TRIG_EXT_TIM3_TRGO  )
#define ADC_EXTERNALTRIG_EXT_IT11        (LL_ADC_REG_TRIG_EXT_EXTI_LINE11)
#define ADC_EXTERNALTRIG_EXT_IT15        (LL_ADC_REG_TRIG_EXT_EXTI_LINE15)

/**
  * @}
  */

/** @defgroup ADC_HAL_EC_REG_OVR_DATA_BEHAVIOR  ADC group regular - Overrun behavior on conversion data
  * @{
  */
#define ADC_OVR_DATA_PRESERVED             (LL_ADC_REG_OVR_DATA_PRESERVED)    /*!< ADC group regular behavior in case
                                           of overrun: data preserved */
#define ADC_OVR_DATA_OVERWRITTEN           (LL_ADC_REG_OVR_DATA_OVERWRITTEN)  /*!< ADC group regular behavior in case
                                           of overrun: data overwritten */
/**
  * @}
  */

/** @defgroup ADC_regular_external_trigger_edge ADC group regular trigger edge (when external trigger is selected)
  * @{
  */
#define ADC_EXTERNALTRIGCONVEDGE_NONE           (0x00000000UL)                      /*!< ADC group regular trigger
                                                disabled (SW start)*/
#define ADC_EXTERNALTRIGCONVEDGE_RISING         (LL_ADC_REG_TRIG_EXT_RISING)        /*!< ADC group regular conversion
                                                trigger polarity set to rising edge */
#define ADC_EXTERNALTRIGCONVEDGE_FALLING        (LL_ADC_REG_TRIG_EXT_FALLING)       /*!< ADC group regular conversion
                                                trigger polarity set to falling edge */
#define ADC_EXTERNALTRIGCONVEDGE_RISINGFALLING  (LL_ADC_REG_TRIG_EXT_RISINGFALLING) /*!< ADC group regular conversion
                                                trigger polarity set to both rising and falling edges */
/**
  * @}
  */

/** @defgroup ADC_EOCSelection ADC sequencer end of unitary conversion or sequence conversions
  * @{
  */
#define ADC_EOC_SINGLE_CONV         (ADC_ISR_EOC)                 /*!< End of unitary conversion flag  */
#define ADC_EOC_SEQ_CONV            (ADC_ISR_EOS)                 /*!< End of sequence conversions flag    */
/**
  * @}
  */

/** @defgroup ADC_HAL_EC_REG_SEQ_RANKS  ADC group regular - Sequencer ranks
  * @{
  */
#define ADC_REGULAR_RANK_1                 (LL_ADC_REG_RANK_1)  /*!< ADC group regular sequencer rank 1 */
#define ADC_REGULAR_RANK_2                 (LL_ADC_REG_RANK_2)  /*!< ADC group regular sequencer rank 2 */
#define ADC_REGULAR_RANK_3                 (LL_ADC_REG_RANK_3)  /*!< ADC group regular sequencer rank 3 */
#define ADC_REGULAR_RANK_4                 (LL_ADC_REG_RANK_4)  /*!< ADC group regular sequencer rank 4 */
#define ADC_REGULAR_RANK_5                 (LL_ADC_REG_RANK_5)  /*!< ADC group regular sequencer rank 5 */
#define ADC_REGULAR_RANK_6                 (LL_ADC_REG_RANK_6)  /*!< ADC group regular sequencer rank 6 */
#define ADC_REGULAR_RANK_7                 (LL_ADC_REG_RANK_7)  /*!< ADC group regular sequencer rank 7 */
#define ADC_REGULAR_RANK_8                 (LL_ADC_REG_RANK_8)  /*!< ADC group regular sequencer rank 8 */
#define ADC_REGULAR_RANK_9                 (LL_ADC_REG_RANK_9)  /*!< ADC group regular sequencer rank 9 */
#define ADC_REGULAR_RANK_10                (LL_ADC_REG_RANK_10) /*!< ADC group regular sequencer rank 10 */
#define ADC_REGULAR_RANK_11                (LL_ADC_REG_RANK_11) /*!< ADC group regular sequencer rank 11 */
#define ADC_REGULAR_RANK_12                (LL_ADC_REG_RANK_12) /*!< ADC group regular sequencer rank 12 */
#define ADC_REGULAR_RANK_13                (LL_ADC_REG_RANK_13) /*!< ADC group regular sequencer rank 13 */
#define ADC_REGULAR_RANK_14                (LL_ADC_REG_RANK_14) /*!< ADC group regular sequencer rank 14 */
#define ADC_REGULAR_RANK_15                (LL_ADC_REG_RANK_15) /*!< ADC group regular sequencer rank 15 */
#define ADC_REGULAR_RANK_16                (LL_ADC_REG_RANK_16) /*!< ADC group regular sequencer rank 16 */
/**
  * @}
  */

/** @defgroup ADC_HAL_EC_CHANNEL_SAMPLINGTIME  Channel - Sampling time
  * @{
  */
#define ADC_SAMPLETIME_2CYCLES_5         (LL_ADC_SAMPLINGTIME_2CYCLES_5)    /*!< Sampling time 2.5 ADC clock cycles */
#define ADC_SAMPLETIME_6CYCLES_5         (LL_ADC_SAMPLINGTIME_6CYCLES_5)    /*!< Sampling time 6.5 ADC clock cycles */
#define ADC_SAMPLETIME_12CYCLES_5        (LL_ADC_SAMPLINGTIME_12CYCLES_5)   /*!< Sampling time 12.5 ADC clock cycles */
#define ADC_SAMPLETIME_24CYCLES_5        (LL_ADC_SAMPLINGTIME_24CYCLES_5)   /*!< Sampling time 24.5 ADC clock cycles */
#define ADC_SAMPLETIME_47CYCLES_5        (LL_ADC_SAMPLINGTIME_47CYCLES_5)   /*!< Sampling time 47.5 ADC clock cycles */
#define ADC_SAMPLETIME_92CYCLES_5        (LL_ADC_SAMPLINGTIME_92CYCLES_5)   /*!< Sampling time 92.5 ADC clock cycles */
#define ADC_SAMPLETIME_247CYCLES_5       (LL_ADC_SAMPLINGTIME_247CYCLES_5)  /*!< Sampling time 247.5 ADC clock cycles */
#define ADC_SAMPLETIME_640CYCLES_5       (LL_ADC_SAMPLINGTIME_640CYCLES_5)  /*!< Sampling time 640.5 ADC clock cycles */
/**
  * @}
  */

/** @defgroup ADC_HAL_EC_CHANNEL  ADC instance - Channel number
  * @{
  */
/* Note: VrefInt, TempSensor internal channels are not available on  */
/*        all ADC instances (refer to Reference Manual).                      */
#define ADC_CHANNEL_0                      (LL_ADC_CHANNEL_0)              /*!< External channel (GPIO pin) ADCx_IN0  */
#define ADC_CHANNEL_1                      (LL_ADC_CHANNEL_1)              /*!< External channel (GPIO pin) ADCx_IN1  */
#define ADC_CHANNEL_2                      (LL_ADC_CHANNEL_2)              /*!< External channel (GPIO pin) ADCx_IN2  */
#define ADC_CHANNEL_3                      (LL_ADC_CHANNEL_3)              /*!< External channel (GPIO pin) ADCx_IN3  */
#define ADC_CHANNEL_4                      (LL_ADC_CHANNEL_4)              /*!< External channel (GPIO pin) ADCx_IN4  */
#define ADC_CHANNEL_5                      (LL_ADC_CHANNEL_5)              /*!< External channel (GPIO pin) ADCx_IN5  */
#define ADC_CHANNEL_6                      (LL_ADC_CHANNEL_6)              /*!< External channel (GPIO pin) ADCx_IN6  */
#define ADC_CHANNEL_7                      (LL_ADC_CHANNEL_7)              /*!< External channel (GPIO pin) ADCx_IN7  */
#define ADC_CHANNEL_8                      (LL_ADC_CHANNEL_8)              /*!< External channel (GPIO pin) ADCx_IN8  */
#define ADC_CHANNEL_9                      (LL_ADC_CHANNEL_9)              /*!< External channel (GPIO pin) ADCx_IN9  */
#define ADC_CHANNEL_10                     (LL_ADC_CHANNEL_10)             /*!< External channel (GPIO pin) ADCx_IN10 */
#define ADC_CHANNEL_11                     (LL_ADC_CHANNEL_11)             /*!< External channel (GPIO pin) ADCx_IN11 */
#define ADC_CHANNEL_12                     (LL_ADC_CHANNEL_12)             /*!< External channel (GPIO pin) ADCx_IN12 */
#define ADC_CHANNEL_13                     (LL_ADC_CHANNEL_13)             /*!< External channel (GPIO pin) ADCx_IN13 */
#define ADC_CHANNEL_14                     (LL_ADC_CHANNEL_14)             /*!< External channel (GPIO pin) ADCx_IN14 */


#define ADC_CHANNEL_TEMPSENSOR             (LL_ADC_CHANNEL_TEMPSENSOR) 
#define ADC_CHANNEL_VREFINT                (LL_ADC_CHANNEL_VREFINT   ) 
#define ADC_CHANNEL_1_3VCCA                (LL_ADC_CHANNEL_1_3VCCA   ) 
#define ADC_CHANNEL_OPA1                   (LL_ADC_CHANNEL_OPA1      ) 
#define ADC_CHANNEL_OPA2                   (LL_ADC_CHANNEL_OPA2      ) 
/**
  * @}
  */

/** @defgroup ADC_analog_watchdog_filtering_config ADC analog watchdog (AWD) filtering configuration
  * @{
  */
#define ADC_AWD_FILTERING_NONE          (0x00000000UL)                            /*!< ADC AWD no filtering, one
out-of-window sample to raise flag or interrupt */
#define ADC_AWD_FILTERING_2SAMPLES      ((ADC_TR_AWDFILT_0))                     /*!< ADC AWD 2 consecutives
                                        out-of-window samples to raise flag or interrupt */
#define ADC_AWD_FILTERING_3SAMPLES      ((ADC_TR_AWDFILT_1))                     /*!< ADC AWD 3 consecutives
                                        out-of-window samples to raise flag or interrupt */
#define ADC_AWD_FILTERING_4SAMPLES      ((ADC_TR_AWDFILT_1 | ADC_TR_AWDFILT_0)) /*!< ADC AWD 4 consecutives
                                        out-of-window samples to raise flag or interrupt */
#define ADC_AWD_FILTERING_5SAMPLES      ((ADC_TR_AWDFILT_2))                     /*!< ADC AWD 5 consecutives
                                        out-of-window samples to raise flag or interrupt */
#define ADC_AWD_FILTERING_6SAMPLES      ((ADC_TR_AWDFILT_2 | ADC_TR_AWDFILT_0)) /*!< ADC AWD 6 consecutives
                                        out-of-window samples to raise flag or interrupt */
#define ADC_AWD_FILTERING_7SAMPLES      ((ADC_TR_AWDFILT_2 | ADC_TR_AWDFILT_1)) /*!< ADC AWD 7 consecutives
                                        out-of-window samples to raise flag or interrupt */
#define ADC_AWD_FILTERING_8SAMPLES      ((ADC_TR_AWDFILT_2 | ADC_TR_AWDFILT_1 \
                                          | ADC_TR_AWDFILT_0))                     /*!< ADC AWD 8 consecutives
                                        out-of-window samples to raise flag or interrupt */
/**
  * @}
  */

/** @defgroup ADC_analog_watchdog_mode ADC analog watchdog (AWD) mode
  * @{
  */
#define ADC_ANALOGWATCHDOG_NONE                 (0x00000000UL)                         /*!< ADC AWD not selected */
#define ADC_ANALOGWATCHDOG_SINGLE_REG           (ADC_CFGR_AWDSGL | ADC_CFGR_AWDEN)   /*!< ADC AWD applied to a regular
                                                group single channel */
#define ADC_ANALOGWATCHDOG_SINGLE_INJEC         (ADC_CFGR_AWDSGL | ADC_CFGR_JAWDEN)  /*!< ADC AWD applied to an
                                                injected group single channel */
#define ADC_ANALOGWATCHDOG_SINGLE_REGINJEC      (ADC_CFGR_AWDSGL | ADC_CFGR_AWDEN\
                                                 | ADC_CFGR_JAWDEN)                    /*!< ADC AWD applied to a regular
                                                and injected groups single channel */
#define ADC_ANALOGWATCHDOG_ALL_REG              (ADC_CFGR_AWDEN)                      /*!< ADC AWD applied to regular
                                                group all channels */
#define ADC_ANALOGWATCHDOG_ALL_INJEC            (ADC_CFGR_JAWDEN)                     /*!< ADC AWD applied to injected
                                                group all channels */
#define ADC_ANALOGWATCHDOG_ALL_REGINJEC         (ADC_CFGR_AWDEN | ADC_CFGR_JAWDEN)   /*!< ADC AWD applied to regular
                                                and injected groups all channels */
/**
  * @}
  */


/** @defgroup ADC_Event_type ADC Event type
  * @{
  */
/**
  * @note Analog watchdog 1 is available on all series
  */
#define ADC_EOSMP_EVENT          (ADC_FLAG_EOSMP) /*!< ADC End of Sampling event */
#define ADC_AWD_EVENT            (ADC_FLAG_AWD)   /*!< ADC Analog watchdog event (main analog watchdog)       */
#define ADC_OVR_EVENT            (ADC_FLAG_OVR)   /*!< ADC overrun event */
/**
  * @}
  */

/** @defgroup ADC_interrupts_definition ADC interrupts definition
  * @{
  */
#define ADC_IT_ADRDY         ADC_IER_ADRDYIE    /*!< ADC ready interrupt source */ 
#define ADC_IT_EOSMP         ADC_IER_EOSMPIE    /*!< ADC End of sampling interrupt source */
#define ADC_IT_EOC           ADC_IER_EOCIE      /*!< ADC End of regular conversion interrupt source */
#define ADC_IT_EOS           ADC_IER_EOSIE      /*!< ADC End of regular sequence of conversions interrupt source */
#define ADC_IT_OVR           ADC_IER_OVRIE      /*!< ADC overrun interrupt source */
#define ADC_IT_JEOC          ADC_IER_JEOCIE     /*!< ADC End of injected conversion interrupt source */
#define ADC_IT_JEOS          ADC_IER_JEOSIE     /*!< ADC End of injected sequence of conversions interrupt source */
#define ADC_IT_AWD           ADC_IER_AWDIE      /*!< ADC Analog watchdog 1 interrupt source (main analog watchdog) */
#define ADC_IT_EOCAL         ADC_IER_EOCALIE    /*!< ADC end of calibration interrupt source */

/**
  * @}
  */

/** @defgroup ADC_flags_definition ADC flags definition
  * @{
  */
#define ADC_FLAG_ADRDY         ADC_ISR_ADRDY    /*!< ADC ready flag */ 
#define ADC_FLAG_EOSMP         ADC_ISR_EOSMP    /*!< ADC End of Sampling flag */
#define ADC_FLAG_EOC           ADC_ISR_EOC      /*!< ADC End of Regular Conversion flag */
#define ADC_FLAG_EOS           ADC_ISR_EOS      /*!< ADC End of Regular sequence of Conversions flag */
#define ADC_FLAG_OVR           ADC_ISR_OVR      /*!< ADC overrun flag */
#define ADC_FLAG_JEOC          ADC_ISR_JEOC     /*!< ADC End of Injected Conversion flag */
#define ADC_FLAG_JEOS          ADC_ISR_JEOS     /*!< ADC End of Injected sequence of Conversions flag */
#define ADC_FLAG_AWD           ADC_ISR_AWD      /*!< ADC Analog watchdog 1 flag (main analog watchdog) */
#define ADC_FLAG_EOCAL         ADC_ISR_EOCAL    /*!< ADC end of calibration flag */

/**
  * @}
  */

/** @defgroup ADC_pwr_mode ADC Power Mode
  * @{
  */
#define ADC_POWER_MODE_6uA         0x00000000     
#define ADC_POWER_MODE_7uA         (                                          ADC_CCR_PWR_MODE_0)    
#define ADC_POWER_MODE_8uA         (                     ADC_CCR_PWR_MODE_1                     )
#define ADC_POWER_MODE_9uA         (                     ADC_CCR_PWR_MODE_1 | ADC_CCR_PWR_MODE_0)   
#define ADC_POWER_MODE_2uA         (ADC_CCR_PWR_MODE_2                                          )    
#define ADC_POWER_MODE_3uA         (ADC_CCR_PWR_MODE_2                      | ADC_CCR_PWR_MODE_0)
#define ADC_POWER_MODE_4uA         (ADC_CCR_PWR_MODE_2 | ADC_CCR_PWR_MODE_1                     )    
#define ADC_POWER_MODE_5uA         (ADC_CCR_PWR_MODE_2 | ADC_CCR_PWR_MODE_1 | ADC_CCR_PWR_MODE_0)      
/**
  * @}
  */

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/

/** @defgroup ADC_Private_Macros ADC Private Macros
  * @{
  */
/* Macro reserved for internal HAL driver usage, not intended to be used in   */
/* code of final user.                                                        */

/**
  * @brief Return resolution bits in CFGR register RES[1:0] field.
  * @param __HANDLE__ ADC handle
  * @retval Value of bitfield RES in CFGR register.
  */
#define ADC_GET_RESOLUTION(__HANDLE__)                                         \
  (LL_ADC_GetResolution((__HANDLE__)->Instance))

/**
  * @brief Clear ADC error code (set it to no error code "HAL_ADC_ERROR_NONE").
  * @param __HANDLE__ ADC handle
  * @retval None
  */
#define ADC_CLEAR_ERRORCODE(__HANDLE__) ((__HANDLE__)->ErrorCode = HAL_ADC_ERROR_NONE)

/**
  * @brief Simultaneously clear and set specific bits of the handle State.
  * @note  ADC_STATE_CLR_SET() macro is merely aliased to generic macro MODIFY_REG(),
  *        the first parameter is the ADC handle State, the second parameter is the
  *        bit field to clear, the third and last parameter is the bit field to set.
  * @retval None
  */
#define ADC_STATE_CLR_SET MODIFY_REG

/**
  * @brief Verify that a given value is aligned with the ADC resolution range.
  * @param __RESOLUTION__ ADC resolution (12, 10, 8 or 6 bits).
  * @param __ADC_VALUE__ value checked against the resolution.
  * @retval SET (__ADC_VALUE__ in line with __RESOLUTION__) or RESET (__ADC_VALUE__ not in line with __RESOLUTION__)
  */
#define IS_ADC_RANGE(__RESOLUTION__, __ADC_VALUE__) \
  ((__ADC_VALUE__) <= __LL_ADC_DIGITAL_SCALE(__RESOLUTION__))

/**
  * @brief Verify the length of the scheduled regular conversions group.
  * @param __LENGTH__ number of programmed conversions.
  * @retval SET (__LENGTH__ is within the maximum number of possible programmable regular conversions)
  *         or RESET (__LENGTH__ is null or too large)
  */
#define IS_ADC_REGULAR_NB_CONV(__LENGTH__) (((__LENGTH__) >= (1UL)) && ((__LENGTH__) <= (16UL)))


/**
  * @brief Verify the number of scheduled regular conversions in discontinuous mode.
  * @param NUMBER number of scheduled regular conversions in discontinuous mode.
  * @retval SET (NUMBER is within the maximum number of regular conversions in discontinuous mode)
  *         or RESET (NUMBER is null or too large)
  */
#define IS_ADC_REGULAR_DISCONT_NUMBER(NUMBER) (((NUMBER) >= (1UL)) && ((NUMBER) <= (8UL)))

/**
  * @brief Verify the ADC clock setting.
  * @param __ADC_CLOCK__ programmed ADC clock.
  * @retval SET (__ADC_CLOCK__ is a valid value) or RESET (__ADC_CLOCK__ is invalid)
  */
#define IS_ADC_CLOCKPRESCALER(__ADC_CLOCK__) (((__ADC_CLOCK__) == ADC_CLOCK_SYNC_PCLK_DIV1) || \
                                              ((__ADC_CLOCK__) == ADC_CLOCK_SYNC_PCLK_DIV2) || \
                                              ((__ADC_CLOCK__) == ADC_CLOCK_SYNC_PCLK_DIV4) || \
                                              ((__ADC_CLOCK__) == ADC_CLOCK_ASYNC_DIV1)     || \
                                              ((__ADC_CLOCK__) == ADC_CLOCK_ASYNC_DIV2)     || \
                                              ((__ADC_CLOCK__) == ADC_CLOCK_ASYNC_DIV4)     || \
                                              ((__ADC_CLOCK__) == ADC_CLOCK_ASYNC_DIV6)     || \
                                              ((__ADC_CLOCK__) == ADC_CLOCK_ASYNC_DIV8)     || \
                                              ((__ADC_CLOCK__) == ADC_CLOCK_ASYNC_DIV10)    || \
                                              ((__ADC_CLOCK__) == ADC_CLOCK_ASYNC_DIV12)    || \
                                              ((__ADC_CLOCK__) == ADC_CLOCK_ASYNC_DIV16)    || \
                                              ((__ADC_CLOCK__) == ADC_CLOCK_ASYNC_DIV32)    || \
                                              ((__ADC_CLOCK__) == ADC_CLOCK_ASYNC_DIV64)    || \
                                              ((__ADC_CLOCK__) == ADC_CLOCK_ASYNC_DIV128)   || \
                                              ((__ADC_CLOCK__) == ADC_CLOCK_ASYNC_DIV256) )

/**
  * @brief Verify the ADC resolution setting.
  * @param __RESOLUTION__ programmed ADC resolution.
  * @retval SET (__RESOLUTION__ is a valid value) or RESET (__RESOLUTION__ is invalid)
  */
#define IS_ADC_RESOLUTION(__RESOLUTION__) (((__RESOLUTION__) == ADC_RESOLUTION_12B) || \
                                           ((__RESOLUTION__) == ADC_RESOLUTION_10B) || \
                                           ((__RESOLUTION__) == ADC_RESOLUTION_8B)  || \
                                           ((__RESOLUTION__) == ADC_RESOLUTION_6B)    )

/**
  * @brief Verify the ADC resolution setting when limited to 6 or 8 bits.
  * @param __RESOLUTION__ programmed ADC resolution when limited to 6 or 8 bits.
  * @retval SET (__RESOLUTION__ is a valid value) or RESET (__RESOLUTION__ is invalid)
  */
#define IS_ADC_RESOLUTION_8_6_BITS(__RESOLUTION__) (((__RESOLUTION__) == ADC_RESOLUTION_8B) || \
                                                    ((__RESOLUTION__) == ADC_RESOLUTION_6B)   )

/**
  * @brief Verify the ADC converted data alignment.
  * @param __ALIGN__ programmed ADC converted data alignment.
  * @retval SET (__ALIGN__ is a valid value) or RESET (__ALIGN__ is invalid)
  */
#define IS_ADC_DATA_ALIGN(__ALIGN__) (((__ALIGN__) == ADC_DATAALIGN_RIGHT) || \
                                      ((__ALIGN__) == ADC_DATAALIGN_LEFT)    )

/**
  * @brief Verify the ADC gain compensation.
  * @param __GAIN_COMPENSATION__ programmed ADC gain compensation coefficient.
  * @retval SET (__GAIN_COMPENSATION__ is a valid value) or RESET (__GAIN_COMPENSATION__ is invalid)
  */
#define IS_ADC_GAIN_COMPENSATION(__GAIN_COMPENSATION__) ((__GAIN_COMPENSATION__) <= 16383UL)

/**
  * @brief Verify the ADC scan mode.
  * @param __SCAN_MODE__ programmed ADC scan mode.
  * @retval SET (__SCAN_MODE__ is valid) or RESET (__SCAN_MODE__ is invalid)
  */
#define IS_ADC_SCAN_MODE(__SCAN_MODE__) (((__SCAN_MODE__) == ADC_SCAN_DISABLE) || \
                                         ((__SCAN_MODE__) == ADC_SCAN_ENABLE)    )

/**
  * @brief Verify the ADC edge trigger setting for regular group.
  * @param __EDGE__ programmed ADC edge trigger setting.
  * @retval SET (__EDGE__ is a valid value) or RESET (__EDGE__ is invalid)
  */
#define IS_ADC_EXTTRIG_EDGE(__EDGE__) (((__EDGE__) == ADC_EXTERNALTRIGCONVEDGE_NONE)         || \
                                       ((__EDGE__) == ADC_EXTERNALTRIGCONVEDGE_RISING)       || \
                                       ((__EDGE__) == ADC_EXTERNALTRIGCONVEDGE_FALLING)      || \
                                       ((__EDGE__) == ADC_EXTERNALTRIGCONVEDGE_RISINGFALLING)  )

/**
  * @brief Verify the ADC regular conversions external trigger.
  * @param __HANDLE__ ADC handle
  * @param __REGTRIG__ programmed ADC regular conversions external trigger.
  * @retval SET (__REGTRIG__ is a valid value) or RESET (__REGTRIG__ is invalid)
  */
#define IS_ADC_EXTTRIG(__HANDLE__, __REGTRIG__) (((__REGTRIG__) == ADC_EXTERNALTRIG_T1_TRGO   )  || \
                                                 ((__REGTRIG__) == ADC_EXTERNALTRIG_T1_CC1    )  || \
                                                 ((__REGTRIG__) == ADC_EXTERNALTRIG_TI_CC2    )  || \
                                                 ((__REGTRIG__) == ADC_EXTERNALTRIG_T1_CC3    )  || \
                                                 ((__REGTRIG__) == ADC_EXTERNALTRIG_T1_CC4    )  || \
                                                 ((__REGTRIG__) == ADC_EXTERNALTRIG_T1_CC5   )  || \
                                                 ((__REGTRIG__) == ADC_EXTERNALTRIG_T1_CC6    )  || \
                                                 ((__REGTRIG__) == ADC_EXTERNALTRIG_T3_CC1    )  || \
                                                 ((__REGTRIG__) == ADC_EXTERNALTRIG_T3_TRGO   )  || \
                                                 ((__REGTRIG__) == ADC_EXTERNALTRIG_EXT_IT11  )  || \
                                                 ((__REGTRIG__) == ADC_EXTERNALTRIG_EXT_IT15  )  || \
                                                 ((__REGTRIG__) == ADC_SOFTWARE_START         ))

/**
  * @brief Verify the ADC regular conversions check for converted data availability.
  * @param __EOC_SELECTION__ converted data availability check.
  * @retval SET (__EOC_SELECTION__ is a valid value) or RESET (__EOC_SELECTION__ is invalid)
  */
#define IS_ADC_EOC_SELECTION(__EOC_SELECTION__) (((__EOC_SELECTION__) == ADC_EOC_SINGLE_CONV)    || \
                                                 ((__EOC_SELECTION__) == ADC_EOC_SEQ_CONV)  )

/**
  * @brief Verify the ADC regular conversions overrun handling.
  * @param __OVR__ ADC regular conversions overrun handling.
  * @retval SET (__OVR__ is a valid value) or RESET (__OVR__ is invalid)
  */
#define IS_ADC_OVERRUN(__OVR__) (((__OVR__) == ADC_OVR_DATA_PRESERVED)  || \
                                 ((__OVR__) == ADC_OVR_DATA_OVERWRITTEN)  )                                               

/**
  * @brief Verify the ADC conversions sampling time.
  * @param __TIME__ ADC conversions sampling time.
  * @retval SET (__TIME__ is a valid value) or RESET (__TIME__ is invalid)
  */
#define IS_ADC_SAMPLE_TIME(__TIME__) (((__TIME__) == ADC_SAMPLETIME_2CYCLES_5)   || \
                                      ((__TIME__) == ADC_SAMPLETIME_6CYCLES_5)   || \
                                      ((__TIME__) == ADC_SAMPLETIME_12CYCLES_5)  || \
                                      ((__TIME__) == ADC_SAMPLETIME_24CYCLES_5)  || \
                                      ((__TIME__) == ADC_SAMPLETIME_47CYCLES_5)  || \
                                      ((__TIME__) == ADC_SAMPLETIME_92CYCLES_5)  || \
                                      ((__TIME__) == ADC_SAMPLETIME_247CYCLES_5) || \
                                      ((__TIME__) == ADC_SAMPLETIME_640CYCLES_5)   )

/**
  * @brief Verify the ADC reference config.
  * @param __VREFBUF__ ADC reference config.
  * @retval SET (__VREFBUF__ is a valid value) or RESET (__VREFBUF__ is invalid)
  */
#define IS_ADC_VREFBUF(__VREFBUF__) (((__VREFBUF__) == ADC_VREFBUF_VCCA  )  || \
                                     ((__VREFBUF__) == ADC_VREFBUF_1P024V)  || \
                                     ((__VREFBUF__) == ADC_VREFBUF_1P5V  )  || \
                                     ((__VREFBUF__) == ADC_VREFBUF_2P048V))

/**
  * @brief Verify the ADC regular channel setting.
  * @param  __CHANNEL__ programmed ADC regular channel.
  * @retval SET (__CHANNEL__ is valid) or RESET (__CHANNEL__ is invalid)
  */
#define IS_ADC_REGULAR_RANK(__CHANNEL__) (((__CHANNEL__) == ADC_REGULAR_RANK_1 ) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_2 ) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_3 ) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_4 ) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_5 ) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_6 ) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_7 ) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_8 ) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_9 ) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_10) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_11) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_12) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_13) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_14) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_15) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_16)   )

/**
  * @}
  */


/* Private constants ---------------------------------------------------------*/

/** @defgroup ADC_Private_Constants ADC Private Constants
  * @{
  */

/* Fixed timeout values for ADC conversion (including sampling time)        */
/* Maximum sampling time is 640.5 ADC clock cycle (SMPx[2:0] = 0b111        */
/* Maximum conversion time is 12.5 + Maximum sampling time                  */
/*                       or 12.5  + 640.5 = 653 ADC clock cycles            */
#define ADC_STOP_CONVERSION_TIMEOUT     ( 5UL)     /*!< ADC stop time-out value */

/* Delay for temperature sensor stabilization time.                         */
/* Maximum delay is 120us (refer device datasheet, parameter tSTART).       */
/* Unit: us                                                                 */
#define ADC_TEMPSENSOR_DELAY_US         (LL_ADC_DELAY_TEMPSENSOR_STAB_US)

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/** @defgroup ADC_Exported_Macros ADC Exported Macros
  * @{
  */
/* Macro for internal HAL driver usage, and possibly can be used into code of */
/* final user.                                                                */

/** @defgroup ADC_HAL_EM_HANDLE_IT_FLAG HAL ADC macro to manage HAL ADC handle, IT and flags.
  * @{
  */

/** @brief  Reset ADC handle state.
  * @param __HANDLE__ ADC handle
  * @retval None
  */
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
#define __HAL_ADC_RESET_HANDLE_STATE(__HANDLE__)                               \
  do{                                                                          \
    (__HANDLE__)->State = HAL_ADC_STATE_RESET;                                 \
    (__HANDLE__)->MspInitCallback = NULL;                                      \
    (__HANDLE__)->MspDeInitCallback = NULL;                                    \
  } while(0)
#else
#define __HAL_ADC_RESET_HANDLE_STATE(__HANDLE__)                               \
  ((__HANDLE__)->State = HAL_ADC_STATE_RESET)
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */

/**
  * @brief Enable ADC interrupt.
  * @param __HANDLE__ ADC handle
  * @param __INTERRUPT__ ADC Interrupt
  *        This parameter can be one of the following values:
  *            @arg @ref ADC_IT_ADRDY  ADC ready interrupt source
  *            @arg @ref ADC_IT_EOSMP  ADC End of Sampling interrupt source
  *            @arg @ref ADC_IT_EOC    ADC End of Regular Conversion interrupt source
  *            @arg @ref ADC_IT_EOS    ADC End of Regular sequence of Conversions interrupt source
  *            @arg @ref ADC_IT_OVR    ADC overrun interrupt source
  *            @arg @ref ADC_IT_JEOC   ADC End of Injected Conversion interrupt source
  *            @arg @ref ADC_IT_JEOS   ADC End of Injected sequence of Conversions interrupt source
  *            @arg @ref ADC_IT_AWD    ADC Analog watchdog interrupt source (main analog watchdog)
  *            @arg @ref ADC_IT_EOCAL  ADC end of calibration interrupt source
  * @retval None
  */
#define __HAL_ADC_ENABLE_IT(__HANDLE__, __INTERRUPT__)                         \
  (((__HANDLE__)->Instance->IER) |= (__INTERRUPT__))

/**
  * @brief Disable ADC interrupt.
  * @param __HANDLE__ ADC handle
  * @param __INTERRUPT__ ADC Interrupt
  *        This parameter can be one of the following values:
  *            @arg @ref ADC_IT_ADRDY  ADC ready interrupt source
  *            @arg @ref ADC_IT_EOSMP  ADC End of Sampling interrupt source
  *            @arg @ref ADC_IT_EOC    ADC End of Regular Conversion interrupt source
  *            @arg @ref ADC_IT_EOS    ADC End of Regular sequence of Conversions interrupt source
  *            @arg @ref ADC_IT_OVR    ADC overrun interrupt source
  *            @arg @ref ADC_IT_JEOC   ADC End of Injected Conversion interrupt source
  *            @arg @ref ADC_IT_JEOS   ADC End of Injected sequence of Conversions interrupt source
  *            @arg @ref ADC_IT_AWD    ADC Analog watchdog interrupt source (main analog watchdog)
  *            @arg @ref ADC_IT_EOCAL  ADC end of calibration interrupt source
  * @retval None
  */
#define __HAL_ADC_DISABLE_IT(__HANDLE__, __INTERRUPT__)                        \
  (((__HANDLE__)->Instance->IER) &= ~(__INTERRUPT__))

/** @brief  Checks if the specified ADC interrupt source is enabled or disabled.
  * @param __HANDLE__ ADC handle
  * @param __INTERRUPT__ ADC interrupt source to check
  *          This parameter can be one of the following values:
  *            @arg @ref ADC_IT_ADRDY  ADC ready interrupt source
  *            @arg @ref ADC_IT_EOSMP  ADC End of Sampling interrupt source
  *            @arg @ref ADC_IT_EOC    ADC End of Regular Conversion interrupt source
  *            @arg @ref ADC_IT_EOS    ADC End of Regular sequence of Conversions interrupt source
  *            @arg @ref ADC_IT_OVR    ADC overrun interrupt source
  *            @arg @ref ADC_IT_JEOC   ADC End of Injected Conversion interrupt source
  *            @arg @ref ADC_IT_JEOS   ADC End of Injected sequence of Conversions interrupt source
  *            @arg @ref ADC_IT_AWD    ADC Analog watchdog interrupt source (main analog watchdog)
  *            @arg @ref ADC_IT_EOCAL  ADC end of calibration interrupt source
  * @retval State of interruption (SET or RESET)
  */
#define __HAL_ADC_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)                     \
  (((__HANDLE__)->Instance->IER & (__INTERRUPT__)) == (__INTERRUPT__))

/**
  * @brief Check whether the specified ADC flag is set or not.
  * @param __HANDLE__ ADC handle
  * @param __FLAG__ ADC flag
  *        This parameter can be one of the following values:
  *            @arg @ref ADC_FLAG_RDY     ADC ready flag
  *            @arg @ref ADC_FLAG_EOSMP   ADC End of Sampling flag
  *            @arg @ref ADC_FLAG_EOC     ADC End of Regular Conversion flag
  *            @arg @ref ADC_FLAG_EOS     ADC End of Regular sequence of Conversions flag
  *            @arg @ref ADC_FLAG_OVR     ADC overrun flag
  *            @arg @ref ADC_FLAG_JEOC    ADC End of Injected Conversion flag
  *            @arg @ref ADC_FLAG_JEOS    ADC End of Injected sequence of Conversions flag
  *            @arg @ref ADC_FLAG_AWD     ADC Analog watchdog flag (main analog watchdog)
  *            @arg @ref ADC_FLAG_EOCAL   ADC end of calibration flag
  * @retval State of flag (TRUE or FALSE).
  */
#define __HAL_ADC_GET_FLAG(__HANDLE__, __FLAG__)                               \
  ((((__HANDLE__)->Instance->ISR) & (__FLAG__)) == (__FLAG__))

/**
  * @brief Clear the specified ADC flag.
  * @param __HANDLE__ ADC handle
  * @param __FLAG__ ADC flag
  *        This parameter can be one of the following values:
  *            @arg @ref ADC_FLAG_RDY     ADC ready flag
  *            @arg @ref ADC_FLAG_EOSMP   ADC End of Sampling flag
  *            @arg @ref ADC_FLAG_EOC     ADC End of Regular Conversion flag
  *            @arg @ref ADC_FLAG_EOS     ADC End of Regular sequence of Conversions flag
  *            @arg @ref ADC_FLAG_OVR     ADC overrun flag
  *            @arg @ref ADC_FLAG_JEOC    ADC End of Injected Conversion flag
  *            @arg @ref ADC_FLAG_JEOS    ADC End of Injected sequence of Conversions flag
  *            @arg @ref ADC_FLAG_AWD     ADC Analog watchdog flag (main analog watchdog)
  *            @arg @ref ADC_FLAG_EOCAL   ADC end of calibration flag
  * @retval None
  */
/* Note: bit cleared bit by writing 1 (writing 0 has no effect on any bit of register ISR) */
#define __HAL_ADC_CLEAR_FLAG(__HANDLE__, __FLAG__)                             \
  (((__HANDLE__)->Instance->ISR) = (__FLAG__))

/**
  * @}
  */

/** @defgroup ADC_HAL_EM_HELPER_MACRO HAL ADC helper macro
  * @{
  */

/**
  * @brief  Helper macro to get ADC channel number in decimal format
  *         from literals ADC_CHANNEL_x.
  * @note   Example:
  *           __HAL_ADC_CHANNEL_TO_DECIMAL_NB(ADC_CHANNEL_4)
  *           will return decimal number "4".
  * @note   The input can be a value from functions where a channel
  *         number is returned, either defined with number
  *         or with bitfield (only one bit must be set).
  * @param  __CHANNEL__ This parameter can be one of the following values:
  *         @arg @ref ADC_CHANNEL_0
  *         @arg @ref ADC_CHANNEL_1                 
  *         @arg @ref ADC_CHANNEL_2                 
  *         @arg @ref ADC_CHANNEL_3                 
  *         @arg @ref ADC_CHANNEL_4                 
  *         @arg @ref ADC_CHANNEL_5                 
  *         @arg @ref ADC_CHANNEL_6
  *         @arg @ref ADC_CHANNEL_7
  *         @arg @ref ADC_CHANNEL_8
  *         @arg @ref ADC_CHANNEL_9
  *         @arg @ref ADC_CHANNEL_10
  *         @arg @ref ADC_CHANNEL_11
  *         @arg @ref ADC_CHANNEL_12
  *         @arg @ref ADC_CHANNEL_13
  *         @arg @ref ADC_CHANNEL_14
  *         @arg @ref ADC_CHANNEL_TEMPSENSOR          
  *         @arg @ref ADC_CHANNEL_VREFINT     
  *         @arg @ref ADC_CHANNEL_1_3VCCA        
  *         @arg @ref ADC_CHANNEL_OPA1                     
  *         @arg @ref ADC_CHANNEL_OPA2                      
  * @note   On this chip series, above parameter are not available on all ADC instances.\n
  *         On this chip series, all ADCx are not available on all devices. Refer to device datasheet
  *         for more details.
  * @retval Value between Min_Data=0 and Max_Data=19
  */
#define __HAL_ADC_CHANNEL_TO_DECIMAL_NB(__CHANNEL__)                           \
  __LL_ADC_CHANNEL_TO_DECIMAL_NB((__CHANNEL__))

/**
  * @brief  Helper macro to get ADC channel in literal format ADC_CHANNEL_x
  *         from number in decimal format.
  * @note   Example:
  *           __HAL_ADC_DECIMAL_NB_TO_CHANNEL(4)
  *           will return a data equivalent to "ADC_CHANNEL_4".
  * @param  __DECIMAL_NB__ Value between Min_Data=0 and Max_Data=18
  * @retval Returned value can be one of the following values:
  *         @arg @ref ADC_CHANNEL_0
  *         @arg @ref ADC_CHANNEL_1                 
  *         @arg @ref ADC_CHANNEL_2                 
  *         @arg @ref ADC_CHANNEL_3                 
  *         @arg @ref ADC_CHANNEL_4                 
  *         @arg @ref ADC_CHANNEL_5                 
  *         @arg @ref ADC_CHANNEL_6
  *         @arg @ref ADC_CHANNEL_7
  *         @arg @ref ADC_CHANNEL_8
  *         @arg @ref ADC_CHANNEL_9
  *         @arg @ref ADC_CHANNEL_10
  *         @arg @ref ADC_CHANNEL_11
  *         @arg @ref ADC_CHANNEL_12
  *         @arg @ref ADC_CHANNEL_13
  *         @arg @ref ADC_CHANNEL_14
  *         @arg @ref ADC_CHANNEL_TEMPSENSOR          
  *         @arg @ref ADC_CHANNEL_VREFINT     
  *         @arg @ref ADC_CHANNEL_1_3VCCA        
  *         @arg @ref ADC_CHANNEL_OPA1                     
  *         @arg @ref ADC_CHANNEL_OPA2          
  * @note   On this chip series, above parameter are not available on all ADC instances.\n
  *         On this chip series, all ADCx are not available on all devices. Refer to device datasheet
  *         for more details.
  */
#define __HAL_ADC_DECIMAL_NB_TO_CHANNEL(__DECIMAL_NB__)                        \
  __LL_ADC_DECIMAL_NB_TO_CHANNEL((__DECIMAL_NB__))

/**
  * @brief  Helper macro to determine whether the selected channel
  *         corresponds to literal definitions of driver.
  * @note   The different literal definitions of ADC channels are:
  *         - ADC internal channel:
  *           ADC_CHANNEL_VREFINT, ADC_CHANNEL_TEMPSENSOR, ...
  *         - ADC external channel (channel connected to a GPIO pin):
  *           ADC_CHANNEL_1, ADC_CHANNEL_2, ...
  * @note   The channel parameter must be a value defined from literal
  *         definition of a ADC internal channel (ADC_CHANNEL_VREFINT,
  *         ADC_CHANNEL_TEMPSENSOR, ...),
  *         ADC external channel (ADC_CHANNEL_1, ADC_CHANNEL_2, ...),
  *         must not be a value from functions where a channel number is
  *         returned from ADC registers,
  *         because internal and external channels share the same channel
  *         number in ADC registers. The differentiation is made only with
  *         parameters definitions of driver.
  * @param  __CHANNEL__ This parameter can be one of the following values:
  *         @arg @ref ADC_CHANNEL_0
  *         @arg @ref ADC_CHANNEL_1                 
  *         @arg @ref ADC_CHANNEL_2                 
  *         @arg @ref ADC_CHANNEL_3                 
  *         @arg @ref ADC_CHANNEL_4                 
  *         @arg @ref ADC_CHANNEL_5                 
  *         @arg @ref ADC_CHANNEL_6
  *         @arg @ref ADC_CHANNEL_7
  *         @arg @ref ADC_CHANNEL_8
  *         @arg @ref ADC_CHANNEL_9
  *         @arg @ref ADC_CHANNEL_10
  *         @arg @ref ADC_CHANNEL_11
  *         @arg @ref ADC_CHANNEL_12
  *         @arg @ref ADC_CHANNEL_13
  *         @arg @ref ADC_CHANNEL_14
  *         @arg @ref ADC_CHANNEL_TEMPSENSOR          
  *         @arg @ref ADC_CHANNEL_VREFINT     
  *         @arg @ref ADC_CHANNEL_1_3VCCA        
  *         @arg @ref ADC_CHANNEL_OPA1                     
  *         @arg @ref ADC_CHANNEL_OPA2             
  * @note   On this chip series, above parameter are not available on all ADC instances.\n
  *         On this chip series, all ADCx are not available on all devices. Refer to device datasheet
  *         for more details.
  * @retval Value "0" if the channel corresponds to a parameter definition of a ADC external channel (channel
  *         connected to a GPIO pin).
  *         Value "1" if the channel corresponds to a parameter definition of a ADC internal channel.
  */
#define __HAL_ADC_IS_CHANNEL_INTERNAL(__CHANNEL__)                             \
  __LL_ADC_IS_CHANNEL_INTERNAL((__CHANNEL__))

/**
  * @brief  Helper macro to convert a channel defined from parameter
  *         definition of a ADC internal channel (ADC_CHANNEL_VREFINT,
  *         ADC_CHANNEL_TEMPSENSOR, ...),
  *         to its equivalent parameter definition of a ADC external channel
  *         (ADC_CHANNEL_1, ADC_CHANNEL_2, ...).
  * @note   The channel parameter can be, additionally to a value
  *         defined from parameter definition of a ADC internal channel
  *         (ADC_CHANNEL_VREFINT, ADC_CHANNEL_TEMPSENSOR, ...),
  *         a value defined from parameter definition of
  *         ADC external channel (ADC_CHANNEL_1, ADC_CHANNEL_2, ...)
  *         or a value from functions where a channel number is returned
  *         from ADC registers.
  * @param  __CHANNEL__ This parameter can be one of the following values:
  *         @arg @ref ADC_CHANNEL_0
  *         @arg @ref ADC_CHANNEL_1                 
  *         @arg @ref ADC_CHANNEL_2                 
  *         @arg @ref ADC_CHANNEL_3                 
  *         @arg @ref ADC_CHANNEL_4                 
  *         @arg @ref ADC_CHANNEL_5                 
  *         @arg @ref ADC_CHANNEL_6
  *         @arg @ref ADC_CHANNEL_7
  *         @arg @ref ADC_CHANNEL_8
  *         @arg @ref ADC_CHANNEL_9
  *         @arg @ref ADC_CHANNEL_10
  *         @arg @ref ADC_CHANNEL_11
  *         @arg @ref ADC_CHANNEL_12
  *         @arg @ref ADC_CHANNEL_13
  *         @arg @ref ADC_CHANNEL_14
  *         @arg @ref ADC_CHANNEL_TEMPSENSOR          
  *         @arg @ref ADC_CHANNEL_VREFINT     
  *         @arg @ref ADC_CHANNEL_1_3VCCA        
  *         @arg @ref ADC_CHANNEL_OPA1                     
  *         @arg @ref ADC_CHANNEL_OPA2            
  * @note   On this chip series, above parameter are not available on all ADC instances.\n
  *         On this chip series, all ADCx are not available on all devices. Refer to device datasheet
  *         for more details.
  * @retval Returned value can be one of the following values:
  *         @arg @ref ADC_CHANNEL_0
  *         @arg @ref ADC_CHANNEL_1                 
  *         @arg @ref ADC_CHANNEL_2                 
  *         @arg @ref ADC_CHANNEL_3                 
  *         @arg @ref ADC_CHANNEL_4                 
  *         @arg @ref ADC_CHANNEL_5                 
  *         @arg @ref ADC_CHANNEL_6
  *         @arg @ref ADC_CHANNEL_7
  *         @arg @ref ADC_CHANNEL_8
  *         @arg @ref ADC_CHANNEL_9
  *         @arg @ref ADC_CHANNEL_10
  *         @arg @ref ADC_CHANNEL_11
  *         @arg @ref ADC_CHANNEL_12
  *         @arg @ref ADC_CHANNEL_13
  *         @arg @ref ADC_CHANNEL_14
  */
#define __HAL_ADC_CHANNEL_INTERNAL_TO_EXTERNAL(__CHANNEL__)                    \
  __LL_ADC_CHANNEL_INTERNAL_TO_EXTERNAL((__CHANNEL__))

/**
  * @brief  Helper macro to select the ADC common instance
  *         to which is belonging the selected ADC instance.
  * @note   ADC common register instance can be used for:
  *         - Set parameters common to several ADC instances
  *         - Multimode (for devices with several ADC instances)
  *         Refer to functions having argument "ADCxy_COMMON" as parameter.
  * @param  __ADCx__ ADC instance
  * @retval ADC common register instance
  */
#define __HAL_ADC_COMMON_INSTANCE(__ADCx__)                                    \
  __LL_ADC_COMMON_INSTANCE((__ADCx__))

/**
  * @brief  Helper macro to check if all ADC instances sharing the same
  *         ADC common instance are disabled.
  * @note   This check is required by functions with setting conditioned to
  *         ADC state:
  *         All ADC instances of the ADC common group must be disabled.
  *         Refer to functions having argument "ADCxy_COMMON" as parameter.
  * @note   On devices with only 1 ADC common instance, parameter of this macro
  *         is useless and can be ignored (parameter kept for compatibility
  *         with devices featuring several ADC common instances).
  * @param  __ADCXY_COMMON__ ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval Value "0" if all ADC instances sharing the same ADC common instance
  *         are disabled.
  *         Value "1" if at least one ADC instance sharing the same ADC common instance
  *         is enabled.
  */
#define __HAL_ADC_IS_ENABLED_ALL_COMMON_INSTANCE(__ADCXY_COMMON__)              \
  __LL_ADC_IS_ENABLED_ALL_COMMON_INSTANCE((__ADCXY_COMMON__))

/**
  * @brief  Helper macro to define the ADC conversion data full-scale digital
  *         value corresponding to the selected ADC resolution.
  * @note   ADC conversion data full-scale corresponds to voltage range
  *         determined by analog voltage references Vref+ and Vref-
  *         (refer to reference manual).
  * @param  __ADC_RESOLUTION__ This parameter can be one of the following values:
  *         @arg @ref ADC_RESOLUTION_12B
  *         @arg @ref ADC_RESOLUTION_10B
  *         @arg @ref ADC_RESOLUTION_8B
  *         @arg @ref ADC_RESOLUTION_6B
  * @retval ADC conversion data full-scale digital value
  */
#define __HAL_ADC_DIGITAL_SCALE(__ADC_RESOLUTION__)                             \
  __LL_ADC_DIGITAL_SCALE((__ADC_RESOLUTION__))

/**
  * @brief  Helper macro to convert the ADC conversion data from
  *         a resolution to another resolution.
  * @param  __DATA__ ADC conversion data to be converted
  * @param  __ADC_RESOLUTION_CURRENT__ Resolution of to the data to be converted
  *         This parameter can be one of the following values:
  *         @arg @ref ADC_RESOLUTION_12B
  *         @arg @ref ADC_RESOLUTION_10B
  *         @arg @ref ADC_RESOLUTION_8B
  *         @arg @ref ADC_RESOLUTION_6B
  * @param  __ADC_RESOLUTION_TARGET__ Resolution of the data after conversion
  *         This parameter can be one of the following values:
  *         @arg @ref ADC_RESOLUTION_12B
  *         @arg @ref ADC_RESOLUTION_10B
  *         @arg @ref ADC_RESOLUTION_8B
  *         @arg @ref ADC_RESOLUTION_6B
  * @retval ADC conversion data to the requested resolution
  */
#define __HAL_ADC_CONVERT_DATA_RESOLUTION(__DATA__,\
                                          __ADC_RESOLUTION_CURRENT__,\
                                          __ADC_RESOLUTION_TARGET__) \
__LL_ADC_CONVERT_DATA_RESOLUTION((__DATA__),\
                                 (__ADC_RESOLUTION_CURRENT__),\
                                 (__ADC_RESOLUTION_TARGET__))

/**
  * @brief  Helper macro to calculate the voltage (unit: mVolt)
  *         corresponding to a ADC conversion data (unit: digital value).
  * @note   Analog reference voltage (Vref+) must be either known from
  *         user board environment or can be calculated using ADC measurement
  * @param  __VREFANALOG_VOLTAGE__ Analog reference voltage (unit: mV)
  * @param  __ADC_DATA__ ADC conversion data (resolution 12 bits)
  *                       (unit: digital value).
  * @param  __ADC_RESOLUTION__ This parameter can be one of the following values:
  *         @arg @ref ADC_RESOLUTION_12B
  *         @arg @ref ADC_RESOLUTION_10B
  *         @arg @ref ADC_RESOLUTION_8B
  *         @arg @ref ADC_RESOLUTION_6B
  * @retval ADC conversion data equivalent voltage value (unit: mVolt)
  */
#define __HAL_ADC_CALC_DATA_TO_VOLTAGE(__VREFANALOG_VOLTAGE__,\
                                       __ADC_DATA__,\
                                       __ADC_RESOLUTION__) \
__LL_ADC_CALC_DATA_TO_VOLTAGE((__VREFANALOG_VOLTAGE__),\
                              (__ADC_DATA__),\
                              (__ADC_RESOLUTION__))

/**
  * @brief  Helper macro to calculate the voltage (unit: mVolt)
  *         corresponding to a ADC conversion data (unit: digital value)
  *         in differential ended mode.
  * @note   Analog reference voltage (Vref+) must be either known from
  *         user board environment or can be calculated using ADC measurement
  * @param  __VREFANALOG_VOLTAGE__ Analog reference voltage (unit: mV)
  * @param  __ADC_DATA__ ADC conversion data (resolution 12 bits)
  *                       (unit: digital value).
  * @param  __ADC_RESOLUTION__ This parameter can be one of the following values:
  *         @arg @ref ADC_RESOLUTION_12B
  *         @arg @ref ADC_RESOLUTION_10B
  *         @arg @ref ADC_RESOLUTION_8B
  *         @arg @ref ADC_RESOLUTION_6B
  * @retval ADC conversion data equivalent voltage value (unit: mVolt)
  */
#define __HAL_ADC_CALC_DIFF_DATA_TO_VOLTAGE(__VREFANALOG_VOLTAGE__,\
                                            __ADC_DATA__,\
                                            __ADC_RESOLUTION__) \
__LL_ADC_CALC_DIFF_DATA_TO_VOLTAGE((__VREFANALOG_VOLTAGE__),\
                                   (__ADC_DATA__),\
                                   (__ADC_RESOLUTION__))

/**
  * @brief  Helper macro to calculate the temperature (unit: degree Celsius)
  *         from ADC conversion data of internal temperature sensor.
  * @note   Computation is using temperature sensor calibration values
  *         stored in system memory for each device during production.
  * @note   Calculation formula:
  *           Temperature = ((TS_ADC_DATA - TS_CAL1)
  *                           * (TS_CAL2_TEMP - TS_CAL1_TEMP))
  *                         / (TS_CAL2 - TS_CAL1) + TS_CAL1_TEMP
  *           with TS_ADC_DATA = temperature sensor raw data measured by ADC
  *                Avg_Slope = (TS_CAL2 - TS_CAL1)
  *                            / (TS_CAL2_TEMP - TS_CAL1_TEMP)
  *                TS_CAL1   = equivalent TS_ADC_DATA at temperature
  *                            TEMP_DEGC_CAL1 (calibrated in factory)
  *                TS_CAL2   = equivalent TS_ADC_DATA at temperature
  *                            TEMP_DEGC_CAL2 (calibrated in factory)
  *         Caution: Calculation relevancy under reserve that calibration
  *                  parameters are correct (address and data).
  *                  To calculate temperature using temperature sensor
  *                  datasheet typical values (generic values less, therefore
  *                  less accurate than calibrated values),
  *                  use helper macro @ref __LL_ADC_CALC_TEMPERATURE_TYP_PARAMS().
  * @note   As calculation input, the analog reference voltage (Vref+) must be
  *         defined as it impacts the ADC LSB equivalent voltage.
  * @note   Analog reference voltage (Vref+) must be either known from
  *         user board environment or can be calculated using ADC measurement
  * @note   On this mcu series, calibration data of temperature sensor
  *         corresponds to a resolution of 12 bits,
  *         this is the recommended ADC resolution to convert voltage of
  *         temperature sensor.
  *         Otherwise, this macro performs the processing to scale
  *         ADC conversion data to 12 bits.
  * @param  __VREFANALOG_VOLTAGE__  Analog reference voltage (unit: mV)
  * @param  __TEMPSENSOR_ADC_DATA__ ADC conversion data of internal
  *                                 temperature sensor (unit: digital value).
  * @param  __ADC_RESOLUTION__      ADC resolution at which internal temperature
  *                                 sensor voltage has been measured.
  *         This parameter can be one of the following values:
  *         @arg @ref ADC_RESOLUTION_12B
  *         @arg @ref ADC_RESOLUTION_10B
  *         @arg @ref ADC_RESOLUTION_8B
  *         @arg @ref ADC_RESOLUTION_6B
  * @retval Temperature (unit: degree Celsius)
  */
#define __HAL_ADC_CALC_TEMPERATURE(__VREFANALOG_VOLTAGE__,\
                                   __TEMPSENSOR_ADC_DATA__,\
                                   __ADC_RESOLUTION__) \
__LL_ADC_CALC_TEMPERATURE((__VREFANALOG_VOLTAGE__),\
                          (__TEMPSENSOR_ADC_DATA__),\
                          (__ADC_RESOLUTION__))

/**
  * @}
  */

/**
  * @}
  */

/* Include ADC HAL Extended module */
#include "py32f032_hal_adc_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @addtogroup ADC_Exported_Functions
  * @{
  */

/** @addtogroup ADC_Exported_Functions_Group1
  * @brief    Initialization and Configuration functions
  * @{
  */
/* Initialization and de-initialization functions  ****************************/
HAL_StatusTypeDef       HAL_ADC_Init(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef       HAL_ADC_DeInit(ADC_HandleTypeDef *hadc);
void                    HAL_ADC_MspInit(ADC_HandleTypeDef *hadc);
void                    HAL_ADC_MspDeInit(ADC_HandleTypeDef *hadc);

#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
/* Callbacks Register/UnRegister functions  ***********************************/
HAL_StatusTypeDef HAL_ADC_RegisterCallback(ADC_HandleTypeDef *hadc, HAL_ADC_CallbackIDTypeDef CallbackID,
                                           pADC_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_ADC_UnRegisterCallback(ADC_HandleTypeDef *hadc, HAL_ADC_CallbackIDTypeDef CallbackID);
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @addtogroup ADC_Exported_Functions_Group2
  * @brief    IO operation functions
  * @{
  */
/* IO operation functions  *****************************************************/

/* Blocking mode: Polling */
HAL_StatusTypeDef       HAL_ADC_Start(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef       HAL_ADC_Stop(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef       HAL_ADC_PollForConversion(ADC_HandleTypeDef *hadc, uint32_t Timeout);
HAL_StatusTypeDef       HAL_ADC_PollForEvent(ADC_HandleTypeDef *hadc, uint32_t EventType, uint32_t Timeout);

/* Non-blocking mode: Interruption */
HAL_StatusTypeDef       HAL_ADC_Start_IT(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef       HAL_ADC_Stop_IT(ADC_HandleTypeDef *hadc);

/* Non-blocking mode: DMA */
HAL_StatusTypeDef       HAL_ADC_Start_DMA(ADC_HandleTypeDef *hadc, uint32_t *pData, uint32_t Length);
HAL_StatusTypeDef       HAL_ADC_Stop_DMA(ADC_HandleTypeDef *hadc);

/* ADC retrieve conversion value intended to be used with polling or interruption */
uint32_t                HAL_ADC_GetValue(const ADC_HandleTypeDef *hadc);

/* ADC IRQHandler and Callbacks used in non-blocking modes (Interruption and DMA) */
void                    HAL_ADC_IRQHandler(ADC_HandleTypeDef *hadc);
void                    HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);
void                    HAL_ADC_ConvHalfBlockCpltCallback(ADC_HandleTypeDef *hadc);
void                    HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef *hadc);
void                    HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc);
/**
  * @}
  */

/** @addtogroup ADC_Exported_Functions_Group3 Peripheral Control functions
  *  @brief    Peripheral Control functions
  * @{
  */
/* Peripheral Control functions ***********************************************/
HAL_StatusTypeDef       HAL_ADC_ConfigChannel(ADC_HandleTypeDef *hadc, const ADC_ChannelConfTypeDef *pConfig);
HAL_StatusTypeDef       HAL_ADC_AnalogWDGConfig(ADC_HandleTypeDef *hadc,
                                                const ADC_AnalogWDGConfTypeDef *pAnalogWDGConfig);
HAL_StatusTypeDef       HAL_ADC_ConfigVrefBuf(ADC_HandleTypeDef* hadc, uint32_t VrefBuf);
HAL_StatusTypeDef HAL_ADC_ConfigPowerMode(ADC_HandleTypeDef* hadc, uint32_t PowerMode);
/**
  * @}
  */

/* Peripheral State functions *************************************************/
/** @addtogroup ADC_Exported_Functions_Group4
  * @{
  */
uint32_t                HAL_ADC_GetState(const ADC_HandleTypeDef *hadc);
uint32_t                HAL_ADC_GetError(const ADC_HandleTypeDef *hadc);

/**
  * @}
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @addtogroup ADC_Private_Functions ADC Private Functions
  * @{
  */
HAL_StatusTypeDef ADC_ConversionStop(ADC_HandleTypeDef* hadc, uint32_t ConversionGroup);
HAL_StatusTypeDef ADC_Enable(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef ADC_Disable(ADC_HandleTypeDef *hadc);
void ADC_DMAConvCplt(DMA_HandleTypeDef *hdma);
void ADC_DMAHalfBlockConvCplt(DMA_HandleTypeDef *hdma);
void ADC_DMAError(DMA_HandleTypeDef *hdma);

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


#endif /* PY32F032_HAL_ADC_H */
