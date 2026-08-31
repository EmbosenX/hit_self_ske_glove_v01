/**
 ******************************************************************************
 * @file    app_usart_task.c
 * @brief   串口通信任务，处理USART数据收发和协议解析
 ******************************************************************************
 */

#include "app_usart_task.h"
#include "usart.h"
#include "uart.h"
#include "main.h"
#include "app_sample_task.h"
#include "app_tac_config.h"
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#define  INSIDE		1

/******************************************************************************
 * 静态任务资源（仅本文件可见，静态分配）
 ******************************************************************************/
static StaticTask_t  xUsartTaskTcb;
static StackType_t   uxUsartTaskStack[USART_TASK_STACK_SIZE];
TaskHandle_t  xUsartTaskHandle = NULL;
/* 发送消息队列：缓存待发送帧 */
#define USART_BSP_MAX_FRAME_LEN (350U)
typedef struct {
    uint16_t u16Len;
    uint8_t  au8Data[USART_BSP_MAX_FRAME_LEN];
} stc_usart_tx_msg_t;
static stc_usart_tx_msg_t stcTxMsg={0};

/******************************************************************************
 * 内部函数声明
 ******************************************************************************/
static void AppTaskUsart(void *pvParameters);
static uint16_t usart_crc16(const uint8_t *data, uint16_t size);
#if(INSIDE==0)
static uint16_t finger_data_tx_frame(uint8_t AREA,uint8_t *pTxBuff);
#else
static uint16_t inside_data_tx_frame(uint8_t AREA,uint8_t *pTxBuff);
#endif

/******************************************************************************
 * 对外接口实现
 ******************************************************************************/

/**
 * @brief  初始化USART任务
 */
uint8_t APP_Usart_TaskCreate(void)
{
    /* 1. 硬件初始化 */
    Usart_Init();
		Uart_Init();

    /* 4. 创建静态任务 */
    xUsartTaskHandle = xTaskCreateStatic(
        AppTaskUsart,
        "UsartTask",
        USART_TASK_STACK_SIZE,
        NULL,
        USART_TASK_PRIORITY,
        uxUsartTaskStack,
        &xUsartTaskTcb
    );
    return 0U;
}

/******************************************************************************
 * 任务主体
 ******************************************************************************/

static void AppTaskUsart(void *pvParameters)
{
    uint16_t rx_len;
		static uint8_t rx_buf[350]={0};
		uint16_t data_len=0,crc1=0,crc2=0;
    (void)pvParameters;

		/* Start the transmission process */
		//Usart_SendDMA(aTxStartMessage, TXSTARTMESSAGESIZE, 100);
    for (;;) {
				/* 缓冲区为空时，阻塞等待新数据 */
			  BaseType_t ret = xSemaphoreTake(xUartRxNewDataSem, portMAX_DELAY);
				if (ret==pdTRUE)
				{
					rx_len = Uart_Read(rx_buf, sizeof(rx_buf));
					if (rx_len > 0)
					{
						crc1 = (rx_buf[rx_len-4]|(rx_buf[rx_len-3]<<8))&0XFFFF;
						if(rx_buf[2]==0x02&&rx_buf[3]==0x00)
						{
							data_len = (rx_buf[4]|(rx_buf[5]<<8))&0XFFFF;
							crc2 = usart_crc16(&rx_buf[6],data_len);
							if(crc2==crc1)
							{
								/* 小指 */
								memcpy(stcTxMsg.au8Data,rx_buf,rx_len);
								stcTxMsg.u16Len = inside_data_tx_frame(TAC_AREA_LITTLE_MCP, stcTxMsg.au8Data);
								Usart_SendDMA(stcTxMsg.au8Data, stcTxMsg.u16Len,10);
							}
						}
					}
				}
    }
}

static uint16_t usart_crc16(const uint8_t *data, uint16_t size)
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

#if(INSIDE==0)
static uint16_t finger_data_tx_frame(uint8_t AREA,uint8_t *pTxBuff)
{
		const tac_data_cfg_t* pTacData = GetTacDataCfg();
		uint16_t length=0, length_data=0;
	  uint16_t CRC16=0;
	
		switch(AREA)
		{
			case (TAC_AREA_THUMB_DIP+TAC_AREA_THUMB_MCP):
						pTxBuff[0] = 0X3C;
						pTxBuff[1] = 0X3C;
						pTxBuff[2] = 0X02;
						pTxBuff[3] = 0X00;
						length_data = 4+sizeof(pTacData->thumb_dip)+3+sizeof(pTacData->thumb_mcp);
						pTxBuff[4] = (length_data>>0)&0xff;
						pTxBuff[5] = (length_data>>8)&0xff;
						pTxBuff[6] = 0x12;
						pTxBuff[7] = 0X01;
						pTxBuff[8] = TAC_COL_THUMB_DIP_END - TAC_COL_THUMB_DIP_START + 1U;
						pTxBuff[9] = TAC_ROW_THUMB_DIP_END - TAC_ROW_THUMB_DIP_START + 1U;
						memcpy(&pTxBuff[10],pTacData->thumb_dip,sizeof(pTacData->thumb_dip));
						
						pTxBuff[10+sizeof(pTacData->thumb_dip)] = 0X02;
						pTxBuff[11+sizeof(pTacData->thumb_dip)] = TAC_COL_THUMB_MCP_END - TAC_COL_THUMB_MCP_START + 1U;
						pTxBuff[12+sizeof(pTacData->thumb_dip)] = TAC_ROW_THUMB_MCP_END - TAC_ROW_THUMB_MCP_START + 1U;
						memcpy(&pTxBuff[13+sizeof(pTacData->thumb_dip)],pTacData->thumb_mcp,sizeof(pTacData->thumb_mcp));
						
						CRC16 = usart_crc16(&pTxBuff[6],length_data);
						pTxBuff[13+sizeof(pTacData->thumb_dip)+sizeof(pTacData->thumb_mcp)] = (CRC16>>0)&0xff;
						pTxBuff[14+sizeof(pTacData->thumb_dip)+sizeof(pTacData->thumb_mcp)] = (CRC16>>8)&0xff;
						pTxBuff[15+sizeof(pTacData->thumb_dip)+sizeof(pTacData->thumb_mcp)] = 0x3E;
						pTxBuff[16+sizeof(pTacData->thumb_dip)+sizeof(pTacData->thumb_mcp)] = 0x3E;
						length = 17+sizeof(pTacData->thumb_dip)+sizeof(pTacData->thumb_mcp);
				break;
			case (TAC_AREA_INDEX_DIP+TAC_AREA_INDEX_PIP+TAC_AREA_INDEX_MCP):
						pTxBuff[0] = 0X3C;
						pTxBuff[1] = 0X3C;
						pTxBuff[2] = 0X02;
						pTxBuff[3] = 0X00;
						length_data = 4+sizeof(pTacData->index_dip)+3+sizeof(pTacData->index_pip)+3+sizeof(pTacData->index_mcp);
						pTxBuff[4] = (length_data>>0)&0xff;
						pTxBuff[5] = (length_data>>8)&0xff;
						pTxBuff[6] = 0x23;
						pTxBuff[7] = 0X01;
						pTxBuff[8] = TAC_COL_INDEX_DIP_END - TAC_COL_INDEX_DIP_START + 1U;
						pTxBuff[9] = TAC_ROW_INDEX_DIP_END - TAC_ROW_INDEX_DIP_START + 1U;
						memcpy(&pTxBuff[10],pTacData->index_dip,sizeof(pTacData->index_dip));

						pTxBuff[10+sizeof(pTacData->index_dip)] = 0X02;
						pTxBuff[11+sizeof(pTacData->index_dip)] = TAC_COL_INDEX_PIP_END - TAC_COL_INDEX_PIP_START + 1U;
						pTxBuff[12+sizeof(pTacData->index_dip)] = TAC_ROW_INDEX_PIP_END - TAC_ROW_INDEX_PIP_START + 1U;
						memcpy(&pTxBuff[13+sizeof(pTacData->index_dip)],pTacData->index_pip,sizeof(pTacData->index_pip));
						
						pTxBuff[13+sizeof(pTacData->index_dip)+sizeof(pTacData->index_pip)] = 0X03;
						pTxBuff[14+sizeof(pTacData->index_dip)+sizeof(pTacData->index_pip)] = TAC_COL_INDEX_MCP_END - TAC_COL_INDEX_MCP_START + 1U;
						pTxBuff[15+sizeof(pTacData->index_dip)+sizeof(pTacData->index_pip)] = TAC_ROW_INDEX_MCP_END - TAC_ROW_INDEX_MCP_START + 1U;
						memcpy(&pTxBuff[16+sizeof(pTacData->index_dip)+sizeof(pTacData->index_pip)],pTacData->index_mcp,sizeof(pTacData->index_mcp));

						CRC16 = usart_crc16(&pTxBuff[6],length_data);
						pTxBuff[16+sizeof(pTacData->index_dip)+sizeof(pTacData->index_pip)+sizeof(pTacData->index_mcp)] = (CRC16>>0)&0xff;
						pTxBuff[17+sizeof(pTacData->index_dip)+sizeof(pTacData->index_pip)+sizeof(pTacData->index_mcp)] = (CRC16>>8)&0xff;
						pTxBuff[18+sizeof(pTacData->index_dip)+sizeof(pTacData->index_pip)+sizeof(pTacData->index_mcp)] = 0x3E;
						pTxBuff[19+sizeof(pTacData->index_dip)+sizeof(pTacData->index_pip)+sizeof(pTacData->index_mcp)] = 0x3E;
						length = 20+sizeof(pTacData->index_dip)+sizeof(pTacData->index_pip)+sizeof(pTacData->index_mcp);
				break;
			case (TAC_AREA_MIDDLE_DIP+TAC_AREA_MIDDLE_PIP+TAC_AREA_MIDDLE_MCP):
						pTxBuff[0] = 0X3C;
						pTxBuff[1] = 0X3C;
						pTxBuff[2] = 0X02;
						pTxBuff[3] = 0X00;
						length_data = 4+sizeof(pTacData->middle_dip)+3+sizeof(pTacData->middle_pip)+3+sizeof(pTacData->middle_mcp);
						pTxBuff[4] = (length_data>>0)&0xff;
						pTxBuff[5] = (length_data>>8)&0xff;
						pTxBuff[6] = 0x33;
						pTxBuff[7] = 0X01;
						pTxBuff[8] = TAC_COL_MIDDLE_DIP_END - TAC_COL_MIDDLE_DIP_START + 1U;
						pTxBuff[9] = TAC_ROW_MIDDLE_DIP_END - TAC_ROW_MIDDLE_DIP_START + 1U;
						memcpy(&pTxBuff[10],pTacData->middle_dip,sizeof(pTacData->middle_dip));

						pTxBuff[10+sizeof(pTacData->middle_dip)] = 0X02;
						pTxBuff[11+sizeof(pTacData->middle_dip)] = TAC_COL_MIDDLE_PIP_END - TAC_COL_MIDDLE_PIP_START + 1U;
						pTxBuff[12+sizeof(pTacData->middle_dip)] = TAC_ROW_MIDDLE_PIP_END - TAC_ROW_MIDDLE_PIP_START + 1U;
						memcpy(&pTxBuff[13+sizeof(pTacData->middle_dip)],pTacData->middle_pip,sizeof(pTacData->middle_pip));
						
						pTxBuff[13+sizeof(pTacData->middle_dip)+sizeof(pTacData->middle_pip)] = 0X03;
						pTxBuff[14+sizeof(pTacData->middle_dip)+sizeof(pTacData->middle_pip)] = TAC_COL_MIDDLE_MCP_END - TAC_COL_MIDDLE_MCP_START + 1U;
						pTxBuff[15+sizeof(pTacData->middle_dip)+sizeof(pTacData->middle_pip)] = TAC_ROW_MIDDLE_MCP_END - TAC_ROW_MIDDLE_MCP_START + 1U;
						memcpy(&pTxBuff[16+sizeof(pTacData->middle_dip)+sizeof(pTacData->middle_pip)],pTacData->middle_mcp,sizeof(pTacData->middle_mcp));

						CRC16 = usart_crc16(&pTxBuff[6],length_data);
						pTxBuff[16+sizeof(pTacData->middle_dip)+sizeof(pTacData->middle_pip)+sizeof(pTacData->middle_mcp)] = (CRC16>>0)&0xff;
						pTxBuff[17+sizeof(pTacData->middle_dip)+sizeof(pTacData->middle_pip)+sizeof(pTacData->middle_mcp)] = (CRC16>>8)&0xff;
						pTxBuff[18+sizeof(pTacData->middle_dip)+sizeof(pTacData->middle_pip)+sizeof(pTacData->middle_mcp)] = 0x3E;
						pTxBuff[19+sizeof(pTacData->middle_dip)+sizeof(pTacData->middle_pip)+sizeof(pTacData->middle_mcp)] = 0x3E;
						length = 20+sizeof(pTacData->middle_dip)+sizeof(pTacData->middle_pip)+sizeof(pTacData->middle_mcp);
				break;
			case (TAC_AREA_RING_DIP+TAC_AREA_RING_PIP+TAC_AREA_RING_MCP):
						pTxBuff[0] = 0X3C;
						pTxBuff[1] = 0X3C;
						pTxBuff[2] = 0X02;
						pTxBuff[3] = 0X00;
						length_data = 4+sizeof(pTacData->ring_dip)+3+sizeof(pTacData->ring_pip)+3+sizeof(pTacData->ring_mcp);
						pTxBuff[4] = (length_data>>0)&0xff;
						pTxBuff[5] = (length_data>>8)&0xff;
						pTxBuff[6] = 0x43;
						pTxBuff[7] = 0X01;
						pTxBuff[8] = TAC_COL_RING_DIP_END - TAC_COL_RING_DIP_START + 1U;
						pTxBuff[9] = TAC_ROW_RING_DIP_END - TAC_ROW_RING_DIP_START + 1U;
						memcpy(&pTxBuff[10],pTacData->ring_dip,sizeof(pTacData->ring_dip));

						pTxBuff[10+sizeof(pTacData->ring_dip)] = 0X02;
						pTxBuff[11+sizeof(pTacData->ring_dip)] = TAC_COL_RING_PIP_END - TAC_COL_RING_PIP_START + 1U;
						pTxBuff[12+sizeof(pTacData->ring_dip)] = TAC_ROW_RING_PIP_END - TAC_ROW_RING_PIP_START + 1U;
						memcpy(&pTxBuff[13+sizeof(pTacData->ring_dip)],pTacData->ring_pip,sizeof(pTacData->ring_pip));
						
						pTxBuff[13+sizeof(pTacData->ring_dip)+sizeof(pTacData->ring_pip)] = 0X03;
						pTxBuff[14+sizeof(pTacData->ring_dip)+sizeof(pTacData->ring_pip)] = TAC_COL_RING_MCP_END - TAC_COL_RING_MCP_START + 1U;
						pTxBuff[15+sizeof(pTacData->ring_dip)+sizeof(pTacData->ring_pip)] = TAC_ROW_RING_MCP_END - TAC_ROW_RING_MCP_START + 1U;
						memcpy(&pTxBuff[16+sizeof(pTacData->ring_dip)+sizeof(pTacData->ring_pip)],pTacData->ring_mcp,sizeof(pTacData->ring_mcp));

						CRC16 = usart_crc16(&pTxBuff[6],length_data);
						pTxBuff[16+sizeof(pTacData->ring_dip)+sizeof(pTacData->ring_pip)+sizeof(pTacData->ring_mcp)] = (CRC16>>0)&0xff;
						pTxBuff[17+sizeof(pTacData->ring_dip)+sizeof(pTacData->ring_pip)+sizeof(pTacData->ring_mcp)] = (CRC16>>8)&0xff;
						pTxBuff[18+sizeof(pTacData->ring_dip)+sizeof(pTacData->ring_pip)+sizeof(pTacData->ring_mcp)] = 0x3E;
						pTxBuff[19+sizeof(pTacData->ring_dip)+sizeof(pTacData->ring_pip)+sizeof(pTacData->ring_mcp)] = 0x3E;
						length = 20+sizeof(pTacData->ring_dip)+sizeof(pTacData->ring_pip)+sizeof(pTacData->ring_mcp);
				break;
			case (TAC_AREA_LITTLE_DIP+TAC_AREA_LITTLE_PIP+TAC_AREA_LITTLE_MCP):
						pTxBuff[0] = 0X3C;
						pTxBuff[1] = 0X3C;
						pTxBuff[2] = 0X02;
						pTxBuff[3] = 0X00;
						length_data = 4+sizeof(pTacData->little_dip)+3+sizeof(pTacData->little_pip)+3+sizeof(pTacData->little_mcp);
						pTxBuff[4] = (length_data>>0)&0xff;
						pTxBuff[5] = (length_data>>8)&0xff;
						pTxBuff[6] = 0x53;
						pTxBuff[7] = 0X01;
						pTxBuff[8] = TAC_COL_LITTLE_DIP_END - TAC_COL_LITTLE_DIP_START + 1U;
						pTxBuff[9] = TAC_ROW_LITTLE_DIP_END - TAC_ROW_LITTLE_DIP_START + 1U;
						memcpy(&pTxBuff[10],pTacData->little_dip,sizeof(pTacData->little_dip));

						pTxBuff[10+sizeof(pTacData->little_dip)] = 0X02;
						pTxBuff[11+sizeof(pTacData->little_dip)] = TAC_COL_LITTLE_PIP_END - TAC_COL_LITTLE_PIP_START + 1U;
						pTxBuff[12+sizeof(pTacData->little_dip)] = TAC_ROW_LITTLE_PIP_END - TAC_ROW_LITTLE_PIP_START + 1U;
						memcpy(&pTxBuff[13+sizeof(pTacData->little_dip)],pTacData->little_pip,sizeof(pTacData->little_pip));
						
						pTxBuff[13+sizeof(pTacData->little_dip)+sizeof(pTacData->little_pip)] = 0X03;
						pTxBuff[14+sizeof(pTacData->little_dip)+sizeof(pTacData->little_pip)] = TAC_COL_LITTLE_MCP_END - TAC_COL_LITTLE_MCP_START + 1U;
						pTxBuff[15+sizeof(pTacData->little_dip)+sizeof(pTacData->little_pip)] = TAC_ROW_LITTLE_MCP_END - TAC_ROW_LITTLE_MCP_START + 1U;
						memcpy(&pTxBuff[16+sizeof(pTacData->little_dip)+sizeof(pTacData->little_pip)],pTacData->little_mcp,sizeof(pTacData->little_mcp));

						CRC16 = usart_crc16(&pTxBuff[6],length_data);
						pTxBuff[16+sizeof(pTacData->little_dip)+sizeof(pTacData->little_pip)+sizeof(pTacData->little_mcp)] = (CRC16>>0)&0xff;
						pTxBuff[17+sizeof(pTacData->little_dip)+sizeof(pTacData->little_pip)+sizeof(pTacData->little_mcp)] = (CRC16>>8)&0xff;
						pTxBuff[18+sizeof(pTacData->little_dip)+sizeof(pTacData->little_pip)+sizeof(pTacData->little_mcp)] = 0x3E;
						pTxBuff[19+sizeof(pTacData->little_dip)+sizeof(pTacData->little_pip)+sizeof(pTacData->little_mcp)] = 0x3E;
						length = 20+sizeof(pTacData->little_dip)+sizeof(pTacData->little_pip)+sizeof(pTacData->little_mcp);
				break;
			case (TAC_AREA_PALM1+TAC_AREA_PALM2):
						pTxBuff[0] = 0X3C;
						pTxBuff[1] = 0X3C;
						pTxBuff[2] = 0X02;
						pTxBuff[3] = 0X00;
						length_data = 4+sizeof(pTacData->palm1)+3+sizeof(pTacData->palm2);
						pTxBuff[4] = (length_data>>0)&0xff;
						pTxBuff[5] = (length_data>>8)&0xff;
						pTxBuff[6] = 0x62;
						pTxBuff[7] = 0X01;
						pTxBuff[8] = TAC_COL_PALM1_END - TAC_COL_PALM1_START + 1U;
						pTxBuff[9] = TAC_ROW_PALM1_END - TAC_ROW_PALM1_START + 1U;
						memcpy(&pTxBuff[10],pTacData->palm1,sizeof(pTacData->palm1));
			
						pTxBuff[10+sizeof(pTacData->palm1)] = 0X02;
						pTxBuff[11+sizeof(pTacData->palm1)] = TAC_COL_PALM2_END - TAC_COL_PALM2_START + 1U;
						pTxBuff[12+sizeof(pTacData->palm1)] = TAC_ROW_PALM2_END - TAC_ROW_PALM2_START + 1U;
						memcpy(&pTxBuff[13+sizeof(pTacData->palm1)],pTacData->palm2,sizeof(pTacData->palm2));
						
						CRC16 = usart_crc16(&pTxBuff[6],length_data);
						pTxBuff[13+sizeof(pTacData->palm1)+sizeof(pTacData->palm2)] = (CRC16>>0)&0xff;
						pTxBuff[14+sizeof(pTacData->palm1)+sizeof(pTacData->palm2)] = (CRC16>>8)&0xff;
						pTxBuff[15+sizeof(pTacData->palm1)+sizeof(pTacData->palm2)] = 0x3E;
						pTxBuff[16+sizeof(pTacData->palm1)+sizeof(pTacData->palm2)] = 0x3E;
						length = 17+sizeof(pTacData->palm1)+sizeof(pTacData->palm2);
				break;
			default:break;
		}
		return length;
}
#else
static uint16_t inside_data_tx_frame(uint8_t AREA,uint8_t *pTxBuff)
{
		const tac_data_cfg_t* pTacData = GetTacDataCfg();
		uint16_t length=0, length_data=0;
	  uint16_t CRC16=0;
	
		switch(AREA)
		{
				case TAC_AREA_THUMB_DIP:break;
				case TAC_AREA_THUMB_MCP:break;
				case TAC_AREA_INDEX_DIP:break;
				case TAC_AREA_INDEX_PIP:break;
				case TAC_AREA_INDEX_MCP:break;
				case TAC_AREA_MIDDLE_DIP:break;
				case TAC_AREA_MIDDLE_PIP:break;
				case TAC_AREA_MIDDLE_MCP:break;
				case TAC_AREA_RING_DIP:break;
				case TAC_AREA_RING_PIP:break;
				case TAC_AREA_RING_MCP:break;
				case TAC_AREA_LITTLE_DIP:break;
				case TAC_AREA_LITTLE_PIP:break;
				case TAC_AREA_LITTLE_MCP:
						length_data = 4+sizeof(little_dip)+3+sizeof(pTacData->little_pip)+3+sizeof(pTacData->little_mcp);
						pTxBuff[4] = (length_data>>0)&0xff;
						pTxBuff[5] = (length_data>>8)&0xff;
						pTxBuff[6] = 0x33;
						pTxBuff[13+sizeof(little_dip)+sizeof(pTacData->little_pip)] = 0X03;
						pTxBuff[14+sizeof(little_dip)+sizeof(pTacData->little_pip)] = TAC_COL_LITTLE_MCP_END - TAC_COL_LITTLE_MCP_START + 1U;
						pTxBuff[15+sizeof(little_dip)+sizeof(pTacData->little_pip)] = TAC_ROW_LITTLE_MCP_END - TAC_ROW_LITTLE_MCP_START + 1U;
						memcpy(&pTxBuff[16+sizeof(little_dip)+sizeof(pTacData->little_pip)],pTacData->little_mcp,sizeof(pTacData->little_mcp));
						CRC16 = usart_crc16(&pTxBuff[6],length_data);
						pTxBuff[16+sizeof(little_dip)+sizeof(pTacData->little_pip)+sizeof(pTacData->little_mcp)] = (CRC16>>0)&0xff;
						pTxBuff[17+sizeof(little_dip)+sizeof(pTacData->little_pip)+sizeof(pTacData->little_mcp)] = (CRC16>>8)&0xff;
						pTxBuff[18+sizeof(little_dip)+sizeof(pTacData->little_pip)+sizeof(pTacData->little_mcp)] = 0x3E;
						pTxBuff[19+sizeof(little_dip)+sizeof(pTacData->little_pip)+sizeof(pTacData->little_mcp)] = 0x3E;
						length = 20+sizeof(little_dip)+sizeof(pTacData->little_pip)+sizeof(pTacData->little_mcp);
						break;
				case TAC_AREA_PALM1:break;
				case TAC_AREA_PALM2:break;
				default:break;
		}
		return length;
}
#endif


