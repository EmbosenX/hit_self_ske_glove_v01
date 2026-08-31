/**
 ******************************************************************************
 * @file    app_imu_task.h
 * @brief   源文件
 ******************************************************************************
 */
#ifndef __APP_IMU_TASK_H__
#define __APP_IMU_TASK_H__

#include "hc32_ll.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "spi_imu.h"

/* -------------------------- 任务配置宏 -------------------------- */
#define IMU_TASK_STACK_SIZE         896U
#define IMU_TASK_PRIORITY           (configMAX_PRIORITIES - 3)
#define IMU_MSG_Q_DEPTH             10U
#define IMU_SAMPLE_PERIOD_MS        10U        // IMU采样周期10ms

/* 硬件IMU通道数量 */
#define IMU_CH_MAX_NUM              3U

/* -------------------------- 任务消息枚举 -------------------------- */
typedef enum
{
    IMU_MSG_INIT = 0U,          // IMU硬件初始化
    IMU_MSG_START_SAMPLE,       // 开启姿态采集
    IMU_MSG_STOP_SAMPLE,        // 停止姿态采集
    IMU_MSG_SENSOR_CALIB,       // IMU零点校准
    IMU_MSG_READ_FRAME,         // 读取完整姿态帧
    IMU_MSG_MODULE_RESET,       // SPI IMU模块复位
} en_imu_msg_t;

/* -------------------------- IMU运行状态机 -------------------------- */
typedef enum
{
    IMU_STATE_IDLE = 0U,
    IMU_STATE_INITING,
    IMU_STATE_SAMPLING,
    IMU_STATE_CALIBRATING
} en_imu_state_t;

/* -------------------------- 消息队列单元结构体 -------------------------- */
typedef struct
{
    en_imu_msg_t enMsgType;
    uint8_t      u8ChIndex;     // 指定IMU通道 1~3
    uint32_t     u32Param;
} stc_imu_msg_t;

/* -------------------------- 对外全局句柄与状态声明 -------------------------- */
extern TaskHandle_t        m_hImuTask;
extern QueueHandle_t       m_hImuMsgQueue;
extern SemaphoreHandle_t   m_hImuDataMutex;
extern en_imu_state_t      m_enImuState;
extern mpu9250_data_t      m_stImuFrame[IMU_CH_MAX_NUM];

/* -------------------------- 对外业务API -------------------------- */
void APP_Imu_TaskCreate(void);
void APP_Imu_SendMsg(en_imu_msg_t enMsg, uint8_t u8Ch, uint32_t u32Param);
uint8_t APP_Imu_IsSampling(void);
BaseType_t APP_Imu_GetFrame(uint8_t u8Ch, mpu9250_data_t *pstData, TickType_t xWait);

#endif /* __APP_IMU_TASK_H__ */


