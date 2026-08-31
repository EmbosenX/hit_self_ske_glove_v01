/* ==================== 用户代码开始 ==================== */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* ==================== 用户代码结束 ==================== */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* ==================== 用户代码开始 ==================== */
#include "usb_bsp.h"
#include "adc_sample.h"
#include "usart_bsp.h"
#include "queue.h"

#include <stdlib.h>
#include <string.h>
/* ==================== 用户代码结束 ==================== */

/* ==================== 私有类型定义 ==================== */
typedef StaticTask_t osStaticThreadDef_t;
typedef StaticQueue_t osStaticMessageQDef_t;
/* ==================== 用户代码开始 ==================== */

/* ==================== 用户代码结束 ==================== */

/* ==================== 私有宏定义 ==================== */
/* ==================== 用户代码开始 ==================== */

/* ==================== 用户代码结束 ==================== */

/* ==================== 私有宏定义 ==================== */
/* ==================== 用户代码开始 ==================== */

/* ==================== 用户代码结束 ==================== */

/* ==================== 私有变量 ==================== */
/* ==================== 用户代码开始 ==================== */

/* ==================== 用户代码结束 ==================== */
/* Definitions for UsbTask */
osThreadId_t UsbTaskHandle;
uint32_t UsbTaskBuffer[ 1024 ];
osStaticThreadDef_t UsbTaskControlBlock;
const osThreadAttr_t UsbTask_attributes = {
  .name = "UsbTask",
  .cb_mem = &UsbTaskControlBlock,
  .cb_size = sizeof(UsbTaskControlBlock),
  .stack_mem = &UsbTaskBuffer[0],
  .stack_size = sizeof(UsbTaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for SampleTask */
osThreadId_t SampleTaskHandle;
uint32_t SampleTaskBuffer[ 1024 ];
osStaticThreadDef_t SampleTaskControlBlock;
const osThreadAttr_t SampleTask_attributes = {
  .name = "SampleTask",
  .cb_mem = &SampleTaskControlBlock,
  .cb_size = sizeof(SampleTaskControlBlock),
  .stack_mem = &SampleTaskBuffer[0],
  .stack_size = sizeof(SampleTaskBuffer),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for UsartTask */
osThreadId_t UsartTaskHandle;
uint32_t UsartTaskBuffer[ 1024 ];
osStaticThreadDef_t UsartTaskControlBlock;
const osThreadAttr_t UsartTask_attributes = {
  .name = "UsartTask",
  .cb_mem = &UsartTaskControlBlock,
  .cb_size = sizeof(UsartTaskControlBlock),
  .stack_mem = &UsartTaskBuffer[0],
  .stack_size = sizeof(UsartTaskBuffer),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for LedTask */
osThreadId_t LedTaskHandle;
uint32_t LedTaskBuffer[ 128 ];
osStaticThreadDef_t LedTaskControlBlock;
const osThreadAttr_t LedTask_attributes = {
  .name = "LedTask",
  .cb_mem = &LedTaskControlBlock,
  .cb_size = sizeof(LedTaskControlBlock),
  .stack_mem = &LedTaskBuffer[0],
  .stack_size = sizeof(LedTaskBuffer),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for IapTask */
osThreadId_t IapTaskHandle;
uint32_t IapTaskBuffer[ 512 ];
osStaticThreadDef_t IapTaskControlBlock;
const osThreadAttr_t IapTask_attributes = {
  .name = "IapTask",
  .cb_mem = &IapTaskControlBlock,
  .cb_size = sizeof(IapTaskControlBlock),
  .stack_mem = &IapTaskBuffer[0],
  .stack_size = sizeof(IapTaskBuffer),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Usart2Queue */
osMessageQueueId_t Usart2QueueHandle;
uint8_t Usart2QueueBuffer[ 16 * sizeof( usart_frame_t ) ];
osStaticMessageQDef_t Usart2QueueControlBlock;
const osMessageQueueAttr_t Usart2Queue_attributes = {
  .name = "Usart2Queue",
  .cb_mem = &Usart2QueueControlBlock,
  .cb_size = sizeof(Usart2QueueControlBlock),
  .mq_mem = &Usart2QueueBuffer,
  .mq_size = sizeof(Usart2QueueBuffer)
};
/* Definitions for Usart3Queue */
osMessageQueueId_t Usart3QueueHandle;
uint8_t Usart3QueueBuffer[ 16 * sizeof( usart_frame_t ) ];
osStaticMessageQDef_t Usart3QueueControlBlock;
const osMessageQueueAttr_t Usart3Queue_attributes = {
  .name = "Usart3Queue",
  .cb_mem = &Usart3QueueControlBlock,
  .cb_size = sizeof(Usart3QueueControlBlock),
  .mq_mem = &Usart3QueueBuffer,
  .mq_size = sizeof(Usart3QueueBuffer)
};
/* Definitions for Usart4Queue */
osMessageQueueId_t Usart4QueueHandle;
uint8_t Usart4QueueBuffer[ 16 * sizeof( usart_frame_t ) ];
osStaticMessageQDef_t Usart4QueueControlBlock;
const osMessageQueueAttr_t Usart4Queue_attributes = {
  .name = "Usart4Queue",
  .cb_mem = &Usart4QueueControlBlock,
  .cb_size = sizeof(Usart4QueueControlBlock),
  .mq_mem = &Usart4QueueBuffer,
  .mq_size = sizeof(Usart4QueueBuffer)
};
/* Definitions for Usart5Queue */
osMessageQueueId_t Usart5QueueHandle;
uint8_t Usart5QueueBuffer[ 16 * sizeof( usart_frame_t ) ];
osStaticMessageQDef_t Usart5QueueControlBlock;
const osMessageQueueAttr_t Usart5Queue_attributes = {
  .name = "Usart5Queue",
  .cb_mem = &Usart5QueueControlBlock,
  .cb_size = sizeof(Usart5QueueControlBlock),
  .mq_mem = &Usart5QueueBuffer,
  .mq_size = sizeof(Usart5QueueBuffer)
};
/* Definitions for Usart7Queue */
osMessageQueueId_t Usart7QueueHandle;
uint8_t Usart7QueueBuffer[ 16 * sizeof( usart_frame_t ) ];
osStaticMessageQDef_t Usart7QueueControlBlock;
const osMessageQueueAttr_t Usart7Queue_attributes = {
  .name = "Usart7Queue",
  .cb_mem = &Usart7QueueControlBlock,
  .cb_size = sizeof(Usart7QueueControlBlock),
  .mq_mem = &Usart7QueueBuffer,
  .mq_size = sizeof(Usart7QueueBuffer)
};

/* ==================== 私有函数声明 ==================== */
/* ==================== 用户代码开始 ==================== */
/* Definitions for Usart1Queue */
osMessageQueueId_t Usart1QueueHandle;
uint8_t Usart1QueueBuffer[ 16 * sizeof( usart_frame_t ) ];
osStaticMessageQDef_t Usart1QueueControlBlock;
const osMessageQueueAttr_t Usart1Queue_attributes = {
  .name = "Usart1Queue",
  .cb_mem = &Usart1QueueControlBlock,
  .cb_size = sizeof(Usart1QueueControlBlock),
  .mq_mem = &Usart1QueueBuffer,
  .mq_size = sizeof(Usart1QueueBuffer)
};
/* Definitions for UsbCdcRxQueue 保持单字节不变，如需整帧可同法修改 */
osMessageQueueId_t UsbCdcRxQueueHandle;
uint8_t UsbCdcRxQueueBuffer[ 1024 * sizeof( uint8_t ) ];
osStaticMessageQDef_t UsbCdcRxQueueControlBlock;
const osMessageQueueAttr_t UsbCdcRxQueue_attributes = {
  .name = "UsbCdcRxQueue",
  .cb_mem = &UsbCdcRxQueueControlBlock,
  .cb_size = sizeof(UsbCdcRxQueueControlBlock),
  .mq_mem = &UsbCdcRxQueueBuffer,
  .mq_size = sizeof(UsbCdcRxQueueBuffer)
};
/* 发送消息队列：USB发送用，保持原样不变 */
#define USART_TX_QUEUE_DEPTH    (10U)
#define USART_BSP_MAX_FRAME_LEN         (768U)
typedef struct {
    uint16_t u16Len;
    uint8_t  au8Data[USART_BSP_MAX_FRAME_LEN];
} stc_usart_tx_msg_t;
static StaticQueue_t m_xTxQueueBuffer;
static uint8_t m_au8TxQueueStorage[USART_TX_QUEUE_DEPTH * sizeof(stc_usart_tx_msg_t)];
static QueueHandle_t m_xTxQueue = NULL;
static stc_usart_tx_msg_t stcTxMsg={0};
/* ==================== 用户代码结束 ==================== */

void StartUsbTask(void *argument);
void StartSampleTask(void *argument);
void StartUsartTask(void *argument);
void StartLedTask(void *argument);
void StartIapTask(void *argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */

  /* ==================== 用户代码开始 ==================== */
  /* add mutexes, ... */
  /* ==================== 用户代码结束 ==================== */

  /* ==================== 用户代码开始 ==================== */
  /* add semaphores, ... */
  /* ==================== 用户代码结束 ==================== */

  /* ==================== 用户代码开始 ==================== */
  /* start timers, add new ones, ... */
  /* ==================== 用户代码结束 ==================== */

  /* Create the queue(s) */
  /* creation of Usart2Queue */
  Usart2QueueHandle = osMessageQueueNew (16, sizeof(usart_frame_t), &Usart2Queue_attributes);

  /* creation of Usart3Queue */
  Usart3QueueHandle = osMessageQueueNew (16, sizeof(usart_frame_t), &Usart3Queue_attributes);

  /* creation of Usart4Queue */
  Usart4QueueHandle = osMessageQueueNew (16, sizeof(usart_frame_t), &Usart4Queue_attributes);

  /* creation of Usart5Queue */
  Usart5QueueHandle = osMessageQueueNew (16, sizeof(usart_frame_t), &Usart5Queue_attributes);

  /* creation of Usart7Queue */
  Usart7QueueHandle = osMessageQueueNew (16, sizeof(usart_frame_t), &Usart7Queue_attributes);

  /* ==================== 用户代码开始 ==================== */
  /* creation of Usart1Queue */
  Usart1QueueHandle = osMessageQueueNew (16, sizeof(usart_frame_t), &Usart1Queue_attributes);
	/* creation of UsbCdcRxQueue */
	UsbCdcRxQueueHandle = osMessageQueueNew (1024, sizeof(uint8_t), &UsbCdcRxQueue_attributes);
	/* 创建发送队列 */
	m_xTxQueue = xQueueCreateStatic(USART_TX_QUEUE_DEPTH,
																	sizeof(stc_usart_tx_msg_t),
																	m_au8TxQueueStorage,   /* 数据存储区 */
																	&m_xTxQueueBuffer);    /* 队列控制块 */
  /* ==================== 用户代码结束 ==================== */

  /* Create the thread(s) */
  /* creation of UsbTask */
  UsbTaskHandle = osThreadNew(StartUsbTask, NULL, &UsbTask_attributes);

  /* creation of SampleTask */
  SampleTaskHandle = osThreadNew(StartSampleTask, NULL, &SampleTask_attributes);

  /* creation of UsartTask */
  UsartTaskHandle = osThreadNew(StartUsartTask, NULL, &UsartTask_attributes);

  /* creation of LedTask */
  LedTaskHandle = osThreadNew(StartLedTask, NULL, &LedTask_attributes);

  /* creation of IapTask */
  IapTaskHandle = osThreadNew(StartIapTask, NULL, &IapTask_attributes);

  /* ==================== 用户代码开始 ==================== */
  /* add threads, ... */
  /* ==================== 用户代码结束 ==================== */

  /* ==================== 用户代码开始 ==================== */
  /* add events, ... */
  /* ==================== 用户代码结束 ==================== */

}

/* ==================== 用户代码开始 ==================== */
/**
  * @brief  Function implementing the UsbTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* ==================== 用户代码结束 ==================== */
void StartUsbTask(void *argument)
{
  /* init code for USB_DEVICE */
	vTaskSuspend(UsbTaskHandle);
  MX_USB_DEVICE_Init();
  /* ==================== 用户代码开始 ==================== */
	UsbCdc_Init();   /* BSP初始化 */
  /* Infinite loop */
  for(;;)
  {
			/************************ 等待外部任务通知采集完成 ************************/
			ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
			/* ---------- 所有手指一次性组帧并入队 ---------- */
			/* 大拇指 */
			stcTxMsg.u16Len = finger_data_tx_frame(TAC_AREA_THUMB_DIP+TAC_AREA_THUMB_MCP, stcTxMsg.au8Data);
			xQueueSend(m_xTxQueue, &stcTxMsg, 1000);
			/* 食指 */
			stcTxMsg.u16Len = finger_data_tx_frame(TAC_AREA_INDEX_DIP+TAC_AREA_INDEX_PIP+TAC_AREA_INDEX_MCP, stcTxMsg.au8Data);
			xQueueSend(m_xTxQueue, &stcTxMsg, 1000);
			/* 中指 */
			stcTxMsg.u16Len = finger_data_tx_frame(TAC_AREA_MIDDLE_DIP+TAC_AREA_MIDDLE_PIP+TAC_AREA_MIDDLE_MCP, stcTxMsg.au8Data);
			xQueueSend(m_xTxQueue, &stcTxMsg, 1000);
			/* 无名指 */
			stcTxMsg.u16Len = finger_data_tx_frame(TAC_AREA_RING_DIP+TAC_AREA_RING_PIP+TAC_AREA_RING_MCP, stcTxMsg.au8Data);
			xQueueSend(m_xTxQueue, &stcTxMsg, 1000);
			/* 小指 */
			stcTxMsg.u16Len = finger_data_tx_frame(TAC_AREA_LITTLE_DIP+TAC_AREA_LITTLE_PIP+TAC_AREA_LITTLE_MCP, stcTxMsg.au8Data);
			xQueueSend(m_xTxQueue, &stcTxMsg, 1000);
			/* 掌心 */
			stcTxMsg.u16Len = finger_data_tx_frame(TAC_AREA_PALM1+TAC_AREA_PALM2, stcTxMsg.au8Data);
			xQueueSend(m_xTxQueue, &stcTxMsg, 1000);
			/* ---------- 逐个发送队列里的帧，发完一帧再发下一帧 ---------- */
			while (uxQueueMessagesWaiting(m_xTxQueue) > 0) {
					xQueueReceive(m_xTxQueue, &stcTxMsg, 100);
				/* USB阻塞发送 */
					UsbCdc_Send(stcTxMsg.au8Data, stcTxMsg.u16Len);
			}
  }
  /* ==================== 用户代码结束 ==================== */
}

/* ==================== 用户代码开始 ==================== */
/**
* @brief Function implementing the SampleTask thread.
* @param argument: Not used
* @retval None
*/
/* ==================== 用户代码结束 ==================== */
void StartSampleTask(void *argument)
{
  /* ==================== 用户代码开始 ==================== */
	/* 采集使能时执行ADC采样 */
	Sample_Init();
	osDelay(100);
	Sample_Caliber();
  /* Infinite loop */
  for(;;)
  {
        /************************ 第一步：等待外部任务通知启动采集 ************************/
        /* 采集使能时执行ADC采样 */
				ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        Sample_DoCollect();
				if(UsartTaskHandle!=NULL)
				{
					xTaskNotifyGive(UsartTaskHandle);
				}
  }
  /* ==================== 用户代码结束 ==================== */
}

/* ==================== 用户代码开始 ==================== */
/**
* @brief Function implementing the UsartTask thread.
* @param argument: Not used
* @retval None
*/
/* ==================== 用户代码结束 ==================== */
void StartUsartTask(void *argument)
{
  /* ==================== 用户代码开始 ==================== */
  usart_frame_t rx_frame[USART_BSP_NUM]={0};
  osStatus_t status;
	uint32_t task_ret=0;
	UsartBsp_Init();
  /* Infinite loop */
  for(;;)
  {
    /* 阻塞等待最新帧，永远拿到的是当前最新的一帧，旧帧自动丢弃 */
		task_ret = ulTaskNotifyTake(pdTRUE, 1);
		if(task_ret==pdTRUE)
		{
			stcTxMsg.u16Len = finger_data_tx_frame(TAC_AREA_PALM1, stcTxMsg.au8Data);
			xQueueSend(m_xTxQueue, &stcTxMsg, 100);
			/* ---------- 逐个发送队列里的帧，发完一帧再发下一帧 ---------- */
			while (uxQueueMessagesWaiting(m_xTxQueue) > 0) {
					xQueueReceive(m_xTxQueue, &stcTxMsg, 100);
					/* 启动DMA发送 */
					UsartBsp_Send(USART_BSP_IDX_1, stcTxMsg.au8Data, stcTxMsg.u16Len);
			}
		}
		status = UsartBsp_ReadLatestFrame(USART_BSP_IDX_2, &rx_frame[USART_BSP_IDX_2], 0);
		if(status == osOK)
		{
				/* 业务处理：rx_frame.data 为完整帧（含0x3C 0x3C头、0x3E 0x3E尾） */
				UsartBsp_Send(USART_BSP_IDX_1, rx_frame[USART_BSP_IDX_2].data, rx_frame[USART_BSP_IDX_2].len);
		}
		status = UsartBsp_ReadLatestFrame(USART_BSP_IDX_3, &rx_frame[USART_BSP_IDX_3], 0);
		if(status == osOK)
		{
				/* 业务处理：rx_frame.data 为完整帧（含0x3C 0x3C头、0x3E 0x3E尾） */
				UsartBsp_Send(USART_BSP_IDX_1, rx_frame[USART_BSP_IDX_3].data, rx_frame[USART_BSP_IDX_3].len);
		}
		status = UsartBsp_ReadLatestFrame(USART_BSP_IDX_4, &rx_frame[USART_BSP_IDX_4], 0);
		if(status == osOK)
		{
				/* 业务处理：rx_frame.data 为完整帧（含0x3C 0x3C头、0x3E 0x3E尾） */
				UsartBsp_Send(USART_BSP_IDX_1, rx_frame[USART_BSP_IDX_4].data, rx_frame[USART_BSP_IDX_4].len);
		}
		status = UsartBsp_ReadLatestFrame(USART_BSP_IDX_5, &rx_frame[USART_BSP_IDX_5], 0);
		if(status == osOK)
		{
				/* 业务处理：rx_frame.data 为完整帧（含0x3C 0x3C头、0x3E 0x3E尾） */
				UsartBsp_Send(USART_BSP_IDX_1, rx_frame[USART_BSP_IDX_5].data, rx_frame[USART_BSP_IDX_5].len);
		}
		status = UsartBsp_ReadLatestFrame(USART_BSP_IDX_7, &rx_frame[USART_BSP_IDX_7], 0);
		if(status == osOK)
		{
				/* 业务处理：rx_frame.data 为完整帧（含0x3C 0x3C头、0x3E 0x3E尾） */
				UsartBsp_Send(USART_BSP_IDX_1, rx_frame[USART_BSP_IDX_7].data, rx_frame[USART_BSP_IDX_7].len);
		}
		if(SampleTaskHandle!=NULL)
		{
			xTaskNotifyGive(SampleTaskHandle);
		}
		RGB_led_set(GREEN,  GPIO_PIN_RESET);
  }
  /* ==================== 用户代码结束 ==================== */
}

/* ==================== 用户代码开始 ==================== */
/**
* @brief Function implementing the LedTask thread.
* @param argument: Not used
* @retval None
*/
/* ==================== 用户代码结束 ==================== */
void StartLedTask(void *argument)
{
  /* ==================== 用户代码开始 ==================== */
	uint32_t task_ret=0;
	RGB_led_set(RED,  GPIO_PIN_SET);
	RGB_led_set(BLUE,  GPIO_PIN_SET);
	RGB_led_set(GREEN,  GPIO_PIN_SET);
	RGB_led_set(BLUE,  GPIO_PIN_RESET);
	vTaskSuspend(LedTaskHandle);
  /* Infinite loop */
  for(;;)
  {
		task_ret = ulTaskNotifyTake(pdTRUE, 0);
		if(task_ret==pdTRUE)
		{
			RGB_led_set(GREEN,  GPIO_PIN_RESET);
		}
  }
  /* ==================== 用户代码结束 ==================== */
}

/* ==================== 用户代码开始 ==================== */
/**
* @brief Function implementing the IapTask thread.
* @param argument: Not used
* @retval None
*/
/* ==================== 用户代码结束 ==================== */
void StartIapTask(void *argument)
{
  /* ==================== 用户代码开始 ==================== */
	vTaskSuspend(IapTaskHandle);
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* ==================== 用户代码结束 ==================== */
}

/* Private application code --------------------------------------------------*/
/* ==================== 用户代码开始 ==================== */

/* ==================== 用户代码结束 ==================== */

