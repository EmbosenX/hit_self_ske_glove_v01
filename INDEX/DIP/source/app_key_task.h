/**
 *******************************************************************************
 * @file  app_key_task.h
 * @brief 按键应用任务头文件 (周期扫描版)
 *        基于FreeRTOS周期任务 + 状态机，实现单按键消抖与长短按检测
 *        适配硬件：PD1独立按键，低电平有效，外部上拉
 *******************************************************************************
 */
#ifndef __APP_KEY_TASK_H__
#define __APP_KEY_TASK_H__

#include "hc32_ll.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/******************************************************************************
 * 硬件引脚配置
 *****************************************************************************/
#define KEY_IN_PORT                 GPIO_PORT_D
#define KEY_IN_PIN                  GPIO_PIN_01
#define KEY_PRESS_LEVEL             RESET  /* 按下为低电平 */

#define POWER_OUT_PORT                 GPIO_PORT_B
#define POWER_OUT_PIN                  GPIO_PIN_03
#define POWER_PRESS_LEVEL              SET  /* 高电平上电 */

/******************************************************************************
 * 时间参数配置 (单位：ms)
 *****************************************************************************/
#define KEY_SCAN_PERIOD_MS          10U     /* 扫描周期 */
#define KEY_DEBOUNCE_MS             20U     /* 消抖时间 (需≥1个扫描周期) */
#define KEY_LONG_PRESS_MS           1000U   /* 长按触发阈值 */

/******************************************************************************
 * 按键事件枚举
 *****************************************************************************/
typedef enum {
    KEY_EVT_NONE  = 0U,
    KEY_EVT_SHORT = 1U,   /* 短按事件：松开后触发 */
    KEY_EVT_LONG  = 2U    /* 长按事件：达到阈值触发1次 */
} key_event_t;

/* 按键事件队列句柄，应用层通过xQueueReceive读取事件 */
extern QueueHandle_t xKeyEventQueue;

/******************************************************************************
 * 对外接口声明
 *****************************************************************************/

void App_Key_TaskCreate(void);
void App_Power_Init(void);

#endif /* __APP_KEY_TASK_H__ */


