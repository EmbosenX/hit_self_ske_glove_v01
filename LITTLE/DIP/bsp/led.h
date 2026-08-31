/**
 ******************************************************************************
 * @file    led.h
 * @brief   LED驱动头文件，定义LED索引枚举和控制接口
 ******************************************************************************
 */

#ifndef __LED_H
#define __LED_H

#include "hc32_ll.h"
#include "hc32_ll_gpio.h"

/* 硬件配置区 */
#define LED_COMMON_ANODE     1u   // 1=共阳(低电平亮), 0=共阴(高电平亮)

typedef enum
{
    LED_RED = 0u,    // PA10 系统红灯
    LED_GREEN,       // PC9  系统绿灯
    LED_BLUE,        // PC6  系统蓝灯
    LED_BAT_LOW,     // 电池 低电量指示灯
    LED_MAX          // LED总数
} led_index_t;

/* 通用API */
void led_init(void);
void led_on(led_index_t led_idx);
void led_off(led_index_t led_idx);
void led_toggle(led_index_t led_idx);
void led_all_off(void);
void led_all_on(void);

#endif


