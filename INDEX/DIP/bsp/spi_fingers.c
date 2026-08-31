/**
 *******************************************************************************
 * @file  spi_fingers.c
 * @brief This midware file provides firmware functions to fingers group spi.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2023-12-15       CDT             Add null pointer check
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2025, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "spi_fingers.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/*******************************************************************************
 * 硬件引脚与外设定义（完全匹配指定引脚）
 ******************************************************************************/
/* SPI3 外设 */
#define SPI_UNIT                (CM_SPI3)
#define SPI_CLK                 (FCG1_PERIPH_SPI3)
#define SPI_TX_EVT_SRC          (EVT_SRC_SPI3_SPTI)
#define SPI_RX_EVT_SRC          (EVT_SRC_SPI3_SPRI)

/* DMA 外设（沿用DMA1通道0/1） */
#define DMA_UNIT                (CM_DMA1)
#define DMA_CLK                 (FCG0_PERIPH_DMA1 | FCG0_PERIPH_AOS)
#define DMA_TX_CH               (DMA_CH0)
#define DMA_TX_TRIG_CH          (AOS_DMA1_0)
#define DMA_RX_CH               (DMA_CH1)
#define DMA_RX_INT_CH           (DMA_INT_TC_CH1)
#define DMA_RX_TRIG_CH          (AOS_DMA1_1)
#define DMA_RX_INT_SRC          (INT_SRC_DMA1_TC1)
#define DMA_RX_IRQ_NUM          (INT007_IRQn)

/* 5路片选 CS 引脚：1=拇指 2=食指 3=中指 4=无名指 5=小指 */
#define SPI_CS1_PORT            GPIO_PORT_B
#define SPI_CS1_PIN             GPIO_PIN_15     /* THUMB */

#define SPI_CS2_PORT            GPIO_PORT_D
#define SPI_CS2_PIN             GPIO_PIN_15     /* INDEX */

#define SPI_CS3_PORT            GPIO_PORT_D
#define SPI_CS3_PIN             GPIO_PIN_14     /* MIDDLE */

#define SPI_CS4_PORT            GPIO_PORT_D
#define SPI_CS4_PIN             GPIO_PIN_13     /* RING */

#define SPI_CS5_PORT            GPIO_PORT_D
#define SPI_CS5_PIN             GPIO_PIN_12     /* PINKY */

/* SPI1 总线引脚与复用功能号
 * 注：若编译后SPI无输出，请根据实际数据手册调整功能号，
 * HC32F460 SPI1常用功能号为 GPIO_FUNC_4，部分重映射需配合SYSCFG配置 */
#define SPI_SCK_PORT            GPIO_PORT_B
#define SPI_SCK_PIN             GPIO_PIN_14
#define SPI_SCK_FUNC            GPIO_FUNC_43 //SPI3

#define SPI_MOSI_PORT           GPIO_PORT_D
#define SPI_MOSI_PIN            GPIO_PIN_11
#define SPI_MOSI_FUNC           GPIO_FUNC_40 //SPI3

#define SPI_MISO_PORT           GPIO_PORT_D
#define SPI_MISO_PIN            GPIO_PIN_10
#define SPI_MISO_FUNC           GPIO_FUNC_41 //SPI3

/* 传输超时（约5ms@200MHz主频） */
#define SPI_TRANS_TIMEOUT       500000UL
/*******************************************************************************
 * 局部变量
 ******************************************************************************/
static SemaphoreHandle_t g_spi_mutex = NULL;
static __IO en_flag_status_t enRxCompleteFlag = RESET;

static uint8_t m_u8TxBuf[SPI_MAX_FRAME_LEN];
static uint8_t m_u8RxBuf[SPI_MAX_FRAME_LEN];
/*******************************************************************************
 * 局部函数声明
 ******************************************************************************/
static uint16_t CRC16_CCITT(const uint8_t *pData, uint16_t len);

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
 /**
 * @brief  CRC16-CCITT 校验算法（与从机端完全一致）
 */
static uint16_t CRC16_CCITT(const uint8_t *pData, uint16_t len)
{
    uint16_t crc = 0xFFFFU;
    const uint16_t poly = 0x1021U;
    uint16_t i, j;

    for (i = 0U; i < len; i++)
    {
        crc ^= ((uint16_t)pData[i] << 8U);
        for (j = 0U; j < 8U; j++)
        {
            if (crc & 0x8000U) {
                crc = (crc << 1U) ^ poly;
            } else {
                crc = crc << 1U;
            }
        }
    }
    return crc;
}
/**
 * @brief  DMA接收完成中断回调
 */
static void DMA_TransCompleteCallback(void)
{
    enRxCompleteFlag = SET;
    DMA_ClearTransCompleteStatus(DMA_UNIT, DMA_RX_INT_CH);
}

/**
 * @brief  SPI主机硬件初始化
 */
void Fingers_SPI_Config(void)
{
    stc_spi_init_t stcSpiInit;
    stc_dma_init_t stcDmaInit;
    stc_irq_signin_config_t stcIrqSignConfig;
    stc_gpio_init_t stcGpioInit;

    /* 创建总线互斥量，多任务安全 */
    g_spi_mutex = xSemaphoreCreateMutex();
    enRxCompleteFlag = RESET;

    /* GPIO 默认配置 */
    (void)GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinDrv = PIN_HIGH_DRV;
    stcGpioInit.u16PinDir = PIN_DIR_OUT;

    /**************** 1. 初始化 5 路 CS 引脚，默认全部拉高 ****************/
    (void)GPIO_Init(SPI_CS1_PORT, SPI_CS1_PIN, &stcGpioInit);
    GPIO_SetPins(SPI_CS1_PORT, SPI_CS1_PIN);
    (void)GPIO_Init(SPI_CS2_PORT, SPI_CS2_PIN, &stcGpioInit);
    GPIO_SetPins(SPI_CS2_PORT, SPI_CS2_PIN);
    (void)GPIO_Init(SPI_CS3_PORT, SPI_CS3_PIN, &stcGpioInit);
    GPIO_SetPins(SPI_CS3_PORT, SPI_CS3_PIN);
    (void)GPIO_Init(SPI_CS4_PORT, SPI_CS4_PIN, &stcGpioInit);
    GPIO_SetPins(SPI_CS4_PORT, SPI_CS4_PIN);
    (void)GPIO_Init(SPI_CS5_PORT, SPI_CS5_PIN, &stcGpioInit);
    GPIO_SetPins(SPI_CS5_PORT, SPI_CS5_PIN);

    /**************** 2. 初始化 SPI 总线引脚复用 ****************/
    GPIO_SetFunc(SPI_SCK_PORT,  SPI_SCK_PIN,  SPI_SCK_FUNC);
    GPIO_SetFunc(SPI_MOSI_PORT, SPI_MOSI_PIN, SPI_MOSI_FUNC);
    GPIO_SetFunc(SPI_MISO_PORT, SPI_MISO_PIN, SPI_MISO_FUNC);

    /**************** 3. SPI 外设配置：Mode3、主机、8bit、MSB ****************/
    FCG_Fcg1PeriphClockCmd(SPI_CLK, ENABLE);
    (void)SPI_StructInit(&stcSpiInit);
    stcSpiInit.u32WireMode          = SPI_4_WIRE;
    stcSpiInit.u32TransMode         = SPI_FULL_DUPLEX;
    stcSpiInit.u32MasterSlave       = SPI_MASTER;
    stcSpiInit.u32Parity            = SPI_PARITY_INVD;
    stcSpiInit.u32SpiMode           = SPI_MD_3;        /* 协议约定 Mode3，与从机严格一致 */
    stcSpiInit.u32BaudRatePrescaler = SPI_BR_CLK_DIV8; /* 约25MHz@200MHz，可按需调整 */
    stcSpiInit.u32DataBits          = SPI_DATA_SIZE_8BIT;
    stcSpiInit.u32FirstBit          = SPI_FIRST_MSB;
    stcSpiInit.u32FrameLevel        = SPI_1_FRAME;
    (void)SPI_Init(SPI_UNIT, &stcSpiInit);

    /**************** 4. DMA 配置 ****************/
    FCG_Fcg0PeriphClockCmd(DMA_CLK, ENABLE);
    (void)DMA_StructInit(&stcDmaInit);
    stcDmaInit.u32BlockSize  = 1UL;
    stcDmaInit.u32TransCount = SPI_MAX_FRAME_LEN;
    stcDmaInit.u32DataWidth  = DMA_DATAWIDTH_8BIT;

    /* TX DMA：内存 → SPI_DR */
    stcDmaInit.u32SrcAddrInc  = DMA_SRC_ADDR_INC;
    stcDmaInit.u32DestAddrInc = DMA_DEST_ADDR_FIX;
    stcDmaInit.u32SrcAddr     = (uint32_t)m_u8TxBuf;
    stcDmaInit.u32DestAddr    = (uint32_t)(&SPI_UNIT->DR);
    (void)DMA_Init(DMA_UNIT, DMA_TX_CH, &stcDmaInit);
    AOS_SetTriggerEventSrc(DMA_TX_TRIG_CH, SPI_TX_EVT_SRC);

    /* RX DMA：SPI_DR → 内存 */
    stcDmaInit.u32IntEn       = DMA_INT_ENABLE;
    stcDmaInit.u32SrcAddrInc  = DMA_SRC_ADDR_FIX;
    stcDmaInit.u32DestAddrInc = DMA_DEST_ADDR_INC;
    stcDmaInit.u32SrcAddr     = (uint32_t)(&SPI_UNIT->DR);
    stcDmaInit.u32DestAddr    = (uint32_t)m_u8RxBuf;
    (void)DMA_Init(DMA_UNIT, DMA_RX_CH, &stcDmaInit);
    AOS_SetTriggerEventSrc(DMA_RX_TRIG_CH, SPI_RX_EVT_SRC);

    /* DMA 接收中断注册 */
    stcIrqSignConfig.enIntSrc    = DMA_RX_INT_SRC;
    stcIrqSignConfig.enIRQn      = DMA_RX_IRQ_NUM;
    stcIrqSignConfig.pfnCallback = DMA_TransCompleteCallback;
    (void)INTC_IrqSignIn(&stcIrqSignConfig);
    NVIC_ClearPendingIRQ(stcIrqSignConfig.enIRQn);
    NVIC_SetPriority(stcIrqSignConfig.enIRQn, DDL_IRQ_PRIO_06);
    NVIC_EnableIRQ(stcIrqSignConfig.enIRQn);

    DMA_Cmd(DMA_UNIT, ENABLE);
    DMA_ChCmd(DMA_UNIT, DMA_TX_CH, DISABLE);
    DMA_ChCmd(DMA_UNIT, DMA_RX_CH, DISABLE);

    memset(m_u8TxBuf, 0x00, sizeof(m_u8TxBuf));
}
/**
 * @brief  底层 DMA 全双工传输（内部调用，外部已加互斥锁）
 */
static int32_t SPI_DoDmaTransmit(uint8_t u8SlaveIdx, const uint8_t *pu8TxBuf,
                                 uint8_t *pu8RxBuf, uint32_t u32Len)
{
    uint32_t u32Timeout;

    /* 1. 拉低对应片选，建立时间 ≥1μs */
    switch (u8SlaveIdx)
    {
        case 1U: GPIO_ResetPins(SPI_CS1_PORT, SPI_CS1_PIN); break;
        case 2U: GPIO_ResetPins(SPI_CS2_PORT, SPI_CS2_PIN); break;
        case 3U: GPIO_ResetPins(SPI_CS3_PORT, SPI_CS3_PIN); break;
        case 4U: GPIO_ResetPins(SPI_CS4_PORT, SPI_CS4_PIN); break;
        case 5U: GPIO_ResetPins(SPI_CS5_PORT, SPI_CS5_PIN); break;
        default: return SPI_ERR_PARAM;
    }
		DDL_DelayUS(1);
    /* 2. 重置 DMA，重载地址与长度 */
    DMA_ChCmd(DMA_UNIT, DMA_TX_CH, DISABLE);
    DMA_ChCmd(DMA_UNIT, DMA_RX_CH, DISABLE);
    DMA_ClearTransCompleteStatus(DMA_UNIT, DMA_RX_INT_CH);
    enRxCompleteFlag = RESET;

    DMA_SetSrcAddr(DMA_UNIT, DMA_TX_CH, (uint32_t)pu8TxBuf);
    DMA_SetTransCount(DMA_UNIT, DMA_TX_CH, u32Len);
    DMA_SetDestAddr(DMA_UNIT, DMA_RX_CH, (uint32_t)pu8RxBuf);
    DMA_SetTransCount(DMA_UNIT, DMA_RX_CH, u32Len);

    DMA_ChCmd(DMA_UNIT, DMA_TX_CH, ENABLE);
    DMA_ChCmd(DMA_UNIT, DMA_RX_CH, ENABLE);

    /* 3. 清SPI残留数据，启动传输 */
    if (SET == SPI_GetStatus(SPI_UNIT, SPI_FLAG_RX_BUF_FULL))
    {
        (void)SPI_ReadData(SPI_UNIT);
    }
    SPI_Cmd(SPI_UNIT, ENABLE);

    /* 4. 等待传输完成+超时检测 */
    u32Timeout = SPI_TRANS_TIMEOUT;
    while ((RESET == enRxCompleteFlag) && (u32Timeout-- > 0U))
    {
        if (SET == DMA_GetTransCompleteStatus(DMA_UNIT, DMA_RX_INT_CH)) {
            enRxCompleteFlag = SET;
            break;
        }
    }

    /* 超时异常处理 */
    if (RESET == enRxCompleteFlag)
    {
        SPI_Cmd(SPI_UNIT, DISABLE);
        DMA_ChCmd(DMA_UNIT, DMA_TX_CH, DISABLE);
        DMA_ChCmd(DMA_UNIT, DMA_RX_CH, DISABLE);
        GPIO_SetPins(SPI_CS1_PORT, SPI_CS1_PIN);
        GPIO_SetPins(SPI_CS2_PORT, SPI_CS2_PIN);
        GPIO_SetPins(SPI_CS3_PORT, SPI_CS3_PIN);
        GPIO_SetPins(SPI_CS4_PORT, SPI_CS4_PIN);
        GPIO_SetPins(SPI_CS5_PORT, SPI_CS5_PIN);
        return SPI_ERR_TIMEOUT;
    }

    /* 5. 等待SPI总线完全空闲 */
    while (RESET == SPI_GetStatus(SPI_UNIT, SPI_FLAG_IDLE))
    {
    }

    /* 6. 关闭SPI，释放所有片选 */
    SPI_Cmd(SPI_UNIT, DISABLE);
    DMA_ChCmd(DMA_UNIT, DMA_TX_CH, DISABLE);
    DMA_ChCmd(DMA_UNIT, DMA_RX_CH, DISABLE);

    GPIO_SetPins(SPI_CS1_PORT, SPI_CS1_PIN);
    GPIO_SetPins(SPI_CS2_PORT, SPI_CS2_PIN);
    GPIO_SetPins(SPI_CS3_PORT, SPI_CS3_PIN);
    GPIO_SetPins(SPI_CS4_PORT, SPI_CS4_PIN);
    GPIO_SetPins(SPI_CS5_PORT, SPI_CS5_PIN);
	DDL_DelayUS(1);
    return SPI_OK;
}

/**
 * @brief  SPI标准事务接口（协议层封装）
 */
int32_t Fingers_SPI_Transact(uint8_t u8SlaveIdx, uint8_t u8Cmd, uint16_t u16CmdParam,
                             uint16_t u16RdMaxLen, uint8_t *pu8RespPayload,
                             uint16_t *pu16RespLen, uint8_t *pu8Status)
{
    int32_t s32Ret;
    uint16_t u16HeadCrc;
    uint16_t u16DataLen;
    uint16_t u16RespCrc;

    /* 1. 参数校验 */
    if ((u8SlaveIdx < 1U) || (u8SlaveIdx > 5U)) {
        return SPI_ERR_PARAM;
    }
    if ((pu8RespPayload == NULL) || (pu16RespLen == NULL) || (pu8Status == NULL)) {
        return SPI_ERR_PARAM;
    }
    if (u16RdMaxLen > SPI_MAX_PAYLOAD_LEN) {
        u16RdMaxLen = SPI_MAX_PAYLOAD_LEN;
    }

    /* 2. 组装主机请求帧（10字节，大端序） */
    memset(m_u8TxBuf, 0x00, sizeof(m_u8TxBuf));
    m_u8TxBuf[0] = SPI_REQ_HEADER;
    m_u8TxBuf[1] = u8Cmd;
    m_u8TxBuf[2] = (uint8_t)((u16CmdParam >> 8U) & 0xFFU);
    m_u8TxBuf[3] = (uint8_t)(u16CmdParam & 0xFFU);
    m_u8TxBuf[4] = (uint8_t)((u16RdMaxLen >> 8U) & 0xFFU);
    m_u8TxBuf[5] = (uint8_t)(u16RdMaxLen & 0xFFU);

    u16HeadCrc = CRC16_CCITT(m_u8TxBuf, 6U);
    m_u8TxBuf[6] = (uint8_t)((u16HeadCrc >> 8U) & 0xFFU);
    m_u8TxBuf[7] = (uint8_t)(u16HeadCrc & 0xFFU);
		m_u8TxBuf[8] = (uint8_t)(0X0D & 0xFFU);
		m_u8TxBuf[9] = (uint8_t)(0X0D & 0xFFU);
    /* 3. 总线加锁，执行DMA传输 */
    xSemaphoreTake(g_spi_mutex, portMAX_DELAY);
    s32Ret = SPI_DoDmaTransmit(u8SlaveIdx, m_u8TxBuf, m_u8RxBuf, SPI_MAX_FRAME_LEN);
    xSemaphoreGive(g_spi_mutex);

    if (s32Ret != SPI_OK) {
        return s32Ret;
    }

    /* 4. 解析应答帧，校验合法性 */
    if (m_u8RxBuf[0] != SPI_RESP_HEADER) {
        return SPI_ERR_FRAME;
    }

    u16HeadCrc = CRC16_CCITT(m_u8RxBuf, 6U);
    u16RespCrc = ((uint16_t)m_u8RxBuf[6] << 8U) | (uint16_t)m_u8RxBuf[7];
    if (u16HeadCrc != u16RespCrc) {
        return SPI_ERR_FRAME;
    }

    *pu8Status = m_u8RxBuf[1];
    u16DataLen = ((uint16_t)m_u8RxBuf[4] << 8U) | (uint16_t)m_u8RxBuf[5];

    if (u16DataLen > SPI_MAX_PAYLOAD_LEN) {
        return SPI_ERR_FRAME;
    }

    /* 5. 拷贝载荷数据 */
    if (u16DataLen > 0U) {
        memcpy(pu8RespPayload, &m_u8RxBuf[SPI_RESP_HEAD_LEN], u16DataLen);
    }
    *pu16RespLen = u16DataLen;

    return SPI_OK;
}
/*******************************************************************************
 * 测试接口实现
 ******************************************************************************/


/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
