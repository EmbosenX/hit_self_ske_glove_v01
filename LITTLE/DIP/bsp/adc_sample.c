/**
 ******************************************************************************
 * @file    adc_sample.c
 * @brief   源文件
 ******************************************************************************
 */
#include "adc_sample.h"
#include <string.h>
#include "app_tac_config.h"
#include "main.h"

/* ADC基础配置 */
#define ADC_UNIT       			(CM_ADC1)
#define ADC_PERIPH_CLK      (FCG3_PERIPH_ADC1)
#define ADC_SEQ        			ADC_SEQ_A
#define ADC_EOC_FLAG   			ADC_FLAG_EOCA

/* ADC通道引脚定义 */
#define AD0_ADC_PORT       GPIO_PORT_A
#define AD0_ADC_PIN        GPIO_PIN_00
#define AD0_ADC_CH         ADC_CH0
#define AD0_ADC_PGA_PIN    ADC_PGA_PIN_ADC1_PA0

#define AD1_ADC_PORT       GPIO_PORT_A
#define AD1_ADC_PIN        GPIO_PIN_01
#define AD1_ADC_CH         ADC_CH1
#define AD1_ADC_PGA_PIN    ADC_PGA_PIN_ADC1_PA1

#define AD2_ADC_PORT       GPIO_PORT_A
#define AD2_ADC_PIN        GPIO_PIN_02
#define AD2_ADC_CH         ADC_CH2
#define AD2_ADC_PGA_PIN    ADC_PGA_PIN_ADC1_PA2

#define AD3_ADC_PORT       GPIO_PORT_A
#define AD3_ADC_PIN        GPIO_PIN_03
#define AD3_ADC_CH         ADC_CH3
#define AD3_ADC_PGA_PIN    ADC_PGA_PIN_ADC1_PA3

#define AD4_ADC_PORT       GPIO_PORT_A
#define AD4_ADC_PIN        GPIO_PIN_04
#define AD4_ADC_CH         ADC_CH4
#define AD4_ADC_PGA_PIN    ADC_PGA_PIN_ADC1_PA4

#define AD5_ADC_PORT       GPIO_PORT_A
#define AD5_ADC_PIN        GPIO_PIN_05
#define AD5_ADC_CH         ADC_CH5
#define AD5_ADC_PGA_PIN    ADC_PGA_PIN_ADC1_PA5

#define AD6_ADC_PORT       GPIO_PORT_A
#define AD6_ADC_PIN        GPIO_PIN_06
#define AD6_ADC_CH         ADC_CH6
#define AD6_ADC_PGA_PIN    ADC_PGA_PIN_ADC1_PA6

#define AD7_ADC_PORT       GPIO_PORT_A
#define AD7_ADC_PIN        GPIO_PIN_07
#define AD7_ADC_CH         ADC_CH7
#define AD7_ADC_PGA_PIN    ADC_PGA_PIN_ADC1_PA7

#define AD_ADC_PGA_UNIT     (ADC_PGA1)
#define AD_ADC_PGA_GAIN     (ADC_PGA_GAIN_8)
#define AD_ADC_PGA_VSS      (ADC_PGA_VSS_AVSS)

/* ADC参数配置 */
#define ADC_VREF            (3.3F)
#define ADC_ACCURACY        (1UL << 12U)
#define ADC_TIMEOUT_VAL     (1000U)
#define ADC_SAMPLE_TIME     (0x20U)    /* 采样周期，加长适配高阻传感器 */

#define SAMPLER_MUX_CHANNELS   (8U)

/* ====================== 静态内部函数声明 ====================== */
static void GPIO_Y_Init(void);
static void GPIO_AS_Init(void);
static void ADC_Palm_Init(void);
static void AdcClockConfig(void);
static void SetSinglePin(uint8_t u8Port, uint16_t u16Pin, en_pin_level_t enLevel);
static void sampler_switch_cols(uint8_t AREA,uint8_t N);
static void Y_Channel_AllLow(void);
static void AS_Chip_Enable(en_as_chip_t enChip);
static void AS_Channel_Select(en_as_channel_t enCh);
static void AS_AllChip_Disable(void);
static int32_t AdcPollingSample(uint8_t adx, uint16_t *pu16AdcVal);

/* ====================== 管脚映射表：Y编号 -> PORT/PIN ====================== */
typedef struct
{
    uint8_t 			pstPort;
    uint16_t      u16Pin;
} stc_y_pin_map_t;

static const stc_y_pin_map_t m_stYPinMap[] =
{
		// 扫描顺序：y0-y22 （下标0 = Y0，下标22 = Y22）
		{PIN_TY0_PORT,  PIN_TY0_PIN},  // Y0  0
		{PIN_TY1_PORT,  PIN_TY1_PIN},  // Y1  1
		{PIN_TY2_PORT,  PIN_TY2_PIN},  // Y2  2
		{PIN_TY3_PORT,  PIN_TY3_PIN},  // Y3  3
		{PIN_TY4_PORT,  PIN_TY4_PIN},  // Y4  4
		{PIN_TY5_PORT,  PIN_TY5_PIN},  // Y5  5
		{PIN_TY6_PORT,  PIN_TY6_PIN},  // Y6  6
		{PIN_TY7_PORT,  PIN_TY7_PIN},  // Y7  7
		{PIN_TY8_PORT,  PIN_TY8_PIN},  // Y8  8
		{PIN_TY9_PORT,  PIN_TY9_PIN},  // Y9  9
		{PIN_TY10_PORT, PIN_TY10_PIN}, // Y10 10
		{PIN_TY11_PORT, PIN_TY11_PIN}, // Y11 11
		{PIN_TY12_PORT, PIN_TY12_PIN}, // Y12 12
		{PIN_TY13_PORT, PIN_TY13_PIN}, // Y13 13
		{PIN_TY14_PORT, PIN_TY14_PIN}, // Y14 14
		{PIN_TY15_PORT, PIN_TY15_PIN}, // Y15 15
		{PIN_TY16_PORT, PIN_TY16_PIN}, // Y16 16
		{PIN_TY17_PORT, PIN_TY17_PIN}, // Y17 17
};
#define Y_CH_TOTAL_NUM  (sizeof(m_stYPinMap)/sizeof(stc_y_pin_map_t))

/**
 * @brief 底层驱动总初始化：Y输出IO + AS控制IO + PALM ADC
 */
void ADC_SAMPLE_Init(void)
{
		/* 释放PB3(PY10/Y10) JTDO，PB4(PY11/Y11) NJTRST，PA15(Y6) JTDI，保留SWD(PA13 PA14)可用 */
		GPIO_SetDebugPort(GPIO_PIN_TDO, DISABLE);   /* PB3  */
		GPIO_SetDebugPort(GPIO_PIN_TRST, DISABLE);  /* PB4  */
		GPIO_SetDebugPort(GPIO_PIN_TDI, DISABLE);   /* PA15  */
    GPIO_Y_Init();
    GPIO_AS_Init();
    ADC_Palm_Init();

    /* 上电默认全部关闭 */
    Y_Channel_AllLow();
    AS_AllChip_Disable();
}

/**
 * @brief Y0~Y34全部推挽输出初始化，默认低电平
 */
static void GPIO_Y_Init(void)
{
    stc_gpio_init_t stcGpioInit;
    uint8_t u8Idx;
    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinAttr = PIN_ATTR_DIGITAL;
    stcGpioInit.u16PinDrv = PIN_HIGH_DRV;
    stcGpioInit.u16PinDir = PIN_DIR_OUT;
		stcGpioInit.u16PullUp = PIN_PU_ON;
		stcGpioInit.u16PinOutputType = PIN_OUT_TYPE_CMOS;

    for(u8Idx = 0; u8Idx < Y_CH_TOTAL_NUM; u8Idx++)
    {
        GPIO_Init(m_stYPinMap[u8Idx].pstPort, m_stYPinMap[u8Idx].u16Pin, &stcGpioInit);
				GPIO_OutputCmd(m_stYPinMap[u8Idx].pstPort, m_stYPinMap[u8Idx].u16Pin,ENABLE);
				SetSinglePin(m_stYPinMap[u8Idx].pstPort, m_stYPinMap[u8Idx].u16Pin, PIN_LOW);
    }
}

/**
 * @brief AS模拟开关控制管脚初始化（AS_EN1~7 / AS_S1~3 推挽输出）
 */
static void GPIO_AS_Init(void)
{
    stc_gpio_init_t stcGpioInit;
    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinAttr = PIN_ATTR_DIGITAL;
    stcGpioInit.u16PinDrv = PIN_HIGH_DRV;
    stcGpioInit.u16PinDir = PIN_DIR_OUT;
		stcGpioInit.u16PinOutputType = PIN_OUT_TYPE_CMOS;
	
    /* AS_EN */
		GPIO_Init(AS_EN0_PORT, AS_EN0_PIN, &stcGpioInit);
    /* AS_S 通道选择 */
    GPIO_Init(AS_S1_PORT, AS_S1_PIN, &stcGpioInit);
    GPIO_Init(AS_S2_PORT, AS_S2_PIN, &stcGpioInit);
    GPIO_Init(AS_S3_PORT, AS_S3_PIN, &stcGpioInit);

    /* 默认全部关闭 */
    AS_AllChip_Disable();
}

/**
 * @brief ADC时钟配置（对齐原厂例程规范）
 * @note  适配200MHz系统主频，PCLK2=50MHz(ADC模拟时钟)，PCLK4=100MHz(数字接口)，比例2:1符合规格
 */
static void AdcClockConfig(void)
{
    /* 选择系统PCLK作为ADC时钟源 */
    CLK_SetPeriClockSrc(CLK_PERIPHCLK_PCLK);
}

/**
 * @brief PALM多通道ADC初始化（对齐原厂DDL标准流程）
 */
static void ADC_Palm_Init(void)
{
    stc_adc_init_t stcAdcInit;
    stc_gpio_init_t stcGpioInit;
    uint8_t u8Ch;

    /* 1. ADC时钟配置 */
    AdcClockConfig();
    
    /* 2. 使能ADC外设时钟 */
    FCG_Fcg3PeriphClockCmd(ADC_PERIPH_CLK, ENABLE);

    /* 3. ADC内核初始化 */
    (void)ADC_StructInit(&stcAdcInit);
    (void)ADC_Init(ADC_UNIT, &stcAdcInit);

    /* 4. 配置所有模拟输入引脚 */
    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinAttr = PIN_ATTR_ANALOG;
    GPIO_Init(AD0_ADC_PORT, AD0_ADC_PIN, &stcGpioInit);

		ADC_ChCmd(ADC_UNIT, ADC_SEQ, AD0_ADC_CH, DISABLE);
		ADC_ChCmd(ADC_UNIT, ADC_SEQ, AD1_ADC_CH, DISABLE);
		ADC_ChCmd(ADC_UNIT, ADC_SEQ, AD2_ADC_CH, DISABLE);
		ADC_ChCmd(ADC_UNIT, ADC_SEQ, AD3_ADC_CH, DISABLE);
		ADC_ChCmd(ADC_UNIT, ADC_SEQ, AD4_ADC_CH, DISABLE);
		ADC_ChCmd(ADC_UNIT, ADC_SEQ, AD5_ADC_CH, DISABLE);
		ADC_ChCmd(ADC_UNIT, ADC_SEQ, AD6_ADC_CH, DISABLE);
		ADC_ChCmd(ADC_UNIT, ADC_SEQ, AD7_ADC_CH, DISABLE);
    /* 5. 统一配置所有通道的采样时间 + 硬件平均（全局配置，通道开关不影响） */
    for (u8Ch = AD0_ADC_CH; u8Ch <= AD7_ADC_CH; u8Ch++) {
        ADC_SetSampleTime(ADC_UNIT, u8Ch, ADC_SAMPLE_TIME);
    }
    ADC_PGA_Config(ADC_UNIT, AD_ADC_PGA_UNIT, AD_ADC_PGA_GAIN, AD_ADC_PGA_VSS);
    ADC_PGA_Cmd(ADC_UNIT, AD_ADC_PGA_UNIT, ENABLE);
}

/* ====================== Y通道操作函数 ====================== */
static void SetSinglePin(uint8_t u8Port, uint16_t u16Pin, en_pin_level_t enLevel)
{
    if(PIN_HIGH == enLevel)
    {
        GPIO_SetPins(u8Port, u16Pin);
    }
    else
    {
        GPIO_ResetPins(u8Port, u16Pin);
    }
}

static void sampler_switch_cols(uint8_t AREA,uint8_t N)
{
    uint8_t i;

		switch(AREA)
		{
				case TAC_AREA_THUMB_DIP:
				case TAC_AREA_THUMB_MCP:
				case TAC_AREA_INDEX_DIP:
				case TAC_AREA_INDEX_PIP:
				case TAC_AREA_INDEX_MCP:
				case TAC_AREA_MIDDLE_DIP:
				case TAC_AREA_MIDDLE_PIP:
				case TAC_AREA_MIDDLE_MCP:
				case TAC_AREA_RING_DIP:
				case TAC_AREA_RING_PIP:
				case TAC_AREA_RING_MCP:
				case TAC_AREA_LITTLE_DIP:
				case TAC_AREA_LITTLE_PIP:
				case TAC_AREA_LITTLE_MCP:
				case TAC_AREA_PALM1:
				case TAC_AREA_PALM2:
				for (i = TacAreaRange[AREA].col_start; i <= TacAreaRange[AREA].col_end; ++i) 
				{
						SetSinglePin(m_stYPinMap[i].pstPort,m_stYPinMap[i].u16Pin,((i == N) ? PIN_HIGH : PIN_LOW));
				}
				break;
				default:break;
		}
}

static void Y_Channel_AllLow(void)
{
    uint8_t u8Idx;
    for(u8Idx = 0; u8Idx < Y_CH_TOTAL_NUM; u8Idx++)
    {
        GPIO_ResetPins(m_stYPinMap[u8Idx].pstPort, m_stYPinMap[u8Idx].u16Pin);
    }
}

/* ====================== AS模拟开关操作函数 ====================== */
static void AS_Chip_Enable(en_as_chip_t enChip)
{
    en_pin_level_t enPin = PIN_LOW;
    switch(enChip)
    {
				case AS_CHIP_0: SetSinglePin(AS_EN0_PORT, AS_EN0_PIN, enPin); break;
        default: break;
    }
}

static void AS_Channel_Select(en_as_channel_t enCh)
{
    /* S3 S2 S1 三位控制位 */
    SetSinglePin(AS_S1_PORT, AS_S1_PIN, (enCh & 0x01U) ? PIN_HIGH : PIN_LOW);
    SetSinglePin(AS_S2_PORT, AS_S2_PIN, (enCh & 0x02U) ? PIN_HIGH : PIN_LOW);
    SetSinglePin(AS_S3_PORT, AS_S3_PIN, (enCh & 0x04U) ? PIN_HIGH : PIN_LOW);
}

static void AS_AllChip_Disable(void)
{
		SetSinglePin(AS_EN0_PORT, AS_EN0_PIN, PIN_HIGH);
}

/* ====================== PALM ADC采集函数 ====================== */
/**
 * @brief 轮询ADC单通道采集（完全对齐原厂例程逻辑）
 * @param  adx         ADC通道号
 * @param  pu16AdcVal  采样结果输出
 * @retval LL_OK：成功，LL_ERR：超时失败
 */
static int32_t AdcPollingSample(uint8_t adx, uint16_t *pu16AdcVal)
{
    int32_t iRet = LL_ERR;
    __IO uint32_t u32TimeCount = 0UL;
    static uint8_t u8CurEnabledCh = 0xFFU; /* 缓存当前已使能的通道，0xFF表示无 */

    /* 通道切换：仅当目标通道与当前使能通道不同时，重新配置 */
    if (adx != u8CurEnabledCh) {
				ADC_PGA_SelectInputSrc(ADC_UNIT, (uint32_t)(1<<adx));
        /* 关闭所有7个通道 */
        ADC_ChCmd(ADC_UNIT, ADC_SEQ, AD0_ADC_CH, DISABLE);
				ADC_ChCmd(ADC_UNIT, ADC_SEQ, AD1_ADC_CH, DISABLE);
				ADC_ChCmd(ADC_UNIT, ADC_SEQ, AD2_ADC_CH, DISABLE);
				ADC_ChCmd(ADC_UNIT, ADC_SEQ, AD3_ADC_CH, DISABLE);
				ADC_ChCmd(ADC_UNIT, ADC_SEQ, AD4_ADC_CH, DISABLE);
				ADC_ChCmd(ADC_UNIT, ADC_SEQ, AD5_ADC_CH, DISABLE);
				ADC_ChCmd(ADC_UNIT, ADC_SEQ, AD6_ADC_CH, DISABLE);
				ADC_ChCmd(ADC_UNIT, ADC_SEQ, AD7_ADC_CH, DISABLE);
        /* 仅使能目标通道 */
        ADC_ChCmd(ADC_UNIT, ADC_SEQ, adx, ENABLE);
        u8CurEnabledCh = adx;
        /* 通道切换后加1us稳定延时，确保多路开关建立完成 */
        DDL_DelayUS(1);
    }
    /* 启动序列A转换 */
    ADC_Start(ADC_UNIT);
    do
    {
        if(SET == ADC_GetStatus(ADC_UNIT, ADC_EOC_FLAG))
        {
            ADC_ClearStatus(ADC_UNIT, ADC_EOC_FLAG);
            *pu16AdcVal = ADC_GetValue(ADC_UNIT, adx);
            iRet = LL_OK;
            break;
        }
    } while (u32TimeCount++ < ADC_TIMEOUT_VAL);

    if(LL_ERR == iRet)
    {
        ADC_Stop(ADC_UNIT);
    }
    return iRet;
}

/**
 * @brief X通道模拟开关选择
 */
static void sampler_select_mux(uint8_t AREA, uint8_t u8XIndex)
{
    en_as_chip_t mux_index;
    en_as_channel_t channel;
		
    if (u8XIndex >= ALL_ROW) {
        AS_AllChip_Disable();
        return;
    }
		switch(AREA)
		{
			case TAC_AREA_THUMB_DIP:
			case TAC_AREA_THUMB_MCP:
				break;
			case TAC_AREA_INDEX_DIP:
			case TAC_AREA_INDEX_PIP:
			case TAC_AREA_INDEX_MCP:
				break;
			case TAC_AREA_MIDDLE_DIP:
			case TAC_AREA_MIDDLE_PIP:
			case TAC_AREA_MIDDLE_MCP:
				break;
			case TAC_AREA_RING_DIP:
			case TAC_AREA_RING_PIP:
			case TAC_AREA_RING_MCP:
				break;
			case TAC_AREA_LITTLE_DIP:
				if(u8XIndex>6)
				{
					mux_index = AS_CHIP_0;
					channel = (en_as_channel_t)((u8XIndex-7) % SAMPLER_MUX_CHANNELS);
				}
				else{
				  AS_AllChip_Disable();
					return;
				}
				break;
			case TAC_AREA_LITTLE_PIP:
			case TAC_AREA_LITTLE_MCP:
				break;
			case TAC_AREA_PALM1:
				break;
			case TAC_AREA_PALM2:
				break;
			default:break;
		}
    AS_AllChip_Disable();
    AS_Channel_Select(channel);
		AS_Chip_Enable(mux_index);
}

/* ====================== 对外采集函数 ====================== */
/**
 * @brief 轮询采集指定区域的完整触觉帧
 * @param  AREA   区域编号
 * @param  row    区域行数
 * @param  col    区域列数
 * @param  buffer 输出二维数组缓冲区
 * @retval 采集到的总数据字节数
 */
#if(DATA_FRAME_BYTE_NUM)
uint16_t SampleGetFrame(uint8_t AREA, uint8_t row, uint8_t col, uint16_t buffer[][col])
{
    int i;
    int j;
		uint16_t length=0;
		const tac_data_cfg_t* pTacMaskData = GetTacMaskData();
		int32_t iRet = LL_ERR;
    for (i = TacAreaRange[AREA].col_start; i <= TacAreaRange[AREA].col_end; i++) {
        sampler_switch_cols(AREA,(uint8_t)i);
        for (j = TacAreaRange[AREA].row_start; j <= TacAreaRange[AREA].row_end; j++) {
            uint16_t value=0;
						sampler_select_mux(AREA,(uint8_t)j);
						DDL_DelayUS(1);
						switch(AREA)
						{
							case TAC_AREA_THUMB_DIP:
								break;
							case TAC_AREA_THUMB_MCP:
								break;
							case TAC_AREA_INDEX_DIP:
								break;
							case TAC_AREA_INDEX_PIP:
								break;
							case TAC_AREA_INDEX_MCP:
								break;
							case TAC_AREA_MIDDLE_DIP:
								break;
							case TAC_AREA_MIDDLE_PIP:
								break;
							case TAC_AREA_MIDDLE_MCP:
								break;
							case TAC_AREA_RING_DIP:
								break;
							case TAC_AREA_RING_PIP:
								break;
							case TAC_AREA_RING_MCP:
								break;
							case TAC_AREA_LITTLE_DIP:
								if(pTacMaskData->little_dip[j-TacAreaRange[AREA].row_start][i-TacAreaRange[AREA].col_start]==0x0000)
								{
									value=0;
								}
								else{
									if(j<=6)
									{
										iRet = AdcPollingSample(j,&value);
									}
									else{
										iRet = AdcPollingSample(AD7_ADC_CH,&value);
									}
								}
								break;
							case TAC_AREA_LITTLE_PIP:
								break;
							case TAC_AREA_LITTLE_MCP:
								break;
							case TAC_AREA_PALM1:
								break;
							case TAC_AREA_PALM2:
								break;
							default:break;
						}
						if(iRet==LL_ERR)
						{
							buffer[j-TacAreaRange[AREA].row_start][i-TacAreaRange[AREA].col_start] = 0;
						}
						else{
							uint8_t p=0,q=0;
							p = j-TacAreaRange[AREA].row_start;
							q = i-TacAreaRange[AREA].col_start;
							buffer[p][q] = (value);
						}
        }
    }
		length = col*row;
    Y_Channel_AllLow();
    AS_AllChip_Disable();
		return length;
}
#else
uint16_t SampleGetFrame(uint8_t AREA, uint8_t row, uint8_t col, uint8_t buffer[][col])
{
    int i;
    int j;
		uint16_t length=0;
		int32_t iRet = LL_ERR;
		const tac_data_cfg_t* pTacMaskData = GetTacMaskData();
    for (i = TacAreaRange[AREA].col_start; i <= TacAreaRange[AREA].col_end; i++) {
        sampler_switch_cols(AREA,(uint8_t)i);
        for (j = TacAreaRange[AREA].row_start; j <= TacAreaRange[AREA].row_end; j++) {
            uint16_t value=0;
						sampler_select_mux(AREA,(uint8_t)j);
						DDL_DelayUS(1);
						switch(AREA)
						{
							case TAC_AREA_THUMB_DIP:break;
							case TAC_AREA_THUMB_MCP:break;
							case TAC_AREA_INDEX_DIP:break;
							case TAC_AREA_INDEX_PIP:break;
							case TAC_AREA_INDEX_MCP:break;
							case TAC_AREA_MIDDLE_DIP:break;
							case TAC_AREA_MIDDLE_PIP:break;
							case TAC_AREA_MIDDLE_MCP:break;
							case TAC_AREA_RING_DIP:break;
							case TAC_AREA_RING_PIP:break;
							case TAC_AREA_RING_MCP:break;
							case TAC_AREA_LITTLE_DIP:
								if(pTacMaskData->little_dip[j-TacAreaRange[AREA].row_start][i-TacAreaRange[AREA].col_start]==0x0000)
								{
									value=0;
								}
								else{
									if(j<=6)
									{
										iRet = AdcPollingSample(j,&value);
									}
									else{
										iRet = AdcPollingSample(AD7_ADC_CH,&value);
									}
								}
								break;
							case TAC_AREA_LITTLE_PIP:break;
							case TAC_AREA_LITTLE_MCP:break;
							case TAC_AREA_PALM1:break;
							case TAC_AREA_PALM2:break;
							default:break;
						}
						if(iRet==LL_ERR)
						{
							buffer[j-TacAreaRange[AREA].row_start][i-TacAreaRange[AREA].col_start] = 0;
						}
						else{
							uint8_t p=0,q=0;
							p = j-TacAreaRange[AREA].row_start;
							q = i-TacAreaRange[AREA].col_start;
							buffer[p][q] = (value>>4)&0XFF;
						}
        }
    }
		length = col*row;
    Y_Channel_AllLow();
    AS_AllChip_Disable();
		return length;
}
#endif


