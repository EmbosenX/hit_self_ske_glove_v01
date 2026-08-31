/**
 ******************************************************************************
 * @file    adc_bat.c
 * @brief   源文件
 ******************************************************************************
 */
#include "adc_bat.h"

/* ==================== 硬件管脚定义 ==================== */
#define BAT_ADC_UNIT        CM_ADC1
#define BAT_ADC_PERIPH_CLK  FCG3_PERIPH_ADC1
#define BAT_ADC_PORT        GPIO_PORT_A
#define BAT_ADC_PIN         GPIO_PIN_02
#define BAT_ADC_CH          ADC_CH2
#define BAT_ADC_SEQ         ADC_SEQ_A
#define BAT_ADC_EOC_FLAG    ADC_FLAG_EOCA


/* ==================== ADC参数 ==================== */
#define ADC_VREF            (3.30F)
#define ADC_RESOLUTION      (4096UL)   /* 12bit */
#define ADC_TIMEOUT_VAL     (1000U)

/* ==================== 内部函数声明 ==================== */
static void BatAdcGpioInit(void);
static void BatAdcHardwareInit(void);
static int32_t BatAdcPollingGetVal(uint16_t *pu16AdcVal);

/**
 * @brief 电池ADC模块总初始化
 */
void ADC_BAT_Init(void)
{
    BatAdcGpioInit();
    BatAdcHardwareInit();
}

/**
 * @brief PA2 设置为模拟输入
 */
static void BatAdcGpioInit(void)
{
    stc_gpio_init_t stcGpioInit;
    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinAttr = PIN_ATTR_ANALOG;
    GPIO_Init(BAT_ADC_PORT, BAT_ADC_PIN, &stcGpioInit);
}

/**
 * @brief ADC1基础初始化
 */
static void BatAdcHardwareInit(void)
{
    stc_adc_init_t stcAdcInit;

    /* 使能ADC时钟 */
    FCG_Fcg3PeriphClockCmd(BAT_ADC_PERIPH_CLK, ENABLE);

    ADC_StructInit(&stcAdcInit);
    ADC_Init(BAT_ADC_UNIT, &stcAdcInit);

    /* 使能序列A通道 */
    ADC_ChCmd(BAT_ADC_UNIT, BAT_ADC_SEQ, BAT_ADC_CH, ENABLE);

    /* 硬件均值滤波 8次平均，抑制噪声 */
    ADC_ConvDataAverageConfig(BAT_ADC_UNIT, ADC_AVG_CNT8);
    ADC_ConvDataAverageChCmd(BAT_ADC_UNIT, BAT_ADC_CH, ENABLE);
}

/**
 * @brief ADC轮询采集（带超时保护，官方标准架构）
 */
static int32_t BatAdcPollingGetVal(uint16_t *pu16AdcVal)
{
    int32_t iRet = LL_ERR;
    __IO uint32_t u32TimeCount = 0UL;

    ADC_Start(BAT_ADC_UNIT);
    do
    {
        if(SET == ADC_GetStatus(BAT_ADC_UNIT, BAT_ADC_EOC_FLAG))
        {
            ADC_ClearStatus(BAT_ADC_UNIT, BAT_ADC_EOC_FLAG);
            *pu16AdcVal = ADC_GetValue(BAT_ADC_UNIT, BAT_ADC_CH);
            iRet = LL_OK;
            break;
        }
    } while (u32TimeCount++ < ADC_TIMEOUT_VAL);

    if(LL_ERR == iRet)
    {
        ADC_Stop(BAT_ADC_UNIT);
    }
    return iRet;
}

/**
 * @brief 单次ADC原始采样
 */
uint16_t BAT_ADC_SingleSample(void)
{
    uint16_t u16AdcVal = 0U;
    if(LL_OK == BatAdcPollingGetVal(&u16AdcVal))
    {
        return u16AdcVal;
    }
    return 0U;
}

/**
 * @brief 多次采样均值滤波
 */
uint16_t BAT_ADC_ReadAvg(uint8_t u8SampleCnt)
{
    uint32_t u32Sum = 0U;
    uint8_t i;

    if(0U == u8SampleCnt)
    {
        return BAT_ADC_SingleSample();
    }

    for(i = 0; i < u8SampleCnt; i++)
    {
        u32Sum += BAT_ADC_SingleSample();
        vTaskDelay(10);
    }
    return (uint16_t)(u32Sum / u8SampleCnt);
}

/**
 * @brief 获取电池电压 mV
 * 分压电路：Vadc = VBAT / 2 → VBAT = Vadc * 2
 * Vadc(mV) = adcVal * 3300 / 4096
 */
uint16_t BAT_GetVoltage_mV(void)
{
    uint16_t u16AdcRaw = BAT_ADC_ReadAvg(16U);
    uint32_t u32Vadc_mV = ((uint32_t)u16AdcRaw * 3300UL) / ADC_RESOLUTION;
    uint32_t u32Vbat_mV = u32Vadc_mV * 2UL;  /* 分压1/2，乘以2还原 */
    return (uint16_t)u32Vbat_mV;
}


