/**
  ******************************************************************************
  * @file    py32f032_ll_dma.h
  * @author  MCU Application Team
  * @brief   Header file of DMA LL module.
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
#ifndef __PY32F032_LL_DMA_H
#define __PY32F032_LL_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f0xx.h"

/** @addtogroup PY32F032_LL_Driver
  * @{
  */
#if defined (DMA1)

/** @defgroup DMA_LL DMA
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @defgroup DMA_LL_Private_Variables DMA Private Variables
  * @{
  */
/* Array used to get the DMA channel register offset versus channel index LL_DMA_CHANNEL_x */
static const uint8_t CHANNEL_OFFSET_TAB[] =
{
  (uint8_t)(DMA1_Channel1_BASE - DMA1_BASE),
  (uint8_t)(DMA1_Channel2_BASE - DMA1_BASE),
  (uint8_t)(DMA1_Channel3_BASE - DMA1_BASE)
};
/**
  * @}
  */
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup DMA_LL_Private_Macros DMA Private Macros
  * @{
  */
/**
  * @}
  */
#endif /*USE_FULL_LL_DRIVER*/

/* Exported types ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup DMA_LL_ES_INIT DMA Exported Init structure
  * @{
  */
typedef struct
{
  uint32_t PeriphOrM2MSrcAddress;  /*!< Specifies the peripheral base address for DMA transfer
                                        or as Source base address in case of memory to memory transfer direction.

                                        This parameter must be a value between Min_Data = 0 and Max_Data = 0xFFFFFFFF. */

  uint32_t MemoryOrM2MDstAddress;  /*!< Specifies the memory base address for DMA transfer
                                        or as Destination base address in case of memory to memory transfer direction.

                                        This parameter must be a value between Min_Data = 0 and Max_Data = 0xFFFFFFFF. */

  uint32_t Direction;              /*!< Specifies if the data will be transferred from memory to peripheral,
                                        from memory to memory or from peripheral to memory.
                                        This parameter can be a value of @ref DMA_LL_EC_DIRECTION
  
                                        This feature can be modified afterwards using unitary function @ref LL_DMA_SetDataTransferDirection(). */

  uint32_t Mode;                   /*!< Specifies operation mode.
                                        This parameter can be a value of @ref DMA_LL_EC_MODE */

  uint32_t PeriphOrM2MSrcIncMode;  /*!< Specifies whether the Peripheral address or Source address in case of memory to memory transfer direction
                                        is incremented or not.
                                        This parameter can be a value of @ref DMA_LL_EC_PERIPH

                                        This feature can be modified afterwards using unitary function @ref LL_DMA_SetPeriphIncMode(). */

  uint32_t MemoryOrM2MDstIncMode;  /*!< Specifies whether the Memory address or Destination address in case of memory to memory transfer direction
                                        is incremented or not.
                                        This parameter can be a value of @ref DMA_LL_EC_MEMORY

                                        This feature can be modified afterwards using unitary function @ref LL_DMA_SetMemoryIncMode(). */

  uint32_t PeriphOrM2MSrcDataSize; /*!< Specifies the Peripheral data size alignment or Source data size alignment (byte, half word, word)
                                        in case of memory to memory transfer direction.
                                        This parameter can be a value of @ref DMA_LL_EC_PDATAALIGN

                                        This feature can be modified afterwards using unitary function @ref LL_DMA_SetPeriphSize(). */

  uint32_t MemoryOrM2MDstDataSize; /*!< Specifies the Memory data size alignment or Destination data size alignment (byte, half word, word)
                                        in case of memory to memory transfer direction.
                                        This parameter can be a value of @ref DMA_LL_EC_MDATAALIGN

                                        This feature can be modified afterwards using unitary function @ref LL_DMA_SetMemorySize(). */

  uint32_t NbData;                 /*!< Specifies the number of data to transfer, in data unit.
                                        The data unit is equal to the source buffer configuration set in PeripheralSize
                                        or MemorySize parameters depending in the transfer direction. */

  uint32_t Priority;               /*!< Specifies the channel priority level.
                                        This parameter can be a value of @ref DMA_LL_EC_PRIORITY

                                        This feature can be modified afterwards using unitary function @ref LL_DMA_SetChannelPriorityLevel(). */
  
  uint32_t PeriphReload;              /*!< Specifies whether peripheral address reload is enabled.
                                            This parameter can be a value of @ref DMA_LL_EC_Peripheral_Reload
                                            @note This configuration is used for LL_DMA_MODE_FINITE_CIRCULAR mode and
                                                  LL_DMA_MODE_INFINITE_CIRCULAR mode, not for LL_DMA_MODE_NORMAL mode */
  
  uint32_t MemReload;                 /*!< Specifies whether memory address reload is enabled.
                                            This parameter can be a value of @ref DMA_LL_EC_Memory_Reload
                                            @note This configuration is used for LL_DMA_MODE_FINITE_CIRCULAR mode and
                                                  LL_DMA_MODE_INFINITE_CIRCULAR mode, not for LL_DMA_MODE_NORMAL mode */
  
  uint32_t BlockLen;                  /*!< Specifies block length in LL_DMA_MODE_FINITE_CIRCULAR mode.
                                            This parameter must be a number between Min_Data = 1 and Max_Data = 65535.
                                            @note This configuration is used for LL_DMA_MODE_FINITE_CIRCULAR mode */
  
  uint32_t TransMode;                 /*!< Specifies data transfer mode.
                                           This parameter can be a value of @ref DMA_LL_EC_Transfer_Mode
                                           @note This configuration is used for data transfer between memory and peripherals,
                                                 not for data transfer between memory and memory. */
  
  uint32_t ArbMode;                   /*!< Specifies arbitration mode.
                                           This parameter can be a value of @ref DMA_LL_EC_Arbitration_Mode
                                           @note This configuration is used for data transfer between memory and memory. */
  
  uint32_t BTCSuspend;               /*!< Specifies BTC interrupt post-processing mode.
                                           This parameter can be a value of @ref DMA_LL_EC_BTC_Suspend
                                           @note This configuration is used for LL_DMA_MODE_FINITE_CIRCULAR mode and
                                                  LL_DMA_MODE_INFINITE_CIRCULAR mode, not for LL_DMA_MODE_NORMAL mode */

} LL_DMA_InitTypeDef;
/**
  * @}
  */
#endif /*USE_FULL_LL_DRIVER*/

/* Exported constants --------------------------------------------------------*/
/** @defgroup DMA_LL_Exported_Constants DMA Exported Constants
  * @{
  */
/** @defgroup DMA_LL_EC_CLEAR_FLAG Clear Flags Defines
  * @brief    Flags defines which can be used with LL_DMA_WriteReg function
  * @{
  */
#define LL_DMA_IFCR_CTCIF1                DMA_IFCR_CTCIF1       /*!< Channel 1 all block transfer complete flag */
#define LL_DMA_IFCR_CBTCIF1               DMA_IFCR_CBTCIF1      /*!< Channel 1 block transfer complete flag */
#define LL_DMA_IFCR_CHBTIF1               DMA_IFCR_CHBTIF1      /*!< Channel 1 block half transfer complete flag */
#define LL_DMA_IFCR_CTEIF1                DMA_IFCR_CTEIF1       /*!< Channel 1 transfer error flag    */
#define LL_DMA_IFCR_CTCIF2                DMA_IFCR_CTCIF2       /*!< Channel 2 all block transfer complete flag */
#define LL_DMA_IFCR_CBTCIF2               DMA_IFCR_CBTCIF2      /*!< Channel 2 block transfer complete flag */
#define LL_DMA_IFCR_CHBTIF2               DMA_IFCR_CHBTIF2      /*!< Channel 2 block half transfer complete flag */
#define LL_DMA_IFCR_CTEIF2                DMA_IFCR_CTEIF2       /*!< Channel 2 transfer error flag    */
#define LL_DMA_IFCR_CTCIF3                DMA_IFCR_CTCIF3       /*!< Channel 3 all block transfer complete flag */
#define LL_DMA_IFCR_CBTCIF3               DMA_IFCR_CBTCIF3      /*!< Channel 3 block transfer complete flag */
#define LL_DMA_IFCR_CHBTIF3               DMA_IFCR_CHBTIF3      /*!< Channel 3 block half transfer complete flag */
#define LL_DMA_IFCR_CTEIF3                DMA_IFCR_CTEIF3       /*!< Channel 3 transfer error flag    */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_DMA_ReadReg function
  * @{
  */
#define LL_DMA_ISR_TCIF1                DMA_ISR_TCIF1       /*!< Channel 1 all block transfer complete flag */
#define LL_DMA_ISR_BTCIF1               DMA_ISR_BTCIF1      /*!< Channel 1 block transfer complete flag */
#define LL_DMA_ISR_HBTIF1               DMA_ISR_HBTIF1      /*!< Channel 1 block half transfer complete flag */
#define LL_DMA_ISR_TEIF1                DMA_ISR_TEIF1       /*!< Channel 1 transfer error flag    */
#define LL_DMA_ISR_TCIF2                DMA_ISR_TCIF2       /*!< Channel 2 all block transfer complete flag */
#define LL_DMA_ISR_BTCIF2               DMA_ISR_BTCIF2      /*!< Channel 2 block transfer complete flag */
#define LL_DMA_ISR_HBTIF2               DMA_ISR_HBTIF2      /*!< Channel 2 block half transfer complete flag */
#define LL_DMA_ISR_TEIF2                DMA_ISR_TEIF2       /*!< Channel 2 transfer error flag    */
#define LL_DMA_ISR_TCIF3                DMA_ISR_TCIF3       /*!< Channel 3 all block transfer complete flag */
#define LL_DMA_ISR_BTCIF3               DMA_ISR_BTCIF3      /*!< Channel 3 block transfer complete flag */
#define LL_DMA_ISR_HBTIF3               DMA_ISR_HBTIF3      /*!< Channel 3 block half transfer complete flag */
#define LL_DMA_ISR_TEIF3                DMA_ISR_TEIF3       /*!< Channel 3 transfer error flag    */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_IT IT Defines
  * @brief    IT defines which can be used with LL_DMA_ReadReg and  LL_DMA_WriteReg functions
  * @{
  */
#define LL_DMA_CCR_TCIE                   DMA_CCR_TCIE           /*!< All block transfer complete interrupt */
#define LL_DMA_CCR_BTCIE                  DMA_CCR_BTCIE          /*!< Block transfer complete interrupt */
#define LL_DMA_CCR_HBTIE                  DMA_CCR_HBTIE          /*!< Block half transfer complete interrupt     */
#define LL_DMA_CCR_TEIE                   DMA_CCR_TEIE           /*!< Transfer error interrupt    */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_CHANNEL CHANNEL
  * @{
  */
#define LL_DMA_CHANNEL_1                  0x00000001U /*!< DMA Channel 1 */
#define LL_DMA_CHANNEL_2                  0x00000002U /*!< DMA Channel 2 */
#define LL_DMA_CHANNEL_3                  0x00000003U /*!< DMA Channel 3 */
#if defined(USE_FULL_LL_DRIVER)
#define LL_DMA_CHANNEL_ALL                0xFFFF0000U /*!< DMA Channel all (used only for function @ref LL_DMA_DeInit(). */
#endif /*USE_FULL_LL_DRIVER*/
/**
  * @}
  */

/** @defgroup DMA_LL_EC_DIRECTION Transfer Direction
  * @{
  */
#define LL_DMA_DIRECTION_PERIPH_TO_MEMORY 0x00000000U             /*!< Peripheral to memory direction */
#define LL_DMA_DIRECTION_MEMORY_TO_PERIPH DMA_CCR_DIR             /*!< Memory to peripheral direction */
#define LL_DMA_DIRECTION_MEMORY_TO_MEMORY DMA_CCR_MEM2MEM         /*!< Memory to memory direction     */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_MODE Transfer mode
  * @{
  */
#define LL_DMA_MODE_NORMAL               (0x00000000U)               /*!< Normal Mode                  */
#define LL_DMA_MODE_FINITE_CIRCULAR      (0x00000001U)               /*!< Finite Circular Mode         */
#define LL_DMA_MODE_INFINITE_CIRCULAR    (0x00000002U)               /*!< Infinite Circular Mode       */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_PERIPH Peripheral increment mode
  * @{
  */
#define LL_DMA_PERIPH_FIX                 (0x00000000U)               /*!< Peripheral address fixed */
#define LL_DMA_PERIPH_INCREMENT           ((uint32_t)DMA_CCR_PINC_0)  /*!< Peripheral address increment */
#define LL_DMA_PERIPH_DECREMENT           ((uint32_t)DMA_CCR_PINC_1)  /*!< Peripheral address decrement */

/**
  * @}
  */

/** @defgroup DMA_LL_EC_MEMORY Memory increment mode
  * @{
  */

#define LL_DMA_MEMORY_FIX                 (0x00000000U)               /*!< Memory address fixed  */
#define LL_DMA_MEMORY_INCREMENT           ((uint32_t)DMA_CCR_MINC_0)  /*!< Memory address increment */
#define LL_DMA_MEMORY_DECREMENT           ((uint32_t)DMA_CCR_MINC_1)  /*!< Memory address decrement */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_PDATAALIGN Peripheral data alignment
  * @{
  */
#define LL_DMA_PDATAALIGN_BYTE            0x00000000U             /*!< Peripheral data alignment : Byte     */
#define LL_DMA_PDATAALIGN_HALFWORD        DMA_CCR_PSIZE_0         /*!< Peripheral data alignment : HalfWord */
#define LL_DMA_PDATAALIGN_WORD            DMA_CCR_PSIZE_1         /*!< Peripheral data alignment : Word     */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_MDATAALIGN Memory data alignment
  * @{
  */
#define LL_DMA_MDATAALIGN_BYTE            0x00000000U             /*!< Memory data alignment : Byte     */
#define LL_DMA_MDATAALIGN_HALFWORD        DMA_CCR_MSIZE_0         /*!< Memory data alignment : HalfWord */
#define LL_DMA_MDATAALIGN_WORD            DMA_CCR_MSIZE_1         /*!< Memory data alignment : Word     */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_PRIORITY Transfer Priority level
  * @{
  */
#define LL_DMA_PRIORITY_0          (0x00000000U)                              /*!< Priority level : 0    */
#define LL_DMA_PRIORITY_1          ((uint32_t)DMA_CCR_PL_0)                   /*!< Priority level : 1    */
#define LL_DMA_PRIORITY_2          ((uint32_t)DMA_CCR_PL_1)                   /*!< Priority level : 2    */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_Peripheral_Reload DMA Peripheral Address Reload
  * @{
  */
#define LL_DMA_PRELOAD_ENABLE   (0x00000000U)                /*!< Peripheral address reload enable    */
#define LL_DMA_PRELOAD_DISABLE  ((uint32_t)DMA_CCR_PNORLD)   /*!< Peripheral address reload disable    */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_Memory_Reload DMA Memory Address Reload
  * @{
  */
#define LL_DMA_MRELOAD_ENABLE   (0x00000000U)                  /*!< Peripheral address reload enable    */
#define LL_DMA_MRELOAD_DISABLE  ((uint32_t)DMA_CCR_MNORLD)     /*!< Memory address reload disable    */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_Transfer_Mode DMA Transfer Mode
  * @{
  */
#define LL_DMA_TRANSFER_SINGLE   (0x00000000U)                  /*!< single transfer     */
#define LL_DMA_TRANSFER_BULK     ((uint32_t)DMA_CCR_TRANST)     /*!< bulk transfer     */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_Arbitration_Mode DMA Arbitration Mode
  * @{
  */
#define LL_DMA_ARB_FAST   (0x00000000U)                  /*!< Do not release the bus after 1 data transfer   */
#define LL_DMA_ARB_POLL   ((uint32_t)DMA_CCR_M2MARB)     /*!< Release bus after 1 data transfer      */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_BTC_Suspend DMA BTC Suspend Mode
  * @{
  */
#define LL_DMA_BTC_SUSPEND_DISABLE   (0x00000000U)                  /*!< Disable suspend transfer after block transfer completion interrupt    */
#define LL_DMA_BTC_SUSPEND_ENABLE    ((uint32_t)DMA_CCR_BTCSUSP)    /*!< Enable suspend transfer after block transfer completion interrupt      */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup DMA_LL_Exported_Macros DMA Exported Macros
  * @{
  */

/** @defgroup DMA_LL_EM_WRITE_READ Common Write and read registers macros
  * @{
  */
/**
  * @brief  Write a value in DMA register
  * @param  __INSTANCE__ DMA Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_DMA_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in DMA register
  * @param  __INSTANCE__ DMA Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_DMA_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/** @defgroup DMA_LL_EM_CONVERT_DMAxCHANNELy Convert DMAxChannely
  * @{
  */

/**
  * @brief  Convert DMAx_Channely into DMAx
  * @param  __CHANNEL_INSTANCE__ DMAx_Channely
  * @retval DMAx
  */
#define __LL_DMA_GET_INSTANCE(__CHANNEL_INSTANCE__)  (DMA1)

/**
  * @brief  Convert DMAx_Channely into LL_DMA_CHANNEL_y
  * @param  __CHANNEL_INSTANCE__ DMAx_Channely
  * @retval LL_DMA_CHANNEL_y
  */
#define __LL_DMA_GET_CHANNEL(__CHANNEL_INSTANCE__)   \
(((uint32_t)(__CHANNEL_INSTANCE__) == ((uint32_t)DMA1_Channel1)) ? LL_DMA1_CHANNEL_1 : \
 ((uint32_t)(__CHANNEL_INSTANCE__) == ((uint32_t)DMA1_Channel2)) ? LL_DMA1_CHANNEL_2 : \
 LL_DMA1_CHANNEL_3)

/**
  * @brief  Convert DMA Instance DMAx and LL_DMA_CHANNEL_y into DMAx_Channely
  * @param  __DMA_INSTANCE__ DMAx
  * @param  __CHANNEL__ LL_DMA_CHANNEL_y
  * @retval DMAx_Channely
  */
#define __LL_DMA_GET_CHANNEL_INSTANCE(__DMA_INSTANCE__, __CHANNEL__)   \
((((uint32_t)(__DMA_INSTANCE__) == ((uint32_t)DMA1)) && ((uint32_t)(__CHANNEL__) == ((uint32_t)LL_DMA_CHANNEL_1))) ? DMA1_Channel1 : \
 (((uint32_t)(__DMA_INSTANCE__) == ((uint32_t)DMA1)) && ((uint32_t)(__CHANNEL__) == ((uint32_t)LL_DMA_CHANNEL_2))) ? DMA1_Channel2 : \
 DMA1_Channel3)

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup DMA_LL_Exported_Functions DMA Exported Functions
 * @{
 */

/** @defgroup DMA_LL_EF_Configuration Configuration
  * @{
  */
/**
  * @brief  Enable DMA channel.
  * @rmtoll CCR          EN            LL_DMA_EnableChannel
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval None
  */
__STATIC_INLINE void LL_DMA_EnableChannel(DMA_TypeDef *DMAx, uint32_t Channel)
{
  SET_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_EN);
}

/**
  * @brief  Disable DMA channel.
  * @rmtoll CCR          EN            LL_DMA_DisableChannel
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval None
  */
__STATIC_INLINE void LL_DMA_DisableChannel(DMA_TypeDef *DMAx, uint32_t Channel)
{
  CLEAR_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_EN);
}

/**
  * @brief  Check if DMA channel is enabled or disabled.
  * @rmtoll CCR          EN            LL_DMA_IsEnabledChannel
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledChannel(DMA_TypeDef *DMAx, uint32_t Channel)
{
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
                   DMA_CCR_EN) == (DMA_CCR_EN));
}

/**
  * @brief  Configure all parameters link to DMA transfer.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @param  Configuration This parameter must be a combination of all the following values:
  *         @arg @ref LL_DMA_DIRECTION_PERIPH_TO_MEMORY or @ref LL_DMA_DIRECTION_MEMORY_TO_PERIPH or @ref LL_DMA_DIRECTION_MEMORY_TO_MEMORY
  *         @arg @ref LL_DMA_PERIPH_FIX or @ref LL_DMA_PERIPH_INCREMENT or @ref LL_DMA_PERIPH_DECREMENT
  *         @arg @ref LL_DMA_MEMORY_FIX or @ref LL_DMA_MEMORY_INCREMENT or @ref LL_DMA_MEMORY_DECREMENT
  *         @arg @ref LL_DMA_PDATAALIGN_BYTE or @ref LL_DMA_PDATAALIGN_HALFWORD or @ref LL_DMA_PDATAALIGN_WORD
  *         @arg @ref LL_DMA_MDATAALIGN_BYTE or @ref LL_DMA_MDATAALIGN_HALFWORD or @ref LL_DMA_MDATAALIGN_WORD
  *         @arg @ref LL_DMA_PRIORITY_0 or @ref LL_DMA_PRIORITY_1 or @ref LL_DMA_PRIORITY_2
  */
__STATIC_INLINE void LL_DMA_ConfigTransfer(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Configuration)
{
  MODIFY_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
             DMA_CCR_DIR | DMA_CCR_MEM2MEM | DMA_CCR_PINC | DMA_CCR_MINC | DMA_CCR_PSIZE | DMA_CCR_MSIZE | DMA_CCR_PL,
             Configuration);
}

/**
  * @brief  Set Data transfer direction (read from peripheral or from memory).
  * @rmtoll CCR          DIR           LL_DMA_SetDataTransferDirection\n
  *         CCR          MEM2MEM       LL_DMA_SetDataTransferDirection
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @param  Direction This parameter can be one of the following values:
  *         @arg @ref LL_DMA_DIRECTION_PERIPH_TO_MEMORY
  *         @arg @ref LL_DMA_DIRECTION_MEMORY_TO_PERIPH
  *         @arg @ref LL_DMA_DIRECTION_MEMORY_TO_MEMORY
  * @retval None
  */
__STATIC_INLINE void LL_DMA_SetDataTransferDirection(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Direction)
{
  MODIFY_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
             DMA_CCR_DIR | DMA_CCR_MEM2MEM, Direction);
}

/**
  * @brief  Get Data transfer direction (read from peripheral or from memory).
  * @rmtoll CCR          DIR           LL_DMA_GetDataTransferDirection\n
  *         CCR          MEM2MEM       LL_DMA_GetDataTransferDirection
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_DIRECTION_PERIPH_TO_MEMORY
  *         @arg @ref LL_DMA_DIRECTION_MEMORY_TO_PERIPH
  *         @arg @ref LL_DMA_DIRECTION_MEMORY_TO_MEMORY
  */
__STATIC_INLINE uint32_t LL_DMA_GetDataTransferDirection(DMA_TypeDef *DMAx, uint32_t Channel)
{
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
                   DMA_CCR_DIR | DMA_CCR_MEM2MEM));
}

/**
  * @brief  Enable DMA circular Mode.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval None
  */
__STATIC_INLINE void LL_DMA_EnableCircularMode(DMA_TypeDef *DMAx, uint32_t Channel)
{
  SET_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_CIRC);
}

/**
  * @brief  Disable DMA circular Mode.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval None
  */
__STATIC_INLINE void LL_DMA_DisableCircularMode(DMA_TypeDef *DMAx, uint32_t Channel)
{
  CLEAR_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_CIRC);
}

/**
  * @brief  Check if enable DMA circular Mode.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledCircularMode(DMA_TypeDef *DMAx, uint32_t Channel)
{
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
                   DMA_CCR_CIRC) == (DMA_CCR_CIRC));
}

/**
  * @brief  Set Peripheral increment mode.
  * @rmtoll CCR          PINC          LL_DMA_SetPeriphIncMode
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @param  PeriphOrM2MSrcIncMode This parameter can be one of the following values:
  *         @arg @ref LL_DMA_PERIPH_FIX      
  *         @arg @ref LL_DMA_PERIPH_INCREMENT
  *         @arg @ref LL_DMA_PERIPH_DECREMENT
  * @retval None
  */
__STATIC_INLINE void LL_DMA_SetPeriphIncMode(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t PeriphOrM2MSrcIncMode)
{
  MODIFY_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_PINC,
             PeriphOrM2MSrcIncMode);
}

/**
  * @brief  Get Peripheral increment mode.
  * @rmtoll CCR          PINC          LL_DMA_GetPeriphIncMode
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_PERIPH_FIX      
  *         @arg @ref LL_DMA_PERIPH_INCREMENT
  *         @arg @ref LL_DMA_PERIPH_DECREMENT
  */
__STATIC_INLINE uint32_t LL_DMA_GetPeriphIncMode(DMA_TypeDef *DMAx, uint32_t Channel)
{
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
                   DMA_CCR_PINC));
}

/**
  * @brief  Set Memory increment mode.
  * @rmtoll CCR          MINC          LL_DMA_SetMemoryIncMode
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @param  MemoryOrM2MDstIncMode This parameter can be one of the following values:
  *         @arg @ref LL_DMA_MEMORY_FIX      
  *         @arg @ref LL_DMA_MEMORY_INCREMENT
  *         @arg @ref LL_DMA_MEMORY_DECREMENT
  * @retval None
  */
__STATIC_INLINE void LL_DMA_SetMemoryIncMode(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t MemoryOrM2MDstIncMode)
{
  MODIFY_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_MINC,
             MemoryOrM2MDstIncMode);
}

/**
  * @brief  Get Memory increment mode.
  * @rmtoll CCR          MINC          LL_DMA_GetMemoryIncMode
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_MEMORY_FIX      
  *         @arg @ref LL_DMA_MEMORY_INCREMENT
  *         @arg @ref LL_DMA_MEMORY_DECREMENT
  */
__STATIC_INLINE uint32_t LL_DMA_GetMemoryIncMode(DMA_TypeDef *DMAx, uint32_t Channel)
{
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
                   DMA_CCR_MINC));
}

/**
  * @brief  Set Peripheral size.
  * @rmtoll CCR          PSIZE         LL_DMA_SetPeriphSize
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @param  PeriphOrM2MSrcDataSize This parameter can be one of the following values:
  *         @arg @ref LL_DMA_PDATAALIGN_BYTE
  *         @arg @ref LL_DMA_PDATAALIGN_HALFWORD
  *         @arg @ref LL_DMA_PDATAALIGN_WORD
  * @retval None
  */
__STATIC_INLINE void LL_DMA_SetPeriphSize(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t PeriphOrM2MSrcDataSize)
{
  MODIFY_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_PSIZE,
             PeriphOrM2MSrcDataSize);
}

/**
  * @brief  Get Peripheral size.
  * @rmtoll CCR          PSIZE         LL_DMA_GetPeriphSize
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_PDATAALIGN_BYTE
  *         @arg @ref LL_DMA_PDATAALIGN_HALFWORD
  *         @arg @ref LL_DMA_PDATAALIGN_WORD
  */
__STATIC_INLINE uint32_t LL_DMA_GetPeriphSize(DMA_TypeDef *DMAx, uint32_t Channel)
{
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
                   DMA_CCR_PSIZE));
}

/**
  * @brief  Set Memory size.
  * @rmtoll CCR          MSIZE         LL_DMA_SetMemorySize
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @param  MemoryOrM2MDstDataSize This parameter can be one of the following values:
  *         @arg @ref LL_DMA_MDATAALIGN_BYTE
  *         @arg @ref LL_DMA_MDATAALIGN_HALFWORD
  *         @arg @ref LL_DMA_MDATAALIGN_WORD
  * @retval None
  */
__STATIC_INLINE void LL_DMA_SetMemorySize(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t MemoryOrM2MDstDataSize)
{
  MODIFY_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_MSIZE,
             MemoryOrM2MDstDataSize);
}

/**
  * @brief  Get Memory size.
  * @rmtoll CCR          MSIZE         LL_DMA_GetMemorySize
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_MDATAALIGN_BYTE
  *         @arg @ref LL_DMA_MDATAALIGN_HALFWORD
  *         @arg @ref LL_DMA_MDATAALIGN_WORD
  */
__STATIC_INLINE uint32_t LL_DMA_GetMemorySize(DMA_TypeDef *DMAx, uint32_t Channel)
{
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
                   DMA_CCR_MSIZE));
}

/**
  * @brief  Set Channel priority level.
  * @rmtoll CCR          PL            LL_DMA_SetChannelPriorityLevel
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @param  Priority This parameter can be one of the following values:
  *         @arg @ref LL_DMA_PRIORITY_0
  *         @arg @ref LL_DMA_PRIORITY_1
  *         @arg @ref LL_DMA_PRIORITY_2
  * @retval None
  */
__STATIC_INLINE void LL_DMA_SetChannelPriorityLevel(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Priority)
{
  MODIFY_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_PL,
             Priority);
}

/**
  * @brief  Get Channel priority level.
  * @rmtoll CCR          PL            LL_DMA_GetChannelPriorityLevel
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_PRIORITY_0
  *         @arg @ref LL_DMA_PRIORITY_1
  *         @arg @ref LL_DMA_PRIORITY_2
  */
__STATIC_INLINE uint32_t LL_DMA_GetChannelPriorityLevel(DMA_TypeDef *DMAx, uint32_t Channel)
{
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
                   DMA_CCR_PL));
}

/**
  * @brief  Set block length.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @param  BlockLength Between Min_Data = 0 and Max_Data = 0x0000FFFF
  * @retval None
  */
__STATIC_INLINE void LL_DMA_SetBlockLength(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t BlockLength)
{
  MODIFY_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CNDTR,
             DMA_CNDTR_NDT, BlockLength);
}

/**
  * @brief  Get block length.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval Between Min_Data = 0 and Max_Data = 0x0000FFFF
  */
__STATIC_INLINE uint32_t LL_DMA_GetBlockLength(DMA_TypeDef *DMAx, uint32_t Channel)
{
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CNDTR,
                   DMA_CNDTR_NDT));
}

/**
  * @brief  Set number of blocks.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @param  BlockNum Between Min_Data = 0 and Max_Data = 0x000000FF
  * @retval None
  */
__STATIC_INLINE void LL_DMA_SetBlockNum(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t BlockNum)
{
  MODIFY_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCCFGR,
             DMA_CCCFGR_NBT, BlockNum);
}

/**
  * @brief  Get number of blocks.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval Between Min_Data = 0 and Max_Data = 0x000000FF
  */
__STATIC_INLINE uint32_t LL_DMA_GetBlockNum(DMA_TypeDef *DMAx, uint32_t Channel)
{
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCCFGR,
                   DMA_CCCFGR_NBT));
}

/**
  * @brief  Set length of last block data transfers in finite cycle mode.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @param  RemainLength Between Min_Data = 0 and Max_Data = 0x0000FFFF
  * @retval None
  */
__STATIC_INLINE void LL_DMA_SetRemainLength(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t RemainLength)
{
  MODIFY_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCCFGR,
             DMA_CCCFGR_NDTL, RemainLength << DMA_CCCFGR_NDTL_Pos);
}

/**
  * @brief  Get length of last block data transfers in finite cycle mode.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval Between Min_Data = 0 and Max_Data = 0x0000FFFF
  */
__STATIC_INLINE uint32_t LL_DMA_GetRemainLength(DMA_TypeDef *DMAx, uint32_t Channel)
{
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCCFGR,
                   DMA_CCCFGR_NDTL) >> DMA_CCCFGR_NDTL_Pos);
}

/**
  * @brief  Configure the Source and Destination addresses.
  * @note   This API must not be called when the DMA channel is enabled.
  * @note   Each IP using DMA provides an API to get directly the register adress (LL_PPP_DMA_GetRegAddr).
  * @rmtoll CPAR         PA            LL_DMA_ConfigAddresses\n
  *         CMAR         MA            LL_DMA_ConfigAddresses
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @param  SrcAddress Between Min_Data = 0 and Max_Data = 0xFFFFFFFF
  * @param  DstAddress Between Min_Data = 0 and Max_Data = 0xFFFFFFFF
  * @param  Direction This parameter can be one of the following values:
  *         @arg @ref LL_DMA_DIRECTION_PERIPH_TO_MEMORY
  *         @arg @ref LL_DMA_DIRECTION_MEMORY_TO_PERIPH
  *         @arg @ref LL_DMA_DIRECTION_MEMORY_TO_MEMORY
  * @retval None
  */
__STATIC_INLINE void LL_DMA_ConfigAddresses(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t SrcAddress,
                                            uint32_t DstAddress, uint32_t Direction)
{
  /* Direction Memory to Periph */
  if (Direction == LL_DMA_DIRECTION_MEMORY_TO_PERIPH)
  {
    WRITE_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CMAR, SrcAddress);
    WRITE_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CPAR, DstAddress);
  }
  /* Direction Periph to Memory and Memory to Memory */
  else
  {
    WRITE_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CPAR, SrcAddress);
    WRITE_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CMAR, DstAddress);
  }
}

/**
  * @brief  Set the Memory address.
  * @note   Interface used for direction LL_DMA_DIRECTION_PERIPH_TO_MEMORY or LL_DMA_DIRECTION_MEMORY_TO_PERIPH only.
  * @note   This API must not be called when the DMA channel is enabled.
  * @rmtoll CMAR         MA            LL_DMA_SetMemoryAddress
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @param  MemoryAddress Between Min_Data = 0 and Max_Data = 0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void LL_DMA_SetMemoryAddress(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t MemoryAddress)
{
  WRITE_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CMAR, MemoryAddress);
}

/**
  * @brief  Set the Peripheral address.
  * @note   Interface used for direction LL_DMA_DIRECTION_PERIPH_TO_MEMORY or LL_DMA_DIRECTION_MEMORY_TO_PERIPH only.
  * @note   This API must not be called when the DMA channel is enabled.
  * @rmtoll CPAR         PA            LL_DMA_SetPeriphAddress
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @param  PeriphAddress Between Min_Data = 0 and Max_Data = 0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void LL_DMA_SetPeriphAddress(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t PeriphAddress)
{
  WRITE_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CPAR, PeriphAddress);
}

/**
  * @brief  Get Memory address.
  * @note   Interface used for direction LL_DMA_DIRECTION_PERIPH_TO_MEMORY or LL_DMA_DIRECTION_MEMORY_TO_PERIPH only.
  * @rmtoll CMAR         MA            LL_DMA_GetMemoryAddress
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval Between Min_Data = 0 and Max_Data = 0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_DMA_GetMemoryAddress(DMA_TypeDef *DMAx, uint32_t Channel)
{
  return (READ_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CMAR));
}

/**
  * @brief  Get Peripheral address.
  * @note   Interface used for direction LL_DMA_DIRECTION_PERIPH_TO_MEMORY or LL_DMA_DIRECTION_MEMORY_TO_PERIPH only.
  * @rmtoll CPAR         PA            LL_DMA_GetPeriphAddress
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval Between Min_Data = 0 and Max_Data = 0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_DMA_GetPeriphAddress(DMA_TypeDef *DMAx, uint32_t Channel)
{
  return (READ_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CPAR));
}

/**
  * @brief  Set the Memory to Memory Source address.
  * @note   Interface used for direction LL_DMA_DIRECTION_MEMORY_TO_MEMORY only.
  * @note   This API must not be called when the DMA channel is enabled.
  * @rmtoll CPAR         PA            LL_DMA_SetM2MSrcAddress
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @param  MemoryAddress Between Min_Data = 0 and Max_Data = 0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void LL_DMA_SetM2MSrcAddress(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t MemoryAddress)
{
  WRITE_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CPAR, MemoryAddress);
}

/**
  * @brief  Set the Memory to Memory Destination address.
  * @note   Interface used for direction LL_DMA_DIRECTION_MEMORY_TO_MEMORY only.
  * @note   This API must not be called when the DMA channel is enabled.
  * @rmtoll CMAR         MA            LL_DMA_SetM2MDstAddress
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @param  MemoryAddress Between Min_Data = 0 and Max_Data = 0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void LL_DMA_SetM2MDstAddress(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t MemoryAddress)
{
  WRITE_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CMAR, MemoryAddress);
}

/**
  * @brief  Get the Memory to Memory Source address.
  * @note   Interface used for direction LL_DMA_DIRECTION_MEMORY_TO_MEMORY only.
  * @rmtoll CPAR         PA            LL_DMA_GetM2MSrcAddress
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval Between Min_Data = 0 and Max_Data = 0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_DMA_GetM2MSrcAddress(DMA_TypeDef *DMAx, uint32_t Channel)
{
  return (READ_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CPAR));
}

/**
  * @brief  Get the Memory to Memory Destination address.
  * @note   Interface used for direction LL_DMA_DIRECTION_MEMORY_TO_MEMORY only.
  * @rmtoll CMAR         MA            LL_DMA_GetM2MDstAddress
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval Between Min_Data = 0 and Max_Data = 0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_DMA_GetM2MDstAddress(DMA_TypeDef *DMAx, uint32_t Channel)
{
  return (READ_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CMAR));
}

/**
  * @brief  Enable DMA peripheral address reload.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval None
  */
__STATIC_INLINE void LL_DMA_EnablePeriphAddressReload(DMA_TypeDef *DMAx, uint32_t Channel)
{
  CLEAR_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_PNORLD);
}

/**
  * @brief  Disable DMA peripheral address reload.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval None
  */
__STATIC_INLINE void LL_DMA_DisablePeriphAddressReload(DMA_TypeDef *DMAx, uint32_t Channel)
{
  SET_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_PNORLD);
}

/**
  * @brief  Check if DMA peripheral address reload.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledPeriphAddressReload(DMA_TypeDef *DMAx, uint32_t Channel)
{
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
                   DMA_CCR_PNORLD) == 0x0);
}

/**
  * @brief  Enable DMA Memory address reload.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval None
  */
__STATIC_INLINE void LL_DMA_EnableMemoryAddressReload(DMA_TypeDef *DMAx, uint32_t Channel)
{
  CLEAR_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_MNORLD);
}

/**
  * @brief  Disable DMA Memory address reload.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval None
  */
__STATIC_INLINE void LL_DMA_DisableMemoryAddressReload(DMA_TypeDef *DMAx, uint32_t Channel)
{
  SET_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_MNORLD);
}

/**
  * @brief  Check if DMA Memory address reload.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledMemoryAddressReload(DMA_TypeDef *DMAx, uint32_t Channel)
{
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
                   DMA_CCR_MNORLD) == 0x0);
}

/**
  * @brief  Set DMA transfer mode.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref LL_DMA_TRANSFER_SINGLE
  *         @arg @ref LL_DMA_TRANSFER_BULK  
  * @retval None
  */
__STATIC_INLINE void LL_DMA_SetTransferMode(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Mode)
{
  MODIFY_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_TRANST,
              Mode);
}

/**
  * @brief  Get DMA transfer mode.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_TRANSFER_SINGLE
  *         @arg @ref LL_DMA_TRANSFER_BULK  
  */
__STATIC_INLINE uint32_t LL_DMA_GetTransferMode(DMA_TypeDef *DMAx, uint32_t Channel)
{
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
                   DMA_CCR_TRANST));
}

/**
  * @brief  Set DMA arbitration mode.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref LL_DMA_ARB_FAST
  *         @arg @ref LL_DMA_ARB_POLL
  * @retval None
  */
__STATIC_INLINE void LL_DMA_SetArbMode(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Mode)
{
  MODIFY_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_M2MARB,
              Mode);
}

/**
  * @brief  Get DMA arbitration mode.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_ARB_FAST
  *         @arg @ref LL_DMA_ARB_POLL
  */
__STATIC_INLINE uint32_t LL_DMA_GetArbMode(DMA_TypeDef *DMAx, uint32_t Channel)
{
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
                   DMA_CCR_M2MARB));
}

/**
  * @brief  Enable suspend transfer after block transfer completion interrupt.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval None
  */
__STATIC_INLINE void LL_DMA_EnableBTCSuspend(DMA_TypeDef *DMAx, uint32_t Channel)
{
  SET_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_BTCSUSP);
}

/**
  * @brief  Disable suspend transfer after block transfer completion interrupt.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval None
  */
__STATIC_INLINE void LL_DMA_DisableBTCSuspend(DMA_TypeDef *DMAx, uint32_t Channel)
{
  CLEAR_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_BTCSUSP);
}

/**
  * @brief  Check if suspend transfer after block transfer completion interrupt.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledBTCSuspend(DMA_TypeDef *DMAx, uint32_t Channel)
{
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
                   DMA_CCR_BTCSUSP) == (DMA_CCR_BTCSUSP));
}

/**
  * @}
  */

/** @defgroup DMA_LL_EF_FLAG_Management FLAG Management
  * @{
  */

/**
  * @brief  Get Channel 1 transfer complete flag.
  * @rmtoll ISR          TCIF1         LL_DMA_IsActiveFlag_TC1
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_TC1(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->ISR, DMA_ISR_TCIF1) == (DMA_ISR_TCIF1));
}

/**
  * @brief  Get Channel 2 transfer complete flag.
  * @rmtoll ISR          TCIF2         LL_DMA_IsActiveFlag_TC2
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_TC2(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->ISR, DMA_ISR_TCIF2) == (DMA_ISR_TCIF2));
}

/**
  * @brief  Get Channel 3 transfer complete flag.
  * @rmtoll ISR          TCIF3         LL_DMA_IsActiveFlag_TC3
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_TC3(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->ISR, DMA_ISR_TCIF3) == (DMA_ISR_TCIF3));
}

/**
  * @brief  Get Channel 1 block transfer complete flag.
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_BTC1(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->ISR, DMA_ISR_BTCIF1) == (DMA_ISR_BTCIF1));
}

/**
  * @brief  Get Channel 2 block transfer complete flag.
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_BTC2(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->ISR, DMA_ISR_BTCIF2) == (DMA_ISR_BTCIF2));
}

/**
  * @brief  Get Channel 3 block transfer complete flag.
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_BTC3(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->ISR, DMA_ISR_BTCIF3) == (DMA_ISR_BTCIF3));
}


/**
  * @brief  Get Channel 1 block half transfer flag.
  * @rmtoll ISR          HBTIF1         LL_DMA_IsActiveFlag_HBT1
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_HBT1(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->ISR, DMA_ISR_HBTIF1) == (DMA_ISR_HBTIF1));
}

/**
  * @brief  Get Channel 2 block half transfer flag.
  * @rmtoll ISR          HBTIF2         LL_DMA_IsActiveFlag_HBT2
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_HBT2(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->ISR, DMA_ISR_HBTIF2) == (DMA_ISR_HBTIF2));
}

/**
  * @brief  Get Channel 3 block half transfer flag.
  * @rmtoll ISR          HBTIF3         LL_DMA_IsActiveFlag_HBT3
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_HBT3(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->ISR, DMA_ISR_HBTIF3) == (DMA_ISR_HBTIF3));
}

/**
  * @brief  Get Channel 1 transfer error flag.
  * @rmtoll ISR          TEIF1         LL_DMA_IsActiveFlag_TE1
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_TE1(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->ISR, DMA_ISR_TEIF1) == (DMA_ISR_TEIF1));
}

/**
  * @brief  Get Channel 2 transfer error flag.
  * @rmtoll ISR          TEIF2         LL_DMA_IsActiveFlag_TE2
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_TE2(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->ISR, DMA_ISR_TEIF2) == (DMA_ISR_TEIF2));
}

/**
  * @brief  Get Channel 3 transfer error flag.
  * @rmtoll ISR          TEIF3         LL_DMA_IsActiveFlag_TE3
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_TE3(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->ISR, DMA_ISR_TEIF3) == (DMA_ISR_TEIF3));
}


/**
  * @brief  Clear Channel 1  transfer complete flag.
  * @rmtoll IFCR         CTCIF1        LL_DMA_ClearFlag_TC1
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void LL_DMA_ClearFlag_TC1(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CTCIF1);
}

/**
  * @brief  Clear Channel 2  transfer complete flag.
  * @rmtoll IFCR         CTCIF2        LL_DMA_ClearFlag_TC2
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void LL_DMA_ClearFlag_TC2(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CTCIF2);
}

/**
  * @brief  Clear Channel 3  transfer complete flag.
  * @rmtoll IFCR         CTCIF3        LL_DMA_ClearFlag_TC3
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void LL_DMA_ClearFlag_TC3(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CTCIF3);
}

/**
  * @brief  Clear Channel 1 block transfer complete flag.
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void LL_DMA_ClearFlag_BTC1(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CBTCIF1);
}

/**
  * @brief  Clear Channel 2 block transfer complete flag.
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void LL_DMA_ClearFlag_BTC2(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CBTCIF2);
}

/**
  * @brief  Clear Channel 3 block transfer complete flag.
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void LL_DMA_ClearFlag_BTC3(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CBTCIF3);
}

/**
  * @brief  Clear Channel 1 block half transfer flag.
  * @rmtoll IFCR         CHBTIF1        LL_DMA_ClearFlag_HBT1
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void LL_DMA_ClearFlag_HBT1(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CHBTIF1);
}

/**
  * @brief  Clear Channel 2 block half transfer flag.
  * @rmtoll IFCR         CHBTIF2        LL_DMA_ClearFlag_HBT2
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void LL_DMA_ClearFlag_HBT2(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CHBTIF2);
}

/**
  * @brief  Clear Channel 3 block half transfer flag.
  * @rmtoll IFCR         CHBTIF3        LL_DMA_ClearFlag_HBT3
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void LL_DMA_ClearFlag_HBT3(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CHBTIF3);
}

/**
  * @brief  Clear Channel 1 transfer error flag.
  * @rmtoll IFCR         CTEIF1        LL_DMA_ClearFlag_TE1
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void LL_DMA_ClearFlag_TE1(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CTEIF1);
}

/**
  * @brief  Clear Channel 2 transfer error flag.
  * @rmtoll IFCR         CTEIF2        LL_DMA_ClearFlag_TE2
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void LL_DMA_ClearFlag_TE2(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CTEIF2);
}

/**
  * @brief  Clear Channel 3 transfer error flag.
  * @rmtoll IFCR         CTEIF3        LL_DMA_ClearFlag_TE3
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void LL_DMA_ClearFlag_TE3(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CTEIF3);
}

/**
  * @}
  */

/** @defgroup DMA_LL_EF_IT_Management IT Management
  * @{
  */

/**
  * @brief  Enable Transfer complete interrupt.
  * @rmtoll CCR          TCIE          LL_DMA_EnableIT_TC
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval None
  */
__STATIC_INLINE void LL_DMA_EnableIT_TC(DMA_TypeDef *DMAx, uint32_t Channel)
{
  SET_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_TCIE);
}

/**
  * @brief  Enable block transfer complete interrupt.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval None
  */
__STATIC_INLINE void LL_DMA_EnableIT_BTC(DMA_TypeDef *DMAx, uint32_t Channel)
{
  SET_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_BTCIE);
}

/**
  * @brief  Enable Half transfer interrupt.
  * @rmtoll CCR          HBTIE          LL_DMA_EnableIT_HBT
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval None
  */
__STATIC_INLINE void LL_DMA_EnableIT_HBT(DMA_TypeDef *DMAx, uint32_t Channel)
{
  SET_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_HBTIE);
}

/**
  * @brief  Enable Transfer error interrupt.
  * @rmtoll CCR          TEIE          LL_DMA_EnableIT_TE
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval None
  */
__STATIC_INLINE void LL_DMA_EnableIT_TE(DMA_TypeDef *DMAx, uint32_t Channel)
{
  SET_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_TEIE);
}

/**
  * @brief  Disable Transfer complete interrupt.
  * @rmtoll CCR          TCIE          LL_DMA_DisableIT_TC
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval None
  */
__STATIC_INLINE void LL_DMA_DisableIT_TC(DMA_TypeDef *DMAx, uint32_t Channel)
{
  CLEAR_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_TCIE);
}

/**
  * @brief  Disable Block Transfer complete interrupt.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval None
  */
__STATIC_INLINE void LL_DMA_DisableIT_BTC(DMA_TypeDef *DMAx, uint32_t Channel)
{
  CLEAR_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_BTCIE);
}

/**
  * @brief  Disable Block Half transfer interrupt.
  * @rmtoll CCR          HBTIE          LL_DMA_DisableIT_HBT
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval None
  */
__STATIC_INLINE void LL_DMA_DisableIT_HBT(DMA_TypeDef *DMAx, uint32_t Channel)
{
  CLEAR_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_HBTIE);
}

/**
  * @brief  Disable Transfer error interrupt.
  * @rmtoll CCR          TEIE          LL_DMA_DisableIT_TE
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval None
  */
__STATIC_INLINE void LL_DMA_DisableIT_TE(DMA_TypeDef *DMAx, uint32_t Channel)
{
  CLEAR_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_TEIE);
}

/**
  * @brief  Check if Transfer complete Interrupt is enabled.
  * @rmtoll CCR          TCIE          LL_DMA_IsEnabledIT_TC
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledIT_TC(DMA_TypeDef *DMAx, uint32_t Channel)
{
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
                   DMA_CCR_TCIE) == (DMA_CCR_TCIE));
}

/**
  * @brief  Check if block Transfer complete Interrupt is enabled.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledIT_BTC(DMA_TypeDef *DMAx, uint32_t Channel)
{
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
                   DMA_CCR_BTCIE) == (DMA_CCR_BTCIE));
}

/**
  * @brief  Check if Block Half transfer Interrupt is enabled.
  * @rmtoll CCR          HBTIE          LL_DMA_IsEnabledIT_HBT
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledIT_HBT(DMA_TypeDef *DMAx, uint32_t Channel)
{
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
                   DMA_CCR_HBTIE) == (DMA_CCR_HBTIE));
}

/**
  * @brief  Check if Transfer error Interrupt is enabled.
  * @rmtoll CCR          TEIE          LL_DMA_IsEnabledIT_TE
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledIT_TE(DMA_TypeDef *DMAx, uint32_t Channel)
{
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
                   DMA_CCR_TEIE) == (DMA_CCR_TEIE));
}

/**
  * @}
  */

/** @defgroup DMA_REMAP DMA Remap
  * @{
  */

/**
  * @brief  Set the DMA Remap
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @param  MapReqNum This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_DMA_MAP_ADC             
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI1_RX   
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI1_TX   
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI2_RX   
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI2_TX   
  *         @arg @ref LL_SYSCFG_DMA_MAP_USART1_RX 
  *         @arg @ref LL_SYSCFG_DMA_MAP_USART1_TX 
  *         @arg @ref LL_SYSCFG_DMA_MAP_UART1_RX  
  *         @arg @ref LL_SYSCFG_DMA_MAP_UART1_TX  
  *         @arg @ref LL_SYSCFG_DMA_MAP_LPUART1_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_LPUART1_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_I2C1_RX   
  *         @arg @ref LL_SYSCFG_DMA_MAP_I2C1_TX    
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH1  
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH2  
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH3  
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH4  
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_COM  
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_TRG  
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_UP   
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_CH1  
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_CH2  
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_CH3  
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_CH4  
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_UP   
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_TRG  
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM16_CH1 
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM16_UP  
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM17_CH1 
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM17_UP  
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetDMARemap(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t MapReqNum)
{
  uint32_t position;
  uint32_t channelmapmsk;

  channelmapmsk = 0x3F;

  position = ((uint32_t)Channel - (uint32_t)LL_DMA_CHANNEL_1) / ((uint32_t)LL_DMA_CHANNEL_2 - (uint32_t)LL_DMA_CHANNEL_1);
  
  MODIFY_REG(SYSCFG->CFGR3, (channelmapmsk << (8U * (position & 0x03U))), (MapReqNum << (8U * (position & 0x03U))));
}

/**
  * @brief  Get the DMA Remap
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  * @return  MapReqNum This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_DMA_MAP_ADC            
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI1_RX   
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI1_TX   
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI2_RX   
  *         @arg @ref LL_SYSCFG_DMA_MAP_SPI2_TX   
  *         @arg @ref LL_SYSCFG_DMA_MAP_USART1_RX 
  *         @arg @ref LL_SYSCFG_DMA_MAP_USART1_TX 
  *         @arg @ref LL_SYSCFG_DMA_MAP_UART1_RX  
  *         @arg @ref LL_SYSCFG_DMA_MAP_UART1_TX  
  *         @arg @ref LL_SYSCFG_DMA_MAP_LPUART1_RX
  *         @arg @ref LL_SYSCFG_DMA_MAP_LPUART1_TX
  *         @arg @ref LL_SYSCFG_DMA_MAP_I2C1_RX   
  *         @arg @ref LL_SYSCFG_DMA_MAP_I2C1_TX      
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH1  
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH2  
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH3  
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_CH4  
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_COM  
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_TRG  
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM1_UP    
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_CH1  
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_CH2  
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_CH3  
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_CH4  
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_UP   
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM3_TRG  
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM16_CH1 
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM16_UP  
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM17_CH1 
  *         @arg @ref LL_SYSCFG_DMA_MAP_TIM17_UP
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetDMARemap(DMA_TypeDef *DMAx,uint32_t Channel)
{
  uint32_t position;
  uint32_t channelmapmsk;

  channelmapmsk = 0x3F;

  position = ((uint32_t)Channel - (uint32_t)LL_DMA_CHANNEL_1) / ((uint32_t)LL_DMA_CHANNEL_2 - (uint32_t)LL_DMA_CHANNEL_1);
  
  return (READ_BIT(SYSCFG->CFGR3, (channelmapmsk << (8U * (position & 0x03U)))) >> (8U * (position & 0x03U)));
}

/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup DMA_LL_EF_Init Initialization and de-initialization functions
  * @{
  */

uint32_t LL_DMA_Init(DMA_TypeDef *DMAx, uint32_t Channel, LL_DMA_InitTypeDef *DMA_InitStruct);
uint32_t LL_DMA_DeInit(DMA_TypeDef *DMAx, uint32_t Channel);
void LL_DMA_StructInit(LL_DMA_InitTypeDef *DMA_InitStruct);

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

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

#ifdef __cplusplus
}
#endif

#endif /* __PY32F032_LL_DMA_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
