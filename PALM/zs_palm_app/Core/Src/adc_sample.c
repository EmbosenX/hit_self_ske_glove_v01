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
#include "FreeRTOS.h"

/*所有的行列*/
#define ALL_ROW			18
#define ALL_COL 		23
#define SAMPLER_MUX_CHANNELS   (8U)

static void AS_Chip_Enable(en_as_chip_t enChip);
static void AS_AllChip_Disable(void);
static void AS_Channel_Select(en_as_channel_t enCh);
static void Y_Channel_AllLow(void);

const stc_y_pin_map_t m_stYPinMap[] =
{
		{GPIOB,  GPIO_PIN_12},  // Y0
		{GPIOB,  GPIO_PIN_13},  // Y1
		{GPIOB,  GPIO_PIN_11},  // Y2 
		{GPIOB,  GPIO_PIN_10},  // Y3
		{GPIOE,  GPIO_PIN_13},  // Y4
		{GPIOE,  GPIO_PIN_12},  // Y5
		{GPIOE,  GPIO_PIN_9},  // Y6
		
    {GPIOE,  GPIO_PIN_8},  // Y7
    {GPIOD,  GPIO_PIN_12},  // Y8 
    {GPIOD,  GPIO_PIN_8},  // Y9
    {GPIOD,  GPIO_PIN_9},  // Y10
    {GPIOD,  GPIO_PIN_10},  // Y11
    {GPIOD,  GPIO_PIN_11},  // Y12
    {GPIOD,  GPIO_PIN_14},  // Y13
		
    {GPIOD,  GPIO_PIN_15},  // Y14
    {GPIOE,  GPIO_PIN_15},  // Y15
    {GPIOE,  GPIO_PIN_14},  // Y16
    {GPIOE,  GPIO_PIN_11},  // Y17 
//    {GPIOA,  GPIO_PIN_1},  // Y18
//    {GPIOA,  GPIO_PIN_0},  // Y19
//    {GPIOA,  GPIO_PIN_4},  // Y20
//		
//    {GPIOA,  GPIO_PIN_5},  // Y21
//    {GPIOE,  GPIO_PIN_7},  // Y22
//    {GPIOB,  GPIO_PIN_2},  // Y23
//    {GPIOE,  GPIO_PIN_10},  // Y24
//    {GPIOC,  GPIO_PIN_13},  // Y25
//    {GPIOC,  GPIO_PIN_14},  // Y26
//    {GPIOC,  GPIO_PIN_15},  // Y27
//		
//    {GPIOA,  GPIO_PIN_3},  // Y31
//    {GPIOA,  GPIO_PIN_2},  // Y32
//    {GPIOA,  GPIO_PIN_7},  // Y33
//    {GPIOB,  GPIO_PIN_1},  // Y34
};

static void AS_Chip_Enable(en_as_chip_t enChip)
{
    GPIO_PinState enPin = GPIO_PIN_RESET;
    switch(enChip)
    {
				case AS_CHIP_1: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, enPin); break;
        case AS_CHIP_2: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, enPin); break;
        case AS_CHIP_3: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, enPin); break;
        case AS_CHIP_4: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, enPin); break;
        default: break;
    }
}
static void AS_AllChip_Disable(void)
{
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET);
}
static void AS_Channel_Select(en_as_channel_t enCh)
{
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, (enCh & 0x01U) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, (enCh & 0x02U) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, (enCh & 0x04U) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void Sample_Init(void)
{
	  uint8_t u8Idx;
    for(u8Idx = 0; u8Idx < Y_CH_TOTAL_NUM; u8Idx++)
    {
				HAL_GPIO_WritePin(m_stYPinMap[u8Idx].pstPort, m_stYPinMap[u8Idx].u16Pin, GPIO_PIN_RESET);
    }
    AS_AllChip_Disable();

}

static void Y_Channel_AllLow(void)
{
    uint8_t u8Idx;
    for(u8Idx = 0; u8Idx < Y_CH_TOTAL_NUM; u8Idx++)
    {
        HAL_GPIO_WritePin(m_stYPinMap[u8Idx].pstPort, m_stYPinMap[u8Idx].u16Pin, GPIO_PIN_RESET);
    }
}

static void sampler_switch_cols(uint8_t AREA,uint8_t N,uint8_t start,uint8_t end)
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
				for (i = start; i <= end; ++i) 
				{
						HAL_GPIO_WritePin(m_stYPinMap[i].pstPort,m_stYPinMap[i].u16Pin,((i == N) ? GPIO_PIN_SET : GPIO_PIN_RESET));
				}
				break;
				default:break;
		}
}
/**
 * @brief X通道模拟开关选择
 */
static void sampler_select_mux(uint8_t AREA, uint8_t u8XIndex)
{
    en_as_chip_t mux_index;
    en_as_channel_t channel;
		
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
			case TAC_AREA_LITTLE_PIP:
			case TAC_AREA_LITTLE_MCP:
				break;
			case TAC_AREA_PALM1:
				mux_index =(en_as_chip_t) ((TAC_COL_PALM1_END-u8XIndex) / SAMPLER_MUX_CHANNELS);
				channel = (en_as_channel_t)((TAC_COL_PALM1_END-u8XIndex) % SAMPLER_MUX_CHANNELS);
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
		int32_t iRet = 0;
    for (i = TacAreaRange[AREA].col_start; i <= TacAreaRange[AREA].col_end; i++) {
        sampler_switch_cols(AREA,(uint8_t)i);
        for (j = TacAreaRange[AREA].row_start; j <= TacAreaRange[AREA].row_end; j++) {
            uint16_t value=0;
						sampler_select_mux(AREA,(uint8_t)j);
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
								break;
							case TAC_AREA_LITTLE_MCP:
								break;
							case TAC_AREA_PALM1:
								if(pTacMaskData->palm1[j-TacAreaRange[AREA].row_start][i-TacAreaRange[AREA].col_start]==0x0000)
								{
									value=0;
								}
								else{
									iRet = AdcPollingSample(&value);
								}
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
    AS_AllChip_Disable();
		return length;
}
#else
uint16_t SampleGetFrame(uint8_t AREA, uint8_t row, uint8_t col, uint8_t buffer[][col])
{
    int i;
    int j;
		uint16_t length=0;
		int32_t iRet = 0;
		const tac_data_cfg_t* pTacMaskData = GetTacMaskData();
    for (i = TacAreaRange[AREA].col_start; i <= TacAreaRange[AREA].col_end; i++) {
				sampler_select_mux(AREA,(uint8_t)i);
        for (j = TacAreaRange[AREA].row_start; j <= TacAreaRange[AREA].row_end; j++) {
            uint16_t value=0;
						sampler_switch_cols(AREA,(uint8_t)j,TacAreaRange[AREA].row_start,TacAreaRange[AREA].row_end);
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
							case TAC_AREA_LITTLE_PIP:
							case TAC_AREA_LITTLE_MCP:
								break;
							case TAC_AREA_PALM1:
								if(pTacMaskData->palm1[j-TacAreaRange[AREA].row_start][i-TacAreaRange[AREA].col_start]==0x0000)
								{
									value=0;
								}
								else{
									iRet = AdcPollingSample(&value);
								}
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


/**
 * @brief 执行单次多路ADC采集
 */
void Sample_DoCollect(void)
{
		tac_data_cfg_t* pTacData = GetTacDataCfg();
		tac_data_cfg_t* pTacCalib = GetTacCalibData();
	
		SampleGetFrame(TAC_AREA_PALM1,
									TacAreaRange[TAC_AREA_PALM1].row_end-TacAreaRange[TAC_AREA_PALM1].row_start+1,
									TacAreaRange[TAC_AREA_PALM1].col_end-TacAreaRange[TAC_AREA_PALM1].col_start+1,
									pTacData->palm1);
		Sample_CalibrateZero(TacAreaRange[TAC_AREA_PALM1].row_end-TacAreaRange[TAC_AREA_PALM1].row_start+1, 
												 TacAreaRange[TAC_AREA_PALM1].col_end-TacAreaRange[TAC_AREA_PALM1].col_start+1, 
												 pTacData->palm1, pTacCalib->palm1);
}

/**
 * @brief 执行单次多路ADC采集
 */
void Sample_Caliber(void)
{
		tac_data_cfg_t* pTacCalib = GetTacCalibData();
		SampleGetFrame(TAC_AREA_PALM1,
									TacAreaRange[TAC_AREA_PALM1].row_end-TacAreaRange[TAC_AREA_PALM1].row_start+1,
									TacAreaRange[TAC_AREA_PALM1].col_end-TacAreaRange[TAC_AREA_PALM1].col_start+1,
									pTacCalib->palm1);
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
					value = (value > (calib[j][i]+10)) ? (value - (calib[j][i]+10)) : 0;
					frame[j][i] = (uint8_t)(value&0xff);
			}
    }
}
#endif

