/* ==================== 用户代码开始 ==================== */
/**
  ******************************************************************************
  * @file    adc.c
  * @brief   ADC1采集OPAMP放大后的内部信号
  ******************************************************************************
  */
/* ==================== 用户代码结束 ==================== */
#include "adc.h"

ADC_HandleTypeDef hadc1;

/**
  * @brief  ADC1 初始化：单通道，采集OPAMP内部输出
  */
void MX_ADC1_Init(void)
{
  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /** 通用配置
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV6;  /* 6分频，确保ADC内核时钟≤36MHz */
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
  hadc1.Init.OversamplingMode = DISABLE;
  hadc1.Init.Oversampling.Ratio = 1;
  
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** 独立模式
  */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    Error_Handler();
  }

  /** 配置规则通道：ADC1_IN4 对应OPAMP1内部输出
  */
  sConfig.Channel = ADC_CHANNEL_4;       /* 通道4对应PC4，OPAMP输出内部直连此处 */
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_387CYCLES_5; /* 加长采样时间，适配运放输出阻抗 */
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  sConfig.OffsetSignedSaturation = DISABLE;
  
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /* 16位ADC硬件偏移校准，必须执行 */
  if (HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED) != HAL_OK)
  {
    Error_Handler();
  }
}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(adcHandle->Instance==ADC1)
  {
    /** ADC时钟配置
    */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_ADC;
    PeriphClkInitStruct.PLL2.PLL2M = 1;
    PeriphClkInitStruct.PLL2.PLL2N = 12;
    PeriphClkInitStruct.PLL2.PLL2P = 2;
    PeriphClkInitStruct.PLL2.PLL2Q = 2;
    PeriphClkInitStruct.PLL2.PLL2R = 2;
    PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_3;
    PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOMEDIUM;
    PeriphClkInitStruct.PLL2.PLL2FRACN = 4096;
    PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
    
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_RCC_ADC12_CLK_ENABLE();
    /* PC4已在OPAMP初始化中配置为模拟模式，此处无需重复配置 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{
  if(adcHandle->Instance==ADC1)
  {
    __HAL_RCC_ADC12_CLK_DISABLE();
  }
}

/* ==================== 用户代码开始 ==================== */
/**
 * @brief  ADC1单通道轮询采集（ADC保持上电，仅触发转换）
 * @param  pu16AdcVal  输出16位原始采样值
 * @retval 1成功，0失败
 */
int32_t AdcPollingSample(uint16_t *pu16AdcVal)
{
    const uint32_t ADC_TIMEOUT_MS = 10U;

    if (pu16AdcVal == NULL)
    {
        return 0;
    }

    /* 清除转换完成、溢出标志 */
    __HAL_ADC_CLEAR_FLAG(&hadc1, ADC_FLAG_EOC | ADC_FLAG_OVR);

    /* 软件触发单次转换（ADC已上电，仅启动转换序列） */
    if (HAL_ADC_Start(&hadc1) != HAL_OK)
    {
        return 0;
    }

    /* 等待转换完成 */
    if (HAL_ADC_PollForConversion(&hadc1, ADC_TIMEOUT_MS) == HAL_OK)
    {
        /* 读取结果，读DR寄存器会自动清除EOC标志 */
        *pu16AdcVal = (uint16_t)HAL_ADC_GetValue(&hadc1);
        return 1;
    }
    else
    {
        /* 仅超时异常时才停止ADC复位状态 */
        HAL_ADC_Stop(&hadc1);
        return 0;
    }
}
/* ==================== 用户代码结束 ==================== */



