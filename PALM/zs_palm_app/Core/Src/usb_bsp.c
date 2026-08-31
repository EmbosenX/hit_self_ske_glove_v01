/**
 ******************************************************************************
 * @file    usb_bsp.c
 * @brief   USB设备端BSP驱动，实现USB硬件层初始化和中断处理
 ******************************************************************************
 */

#include "usb_bsp.h"
#include "usbd_cdc_if.h"
#include <string.h>
#include "FreeRTOS.h"
#include "app_tac_config.h"
#include "usbd_core.h"
#include "usb_device.h"
/* 外部接收队列句柄，需在freertos.c中静态定义并创建 */
extern osMessageQueueId_t UsbCdcRxQueueHandle;

/* 发送同步二进制信号量（静态控制块，编译期分配内存） */
static StaticSemaphore_t s_tx_sem_cb;
static osSemaphoreId_t   s_tx_sem;
static uint8_t           s_tx_busy = 0U;

/* USB FS模式CDC端点最大包长（固定64字节） */
#define USB_CDC_FS_MPS    64U

/* ==================== 用户代码结束 ==================== */
/**
  * @brief  判断USB是否枚举完成（进入配置状态）
  * @retval 1: 已枚举 0: 未枚举/挂起
  */
uint8_t UsbCdc_IsEnumerated(void)
{
    return (hUsbDeviceFS.dev_state == USBD_STATE_CONFIGURED) ? 1U : 0U;
}
/**
  * @brief  判断USB线是否物理插入（VBUS供电）
  * @retval 1: 已插入 0: 未插入
  */
uint8_t UsbCdc_IsVbusPresent(void)
{
    return (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) == GPIO_PIN_SET) ? 1U : 0U;
}
/**
  * @brief  USB CDC BSP初始化
  */
void UsbCdc_Init(void)
{
    osSemaphoreAttr_t sem_attr = {0};
    
    /* 静态创建二进制信号量，用于发送完成同步 */
    sem_attr.cb_mem  = &s_tx_sem_cb;
    sem_attr.cb_size = sizeof(StaticSemaphore_t);
    
    s_tx_sem = osSemaphoreNew(1U, 0U, &sem_attr);
    s_tx_busy = 0U;
}

/**
  * @brief  USB发送完成中断回调处理
  */
void UsbCdc_TxCpltHandler(void)
{
    if (s_tx_busy)
    {
        s_tx_busy = 0U;
        osSemaphoreRelease(s_tx_sem);
    }
}

/**
  * @brief  USB接收数据处理：逐字节写入FreeRTOS队列
  * @note   运行在USB中断上下文，非阻塞写入，队列满则丢弃
  */
void UsbCdc_RxHandler(uint8_t *buf, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++)
    {
        osMessageQueuePut(UsbCdcRxQueueHandle, &buf[i], 0U, 0U);
    }
}

/**
  * @brief  阻塞发送不定长数据包，自动按64字节分包，支持ZLP结束包
  */
HAL_StatusTypeDef UsbCdc_Send(uint8_t *data, uint16_t len)
{
    /* 参数校验 */
    if (data == NULL || len == 0U || len > USB_CDC_MAX_TX_LEN)
    {
        return HAL_ERROR;
    }

    /* 等待上一次发送完成，保证线程安全 */
    if (s_tx_busy)
    {
        osSemaphoreAcquire(s_tx_sem, osWaitForever);
    }

    uint16_t offset = 0U;
    uint16_t remain = len;

    /* 循环分包发送 */
    while (remain > 0U)
    {
        /* 计算本次发包长度，不超过最大包长 */
        uint16_t send_len = (remain > USB_CDC_FS_MPS) ? USB_CDC_FS_MPS : remain;

        s_tx_busy = 1U;
        
        /* 调用原厂CDC发送接口 */
        uint8_t ret = CDC_Transmit_FS(&data[offset], send_len);
        if (ret != USBD_OK)
        {
            s_tx_busy = 0U;
            return HAL_ERROR;
        }

        /* 阻塞等待本包发送完成 */
        osSemaphoreAcquire(s_tx_sem, osWaitForever);

        offset += send_len;
        remain -= send_len;
    }

    /* 关键：若数据总长度刚好是64的整数倍，发送零长度包(ZLP)结束传输
       否则上位机会认为数据未结束，持续等待后续包 */
    if ((len % USB_CDC_FS_MPS) == 0U)
    {
        s_tx_busy = 1U;
        uint8_t ret = CDC_Transmit_FS(NULL, 0U);
        if (ret == USBD_OK)
        {
            osSemaphoreAcquire(s_tx_sem, osWaitForever);
        }
        else
        {
            s_tx_busy = 0U;
            return HAL_ERROR;
        }
    }

    return HAL_OK;
}

/**
  * @brief  从接收队列读取单字节
  */
osStatus_t UsbCdc_ReadByte(uint8_t *pByte, uint32_t timeout)
{
    if (pByte == NULL)
    {
        return osErrorParameter;
    }
    return osMessageQueueGet(UsbCdcRxQueueHandle, pByte, NULL, timeout);
}


uint16_t usart_crc16(const uint8_t *data, uint16_t size)
{
    uint16_t crc = 0x0000U;
    uint16_t i;
    uint8_t bit;

    for (i = 0U; i < size; ++i) {
        crc ^= data[i];
        for (bit = 0U; bit < 8U; ++bit) {
            if ((crc & 0x0001U) != 0U) {
                crc = (uint16_t)((crc >> 1U) ^ 0xA001U);
            } else {
                crc >>= 1U;
            }
        }
    }

    return crc;
}


