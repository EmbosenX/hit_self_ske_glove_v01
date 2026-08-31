/**
 ******************************************************************************
 * @file    iic_imu.c
 * @brief   I2C接口IMU九轴传感器驱动，实现MPU9250等姿态传感器数据读取
 ******************************************************************************
 */

#include "iic_imu.h"
#include <math.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"



static SemaphoreHandle_t g_i2c_mutex = NULL;
/************************* 全局变量 *************************/
mpu9250_i2c_data_t g_mpu_i2c_data;

// 量程灵敏度系数（运行时根据配置更新）
static float s_accel_lsb = 16384.0f;  // ±2g 默认
static float s_gyro_lsb  = 131.0f;    // ±250°/s 默认
/************************* 寄存器地址（与厂家例程完全对齐） *************************/
#define REG_SMPLRT_DIV      0x19
#define REG_CONFIG          0x1A
#define REG_GYRO_CONFIG     0x1B
#define REG_ACCEL_CONFIG    0x1C
#define REG_ACCEL_XOUT_H    0x3B
#define REG_PWR_MGMT_1      0x6B
#define REG_WHO_AM_I        0x75
#define REG_USER_CTRL       0x6A    // 内部I2C主机控制
#define REG_INT_PIN_CFG     0x37    // 旁路模式控制

#define AK8963_WHO_AM_I     0x00
#define AK8963_CNTL1        0x0A
#define AK8963_CNTL2        0x0B
#define AK8963_HXL          0x03
#define AK8963_ASAX         0x10
/************************* I2C 引脚操作宏 *************************/
#define SCL_H()     GPIO_SetPins(MPU_I2C_SCL_PORT, MPU_I2C_SCL_PIN)
#define SCL_L()     GPIO_ResetPins(MPU_I2C_SCL_PORT, MPU_I2C_SCL_PIN)
#define SDA_H()     GPIO_SetPins(MPU_I2C_SDA_PORT, MPU_I2C_SDA_PIN)
#define SDA_L()     GPIO_ResetPins(MPU_I2C_SDA_PORT, MPU_I2C_SDA_PIN)
#define SDA_READ()  (GPIO_ReadInputPins(MPU_I2C_SDA_PORT, MPU_I2C_SDA_PIN) != 0)

/************************* 寄存器地址定义 *************************/
#define REG_SMPLRT_DIV      0x19
#define REG_CONFIG          0x1A
#define REG_GYRO_CONFIG     0x1B
#define REG_ACCEL_CONFIG    0x1C
#define REG_ACCEL_XOUT_H    0x3B
#define REG_PWR_MGMT_1      0x6B
#define REG_WHO_AM_I        0x75
#define REG_INT_PIN_CFG     0x37    // 旁路模式控制

#define AK8963_WHO_AM_I     0x00
#define AK8963_CNTL1        0x0A
#define AK8963_CNTL2        0x0B
#define AK8963_HXL          0x03
#define AK8963_ASAX         0x10

/************************* 软件延时 *************************/
static void i2c_delay(void)
{
    uint32_t i = 30;
    while(i--);
}

/************************* I2C 底层时序 *************************/
static void i2c_start(void)
{
    SDA_H();
    SCL_H();
    i2c_delay();
    SDA_L();
    i2c_delay();
    SCL_L();
    i2c_delay();
}

static void i2c_stop(void)
{
    SDA_L();
    i2c_delay();
    SCL_H();
    i2c_delay();
    SDA_H();
    i2c_delay();
}

static uint8_t i2c_wait_ack(void)
{
    uint8_t ack;
    SDA_H();
    i2c_delay();
    SCL_H();
    i2c_delay();
    ack = SDA_READ() ? 0 : 1;
    SCL_L();
    i2c_delay();
    return ack;
}

static void i2c_send_ack(void)
{
    SDA_L();
    i2c_delay();
    SCL_H();
    i2c_delay();
    SCL_L();
    i2c_delay();
    SDA_H();
}

static void i2c_send_nack(void)
{
    SDA_H();
    i2c_delay();
    SCL_H();
    i2c_delay();
    SCL_L();
    i2c_delay();
}

static void i2c_send_byte(uint8_t data)
{
    uint8_t i;
    for(i = 0; i < 8; i++)
    {
        if(data & 0x80) SDA_H();
        else SDA_L();
        data <<= 1;
        i2c_delay();
        SCL_H();
        i2c_delay();
        SCL_L();
        i2c_delay();
    }
}

static uint8_t i2c_read_byte(void)
{
    uint8_t i, data = 0;
    SDA_H();
    for(i = 0; i < 8; i++)
    {
        data <<= 1;
        SCL_H();
        i2c_delay();
        if(SDA_READ()) data++;
        SCL_L();
        i2c_delay();
    }
    return data;
}

/************************* 寄存器读写接口 *************************/
// 写单个寄存器
static void mpu_write_reg(uint8_t dev_addr, uint8_t reg, uint8_t data)
{
    // 1. 多任务总线互斥
    xSemaphoreTake(g_i2c_mutex, portMAX_DELAY);
    // 2. 挂起任务调度，保证时序不被任务打断
    vTaskSuspendAll();
	
    i2c_start();
    i2c_send_byte(dev_addr << 1);
    i2c_wait_ack();
    i2c_send_byte(reg);
    i2c_wait_ack();
    i2c_send_byte(data);
    i2c_wait_ack();
    i2c_stop();
	
    // 3. 恢复任务调度
    xTaskResumeAll();
    // 4. 释放总线锁
    xSemaphoreGive(g_i2c_mutex);
}

// 读单个寄存器
static uint8_t mpu_read_reg(uint8_t dev_addr, uint8_t reg)
{
    uint8_t data;
		
    xSemaphoreTake(g_i2c_mutex, portMAX_DELAY);
    vTaskSuspendAll();
	
    i2c_start();
    i2c_send_byte(dev_addr << 1);
    i2c_wait_ack();
    i2c_send_byte(reg);
    i2c_wait_ack();
    i2c_start();
    i2c_send_byte((dev_addr << 1) | 0x01);
    i2c_wait_ack();
    data = i2c_read_byte();
    i2c_send_nack();
    i2c_stop();
	
    xTaskResumeAll();
    xSemaphoreGive(g_i2c_mutex);
    return data;
}

// 连续读多个寄存器
static void mpu_read_regs(uint8_t dev_addr, uint8_t reg, uint8_t *buf, uint8_t len)
{
    uint8_t i;
	
    xSemaphoreTake(g_i2c_mutex, portMAX_DELAY);
    vTaskSuspendAll();
	
    i2c_start();
    i2c_send_byte(dev_addr << 1);
    i2c_wait_ack();
    i2c_send_byte(reg);
    i2c_wait_ack();
    i2c_start();
    i2c_send_byte((dev_addr << 1) | 0x01);
    i2c_wait_ack();
    for(i = 0; i < len; i++)
    {
        buf[i] = i2c_read_byte();
        if(i == len - 1) i2c_send_nack();
        else i2c_send_ack();
    }
    i2c_stop();
	
    xTaskResumeAll();
    xSemaphoreGive(g_i2c_mutex);
}

/************************* GPIO 初始化 *************************/
void MPU9250_I2C_InitGPIO(void)
{
    stc_gpio_init_t stcGpioInit;
    GPIO_StructInit(&stcGpioInit);

    stcGpioInit.u16PinDir = PIN_DIR_OUT;
    stcGpioInit.u16PinDrv = PIN_HIGH_DRV;
    stcGpioInit.u16PinOutputType = PIN_OUT_TYPE_NMOS;  // 开漏输出，I2C必须

    GPIO_Init(MPU_I2C_SCL_PORT, MPU_I2C_SCL_PIN, &stcGpioInit);
    GPIO_Init(MPU_I2C_SDA_PORT, MPU_I2C_SDA_PIN, &stcGpioInit);

    SCL_H();
    SDA_H();
    // 创建I2C总线互斥锁
    if (g_i2c_mutex == NULL) {
        g_i2c_mutex = xSemaphoreCreateMutex();
    }
}

/************************* MPU9250 初始化 *************************/
int8_t MPU9250_I2C_Init(void)
{
    uint8_t dev_id;

    MPU9250_I2C_InitGPIO();
    DDL_DelayMS(100);

    // 1. 读取设备ID验证
    dev_id = mpu_read_reg(MPU9250_ADDR, REG_WHO_AM_I);
    if(dev_id != 0x71 && dev_id != 0x70) return -1;

    // 2. 软件复位
    mpu_write_reg(MPU9250_ADDR, REG_PWR_MGMT_1, 0x80);
    DDL_DelayMS(100);

    // 3. 解除休眠，唤醒设备（与例程完全一致）
    mpu_write_reg(MPU9250_ADDR, REG_PWR_MGMT_1, 0x00);
    DDL_DelayMS(10);

    // 4. 基础配置（与例程参数对齐）
    mpu_write_reg(MPU9250_ADDR, REG_SMPLRT_DIV, 0x07);   // 采样率125Hz
    mpu_write_reg(MPU9250_ADDR, REG_CONFIG, 0x06);       // 低通滤波5Hz
    mpu_write_reg(MPU9250_ADDR, REG_GYRO_CONFIG, 0x18);  // 陀螺仪±2000°/s
    s_gyro_lsb = 16.4f;
    mpu_write_reg(MPU9250_ADDR, REG_ACCEL_CONFIG, 0x00); // 加速度±2g（与例程一致）
    s_accel_lsb = 16384.0f;

    // 【关键】关闭内部I2C主机（对应例程注释的 close Master Mode）
    mpu_write_reg(MPU9250_ADDR, REG_USER_CTRL, 0x00);
    DDL_DelayMS(2);

    // 初始化四元数
    g_mpu_i2c_data.q0 = 1.0f;
    g_mpu_i2c_data.q1 = g_mpu_i2c_data.q2 = g_mpu_i2c_data.q3 = 0.0f;
    g_mpu_i2c_data.roll = g_mpu_i2c_data.pitch = g_mpu_i2c_data.yaw = 0.0f;

    return 0;
}

/************************* 读取加速度+陀螺仪+温度 *************************/
void MPU9250_I2C_ReadAccelGyroTemp(void)
{
    uint8_t buf[14];
    mpu_read_regs(MPU9250_ADDR, REG_ACCEL_XOUT_H, buf, 14);

    g_mpu_i2c_data.acc_x_raw  = (int16_t)((buf[0] << 8) | buf[1]);
    g_mpu_i2c_data.acc_y_raw  = (int16_t)((buf[2] << 8) | buf[3]);
    g_mpu_i2c_data.acc_z_raw  = (int16_t)((buf[4] << 8) | buf[5]);
    g_mpu_i2c_data.temp_raw   = (int16_t)((buf[6] << 8) | buf[7]);
    g_mpu_i2c_data.gyro_x_raw = (int16_t)((buf[8] << 8) | buf[9]);
    g_mpu_i2c_data.gyro_y_raw = (int16_t)((buf[10] << 8) | buf[11]);
    g_mpu_i2c_data.gyro_z_raw = (int16_t)((buf[12] << 8) | buf[13]);

    g_mpu_i2c_data.ax = g_mpu_i2c_data.acc_x_raw / s_accel_lsb;
    g_mpu_i2c_data.ay = g_mpu_i2c_data.acc_y_raw / s_accel_lsb;
    g_mpu_i2c_data.az = g_mpu_i2c_data.acc_z_raw / s_accel_lsb;

    // 扣除陀螺仪零偏后转换为物理单位
    g_mpu_i2c_data.gx = (g_mpu_i2c_data.gyro_x_raw - g_mpu_i2c_data.gyro_bias_x) / s_gyro_lsb;
    g_mpu_i2c_data.gy = (g_mpu_i2c_data.gyro_y_raw - g_mpu_i2c_data.gyro_bias_y) / s_gyro_lsb;
    g_mpu_i2c_data.gz = (g_mpu_i2c_data.gyro_z_raw - g_mpu_i2c_data.gyro_bias_z) / s_gyro_lsb;

    g_mpu_i2c_data.temp = (g_mpu_i2c_data.temp_raw / 333.87f) + 21.0f;
}

/************************* 读取磁力计 *************************/
void MPU9250_I2C_ReadMag(void)
{
    uint8_t buf_l, buf_h;

    // 1. 开启I2C旁路模式（与例程完全一致）
    mpu_write_reg(MPU9250_ADDR, REG_INT_PIN_CFG, 0x02);
    vTaskDelay(10);

    // 2. 触发单次测量模式（对应例程 Single_Write(MAG_ADDRESS,0x0A,0x01)）
    mpu_write_reg(AK8963_ADDR, AK8963_CNTL1, 0x01);
    vTaskDelay(10);

    // 3. 读取X轴数据（低字节在前，小端模式，与例程一致）
    buf_l = mpu_read_reg(AK8963_ADDR, AK8963_HXL);
    buf_h = mpu_read_reg(AK8963_ADDR, AK8963_HXL + 1);
    g_mpu_i2c_data.mag_x_raw = (int16_t)((buf_h << 8) | buf_l);

    // 4. 读取Y轴数据
    buf_l = mpu_read_reg(AK8963_ADDR, AK8963_HXL + 2);
    buf_h = mpu_read_reg(AK8963_ADDR, AK8963_HXL + 3);
    g_mpu_i2c_data.mag_y_raw = (int16_t)((buf_h << 8) | buf_l);

    // 5. 读取Z轴数据
    buf_l = mpu_read_reg(AK8963_ADDR, AK8963_HXL + 4);
    buf_h = mpu_read_reg(AK8963_ADDR, AK8963_HXL + 5);
    g_mpu_i2c_data.mag_z_raw = (int16_t)((buf_h << 8) | buf_l);

    // 6. 转换为物理单位（14位单次模式，灵敏度0.6μT/LSB）
    g_mpu_i2c_data.mx = g_mpu_i2c_data.mag_x_raw * 0.6f;
    g_mpu_i2c_data.my = g_mpu_i2c_data.mag_y_raw * 0.6f;
    g_mpu_i2c_data.mz = g_mpu_i2c_data.mag_z_raw * 0.6f;
}

/************************* 读取全部九轴数据 *************************/
void MPU9250_I2C_ReadAll(void)
{
    MPU9250_I2C_ReadAccelGyroTemp();
    MPU9250_I2C_ReadMag();
}

/************************* 新增：陀螺仪零偏校准 *************************/
/**
 * @brief  陀螺仪零偏校准，调用时需保持模块静止水平
 * @param  sample_cnt 采样次数，推荐100~500次
 */
void MPU9250_GyroCalibrate(uint16_t sample_cnt)
{
    int32_t gx_sum = 0, gy_sum = 0, gz_sum = 0;
    uint8_t buf[14];

    g_mpu_i2c_data.gyro_bias_x = 0;
    g_mpu_i2c_data.gyro_bias_y = 0;
    g_mpu_i2c_data.gyro_bias_z = 0;

    for(uint16_t i = 0; i < sample_cnt; i++)
    {
        mpu_read_regs(MPU9250_ADDR, REG_ACCEL_XOUT_H, buf, 14);
        gx_sum += (int16_t)((buf[8] << 8) | buf[9]);
        gy_sum += (int16_t)((buf[10] << 8) | buf[11]);
        gz_sum += (int16_t)((buf[12] << 8) | buf[13]);
        DDL_DelayMS(5);
    }

    g_mpu_i2c_data.gyro_bias_x = (float)gx_sum / sample_cnt;
    g_mpu_i2c_data.gyro_bias_y = (float)gy_sum / sample_cnt;
    g_mpu_i2c_data.gyro_bias_z = (float)gz_sum / sample_cnt;
}

/************************* 新增：9轴四元数姿态解算（Mahony互补滤波） *************************/
/**
 * @brief  9轴姿态解算，融合加速度+陀螺仪+磁力计
 * @param  dt 采样周期，单位：秒
 */
void MPU9250_IIC_AttitudeCalc(float dt)
{
    float norm;
    float hx, hy, hz;
    float bx, bz;
    float vx, vy, vz;
    float wx, wy, wz;
    float ex, ey, ez;
    float gx_rad, gy_rad, gz_rad;

    // 读取数据并转换为 rad/s
    gx_rad = g_mpu_i2c_data.gx * 0.0174533f;
    gy_rad = g_mpu_i2c_data.gy * 0.0174533f;
    gz_rad = g_mpu_i2c_data.gz * 0.0174533f;

    // ========== 1. 加速度计归一化 ==========
    norm = sqrtf(g_mpu_i2c_data.ax*g_mpu_i2c_data.ax + 
                 g_mpu_i2c_data.ay*g_mpu_i2c_data.ay + 
                 g_mpu_i2c_data.az*g_mpu_i2c_data.az);
    if (norm > 0.001f) {
        g_mpu_i2c_data.ax /= norm;
        g_mpu_i2c_data.ay /= norm;
        g_mpu_i2c_data.az /= norm;
    }

    // ========== 2. 磁力计归一化 ==========
    norm = sqrtf(g_mpu_i2c_data.mx*g_mpu_i2c_data.mx + 
                 g_mpu_i2c_data.my*g_mpu_i2c_data.my + 
                 g_mpu_i2c_data.mz*g_mpu_i2c_data.mz);
    if (norm > 0.001f) {
        g_mpu_i2c_data.mx /= norm;
        g_mpu_i2c_data.my /= norm;
        g_mpu_i2c_data.mz /= norm;
    }

    // ========== 3. 计算地理坐标系下地磁参考向量 ==========
    // 将磁力计从机体坐标系转到地理坐标系
    hx = 2.0f * (g_mpu_i2c_data.mx * (0.5f - g_mpu_i2c_data.q2*g_mpu_i2c_data.q2 - g_mpu_i2c_data.q3*g_mpu_i2c_data.q3) +
                 g_mpu_i2c_data.my * (g_mpu_i2c_data.q1*g_mpu_i2c_data.q2 - g_mpu_i2c_data.q0*g_mpu_i2c_data.q3) +
                 g_mpu_i2c_data.mz * (g_mpu_i2c_data.q1*g_mpu_i2c_data.q3 + g_mpu_i2c_data.q0*g_mpu_i2c_data.q2));
    hy = 2.0f * (g_mpu_i2c_data.mx * (g_mpu_i2c_data.q1*g_mpu_i2c_data.q2 + g_mpu_i2c_data.q0*g_mpu_i2c_data.q3) +
                 g_mpu_i2c_data.my * (0.5f - g_mpu_i2c_data.q1*g_mpu_i2c_data.q1 - g_mpu_i2c_data.q3*g_mpu_i2c_data.q3) +
                 g_mpu_i2c_data.mz * (g_mpu_i2c_data.q2*g_mpu_i2c_data.q3 - g_mpu_i2c_data.q0*g_mpu_i2c_data.q1));
    hz = 2.0f * (g_mpu_i2c_data.mx * (g_mpu_i2c_data.q1*g_mpu_i2c_data.q3 - g_mpu_i2c_data.q0*g_mpu_i2c_data.q2) +
                 g_mpu_i2c_data.my * (g_mpu_i2c_data.q2*g_mpu_i2c_data.q3 + g_mpu_i2c_data.q0*g_mpu_i2c_data.q1) +
                 g_mpu_i2c_data.mz * (0.5f - g_mpu_i2c_data.q1*g_mpu_i2c_data.q1 - g_mpu_i2c_data.q2*g_mpu_i2c_data.q2));

    // 地磁水平分量与垂直分量
    bx = sqrtf(hx*hx + hy*hy);
    bz = hz;

    // ========== 4. 计算机体坐标系下的参考向量（重力 + 地磁） ==========
    // 重力方向投影
    vx = 2.0f * (g_mpu_i2c_data.q1*g_mpu_i2c_data.q3 - g_mpu_i2c_data.q0*g_mpu_i2c_data.q2);
    vy = 2.0f * (g_mpu_i2c_data.q0*g_mpu_i2c_data.q1 + g_mpu_i2c_data.q2*g_mpu_i2c_data.q3);
    vz = g_mpu_i2c_data.q0*g_mpu_i2c_data.q0 - g_mpu_i2c_data.q1*g_mpu_i2c_data.q1 
         - g_mpu_i2c_data.q2*g_mpu_i2c_data.q2 + g_mpu_i2c_data.q3*g_mpu_i2c_data.q3;

    // 地磁方向投影
    wx = bx * (g_mpu_i2c_data.q0*g_mpu_i2c_data.q0 + g_mpu_i2c_data.q1*g_mpu_i2c_data.q1 
               - g_mpu_i2c_data.q2*g_mpu_i2c_data.q2 - g_mpu_i2c_data.q3*g_mpu_i2c_data.q3)
         + 2.0f * bz * (g_mpu_i2c_data.q1*g_mpu_i2c_data.q3 - g_mpu_i2c_data.q0*g_mpu_i2c_data.q2);
    wy = 2.0f * bx * (g_mpu_i2c_data.q1*g_mpu_i2c_data.q2 - g_mpu_i2c_data.q0*g_mpu_i2c_data.q3)
         + 2.0f * bz * (g_mpu_i2c_data.q0*g_mpu_i2c_data.q1 + g_mpu_i2c_data.q2*g_mpu_i2c_data.q3);
    wz = 2.0f * bx * (g_mpu_i2c_data.q0*g_mpu_i2c_data.q2 + g_mpu_i2c_data.q1*g_mpu_i2c_data.q3)
         + bz * (g_mpu_i2c_data.q0*g_mpu_i2c_data.q0 - g_mpu_i2c_data.q1*g_mpu_i2c_data.q1
                 - g_mpu_i2c_data.q2*g_mpu_i2c_data.q2 + g_mpu_i2c_data.q3*g_mpu_i2c_data.q3);

    // ========== 5. 误差计算（测量值与估计值叉积） ==========
    ex = (g_mpu_i2c_data.ay * vz - g_mpu_i2c_data.az * vy) + (g_mpu_i2c_data.my * wz - g_mpu_i2c_data.mz * wy);
    ey = (g_mpu_i2c_data.az * vx - g_mpu_i2c_data.ax * vz) + (g_mpu_i2c_data.mz * wx - g_mpu_i2c_data.mx * wz);
    ez = (g_mpu_i2c_data.ax * vy - g_mpu_i2c_data.ay * vx) + (g_mpu_i2c_data.mx * wy - g_mpu_i2c_data.my * wx);

    // ========== 6. PI 修正陀螺仪角速度 ==========
    g_mpu_i2c_data.ex_int += ex * AHRS_KI * dt;
    g_mpu_i2c_data.ey_int += ey * AHRS_KI * dt;
    g_mpu_i2c_data.ez_int += ez * AHRS_KI * dt;

    gx_rad += AHRS_KP * ex + g_mpu_i2c_data.ex_int;
    gy_rad += AHRS_KP * ey + g_mpu_i2c_data.ey_int;
    gz_rad += AHRS_KP * ez + g_mpu_i2c_data.ez_int;

    // ========== 7. 四元数微分方程更新 ==========
    g_mpu_i2c_data.q0 += (-g_mpu_i2c_data.q1*gx_rad - g_mpu_i2c_data.q2*gy_rad - g_mpu_i2c_data.q3*gz_rad) * 0.5f * dt;
    g_mpu_i2c_data.q1 += ( g_mpu_i2c_data.q0*gx_rad + g_mpu_i2c_data.q2*gz_rad - g_mpu_i2c_data.q3*gy_rad) * 0.5f * dt;
    g_mpu_i2c_data.q2 += ( g_mpu_i2c_data.q0*gy_rad - g_mpu_i2c_data.q1*gz_rad + g_mpu_i2c_data.q3*gx_rad) * 0.5f * dt;
    g_mpu_i2c_data.q3 += ( g_mpu_i2c_data.q0*gz_rad + g_mpu_i2c_data.q1*gy_rad - g_mpu_i2c_data.q2*gx_rad) * 0.5f * dt;

    // ========== 8. 四元数归一化 ==========
    norm = sqrtf(g_mpu_i2c_data.q0*g_mpu_i2c_data.q0 + 
                 g_mpu_i2c_data.q1*g_mpu_i2c_data.q1 + 
                 g_mpu_i2c_data.q2*g_mpu_i2c_data.q2 + 
                 g_mpu_i2c_data.q3*g_mpu_i2c_data.q3);
    g_mpu_i2c_data.q0 /= norm;
    g_mpu_i2c_data.q1 /= norm;
    g_mpu_i2c_data.q2 /= norm;
    g_mpu_i2c_data.q3 /= norm;

    // ========== 9. 四元数转欧拉角 ==========
    g_mpu_i2c_data.roll  = atan2f(2*(g_mpu_i2c_data.q0*g_mpu_i2c_data.q1 + g_mpu_i2c_data.q2*g_mpu_i2c_data.q3), 
                                  1 - 2*(g_mpu_i2c_data.q1*g_mpu_i2c_data.q1 + g_mpu_i2c_data.q2*g_mpu_i2c_data.q2)) * 57.2957795f;
    g_mpu_i2c_data.pitch = asinf(2*(g_mpu_i2c_data.q0*g_mpu_i2c_data.q2 - g_mpu_i2c_data.q1*g_mpu_i2c_data.q3)) * 57.2957795f;
    g_mpu_i2c_data.yaw   = atan2f(2*(g_mpu_i2c_data.q0*g_mpu_i2c_data.q3 + g_mpu_i2c_data.q1*g_mpu_i2c_data.q2), 
                                  1 - 2*(g_mpu_i2c_data.q2*g_mpu_i2c_data.q2 + g_mpu_i2c_data.q3*g_mpu_i2c_data.q3)) * 57.2957795f;

    // 航向角归一化到 0~360°
    if (g_mpu_i2c_data.yaw < 0) {
        g_mpu_i2c_data.yaw += 360.0f;
    }
}

















