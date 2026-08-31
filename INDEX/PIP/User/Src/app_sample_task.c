/**
 ******************************************************************************
 * @file    app_sample_task.c
 * @brief   源文件
 ******************************************************************************
 */
#include "app_sample_task.h"
#include <string.h>
#include "adc_sample.h"
#include "app_usart_task.h"
#include "app_tac_config.h"
#include "main.h"
/* ====================== 静态内存缓冲区（全局静态RAM，不占用堆） ====================== */
/* 1. 采集任务静态栈 & TCB控制块 */
static StackType_t m_auSampleTaskStack[SAMPLE_TASK_STACK_SIZE];
static StaticTask_t m_stSampleTaskTcb;

/* ====================== 对外全局变量定义 ====================== */
TaskHandle_t        m_hSampleTask = NULL;

/* ====================== 私有静态局部变量 ====================== */

/* ====================== 内部函数前置声明 ====================== */
static void Sample_TaskEntry(void *pvParam);
static void Sample_DoCollect(void);
#if(DATA_FRAME_BYTE_NUM)
static void Sample_CalibrateZero(uint8_t row, uint8_t col, uint16_t frame[][col], uint16_t calib[][col]);
#else
static void Sample_CalibrateZero(uint8_t row, uint8_t col, uint8_t frame[][col], uint8_t calib[][col]);
#endif
static void Sample_Caliber(void);
/**
 * @brief 静态创建采集任务、消息队列、数据互斥锁
 */
void APP_Sample_TaskCreate(void)
{
    /* 底层ADC硬件初始化 */
		ADC_SAMPLE_Init();

    /* 静态创建采集主任务 */
    m_hSampleTask = xTaskCreateStatic(
        Sample_TaskEntry,
        "SampleTask",
        SAMPLE_TASK_STACK_SIZE,
        NULL,
        SAMPLE_TASK_PRIORITY,
        m_auSampleTaskStack,
        &m_stSampleTaskTcb
    );
}


/**
 * @brief 采集任务主循环入口
 */
static void Sample_TaskEntry(void *pvParam)
{
		/* 采集使能时执行ADC采样 */
		Sample_Caliber();
    while(1)
    {
				/* 采集使能时执行ADC采样 */
				Sample_DoCollect();
				vTaskDelay(10);
    }
}

/**
 * @brief 执行单次多路ADC采集
 */
static void Sample_DoCollect(void)
{
		tac_data_cfg_t* pTacData = GetTacDataCfg();
		tac_data_cfg_t* pTacCalib = GetTacCalibData();
		uint8_t tac_id = TAC_AREA_LITTLE_PIP;
#if(DATA_FRAME_BYTE_NUM)
		uint16_t (*pBuff1)[TacAreaRange[tac_id].col_end-TacAreaRange[tac_id].col_start+1] = pTacData->little_pip;
		uint16_t (*pBuff2)[TacAreaRange[tac_id].col_end-TacAreaRange[tac_id].col_start+1] = pTacCalib->little_pip;
#else
		uint8_t (*pBuff1)[TacAreaRange[tac_id].col_end-TacAreaRange[tac_id].col_start+1] = pTacData->little_pip;
		uint8_t (*pBuff2)[TacAreaRange[tac_id].col_end-TacAreaRange[tac_id].col_start+1] = pTacCalib->little_pip;
#endif
		SampleGetFrame(tac_id,
									TacAreaRange[tac_id].row_end-TacAreaRange[tac_id].row_start+1,
									TacAreaRange[tac_id].col_end-TacAreaRange[tac_id].col_start+1,
									pBuff1);
		Sample_CalibrateZero(TacAreaRange[tac_id].row_end-TacAreaRange[tac_id].row_start+1, 
												 TacAreaRange[tac_id].col_end-TacAreaRange[tac_id].col_start+1, 
												 pBuff1, pBuff2);
}

/**
 * @brief 执行单次多路ADC采集
 */
static void Sample_Caliber(void)
{
		tac_data_cfg_t* pTacCalib = GetTacCalibData();
		uint8_t tac_id = TAC_AREA_LITTLE_PIP;
#if(DATA_FRAME_BYTE_NUM)
		uint16_t (*pBuff2)[TacAreaRange[tac_id].col_end-TacAreaRange[tac_id].col_start+1] = pTacCalib->little_pip;
#else
		uint8_t (*pBuff2)[TacAreaRange[tac_id].col_end-TacAreaRange[tac_id].col_start+1] = pTacCalib->little_pip;
#endif
		SampleGetFrame(tac_id,
									TacAreaRange[tac_id].row_end-TacAreaRange[tac_id].row_start+1,
									TacAreaRange[tac_id].col_end-TacAreaRange[tac_id].col_start+1,
									pBuff2);
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
					value = (value > calib[j][i]) ? (value - calib[j][i]) : 0;
					frame[j][i] = (uint8_t)(value&0xff);
			}
    }
}
#endif

