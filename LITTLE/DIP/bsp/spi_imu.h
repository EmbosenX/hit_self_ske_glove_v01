/**
 *******************************************************************************
 * @file  spi_imu.h
 * @brief This file provides firmware functions to W25QXX group spi flash.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
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
#ifndef __SPI_IMU_H__
#define __SPI_IMU_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"
#include "hc32_ll.h"
#include "ev_hc32f460_lqfp100_v2_bsp.h"
#include <string.h>
#include "hc32_ll_spi.h"
#include "hc32_ll_aos.h"

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup Fingers_Global_Types FINGERS Global Types
 * @{
 */

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup FINGERS_Global_Macros FINGERS Global Macros
 * @{
 */
/* IMU 数据结构体 */
typedef struct {
    int16_t acc_x_raw;  // 加速度原始值
    int16_t acc_y_raw;
    int16_t acc_z_raw;
    int16_t gyro_x_raw; // 陀螺仪原始值
    int16_t gyro_y_raw;
    int16_t gyro_z_raw;
    int16_t temp_raw;   // 温度原始值
    int16_t mag_x_raw;  // 磁力计原始值
    int16_t mag_y_raw;
    int16_t mag_z_raw;
	
    float ax;   // 加速度 单位：g
    float ay;
    float az;
    float gx;   // 角速度 单位：°/s
    float gy;
    float gz;
    float temp; // 温度 单位：℃
    float mx;		// 磁力计物理值，单位：μT
		float my;
		float mz;   

    float mag_asa[3];   // 工厂灵敏度校准系数
		
    float roll;  // 横滚角 °
    float pitch; // 俯仰角 °
    float yaw;   // 航向角 °
		
    float q0, q1, q2, q3;   // 姿态四元数
    float ex_int, ey_int, ez_int; // 积分误差项（PI修正用）
} mpu9250_data_t;
/**
 * @defgroup 
 * @{
 */
extern mpu9250_data_t imu_data[3];
/**
 * @}
 */

/**
 * @defgroup 
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup 
 * @{
 */

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
void IMU_SPI_Config(void);
int8_t MPU9250_Init(uint8_t cs_num);
void MPU9250_ReadData(uint8_t cs_num);
void MPU9250_AttitudeCalc(uint8_t cs_num, float dt);
int8_t AK8963_Init(uint8_t cs_num);
uint8_t ak8963_debug_read_id(uint8_t cs_num);
void MPU9250_AttitudeCalc_Quaternion(uint8_t cs_num, float dt);
#ifdef __cplusplus
}
#endif

#endif

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
