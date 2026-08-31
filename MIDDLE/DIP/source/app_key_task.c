/**
 *******************************************************************************
 * @file  app_key_task.c
 * @brief 按键应用任务实现 (周期扫描版)
 *        全FreeRTOS静态分配，状态机实现消抖、长短按分离检测
 *******************************************************************************
 */

#include "app_key_task.h"

/*******************************************************************************
 * 状态机状态定义
 ******************************************************************************/
#define KEY_STA_IDLE                0x00U   /* 空闲：按键松开 */
#define KEY_STA_DEBOUNCE            0x01U   /* 消抖中：检测到按下 */
#define KEY_STA_PRESSED             0x02U   /* 确认按下：计时长短按 */
#define KEY_STA_RELEASE             0x03U   /* 松开消抖中 */

/*******************************************************************************
 * FreeRTOS静态资源
 ******************************************************************************/
/* 按键任务栈与控制块 */
static StaticTask_t xKeyTaskTcb;
static StackType_t  xKeyTaskStack[256U];

/* 按键事件队列 (静态分配) */
static StaticQueue_t xKeyQueueBuffer;
static uint8_t       ucKeyQueueStorage[4U * sizeof(key_event_t)];
QueueHandle_t        xKeyEventQueue;

/*******************************************************************************
 * 内部状态变量
 ******************************************************************************/
static uint8_t  u8KeyState = KEY_STA_IDLE;
static uint32_t u32PressTick = 0U;
static uint8_t  u8LongTrigFlag = 0U;

/*******************************************************************************
 * 内部函数声明
 ******************************************************************************/
static void App_Key_Task(void *pvParameters);
static uint8_t App_Key_ReadLevel(void);
static void App_Key_Init(void);
/*******************************************************************************
 * 函数实现
 ******************************************************************************/

/**
 * @brief  读取按键引脚电平
 */
static uint8_t App_Key_ReadLevel(void)
{
    return GPIO_ReadInputPins(KEY_IN_PORT, KEY_IN_PIN);
}

/**
 * @brief  按键处理任务主体
 */
static void App_Key_Task(void *pvParameters)
{
    key_event_t enEvent;
    uint8_t u8CurLevel;
    uint32_t u32Duration;
    (void)pvParameters;
	
		App_Key_Init();
    for (;;) {
        u8CurLevel = App_Key_ReadLevel();

        switch (u8KeyState)
        {
            case KEY_STA_IDLE:
                if (u8CurLevel == KEY_PRESS_LEVEL) {
                    /* 检测到按下电平，进入消抖，记录时间 */
                    u8KeyState = KEY_STA_DEBOUNCE;
                    u32PressTick = xTaskGetTickCount();
                    u8LongTrigFlag = 0U;
                }
                break;

            case KEY_STA_DEBOUNCE:
                if (u8CurLevel == KEY_PRESS_LEVEL) {
                    /* 消抖时间到，确认按下 */
                    if ((xTaskGetTickCount() - u32PressTick) >= pdMS_TO_TICKS(KEY_DEBOUNCE_MS)) {
                        u8KeyState = KEY_STA_PRESSED;
                        u32PressTick = xTaskGetTickCount(); /* 重新计时长按 */
                    }
                } else {
                    /* 抖动，回到空闲 */
                    u8KeyState = KEY_STA_IDLE;
                }
                break;

            case KEY_STA_PRESSED:
                if (u8CurLevel == KEY_PRESS_LEVEL) {
                    u32Duration = xTaskGetTickCount() - u32PressTick;
                    /* 达到长按阈值，且未触发过，发送长按事件 */
                    if ((u32Duration >= pdMS_TO_TICKS(KEY_LONG_PRESS_MS)) && (0U == u8LongTrigFlag)) {
                        enEvent = KEY_EVT_LONG;
                        (void)xQueueSend(xKeyEventQueue, &enEvent, 0U);
                        u8LongTrigFlag = 1U;
												GPIO_ResetPins(POWER_OUT_PORT,POWER_OUT_PIN);//长按关机
                    }
                } else {
                    /* 检测到松开，进入松开消抖 */
                    u8KeyState = KEY_STA_RELEASE;
                    u32PressTick = xTaskGetTickCount();
                }
                break;

            case KEY_STA_RELEASE:
                if (u8CurLevel != KEY_PRESS_LEVEL) {
                    /* 松开消抖时间到，确认松开 */
                    if ((xTaskGetTickCount() - u32PressTick) >= pdMS_TO_TICKS(KEY_DEBOUNCE_MS)) {
                        /* 未触发过长按则判定为短按 */
                        if (0U == u8LongTrigFlag) {
                            enEvent = KEY_EVT_SHORT;
                            (void)xQueueSend(xKeyEventQueue, &enEvent, 0U);
                        }
                        u8KeyState = KEY_STA_IDLE;
                    }
                } else {
                    /* 松开过程中再次按下，回到按下状态 */
                    u8KeyState = KEY_STA_PRESSED;
                }
                break;

            default:
                u8KeyState = KEY_STA_IDLE;
                break;
        }

        vTaskDelay(pdMS_TO_TICKS(KEY_SCAN_PERIOD_MS));
    }
}

/**
 * @brief  按键硬件初始化 (仅GPIO输入配置)
 * @note   调度器启动前调用
 */
static void App_Key_Init(void)
{
    stc_gpio_init_t stcGpioCfg;

    /* 配置为输入模式，外部已有上拉，关闭内部上拉 */
    (void)GPIO_StructInit(&stcGpioCfg);
    stcGpioCfg.u16PinDir = PIN_DIR_IN;
    stcGpioCfg.u16PullUp = PIN_PU_OFF;
    (void)GPIO_Init(KEY_IN_PORT, KEY_IN_PIN, &stcGpioCfg);
}
void App_Power_Init(void)
{
    stc_gpio_init_t stcGpioCfg;

    /* 配置为输出模式 内部上拉 */
    (void)GPIO_StructInit(&stcGpioCfg);
    stcGpioCfg.u16PinDrv = PIN_HIGH_DRV;
    stcGpioCfg.u16PinDir = PIN_DIR_OUT;
		stcGpioCfg.u16PullUp = PIN_PU_ON;
    (void)GPIO_Init(POWER_OUT_PORT, POWER_OUT_PIN, &stcGpioCfg);
		GPIO_SetPins(POWER_OUT_PORT,POWER_OUT_PIN);
}
/**
 * @brief  创建按键任务与RTOS资源 (全部静态分配)
 * @note   调度器启动前调用
 */
void App_Key_TaskCreate(void)
{
		App_Key_Init();
    /* 创建事件队列 */
    xKeyEventQueue = xQueueCreateStatic(4U,
                                        sizeof(key_event_t),
                                        ucKeyQueueStorage,
                                        &xKeyQueueBuffer);

    /* 创建按键任务，优先级3 */
    (void)xTaskCreateStatic(App_Key_Task,
                            "key_task",
                            256U,
                            NULL,
                            3U,
                            xKeyTaskStack,
                            &xKeyTaskTcb);
}

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/

