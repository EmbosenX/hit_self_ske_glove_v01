/**
  ******************************************************************************
  * @file    py32f032_ll_dma.c
  * @author  MCU Application Team
  * @brief   DMA LL module driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 Puya Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by Puya under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "py32f032_ll_dma.h"
#ifdef  USE_FULL_ASSERT
  #include "py32_assert.h"
#else
  #define assert_param(expr) ((void)0U)
#endif

/** @addtogroup PY32F032_LL_Driver
  * @{
  */

#if defined (DMA1)

/** @defgroup DMA_LL DMA
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @addtogroup DMA_LL_Private_Macros
  * @{
  */
#define IS_LL_DMA_DIRECTION(__VALUE__)          (((__VALUE__) == LL_DMA_DIRECTION_PERIPH_TO_MEMORY) || \
                                                 ((__VALUE__) == LL_DMA_DIRECTION_MEMORY_TO_PERIPH) || \
                                                 ((__VALUE__) == LL_DMA_DIRECTION_MEMORY_TO_MEMORY))

#define IS_LL_DMA_MODE(__VALUE__)               (((__VALUE__) == LL_DMA_MODE_NORMAL) || \
                                                 ((__VALUE__) == LL_DMA_MODE_FINITE_CIRCULAR) || \
                                                 ((__VALUE__) == LL_DMA_MODE_INFINITE_CIRCULAR))

#define IS_LL_DMA_PERIPHINCMODE(__VALUE__)      (((__VALUE__) == LL_DMA_PERIPH_FIX) || \
                                                 ((__VALUE__) == LL_DMA_PERIPH_INCREMENT) || \
                                                 ((__VALUE__) == LL_DMA_PERIPH_DECREMENT))

#define IS_LL_DMA_MEMORYINCMODE(__VALUE__)      (((__VALUE__) == LL_DMA_MEMORY_FIX) || \
                                                 ((__VALUE__) == LL_DMA_MEMORY_INCREMENT) || \
                                                 ((__VALUE__) == LL_DMA_MEMORY_DECREMENT))

#define IS_LL_DMA_PERIPHDATASIZE(__VALUE__)     (((__VALUE__) == LL_DMA_PDATAALIGN_BYTE)      || \
                                                 ((__VALUE__) == LL_DMA_PDATAALIGN_HALFWORD)  || \
                                                 ((__VALUE__) == LL_DMA_PDATAALIGN_WORD))

#define IS_LL_DMA_MEMORYDATASIZE(__VALUE__)     (((__VALUE__) == LL_DMA_MDATAALIGN_BYTE)      || \
                                                 ((__VALUE__) == LL_DMA_MDATAALIGN_HALFWORD)  || \
                                                 ((__VALUE__) == LL_DMA_MDATAALIGN_WORD))

#define IS_LL_DMA_PRIORITY(__VALUE__)           (((__VALUE__) == LL_DMA_PRIORITY_0)    || \
                                                 ((__VALUE__) == LL_DMA_PRIORITY_1) || \
                                                 ((__VALUE__) == LL_DMA_PRIORITY_2))

#define IS_LL_DMA_ALL_CHANNEL_INSTANCE(INSTANCE, CHANNEL)  ((((INSTANCE) == DMA1) && \
                                                            (((CHANNEL) == LL_DMA_CHANNEL_1) || \
                                                             ((CHANNEL) == LL_DMA_CHANNEL_2) || \
                                                             ((CHANNEL) == LL_DMA_CHANNEL_3))))
                                                             
#define IS_LL_DMA_PERIPHERAL_RELOAD(STATE) (((STATE) == LL_DMA_PRELOAD_ENABLE) || \
                                            ((STATE) == LL_DMA_PRELOAD_DISABLE))

#define IS_LL_DMA_MEMORY_RELOAD(STATE) (((STATE) == LL_DMA_MRELOAD_ENABLE) || \
                                        ((STATE) == LL_DMA_MRELOAD_DISABLE))

#define IS_LL_DMA_BLOCK_SIZE(SIZE) ((SIZE) <= 65535U)

#define IS_LL_DMA_TRANSFER_MODE(MODE) (((MODE) == LL_DMA_TRANSFER_SINGLE) || \
                                       ((MODE) == LL_DMA_TRANSFER_BULK))

#define IS_LL_DMA_ARB_MODE(MODE) (((MODE) == LL_DMA_ARB_FAST) || \
                                  ((MODE) == LL_DMA_ARB_POLL))

#define IS_LL_DMA_BTC_SUSPEND(STATE) (((STATE) == LL_DMA_BTC_SUSPEND_DISABLE) || \
                                      ((STATE) == LL_DMA_BTC_SUSPEND_ENABLE))
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup DMA_LL_Exported_Functions
  * @{
  */

/** @addtogroup DMA_LL_EF_Init
  * @{
  */

/**
  * @brief  De-initialize the DMA registers to their default reset values.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: DMA registers are de-initialized
  *          - ERROR: DMA registers are not de-initialized
  */
uint32_t LL_DMA_DeInit(DMA_TypeDef *DMAx, uint32_t Channel)
{
  DMA_Channel_TypeDef *tmp = (DMA_Channel_TypeDef *)DMA1_Channel1;
  ErrorStatus status = SUCCESS;

  /* Check the DMA Instance DMAx and Channel parameters*/
  assert_param(IS_LL_DMA_ALL_CHANNEL_INSTANCE(DMAx, Channel));

  tmp = (DMA_Channel_TypeDef *)(__LL_DMA_GET_CHANNEL_INSTANCE(DMAx, Channel));

  /* Disable the selected DMAx_Channely */
  CLEAR_BIT(tmp->CCR, DMA_CCR_EN);

  /* Reset DMAx_Channely control register */
  LL_DMA_WriteReg(tmp, CCR, 0U);

  /* Reset DMAx_Channely remaining bytes register */
  LL_DMA_WriteReg(tmp, CNDTR, 0U);

  /* Reset DMAx_Channely peripheral address register */
  LL_DMA_WriteReg(tmp, CPAR, 0U);

  /* Reset DMAx_Channely memory address register */
  LL_DMA_WriteReg(tmp, CMAR, 0U);
  
  /* Reset DMAx_Channely  cyclic transfer configuration register  */
  LL_DMA_WriteReg(tmp, CCCFGR, 0U);

  if (Channel == LL_DMA_CHANNEL_1)
  {
    /* Reset interrupt pending bits for DMAx Channel1 */
    LL_DMA_ClearFlag_TC1(DMAx);
    LL_DMA_ClearFlag_BTC1(DMAx);
    LL_DMA_ClearFlag_HBT1(DMAx);
    LL_DMA_ClearFlag_TE1(DMAx);
  }
  else if (Channel == LL_DMA_CHANNEL_2)
  {
    /* Reset interrupt pending bits for DMAx Channel1 */
    LL_DMA_ClearFlag_TC2(DMAx);
    LL_DMA_ClearFlag_BTC2(DMAx);
    LL_DMA_ClearFlag_HBT2(DMAx);
    LL_DMA_ClearFlag_TE2(DMAx);
  }
  else if (Channel == LL_DMA_CHANNEL_3)
  {
    /* Reset interrupt pending bits for DMAx Channel1 */
    LL_DMA_ClearFlag_TC3(DMAx);
    LL_DMA_ClearFlag_BTC3(DMAx);
    LL_DMA_ClearFlag_HBT3(DMAx);
    LL_DMA_ClearFlag_TE3(DMAx);
  }
  else
  {
    status = ERROR;
  }

  return status;
}

/**
  * @brief  Initialize the DMA registers according to the specified parameters in DMA_InitStruct.
  * @note   To convert DMAx_Channely Instance to DMAx Instance and Channely, use helper macros :
  *         @arg @ref __LL_DMA_GET_INSTANCE
  *         @arg @ref __LL_DMA_GET_CHANNEL
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @param  DMA_InitStruct pointer to a @ref LL_DMA_InitTypeDef structure.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: DMA registers are initialized
  *          - ERROR: Not applicable
  */
uint32_t LL_DMA_Init(DMA_TypeDef *DMAx, uint32_t Channel, LL_DMA_InitTypeDef *DMA_InitStruct)
{
  /* Check the DMA Instance DMAx and Channel parameters*/
  assert_param(IS_LL_DMA_ALL_CHANNEL_INSTANCE(DMAx, Channel));

  /* Check the DMA parameters from DMA_InitStruct */
  assert_param(IS_LL_DMA_DIRECTION(DMA_InitStruct->Direction));
  assert_param(IS_LL_DMA_MODE(DMA_InitStruct->Mode));
  assert_param(IS_LL_DMA_PERIPHINCMODE(DMA_InitStruct->PeriphOrM2MSrcIncMode));
  assert_param(IS_LL_DMA_MEMORYINCMODE(DMA_InitStruct->MemoryOrM2MDstIncMode));
  assert_param(IS_LL_DMA_PERIPHDATASIZE(DMA_InitStruct->PeriphOrM2MSrcDataSize));
  assert_param(IS_LL_DMA_MEMORYDATASIZE(DMA_InitStruct->MemoryOrM2MDstDataSize));
  assert_param(IS_LL_DMA_PRIORITY(DMA_InitStruct->Priority));
  assert_param(IS_LL_DMA_PERIPHERAL_RELOAD(DMA_InitStruct->PeriphReload));
  assert_param(IS_LL_DMA_MEMORY_RELOAD(DMA_InitStruct->MemReload));
  assert_param(IS_LL_DMA_BLOCK_SIZE(DMA_InitStruct->BlockLen));
  assert_param(IS_LL_DMA_TRANSFER_MODE(DMA_InitStruct->TransMode));
  assert_param(IS_LL_DMA_ARB_MODE(DMA_InitStruct->ArbMode));
  assert_param(IS_LL_DMA_BTC_SUSPEND(DMA_InitStruct->BTCSuspend));

  /*---------------------------- DMAx CCR Configuration ------------------------
   * Configure DMAx_Channely: data transfer direction, data transfer mode,
   *                          peripheral and memory increment mode,
   *                          data size alignment and  priority level with parameters :
   * - Direction:      DMA_CCR_DIR and DMA_CCR_MEM2MEM bits
   * - Mode:           DMA_CCR_CIRC bit
   * - PeriphOrM2MSrcIncMode:  DMA_CCR_PINC bit
   * - MemoryOrM2MDstIncMode:  DMA_CCR_MINC bit
   * - PeriphOrM2MSrcDataSize: DMA_CCR_PSIZE[1:0] bits
   * - MemoryOrM2MDstDataSize: DMA_CCR_MSIZE[1:0] bits
   * - Priority:               DMA_CCR_PL[1:0] bits
   */
  LL_DMA_ConfigTransfer(DMAx, Channel, DMA_InitStruct->Direction | \
                        DMA_InitStruct->PeriphOrM2MSrcIncMode  | \
                        DMA_InitStruct->MemoryOrM2MDstIncMode  | \
                        DMA_InitStruct->PeriphOrM2MSrcDataSize | \
                        DMA_InitStruct->MemoryOrM2MDstDataSize | \
                        DMA_InitStruct->Priority);
  
  if (DMA_InitStruct->Mode != LL_DMA_MODE_NORMAL)
  {
    SET_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_CIRC);
    
    MODIFY_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, \
                DMA_CCR_PNORLD | DMA_CCR_MNORLD | DMA_CCR_BTCSUSP, \
                DMA_InitStruct->PeriphReload | DMA_InitStruct->MemReload | DMA_InitStruct->BTCSuspend);
    
    /* set length */
    if (DMA_InitStruct->Mode == LL_DMA_MODE_FINITE_CIRCULAR)
    {
      WRITE_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CNDTR, DMA_InitStruct->BlockLen);
      WRITE_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCCFGR, \
                 ((DMA_InitStruct->NbData / DMA_InitStruct->BlockLen) & 0xFFU) | (((DMA_InitStruct->NbData % DMA_InitStruct->BlockLen) & 0xFFFFU) << DMA_CCCFGR_NDTL_Pos));
    }
    else
    {
      WRITE_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CNDTR, DMA_InitStruct->NbData);
      CLEAR_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCCFGR, DMA_CCCFGR_NBT);
    }
  }
  else
  {
    CLEAR_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_CIRC);
    
    /* set length */
    WRITE_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CNDTR, DMA_InitStruct->NbData);
    CLEAR_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCCFGR, DMA_CCCFGR_NBT);
  }
  
  if (DMA_InitStruct->Direction == LL_DMA_DIRECTION_MEMORY_TO_MEMORY)
  {
    MODIFY_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, \
                DMA_CCR_M2MARB, DMA_InitStruct->ArbMode);
  }
  else
  {
    MODIFY_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, \
                DMA_CCR_TRANST, DMA_InitStruct->TransMode);
  }

  /*-------------------------- DMAx CMAR Configuration -------------------------
   * Configure the memory or destination base address with parameter :
   * - MemoryOrM2MDstAddress: DMA_CMAR_MA[31:0] bits
   */
  LL_DMA_SetMemoryAddress(DMAx, Channel, DMA_InitStruct->MemoryOrM2MDstAddress);

  /*-------------------------- DMAx CPAR Configuration -------------------------
   * Configure the peripheral or source base address with parameter :
   * - PeriphOrM2MSrcAddress: DMA_CPAR_PA[31:0] bits
   */
  LL_DMA_SetPeriphAddress(DMAx, Channel, DMA_InitStruct->PeriphOrM2MSrcAddress);

  return SUCCESS;
}

/**
  * @brief  Set each @ref LL_DMA_InitTypeDef field to default value.
  * @param  DMA_InitStruct Pointer to a @ref LL_DMA_InitTypeDef structure.
  * @retval None
  */
void LL_DMA_StructInit(LL_DMA_InitTypeDef *DMA_InitStruct)
{
  /* Set DMA_InitStruct fields to default values */
  DMA_InitStruct->PeriphOrM2MSrcAddress  = 0x00000000U;
  DMA_InitStruct->MemoryOrM2MDstAddress  = 0x00000000U;
  DMA_InitStruct->Direction              = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
  DMA_InitStruct->Mode                   = LL_DMA_MODE_NORMAL;
  DMA_InitStruct->PeriphOrM2MSrcIncMode  = LL_DMA_PERIPH_FIX;
  DMA_InitStruct->MemoryOrM2MDstIncMode  = LL_DMA_MEMORY_FIX;
  DMA_InitStruct->PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
  DMA_InitStruct->MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
  DMA_InitStruct->NbData                 = 0x00000000U;
  DMA_InitStruct->Priority               = LL_DMA_PRIORITY_0;
  DMA_InitStruct->PeriphReload           = LL_DMA_PRELOAD_ENABLE;
  DMA_InitStruct->MemReload              = LL_DMA_MRELOAD_ENABLE;
  DMA_InitStruct->BlockLen               = 0x00000000U;
  DMA_InitStruct->TransMode              = LL_DMA_TRANSFER_SINGLE;
  DMA_InitStruct->ArbMode                = LL_DMA_ARB_FAST;
  DMA_InitStruct->BTCSuspend             = LL_DMA_BTC_SUSPEND_DISABLE;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* DMA */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
