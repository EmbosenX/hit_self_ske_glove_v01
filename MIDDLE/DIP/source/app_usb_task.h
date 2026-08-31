/**
 ******************************************************************************
 * @file    app_usb_task.h
 * @brief   源文件
 ******************************************************************************
 */
#ifndef __APP_USB_TASK_H__
#define __APP_USB_TASK_H__

#include "hc32_ll.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "usb_lib.h"
#include "app_tac_config.h"

/* 任务配置 */
#define USB_CDC_TASK_STACK_SIZE    768U
#define USB_CDC_TASK_PRIORITY      (configMAX_PRIORITIES - 3)
#define USB_MSG_QUEUE_DEPTH        10U

/* 缓冲区长度 */
#define USB_CDC_RX_BUF_MAX_LEN     256U
#define USB_CDC_TX_BUF_MAX_LEN     256U

/* USB消息类型 */
typedef enum
{
    USB_CDC_MSG_CONNECT    = 0U,
    USB_CDC_MSG_DISCONNECT,
    USB_CDC_MSG_RECV_DATA,
    USB_CDC_MSG_SEND_DATA,
    USB_CDC_MSG_RESET
} en_usb_cdc_msg_t;

/* 消息队列结构体 */
typedef struct
{
    en_usb_cdc_msg_t enMsg;
    uint16_t u16DataLen;
    uint8_t  au8Data[USB_CDC_RX_BUF_MAX_LEN];
} stc_usb_cdc_msg_t;

/* USB连接状态 */
typedef enum
{
    USB_CDC_STATE_IDLE      = 0U,
    USB_CDC_STATE_CONNECTED = 1U
} en_usb_cdc_state_t;
/* 自定义数据包 */
#pragma pack(push, 1)   // 保存原有对齐设置，设置1字节对齐
typedef union
{
		uint8_t  payload_buf[2048];
		struct{
			uint8_t ID_STAGE;
			struct{
			uint8_t stage1;
			uint8_t row1;
			uint8_t col1;
			uint8_t buff1[512];
			};
			struct{
			uint8_t stage2;
			uint8_t row2;
			uint8_t col2;
			uint8_t buff2[512];
			};
			struct{
			uint8_t stage3;
			uint8_t row3;
			uint8_t col3;
			uint8_t buff3[512];
			};
		};
}payload_data_un;
typedef struct
{
		uint16_t header;
    uint8_t  channel;
    uint8_t  flags;
    uint16_t length;
    uint16_t crc16;
		uint16_t tailer;
} package_t;
#pragma pack(pop)       // 恢复原先对齐方式
/* 全局句柄对外声明 */
extern TaskHandle_t  m_hUsbCdcTask;
extern en_usb_cdc_state_t m_enUsbCdcState;
extern usb_core_instance  usb_dev;

/* 对外API */
void APP_UsbCdc_TaskCreate(void);

#endif /* __APP_USB_TASK_H__ */



