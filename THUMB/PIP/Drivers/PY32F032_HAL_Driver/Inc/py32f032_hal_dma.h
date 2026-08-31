/**
  ******************************************************************************
  * @file    py32f032_hal_dma.h
  * @author  MCU Application Team
  * @brief   Header file of DMA HAL module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PY32F032_HAL_DMA_H
#define __PY32F032_HAL_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f032_hal_def.h"

/** @addtogroup PY32F032_HAL_Driver
  * @{
  */

/** @addtogroup DMA
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup DMA_Exported_Types DMA Exported Types
  * @{
  */

/**
  * @brief  DMA Configuration Structure definition
  */
typedef struct
{
  uint32_t Direction;                 /*!< Specifies if the data will be transferred from memory to peripheral,
                                           from memory to memory or from peripheral to memory.
                                           This parameter can be a value of @ref DMA_Data_transfer_direction */

  uint32_t PeriphInc;                 /*!< Specifies whether the Peripheral address register should be incremented or not.
                                           This parameter can be a value of @ref DMA_Peripheral_incremented_mode */

  uint32_t MemInc;                    /*!< Specifies whether the memory address register should be incremented or not.
                                           This parameter can be a value of @ref DMA_Memory_incremented_mode */

  uint32_t PeriphDataAlignment;       /*!< Specifies the Peripheral data width.
                                           This parameter can be a value of @ref DMA_Peripheral_data_size */

  uint32_t MemDataAlignment;          /*!< Specifies the Memory data width.
                                           This parameter can be a value of @ref DMA_Memory_data_size */

  uint32_t Mode;                      /*!< Specifies the operation mode of the DMAy Channelx.
                                           This parameter can be a value of @ref DMA_mode */

  uint32_t Priority;                  /*!< Specifies the software priority for the DMAy Channelx.
                                            This parameter can be a value of @ref DMA_Priority_level */
  
  uint32_t PeriphReload;              /*!< Specifies whether peripheral address reload is enabled.
                                            This parameter can be a value of @ref DMA_Peripheral_Reload
                                            @note This configuration is used for DMA_FINITE_CIRCULAR mode and
                                                  DMA_INFINITE_CIRCULAR mode, not for DMA_NORMAL mode */
  
  uint32_t MemReload;                 /*!< Specifies whether memory address reload is enabled.
                                            This parameter can be a value of @ref DMA_Memory_Reload
                                            @note This configuration is used for DMA_FINITE_CIRCULAR mode and
                                                  DMA_INFINITE_CIRCULAR mode, not for DMA_NORMAL mode */
  
  uint32_t BlockLen;                  /*!< Specifies block length in DMA_FINITE_CIRCULAR mode.
                                            This parameter must be a number between Min_Data = 1 and Max_Data = 65535.
                                            @note This configuration is used for DMA_FINITE_CIRCULAR mode */
  
  uint32_t TransMode;                 /*!< Specifies data transfer mode.
                                           This parameter can be a value of @ref DMA_Transfer_Mode
                                           @note This configuration is used for data transfer between memory and peripherals,
                                                 not for data transfer between memory and memory. */
  
  uint32_t ArbMode;                   /*!< Specifies arbitration mode.
                                           This parameter can be a value of @ref DMA_Arbitration_Mode
                                           @note This configuration is used for data transfer between memory and memory. */
  
  uint32_t BTCSuspend;               /*!< Specifies BTC interrupt post-processing mode.
                                           This parameter can be a value of @ref DMA_BTC_Suspend
                                           @note This configuration is used for DMA_FINITE_CIRCULAR mode and
                                                  DMA_INFINITE_CIRCULAR mode, not for DMA_NORMAL mode */
} DMA_InitTypeDef;

/**
  * @brief  HAL DMA State structures definition
  */
typedef enum
{
  HAL_DMA_STATE_RESET             = 0x00U,  /*!< DMA not yet initialized or disabled */
  HAL_DMA_STATE_READY             = 0x01U,  /*!< DMA initialized and ready for use   */
  HAL_DMA_STATE_BUSY              = 0x02U,  /*!< DMA process is ongoing              */
  HAL_DMA_STATE_TIMEOUT           = 0x03U   /*!< DMA timeout state                   */
} HAL_DMA_StateTypeDef;

/**
  * @brief  HAL DMA Error Code structure definition
  */
typedef enum
{
  HAL_DMA_FULL_TRANSFER            = 0x00U,    /*!< Full transfer     */
  HAL_DMA_HALF_BLOCK_TRANSFER      = 0x01U     /*!< Half block Transfer   */
} HAL_DMA_LevelCompleteTypeDef;

/**
  * @brief  HAL DMA Callback ID structure definition
  */
typedef enum
{
  HAL_DMA_XFER_CPLT_CB_ID            = 0x00U,    /*!< Full transfer     */
  HAL_DMA_XFER_BLOCK_CPLT_CB_ID      = 0x01U,    /*!< DMA block transfer complete     */
  HAL_DMA_XFER_HALFBLOCK_CPLT_CB_ID  = 0x02U,    /*!< DMA half block transfer complete     */
  HAL_DMA_XFER_ERROR_CB_ID           = 0x03U,    /*!< Error             */
  HAL_DMA_XFER_ABORT_CB_ID           = 0x04U,    /*!< Abort             */
  HAL_DMA_XFER_ALL_CB_ID             = 0x05U     /*!< All               */

} HAL_DMA_CallbackIDTypeDef;

/**
  * @brief  DMA handle Structure definition
  */
typedef struct __DMA_HandleTypeDef
{
  DMA_Channel_TypeDef   *Instance;                                                    /*!< Register base address                  */

  DMA_InitTypeDef       Init;                                                         /*!< DMA communication parameters           */

  HAL_LockTypeDef       Lock;                                                         /*!< DMA locking object                     */

  __IO HAL_DMA_StateTypeDef  State;                                                   /*!< DMA transfer state                     */

  void                  *Parent;                                                      /*!< Parent object state                    */

  void                  (* XferCpltCallback)( struct __DMA_HandleTypeDef * hdma);     /*!< DMA transfer complete callback         */

  void                  (* XferHalfCpltCallback)( struct __DMA_HandleTypeDef * hdma); /*!< DMA block transfer complete callback  */
  
  void                  (* XferBlockCpltCallback)( struct __DMA_HandleTypeDef * hdma); /*!< DMA block transfer complete callback  */
  
  void                  (* XferHalfBlockCpltCallback)( struct __DMA_HandleTypeDef * hdma); /*!< DMA half block transfer complete callback         */

  void                  (* XferErrorCallback)( struct __DMA_HandleTypeDef * hdma);    /*!< DMA transfer error callback            */

  void                  (* XferAbortCallback)( struct __DMA_HandleTypeDef * hdma);    /*!< DMA transfer abort callback            */

  __IO uint32_t         ErrorCode;                                                    /*!< DMA Error code                         */

  DMA_TypeDef          *DmaBaseAddress;                                               /*!< DMA Channel Base Address                */

  uint32_t              ChannelIndex;                                                 /*!< DMA Channel Index                       */
} DMA_HandleTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup DMA_Exported_Constants DMA Exported Constants
  * @{
  */

/** @defgroup DMA_Error_Code DMA Error Code
  * @{
  */
#define HAL_DMA_ERROR_NONE          (0x00000000U)    /*!< No error             */
#define HAL_DMA_ERROR_TE            (0x00000001U)    /*!< Transfer error       */
#define HAL_DMA_ERROR_NO_XFER       (0x00000004U)    /*!< no ongoin transfer   */
#define HAL_DMA_ERROR_TIMEOUT       (0x00000020U)    /*!< Timeout error        */
#define HAL_DMA_ERROR_NOT_SUPPORTED (0x00000100U)    /*!< Not supported mode */
/**
  * @}
  */

/** @defgroup DMA_Data_transfer_direction DMA Data transfer direction
  * @{
  */
#define DMA_PERIPH_TO_MEMORY         (0x00000000U)                 /*!< Peripheral to memory direction */
#define DMA_MEMORY_TO_PERIPH         ((uint32_t)DMA_CCR_DIR)       /*!< Memory to peripheral direction */
#define DMA_MEMORY_TO_MEMORY         ((uint32_t)(DMA_CCR_MEM2MEM)) /*!< Memory to memory direction     */

/**
  * @}
  */

/** @defgroup DMA_Peripheral_incremented_mode DMA Peripheral incremented mode
  * @{
  */
#define DMA_PADDR_FIX        (0x00000000U)               /*!< Peripheral address fixed  */
#define DMA_PADDR_INC        ((uint32_t)DMA_CCR_PINC_0)  /*!< Peripheral address increment */
#define DMA_PADDR_DEC        ((uint32_t)DMA_CCR_PINC_1)  /*!< Peripheral address decrement */
/**
  * @}
  */

/** @defgroup DMA_Memory_incremented_mode DMA Memory incremented mode
  * @{
  */
#define DMA_MADDR_FIX        (0x00000000U)               /*!< Memory address fixed  */
#define DMA_MADDR_INC        ((uint32_t)DMA_CCR_MINC_0)  /*!< Memory address increment */
#define DMA_MADDR_DEC        ((uint32_t)DMA_CCR_MINC_1)  /*!< Memory address decrement */
/**
  * @}
  */

/** @defgroup DMA_Peripheral_data_size DMA Peripheral data size
  * @{
  */
#define DMA_PDATAALIGN_BYTE          (0x00000000U)                /*!< Peripheral data alignment : Byte     */
#define DMA_PDATAALIGN_HALFWORD      ((uint32_t)DMA_CCR_PSIZE_0)  /*!< Peripheral data alignment : HalfWord */
#define DMA_PDATAALIGN_WORD          ((uint32_t)DMA_CCR_PSIZE_1)  /*!< Peripheral data alignment : Word     */
/**
  * @}
  */

/** @defgroup DMA_Memory_data_size DMA Memory data size
  * @{
  */
#define DMA_MDATAALIGN_BYTE          (0x00000000U)                /*!< Memory data alignment : Byte     */
#define DMA_MDATAALIGN_HALFWORD      ((uint32_t)DMA_CCR_MSIZE_0)  /*!< Memory data alignment : HalfWord */
#define DMA_MDATAALIGN_WORD          ((uint32_t)DMA_CCR_MSIZE_1)  /*!< Memory data alignment : Word     */
/**
  * @}
  */

/** @defgroup DMA_mode DMA mode
  * @{
  */
#define DMA_NORMAL               (0x00000000U)               /*!< Normal Mode                  */
#define DMA_FINITE_CIRCULAR      (0x00000001U)               /*!< Finite Circular Mode         */
#define DMA_INFINITE_CIRCULAR    (0x00000002U)               /*!< Infinite Circular Mode       */
/**
  * @}
  */

/** @defgroup DMA_Priority_level DMA Priority level
  * @{
  */
#define DMA_PRIORITY_0          (0x00000000U)                              /*!< Priority level : 0    */
#define DMA_PRIORITY_1          ((uint32_t)DMA_CCR_PL_0)                   /*!< Priority level : 1    */
#define DMA_PRIORITY_2          ((uint32_t)DMA_CCR_PL_1)                   /*!< Priority level : 2    */
/**
  * @}
  */

/** @defgroup DMA_Peripheral_Reload DMA Peripheral Address Reload
  * @{
  */
#define DMA_PRELOAD_ENABLE   (0x00000000U)                /*!< Peripheral address reload enable    */
#define DMA_PRELOAD_DISABLE  ((uint32_t)DMA_CCR_PNORLD)   /*!< Peripheral address reload disable    */
/**
  * @}
  */

/** @defgroup DMA_Memory_Reload DMA Memory Address Reload
  * @{
  */
#define DMA_MRELOAD_ENABLE   (0x00000000U)                  /*!< Memory address reload enable    */
#define DMA_MRELOAD_DISABLE  ((uint32_t)DMA_CCR_MNORLD)     /*!< Memory address reload disable    */
/**
  * @}
  */

/** @defgroup DMA_Transfer_Mode DMA Transfer Mode
  * @{
  */
#define DMA_TRANSFER_SINGLE   (0x00000000U)                  /*!< single transfer     */
#define DMA_TRANSFER_BULK     ((uint32_t)DMA_CCR_TRANST)     /*!< bulk transfer     */
/**
  * @}
  */

/** @defgroup DMA_Arbitration_Mode DMA Arbitration Mode
  * @{
  */
#define DMA_ARB_FAST   (0x00000000U)                  /*!< Do not release the bus after 1 data transfer   */
#define DMA_ARB_POLL   ((uint32_t)DMA_CCR_M2MARB)     /*!< Release bus after 1 data transfer      */
/**
  * @}
  */

/** @defgroup DMA_BTC_Suspend DMA BTC Suspend Mode
  * @{
  */
#define DMA_BTC_SUSPEND_DISABLE   (0x00000000U)                  /*!< Disable suspend transfer after block transfer completion interrupt    */
#define DMA_BTC_SUSPEND_ENABLE    ((uint32_t)DMA_CCR_BTCSUSP)    /*!< Enable suspend transfer after block transfer completion interrupt      */
/**
  * @}
  */

/** @defgroup DMA_interrupt_enable_definitions DMA interrupt enable definitions
  * @{
  */
#define DMA_IT_TC                         ((uint32_t)DMA_CCR_TCIE)
#define DMA_IT_BTC                        ((uint32_t)DMA_CCR_BTCIE)
#define DMA_IT_HBT                        ((uint32_t)DMA_CCR_HBTIE)
#define DMA_IT_TE                         ((uint32_t)DMA_CCR_TEIE)
/**
  * @}
  */

/** @defgroup DMA_flag_definitions DMA flag definitions
  * @{
  */
#define DMA_FLAG_TC1                      0x00000001U
#define DMA_FLAG_BTC1                     0x00000002U
#define DMA_FLAG_HBT1                     0x00000004U
#define DMA_FLAG_TE1                      0x00000008U
#define DMA_FLAG_TC2                      0x00000010U
#define DMA_FLAG_BTC2                     0x00000020U
#define DMA_FLAG_HBT2                     0x00000040U
#define DMA_FLAG_TE2                      0x00000080U
#define DMA_FLAG_TC3                      0x00000100U
#define DMA_FLAG_BTC3                     0x00000200U
#define DMA_FLAG_HBT3                     0x00000400U
#define DMA_FLAG_TE3                      0x00000800U
/**
  * @}
  */



/** @defgroup DMA_Channel_map DMA Channel map
  * @{
  */
#define DMA_CHANNEL_MAP_ADC               0U
#define DMA_CHANNEL_MAP_SPI1_RX           3U
#define DMA_CHANNEL_MAP_SPI1_TX           4U
#define DMA_CHANNEL_MAP_SPI2_RX           5U
#define DMA_CHANNEL_MAP_SPI2_TX           6U
#define DMA_CHANNEL_MAP_USART1_RX         7U
#define DMA_CHANNEL_MAP_USART1_TX         8U
#define DMA_CHANNEL_MAP_UART1_RX          11U
#define DMA_CHANNEL_MAP_UART1_TX          12U
#define DMA_CHANNEL_MAP_LPUART1_RX        13U
#define DMA_CHANNEL_MAP_LPUART1_TX        14U
#define DMA_CHANNEL_MAP_I2C1_RX           15U
#define DMA_CHANNEL_MAP_I2C1_TX           16U
#define DMA_CHANNEL_MAP_TIM1_CH1          19U
#define DMA_CHANNEL_MAP_TIM1_CH2          20U
#define DMA_CHANNEL_MAP_TIM1_CH3          21U
#define DMA_CHANNEL_MAP_TIM1_CH4          22U
#define DMA_CHANNEL_MAP_TIM1_COM          23U
#define DMA_CHANNEL_MAP_TIM1_TRG          24U
#define DMA_CHANNEL_MAP_TIM1_UP           25U

#define DMA_CHANNEL_MAP_TIM3_CH1          32U
#define DMA_CHANNEL_MAP_TIM3_CH2          33U
#define DMA_CHANNEL_MAP_TIM3_CH3          34U
#define DMA_CHANNEL_MAP_TIM3_CH4          35U
#define DMA_CHANNEL_MAP_TIM3_UP           36U
#define DMA_CHANNEL_MAP_TIM3_TRG          37U

#define DMA_CHANNEL_MAP_TIM16_CH1         45U
#define DMA_CHANNEL_MAP_TIM16_UP          46U
#define DMA_CHANNEL_MAP_TIM17_CH1         47U
#define DMA_CHANNEL_MAP_TIM17_UP          48U

#define DMA_CHANNEL_MAP_END               59U
/**
 * @}
 */





/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup DMA_Exported_Macros DMA Exported Macros
  * @{
  */

/** @brief  Reset DMA handle state
  * @param  __HANDLE__ DMA handle.
  * @retval None
  */
#define __HAL_DMA_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_DMA_STATE_RESET)

/**
  * @brief  Enable the specified DMA Channel.
  * @param  __HANDLE__ DMA handle
  * @retval None
  */
#define __HAL_DMA_ENABLE(__HANDLE__)        ((__HANDLE__)->Instance->CCR |= DMA_CCR_EN)

/**
  * @brief  Disable the specified DMA Channel.
  * @param  __HANDLE__ DMA handle
  * @retval None
  */
#define __HAL_DMA_DISABLE(__HANDLE__)       ((__HANDLE__)->Instance->CCR &= ~DMA_CCR_EN)


/* Interrupt & Flag management */

/**
  * @brief  Enables the specified DMA Channel interrupts.
  * @param  __HANDLE__ DMA handle
  * @param __INTERRUPT__ specifies the DMA interrupt sources to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_IT_TC :  Transfer complete interrupt mask
  *            @arg DMA_IT_BTC:  block transfer complete interrupt mask
  *            @arg DMA_IT_HBT:  Half block transfer complete interrupt mask
  *            @arg DMA_IT_TE :  Transfer error interrupt mask
  * @retval None
  */
#define __HAL_DMA_ENABLE_IT(__HANDLE__, __INTERRUPT__)   ((__HANDLE__)->Instance->CCR |= (__INTERRUPT__))

/**
  * @brief  Disables the specified DMA Channel interrupts.
  * @param  __HANDLE__ DMA handle
  * @param __INTERRUPT__ specifies the DMA interrupt sources to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_IT_TC :  Transfer complete interrupt mask
  *            @arg DMA_IT_BTC:  block transfer complete interrupt mask
  *            @arg DMA_IT_HBT:  Half block transfer complete interrupt mask
  *            @arg DMA_IT_TE :  Transfer error interrupt mask
  * @retval None
  */
#define __HAL_DMA_DISABLE_IT(__HANDLE__, __INTERRUPT__)  ((__HANDLE__)->Instance->CCR &= ~(__INTERRUPT__))

/**
  * @brief  Checks whether the specified DMA Channel interrupt is enabled or disabled.
  * @param  __HANDLE__ DMA handle
  * @param  __INTERRUPT__ specifies the DMA interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg DMA_IT_TC :  Transfer complete interrupt mask
  *            @arg DMA_IT_BTC:  block transfer complete interrupt mask
  *            @arg DMA_IT_HBT:  Half block transfer complete interrupt mask
  *            @arg DMA_IT_TE :  Transfer error interrupt mask
  * @retval The state of DMA_IT (SET or RESET).
  */
#define __HAL_DMA_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)  (((__HANDLE__)->Instance->CCR & (__INTERRUPT__)))

/**
  * @brief  Returns the number of remaining data units in the current DMAy Channelx transfer.
  * @param  __HANDLE__ DMA handle
  *
  * @retval The number of remaining data units in the current DMA Channel transfer.
  */
#define __HAL_DMA_GET_COUNTER(__HANDLE__) ((__HANDLE__)->Instance->CNDTR)





/**
  * @}
  */

/* Include DMA HAL Extension module */
#include "py32f032_hal_dma_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @addtogroup DMA_Exported_Functions
  * @{
  */

/** @addtogroup DMA_Exported_Functions_Group1
  * @{
  */
/* Initialization and de-initialization functions *****************************/
HAL_StatusTypeDef HAL_DMA_Init(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_DeInit (DMA_HandleTypeDef *hdma);
/**
  * @}
  */

/** @addtogroup DMA_Exported_Functions_Group2
  * @{
  */
/* Input and Output operation functions *****************************************************/
HAL_StatusTypeDef HAL_DMA_Start (DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
HAL_StatusTypeDef HAL_DMA_Start_IT(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
HAL_StatusTypeDef HAL_DMA_Abort(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_Abort_IT(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_PollForTransfer(DMA_HandleTypeDef *hdma, uint32_t CompleteLevel, uint32_t Timeout);
void              HAL_DMA_IRQHandler(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_RegisterCallback(DMA_HandleTypeDef *hdma, HAL_DMA_CallbackIDTypeDef CallbackID, void (* pCallback)( DMA_HandleTypeDef * _hdma));
HAL_StatusTypeDef HAL_DMA_UnRegisterCallback(DMA_HandleTypeDef *hdma, HAL_DMA_CallbackIDTypeDef CallbackID);
void              HAL_DMA_ChannelMap(DMA_HandleTypeDef *hdma, uint32_t MapReqNum);

/**
  * @}
  */

/** @addtogroup DMA_Exported_Functions_Group3
  * @{
  */
/* Peripheral State and Error functions ***************************************/
HAL_DMA_StateTypeDef HAL_DMA_GetState(DMA_HandleTypeDef *hdma);
uint32_t             HAL_DMA_GetError(DMA_HandleTypeDef *hdma);
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup DMA_Private_Macros DMA Private Macros
  * @{
  */
#define IS_DMA_DIRECTION(DIRECTION) (((DIRECTION) == DMA_PERIPH_TO_MEMORY ) || \
                                     ((DIRECTION) == DMA_MEMORY_TO_PERIPH)  || \
                                     ((DIRECTION) == DMA_MEMORY_TO_MEMORY))
                                     
#define IS_DMA_PERIPHERAL_INC_STATE(STATE) (((STATE) == DMA_PADDR_FIX) || \
                                            ((STATE) == DMA_PADDR_INC) || \
                                            ((STATE) == DMA_PADDR_DEC))

#define IS_DMA_MEMORY_INC_STATE(STATE) (((STATE) == DMA_MADDR_FIX) || \
                                        ((STATE) == DMA_MADDR_INC) || \
                                        ((STATE) == DMA_MADDR_DEC))
                                        
#define IS_DMA_PERIPHERAL_DATA_SIZE(SIZE) (((SIZE) == DMA_PDATAALIGN_BYTE)     || \
                                           ((SIZE) == DMA_PDATAALIGN_HALFWORD) || \
                                           ((SIZE) == DMA_PDATAALIGN_WORD))

#define IS_DMA_MEMORY_DATA_SIZE(SIZE) (((SIZE) == DMA_MDATAALIGN_BYTE)     || \
                                       ((SIZE) == DMA_MDATAALIGN_HALFWORD) || \
                                       ((SIZE) == DMA_MDATAALIGN_WORD ))

#define IS_DMA_MODE(MODE) (((MODE) == DMA_NORMAL )  || \
                           ((MODE) == DMA_FINITE_CIRCULAR )  || \
                           ((MODE) == DMA_INFINITE_CIRCULAR))
                           
#define IS_DMA_PRIORITY(PRIORITY) (((PRIORITY) == DMA_PRIORITY_0) || \
                                   ((PRIORITY) == DMA_PRIORITY_1) || \
                                   ((PRIORITY) == DMA_PRIORITY_2))

#define IS_DMA_PERIPHERAL_RELOAD(STATE) (((STATE) == DMA_PRELOAD_ENABLE) || \
                                         ((STATE) == DMA_PRELOAD_DISABLE))

#define IS_DMA_MEMORY_RELOAD(STATE) (((STATE) == DMA_MRELOAD_ENABLE) || \
                                     ((STATE) == DMA_MRELOAD_DISABLE))

#define IS_DMA_BLOCK_SIZE(SIZE) ((SIZE) <= 65535U)

#define IS_DMA_TRANSFER_MODE(MODE) (((MODE) == DMA_TRANSFER_SINGLE) || \
                                    ((MODE) == DMA_TRANSFER_BULK))

#define IS_DMA_ARB_MODE(MODE) (((MODE) == DMA_ARB_FAST) || \
                               ((MODE) == DMA_ARB_POLL))

#define IS_DMA_BTC_SUSPEND(STATE) (((STATE) == DMA_BTC_SUSPEND_DISABLE) || \
                                   ((STATE) == DMA_BTC_SUSPEND_ENABLE))

#define IS_DMA_MAP_VALUE(VALUE)  (VALUE < DMA_CHANNEL_MAP_END)



/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __PY32F032_HAL_DMA_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
