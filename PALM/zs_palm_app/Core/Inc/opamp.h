/**
 ******************************************************************************
 * @file    opamp.h
 * @brief   OPAMP运算放大器头文件
 ******************************************************************************
 */

#ifndef __OPAMP_H__
#define __OPAMP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

extern OPAMP_HandleTypeDef hopamp1;

void MX_OPAMP1_Init(void);

/* ==================== 用户代码开始 ==================== */
void OPAMP1_Start(void);
void OPAMP1_Stop(void);
void OPAMP1_SetGain(uint32_t gain);
/* ==================== 用户代码结束 ==================== */

#ifdef __cplusplus
}
#endif

#endif /* __OPAMP_H__ */



