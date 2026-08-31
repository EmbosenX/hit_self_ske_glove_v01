/**
 ******************************************************************************
 * @file    adc.c
 * @brief   PY32F032 ADC+PGA采集驱动实现
 *
 *  采集路径：外部信号 → PA9/PB8 → 内部OPA(PGA放大) → ADC内部通道
 *  采集方式：单通道软件触发 + 轮询等待转换完成
 ******************************************************************************
 */

#include "adc.h"
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "gpio.h"
/* ============================================================
 *  内部变量
 * ============================================================ */
ADC_HandleTypeDef        hADC;
OPA_HandleTypeDef 			 hopa1,hopa2;

/* ============================================================
 *  内部函数声明
 * ============================================================ */

/* ============================================================
 *  公开函数实现
 * ============================================================ */
/**
  * @brief  ADC Configuration
  * @param  None
  * @retval None
  */
static void APP_AdcConfig(void)
{
  ADC_ChannelConfTypeDef   sConfig = {0};
  
  hADC.Instance = ADC1;
  hADC.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV4;
  hADC.Init.Resolution            = ADC_RESOLUTION_12B;
  hADC.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
  hADC.Init.ScanConvMode          = ADC_SCAN_DISABLE;    /* 单通道，关闭扫描模式 */
  hADC.Init.EOCSelection          = ADC_EOC_SINGLE_CONV; /* 单通道转换完成置位EOC */
  hADC.Init.LowPowerAutoWait      = DISABLE;
  hADC.Init.ContinuousConvMode    = DISABLE;             /* 单次转换 */
  hADC.Init.NbrOfConversion       = 1;                   /* 仅1路转换序列 */
  hADC.Init.DiscontinuousConvMode = DISABLE;
  hADC.Init.Overrun               = ADC_OVR_DATA_PRESERVED;
  hADC.Init.DMAContinuousRequests = DISABLE;
  hADC.Init.ExternalTrigConv      = ADC_SOFTWARE_START;
  hADC.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;
  
  if (HAL_ADC_Init(&hADC) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  /* 初始化时先默认配置OPA1通道，后续采集函数会动态覆盖 */
  sConfig.Channel      = ADC_CHANNEL_OPA1;
  sConfig.Rank         = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_640CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hADC, &sConfig) != HAL_OK)
  {
    APP_ErrorHandler();
  }
}
/**
  * @brief  OPA 外设 MSP 初始化：时钟、GPIO、模拟开关
  */
void HAL_OPA_MspInit(OPA_HandleTypeDef *hopa)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_SYSCFG_CLK_ENABLE();  // 操作模拟开关必须先开启SYSCFG时钟

    if (hopa->Instance == OPA1)
    {
        __HAL_RCC_OPA1_CLK_ENABLE();  // 开启OPA1独立外设时钟
        __HAL_RCC_GPIOA_CLK_ENABLE();
        
        /* PA9 配置为纯模拟模式 */
        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Pin  = GPIO_PIN_9;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        
        /* 开启PA9第二模拟功能，映射到OPA1同相输入 */
        HAL_SYSCFG_EnableGPIOAnalog2(GPIOA, GPIO_PIN_9);
    }
    else if (hopa->Instance == OPA2)
    {
        __HAL_RCC_OPA2_CLK_ENABLE();  // 开启OPA2独立外设时钟
        __HAL_RCC_GPIOB_CLK_ENABLE();
        
        /* PB3 配置为纯模拟模式 */
        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Pin  = GPIO_PIN_3;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
        
        /* 开启PB3第二模拟功能，关闭JTAG复用，映射到OPA2同相输入 */
        HAL_SYSCFG_EnableGPIOAnalog2(GPIOB, GPIO_PIN_3);
    }
}

/**
  * @brief  双路OPA配置：PGA模式4倍增益，内部输出直连ADC
  */
static void OPA_Config(void)
{
    /* ---------- OPA1：PA9输入，4倍PGA，内部输出到ADC ---------- */
    hopa1.Instance = OPA1;
    hopa1.Init.Mode           = OPA_PGA_MODE;
    hopa1.Init.PgaGain        = OPA_PGA_GAIN_8;
    hopa1.Init.ExternalOutput = DISABLE;     // 不引出外部引脚，仅内部直连ADC，噪声更低
    hopa1.Init.BiasVoltage    = 0;           // 无内置偏置，适配单极性正信号输入
    HAL_OPA_Init(&hopa1);
    HAL_OPA_Start(&hopa1);

    /* ---------- OPA2：PB3输入，4倍PGA，内部输出到ADC ---------- */
    hopa2.Instance = OPA2;
    hopa2.Init.Mode           = OPA_PGA_MODE;
    hopa2.Init.PgaGain        = OPA_PGA_GAIN_8;
    hopa2.Init.ExternalOutput = DISABLE;
    hopa2.Init.BiasVoltage    = 0;
    HAL_OPA_Init(&hopa2);
    HAL_OPA_Start(&hopa2);
	
    delay_ms(1);  // 等待两路OPA输出稳定，再执行ADC校准
}

/**
  * @brief  ADC+PGA驱动总初始化
  */
void Adc_Init(void)
{
    OPA_Config();
    APP_AdcConfig();

    /* ADC校准：必须在OPA输出稳定后执行 */
    if (HAL_ADCEx_Calibration_Start(&hADC, ADC_CALIBRATION_NUMBER_1) != HAL_OK)
    {
        APP_ErrorHandler();
    }
}

/**
  * @brief  ADC MSP初始化
  */
void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
    RCC_PeriphCLKInitTypeDef RCC_PeriphCLKInit = {0};

    /* ADC时钟源选择系统时钟 */
    RCC_PeriphCLKInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
    RCC_PeriphCLKInit.AdcClockSelection    = RCC_ADCCLKSOURCE_SYSCLK;
    HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphCLKInit);
  
    __HAL_RCC_ADC_CLK_ENABLE();
}
/**
  * @brief  单路OPA采集：启动目标OPA，关闭另一路OPA，返回ADC原始值
  * @param  ch: 选择采集通道 ADC_CH_PGA1 / ADC_CH_PGA2
  * @retval 12位ADC原始值
  */
uint16_t Adc_GetSingleOPA(AdcChannel_t ch)
{
    static AdcChannel_t s_currentCh = ADC_CH_PGA1; // 记录当前已配置的通道
    ADC_ChannelConfTypeDef sConfig = {0};
    uint16_t rawVal = 0;

    /* 只有通道发生变化时，才重新配置OPA和ADC通道 */
    if (ch != s_currentCh)
    {
        /* 1. 切换OPA：关闭不用的一路，开启目标一路 */
        if (ch == ADC_CH_PGA1)
        {
            HAL_OPA_Stop(&hopa2);
            HAL_OPA_Start(&hopa1);
            sConfig.Channel = ADC_CHANNEL_OPA1;
        }
        else
        {
            HAL_OPA_Stop(&hopa1);
            HAL_OPA_Start(&hopa2);
            sConfig.Channel = ADC_CHANNEL_OPA2;
        }

        /* 2. 等待OPA输出建立稳定（8倍增益建议50~100us即可，不用1ms）
           这里如果有微秒延时函数建议用udelay，没有的话可临时用软件循环延时 */
        delay_us(1); 

        /* 3. 重配ADC规则组通道 */
        sConfig.Rank         = ADC_REGULAR_RANK_1;
        sConfig.SamplingTime = ADC_SAMPLETIME_640CYCLES_5;
        HAL_ADC_ConfigChannel(&hADC, &sConfig);

        /* 更新当前通道记录 */
        s_currentCh = ch;
    }

    /* 4. 启动单次转换 + 轮询读取（同通道采集直接走到这一步） */
    HAL_ADC_Start(&hADC);
    if (HAL_ADC_PollForConversion(&hADC, 1000) == HAL_OK)
    {
        rawVal = HAL_ADC_GetValue(&hADC);
    }
    // 单次转换完成后自动停止，不需要手动HAL_ADC_Stop

    return rawVal;
}

uint16_t Adc_GetRawValue(AdcChannel_t ch)
{
    /* 直接调用单路采集，另一路OPA会自动关闭 */
    return Adc_GetSingleOPA(ch);
}

