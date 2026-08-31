/**
 ******************************************************************************
 * @file    app_tac_config.h
 * @brief   触觉传感器配置头文件
 ******************************************************************************
 */

#ifndef __APP_TAC_CONFIG_H__
#define __APP_TAC_CONFIG_H__

#include <stdint.h>
#include "py32f0xx_hal.h"
#include "main.h"

#define 	DATA_FRAME_BYTE_NUM  0

/******************************************************************************
 * 手型点位抽象 - 行列范围映射
 * 行分组：远节(DIP)、中节(PIP)、近节(MCP)、掌心(Palm)
 * 列分组：拇指、食指、中指、无名指、小指
 ******************************************************************************/
/* 行号分段定义 */
#define TAC_ROW_THUMB_DIP_START (0U)		/* 大拇指远节指节 - 起始行 */
#define TAC_ROW_THUMB_DIP_END   (0U)		/* 大拇指远节指节 - 结束行 */
#define TAC_ROW_THUMB_MCP_START (0U)		/* 大拇指近节指节 - 起始行 */
#define TAC_ROW_THUMB_MCP_END   (0U)		/* 大拇指近节指节 - 结束行 */

//原理图已确定
#define TAC_ROW_INDEX_DIP_START (0U)		/* 食指远节指节 - 起始行 */
#define TAC_ROW_INDEX_DIP_END   (0U)		/* 食指远节指节 - 结束行 */
#define TAC_ROW_INDEX_PIP_START (0U)		/* 食指中节指节 - 起始行 */
#define TAC_ROW_INDEX_PIP_END   (0U)		/* 食指中节指节 - 结束行 */
#define TAC_ROW_INDEX_MCP_START (0U)		/* 食指近节指节 - 起始行 */
#define TAC_ROW_INDEX_MCP_END   (0U)		/* 食指近节指节 - 结束行 */

#define TAC_ROW_MIDDLE_DIP_START (0U)		/* 中指远节指节 - 起始行 */
#define TAC_ROW_MIDDLE_DIP_END   (0U)		/* 中指远节指节 - 结束行 */
#define TAC_ROW_MIDDLE_PIP_START (0U)		/* 中指中节指节 - 起始行 */
#define TAC_ROW_MIDDLE_PIP_END   (0U)		/* 中指中节指节 - 结束行 */
#define TAC_ROW_MIDDLE_MCP_START (0U)		/* 中指近节指节 - 起始行 */
#define TAC_ROW_MIDDLE_MCP_END   (0U)		/* 中指近节指节 - 结束行 */

#define TAC_ROW_RING_DIP_START (0U)		/* 无名指远节指节 - 起始行 */
#define TAC_ROW_RING_DIP_END   (0U)		/* 无名指远节指节 - 结束行 */
#define TAC_ROW_RING_PIP_START (0U)		/* 无名指中节指节 - 起始行 */
#define TAC_ROW_RING_PIP_END   (0U)		/* 无名指中节指节 - 结束行 */
#define TAC_ROW_RING_MCP_START (0U)		/* 无名指近节指节 - 起始行 */
#define TAC_ROW_RING_MCP_END   (0U)		/* 无名指近节指节 - 结束行 */

#define TAC_ROW_LITTLE_DIP_START (0U)		/* 小指远节指节 - 起始行 */
#define TAC_ROW_LITTLE_DIP_END   (13U)		/* 小指远节指节 - 结束行 */
#define TAC_ROW_LITTLE_PIP_START (0U)		/* 小指中节指节 - 起始行 */
#define TAC_ROW_LITTLE_PIP_END   (1U)		/* 小指中节指节 - 结束行 */
#define TAC_ROW_LITTLE_MCP_START (0U)		/* 小指近节指节 - 起始行 */
#define TAC_ROW_LITTLE_MCP_END   (0U)		/* 小指近节指节 - 结束行 */

#define TAC_ROW_PALM1_START    	(0U)		/* 掌心1 - 起始行 */
#define TAC_ROW_PALM1_END      	(0U)		/* 掌心1 - 结束行 */

#define TAC_ROW_PALM2_START    	(0U)		/* 掌心2 - 起始行 */
#define TAC_ROW_PALM2_END      	(0U)		/* 掌心2 - 结束行 */
/* 列号分段定义：映射变量成员初始化编号 static const stc_y_pin_map_t m_stYPinMap[] */
#define TAC_COL_THUMB_DIP_START     (0U)
#define TAC_COL_THUMB_DIP_END       (0U)
#define TAC_COL_THUMB_MCP_START     (0U)
#define TAC_COL_THUMB_MCP_END       (0U)

#define TAC_COL_INDEX_DIP_START     (0U)
#define TAC_COL_INDEX_DIP_END       (0U)
#define TAC_COL_INDEX_PIP_START     (0U)
#define TAC_COL_INDEX_PIP_END       (0U)
#define TAC_COL_INDEX_MCP_START     (0U)
#define TAC_COL_INDEX_MCP_END       (0U)

#define TAC_COL_MIDDLE_DIP_START     (0U)
#define TAC_COL_MIDDLE_DIP_END       (0U)
#define TAC_COL_MIDDLE_PIP_START     (0U)
#define TAC_COL_MIDDLE_PIP_END       (0U)
#define TAC_COL_MIDDLE_MCP_START     (0U)
#define TAC_COL_MIDDLE_MCP_END       (0U)

#define TAC_COL_RING_DIP_START     (0U)
#define TAC_COL_RING_DIP_END       (0U)
#define TAC_COL_RING_PIP_START     (0U)
#define TAC_COL_RING_PIP_END       (0U)
#define TAC_COL_RING_MCP_START     (0U)
#define TAC_COL_RING_MCP_END       (0U)

#define TAC_COL_LITTLE_DIP_START     (0U)
#define TAC_COL_LITTLE_DIP_END       (19U)
#define TAC_COL_LITTLE_PIP_START     (0U)
#define TAC_COL_LITTLE_PIP_END       (7U)
#define TAC_COL_LITTLE_MCP_START     (0U)
#define TAC_COL_LITTLE_MCP_END       (0U)

#define TAC_COL_PALM1_START    	(0U)
#define TAC_COL_PALM1_END      	(0U)

#define TAC_COL_PALM2_START    	(0U)
#define TAC_COL_PALM2_END      	(0U)
 
/* 触觉区域枚举 */
typedef enum {
    TAC_AREA_THUMB_DIP=0,        /* 大拇指 - 远节 */
		TAC_AREA_THUMB_MCP,        /* 大拇指 - 近节 */
	
		TAC_AREA_INDEX_DIP,        /* 食指 - 远节 */
    TAC_AREA_INDEX_PIP=3,        /* 食指 - 中节 */
    TAC_AREA_INDEX_MCP,        /* 食指 - 近节 */
	
		TAC_AREA_MIDDLE_DIP,        /* 中指 - 远节 */
    TAC_AREA_MIDDLE_PIP=6,       /* 中指 - 中节 */
    TAC_AREA_MIDDLE_MCP,       /* 中指 - 近节 */

		TAC_AREA_RING_DIP,        /* 无名指 - 远节 */
    TAC_AREA_RING_PIP=9,         /* 无名指 - 中节 */
    TAC_AREA_RING_MCP,         /* 无名指 - 近节 */
	
		TAC_AREA_LITTLE_DIP,        /* 小指 - 远节 */
    TAC_AREA_LITTLE_PIP=12,       /* 小指 - 中节 */
    TAC_AREA_LITTLE_MCP,       /* 小指 - 近节 */
	
    TAC_AREA_PALM1=14,             /* 掌心1 */
		TAC_AREA_PALM2,             /* 掌心2 */
    TAC_AREA_MAX
} tac_area_t;

/* 区域范围结构体 */
typedef struct {
    uint8_t row_start;     /* 区域起始行 */
    uint8_t row_end;       /* 区域结束行 */
    uint8_t col_start;     /* 区域起始列 */
    uint8_t col_end;       /* 区域结束列 */
    uint16_t point_cnt;    /* 区域内传感点总数 */
} tac_area_range_t;

#pragma pack(push, 1)   // 保存原有对齐设置，设置1字节对齐
//目标																		计算方式																说明
//单行总字节数（行大小）									sizeof(palm[0])													第 0 行是一个完整的一维数组，sizeof 返回整行的总字节数
//总行数																	sizeof(palm) / sizeof(palm[0])					数组总字节数 ÷ 单行字节数 = 行数
//总列数（每行元素数）										sizeof(palm[0]) / sizeof(palm[0][0])		单行字节数 ÷ 单个元素字节数 = 每行元素个数
//单个元素字节数													sizeof(palm[0][0])											数组单个元素的大小
typedef struct{
#if(DATA_FRAME_BYTE_NUM)
	uint16_t thumb_dip[TAC_ROW_THUMB_DIP_END - TAC_ROW_THUMB_DIP_START + 1U][TAC_COL_THUMB_DIP_END - TAC_COL_THUMB_DIP_START + 1U];//大拇指fpc型指尖
	uint16_t thumb_mcp[TAC_ROW_THUMB_MCP_END - TAC_ROW_THUMB_MCP_START + 1U][TAC_COL_THUMB_MCP_END - TAC_COL_THUMB_MCP_START + 1U];
	uint16_t index_dip[TAC_ROW_INDEX_DIP_END - TAC_ROW_INDEX_DIP_START + 1U][TAC_COL_INDEX_DIP_END - TAC_COL_INDEX_DIP_START + 1U];//食指fpc型指尖
	uint16_t index_pip[TAC_ROW_INDEX_PIP_END - TAC_ROW_INDEX_PIP_START + 1U][TAC_COL_INDEX_PIP_END - TAC_COL_INDEX_PIP_START + 1U];
	uint16_t index_mcp[TAC_ROW_INDEX_MCP_END - TAC_ROW_INDEX_MCP_START + 1U][TAC_COL_INDEX_MCP_END - TAC_COL_INDEX_MCP_START + 1U];
	uint16_t middle_dip[TAC_ROW_MIDDLE_DIP_END - TAC_ROW_MIDDLE_DIP_START + 1U][TAC_COL_MIDDLE_DIP_END - TAC_COL_MIDDLE_DIP_START + 1U];//中指fpc型指尖
	uint16_t middle_pip[TAC_ROW_MIDDLE_PIP_END - TAC_ROW_MIDDLE_PIP_START + 1U][TAC_COL_MIDDLE_PIP_END - TAC_COL_MIDDLE_PIP_START + 1U];
	uint16_t middle_mcp[TAC_ROW_MIDDLE_MCP_END - TAC_ROW_MIDDLE_MCP_START + 1U][TAC_COL_MIDDLE_MCP_END - TAC_COL_MIDDLE_MCP_START + 1U];
	uint16_t ring_dip[TAC_ROW_RING_DIP_END - TAC_ROW_RING_DIP_START + 1U][TAC_COL_RING_DIP_END - TAC_COL_RING_DIP_START + 1U];//无名指fpc型指尖
	uint16_t ring_pip[TAC_ROW_RING_PIP_END - TAC_ROW_RING_PIP_START + 1U][TAC_COL_RING_PIP_END - TAC_COL_RING_PIP_START + 1U];
	uint16_t ring_mcp[TAC_ROW_RING_MCP_END - TAC_ROW_RING_MCP_START + 1U][TAC_COL_RING_MCP_END - TAC_COL_RING_MCP_START + 1U];
	uint16_t little_dip[TAC_ROW_LITTLE_DIP_END - TAC_ROW_LITTLE_DIP_START + 1U][TAC_COL_LITTLE_DIP_END - TAC_COL_LITTLE_DIP_START + 1U];//小拇指fpc型指尖
	uint16_t little_pip[TAC_ROW_LITTLE_PIP_END - TAC_ROW_LITTLE_PIP_START + 1U][TAC_COL_LITTLE_PIP_END - TAC_COL_LITTLE_PIP_START + 1U];
	uint16_t little_mcp[TAC_ROW_LITTLE_MCP_END - TAC_ROW_LITTLE_MCP_START + 1U][TAC_COL_LITTLE_MCP_END - TAC_COL_LITTLE_MCP_START + 1U];
	uint16_t palm1[TAC_ROW_PALM1_END - TAC_ROW_PALM1_START + 1U][TAC_COL_PALM1_END - TAC_COL_PALM1_START + 1U];
	uint16_t palm2[TAC_ROW_PALM2_END - TAC_ROW_PALM2_START + 1U][TAC_COL_PALM2_END - TAC_COL_PALM2_START + 1U];
#else
//	uint8_t thumb_dip[TAC_ROW_THUMB_DIP_END - TAC_ROW_THUMB_DIP_START + 1U][TAC_COL_THUMB_DIP_END - TAC_COL_THUMB_DIP_START + 1U];//大拇指fpc型指尖
//	uint8_t thumb_mcp[TAC_ROW_THUMB_MCP_END - TAC_ROW_THUMB_MCP_START + 1U][TAC_COL_THUMB_MCP_END - TAC_COL_THUMB_MCP_START + 1U];
//	uint8_t index_dip[TAC_ROW_INDEX_DIP_END - TAC_ROW_INDEX_DIP_START + 1U][TAC_COL_INDEX_DIP_END - TAC_COL_INDEX_DIP_START + 1U];//食指fpc型指尖
//	uint8_t index_pip[TAC_ROW_INDEX_PIP_END - TAC_ROW_INDEX_PIP_START + 1U][TAC_COL_INDEX_PIP_END - TAC_COL_INDEX_PIP_START + 1U];
//	uint8_t index_mcp[TAC_ROW_INDEX_MCP_END - TAC_ROW_INDEX_MCP_START + 1U][TAC_COL_INDEX_MCP_END - TAC_COL_INDEX_MCP_START + 1U];
//	uint8_t middle_dip[TAC_ROW_MIDDLE_DIP_END - TAC_ROW_MIDDLE_DIP_START + 1U][TAC_COL_MIDDLE_DIP_END - TAC_COL_MIDDLE_DIP_START + 1U];//中指fpc型指尖
//	uint8_t middle_pip[TAC_ROW_MIDDLE_PIP_END - TAC_ROW_MIDDLE_PIP_START + 1U][TAC_COL_MIDDLE_PIP_END - TAC_COL_MIDDLE_PIP_START + 1U];
//	uint8_t middle_mcp[TAC_ROW_MIDDLE_MCP_END - TAC_ROW_MIDDLE_MCP_START + 1U][TAC_COL_MIDDLE_MCP_END - TAC_COL_MIDDLE_MCP_START + 1U];
//	uint8_t ring_dip[TAC_ROW_RING_DIP_END - TAC_ROW_RING_DIP_START + 1U][TAC_COL_RING_DIP_END - TAC_COL_RING_DIP_START + 1U];//无名指fpc型指尖
//	uint8_t ring_pip[TAC_ROW_RING_PIP_END - TAC_ROW_RING_PIP_START + 1U][TAC_COL_RING_PIP_END - TAC_COL_RING_PIP_START + 1U];
//	uint8_t ring_mcp[TAC_ROW_RING_MCP_END - TAC_ROW_RING_MCP_START + 1U][TAC_COL_RING_MCP_END - TAC_COL_RING_MCP_START + 1U];
//	uint8_t little_dip[TAC_ROW_LITTLE_DIP_END - TAC_ROW_LITTLE_DIP_START + 1U][TAC_COL_LITTLE_DIP_END - TAC_COL_LITTLE_DIP_START + 1U];//小拇指fpc型指尖
	uint8_t little_pip[TAC_ROW_LITTLE_PIP_END - TAC_ROW_LITTLE_PIP_START + 1U][TAC_COL_LITTLE_PIP_END - TAC_COL_LITTLE_PIP_START + 1U];
	uint8_t little_mcp[TAC_ROW_LITTLE_MCP_END - TAC_ROW_LITTLE_MCP_START + 1U][TAC_COL_LITTLE_MCP_END - TAC_COL_LITTLE_MCP_START + 1U];
//	uint8_t palm1[TAC_ROW_PALM1_END - TAC_ROW_PALM1_START + 1U][TAC_COL_PALM1_END - TAC_COL_PALM1_START + 1U];
//	uint8_t palm2[TAC_ROW_PALM2_END - TAC_ROW_PALM2_START + 1U][TAC_COL_PALM2_END - TAC_COL_PALM2_START + 1U];
#endif
}tac_data_cfg_t;
#pragma pack(pop)       // 恢复原先对齐方式

extern const tac_area_range_t TacAreaRange[TAC_AREA_MAX];
extern const uint8_t little_dip[(TAC_ROW_LITTLE_DIP_END - TAC_ROW_LITTLE_DIP_START + 1U)][(TAC_COL_LITTLE_DIP_END - TAC_COL_LITTLE_DIP_START + 1U)];
tac_data_cfg_t* GetTacDataCfg(void);
tac_data_cfg_t* GetTacCalibData(void);
const tac_data_cfg_t* GetTacMaskData(void);
float ad_to_weight(float ad_val);

#endif /* __APP_TAC_CONFIG_H__ */


