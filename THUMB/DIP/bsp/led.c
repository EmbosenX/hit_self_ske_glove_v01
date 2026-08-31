/**
 ******************************************************************************
 * @file    led.c
 * @brief   LED驱动模块，实现板载LED的初始化、点亮、熄灭、翻转等控制
 * @note    支持共阳/共阴两种硬件接法，通过LED_COMMON_ANODE宏切换电平逻辑
 ******************************************************************************
 */
#include "led.h"

/**
 * @brief LED引脚配置结构体
 */
typedef struct
{
    uint8_t port;     /*!< GPIO端口号 */
    uint16_t pin;     /*!< GPIO引脚号 */
} led_cfg_t;

/*!< LED引脚配置表，下标与led_index_t枚举一一对应 */
static const led_cfg_t g_led_cfg[LED_MAX] = {
    [LED_RED]     = {GPIO_PORT_A, GPIO_PIN_10},   /*!< 红灯  -> PA10 */
    [LED_GREEN]   = {GPIO_PORT_C, GPIO_PIN_09},   /*!< 绿灯  -> PC9  */
    [LED_BLUE]    = {GPIO_PORT_C, GPIO_PIN_06},   /*!< 蓝灯  -> PC6  */
    [LED_BAT_LOW] = {GPIO_PORT_A, GPIO_PIN_15},   /*!< 低电量灯 -> PA15 */
};

/*!< 根据硬件接法自动适配亮/灭电平逻辑 */
#if LED_COMMON_ANODE
    /* 共阳接法：低电平点亮，高电平熄灭 */
    #define LED_OUTPUT_ON(port, pin)     GPIO_ResetPins(port, pin)
    #define LED_OUTPUT_OFF(port, pin)    GPIO_SetPins(port, pin)
#else
    /* 共阴接法：高电平点亮，低电平熄灭 */
    #define LED_OUTPUT_ON(port, pin)     GPIO_SetPins(port, pin)
    #define LED_OUTPUT_OFF(port, pin)    GPIO_ResetPins(port, pin)
#endif

/**
 * @brief  初始化所有LED引脚为数字输出模式
 * @note   初始化过程中会依次点亮每个LED 200ms用于自检
 */
void led_init(void)
{
    uint8_t i;
    stc_gpio_init_t stcGpioCfg;

    GPIO_StructInit(&stcGpioCfg);
    stcGpioCfg.u16PinAttr = PIN_ATTR_DIGITAL;  /*!< 数字引脚属性 */

    for (i = 0u; i < LED_MAX; i++)
    {
        GPIO_Init(g_led_cfg[i].port, g_led_cfg[i].pin, &stcGpioCfg);
        led_on((led_index_t)i);
        DDL_DelayMS(200);   /*!< 点亮200ms自检 */
        led_off((led_index_t)i);
    }
}

/**
 * @brief  点亮指定LED
 * @param  led_idx LED索引（见led_index_t）
 */
void led_on(led_index_t led_idx)
{
    if (led_idx >= LED_MAX) return;
    LED_OUTPUT_ON(g_led_cfg[led_idx].port, g_led_cfg[led_idx].pin);
}

/**
 * @brief  熄灭指定LED
 * @param  led_idx LED索引（见led_index_t）
 */
void led_off(led_index_t led_idx)
{
    if (led_idx >= LED_MAX) return;
    LED_OUTPUT_OFF(g_led_cfg[led_idx].port, g_led_cfg[led_idx].pin);
}

/**
 * @brief  翻转指定LED状态
 * @param  led_idx LED索引（见led_index_t）
 */
void led_toggle(led_index_t led_idx)
{
    if (led_idx >= LED_MAX) return;
    GPIO_TogglePins(g_led_cfg[led_idx].port, g_led_cfg[led_idx].pin);
}

/**
 * @brief  熄灭所有LED
 */
void led_all_off(void)
{
    uint8_t i;
    for (i = 0u; i < LED_MAX; i++) led_off((led_index_t)i);
}

/**
 * @brief  点亮所有LED
 */
void led_all_on(void)
{
    uint8_t i;
    for (i = 0u; i < LED_MAX; i++) led_on((led_index_t)i);
}
