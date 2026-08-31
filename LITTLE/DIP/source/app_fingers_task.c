/**
 ******************************************************************************
 * @file    app_fingers_task.c
 * @brief   源文件
 ******************************************************************************
 */
#include "app_fingers_task.h"
#include "spi_fingers.h"
#include "app_sample_task.h"

/*******************************************************************************
 * 私有宏定义
 ******************************************************************************/
#define FINGER_COUNT        5U
#define ADC_PAYLOAD_MAX     2000U

typedef struct {
    uint8_t  u8Status;
    uint16_t u16DataLen;
    uint8_t  au8Data[ADC_PAYLOAD_MAX];
} finger_data_t;

/*******************************************************************************
 * 私有全局变量
 ******************************************************************************/
static StaticTask_t xAppFingersTaskTcb;
static StackType_t  uxAppFingersTaskStack[1024];
TaskHandle_t xAppFingersTaskHandle = NULL;

/*******************************************************************************
 * 静态内部函数声明
 ******************************************************************************/
static void Fingers_TaskEntry(void *pvParameters);
/*******************************************************************************
 * 全局共享数据（SPI采集结果，供其他任务读取）
 ******************************************************************************/
/* 5个手指的采集数据缓存，SPI任务写，其他任务读 */
finger_data_t g_stcFingerData[FINGER_COUNT];
/*******************************************************************************
 * 对外接口实现
 ******************************************************************************/
/**
 * @brief 创建手指采集任务、队列、信号量
 */
void APP_Fingers_TaskCreate(void)
{
    xAppFingersTaskHandle = xTaskCreateStatic(
        Fingers_TaskEntry,
        "app fingers task",
        1024,
        NULL,
        10,
        uxAppFingersTaskStack,
        &xAppFingersTaskTcb
    );
		if(xAppFingersTaskHandle!=NULL){DDL_Printf("AppFingersTask success!\r\n");}
}



/*******************************************************************************
 * 静态任务主体函数
 ******************************************************************************/
static void Fingers_TaskEntry(void *pvParameters)
{
    (void)pvParameters;
    uint8_t  u8SlaveIdx=1;
    int32_t  s32Ret;
	
    Fingers_SPI_Config();
	
    for (;;) {
        /************************ 第一步：等待外部任务通知启动采集 ************************/
        /* pdTRUE：接收后清零通知值，等价于二值信号量；portMAX_DELAY：永久阻塞 */
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        /* 依次轮询5个从机 */
        for (u8SlaveIdx = 1U; u8SlaveIdx <= FINGER_COUNT; u8SlaveIdx++) 
				{
            finger_data_t *pstcData = &g_stcFingerData[u8SlaveIdx - 1U];

            /* 发送读取命令：8bit格式，最大读取2000字节 */
            s32Ret = Fingers_SPI_Transact(
                u8SlaveIdx,
                SPI_CMD_READ_DATA,
								(DATA_FRAME_BYTE_NUM==1?ADC_FMT_16BIT:ADC_FMT_8BIT),
                ADC_PAYLOAD_MAX,
                pstcData->au8Data,
                &pstcData->u16DataLen,
                &pstcData->u8Status
            );

            if (s32Ret != SPI_OK) {
                pstcData->u8Status = 0xFFU; /* 标记通讯失败 */
                pstcData->u16DataLen = 0U;
            }
        }
        /************************ 第三步：通知外部控制任务，采集已完成 ************************/
        if (m_hSampleTask != NULL) {
            xTaskNotifyGive(m_hSampleTask);
        }
    }
}
/*******************************************************************************
 * 静态采样处理函数
 ******************************************************************************/


/*******************************************************************************
 * 静态滑动均值滤波
 ******************************************************************************/



