/**
 ******************************************************************************
 * @file    app_wireless_task.h
 * @brief   源文件
 ******************************************************************************
 */
#ifndef __APP_WIRELESS_TASK_H__
#define __APP_WIRELESS_TASK_H__

#include "hc32_ll.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "ai_wb2.h"

/* 任务基础配置 */
#define WIRELESS_TASK_STACK_SIZE       896U
#define WIRELESS_TASK_PRIORITY         (configMAX_PRIORITIES - 3)
#define WIRELESS_MSG_Q_DEPTH           12U

/* 数据缓存长度 */
#define WIRELESS_TX_BUF_MAX            256U
#define WIRELESS_RX_BUF_MAX            512U

/* 无线任务消息枚举 */
typedef enum
{
    WIFI_MSG_INIT = 0U,                // WiFi模块初始化
    WIFI_MSG_CONNECT_AP,               // 连接路由器AP
    WIFI_MSG_SOCKET_CREATE,            // 创建Socket连接
    WIFI_MSG_SOCKET_SEND,              // Socket发送数据
    WIFI_MSG_SOCKET_CLOSE,             // 关闭Socket
    WIFI_MSG_MODULE_RESET,             // AI-WB2硬件复位
    WIFI_MSG_POLL_RECV,                // 轮询接收模块上报数据
    WIFI_MSG_WIFI_DISCONNECT,          // WiFi断连事件
} en_wifi_msg_t;

/* 消息队列单条数据结构 */
typedef struct
{
    en_wifi_msg_t enMsgType;
    uint8_t u8ConId;                   // Socket通道ID
    uint16_t u16DataLen;               // 数据长度
    uint8_t au8Payload[WIRELESS_TX_BUF_MAX];
    char au8ParamStr[128];             // 字符串参数(SSID/IP/密码)
} stc_wifi_msg_t;

/* WiFi连接状态 */
typedef enum
{
    WIFI_STATE_IDLE = 0U,
    WIFI_STATE_INITING,
    WIFI_STATE_CONNECT_AP,
    WIFI_STATE_GOT_IP,
    WIFI_STATE_SOCKET_CONNECTED,
    WIFI_STATE_DISCONNECT
} en_wifi_state_t;

/* 对外全局句柄&状态 */
extern TaskHandle_t m_hWirelessTask;
extern QueueHandle_t m_hWirelessMsgQueue;
extern SemaphoreHandle_t m_hWifiTxMutex;
extern en_wifi_state_t m_enWifiState;

/* 对外业务API */
void APP_Wireless_TaskCreate(void);
void APP_Wireless_SendMsg(en_wifi_msg_t enMsg, const uint8_t *pu8Data, uint16_t u16Len, const char *pcParam);
BaseType_t APP_Wireless_SocketTx(uint8_t u8ConId, const uint8_t *pu8Data, uint16_t u16Len, TickType_t xWait);
uint8_t APP_Wireless_IsWifiOnline(void);

#endif /* __APP_WIRELESS_TASK_H__ */




