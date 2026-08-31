/**
 ******************************************************************************
 * @file    app_fingers_task.h
 * @brief   源文件
 ******************************************************************************
 */
#ifndef __APP_FINGERS_TASK_H__
#define __APP_FINGERS_TASK_H__

#include "hc32_ll.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/* 手指通道数量定义 */


/* 手指数据结构体 */



/* 任务消息枚举 */


/* 消息队列数据单元 */


/* 外部全局句柄声明 */
extern TaskHandle_t xAppFingersTaskHandle;



/* 对外函数声明 */
void APP_Fingers_TaskCreate(void);

#endif /* __APP_FINGERS_TASK_H__ */


