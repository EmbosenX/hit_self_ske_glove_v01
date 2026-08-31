/*******************************************************************************
 * @file        adc_sample.h
 * @brief       Y0~Y34 IO输出控制 + AS模拟开关使能/通道选择 + PALM_RP_AD01 ADC采集驱动
 * @author      
 * @date        2026-07-21
 * @version     V1.0
 * @note        适配HC32F460PEHB-VFBGA100原理图，单路ADC轮询多路模拟开关采集
 ******************************************************************************/
#ifndef __ADC_SAMPLE_H__
#define __ADC_SAMPLE_H__

#include "gpio.h"
#include "adc.h"
#include "app_tac_config.h"

#define Y0_PORT			GPIOB
#define Y0_PIN			GPIO_PIN_4
#define Y1_PORT			GPIOB
#define Y1_PIN			GPIO_PIN_5
#define Y2_PORT			GPIOB
#define Y2_PIN			GPIO_PIN_7
#define Y3_PORT			GPIOA
#define Y3_PIN			GPIO_PIN_0
#define Y4_PORT			GPIOA
#define Y4_PIN			GPIO_PIN_1
#define Y5_PORT			GPIOA
#define Y5_PIN			GPIO_PIN_4
#define Y6_PORT			GPIOA
#define Y6_PIN			GPIO_PIN_5
#define Y7_PORT			GPIOB
#define Y7_PIN			GPIO_PIN_1
#define Y8_PORT			GPIOA
#define Y8_PIN			GPIO_PIN_10

#define Y_CH_TOTAL_NUM  (sizeof(m_stYPinMap)/sizeof(stc_y_pin_map_t))
	
typedef struct
{
    GPIO_TypeDef * 			pstPort;
    uint16_t      			u16Pin;
} stc_y_pin_map_t;
typedef enum
{
		AS_CH_0 = 0x00U,
    AS_CH_1 = 0x01U,
    AS_CH_2 = 0x02U,
    AS_CH_3 = 0x03U,
    AS_CH_4 = 0x04U,
		AS_CH_5 = 0x05U,
		AS_CH_6 = 0x06U,
		AS_CH_7 = 0x07U,
	
} en_as_channel_t;
typedef enum
{
    AS_CHIP_1 = 0U,
    AS_CHIP_2 = 1U,
    AS_CHIP_3 = 2U,
    AS_CHIP_4 = 3U,

} en_as_chip_t;

/* 对外API */
void ADC_SAMPLE_Init(void);
#if(DATA_FRAME_BYTE_NUM)
uint16_t SampleGetFrame(uint8_t AREA, uint8_t row, uint8_t col, uint16_t buffer[][col]);
#else
uint16_t SampleGetFrame(uint8_t AREA, uint8_t row, uint8_t col, uint8_t buffer[][col]);
#endif

#if(DATA_FRAME_BYTE_NUM)
void Sample_CalibrateZero(uint8_t row, uint8_t col, uint16_t frame[][col], uint16_t calib[][col]);
#else
static void Sample_CalibrateZero(uint8_t row, uint8_t col, uint8_t frame[][col], uint8_t calib[][col]);
#endif
void Sample_Caliber(void);
/* ADC单次采集函数 */

#endif /* __ADC_SAMPLE_H__ */


