/**
 ******************************************************************************
 * @file    app_led_task.h
 * @brief   LED指示任务头文件
 ******************************************************************************
 */

#ifndef __APP_LED_H
#define __APP_LED_H

#include "led.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* LED工作模式 */
typedef enum
{
    LED_MODE_OFF = 0,       // 常灭
    LED_MODE_ON,            // 常亮
    LED_MODE_BLINK_SLOW,    // 慢闪 1Hz (500ms亮/500ms灭)
    LED_MODE_BLINK_FAST,    // 快闪 4Hz (125ms亮/125ms灭)
    LED_MODE_CUSTOM         // 自定义亮灭周期
} led_mode_t;

/* 控制指令结构体 */
typedef struct
{
    led_index_t led;        // 目标LED
    led_mode_t  mode;       // 工作模式
    uint32_t    on_ms;      // 自定义亮时长(ms)，仅CUSTOM模式有效
    uint32_t    off_ms;     // 自定义灭时长(ms)，仅CUSTOM模式有效
} led_cmd_t;

/************************ API ************************/
/**
 * @brief  创建LED服务任务并初始化硬件
 * @param  
 * @param  
 */
void APP_Led_TaskCreate(void);

/**
 * @brief  设置指定LED工作模式（线程安全，可在任意任务调用）
 * @param  led  LED编号
 * @param  mode 工作模式
 */
void LED_SetMode(led_index_t led, led_mode_t mode);

/**
 * @brief  设置LED自定义闪烁周期
 * @param  led    LED编号
 * @param  on_ms  亮灯时长(ms)
 * @param  off_ms 灭灯时长(ms)
 */
void LED_SetCustomBlink(led_index_t led, uint32_t on_ms, uint32_t off_ms);

/************************ 业务快捷接口 ************************/
/* 系统状态快捷设置 */
void LED_Sys_Disconnected(void);   // 蓝灯常亮：未连接
void LED_Sys_Connected(void);      // 绿灯常亮：已连接
void LED_Sys_Error(void);          // 红灯快闪：系统异常

/* 充电状态快捷设置 */
void LED_Bat_LowWarn(void);        // 低电量灯快闪：电量不足

#endif


