#include "app_led_task.h"

/************************ 内部配置 ************************/
#define LED_TASK_PERIOD_MS    50u    // 任务扫描节拍 50ms
#define LED_CMD_QUEUE_SIZE    8u     // 控制队列深度

/* 每个LED的控制状态块 */
typedef struct
{
    led_mode_t  mode;        // 当前LED工作模式
    uint32_t    on_ticks;    // 当处于闪烁模式时，持续点亮的节拍数
    uint32_t    off_ticks;   // 当处于闪烁模式时，持续熄灭的节拍数
    uint32_t    tick_cnt;    // 当前计数值，用于闪烁周期切换
    uint8_t     cur_state;   // 当前亮灭状态 1=亮 0=灭
} led_ctrl_t;

static void AppledTask(void *pvParameters);
/************************ 内部变量 ************************/
/* LED任务控制块，用于创建静态任务 */
static StaticTask_t xLedTaskTcb;
static StackType_t  uxLedTaskStack[256];
static TaskHandle_t xLedTaskHandle = NULL;

/* 静态队列相关：队列控制块 + 数据存储缓冲区 */
static QueueHandle_t g_led_cmd_q    = NULL;
static StaticQueue_t g_led_cmd_q_cb;
static uint8_t       g_led_cmd_q_buf[LED_CMD_QUEUE_SIZE * sizeof(led_cmd_t)];

/* LED控制状态数组，保存每个LED的当前模式和闪烁状态 */
static led_ctrl_t    g_led_ctrl[LED_MAX];

/************************ 内部函数声明 ************************/
static void Led_TaskEntry(void *pvParameters);            // LED任务入口函数
static void led_process_blink(led_index_t idx);          // 处理单个LED的闪烁逻辑
static void led_execute_cmd(const led_cmd_t *cmd);       // 执行LED控制命令

/************************ 公开API ************************/
void APP_Led_TaskCreate(void)
{
		/* 创建静态队列：无需动态内存分配 */
    g_led_cmd_q = xQueueCreateStatic(LED_CMD_QUEUE_SIZE,   // 队列深度
                                     sizeof(led_cmd_t),     // 单个元素大小
                                     g_led_cmd_q_buf,       // 数据存储缓冲区
                                     &g_led_cmd_q_cb);      // 队列控制块

    /* 创建LED服务任务 */
    xLedTaskHandle = xTaskCreateStatic(
        Led_TaskEntry,
        "LedTask",
        256,
        NULL,
        10,
        uxLedTaskStack,
        &xLedTaskTcb
    );
		if(xLedTaskHandle!=NULL){DDL_Printf("LedTask success!\r\n");}
}

void LED_SetMode(led_index_t led, led_mode_t mode)
{
    led_cmd_t cmd;
    cmd.led  = led;
    cmd.mode = mode;

    if (g_led_cmd_q != NULL)
    {
        xQueueSend(g_led_cmd_q, &cmd, 0);
    }
}

void LED_SetCustomBlink(led_index_t led, uint32_t on_ms, uint32_t off_ms)
{
    led_cmd_t cmd;
    cmd.led    = led;
    cmd.mode   = LED_MODE_CUSTOM;
    cmd.on_ms  = on_ms;
    cmd.off_ms = off_ms;

    if (g_led_cmd_q != NULL)
    {
        xQueueSend(g_led_cmd_q, &cmd, 0);
    }
}

/************************ 业务快捷接口 ************************/
void LED_Sys_Disconnected(void)
{
    LED_SetMode(LED_RED,   LED_MODE_OFF);
    LED_SetMode(LED_GREEN, LED_MODE_OFF);
    LED_SetMode(LED_BLUE,  LED_MODE_BLINK_SLOW);
}

void LED_Sys_Connected(void)
{
    LED_SetMode(LED_RED,   LED_MODE_OFF);
    LED_SetMode(LED_GREEN, LED_MODE_ON);
    LED_SetMode(LED_BLUE,  LED_MODE_OFF);
}

void LED_Sys_Error(void)
{
    LED_SetMode(LED_RED,   LED_MODE_BLINK_FAST);
    LED_SetMode(LED_GREEN, LED_MODE_OFF);
    LED_SetMode(LED_BLUE,  LED_MODE_OFF);
}

void LED_Bat_LowWarn(void)
{
    LED_SetMode(LED_BAT_LOW, LED_MODE_BLINK_FAST);
}

/*******************************************************************************
 * @brief  LED任务：状态指示
 ******************************************************************************/
static void Led_TaskEntry(void *pvParameters)
{
    led_cmd_t cmd;
    uint8_t i;
    (void)pvParameters;

    /* 初始化硬件 */
    led_init();

    /* 初始化控制块 默认全灭 */
    for (i = 0u; i < LED_MAX; i++)
    {
        g_led_ctrl[i].mode      = LED_MODE_OFF;
        g_led_ctrl[i].on_ticks  = 0;
        g_led_ctrl[i].off_ticks = 0;
        g_led_ctrl[i].tick_cnt  = 0;
        g_led_ctrl[i].cur_state = 0;
    }

    for (;;)
    {
        /* 处理控制指令 非阻塞 */
        while (xQueueReceive(g_led_cmd_q, &cmd, 0) == pdTRUE)
        {
            led_execute_cmd(&cmd);
        }

        /* 扫描所有LED 处理闪烁逻辑 */
        for (i = 0u; i < LED_MAX; i++)
        {
            led_process_blink((led_index_t)i);
        }

        /* 任务节拍延时 */
        vTaskDelay(pdMS_TO_TICKS(LED_TASK_PERIOD_MS));
    }
}

static void led_execute_cmd(const led_cmd_t *cmd)
{
    led_ctrl_t *p = &g_led_ctrl[cmd->led];

    if (cmd->led >= LED_MAX) return;

    p->mode     = cmd->mode;
    p->tick_cnt = 0;

    switch (cmd->mode)
    {
        case LED_MODE_OFF:
            led_off(cmd->led);
            p->cur_state = 0;
            break;

        case LED_MODE_ON:
            led_on(cmd->led);
            p->cur_state = 1;
            break;

        case LED_MODE_BLINK_SLOW:
            p->on_ticks  = 500 / LED_TASK_PERIOD_MS;  // 500ms亮
            p->off_ticks = 500 / LED_TASK_PERIOD_MS;  // 500ms灭
            led_on(cmd->led);
            p->cur_state = 1;
            break;

        case LED_MODE_BLINK_FAST:
            p->on_ticks  = 200 / LED_TASK_PERIOD_MS;  // 200ms亮
            p->off_ticks = 200 / LED_TASK_PERIOD_MS;  // 200ms灭
            led_on(cmd->led);
            p->cur_state = 1;
            break;

        case LED_MODE_CUSTOM:
            p->on_ticks  = cmd->on_ms  / LED_TASK_PERIOD_MS;
            p->off_ticks = cmd->off_ms / LED_TASK_PERIOD_MS;
            if (p->on_ticks  == 0) p->on_ticks  = 1;
            if (p->off_ticks == 0) p->off_ticks = 1;
            led_on(cmd->led);
            p->cur_state = 1;
            break;

        default:
            break;
    }
}

static void led_process_blink(led_index_t idx)
{
    led_ctrl_t *p = &g_led_ctrl[idx];

    /* 常亮/常灭模式无需处理 */
    if ((p->mode == LED_MODE_ON) || (p->mode == LED_MODE_OFF))
    {
        return;
    }

    /* 闪烁模式计数+翻转 */
    p->tick_cnt++;

    if (p->cur_state == 1)
    {
        if (p->tick_cnt >= p->on_ticks)
        {
            led_off(idx);
            p->cur_state = 0;
            p->tick_cnt  = 0;
        }
    }
    else
    {
        if (p->tick_cnt >= p->off_ticks)
        {
            led_on(idx);
            p->cur_state = 1;
            p->tick_cnt  = 0;
        }
    }
}


