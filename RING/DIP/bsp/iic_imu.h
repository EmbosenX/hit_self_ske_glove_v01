/**
 ******************************************************************************
 * @file    iic_imu.h
 * @brief   I2C IMU传感器驱动头文件
 ******************************************************************************
 */

#ifndef __IIC_IMU_H__
#define __IIC_IMU_H__

#include <stdint.h>
#include "hc32_ll.h"
/************************* 硬件引脚配置（根据实际板子修改）*************************/
#define MPU_I2C_SCL_PORT      GPIO_PORT_B
#define MPU_I2C_SCL_PIN       GPIO_PIN_12
#define MPU_I2C_SDA_PORT      GPIO_PORT_B
#define MPU_I2C_SDA_PIN       GPIO_PIN_13

/************************* 设备地址定义 *************************/
#define MPU9250_ADDR          0x68    // MPU9250 7位I2C地址（AD0低电平）
#define AK8963_ADDR           0x0C    // AK8963 7位I2C地址

/************************* 量程配置 *************************/
#define ACCEL_RANGE_2G        0x00
#define ACCEL_RANGE_4G        0x08
#define ACCEL_RANGE_8G        0x10
#define ACCEL_RANGE_16G       0x18

#define GYRO_RANGE_250DPS     0x00
#define GYRO_RANGE_500DPS     0x08
#define GYRO_RANGE_1000DPS    0x10
#define GYRO_RANGE_2000DPS    0x18

/************************* 姿态解算参数 *************************/
#define AHRS_KP               2.0f    // 比例增益：越大收敛越快，噪声越大
#define AHRS_KI               0.005f  // 积分增益：修正陀螺仪零偏漂移

/************************* 数据结构体 *************************/
typedef struct {
    /* 原始数据 */
    int16_t acc_x_raw;
    int16_t acc_y_raw;
    int16_t acc_z_raw;
    int16_t temp_raw;
    int16_t gyro_x_raw;
    int16_t gyro_y_raw;
    int16_t gyro_z_raw;
    int16_t mag_x_raw;
    int16_t mag_y_raw;
    int16_t mag_z_raw;

    /* 物理单位数据 */
    float ax;    // 单位 g
    float ay;
    float az;
    float gx;    // 单位 °/s（已扣除零偏）
    float gy;
    float gz;
    float temp;  // 单位 ℃
    float mx;    // 单位 μT
    float my;
    float mz;

    /* 校准参数 */
    float mag_asa[3];     // 磁力计工厂灵敏度校准系数
    float gyro_bias_x;    // 陀螺仪零偏
    float gyro_bias_y;
    float gyro_bias_z;

    /* 姿态解算中间量 */
    float q0, q1, q2, q3; // 姿态四元数
    float ex_int, ey_int, ez_int; // PI积分误差项

    /* 最终欧拉角 单位：° */
    float roll;   // 横滚角 -180° ~ 180°
    float pitch;  // 俯仰角 -90° ~ 90°
    float yaw;    // 航向角 0° ~ 360°（地磁北为0）
} mpu9250_i2c_data_t;

/************************* 函数声明 *************************/
void MPU9250_I2C_InitGPIO(void);
int8_t MPU9250_I2C_Init(void);
void MPU9250_I2C_ReadAccelGyroTemp(void);
void MPU9250_I2C_ReadMag(void);
void MPU9250_I2C_ReadAll(void);

/* 新增：校准与姿态解算 */
void MPU9250_GyroCalibrate(uint16_t sample_cnt);
void MPU9250_IIC_AttitudeCalc(float dt);

extern mpu9250_i2c_data_t g_mpu_i2c_data;

#endif


