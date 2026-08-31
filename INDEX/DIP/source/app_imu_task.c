/**
 ******************************************************************************
 * @file    app_imu_task.c
 * @brief   源文件
 ******************************************************************************
 */
#include "app_imu_task.h"

#if(IMU_FUN_ENABLE)
/* ====================== 静态内存缓冲区（全局静态RAM，不占用堆） ====================== */
/* 1. IMU采集任务静态栈 & TCB控制块 */
static StackType_t m_auImuTaskStack[IMU_TASK_STACK_SIZE];
static StaticTask_t m_stImuTaskTcb;

/* 2. 消息队列静态存储区 + 队列管理结构体 */
static uint8_t m_auImuQStorage[IMU_MSG_Q_DEPTH * sizeof(stc_imu_msg_t)];
static StaticQueue_t m_stImuMsgQueueBuf;

/* 3. IMU数据缓存互斥锁静态内存 */
static StaticSemaphore_t m_stImuDataMutexBuf;

/* ====================== 对外全局变量定义 ====================== */
TaskHandle_t        m_hImuTask = NULL;
QueueHandle_t       m_hImuMsgQueue = NULL;
SemaphoreHandle_t   m_hImuDataMutex = NULL;
en_imu_state_t      m_enImuState = IMU_STATE_IDLE;
mpu9250_data_t      m_stImuFrame[IMU_CH_MAX_NUM] = {0};

/* ====================== 私有静态局部变量 ====================== */
static TickType_t m_xLastWakeTick = 0U;
static float m_fDt = IMU_SAMPLE_PERIOD_MS / 1000.0f;

/* ====================== 内部函数前置声明 ====================== */
static void Imu_TaskEntry(void *pvParam);
static void Imu_MsgDispatch(stc_imu_msg_t *pstMsg);
static void Imu_DoMultiSample(void);
static void Imu_SingleCalibrate(uint8_t u8Ch);
#endif
/**
 * @brief 静态创建IMU任务、消息队列、数据互斥锁
 */
void APP_Imu_TaskCreate(void)
{
#if(IMU_FUN_ENABLE)
		IMU_SPI_Config();

    /* 依次初始化3个模块的MPU9250 + AK8963 */
    for (uint8_t i = 1; i <= 3; i++) {
        if (0 != MPU9250_Init(i)) {
            // MPU初始化失败处理
            while(1);
        }
				ak8963_debug_read_id(i);
        if (0 != AK8963_Init(i)) {
            // 磁力计初始化失败处理
            while(1);
        }
    }

    /* 静态创建消息队列 */
    m_hImuMsgQueue = xQueueCreateStatic(
        IMU_MSG_Q_DEPTH,
        sizeof(stc_imu_msg_t),
        m_auImuQStorage,
        &m_stImuMsgQueueBuf
    );

    /* 静态创建互斥锁，保护三路IMU全局姿态数据 */
    m_hImuDataMutex = xSemaphoreCreateMutexStatic(&m_stImuDataMutexBuf);

    /* 静态创建IMU主采集任务 */
    m_hImuTask = xTaskCreateStatic(
        Imu_TaskEntry,
        "ImuTask",
        IMU_TASK_STACK_SIZE,
        NULL,
        IMU_TASK_PRIORITY,
        m_auImuTaskStack,
        &m_stImuTaskTcb
    );

    /* 静态资源创建容错判断 */
    if((NULL == m_hImuTask) || (NULL == m_hImuMsgQueue) || (NULL == m_hImuDataMutex))
    {
        DDL_Printf("IMU Static Resource Create Failed!\r\n");
    }
#endif
}
#if(IMU_FUN_ENABLE)
/**
 * @brief 向IMU任务下发控制消息
 * @param enMsg 消息类型
 * @param u8Ch 目标IMU通道 1~3
 * @param u32Param 附加参数
 */
void APP_Imu_SendMsg(en_imu_msg_t enMsg, uint8_t u8Ch, uint32_t u32Param)
{
    stc_imu_msg_t stMsg;
    stMsg.enMsgType = enMsg;
    stMsg.u8ChIndex = u8Ch;
    stMsg.u32Param = u32Param;

    if(NULL != m_hImuMsgQueue)
    {
        xQueueSend(m_hImuMsgQueue, &stMsg, 0U);
    }
}

/**
 * @brief 查询当前IMU是否处于采集运行状态
 */
uint8_t APP_Imu_IsSampling(void)
{
    uint8_t u8Ret;
    taskENTER_CRITICAL();
    u8Ret = (IMU_STATE_SAMPLING == m_enImuState) ? 1U : 0U;
    taskEXIT_CRITICAL();
    return u8Ret;
}

/**
 * @brief 外部任务安全读取指定通道一帧完整IMU姿态数据（互斥锁保护）
 * @param u8Ch IMU通道 1~3
 * @param pstData 外部接收数据缓存
 * @param xWait 获取互斥锁超时时间
 * @retval pdPASS 读取成功 / pdFALSE 超时失败
 */
BaseType_t APP_Imu_GetFrame(uint8_t u8Ch, mpu9250_data_t *pstData, TickType_t xWait)
{
    BaseType_t xRet = pdFALSE;
    if((NULL == pstData) || (u8Ch < 1U) || (u8Ch > IMU_CH_MAX_NUM))
    {
        return pdFALSE;
    }

    if(pdPASS == xSemaphoreTake(m_hImuDataMutex, xWait))
    {
        memcpy(pstData, &m_stImuFrame[u8Ch - 1], sizeof(mpu9250_data_t));
        xSemaphoreGive(m_hImuDataMutex);
        xRet = pdPASS;
    }
    return xRet;
}

/**
 * @brief IMU采集任务主循环入口
 */
static void Imu_TaskEntry(void *pvParam)
{
    stc_imu_msg_t stRecvMsg;
    BaseType_t xQueueRet;

    /* 底层SPI硬件初始化 */
    IMU_SPI_Config();
    m_xLastWakeTick = xTaskGetTickCount();
    DDL_Printf("Static IMU Task Start, Period:%dms\r\n", IMU_SAMPLE_PERIOD_MS);

    while(1)
    {
        /* 固定周期阻塞运行，精准10ms采样周期 */
        vTaskDelayUntil(&m_xLastWakeTick, pdMS_TO_TICKS(IMU_SAMPLE_PERIOD_MS));

        /* 处理控制消息 */
        xQueueRet = xQueueReceive(m_hImuMsgQueue, &stRecvMsg, 0U);
        if(pdPASS == xQueueRet)
        {
            Imu_MsgDispatch(&stRecvMsg);
        }

        /* 采集使能时遍历3路IMU读取数据并解算姿态 */
        if(IMU_STATE_SAMPLING == m_enImuState)
        {
            Imu_DoMultiSample();
        }
    }
}

/**
 * @brief 消息分发处理函数
 */
static void Imu_MsgDispatch(stc_imu_msg_t *pstMsg)
{
    int8_t i32InitRet;
    uint8_t u8Ch = pstMsg->u8ChIndex;
    switch(pstMsg->enMsgType)
    {
        case IMU_MSG_INIT:
            m_enImuState = IMU_STATE_INITING;
            /* 依次初始化三路MPU9250 */
            for(uint8_t ch = 1; ch <= IMU_CH_MAX_NUM; ch++)
            {
                i32InitRet = MPU9250_Init(ch);
                if(0 == i32InitRet)
                {
                    DDL_Printf("IMU Ch%d Init OK\r\n", ch);
                }
                else
                {
                    DDL_Printf("IMU Ch%d Init Fail, Check SPI/CS\r\n", ch);
                }
            }
            m_enImuState = IMU_STATE_IDLE;
            break;

        case IMU_MSG_START_SAMPLE:
            m_enImuState = IMU_STATE_SAMPLING;
            DDL_Printf("IMU Multi Channel Sample Start\r\n");
            break;

        case IMU_MSG_STOP_SAMPLE:
            m_enImuState = IMU_STATE_IDLE;
            DDL_Printf("IMU Sample Stop\r\n");
            break;

        case IMU_MSG_SENSOR_CALIB:
            m_enImuState = IMU_STATE_CALIBRATING;
            Imu_SingleCalibrate(u8Ch);
            m_enImuState = IMU_STATE_IDLE;
            DDL_Printf("IMU Ch%d Calibrate Complete\r\n", u8Ch);
            break;

        case IMU_MSG_MODULE_RESET:
            IMU_SPI_Config();
            m_enImuState = IMU_STATE_IDLE;
            DDL_Printf("SPI IMU Hardware Reset\r\n");
            break;

        default: break;
    }
}

/**
 * @brief 多路IMU统一采集+姿态解算，互斥锁保护全局数据缓存
 */
static void Imu_DoMultiSample(void)
{
    xSemaphoreTake(m_hImuDataMutex, portMAX_DELAY);
    /* 循环读取3路MPU9250 */
    for(uint8_t ch = 1; ch <= IMU_CH_MAX_NUM; ch++)
    {
        /* 读取原始加速度/陀螺仪数据 */
        MPU9250_ReadData(ch);
        /* Mahony四元数姿态解算 */
        MPU9250_AttitudeCalc_Quaternion(ch, m_fDt);
        /* 拷贝至全局对外缓存 */
        memcpy(&m_stImuFrame[ch - 1], &imu_data[ch - 1], sizeof(mpu9250_data_t));
    }
    xSemaphoreGive(m_hImuDataMutex);
}

/**
 * @brief 单通道IMU简易校准（清空积分、重置四元数）
 */
static void Imu_SingleCalibrate(uint8_t u8Ch)
{
    mpu9250_data_t *pDev = &imu_data[u8Ch - 1];
    /* 重置四元数初始姿态 */
    pDev->q0 = 1.0f;
    pDev->q1 = 0.0f;
    pDev->q2 = 0.0f;
    pDev->q3 = 0.0f;
    /* 清空积分误差 */
    pDev->ex_int = 0.0f;
    pDev->ey_int = 0.0f;
    pDev->ez_int = 0.0f;
    /* 清空欧拉角 */
    pDev->roll = 0.0f;
    pDev->pitch = 0.0f;
    pDev->yaw = 0.0f;
}


#endif

