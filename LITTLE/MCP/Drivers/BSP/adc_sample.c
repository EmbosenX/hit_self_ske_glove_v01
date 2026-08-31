/*******************************************************************************
 * @file        adc_sample.c
 * @brief       Y0~Y34输出控制 + AS模拟开关 + PALM多通道ADC采集底层驱动
 * @author      
 * @date        2026-07-21
 * @version     V1.1  对齐原厂DDL规范优化ADC底层
 ******************************************************************************/
#include "adc_sample.h"
#include <string.h>
#include "app_tac_config.h"
#include "main.h"
#include "FreeRTOS.h"

/*所有的行列*/
#define ALL_ROW			2
#define ALL_COL 		8
#define SAMPLER_MUX_CHANNELS   (8U)


static void GPIO_Y_Init(void);
static void Y_Channel_AllLow(void);

const stc_y_pin_map_t m_stYPinMap[] =
{
		{Y0_PORT,  Y0_PIN},  // Y0
		{Y1_PORT,  Y1_PIN},  // Y1
		{Y2_PORT,  Y2_PIN},  // Y2 
		{Y3_PORT,  Y3_PIN},  // Y3
		{Y4_PORT,  Y4_PIN},  // Y4
		{Y5_PORT,  Y5_PIN},  // Y5
		{Y6_PORT,  Y6_PIN},  // Y6
		{Y7_PORT,  Y7_PIN},  // Y7
		{Y8_PORT,  Y8_PIN},  // Y8
};
/**
 * @brief 底层驱动总初始化：Y输出IO + AS控制IO + PALM ADC
 */
void ADC_SAMPLE_Init(void)
{
		/* 释放PB3(PY10/Y10) JTDO，PB4(PY11/Y11) NJTRST，PA15(Y6) JTDI，保留SWD(PA13 PA14)可用 */

    GPIO_Y_Init();
		Adc_Init();
    /* 上电默认全部关闭 */
    Y_Channel_AllLow();
}

/**
 * @brief Y0~Y34全部推挽输出初始化，默认低电平
 */
static void GPIO_Y_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    uint8_t u8Idx;
		__HAL_RCC_GPIOF_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    for(u8Idx = 0; u8Idx < Y_CH_TOTAL_NUM; u8Idx++)
    {
				GPIO_InitStruct.Pin = m_stYPinMap[u8Idx].u16Pin;
        HAL_GPIO_Init(m_stYPinMap[u8Idx].pstPort, &GPIO_InitStruct);
				HAL_GPIO_WritePin(m_stYPinMap[u8Idx].pstPort, m_stYPinMap[u8Idx].u16Pin, GPIO_PIN_RESET);
    }
}

static void Y_Channel_AllLow(void)
{
    uint8_t u8Idx;
    for(u8Idx = 0; u8Idx < Y_CH_TOTAL_NUM; u8Idx++)
    {
        HAL_GPIO_WritePin(m_stYPinMap[u8Idx].pstPort, m_stYPinMap[u8Idx].u16Pin, GPIO_PIN_RESET);
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
						HAL_GPIO_WritePin(m_stYPinMap[i].pstPort,m_stYPinMap[i].u16Pin,((i == N) ? GPIO_PIN_SET : GPIO_PIN_RESET));
				}
				break;
				default:break;
		}
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
		int32_t iRet = 0;
    for (i = TacAreaRange[AREA].col_start; i <= TacAreaRange[AREA].col_end; i++) {
        sampler_switch_cols(AREA,(uint8_t)i);
        for (j = TacAreaRange[AREA].row_start; j <= TacAreaRange[AREA].row_end; j++) {
            uint16_t value=0;
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
								break;
							case TAC_AREA_LITTLE_PIP:
								if(pTacMaskData->little_dip[j-TacAreaRange[AREA].row_start][i-TacAreaRange[AREA].col_start]==0x0000)
								{
									value=0;
								}
								else{
										if(j==0)
										{
											iRet = Adc_GetRawValue(ADC_CH_PGA1);
										}
										else if(j==1)
										{
											iRet = Adc_GetRawValue(ADC_CH_PGA2);
										}
										else{}
								}
								break;
							case TAC_AREA_LITTLE_MCP:
								break;
							case TAC_AREA_PALM1:
								break;
							case TAC_AREA_PALM2:
								break;
							default:break;
						}
						if(iRet==0)
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
		return length;
}
#else
uint16_t SampleGetFrame(uint8_t AREA, uint8_t row, uint8_t col, uint8_t buffer[][col])
{
    int i;
    int j;
		uint16_t length=0;
		const tac_data_cfg_t* pTacMaskData = GetTacMaskData();
    for (i = TacAreaRange[AREA].col_start; i <= TacAreaRange[AREA].col_end; i++) {
        sampler_switch_cols(AREA,(uint8_t)i);
        for (j = TacAreaRange[AREA].row_start; j <= TacAreaRange[AREA].row_end; j++) {
            uint16_t value=0;
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
							case TAC_AREA_LITTLE_DIP:break;
							case TAC_AREA_LITTLE_PIP:break;
							case TAC_AREA_LITTLE_MCP:
								if(pTacMaskData->little_pip[j-TacAreaRange[AREA].row_start][i-TacAreaRange[AREA].col_start]==0x0000)
								{
									value=0;
								}
								else{
										if(j==0)
										{
											value = Adc_GetRawValue(ADC_CH_PGA1);
										}
										else if(j==1)
										{
											value = Adc_GetRawValue(ADC_CH_PGA2);
										}
										else{}
								}
								break;
							case TAC_AREA_PALM1:break;
							case TAC_AREA_PALM2:break;
							default:break;
						}
						uint8_t p=0,q=0;
						p = j-TacAreaRange[AREA].row_start;
						q = i-TacAreaRange[AREA].col_start;
						buffer[p][q] = (value>>4)&0XFF;
        }
    }
		length = col*row;
    Y_Channel_AllLow();
		return length;
}
#endif


/**
 * @brief 执行单次多路ADC采集
 */
void Sample_DoCollect(void)
{
		tac_data_cfg_t* pTacData = GetTacDataCfg();
		tac_data_cfg_t* pTacCalib = GetTacCalibData();
		SampleGetFrame(TAC_AREA_LITTLE_PIP,
									TacAreaRange[TAC_AREA_LITTLE_PIP].row_end-TacAreaRange[TAC_AREA_LITTLE_PIP].row_start+1,
									TacAreaRange[TAC_AREA_LITTLE_PIP].col_end-TacAreaRange[TAC_AREA_LITTLE_PIP].col_start+1,
									pTacData->little_pip);
		Sample_CalibrateZero(TacAreaRange[TAC_AREA_LITTLE_PIP].row_end-TacAreaRange[TAC_AREA_LITTLE_PIP].row_start+1, 
												 TacAreaRange[TAC_AREA_LITTLE_PIP].col_end-TacAreaRange[TAC_AREA_LITTLE_PIP].col_start+1, 
												 pTacData->little_pip, pTacCalib->little_pip);
}

/**
 * @brief 执行单次多路ADC采集
 */
void Sample_Caliber(void)
{
		tac_data_cfg_t* pTacCalib = GetTacCalibData();
		SampleGetFrame(TAC_AREA_LITTLE_PIP,
									TacAreaRange[TAC_AREA_LITTLE_PIP].row_end-TacAreaRange[TAC_AREA_LITTLE_PIP].row_start+1,
									TacAreaRange[TAC_AREA_LITTLE_PIP].col_end-TacAreaRange[TAC_AREA_LITTLE_PIP].col_start+1,
									pTacCalib->little_pip);
}
/**
 * @brief 传感器零点校准流程
 */
#if(DATA_FRAME_BYTE_NUM)
static void Sample_CalibrateZero(uint8_t row, uint8_t col, uint16_t frame[][col], uint16_t calib[][col])
{
		const uint8_t CALIB_ERR = 10;
    for (int i = 0; i < col; i++) 
		{
			for(int j = 0; j < row; j++)
			{
					uint16_t value = frame[j][i];
					value = (value > (calib[j][i]+CALIB_ERR)) ? (value - (calib[j][i]+CALIB_ERR)) : 0;
					frame[j][i] = value;
			}
    }
}
#else
static void Sample_CalibrateZero(uint8_t row, uint8_t col, uint8_t frame[][col], uint8_t calib[][col])
{
    for (int i = 0; i < col; i++) 
		{
			for(int j = 0; j < row; j++)
			{
					uint16_t value = frame[j][i];
					value = (value > (calib[j][i]+10)) ? (value - calib[j][i]) : 0;
					frame[j][i] = (uint8_t)(value&0xff);
			}
    }
}
#endif

