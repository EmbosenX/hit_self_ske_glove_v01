/**
 ******************************************************************************
 * @file    usart_bsp.c
 * @brief   USART串口BSP驱动，实现DMA收发和空闲中断接收
 ******************************************************************************
 */

#include "usart_bsp.h"
#include <string.h>
#include "app_usart_task.h"
/******************************************************************************
 * 内部硬件宏定义（已同步适配 USART1）
 ******************************************************************************/
/* DMA接收配置 */
#define RX_DMA_UNIT                     (CM_DMA1)
#define RX_DMA_CH                       (DMA_CH0)
#define RX_DMA_FCG_ENABLE()             (FCG_Fcg0PeriphClockCmd(FCG0_PERIPH_DMA1, ENABLE))
#define RX_DMA_TRIG_SEL                 (AOS_DMA1_0)
#define RX_DMA_TRIG_EVT_SRC             (EVT_SRC_USART1_RI)    /* 改为USART1接收事件 */
#define RX_DMA_RECONF_TRIG_SEL          (AOS_DMA_RC)
#define RX_DMA_RECONF_TRIG_EVT_SRC      (EVT_SRC_AOS_STRG)
#define RX_DMA_TC_FLAG                  (DMA_FLAG_TC_CH0)
#define RX_DMA_TC_IRQn                  (INT000_IRQn)
#define RX_DMA_TC_INT_SRC               (INT_SRC_DMA1_TC0)

/* DMA发送配置 */
#define TX_DMA_UNIT                     (CM_DMA2)
#define TX_DMA_CH                       (DMA_CH0)
#define TX_DMA_FCG_ENABLE()             (FCG_Fcg0PeriphClockCmd(FCG0_PERIPH_DMA2, ENABLE))
#define TX_DMA_TRIG_SEL                 (AOS_DMA2_0)
#define TX_DMA_TRIG_EVT_SRC             (EVT_SRC_USART1_TI)    /* 改为USART1发送事件 */
#define TX_DMA_TC_FLAG                  (DMA_FLAG_TC_CH0)
#define TX_DMA_TC_IRQn                  (INT001_IRQn)
#define TX_DMA_TC_INT_SRC               (INT_SRC_DMA2_TC0)

/* 超时定时器配置（无需修改） */
#define TMR0_UNIT                       (CM_TMR0_1)
#define TMR0_CH                         (TMR0_CH_B)
#define TMR0_FCG_ENABLE()               (FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMR0_1, ENABLE))

/* USART中断配置（已同步改为USART1） */
#define USART_TX_CPLT_IRQn              (INT002_IRQn)
#define USART_TX_CPLT_INT_SRC           (INT_SRC_USART1_TCI)   /* 发送完成中断源 */
#define USART_RX_ERR_IRQn               (INT003_IRQn)
#define USART_RX_ERR_INT_SRC            (INT_SRC_USART1_EI)    /* 接收错误中断源 */
#define USART_RX_TIMEOUT_IRQn           (INT004_IRQn)
#define USART_RX_TIMEOUT_INT_SRC        (INT_SRC_USART1_RTO)   /* 接收超时中断源 */

/******************************************************************************
 * 静态全局变量
 ******************************************************************************/
static uint8_t m_au8RxBuf[USART_BSP_MAX_FRAME_LEN];
static __IO uint8_t m_u8RxFrameDone = 0U;
static __IO uint16_t m_u16RxLen = 0U;

static __IO uint8_t m_u8TxBusy = 0U;
static stc_dma_llp_descriptor_t m_stcLlpDesc;

/******************************************************************************
 * 内部静态函数声明
 ******************************************************************************/
static void DMA_Config(void);
static void TMR0_Config(uint16_t u16TimeoutBits);
static void USART_StopTimeoutTimer(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch);

/******************************************************************************
 * 中断回调函数
 ******************************************************************************/

/**
 * @brief  DMA接收完成中断回调
 */
static void RX_DMA_TC_IrqCallback(void)
{
    m_u8RxFrameDone = 1U;
    m_u16RxLen = USART_BSP_MAX_FRAME_LEN;

    USART_FuncCmd(USART_BSP_UNIT, USART_RX_TIMEOUT, DISABLE);
    DMA_ClearTransCompleteStatus(RX_DMA_UNIT, RX_DMA_TC_FLAG);

    /* 调用接收完成回调 */
    USART_BSP_RxCpltCallback(m_u16RxLen);
}

/**
 * @brief  DMA发送完成中断回调
 */
static void TX_DMA_TC_IrqCallback(void)
{
    /* 开启发送完成中断，等待移位寄存器空 */
    USART_FuncCmd(USART_BSP_UNIT, USART_INT_TX_CPLT, ENABLE);
    DMA_ClearTransCompleteStatus(TX_DMA_UNIT, TX_DMA_TC_FLAG);
}

/**
 * @brief  接收超时中断回调（不定长帧核心）
 */
static void USART_RxTimeout_IrqCallback(void)
{
    if (m_u8RxFrameDone == 0U) {
        m_u8RxFrameDone = 1U;
        m_u16RxLen = USART_BSP_MAX_FRAME_LEN - (uint16_t)DMA_GetTransCount(RX_DMA_UNIT, RX_DMA_CH);

        /* 触发DMA重配置，为下一次接收做准备 */
        AOS_SW_Trigger();

        /* 调用接收完成回调 */
        USART_BSP_RxCpltCallback(m_u16RxLen);
    }

    USART_StopTimeoutTimer(TMR0_UNIT, TMR0_CH);
    USART_ClearStatus(USART_BSP_UNIT, USART_FLAG_RX_TIMEOUT);
}

/**
 * @brief  发送完成中断回调
 */
static void USART_TxComplete_IrqCallback(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    USART_FuncCmd(USART_BSP_UNIT, (USART_TX | USART_INT_TX_CPLT), DISABLE);
    m_u8TxBusy = 0U;

    /* 发送任务通知：唤醒阻塞等待发送完成的任务 */
    if (xUsartTaskHandle != NULL) {
        vTaskNotifyGiveFromISR(xUsartTaskHandle, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
    /* 调用发送完成回调 */
    USART_BSP_TxCpltCallback();
}

/**
 * @brief  接收错误中断回调
 */
static void USART_RxError_IrqCallback(void)
{
    /* 读空数据寄存器，清除溢出错误 */
    (void)USART_ReadData(USART_BSP_UNIT);
    USART_ClearStatus(USART_BSP_UNIT, (USART_FLAG_PARITY_ERR | USART_FLAG_FRAME_ERR | USART_FLAG_OVERRUN));
}

/******************************************************************************
 * 内部硬件初始化
 ******************************************************************************/

/**
 * @brief  DMA配置
 */
static void DMA_Config(void)
{
    stc_dma_init_t stcDmaInit;
    stc_dma_llp_init_t stcDmaLlpInit;
    stc_irq_signin_config_t stcIrqSignConfig;

    /* 使能时钟 */
    RX_DMA_FCG_ENABLE();
    TX_DMA_FCG_ENABLE();
    FCG_Fcg0PeriphClockCmd(FCG0_PERIPH_AOS, ENABLE);

    /************************ 接收DMA ************************/
    (void)DMA_StructInit(&stcDmaInit);
    stcDmaInit.u32IntEn = DMA_INT_ENABLE;
    stcDmaInit.u32BlockSize = 1UL;
    stcDmaInit.u32TransCount = USART_BSP_MAX_FRAME_LEN;
    stcDmaInit.u32DataWidth = DMA_DATAWIDTH_8BIT;
    stcDmaInit.u32SrcAddr = (uint32_t)(&USART_BSP_UNIT->RDR);
    stcDmaInit.u32DestAddr = (uint32_t)m_au8RxBuf;
    stcDmaInit.u32SrcAddrInc = DMA_SRC_ADDR_FIX;
    stcDmaInit.u32DestAddrInc = DMA_DEST_ADDR_INC;
    (void)DMA_Init(RX_DMA_UNIT, RX_DMA_CH, &stcDmaInit);

    /* 链表重配置：接收超时后自动重置DMA */
    (void)DMA_LlpStructInit(&stcDmaLlpInit);
    stcDmaLlpInit.u32State = DMA_LLP_ENABLE;
    stcDmaLlpInit.u32Mode  = DMA_LLP_WAIT;
    stcDmaLlpInit.u32Addr  = (uint32_t)&m_stcLlpDesc;
    (void)DMA_LlpInit(RX_DMA_UNIT, RX_DMA_CH, &stcDmaLlpInit);

    m_stcLlpDesc.SARx   = stcDmaInit.u32SrcAddr;
    m_stcLlpDesc.DARx   = stcDmaInit.u32DestAddr;
    m_stcLlpDesc.DTCTLx = (stcDmaInit.u32TransCount << DMA_DTCTL_CNT_POS) | (stcDmaInit.u32BlockSize << DMA_DTCTL_BLKSIZE_POS);
    m_stcLlpDesc.LLPx   = (uint32_t)&m_stcLlpDesc;
    m_stcLlpDesc.CHCTLx = stcDmaInit.u32SrcAddrInc | stcDmaInit.u32DestAddrInc | stcDmaInit.u32DataWidth |
                          stcDmaInit.u32IntEn      | stcDmaLlpInit.u32State    | stcDmaLlpInit.u32Mode;

    DMA_ReconfigLlpCmd(RX_DMA_UNIT, RX_DMA_CH, ENABLE);
    DMA_ReconfigCmd(RX_DMA_UNIT, ENABLE);
    AOS_SetTriggerEventSrc(RX_DMA_RECONF_TRIG_SEL, RX_DMA_RECONF_TRIG_EVT_SRC);

    /* 接收DMA中断注册 */
    stcIrqSignConfig.enIntSrc = RX_DMA_TC_INT_SRC;
    stcIrqSignConfig.enIRQn  = RX_DMA_TC_IRQn;
    stcIrqSignConfig.pfnCallback = &RX_DMA_TC_IrqCallback;
    (void)INTC_IrqSignIn(&stcIrqSignConfig);
    NVIC_ClearPendingIRQ(stcIrqSignConfig.enIRQn);
    NVIC_SetPriority(stcIrqSignConfig.enIRQn, DDL_IRQ_PRIO_05);
    NVIC_EnableIRQ(stcIrqSignConfig.enIRQn);

    AOS_SetTriggerEventSrc(RX_DMA_TRIG_SEL, RX_DMA_TRIG_EVT_SRC);
    DMA_Cmd(RX_DMA_UNIT, ENABLE);
    DMA_TransCompleteIntCmd(RX_DMA_UNIT, RX_DMA_TC_FLAG, ENABLE);
    (void)DMA_ChCmd(RX_DMA_UNIT, RX_DMA_CH, ENABLE);

    /************************ 发送DMA ************************/
    (void)DMA_StructInit(&stcDmaInit);
    stcDmaInit.u32IntEn = DMA_INT_ENABLE;
    stcDmaInit.u32BlockSize = 1UL;
    stcDmaInit.u32TransCount = 0U;
    stcDmaInit.u32DataWidth = DMA_DATAWIDTH_8BIT;
    stcDmaInit.u32SrcAddr = (uint32_t)m_au8RxBuf;
    stcDmaInit.u32DestAddr = (uint32_t)(&USART_BSP_UNIT->TDR);
    stcDmaInit.u32SrcAddrInc = DMA_SRC_ADDR_INC;
    stcDmaInit.u32DestAddrInc = DMA_DEST_ADDR_FIX;
    (void)DMA_Init(TX_DMA_UNIT, TX_DMA_CH, &stcDmaInit);

    /* 发送DMA中断注册 */
    stcIrqSignConfig.enIntSrc = TX_DMA_TC_INT_SRC;
    stcIrqSignConfig.enIRQn  = TX_DMA_TC_IRQn;
    stcIrqSignConfig.pfnCallback = &TX_DMA_TC_IrqCallback;
    (void)INTC_IrqSignIn(&stcIrqSignConfig);
    NVIC_ClearPendingIRQ(stcIrqSignConfig.enIRQn);
    NVIC_SetPriority(stcIrqSignConfig.enIRQn, DDL_IRQ_PRIO_05);
    NVIC_EnableIRQ(stcIrqSignConfig.enIRQn);

    AOS_SetTriggerEventSrc(TX_DMA_TRIG_SEL, TX_DMA_TRIG_EVT_SRC);
    DMA_Cmd(TX_DMA_UNIT, ENABLE);
    DMA_TransCompleteIntCmd(TX_DMA_UNIT, TX_DMA_TC_FLAG, ENABLE);
}
/**
 * @brief  超时定时器配置（适配USART1+内部LRC）
 */
static void TMR0_Config(uint16_t u16TimeoutBits)
{
    uint16_t u16Div;
    uint16_t u16Delay;
    uint16_t u16CompareValue;
    stc_tmr0_init_t stcTmr0Init;

    /* 使能TMR0外设时钟 */
    TMR0_FCG_ENABLE();

    /* 时钟源改为内部低速RC，无需外部晶振 */
    stcTmr0Init.u32ClockSrc = TMR0_CLK_SRC_LRC;
    stcTmr0Init.u32ClockDiv = TMR0_CLK_DIV8;
    stcTmr0Init.u32Func     = TMR0_FUNC_CMP;

    /* 不同分频下的硬件延迟补偿值 */
    if (TMR0_CLK_DIV1 == stcTmr0Init.u32ClockDiv) {
        u16Delay = 7U;
    } else if (TMR0_CLK_DIV2 == stcTmr0Init.u32ClockDiv) {
        u16Delay = 5U;
    } else if ((TMR0_CLK_DIV4 == stcTmr0Init.u32ClockDiv) ||
               (TMR0_CLK_DIV8 == stcTmr0Init.u32ClockDiv) ||
               (TMR0_CLK_DIV16 == stcTmr0Init.u32ClockDiv)) {
        u16Delay = 3U;
    } else {
        u16Delay = 2U;
    }

    /* 计算分频系数与比较值 */
    u16Div = (uint16_t)1U << (stcTmr0Init.u32ClockDiv >> TMR0_BCONR_CKDIVA_POS);
    u16CompareValue = ((u16TimeoutBits + u16Div - 1U) / u16Div) - u16Delay;
    stcTmr0Init.u16CompareValue = u16CompareValue;
    (void)TMR0_Init(TMR0_UNIT, TMR0_CH, &stcTmr0Init);

    /* 使能硬件启动、硬件清零，配合USART接收超时 */
    TMR0_HWStartCondCmd(TMR0_UNIT, TMR0_CH, ENABLE);
    TMR0_HWClearCondCmd(TMR0_UNIT, TMR0_CH, ENABLE);
}

/**
 * @brief  停止超时定时器
 */
static void USART_StopTimeoutTimer(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch)
{
    uint32_t u32ClrMask;
    uint32_t u32SetMask;
    uint32_t u32BitOffset;

    u32BitOffset = 16UL * u32Ch;
    u32ClrMask = (TMR0_BCONR_SYNCLKA | TMR0_BCONR_SYNSA) << u32BitOffset;
    u32SetMask = TMR0_BCONR_SYNCLKA << u32BitOffset;
    MODIFY_REG32(TMR0x->BCONR, u32ClrMask, u32SetMask);

    u32ClrMask = (TMR0_BCONR_SYNCLKA | TMR0_BCONR_SYNSA | TMR0_BCONR_CSTA) << u32BitOffset;
    u32SetMask = TMR0_BCONR_SYNSA << u32BitOffset;
    MODIFY_REG32(TMR0x->BCONR, u32ClrMask, u32SetMask);
}

/******************************************************************************
 * 对外接口实现
 ******************************************************************************/

/**
 * @brief  USART BSP初始化
 */
void USART_BSP_Init(void)
{
    stc_usart_uart_init_t stcUartInit;
    stc_irq_signin_config_t stcIrqSigninConfig;

    /* 1. GPIO引脚功能配置 */
    GPIO_SetFunc(USART_BSP_RX_PORT, USART_BSP_RX_PIN, USART_BSP_RX_FUNC);
    GPIO_SetFunc(USART_BSP_TX_PORT, USART_BSP_TX_PIN, USART_BSP_TX_FUNC);

    /* 2. 外设时钟使能：改为USART1时钟 */
    FCG_Fcg1PeriphClockCmd(FCG1_PERIPH_USART1, ENABLE);

    /* 3. DMA初始化 */
    DMA_Config();

    /* 4. 超时定时器初始化 */
    TMR0_Config(USART_BSP_TIMEOUT_BITS);

    /* 5. USART串口初始化 */
    (void)USART_UART_StructInit(&stcUartInit);
    stcUartInit.u32ClockDiv = USART_CLK_DIV1;
    stcUartInit.u32CKOutput = USART_CK_OUTPUT_ENABLE;
    stcUartInit.u32Baudrate = USART_BSP_BAUDRATE;
    stcUartInit.u32OverSampleBit = USART_OVER_SAMPLE_8BIT;
    (void)USART_UART_Init(USART_BSP_UNIT, &stcUartInit, NULL);

    /* 6. 中断注册 */
    /* 发送完成中断 */
    stcIrqSigninConfig.enIRQn = USART_TX_CPLT_IRQn;
    stcIrqSigninConfig.enIntSrc = USART_TX_CPLT_INT_SRC;
    stcIrqSigninConfig.pfnCallback = &USART_TxComplete_IrqCallback;
    (void)INTC_IrqSignIn(&stcIrqSigninConfig);
    NVIC_ClearPendingIRQ(stcIrqSigninConfig.enIRQn);
    NVIC_SetPriority(stcIrqSigninConfig.enIRQn, DDL_IRQ_PRIO_05);
    NVIC_EnableIRQ(stcIrqSigninConfig.enIRQn);

    /* 接收错误中断 */
    stcIrqSigninConfig.enIRQn = USART_RX_ERR_IRQn;
    stcIrqSigninConfig.enIntSrc = USART_RX_ERR_INT_SRC;
    stcIrqSigninConfig.pfnCallback = &USART_RxError_IrqCallback;
    (void)INTC_IrqSignIn(&stcIrqSigninConfig);
    NVIC_ClearPendingIRQ(stcIrqSigninConfig.enIRQn);
    NVIC_SetPriority(stcIrqSigninConfig.enIRQn, DDL_IRQ_PRIO_05);
    NVIC_EnableIRQ(stcIrqSigninConfig.enIRQn);

    /* 接收超时中断 */
    stcIrqSigninConfig.enIRQn = USART_RX_TIMEOUT_IRQn;
    stcIrqSigninConfig.enIntSrc = USART_RX_TIMEOUT_INT_SRC;
    stcIrqSigninConfig.pfnCallback = &USART_RxTimeout_IrqCallback;
    (void)INTC_IrqSignIn(&stcIrqSigninConfig);
    NVIC_ClearPendingIRQ(stcIrqSigninConfig.enIRQn);
    NVIC_SetPriority(stcIrqSigninConfig.enIRQn, DDL_IRQ_PRIO_05);
    NVIC_EnableIRQ(stcIrqSigninConfig.enIRQn);

    /* 7. 开启接收 */
    USART_FuncCmd(USART_BSP_UNIT,
                  (USART_RX | USART_INT_RX | USART_RX_TIMEOUT | USART_INT_RX_TIMEOUT),
                  ENABLE);

    m_u8RxFrameDone = 0U;
    m_u8TxBusy = 0U;
}

/**
 * @brief  DMA方式发送数据
 */
int32_t USART_BSP_Send(const uint8_t *pu8Data, uint16_t u16Len)
{
    uint32_t u32Timeout = 0x1000UL;

    if ((pu8Data == NULL) || (u16Len == 0U) || (u16Len > USART_BSP_MAX_FRAME_LEN)) {
        return LL_ERR_INVD_PARAM;
    }

    /* 忙检测：软件标志 + 硬件通道状态双重校验 */
    if ((m_u8TxBusy != 0U) || (SET == DMA_GetTransStatus(TX_DMA_UNIT, DMA_STAT_TRANS_CH0))) {
        return LL_ERR_BUSY;
    }

    /* 先置忙标志，再操作硬件，防止中断提前触发清标志 */
    m_u8TxBusy = 1U;

    /* 关闭DMA通道，等待硬件停止 */
    DMA_ChCmd(TX_DMA_UNIT, TX_DMA_CH, DISABLE);
    while ((SET == DMA_GetTransStatus(TX_DMA_UNIT, DMA_STAT_TRANS_CH0)) && (u32Timeout-- > 0U)) {
        ;
    }

    /* 清除所有残留中断标志：防止旧标志误触发 */
    DMA_ClearTransCompleteStatus(TX_DMA_UNIT, DMA_FLAG_TC_CH0 | DMA_FLAG_BTC_CH0);
    DMA_ClearErrStatus(TX_DMA_UNIT, DMA_FLAG_TRANS_ERR_CH0 | DMA_FLAG_REQ_ERR_CH0);
    USART_ClearStatus(USART_BSP_UNIT, USART_FLAG_TX_CPLT);
    /* 重配置DMA参数 */
    DMA_SetSrcAddr(TX_DMA_UNIT, TX_DMA_CH, (uint32_t)pu8Data);
    DMA_SetTransCount(TX_DMA_UNIT, TX_DMA_CH, u16Len);
    DMA_ChCmd(TX_DMA_UNIT, TX_DMA_CH, ENABLE);
    USART_FuncCmd(USART_BSP_UNIT, USART_TX, ENABLE);
    return LL_OK;
}
/**
 * @brief  查询接收完成状态
 */
uint8_t USART_BSP_IsRxFrameDone(void)
{
    return m_u8RxFrameDone;
}

/**
 * @brief  获取接收帧数据
 */
uint16_t USART_BSP_GetRxFrame(uint8_t *pu8Buf, uint16_t u16BufLen)
{
    uint16_t u16CopyLen;

    if ((pu8Buf == NULL) || (m_u8RxFrameDone == 0U)) {
        return 0U;
    }

    u16CopyLen = (m_u16RxLen < u16BufLen) ? m_u16RxLen : u16BufLen;
    memcpy(pu8Buf, m_au8RxBuf, u16CopyLen);

    return u16CopyLen;
}

/**
 * @brief  清除接收标志，开启下一次接收
 */
void USART_BSP_ClearRxFlag(void)
{
    m_u8RxFrameDone = 0U;
    m_u16RxLen = 0U;
}

/******************************************************************************
 * 弱回调函数默认实现
 ******************************************************************************/
__WEAK void USART_BSP_RxCpltCallback(uint16_t u16Len)
{
    (void)u16Len;
}

__WEAK void USART_BSP_TxCpltCallback(void)
{
	
}


