/**
 ******************************************************************************
 * @file    app_usart_task.h
 * @brief   串口通信任务头文件
 ******************************************************************************
 */

#ifndef __APP_USART_TASK_H__
#define __APP_USART_TASK_H__

#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"

#define USART_TASK_STACK_SIZE      256U
#define USART_TASK_PRIORITY        (configMAX_PRIORITIES - 3)

extern TaskHandle_t  xUsartTaskHandle;
/**
 * @brief  初始化并创建USART应用任务（静态内存分配）
 * @retval 1=成功，0=失败
 */
uint8_t APP_Usart_TaskCreate(void);

/**
 * @brief  串口发送接口（线程安全，可在其他任务调用）
 * @param  pu8Data 数据指针
 * @param  u16Len  数据长度
 * @retval 0=成功，其他=失败
 */
int32_t AppUsartTask_Send(const uint8_t *pu8Data, uint16_t u16Len);

#endif /* __APP_USART_TASK_H__ */


