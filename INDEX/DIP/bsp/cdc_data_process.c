/**
 *******************************************************************************
 * @file  cdc_data_process.c
 * @brief Remove USART3 transparent transmission, only function stub reserved
 *******************************************************************************
 */
#include "cdc_data_process.h"

/**
 * @addtogroup USB_Dev_Cdc
 * @{
 */

/*******************************************************************************
 * Global function
 ******************************************************************************/
void vcp_init(void)
{
    /* 移除全部USART初始化 */
}

void vcp_deinit(void)
{
}

void vcp_ctrlpare(uint32_t Cmd, uint8_t *Buf, uint32_t Len)
{
    (void)Cmd;
    (void)Buf;
    (void)Len;
    /* CDC串口配置请求空处理，不再操作硬件串口 */
}

void vcp_txdata(void)
{
    /* 原串口接收存入缓存，不再使用 */
}

void vcp_rxdata(uint8_t *Buf, uint32_t Len)
{
    (void)Buf;
    (void)Len;
    /* 不再在这里转发USB数据到串口；接收逻辑迁移至class文件 */
}

/**
 * @}
 */
/**
 * @}
 */
/*******************************************************************************
 * EOF
 ******************************************************************************/
