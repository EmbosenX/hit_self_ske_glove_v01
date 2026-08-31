/**
 ******************************************************************************
 * @file    app_usb_task.c
 * @brief   源文件
 ******************************************************************************
 */
#include "app_usb_task.h"
#include "usb_bsp.h"
#include "main.h"
#include <string.h>
#include "app_sample_task.h"


/* ===================== 静态内存定义（全部放在全局静态区） ===================== */
/* 1. USB CDC 任务静态栈 + TCB */
static StackType_t m_au8UsbTaskStack[USB_CDC_TASK_STACK_SIZE];
static StaticTask_t m_stUsbTaskTcb;

/* ===================== 对外句柄（仅声明，赋值由静态创建函数返回） ===================== */
TaskHandle_t  m_hUsbCdcTask = NULL;

en_usb_cdc_state_t m_enUsbCdcState;
/* 私有缓存 */
static uint8_t payload_temp[1024]={0};
static payload_data_un payload_data;
static package_t package;

/* 内部函数声明 */
static void UsbCdc_TaskEntry(void *pvParam);
/*******************************************************************************
 * USB 设备实例（保留原有CDC功能）
 ******************************************************************************/
usb_core_instance  usb_dev;
/**
 * @brief 创建USB CDC任务、队列、互斥锁【全部静态分配】
 */
void APP_UsbCdc_TaskCreate(void)
{
    /* ---------- 3. 静态创建任务 ---------- */
    m_hUsbCdcTask = xTaskCreateStatic(
        UsbCdc_TaskEntry,
        "UsbCdcTask",
        USB_CDC_TASK_STACK_SIZE,
        NULL,
        USB_CDC_TASK_PRIORITY,
        m_au8UsbTaskStack,   // 任务栈静态数组
        &m_stUsbTaskTcb      // 任务TCB静态结构体
    );

    /* 判空保护（静态创建理论不会返回NULL，仅容错） */
    if((NULL == m_hUsbCdcTask))
    {
        DDL_Printf("USB CDC Static Object Create Fail!\r\n");
    }
}

/**
 * @brief 查询USB虚拟串口是否连接上位机
 */
static uint8_t APP_UsbCdc_IsConnect(void)
{
    return (usb_dev.dev.connection_status == 1);
}

static uint16_t palm_host_crc16(const uint8_t *data, uint16_t size)
{
    uint16_t crc = 0x0000U;
    uint16_t i;
    uint8_t bit;

    for (i = 0U; i < size; ++i) {
        crc ^= data[i];
        for (bit = 0U; bit < 8U; ++bit) {
            if ((crc & 0x0001U) != 0U) {
                crc = (uint16_t)((crc >> 1U) ^ 0xA001U);
            } else {
                crc >>= 1U;
            }
        }
    }

    return crc;
}
/**
 * @brief USB CDC任务主循环
 */
static void UsbCdc_TaskEntry(void *pvParam)
{
	  const tac_data_cfg_t* pTacDataCfg = GetTacDataCfg();
		static uint8_t tx_buff[2048]={0};
    /* 初始化底层USB CDC外设 */
#if(USB_FUN_ENABLE)
    stc_usb_port_identify stcPortIdentify;
    stcPortIdentify.u8CoreID = USBFS_CORE_ID;
    usb_dev_init(&usb_dev, &stcPortIdentify, &user_desc, &class_cdc_cbk, &user_cb);
#endif
    DDL_Printf("USB CDC Static Task Start\r\n");

    while(1)
    {
        /************************ 第一步：等待外部任务通知启动采集 ************************/
				ulTaskNotifyTake(pdTRUE, portMAX_DELAY);//usb发送通知
        if(APP_UsbCdc_IsConnect())
				{
					/*发送手掌的采集数据组包*/
					m_enUsbCdcState = USB_CDC_STATE_CONNECTED;
					/*掌心数据组包发送*/
					payload_data.ID_STAGE = 0x61;//手掌
					payload_data.stage1 = 0X01;
					payload_data.col1 = sizeof(pTacDataCfg->palm1[0]) / sizeof(pTacDataCfg->palm1[0][0]);
					payload_data.row1 = sizeof(pTacDataCfg->palm1) / sizeof(pTacDataCfg->palm1[0]);
					memcpy(payload_data.buff1, pTacDataCfg->palm1, sizeof(pTacDataCfg->palm1));// 直接整帧拷贝：源=二维数组首地址，目标=一维数组，长度=整个二维数组的字节数
					memcpy(payload_temp,&payload_data.ID_STAGE,(4+sizeof(pTacDataCfg->palm1)));
					package.header = 0x3C3C;
					package.channel = 0X02;
					package.flags = 0X00;
					package.length = (4+sizeof(pTacDataCfg->palm1));
					package.crc16 = palm_host_crc16(&payload_temp[0],package.length);
					package.tailer = 0X3E3E;
					tx_buff[0] = (package.header>>0)&0XFF;
					tx_buff[1] = (package.header>>8)&0XFF;
					tx_buff[2] =  package.channel;
					tx_buff[3] = 	package.flags;
					tx_buff[4] = (package.length>>0)&0XFF;
					tx_buff[5] = (package.length>>8)&0XFF;
					memcpy(&tx_buff[6],&payload_temp[0],package.length);
					tx_buff[package.length+6] = (package.crc16>>0)&0XFF;
					tx_buff[package.length+7] = (package.crc16>>8)&0XFF;
					tx_buff[package.length+8] = (package.tailer>>0)&0XFF;
					tx_buff[package.length+9] = (package.tailer>>8)&0XFF;
					CDC_SendData(tx_buff, (10+package.length));
					while(!CDC_IsTxIdle()){vTaskDelay(0);}
					/*大拇指数据组包发送*/
					payload_data.ID_STAGE = 0x12;//大拇指
					payload_data.stage1 = 0X01;
					payload_data.col1 = sizeof(pTacDataCfg->thumb_dip[0]) / sizeof(pTacDataCfg->thumb_dip[0][0]);
					payload_data.row1 = sizeof(pTacDataCfg->thumb_dip) / sizeof(pTacDataCfg->thumb_dip[0]);
					memcpy(payload_data.buff1, pTacDataCfg->thumb_dip, sizeof(pTacDataCfg->thumb_dip));// 直接整帧拷贝：源=二维数组首地址，目标=一维数组，长度=整个二维数组的字节数
					memcpy(payload_temp,&payload_data.ID_STAGE,(4+sizeof(pTacDataCfg->thumb_dip)));
					payload_data.stage2 = 0X02;
					payload_data.col2 = sizeof(pTacDataCfg->thumb_mcp[0]) / sizeof(pTacDataCfg->thumb_mcp[0][0]);
					payload_data.row2 = sizeof(pTacDataCfg->thumb_mcp) / sizeof(pTacDataCfg->thumb_mcp[0]);
					memcpy(payload_data.buff2, pTacDataCfg->thumb_mcp, sizeof(pTacDataCfg->thumb_mcp));// 直接整帧拷贝：源=二维数组首地址，目标=一维数组，长度=整个二维数组的字节数
					memcpy(&payload_temp[4+sizeof(pTacDataCfg->thumb_dip)],&payload_data.stage2,(3+sizeof(pTacDataCfg->thumb_mcp)));
					package.header = 0x3C3C;
					package.channel = 0X02;
					package.flags = 0X00;
					package.length = (4+sizeof(pTacDataCfg->thumb_dip))+(3+sizeof(pTacDataCfg->thumb_mcp));
					package.crc16 = palm_host_crc16(&payload_temp[0],package.length);
					package.tailer = 0X3E3E;
					tx_buff[0] = (package.header>>0)&0XFF;
					tx_buff[1] = (package.header>>8)&0XFF;
					tx_buff[2] =  package.channel;
					tx_buff[3] = 	package.flags;
					tx_buff[4] = (package.length>>0)&0XFF;
					tx_buff[5] = (package.length>>8)&0XFF;
					memcpy(&tx_buff[6],&payload_data.payload_buf[0],package.length);
					tx_buff[package.length+6] = (package.crc16>>0)&0XFF;
					tx_buff[package.length+7] = (package.crc16>>8)&0XFF;
					tx_buff[package.length+8] = (package.tailer>>0)&0XFF;
					tx_buff[package.length+9] = (package.tailer>>8)&0XFF;
					CDC_SendData(tx_buff, (10+package.length));
					while(!CDC_IsTxIdle()){vTaskDelay(0);}
					/*食指数据组包发送*/
					payload_data.ID_STAGE = 0x23;//食指
					payload_data.stage1 = 0X01;
					payload_data.col1 = sizeof(pTacDataCfg->index_dip[0]) / sizeof(pTacDataCfg->index_dip[0][0]);
					payload_data.row1 = sizeof(pTacDataCfg->index_dip) / sizeof(pTacDataCfg->index_dip[0]);
					memcpy(payload_data.buff1, pTacDataCfg->index_dip, sizeof(pTacDataCfg->index_dip));// 直接整帧拷贝：源=二维数组首地址，目标=一维数组，长度=整个二维数组的字节数
					memcpy(payload_temp,&payload_data.ID_STAGE,(4+sizeof(pTacDataCfg->index_dip)));
					payload_data.stage2 = 0X02;
					payload_data.col2 = sizeof(pTacDataCfg->index_pip[0]) / sizeof(pTacDataCfg->index_pip[0][0]);
					payload_data.row2 = sizeof(pTacDataCfg->index_pip) / sizeof(pTacDataCfg->index_pip[0]);
					memcpy(payload_data.buff2, pTacDataCfg->index_pip, sizeof(pTacDataCfg->index_pip));// 直接整帧拷贝：源=二维数组首地址，目标=一维数组，长度=整个二维数组的字节数
					memcpy(&payload_temp[4+sizeof(pTacDataCfg->index_dip)],&payload_data.stage2,(3+sizeof(pTacDataCfg->index_pip)));
					payload_data.stage3 = 0X03;
					payload_data.col3 = sizeof(pTacDataCfg->index_mcp[0]) / sizeof(pTacDataCfg->index_mcp[0][0]);
					payload_data.row3 = sizeof(pTacDataCfg->index_mcp) / sizeof(pTacDataCfg->index_mcp[0]);
					memcpy(payload_data.buff3, pTacDataCfg->index_mcp, sizeof(pTacDataCfg->index_mcp));// 直接整帧拷贝：源=二维数组首地址，目标=一维数组，长度=整个二维数组的字节数
					memcpy(&payload_temp[(4+sizeof(pTacDataCfg->index_dip))+(3+sizeof(pTacDataCfg->index_pip))],&payload_data.stage3,(3+sizeof(pTacDataCfg->index_mcp)));
					package.header = 0x3C3C;
					package.channel = 0X02;
					package.flags = 0X00;
					package.length = (4+sizeof(pTacDataCfg->index_dip))+(3+sizeof(pTacDataCfg->index_pip))+(3+sizeof(pTacDataCfg->index_mcp));
					package.crc16 = palm_host_crc16(&payload_temp[0],package.length);
					package.tailer = 0X3E3E;
					tx_buff[0] = (package.header>>0)&0XFF;
					tx_buff[1] = (package.header>>8)&0XFF;
					tx_buff[2] =  package.channel;
					tx_buff[3] = 	package.flags;
					tx_buff[4] = (package.length>>0)&0XFF;
					tx_buff[5] = (package.length>>8)&0XFF;
					memcpy(&tx_buff[6],&payload_temp[0],package.length);
					tx_buff[package.length+6] = (package.crc16>>0)&0XFF;
					tx_buff[package.length+7] = (package.crc16>>8)&0XFF;
					tx_buff[package.length+8] = (package.tailer>>0)&0XFF;
					tx_buff[package.length+9] = (package.tailer>>8)&0XFF;
					CDC_SendData(tx_buff, (10+package.length));
					while(!CDC_IsTxIdle()){vTaskDelay(0);}
					/*中指数据组包发送*/
					payload_data.ID_STAGE = 0x33;//食指
					payload_data.stage1 = 0X01;
					payload_data.col1 = sizeof(pTacDataCfg->middle_dip[0]) / sizeof(pTacDataCfg->middle_dip[0][0]);
					payload_data.row1 = sizeof(pTacDataCfg->middle_dip) / sizeof(pTacDataCfg->middle_dip[0]);
					memcpy(payload_data.buff1, pTacDataCfg->middle_dip, sizeof(pTacDataCfg->middle_dip));// 直接整帧拷贝：源=二维数组首地址，目标=一维数组，长度=整个二维数组的字节数
					memcpy(payload_temp,&payload_data.ID_STAGE,(4+sizeof(pTacDataCfg->middle_dip)));
					payload_data.stage2 = 0X02;
					payload_data.col2 = sizeof(pTacDataCfg->middle_pip[0]) / sizeof(pTacDataCfg->middle_pip[0][0]);
					payload_data.row2 = sizeof(pTacDataCfg->middle_pip) / sizeof(pTacDataCfg->middle_pip[0]);
					memcpy(payload_data.buff2, pTacDataCfg->middle_pip, sizeof(pTacDataCfg->middle_pip));// 直接整帧拷贝：源=二维数组首地址，目标=一维数组，长度=整个二维数组的字节数
					memcpy(&payload_temp[4+sizeof(pTacDataCfg->middle_dip)],&payload_data.stage2,(3+sizeof(pTacDataCfg->middle_pip)));
					payload_data.stage3 = 0X03;
					payload_data.col3 = sizeof(pTacDataCfg->middle_mcp[0]) / sizeof(pTacDataCfg->middle_mcp[0][0]);
					payload_data.row3 = sizeof(pTacDataCfg->middle_mcp) / sizeof(pTacDataCfg->middle_mcp[0]);
					memcpy(payload_data.buff3, pTacDataCfg->middle_mcp, sizeof(pTacDataCfg->middle_mcp));// 直接整帧拷贝：源=二维数组首地址，目标=一维数组，长度=整个二维数组的字节数
					memcpy(&payload_temp[(4+sizeof(pTacDataCfg->middle_dip))+(3+sizeof(pTacDataCfg->middle_pip))],&payload_data.stage3,(3+sizeof(pTacDataCfg->middle_mcp)));
					package.header = 0x3C3C;
					package.channel = 0X02;
					package.flags = 0X00;
					package.length = (4+sizeof(pTacDataCfg->middle_dip))+(3+sizeof(pTacDataCfg->middle_pip))+(3+sizeof(pTacDataCfg->middle_mcp));
					package.crc16 = palm_host_crc16(&payload_temp[0],package.length);
					package.tailer = 0X3E3E;
					tx_buff[0] = (package.header>>0)&0XFF;
					tx_buff[1] = (package.header>>8)&0XFF;
					tx_buff[2] =  package.channel;
					tx_buff[3] = 	package.flags;
					tx_buff[4] = (package.length>>0)&0XFF;
					tx_buff[5] = (package.length>>8)&0XFF;
					memcpy(&tx_buff[6],&payload_temp[0],package.length);
					tx_buff[package.length+6] = (package.crc16>>0)&0XFF;
					tx_buff[package.length+7] = (package.crc16>>8)&0XFF;
					tx_buff[package.length+8] = (package.tailer>>0)&0XFF;
					tx_buff[package.length+9] = (package.tailer>>8)&0XFF;
					CDC_SendData(tx_buff, (10+package.length));
					while(!CDC_IsTxIdle()){vTaskDelay(0);}
					/*无名指数据组包发送*/
					payload_data.ID_STAGE = 0x33;//食指
					payload_data.stage1 = 0X01;
					payload_data.col1 = sizeof(pTacDataCfg->ring_dip[0]) / sizeof(pTacDataCfg->ring_dip[0][0]);
					payload_data.row1 = sizeof(pTacDataCfg->ring_dip) / sizeof(pTacDataCfg->ring_dip[0]);
					memcpy(payload_data.buff1, pTacDataCfg->ring_dip, sizeof(pTacDataCfg->ring_dip));// 直接整帧拷贝：源=二维数组首地址，目标=一维数组，长度=整个二维数组的字节数
					memcpy(payload_temp,&payload_data.ID_STAGE,(4+sizeof(pTacDataCfg->ring_dip)));
					payload_data.stage2 = 0X02;
					payload_data.col2 = sizeof(pTacDataCfg->ring_pip[0]) / sizeof(pTacDataCfg->ring_pip[0][0]);
					payload_data.row2 = sizeof(pTacDataCfg->ring_pip) / sizeof(pTacDataCfg->ring_pip[0]);
					memcpy(payload_data.buff2, pTacDataCfg->ring_pip, sizeof(pTacDataCfg->ring_pip));// 直接整帧拷贝：源=二维数组首地址，目标=一维数组，长度=整个二维数组的字节数
					memcpy(&payload_temp[4+sizeof(pTacDataCfg->ring_dip)],&payload_data.stage2,(3+sizeof(pTacDataCfg->ring_pip)));
					payload_data.stage3 = 0X03;
					payload_data.col3 = sizeof(pTacDataCfg->ring_mcp[0]) / sizeof(pTacDataCfg->ring_mcp[0][0]);
					payload_data.row3 = sizeof(pTacDataCfg->ring_mcp) / sizeof(pTacDataCfg->ring_mcp[0]);
					memcpy(payload_data.buff3, pTacDataCfg->ring_mcp, sizeof(pTacDataCfg->ring_mcp));// 直接整帧拷贝：源=二维数组首地址，目标=一维数组，长度=整个二维数组的字节数
					memcpy(&payload_temp[(4+sizeof(pTacDataCfg->ring_dip))+(3+sizeof(pTacDataCfg->ring_pip))],&payload_data.stage3,(3+sizeof(pTacDataCfg->ring_mcp)));
					package.header = 0x3C3C;
					package.channel = 0X02;
					package.flags = 0X00;
					package.length = (4+sizeof(pTacDataCfg->ring_dip))+(3+sizeof(pTacDataCfg->ring_pip))+(3+sizeof(pTacDataCfg->ring_mcp));
					package.crc16 = palm_host_crc16(&payload_temp[0],package.length);
					package.tailer = 0X3E3E;
					tx_buff[0] = (package.header>>0)&0XFF;
					tx_buff[1] = (package.header>>8)&0XFF;
					tx_buff[2] =  package.channel;
					tx_buff[3] = 	package.flags;
					tx_buff[4] = (package.length>>0)&0XFF;
					tx_buff[5] = (package.length>>8)&0XFF;
					memcpy(&tx_buff[6],&payload_temp[0],package.length);
					tx_buff[package.length+6] = (package.crc16>>0)&0XFF;
					tx_buff[package.length+7] = (package.crc16>>8)&0XFF;
					tx_buff[package.length+8] = (package.tailer>>0)&0XFF;
					tx_buff[package.length+9] = (package.tailer>>8)&0XFF;
					CDC_SendData(tx_buff, (10+package.length));
					while(!CDC_IsTxIdle()){vTaskDelay(0);}
					/*小指数据组包发送*/
					payload_data.ID_STAGE = 0x33;//食指
					payload_data.stage1 = 0X01;
					payload_data.col1 = sizeof(pTacDataCfg->little_dip[0]) / sizeof(pTacDataCfg->little_dip[0][0]);
					payload_data.row1 = sizeof(pTacDataCfg->little_dip) / sizeof(pTacDataCfg->little_dip[0]);
					memcpy(payload_data.buff1, pTacDataCfg->little_dip, sizeof(pTacDataCfg->little_dip));// 直接整帧拷贝：源=二维数组首地址，目标=一维数组，长度=整个二维数组的字节数
					memcpy(payload_temp,&payload_data.ID_STAGE,(4+sizeof(pTacDataCfg->little_dip)));
					payload_data.stage2 = 0X02;
					payload_data.col2 = sizeof(pTacDataCfg->little_pip[0]) / sizeof(pTacDataCfg->little_pip[0][0]);
					payload_data.row2 = sizeof(pTacDataCfg->little_pip) / sizeof(pTacDataCfg->little_pip[0]);
					memcpy(payload_data.buff2, pTacDataCfg->little_pip, sizeof(pTacDataCfg->little_pip));// 直接整帧拷贝：源=二维数组首地址，目标=一维数组，长度=整个二维数组的字节数
					memcpy(&payload_temp[4+sizeof(pTacDataCfg->little_dip)],&payload_data.stage2,(3+sizeof(pTacDataCfg->little_pip)));
					payload_data.stage3 = 0X03;
					payload_data.col3 = sizeof(pTacDataCfg->little_mcp[0]) / sizeof(pTacDataCfg->little_mcp[0][0]);
					payload_data.row3 = sizeof(pTacDataCfg->little_mcp) / sizeof(pTacDataCfg->little_mcp[0]);
					memcpy(payload_data.buff3, pTacDataCfg->little_mcp, sizeof(pTacDataCfg->little_mcp));// 直接整帧拷贝：源=二维数组首地址，目标=一维数组，长度=整个二维数组的字节数
					memcpy(&payload_temp[(4+sizeof(pTacDataCfg->little_dip))+(3+sizeof(pTacDataCfg->little_pip))],&payload_data.stage3,(3+sizeof(pTacDataCfg->little_mcp)));
					package.header = 0x3C3C;
					package.channel = 0X02;
					package.flags = 0X00;
					package.length = (4+sizeof(pTacDataCfg->little_dip))+(3+sizeof(pTacDataCfg->little_pip))+(3+sizeof(pTacDataCfg->little_mcp));
					package.crc16 = palm_host_crc16(&payload_temp[0],package.length);
					package.tailer = 0X3E3E;
					tx_buff[0] = (package.header>>0)&0XFF;
					tx_buff[1] = (package.header>>8)&0XFF;
					tx_buff[2] =  package.channel;
					tx_buff[3] = 	package.flags;
					tx_buff[4] = (package.length>>0)&0XFF;
					tx_buff[5] = (package.length>>8)&0XFF;
					memcpy(&tx_buff[6],&payload_temp[0],package.length);
					tx_buff[package.length+6] = (package.crc16>>0)&0XFF;
					tx_buff[package.length+7] = (package.crc16>>8)&0XFF;
					tx_buff[package.length+8] = (package.tailer>>0)&0XFF;
					tx_buff[package.length+9] = (package.tailer>>8)&0XFF;
					CDC_SendData(tx_buff, (10+package.length));
					while(!CDC_IsTxIdle()){vTaskDelay(0);}
				}
				else{
					m_enUsbCdcState = USB_CDC_STATE_IDLE;
				}
    }
}




