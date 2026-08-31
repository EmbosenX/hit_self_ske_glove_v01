/**
 ******************************************************************************
 * @file    app_sample_task.h
 * @brief   源文件
 ******************************************************************************
 */
#ifndef __APP_SAMPLE_TASK_H__
#define __APP_SAMPLE_TASK_H__

#include "py32f0xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "adc_sample.h"
#include "main.h"
/* -------------------------- 任务配置宏 -------------------------- */
#define SAMPLE_TASK_STACK_SIZE      256U
#define SAMPLE_TASK_PRIORITY        (configMAX_PRIORITIES - 3)
#define SAMPLE_PERIOD_MS            10U    // 默认采集周期10ms

/* -------------------------- 采集缓存配置 -------------------------- */
#define SAMPLE_PLAT_NUM             (ALL_ROW*ALL_COL*DATA_FRAME_BYTE_NUM)     // 采集通道总数（手指触觉）

/* -------------------------- 采集完整数据帧结构体 -------------------------- */

/* -------------------------- 对外全局句柄与状态声明 -------------------------- */
extern TaskHandle_t        m_hSampleTask;

/* -------------------------- 对外业务API -------------------------- */
void APP_Sample_TaskCreate(void);

#endif /* __APP_SAMPLE_TASK_H__ */


