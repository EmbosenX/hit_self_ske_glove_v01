/**
 ******************************************************************************
 * @file    app_tac_config.c
 * @brief   触觉传感器配置模块，管理标定参数和通道映射
 ******************************************************************************
 */

#include "app_tac_config.h"

// 标定点数量
#define CALIB_POINT_NUM     6

static tac_data_cfg_t tac_data_cfg={0};
static tac_data_cfg_t tac_calib_data={0};
static const tac_data_cfg_t tac_mask_data = 
{
		.little_dip = 
    {
        { 0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0 },
        { 0,0,0,0,1,0,0,0,1,1,0,1,0,0,0,0 },
				{ 0,0,0,0,1,0,0,0,1,1,0,1,0,0,0,0 },
				{ 0,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0 },
				{ 0,0,0,0,1,0,0,0,1,1,0,1,0,0,0,0 },
				{ 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0 },
				{ 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0 },
				{ 1,1,1,1,0,0,0,0,1,0,0,0,1,1,1,1 },
				{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
				{ 0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0 },
    },
};

/************************
 * 标定数据表
 * calib_ad：AD平均值（按升序排列）
 * calib_weight：对应克重，单位g
 * 两组数组下标一一对应
 ************************/
const float calib_ad[CALIB_POINT_NUM] = {
    15.5f,
    29.0f,
    43.5f,
    51.857143f,
    71.142857f,
    92.428571f
};

const float calib_weight[CALIB_POINT_NUM] = {
    40.0f,
    540.0f,
    1040.0f,
    1540.0f,
    2040.0f,
    2540.0f
};

/* 全局区域范围表 - 可直接通过枚举索引 */
const tac_area_range_t TacAreaRange[TAC_AREA_MAX] = 
{
    /* 大拇指：远节+近节 */
    [TAC_AREA_THUMB_DIP] = {
        .row_start = TAC_ROW_THUMB_DIP_START,
        .row_end   = TAC_ROW_THUMB_DIP_END,
        .col_start = TAC_COL_THUMB_DIP_START,
        .col_end   = TAC_COL_THUMB_DIP_END,
        .point_cnt = (TAC_ROW_THUMB_DIP_END - TAC_ROW_THUMB_DIP_START + 1U) *
                     (TAC_COL_THUMB_DIP_END - TAC_COL_THUMB_DIP_START + 1U)
    },
    [TAC_AREA_THUMB_MCP] = {
        .row_start = TAC_ROW_THUMB_MCP_START,
        .row_end   = TAC_ROW_THUMB_MCP_END,
        .col_start = TAC_COL_THUMB_MCP_START,
        .col_end   = TAC_COL_THUMB_MCP_END,
        .point_cnt = (TAC_ROW_THUMB_MCP_END - TAC_ROW_THUMB_MCP_START + 1U) *
                     (TAC_COL_THUMB_MCP_END - TAC_COL_THUMB_MCP_START + 1U)
    },

    /* 食指：远节+中节+近节 */
		[TAC_AREA_INDEX_DIP] = {
        .row_start = TAC_ROW_INDEX_DIP_START,
        .row_end   = TAC_ROW_INDEX_DIP_END,
        .col_start = TAC_COL_INDEX_DIP_START,
        .col_end   = TAC_COL_INDEX_DIP_END,
        .point_cnt = (TAC_ROW_INDEX_DIP_END - TAC_ROW_INDEX_DIP_START + 1U) *
                     (TAC_COL_INDEX_DIP_END - TAC_COL_INDEX_DIP_START + 1U)
    },
    [TAC_AREA_INDEX_PIP] = {
        .row_start = TAC_ROW_INDEX_PIP_START,
        .row_end   = TAC_ROW_INDEX_PIP_END,
        .col_start = TAC_COL_INDEX_PIP_START,
        .col_end   = TAC_COL_INDEX_PIP_END,
        .point_cnt = (TAC_ROW_INDEX_PIP_END - TAC_ROW_INDEX_PIP_START + 1U) *
                     (TAC_COL_INDEX_PIP_END - TAC_COL_INDEX_PIP_START + 1U)
    },
    [TAC_AREA_INDEX_MCP] = {
        .row_start = TAC_ROW_INDEX_MCP_START,
        .row_end   = TAC_ROW_INDEX_MCP_END,
        .col_start = TAC_COL_INDEX_MCP_START,
        .col_end   = TAC_COL_INDEX_MCP_END,
        .point_cnt = (TAC_ROW_INDEX_MCP_END - TAC_ROW_INDEX_MCP_START + 1U) *
                     (TAC_COL_INDEX_MCP_END - TAC_COL_INDEX_MCP_START + 1U)
    },

    /* 中指：远节+中节+近节 */
		[TAC_AREA_MIDDLE_DIP] = {
        .row_start = TAC_ROW_MIDDLE_DIP_START,
        .row_end   = TAC_ROW_MIDDLE_DIP_END,
        .col_start = TAC_COL_MIDDLE_DIP_START,
        .col_end   = TAC_COL_MIDDLE_DIP_END,
        .point_cnt = (TAC_ROW_MIDDLE_DIP_END - TAC_ROW_MIDDLE_DIP_START + 1U) *
                     (TAC_COL_MIDDLE_DIP_END - TAC_COL_MIDDLE_DIP_START + 1U)
    },
    [TAC_AREA_MIDDLE_PIP] = {
        .row_start = TAC_ROW_MIDDLE_PIP_START,
        .row_end   = TAC_ROW_MIDDLE_PIP_END,
        .col_start = TAC_COL_MIDDLE_PIP_START,
        .col_end   = TAC_COL_MIDDLE_PIP_END,
        .point_cnt = (TAC_ROW_MIDDLE_PIP_END - TAC_ROW_MIDDLE_PIP_START + 1U) *
                     (TAC_COL_MIDDLE_PIP_END - TAC_COL_MIDDLE_PIP_START + 1U)
    },
    [TAC_AREA_MIDDLE_MCP] = {
        .row_start = TAC_ROW_MIDDLE_MCP_START,
        .row_end   = TAC_ROW_MIDDLE_MCP_END,
        .col_start = TAC_COL_MIDDLE_MCP_START,
        .col_end   = TAC_COL_MIDDLE_MCP_END,
        .point_cnt = (TAC_ROW_MIDDLE_MCP_END - TAC_ROW_MIDDLE_MCP_START + 1U) *
                     (TAC_COL_MIDDLE_MCP_END - TAC_COL_MIDDLE_MCP_START + 1U)
    },

    /* 无名指：远节+中节+近节 */
		[TAC_AREA_RING_DIP] = {
        .row_start = TAC_ROW_RING_DIP_START,
        .row_end   = TAC_ROW_RING_DIP_END,
        .col_start = TAC_COL_RING_DIP_START,
        .col_end   = TAC_COL_RING_DIP_END,
        .point_cnt = (TAC_ROW_RING_DIP_END - TAC_ROW_RING_DIP_START + 1U) *
                     (TAC_COL_RING_DIP_END - TAC_COL_RING_DIP_START + 1U)
    },
    [TAC_AREA_RING_PIP] = {
        .row_start = TAC_ROW_RING_PIP_START,
        .row_end   = TAC_ROW_RING_PIP_END,
        .col_start = TAC_COL_RING_PIP_START,
        .col_end   = TAC_COL_RING_PIP_END,
        .point_cnt = (TAC_ROW_RING_PIP_END - TAC_ROW_RING_PIP_START + 1U) *
                     (TAC_COL_RING_PIP_END - TAC_COL_RING_PIP_START + 1U)
    },
    [TAC_AREA_RING_MCP] = {
        .row_start = TAC_ROW_RING_MCP_START,
        .row_end   = TAC_ROW_RING_MCP_END,
        .col_start = TAC_COL_RING_MCP_START,
        .col_end   = TAC_COL_RING_MCP_END,
        .point_cnt = (TAC_ROW_RING_MCP_END - TAC_ROW_RING_MCP_START + 1U) *
                     (TAC_COL_RING_MCP_END - TAC_COL_RING_MCP_START + 1U)
    },

    /* 小指：远节+中节+近节 */
		[TAC_AREA_LITTLE_DIP] = {
        .row_start = TAC_ROW_LITTLE_DIP_START,
        .row_end   = TAC_ROW_LITTLE_DIP_END,
        .col_start = TAC_COL_LITTLE_DIP_START,
        .col_end   = TAC_COL_LITTLE_DIP_END,
        .point_cnt = (TAC_ROW_LITTLE_DIP_END - TAC_ROW_LITTLE_DIP_START + 1U) *
                     (TAC_COL_LITTLE_DIP_END - TAC_COL_LITTLE_DIP_START + 1U)
    },
    [TAC_AREA_LITTLE_PIP] = {
        .row_start = TAC_ROW_LITTLE_PIP_START,
        .row_end   = TAC_ROW_LITTLE_PIP_END,
        .col_start = TAC_COL_LITTLE_PIP_START,
        .col_end   = TAC_COL_LITTLE_PIP_END,
        .point_cnt = (TAC_ROW_LITTLE_PIP_END - TAC_ROW_LITTLE_PIP_START + 1U) *
                     (TAC_COL_LITTLE_PIP_END - TAC_COL_LITTLE_PIP_START + 1U)
    },
    [TAC_AREA_LITTLE_MCP] = {
        .row_start = TAC_ROW_LITTLE_MCP_START,
        .row_end   = TAC_ROW_LITTLE_MCP_END,
        .col_start = TAC_COL_LITTLE_MCP_START,
        .col_end   = TAC_COL_LITTLE_MCP_END,
        .point_cnt = (TAC_ROW_LITTLE_MCP_END - TAC_ROW_LITTLE_MCP_START + 1U) *
                     (TAC_COL_LITTLE_MCP_END - TAC_COL_LITTLE_MCP_START + 1U)
    },

    /* 掌心：全列覆盖 */
    [TAC_AREA_PALM1] = {
        .row_start = TAC_ROW_PALM1_START,
        .row_end   = TAC_ROW_PALM1_END,
        .col_start = TAC_COL_PALM1_START,
        .col_end   = TAC_COL_PALM1_END,
        .point_cnt = (TAC_ROW_PALM1_END - TAC_ROW_PALM1_START + 1U) * 
											(TAC_COL_PALM1_END - TAC_COL_PALM1_START + 1U)
    },
    [TAC_AREA_PALM2] = {
        .row_start = TAC_ROW_PALM2_START,
        .row_end   = TAC_ROW_PALM2_END,
        .col_start = TAC_COL_PALM2_START,
        .col_end   = TAC_COL_PALM2_END,
        .point_cnt = (TAC_ROW_PALM2_END - TAC_ROW_PALM2_START + 1U) * 
											(TAC_COL_PALM2_END - TAC_COL_PALM2_START + 1U)
    }
};

/**
 * @brief  通过AD值插值计算对应克重
 * @param  ad_val  输入的AD平均值
 * @return float   计算得到的克重（单位：g）
 * @note   超出标定范围时使用最近两端点的斜率做线性外推
 */
float ad_to_weight(float ad_val)
{
    // 边界外推：小于最小标定AD值，用前两点斜率外推
    if (ad_val < calib_ad[0])
    {
        float slope = (calib_weight[1] - calib_weight[0]) / (calib_ad[1] - calib_ad[0]);
        return calib_weight[0] + (ad_val - calib_ad[0]) * slope;
    }

    // 边界外推：大于最大标定AD值，用最后两点斜率外推
    if (ad_val > calib_ad[CALIB_POINT_NUM - 1])
    {
        uint8_t last_idx = CALIB_POINT_NUM - 1;
        float slope = (calib_weight[last_idx] - calib_weight[last_idx - 1]) 
                    / (calib_ad[last_idx] - calib_ad[last_idx - 1]);
        return calib_weight[last_idx] + (ad_val - calib_ad[last_idx]) * slope;
    }

    // 标定区间内：查找所在分段
    uint8_t i;
    for (i = 0; i < CALIB_POINT_NUM - 1; i++)
    {
        if (ad_val >= calib_ad[i] && ad_val <= calib_ad[i + 1])
        {
            break;
        }
    }

    // 分段线性插值计算
    float ad_diff     = calib_ad[i + 1] - calib_ad[i];
    float weight_diff = calib_weight[i + 1] - calib_weight[i];
    float ratio       = (ad_val - calib_ad[i]) / ad_diff;
    float weight      = calib_weight[i] + ratio * weight_diff;

    return weight;
}


tac_data_cfg_t* GetTacDataCfg(void)
{
		return &tac_data_cfg;
}
tac_data_cfg_t* GetTacCalibData(void)
{
		return &tac_calib_data;
}

const tac_data_cfg_t* GetTacMaskData(void)
{
		return &tac_mask_data;
}
