/**
 *******************************************************************************
 * @file  spi_imu.c
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
#include "spi_imu.h"
#include <math.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
static SemaphoreHandle_t g_spi_mutex = NULL;
/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/*
DMA1 通道	中断源宏 INT_SRC_xxx	中断向量 IRQn
CH0	INT_SRC_DMA1_TC0	INT006_IRQn
CH1	INT_SRC_DMA1_TC1	INT007_IRQn
CH2	INT_SRC_DMA1_TC2	INT008_IRQn
CH3	INT_SRC_DMA1_TC3	INT009_IRQn

DMA2 通道	中断源宏 INT_SRC_xxx	中断向量 IRQn
CH0	INT_SRC_DMA2_TC0	INT013_IRQn
CH1	INT_SRC_DMA2_TC1	INT014_IRQn
CH2	INT_SRC_DMA2_TC2	INT015_IRQn
CH3	INT_SRC_DMA2_TC3	INT016_IRQn
*/
/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* Configuration for Example */
#define EXAMPLE_SPI_MASTER_SLAVE        (SPI_MASTER)													//SPI主机模式
#define EXAMPLE_SPI_BUF_LEN             (128UL)																//SPI的DMA缓存区大小
/* SPI definition */
#define SPI_UNIT                        (CM_SPI2)															//SPI2模#块
#define SPI_CLK                         (FCG1_PERIPH_SPI2)										//SPI时钟
#define SPI_TX_EVT_SRC                  (EVT_SRC_SPI2_SPTI)										//SPI2发送
#define SPI_RX_EVT_SRC                  (EVT_SRC_SPI2_SPRI)										//SPI2接收
/* DMA definition */
#define DMA_UNIT                        (CM_DMA1)															//DMA1模#块
#define DMA_CLK                         (FCG0_PERIPH_DMA1 | FCG0_PERIPH_AOS)	//DMA时钟
#define DMA_TX_CH                       (DMA_CH2)															//发送方通道号
#define DMA_TX_TRIG_CH                  (AOS_DMA1_2)													//发送方DMA1通道3
#define DMA_RX_CH                       (DMA_CH3)															//接收方通道号
#define DMA_RX_TRIG_CH                  (AOS_DMA1_3)													//接收方DMA1通道3

#define DMA_RX_INT_CH                   (DMA_INT_TC_CH3)											//接收方的DMA传输完成中断
#define DMA_RX_INT_SRC                  (INT_SRC_DMA1_TC3)										//接收方的DMA1 通道 3 中断源
#define DMA_RX_IRQ_NUM                  (INT009_IRQn)													//接收方的中断源对应中断函数

/* 5个片选CS引脚定义，全部初始拉高，选中时拉低 */
#define SPI_CS1_PORT                    GPIO_PORT_D
#define SPI_CS1_PIN                     GPIO_PIN_12

#define SPI_CS2_PORT                    GPIO_PORT_E
#define SPI_CS2_PIN                     GPIO_PIN_11

#define SPI_CS3_PORT                    GPIO_PORT_E
#define SPI_CS3_PIN                     GPIO_PIN_13


/* SCK = PA02 */
#define SPI_SCK_PORT                    (GPIO_PORT_A)
#define SPI_SCK_PIN                     (GPIO_PIN_02)
#define SPI_SCK_FUNC                    (GPIO_FUNC_47)
/* MOSI = PA00 */
#define SPI_MOSI_PORT                   (GPIO_PORT_A)
#define SPI_MOSI_PIN                    (GPIO_PIN_00)
#define SPI_MOSI_FUNC                   (GPIO_FUNC_44)
/* MISO = PA01 */
#define SPI_MISO_PORT                   (GPIO_PORT_A)
#define SPI_MISO_PIN                    (GPIO_PIN_01)
#define SPI_MISO_FUNC                   (GPIO_FUNC_45)
/*******************************************************************************
 * static val
 ******************************************************************************/
static char u8TxBuf[EXAMPLE_SPI_BUF_LEN] = "SPI Master/Slave example: Communication between two boards!";
static char u8RxBuf[EXAMPLE_SPI_BUF_LEN];
static __IO en_flag_status_t enRxCompleteFlag = RESET;
/*******************************************************************************
 * 
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
/************************* MPU9250 寄存器定义 *************************/
#define MPU9250_REG_WHO_AM_I      0x75    // 设备ID，MPU9250固定为0x71
#define MPU9250_REG_PWR_MGMT_1    0x6B    // 电源管理1
#define MPU9250_REG_SMPLRT_DIV    0x19    // 采样率分频
#define MPU9250_REG_CONFIG        0x1A    // 低通滤波配置
#define MPU9250_REG_GYRO_CONFIG   0x1B    // 陀螺仪量程配置
#define MPU9250_REG_ACCEL_CONFIG  0x1C    // 加速度计量程配置
#define MPU9250_REG_ACCEL_XOUT_H  0x3B    // 加速度计X轴高字节（连续读起始地址）
/************************* MPU 寄存器（地址十进制转十六进制） *************************/
#define MPU_REG_USER_CTRL       0x6A    // 106号寄存器
#define MPU_REG_INT_PIN_CFG     0x37    // 55号寄存器
#define MPU_REG_I2C_MST_CTRL    0x24    // 36号寄存器
#define MPU_REG_I2C_SLV0_ADDR   0x25    // 37号寄存器
#define MPU_REG_I2C_SLV0_REG    0x26    // 38号寄存器
#define MPU_REG_I2C_SLV0_CTRL   0x27    // 39号寄存器
#define MPU_REG_I2C_SLV0_DO     0x63    // 99号寄存器
#define MPU_REG_I2C_MST_STATUS  0x36    // 54号寄存器
#define MPU_REG_EXT_SENS_DATA_00 0x49   // 73号寄存器
#define MPU_REG_PWR_MGMT_1    	0x6B

#define MPU_REG_I2C_SLV4_ADDR   0x31
#define MPU_REG_I2C_SLV4_REG    0x32
#define MPU_REG_I2C_SLV4_DO     0x33
#define MPU_REG_I2C_SLV4_CTRL   0x34
#define MPU_REG_I2C_SLV4_DI     0x35
/************************* AK8963 磁力计完整寄存器定义 *************************/
#define AK8963_ADDR             0x0C    // 7位I2C设备地址

/* 设备与状态寄存器 */
#define AK8963_WHO_AM_I         0x00    // WIA 设备ID，固定值0x48
#define AK8963_INFO             0x01    // 设备信息
#define AK8963_ST1              0x02    // 状态寄存器1（数据就绪标志）
#define AK8963_ST2              0x09    // 状态寄存器2（溢出/位宽标志）

/* 测量数据寄存器（小端模式，低字节在前） */
#define AK8963_HXL              0x03    // X轴磁力数据低字节
#define AK8963_HXH              0x04    // X轴磁力数据高字节
#define AK8963_HYL              0x05    // Y轴磁力数据低字节
#define AK8963_HYH              0x06    // Y轴磁力数据高字节
#define AK8963_HZL              0x07    // Z轴磁力数据低字节
#define AK8963_HZH              0x08    // Z轴磁力数据高字节

/* 控制寄存器 */
#define AK8963_CNTL1            0x0A    // 控制寄存器1（模式+位宽）
#define AK8963_CNTL2            0x0B    // 控制寄存器2（软复位）
#define AK8963_ASTC             0x0C    // 自测试控制

/* 工厂灵敏度校准寄存器（仅ROM模式可读） */
#define AK8963_ASAX             0x10    // X轴灵敏度校准值
#define AK8963_ASAY             0x11    // Y轴灵敏度校准值
#define AK8963_ASAZ             0x12    // Z轴灵敏度校准值

/* 工作模式定义 */
#define AK8963_MODE_POWERDOWN   0x00    // 掉电模式
#define AK8963_MODE_ROM_ACCESS  0x0F    // Fuse ROM访问模式
#define AK8963_MODE_CONT_100HZ  0x16    // 16位输出 + 100Hz连续测量模式2
/* 磁力计灵敏度：16位模式下 0.15μT/LSB */
#define MAG_SENSITIVITY         0.15f

/* 3个IMU模块对应CS1~CS3 */
mpu9250_data_t imu_data[3];
/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  DMA transmit complete callback.
 * @param  None
 * @retval None
 */
static void DMA_TransCompleteCallback(void)
{
    enRxCompleteFlag = SET;
    DMA_ClearTransCompleteStatus(DMA_UNIT, DMA_RX_INT_CH);
}

void IMU_SPI_Config(void)
{
    stc_spi_init_t stcSpiInit;
    stc_dma_init_t stcDmaInit;
    stc_irq_signin_config_t stcIrqSignConfig;
    stc_gpio_init_t stcGpioInit;

    (void)GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinDrv       = PIN_HIGH_DRV;
    stcGpioInit.u16PinDir       = PIN_DIR_OUT;  // 推挽输出

    /* 1. 初始化5个CS引脚，默认全部拉高（空闲状态） */
    (void)GPIO_Init(SPI_CS1_PORT, SPI_CS1_PIN, &stcGpioInit);
    GPIO_SetPins(SPI_CS1_PORT, SPI_CS1_PIN);
    (void)GPIO_Init(SPI_CS2_PORT, SPI_CS2_PIN, &stcGpioInit);
    GPIO_SetPins(SPI_CS2_PORT, SPI_CS2_PIN);
    (void)GPIO_Init(SPI_CS3_PORT, SPI_CS3_PIN, &stcGpioInit);
    GPIO_SetPins(SPI_CS3_PORT, SPI_CS3_PIN);


    /* 2. SPI总线引脚：SCK/MOSI/MISO 保持SPI复用功能，和原来一致 */
    (void)GPIO_Init(SPI_SCK_PORT,  SPI_SCK_PIN,  &stcGpioInit);
    (void)GPIO_Init(SPI_MOSI_PORT, SPI_MOSI_PIN, &stcGpioInit);
    (void)GPIO_Init(SPI_MISO_PORT, SPI_MISO_PIN, &stcGpioInit);

    GPIO_SetFunc(SPI_SCK_PORT,  SPI_SCK_PIN,  SPI_SCK_FUNC);
    GPIO_SetFunc(SPI_MOSI_PORT, SPI_MOSI_PIN, SPI_MOSI_FUNC);
    GPIO_SetFunc(SPI_MISO_PORT, SPI_MISO_PIN, SPI_MISO_FUNC);
    // 注意：不再配置原来的SPI_SS引脚为SPI功能，改用软件GPIO控制CS

    /* 3. SPI外设配置：保持4线全双工，和原来完全一致 */
    FCG_Fcg1PeriphClockCmd(SPI_CLK, ENABLE);
    SPI_StructInit(&stcSpiInit);
    stcSpiInit.u32WireMode          = SPI_4_WIRE;  // 继续用4线全双工
    stcSpiInit.u32TransMode         = SPI_FULL_DUPLEX;
    stcSpiInit.u32MasterSlave       = EXAMPLE_SPI_MASTER_SLAVE;
    stcSpiInit.u32Parity            = SPI_PARITY_INVD;
    stcSpiInit.u32SpiMode           = SPI_MD_3;
    stcSpiInit.u32BaudRatePrescaler = SPI_BR_CLK_DIV32;
    stcSpiInit.u32DataBits          = SPI_DATA_SIZE_8BIT;
    stcSpiInit.u32FirstBit          = SPI_FIRST_MSB;
    stcSpiInit.u32FrameLevel        = SPI_1_FRAME;
    (void)SPI_Init(SPI_UNIT, &stcSpiInit);

    /* 4. DMA配置：完全不用改，和原来一模一样 */
    // 原DMA初始化代码全部保留
    // AOS触发源、DMA通道、中断配置都不变
    /* DMA configuration */
    FCG_Fcg0PeriphClockCmd(DMA_CLK, ENABLE);
    (void)DMA_StructInit(&stcDmaInit);
    stcDmaInit.u32BlockSize  = 1UL;
    stcDmaInit.u32TransCount = EXAMPLE_SPI_BUF_LEN;
    stcDmaInit.u32DataWidth  = DMA_DATAWIDTH_8BIT;
    /* Configure TX */
    stcDmaInit.u32SrcAddrInc  = DMA_SRC_ADDR_INC;
    stcDmaInit.u32DestAddrInc = DMA_DEST_ADDR_FIX;
    stcDmaInit.u32SrcAddr     = (uint32_t)(&u8TxBuf[0]);
    stcDmaInit.u32DestAddr    = (uint32_t)(&SPI_UNIT->DR);
    if (LL_OK != DMA_Init(DMA_UNIT, DMA_TX_CH, &stcDmaInit)) {
        for (;;) {
        }
    }
    AOS_SetTriggerEventSrc(DMA_TX_TRIG_CH, SPI_TX_EVT_SRC);
    /* Configure RX */
    stcDmaInit.u32IntEn       = DMA_INT_ENABLE;
    stcDmaInit.u32SrcAddrInc  = DMA_SRC_ADDR_FIX;
    stcDmaInit.u32DestAddrInc = DMA_DEST_ADDR_INC;
    stcDmaInit.u32SrcAddr     = (uint32_t)(&SPI_UNIT->DR);
    stcDmaInit.u32DestAddr    = (uint32_t)(&u8RxBuf[0]);
    if (LL_OK != DMA_Init(DMA_UNIT, DMA_RX_CH, &stcDmaInit)) {
        for (;;) {
        }
    }
    AOS_SetTriggerEventSrc(DMA_RX_TRIG_CH, SPI_RX_EVT_SRC);

    /* DMA receive NVIC configure */
    stcIrqSignConfig.enIntSrc    = DMA_RX_INT_SRC;
    stcIrqSignConfig.enIRQn      = DMA_RX_IRQ_NUM;
    stcIrqSignConfig.pfnCallback = &DMA_TransCompleteCallback;
    (void)INTC_IrqSignIn(&stcIrqSignConfig);
    NVIC_ClearPendingIRQ(stcIrqSignConfig.enIRQn);
    NVIC_SetPriority(stcIrqSignConfig.enIRQn, DDL_IRQ_PRIO_06);
    NVIC_EnableIRQ(stcIrqSignConfig.enIRQn);

    /* Enable DMA and channel */
    DMA_Cmd(DMA_UNIT, ENABLE);
    DMA_ChCmd(DMA_UNIT, DMA_TX_CH, ENABLE);
    DMA_ChCmd(DMA_UNIT, DMA_RX_CH, ENABLE);
    /* 初始化SPI总线互斥锁 */
    if (g_spi_mutex == NULL) {
        g_spi_mutex = xSemaphoreCreateMutex();
    }
}
 
/**
 * @}
 */
/**
 * @brief  指定CS的SPI全双工DMA传输
 * @param  u8CsNum 片选编号 1~5
 * @param  pu8TxBuf 发送缓冲区
 * @param  pu8RxBuf 接收缓冲区
 * @param  u32Len 传输长度
 * @retval None
 */
void IMU_SPI_DmaTransmit(uint8_t u8CsNum, const uint8_t *pu8TxBuf, uint8_t *pu8RxBuf, uint32_t u32Len)
{
    /* 总线加锁，防止多任务并发 */
    xSemaphoreTake(g_spi_mutex, portMAX_DELAY);
    // 1. 拉低对应片选
    switch(u8CsNum) {
        case 1: GPIO_ResetPins(SPI_CS1_PORT, SPI_CS1_PIN); break;
        case 2: GPIO_ResetPins(SPI_CS2_PORT, SPI_CS2_PIN); break;
				case 3: GPIO_ResetPins(SPI_CS3_PORT, SPI_CS3_PIN); break;
        default: return;
    }
    // 2. 先关闭 DMA 通道，再修改配置（关键！）
    DMA_ChCmd(DMA_UNIT, DMA_TX_CH, DISABLE);
    DMA_ChCmd(DMA_UNIT, DMA_RX_CH, DISABLE);
    // 3. 清 DMA 传输完成标志，避免上次残留
    DMA_ClearTransCompleteStatus(DMA_UNIT, DMA_RX_INT_CH);
    // 4. 重载地址和长度
    enRxCompleteFlag = RESET;
    DMA_SetSrcAddr(DMA_UNIT, DMA_TX_CH, (uint32_t)pu8TxBuf);
    DMA_SetTransCount(DMA_UNIT, DMA_TX_CH, u32Len);
    DMA_SetDestAddr(DMA_UNIT, DMA_RX_CH, (uint32_t)pu8RxBuf);
    DMA_SetTransCount(DMA_UNIT, DMA_RX_CH, u32Len);
    // 5. 重新使能 DMA 通道
    DMA_ChCmd(DMA_UNIT, DMA_TX_CH, ENABLE);
    DMA_ChCmd(DMA_UNIT, DMA_RX_CH, ENABLE);
    // 6. 清SPI残留接收数据，启动SPI
    if (SET == SPI_GetStatus(SPI_UNIT, SPI_FLAG_RX_BUF_FULL)) {
        (void)SPI_ReadData(SPI_UNIT); // 读一次DR，自动清空RX满标志
    }
    SPI_Cmd(SPI_UNIT, ENABLE);
    // 7. 等待传输完成（双重判断：中断标志 + 硬件计数，兜底）
    uint32_t timeout = 100000;
    while ((RESET == enRxCompleteFlag) && (timeout--))
    {
        // 兜底：直接查 DMA 硬件完成标志
        if (SET == DMA_GetTransCompleteStatus(DMA_UNIT, DMA_RX_INT_CH)) {
            enRxCompleteFlag = SET;
            break;
        }
    }
    // 8. 等待 SPI 总线完全空闲
    while (RESET == SPI_GetStatus(SPI_UNIT, SPI_FLAG_IDLE));
    // 9. 关闭 SPI，拉高所有片选
    SPI_Cmd(SPI_UNIT, DISABLE);
    GPIO_SetPins(SPI_CS1_PORT, SPI_CS1_PIN);
    GPIO_SetPins(SPI_CS2_PORT, SPI_CS2_PIN);
		GPIO_SetPins(SPI_CS3_PORT, SPI_CS3_PIN);
    /* 总线解锁 */
    xSemaphoreGive(g_spi_mutex);
}
/**
 * @}
 */
/**
 * @brief  MPU9250 写单个寄存器
 * @param  cs_num  片选编号 1~3
 * @param  reg     寄存器地址
 * @param  data    待写入数据
 * @retval None
 */
static void mpu9250_write_reg(uint8_t cs_num, uint8_t reg, uint8_t data)
{
    uint8_t tx_buf[2] = {reg & 0x7F, data}; // SPI写：bit7=0
    uint8_t rx_buf[2];
    IMU_SPI_DmaTransmit(cs_num, tx_buf, rx_buf, 2);
}

/**
 * @brief  MPU9250 读单个寄存器
 * @param  cs_num  片选编号 1~3
 * @param  reg     寄存器地址
 * @retval 读取到的寄存器值
 */
static uint8_t mpu9250_read_reg(uint8_t cs_num, uint8_t reg)
{
    uint8_t tx_buf[2] = {reg | 0x80, 0xFF}; // SPI读：bit7=1，第二字节发dummy
    uint8_t rx_buf[2];
    IMU_SPI_DmaTransmit(cs_num, tx_buf, rx_buf, 2);
    return rx_buf[1]; // 第一个字节为无效数据，第二个才是寄存器值
}

/**
 * @brief  MPU9250 连续读多个寄存器
 * @param  cs_num  片选编号 1~3
 * @param  reg     起始寄存器地址
 * @param  buf     接收缓冲区
 * @param  len     读取长度
 * @retval None
 */
static void mpu9250_read_regs(uint8_t cs_num, uint8_t reg, uint8_t *buf, uint8_t len)
{
    uint8_t tx_buf[128];
    uint8_t rx_buf[128];

    tx_buf[0] = reg | 0x80;
    memset(&tx_buf[1], 0xFF, len); // 后续字节全部发dummy

    IMU_SPI_DmaTransmit(cs_num, tx_buf, rx_buf, len + 1);
    memcpy(buf, &rx_buf[1], len); // 跳过第一个无效字节
}
/**
 * @}
 */
/**
 * @brief  指定片选的 MPU9250 初始化
 * @param  cs_num  片选编号 1~3
 * @retval 0:成功  -1:设备未找到
 */
int8_t MPU9250_Init(uint8_t cs_num)
{
    uint8_t dev_id;

    DDL_DelayMS(100);// 等待上电稳定
		mpu9250_write_reg(1, MPU9250_REG_SMPLRT_DIV, 0xAA);
		uint8_t test_val = mpu9250_read_reg(1, MPU9250_REG_SMPLRT_DIV);
		// test_val 必须等于 0xAA，否则SPI本身还有时序问题，先修SPI
    /* 1. 读取设备ID，验证通信 */
    dev_id = mpu9250_read_reg(cs_num, MPU9250_REG_WHO_AM_I);
    if (dev_id != 0x71&&dev_id != 0x70) {
        return -1; // ID不匹配，检查接线/SPI模式/片选
    }

    /* 2. 软件复位 */
    mpu9250_write_reg(cs_num, MPU9250_REG_PWR_MGMT_1, 0x80);
    DDL_DelayMS(100);

    /* 3. 唤醒设备，关闭睡眠模式，使用内部8MHz时钟 */
    mpu9250_write_reg(cs_num, MPU9250_REG_PWR_MGMT_1, 0x00);
    DDL_DelayMS(10);

    /* 4. 采样率配置：1000Hz / (1+7) = 125Hz */
    mpu9250_write_reg(cs_num, MPU9250_REG_SMPLRT_DIV, 0x07);

    /* 5. 数字低通滤波，带宽42Hz */
    mpu9250_write_reg(cs_num, MPU9250_REG_CONFIG, 0x03);

    /* 6. 陀螺仪量程 ±2000°/s */
    mpu9250_write_reg(cs_num, MPU9250_REG_GYRO_CONFIG, 0x18);

    /* 7. 加速度计量程 ±8g */
    mpu9250_write_reg(cs_num, MPU9250_REG_ACCEL_CONFIG, 0x10);

    /* 初始化姿态角 */
    imu_data[cs_num - 1].roll  = 0.0f;
    imu_data[cs_num - 1].pitch = 0.0f;
    imu_data[cs_num - 1].yaw   = 0.0f;
    imu_data[cs_num - 1].q0  	= 1.0f;
    imu_data[cs_num - 1].q1 	= 0.0f;
    imu_data[cs_num - 1].q2   = 0.0f;
		imu_data[cs_num - 1].q3   = 0.0f;

    return 0;
}

#if 0
/**
 * @brief  单次写AK8963寄存器（通过MPU内部I2C主机SLV4通道）
 */
static void ak8963_single_write(uint8_t cs_num, uint8_t reg, uint8_t data)
{
    /* 配置从机地址：写操作，RNW位(bit7)=0 */
    mpu9250_write_reg(cs_num, MPU_REG_I2C_SLV4_ADDR, AK8963_ADDR & 0x7F);
    /* 配置AK8963目标寄存器 */
    mpu9250_write_reg(cs_num, MPU_REG_I2C_SLV4_REG, reg);
    /* 配置要写入的数据 */
    mpu9250_write_reg(cs_num, MPU_REG_I2C_SLV4_DO, data);
    /* 置位SLV4_EN，触发一次单次写传输 */
    mpu9250_write_reg(cs_num, MPU_REG_I2C_SLV4_CTRL, 0x80);

    /* 等待传输完成：bit6 = I2C_SLV4_DONE */
    uint32_t timeout = 20000;
    while (timeout--) {
        uint8_t sta = mpu9250_read_reg(cs_num, MPU_REG_I2C_MST_STATUS);
        if (sta & 0x40) {
            break;
        }
    }
    /* 读一次状态寄存器，硬件自动清除DONE标志 */
    mpu9250_read_reg(cs_num, MPU_REG_I2C_MST_STATUS);
}

/**
 * @brief  单次读AK8963寄存器（通过MPU内部I2C主机SLV4通道）
 */
static uint8_t ak8963_single_read(uint8_t cs_num, uint8_t reg)
{
    /* 配置从机地址：读操作，RNW位(bit7)=1 */
    mpu9250_write_reg(cs_num, MPU_REG_I2C_SLV4_ADDR, AK8963_ADDR | 0x80);
    /* 配置AK8963目标寄存器 */
    mpu9250_write_reg(cs_num, MPU_REG_I2C_SLV4_REG, reg);
    /* 置位SLV4_EN，触发一次单次读传输 */
    mpu9250_write_reg(cs_num, MPU_REG_I2C_SLV4_CTRL, 0x80);

    /* 等待传输完成：bit6 = I2C_SLV4_DONE */
    uint32_t timeout = 20000;
    while (timeout--) {
        uint8_t sta = mpu9250_read_reg(cs_num, MPU_REG_I2C_MST_STATUS);
        if (sta & 0x40) {
            break;
        }
    }

    /* 读取接收到的数据 */
    uint8_t ret = mpu9250_read_reg(cs_num, MPU_REG_I2C_SLV4_DI);
    /* 读一次状态寄存器清标志 */
    mpu9250_read_reg(cs_num, MPU_REG_I2C_MST_STATUS);
    return ret;
}
/**
 * @brief  指定片选的 AK8963 磁力计初始化
 * @param  cs_num  片选编号1~3
 * @retval 0:成功  -1:设备未找到
 */
int8_t AK8963_Init(uint8_t cs_num)
{
    uint8_t dev_id;
    uint8_t asa[3];
    mpu9250_data_t *p_data = &imu_data[cs_num - 1];

    /******************** 前置关键配置 ********************/
    /* 1. SPI模式下禁用MPU的I2C从机，避免内部总线冲突 */
    mpu9250_write_reg(cs_num, MPU_REG_USER_CTRL, 0x10);  // I2C_IF_DIS = 1
    DDL_DelayMS(2);

    /* 2. 关闭I2C旁路模式，内部I2C主机才能访问AK8963 */
    mpu9250_write_reg(cs_num, MPU_REG_INT_PIN_CFG, 0x00); // BYPASS_EN = 0
    DDL_DelayMS(2);

    /* 3. 复位I2C主机控制器 */
    mpu9250_write_reg(cs_num, MPU_REG_USER_CTRL, 0x12);  // I2C_IF_DIS + I2C_MST_RST
    DDL_DelayMS(10);

    /* 4. 使能I2C主机 + 保持I2C从机禁用 */
    mpu9250_write_reg(cs_num, MPU_REG_USER_CTRL, 0x30);  // I2C_MST_EN + I2C_IF_DIS
    DDL_DelayMS(2);

    /* 5. 设置I2C总线时钟为400kHz */
    mpu9250_write_reg(cs_num, MPU_REG_I2C_MST_CTRL, 0x00);
    DDL_DelayMS(10);

    /******************** 第一步：验证通信 ********************/
    dev_id = ak8963_single_read(cs_num, AK8963_WHO_AM_I);
		uint8_t i2c_sta = mpu9250_read_reg(cs_num, MPU_REG_I2C_MST_STATUS);
    if (dev_id != 0x48) {
        return -1; // 此处打断点，正常应读到 0x48
    }

    /******************** 第二步：软复位 + 读校准值 ********************/
    /* 软复位AK8963 */
    ak8963_single_write(cs_num, 0x0B, 0x01); // CNTL2 寄存器 SRST 位
    DDL_DelayMS(50);

    /* 进入ROM访问模式，读取工厂灵敏度校准值 */
    ak8963_single_write(cs_num, AK8963_CNTL1, AK8963_MODE_ROM_ACCESS);
    DDL_DelayMS(10);
    asa[0] = ak8963_single_read(cs_num, AK8963_ASAX);
    asa[1] = ak8963_single_read(cs_num, AK8963_ASAY);
    asa[2] = ak8963_single_read(cs_num, AK8963_ASAZ);

    /* 按手册公式计算校准系数 */
    for (uint8_t i = 0; i < 3; i++) {
        p_data->mag_asa[i] = ((float)(asa[i] - 128) * 0.5f / 128.0f) + 1.0f;
    }

    /******************** 第三步：设置工作模式 ********************/
    /* 16位输出 + 100Hz连续测量模式2 */
    ak8963_single_write(cs_num, AK8963_CNTL1, AK8963_MODE_CONT_100HZ);
    DDL_DelayMS(10);

    /******************** 第四步：配置SLV0自动周期读取 ********************/
    /* 后续每个采样周期自动读取7字节磁力计数据，存入EXT_SENS_DATA_00起始区域 */
    mpu9250_write_reg(cs_num, MPU_REG_I2C_SLV0_ADDR, AK8963_ADDR | 0x80);
    mpu9250_write_reg(cs_num, MPU_REG_I2C_SLV0_REG, 0x03);   // 起始地址 HXL
    mpu9250_write_reg(cs_num, MPU_REG_I2C_SLV0_CTRL, 0x80 | 0x07); // 使能，读7字节

    return 0;
}

/**
 * @brief  更新原有 MPU9250_ReadData 函数，追加磁力计数据读取与校准转换
 * @param  cs_num  片选编号1~3
 * @retval
 */
void MPU9250_ReadData(uint8_t cs_num)
{
    uint8_t buf[14];
    uint8_t mag_buf[7];
    mpu9250_data_t *p_data = &imu_data[cs_num - 1];

    /* 原有加速度+陀螺仪+温度读取代码保持不变 */
    mpu9250_read_regs(cs_num, MPU9250_REG_ACCEL_XOUT_H, buf, 14);
    p_data->acc_x_raw  = (int16_t)((buf[0]  << 8) | buf[1]);
    p_data->acc_y_raw  = (int16_t)((buf[2]  << 8) | buf[3]);
    p_data->acc_z_raw  = (int16_t)((buf[4]  << 8) | buf[5]);
    p_data->temp_raw   = (int16_t)((buf[6]  << 8) | buf[7]);
    p_data->gyro_x_raw = (int16_t)((buf[8]  << 8) | buf[9]);
    p_data->gyro_y_raw = (int16_t)((buf[10] << 8) | buf[11]);
    p_data->gyro_z_raw = (int16_t)((buf[12] << 8) | buf[13]);

    p_data->ax = p_data->acc_x_raw / 4096.0f;
    p_data->ay = p_data->acc_y_raw / 4096.0f;
    p_data->az = p_data->acc_z_raw / 4096.0f;
    p_data->gx = p_data->gyro_x_raw / 16.4f;
    p_data->gy = p_data->gyro_y_raw / 16.4f;
    p_data->gz = p_data->gyro_z_raw / 16.4f;
    p_data->temp = (p_data->temp_raw / 333.87f) + 21.0f;

    /********** 追加：磁力计数据读取 **********/
    /* 从MPU扩展寄存器读取7字节磁力计数据（已由I2C主机自动更新） */
    mpu9250_read_regs(cs_num, MPU_REG_EXT_SENS_DATA_00, mag_buf, 7);

    /* AK8963为小端模式，低字节在前 */
    p_data->mag_x_raw = (int16_t)((mag_buf[1] << 8) | mag_buf[0]);
    p_data->mag_y_raw = (int16_t)((mag_buf[3] << 8) | mag_buf[2]);
    p_data->mag_z_raw = (int16_t)((mag_buf[5] << 8) | mag_buf[4]);

    /* 应用工厂灵敏度校准 + 单位转换为μT */
    p_data->mx = p_data->mag_x_raw * MAG_SENSITIVITY * p_data->mag_asa[0];
    p_data->my = p_data->mag_y_raw * MAG_SENSITIVITY * p_data->mag_asa[1];
    p_data->mz = p_data->mag_z_raw * MAG_SENSITIVITY * p_data->mag_asa[2];
}
/**
 * @brief  带磁力计修正的姿态解算
 * @param  cs_num  片选编号1~3
 * @retval
 */
void MPU9250_AttitudeCalc(uint8_t cs_num, float dt)
{
    float roll_acc, pitch_acc;
    float mag_x_rot, mag_y_rot;
    float yaw_mag;
    mpu9250_data_t *p_data = &imu_data[cs_num - 1];

    /* 加速度计计算静态姿态角 */
    roll_acc  = atan2f(p_data->ay, p_data->az) * 57.2957795f;
    pitch_acc = atan2f(-p_data->ax, sqrtf(p_data->ay*p_data->ay + p_data->az*p_data->az)) * 57.2957795f;

    /* 互补滤波：横滚、俯仰 */
    p_data->roll  = 0.98f * (p_data->roll  + p_data->gx * dt) + 0.02f * roll_acc;
    p_data->pitch = 0.98f * (p_data->pitch + p_data->gy * dt) + 0.02f * pitch_acc;

    /* 磁力计倾斜补偿，计算地理坐标系下的航向角 */
    float sin_roll = sinf(p_data->roll * 0.0174533f);
    float cos_roll = cosf(p_data->roll * 0.0174533f);
    float sin_pitch = sinf(p_data->pitch * 0.0174533f);
    float cos_pitch = cosf(p_data->pitch * 0.0174533f);

    /* 将磁力计数据从机体坐标系转到水平坐标系 */
    mag_x_rot = p_data->mx * cos_pitch + p_data->my * sin_roll * sin_pitch + p_data->mz * cos_roll * sin_pitch;
    mag_y_rot = p_data->my * cos_roll - p_data->mz * sin_roll;

    /* 计算地磁航向角 */
    yaw_mag = atan2f(-mag_y_rot, mag_x_rot) * 57.2957795f;

    /* 互补滤波：航向角（陀螺积分为主，磁力计修正漂移） */
    p_data->yaw = 0.98f * (p_data->yaw + p_data->gz * dt) + 0.02f * yaw_mag;

    /* 航向角归一化到 0~360° */
    if (p_data->yaw < 0) p_data->yaw += 360.0f;
    if (p_data->yaw >= 360.0f) p_data->yaw -= 360.0f;
}

/**
 * @brief  最简调试版：用SLV4单次读取AK8963的ID
 * @retval 读到的设备ID，正常应为0x48
 */
uint8_t ak8963_debug_read_id(uint8_t cs_num)
{
    uint8_t sta;
    uint8_t dev_id;

    // 1. MPU全芯片软复位
    mpu9250_write_reg(cs_num, 0x6B, 0x80);
    DDL_DelayMS(100);

    // 2. 唤醒并切换到PLL时钟源（时序更精准）
    mpu9250_write_reg(cs_num, 0x6B, 0x01);
    DDL_DelayMS(20);

    // 3. 双重关闭旁路模式
    mpu9250_write_reg(cs_num, 0x37, 0x00);
    DDL_DelayMS(2);
    mpu9250_write_reg(cs_num, 0x37, 0x00);
    DDL_DelayMS(5);

    // 4. 复位I2C主机控制器
    mpu9250_write_reg(cs_num, 0x6A, 0x02);
    DDL_DelayMS(20);

    // 5. 仅使能I2C主机，不开启I2C_IF_DIS（关键修改）
    mpu9250_write_reg(cs_num, 0x6A, 0x20);
    DDL_DelayMS(10);

    // 6. I2C时钟设为348kHz
    mpu9250_write_reg(cs_num, 0x24, 0x0F);
    DDL_DelayMS(5);

    // 7. 先软复位AK8963，清除异常状态
    mpu9250_write_reg(cs_num, 0x31, 0x0C & 0x7F); // 写地址
    mpu9250_write_reg(cs_num, 0x32, 0x0B);        // CNTL2寄存器
    mpu9250_write_reg(cs_num, 0x33, 0x01);        // 软复位命令
    mpu9250_write_reg(cs_num, 0x34, 0x80);        // 启动传输
    DDL_DelayMS(50);

    // 8. 读取WHO_AM_I寄存器
    mpu9250_write_reg(cs_num, 0x31, 0x0C | 0x80); // 读地址
    mpu9250_write_reg(cs_num, 0x32, 0x00);        // WHO_AM_I地址
    mpu9250_write_reg(cs_num, 0x34, 0x80);        // 启动传输

    DDL_DelayMS(5);
    sta = mpu9250_read_reg(cs_num, 0x36);
    dev_id = mpu9250_read_reg(cs_num, 0x35);

    printf("sta=0x%02X  dev_id=0x%02X\r\n", sta, dev_id);
    return dev_id;
}
#else 
/**
 * @brief  读取加速度、陀螺仪、温度原始数据并转换为物理单位（不含磁力计）
 * @param  cs_num  片选编号1~3
 * @retval None
 */
void MPU9250_ReadData(uint8_t cs_num)
{
    uint8_t buf[14];
    mpu9250_data_t *p_data = &imu_data[cs_num - 1];

    /* 连续读取14字节：加速度(6)+温度(2)+陀螺仪(6) */
    mpu9250_read_regs(cs_num, MPU9250_REG_ACCEL_XOUT_H, buf, 14);

    /* 拼接原始数据（MPU9250为大端模式，高字节在前） */
    p_data->acc_x_raw  = (int16_t)((buf[0]  << 8) | buf[1]);
    p_data->acc_y_raw  = (int16_t)((buf[2]  << 8) | buf[3]);
    p_data->acc_z_raw  = (int16_t)((buf[4]  << 8) | buf[5]);
    p_data->temp_raw   = (int16_t)((buf[6]  << 8) | buf[7]);
    p_data->gyro_x_raw = (int16_t)((buf[8]  << 8) | buf[9]);
    p_data->gyro_y_raw = (int16_t)((buf[10] << 8) | buf[11]);
    p_data->gyro_z_raw = (int16_t)((buf[12] << 8) | buf[13]);

    /* 单位转换 */
    // ±8g 量程：灵敏度 4096 LSB/g
    p_data->ax = p_data->acc_x_raw / 4096.0f;
    p_data->ay = p_data->acc_y_raw / 4096.0f;
    p_data->az = p_data->acc_z_raw / 4096.0f;

    // ±2000°/s 量程：灵敏度 16.4 LSB/(°/s)
    p_data->gx = p_data->gyro_x_raw / 16.4f;
    p_data->gy = p_data->gyro_y_raw / 16.4f;
    p_data->gz = p_data->gyro_z_raw / 16.4f;

    // 温度转换公式
    p_data->temp = (p_data->temp_raw / 333.87f) + 21.0f;
}
/**
 * @brief  一阶互补滤波姿态解算（仅加速度+陀螺仪，无磁力计）
 * @param  cs_num  片选编号1~3
 * @param  dt      采样周期，单位秒
 * @retval None
 */
void MPU9250_AttitudeCalc(uint8_t cs_num, float dt)
{
    float roll_acc, pitch_acc;
    float alpha;
    mpu9250_data_t *p_data = &imu_data[cs_num - 1];

    /* dt 异常限幅：最大不超过50ms，防止卡死重启后角度跳变 */
    if (dt > 0.05f) {
        dt = 0.05f;
    }
    if (dt < 0.001f) {
        dt = 0.001f;
    }

    /* 动态计算互补滤波系数，适配不同dt */
    #define IMU_FILTER_TAU  0.5f    // 滤波时间常数，越大越信任陀螺仪
    alpha = IMU_FILTER_TAU / (IMU_FILTER_TAU + dt);

    /* 加速度计计算静态姿态角 */
    roll_acc  = atan2f(p_data->ay, p_data->az) * 57.2957795f;
    pitch_acc = atan2f(-p_data->ax, sqrtf(p_data->ay*p_data->ay + p_data->az*p_data->az)) * 57.2957795f;

    /* 互补滤波：动态权重，适配任意采样周期 */
    p_data->roll  = alpha * (p_data->roll  + p_data->gx * dt) + (1.0f - alpha) * roll_acc;
    p_data->pitch = alpha * (p_data->pitch + p_data->gy * dt) + (1.0f - alpha) * pitch_acc;

    /* 航向角纯积分 + 慢漂移限制 */
    p_data->yaw += p_data->gz * dt;

    /* 归一化到 -180 ~ 180，避免数值累积过大 */
    if (p_data->yaw > 180.0f)  p_data->yaw -= 360.0f;
    if (p_data->yaw < -180.0f) p_data->yaw += 360.0f;
}
/**
 * @brief  6轴Mahony互补滤波（加速度+陀螺仪，四元数解算）
 * @param  cs_num 片选编号
 * @param  dt     采样周期，单位秒
 */
void MPU9250_AttitudeCalc_Quaternion(uint8_t cs_num, float dt)
{
    float ax, ay, az;
    float gx, gy, gz;
    float norm;
    float vx, vy, vz;
    float ex, ey, ez;
    float ki = 0.005f;   // 积分项系数
    float kp = 2.0f;     // 比例项系数
    mpu9250_data_t *p_data = &imu_data[cs_num - 1];

    ax = p_data->ax;
    ay = p_data->ay;
    az = p_data->az;
    // 陀螺仪单位转成 rad/s
    gx = p_data->gx * 0.0174533f;
    gy = p_data->gy * 0.0174533f;
    gz = p_data->gz * 0.0174533f;

    // 加速度计归一化
    norm = sqrtf(ax*ax + ay*ay + az*az);
    if (norm > 0.001f) {
        ax /= norm;
        ay /= norm;
        az /= norm;

        // 估算重力方向在机体坐标系的投影
        vx = 2*(p_data->q1*p_data->q3 - p_data->q0*p_data->q2);
        vy = 2*(p_data->q0*p_data->q1 + p_data->q2*p_data->q3);
        vz = p_data->q0*p_data->q0 - p_data->q1*p_data->q1 - p_data->q2*p_data->q2 + p_data->q3*p_data->q3;

        // 计算误差（叉积）
        ex = ay*vz - az*vy;
        ey = az*vx - ax*vz;
        ez = ax*vy - ay*vx;

        // PI 修正积分
        p_data->ex_int += ex * ki * dt;
        p_data->ey_int += ey * ki * dt;
        p_data->ez_int += ez * ki * dt;

        // 修正陀螺仪角速度
        gx += kp * ex + p_data->ex_int;
        gy += kp * ey + p_data->ey_int;
        gz += kp * ez + p_data->ez_int;
    }

    // 四元数微分方程更新（一阶龙格库塔）
    p_data->q0 += (-p_data->q1*gx - p_data->q2*gy - p_data->q3*gz) * 0.5f * dt;
    p_data->q1 += ( p_data->q0*gx + p_data->q2*gz - p_data->q3*gy) * 0.5f * dt;
    p_data->q2 += ( p_data->q0*gy - p_data->q1*gz + p_data->q3*gx) * 0.5f * dt;
    p_data->q3 += ( p_data->q0*gz + p_data->q1*gy - p_data->q2*gx) * 0.5f * dt;

    // 四元数归一化
    norm = sqrtf(p_data->q0*p_data->q0 + p_data->q1*p_data->q1 + p_data->q2*p_data->q2 + p_data->q3*p_data->q3);
    p_data->q0 /= norm;
    p_data->q1 /= norm;
    p_data->q2 /= norm;
    p_data->q3 /= norm;

    // 四元数转欧拉角（roll/pitch/yaw，单位°）
    p_data->roll  = atan2f(2*(p_data->q0*p_data->q1 + p_data->q2*p_data->q3), 1 - 2*(p_data->q1*p_data->q1 + p_data->q2*p_data->q2)) * 57.2957795f;
    p_data->pitch = asinf(2*(p_data->q0*p_data->q2 - p_data->q1*p_data->q3)) * 57.2957795f;
    p_data->yaw   = atan2f(2*(p_data->q0*p_data->q3 + p_data->q1*p_data->q2), 1 - 2*(p_data->q2*p_data->q2 + p_data->q3*p_data->q3)) * 57.2957795f;

    // 航向角归一化到 0~360°
    if (p_data->yaw < 0) p_data->yaw += 360.0f;
}
#endif 

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
