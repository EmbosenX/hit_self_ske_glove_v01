/* ==================== 用户代码开始 ==================== */
/**
  ******************************************************************************
  * @file    opamp.c
  * @brief   OPAMP1 PGA内部放大模式，PB0输入，内部直连ADC
  ******************************************************************************
  */
/* ==================== 用户代码结束 ==================== */
#include "opamp.h"

OPAMP_HandleTypeDef hopamp1;

/**
  * @brief  OPAMP1 初始化：PGA模式，内部反馈，无外部输出引脚
  */
void MX_OPAMP1_Init(void)
{
  hopamp1.Instance = OPAMP1;
  hopamp1.Init.Mode = OPAMP_PGA_MODE;                    /* 可编程增益放大器模式 */
  hopamp1.Init.NonInvertingInput = OPAMP_NONINVERTINGINPUT_IO0;  /* 同相输入：PB0外部引脚 */
  hopamp1.Init.PowerMode = OPAMP_POWERMODE_NORMAL;       /* 正常功耗模式 */
  hopamp1.Init.PgaConnect = OPAMP_PGA_CONNECT_INVERTINGINPUT_NO; /* 反相端内部接反馈网络，无需外部PC5引脚 */
  hopamp1.Init.PgaGain = OPAMP_PGA_GAIN_8_OR_MINUS_7;    /* 同相增益=4倍，可选2/4/8/16倍 */
  hopamp1.Init.UserTrimming = OPAMP_TRIMMING_FACTORY;    /* 工厂校准参数，精度最优 */
  
  if (HAL_OPAMP_Init(&hopamp1) != HAL_OK)
  {
    Error_Handler();
  }
}

void HAL_OPAMP_MspInit(OPAMP_HandleTypeDef* opampHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(opampHandle->Instance==OPAMP1)
  {
    __HAL_RCC_OPAMP_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    /**OPAMP1 GPIO Configuration
    PB0  ------> OPAMP1_VINP （外部模拟信号输入）
    PC4  ------> OPAMP1_VOUT （内部直连ADC，无需外部接线）
    */
    /* PB0：外部输入引脚 */
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* PC4：仅作内部模拟通路，连接ADC输入，无需外部接线 */
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  }
}

void HAL_OPAMP_MspDeInit(OPAMP_HandleTypeDef* opampHandle)
{
  if(opampHandle->Instance==OPAMP1)
  {
    __HAL_RCC_OPAMP_CLK_DISABLE();
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_0);
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_4);
  }
}

/* ==================== 用户代码开始 ==================== */
/**
 * @brief  启动OPAMP1，进入正常放大状态
 * @note   初始化后必须调用此函数，否则OPAMP处于高阻状态，不工作
 */
void OPAMP1_Start(void)
{
    HAL_OPAMP_Start(&hopamp1);
    HAL_Delay(1); /* 等待运放输出稳定，典型稳定时间5us，延时1ms确保可靠 */
}

/**
 * @brief  停止OPAMP1，进入低功耗
 */
void OPAMP1_Stop(void)
{
    HAL_OPAMP_Stop(&hopamp1);
}

/**
 * @brief  动态切换PGA增益
 * @param  gain: 增益宏，如 OPAMP_PGA_GAIN_2_OR_MINUS_1
 */
void OPAMP1_SetGain(uint32_t gain)
{
    HAL_OPAMP_Stop(&hopamp1);
    hopamp1.Init.PgaGain = gain;
    HAL_OPAMP_Init(&hopamp1);
    HAL_OPAMP_Start(&hopamp1);
    HAL_Delay(1);
}
/* ==================== 用户代码结束 ==================== */


