/**
 ******************************************************************************
 * @file    adc_sample.h
 * @brief   源文件
 ******************************************************************************
 */
#ifndef __ADC_SAMPLE_H__
#define __ADC_SAMPLE_H__

#include "hc32_ll.h"
#include "main.h"
/* ====================== 硬件管脚定义（严格匹配原理图） ====================== */
/* 大拇指通用输出Y管脚 - 完整对应表 */
#define PIN_TY0_PORT     GPIO_PORT_B
#define PIN_TY0_PIN      GPIO_PIN_09

#define PIN_TY1_PORT     GPIO_PORT_B
#define PIN_TY1_PIN      GPIO_PIN_08

#define PIN_TY2_PORT     GPIO_PORT_B
#define PIN_TY2_PIN      GPIO_PIN_07

#define PIN_TY3_PORT     GPIO_PORT_B
#define PIN_TY3_PIN      GPIO_PIN_06

#define PIN_TY4_PORT     GPIO_PORT_B
#define PIN_TY4_PIN      GPIO_PIN_05

#define PIN_TY5_PORT     GPIO_PORT_B
#define PIN_TY5_PIN      GPIO_PIN_04

#define PIN_TY6_PORT     GPIO_PORT_B
#define PIN_TY6_PIN      GPIO_PIN_03

#define PIN_TY7_PORT     GPIO_PORT_A
#define PIN_TY7_PIN      GPIO_PIN_15

#define PIN_TY8_PORT     GPIO_PORT_A
#define PIN_TY8_PIN      GPIO_PIN_08

#define PIN_TY9_PORT     GPIO_PORT_B
#define PIN_TY9_PIN      GPIO_PIN_15

#define PIN_TY10_PORT    GPIO_PORT_B
#define PIN_TY10_PIN     GPIO_PIN_14

#define PIN_TY11_PORT    GPIO_PORT_B
#define PIN_TY11_PIN     GPIO_PIN_13

#define PIN_TY12_PORT    GPIO_PORT_B
#define PIN_TY12_PIN     GPIO_PIN_12

#define PIN_TY13_PORT    GPIO_PORT_B
#define PIN_TY13_PIN     GPIO_PIN_10

#define PIN_TY14_PORT    GPIO_PORT_B
#define PIN_TY14_PIN     GPIO_PIN_02

#define PIN_TY15_PORT    GPIO_PORT_B
#define PIN_TY15_PIN     GPIO_PIN_00

#define PIN_TY16_PORT    GPIO_PORT_H
#define PIN_TY16_PIN     GPIO_PIN_01

#define PIN_TY17_PORT    GPIO_PORT_H
#define PIN_TY17_PIN     GPIO_PIN_00

/* 食指通用输出Y管脚 */

/* 无名指通用输出Y管脚 */

/* 中指通用输出Y管脚 */ 

/* 小指通用输出Y管脚 */

/* 手掌通用输出Y管脚 */

/* 模拟开关 AS 使能管脚 AS_EN1 ~ AS_EN4 */
#define AS_EN0_PORT     GPIO_PORT_H
#define AS_EN0_PIN      GPIO_PIN_02

/* 模拟开关通道选择 AS_S1 ~ AS_S3 */
#define AS_S1_PORT      GPIO_PORT_C
#define AS_S1_PIN       GPIO_PIN_13

#define AS_S2_PORT      GPIO_PORT_C
#define AS_S2_PIN       GPIO_PIN_15

#define AS_S3_PORT      GPIO_PORT_C
#define AS_S3_PIN       GPIO_PIN_14


/*所有的行列*/
#define ALL_ROW			10
#define ALL_COL 		16


/* 电平枚举 */
typedef enum
{
    PIN_LOW  = 0U,
    PIN_HIGH = 1U
} en_pin_level_t;

/* AS模拟开关通道选择编码 0~7 (S3 S2 S1 三位二进制) */
typedef enum
{
    AS_CH_0 = 0x00U,    // 000
    AS_CH_1 = 0x01U,    // 001
    AS_CH_2 = 0x02U,    // 010
    AS_CH_3 = 0x03U,    // 011
    AS_CH_4 = 0x04U,    // 100
    AS_CH_5 = 0x05U,    // 101
    AS_CH_6 = 0x06U,    // 110
    AS_CH_7 = 0x07U     // 111
} en_as_channel_t;

/* 模拟开关芯片编号 1~4 */
typedef enum
{
		AS_CHIP_0 = 0U,

} en_as_chip_t;

/* 对外API */
void ADC_SAMPLE_Init(void);
#if(DATA_FRAME_BYTE_NUM)
uint16_t SampleGetFrame(uint8_t AREA, uint8_t row, uint8_t col, uint16_t buffer[][col]);
#else
uint16_t SampleGetFrame(uint8_t AREA, uint8_t row, uint8_t col, uint8_t buffer[][col]);
#endif
/* ADC单次采集函数 */

#endif /* __ADC_SAMPLE_H__ */



