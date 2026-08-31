/**
 ******************************************************************************
 * @file    app_wireless_task.c
 * @brief   源文件
 ******************************************************************************
 */
#include "app_wireless_task.h"

/* ====================== 静态内存区：任务/队列/互斥锁 全部静态存储 ====================== */
/* 1. 无线任务静态栈 + TCB控制块 */
static StackType_t m_auWirelessTaskStack[WIRELESS_TASK_STACK_SIZE];
static StaticTask_t m_stWirelessTaskTcb;

/* 2. 消息队列静态缓存 + 队列管理结构体 */
static uint8_t m_auWifiQStorage[WIRELESS_MSG_Q_DEPTH * sizeof(stc_wifi_msg_t)];
static StaticQueue_t m_stWifiMsgQueueBuf;

/* 3. 发送互斥锁静态内存 */
static StaticSemaphore_t m_stWifiTxMutexBuf;

/* ====================== 全局对外变量 ====================== */
TaskHandle_t m_hWirelessTask = NULL;
QueueHandle_t m_hWirelessMsgQueue = NULL;
SemaphoreHandle_t m_hWifiTxMutex = NULL;
en_wifi_state_t m_enWifiState = WIFI_STATE_IDLE;

/* ====================== 模块私有缓存 ====================== */
static uint8_t m_auWifiTxCache[WIRELESS_TX_BUF_MAX] = {0};
static uint8_t m_auWifiRxCache[WIRELESS_RX_BUF_MAX] = {0};

/* AP连接参数缓存 */
static char m_apSsid[64] = {0};
static char m_apPwd[64] = {0};
static char m_remoteIp[32] = {0};
static uint16_t m_u16RemotePort = 0;

/* ====================== 内部函数前置声明 ====================== */
static void Wireless_TaskEntry(void *pvParam);
static void Wireless_MsgDispatch(stc_wifi_msg_t *pstMsg);
static void Wifi_RecvDataCallback(uint8_t u8ConId, uint8_t *pu8Data, uint16_t u16Len);
static void Wifi_ConnectApProcess(const char *ssid, const char *pwd);
static void Wifi_SocketCreateProcess(const char *ip, uint16_t port);

/*******************************************************************************
 * @brief 静态创建无线任务、消息队列、发送互斥锁
 ******************************************************************************/
void APP_Wireless_TaskCreate(void)
{
    /* 1. 静态创建消息队列 */
    m_hWirelessMsgQueue = xQueueCreateStatic(
        WIRELESS_MSG_Q_DEPTH,
        sizeof(stc_wifi_msg_t),
        m_auWifiQStorage,
        &m_stWifiMsgQueueBuf
    );

    /* 2. 静态创建互斥锁，多任务发送互斥保护 */
    m_hWifiTxMutex = xSemaphoreCreateMutexStatic(&m_stWifiTxMutexBuf);

    /* 3. 静态创建主业务任务 */
    m_hWirelessTask = xTaskCreateStatic(
        Wireless_TaskEntry,
        "WifiTask",
        WIRELESS_TASK_STACK_SIZE,
        NULL,
        WIRELESS_TASK_PRIORITY,
        m_auWirelessTaskStack,
        &m_stWirelessTaskTcb
    );

    /* 静态创建容错判断，理论不会NULL */
    if((NULL == m_hWirelessTask) || (NULL == m_hWirelessMsgQueue) || (NULL == m_hWifiTxMutex))
    {
        DDL_Printf("Wireless Static Object Create Fail!\r\n");
    }
}

/*******************************************************************************
 * @brief 向无线任务发送控制消息
 * @param enMsg 消息类型
 * @param pu8Data Socket发送载荷数据
 * @param u16Len 载荷长度
 * @param pcParam 字符串参数(SSID/IP等)
 ******************************************************************************/
void APP_Wireless_SendMsg(en_wifi_msg_t enMsg, const uint8_t *pu8Data, uint16_t u16Len, const char *pcParam)
{
    stc_wifi_msg_t stMsg;
    stMsg.enMsgType = enMsg;
    stMsg.u16DataLen = u16Len;

    /* 拷贝二进制载荷 */
    if((NULL != pu8Data) && (u16Len > 0U) && (u16Len < WIRELESS_TX_BUF_MAX))
    {
        memcpy(stMsg.au8Payload, pu8Data, u16Len);
    }

    /* 拷贝字符串参数 */
    if(NULL != pcParam)
    {
        strncpy(stMsg.au8ParamStr, pcParam, sizeof(stMsg.au8ParamStr)-1);
    }

    if(NULL != m_hWirelessMsgQueue)
    {
        xQueueSend(m_hWirelessMsgQueue, &stMsg, 0U);
    }
}

/*******************************************************************************
 * @brief 外部通用Socket发送接口，带互斥锁保护
 * @retval pdPASS 成功 / pdFALSE 失败
 ******************************************************************************/
BaseType_t APP_Wireless_SocketTx(uint8_t u8ConId, const uint8_t *pu8Data, uint16_t u16Len, TickType_t xWait)
{
    BaseType_t xRet = pdFALSE;
    if((NULL == pu8Data) || (0U == u16Len) || (WIFI_STATE_SOCKET_CONNECTED != m_enWifiState))
    {
        return pdFALSE;
    }

    if(pdPASS == xSemaphoreTake(m_hWifiTxMutex, xWait))
    {
        memcpy(m_auWifiTxCache, pu8Data, u16Len);
        /* 填充消息 */
        stc_wifi_msg_t stMsg;
        stMsg.enMsgType = WIFI_MSG_SOCKET_SEND;
        stMsg.u8ConId = u8ConId;
        stMsg.u16DataLen = u16Len;
        memcpy(stMsg.au8Payload, m_auWifiTxCache, u16Len);

        xQueueSend(m_hWirelessMsgQueue, &stMsg, 0U);
        xRet = pdPASS;
        xSemaphoreGive(m_hWifiTxMutex);
    }
    return xRet;
}

/*******************************************************************************
 * @brief 查询WiFi是否正常联网(分配IP且Socket已建立)
 ******************************************************************************/
uint8_t APP_Wireless_IsWifiOnline(void)
{
    uint8_t u8Ret;
    taskENTER_CRITICAL();
    u8Ret = (WIFI_STATE_SOCKET_CONNECTED == m_enWifiState) ? 1U : 0U;
    taskEXIT_CRITICAL();
    return u8Ret;
}

/*******************************************************************************
 * @brief WiFi主任务循环
 ******************************************************************************/
static void Wireless_TaskEntry(void *pvParam)
{
    stc_wifi_msg_t stRecvMsg;
    BaseType_t xQRet;

    DDL_Printf("Static Wireless Task Start\r\n");

    while(1)
    {
        /* 阻塞等待消息，10ms超时执行底层轮询 */
        xQRet = xQueueReceive(m_hWirelessMsgQueue, &stRecvMsg, pdMS_TO_TICKS(10));
        if(pdPASS == xQRet)
        {
            Wireless_MsgDispatch(&stRecvMsg);
        }

        /* 底层AI-WB2轮询接收AT上报数据 */
        AI_WB2_Poll();
    }
}

/*******************************************************************************
 * @brief 消息分发处理函数
 ******************************************************************************/
static void Wireless_MsgDispatch(stc_wifi_msg_t *pstMsg)
{
    int32_t i32Ret;
    uint8_t u8ConId;
    switch(pstMsg->enMsgType)
    {
        case WIFI_MSG_INIT:
            m_enWifiState = WIFI_STATE_INITING;
            /* 初始化WB2硬件驱动，注册接收回调 */
            i32Ret = AI_WB2_Init();
            if(0 == i32Ret)
            {
                AI_WB2_RegisterRecvCallback(Wifi_RecvDataCallback);
                DDL_Printf("AI-WB2 Module Init OK, Ver:%s\r\n", AI_WB2_GetVersion());
                m_enWifiState = WIFI_STATE_IDLE;
            }
            else
            {
                DDL_Printf("AI-WB2 Init Failed!\r\n");
                m_enWifiState = WIFI_STATE_DISCONNECT;
            }
            break;

        case WIFI_MSG_CONNECT_AP:
            Wifi_ConnectApProcess(pstMsg->au8ParamStr, pstMsg->au8Payload);
            break;

        case WIFI_MSG_SOCKET_CREATE:
            strncpy(m_remoteIp, pstMsg->au8ParamStr, sizeof(m_remoteIp)-1);
            m_u16RemotePort = atoi((char *)pstMsg->au8Payload);
            Wifi_SocketCreateProcess(m_remoteIp, m_u16RemotePort);
            break;

        case WIFI_MSG_SOCKET_SEND:
            u8ConId = pstMsg->u8ConId;
            AI_WB2_SocketSend(u8ConId, pstMsg->au8Payload, pstMsg->u16DataLen);
            break;

        case WIFI_MSG_SOCKET_CLOSE:
            AI_WB2_SocketDelete(pstMsg->u8ConId);
            m_enWifiState = WIFI_STATE_GOT_IP;
            break;

        case WIFI_MSG_MODULE_RESET:
            AI_WB2_Reset();
            m_enWifiState = WIFI_STATE_IDLE;
            break;

        case WIFI_MSG_WIFI_DISCONNECT:
            m_enWifiState = WIFI_STATE_DISCONNECT;
            DDL_Printf("WiFi AP Disconnect!\r\n");
            break;

        default: break;
    }
}

/*******************************************************************************
 * @brief AP连接业务处理
 ******************************************************************************/
static void Wifi_ConnectApProcess(const char *ssid, const char *pwd)
{
    int32_t i32Ret;
    m_enWifiState = WIFI_STATE_CONNECT_AP;

    strncpy(m_apSsid, ssid, sizeof(m_apSsid)-1);
    strncpy(m_apPwd, pwd, sizeof(m_apPwd)-1);

    i32Ret = AI_WB2_ConnectAP(m_apSsid, m_apPwd);
    if(0 == i32Ret)
    {
        DDL_Printf("WiFi Get IP Success\r\n");
        m_enWifiState = WIFI_STATE_GOT_IP;
    }
    else
    {
        DDL_Printf("WiFi Connect AP Fail\r\n");
        m_enWifiState = WIFI_STATE_IDLE;
    }
}

/*******************************************************************************
 * @brief TCP客户端Socket创建处理
 ******************************************************************************/
static void Wifi_SocketCreateProcess(const char *ip, uint16_t port)
{
    uint8_t u8ConId;
    int32_t i32Ret;

    i32Ret = AI_WB2_SocketCreate(&u8ConId, AI_WB2_SOCK_TCP_CLIENT, ip, port, 0);
    if(0 == i32Ret)
    {
        DDL_Printf("Socket Create OK ConID:%d\r\n", u8ConId);
        m_enWifiState = WIFI_STATE_SOCKET_CONNECTED;
    }
    else
    {
        DDL_Printf("Socket Create Fail\r\n");
        m_enWifiState = WIFI_STATE_GOT_IP;
    }
}

/*******************************************************************************
 * @brief AI-WB2底层接收回调，收到Socket上行数据
 ******************************************************************************/
static void Wifi_RecvDataCallback(uint8_t u8ConId, uint8_t *pu8Data, uint16_t u16Len)
{
    /* 可转发至USB虚拟串口/其他业务任务 */
    DDL_Printf("Wifi Recv ConId:%d Len:%d\r\n", u8ConId, u16Len);
    // APP_UsbCdc_Write(pu8Data, u16Len, 0);
}



