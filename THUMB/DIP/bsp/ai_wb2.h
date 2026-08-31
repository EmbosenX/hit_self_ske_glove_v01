/**
 ******************************************************************************
 * @file    ai_wb2.h
 * @brief   AI-WB2 WiFi模块驱动头文件
 ******************************************************************************
 */

#ifndef __AI_WB2_H__
#define __AI_WB2_H__

#include "hc32_ll.h"
#include "hc32_ll_tmr0.h"
#include "hc32_ll_usart.h"
#include "hc32_ll_dma.h"

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

/* ========================== 硬件配置宏 ========================== */
/* USART配置：USART1 PA9-TX  PA10-RX */
#define AI_WB2_USART_UNIT             (CM_USART1)
#define AI_WB2_USART_CLK              (FCG1_PERIPH_USART1)
#define AI_WB2_USART_BAUDRATE         (115200UL)

#define AI_WB2_TX_PORT                (GPIO_PORT_A)
#define AI_WB2_TX_PIN                 (GPIO_PIN_09)
#define AI_WB2_TX_FUNC                (GPIO_FUNC_32)

#define AI_WB2_RX_PORT                (GPIO_PORT_A)
#define AI_WB2_RX_PIN                 (GPIO_PIN_10)
#define AI_WB2_RX_FUNC                (GPIO_FUNC_33)

/* DMA配置：DMA1_CH2发送 / DMA1_CH3接收 */
#define AI_WB2_DMA_UNIT               (CM_DMA1)
#define AI_WB2_DMA_CLK                (FCG0_PERIPH_DMA1)
#define AI_WB2_AOS_CLK                (FCG0_PERIPH_AOS)

/* DMA发送通道 */
#define AI_WB2_DMA_TX_CH              (DMA_CH2)
#define AI_WB2_DMA_TX_TRIG_SEL        (AOS_DMA1_2)
#define AI_WB2_DMA_TX_TRIG_EVT        (EVT_SRC_USART1_TI)
#define AI_WB2_DMA_TX_TC_INT          (DMA_INT_TC_CH2)
#define AI_WB2_DMA_TX_TC_FLAG         (DMA_FLAG_TC_CH2)
#define AI_WB2_DMA_TX_IRQn            (INT000_IRQn)
#define AI_WB2_DMA_TX_INT_SRC         (INT_SRC_DMA1_TC2)

/* DMA接收通道 */
#define AI_WB2_DMA_RX_CH              (DMA_CH3)
#define AI_WB2_DMA_RX_TRIG_SEL        (AOS_DMA1_3)
#define AI_WB2_DMA_RX_TRIG_EVT        (EVT_SRC_USART1_RI)
#define AI_WB2_DMA_RX_RECONF_TRIG     (AOS_DMA_RC)
#define AI_WB2_DMA_RX_RECONF_EVT      (EVT_SRC_AOS_STRG)
#define AI_WB2_DMA_RX_TC_INT          (DMA_INT_TC_CH3)
#define AI_WB2_DMA_RX_TC_FLAG         (DMA_FLAG_TC_CH3)
#define AI_WB2_DMA_RX_IRQn            (INT001_IRQn)
#define AI_WB2_DMA_RX_INT_SRC         (INT_SRC_DMA1_TC3)

/* 超时定时器：TMR0_1通道A */
#define AI_WB2_TMR0_UNIT              (CM_TMR0_1)
#define AI_WB2_TMR0_CH                (TMR0_CH_A)
#define AI_WB2_TMR0_CLK               (FCG2_PERIPH_TMR0_1)
#define AI_WB2_TIMEOUT_BITS           (2000U)

/* USART中断 */
#define AI_WB2_USART_RTO_IRQn         (INT002_IRQn)
#define AI_WB2_USART_RTO_INT_SRC      (INT_SRC_USART1_RTO)
#define AI_WB2_USART_ERR_IRQn         (INT003_IRQn)
#define AI_WB2_USART_ERR_INT_SRC      (INT_SRC_USART1_EI)

/* 缓冲区大小 */
#define AI_WB2_RX_BUF_SIZE            (2048U)
#define AI_WB2_TX_BUF_SIZE            (1024U)
#define AI_WB2_AT_TIMEOUT_MS          (3000U)
#define AI_WB2_WIFI_CONN_TIMEOUT      (15000U)
#define AI_WB2_MAX_SOCKET_NUM         (4U)

/* ========================== 类型定义 ========================== */
typedef enum {
    AI_WB2_MODE_OFF   = 0,
    AI_WB2_MODE_STA   = 1,
    AI_WB2_MODE_AP    = 2,
    AI_WB2_MODE_APSTA = 3
} ai_wb2_wifi_mode_t;

typedef enum {
    AI_WB2_SOCK_UDP_SERVER = 1,
    AI_WB2_SOCK_UDP_CLIENT = 2,
    AI_WB2_SOCK_TCP_SERVER = 3,
    AI_WB2_SOCK_TCP_CLIENT = 4
} ai_wb2_sock_type_t;

typedef struct {
    uint8_t  con_id;
    ai_wb2_sock_type_t type;
    bool     is_connected;
    uint16_t remote_port;
    uint16_t local_port;
} ai_wb2_socket_t;

typedef void (*ai_wb2_recv_cb_t)(uint8_t con_id, uint8_t *data, uint16_t len);

/* ========================== 函数声明 ========================== */
/* 基础功能 */
int32_t AI_WB2_Init(void);
int32_t AI_WB2_Reset(void);
int32_t AI_WB2_TestAT(void);
const char* AI_WB2_GetVersion(void);

/* WiFi功能 */
int32_t AI_WB2_SetWifiMode(ai_wb2_wifi_mode_t mode, bool save_flash);
int32_t AI_WB2_ConnectAP(const char *ssid, const char *password);
int32_t AI_WB2_SetAutoConnect(bool enable);
int32_t AI_WB2_GetStaInfo(char *buf, uint16_t buf_len);

/* Socket功能 */
int32_t AI_WB2_SocketCreate(uint8_t *con_id, ai_wb2_sock_type_t type,
                            const char *remote_host, uint16_t remote_port,
                            uint16_t local_port);
int32_t AI_WB2_SocketDelete(uint8_t con_id);
int32_t AI_WB2_SocketSend(uint8_t con_id, const uint8_t *data, uint16_t len);
int32_t AI_WB2_SocketSendLine(uint8_t con_id, const char *str);

/* 回调与轮询 */
void AI_WB2_RegisterRecvCallback(ai_wb2_recv_cb_t cb);
void AI_WB2_Poll(void);

#endif /* __AI_WB2_H__ */
