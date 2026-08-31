#include "ai_wb2.h"

/* ========================== 内部变量 ========================== */
/* DMA发送缓冲区 4字节对齐 */
static uint8_t m_tx_buf[AI_WB2_TX_BUF_SIZE] __attribute__((aligned(4)));
static volatile en_flag_status_t m_tx_done = SET;

/* DMA接收缓冲区 & LLP循环描述符 */
static uint8_t m_rx_dma_buf[AI_WB2_RX_BUF_SIZE] __attribute__((aligned(4)));
static stc_dma_llp_descriptor_t m_rxLlpDesc;
static volatile en_flag_status_t m_rx_frame_end = RESET;
static volatile uint16_t m_rx_frame_len = 0;

/* 解析环形缓冲区 */
static uint8_t m_parse_buf[AI_WB2_RX_BUF_SIZE];
static uint16_t m_parse_head = 0;
static uint16_t m_parse_tail = 0;

static ai_wb2_recv_cb_t m_recv_cb = NULL;
static ai_wb2_socket_t  m_socket_list[AI_WB2_MAX_SOCKET_NUM];
static uint8_t          m_socket_cnt = 0;
static char             m_version_str[64];

/* ========================== 内部函数声明 ========================== */
static void UsartDma_Init(void);
static void DmaTx_Init(void);
static void DmaRx_Init(void);
static void Tmr0_Timeout_Init(uint16_t u16TimeoutBits);
static void Usart_StopTimeoutTimer(void);

static int32_t UsartDma_Send(const uint8_t *data, uint16_t len);
static void UsartDma_StartRx(void);
static void MoveDmaToParseBuf(void);

static bool ParseBuf_GetByte(uint8_t *ch);
static void ClearParseBuf(void);

static int32_t SendATCmd(const char *cmd, const char *expect_ack,
                         char *resp_buf, uint16_t resp_len, uint32_t timeout_ms);
static int32_t WaitForResponse(const char *expect, char *resp_buf,
                               uint16_t resp_len, uint32_t timeout_ms);
static uint8_t AllocConID(void);

/* ========================== 中断回调函数 ========================== */
static void DmaTx_TC_IrqCallback(void)
{
    DMA_ClearTransCompleteStatus(AI_WB2_DMA_UNIT, AI_WB2_DMA_TX_TC_FLAG);
    DMA_ChCmd(AI_WB2_DMA_UNIT, AI_WB2_DMA_TX_CH, DISABLE);
    m_tx_done = SET;
}

static void DmaRx_TC_IrqCallback(void)
{
    DMA_ClearTransCompleteStatus(AI_WB2_DMA_UNIT, AI_WB2_DMA_RX_TC_FLAG);
    USART_FuncCmd(AI_WB2_USART_UNIT, USART_RX_TIMEOUT, DISABLE);
    m_rx_frame_end = SET;
    m_rx_frame_len = AI_WB2_RX_BUF_SIZE;
}

static void Usart_RxTimeout_IrqCallback(void)
{
    if (RESET == m_rx_frame_end) {
        m_rx_frame_end = SET;
        m_rx_frame_len = AI_WB2_RX_BUF_SIZE - (uint16_t)DMA_GetTransCount(AI_WB2_DMA_UNIT, AI_WB2_DMA_RX_CH);
        /* 触发DMA重配置，自动重装接收计数 */
        AOS_SW_Trigger();
    }
    Usart_StopTimeoutTimer();
    USART_ClearStatus(AI_WB2_USART_UNIT, USART_FLAG_RX_TIMEOUT);
}

static void Usart_RxError_IrqCallback(void)
{
    /* 读一次数据寄存器清除溢出 */
    (void)USART_ReadData(AI_WB2_USART_UNIT);
    USART_ClearStatus(AI_WB2_USART_UNIT, USART_FLAG_PARITY_ERR | USART_FLAG_FRAME_ERR | USART_FLAG_OVERRUN);
}

/* ========================== 底层硬件初始化 ========================== */
static void DmaTx_Init(void)
{
    stc_dma_init_t stcDmaInit;
    stc_irq_signin_config_t stcIrqSignConfig;

    /* 发送DMA初始化 */
    DMA_StructInit(&stcDmaInit);
    stcDmaInit.u32IntEn      = DMA_INT_ENABLE;
    stcDmaInit.u32BlockSize  = 1UL;
    stcDmaInit.u32TransCount = 0UL;
    stcDmaInit.u32DataWidth  = DMA_DATAWIDTH_8BIT;
    stcDmaInit.u32SrcAddr    = (uint32_t)m_tx_buf;
    stcDmaInit.u32DestAddr   = (uint32_t)(&AI_WB2_USART_UNIT->TDR);
    stcDmaInit.u32SrcAddrInc = DMA_SRC_ADDR_INC;
    stcDmaInit.u32DestAddrInc= DMA_DEST_ADDR_FIX;
    DMA_Init(AI_WB2_DMA_UNIT, AI_WB2_DMA_TX_CH, &stcDmaInit);

    /* 注册DMA发送完成中断 */
    stcIrqSignConfig.enIntSrc    = AI_WB2_DMA_TX_INT_SRC;
    stcIrqSignConfig.enIRQn      = AI_WB2_DMA_TX_IRQn;
    stcIrqSignConfig.pfnCallback = &DmaTx_TC_IrqCallback;
    INTC_IrqSignIn(&stcIrqSignConfig);

    NVIC_ClearPendingIRQ(AI_WB2_DMA_TX_IRQn);
    NVIC_SetPriority(AI_WB2_DMA_TX_IRQn, DDL_IRQ_PRIO_06);
    NVIC_EnableIRQ(AI_WB2_DMA_TX_IRQn);

    /* 配置DMA触发源 */
    AOS_SetTriggerEventSrc(AI_WB2_DMA_TX_TRIG_SEL, AI_WB2_DMA_TX_TRIG_EVT);

    /* 使能DMA控制器 & 传输完成中断 */
    DMA_Cmd(AI_WB2_DMA_UNIT, ENABLE);
    DMA_TransCompleteIntCmd(AI_WB2_DMA_UNIT, AI_WB2_DMA_TX_TC_INT, ENABLE);
}

static void DmaRx_Init(void)
{
    stc_dma_init_t stcDmaInit;
    stc_dma_llp_init_t stcDmaLlpInit;
    stc_irq_signin_config_t stcIrqSignConfig;

    /* 接收DMA初始化 */
    DMA_StructInit(&stcDmaInit);
    stcDmaInit.u32IntEn      = DMA_INT_ENABLE;
    stcDmaInit.u32BlockSize  = 1UL;
    stcDmaInit.u32TransCount = AI_WB2_RX_BUF_SIZE;
    stcDmaInit.u32DataWidth  = DMA_DATAWIDTH_8BIT;
    stcDmaInit.u32SrcAddr    = (uint32_t)(&AI_WB2_USART_UNIT->RDR);
    stcDmaInit.u32DestAddr   = (uint32_t)m_rx_dma_buf;
    stcDmaInit.u32SrcAddrInc = DMA_SRC_ADDR_FIX;
    stcDmaInit.u32DestAddrInc= DMA_DEST_ADDR_INC;
    DMA_Init(AI_WB2_DMA_UNIT, AI_WB2_DMA_RX_CH, &stcDmaInit);

    /* LLP链表自指向，实现循环接收自动重装 */
    DMA_LlpStructInit(&stcDmaLlpInit);
    stcDmaLlpInit.u32State = DMA_LLP_ENABLE;
    stcDmaLlpInit.u32Mode  = DMA_LLP_WAIT;
    stcDmaLlpInit.u32Addr  = (uint32_t)&m_rxLlpDesc;
    DMA_LlpInit(AI_WB2_DMA_UNIT, AI_WB2_DMA_RX_CH, &stcDmaLlpInit);

    /* 填充LLP描述符，自指向实现循环 */
    m_rxLlpDesc.SARx   = stcDmaInit.u32SrcAddr;
    m_rxLlpDesc.DARx   = stcDmaInit.u32DestAddr;
    m_rxLlpDesc.DTCTLx = (stcDmaInit.u32TransCount << DMA_DTCTL_CNT_POS) | (stcDmaInit.u32BlockSize << DMA_DTCTL_BLKSIZE_POS);
    m_rxLlpDesc.LLPx   = (uint32_t)&m_rxLlpDesc;
    m_rxLlpDesc.CHCTLx = stcDmaInit.u32SrcAddrInc | stcDmaInit.u32DestAddrInc | stcDmaInit.u32DataWidth | \
                         stcDmaInit.u32IntEn      | stcDmaLlpInit.u32State    | stcDmaLlpInit.u32Mode;

    DMA_ReconfigLlpCmd(AI_WB2_DMA_UNIT, AI_WB2_DMA_RX_CH, ENABLE);
    DMA_ReconfigCmd(AI_WB2_DMA_UNIT, ENABLE);
    AOS_SetTriggerEventSrc(AI_WB2_DMA_RX_RECONF_TRIG, AI_WB2_DMA_RX_RECONF_EVT);

    /* 注册DMA接收完成中断 */
    stcIrqSignConfig.enIntSrc    = AI_WB2_DMA_RX_INT_SRC;
    stcIrqSignConfig.enIRQn      = AI_WB2_DMA_RX_IRQn;
    stcIrqSignConfig.pfnCallback = &DmaRx_TC_IrqCallback;
    INTC_IrqSignIn(&stcIrqSignConfig);

    NVIC_ClearPendingIRQ(AI_WB2_DMA_RX_IRQn);
    NVIC_SetPriority(AI_WB2_DMA_RX_IRQn, DDL_IRQ_PRIO_06);
    NVIC_EnableIRQ(AI_WB2_DMA_RX_IRQn);

    /* 配置DMA接收触发源 */
    AOS_SetTriggerEventSrc(AI_WB2_DMA_RX_TRIG_SEL, AI_WB2_DMA_RX_TRIG_EVT);

    /* 使能DMA控制器 & 传输完成中断 */
    DMA_Cmd(AI_WB2_DMA_UNIT, ENABLE);
    DMA_TransCompleteIntCmd(AI_WB2_DMA_UNIT, AI_WB2_DMA_RX_TC_INT, ENABLE);
    DMA_ChCmd(AI_WB2_DMA_UNIT, AI_WB2_DMA_RX_CH, ENABLE);
}

static void Tmr0_Timeout_Init(uint16_t u16TimeoutBits)
{
    uint16_t u16Div;
    uint16_t u16Delay;
    uint16_t u16CompareValue;
    stc_tmr0_init_t stcTmr0Init;

    FCG_Fcg2PeriphClockCmd(AI_WB2_TMR0_CLK, ENABLE);

    TMR0_StructInit(&stcTmr0Init);
    stcTmr0Init.u32ClockSrc = TMR0_CLK_SRC_XTAL32;
    stcTmr0Init.u32ClockDiv = TMR0_CLK_DIV8;
    stcTmr0Init.u32Func     = TMR0_FUNC_CMP;

    if (TMR0_CLK_DIV1 == stcTmr0Init.u32ClockDiv) {
        u16Delay = 7U;
    } else if (TMR0_CLK_DIV2 == stcTmr0Init.u32ClockDiv) {
        u16Delay = 5U;
    } else {
        u16Delay = 3U;
    }

    u16Div = (uint16_t)1U << (stcTmr0Init.u32ClockDiv >> TMR0_BCONR_CKDIVA_POS);
    u16CompareValue = ((u16TimeoutBits + u16Div - 1U) / u16Div) - u16Delay;
    stcTmr0Init.u16CompareValue = u16CompareValue;
    TMR0_Init(AI_WB2_TMR0_UNIT, AI_WB2_TMR0_CH, &stcTmr0Init);

    TMR0_HWStartCondCmd(AI_WB2_TMR0_UNIT, AI_WB2_TMR0_CH, ENABLE);
    TMR0_HWClearCondCmd(AI_WB2_TMR0_UNIT, AI_WB2_TMR0_CH, ENABLE);
}

static void Usart_StopTimeoutTimer(void)
{
    uint32_t u32ClrMask;
    uint32_t u32SetMask;
    uint32_t u32BitOffset;
    CM_TMR0_TypeDef *TMR0x = AI_WB2_TMR0_UNIT;
    uint32_t u32Ch = AI_WB2_TMR0_CH;

    u32BitOffset = 16UL * u32Ch;
    u32ClrMask = (TMR0_BCONR_SYNCLKA | TMR0_BCONR_SYNSA) << u32BitOffset;
    u32SetMask = TMR0_BCONR_SYNCLKA << u32BitOffset;
    MODIFY_REG32(TMR0x->BCONR, u32ClrMask, u32SetMask);

    u32ClrMask = (TMR0_BCONR_SYNCLKA | TMR0_BCONR_SYNSA | TMR0_BCONR_CSTA) << u32BitOffset;
    u32SetMask = TMR0_BCONR_SYNSA << u32BitOffset;
    MODIFY_REG32(TMR0x->BCONR, u32ClrMask, u32SetMask);
}

static void UsartDma_Init(void)
{
    stc_usart_uart_init_t stcUartInit;
    stc_irq_signin_config_t stcIrqSignConfig;

    /* 开启外设时钟 */
    FCG_Fcg1PeriphClockCmd(AI_WB2_USART_CLK, ENABLE);
    FCG_Fcg0PeriphClockCmd(AI_WB2_DMA_CLK, ENABLE);
    FCG_Fcg0PeriphClockCmd(AI_WB2_AOS_CLK, ENABLE);

    /* 配置GPIO复用 */
    GPIO_SetFunc(AI_WB2_TX_PORT, AI_WB2_TX_PIN, AI_WB2_TX_FUNC);
    GPIO_SetFunc(AI_WB2_RX_PORT, AI_WB2_RX_PIN, AI_WB2_RX_FUNC);

    /* 初始化UART参数 */
    USART_UART_StructInit(&stcUartInit);
    stcUartInit.u32ClockDiv    = USART_CLK_DIV1;
    stcUartInit.u32CKOutput    = USART_CK_OUTPUT_ENABLE;
    stcUartInit.u32Baudrate    = AI_WB2_USART_BAUDRATE;
    stcUartInit.u32DataWidth   = USART_DATA_WIDTH_8BIT;
    stcUartInit.u32StopBit     = USART_STOPBIT_1BIT;
    stcUartInit.u32Parity      = USART_PARITY_NONE;
    stcUartInit.u32OverSampleBit = USART_OVER_SAMPLE_16BIT;
    USART_UART_Init(AI_WB2_USART_UNIT, &stcUartInit, NULL);

    /* 初始化DMA通道 */
    DmaTx_Init();
    DmaRx_Init();

    /* 初始化超时定时器 */
    Tmr0_Timeout_Init(AI_WB2_TIMEOUT_BITS);

    /* 注册接收超时中断 */
    stcIrqSignConfig.enIntSrc    = AI_WB2_USART_RTO_INT_SRC;
    stcIrqSignConfig.enIRQn      = AI_WB2_USART_RTO_IRQn;
    stcIrqSignConfig.pfnCallback = &Usart_RxTimeout_IrqCallback;
    INTC_IrqSignIn(&stcIrqSignConfig);
    NVIC_ClearPendingIRQ(AI_WB2_USART_RTO_IRQn);
    NVIC_SetPriority(AI_WB2_USART_RTO_IRQn, DDL_IRQ_PRIO_06);
    NVIC_EnableIRQ(AI_WB2_USART_RTO_IRQn);

    /* 注册接收错误中断 */
    stcIrqSignConfig.enIntSrc    = AI_WB2_USART_ERR_INT_SRC;
    stcIrqSignConfig.enIRQn      = AI_WB2_USART_ERR_IRQn;
    stcIrqSignConfig.pfnCallback = &Usart_RxError_IrqCallback;
    INTC_IrqSignIn(&stcIrqSignConfig);
    NVIC_ClearPendingIRQ(AI_WB2_USART_ERR_IRQn);
    NVIC_SetPriority(AI_WB2_USART_ERR_IRQn, DDL_IRQ_PRIO_06);
    NVIC_EnableIRQ(AI_WB2_USART_ERR_IRQn);

    /* 使能UART接收、接收超时功能 */
    USART_FuncCmd(AI_WB2_USART_UNIT, USART_RX | USART_RX_TIMEOUT | USART_INT_RX_TIMEOUT, ENABLE);
    USART_FuncCmd(AI_WB2_USART_UNIT, USART_TX, ENABLE);
}

/* ========================== DMA发送函数 ========================== */
static int32_t UsartDma_Send(const uint8_t *data, uint16_t len)
{
    if (len > AI_WB2_TX_BUF_SIZE) {
        return -1;
    }

    /* 等待上一次发送完成 */
    uint32_t start = SysTick_GetTick();
    while (SET != m_tx_done) {
        if ((SysTick_GetTick() - start) > 1000U) {
            return -2;
        }
    }

    /* 拷贝数据到发送缓冲区 */
    memcpy(m_tx_buf, data, len);
    m_tx_done = RESET;

    /* 配置传输长度并启动DMA */
    DMA_SetTransCount(AI_WB2_DMA_UNIT, AI_WB2_DMA_TX_CH, len);
    DMA_ChCmd(AI_WB2_DMA_UNIT, AI_WB2_DMA_TX_CH, ENABLE);

    /* 等待发送完成 */
    start = SysTick_GetTick();
    while (SET != m_tx_done) {
        if ((SysTick_GetTick() - start) > 1000U) {
            return -2;
        }
    }

    return 0;
}

/* ========================== DMA接收处理 ========================== */
static void MoveDmaToParseBuf(void)
{
    if (RESET == m_rx_frame_end) {
        return;
    }

    /* 把一帧数据搬入解析缓冲区 */
    for (uint16_t i = 0; i < m_rx_frame_len; i++) {
        uint16_t next_head = (m_parse_head + 1) % AI_WB2_RX_BUF_SIZE;
        if (next_head != m_parse_tail) {
            m_parse_buf[m_parse_head] = m_rx_dma_buf[i];
            m_parse_head = next_head;
        }
    }

    m_rx_frame_end = RESET;
    /* 重新开启接收超时 */
    USART_FuncCmd(AI_WB2_USART_UNIT, USART_RX_TIMEOUT | USART_INT_RX_TIMEOUT, ENABLE);
}

static bool ParseBuf_GetByte(uint8_t *ch)
{
    if (m_parse_head == m_parse_tail) {
        return false;
    }
    *ch = m_parse_buf[m_parse_tail];
    m_parse_tail = (m_parse_tail + 1) % AI_WB2_RX_BUF_SIZE;
    return true;
}

static void ClearParseBuf(void)
{
    __disable_irq();
    m_parse_head = 0;
    m_parse_tail = 0;
    m_rx_frame_end = RESET;
    m_rx_frame_len = 0;
    __enable_irq();
}

/* ========================== AT指令核心交互 ========================== */
static int32_t SendATCmd(const char *cmd, const char *expect_ack,
                         char *resp_buf, uint16_t resp_len, uint32_t timeout_ms)
{
    char send_buf[256];
    uint16_t cmd_len;

    ClearParseBuf();

    cmd_len = snprintf(send_buf, sizeof(send_buf), "%s\r\n", cmd);
    if (UsartDma_Send((uint8_t *)send_buf, cmd_len) != 0) {
        return -3;
    }

    if (expect_ack == NULL) {
        return 0;
    }
    return WaitForResponse(expect_ack, resp_buf, resp_len, timeout_ms);
}

static int32_t WaitForResponse(const char *expect, char *resp_buf,
                               uint16_t resp_len, uint32_t timeout_ms)
{
    uint16_t idx = 0;
    uint8_t ch;
    uint32_t start_tick = SysTick_GetTick();

    if (resp_buf != NULL && resp_len > 0) {
        memset(resp_buf, 0, resp_len);
    }

    while (1) {
        /* 兜底搬移帧数据 */
        MoveDmaToParseBuf();

        if (ParseBuf_GetByte(&ch)) {
            if (resp_buf != NULL && idx < resp_len - 1) {
                resp_buf[idx++] = (char)ch;
            }
            if (resp_buf != NULL && strstr(resp_buf, expect) != NULL) {
                return 0;
            }
            if (resp_buf != NULL && strstr(resp_buf, "ERROR") != NULL) {
                return -2;
            }
        }

        if ((SysTick_GetTick() - start_tick) > timeout_ms) {
            return -1;
        }
    }
}

/* ========================== 基础功能实现 ========================== */
int32_t AI_WB2_Init(void)
{
    int32_t ret;
    char tmp[256];

    /* 外设寄存器写解锁 */
    LL_PERIPH_WE(LL_PERIPH_GPIO | LL_PERIPH_FCG | LL_PERIPH_PWC_CLK_RMU);

    UsartDma_Init();
    DDL_DelayMS(100);

    /* 测试AT通信 */
    ret = AI_WB2_TestAT();
    if (ret != 0) {
        return -1;
    }

    /* 关闭回显 */
    SendATCmd("ATE0", "OK", NULL, 0, AI_WB2_AT_TIMEOUT_MS);

    /* 获取固件版本 */
    if (SendATCmd("AT+GMR", "OK", tmp, sizeof(tmp), AI_WB2_AT_TIMEOUT_MS) == 0) {
        char *p = strstr(tmp, "firmware version:");
        if (p != NULL) {
            strncpy(m_version_str, p + 17, sizeof(m_version_str) - 1);
            char *end = strstr(m_version_str, "\r\n");
            if (end != NULL) {
                *end = '\0';
            }
        }
    }

    memset(m_socket_list, 0, sizeof(m_socket_list));
    m_socket_cnt = 0;

    /* 外设寄存器写保护 */
    LL_PERIPH_WP(LL_PERIPH_GPIO | LL_PERIPH_FCG | LL_PERIPH_PWC_CLK_RMU);

    return 0;
}

int32_t AI_WB2_TestAT(void)
{
    return SendATCmd("AT", "OK", NULL, 0, AI_WB2_AT_TIMEOUT_MS);
}

int32_t AI_WB2_Reset(void)
{
    int32_t ret = SendATCmd("AT+RST", "OK", NULL, 0, AI_WB2_AT_TIMEOUT_MS);
    if (ret == 0) {
        DDL_DelayMS(2000);
    }
    return ret;
}

const char* AI_WB2_GetVersion(void)
{
    return m_version_str;
}

/* ========================== WiFi功能实现 ========================== */
int32_t AI_WB2_SetWifiMode(ai_wb2_wifi_mode_t mode, bool save_flash)
{
    char cmd[32];
    snprintf(cmd, sizeof(cmd), "AT+WMODE=%d,%d", mode, save_flash ? 1 : 0);
    return SendATCmd(cmd, "OK", NULL, 0, AI_WB2_AT_TIMEOUT_MS);
}

int32_t AI_WB2_ConnectAP(const char *ssid, const char *password)
{
    char cmd[128];
    char resp[256];

    AI_WB2_SetWifiMode(AI_WB2_MODE_STA, false);
    DDL_DelayMS(500);

    snprintf(cmd, sizeof(cmd), "AT+WJAP=\"%s\",\"%s\"", ssid, password);
    if (SendATCmd(cmd, "OK", NULL, 0, AI_WB2_AT_TIMEOUT_MS) != 0) {
        return -1;
    }

    return WaitForResponse("+EVENT:WIFI_GOT_IP", resp,
                           sizeof(resp), AI_WB2_WIFI_CONN_TIMEOUT);
}

int32_t AI_WB2_SetAutoConnect(bool enable)
{
    char cmd[32];
    snprintf(cmd, sizeof(cmd), "AT+WAUTOCONN=%d", enable ? 1 : 0);
    return SendATCmd(cmd, "OK", NULL, 0, AI_WB2_AT_TIMEOUT_MS);
}

int32_t AI_WB2_GetStaInfo(char *buf, uint16_t buf_len)
{
    return SendATCmd("AT+STAINFO?", "OK", buf, buf_len, AI_WB2_AT_TIMEOUT_MS);
}

/* ========================== Socket功能实现 ========================== */
static uint8_t AllocConID(void)
{
    static uint8_t s_next_id = 1;
    return s_next_id++;
}

int32_t AI_WB2_SocketCreate(uint8_t *con_id, ai_wb2_sock_type_t type,
                            const char *remote_host, uint16_t remote_port,
                            uint16_t local_port)
{
    char cmd[128];
    char resp[256];
    uint8_t id = AllocConID();

    if (type == AI_WB2_SOCK_TCP_CLIENT || type == AI_WB2_SOCK_UDP_CLIENT) {
        snprintf(cmd, sizeof(cmd), "AT+SOCKET=%d,\"%s\",%d,,%d",
                 type, remote_host, remote_port, id);
    } else {
        snprintf(cmd, sizeof(cmd), "AT+SOCKET=%d,%d,,%d",
                 type, local_port, id);
    }

    if (SendATCmd(cmd, "connect success ConID=", resp, sizeof(resp), 5000) != 0) {
        return -1;
    }

    if (m_socket_cnt < AI_WB2_MAX_SOCKET_NUM) {
        m_socket_list[m_socket_cnt].con_id = id;
        m_socket_list[m_socket_cnt].type = type;
        m_socket_list[m_socket_cnt].is_connected = true;
        m_socket_cnt++;
    }

    if (con_id != NULL) {
        *con_id = id;
    }
    return 0;
}

int32_t AI_WB2_SocketDelete(uint8_t con_id)
{
    char cmd[32];
    snprintf(cmd, sizeof(cmd), "AT+SOCKETDEL=%d", con_id);
    return SendATCmd(cmd, "OK", NULL, 0, AI_WB2_AT_TIMEOUT_MS);
}

int32_t AI_WB2_SocketSend(uint8_t con_id, const uint8_t *data, uint16_t len)
{
    char cmd[32];
    char resp[16];
    int32_t ret;

    snprintf(cmd, sizeof(cmd), "AT+SOCKETSEND=%d,%d\r\n", con_id, len);

    ClearParseBuf();
    UsartDma_Send((uint8_t *)cmd, strlen(cmd));

    ret = WaitForResponse(">", resp, sizeof(resp), 1000);
    if (ret != 0) {
        return -1;
    }

    UsartDma_Send(data, len);
    return WaitForResponse("OK", resp, sizeof(resp), 3000);
}

int32_t AI_WB2_SocketSendLine(uint8_t con_id, const char *str)
{
    char cmd[256];
    uint16_t len = strlen(str);
    snprintf(cmd, sizeof(cmd), "AT+SOCKETSENDLINE=%d,%d,\"%s\"", con_id, len, str);
    return SendATCmd(cmd, "OK", NULL, 0, AI_WB2_AT_TIMEOUT_MS);
}

/* ========================== 接收数据处理与轮询 ========================== */
void AI_WB2_RegisterRecvCallback(ai_wb2_recv_cb_t cb)
{
    m_recv_cb = cb;
}

void AI_WB2_Poll(void)
{
    static char line_buf[512];
    static uint16_t line_idx = 0;
    uint8_t ch;

    MoveDmaToParseBuf();

    while (ParseBuf_GetByte(&ch)) {
        if (ch == '\n' && line_idx > 0) {
            line_buf[line_idx] = '\0';

            /* 解析Socket下行数据 */
            if (strstr(line_buf, "+EVENT:SocketDown") != NULL) {
                uint8_t con_id;
                uint16_t data_len;
                char *p = line_buf + strlen("+EVENT:SocketDown,");

                con_id = (uint8_t)atoi(p);
                p = strchr(p, ',') + 1;
                data_len = (uint16_t)atoi(p);

                p = strchr(p, ',');
                if (p != NULL && m_recv_cb != NULL) {
                    p++;
                    m_recv_cb(con_id, (uint8_t *)p, data_len);
                }
            }

            line_idx = 0;
        } else if (ch != '\r') {
            if (line_idx < sizeof(line_buf) - 1) {
                line_buf[line_idx++] = ch;
            }
        }
    }
}


