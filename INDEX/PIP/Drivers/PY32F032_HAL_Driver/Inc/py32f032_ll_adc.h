/**
  ******************************************************************************
  * @file    py32f032_ll_adc.h
  * @author  MCU Application Team
  * @brief   Header file of ADC LL module.
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
#ifndef PY32F032_LL_ADC_H
#define PY32F032_LL_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f0xx.h"

/** @addtogroup PY32F032_LL_Driver
  * @{
  */

#if defined (ADC1)

/** @defgroup ADC_LL ADC
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/** @defgroup ADC_LL_Private_Constants ADC Private Constants
  * @{
  */

/* Internal mask for ADC group regular sequencer:                             */
/* To select into literal LL_ADC_REG_RANK_x the relevant bits for:            */
/* - sequencer register offset                                                */
/* - sequencer rank bits position into the selected register                  */

/* Internal register offset for ADC group regular sequencer configuration */
/* (offset placed into a spare area of literal definition) */
#define ADC_SQR1_REGOFFSET                 (0x00000000UL)
#define ADC_SQR2_REGOFFSET                 (0x00000100UL)
#define ADC_SQR3_REGOFFSET                 (0x00000200UL)
#define ADC_SQR4_REGOFFSET                 (0x00000300UL)

#define ADC_REG_SQRX_REGOFFSET_MASK        (ADC_SQR1_REGOFFSET | ADC_SQR2_REGOFFSET \
                                            | ADC_SQR3_REGOFFSET | ADC_SQR4_REGOFFSET)
#define ADC_SQRX_REGOFFSET_POS             (8UL) /* Position of bits ADC_SQRx_REGOFFSET in ADC_REG_SQRX_REGOFFSET_MASK*/
#define ADC_REG_RANK_ID_SQRX_MASK          (0x1F)

/* Definition of ADC group regular sequencer bits information to be inserted  */
/* into ADC group regular sequencer ranks literals definition.                */
#define ADC_REG_RANK_1_SQRX_BITOFFSET_POS  (ADC_SQR1_SQ1_Pos)
#define ADC_REG_RANK_2_SQRX_BITOFFSET_POS  (ADC_SQR1_SQ2_Pos)
#define ADC_REG_RANK_3_SQRX_BITOFFSET_POS  (ADC_SQR1_SQ3_Pos)
#define ADC_REG_RANK_4_SQRX_BITOFFSET_POS  (ADC_SQR1_SQ4_Pos)
#define ADC_REG_RANK_5_SQRX_BITOFFSET_POS  (ADC_SQR2_SQ5_Pos)
#define ADC_REG_RANK_6_SQRX_BITOFFSET_POS  (ADC_SQR2_SQ6_Pos)
#define ADC_REG_RANK_7_SQRX_BITOFFSET_POS  (ADC_SQR2_SQ7_Pos)
#define ADC_REG_RANK_8_SQRX_BITOFFSET_POS  (ADC_SQR2_SQ8_Pos)
#define ADC_REG_RANK_9_SQRX_BITOFFSET_POS  (ADC_SQR2_SQ9_Pos)
#define ADC_REG_RANK_10_SQRX_BITOFFSET_POS (ADC_SQR3_SQ10_Pos)
#define ADC_REG_RANK_11_SQRX_BITOFFSET_POS (ADC_SQR3_SQ11_Pos)
#define ADC_REG_RANK_12_SQRX_BITOFFSET_POS (ADC_SQR3_SQ12_Pos)
#define ADC_REG_RANK_13_SQRX_BITOFFSET_POS (ADC_SQR3_SQ13_Pos)
#define ADC_REG_RANK_14_SQRX_BITOFFSET_POS (ADC_SQR3_SQ14_Pos)
#define ADC_REG_RANK_15_SQRX_BITOFFSET_POS (ADC_SQR4_SQ15_Pos)
#define ADC_REG_RANK_16_SQRX_BITOFFSET_POS (ADC_SQR4_SQ16_Pos)



/* Internal mask for ADC group injected sequencer:                            */
/* To select into literal LL_ADC_INJ_RANK_x the relevant bits for:            */
/* - data register offset                                                     */
/* - sequencer rank bits position into the selected register                  */

/* Internal register offset for ADC group injected data register */
/* (offset placed into a spare area of literal definition) */
#define ADC_JDR1_REGOFFSET                 (0x00000000UL)
#define ADC_JDR2_REGOFFSET                 (0x00000100UL)
#define ADC_JDR3_REGOFFSET                 (0x00000200UL)
#define ADC_JDR4_REGOFFSET                 (0x00000300UL)

#define ADC_INJ_JDRX_REGOFFSET_MASK        (ADC_JDR1_REGOFFSET | ADC_JDR2_REGOFFSET \
                                            | ADC_JDR3_REGOFFSET | ADC_JDR4_REGOFFSET)
#define ADC_INJ_RANK_ID_JSQR_MASK          (0x1F)
#define ADC_JDRX_REGOFFSET_POS             (8UL) /* Position of bits ADC_JDRx_REGOFFSET in ADC_INJ_JDRX_REGOFFSET_MASK*/

/* Definition of ADC group injected sequencer bits information to be inserted */
/* into ADC group injected sequencer ranks literals definition.               */
#define ADC_INJ_RANK_1_JSQR_BITOFFSET_POS  (ADC_JSQR_JSQ1_Pos)
#define ADC_INJ_RANK_2_JSQR_BITOFFSET_POS  (ADC_JSQR_JSQ2_Pos)
#define ADC_INJ_RANK_3_JSQR_BITOFFSET_POS  (ADC_JSQR_JSQ3_Pos)
#define ADC_INJ_RANK_4_JSQR_BITOFFSET_POS  (ADC_JSQR_JSQ4_Pos)



/* Internal mask for ADC group regular trigger:                               */
/* To select into literal LL_ADC_REG_TRIG_x the relevant bits for:            */
/* - regular trigger source                                                   */
/* - regular trigger edge                                                     */
#define ADC_REG_TRIG_EXT_EDGE_DEFAULT      (ADC_CFGR_EXTEN_0) /* Trigger edge set to rising edge (default setting for
                                                                 compatibility with some ADC on other chip series
                                                                 having this setting set by HW default value) */

/* Mask containing trigger source masks for each of possible                  */
/* trigger edge selection duplicated with shifts [0; 4; 8; 12]                */
/* corresponding to {SW start; ext trigger; ext trigger; ext trigger}.        */
#define ADC_REG_TRIG_SOURCE_MASK           (((LL_ADC_REG_TRIG_SOFTWARE & ADC_CFGR_EXTSEL) << (4U * 0UL)) | \
                                            ((ADC_CFGR_EXTSEL)                            << (4U * 1UL)) | \
                                            ((ADC_CFGR_EXTSEL)                            << (4U * 2UL)) | \
                                            ((ADC_CFGR_EXTSEL)                            << (4U * 3UL))  )

/* Mask containing trigger edge masks for each of possible                    */
/* trigger edge selection duplicated with shifts [0; 4; 8; 12]                */
/* corresponding to {SW start; ext trigger; ext trigger; ext trigger}.        */
#define ADC_REG_TRIG_EDGE_MASK             (((LL_ADC_REG_TRIG_SOFTWARE & ADC_CFGR_EXTEN) << (4U * 0UL)) | \
                                            ((ADC_REG_TRIG_EXT_EDGE_DEFAULT)             << (4U * 1UL)) | \
                                            ((ADC_REG_TRIG_EXT_EDGE_DEFAULT)             << (4U * 2UL)) | \
                                            ((ADC_REG_TRIG_EXT_EDGE_DEFAULT)             << (4U * 3UL))  )

/* Definition of ADC group regular trigger bits information.                  */
#define ADC_REG_TRIG_EXTSEL_BITOFFSET_POS  (ADC_CFGR_EXTSEL_Pos)
#define ADC_REG_TRIG_EXTEN_BITOFFSET_POS   (ADC_CFGR_EXTEN_Pos)



/* Internal mask for ADC group injected trigger:                              */
/* To select into literal LL_ADC_INJ_TRIG_x the relevant bits for:            */
/* - injected trigger source                                                  */
/* - injected trigger edge                                                    */
#define ADC_INJ_TRIG_EXT_EDGE_DEFAULT      (ADC_JSQR_JEXTEN_0) /* Trigger edge set to rising edge (default setting for
                                                                  compatibility with some ADC on other chip series
                                                                  having this setting set by HW default value) */

/* Mask containing trigger source masks for each of possible                  */
/* trigger edge selection duplicated with shifts [0; 4; 8; 12]                */
/* corresponding to {SW start; ext trigger; ext trigger; ext trigger}.        */
#define ADC_INJ_TRIG_SOURCE_MASK           (((LL_ADC_INJ_TRIG_SOFTWARE & ADC_JSQR_JEXTSEL)  << (4U * 0UL)) | \
                                            ((ADC_JSQR_JEXTSEL)                             << (4U * 1UL)) | \
                                            ((ADC_JSQR_JEXTSEL)                             << (4U * 2UL)) | \
                                            ((ADC_JSQR_JEXTSEL)                             << (4U * 3UL))  )

/* Mask containing trigger edge masks for each of possible                    */
/* trigger edge selection duplicated with shifts [0; 4; 8; 12]                */
/* corresponding to {SW start; ext trigger; ext trigger; ext trigger}.        */
#define ADC_INJ_TRIG_EDGE_MASK             (((LL_ADC_INJ_TRIG_SOFTWARE & ADC_JSQR_JEXTEN) << (4U * 0UL)) | \
                                            ((ADC_INJ_TRIG_EXT_EDGE_DEFAULT)              << (4U * 1UL)) | \
                                            ((ADC_INJ_TRIG_EXT_EDGE_DEFAULT)              << (4U * 2UL)) | \
                                            ((ADC_INJ_TRIG_EXT_EDGE_DEFAULT)              << (4U * 3UL))  )

/* Definition of ADC group injected trigger bits information.                 */
#define ADC_INJ_TRIG_EXTSEL_BITOFFSET_POS  (ADC_JSQR_JEXTSEL_Pos)
#define ADC_INJ_TRIG_EXTEN_BITOFFSET_POS   (ADC_JSQR_JEXTEN_Pos)






/* Internal mask for ADC channel:                                             */
/* To select into literal LL_ADC_CHANNEL_x the relevant bits for:             */
/* - channel identifier defined by number                                     */
/* - channel identifier defined by bitfield                                   */
/* - channel differentiation between external channels (connected to          */
/*   GPIO pins) and internal channels (connected to internal paths)           */
/* - channel sampling time defined by SMPRx register offset                   */
/*   and SMPx bits positions into SMPRx register                              */
#define ADC_CHANNEL_ID_NUMBER_MASK          (ADC_CFGR_AWDCH)
#define ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS (ADC_CFGR_AWDCH_Pos)
#define ADC_CHANNEL_ID_MASK                 (ADC_CHANNEL_ID_NUMBER_MASK \
                                             | ADC_CHANNEL_ID_INTERNAL_CH_MASK)
/* Equivalent mask of ADC_CHANNEL_NUMBER_MASK aligned on register LSB (bit 0) */
#define ADC_CHANNEL_ID_NUMBER_MASK_POSBIT0 (ADC_SQR2_SQ5) /* Equivalent to shift: (ADC_CHANNEL_NUMBER_MASK
  >> [Position of bitfield "ADC_CHANNEL_NUMBER_MASK" in register]) */

/* Channel differentiation between external and internal channels */
#define ADC_CHANNEL_ID_INTERNAL_CH         (0x00000001UL) /* Marker of internal channel */
#define ADC_CHANNEL_ID_INTERNAL_CH_MASK    (ADC_CHANNEL_ID_INTERNAL_CH)

/* Internal register offset for ADC channel sampling time configuration */
/* (offset placed into a spare area of literal definition) */
#define ADC_SMPR1_REGOFFSET                (0x00000000UL)
#define ADC_SMPR2_REGOFFSET                (0x01000000UL)
#define ADC_CHANNEL_SMPRX_REGOFFSET_MASK   (ADC_SMPR1_REGOFFSET | ADC_SMPR2_REGOFFSET)
#define ADC_SMPRX_REGOFFSET_POS            (24UL)           /* Position of bits ADC_SMPRx_REGOFFSET
                                                               in ADC_CHANNEL_SMPRX_REGOFFSET_MASK */

#define ADC_CHANNEL_SMPx_BITOFFSET_MASK    (0x00F80000UL)
#define ADC_CHANNEL_SMPx_BITOFFSET_POS     (19UL)           /* Equivalent to bitfield "ADC_CHANNEL_SMPx_BITOFFSET_MASK"
                                                               position in register */

/* Definition of channels ID number information to be inserted into           */
/* channels literals definition.                                              */
#define ADC_CHANNEL_0_NUMBER               (0x00000000UL)
#define ADC_CHANNEL_1_NUMBER               (ADC_CFGR_AWDCH_0)
#define ADC_CHANNEL_2_NUMBER               (ADC_CFGR_AWDCH_1)
#define ADC_CHANNEL_3_NUMBER               (ADC_CFGR_AWDCH_1 | ADC_CFGR_AWDCH_0)
#define ADC_CHANNEL_4_NUMBER               (ADC_CFGR_AWDCH_2)
#define ADC_CHANNEL_5_NUMBER               (ADC_CFGR_AWDCH_2 | ADC_CFGR_AWDCH_0)
#define ADC_CHANNEL_6_NUMBER               (ADC_CFGR_AWDCH_2 | ADC_CFGR_AWDCH_1)
#define ADC_CHANNEL_7_NUMBER               (ADC_CFGR_AWDCH_2 | ADC_CFGR_AWDCH_1 | ADC_CFGR_AWDCH_0)
#define ADC_CHANNEL_8_NUMBER               (ADC_CFGR_AWDCH_3)
#define ADC_CHANNEL_9_NUMBER               (ADC_CFGR_AWDCH_3 | ADC_CFGR_AWDCH_0)
#define ADC_CHANNEL_10_NUMBER              (ADC_CFGR_AWDCH_3 | ADC_CFGR_AWDCH_1)
#define ADC_CHANNEL_11_NUMBER              (ADC_CFGR_AWDCH_3 | ADC_CFGR_AWDCH_1 | ADC_CFGR_AWDCH_0)
#define ADC_CHANNEL_12_NUMBER              (ADC_CFGR_AWDCH_3 | ADC_CFGR_AWDCH_2)
#define ADC_CHANNEL_13_NUMBER              (ADC_CFGR_AWDCH_3 | ADC_CFGR_AWDCH_2 | ADC_CFGR_AWDCH_0)
#define ADC_CHANNEL_14_NUMBER              (ADC_CFGR_AWDCH_3 | ADC_CFGR_AWDCH_2 | ADC_CFGR_AWDCH_1)

/* Definition of channels sampling time information to be inserted into       */
/* channels literals definition.                                              */
/* Value shifted are equivalent to bitfield "ADC_SMPRx_SMPy" position         */
/* in register.                                                               */
#define ADC_CHANNEL_0_SMP                  (ADC_SMPR1_REGOFFSET | (( 0UL) << ADC_CHANNEL_SMPx_BITOFFSET_POS))
#define ADC_CHANNEL_1_SMP                  (ADC_SMPR1_REGOFFSET | (( 3UL) << ADC_CHANNEL_SMPx_BITOFFSET_POS))
#define ADC_CHANNEL_2_SMP                  (ADC_SMPR1_REGOFFSET | (( 6UL) << ADC_CHANNEL_SMPx_BITOFFSET_POS))
#define ADC_CHANNEL_3_SMP                  (ADC_SMPR1_REGOFFSET | (( 9UL) << ADC_CHANNEL_SMPx_BITOFFSET_POS))
#define ADC_CHANNEL_4_SMP                  (ADC_SMPR1_REGOFFSET | ((12UL) << ADC_CHANNEL_SMPx_BITOFFSET_POS))
#define ADC_CHANNEL_5_SMP                  (ADC_SMPR1_REGOFFSET | ((15UL) << ADC_CHANNEL_SMPx_BITOFFSET_POS))
#define ADC_CHANNEL_6_SMP                  (ADC_SMPR1_REGOFFSET | ((18UL) << ADC_CHANNEL_SMPx_BITOFFSET_POS))
#define ADC_CHANNEL_7_SMP                  (ADC_SMPR1_REGOFFSET | ((21UL) << ADC_CHANNEL_SMPx_BITOFFSET_POS))
#define ADC_CHANNEL_8_SMP                  (ADC_SMPR1_REGOFFSET | ((24UL) << ADC_CHANNEL_SMPx_BITOFFSET_POS))
#define ADC_CHANNEL_9_SMP                  (ADC_SMPR1_REGOFFSET | ((27UL) << ADC_CHANNEL_SMPx_BITOFFSET_POS))
#define ADC_CHANNEL_10_SMP                 (ADC_SMPR2_REGOFFSET | (( 0UL) << ADC_CHANNEL_SMPx_BITOFFSET_POS))
#define ADC_CHANNEL_11_SMP                 (ADC_SMPR2_REGOFFSET | (( 3UL) << ADC_CHANNEL_SMPx_BITOFFSET_POS))
#define ADC_CHANNEL_12_SMP                 (ADC_SMPR2_REGOFFSET | (( 6UL) << ADC_CHANNEL_SMPx_BITOFFSET_POS))
#define ADC_CHANNEL_13_SMP                 (ADC_SMPR2_REGOFFSET | (( 9UL) << ADC_CHANNEL_SMPx_BITOFFSET_POS))
#define ADC_CHANNEL_14_SMP                 (ADC_SMPR2_REGOFFSET | ((12UL) << ADC_CHANNEL_SMPx_BITOFFSET_POS))

/* Internal register offset for ADC analog watchdog channel configuration */
#define ADC_AWD_CR1_REGOFFSET              (0x00000000UL)

#define ADC_AWD_CR1_CHANNEL_MASK           (ADC_CFGR_AWDCH | ADC_CFGR_JAWDEN | ADC_CFGR_AWDEN | ADC_CFGR_AWDSGL)
#define ADC_AWD_CR_ALL_CHANNEL_MASK        (ADC_AWD_CR1_CHANNEL_MASK)

/* Internal register offset for ADC analog watchdog threshold configuration */
#define ADC_AWD_TR1_REGOFFSET              (ADC_AWD_CR1_REGOFFSET)
#define ADC_AWD_TRX_REGOFFSET_MASK         (ADC_AWD_TR1_REGOFFSET)

#define ADC_AWD_TRX_BIT_HIGH_MASK          (0x00010000UL)                   /* Selection of 1 bit to discriminate
                                                                               threshold high: mask of bit */
#define ADC_AWD_TRX_BIT_HIGH_POS           (16UL)                           /* Selection of 1 bit to discriminate
                                                                               threshold high: position of bit */
#define ADC_AWD_TRX_BIT_HIGH_SHIFT4        (ADC_AWD_TRX_BIT_HIGH_POS - 4UL) /* Shift of bit ADC_AWD_TRX_BIT_HIGH to
                                                                               position to perform a shift of 4 ranks */

/* ADC registers bits positions */
#define ADC_CFGR_RES_BITOFFSET_POS         (ADC_CFGR_RES_Pos)
#define ADC_CFGR_AWDSGL_BITOFFSET_POS      (ADC_CFGR_AWDSGL_Pos)
#define ADC_CFGR_AWDEN_BITOFFSET_POS       (ADC_CFGR_AWDEN_Pos)
#define ADC_CFGR_JAWDEN_BITOFFSET_POS      (ADC_CFGR_JAWDEN_Pos)
#define ADC_TR_HT_BITOFFSET_POS            (ADC_TR_HT_Pos)


/* ADC registers bits groups */
#define ADC_CR_BITS_PROPERTY_RS            (ADC_CR_ADCAL | ADC_CR_RSTCAL | ADC_CR_JADSTP | ADC_CR_JADSTART \
                                            | ADC_CR_ADSTART | ADC_CR_ADSTP | ADC_CR_ADDIS | ADC_CR_ADEN)            /* ADC register CR bits with
                                           HW property "rs": Software can read as well as set this bit.
                                           Writing '0' has no effect on the bit value. */


/* ADC internal channels related definitions */
/* Temperature sensor */
#define TEMPSENSOR_CAL1_ADDR               ((uint16_t*) (0x1FFF1120UL)) /* Address of parameter TS_CAL1,
                                           temperature sensor ADC raw data acquired at temperature 30 DegC
                                           (tolerance: +-5 DegC), Vref+ = 3.0 V (tolerance: +-10 mV). */
#define TEMPSENSOR_CAL2_ADDR               ((uint16_t*) (0x1FFF1124UL)) /* Address of parameter TS_CAL2,
                                           temperature sensor ADC raw data acquired at temperature 125 DegC
                                           (tolerance: +-5 DegC), Vref+ = 3.0 V (tolerance: +-10 mV). */
#define TEMPSENSOR_CAL1_TEMP               (30L)                        /* Temperature at which temperature sensor
                                           has been calibrated in production for data into TEMPSENSOR_CAL1_ADDR
                                           (tolerance: +-5 DegC) (unit: DegC). */
#define TEMPSENSOR_CAL2_TEMP               (125L)                       /* Temperature at which temperature sensor
                                           has been calibrated in production for data into TEMPSENSOR_CAL2_ADDR
                                           (tolerance: +-5 DegC) (unit: DegC). */
#define TEMPSENSOR_CAL_VREFANALOG          (3300UL)                     /* Analog voltage reference (Vref+) value
                                           with which temperature sensor has been calibrated in production
                                           (tolerance +-10 mV) (unit: mV). */

/**
  * @}
  */


/* Private macros ------------------------------------------------------------*/
/** @defgroup ADC_LL_Private_Macros ADC Private Macros
  * @{
  */

/**
  * @brief  Driver macro reserved for internal use: set a pointer to
  *         a register from a register basis from which an offset
  *         is applied.
  * @param  __REG__ Register basis from which the offset is applied.
  * @param  __REG_OFFFSET__ Offset to be applied (unit: number of registers).
  * @retval Pointer to register address
  */
#define __ADC_PTR_REG_OFFSET(__REG__, __REG_OFFFSET__)                         \
  ((__IO uint32_t *)((uint32_t) ((uint32_t)(&(__REG__)) + ((__REG_OFFFSET__) << 2UL))))

/**
  * @}
  */


/* Exported types ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup ADC_LL_ES_INIT ADC Exported Init structure
  * @{
  */

/**
  * @brief  Structure definition of some features of ADC common parameters
  *         and multimode
  *         (all ADC instances belonging to the same ADC common instance).
  * @note   The setting of these parameters by function @ref LL_ADC_CommonInit()
  *         is conditioned to ADC instances state (all ADC instances
  *         sharing the same ADC common instance):
  *         All ADC instances sharing the same ADC common instance must be
  *         disabled.
  */
typedef struct
{
  uint32_t CommonClock;                 /*!< Set parameter common to several ADC: Clock source and prescaler.
                                             This parameter can be a value of @ref ADC_LL_EC_COMMON_CLOCK_SOURCE
                                             @note On this chip series, if ADC group injected is used, some clock ratio
                                                   constraints between ADC clock and AHB clock must be respected.
                                                   Refer to reference manual.
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_SetCommonClock(). */
} LL_ADC_CommonInitTypeDef;

/**
  * @brief  Structure definition of some features of ADC instance.
  * @note   These parameters have an impact on ADC scope: ADC instance.
  *         Affects both group regular and group injected (availability
  *         of ADC group injected depends on chip series).
  *         Refer to corresponding unitary functions into
  *         @ref ADC_LL_EF_Configuration_ADC_Instance .
  * @note   The setting of these parameters by function @ref LL_ADC_Init()
  *         is conditioned to ADC state:
  *         ADC instance must be disabled.
  *         This condition is applied to all ADC features, for efficiency
  *         and compatibility over all chip series. However, the different
  *         features can be set under different ADC state conditions
  *         (setting possible with ADC enabled without conversion on going,
  *         ADC enabled with conversion on going, ...)
  *         Each feature can be updated afterwards with a unitary function
  *         and potentially with ADC in a different state than disabled,
  *         refer to description of each function for setting
  *         conditioned to ADC state.
  */
typedef struct
{
  uint32_t Resolution;                  /*!< Set ADC resolution.
                                             This parameter can be a value of @ref ADC_LL_EC_RESOLUTION
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_SetResolution(). */

  uint32_t DataAlignment;               /*!< Set ADC conversion data alignment.
                                             This parameter can be a value of @ref ADC_LL_EC_DATA_ALIGN
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_SetDataAlignment(). */

  uint32_t LowPowerMode;                /*!< Set ADC low power mode.
                                             This parameter can be a value of @ref ADC_LL_EC_LP_MODE
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_SetLowPowerMode(). */

} LL_ADC_InitTypeDef;

/**
  * @brief  Structure definition of some features of ADC group regular.
  * @note   These parameters have an impact on ADC scope: ADC group regular.
  *         Refer to corresponding unitary functions into
  *         @ref ADC_LL_EF_Configuration_ADC_Group_Regular
  *         (functions with prefix "REG").
  * @note   The setting of these parameters by function @ref LL_ADC_REG_Init()
  *         is conditioned to ADC state:
  *         ADC instance must be disabled.
  *         This condition is applied to all ADC features, for efficiency
  *         and compatibility over all chip series. However, the different
  *         features can be set under different ADC state conditions
  *         (setting possible with ADC enabled without conversion on going,
  *         ADC enabled with conversion on going, ...)
  *         Each feature can be updated afterwards with a unitary function
  *         and potentially with ADC in a different state than disabled,
  *         refer to description of each function for setting
  *         conditioned to ADC state.
  */
typedef struct
{
  uint32_t TriggerSource;               /*!< Set ADC group regular conversion trigger source: internal (SW start) or
                                             from external peripheral (timer event, external interrupt line).
                                             This parameter can be a value of @ref ADC_LL_EC_REG_TRIGGER_SOURCE
                                             @note setting trigger source to external trigger also set trigger
                                                   polarity to rising edge.
                                                   In case of need to modify trigger edge, use function
                                                   @ref LL_ADC_REG_SetTriggerEdge().
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_REG_SetTriggerSource(). */

  uint32_t SequencerLength;             /*!< Set ADC group regular sequencer length.
                                             This parameter can be a value of @ref ADC_LL_EC_REG_SEQ_SCAN_LENGTH
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_REG_SetSequencerLength(). */

  uint32_t SequencerDiscont;            /*!< Set ADC group regular sequencer discontinuous mode: sequence subdivided
                                             and scan conversions interrupted every selected number of ranks.
                                             This parameter can be a value of @ref ADC_LL_EC_REG_SEQ_DISCONT_MODE
                                             @note This parameter has an effect only if group regular sequencer is
                                                    enabled (scan length of 2 ranks or more).
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_REG_SetSequencerDiscont(). */

  uint32_t ContinuousMode;              /*!< Set ADC continuous conversion mode on ADC group regular, whether ADC
                                             conversions are performed in single mode (one conversion per trigger) or in
                                             continuous mode (after the first trigger, following conversions launched
                                             successively automatically).
                                             This parameter can be a value of @ref ADC_LL_EC_REG_CONTINUOUS_MODE
                                             Note: It is not possible to enable both ADC group regular continuous mode
                                                   and discontinuous mode.
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_REG_SetContinuousMode(). */

  uint32_t DMATransfer;                 /*!< Set ADC group regular conversion data transfer: no transfer or transfer
                                             by DMA, and DMA requests mode.
                                             This parameter can be a value of @ref ADC_LL_EC_REG_DMA_TRANSFER
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_REG_SetDMATransfer(). */

  uint32_t Overrun;                     /*!< Set ADC group regular behavior in case of overrun:
                                             data preserved or overwritten.
                                             This parameter can be a value of @ref ADC_LL_EC_REG_OVR_DATA_BEHAVIOR
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_REG_SetOverrun(). */

} LL_ADC_REG_InitTypeDef;

/**
  * @brief  Structure definition of some features of ADC group injected.
  * @note   These parameters have an impact on ADC scope: ADC group injected.
  *         Refer to corresponding unitary functions into
  *         @ref ADC_LL_EF_Configuration_ADC_Group_Regular
  *         (functions with prefix "INJ").
  * @note   The setting of these parameters by function @ref LL_ADC_INJ_Init()
  *         is conditioned to ADC state:
  *         ADC instance must be disabled.
  *         This condition is applied to all ADC features, for efficiency
  *         and compatibility over all chip series. However, the different
  *         features can be set under different ADC state conditions
  *         (setting possible with ADC enabled without conversion on going,
  *         ADC enabled with conversion on going, ...)
  *         Each feature can be updated afterwards with a unitary function
  *         and potentially with ADC in a different state than disabled,
  *         refer to description of each function for setting
  *         conditioned to ADC state.
  */
typedef struct
{
  uint32_t TriggerSource;               /*!< Set ADC group injected conversion trigger source: internal (SW start)
                                             or from external peripheral (timer event, external interrupt line).
                                             This parameter can be a value of @ref ADC_LL_EC_INJ_TRIGGER_SOURCE
                                             @note On this chip series, setting trigger source to external trigger also
                                                   set trigger polarity to rising edge (default setting for
                                                   compatibility with some ADC on other chip series having this
                                                   setting set by HW default value).
                                                   In case of need to modify trigger edge, use function
                                                   @ref LL_ADC_INJ_SetTriggerEdge().
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_INJ_SetTriggerSource(). */

  uint32_t SequencerLength;             /*!< Set ADC group injected sequencer length.
                                             This parameter can be a value of @ref ADC_LL_EC_INJ_SEQ_SCAN_LENGTH
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_INJ_SetSequencerLength(). */

  uint32_t SequencerDiscont;            /*!< Set ADC group injected sequencer discontinuous mode: sequence subdivided
                                             and scan conversions interrupted every selected number of ranks.
                                             This parameter can be a value of @ref ADC_LL_EC_INJ_SEQ_DISCONT_MODE
                                             @note This parameter has an effect only if group injected sequencer is
                                                   enabled (scan length of 2 ranks or more).
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_INJ_SetSequencerDiscont(). */

  uint32_t TrigAuto;                    /*!< Set ADC group injected conversion trigger: independent or from ADC group
                                             regular.
                                             This parameter can be a value of @ref ADC_LL_EC_INJ_TRIG_AUTO
                                             Note: This parameter must be set to set to independent trigger if injected
                                                   trigger source is set to an external trigger.
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_INJ_SetTrigAuto(). */

} LL_ADC_INJ_InitTypeDef;

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/* Exported constants --------------------------------------------------------*/
/** @defgroup ADC_LL_Exported_Constants ADC Exported Constants
  * @{
  */

/** @defgroup ADC_LL_EC_FLAG ADC flags
  * @brief    Flags defines which can be used with LL_ADC_ReadReg function
  * @{
  */
#define LL_ADC_FLAG_ADRDY                  ADC_ISR_ADRDY      /*!< ADC flag ADC ready */
#define LL_ADC_FLAG_EOSMP                  ADC_ISR_EOSMP      /*!< ADC flag ADC group regular end of sampling phase */
#define LL_ADC_FLAG_EOC                    ADC_ISR_EOC        /*!< ADC flag ADC group regular end of unitary conversion */
#define LL_ADC_FLAG_EOS                    ADC_ISR_EOS        /*!< ADC flag ADC group regular end of sequence conversions */
#define LL_ADC_FLAG_OVR                    ADC_ISR_OVR        /*!< ADC flag ADC group regular overrun */
#define LL_ADC_FLAG_JEOC                   ADC_ISR_JEOC       /*!< ADC flag ADC group injected end of unitary conversion */
#define LL_ADC_FLAG_JEOS                   ADC_ISR_JEOS       /*!< ADC flag ADC group injected end of sequence conversions */
#define LL_ADC_FLAG_AWD                    ADC_ISR_AWD        /*!< ADC flag ADC analog watchdog */
#define LL_ADC_FLAG_EOCAL                  ADC_ISR_EOCAL      /*!< ADC flag end of calibration */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_IT ADC interruptions for configuration (interruption enable or disable)
  * @brief    IT defines which can be used with LL_ADC_ReadReg and  LL_ADC_WriteReg functions
  * @{
  */
#define LL_ADC_IT_ADRDY                    ADC_IER_ADRDYIE    /*!< ADC interruption ADC ready */
#define LL_ADC_IT_EOSMP                    ADC_IER_EOSMPIE    /*!< ADC interruption ADC group regular end of sampling phase */
#define LL_ADC_IT_EOC                      ADC_IER_EOCIE      /*!< ADC interruption ADC group regular end of unitary conversion */
#define LL_ADC_IT_EOS                      ADC_IER_EOSIE      /*!< ADC interruption ADC group regular end of sequence conversions */
#define LL_ADC_IT_OVR                      ADC_IER_OVRIE      /*!< ADC interruption ADC group regular regular overrun */
#define LL_ADC_IT_JEOC                     ADC_IER_JEOCIE     /*!< ADC interruption ADC group injected end of unitary conversion */
#define LL_ADC_IT_JEOS                     ADC_IER_JEOSIE     /*!< ADC interruption ADC group injected end of sequence conversions */
#define LL_ADC_IT_AWD                      ADC_IER_AWDIE      /*!< ADC interruption ADC analog watchdog */
#define LL_ADC_IT_EOCAL                    ADC_IER_EOCALIE    /*!< ADC interruption end of calibration */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_COMMON_CLOCK_SOURCE  ADC common - Clock source
  * @{
  */
#define LL_ADC_CLOCK_SYNC_PCLK_DIV1        (ADC_CCR_CKMODE_1 | ADC_CCR_CKMODE_0)                    /*!< ADC synchronous clock derived from
                                           AHB clock without prescaler */
#define LL_ADC_CLOCK_SYNC_PCLK_DIV2        (ADC_CCR_CKMODE_0)                    /*!< ADC synchronous clock derived from
                                           AHB clock with prescaler division by 2 */
#define LL_ADC_CLOCK_SYNC_PCLK_DIV4        (ADC_CCR_CKMODE_1) /*!< ADC synchronous clock derived from
                                           AHB clock with prescaler division by 4 */
#define LL_ADC_CLOCK_ASYNC_DIV1            (0x00000000UL)                      /*!< ADC asynchronous clock without
                                           prescaler */
#define LL_ADC_CLOCK_ASYNC_DIV2            (ADC_CCR_PRESC_0)                   /*!< ADC asynchronous clock with
                                           prescaler division by 2 */
#define LL_ADC_CLOCK_ASYNC_DIV4            (ADC_CCR_PRESC_1)                   /*!< ADC asynchronous clock with
                                           prescaler division by 4 */
#define LL_ADC_CLOCK_ASYNC_DIV6            (ADC_CCR_PRESC_1 | ADC_CCR_PRESC_0) /*!< ADC asynchronous clock with
                                           prescaler division by 6 */
#define LL_ADC_CLOCK_ASYNC_DIV8            (ADC_CCR_PRESC_2)                   /*!< ADC asynchronous clock with
                                           prescaler division by 8 */
#define LL_ADC_CLOCK_ASYNC_DIV10           (ADC_CCR_PRESC_2 | ADC_CCR_PRESC_0) /*!< ADC asynchronous clock with
                                           prescaler division by 10 */
#define LL_ADC_CLOCK_ASYNC_DIV12           (ADC_CCR_PRESC_2 | ADC_CCR_PRESC_1) /*!< ADC asynchronous clock with
                                           prescaler division by 12 */
#define LL_ADC_CLOCK_ASYNC_DIV16           (ADC_CCR_PRESC_2 | ADC_CCR_PRESC_1 \
                                            | ADC_CCR_PRESC_0)                  /*!< ADC asynchronous clock with
                                           prescaler division by 16  */
#define LL_ADC_CLOCK_ASYNC_DIV32           (ADC_CCR_PRESC_3)                   /*!< ADC asynchronous clock with
                                           prescaler division by 32 */
#define LL_ADC_CLOCK_ASYNC_DIV64           (ADC_CCR_PRESC_3 | ADC_CCR_PRESC_0) /*!< ADC asynchronous clock with
                                           prescaler division by 64 */
#define LL_ADC_CLOCK_ASYNC_DIV128          (ADC_CCR_PRESC_3 | ADC_CCR_PRESC_1) /*!< ADC asynchronous clock with
                                           prescaler division by 128 */
#define LL_ADC_CLOCK_ASYNC_DIV256          (ADC_CCR_PRESC_3 | ADC_CCR_PRESC_1 \
                                            | ADC_CCR_PRESC_0)                  /*!< ADC asynchronous clock with
                                           prescaler division by 256 */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_COMMON_PATH_INTERNAL  ADC common - Measurement path to internal channels
  * @{
  */
/* Note: Other measurement paths to internal channels may be available        */
/*       (connections to other peripherals).                                  */
/*       If they are not listed below, they do not require any specific       */
/*       path enable. In this case, Access to measurement path is done        */
/*       only by selecting the corresponding ADC internal channel.            */
#define LL_ADC_PATH_INTERNAL_NONE          (0x00000000UL)       /*!< ADC measurement paths all disabled */
#define LL_ADC_PATH_INTERNAL_VREFINT       (ADC_CCR_VREFINT_EN) /*!< ADC measurement path to internal channel VrefInt */
#define LL_ADC_PATH_INTERNAL_TEMPSENSOR    (ADC_CCR_TSEN)  /*!< ADC measurement path to internal channel
                                                                     temperature sensor */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_RESOLUTION  ADC instance - Resolution
  * @{
  */
#define LL_ADC_RESOLUTION_12B              (0x00000000UL)                      /*!< ADC resolution 12 bits */
#define LL_ADC_RESOLUTION_10B              (                 ADC_CFGR_RES_0)   /*!< ADC resolution 10 bits */
#define LL_ADC_RESOLUTION_8B               (ADC_CFGR_RES_1                 )   /*!< ADC resolution  8 bits */
#define LL_ADC_RESOLUTION_6B               (ADC_CFGR_RES_1 | ADC_CFGR_RES_0)   /*!< ADC resolution  6 bits */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_DATA_ALIGN  ADC instance - Data alignment
  * @{
  */
#define LL_ADC_DATA_ALIGN_RIGHT            (0x00000000UL)     /*!< ADC conversion data alignment: right aligned
                                           (alignment on data register LSB bit 0)*/
#define LL_ADC_DATA_ALIGN_LEFT             (ADC_CFGR_ALIGN)   /*!< ADC conversion data alignment: left aligned
                                           (alignment on data register MSB bit 15)*/
/**
  * @}
  */

/** @defgroup ADC_LL_EC_LP_MODE  ADC instance - Low power mode
  * @{
  */
#define LL_ADC_LP_MODE_NONE                (0x00000000UL)     /*!< No ADC low power mode activated */
#define LL_ADC_LP_AUTOWAIT                 (ADC_CFGR_AUTDLY)  /*!< ADC low power mode auto delay: Dynamic low power
                                           mode, ADC conversions are performed only when necessary
                                           (when previous ADC conversion data is read).
                                           See description with function @ref LL_ADC_SetLowPowerMode(). */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_GROUPS  ADC instance - Groups
  * @{
  */
#define LL_ADC_GROUP_REGULAR               (0x00000001UL)     /*!< ADC group regular  */
#define LL_ADC_GROUP_INJECTED              (0x00000002UL)     /*!< ADC group injected */
#define LL_ADC_GROUP_REGULAR_INJECTED      (0x00000003UL)     /*!< ADC both groups regular and injected */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_CHANNEL  ADC instance - Channel number
  * @{
  */
#define LL_ADC_CHANNEL_0                   (ADC_CHANNEL_0_NUMBER  | ADC_CHANNEL_0_SMP  )                        /*!< ADC channel ADCx_IN0 */
#define LL_ADC_CHANNEL_1                   (ADC_CHANNEL_1_NUMBER  | ADC_CHANNEL_1_SMP  )                        /*!< ADC channel ADCx_IN1 */
#define LL_ADC_CHANNEL_2                   (ADC_CHANNEL_2_NUMBER  | ADC_CHANNEL_2_SMP  )                        /*!< ADC channel ADCx_IN2 */
#define LL_ADC_CHANNEL_3                   (ADC_CHANNEL_3_NUMBER  | ADC_CHANNEL_3_SMP  )                        /*!< ADC channel ADCx_IN3 */
#define LL_ADC_CHANNEL_4                   (ADC_CHANNEL_4_NUMBER  | ADC_CHANNEL_4_SMP  )                        /*!< ADC channel ADCx_IN4 */
#define LL_ADC_CHANNEL_5                   (ADC_CHANNEL_5_NUMBER  | ADC_CHANNEL_5_SMP  )                        /*!< ADC channel ADCx_IN5 */
#define LL_ADC_CHANNEL_6                   (ADC_CHANNEL_6_NUMBER  | ADC_CHANNEL_6_SMP  )                        /*!< ADC channel ADCx_IN6 */
#define LL_ADC_CHANNEL_7                   (ADC_CHANNEL_7_NUMBER  | ADC_CHANNEL_7_SMP  )                        /*!< ADC channel ADCx_IN7 */
#define LL_ADC_CHANNEL_8                   (ADC_CHANNEL_8_NUMBER  | ADC_CHANNEL_8_SMP  )                        /*!< ADC channel ADCx_IN8 */
#define LL_ADC_CHANNEL_9                   (ADC_CHANNEL_9_NUMBER  | ADC_CHANNEL_9_SMP  )                        /*!< ADC channel ADCx_IN9 */
#define LL_ADC_CHANNEL_10                  (ADC_CHANNEL_10_NUMBER | ADC_CHANNEL_10_SMP )                        /*!< ADC channel ADCx_IN10 */
#define LL_ADC_CHANNEL_11                  (ADC_CHANNEL_11_NUMBER | ADC_CHANNEL_11_SMP )                        /*!< ADC channel ADCx_IN11 */
#define LL_ADC_CHANNEL_12                  (ADC_CHANNEL_12_NUMBER | ADC_CHANNEL_12_SMP )                        /*!< ADC channel ADCx_IN12 */
#define LL_ADC_CHANNEL_13                  (ADC_CHANNEL_13_NUMBER | ADC_CHANNEL_13_SMP )                        /*!< ADC channel ADCx_IN13 */
#define LL_ADC_CHANNEL_14                  (ADC_CHANNEL_14_NUMBER | ADC_CHANNEL_14_SMP )                        /*!< ADC channel ADCx_IN14 */


#define LL_ADC_CHANNEL_TEMPSENSOR          (LL_ADC_CHANNEL_10 | ADC_CHANNEL_ID_INTERNAL_CH) 
#define LL_ADC_CHANNEL_VREFINT             (LL_ADC_CHANNEL_11 | ADC_CHANNEL_ID_INTERNAL_CH) 
#define LL_ADC_CHANNEL_1_3VCCA             (LL_ADC_CHANNEL_12 | ADC_CHANNEL_ID_INTERNAL_CH) 
#define LL_ADC_CHANNEL_OPA1                (LL_ADC_CHANNEL_13 | ADC_CHANNEL_ID_INTERNAL_CH) 
#define LL_ADC_CHANNEL_OPA2                (LL_ADC_CHANNEL_14 | ADC_CHANNEL_ID_INTERNAL_CH) 


/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_TRIGGER_SOURCE  ADC group regular - Trigger source
  * @{
  */
#define LL_ADC_REG_TRIG_SOFTWARE             (0x00000000UL)
#define LL_ADC_REG_TRIG_EXT_TIM1_TRGO        (ADC_REG_TRIG_EXT_EDGE_DEFAULT)  
#define LL_ADC_REG_TRIG_EXT_TIM1_CH1         (ADC_REG_TRIG_EXT_EDGE_DEFAULT | ADC_CFGR_EXTSEL_0)  
#define LL_ADC_REG_TRIG_EXT_TIM1_CH2         (ADC_REG_TRIG_EXT_EDGE_DEFAULT | ADC_CFGR_EXTSEL_1)  
#define LL_ADC_REG_TRIG_EXT_TIM1_CH3         (ADC_REG_TRIG_EXT_EDGE_DEFAULT | ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0)  
#define LL_ADC_REG_TRIG_EXT_TIM1_CH4         (ADC_REG_TRIG_EXT_EDGE_DEFAULT | ADC_CFGR_EXTSEL_2)  
#define LL_ADC_REG_TRIG_EXT_TIM1_CH5         (ADC_REG_TRIG_EXT_EDGE_DEFAULT | ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_0)  
#define LL_ADC_REG_TRIG_EXT_TIM1_CH6         (ADC_REG_TRIG_EXT_EDGE_DEFAULT | ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1) 
#define LL_ADC_REG_TRIG_EXT_TIM3_CH1         (ADC_REG_TRIG_EXT_EDGE_DEFAULT | ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0)  
#define LL_ADC_REG_TRIG_EXT_TIM3_TRGO        (ADC_REG_TRIG_EXT_EDGE_DEFAULT | ADC_CFGR_EXTSEL_3 )  
#define LL_ADC_REG_TRIG_EXT_EXTI_LINE11      (ADC_REG_TRIG_EXT_EDGE_DEFAULT | ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_0)  
#define LL_ADC_REG_TRIG_EXT_EXTI_LINE15      (ADC_REG_TRIG_EXT_EDGE_DEFAULT | ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_1)  

/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_TRIGGER_EDGE  ADC group regular - Trigger edge
  * @{
  */
#define LL_ADC_REG_TRIG_EXT_RISING         (ADC_CFGR_EXTEN_0)                      /*!< ADC group regular conversion
                                           trigger polarity set to rising edge */
#define LL_ADC_REG_TRIG_EXT_FALLING        (ADC_CFGR_EXTEN_1)                      /*!< ADC group regular conversion
                                           trigger polarity set to falling edge */
#define LL_ADC_REG_TRIG_EXT_RISINGFALLING  (ADC_CFGR_EXTEN_1 | ADC_CFGR_EXTEN_0)   /*!< ADC group regular conversion
                                           trigger polarity set to both rising and falling edges */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_CONTINUOUS_MODE  ADC group regular - Continuous mode
  * @{
  */
#define LL_ADC_REG_CONV_SINGLE             (0x00000000UL)     /*!< ADC conversions performed in single mode:
                                           one conversion per trigger */
#define LL_ADC_REG_CONV_CONTINUOUS         (ADC_CFGR_CONT)    /*!< ADC conversions performed in continuous mode:
                                           after the first trigger, following conversions launched successively
                                           automatically */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_DMA_TRANSFER  ADC group regular - DMA transfer of ADC conversion data
  * @{
  */
#define LL_ADC_REG_DMA_TRANSFER_NONE       (0x00000000UL)     /*!< ADC conversions are not transferred by DMA */
#define LL_ADC_REG_DMA_TRANSFER_LIMITED    (ADC_CFGR_DMAEN)   /*!< ADC conversion data are transferred by DMA
                                           in limited mode (one shot mode): DMA transfer requests are stopped when
                                           number of DMA data transfers (number of ADC conversions) is reached.
                                           This ADC mode is intended to be used with DMA mode non-circular. */
#define LL_ADC_REG_DMA_TRANSFER_UNLIMITED  (ADC_CFGR_DMACFG | ADC_CFGR_DMAEN)    /*!< ADC conversion data are
                                           transferred by DMA, in unlimited mode: DMA transfer requests are unlimited,
                                           whatever number of DMA data transferred (number of ADC conversions).
                                           This ADC mode is intended to be used with DMA mode circular. */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_OVR_DATA_BEHAVIOR  ADC group regular - Overrun behavior on conversion data
  * @{
  */
#define LL_ADC_REG_OVR_DATA_PRESERVED      (0x00000000UL)     /*!< ADC group regular behavior in case of overrun:
                                                                   data preserved */
#define LL_ADC_REG_OVR_DATA_OVERWRITTEN    (ADC_CFGR_OVRMOD)  /*!< ADC group regular behavior in case of overrun:
                                                                   data overwritten */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_SEQ_SCAN_LENGTH  ADC group regular - Sequencer scan length
  * @{
  */
#define LL_ADC_REG_SEQ_SCAN_DISABLE        (0x00000000UL)                 /*!< ADC group regular sequencer disable
                                           (equivalent to sequencer of 1 rank: ADC conversion on only 1 channel) */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS  (ADC_SQR1_L_0)                 /*!< ADC group regular sequencer enable
                                           with 2 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_3RANKS  (ADC_SQR1_L_1)                 /*!< ADC group regular sequencer enable
                                           with 3 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_4RANKS  (ADC_SQR1_L_1 | ADC_SQR1_L_0)  /*!< ADC group regular sequencer enable
                                           with 4 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_5RANKS  (ADC_SQR1_L_2)                 /*!< ADC group regular sequencer enable
                                           with 5 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_6RANKS  (ADC_SQR1_L_2 | ADC_SQR1_L_0)  /*!< ADC group regular sequencer enable
                                           with 6 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_7RANKS  (ADC_SQR1_L_2 | ADC_SQR1_L_1) /*!< ADC group regular sequencer enable
                                           with 7 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_8RANKS  (ADC_SQR1_L_2 | ADC_SQR1_L_1 \
                                            | ADC_SQR1_L_0)                /*!< ADC group regular sequencer enable
                                           with 8 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_9RANKS  (ADC_SQR1_L_3)                 /*!< ADC group regular sequencer enable
                                           with 9 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_10RANKS (ADC_SQR1_L_3 | ADC_SQR1_L_0)  /*!< ADC group regular sequencer enable
                                           with 10 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_11RANKS (ADC_SQR1_L_3 | ADC_SQR1_L_1)  /*!< ADC group regular sequencer enable
                                           with 11 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_12RANKS (ADC_SQR1_L_3 | ADC_SQR1_L_1 \
                                            | ADC_SQR1_L_0)                /*!< ADC group regular sequencer enable
                                           with 12 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_13RANKS (ADC_SQR1_L_3 | ADC_SQR1_L_2)  /*!< ADC group regular sequencer enable
                                           with 13 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_14RANKS (ADC_SQR1_L_3 | ADC_SQR1_L_2 \
                                            | ADC_SQR1_L_0)                /*!< ADC group regular sequencer enable
                                           with 14 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_15RANKS (ADC_SQR1_L_3 | ADC_SQR1_L_2 \
                                            | ADC_SQR1_L_1)                /*!< ADC group regular sequencerenable
                                           with 15 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_16RANKS (ADC_SQR1_L_3 | ADC_SQR1_L_2 \
                                            | ADC_SQR1_L_1 | ADC_SQR1_L_0) /*!< ADC group regular sequencer enable
                                                                              with 16 ranks in the sequence */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_SEQ_DISCONT_MODE  ADC group regular - Sequencer discontinuous mode
  * @{
  */
#define LL_ADC_REG_SEQ_DISCONT_DISABLE     (0x00000000UL)                          /*!< ADC group regular sequencer
                                           discontinuous mode disable */
#define LL_ADC_REG_SEQ_DISCONT_1RANK       (ADC_CFGR_DISCEN)                       /*!< ADC group regular sequencer
                                           discontinuous mode enable with sequence interruption every rank */
#define LL_ADC_REG_SEQ_DISCONT_2RANKS      (ADC_CFGR_DISCNUM_0 | ADC_CFGR_DISCEN)  /*!< ADC group regular sequencer
                                           discontinuous mode enabled with sequence interruption every 2 ranks */
#define LL_ADC_REG_SEQ_DISCONT_3RANKS      (ADC_CFGR_DISCNUM_1 | ADC_CFGR_DISCEN)  /*!< ADC group regular sequencer
                                           discontinuous mode enable with sequence interruption every 3 ranks */
#define LL_ADC_REG_SEQ_DISCONT_4RANKS      (ADC_CFGR_DISCNUM_1 | ADC_CFGR_DISCNUM_0 \
                                            | ADC_CFGR_DISCEN)                       /*!< ADC group regular sequencer
                                           discontinuous mode enable with sequence interruption every 4 ranks */
#define LL_ADC_REG_SEQ_DISCONT_5RANKS      (ADC_CFGR_DISCNUM_2 | ADC_CFGR_DISCEN)   /*!< ADC group regular sequencer
                                           discontinuous mode enable with sequence interruption every 5 ranks */
#define LL_ADC_REG_SEQ_DISCONT_6RANKS      (ADC_CFGR_DISCNUM_2 | ADC_CFGR_DISCNUM_0 \
                                            | ADC_CFGR_DISCEN)                       /*!< ADC group regular sequencer
                                           discontinuous mode enable with sequence interruption every 6 ranks */
#define LL_ADC_REG_SEQ_DISCONT_7RANKS      (ADC_CFGR_DISCNUM_2 | ADC_CFGR_DISCNUM_1 \
                                            | ADC_CFGR_DISCEN)                       /*!< ADC group regular sequencer
                                           discontinuous mode enable with sequence interruption every 7 ranks */
#define LL_ADC_REG_SEQ_DISCONT_8RANKS      (ADC_CFGR_DISCNUM_2 | ADC_CFGR_DISCNUM_1 \
                                            | ADC_CFGR_DISCNUM_0 | ADC_CFGR_DISCEN)  /*!< ADC group regular sequencer
                                           discontinuous mode enable with sequence interruption every 8 ranks */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_SEQ_RANKS  ADC group regular - Sequencer ranks
  * @{
  */
#define LL_ADC_REG_RANK_1                  (ADC_SQR1_REGOFFSET | ADC_REG_RANK_1_SQRX_BITOFFSET_POS)  /*!< ADC group
                                           regular sequencer rank 1 */
#define LL_ADC_REG_RANK_2                  (ADC_SQR1_REGOFFSET | ADC_REG_RANK_2_SQRX_BITOFFSET_POS)  /*!< ADC group
                                           regular sequencer rank 2 */
#define LL_ADC_REG_RANK_3                  (ADC_SQR1_REGOFFSET | ADC_REG_RANK_3_SQRX_BITOFFSET_POS)  /*!< ADC group
                                           regular sequencer rank 3 */
#define LL_ADC_REG_RANK_4                  (ADC_SQR1_REGOFFSET | ADC_REG_RANK_4_SQRX_BITOFFSET_POS)  /*!< ADC group
                                           regular sequencer rank 4 */
#define LL_ADC_REG_RANK_5                  (ADC_SQR2_REGOFFSET | ADC_REG_RANK_5_SQRX_BITOFFSET_POS)  /*!< ADC group
                                           regular sequencer rank 5 */
#define LL_ADC_REG_RANK_6                  (ADC_SQR2_REGOFFSET | ADC_REG_RANK_6_SQRX_BITOFFSET_POS)  /*!< ADC group
                                           regular sequencer rank 6 */
#define LL_ADC_REG_RANK_7                  (ADC_SQR2_REGOFFSET | ADC_REG_RANK_7_SQRX_BITOFFSET_POS)  /*!< ADC group
                                           regular sequencer rank 7 */
#define LL_ADC_REG_RANK_8                  (ADC_SQR2_REGOFFSET | ADC_REG_RANK_8_SQRX_BITOFFSET_POS)  /*!< ADC group
                                           regular sequencer rank 8 */
#define LL_ADC_REG_RANK_9                  (ADC_SQR2_REGOFFSET | ADC_REG_RANK_9_SQRX_BITOFFSET_POS)  /*!< ADC group
                                           regular sequencer rank 9 */
#define LL_ADC_REG_RANK_10                 (ADC_SQR3_REGOFFSET | ADC_REG_RANK_10_SQRX_BITOFFSET_POS) /*!< ADC group
                                           regular sequencer rank 10 */
#define LL_ADC_REG_RANK_11                 (ADC_SQR3_REGOFFSET | ADC_REG_RANK_11_SQRX_BITOFFSET_POS) /*!< ADC group
                                           regular sequencer rank 11 */
#define LL_ADC_REG_RANK_12                 (ADC_SQR3_REGOFFSET | ADC_REG_RANK_12_SQRX_BITOFFSET_POS) /*!< ADC group
                                           regular sequencer rank 12 */
#define LL_ADC_REG_RANK_13                 (ADC_SQR3_REGOFFSET | ADC_REG_RANK_13_SQRX_BITOFFSET_POS) /*!< ADC group
                                           regular sequencer rank 13 */
#define LL_ADC_REG_RANK_14                 (ADC_SQR3_REGOFFSET | ADC_REG_RANK_14_SQRX_BITOFFSET_POS) /*!< ADC group
                                           regular sequencer rank 14 */
#define LL_ADC_REG_RANK_15                 (ADC_SQR4_REGOFFSET | ADC_REG_RANK_15_SQRX_BITOFFSET_POS) /*!< ADC group
                                           regular sequencer rank 15 */
#define LL_ADC_REG_RANK_16                 (ADC_SQR4_REGOFFSET | ADC_REG_RANK_16_SQRX_BITOFFSET_POS) /*!< ADC group
                                           regular sequencer rank 16 */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_INJ_TRIGGER_SOURCE  ADC group injected - Trigger source
  * @{
  */
#define LL_ADC_INJ_TRIG_SOFTWARE           (0x00000000UL)                                        /*!< ADC group injected
                                           conversion trigger internal: SW start. */

#define LL_ADC_INJ_TRIG_EXT_TIM1_TRGO        (ADC_INJ_TRIG_EXT_EDGE_DEFAULT ) 
#define LL_ADC_INJ_TRIG_EXT_TIM1_CH1         (ADC_INJ_TRIG_EXT_EDGE_DEFAULT | ADC_JSQR_JEXTSEL_0) 
#define LL_ADC_INJ_TRIG_EXT_TIM1_CH2         (ADC_INJ_TRIG_EXT_EDGE_DEFAULT | ADC_JSQR_JEXTSEL_1) 
#define LL_ADC_INJ_TRIG_EXT_TIM1_CH3         (ADC_INJ_TRIG_EXT_EDGE_DEFAULT | ADC_JSQR_JEXTSEL_1 | ADC_JSQR_JEXTSEL_0) 
#define LL_ADC_INJ_TRIG_EXT_TIM1_CH4         (ADC_INJ_TRIG_EXT_EDGE_DEFAULT | ADC_JSQR_JEXTSEL_2) 
#define LL_ADC_INJ_TRIG_EXT_TIM1_CH5         (ADC_INJ_TRIG_EXT_EDGE_DEFAULT | ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_0) 
#define LL_ADC_INJ_TRIG_EXT_TIM1_CH6         (ADC_INJ_TRIG_EXT_EDGE_DEFAULT | ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1) 
#define LL_ADC_INJ_TRIG_EXT_TIM3_CH1         (ADC_INJ_TRIG_EXT_EDGE_DEFAULT | ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1 | ADC_JSQR_JEXTSEL_0)
#define LL_ADC_INJ_TRIG_EXT_TIM3_TRGO        (ADC_INJ_TRIG_EXT_EDGE_DEFAULT | ADC_JSQR_JEXTSEL_3) 
#define LL_ADC_INJ_TRIG_EXT_EXTI_LINE11      (ADC_INJ_TRIG_EXT_EDGE_DEFAULT | ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_0) 
#define LL_ADC_INJ_TRIG_EXT_EXTI_LINE15      (ADC_INJ_TRIG_EXT_EDGE_DEFAULT | ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2) 

/**
  * @}
  */

/** @defgroup ADC_LL_EC_INJ_TRIGGER_EDGE  ADC group injected - Trigger edge
  * @{
  */
#define LL_ADC_INJ_TRIG_EXT_RISING         (                    ADC_JSQR_JEXTEN_0) /*!< ADC group injected conversion
                                           trigger polarity set to rising edge */
#define LL_ADC_INJ_TRIG_EXT_FALLING        (ADC_JSQR_JEXTEN_1                    ) /*!< ADC group injected conversion
                                           trigger polarity set to falling edge */
#define LL_ADC_INJ_TRIG_EXT_RISINGFALLING  (ADC_JSQR_JEXTEN_1 | ADC_JSQR_JEXTEN_0) /*!< ADC group injected conversion
                                           trigger polarity set to both rising and falling edges */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_INJ_TRIG_AUTO  ADC group injected - Automatic trigger mode
  * @{
  */
#define LL_ADC_INJ_TRIG_INDEPENDENT        (0x00000000UL)     /*!< ADC group injected conversion trigger independent.
                                           Setting mandatory if ADC group injected injected trigger source is set to
                                           an external trigger. */
#define LL_ADC_INJ_TRIG_FROM_GRP_REGULAR   (ADC_CFGR_JAUTO)   /*!< ADC group injected conversion trigger from ADC group
                                           regular. Setting compliant only with group injected trigger source set to
                                           SW start, without any further action on  ADC group injected conversion start
                                           or stop: in this case, ADC group injected is controlled only from ADC group
                                           regular. */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_INJ_SEQ_SCAN_LENGTH  ADC group injected - Sequencer scan length
  * @{
  */
#define LL_ADC_INJ_SEQ_SCAN_DISABLE        (0x00000000UL)                  /*!< ADC group injected sequencer enable
                                           (equivalent to sequencer of 1 rank: ADC conversion on only 1 channel) */
#define LL_ADC_INJ_SEQ_SCAN_ENABLE_2RANKS  (                ADC_JSQR_JL_0) /*!< ADC group injected sequencer enable
                                           with 2 ranks in the sequence */
#define LL_ADC_INJ_SEQ_SCAN_ENABLE_3RANKS  (ADC_JSQR_JL_1                ) /*!< ADC group injected sequencer enable
                                           with 3 ranks in the sequence */
#define LL_ADC_INJ_SEQ_SCAN_ENABLE_4RANKS  (ADC_JSQR_JL_1 | ADC_JSQR_JL_0) /*!< ADC group injected sequencer enable
                                           with 4 ranks in the sequence */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_INJ_SEQ_DISCONT_MODE  ADC group injected - Sequencer discontinuous mode
  * @{
  */
#define LL_ADC_INJ_SEQ_DISCONT_DISABLE     (0x00000000UL)     /*!< ADC group injected sequencer discontinuous mode
                                           disable */
#define LL_ADC_INJ_SEQ_DISCONT_1RANK       (ADC_CFGR_JDISCEN) /*!< ADC group injected sequencer discontinuous mode
                                           enable with sequence interruption every rank */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_INJ_SEQ_RANKS  ADC group injected - Sequencer ranks
  * @{
  */
#define LL_ADC_INJ_RANK_1                  (ADC_JDR1_REGOFFSET \
                                            | ADC_INJ_RANK_1_JSQR_BITOFFSET_POS) /*!< ADC group inj. sequencer rank 1 */
#define LL_ADC_INJ_RANK_2                  (ADC_JDR2_REGOFFSET \
                                            | ADC_INJ_RANK_2_JSQR_BITOFFSET_POS) /*!< ADC group inj. sequencer rank 2 */
#define LL_ADC_INJ_RANK_3                  (ADC_JDR3_REGOFFSET \
                                            | ADC_INJ_RANK_3_JSQR_BITOFFSET_POS) /*!< ADC group inj. sequencer rank 3 */
#define LL_ADC_INJ_RANK_4                  (ADC_JDR4_REGOFFSET \
                                            | ADC_INJ_RANK_4_JSQR_BITOFFSET_POS) /*!< ADC group inj. sequencer rank 4 */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_CHANNEL_SAMPLINGTIME  Channel - Sampling time
  * @{
  */
#define LL_ADC_SAMPLINGTIME_2CYCLES_5      (0x00000000UL)       /*!< Sampling time 2.5 ADC clock cycles */
#define LL_ADC_SAMPLINGTIME_6CYCLES_5      (ADC_SMPR2_SMP10_0)  /*!< Sampling time 6.5 ADC clock cycles */
#define LL_ADC_SAMPLINGTIME_12CYCLES_5     (ADC_SMPR2_SMP10_1)  /*!< Sampling time 12.5 ADC clock cycles */
#define LL_ADC_SAMPLINGTIME_24CYCLES_5     (ADC_SMPR2_SMP10_1 \
                                            | ADC_SMPR2_SMP10_0) /*!< Sampling time 24.5 ADC clock cycles */
#define LL_ADC_SAMPLINGTIME_47CYCLES_5     (ADC_SMPR2_SMP10_2)  /*!< Sampling time 47.5 ADC clock cycles */
#define LL_ADC_SAMPLINGTIME_92CYCLES_5     (ADC_SMPR2_SMP10_2 \
                                            | ADC_SMPR2_SMP10_0) /*!< Sampling time 92.5 ADC clock cycles */
#define LL_ADC_SAMPLINGTIME_247CYCLES_5    (ADC_SMPR2_SMP10_2 \
                                            | ADC_SMPR2_SMP10_1) /*!< Sampling time 247.5 ADC clock cycles */
#define LL_ADC_SAMPLINGTIME_640CYCLES_5    (ADC_SMPR2_SMP10_2 \
                                            | ADC_SMPR2_SMP10_1 \
                                            | ADC_SMPR2_SMP10_0) /*!< Sampling time 640.5 ADC clock cycles */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_CALIBRATION_NUMBER  calibration number
  * @{
  */
#define LL_ADC_CALIBRATION_NUMBER_1                (0x00000000UL)
#define LL_ADC_CALIBRATION_NUMBER_2                (ADC_CFGR2_CALNUM_0)
#define LL_ADC_CALIBRATION_NUMBER_4                (ADC_CFGR2_CALNUM_1)
#define LL_ADC_CALIBRATION_NUMBER_8                (ADC_CFGR2_CALNUM_1 | ADC_CFGR2_CALNUM_0)
#define LL_ADC_CALIBRATION_NUMBER_16               (ADC_CFGR2_CALNUM_2)
#define LL_ADC_CALIBRATION_NUMBER_32               (ADC_CFGR2_CALNUM_2 | ADC_CFGR2_CALNUM_0)

/**
  * @}
  */

/** @defgroup ADC_LL_EC_AWD_NUMBER Analog watchdog - Analog watchdog number
  * @{
  */
#define LL_ADC_AWD1                        (ADC_AWD_CR1_CHANNEL_MASK \
                                            | ADC_AWD_CR1_REGOFFSET) /*!< ADC analog watchdog number 1 */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_AWD_CHANNELS  Analog watchdog - Monitored channels
  * @{
  */
#define LL_ADC_AWD_DISABLE                 (0x00000000UL)                           /*!< ADC analog watchdog monitoring
                                           disabled */
#define LL_ADC_AWD_ALL_CHANNELS_REG        (ADC_CFGR_AWDEN)                       /*!< ADC analog watchdog monitoring
                                           of all channels, converted by group regular only */
#define LL_ADC_AWD_ALL_CHANNELS_INJ        (ADC_CFGR_JAWDEN)                      /*!< ADC analog watchdog monitoring
                                           of all channels, converted by group injected only */
#define LL_ADC_AWD_ALL_CHANNELS_REG_INJ    (ADC_CFGR_JAWDEN | ADC_CFGR_AWDEN)    /*!< ADC analog watchdog monitoring
                                           of all channels, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_0_REG           ((LL_ADC_CHANNEL_0  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_AWDEN | ADC_CFGR_AWDSGL)    /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN0, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_0_INJ           ((LL_ADC_CHANNEL_0  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDSGL)   /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN0, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_0_REG_INJ       ((LL_ADC_CHANNEL_0  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDEN \
                                            | ADC_CFGR_AWDSGL)                      /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN0, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_1_REG           ((LL_ADC_CHANNEL_1  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_AWDEN | ADC_CFGR_AWDSGL)    /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN1, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_1_INJ           ((LL_ADC_CHANNEL_1  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDSGL)   /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN1, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_1_REG_INJ       ((LL_ADC_CHANNEL_1  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDEN \
                                            | ADC_CFGR_AWDSGL)                      /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN1, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_2_REG           ((LL_ADC_CHANNEL_2  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_AWDEN | ADC_CFGR_AWDSGL)    /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN2, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_2_INJ           ((LL_ADC_CHANNEL_2  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDSGL)   /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN2, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_2_REG_INJ       ((LL_ADC_CHANNEL_2  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDEN \
                                            | ADC_CFGR_AWDSGL)                      /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN2, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_3_REG           ((LL_ADC_CHANNEL_3  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_AWDEN | ADC_CFGR_AWDSGL)    /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN3, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_3_INJ           ((LL_ADC_CHANNEL_3  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDSGL)   /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN3, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_3_REG_INJ       ((LL_ADC_CHANNEL_3  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDEN \
                                            | ADC_CFGR_AWDSGL)                      /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN3, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_4_REG           ((LL_ADC_CHANNEL_4  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_AWDEN | ADC_CFGR_AWDSGL)    /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN4, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_4_INJ           ((LL_ADC_CHANNEL_4  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDSGL)   /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN4, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_4_REG_INJ       ((LL_ADC_CHANNEL_4  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDEN \
                                            | ADC_CFGR_AWDSGL)                      /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN4, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_5_REG           ((LL_ADC_CHANNEL_5  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_AWDEN | ADC_CFGR_AWDSGL)    /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN5, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_5_INJ           ((LL_ADC_CHANNEL_5  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDSGL)   /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN5, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_5_REG_INJ       ((LL_ADC_CHANNEL_5  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDEN \
                                            | ADC_CFGR_AWDSGL)                      /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN5, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_6_REG           ((LL_ADC_CHANNEL_6  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_AWDEN | ADC_CFGR_AWDSGL)    /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN6, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_6_INJ           ((LL_ADC_CHANNEL_6  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDSGL)   /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN6, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_6_REG_INJ       ((LL_ADC_CHANNEL_6  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDEN \
                                            | ADC_CFGR_AWDSGL)                      /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN6, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_7_REG           ((LL_ADC_CHANNEL_7  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_AWDEN | ADC_CFGR_AWDSGL)    /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN7, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_7_INJ           ((LL_ADC_CHANNEL_7  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDSGL)   /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN7, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_7_REG_INJ       ((LL_ADC_CHANNEL_7  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDEN \
                                            | ADC_CFGR_AWDSGL)                      /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN7, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_8_REG           ((LL_ADC_CHANNEL_8  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_AWDEN | ADC_CFGR_AWDSGL)    /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN8, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_8_INJ           ((LL_ADC_CHANNEL_8  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDSGL)   /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN8, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_8_REG_INJ       ((LL_ADC_CHANNEL_8  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDEN \
                                            | ADC_CFGR_AWDSGL)                      /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN8, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_9_REG           ((LL_ADC_CHANNEL_9  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_AWDEN | ADC_CFGR_AWDSGL)    /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN9, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_9_INJ           ((LL_ADC_CHANNEL_9  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDSGL)   /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN9, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_9_REG_INJ       ((LL_ADC_CHANNEL_9  & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDEN \
                                            | ADC_CFGR_AWDSGL)                      /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN9, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_10_REG          ((LL_ADC_CHANNEL_10 & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_AWDEN | ADC_CFGR_AWDSGL)    /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN10, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_10_INJ          ((LL_ADC_CHANNEL_10 & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDSGL)   /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN10, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_10_REG_INJ      ((LL_ADC_CHANNEL_10 & ADC_CHANNEL_ID_MASK)\
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDEN \
                                            | ADC_CFGR_AWDSGL)                      /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN10, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_11_REG          ((LL_ADC_CHANNEL_11 & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_AWDEN | ADC_CFGR_AWDSGL)    /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN11, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_11_INJ          ((LL_ADC_CHANNEL_11 & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDSGL)   /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN11, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_11_REG_INJ      ((LL_ADC_CHANNEL_11 & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDEN \
                                            | ADC_CFGR_AWDSGL)                      /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN11, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_12_REG          ((LL_ADC_CHANNEL_12 & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_AWDEN | ADC_CFGR_AWDSGL)    /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN12, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_12_INJ          ((LL_ADC_CHANNEL_12 & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDSGL)   /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN12, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_12_REG_INJ      ((LL_ADC_CHANNEL_12 & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDEN \
                                            | ADC_CFGR_AWDSGL)                      /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN12, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_13_REG          ((LL_ADC_CHANNEL_13 & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_AWDEN | ADC_CFGR_AWDSGL)    /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN13, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_13_INJ          ((LL_ADC_CHANNEL_13 & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDSGL)   /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN13, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_13_REG_INJ      ((LL_ADC_CHANNEL_13 & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDEN \
                                            | ADC_CFGR_AWDSGL)                      /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN13, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_14_REG          ((LL_ADC_CHANNEL_14 & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_AWDEN | ADC_CFGR_AWDSGL)    /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN14, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_14_INJ          ((LL_ADC_CHANNEL_14 & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDSGL)   /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN14, converted by group only */
#define LL_ADC_AWD_CHANNEL_14_REG_INJ      ((LL_ADC_CHANNEL_14 & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDEN \
                                            | ADC_CFGR_AWDSGL)                      /*!< ADC analog watchdog monitoring
                                           of ADC channel ADCx_IN14, converted by either group regular or injected */


#define LL_ADC_AWD_CH_TEMPSENSOR_REG       ((LL_ADC_CHANNEL_TEMPSENSOR & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_AWDEN | ADC_CFGR_AWDSGL)    /*!< ADC analog watchdog monitoring
                                           of ADC internal channel connected to Tempsensor ,converted by group regular only */
#define LL_ADC_AWD_CH_TEMPSENSOR_INJ       ((LL_ADC_CHANNEL_TEMPSENSOR & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDSGL)   /*!< ADC analog watchdog monitoring
                                           of ADC internal channel connected to Tempsensor ,converted by group injected only */
#define LL_ADC_AWD_CH_TEMPSENSOR_REG_INJ   ((LL_ADC_CHANNEL_TEMPSENSOR & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDEN \
                                            | ADC_CFGR_AWDSGL)                      /*!< ADC analog watchdog monitoring
                                           of ADC internal channel connected to Tempsensor, converted by either group regular or injected */
#define LL_ADC_AWD_CH_VREFINT_REG          ((LL_ADC_CHANNEL_VREFINT & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_AWDEN | ADC_CFGR_AWDSGL)    /*!< ADC analog watchdog monitoring
                                           of ADC internal channel connected to Vrefint ,converted by group regular only */
#define LL_ADC_AWD_CH_VREFINT_INJ          ((LL_ADC_CHANNEL_VREFINT & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDSGL)   /*!< ADC analog watchdog monitoring
                                           of ADC internal channel connected to Vrefint ,converted by group injected only */
#define LL_ADC_AWD_CH_VREFINT_REG_INJ      ((LL_ADC_CHANNEL_VREFINT & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDEN \
                                            | ADC_CFGR_AWDSGL)                      /*!< ADC analog watchdog monitoring
                                           of ADC internal channel connected to Vrefint, converted by either group regular or injected */
#define LL_ADC_AWD_CH_1_3VCCA_REG             ((LL_ADC_CHANNEL_1_3VCCA & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_AWDEN | ADC_CFGR_AWDSGL)    /*!< ADC analog watchdog monitoring
                                           of ADC internal channel connected to 1/3 VCCA: Internal
                                           voltage reference, converted by group regular only */
#define LL_ADC_AWD_CH_1_3VCCA_INJ             ((LL_ADC_CHANNEL_1_3VCCA & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDSGL)   /*!< ADC analog watchdog monitoring
                                           of ADC internal channel connected to 1/3 VCCA: Internal
                                           voltage reference, converted by group injected only */
#define LL_ADC_AWD_CH_1_3VCCA_REG_INJ         ((LL_ADC_CHANNEL_1_3VCCA & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDEN \
                                            | ADC_CFGR_AWDSGL)                      /*!< ADC analog watchdog monitoring
                                           of ADC internal channel connected to 1/3 VCCA: Internal
                                           voltage reference, converted by either group regular or injected */
#define LL_ADC_AWD_CH_OPA1_REG              ((LL_ADC_CHANNEL_OPA1 & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_AWDEN | ADC_CFGR_AWDSGL)    /*!< ADC analog watchdog monitoring
                                           of ADC internal channel connected to OPA1 ,converted by group regular only */
#define LL_ADC_AWD_CH_OPA1_INJ              ((LL_ADC_CHANNEL_OPA1 & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDSGL)   /*!< ADC analog watchdog monitoring
                                           of ADC internal channel connected to OPA1 ,converted by group injected only */
#define LL_ADC_AWD_CH_OPA1_REG_INJ          ((LL_ADC_CHANNEL_OPA1 & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDEN \
                                            | ADC_CFGR_AWDSGL)                      /*!< ADC analog watchdog monitoring
                                           of ADC internal channel connected to OPA1, converted by either group regular or injected */
#define LL_ADC_AWD_CH_OPA2_REG              ((LL_ADC_CHANNEL_OPA2 & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_AWDEN | ADC_CFGR_AWDSGL)    /*!< ADC analog watchdog monitoring
                                           of ADC internal channel connected to OPA2 ,converted by group regular only */
#define LL_ADC_AWD_CH_OPA2_INJ              ((LL_ADC_CHANNEL_OPA2 & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDSGL)   /*!< ADC analog watchdog monitoring
                                           of ADC internal channel connected to OPA2 ,converted by group injected only */
#define LL_ADC_AWD_CH_OPA2_REG_INJ          ((LL_ADC_CHANNEL_OPA2 & ADC_CHANNEL_ID_MASK) \
                                            | ADC_CFGR_JAWDEN | ADC_CFGR_AWDEN \
                                            | ADC_CFGR_AWDSGL)                      /*!< ADC analog watchdog monitoring
                                           of ADC internal channel connected to OPA2, converted by either group regular or injected */

/**
  * @}
  */

/** @defgroup ADC_LL_EC_AWD_THRESHOLDS  Analog watchdog - Thresholds
  * @{
  */
#define LL_ADC_AWD_THRESHOLD_HIGH          (ADC_TR_HT)      /*!< ADC analog watchdog threshold high */
#define LL_ADC_AWD_THRESHOLD_LOW           (ADC_TR_LT)      /*!< ADC analog watchdog threshold low */
#define LL_ADC_AWD_THRESHOLDS_HIGH_LOW     (ADC_TR_HT \
                                            | ADC_TR_LT)     /*!< ADC analog watchdog both thresholds high and low
                                           concatenated into the same data */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_AWD_FILTERING_CONFIG  Analog watchdog - filtering config
  * @{
  */
#define LL_ADC_AWD_FILTERING_NONE          (0x00000000UL)                          /*!< ADC analog watchdog no filtering,
                                           one out-of-window sample is needed to raise flag or interrupt */
#define LL_ADC_AWD_FILTERING_2SAMPLES      (ADC_TR_AWDFILT_0)                     /*!< ADC analog watchdog 2
                                           out-of-window samples are needed to raise flag or interrupt */
#define LL_ADC_AWD_FILTERING_3SAMPLES      (ADC_TR_AWDFILT_1)                     /*!< ADC analog watchdog 3
                                           consecutives out-of-window samples are needed to raise flag or interrupt */
#define LL_ADC_AWD_FILTERING_4SAMPLES      (ADC_TR_AWDFILT_1 | ADC_TR_AWDFILT_0) /*!< ADC analog watchdog 4
                                           consecutives out-of-window samples are needed to raise flag or interrupt */
#define LL_ADC_AWD_FILTERING_5SAMPLES      (ADC_TR_AWDFILT_2)                     /*!< ADC analog watchdog 5
                                           consecutives out-of-window samples are needed to raise flag or interrupt */
#define LL_ADC_AWD_FILTERING_6SAMPLES      (ADC_TR_AWDFILT_2 | ADC_TR_AWDFILT_0) /*!< ADC analog watchdog 6
                                           consecutives out-of-window samples are needed to raise flag or interrupt */
#define LL_ADC_AWD_FILTERING_7SAMPLES      (ADC_TR_AWDFILT_2 | ADC_TR_AWDFILT_1) /*!< ADC analog watchdog 7
                                           consecutives out-of-window samples are needed to raise flag or interrupt */
#define LL_ADC_AWD_FILTERING_8SAMPLES      (ADC_TR_AWDFILT_2 | ADC_TR_AWDFILT_1 \
                                            | ADC_TR_AWDFILT_0)                    /*!< ADC analog watchdog 8
                                           consecutives out-of-window samples are needed to raise flag or interrupt */
/**
  * @}
  */

#if defined(ADC_CCR_VREFSEL)
/** @defgroup ADC_LL_EC_Reference  ADC Reference
  * @{
  */
#define LL_ADC_REFERENCE_VCCA                  (0x00000000)                                /*!< ADC Reference VCCA */
#define LL_ADC_REFERENCE_VREFBUF               (ADC_CCR_VREFSEL)                           /*!< ADC Reference Vrefbuf */
/**
  * @}
  */
#endif

/** @defgroup ADC_LL_EC_HELPER_MACRO  Definitions of constants used by helper macro
  * @{
  */
#define LL_ADC_TEMPERATURE_CALC_ERROR      ((int16_t)0x7FFF)  /* Temperature calculation error using helper macro
                                                                 @ref __LL_ADC_CALC_TEMPERATURE(), due to issue on
                                                                 calibration parameters. This value is coded on 16 bits
                                                                 (to fit on signed word or double word) and corresponds
                                                                 to an inconsistent temperature value. */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_HW_DELAYS  Definitions of ADC hardware constraints delays
  * @note   Only ADC peripheral HW delays are defined in ADC LL driver driver,
  *         not timeout values.
  *         For details on delays values, refer to descriptions in source code
  *         above each literal definition.
  * @{
  */

/* Note: Only ADC peripheral HW delays are defined in ADC LL driver driver,   */
/*       not timeout values.                                                  */
/*       Timeout values for ADC operations are dependent to device clock      */
/*       configuration (system clock versus ADC clock),                       */
/*       and therefore must be defined in user application.                   */
/*       Indications for estimation of ADC timeout delays, for this           */
/*       chip series:                                                        */
/*       - ADC calibration time: maximum delay is 112/fADC.                   */
/*         (refer to device datasheet, parameter "tCAL")                      */
/*       - ADC enable time: maximum delay is 1 conversion cycle.              */
/*         (refer to device datasheet, parameter "tSTAB")                     */
/*       - ADC disable time: maximum delay should be a few ADC clock cycles   */
/*       - ADC stop conversion time: maximum delay should be a few ADC clock  */
/*         cycles                                                             */
/*       - ADC conversion time: duration depending on ADC clock and ADC       */
/*         configuration.                                                     */
/*         (refer to device reference manual, section "Timing")               */

/* Delay for internal voltage reference stabilization time.                   */
/* Delay set to maximum value (refer to device datasheet,                     */
/* parameter "tstart_vrefint").                                               */
/* Unit: us                                                                   */
#define LL_ADC_DELAY_VREFINT_STAB_US           ( 12UL)        /*!< Delay for internal voltage reference stabilization
                                                                   time */

/* Delay for temperature sensor stabilization time.                           */
/* Literal set to maximum value (refer to device datasheet,                   */
/* parameter "tSTART").                                                       */
/* Unit: us                                                                   */
#define LL_ADC_DELAY_TEMPSENSOR_STAB_US        ( 10UL)        /*!< Delay for temperature sensor stabilization time */
#define LL_ADC_DELAY_TEMPSENSOR_BUFFER_STAB_US ( 15UL)        /*!< Delay for temperature sensor buffer stabilization
                                                                   time (starting from ADC enable, refer to
                                                                   @ref LL_ADC_Enable()) */

/* Delay required between ADC end of calibration and ADC enable.              */
/* Note: On this chip series, a minimum number of ADC clock cycles           */
/*       are required between ADC end of calibration and ADC enable.          */
/*       Wait time can be computed in user application by waiting for the     */
/*       equivalent number of CPU cycles, by taking into account              */
/*       ratio of CPU clock versus ADC clock prescalers.                      */
/* Unit: ADC clock cycles.                                                    */
#define LL_ADC_DELAY_CALIB_ENABLE_ADC_CYCLES   (  4UL)        /*!< Delay required between ADC end of calibration
                                                                   and ADC enable */

/**
  * @}
  */

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup ADC_LL_Exported_Macros ADC Exported Macros
  * @{
  */

/** @defgroup ADC_LL_EM_WRITE_READ Common write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in ADC register
  * @param  __INSTANCE__ ADC Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_ADC_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in ADC register
  * @param  __INSTANCE__ ADC Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_ADC_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/** @defgroup ADC_LL_EM_HELPER_MACRO ADC helper macro
  * @{
  */

/**
  * @brief  Helper macro to get ADC channel number in decimal format
  *         from literals LL_ADC_CHANNEL_x.
  * @note   Example:
  *           __LL_ADC_CHANNEL_TO_DECIMAL_NB(LL_ADC_CHANNEL_4)
  *           will return decimal number "4".
  * @note   The input can be a value from functions where a channel
  *         number is returned, either defined with number
  *         or with bitfield (only one bit must be set).
  * @param  __CHANNEL__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1                 
  *         @arg @ref LL_ADC_CHANNEL_2                 
  *         @arg @ref LL_ADC_CHANNEL_3                 
  *         @arg @ref LL_ADC_CHANNEL_4                 
  *         @arg @ref LL_ADC_CHANNEL_5                 
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR       
  *         @arg @ref LL_ADC_CHANNEL_VREFINT    
  *         @arg @ref LL_ADC_CHANNEL_1_3VCCA       
  *         @arg @ref LL_ADC_CHANNEL_OPA1                  
  *         @arg @ref LL_ADC_CHANNEL_OPA2                    
  * @note   On this chip series, above parameter are not available on all ADC instances.\n
  *         On this chip series, all ADCx are not available on all devices. Refer to device datasheet
  *         for more details.
  * @retval Value between Min_Data=0 and Max_Data=19
  */
#define __LL_ADC_CHANNEL_TO_DECIMAL_NB(__CHANNEL__)                                        \
  (((__CHANNEL__) & ADC_CHANNEL_ID_NUMBER_MASK) >> ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS)

/**
  * @brief  Helper macro to get ADC channel in literal format LL_ADC_CHANNEL_x
  *         from number in decimal format.
  * @note   Example:
  *           __LL_ADC_DECIMAL_NB_TO_CHANNEL(4)
  *           will return a data equivalent to "LL_ADC_CHANNEL_4".
  * @param  __DECIMAL_NB__ Value between Min_Data=0 and Max_Data=19
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1                 
  *         @arg @ref LL_ADC_CHANNEL_2                 
  *         @arg @ref LL_ADC_CHANNEL_3                 
  *         @arg @ref LL_ADC_CHANNEL_4                 
  *         @arg @ref LL_ADC_CHANNEL_5                 
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR       
  *         @arg @ref LL_ADC_CHANNEL_VREFINT    
  *         @arg @ref LL_ADC_CHANNEL_1_3VCCA       
  *         @arg @ref LL_ADC_CHANNEL_OPA1                  
  *         @arg @ref LL_ADC_CHANNEL_OPA2           
  * @note   On this chip series, above parameter are not available on all ADC instances.\n
  *         On this chip series, all ADCx are not available on all devices. Refer to device datasheet
  *         for more details.
  */
#define __LL_ADC_DECIMAL_NB_TO_CHANNEL(__DECIMAL_NB__)                                                  \
  (((__DECIMAL_NB__) <= 9UL) ?                                                                          \
   (                                                                                                    \
       ((__DECIMAL_NB__) << ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS)                             |          \
       (ADC_SMPR1_REGOFFSET | (((3UL * (__DECIMAL_NB__))) << ADC_CHANNEL_SMPx_BITOFFSET_POS))           \
   )                                                                                                    \
   :                                                                                                    \
   (                                                                                                    \
     ((__DECIMAL_NB__) <= 19UL) ?                                                                         \
     (                                                                                                    \
         ((__DECIMAL_NB__) << ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS)                             |          \
         (ADC_SMPR2_REGOFFSET | (((3UL * ((__DECIMAL_NB__) - 10U))) << ADC_CHANNEL_SMPx_BITOFFSET_POS))   \
     )                                                                                                    \                                                                                            \
   )                                                                                                    \
  )

/**
  * @brief  Helper macro to determine whether the selected channel
  *         corresponds to literal definitions of driver.
  * @note   The different literal definitions of ADC channels are:
  *         - ADC internal channel:
  *           LL_ADC_CHANNEL_VREFINT, LL_ADC_CHANNEL_TEMPSENSOR, ...
  *         - ADC external channel (channel connected to a GPIO pin):
  *           LL_ADC_CHANNEL_1, LL_ADC_CHANNEL_2, ...
  * @note   The channel parameter must be a value defined from literal
  *         definition of a ADC internal channel (LL_ADC_CHANNEL_VREFINT,
  *         LL_ADC_CHANNEL_TEMPSENSOR, ...),
  *         ADC external channel (LL_ADC_CHANNEL_1, LL_ADC_CHANNEL_2, ...),
  *         must not be a value from functions where a channel number is
  *         returned from ADC registers,
  *         because internal and external channels share the same channel
  *         number in ADC registers. The differentiation is made only with
  *         parameters definitions of driver.
  * @param  __CHANNEL__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1                 
  *         @arg @ref LL_ADC_CHANNEL_2                 
  *         @arg @ref LL_ADC_CHANNEL_3                 
  *         @arg @ref LL_ADC_CHANNEL_4                 
  *         @arg @ref LL_ADC_CHANNEL_5                 
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR       
  *         @arg @ref LL_ADC_CHANNEL_VREFINT    
  *         @arg @ref LL_ADC_CHANNEL_1_3VCCA       
  *         @arg @ref LL_ADC_CHANNEL_OPA1                  
  *         @arg @ref LL_ADC_CHANNEL_OPA2      
  * @note   On this chip series, above parameter are not available on all ADC instances.\n
  *         On this chip series, all ADCx are not available on all devices. Refer to device datasheet
  *         for more details.
  * @retval Value "0" if the channel corresponds to a parameter definition of a ADC external channel (channel
                      connected to a GPIO pin).
  *         Value "1" if the channel corresponds to a parameter definition of a ADC internal channel.
  */
#define __LL_ADC_IS_CHANNEL_INTERNAL(__CHANNEL__)                              \
  (((__CHANNEL__) & ADC_CHANNEL_ID_INTERNAL_CH_MASK) != 0UL)

/**
  * @brief  Helper macro to convert a channel defined from parameter
  *         definition of a ADC internal channel (LL_ADC_CHANNEL_VREFINT,
  *         LL_ADC_CHANNEL_TEMPSENSOR, ...),
  *         to its equivalent parameter definition of a ADC external channel
  *         (LL_ADC_CHANNEL_1, LL_ADC_CHANNEL_2, ...).
  * @note   The channel parameter can be, additionally to a value
  *         defined from parameter definition of a ADC internal channel
  *         (LL_ADC_CHANNEL_VREFINT, LL_ADC_CHANNEL_TEMPSENSOR, ...),
  *         a value defined from parameter definition of
  *         ADC external channel (LL_ADC_CHANNEL_1, LL_ADC_CHANNEL_2, ...)
  *         or a value from functions where a channel number is returned
  *         from ADC registers.
  * @param  __CHANNEL__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1                 
  *         @arg @ref LL_ADC_CHANNEL_2                 
  *         @arg @ref LL_ADC_CHANNEL_3                 
  *         @arg @ref LL_ADC_CHANNEL_4                 
  *         @arg @ref LL_ADC_CHANNEL_5                 
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR       
  *         @arg @ref LL_ADC_CHANNEL_VREFINT    
  *         @arg @ref LL_ADC_CHANNEL_1_3VCCA       
  *         @arg @ref LL_ADC_CHANNEL_OPA1                  
  *         @arg @ref LL_ADC_CHANNEL_OPA2          
  * @note   On this chip series, above parameter are not available on all ADC instances.\n
  *         On this chip series, all ADCx are not available on all devices. Refer to device datasheet
  *         for more details.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1                 
  *         @arg @ref LL_ADC_CHANNEL_2                 
  *         @arg @ref LL_ADC_CHANNEL_3                 
  *         @arg @ref LL_ADC_CHANNEL_4                 
  *         @arg @ref LL_ADC_CHANNEL_5                 
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  */
#define __LL_ADC_CHANNEL_INTERNAL_TO_EXTERNAL(__CHANNEL__)                     \
  ((__CHANNEL__) & ~ADC_CHANNEL_ID_INTERNAL_CH_MASK)

/**
  * @brief  Helper macro to define ADC analog watchdog parameter:
  *         define a single channel to monitor with analog watchdog
  *         from sequencer channel and groups definition.
  * @note   To be used with function @ref LL_ADC_SetAnalogWDMonitChannels().
  *         Example:
  *           LL_ADC_SetAnalogWDMonitChannels(
  *             ADC1, LL_ADC_AWD1,
  *             __LL_ADC_ANALOGWD_CHANNEL_GROUP(LL_ADC_CHANNEL4, LL_ADC_GROUP_REGULAR))
  * @param  __CHANNEL__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1                 
  *         @arg @ref LL_ADC_CHANNEL_2                 
  *         @arg @ref LL_ADC_CHANNEL_3                 
  *         @arg @ref LL_ADC_CHANNEL_4                 
  *         @arg @ref LL_ADC_CHANNEL_5                 
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR       
  *         @arg @ref LL_ADC_CHANNEL_VREFINT    
  *         @arg @ref LL_ADC_CHANNEL_1_3VCCA       
  *         @arg @ref LL_ADC_CHANNEL_OPA1                  
  *         @arg @ref LL_ADC_CHANNEL_OPA2          
  * @note   On this chip series, above parameter are not available on all ADC instances.\n
  *         On this chip series, all ADCx are not available on all devices. Refer to device datasheet
  *         for more details.
  * @param  __GROUP__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_GROUP_REGULAR
  *         @arg @ref LL_ADC_GROUP_INJECTED
  *         @arg @ref LL_ADC_GROUP_REGULAR_INJECTED
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_AWD_DISABLE
  *         @arg @ref LL_ADC_AWD_ALL_CHANNELS_REG        
  *         @arg @ref LL_ADC_AWD_ALL_CHANNELS_INJ        
  *         @arg @ref LL_ADC_AWD_ALL_CHANNELS_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_0_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_0_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_0_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_1_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_1_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_1_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_2_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_2_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_2_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_3_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_3_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_3_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_4_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_4_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_4_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_5_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_5_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_5_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_6_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_6_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_6_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_7_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_7_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_7_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_8_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_8_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_8_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_9_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_9_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_9_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_10_REG          
  *         @arg @ref LL_ADC_AWD_CHANNEL_10_INJ          
  *         @arg @ref LL_ADC_AWD_CHANNEL_10_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_11_REG          
  *         @arg @ref LL_ADC_AWD_CHANNEL_11_INJ          
  *         @arg @ref LL_ADC_AWD_CHANNEL_11_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_12_REG          
  *         @arg @ref LL_ADC_AWD_CHANNEL_12_INJ          
  *         @arg @ref LL_ADC_AWD_CHANNEL_12_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_13_REG          
  *         @arg @ref LL_ADC_AWD_CHANNEL_13_INJ          
  *         @arg @ref LL_ADC_AWD_CHANNEL_13_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_14_REG          
  *         @arg @ref LL_ADC_AWD_CHANNEL_14_INJ          
  *         @arg @ref LL_ADC_AWD_CHANNEL_14_REG_INJ
  *         @arg @ref LL_ADC_AWD_CH_VREFINT_REG          
  *         @arg @ref LL_ADC_AWD_CH_VREFINT_INJ          
  *         @arg @ref LL_ADC_AWD_CH_VREFINT_REG_INJ
  *         @arg @ref LL_ADC_AWD_CH_TEMPSENSOR_REG          
  *         @arg @ref LL_ADC_AWD_CH_TEMPSENSOR_INJ          
  *         @arg @ref LL_ADC_AWD_CH_TEMPSENSOR_REG_INJ
  *         @arg @ref LL_ADC_AWD_CH_1_3VCCA_REG             
  *         @arg @ref LL_ADC_AWD_CH_1_3VCCA_INJ             
  *         @arg @ref LL_ADC_AWD_CH_1_3VCCA_REG_INJ         
  *         @arg @ref LL_ADC_AWD_CH_OPA1_REG             
  *         @arg @ref LL_ADC_AWD_CH_OPA1_INJ             
  *         @arg @ref LL_ADC_AWD_CH_OPA1_REG_INJ         
  *         @arg @ref LL_ADC_AWD_CH_OPA2_REG             
  *         @arg @ref LL_ADC_AWD_CH_OPA2_INJ             
  *         @arg @ref LL_ADC_AWD_CH_OPA2_REG_INJ 
  *             On this chip series, all ADCx are not available on all devices. Refer to device datasheet
  *             for more details.
  */
#define __LL_ADC_ANALOGWD_CHANNEL_GROUP(__CHANNEL__, __GROUP__)                                           \
  (((__GROUP__) == LL_ADC_GROUP_REGULAR)                                                                  \
   ? (((__CHANNEL__) & ADC_CHANNEL_ID_MASK) | ADC_CFGR_AWDEN | ADC_CFGR_AWDSGL)                         \
   :                                                                                                      \
   ((__GROUP__) == LL_ADC_GROUP_INJECTED)                                                                 \
   ? (((__CHANNEL__) & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWDEN | ADC_CFGR_AWDSGL)                        \
   :                                                                                                      \
   (((__CHANNEL__) & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWDEN | ADC_CFGR_AWDEN | ADC_CFGR_AWDSGL)        \
  )

/**
  * @brief  Helper macro to set the value of ADC analog watchdog threshold high
  *         or low in function of ADC resolution, when ADC resolution is
  *         different of 12 bits.
  * @note   To be used with function @ref LL_ADC_ConfigAnalogWDThresholds()
  *         or @ref LL_ADC_SetAnalogWDThresholds().
  *         Example, with a ADC resolution of 8 bits, to set the value of
  *         analog watchdog threshold high (on 8 bits):
  *           LL_ADC_SetAnalogWDThresholds
  *            (< ADCx param >,
  *             __LL_ADC_ANALOGWD_SET_THRESHOLD_RESOLUTION(LL_ADC_RESOLUTION_8B, <threshold_value_8_bits>)
  *            );
  * @param  __ADC_RESOLUTION__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @param  __AWD_THRESHOLD__ Value between Min_Data=0x000 and Max_Data=0xFFF
  * @retval Value between Min_Data=0x000 and Max_Data=0xFFF
  */
#define __LL_ADC_ANALOGWD_SET_THRESHOLD_RESOLUTION(__ADC_RESOLUTION__, __AWD_THRESHOLD__) \
  ((__AWD_THRESHOLD__) << ((__ADC_RESOLUTION__) >> (ADC_CFGR_RES_BITOFFSET_POS - 1U )))

/**
  * @brief  Helper macro to get the value of ADC analog watchdog threshold high
  *         or low in function of ADC resolution, when ADC resolution is
  *         different of 12 bits.
  * @note   To be used with function @ref LL_ADC_GetAnalogWDThresholds().
  *         Example, with a ADC resolution of 8 bits, to get the value of
  *         analog watchdog threshold high (on 8 bits):
  *           < threshold_value_6_bits > = __LL_ADC_ANALOGWD_GET_THRESHOLD_RESOLUTION
  *            (LL_ADC_RESOLUTION_8B,
  *             LL_ADC_GetAnalogWDThresholds(<ADCx param>, LL_ADC_AWD_THRESHOLD_HIGH)
  *            );
  * @param  __ADC_RESOLUTION__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @param  __AWD_THRESHOLD_12_BITS__ Value between Min_Data=0x000 and Max_Data=0xFFF
  * @retval Value between Min_Data=0x000 and Max_Data=0xFFF
  */
#define __LL_ADC_ANALOGWD_GET_THRESHOLD_RESOLUTION(__ADC_RESOLUTION__, __AWD_THRESHOLD_12_BITS__) \
  ((__AWD_THRESHOLD_12_BITS__) >> ((__ADC_RESOLUTION__) >> (ADC_CFGR_RES_BITOFFSET_POS - 1U )))

/**
  * @brief  Helper macro to get the ADC analog watchdog threshold high
  *         or low from raw value containing both thresholds concatenated.
  * @note   To be used with function @ref LL_ADC_GetAnalogWDThresholds().
  *         Example, to get analog watchdog threshold high from the register raw value:
  *           __LL_ADC_ANALOGWD_THRESHOLDS_HIGH_LOW(LL_ADC_AWD_THRESHOLD_HIGH, <raw_value_with_both_thresholds>);
  * @param  __AWD_THRESHOLD_TYPE__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_THRESHOLD_HIGH
  *         @arg @ref LL_ADC_AWD_THRESHOLD_LOW
  * @param  __AWD_THRESHOLDS__ Value between Min_Data=0x00000000 and Max_Data=0xFFFFFFFF
  * @retval Value between Min_Data=0x000 and Max_Data=0xFFF
  */
#define __LL_ADC_ANALOGWD_THRESHOLDS_HIGH_LOW(__AWD_THRESHOLD_TYPE__, __AWD_THRESHOLDS__)                            \
  (((__AWD_THRESHOLDS__) >> (((__AWD_THRESHOLD_TYPE__) & ADC_AWD_TRX_BIT_HIGH_MASK) >> ADC_AWD_TRX_BIT_HIGH_SHIFT4)) \
   & LL_ADC_AWD_THRESHOLD_LOW)

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
#define __LL_ADC_COMMON_INSTANCE(__ADCx__)  (ADC_COMMON)

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

#define __LL_ADC_IS_ENABLED_ALL_COMMON_INSTANCE(__ADCXY_COMMON__)              \
  (LL_ADC_IsEnabled(ADC1))

/**
  * @brief  Helper macro to define the ADC conversion data full-scale digital
  *         value corresponding to the selected ADC resolution.
  * @note   ADC conversion data full-scale corresponds to voltage range
  *         determined by analog voltage references Vref+ and Vref-
  *         (refer to reference manual).
  * @param  __ADC_RESOLUTION__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @retval ADC conversion data full-scale digital value (unit: digital value of ADC conversion data)
  */
#define __LL_ADC_DIGITAL_SCALE(__ADC_RESOLUTION__)                             \
  (0xFFFUL >> ((__ADC_RESOLUTION__) >> (ADC_CFGR_RES_BITOFFSET_POS - 1UL)))

/**
  * @brief  Helper macro to convert the ADC conversion data from
  *         a resolution to another resolution.
  * @param  __DATA__ ADC conversion data to be converted
  * @param  __ADC_RESOLUTION_CURRENT__ Resolution of the data to be converted
  *         This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @param  __ADC_RESOLUTION_TARGET__ Resolution of the data after conversion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @retval ADC conversion data to the requested resolution
  */
#define __LL_ADC_CONVERT_DATA_RESOLUTION(__DATA__,\
                                         __ADC_RESOLUTION_CURRENT__,\
                                         __ADC_RESOLUTION_TARGET__)          \
(((__DATA__)                                                                 \
  << ((__ADC_RESOLUTION_CURRENT__) >> (ADC_CFGR_RES_BITOFFSET_POS - 1UL)))   \
 >> ((__ADC_RESOLUTION_TARGET__) >> (ADC_CFGR_RES_BITOFFSET_POS - 1UL))      \
)

/**
  * @brief  Helper macro to calculate the voltage (unit: mVolt)
  *         corresponding to a ADC conversion data (unit: digital value).
  * @param  __VREFANALOG_VOLTAGE__ Analog reference voltage (unit: mV)
  * @param  __ADC_DATA__ ADC conversion data (resolution 12 bits)
  *                       (unit: digital value).
  * @param  __ADC_RESOLUTION__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @retval ADC conversion data equivalent voltage value (unit: mVolt)
  */
#define __LL_ADC_CALC_DATA_TO_VOLTAGE(__VREFANALOG_VOLTAGE__,\
                                      __ADC_DATA__,\
                                      __ADC_RESOLUTION__)                    \
((__ADC_DATA__) * (__VREFANALOG_VOLTAGE__)                                   \
 / __LL_ADC_DIGITAL_SCALE(__ADC_RESOLUTION__)                                \
)

/**
  * @brief  Helper macro to calculate the voltage (unit: mVolt)
  *         corresponding to a ADC conversion data (unit: digital value) in
  *         differential ended mode.
  * @note   ADC data from ADC data register is unsigned and centered around
  *         middle code in. Converted voltage can be positive or negative
  *         depending on differential input voltages.
  * @param  __VREFANALOG_VOLTAGE__ Analog reference voltage (unit: mV)
  * @param  __ADC_DATA__ ADC conversion data (unit: digital value).
  * @param  __ADC_RESOLUTION__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @retval ADC conversion data equivalent voltage value (unit: mVolt)
  */
#define __LL_ADC_CALC_DIFF_DATA_TO_VOLTAGE(__VREFANALOG_VOLTAGE__,\
                                           __ADC_DATA__,\
                                           __ADC_RESOLUTION__)\
((int32_t)((__ADC_DATA__) << 1U) * (int32_t)(__VREFANALOG_VOLTAGE__)\
 / (int32_t)(__LL_ADC_DIGITAL_SCALE(__ADC_RESOLUTION__))\
 - (int32_t)(__VREFANALOG_VOLTAGE__))

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
  * @note   On this chip series, calibration data of temperature sensor
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
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @retval Temperature (unit: degree Celsius)
  *         In case or error, value LL_ADC_TEMPERATURE_CALC_ERROR is returned (inconsistent temperature value)
  */
#define __LL_ADC_CALC_TEMPERATURE(__VREFANALOG_VOLTAGE__,\
                                  __TEMPSENSOR_ADC_DATA__,\
                                  __ADC_RESOLUTION__)\
((((int32_t)*TEMPSENSOR_CAL2_ADDR - (int32_t)*TEMPSENSOR_CAL1_ADDR) != 0) ?       \
 (((( ((int32_t)((__LL_ADC_CONVERT_DATA_RESOLUTION((__TEMPSENSOR_ADC_DATA__),     \
                                                   (__ADC_RESOLUTION__),          \
                                                   LL_ADC_RESOLUTION_12B)         \
                  * (__VREFANALOG_VOLTAGE__))                                     \
                 / TEMPSENSOR_CAL_VREFANALOG)                                     \
       - (int32_t) *TEMPSENSOR_CAL1_ADDR)                                         \
    ) * (int32_t)(TEMPSENSOR_CAL2_TEMP - TEMPSENSOR_CAL1_TEMP)                    \
   ) / (int32_t)((int32_t)*TEMPSENSOR_CAL2_ADDR - (int32_t)*TEMPSENSOR_CAL1_ADDR) \
  ) + TEMPSENSOR_CAL1_TEMP                                                        \
 )                                                                                \
 :                                                                                \
 ((int32_t)LL_ADC_TEMPERATURE_CALC_ERROR)                                         \
)

/**
  * @}
  */

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup ADC_LL_Exported_Functions ADC Exported Functions
  * @{
  */

/** @defgroup ADC_LL_EF_DMA_Management ADC DMA management
  * @{
  */
/* Note: LL ADC functions to set DMA transfer are located into sections of    */
/*       configuration of ADC instance, groups and multimode (if available):  */
/*       @ref LL_ADC_REG_SetDMATransfer(), ...                                */

/**
  * @brief  Function to help to configure DMA transfer from ADC: retrieve the
  *         ADC register address from ADC instance and a list of ADC registers
  *         intended to be used (most commonly) with DMA transfer.
  * @note   These ADC registers are data registers:
  *         when ADC conversion data is available in ADC data registers,
  *         ADC generates a DMA transfer request.
  * @param  ADCx ADC instance
  *
  *         (1) Available on devices with several ADC instances.
  * @retval ADC register address
  */
__STATIC_INLINE uint32_t LL_ADC_DMA_GetRegAddr(const ADC_TypeDef *ADCx)
{

  /* Retrieve address of register DR */
  return (uint32_t) &(ADCx->DR);
}


/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_ADC_Common Configuration of ADC hierarchical scope: common to several
  *           ADC instances
  * @{
  */

/**
  * @brief  Set parameter common to several ADC: Clock source and prescaler.
  * @note   On this chip series, if ADC group injected is used, some
  *         clock ratio constraints between ADC clock and AHB clock
  *         must be respected.
  *         Refer to reference manual.
  * @note   On this chip series, setting of this feature is conditioned to
  *         ADC state:
  *         All ADC instances of the ADC common group must be disabled.
  *         This check can be done with function @ref LL_ADC_IsEnabled() for each
  *         ADC instance or by using helper macro helper macro
  *         @ref __LL_ADC_IS_ENABLED_ALL_COMMON_INSTANCE().
  * @rmtoll CCR      CKMODE         LL_ADC_SetCommonClock\n
  *         CCR      PRESC          LL_ADC_SetCommonClock
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @param  CommonClock This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CLOCK_SYNC_PCLK_DIV1
  *         @arg @ref LL_ADC_CLOCK_SYNC_PCLK_DIV2
  *         @arg @ref LL_ADC_CLOCK_SYNC_PCLK_DIV4
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV1
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV2
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV4
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV6
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV8
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV10
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV12
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV16
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV32
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV64
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV128
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV256
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCommonClock(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t CommonClock)
{
  MODIFY_REG(ADCxy_COMMON->CCR, ADC_CCR_CKMODE | ADC_CCR_PRESC, CommonClock);
}

/**
  * @brief  Get parameter common to several ADC: Clock source and prescaler.
  * @rmtoll CCR      CKMODE         LL_ADC_GetCommonClock\n
  *         CCR      PRESC          LL_ADC_GetCommonClock
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CLOCK_SYNC_PCLK_DIV1
  *         @arg @ref LL_ADC_CLOCK_SYNC_PCLK_DIV2
  *         @arg @ref LL_ADC_CLOCK_SYNC_PCLK_DIV4
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV1
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV2
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV4
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV6
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV8
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV10
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV12
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV16
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV32
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV64
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV128
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV256
  */
__STATIC_INLINE uint32_t LL_ADC_GetCommonClock(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (uint32_t)(READ_BIT(ADCxy_COMMON->CCR, ADC_CCR_CKMODE | ADC_CCR_PRESC));
}

/**
  * @brief  Set parameter common to several ADC: measurement path to
  *         internal channels (VrefInt, temperature sensor, ...).
  *         Configure all paths (overwrite current configuration).
  * @note   One or several values can be selected.
  *         Example: (LL_ADC_PATH_INTERNAL_VREFINT |
  *                   LL_ADC_PATH_INTERNAL_TEMPSENSOR)
  *         The values not selected are removed from configuration.
  * @note   Stabilization time of measurement path to internal channel:
  *         After enabling internal paths, before starting ADC conversion,
  *         a delay is required for internal voltage reference and
  *         temperature sensor stabilization time.
  *         Refer to device datasheet.
  *         Refer to literal @ref LL_ADC_DELAY_VREFINT_STAB_US.
  *         Refer to literals @ref LL_ADC_DELAY_TEMPSENSOR_STAB_US,
  *         @ref LL_ADC_DELAY_TEMPSENSOR_BUFFER_STAB_US.
  * @note   ADC internal channel sampling time constraint:
  *         For ADC conversion of internal channels,
  *         a sampling time minimum value is required.
  *         Refer to device datasheet.
  * @rmtoll CCR      TSEN           LL_ADC_SetCommonPathInternalCh\n
  *         CCR      VREFINT_EN     LL_ADC_SetCommonPathInternalCh\n
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @param  PathInternal This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_PATH_INTERNAL_NONE
  *         @arg @ref LL_ADC_PATH_INTERNAL_VREFINT
  *         @arg @ref LL_ADC_PATH_INTERNAL_TEMPSENSOR
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCommonPathInternalCh(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t PathInternal)
{
  MODIFY_REG(ADCxy_COMMON->CCR, ADC_CCR_TSEN | ADC_CCR_VREFINT_EN, PathInternal);
}

/**
  * @brief  Set parameter common to several ADC: measurement path to
  *         internal channels (VrefInt, temperature sensor, ...).
  *         Add paths to the current configuration.
  * @note   One or several values can be selected.
  *         Example: (LL_ADC_PATH_INTERNAL_VREFINT |
  *                   LL_ADC_PATH_INTERNAL_TEMPSENSOR)
  * @note   Stabilization time of measurement path to internal channel:
  *         After enabling internal paths, before starting ADC conversion,
  *         a delay is required for internal voltage reference and
  *         temperature sensor stabilization time.
  *         Refer to device datasheet.
  *         Refer to literal @ref LL_ADC_DELAY_VREFINT_STAB_US.
  *         Refer to literals @ref LL_ADC_DELAY_TEMPSENSOR_STAB_US,
  *         @ref LL_ADC_DELAY_TEMPSENSOR_BUFFER_STAB_US.
  * @note   ADC internal channel sampling time constraint:
  *         For ADC conversion of internal channels,
  *         a sampling time minimum value is required.
  *         Refer to device datasheet.
  * @rmtoll CCR      TSEN          LL_ADC_SetCommonPathInternalChAdd\n
  *         CCR      VREFINT_EN    LL_ADC_SetCommonPathInternalChAdd\n
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @param  PathInternal This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_PATH_INTERNAL_NONE
  *         @arg @ref LL_ADC_PATH_INTERNAL_VREFINT
  *         @arg @ref LL_ADC_PATH_INTERNAL_TEMPSENSOR
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCommonPathInternalChAdd(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t PathInternal)
{
  SET_BIT(ADCxy_COMMON->CCR, PathInternal);
}

/**
  * @brief  Set parameter common to several ADC: measurement path to
  *         internal channels (VrefInt, temperature sensor, ...).
  *         Remove paths to the current configuration.
  * @note   One or several values can be selected.
  *         Example: (LL_ADC_PATH_INTERNAL_VREFINT |
  *                   LL_ADC_PATH_INTERNAL_TEMPSENSOR)
  * @rmtoll CCR      TSEN            LL_ADC_SetCommonPathInternalChRem\n
  *         CCR      VREFINT_EN      LL_ADC_SetCommonPathInternalChRem
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @param  PathInternal This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_PATH_INTERNAL_NONE
  *         @arg @ref LL_ADC_PATH_INTERNAL_VREFINT
  *         @arg @ref LL_ADC_PATH_INTERNAL_TEMPSENSOR
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCommonPathInternalChRem(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t PathInternal)
{
  CLEAR_BIT(ADCxy_COMMON->CCR, PathInternal);
}

/**
  * @brief  Get parameter common to several ADC: measurement path to internal
  *         channels (VrefInt, temperature sensor, ...).
  * @note   One or several values can be selected.
  *         Example: (LL_ADC_PATH_INTERNAL_VREFINT |
  *                   LL_ADC_PATH_INTERNAL_TEMPSENSOR)
  * @rmtoll CCR      TSEN            LL_ADC_GetCommonPathInternalCh\n
  *         CCR      VREFINT_EN      LL_ADC_GetCommonPathInternalCh
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval Returned value can be a combination of the following values:
  *         @arg @ref LL_ADC_PATH_INTERNAL_NONE
  *         @arg @ref LL_ADC_PATH_INTERNAL_VREFINT
  *         @arg @ref LL_ADC_PATH_INTERNAL_TEMPSENSOR
  */
__STATIC_INLINE uint32_t LL_ADC_GetCommonPathInternalCh(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (uint32_t)(READ_BIT(ADCxy_COMMON->CCR, ADC_CCR_TSEN | ADC_CCR_VREFINT_EN));
}

#if defined(ADC_CCR_VREFSEL)
/**
  * @brief  Enable VrefBuffer Output.
  * @rmtoll CCR      VREFSEL          LL_ADC_EnableVrefBuffVoltage
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableVrefBufferVoltage(ADC_Common_TypeDef *ADCxy_COMMON)
{
  SET_BIT(ADCxy_COMMON->CCR, ADC_CCR_VREFSEL);
}

/**
  * @brief  Disable VrefBuffer Output.
  * @rmtoll CCR      VREFSEL          LL_ADC_DisableVrefBufferVoltage
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableVrefBufferVoltage(ADC_Common_TypeDef *ADCxy_COMMON)
{
  CLEAR_BIT(ADCxy_COMMON->CCR, ADC_CCR_VREFSEL);
}

/**
  * @brief  Get state of VrefBuff Voltage output
  *         (0: output disabled, 1: output enabled).
  * @rmtoll CCR      VREFSEL          LL_ADC_IsEnabled_VrefBuffVoltage
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabled_VrefBufferVoltage(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (READ_BIT(ADCxy_COMMON->CCR, ADC_CCR_VREFSEL) == (ADC_CCR_VREFSEL));
}

#endif /* ADC_CCR_VREFSEL */

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_ADC_Instance Configuration of ADC hierarchical scope: ADC instance
  * @{
  */
/**
  * @brief  Set ADC resolution.
  *         Refer to reference manual for alignments formats
  *         dependencies to ADC resolutions.
  * @note   On this chip series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll CFGR     RES            LL_ADC_SetResolution
  * @param  ADCx ADC instance
  * @param  Resolution This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetResolution(ADC_TypeDef *ADCx, uint32_t Resolution)
{
  MODIFY_REG(ADCx->CFGR, ADC_CFGR_RES, Resolution);
}

/**
  * @brief  Get ADC resolution.
  *         Refer to reference manual for alignments formats
  *         dependencies to ADC resolutions.
  * @rmtoll CFGR     RES            LL_ADC_GetResolution
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  */
__STATIC_INLINE uint32_t LL_ADC_GetResolution(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR, ADC_CFGR_RES));
}

#if defined(ADC_CCR_VREFSEL)
/**
  * @brief  Select ADC Reference.
  * @rmtoll CCR      VREFSEL        LL_ADC_SetReference
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @param  Reference This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REFERENCE_VCCA
  *         @arg @ref LL_ADC_REFERENCE_VREFBUF
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetReference(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t Reference)
{
  MODIFY_REG(ADCxy_COMMON->CCR, ADC_CCR_VREFSEL, Reference);
}

/**
  * @brief  Get ADC Reference.
  * @rmtoll CCR      VREFSEL        LL_ADC_GetReference
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval  This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REFERENCE_VCCA
  *         @arg @ref LL_ADC_REFERENCE_VREFBUF
  */
__STATIC_INLINE uint32_t LL_ADC_GetReference(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (uint32_t)(READ_BIT(ADCxy_COMMON->CCR, ADC_CCR_VREFSEL));
}
#endif /* ADC_CCR_VREFSEL */

/**
  * @brief  Set ADC conversion data alignment.
  * @note   Refer to reference manual for alignments formats
  *         dependencies to ADC resolutions.
  * @note   On this chip series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll CFGR     ALIGN          LL_ADC_SetDataAlignment
  * @param  ADCx ADC instance
  * @param  DataAlignment This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DATA_ALIGN_RIGHT
  *         @arg @ref LL_ADC_DATA_ALIGN_LEFT
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetDataAlignment(ADC_TypeDef *ADCx, uint32_t DataAlignment)
{
  MODIFY_REG(ADCx->CFGR, ADC_CFGR_ALIGN, DataAlignment);
}

/**
  * @brief  Get ADC conversion data alignment.
  * @note   Refer to reference manual for alignments formats
  *         dependencies to ADC resolutions.
  * @rmtoll CFGR     ALIGN          LL_ADC_GetDataAlignment
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_DATA_ALIGN_RIGHT
  *         @arg @ref LL_ADC_DATA_ALIGN_LEFT
  */
__STATIC_INLINE uint32_t LL_ADC_GetDataAlignment(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR, ADC_CFGR_ALIGN));
}

/**
  * @brief  Set ADC low power mode.
  * @note   Description of ADC low power modes:
  *         - ADC low power mode "auto wait": Dynamic low power mode,
  *           ADC conversions occurrences are limited to the minimum necessary
  *           in order to reduce power consumption.
  *           New ADC conversion starts only when the previous
  *           unitary conversion data (for ADC group regular)
  *           or previous sequence conversions data (for ADC group injected)
  *           has been retrieved by user software.
  *           In the meantime, ADC remains idle: does not performs any
  *           other conversion.
  *           This mode allows to automatically adapt the ADC conversions
  *           triggers to the speed of the software that reads the data.
  *           Moreover, this avoids risk of overrun for low frequency
  *           applications.
  *           How to use this low power mode:
  *           - It is not recommended to use with interruption or DMA
  *             since these modes have to clear immediately the EOC flag
  *             (by CPU to free the IRQ pending event or by DMA).
  *             Auto wait will work but fort a very short time, discarding
  *             its intended benefit (except specific case of high load of CPU
  *             or DMA transfers which can justify usage of auto wait).
  *           - Do use with polling: 1. Start conversion,
  *             2. Later on, when conversion data is needed: poll for end of
  *             conversion  to ensure that conversion is completed and
  *             retrieve ADC conversion data. This will trig another
  *             ADC conversion start.
  * @note   With ADC low power mode "auto wait", the ADC conversion data read
  *         is corresponding to previous ADC conversion start, independently
  *         of delay during which ADC was idle.
  *         Therefore, the ADC conversion data may be outdated: does not
  *         correspond to the current voltage level on the selected
  *         ADC channel.
  * @note   On this chip series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll CFGR     AUTDLY         LL_ADC_SetLowPowerMode
  * @param  ADCx ADC instance
  * @param  LowPowerMode This parameter can be one of the following values:
  *         @arg @ref LL_ADC_LP_MODE_NONE
  *         @arg @ref LL_ADC_LP_AUTOWAIT
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetLowPowerMode(ADC_TypeDef *ADCx, uint32_t LowPowerMode)
{
  MODIFY_REG(ADCx->CFGR, ADC_CFGR_AUTDLY, LowPowerMode);
}

/**
  * @brief  Get ADC low power mode:
  * @note   Description of ADC low power modes:
  *         - ADC low power mode "auto wait": Dynamic low power mode,
  *           ADC conversions occurrences are limited to the minimum necessary
  *           in order to reduce power consumption.
  *           New ADC conversion starts only when the previous
  *           unitary conversion data (for ADC group regular)
  *           or previous sequence conversions data (for ADC group injected)
  *           has been retrieved by user software.
  *           In the meantime, ADC remains idle: does not performs any
  *           other conversion.
  *           This mode allows to automatically adapt the ADC conversions
  *           triggers to the speed of the software that reads the data.
  *           Moreover, this avoids risk of overrun for low frequency
  *           applications.
  *           How to use this low power mode:
  *           - It is not recommended to use with interruption or DMA
  *             since these modes have to clear immediately the EOC flag
  *             (by CPU to free the IRQ pending event or by DMA).
  *             Auto wait will work but fort a very short time, discarding
  *             its intended benefit (except specific case of high load of CPU
  *             or DMA transfers which can justify usage of auto wait).
  *           - Do use with polling: 1. Start conversion,
  *             2. Later on, when conversion data is needed: poll for end of
  *             conversion  to ensure that conversion is completed and
  *             retrieve ADC conversion data. This will trig another
  *             ADC conversion start.
  * @note   With ADC low power mode "auto wait", the ADC conversion data read
  *         is corresponding to previous ADC conversion start, independently
  *         of delay during which ADC was idle.
  *         Therefore, the ADC conversion data may be outdated: does not
  *         correspond to the current voltage level on the selected
  *         ADC channel.
  * @rmtoll CFGR     AUTDLY         LL_ADC_GetLowPowerMode
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_LP_MODE_NONE
  *         @arg @ref LL_ADC_LP_AUTOWAIT
  */
__STATIC_INLINE uint32_t LL_ADC_GetLowPowerMode(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR, ADC_CFGR_AUTDLY));
}


/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_ADC_Group_Regular Configuration of ADC hierarchical scope: group regular
  * @{
  */

/**
  * @brief  Set ADC group regular conversion trigger source:
  *         internal (SW start) or from external peripheral (timer event,
  *         external interrupt line).
  * @note   On this chip series, setting trigger source to external trigger
  *         also set trigger polarity to rising edge
  *         (default setting for compatibility with some ADC on other
  *         chip series having this setting set by HW default value).
  *         In case of need to modify trigger edge, use
  *         function @ref LL_ADC_REG_SetTriggerEdge().
  * @note   Availability of parameters of trigger sources from timer
  *         depends on timers availability on the selected device.
  * @note   On this chip series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @rmtoll CFGR     EXTSEL         LL_ADC_REG_SetTriggerSource\n
  *         CFGR     EXTEN          LL_ADC_REG_SetTriggerSource
  * @param  ADCx ADC instance
  * @param  TriggerSource This parameter can be a value of @ref ADC_LL_EC_REG_TRIGGER_SOURCE
  *             On this chip series, all ADCx are not available on all devices. Refer to device datasheet for
  *             more details.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetTriggerSource(ADC_TypeDef *ADCx, uint32_t TriggerSource)
{
  MODIFY_REG(ADCx->CFGR, ADC_CFGR_EXTEN | ADC_CFGR_EXTSEL, TriggerSource);
}

/**
  * @brief  Get ADC group regular conversion trigger source:
  *         internal (SW start) or from external peripheral (timer event,
  *         external interrupt line).
  * @note   To determine whether group regular trigger source is
  *         internal (SW start) or external, without detail
  *         of which peripheral is selected as external trigger,
  *         (equivalent to
  *         "if(LL_ADC_REG_GetTriggerSource(ADC1) == LL_ADC_REG_TRIG_SOFTWARE)")
  *         use function @ref LL_ADC_REG_IsTriggerSourceSWStart.
  * @note   Availability of parameters of trigger sources from timer
  *         depends on timers availability on the selected device.
  * @rmtoll CFGR     EXTSEL         LL_ADC_REG_GetTriggerSource\n
  *         CFGR     EXTEN          LL_ADC_REG_GetTriggerSource
  * @param  ADCx ADC instance
  * @retval Returned value can be a value of @ref ADC_LL_EC_REG_TRIGGER_SOURCE
  *             On this chip series, all ADCx are not available on all devices. Refer to device datasheet for
  *             more details.
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetTriggerSource(const ADC_TypeDef *ADCx)
{
  __IO uint32_t trigger_source = READ_BIT(ADCx->CFGR, ADC_CFGR_EXTSEL | ADC_CFGR_EXTEN);

  /* Value for shift of {0; 4; 8; 12} depending on value of bitfield          */
  /* corresponding to ADC_CFGR_EXTEN {0; 1; 2; 3}.                            */
  uint32_t shift_exten = ((trigger_source & ADC_CFGR_EXTEN) >> (ADC_REG_TRIG_EXTEN_BITOFFSET_POS - 2UL));

  /* Set bitfield corresponding to ADC_CFGR_EXTEN and ADC_CFGR_EXTSEL         */
  /* to match with triggers literals definition.                              */
  return ((trigger_source
           & (ADC_REG_TRIG_SOURCE_MASK >> shift_exten) & ADC_CFGR_EXTSEL)
          | ((ADC_REG_TRIG_EDGE_MASK >> shift_exten) & ADC_CFGR_EXTEN)
         );
}

/**
  * @brief  Get ADC group regular conversion trigger source internal (SW start)
  *         or external.
  * @note   In case of group regular trigger source set to external trigger,
  *         to determine which peripheral is selected as external trigger,
  *         use function @ref LL_ADC_REG_GetTriggerSource().
  * @rmtoll CFGR     EXTEN          LL_ADC_REG_IsTriggerSourceSWStart
  * @param  ADCx ADC instance
  * @retval Value "0" if trigger source external trigger
  *         Value "1" if trigger source SW start.
  */
__STATIC_INLINE uint32_t LL_ADC_REG_IsTriggerSourceSWStart(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CFGR, ADC_CFGR_EXTEN) == (LL_ADC_REG_TRIG_SOFTWARE & ADC_CFGR_EXTEN)) ? 1UL : 0UL);
}

/**
  * @brief  Set ADC group regular conversion trigger polarity.
  * @note   Applicable only for trigger source set to external trigger.
  * @note   On this series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @rmtoll CFGR     EXTEN          LL_ADC_REG_SetTriggerEdge
  * @param  ADCx ADC instance
  * @param  ExternalTriggerEdge This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_TRIG_EXT_RISING
  *         @arg @ref LL_ADC_REG_TRIG_EXT_FALLING
  *         @arg @ref LL_ADC_REG_TRIG_EXT_RISINGFALLING
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetTriggerEdge(ADC_TypeDef *ADCx, uint32_t ExternalTriggerEdge)
{
  MODIFY_REG(ADCx->CFGR, ADC_CFGR_EXTEN, ExternalTriggerEdge);
}

/**
  * @brief  Get ADC group regular conversion trigger polarity.
  * @note   Applicable only for trigger source set to external trigger.
  * @rmtoll CFGR     EXTEN          LL_ADC_REG_GetTriggerEdge
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_TRIG_EXT_RISING
  *         @arg @ref LL_ADC_REG_TRIG_EXT_FALLING
  *         @arg @ref LL_ADC_REG_TRIG_EXT_RISINGFALLING
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetTriggerEdge(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR, ADC_CFGR_EXTEN));
}

/**
  * @brief  Set ADC group regular sequencer length and scan direction.
  * @note   Description of ADC group regular sequencer features:
  *         - For devices with sequencer fully configurable
  *           (function "LL_ADC_REG_SetSequencerRanks()" available):
  *           sequencer length and each rank affectation to a channel
  *           are configurable.
  *           This function performs configuration of:
  *           - Sequence length: Number of ranks in the scan sequence.
  *           - Sequence direction: Unless specified in parameters, sequencer
  *             scan direction is forward (from rank 1 to rank n).
  *           Sequencer ranks are selected using
  *           function "LL_ADC_REG_SetSequencerRanks()".
  *         - For devices with sequencer not fully configurable
  *           (function "LL_ADC_REG_SetSequencerChannels()" available):
  *           sequencer length and each rank affectation to a channel
  *           are defined by channel number.
  *           This function performs configuration of:
  *           - Sequence length: Number of ranks in the scan sequence is
  *             defined by number of channels set in the sequence,
  *             rank of each channel is fixed by channel HW number.
  *             (channel 0 fixed on rank 0, channel 1 fixed on rank1, ...).
  *           - Sequence direction: Unless specified in parameters, sequencer
  *             scan direction is forward (from lowest channel number to
  *             highest channel number).
  *           Sequencer ranks are selected using
  *           function "LL_ADC_REG_SetSequencerChannels()".
  * @note   Sequencer disabled is equivalent to sequencer of 1 rank:
  *         ADC conversion on only 1 channel.
  * @note   On this chip series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @rmtoll SQR1     L              LL_ADC_REG_SetSequencerLength
  * @param  ADCx ADC instance
  * @param  SequencerNbRanks This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_DISABLE
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_3RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_4RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_5RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_6RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_7RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_8RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_9RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_10RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_11RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_12RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_13RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_14RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_15RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_16RANKS
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetSequencerLength(ADC_TypeDef *ADCx, uint32_t SequencerNbRanks)
{
  MODIFY_REG(ADCx->SQR1, ADC_SQR1_L, SequencerNbRanks);
}

/**
  * @brief  Get ADC group regular sequencer length and scan direction.
  * @note   Description of ADC group regular sequencer features:
  *         - For devices with sequencer fully configurable
  *           (function "LL_ADC_REG_SetSequencerRanks()" available):
  *           sequencer length and each rank affectation to a channel
  *           are configurable.
  *           This function retrieves:
  *           - Sequence length: Number of ranks in the scan sequence.
  *           - Sequence direction: Unless specified in parameters, sequencer
  *             scan direction is forward (from rank 1 to rank n).
  *           Sequencer ranks are selected using
  *           function "LL_ADC_REG_SetSequencerRanks()".
  *         - For devices with sequencer not fully configurable
  *           (function "LL_ADC_REG_SetSequencerChannels()" available):
  *           sequencer length and each rank affectation to a channel
  *           are defined by channel number.
  *           This function retrieves:
  *           - Sequence length: Number of ranks in the scan sequence is
  *             defined by number of channels set in the sequence,
  *             rank of each channel is fixed by channel HW number.
  *             (channel 0 fixed on rank 0, channel 1 fixed on rank1, ...).
  *           - Sequence direction: Unless specified in parameters, sequencer
  *             scan direction is forward (from lowest channel number to
  *             highest channel number).
  *           Sequencer ranks are selected using
  *           function "LL_ADC_REG_SetSequencerChannels()".
  * @note   Sequencer disabled is equivalent to sequencer of 1 rank:
  *         ADC conversion on only 1 channel.
  * @rmtoll SQR1     L              LL_ADC_REG_GetSequencerLength
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_DISABLE
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_3RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_4RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_5RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_6RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_7RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_8RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_9RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_10RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_11RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_12RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_13RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_14RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_15RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_16RANKS
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetSequencerLength(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->SQR1, ADC_SQR1_L));
}

/**
  * @brief  Set ADC group regular sequencer discontinuous mode:
  *         sequence subdivided and scan conversions interrupted every selected
  *         number of ranks.
  * @note   It is not possible to enable both ADC group regular
  *         continuous mode and sequencer discontinuous mode.
  * @note   It is not possible to enable both ADC auto-injected mode
  *         and ADC group regular sequencer discontinuous mode.
  * @note   On this chip series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @rmtoll CFGR     DISCEN         LL_ADC_REG_SetSequencerDiscont\n
  *         CFGR     DISCNUM        LL_ADC_REG_SetSequencerDiscont
  * @param  ADCx ADC instance
  * @param  SeqDiscont This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_DISABLE
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_1RANK
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_2RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_3RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_4RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_5RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_6RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_7RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_8RANKS
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetSequencerDiscont(ADC_TypeDef *ADCx, uint32_t SeqDiscont)
{
  MODIFY_REG(ADCx->CFGR, ADC_CFGR_DISCEN | ADC_CFGR_DISCNUM, SeqDiscont);
}

/**
  * @brief  Get ADC group regular sequencer discontinuous mode:
  *         sequence subdivided and scan conversions interrupted every selected
  *         number of ranks.
  * @rmtoll CFGR     DISCEN         LL_ADC_REG_GetSequencerDiscont\n
  *         CFGR     DISCNUM        LL_ADC_REG_GetSequencerDiscont
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_DISABLE
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_1RANK
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_2RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_3RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_4RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_5RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_6RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_7RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_8RANKS
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetSequencerDiscont(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR, ADC_CFGR_DISCEN | ADC_CFGR_DISCNUM));
}

/**
  * @brief  Set ADC group regular sequence: channel on the selected
  *         scan sequence rank.
  * @note   This function performs configuration of:
  *         - Channels ordering into each rank of scan sequence:
  *           whatever channel can be placed into whatever rank.
  * @note   On this chip series, ADC group regular sequencer is
  *         fully configurable: sequencer length and each rank
  *         affectation to a channel are configurable.
  *         Refer to description of function @ref LL_ADC_REG_SetSequencerLength().
  * @note   Depending on devices and packages, some channels may not be available.
  *         Refer to device datasheet for channels availability.
  * @note   On this chip series, to measure internal channels (VrefInt,
  *         TempSensor, ...), measurement paths to internal channels must be
  *         enabled separately.
  *         This can be done using function @ref LL_ADC_SetCommonPathInternalCh().
  * @note   On this chip series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @rmtoll SQR1     SQ1            LL_ADC_REG_SetSequencerRanks\n
  *         SQR1     SQ2            LL_ADC_REG_SetSequencerRanks\n
  *         SQR1     SQ3            LL_ADC_REG_SetSequencerRanks\n
  *         SQR1     SQ4            LL_ADC_REG_SetSequencerRanks\n
  *         SQR2     SQ5            LL_ADC_REG_SetSequencerRanks\n
  *         SQR2     SQ6            LL_ADC_REG_SetSequencerRanks\n
  *         SQR2     SQ7            LL_ADC_REG_SetSequencerRanks\n
  *         SQR2     SQ8            LL_ADC_REG_SetSequencerRanks\n
  *         SQR2     SQ9            LL_ADC_REG_SetSequencerRanks\n
  *         SQR3     SQ10           LL_ADC_REG_SetSequencerRanks\n
  *         SQR3     SQ11           LL_ADC_REG_SetSequencerRanks\n
  *         SQR3     SQ12           LL_ADC_REG_SetSequencerRanks\n
  *         SQR3     SQ13           LL_ADC_REG_SetSequencerRanks\n
  *         SQR3     SQ14           LL_ADC_REG_SetSequencerRanks\n
  *         SQR4     SQ15           LL_ADC_REG_SetSequencerRanks\n
  *         SQR4     SQ16           LL_ADC_REG_SetSequencerRanks
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_RANK_1
  *         @arg @ref LL_ADC_REG_RANK_2
  *         @arg @ref LL_ADC_REG_RANK_3
  *         @arg @ref LL_ADC_REG_RANK_4
  *         @arg @ref LL_ADC_REG_RANK_5
  *         @arg @ref LL_ADC_REG_RANK_6
  *         @arg @ref LL_ADC_REG_RANK_7
  *         @arg @ref LL_ADC_REG_RANK_8
  *         @arg @ref LL_ADC_REG_RANK_9
  *         @arg @ref LL_ADC_REG_RANK_10
  *         @arg @ref LL_ADC_REG_RANK_11
  *         @arg @ref LL_ADC_REG_RANK_12
  *         @arg @ref LL_ADC_REG_RANK_13
  *         @arg @ref LL_ADC_REG_RANK_14
  *         @arg @ref LL_ADC_REG_RANK_15
  *         @arg @ref LL_ADC_REG_RANK_16
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1                 
  *         @arg @ref LL_ADC_CHANNEL_2                 
  *         @arg @ref LL_ADC_CHANNEL_3                 
  *         @arg @ref LL_ADC_CHANNEL_4                 
  *         @arg @ref LL_ADC_CHANNEL_5                 
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR       
  *         @arg @ref LL_ADC_CHANNEL_VREFINT    
  *         @arg @ref LL_ADC_CHANNEL_1_3VCCA       
  *         @arg @ref LL_ADC_CHANNEL_OPA1                  
  *         @arg @ref LL_ADC_CHANNEL_OPA2            
  * @note   On this chip series, above parameter are not available on all ADC instances.\n
  *         On this chip series, all ADCx are not available on all devices. Refer to device datasheet
  *         for more details.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetSequencerRanks(ADC_TypeDef *ADCx, uint32_t Rank, uint32_t Channel)
{
  /* Set bits with content of parameter "Channel" with bits position          */
  /* in register and register position depending on parameter "Rank".         */
  /* Parameters "Rank" and "Channel" are used with masks because containing   */
  /* other bits reserved for other purpose.                                   */
  __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->SQR1,
                                             ((Rank & ADC_REG_SQRX_REGOFFSET_MASK) >> ADC_SQRX_REGOFFSET_POS));

  MODIFY_REG(*preg,
             ADC_CHANNEL_ID_NUMBER_MASK_POSBIT0 << (Rank & ADC_REG_RANK_ID_SQRX_MASK),
             ((Channel & ADC_CHANNEL_ID_NUMBER_MASK) >> ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS)
             << (Rank & ADC_REG_RANK_ID_SQRX_MASK));
}

/**
  * @brief  Get ADC group regular sequence: channel on the selected
  *         scan sequence rank.
  * @note   On this chip series, ADC group regular sequencer is
  *         fully configurable: sequencer length and each rank
  *         affectation to a channel are configurable.
  *         Refer to description of function @ref LL_ADC_REG_SetSequencerLength().
  * @note   Depending on devices and packages, some channels may not be available.
  *         Refer to device datasheet for channels availability.
  * @note   Usage of the returned channel number:
  *         - To reinject this channel into another function LL_ADC_xxx:
  *           the returned channel number is only partly formatted on definition
  *           of literals LL_ADC_CHANNEL_x. Therefore, it has to be compared
  *           with parts of literals LL_ADC_CHANNEL_x or using
  *           helper macro @ref __LL_ADC_CHANNEL_TO_DECIMAL_NB().
  *           Then the selected literal LL_ADC_CHANNEL_x can be used
  *           as parameter for another function.
  *         - To get the channel number in decimal format:
  *           process the returned value with the helper macro
  *           @ref __LL_ADC_CHANNEL_TO_DECIMAL_NB().
  * @rmtoll SQR1     SQ1            LL_ADC_REG_GetSequencerRanks\n
  *         SQR1     SQ2            LL_ADC_REG_GetSequencerRanks\n
  *         SQR1     SQ3            LL_ADC_REG_GetSequencerRanks\n
  *         SQR1     SQ4            LL_ADC_REG_GetSequencerRanks\n
  *         SQR2     SQ5            LL_ADC_REG_GetSequencerRanks\n
  *         SQR2     SQ6            LL_ADC_REG_GetSequencerRanks\n
  *         SQR2     SQ7            LL_ADC_REG_GetSequencerRanks\n
  *         SQR2     SQ8            LL_ADC_REG_GetSequencerRanks\n
  *         SQR2     SQ9            LL_ADC_REG_GetSequencerRanks\n
  *         SQR3     SQ10           LL_ADC_REG_GetSequencerRanks\n
  *         SQR3     SQ11           LL_ADC_REG_GetSequencerRanks\n
  *         SQR3     SQ12           LL_ADC_REG_GetSequencerRanks\n
  *         SQR3     SQ13           LL_ADC_REG_GetSequencerRanks\n
  *         SQR3     SQ14           LL_ADC_REG_GetSequencerRanks\n
  *         SQR4     SQ15           LL_ADC_REG_GetSequencerRanks\n
  *         SQR4     SQ16           LL_ADC_REG_GetSequencerRanks
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_RANK_1
  *         @arg @ref LL_ADC_REG_RANK_2
  *         @arg @ref LL_ADC_REG_RANK_3
  *         @arg @ref LL_ADC_REG_RANK_4
  *         @arg @ref LL_ADC_REG_RANK_5
  *         @arg @ref LL_ADC_REG_RANK_6
  *         @arg @ref LL_ADC_REG_RANK_7
  *         @arg @ref LL_ADC_REG_RANK_8
  *         @arg @ref LL_ADC_REG_RANK_9
  *         @arg @ref LL_ADC_REG_RANK_10
  *         @arg @ref LL_ADC_REG_RANK_11
  *         @arg @ref LL_ADC_REG_RANK_12
  *         @arg @ref LL_ADC_REG_RANK_13
  *         @arg @ref LL_ADC_REG_RANK_14
  *         @arg @ref LL_ADC_REG_RANK_15
  *         @arg @ref LL_ADC_REG_RANK_16
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1                 
  *         @arg @ref LL_ADC_CHANNEL_2                 
  *         @arg @ref LL_ADC_CHANNEL_3                 
  *         @arg @ref LL_ADC_CHANNEL_4                 
  *         @arg @ref LL_ADC_CHANNEL_5                 
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR       
  *         @arg @ref LL_ADC_CHANNEL_VREFINT    
  *         @arg @ref LL_ADC_CHANNEL_1_3VCCA       
  *         @arg @ref LL_ADC_CHANNEL_OPA1                  
  *         @arg @ref LL_ADC_CHANNEL_OPA2            
  * @note   On this chip series, above parameter are not available on all ADC instances.\n
  *         On this chip series, all ADCx are not available on all devices. Refer to device datasheet
  *         for more details.
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetSequencerRanks(const ADC_TypeDef *ADCx, uint32_t Rank)
{
  const __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->SQR1,
                                                   ((Rank & ADC_REG_SQRX_REGOFFSET_MASK) >> ADC_SQRX_REGOFFSET_POS));

  return (uint32_t)((READ_BIT(*preg,
                              ADC_CHANNEL_ID_NUMBER_MASK_POSBIT0 << (Rank & ADC_REG_RANK_ID_SQRX_MASK))
                     >> (Rank & ADC_REG_RANK_ID_SQRX_MASK)) << ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS
                   );
}

/**
  * @brief  Set ADC continuous conversion mode on ADC group regular.
  * @note   Description of ADC continuous conversion mode:
  *         - single mode: one conversion per trigger
  *         - continuous mode: after the first trigger, following
  *           conversions launched successively automatically.
  * @note   It is not possible to enable both ADC group regular
  *         continuous mode and sequencer discontinuous mode.
  * @note   On this chip series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @rmtoll CFGR     CONT           LL_ADC_REG_SetContinuousMode
  * @param  ADCx ADC instance
  * @param  Continuous This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_CONV_SINGLE
  *         @arg @ref LL_ADC_REG_CONV_CONTINUOUS
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetContinuousMode(ADC_TypeDef *ADCx, uint32_t Continuous)
{
  MODIFY_REG(ADCx->CFGR, ADC_CFGR_CONT, Continuous);
}

/**
  * @brief  Get ADC continuous conversion mode on ADC group regular.
  * @note   Description of ADC continuous conversion mode:
  *         - single mode: one conversion per trigger
  *         - continuous mode: after the first trigger, following
  *           conversions launched successively automatically.
  * @rmtoll CFGR     CONT           LL_ADC_REG_GetContinuousMode
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_CONV_SINGLE
  *         @arg @ref LL_ADC_REG_CONV_CONTINUOUS
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetContinuousMode(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR, ADC_CFGR_CONT));
}

/**
  * @brief  Set ADC group regular conversion data transfer: no transfer or
  *         transfer by DMA, and DMA requests mode.
  * @note   To configure DMA source address (peripheral address),
  *         use function @ref LL_ADC_DMA_GetRegAddr().
  * @note   On this chip series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll CFGR     DMAEN          LL_ADC_REG_SetDMATransfer
  *         CFGR     DMACFG         LL_ADC_REG_SetDMATransfer
  * @param  ADCx ADC instance
  * @param  DMATransfer This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_DMA_TRANSFER_NONE
  *         @arg @ref LL_ADC_REG_DMA_TRANSFER_LIMITED
  *         @arg @ref LL_ADC_REG_DMA_TRANSFER_UNLIMITED
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetDMATransfer(ADC_TypeDef *ADCx, uint32_t DMATransfer)
{
  MODIFY_REG(ADCx->CFGR, ADC_CFGR_DMAEN | ADC_CFGR_DMACFG, DMATransfer);
}

/**
  * @brief  Get ADC group regular conversion data transfer: no transfer or
  *         transfer by DMA, and DMA requests mode.
  * @note   To configure DMA source address (peripheral address),
  *         use function @ref LL_ADC_DMA_GetRegAddr().
  * @rmtoll CFGR     DMAEN          LL_ADC_REG_GetDMATransfer
  *         CFGR     DMACFG         LL_ADC_REG_GetDMATransfer
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_DMA_TRANSFER_NONE
  *         @arg @ref LL_ADC_REG_DMA_TRANSFER_LIMITED
  *         @arg @ref LL_ADC_REG_DMA_TRANSFER_UNLIMITED
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetDMATransfer(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR, ADC_CFGR_DMAEN | ADC_CFGR_DMACFG));
}

/**
  * @brief  Set ADC group regular behavior in case of overrun:
  *         data preserved or overwritten.
  * @note   Compatibility with devices without feature overrun:
  *         other devices without this feature have a behavior
  *         equivalent to data overwritten.
  *         The default setting of overrun is data preserved.
  *         Therefore, for compatibility with all devices, parameter
  *         overrun should be set to data overwritten.
  * @rmtoll CFGR     OVRMOD         LL_ADC_REG_SetOverrun
  * @param  ADCx ADC instance
  * @param  Overrun This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_OVR_DATA_PRESERVED
  *         @arg @ref LL_ADC_REG_OVR_DATA_OVERWRITTEN
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetOverrun(ADC_TypeDef *ADCx, uint32_t Overrun)
{
  MODIFY_REG(ADCx->CFGR, ADC_CFGR_OVRMOD, Overrun);
}

/**
  * @brief  Get ADC group regular behavior in case of overrun:
  *         data preserved or overwritten.
  * @rmtoll CFGR     OVRMOD         LL_ADC_REG_GetOverrun
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_OVR_DATA_PRESERVED
  *         @arg @ref LL_ADC_REG_OVR_DATA_OVERWRITTEN
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetOverrun(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR, ADC_CFGR_OVRMOD));
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_ADC_Group_Injected Configuration of ADC hierarchical scope: group injected
  * @{
  */

/**
  * @brief  Set ADC group injected conversion trigger source:
  *         internal (SW start) or from external peripheral (timer event,
  *         external interrupt line).
  * @note   On this chip series, setting trigger source to external trigger
  *         also set trigger polarity to rising edge
  *         (default setting for compatibility with some ADC on other
  *         chip series having this setting set by HW default value).
  *         In case of need to modify trigger edge, use
  *         function @ref LL_ADC_INJ_SetTriggerEdge().
  * @note   Availability of parameters of trigger sources from timer
  *         depends on timers availability on the selected device.
  * @note   On this chip series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must not be disabled. Can be enabled with or without conversion
  *         on going on either groups regular or injected.
  * @rmtoll JSQR     JEXTSEL        LL_ADC_INJ_SetTriggerSource\n
  *         JSQR     JEXTEN         LL_ADC_INJ_SetTriggerSource
  * @param  ADCx ADC instance
  * @param  TriggerSource This parameter can be a value of @ref ADC_LL_EC_INJ_TRIGGER_SOURCE.
  *             On this chip series, all ADCx are not available on all devices. Refer to device datasheet for
  *             more details.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_INJ_SetTriggerSource(ADC_TypeDef *ADCx, uint32_t TriggerSource)
{
  MODIFY_REG(ADCx->JSQR, ADC_JSQR_JEXTSEL | ADC_JSQR_JEXTEN, TriggerSource);
}

/**
  * @brief  Get ADC group injected conversion trigger source:
  *         internal (SW start) or from external peripheral (timer event,
  *         external interrupt line).
  * @note   To determine whether group injected trigger source is
  *         internal (SW start) or external, without detail
  *         of which peripheral is selected as external trigger,
  *         (equivalent to
  *         "if(LL_ADC_INJ_GetTriggerSource(ADC1) == LL_ADC_INJ_TRIG_SOFTWARE)")
  *         use function @ref LL_ADC_INJ_IsTriggerSourceSWStart.
  * @note   Availability of parameters of trigger sources from timer
  *         depends on timers availability on the selected device.
  * @rmtoll JSQR     JEXTSEL        LL_ADC_INJ_GetTriggerSource\n
  *         JSQR     JEXTEN         LL_ADC_INJ_GetTriggerSource
  * @param  ADCx ADC instance
  * @retval Returned value can be a value of @ref ADC_LL_EC_INJ_TRIGGER_SOURCE.
  *             On this chip series, all ADCx are not available on all devices. Refer to device datasheet for
  *             more details.
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetTriggerSource(const ADC_TypeDef *ADCx)
{
  __IO uint32_t trigger_source = READ_BIT(ADCx->JSQR, ADC_JSQR_JEXTSEL | ADC_JSQR_JEXTEN);

  /* Value for shift of {0; 4; 8; 12} depending on value of bitfield          */
  /* corresponding to ADC_JSQR_JEXTEN {0; 1; 2; 3}.                           */
  uint32_t shift_jexten = ((trigger_source & ADC_JSQR_JEXTEN) >> (ADC_INJ_TRIG_EXTEN_BITOFFSET_POS - 2UL));

  /* Set bitfield corresponding to ADC_JSQR_JEXTEN and ADC_JSQR_JEXTSEL       */
  /* to match with triggers literals definition.                              */
  return ((trigger_source
           & (ADC_INJ_TRIG_SOURCE_MASK >> shift_jexten) & ADC_JSQR_JEXTSEL)
          | ((ADC_INJ_TRIG_EDGE_MASK >> shift_jexten) & ADC_JSQR_JEXTEN)
         );
}

/**
  * @brief  Get ADC group injected conversion trigger source internal (SW start)
            or external
  * @note   In case of group injected trigger source set to external trigger,
  *         to determine which peripheral is selected as external trigger,
  *         use function @ref LL_ADC_INJ_GetTriggerSource.
  * @rmtoll JSQR     JEXTEN         LL_ADC_INJ_IsTriggerSourceSWStart
  * @param  ADCx ADC instance
  * @retval Value "0" if trigger source external trigger
  *         Value "1" if trigger source SW start.
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_IsTriggerSourceSWStart(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->JSQR, ADC_JSQR_JEXTEN) == (LL_ADC_INJ_TRIG_SOFTWARE & ADC_JSQR_JEXTEN)) ? 1UL : 0UL);
}

/**
  * @brief  Set ADC group injected conversion trigger polarity.
  *         Applicable only for trigger source set to external trigger.
  * @note   On this chip series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must not be disabled. Can be enabled with or without conversion
  *         on going on either groups regular or injected.
  * @rmtoll JSQR     JEXTEN         LL_ADC_INJ_SetTriggerEdge
  * @param  ADCx ADC instance
  * @param  ExternalTriggerEdge This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_RISING
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_FALLING
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_RISINGFALLING
  * @retval None
  */
__STATIC_INLINE void LL_ADC_INJ_SetTriggerEdge(ADC_TypeDef *ADCx, uint32_t ExternalTriggerEdge)
{
  MODIFY_REG(ADCx->JSQR, ADC_JSQR_JEXTEN, ExternalTriggerEdge);
}

/**
  * @brief  Get ADC group injected conversion trigger polarity.
  *         Applicable only for trigger source set to external trigger.
  * @rmtoll JSQR     JEXTEN         LL_ADC_INJ_GetTriggerEdge
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_RISING
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_FALLING
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_RISINGFALLING
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetTriggerEdge(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->JSQR, ADC_JSQR_JEXTEN));
}

/**
  * @brief  Set ADC group injected sequencer length and scan direction.
  * @note   This function performs configuration of:
  *         - Sequence length: Number of ranks in the scan sequence.
  *         - Sequence direction: Unless specified in parameters, sequencer
  *           scan direction is forward (from rank 1 to rank n).
  * @note   Sequencer disabled is equivalent to sequencer of 1 rank:
  *         ADC conversion on only 1 channel.
  * @note   On this chip series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must not be disabled. Can be enabled with or without conversion
  *         on going on either groups regular or injected.
  * @rmtoll JSQR     JL             LL_ADC_INJ_SetSequencerLength
  * @param  ADCx ADC instance
  * @param  SequencerNbRanks This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_DISABLE
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_2RANKS
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_3RANKS
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_4RANKS
  * @retval None
  */
__STATIC_INLINE void LL_ADC_INJ_SetSequencerLength(ADC_TypeDef *ADCx, uint32_t SequencerNbRanks)
{
  MODIFY_REG(ADCx->JSQR, ADC_JSQR_JL, SequencerNbRanks);
}

/**
  * @brief  Get ADC group injected sequencer length and scan direction.
  * @note   This function retrieves:
  *         - Sequence length: Number of ranks in the scan sequence.
  *         - Sequence direction: Unless specified in parameters, sequencer
  *           scan direction is forward (from rank 1 to rank n).
  * @note   Sequencer disabled is equivalent to sequencer of 1 rank:
  *         ADC conversion on only 1 channel.
  * @rmtoll JSQR     JL             LL_ADC_INJ_GetSequencerLength
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_DISABLE
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_2RANKS
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_3RANKS
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_4RANKS
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetSequencerLength(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->JSQR, ADC_JSQR_JL));
}

/**
  * @brief  Set ADC group injected sequencer discontinuous mode:
  *         sequence subdivided and scan conversions interrupted every selected
  *         number of ranks.
  * @note   It is not possible to enable both ADC group injected
  *         auto-injected mode and sequencer discontinuous mode.
  * @rmtoll CFGR     JDISCEN        LL_ADC_INJ_SetSequencerDiscont
  * @param  ADCx ADC instance
  * @param  SeqDiscont This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_SEQ_DISCONT_DISABLE
  *         @arg @ref LL_ADC_INJ_SEQ_DISCONT_1RANK
  * @retval None
  */
__STATIC_INLINE void LL_ADC_INJ_SetSequencerDiscont(ADC_TypeDef *ADCx, uint32_t SeqDiscont)
{
  MODIFY_REG(ADCx->CFGR, ADC_CFGR_JDISCEN, SeqDiscont);
}

/**
  * @brief  Get ADC group injected sequencer discontinuous mode:
  *         sequence subdivided and scan conversions interrupted every selected
  *         number of ranks.
  * @rmtoll CFGR     JDISCEN        LL_ADC_INJ_GetSequencerDiscont
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_INJ_SEQ_DISCONT_DISABLE
  *         @arg @ref LL_ADC_INJ_SEQ_DISCONT_1RANK
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetSequencerDiscont(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR, ADC_CFGR_JDISCEN));
}

/**
  * @brief  Set ADC group injected sequence: channel on the selected
  *         sequence rank.
  * @note   Depending on devices and packages, some channels may not be available.
  *         Refer to device datasheet for channels availability.
  * @note   On this chip series, to measure internal channels (VrefInt,
  *         TempSensor, ...), measurement paths to internal channels must be
  *         enabled separately.
  *         This can be done using function @ref LL_ADC_SetCommonPathInternalCh().
  * @note   Some fast channels are available: fast analog inputs
  *         coming from GPIO pads (ADC_IN1..5).
  * @note   On this chip series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must not be disabled. Can be enabled with or without conversion
  *         on going on either groups regular or injected.
  * @rmtoll JSQR     JSQ1           LL_ADC_INJ_SetSequencerRanks\n
  *         JSQR     JSQ2           LL_ADC_INJ_SetSequencerRanks\n
  *         JSQR     JSQ3           LL_ADC_INJ_SetSequencerRanks\n
  *         JSQR     JSQ4           LL_ADC_INJ_SetSequencerRanks
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1                 
  *         @arg @ref LL_ADC_CHANNEL_2                 
  *         @arg @ref LL_ADC_CHANNEL_3                 
  *         @arg @ref LL_ADC_CHANNEL_4                 
  *         @arg @ref LL_ADC_CHANNEL_5                 
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR       
  *         @arg @ref LL_ADC_CHANNEL_VREFINT    
  *         @arg @ref LL_ADC_CHANNEL_1_3VCCA       
  *         @arg @ref LL_ADC_CHANNEL_OPA1                  
  *         @arg @ref LL_ADC_CHANNEL_OPA2           
  * @note   On this chip series, above parameter are not available on all ADC instances.\n
  *         On this chip series, all ADCx are not available on all devices. Refer to device datasheet
  *         for more details.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_INJ_SetSequencerRanks(ADC_TypeDef *ADCx, uint32_t Rank, uint32_t Channel)
{
  /* Set bits with content of parameter "Channel" with bits position          */
  /* in register depending on parameter "Rank".                               */
  /* Parameters "Rank" and "Channel" are used with masks because containing   */
  /* other bits reserved for other purpose.                                   */
  MODIFY_REG(ADCx->JSQR,
             (ADC_CHANNEL_ID_NUMBER_MASK >> ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS)
             << (Rank & ADC_INJ_RANK_ID_JSQR_MASK),
             ((Channel & ADC_CHANNEL_ID_NUMBER_MASK) >> ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS)
             << (Rank & ADC_INJ_RANK_ID_JSQR_MASK));
}

/**
  * @brief  Get ADC group injected sequence: channel on the selected
  *         sequence rank.
  * @note   Depending on devices and packages, some channels may not be available.
  *         Refer to device datasheet for channels availability.
  * @note   Usage of the returned channel number:
  *         - To reinject this channel into another function LL_ADC_xxx:
  *           the returned channel number is only partly formatted on definition
  *           of literals LL_ADC_CHANNEL_x. Therefore, it has to be compared
  *           with parts of literals LL_ADC_CHANNEL_x or using
  *           helper macro @ref __LL_ADC_CHANNEL_TO_DECIMAL_NB().
  *           Then the selected literal LL_ADC_CHANNEL_x can be used
  *           as parameter for another function.
  *         - To get the channel number in decimal format:
  *           process the returned value with the helper macro
  *           @ref __LL_ADC_CHANNEL_TO_DECIMAL_NB().
  * @rmtoll JSQR     JSQ1           LL_ADC_INJ_GetSequencerRanks\n
  *         JSQR     JSQ2           LL_ADC_INJ_GetSequencerRanks\n
  *         JSQR     JSQ3           LL_ADC_INJ_GetSequencerRanks\n
  *         JSQR     JSQ4           LL_ADC_INJ_GetSequencerRanks
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1                 
  *         @arg @ref LL_ADC_CHANNEL_2                 
  *         @arg @ref LL_ADC_CHANNEL_3                 
  *         @arg @ref LL_ADC_CHANNEL_4                 
  *         @arg @ref LL_ADC_CHANNEL_5                 
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR       
  *         @arg @ref LL_ADC_CHANNEL_VREFINT    
  *         @arg @ref LL_ADC_CHANNEL_1_3VCCA       
  *         @arg @ref LL_ADC_CHANNEL_OPA1                  
  *         @arg @ref LL_ADC_CHANNEL_OPA2           
  * @note   On this chip series, above parameter are not available on all ADC instances.\n
  *         On this chip series, all ADCx are not available on all devices. Refer to device datasheet
  *         for more details.
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetSequencerRanks(const ADC_TypeDef *ADCx, uint32_t Rank)
{
  return (uint32_t)((READ_BIT(ADCx->JSQR,
                              (ADC_CHANNEL_ID_NUMBER_MASK >> ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS)
                              << (Rank & ADC_INJ_RANK_ID_JSQR_MASK))
                     >> (Rank & ADC_INJ_RANK_ID_JSQR_MASK)) << ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS
                   );
}

/**
  * @brief  Set ADC group injected conversion trigger:
  *         independent or from ADC group regular.
  * @note   This mode can be used to extend number of data registers
  *         updated after one ADC conversion trigger and with data
  *         permanently kept (not erased by successive conversions of scan of
  *         ADC sequencer ranks), up to 5 data registers:
  *         1 data register on ADC group regular, 4 data registers
  *         on ADC group injected.
  * @note   If ADC group injected injected trigger source is set to an
  *         external trigger, this feature must be must be set to
  *         independent trigger.
  *         ADC group injected automatic trigger is compliant only with
  *         group injected trigger source set to SW start, without any
  *         further action on  ADC group injected conversion start or stop:
  *         in this case, ADC group injected is controlled only
  *         from ADC group regular.
  * @note   It is not possible to enable both ADC group injected
  *         auto-injected mode and sequencer discontinuous mode.
  * @note   On this chip series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll CFGR     JAUTO          LL_ADC_INJ_SetTrigAuto
  * @param  ADCx ADC instance
  * @param  TrigAuto This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_TRIG_INDEPENDENT
  *         @arg @ref LL_ADC_INJ_TRIG_FROM_GRP_REGULAR
  * @retval None
  */
__STATIC_INLINE void LL_ADC_INJ_SetTrigAuto(ADC_TypeDef *ADCx, uint32_t TrigAuto)
{
  MODIFY_REG(ADCx->CFGR, ADC_CFGR_JAUTO, TrigAuto);
}

/**
  * @brief  Get ADC group injected conversion trigger:
  *         independent or from ADC group regular.
  * @rmtoll CFGR     JAUTO          LL_ADC_INJ_GetTrigAuto
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_INJ_TRIG_INDEPENDENT
  *         @arg @ref LL_ADC_INJ_TRIG_FROM_GRP_REGULAR
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetTrigAuto(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR, ADC_CFGR_JAUTO));
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_Channels Configuration of ADC hierarchical scope: channels
  * @{
  */

/**
  * @brief  Set sampling time of the selected ADC channel
  *         Unit: ADC clock cycles.
  * @note   On this device, sampling time is on channel scope: independently
  *         of channel mapped on ADC group regular or injected.
  * @note   In case of internal channel (VrefInt, TempSensor, ...) to be
  *         converted:
  *         sampling time constraints must be respected (sampling time can be
  *         adjusted in function of ADC clock frequency and sampling time
  *         setting).
  *         Refer to device datasheet for timings values (parameters TS_vrefint,
  *         TS_temp, ...).
  * @note   Conversion time is the addition of sampling time and processing time.
  *         On this chip series, ADC processing time is:
  *         - 12.5 ADC clock cycles at ADC resolution 12 bits
  *         - 10.5 ADC clock cycles at ADC resolution 10 bits
  *         - 8.5 ADC clock cycles at ADC resolution 8 bits
  *         - 6.5 ADC clock cycles at ADC resolution 6 bits
  * @note   In case of ADC conversion of internal channel (VrefInt,
  *         temperature sensor, ...), a sampling time minimum value
  *         is required.
  *         Refer to device datasheet.
  * @note   On this chip series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll SMPR1    SMP0           LL_ADC_SetChannelSamplingTime\n
  *         SMPR1    SMP1           LL_ADC_SetChannelSamplingTime\n
  *         SMPR1    SMP2           LL_ADC_SetChannelSamplingTime\n
  *         SMPR1    SMP3           LL_ADC_SetChannelSamplingTime\n
  *         SMPR1    SMP4           LL_ADC_SetChannelSamplingTime\n
  *         SMPR1    SMP5           LL_ADC_SetChannelSamplingTime\n
  *         SMPR1    SMP6           LL_ADC_SetChannelSamplingTime\n
  *         SMPR1    SMP7           LL_ADC_SetChannelSamplingTime\n
  *         SMPR1    SMP8           LL_ADC_SetChannelSamplingTime\n
  *         SMPR1    SMP9           LL_ADC_SetChannelSamplingTime\n
  *         SMPR2    SMP10          LL_ADC_SetChannelSamplingTime\n
  *         SMPR2    SMP11          LL_ADC_SetChannelSamplingTime\n
  *         SMPR2    SMP12          LL_ADC_SetChannelSamplingTime\n
  *         SMPR2    SMP13          LL_ADC_SetChannelSamplingTime\n
  *         SMPR2    SMP14          LL_ADC_SetChannelSamplingTime
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1                 
  *         @arg @ref LL_ADC_CHANNEL_2                 
  *         @arg @ref LL_ADC_CHANNEL_3                 
  *         @arg @ref LL_ADC_CHANNEL_4                 
  *         @arg @ref LL_ADC_CHANNEL_5                 
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR       
  *         @arg @ref LL_ADC_CHANNEL_VREFINT    
  *         @arg @ref LL_ADC_CHANNEL_1_3VCCA       
  *         @arg @ref LL_ADC_CHANNEL_OPA1                  
  *         @arg @ref LL_ADC_CHANNEL_OPA2           
  * @param  SamplingTime This parameter can be one of the following values:
  *         @arg @ref LL_ADC_SAMPLINGTIME_2CYCLES_5   
  *         @arg @ref LL_ADC_SAMPLINGTIME_6CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_12CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_24CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_47CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_92CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_247CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_640CYCLES_5
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetChannelSamplingTime(ADC_TypeDef *ADCx, uint32_t Channel, uint32_t SamplingTime)
{
  /* Set bits with content of parameter "SamplingTime" with bits position     */
  /* in register and register position depending on parameter "Channel".      */
  /* Parameter "Channel" is used with masks because containing                */
  /* other bits reserved for other purpose.                                   */
  __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->SMPR1,
                                             ((Channel & ADC_CHANNEL_SMPRX_REGOFFSET_MASK) >> ADC_SMPRX_REGOFFSET_POS));

  MODIFY_REG(*preg,
             ADC_SMPR1_SMP0 << ((Channel & ADC_CHANNEL_SMPx_BITOFFSET_MASK) >> ADC_CHANNEL_SMPx_BITOFFSET_POS),
             SamplingTime   << ((Channel & ADC_CHANNEL_SMPx_BITOFFSET_MASK) >> ADC_CHANNEL_SMPx_BITOFFSET_POS));
}

/**
  * @brief  Get sampling time of the selected ADC channel
  *         Unit: ADC clock cycles.
  * @note   On this device, sampling time is on channel scope: independently
  *         of channel mapped on ADC group regular or injected.
  * @note   Conversion time is the addition of sampling time and processing time.
  *         On this chip series, ADC processing time is:
  *         - 12.5 ADC clock cycles at ADC resolution 12 bits
  *         - 10.5 ADC clock cycles at ADC resolution 10 bits
  *         - 8.5 ADC clock cycles at ADC resolution 8 bits
  *         - 6.5 ADC clock cycles at ADC resolution 6 bits
  * @rmtoll SMPR1    SMP0           LL_ADC_GetChannelSamplingTime\n
  *         SMPR1    SMP1           LL_ADC_GetChannelSamplingTime\n
  *         SMPR1    SMP2           LL_ADC_GetChannelSamplingTime\n
  *         SMPR1    SMP3           LL_ADC_GetChannelSamplingTime\n
  *         SMPR1    SMP4           LL_ADC_GetChannelSamplingTime\n
  *         SMPR1    SMP5           LL_ADC_GetChannelSamplingTime\n
  *         SMPR1    SMP6           LL_ADC_GetChannelSamplingTime\n
  *         SMPR1    SMP7           LL_ADC_GetChannelSamplingTime\n
  *         SMPR1    SMP8           LL_ADC_GetChannelSamplingTime\n
  *         SMPR1    SMP9           LL_ADC_GetChannelSamplingTime\n
  *         SMPR2    SMP10          LL_ADC_GetChannelSamplingTime\n
  *         SMPR2    SMP11          LL_ADC_GetChannelSamplingTime\n
  *         SMPR2    SMP12          LL_ADC_GetChannelSamplingTime\n
  *         SMPR2    SMP13          LL_ADC_GetChannelSamplingTime\n
  *         SMPR2    SMP14          LL_ADC_GetChannelSamplingTime
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1                 
  *         @arg @ref LL_ADC_CHANNEL_2                 
  *         @arg @ref LL_ADC_CHANNEL_3                 
  *         @arg @ref LL_ADC_CHANNEL_4                 
  *         @arg @ref LL_ADC_CHANNEL_5                 
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR       
  *         @arg @ref LL_ADC_CHANNEL_VREFINT    
  *         @arg @ref LL_ADC_CHANNEL_1_3VCCA       
  *         @arg @ref LL_ADC_CHANNEL_OPA1                  
  *         @arg @ref LL_ADC_CHANNEL_OPA2         
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_SAMPLINGTIME_2CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_6CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_12CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_24CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_47CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_92CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_247CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_640CYCLES_5
  *
  */
__STATIC_INLINE uint32_t LL_ADC_GetChannelSamplingTime(const ADC_TypeDef *ADCx, uint32_t Channel)
{
  const __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->SMPR1, ((Channel & ADC_CHANNEL_SMPRX_REGOFFSET_MASK)
                                                                 >> ADC_SMPRX_REGOFFSET_POS));

  return (uint32_t)(READ_BIT(*preg,
                             ADC_SMPR1_SMP0
                             << ((Channel & ADC_CHANNEL_SMPx_BITOFFSET_MASK) >> ADC_CHANNEL_SMPx_BITOFFSET_POS))
                    >> ((Channel & ADC_CHANNEL_SMPx_BITOFFSET_MASK) >> ADC_CHANNEL_SMPx_BITOFFSET_POS)
                   );
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_ADC_AnalogWatchdog Configuration of ADC transversal scope: analog watchdog
  * @{
  */

/**
  * @brief  Set ADC analog watchdog monitored channels:
  *         a single channel, multiple channels or all channels,
  *         on ADC groups regular and-or injected.
  * @note   Once monitored channels are selected, analog watchdog
  *         is enabled.
  * @note   In case of need to define a single channel to monitor
  *         with analog watchdog from sequencer channel definition,
  *         use helper macro @ref __LL_ADC_ANALOGWD_CHANNEL_GROUP().
  * @note   On this chip series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll CFGR     AWDCH         LL_ADC_SetAnalogWDMonitChannels\n
  *         CFGR     AWDSGL        LL_ADC_SetAnalogWDMonitChannels\n
  *         CFGR     AWDEN         LL_ADC_SetAnalogWDMonitChannels\n
  *         CFGR     JAWDEN        LL_ADC_SetAnalogWDMonitChannels
  * @param  ADCx ADC instance
  * @param  AWDChannelGroup This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_DISABLE
  *         @arg @ref LL_ADC_AWD_ALL_CHANNELS_REG        
  *         @arg @ref LL_ADC_AWD_ALL_CHANNELS_INJ        
  *         @arg @ref LL_ADC_AWD_ALL_CHANNELS_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_0_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_0_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_0_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_1_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_1_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_1_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_2_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_2_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_2_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_3_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_3_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_3_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_4_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_4_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_4_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_5_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_5_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_5_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_6_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_6_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_6_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_7_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_7_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_7_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_8_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_8_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_8_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_9_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_9_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_9_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_10_REG          
  *         @arg @ref LL_ADC_AWD_CHANNEL_10_INJ          
  *         @arg @ref LL_ADC_AWD_CHANNEL_10_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_11_REG          
  *         @arg @ref LL_ADC_AWD_CHANNEL_11_INJ          
  *         @arg @ref LL_ADC_AWD_CHANNEL_11_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_12_REG          
  *         @arg @ref LL_ADC_AWD_CHANNEL_12_INJ          
  *         @arg @ref LL_ADC_AWD_CHANNEL_12_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_13_REG          
  *         @arg @ref LL_ADC_AWD_CHANNEL_13_INJ          
  *         @arg @ref LL_ADC_AWD_CHANNEL_13_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_14_REG          
  *         @arg @ref LL_ADC_AWD_CHANNEL_14_INJ          
  *         @arg @ref LL_ADC_AWD_CHANNEL_14_REG_INJ
  *         @arg @ref LL_ADC_AWD_CH_TEMPSENSOR_REG          
  *         @arg @ref LL_ADC_AWD_CH_TEMPSENSOR_INJ          
  *         @arg @ref LL_ADC_AWD_CH_TEMPSENSOR_REG_INJ
  *         @arg @ref LL_ADC_AWD_CH_VREFINT_REG          
  *         @arg @ref LL_ADC_AWD_CH_VREFINT_INJ          
  *         @arg @ref LL_ADC_AWD_CH_VREFINT_REG_INJ
  *         @arg @ref LL_ADC_AWD_CH_1_3VCCA_REG             
  *         @arg @ref LL_ADC_AWD_CH_1_3VCCA_INJ             
  *         @arg @ref LL_ADC_AWD_CH_1_3VCCA_REG_INJ         
  *         @arg @ref LL_ADC_AWD_CH_OPA1_REG             
  *         @arg @ref LL_ADC_AWD_CH_OPA1_INJ             
  *         @arg @ref LL_ADC_AWD_CH_OPA1_REG_INJ         
  *         @arg @ref LL_ADC_AWD_CH_OPA2_REG             
  *         @arg @ref LL_ADC_AWD_CH_OPA2_INJ             
  *         @arg @ref LL_ADC_AWD_CH_OPA2_REG_INJ 
  *             On this chip series, all ADCx are not available on all devices. Refer to device datasheet
  *             for more details.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetAnalogWDMonitChannels(ADC_TypeDef *ADCx, uint32_t AWDChannelGroup)
{
  MODIFY_REG(ADCx->CFGR,
             (ADC_CFGR_AWDEN | ADC_CFGR_JAWDEN | ADC_CFGR_AWDSGL | ADC_CFGR_AWDCH),
             AWDChannelGroup);
}

/**
  * @brief  Get ADC analog watchdog monitored channel.
  * @note   Usage of the returned channel number:
  *         - To reinject this channel into another function LL_ADC_xxx:
  *           the returned channel number is only partly formatted on definition
  *           of literals LL_ADC_CHANNEL_x. Therefore, it has to be compared
  *           with parts of literals LL_ADC_CHANNEL_x or using
  *           helper macro @ref __LL_ADC_CHANNEL_TO_DECIMAL_NB().
  *           Then the selected literal LL_ADC_CHANNEL_x can be used
  *           as parameter for another function.
  *         - To get the channel number in decimal format:
  *           process the returned value with the helper macro
  *           @ref __LL_ADC_CHANNEL_TO_DECIMAL_NB().
  *           Applicable only when the analog watchdog is set to monitor
  *           one channel.
  * @note   On this chip series, there are 2 kinds of analog watchdog
  *         instance:
  *         - AWD standard (instance AWD1):
  *           - channels monitored: can monitor 1 channel or all channels.
  *           - groups monitored: ADC groups regular and-or injected.
  *           - resolution: resolution is not limited (corresponds to
  *             ADC resolution configured).
  * @note   On this chip series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll CFGR     AWDCH         LL_ADC_GetAnalogWDMonitChannels\n
  *         CFGR     AWDSGL        LL_ADC_GetAnalogWDMonitChannels\n
  *         CFGR     AWDEN         LL_ADC_GetAnalogWDMonitChannels\n
  *         CFGR     JAWDEN        LL_ADC_GetAnalogWDMonitChannels
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_AWD_DISABLE
  *         @arg @ref LL_ADC_AWD_ALL_CHANNELS_REG        
  *         @arg @ref LL_ADC_AWD_ALL_CHANNELS_INJ        
  *         @arg @ref LL_ADC_AWD_ALL_CHANNELS_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_0_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_0_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_0_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_1_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_1_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_1_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_2_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_2_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_2_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_3_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_3_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_3_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_4_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_4_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_4_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_5_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_5_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_5_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_6_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_6_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_6_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_7_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_7_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_7_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_8_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_8_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_8_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_9_REG           
  *         @arg @ref LL_ADC_AWD_CHANNEL_9_INJ           
  *         @arg @ref LL_ADC_AWD_CHANNEL_9_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_10_REG          
  *         @arg @ref LL_ADC_AWD_CHANNEL_10_INJ          
  *         @arg @ref LL_ADC_AWD_CHANNEL_10_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_11_REG          
  *         @arg @ref LL_ADC_AWD_CHANNEL_11_INJ          
  *         @arg @ref LL_ADC_AWD_CHANNEL_11_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_12_REG          
  *         @arg @ref LL_ADC_AWD_CHANNEL_12_INJ          
  *         @arg @ref LL_ADC_AWD_CHANNEL_12_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_13_REG          
  *         @arg @ref LL_ADC_AWD_CHANNEL_13_INJ          
  *         @arg @ref LL_ADC_AWD_CHANNEL_13_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_14_REG          
  *         @arg @ref LL_ADC_AWD_CHANNEL_14_INJ          
  *         @arg @ref LL_ADC_AWD_CHANNEL_14_REG_INJ
  *         @arg @ref LL_ADC_AWD_CH_TEMPSENSOR_REG          
  *         @arg @ref LL_ADC_AWD_CH_TEMPSENSOR_INJ          
  *         @arg @ref LL_ADC_AWD_CH_TEMPSENSOR_REG_INJ
  *         @arg @ref LL_ADC_AWD_CH_VREFINT_REG          
  *         @arg @ref LL_ADC_AWD_CH_VREFINT_INJ          
  *         @arg @ref LL_ADC_AWD_CH_VREFINT_REG_INJ
  *         @arg @ref LL_ADC_AWD_CH_1_3VCCA_REG             
  *         @arg @ref LL_ADC_AWD_CH_1_3VCCA_INJ             
  *         @arg @ref LL_ADC_AWD_CH_1_3VCCA_REG_INJ         
  *         @arg @ref LL_ADC_AWD_CH_OPA1_REG             
  *         @arg @ref LL_ADC_AWD_CH_OPA1_INJ             
  *         @arg @ref LL_ADC_AWD_CH_OPA1_REG_INJ         
  *         @arg @ref LL_ADC_AWD_CH_OPA2_REG             
  *         @arg @ref LL_ADC_AWD_CH_OPA2_INJ             
  *         @arg @ref LL_ADC_AWD_CH_OPA2_REG_INJ 
  *             On this chip series, all ADCx are not available on all devices. Refer to device datasheet
  *             for more details.
  */
__STATIC_INLINE uint32_t LL_ADC_GetAnalogWDMonitChannels(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR,
                    (ADC_CFGR_AWDEN | ADC_CFGR_JAWDEN | ADC_CFGR_AWDSGL | ADC_CFGR_AWDCH)));
}

/**
  * @brief  Set ADC analog watchdog thresholds value of both thresholds
  *         high and low.
  * @note   If value of only one threshold high or low must be set,
  *         use function @ref LL_ADC_SetAnalogWDThresholds().
  * @note   In case of ADC resolution different of 12 bits,
  *         analog watchdog thresholds data require a specific shift.
  *         Use helper macro @ref __LL_ADC_ANALOGWD_SET_THRESHOLD_RESOLUTION().
  * @note   If ADC oversampling is enabled, ADC analog watchdog thresholds are
  *         impacted: the comparison of analog watchdog thresholds is done on
  *         oversampling final computation (after ratio and shift application):
  *         ADC data register bitfield [15:4] (12 most significant bits).
  *         Examples:
  *         - Oversampling ratio and shift selected to have ADC conversion data
  *           on 12 bits (ratio 16 and shift 4, or ratio 32 and shift 5, ...):
  *           ADC analog watchdog thresholds must be divided by 16.
  *         - Oversampling ratio and shift selected to have ADC conversion data
  *           on 14 bits (ratio 16 and shift 2, or ratio 32 and shift 3, ...):
  *           ADC analog watchdog thresholds must be divided by 4.
  *         - Oversampling ratio and shift selected to have ADC conversion data
  *           on 16 bits (ratio 16 and shift none, or ratio 32 and shift 1, ...):
  *           ADC analog watchdog thresholds match directly to ADC data register.
  * @rmtoll TR      HT            LL_ADC_ConfigAnalogWDThresholds
  *         TR      LT            LL_ADC_ConfigAnalogWDThresholds
  * @param  ADCx ADC instance
  * @param  AWDThresholdHighValue Value between Min_Data=0x000 and Max_Data=0xFFF
  * @param  AWDThresholdLowValue Value between Min_Data=0x000 and Max_Data=0xFFF
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ConfigAnalogWDThresholds(ADC_TypeDef *ADCx, uint32_t AWDThresholdHighValue,
                                                     uint32_t AWDThresholdLowValue)
{
  MODIFY_REG(ADCx->TR,
             ADC_TR_HT | ADC_TR_LT,
             (AWDThresholdHighValue << ADC_TR_HT_BITOFFSET_POS) | AWDThresholdLowValue);
}

/**
  * @brief  Set ADC analog watchdog threshold value of threshold
  *         high or low.
  * @note   If values of both thresholds high or low must be set,
  *         use function @ref LL_ADC_ConfigAnalogWDThresholds().
  * @note   In case of ADC resolution different of 12 bits,
  *         analog watchdog thresholds data require a specific shift.
  *         Use helper macro @ref __LL_ADC_ANALOGWD_SET_THRESHOLD_RESOLUTION().
  * @note   If ADC oversampling is enabled, ADC analog watchdog thresholds are
  *         impacted: the comparison of analog watchdog thresholds is done on
  *         oversampling final computation (after ratio and shift application):
  *         ADC data register bitfield [15:4] (12 most significant bits).
  *         Examples:
  *         - Oversampling ratio and shift selected to have ADC conversion data
  *           on 12 bits (ratio 16 and shift 4, or ratio 32 and shift 5, ...):
  *           ADC analog watchdog thresholds must be divided by 16.
  *         - Oversampling ratio and shift selected to have ADC conversion data
  *           on 14 bits (ratio 16 and shift 2, or ratio 32 and shift 3, ...):
  *           ADC analog watchdog thresholds must be divided by 4.
  *         - Oversampling ratio and shift selected to have ADC conversion data
  *           on 16 bits (ratio 16 and shift none, or ratio 32 and shift 1, ...):
  *           ADC analog watchdog thresholds match directly to ADC data register.
  * @note   On this chip series, setting of this feature is not conditioned to
  *         ADC state:
  *         ADC can be disabled, enabled with or without conversion on going
  *         on either ADC groups regular or injected.
  * @rmtoll TR      HT            LL_ADC_SetAnalogWDThresholds
  *         TR      LT            LL_ADC_SetAnalogWDThresholds
  * @param  ADCx ADC instance
  * @param  AWDThresholdsHighLow This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_THRESHOLD_HIGH
  *         @arg @ref LL_ADC_AWD_THRESHOLD_LOW
  * @param  AWDThresholdValue Value between Min_Data=0x000 and Max_Data=0xFFF
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetAnalogWDThresholds(ADC_TypeDef *ADCx, uint32_t AWDThresholdsHighLow,
                                                  uint32_t AWDThresholdValue)
{
  MODIFY_REG(ADCx->TR,
             AWDThresholdsHighLow,
             AWDThresholdValue << ((AWDThresholdsHighLow & ADC_AWD_TRX_BIT_HIGH_MASK) >> ADC_AWD_TRX_BIT_HIGH_SHIFT4));
}

/**
  * @brief  Get ADC analog watchdog threshold value of threshold high,
  *         threshold low or raw data with ADC thresholds high and low
  *         concatenated.
  * @note   If raw data with ADC thresholds high and low is retrieved,
  *         the data of each threshold high or low can be isolated
  *         using helper macro:
  *         @ref __LL_ADC_ANALOGWD_THRESHOLDS_HIGH_LOW().
  * @note   In case of ADC resolution different of 12 bits,
  *         analog watchdog thresholds data require a specific shift.
  *         Use helper macro @ref __LL_ADC_ANALOGWD_GET_THRESHOLD_RESOLUTION().
  * @rmtoll TR      HT            LL_ADC_GetAnalogWDThresholds\n
  *         TR      LT            LL_ADC_GetAnalogWDThresholds
  * @param  ADCx ADC instance
  * @param  AWDThresholdsHighLow This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_THRESHOLD_HIGH
  *         @arg @ref LL_ADC_AWD_THRESHOLD_LOW
  *         @arg @ref LL_ADC_AWD_THRESHOLDS_HIGH_LOW
  * @retval Value between Min_Data=0x000 and Max_Data=0xFFF
  */
__STATIC_INLINE uint32_t LL_ADC_GetAnalogWDThresholds(const ADC_TypeDef *ADCx,
                                                      uint32_t AWDThresholdsHighLow)
{
  return (uint32_t)(READ_BIT(ADCx->TR,
                             (AWDThresholdsHighLow | ADC_TR_LT))
                    >> (((AWDThresholdsHighLow & ADC_AWD_TRX_BIT_HIGH_MASK) >> ADC_AWD_TRX_BIT_HIGH_SHIFT4)
                        & ~(AWDThresholdsHighLow & ADC_TR_LT)));
}

/**
  * @brief  Set ADC analog watchdog filtering configuration
  * @rmtoll TR     AWDFILT        LL_ADC_SetAWDFilteringConfiguration
  * @param  ADCx ADC instance
  * @param  AWDy This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD1
  * @param  FilteringConfig This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_FILTERING_NONE
  *         @arg @ref LL_ADC_AWD_FILTERING_2SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_3SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_4SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_5SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_6SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_7SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_8SAMPLES
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetAWDFilteringConfiguration(ADC_TypeDef *ADCx, uint32_t AWDy, uint32_t FilteringConfig)
{
  /* Prevent unused argument(s) compilation warning */
  (void)(AWDy);
  MODIFY_REG(ADCx->TR, ADC_TR_AWDFILT, FilteringConfig);
}

/**
  * @brief  Get ADC analog watchdog filtering configuration
  * @rmtoll TR1      AWDFILT        LL_ADC_GetAWDFilteringConfiguration
  * @param  ADCx ADC instance
  * @param  AWDy This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD1
  * @retval Returned value can be:
  *         @arg @ref LL_ADC_AWD_FILTERING_NONE
  *         @arg @ref LL_ADC_AWD_FILTERING_2SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_3SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_4SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_5SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_6SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_7SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_8SAMPLES
  */
__STATIC_INLINE uint32_t LL_ADC_GetAWDFilteringConfiguration(const ADC_TypeDef *ADCx, uint32_t AWDy)
{
  /* Prevent unused argument(s) compilation warning */
  (void)(AWDy);
  return (uint32_t)(READ_BIT(ADCx->TR, ADC_TR_AWDFILT));
}



/**
  * @}
  */
/** @defgroup ADC_LL_EF_Operation_ADC_Instance Operation on ADC hierarchical scope: ADC instance
  * @{
  */

/**
  * @brief  Enable the selected ADC instance.
  * @note   On this chip series, after ADC enable, a delay for
  *         ADC internal analog stabilization is required before performing a
  *         ADC conversion start.
  *         Refer to device datasheet, parameter tSTAB.
  * @note   On this chip series, flag LL_ADC_FLAG_ADRDY is raised when the ADC
  *         is enabled and when conversion clock is active.
  *         (not only core clock: this ADC has a dual clock domain)
  * @note   On this chip series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be ADC disabled and ADC internal voltage regulator enabled.
  * @rmtoll CR       ADEN           LL_ADC_Enable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_Enable(ADC_TypeDef *ADCx)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  MODIFY_REG(ADCx->CR,
             ADC_CR_BITS_PROPERTY_RS,
             ADC_CR_ADEN);
}

/**
  * @brief  Disable the selected ADC instance.
  * @note   On this chip series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be not disabled. Must be enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll CR       ADDIS          LL_ADC_Disable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_Disable(ADC_TypeDef *ADCx)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  MODIFY_REG(ADCx->CR,
             ADC_CR_BITS_PROPERTY_RS,
             ADC_CR_ADDIS);
}

/**
  * @brief  Get the selected ADC instance enable state.
  * @note   On this chip series, flag LL_ADC_FLAG_ADRDY is raised when the ADC
  *         is enabled and when conversion clock is active.
  *         (not only core clock: this ADC has a dual clock domain)
  * @rmtoll CR       ADEN           LL_ADC_IsEnabled
  * @param  ADCx ADC instance
  * @retval 0: ADC is disabled, 1: ADC is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabled(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CR, ADC_CR_ADEN) == (ADC_CR_ADEN)) ? 1UL : 0UL);
}

/**
  * @brief  Get the selected ADC instance disable state.
  * @rmtoll CR       ADDIS          LL_ADC_IsDisableOngoing
  * @param  ADCx ADC instance
  * @retval 0: no ADC disable command on going.
  */
__STATIC_INLINE uint32_t LL_ADC_IsDisableOngoing(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CR, ADC_CR_ADDIS) == (ADC_CR_ADDIS)) ? 1UL : 0UL);
}

/**
  * @brief  Start ADC calibration in the mode single-ended
  *         or differential (for devices with differential mode available).
  * @note   On this chip series, a minimum number of ADC clock cycles
  *         are required between ADC end of calibration and ADC enable.
  *         Refer to literal @ref LL_ADC_DELAY_CALIB_ENABLE_ADC_CYCLES.
  * @note   For devices with differential mode available:
  *         Calibration of offset is specific to each of
  *         single-ended and differential modes
  *         (calibration run must be performed for each of these
  *         differential modes, if used afterwards and if the application
  *         requires their calibration).
  * @note   On this chip series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be ADC disabled.
  * @rmtoll CR       ADCAL          LL_ADC_StartCalibration
  * @rmtoll CFGR2    CALNUM         LL_ADC_StartCalibration
  * @param  ADCx ADC instance
  * @param  CalNum This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CALIBRATION_NUMBER_1  
  *         @arg @ref LL_ADC_CALIBRATION_NUMBER_2  
  *         @arg @ref LL_ADC_CALIBRATION_NUMBER_4  
  *         @arg @ref LL_ADC_CALIBRATION_NUMBER_8  
  *         @arg @ref LL_ADC_CALIBRATION_NUMBER_16 
  *         @arg @ref LL_ADC_CALIBRATION_NUMBER_32 
  * @retval None
  */
__STATIC_INLINE void LL_ADC_StartCalibration(ADC_TypeDef *ADCx, uint32_t CalNum)
{
  MODIFY_REG(ADCx->CFGR2, ADC_CFGR2_CALNUM, CalNum);
  MODIFY_REG(ADCx->CR,
             ADC_CR_BITS_PROPERTY_RS,
             ADC_CR_ADCAL);
}

/**
  * @brief  Get ADC calibration state.
  * @rmtoll CR       ADCAL          LL_ADC_IsCalibrationOnGoing
  * @param  ADCx ADC instance
  * @retval 0: calibration complete, 1: calibration in progress.
  */
__STATIC_INLINE uint32_t LL_ADC_IsCalibrationOnGoing(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CR, ADC_CR_ADCAL) == (ADC_CR_ADCAL)) ? 1UL : 0UL);
}

/**
  * @brief  Reset ADC calibration value.
  * @rmtoll CR       RSTCAL          LL_ADC_ResetCalibration
  * @param  ADCx ADC instance
  */
__STATIC_INLINE void LL_ADC_ResetCalibration(ADC_TypeDef *ADCx)
{
  MODIFY_REG(ADCx->CR,
             ADC_CR_BITS_PROPERTY_RS,
             ADC_CR_RSTCAL);
}

/**
  * @brief  Get ADC reset calibration state.
  * @rmtoll CR       RSTCAL          LL_ADC_IsCalibrationOnGoing
  * @param  ADCx ADC instance
  * @retval 0: reset calibration complete, 1: reset calibration in progress.
  */
__STATIC_INLINE uint32_t LL_ADC_IsResetCalibrationOnGoing(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CR, ADC_CR_RSTCAL) == (ADC_CR_RSTCAL)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Operation_ADC_Group_Regular Operation on ADC hierarchical scope: group regular
  * @{
  */

/**
  * @brief  Start ADC group regular conversion.
  * @note   On this chip series, this function is relevant for both
  *         internal trigger (SW start) and external trigger:
  *         - If ADC trigger has been set to software start, ADC conversion
  *           starts immediately.
  *         - If ADC trigger has been set to external trigger, ADC conversion
  *           will start at next trigger event (on the selected trigger edge)
  *           following the ADC start conversion command.
  * @note   On this chip series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be enabled without conversion on going on group regular,
  *         without conversion stop command on going on group regular,
  *         without ADC disable command on going.
  * @rmtoll CR       ADSTART        LL_ADC_REG_StartConversion
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_StartConversion(ADC_TypeDef *ADCx)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  MODIFY_REG(ADCx->CR,
             ADC_CR_BITS_PROPERTY_RS,
             ADC_CR_ADSTART);
}

/**
  * @brief  Stop ADC group regular conversion.
  * @note   On this chip series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be enabled with conversion on going on group regular,
  *         without ADC disable command on going.
  * @rmtoll CR       ADSTP          LL_ADC_REG_StopConversion
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_StopConversion(ADC_TypeDef *ADCx)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  MODIFY_REG(ADCx->CR,
             ADC_CR_BITS_PROPERTY_RS,
             ADC_CR_ADSTP);
}

/**
  * @brief  Get ADC group regular conversion state.
  * @rmtoll CR       ADSTART        LL_ADC_REG_IsConversionOngoing
  * @param  ADCx ADC instance
  * @retval 0: no conversion is on going on ADC group regular.
  */
__STATIC_INLINE uint32_t LL_ADC_REG_IsConversionOngoing(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CR, ADC_CR_ADSTART) == (ADC_CR_ADSTART)) ? 1UL : 0UL);
}

/**
  * @brief  Get ADC group regular command of conversion stop state
  * @rmtoll CR       ADSTP          LL_ADC_REG_IsStopConversionOngoing
  * @param  ADCx ADC instance
  * @retval 0: no command of conversion stop is on going on ADC group regular.
  */
__STATIC_INLINE uint32_t LL_ADC_REG_IsStopConversionOngoing(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CR, ADC_CR_ADSTP) == (ADC_CR_ADSTP)) ? 1UL : 0UL);
}

/**
  * @brief  Get ADC group regular conversion data, range fit for
  *         ADC resolution 12 bits.
  * @rmtoll DR       RDATA          LL_ADC_REG_ReadConversionData12
  * @param  ADCx ADC instance
  * @retval Value between Min_Data=0x000 and Max_Data=0xFFF
  */
__STATIC_INLINE uint16_t LL_ADC_REG_ReadConversionData12(const ADC_TypeDef *ADCx)
{
  return (uint16_t)(READ_BIT(ADCx->DR, ADC_DR_RDATA));
}

/**
  * @brief  Get ADC group regular conversion data, range fit for
  *         ADC resolution 10 bits.
  * @rmtoll DR       RDATA          LL_ADC_REG_ReadConversionData10
  * @param  ADCx ADC instance
  * @retval Value between Min_Data=0x000 and Max_Data=0x3FF
  */
__STATIC_INLINE uint16_t LL_ADC_REG_ReadConversionData10(const ADC_TypeDef *ADCx)
{
  return (uint16_t)(READ_BIT(ADCx->DR, ADC_DR_RDATA));
}

/**
  * @brief  Get ADC group regular conversion data, range fit for
  *         ADC resolution 8 bits.
  * @rmtoll DR       RDATA          LL_ADC_REG_ReadConversionData8
  * @param  ADCx ADC instance
  * @retval Value between Min_Data=0x00 and Max_Data=0xFF
  */
__STATIC_INLINE uint8_t LL_ADC_REG_ReadConversionData8(const ADC_TypeDef *ADCx)
{
  return (uint8_t)(READ_BIT(ADCx->DR, ADC_DR_RDATA));
}

/**
  * @brief  Get ADC group regular conversion data, range fit for
  *         ADC resolution 6 bits.
  * @rmtoll DR       RDATA          LL_ADC_REG_ReadConversionData6
  * @param  ADCx ADC instance
  * @retval Value between Min_Data=0x00 and Max_Data=0x3F
  */
__STATIC_INLINE uint8_t LL_ADC_REG_ReadConversionData6(const ADC_TypeDef *ADCx)
{
  return (uint8_t)(READ_BIT(ADCx->DR, ADC_DR_RDATA));
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Operation_ADC_Group_Injected Operation on ADC hierarchical scope: group injected
  * @{
  */

/**
  * @brief  Start ADC group injected conversion.
  * @note   On this chip series, this function is relevant for both
  *         internal trigger (SW start) and external trigger:
  *         - If ADC trigger has been set to software start, ADC conversion
  *           starts immediately.
  *         - If ADC trigger has been set to external trigger, ADC conversion
  *           will start at next trigger event (on the selected trigger edge)
  *           following the ADC start conversion command.
  * @note   On this chip series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be enabled without conversion on going on group injected,
  *         without conversion stop command on going on group injected,
  *         without ADC disable command on going.
  * @rmtoll CR       JADSTART       LL_ADC_INJ_StartConversion
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_INJ_StartConversion(ADC_TypeDef *ADCx)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  MODIFY_REG(ADCx->CR,
             ADC_CR_BITS_PROPERTY_RS,
             ADC_CR_JADSTART);
}

/**
  * @brief  Stop ADC group injected conversion.
  * @note   On this chip series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be enabled with conversion on going on group injected,
  *         without ADC disable command on going.
  * @rmtoll CR       JADSTP          LL_ADC_INJ_StopConversion
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_INJ_StopConversion(ADC_TypeDef *ADCx)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  MODIFY_REG(ADCx->CR,
             ADC_CR_BITS_PROPERTY_RS,
             ADC_CR_JADSTP);
}

/**
  * @brief  Get ADC group injected conversion state.
  * @rmtoll CR       JADSTART       LL_ADC_INJ_IsConversionOngoing
  * @param  ADCx ADC instance
  * @retval 0: no conversion is on going on ADC group injected.
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_IsConversionOngoing(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CR, ADC_CR_JADSTART) == (ADC_CR_JADSTART)) ? 1UL : 0UL);
}

/**
  * @brief  Get ADC group injected command of conversion stop state
  * @rmtoll CR       JADSTP          LL_ADC_INJ_IsStopConversionOngoing
  * @param  ADCx ADC instance
  * @retval 0: no command of conversion stop is on going on ADC group injected.
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_IsStopConversionOngoing(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CR, ADC_CR_JADSTP) == (ADC_CR_JADSTP)) ? 1UL : 0UL);
}

/**
  * @brief  Get ADC group injected conversion data, range fit for
  *         all ADC configurations: all ADC resolutions and
  *         all oversampling increased data width (for devices
  *         with feature oversampling).
  * @rmtoll JDR1     JDATA          LL_ADC_INJ_ReadConversionData32\n
  *         JDR2     JDATA          LL_ADC_INJ_ReadConversionData32\n
  *         JDR3     JDATA          LL_ADC_INJ_ReadConversionData32\n
  *         JDR4     JDATA          LL_ADC_INJ_ReadConversionData32
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @retval Value between Min_Data=0x00000000 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_ReadConversionData32(const ADC_TypeDef *ADCx, uint32_t Rank)
{
  const __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->JDR1,
                                                   ((Rank & ADC_INJ_JDRX_REGOFFSET_MASK) >> ADC_JDRX_REGOFFSET_POS));

  return (uint32_t)(READ_BIT(*preg,
                             ADC_JDR1_JDATA)
                   );
}

/**
  * @brief  Get ADC group injected conversion data, range fit for
  *         ADC resolution 12 bits.
  * @note   For devices with feature oversampling: Oversampling
  *         can increase data width, function for extended range
  *         may be needed: @ref LL_ADC_INJ_ReadConversionData32.
  * @rmtoll JDR1     JDATA          LL_ADC_INJ_ReadConversionData12\n
  *         JDR2     JDATA          LL_ADC_INJ_ReadConversionData12\n
  *         JDR3     JDATA          LL_ADC_INJ_ReadConversionData12\n
  *         JDR4     JDATA          LL_ADC_INJ_ReadConversionData12
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @retval Value between Min_Data=0x000 and Max_Data=0xFFF
  */
__STATIC_INLINE uint16_t LL_ADC_INJ_ReadConversionData12(const ADC_TypeDef *ADCx, uint32_t Rank)
{
  const __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->JDR1,
                                                   ((Rank & ADC_INJ_JDRX_REGOFFSET_MASK) >> ADC_JDRX_REGOFFSET_POS));

  return (uint16_t)(READ_BIT(*preg,
                             ADC_JDR1_JDATA)
                   );
}

/**
  * @brief  Get ADC group injected conversion data, range fit for
  *         ADC resolution 10 bits.
  * @note   For devices with feature oversampling: Oversampling
  *         can increase data width, function for extended range
  *         may be needed: @ref LL_ADC_INJ_ReadConversionData32.
  * @rmtoll JDR1     JDATA          LL_ADC_INJ_ReadConversionData10\n
  *         JDR2     JDATA          LL_ADC_INJ_ReadConversionData10\n
  *         JDR3     JDATA          LL_ADC_INJ_ReadConversionData10\n
  *         JDR4     JDATA          LL_ADC_INJ_ReadConversionData10
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @retval Value between Min_Data=0x000 and Max_Data=0x3FF
  */
__STATIC_INLINE uint16_t LL_ADC_INJ_ReadConversionData10(const ADC_TypeDef *ADCx, uint32_t Rank)
{
  const __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->JDR1,
                                                   ((Rank & ADC_INJ_JDRX_REGOFFSET_MASK) >> ADC_JDRX_REGOFFSET_POS));

  return (uint16_t)(READ_BIT(*preg,
                             ADC_JDR1_JDATA)
                   );
}

/**
  * @brief  Get ADC group injected conversion data, range fit for
  *         ADC resolution 8 bits.
  * @note   For devices with feature oversampling: Oversampling
  *         can increase data width, function for extended range
  *         may be needed: @ref LL_ADC_INJ_ReadConversionData32.
  * @rmtoll JDR1     JDATA          LL_ADC_INJ_ReadConversionData8\n
  *         JDR2     JDATA          LL_ADC_INJ_ReadConversionData8\n
  *         JDR3     JDATA          LL_ADC_INJ_ReadConversionData8\n
  *         JDR4     JDATA          LL_ADC_INJ_ReadConversionData8
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @retval Value between Min_Data=0x00 and Max_Data=0xFF
  */
__STATIC_INLINE uint8_t LL_ADC_INJ_ReadConversionData8(const ADC_TypeDef *ADCx, uint32_t Rank)
{
  const __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->JDR1,
                                                   ((Rank & ADC_INJ_JDRX_REGOFFSET_MASK) >> ADC_JDRX_REGOFFSET_POS));

  return (uint8_t)(READ_BIT(*preg,
                            ADC_JDR1_JDATA)
                  );
}

/**
  * @brief  Get ADC group injected conversion data, range fit for
  *         ADC resolution 6 bits.
  * @note   For devices with feature oversampling: Oversampling
  *         can increase data width, function for extended range
  *         may be needed: @ref LL_ADC_INJ_ReadConversionData32.
  * @rmtoll JDR1     JDATA          LL_ADC_INJ_ReadConversionData6\n
  *         JDR2     JDATA          LL_ADC_INJ_ReadConversionData6\n
  *         JDR3     JDATA          LL_ADC_INJ_ReadConversionData6\n
  *         JDR4     JDATA          LL_ADC_INJ_ReadConversionData6
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @retval Value between Min_Data=0x00 and Max_Data=0x3F
  */
__STATIC_INLINE uint8_t LL_ADC_INJ_ReadConversionData6(const ADC_TypeDef *ADCx, uint32_t Rank)
{
  const __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->JDR1,
                                                   ((Rank & ADC_INJ_JDRX_REGOFFSET_MASK) >> ADC_JDRX_REGOFFSET_POS));

  return (uint8_t)(READ_BIT(*preg,
                            ADC_JDR1_JDATA)
                  );
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_FLAG_Management ADC flag management
  * @{
  */

/**
  * @brief  Get flag ADC ready.
  * @rmtoll ISR      ADRDY            LL_ADC_IsActiveFlag_ADRDY
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_ADRDY(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->ISR, LL_ADC_FLAG_ADRDY) == (LL_ADC_FLAG_ADRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC group regular end of unitary conversion.
  * @rmtoll ISR      EOC            LL_ADC_IsActiveFlag_EOC
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_EOC(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->ISR, ADC_ISR_EOC) == (ADC_ISR_EOC)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC group regular end of sequence conversions.
  * @rmtoll ISR      EOS            LL_ADC_IsActiveFlag_EOS
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_EOS(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->ISR, LL_ADC_FLAG_EOS) == (LL_ADC_FLAG_EOS)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC group regular overrun.
  * @rmtoll ISR      OVR            LL_ADC_IsActiveFlag_OVR
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_OVR(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->ISR, LL_ADC_FLAG_OVR) == (LL_ADC_FLAG_OVR)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC group regular end of sampling phase.
  * @rmtoll ISR      EOSMP          LL_ADC_IsActiveFlag_EOSMP
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_EOSMP(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->ISR, LL_ADC_FLAG_EOSMP) == (LL_ADC_FLAG_EOSMP)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC group injected end of unitary conversion.
  * @rmtoll ISR      JEOC           LL_ADC_IsActiveFlag_JEOC
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_JEOC(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->ISR, LL_ADC_FLAG_JEOC) == (LL_ADC_FLAG_JEOC)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC group injected end of sequence conversions.
  * @rmtoll ISR      JEOS           LL_ADC_IsActiveFlag_JEOS
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_JEOS(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->ISR, LL_ADC_FLAG_JEOS) == (LL_ADC_FLAG_JEOS)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC analog watchdog flag
  * @rmtoll ISR      AWD           LL_ADC_IsActiveFlag_AWD
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_AWD(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->ISR, LL_ADC_FLAG_AWD) == (LL_ADC_FLAG_AWD)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC end of calibration.
  * @rmtoll ISR      EOCAL          LL_ADC_IsActiveFlag_EOCAL
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_EOCAL(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->ISR, LL_ADC_FLAG_EOCAL) == (LL_ADC_FLAG_EOCAL)) ? 1UL : 0UL);
}

/**
  * @brief  Clear flag ADC ready.
  * @rmtoll ISR      ADRDY            LL_ADC_ClearFlag_ADRDY
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_ADRDY(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, LL_ADC_FLAG_ADRDY);
}

/**
  * @brief  Clear flag ADC group regular end of unitary conversion.
  * @rmtoll ISR      EOC            LL_ADC_ClearFlag_EOC
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_EOC(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, LL_ADC_FLAG_EOC);
}

/**
  * @brief  Clear flag ADC group regular end of sequence conversions.
  * @rmtoll ISR      EOS            LL_ADC_ClearFlag_EOS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_EOS(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, LL_ADC_FLAG_EOS);
}

/**
  * @brief  Clear flag ADC group regular overrun.
  * @rmtoll ISR      OVR            LL_ADC_ClearFlag_OVR
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_OVR(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, LL_ADC_FLAG_OVR);
}

/**
  * @brief  Clear flag ADC group regular end of sampling phase.
  * @rmtoll ISR      EOSMP          LL_ADC_ClearFlag_EOSMP
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_EOSMP(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, LL_ADC_FLAG_EOSMP);
}

/**
  * @brief  Clear flag ADC group injected end of unitary conversion.
  * @rmtoll ISR      JEOC           LL_ADC_ClearFlag_JEOC
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_JEOC(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, LL_ADC_FLAG_JEOC);
}

/**
  * @brief  Clear flag ADC group injected end of sequence conversions.
  * @rmtoll ISR      JEOS           LL_ADC_ClearFlag_JEOS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_JEOS(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, LL_ADC_FLAG_JEOS);
}

/**
  * @brief  Clear flag ADC analog watchdog.
  * @rmtoll ISR      AWD           LL_ADC_ClearFlag_AWD
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_AWD(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, LL_ADC_FLAG_AWD);
}

/**
  * @brief  Clear flag ADC end of calibration.
  * @rmtoll ISR      EOCAL         LL_ADC_ClearFlag_EOCAL
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_EOCAL(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, LL_ADC_FLAG_EOCAL);
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_IT_Management ADC IT management
  * @{
  */

/**
  * @brief  Enable interruption ADC ready.
  * @rmtoll IER      ADRDY          LL_ADC_EnableIT_ADRDY
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_ADRDY(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, LL_ADC_IT_ADRDY);
}

/**
  * @brief  Enable interruption ADC group regular end of unitary conversion.
  * @rmtoll IER      EOCIE          LL_ADC_EnableIT_EOC
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_EOC(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, LL_ADC_IT_EOC);
}

/**
  * @brief  Enable interruption ADC group regular end of sequence conversions.
  * @rmtoll IER      EOSIE          LL_ADC_EnableIT_EOS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_EOS(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, LL_ADC_IT_EOS);
}

/**
  * @brief  Enable ADC group regular interruption overrun.
  * @rmtoll IER      OVRIE          LL_ADC_EnableIT_OVR
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_OVR(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, LL_ADC_IT_OVR);
}

/**
  * @brief  Enable interruption ADC group regular end of sampling.
  * @rmtoll IER      EOSMPIE        LL_ADC_EnableIT_EOSMP
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_EOSMP(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, LL_ADC_IT_EOSMP);
}

/**
  * @brief  Enable interruption ADC group injected end of unitary conversion.
  * @rmtoll IER      JEOCIE         LL_ADC_EnableIT_JEOC
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_JEOC(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, LL_ADC_IT_JEOC);
}

/**
  * @brief  Enable interruption ADC group injected end of sequence conversions.
  * @rmtoll IER      JEOSIE         LL_ADC_EnableIT_JEOS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_JEOS(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, LL_ADC_IT_JEOS);
}

/**
  * @brief  Enable interruption ADC analog watchdog.
  * @rmtoll IER      AWDIE         LL_ADC_EnableIT_AWD
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_AWD(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, LL_ADC_IT_AWD);
}

/**
  * @brief  Disable interruption ADC ready.
  * @rmtoll IER      ADRDY          LL_ADC_DisableIT_ADRDY
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_ADRDY(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, LL_ADC_IT_ADRDY);
}

/**
  * @brief  Disable interruption ADC group regular end of unitary conversion.
  * @rmtoll IER      EOCIE          LL_ADC_DisableIT_EOC
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_EOC(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, LL_ADC_IT_EOC);
}

/**
  * @brief  Disable interruption ADC group regular end of sequence conversions.
  * @rmtoll IER      EOSIE          LL_ADC_DisableIT_EOS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_EOS(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, LL_ADC_IT_EOS);
}

/**
  * @brief  Disable interruption ADC group regular overrun.
  * @rmtoll IER      OVRIE          LL_ADC_DisableIT_OVR
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_OVR(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, LL_ADC_IT_OVR);
}

/**
  * @brief  Disable interruption ADC group regular end of sampling.
  * @rmtoll IER      EOSMPIE        LL_ADC_DisableIT_EOSMP
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_EOSMP(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, LL_ADC_IT_EOSMP);
}

/**
  * @brief  Disable interruption ADC group regular end of unitary conversion.
  * @rmtoll IER      JEOCIE         LL_ADC_DisableIT_JEOC
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_JEOC(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, LL_ADC_IT_JEOC);
}

/**
  * @brief  Disable interruption ADC group injected end of sequence conversions.
  * @rmtoll IER      JEOSIE         LL_ADC_DisableIT_JEOS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_JEOS(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, LL_ADC_IT_JEOS);
}

/**
  * @brief  Disable interruption ADC analog watchdog 1.
  * @rmtoll IER      AWDIE         LL_ADC_DisableIT_AWD
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_AWD(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, LL_ADC_IT_AWD);
}

/**
  * @brief  Disable interruption end of calibration.
  * @rmtoll IER      EOCAL         LL_ADC_DisableIT_AWD
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_EOCAL(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, LL_ADC_IT_EOCAL);
}

/**
  * @brief  Get state of interruption ADC ready
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll IER      ADRDY          LL_ADC_IsEnabledIT_ADRDY
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_ADRDY(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IER, LL_ADC_IT_ADRDY) == (LL_ADC_IT_ADRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption ADC group regular end of unitary conversion
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll IER      EOCIE          LL_ADC_IsEnabledIT_EOC
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_EOC(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IER, LL_ADC_IT_EOC) == (LL_ADC_IT_EOC)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption ADC group regular end of sequence conversions
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll IER      EOSIE          LL_ADC_IsEnabledIT_EOS
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_EOS(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IER, LL_ADC_IT_EOS) == (LL_ADC_IT_EOS)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption ADC group regular overrun
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll IER      OVRIE          LL_ADC_IsEnabledIT_OVR
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_OVR(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IER, LL_ADC_IT_OVR) == (LL_ADC_IT_OVR)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption ADC group regular end of sampling
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll IER      EOSMPIE        LL_ADC_IsEnabledIT_EOSMP
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_EOSMP(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IER, LL_ADC_IT_EOSMP) == (LL_ADC_IT_EOSMP)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption ADC group injected end of unitary conversion
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll IER      JEOCIE         LL_ADC_IsEnabledIT_JEOC
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_JEOC(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IER, LL_ADC_IT_JEOC) == (LL_ADC_IT_JEOC)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption ADC group injected end of sequence conversions
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll IER      JEOSIE         LL_ADC_IsEnabledIT_JEOS
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_JEOS(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IER, LL_ADC_IT_JEOS) == (LL_ADC_IT_JEOS)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption ADC analog watchdog
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll IER      AWDIE         LL_ADC_IsEnabledIT_AWD
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_AWD(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IER, LL_ADC_IT_AWD) == (LL_ADC_IT_AWD)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption ADC end of calibration.
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll IER      EOCAL         LL_ADC_IsEnabledIT_EOCAL
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_EOCAL(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IER, LL_ADC_IT_EOCAL) == (LL_ADC_IT_EOCAL)) ? 1UL : 0UL);
}

/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup ADC_LL_EF_Init Initialization and de-initialization functions
  * @{
  */

/* Initialization of some features of ADC common parameters and multimode */
ErrorStatus LL_ADC_CommonDeInit(const ADC_Common_TypeDef *ADCxy_COMMON);
//ErrorStatus LL_ADC_CommonInit(ADC_Common_TypeDef *ADCxy_COMMON, const LL_ADC_CommonInitTypeDef *pADC_CommonInitStruct);
//void        LL_ADC_CommonStructInit(LL_ADC_CommonInitTypeDef *pADC_CommonInitStruct);

/* De-initialization of ADC instance, ADC group regular and ADC group injected */
/* (availability of ADC group injected depends on chip series) */
ErrorStatus LL_ADC_DeInit(ADC_TypeDef *ADCx);

/* Initialization of some features of ADC instance */
ErrorStatus LL_ADC_Init(ADC_TypeDef *ADCx, const LL_ADC_InitTypeDef *pADC_InitStruct);
void        LL_ADC_StructInit(LL_ADC_InitTypeDef *pADC_InitStruct);

/* Initialization of some features of ADC instance and ADC group regular */
ErrorStatus LL_ADC_REG_Init(ADC_TypeDef *ADCx, const LL_ADC_REG_InitTypeDef *pADC_RegInitStruct);
void        LL_ADC_REG_StructInit(LL_ADC_REG_InitTypeDef *pADC_RegInitStruct);

/* Initialization of some features of ADC instance and ADC group injected */
ErrorStatus LL_ADC_INJ_Init(ADC_TypeDef *ADCx, const LL_ADC_INJ_InitTypeDef *pADC_InjInitStruct);
void        LL_ADC_INJ_StructInit(LL_ADC_INJ_InitTypeDef *pADC_InjInitStruct);

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/**
  * @}
  */

/**
  * @}
  */

#endif /* ADC1 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* PY32F032_LL_ADC_H */
