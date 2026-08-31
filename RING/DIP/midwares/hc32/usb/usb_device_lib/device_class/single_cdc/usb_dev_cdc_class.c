/**
 *******************************************************************************
 * @file  usb_dev_cdc_class.c
 * @brief The CDC VCP core functions.
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "usb_dev_cdc_class.h"
#include "usb_dev_driver.h"
#include "usb_dev_ctrleptrans.h"
#include "usb_dev_stdreq.h"
#include "usb_dev_desc.h"
#include "cdc_data_process.h"
#include <stdbool.h>
#include "app_usb_task.h"
/**
 * @addtogroup LL_USB_LIB
 * @{
 */
extern __weak usb_core_instance usb_dev;
/**
 * @addtogroup LL_USB_DEV_CLASS
 * @{
 */

/**
 * @addtogroup LL_USB_SINGLE_CDC USB Device CDC
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define USB_RX_FIFO_SIZE        256U    /* PC下发数据缓存大小，按需调整 */
/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
uint8_t *usb_dev_cdc_getcfgdesc(uint16_t *length);
//void process_asynchdata_uart2usb(void *pdev);
static bool USB_RxFifo_Push(uint8_t *pu8Data, uint16_t u16Len);

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
usb_dev_class_func  class_cdc_cbk = {
    &usb_dev_cdc_init,
    &usb_dev_cdc_deinit,
    &usb_dev_cdc_setup,
    NULL,
    &usb_dev_cdc_ctrlep_rxready,
    &usb_dev_cdc_getcfgdesc,
    &usb_dev_cdc_sof,
    &usb_dev_cdc_datain,
    &usb_dev_cdc_dataout,
    NULL,
    NULL,
};

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
__USB_ALIGN_BEGIN static uint32_t  alternate_setting  = 0UL;
__USB_ALIGN_BEGIN static uint8_t usb_rx_buffer[MAX_CDC_PACKET_SIZE];
__USB_ALIGN_BEGIN static uint8_t CmdBuff[CDC_CMD_PACKET_SIZE];
static uint32_t cdcCmd  = 0xFFUL;
static uint32_t cdcLen  = 0UL;
/* ========== USB接收环形FIFO：缓存PC下发数据 ========== */
static uint8_t m_usb_rx_fifo[USB_RX_FIFO_SIZE];
static uint16_t m_usb_rx_wr = 0U;
static uint16_t m_usb_rx_rd = 0U;
/* 分包发送状态变量 */
static uint8_t  *m_pTxBufCur = NULL;   // 当前发送位置指针
static uint32_t  m_u32TxRemain = 0U;   // 剩余未发送字节数
static bool      m_usb_tx_idle = true; // 整体发送空闲标志（全部发完为true）

__USB_ALIGN_BEGIN static uint8_t usb_dev_cdc_cfgdesc[USB_CDC_CONFIG_DESC_SIZ]  = {
    0x09,
    USB_CFG_DESCRIPTOR_TYPE,
    USB_CDC_CONFIG_DESC_SIZ,
    0x00,
    0x02,
    0x01,
    0x00,
    0xC0,
    0x32,

    0x08,
    0x0B,
    0x00,
    0x02,
    0x02,
    0x02,
    0x01,
    0x04,

    0x09,
    USB_INTERFACE_DESCRIPTOR_TYPE,
    0x00,
    0x00,
    0x01,
    0x02,
    0x02,
    0x01,
    0x00,

    0x05,
    0x24,
    0x00,
    0x10,
    0x01,

    0x05,
    0x24,
    0x01,
    0x00,
    0x01,

    0x04,
    0x24,
    0x02,
    0x02,

    0x05,
    0x24,
    0x06,
    0x00,
    0x01,

    0x07,
    USB_ENDPOINT_DESCRIPTOR_TYPE,
    CDC_CMD_EP,
    0x03,
    LOBYTE(CDC_CMD_PACKET_SIZE),
    HIBYTE(CDC_CMD_PACKET_SIZE),
    0xFF,

    0x09,
    USB_INTERFACE_DESCRIPTOR_TYPE,
    0x01,
    0x00,
    0x02,
    0x0A,
    0x00,
    0x00,
    0x00,

    0x07,
    USB_ENDPOINT_DESCRIPTOR_TYPE,
    CDC_OUT_EP,
    0x02,
    LOBYTE(MAX_CDC_PACKET_SIZE),
    HIBYTE(MAX_CDC_PACKET_SIZE),
    0x00,

    0x07,
    USB_ENDPOINT_DESCRIPTOR_TYPE,
    CDC_IN_EP,
    0x02,
    LOBYTE(MAX_CDC_PACKET_SIZE),
    HIBYTE(MAX_CDC_PACKET_SIZE),
    0x00
} ;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  接收FIFO写入
 */
static bool USB_RxFifo_Push(uint8_t *pu8Data, uint16_t u16Len)
{
    uint16_t i;
    for(i = 0U; i < u16Len; i++)
    {
        uint16_t next_wr = (m_usb_rx_wr + 1U) % USB_RX_FIFO_SIZE;
        if(next_wr == m_usb_rx_rd)
        {
            return false; /* FIFO满，丢弃剩余数据 */
        }
        m_usb_rx_fifo[m_usb_rx_wr] = pu8Data[i];
        m_usb_rx_wr = next_wr;
    }
    return true;
}
/**
 * @brief  Initialize the CDC application
 * @param  [in] pdev        Device instance
 * @retval None
 */
void usb_dev_cdc_init(void *pdev)
{
    usb_opendevep(pdev, CDC_IN_EP, MAX_CDC_IN_PACKET_SIZE, EP_TYPE_BULK);
    usb_opendevep(pdev, CDC_OUT_EP, MAX_CDC_OUT_PACKET_SIZE, EP_TYPE_BULK);
    usb_opendevep(pdev, CDC_CMD_EP, CDC_CMD_PACKET_SIZE, EP_TYPE_INTR);
    vcp_init();
    usb_readytorx(pdev, CDC_OUT_EP, (uint8_t *)(usb_rx_buffer), MAX_CDC_OUT_PACKET_SIZE);
}

/**
 * @brief  Deinitialize the CDC application
 * @param  [in] pdev        Device instance
 * @retval None
 */
void usb_dev_cdc_deinit(void *pdev)
{
    usb_shutdevep(pdev, CDC_IN_EP);
    usb_shutdevep(pdev, CDC_OUT_EP);
    usb_shutdevep(pdev, CDC_CMD_EP);
    vcp_deinit();
}

/**
 * @brief  Handle the setup requests
 * @param  [in] pdev        Device instance
 * @param  [in] req         usb requests
 * @retval status
 */
uint8_t usb_dev_cdc_setup(void *pdev, USB_SETUP_REQ *req)
{
    uint16_t len = USB_CDC_DESC_SIZ;
    uint8_t  *pbuf = usb_dev_cdc_cfgdesc + 9;
    uint8_t  u8Res = USB_DEV_OK;

    switch (req->bmRequest & USB_REQ_TYPE_MASK) {
        case USB_REQ_TYPE_CLASS :
            if (req->wLength != 0U) {
                if ((req->bmRequest & 0x80U) != 0U) {
                    vcp_ctrlpare(req->bRequest, CmdBuff, req->wLength);
                    usb_ctrldatatx(pdev, CmdBuff, req->wLength);
                } else {
                    cdcCmd = req->bRequest;
                    cdcLen = req->wLength;
                    usb_ctrldatarx(pdev, CmdBuff, req->wLength);
                }
            } else {
                vcp_ctrlpare(req->bRequest, NULL, 0UL);
            }
            break;
        case USB_REQ_TYPE_STANDARD:
            switch (req->bRequest) {
                case USB_REQ_GET_DESCRIPTOR:
                    if ((req->wValue >> 8) == CDC_DESCRIPTOR_TYPE) {
                        pbuf = usb_dev_cdc_cfgdesc + 9U + (9U * USBD_ITF_MAX_NUM);
                        len  = LL_MIN(USB_CDC_DESC_SIZ, req->wLength);
                    }
                    usb_ctrldatatx(pdev, pbuf, len);
                    break;

                case USB_REQ_GET_INTERFACE :
                    usb_ctrldatatx(pdev, (uint8_t *)&alternate_setting, 1U);
                    break;

                case USB_REQ_SET_INTERFACE :
                    if ((uint8_t)(req->wValue) < USBD_ITF_MAX_NUM) {
                        alternate_setting = (uint8_t)(req->wValue);
                    } else {
                        usb_ctrlerr(pdev);
                    }
                    break;
                default:
                    break;
            }
            break;

        default:
            usb_ctrlerr(pdev);
            u8Res = USB_DEV_FAIL;
            break;
    }
    return u8Res;
}

/**
 * @brief  Data received on control endpoint
 * @param  [in] pdev        device device instance
 * @retval None
 */
void usb_dev_cdc_ctrlep_rxready(void *pdev)
{
    if (cdcCmd != NO_CMD) {
        vcp_ctrlpare(cdcCmd, CmdBuff, cdcLen);
        cdcCmd = NO_CMD;
    }
}

/**
 * @brief  Data sent on non-control IN endpoint
 * @param  [in] pdev        Device instance
 * @param  [in] epnum       endpoint index
 * @retval None
 */
void usb_dev_cdc_datain(void *pdev, uint8_t epnum)
{
    (void)pdev;

    /* 仅处理CDC数据IN端点的发送完成事件，忽略控制端点、命令端点 */
    if(epnum != (CDC_IN_EP & 0x7FU))
    {
        return;
    }

    if(m_u32TxRemain > 0U)
    {
        /* 还有剩余数据，自动发起下一包传输 */
        uint32_t chunk_len;
        chunk_len = (m_u32TxRemain >= MAX_CDC_IN_PACKET_SIZE) 
                    ? MAX_CDC_IN_PACKET_SIZE 
                    : m_u32TxRemain;

        usb_deveptx(&usb_dev, CDC_IN_EP, m_pTxBufCur, chunk_len);
        m_pTxBufCur += chunk_len;
        m_u32TxRemain -= chunk_len;
    }
    else
    {
        /* 全部数据发送完成，释放空闲标志 */
        m_usb_tx_idle = true;
        m_pTxBufCur = NULL;
    }
}

/**
 * @brief  Data received on non-control Out endpoint
 * @param  [in] pdev        device instance
 * @param  [in] epnum       endpoint index
 * @retval None
 */
void usb_dev_cdc_dataout(void *pdev, uint8_t epnum)
{
    uint16_t usb_rx_cnt;
    usb_core_instance *p_usb = (usb_core_instance *)pdev;

    usb_rx_cnt = p_usb->dev.out_ep[epnum].xfer_count;
    USB_RxFifo_Push(usb_rx_buffer, usb_rx_cnt);

    // 重新投递接收，持续等待下一包PC数据
    usb_readytorx(pdev, CDC_OUT_EP, usb_rx_buffer, MAX_CDC_OUT_PACKET_SIZE);
}

/**
 * @brief  Start Of Frame event management
 * @param  [in] pdev        Device instance
 * @retval status
 */
uint8_t usb_dev_cdc_sof(void *pdev)
{
    (void)pdev;
    // 删除原串口自动发送 process_asynchdata_uart2usb 调用
    return USB_DEV_OK;
}

/**
 * @brief  get the configuration descriptor
 * @param  [in] length          length of configuration descriptor in bytes
 * @retval the pointer to configuration descriptor buffer
 */
uint8_t *usb_dev_cdc_getcfgdesc(uint16_t *length)
{
    *length = (uint16_t)sizeof(usb_dev_cdc_cfgdesc);
    return usb_dev_cdc_cfgdesc;
}

/* ====================== 对外API接口，上层任务调用 ====================== */
/**
 * @brief  MCU主动发送数据到PC，支持大于64字节自动分包
 * @param  pu8Buf 数据首地址（必须保持有效直到发送完成）
 * @param  u32Len 总发送长度
 * @retval Ok=发送启动成功；Error=USB未连接/上一次发送未完成
 */
en_result_t CDC_SendData(uint8_t *pu8Buf, uint32_t u32Len)
{
    /* 1. 前置检查 */
    if(!m_usb_tx_idle)
    {
        return Error;
    }
    if((NULL == pu8Buf) || (0U == u32Len))
    {
        return Ok;
    }

    /* 2. 初始化分包状态 */
    m_pTxBufCur = pu8Buf;
    m_u32TxRemain = u32Len;
    m_usb_tx_idle = false;

    /* 3. 发送第一包 */
    uint32_t first_len;
    first_len = (u32Len >= MAX_CDC_IN_PACKET_SIZE) 
                ? MAX_CDC_IN_PACKET_SIZE 
                : u32Len;
    
    usb_deveptx(&usb_dev, CDC_IN_EP, m_pTxBufCur, first_len);
    m_pTxBufCur += first_len;
    m_u32TxRemain -= first_len;

    return Ok;
}
/**
 * @brief  查询发送是否空闲（全部数据发完）
 */
bool CDC_IsTxIdle(void)
{
    return m_usb_tx_idle;
}
/**
 * @brief  获取接收FIFO有效字节数
 */
uint16_t CDC_GetRxDataLen(void)
{
    if(m_usb_rx_wr >= m_usb_rx_rd)
    {
        return m_usb_rx_wr - m_usb_rx_rd;
    }
    else
    {
        return USB_RX_FIFO_SIZE - (m_usb_rx_rd - m_usb_rx_wr);
    }
}

/**
 * @brief  读取PC下发数据
 * @param  pu8Dst 输出缓存
 * @param  u16MaxLen 最大读取长度
 * @return 实际读到字节数
 */
uint16_t CDC_ReadRxData(uint8_t *pu8Dst, uint16_t u16MaxLen)
{
    uint16_t cnt = 0U;
    while((cnt < u16MaxLen) && (m_usb_rx_rd != m_usb_rx_wr))
    {
        pu8Dst[cnt++] = m_usb_rx_fifo[m_usb_rx_rd];
        m_usb_rx_rd = (m_usb_rx_rd + 1U) % USB_RX_FIFO_SIZE;
    }
    return cnt;
}

/**
 * @brief 清空接收缓冲区
 */
void CDC_ClearRxFifo(void)
{
    m_usb_rx_rd = m_usb_rx_wr;
}
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
