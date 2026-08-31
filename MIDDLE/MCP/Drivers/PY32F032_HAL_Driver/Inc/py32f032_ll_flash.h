/**
  ******************************************************************************
  * @file    py32f032_ll_flash.h
  * @author  MCU Application Team
  * @brief   Header file of FLASH LL module.
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
#ifndef PY32F032_LL_FLASH_H
#define PY32F032_LL_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f0xx.h"



/** @addtogroup PY32F032_LL_Driver
  * @{
  */

#if defined (FLASH)

/** @defgroup FLASH_LL FLASH
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup FLASH_LL_Exported_Constants FLASH Exported Constants
  * @{
  */
 /** @defgroup FLASH_LL_EC_USERSTYPE FLASH Users Type
  * @{
  */
#define LL_FLASH_OPTR_RDP            FLASH_OPTR_RDP
#define LL_FLASH_OPTR_NRST_MODE      FLASH_OPTR_NRST_MODE
#define LL_FLASH_OPTR_IWDG_STOP      FLASH_OPTR_IWDG_STOP
#define LL_FLASH_OPTR_IWDG_SW        FLASH_OPTR_IWDG_SW
#define LL_FLASH_OPTR_WWDG_SW        FLASH_OPTR_WWDG_SW
#define LL_FLASH_OPTR_nBOOT1         FLASH_OPTR_NRST_STOP
#define LL_FLASH_OPTR_BOOT_LOCK      FLASH_OPTR_BOOT_LOCK
#define LL_FLASH_OPTR_BOR_LEVEL      FLASH_OPTR_BOR_OPCR  
#define LL_FLASH_OPTR_BOR_ENABLE     FLASH_OPTR_BOR_EN  
#define LL_FLASH_OPTR_SWD_MODE       FLASH_OPTR_SWD_MODE 
/**
  * @}
  */


/** @defgroup FLASH_LL_EC_BOOT_LOCK BOOT Lock
  * @{
  */
#define LL_FLASH_BOOT_FROM_OB                     0x00000000U             /*!< BOOT from IO or OB */
#define LL_FLASH_BOOT_FROM_MAINFLASH              (FLASH_OPTR_BOOT_LOCK)  /*!< BOOT from MainFlash */
/**
  * @}
  */

/** @defgroup FLASH_LL_EC_SWDMODE SWD Mode
  * @{
  */
#define LL_FLASH_SWDIO_PA13_SWCLK_PA14     (0x00000000U)                                         /*!< SWDIO: PA13 SWCLK: PA14 */
#define LL_FLASH_SWDIO_PF1_SWCLK_PF0       (FLASH_OPTR_SWD_MODE_0)                               /*!< SWDIO: PF1 SWCLK: PF0 */
#define LL_FLASH_SWDIO_PF1_SWCLK_PA14      (FLASH_OPTR_SWD_MODE_1)                               /*!< SWDIO: PF1 SWCLK: PA14 */
#define LL_FLASH_SWDIO_PA13_SWCLK_PF0      (FLASH_OPTR_SWD_MODE_0 | FLASH_OPTR_SWD_MODE_1)       /*!< SWDIO: PA13 SWCLK: PF0 */

/**
  * @}
  */

/** @defgroup FLASH_LL_EC_BORLevel BOR Level
  * @{
  */
#define LL_FLASH_BOR_LEV0          (0x00000000U)                                                            /*!< BOR Level 0 */
#define LL_FLASH_BOR_LEV1          (FLASH_OPTR_BOR_OPCR_0)                                                  /*!< BOR Level 1 */
#define LL_FLASH_BOR_LEV2          (FLASH_OPTR_BOR_OPCR_1)                                                  /*!< BOR Level 2 */
#define LL_FLASH_BOR_LEV3          (FLASH_OPTR_BOR_OPCR_1 | FLASH_OPTR_BOR_OPCR_0)                          /*!< BOR Level 3 */
#define LL_FLASH_BOR_LEV4          (FLASH_OPTR_BOR_OPCR_2)                                                  /*!< BOR Level 4 */
#define LL_FLASH_BOR_LEV5          (FLASH_OPTR_BOR_OPCR_2 | FLASH_OPTR_BOR_OPCR_0)                          /*!< BOR Level 5 */
#define LL_FLASH_BOR_LEV6          (FLASH_OPTR_BOR_OPCR_2 | FLASH_OPTR_BOR_OPCR_1)                          /*!< BOR Level 6 */
#define LL_FLASH_BOR_LEV7          (FLASH_OPTR_BOR_OPCR_2 | FLASH_OPTR_BOR_OPCR_1 | FLASH_OPTR_BOR_OPCR_0)  /*!< BOR Level 7 */
/**
  * @}
  */

/** @defgroup FLASH_LL_EC_BOREnable BOR Enable
  * @{
  */
#define LL_FLASH_BOR_DISABLE          (0x00000000U)                                        /*!< BOR Disable */
#define LL_FLASH_BOR_ENABLE           (FLASH_OPTR_BOR_EN)                                  /*!< BOR Enable */
/**
  * @}
  */

/** @defgroup FLASH_LL_NBOOT1 FLASH Option Bytes User nBOOT1 Type
  * @{
  */
#define LL_FLASH_NBOOT1_SRAM                   0x00000000U                  /*!< Embedded SRAM1 is selected as boot space (if BOOT0=1) */
#define LL_FLASH_NBOOT1_SYSTEM                 (FLASH_OPTR_NBOOT1)          /*!< System memory is selected as boot space (if BOOT0=1) */
/**
  * @}
  */

/** @defgroup FLASH_LL_EC_NRSTMODE NRST Mode
  * @{
  */
#define LL_FLASH_NRST_MODE_RESET          (0x00000000U)                     /*!< NRST Mode Reset */
#define LL_FLASH_NRST_MODE_GPIO           (FLASH_OPTR_NRST_MODE)            /*!< NRST Mode Gpio */
/**
  * @}
  */

/** @defgroup FLASH_LL_EC_WWDGMODE WWDG Mode
  * @{
  */
#define LL_FLASH_WWDG_MODE_HW          (0x00000000U)                        /*!< Hardware WWDG selected */
#define LL_FLASH_WWDG_MODE_SW          (FLASH_OPTR_WWDG_SW)                 /*!< Software WWDG selected */
/**
  * @}
  */

/** @defgroup FLASH_LL_EC_IWDGMODE IWDG Mode
  * @{
  */
#define LL_FLASH_IWDG_MODE_HW          (0x00000000U)                        /*!< Hardware IWDG selected */
#define LL_FLASH_IWDG_MODE_SW          (FLASH_OPTR_IWDG_SW)                 /*!< Software IWDG selected */
/**
  * @}
  */
 
/** @defgroup FLASH_OB_USER_IWDG_STOP FLASH Option Bytes User IWDG Mode On Stop
  * @{
  */
#define LL_FLASH_IWDG_INSTOP_FREEZE             0x00000000U                 /*!< Independent watchdog counter is frozen in Stop mode */
#define LL_FLASH_IWDG_INSTOP_ACTIVE             FLASH_OPTR_IWDG_STOP        /*!< Independent watchdog counter is running in Stop mode */
/**
  * @}
  */

/** @defgroup FLASH_LL_EC_RDP RDP Mode
  * @{
  */
#define LL_FLASH_RDP_LEVEL_0         ((uint8_t)0xAAU)
#define LL_FLASH_RDP_LEVEL_1         ((uint8_t)0x55U)
#define LL_FLASH_RDP_LEVEL_2         ((uint8_t)0xCCU)
/**
  * @}
  */


/** @defgroup FLASH_LL_EC_WRP Write Protection
  * @{
  */
#define LL_FLASH_WRP_DISABLE           ((uint32_t)0x00000000)   /* Write protection disable */
#define LL_FLASH_WRP_SECTOR_0          ((uint32_t)0x00000001)   /* Write protection of Bank0 Sector0 */
#define LL_FLASH_WRP_SECTOR_1          ((uint32_t)0x00000002)   /* Write protection of Bank0 Sector1 */
#define LL_FLASH_WRP_SECTOR_2          ((uint32_t)0x00000004)   /* Write protection of Bank0 Sector2 */
#define LL_FLASH_WRP_SECTOR_3          ((uint32_t)0x00000008)   /* Write protection of Bank0 Sector3 */
#define LL_FLASH_WRP_SECTOR_4          ((uint32_t)0x00000010)   /* Write protection of Bank0 Sector4 */
#define LL_FLASH_WRP_SECTOR_5          ((uint32_t)0x00000020)   /* Write protection of Bank0 Sector5 */
#define LL_FLASH_WRP_SECTOR_6          ((uint32_t)0x00000040)   /* Write protection of Bank0 Sector6 */
#define LL_FLASH_WRP_SECTOR_7          ((uint32_t)0x00000080)   /* Write protection of Bank0 Sector7 */
#define LL_FLASH_WRP_SECTOR_8          ((uint32_t)0x00000100)   /* Write protection of Bank0 Sector8 */
#define LL_FLASH_WRP_SECTOR_9          ((uint32_t)0x00000200)   /* Write protection of Bank0 Sector9 */
#define LL_FLASH_WRP_SECTOR_10         ((uint32_t)0x00000400)   /* Write protection of Bank0 Sector10 */
#define LL_FLASH_WRP_SECTOR_11         ((uint32_t)0x00000800)   /* Write protection of Bank0 Sector11 */
#define LL_FLASH_WRP_SECTOR_12         ((uint32_t)0x00001000)   /* Write protection of Bank0 Sector12 */
#define LL_FLASH_WRP_SECTOR_13         ((uint32_t)0x00002000)   /* Write protection of Bank0 Sector13 */
#define LL_FLASH_WRP_SECTOR_14         ((uint32_t)0x00004000)   /* Write protection of Bank0 Sector14 */
#define LL_FLASH_WRP_SECTOR_15         ((uint32_t)0x00008000)   /* Write protection of Bank0 Sector15 */

#define LL_FLASH_WRP_Pages0to31        ((uint32_t)LL_FLASH_WRP_SECTOR_0)   /* Write protection from bank0 page0   to page31 */
#define LL_FLASH_WRP_Pages32to63       ((uint32_t)LL_FLASH_WRP_SECTOR_1)   /* Write protection from bank0 page32  to page63 */
#define LL_FLASH_WRP_Pages64to95       ((uint32_t)LL_FLASH_WRP_SECTOR_2)   /* Write protection from bank0 page64  to page95 */
#define LL_FLASH_WRP_Pages96to127      ((uint32_t)LL_FLASH_WRP_SECTOR_3)   /* Write protection from bank0 page96  to page127 */
#define LL_FLASH_WRP_Pages128to159     ((uint32_t)LL_FLASH_WRP_SECTOR_4)   /* Write protection from bank0 page128 to page159 */
#define LL_FLASH_WRP_Pages160to191     ((uint32_t)LL_FLASH_WRP_SECTOR_5)   /* Write protection from bank0 page160 to page191 */
#define LL_FLASH_WRP_Pages192to223     ((uint32_t)LL_FLASH_WRP_SECTOR_6)   /* Write protection from bank0 page192 to page223 */
#define LL_FLASH_WRP_Pages224to255     ((uint32_t)LL_FLASH_WRP_SECTOR_7)   /* Write protection from bank0 page224 to page255 */
#define LL_FLASH_WRP_Pages256to287     ((uint32_t)LL_FLASH_WRP_SECTOR_8)   /* Write protection from bank0 page256 to page287 */
#define LL_FLASH_WRP_Pages288to319     ((uint32_t)LL_FLASH_WRP_SECTOR_9)   /* Write protection from bank0 page288 to page319 */
#define LL_FLASH_WRP_Pages320to351     ((uint32_t)LL_FLASH_WRP_SECTOR_10)  /* Write protection from bank0 page320 to page351 */
#define LL_FLASH_WRP_Pages352to383     ((uint32_t)LL_FLASH_WRP_SECTOR_11)  /* Write protection from bank0 page352 to page383 */
#define LL_FLASH_WRP_Pages384to415     ((uint32_t)LL_FLASH_WRP_SECTOR_12)  /* Write protection from bank0 page384 to page415 */
#define LL_FLASH_WRP_Pages416to447     ((uint32_t)LL_FLASH_WRP_SECTOR_13)  /* Write protection from bank0 page416 to page447 */
#define LL_FLASH_WRP_Pages448to479     ((uint32_t)LL_FLASH_WRP_SECTOR_14)  /* Write protection from bank0 page448 to page479 */
#define LL_FLASH_WRP_Pages480to511     ((uint32_t)LL_FLASH_WRP_SECTOR_15)  /* Write protection from bank0 page480 to page511 */


#define LL_FLASH_WRP_AllPages          ((uint32_t)0xFFFFU)      /*!< Write protection of all Sectors */
/**
  * @}
  */

/** @defgroup FLASH_LL_EnterLpmodeDelay FLASH Enter LpMode Delay Time 
  * @{
  */
#define LL_FLASH_ENTERLPMODEDELAY_1HSIDIVCLOCK         (FLASH_LPCR_LPRUN_ENTERT_0)
#define LL_FLASH_ENTERLPMODEDELAY_2HSIDIVCLOCK         (FLASH_LPCR_LPRUN_ENTERT_1)
#define LL_FLASH_ENTERLPMODEDELAY_3HSIDIVCLOCK         (FLASH_LPCR_LPRUN_ENTERT_1 | FLASH_LPCR_LPRUN_ENTERT_0)
#define LL_FLASH_ENTERLPMODEDELAY_4HSIDIVCLOCK         (FLASH_LPCR_LPRUN_ENTERT_2)
#define LL_FLASH_ENTERLPMODEDELAY_5HSIDIVCLOCK         (FLASH_LPCR_LPRUN_ENTERT_2 | FLASH_LPCR_LPRUN_ENTERT_0)
#define LL_FLASH_ENTERLPMODEDELAY_6HSIDIVCLOCK         (FLASH_LPCR_LPRUN_ENTERT_2 | FLASH_LPCR_LPRUN_ENTERT_1)
#define LL_FLASH_ENTERLPMODEDELAY_7HSIDIVCLOCK         (FLASH_LPCR_LPRUN_ENTERT_2 | FLASH_LPCR_LPRUN_ENTERT_1 | FLASH_LPCR_LPRUN_ENTERT_0) 
/**
  * @}
  */

/** @defgroup FLASH_LL_ExitLpmodeDelay FLASH Exit LpMode Delay Time 
  * @{
  */
#define LL_FLASH_EXITLPMODEDELAY_1HSIDIVCLOCK         (FLASH_LPCR_LPRUN_EXITT_0)
#define LL_FLASH_EXITLPMODEDELAY_2HSIDIVCLOCK         (FLASH_LPCR_LPRUN_EXITT_1)
#define LL_FLASH_EXITLPMODEDELAY_3HSIDIVCLOCK         (FLASH_LPCR_LPRUN_EXITT_1 | FLASH_LPCR_LPRUN_EXITT_0)
#define LL_FLASH_EXITLPMODEDELAY_4HSIDIVCLOCK         (FLASH_LPCR_LPRUN_EXITT_2)
#define LL_FLASH_EXITLPMODEDELAY_5HSIDIVCLOCK         (FLASH_LPCR_LPRUN_EXITT_2 | FLASH_LPCR_LPRUN_EXITT_0)
#define LL_FLASH_EXITLPMODEDELAY_6HSIDIVCLOCK         (FLASH_LPCR_LPRUN_EXITT_2 | FLASH_LPCR_LPRUN_EXITT_1)
#define LL_FLASH_EXITLPMODEDELAY_7HSIDIVCLOCK         (FLASH_LPCR_LPRUN_EXITT_2 | FLASH_LPCR_LPRUN_EXITT_1 | FLASH_LPCR_LPRUN_EXITT_0) 
/**
  * @}
  */


/** @defgroup FLASH_LL_EC_KEY Key Value
  * @{
  */
#define LL_FLASH_KEY1                  (FLASH_KEY1)
#define LL_FLASH_KEY2                  (FLASH_KEY2)
/**
  * @}
  */

/** @defgroup FLASH_LL_EC_OPTKEY Optkey Value
  * @{
  */
#define LL_FLASH_OPTKEY1               (FLASH_OPTKEY1)
#define LL_FLASH_OPTKEY2               (FLASH_OPTKEY2)
/**
  * @}
  */
/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup FLASH_LL_Exported_Macros FLASH Exported Macros
  * @{
  */

/** @defgroup FLASH_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in FLASH register
  * @param  __INSTANCE__ FLASH Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_FLASH_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in FLASH register
  * @param  __INSTANCE__ FLASH Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_FLASH_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup FLASH_LL_Exported_Functions FLASH Exported Functions
  * @{
  */

/** @defgroup FLASH_LL_EF_FLAG_Management Flag Management
  * @{
  */

/**
  * @brief  Indicate the status of End of operation flag.
  * @rmtoll SR          EOP              LL_FLASH_IsActiveFlag_EOP
  * @param  FLASHx FLASH Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_EOP(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASHx->SR, FLASH_SR_EOP) == (FLASH_SR_EOP));
}

/**
  * @brief  Indicate the status of WRPERR flag.
  * @rmtoll SR          WPRERR           LL_FLASH_IsActiveFlag_WRPERR
  * @param  FLASHx FLASH Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_WRPERR(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASHx->SR, FLASH_SR_WRPERR) == (FLASH_SR_WRPERR));
}

/**
  * @brief  Indicate the status of RDERR flag.
  * @rmtoll SR          RDERR              LL_FLASH_IsActiveFlag_RDERR
  * @param  FLASHx FLASH Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_RDERR(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASHx->SR, FLASH_SR_RDERR) == (FLASH_SR_RDERR));
}

/**
  * @brief  Indicate the status of USERLOCK flag.
  * @rmtoll SR          USRLOCK              LL_FLASH_IsActiveFlag_USERLOCK
  * @param  FLASHx FLASH Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_USERLOCK(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASHx->SR, FLASH_SR_USERLOCK) == (FLASH_SR_USERLOCK));
}

/**
  * @brief  Indicate the status of OPTVERR flag.
  * @rmtoll SR          OPTVERR          LL_FLASH_IsActiveFlag_OPTVERR
  * @param  FLASHx FLASH Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_OPTVERR(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASHx->SR, FLASH_SR_OPTVERR) == (FLASH_SR_OPTVERR));
}

/**
  * @brief  Indicate the status of BUSY flag.
  * @rmtoll SR          BSY0              LL_FLASH_IsActiveFlag_BUSY
  * @param  FLASHx FLASH Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_BUSY(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASHx->SR, FLASH_SR_BSY) == (FLASH_SR_BSY));
}

/**
  * @brief  Clear End of operation flag.
  * @rmtoll SR          EOP              LL_FLASH_ClearFlag_EOP
  * @param  FLASHx FLASH Instance.
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_EOP(FLASH_TypeDef *FLASHx)
{
  WRITE_REG(FLASHx->SR, FLASH_SR_EOP);
}

/**
  * @brief  Clear WRPERR flag.
  * @rmtoll SR          WRPERR           LL_FLASH_ClearFlag_WRPERR
  * @param  FLASHx FLASH Instance.
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_WRPERR(FLASH_TypeDef *FLASHx)
{
  WRITE_REG(FLASHx->SR, FLASH_SR_WRPERR);
}

/**
  * @brief  Clear RDERR0 flag.
  * @rmtoll SR          RDERR           LL_FLASH_ClearFlag_RDERR
  * @param  FLASHx FLASH Instance.
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_RDERR(FLASH_TypeDef *FLASHx)
{
  WRITE_REG(FLASHx->SR, FLASH_SR_RDERR);
}

/**
  * @brief  Clear OPTVERR flag.
  * @rmtoll SR          OPTVERR          LL_FLASH_ClearFlag_OPTVERR
  * @param  FLASHx FLASH Instance.
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_OPTVERR(FLASH_TypeDef *FLASHx)
{
  WRITE_REG(FLASHx->SR, FLASH_SR_OPTVERR);
}

/**
  * @}
  */

/** @defgroup FLASH_LL_EF_ERASE_Management Erase Management
  * @{
  */

/**
  * @brief  Enable Page Program
  * @rmtoll CR          PG               LL_FLASH_EnablePageProgram
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnablePageProgram(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_PG);
}

/**
  * @brief  Enable Page Erase
  * @rmtoll CR          PER              LL_FLASH_EnablePageErase
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnablePageErase(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_PER);
}

/**
  * @brief  Enable Mass Erase 
  * @rmtoll CR          MER              LL_FLASH_EnableMassErase
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnableMassErase(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_MER);
}


/**
  * @brief  Enable User Data Program
  * @rmtoll CR          UPG              LL_FLASH_EnableUserDataProgram
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnableUserDataProgram(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_UPG);
}

/**
  * @brief  Enable User Data Erase
  * @rmtoll CR          UPER              LL_FLASH_EnableUserDataErase
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnableUserDataErase(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_UPER);
}

/**
  * @brief  Enable Sector Erase
  * @rmtoll CR          SER              LL_FLASH_EnableSectorErase
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnableSectorErase(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_SER);
}

/**
  * @brief  Disable Page Program
  * @rmtoll CR          PG               LL_FLASH_DisablePageProgram
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisablePageProgram(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CR, FLASH_CR_PG);
}

/**
  * @brief  Disable Page Erase
  * @rmtoll CR          PER              LL_FLASH_DisablePageErase
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisablePageErase(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CR, FLASH_CR_PER);
}

/**
  * @brief  Disable Mass Erase
  * @rmtoll CR          MER              LL_FLASH_DisableMassErase
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisableMassErase(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CR, FLASH_CR_MER);
}

/**
  * @brief  Disable UserData Program
  * @rmtoll CR          UPG              LL_FLASH_DisableUserDataProgram
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisableUserDataProgram(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CR, FLASH_CR_UPG);
}

/**
  * @brief  Disable UserData Erase
  * @rmtoll CR          UPER              LL_FLASH_DisableUserDataErase
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisableUserDataErase(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CR, FLASH_CR_UPER);
}

/**
  * @brief  Disable Sector Erase
  * @rmtoll CR          SER              LL_FLASH_DisableSectorErase
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisableSectorErase(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CR, FLASH_CR_SER);
}

/**
  * @brief  Check if Page Program is enabled
  * @rmtoll CR          PG               LL_FLASH_IsEnabledPageProgram
  * @param  FLASHx FLASH Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledPageProgram(FLASH_TypeDef *FLASHx)
{
  return ((READ_BIT(FLASHx->CR, FLASH_CR_PG) == (FLASH_CR_PG)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Page erase is enabled
  * @rmtoll CR          PER              LL_FLASH_IsEnabledPageErase
  * @param  FLASHx FLASH Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledPageErase(FLASH_TypeDef *FLASHx)
{
  return ((READ_BIT(FLASHx->CR, FLASH_CR_PER) == (FLASH_CR_PER)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Bank0 Mass erase is enabled
  * @rmtoll CR          MER0              LL_FLASH_IsEnabledMassEraseBank0
  * @param  FLASHx FLASH Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledMassErase(FLASH_TypeDef *FLASHx)
{
  return ((READ_BIT(FLASHx->CR, FLASH_CR_MER) == (FLASH_CR_MER)) ? 1UL : 0UL);
}


/**
  * @brief  Check if User Data Program is enabled
  * @rmtoll CR          UPG              LL_FLASH_IsEnabledUserDataProgram
  * @param  FLASHx FLASH Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledUserDataProgram(FLASH_TypeDef *FLASHx)
{
  return ((READ_BIT(FLASHx->CR, FLASH_CR_UPG) == (FLASH_CR_UPG)) ? 1UL : 0UL);
}

/**
  * @brief  Check if UserData erase is enabled
  * @rmtoll CR          UPER              LL_FLASH_IsEnabledUserDataErase
  * @param  FLASHx FLASH Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledUserDataErase(FLASH_TypeDef *FLASHx)
{
  return ((READ_BIT(FLASHx->CR, FLASH_CR_UPER) == (FLASH_CR_UPER)) ? 1UL : 0UL);
}


/**
  * @brief  Check if Sector Erase is enabled
  * @rmtoll CR          SER              LL_FLASH_IsEnabledSectorErase
  * @param  FLASHx FLASH Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledSectorErase(FLASH_TypeDef *FLASHx)
{
  return ((READ_BIT(FLASHx->CR, FLASH_CR_SER) == (FLASH_CR_SER)) ? 1UL : 0UL);
}

/**
  * @brief  Set the Erase Address
  * @rmtoll LL_FLASH_SetEraseAddress
  * @param  FLASHx FLASH Instance
  * @param  address Erase address
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetEraseAddress(FLASH_TypeDef *FLASHx,uint32_t address)
{
  *(__IO uint32_t *)(address) = 0xFFFFFFFF;
}

/**
  * @}
  */

/** @defgroup FLASH_LL_EF_Lock_Management Lock Management
  * @{
  */

/**
  * @brief Unlock the Flash
  * @rmtoll KEYR        KEYR             LL_FLASH_Unlock
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_Unlock(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->KEYR, LL_FLASH_KEY1);
  SET_BIT(FLASHx->KEYR, LL_FLASH_KEY2);
}

/**
  * @brief  Unlock the Option
  * @rmtoll OPTKEYR     OPTKEYR          LL_FLASH_OBUnlock
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_OBUnlock(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->OPTKEYR, LL_FLASH_OPTKEY1);
  SET_BIT(FLASHx->OPTKEYR, LL_FLASH_OPTKEY2);
}


/**
  * @brief  Lock the Flash
  * @rmtoll CR          LOCK             LL_FLASH_Lock
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_Lock(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_LOCK);
}

/**
  * @brief  Lock the Option
  * @rmtoll CR          OPTLOCK          LL_FLASH_OBLock
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_OBLock(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_OPTLOCK);
}

/**
  * @brief  Check if Flash is locked
  * @rmtoll CR          LOCK             LL_FLASH_IsLocked
  * @param  FLASHx FLASH Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsLocked(FLASH_TypeDef *FLASHx)
{
  return ((READ_BIT(FLASHx->CR, FLASH_CR_LOCK) == (FLASH_CR_LOCK)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Option is locked
  * @rmtoll CR          OPTLOCK          LL_FLASH_IsOBLocked
  * @param  FLASHx FLASH Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsOBLocked(FLASH_TypeDef *FLASHx)
{
  return ((READ_BIT(FLASHx->CR, FLASH_CR_OPTLOCK) == (FLASH_CR_OPTLOCK)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup FLASH_LL_EF_LAUNCH_Management Launch Management
  * @{
  */

/**
  * @brief  Force the Option byte loading
  * @rmtoll CR          OBL_LAUNCH       LL_FLASH_Launch
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_Launch(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_OBL_LAUNCH);
}

/**
  * @}
  */

/** @defgroup FLASH_LL_EF_IT_Management Interrupt Management
  * @{
  */

/**
  * @brief  Enable Error interrupts.
  * @rmtoll CR          ERRIR            LL_FLASH_EnableIT_ERR
  * @param  FLASHx FLASH Instance.
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnableIT_ERR(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_ERRIE);
}

/**
  * @brief  Enable End of operation interrupts.
  * @rmtoll CR          EOPIE            LL_FLASH_EnableIT_EOP
  * @param  FLASHx FLASH Instance.
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnableIT_EOP(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_EOPIE);
}


/**
  * @brief  Enable PCROP0 Read error interrupts.
  * @rmtoll CR          RDERRIE            LL_FLASH_EnableIT_RDERR
  * @param  FLASHx FLASH Instance.
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnableIT_RDERR(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_RDERRIE);
}

/**
  * @brief  Disable Error interrupts.
  * @rmtoll CR          ERRIE            LL_FLASH_DisableIT_ERR
  * @param  FLASHx FLASH Instance.
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisableIT_ERR(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CR, FLASH_CR_ERRIE);
}

/**
  * @brief  Disable End of operation interrupts.
  * @rmtoll CR          EOPIE            LL_FLASH_DisableIT_EOP
  * @param  FLASHx FLASH Instance.
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisableIT_EOP(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CR, FLASH_CR_EOPIE);
}

/**
  * @brief  Disable End of operation interrupts.
  * @rmtoll CR          RDERRIE            LL_FLASH_DisableIT_RDERR
  * @param  FLASHx FLASH Instance.
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisableIT_RDERR(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CR, FLASH_CR_RDERRIE);
}

/**
  * @brief  Check if Error interrupts are enabled or disabled.
  * @rmtoll CR          ERRIE            LL_FLASH_IsEnabledIT_ERR
  * @param  FLASHx FLASH Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_ERR(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASHx->CR, FLASH_CR_ERRIE) == (FLASH_CR_ERRIE));
}

/**
  * @brief  Check if End of operation interrupts are enabled or disabled.
  * @rmtoll CR          EOPIE            LL_FLASH_IsEnabledIT_EOP
  * @param  FLASHx FLASH Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_EOP(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASHx->CR, FLASH_CR_EOPIE) == (FLASH_CR_EOPIE));
}

/**
  * @brief  Check if PCROP0 Read error interrupts are enabled or disabled.
  * @rmtoll CR          RDERR0IE            LL_FLASH_IsEnabledIT_RDERR0
  * @param  FLASHx FLASH Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_RDERR(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASHx->CR, FLASH_CR_RDERRIE) == (FLASH_CR_RDERRIE));
}

/**
  * @}
  */

/** @defgroup FLASH_LL_EF_LPMODE Flash Lp Mode
  * @{
  */

/**
  * @brief  Set Flash Enter Lpmode Delay time
  * @rmtoll LPCR          LPRUN_ENTERT            LL_FLASH_SetEnterLpModeDelay
  * @param  FLASHx FLASH Instance.
  * @param  Flash_Delay The value be one of the follow:
  *           @arg LL_FLASH_ENTERLPMODEDELAY_1HSIDIVCLOCK: Wait 1 HSIDIV Clock
  *           @arg LL_FLASH_ENTERLPMODEDELAY_2HSIDIVCLOCK: Wait 2 HSIDIV Clock
  *           @arg LL_FLASH_ENTERLPMODEDELAY_3HSIDIVCLOCK: Wait 3 HSIDIV Clock
  *           @arg LL_FLASH_ENTERLPMODEDELAY_4HSIDIVCLOCK: Wait 4 HSIDIV Clock
  *           @arg LL_FLASH_ENTERLPMODEDELAY_5HSIDIVCLOCK: Wait 5 HSIDIV Clock
  *           @arg LL_FLASH_ENTERLPMODEDELAY_6HSIDIVCLOCK: Wait 6 HSIDIV Clock
  *           @arg LL_FLASH_ENTERLPMODEDELAY_7HSIDIVCLOCK: Wait 7 HSIDIV Clock
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetEnterLpModeDelay(FLASH_TypeDef *FLASHx,uint32_t Flash_Delay)
{
  MODIFY_REG(FLASHx->LPCR, FLASH_LPCR_LPRUN_ENTERT, Flash_Delay);
}

/**
  * @brief  Get Flash Enter Lpmode Delay time
  * @rmtoll LPCR          LPRUN_ENTERT            LL_FLASH_GetEnterLpModeDelay
  * @param  FLASHx FLASH Instance.
  * @retval  The value be one of the follow:
  *           @arg LL_FLASH_ENTERLPMODEDELAY_1HSIDIVCLOCK: Wait 1 HSIDIV Clock
  *           @arg LL_FLASH_ENTERLPMODEDELAY_2HSIDIVCLOCK: Wait 2 HSIDIV Clock
  *           @arg LL_FLASH_ENTERLPMODEDELAY_3HSIDIVCLOCK: Wait 3 HSIDIV Clock
  *           @arg LL_FLASH_ENTERLPMODEDELAY_4HSIDIVCLOCK: Wait 4 HSIDIV Clock
  *           @arg LL_FLASH_ENTERLPMODEDELAY_5HSIDIVCLOCK: Wait 5 HSIDIV Clock
  *           @arg LL_FLASH_ENTERLPMODEDELAY_6HSIDIVCLOCK: Wait 6 HSIDIV Clock
  *           @arg LL_FLASH_ENTERLPMODEDELAY_7HSIDIVCLOCK: Wait 7 HSIDIV Clock
  */
__STATIC_INLINE uint32_t LL_FLASH_GetEnterLpModeDelay(FLASH_TypeDef *FLASHx)
{
  return READ_BIT(FLASHx->LPCR, FLASH_LPCR_LPRUN_ENTERT);
}

/**
  * @brief  Set Flash Exit Lpmode Delay time
  * @rmtoll LPCR          LPRUN_EXITT            LL_FLASH_SetExitLpModeDelay
  * @param  FLASHx FLASH Instance.
  * @param  Flash_Delay The value be one of the follow:
  *           @arg LL_FLASH_EXITLPMODEDELAY_1HSIDIVCLOCK: Wait 1 HSIDIV Clock
  *           @arg LL_FLASH_EXITLPMODEDELAY_2HSIDIVCLOCK: Wait 2 HSIDIV Clock
  *           @arg LL_FLASH_EXITLPMODEDELAY_3HSIDIVCLOCK: Wait 3 HSIDIV Clock
  *           @arg LL_FLASH_EXITLPMODEDLEAY_4HSIDIVCLOCK: Wait 4 HSIDIV Clock
  *           @arg LL_FLASH_EXITLPMODEDELAY_5HSIDIVCLOCK: Wait 5 HSIDIV Clock
  *           @arg LL_FLASH_EXITLPMODEDELAY_6HSIDIVCLOCK: Wait 6 HSIDIV Clock
  *           @arg LL_FLASH_EXITLPMODEDELAY_7HSIDIVCLOCK: Wait 7 HSIDIV Clock
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetExitLpModeDelay(FLASH_TypeDef *FLASHx,uint32_t Flash_Delay)
{
  MODIFY_REG(FLASHx->LPCR, FLASH_LPCR_LPRUN_EXITT, Flash_Delay);
}

/**
  * @brief  Get Flash Exit Lpmode Delay time
  * @rmtoll LPCR          LPRUN_EXITT            LL_FLASH_GetExitLpModeDelay
  * @param  FLASHx FLASH Instance.
  * @retval  The value be one of the follow:
  *           @arg LL_FLASH_EXITLPMODEDELAY_1HSIDIVCLOCK: Wait 1 HSIDIV Clock
  *           @arg LL_FLASH_EXITLPMODEDELAY_2HSIDIVCLOCK: Wait 2 HSIDIV Clock
  *           @arg LL_FLASH_EXITLPMODEDELAY_3HSIDIVCLOCK: Wait 3 HSIDIV Clock
  *           @arg LL_FLASH_EXITLPMODEDELAY_4HSIDIVCLOCK: Wait 4 HSIDIV Clock
  *           @arg LL_FLASH_EXITLPMODEDELAY_5HSIDIVCLOCK: Wait 5 HSIDIV Clock
  *           @arg LL_FLASH_EXITLPMODEDELAY_6HSIDIVCLOCK: Wait 6 HSIDIV Clock
  *           @arg LL_FLASH_EXITLPMODEDELAY_7HSIDIVCLOCK: Wait 7 HSIDIV Clock
  */
__STATIC_INLINE uint32_t LL_FLASH_GetExitLpModeDelay(FLASH_TypeDef *FLASHx)
{
  return READ_BIT(FLASHx->LPCR, FLASH_LPCR_LPRUN_EXITT);
}

/**
  * @brief  Enable Flash Sleep
  * @rmtoll LPCR          SLEEP_EN            LL_FLASH_EnableFlashSleep
  * @param  FLASHx FLASH Instance.
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnableFlashSleep(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->LPCR, FLASH_LPCR_SLEEP_EN);
}

/**
  * @brief  Disable Flash Sleep
  * @rmtoll LPCR          SLEEP_EN            LL_FLASH_DisableFlashSleep
  * @param  FLASHx FLASH Instance.
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisableFlashSleep(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->LPCR, FLASH_LPCR_SLEEP_EN);
}

/**
  * @brief  Check if Flash sleep are enabled or disabled.
  * @rmtoll LPCR          SLEEP_EN            LL_FLASH_IsEnabledFlashSleep
  * @param  FLASHx FLASH Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledFlashSleep(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASHx->LPCR, FLASH_LPCR_SLEEP_EN) == (FLASH_LPCR_SLEEP_EN));
}

/**
  * @brief  Set Flash Sleep Time
  * @rmtoll LPCR          SLEEP_TIME            LL_FLASH_SetFlashSleepTime
  * @param  FLASHx FLASH Instance.
  * @param  Sleep_Time The value Sleep Time between Min_Data=0x00 and Max_Data=0xFF
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetFlashSleepTime(FLASH_TypeDef *FLASHx,uint32_t Sleep_Time)
{
  MODIFY_REG(FLASHx->LPCR, FLASH_LPCR_SLEEP_TIME, Sleep_Time << FLASH_LPCR_SLEEP_TIME_Pos);
}

/**
  * @brief  Get Flash Sleep Time
  * @rmtoll LPCR          SLEEP_TIME            LL_FLASH_GetFlashSleepTime
  * @param  FLASHx FLASH Instance.
  * @retval The value Sleep Time between Min_Data=0x00 and Max_Data=0xFF
  */
__STATIC_INLINE uint32_t LL_FLASH_GetFlashSleepTime(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASHx->LPCR, FLASH_LPCR_SLEEP_TIME)>>FLASH_LPCR_SLEEP_TIME_Pos);
}

/**
  * @}
  */

/** @defgroup FLASH_LL_EF_PROGRAM_Management Program Management
  * @{
  */

/**
  * @brief  Enable Page Program Start
  * @rmtoll CR          PGSTRT           LL_FLASH_EnablePageProgramStart
  * @param  FLASHx FLASH Instance
  * @retval None.
  */
__STATIC_INLINE void LL_FLASH_EnablePageProgramStart(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_PGSTRT);
}

/**
  * @brief  Enable Option Program Start
  * @rmtoll CR          OPTSTRT          LL_FLASH_EnableOptionProgramStart
  * @param  FLASHx FLASH Instance
  * @retval None.
  */
__STATIC_INLINE void LL_FLASH_EnableOptionProgramStart(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_OPTSTRT);
}

/**
  * @brief Disable Page Program start
  * @rmtoll CR          PGSTRT           LL_FLASH_DisablePageProgramStart
  * @param  FLASHx FLASH Instance
  * @retval None.
  */
__STATIC_INLINE void LL_FLASH_DisablePageProgramStart(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CR, FLASH_CR_PGSTRT);
}

/**
  * @brief  Disable Option Program start
  * @rmtoll CR          OPTSTRT          LL_FLASH_DisableOptionProgramStart
  * @param  FLASHx FLASH Instance
  * @retval None.
  */
__STATIC_INLINE void LL_FLASH_DisableOptionProgramStart(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CR, FLASH_CR_OPTSTRT);
}

/**
  * @brief  Check if Page Program start is enabled
  * @rmtoll CR          PGSTRT              LL_FLASH_IsEnabledPageProgramStart
  * @param  FLASHx FLASH Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledPageProgramStart(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASHx->CR, FLASH_CR_PGSTRT) == (FLASH_CR_PGSTRT));
}

/**
  * @brief  Check if Option program Start is enabled
  * @rmtoll CR          OPTSTRT         LL_FLASH_IsEnabledOptionProgramStart
  * @param  FLASHx FLASH Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledOptionProgramStart(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASHx->CR, FLASH_CR_OPTSTRT) == (FLASH_CR_OPTSTRT));
}

/**
  * @brief  Trigger the Option Program
  * @param  FLASHx FLASH Instance
  * @retval None.
  */
__STATIC_INLINE void LL_FLASH_TriggerOptionProgramStart(FLASH_TypeDef *FLASHx)
{
  *((__IO uint32_t *)(0x1FFF0F80))=0xff;
}

/**
  * @brief  Program the page
  * @rmtoll CR          PGSTRT          LL_FLASH_PageProgram
  * @param  FLASHx FLASH Instance
  * @param  Address   Program Address
  * @param  DataAddress Data Address
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_PageProgram(FLASH_TypeDef *FLASHx,uint32_t Address, uint32_t * DataAddress)
{
  uint8_t index=0;
  uint32_t dest = Address;
  uint32_t * src = DataAddress;
  uint32_t primask_bit;
  /* Enter critical section */
  primask_bit = __get_PRIMASK();
  __disable_irq();
  /* 32 words*/
  while(index<32U)
  {
    *(uint32_t *)dest = *src;
    src += 1U;
    dest += 4U;
    index++;
    if(index==31)
    {
      LL_FLASH_EnablePageProgramStart(FLASHx);
    }
  }

  /* Exit critical section: restore previous priority mask */
  __set_PRIMASK(primask_bit);
}

/**
  * @}
  */

/** @defgroup FLASH_LL_EF_WRP_Management WRP Management
  * @{
  */

/**
  * @brief  Set WRP Address
  * @rmtoll WRPR        WRP             LL_FLASH_SetWRPRAddress
  * @param  FLASHx FLASH Instance
  * @param  Address This parameter can be a combination of the following values:
  *         @arg @ref LL_FLASH_WRP_DISABLE
  *         @arg @ref LL_FLASH_WRP_SECTOR_0
  *         @arg @ref LL_FLASH_WRP_SECTOR_1
  *         @arg @ref LL_FLASH_WRP_SECTOR_2
  *         @arg @ref LL_FLASH_WRP_SECTOR_3
  *         @arg @ref LL_FLASH_WRP_SECTOR_4
  *         @arg @ref LL_FLASH_WRP_SECTOR_5
  *         @arg @ref LL_FLASH_WRP_SECTOR_6
  *         @arg @ref LL_FLASH_WRP_SECTOR_7
  *         @arg @ref LL_FLASH_WRP_SECTOR_8
  *         @arg @ref LL_FLASH_WRP_SECTOR_9
  *         @arg @ref LL_FLASH_WRP_SECTOR_10
  *         @arg @ref LL_FLASH_WRP_SECTOR_11
  *         @arg @ref LL_FLASH_WRP_SECTOR_12
  *         @arg @ref LL_FLASH_WRP_SECTOR_13
  *         @arg @ref LL_FLASH_WRP_SECTOR_14
  *         @arg @ref LL_FLASH_WRP_SECTOR_15
  *         @arg @ref LL_FLASH_WRP_Pages0to31
  *         @arg @ref LL_FLASH_WRP_Pages32to63
  *         @arg @ref LL_FLASH_WRP_Pages64to95
  *         @arg @ref LL_FLASH_WRP_Pages96to127
  *         @arg @ref LL_FLASH_WRP_Pages128to159
  *         @arg @ref LL_FLASH_WRP_Pages160to191
  *         @arg @ref LL_FLASH_WRP_Pages192to223
  *         @arg @ref LL_FLASH_WRP_Pages224to255
  *         @arg @ref LL_FLASH_WRP_Pages256to287
  *         @arg @ref LL_FLASH_WRP_Pages288to319
  *         @arg @ref LL_FLASH_WRP_Pages320to351
  *         @arg @ref LL_FLASH_WRP_Pages352to383
  *         @arg @ref LL_FLASH_WRP_Pages384to415
  *         @arg @ref LL_FLASH_WRP_Pages416to447
  *         @arg @ref LL_FLASH_WRP_Pages448to479
  *         @arg @ref LL_FLASH_WRP_Pages480to511
  *         @arg @ref LL_FLASH_WRP_AllPages
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetWRPAddress(FLASH_TypeDef *FLASHx,uint32_t Address)
{
  MODIFY_REG(FLASHx->WRPR, FLASH_WRPR_BK_WRPX , ((~(Address)) & (FLASH_WRPR_BK_WRPX)));
}

/**
  * @brief  Get WRP Address
  * @rmtoll WRPR        WRP             LL_FLASH_GetWRPAddress
  * @param  FLASHx FLASH Instance
  * @retval Returned value can be a combination of the following values:
  *         @arg @ref LL_FLASH_WRP_DISABLE
  *         @arg @ref LL_FLASH_WRP_SECTOR_0
  *         @arg @ref LL_FLASH_WRP_SECTOR_1
  *         @arg @ref LL_FLASH_WRP_SECTOR_2
  *         @arg @ref LL_FLASH_WRP_SECTOR_3
  *         @arg @ref LL_FLASH_WRP_SECTOR_4
  *         @arg @ref LL_FLASH_WRP_SECTOR_5
  *         @arg @ref LL_FLASH_WRP_SECTOR_6
  *         @arg @ref LL_FLASH_WRP_SECTOR_7
  *         @arg @ref LL_FLASH_WRP_SECTOR_8
  *         @arg @ref LL_FLASH_WRP_SECTOR_9
  *         @arg @ref LL_FLASH_WRP_SECTOR_10
  *         @arg @ref LL_FLASH_WRP_SECTOR_11
  *         @arg @ref LL_FLASH_WRP_SECTOR_12
  *         @arg @ref LL_FLASH_WRP_SECTOR_13
  *         @arg @ref LL_FLASH_WRP_SECTOR_14
  *         @arg @ref LL_FLASH_WRP_SECTOR_15
  *         @arg @ref LL_FLASH_WRP_Pages0to31
  *         @arg @ref LL_FLASH_WRP_Pages32to63
  *         @arg @ref LL_FLASH_WRP_Pages64to95
  *         @arg @ref LL_FLASH_WRP_Pages96to127
  *         @arg @ref LL_FLASH_WRP_Pages128to159
  *         @arg @ref LL_FLASH_WRP_Pages160to191
  *         @arg @ref LL_FLASH_WRP_Pages192to223
  *         @arg @ref LL_FLASH_WRP_Pages224to255
  *         @arg @ref LL_FLASH_WRP_Pages256to287
  *         @arg @ref LL_FLASH_WRP_Pages288to319
  *         @arg @ref LL_FLASH_WRP_Pages320to351
  *         @arg @ref LL_FLASH_WRP_Pages352to383
  *         @arg @ref LL_FLASH_WRP_Pages384to415
  *         @arg @ref LL_FLASH_WRP_Pages416to447
  *         @arg @ref LL_FLASH_WRP_Pages448to479
  *         @arg @ref LL_FLASH_WRP_Pages480to511
  *         @arg @ref LL_FLASH_WRP_AllPages
  */
__STATIC_INLINE uint32_t LL_FLASH_GetWRPAddress(FLASH_TypeDef *FLASHx)
{
  return ((~(READ_BIT(FLASHx->WRPR, FLASH_WRPR_BK_WRPX)))  & FLASH_WRPR_BK_WRPX);
}

/**
  * @}
  */

/** @defgroup FLASH_LL_EF_PCROP_Management PCROP Management
  * @{
  */
/**
  * @brief  Set PCROP
  * @rmtoll PCROPR        PCROPSR             LL_FLASH_SetPCROP
  * @rmtoll PCROPR        PCROPER             LL_FLASH_SetPCROP
  * @param  FLASHx FLASH Instance
  * @param  PCROPStartAddr This parameter can be StartAdress of pcrop
  * @param  PCROPEndAddr This parameter can be EndAdress of pcrop
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetPCROP(FLASH_TypeDef *FLASHx,uint32_t PCROPStartAddr,uint32_t PCROPEndAddr)
{
  uint32_t reg_value1 = 0;
  uint32_t reg_value2 = 0;
  
  /* Calculate the location of the PCROPStartAddr in FLASH */
  reg_value1 = (PCROPStartAddr >> 7);
  reg_value2 = ((PCROPEndAddr >> 7) << FLASH_PCROPR_PCROPER_Pos) ;

  MODIFY_REG(FLASHx->PCROPR,(FLASH_PCROPR_PCROPSR | FLASH_PCROPR_PCROPER), (reg_value1 | reg_value2));
}

/**
  * @brief  Get PCROP
  * @rmtoll PCROPR        PCROPSR             LL_FLASH_GetPCROP
  * @rmtoll PCROPR        PCROPER             LL_FLASH_GetPCROP
  * @param  FLASHx FLASH Instance
  * @param  PCROPStartAddr This parameter can be StartAdress of pcrop
  * @param  PCROPEndAddr This parameter can be EndAdress of pcrop
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_GetPCROP(FLASH_TypeDef *FLASHx,uint32_t *PCROPStartAddr,uint32_t *PCROPEndAddr)
{
  uint32_t reg_value = 0;

  /* Calculate PCROPStartAddr by FLASHx->PCROPSR */
  reg_value       = ((READ_REG(FLASHx->PCROPR) & FLASH_PCROPR_PCROPSR) << 7);
  *PCROPStartAddr = (reg_value);

  /* Calculate PCROPEndAddr by FLASHx->PCROP0ER */
  reg_value     = (((READ_REG(FLASHx->PCROPR) & FLASH_PCROPR_PCROPER) << 7) >> FLASH_PCROPR_PCROPER_Pos);
  *PCROPEndAddr = (reg_value) ;
}

/**
  * @}
  */

/** @defgroup FLASH_LL_EF_SEC_Management SEC Management
  * @{
  */
/**
  * @brief  Set SECPROT Size
  * @rmtoll SECR        SEC_SIZE             LL_FLASH_SetSecSize
  * @param  FLASHx FLASH Instance
  * @param  SecSize This parameter can be Sec Size
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetSecSize(FLASH_TypeDef *FLASHx,uint32_t SecSize)
{
  MODIFY_REG(FLASHx->SECR,FLASH_SECR_SEC_SIZE, SecSize);
}

/**
  * @brief  Get SECPROT Size
  * @rmtoll SECR        SEC_SIZE             LL_FLASH_GetSecSize
  * @param  FLASHx FLASH Instance
  * @retval Sec Size
  */
__STATIC_INLINE uint32_t LL_FLASH_GetSecSize(FLASH_TypeDef *FLASHx)
{
  return READ_BIT(FLASH->SECR,FLASH_SECR_SEC_SIZE);
}

/**
  * @}
  */

/** @defgroup FLASH_LL_EF_OPTR_Management OPTR Management
  * @{
  */
/**
  * @brief  Set Optr
  * @rmtoll OPTR            BOOT_LOCK        LL_FLASH_SetOPTR
  * @rmtoll OPTR            SWD_MODE         LL_FLASH_SetOPTR
  * @rmtoll OPTR            nBOOT1           LL_FLASH_SetOPTR
  * @rmtoll OPTR            BOR_LEV          LL_FLASH_SetOPTR
  * @rmtoll OPTR            BOR_EN           LL_FLASH_SetOPTR
  * @rmtoll OPTR            NRST_MODE        LL_FLASH_SetOPTR
  * @rmtoll OPTR            WWDG_SW          LL_FLASH_SetOPTR
  * @rmtoll OPTR            IWDG_SW          LL_FLASH_SetOPTR
  * @rmtoll OPTR            IWDG_STOP        LL_FLASH_SetOPTR
  * @rmtoll OPTR            NRST_RDP         LL_FLASH_SetOPTR
  * @param  FLASHx FLASH Instance
  * @param  USERType This parameter can be a combination of following values:
  *         @arg @ref LL_FLASH_OPTR_RDP
  *         @arg @ref LL_FLASH_OPTR_NRST_MODE
  *         @arg @ref LL_FLASH_OPTR_IWDG_STOP
  *         @arg @ref LL_FLASH_OPTR_IWDG_SW
  *         @arg @ref LL_FLASH_OPTR_WWDG_SW
  *         @arg @ref LL_FLASH_OPTR_nBOOT1
  *         @arg @ref LL_FLASH_OPTR_BOOT_LOCK
  *         @arg @ref LL_FLASH_OPTR_BOR_LEVEL
  *         @arg @ref LL_FLASH_OPTR_BOR_ENABLE
  *         @arg @ref LL_FLASH_OPTR_SWD_MODE
  * @param  USERConfig Optr value need to be config by USERType
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetOPTR(FLASH_TypeDef *FLASHx,uint32_t USERType,uint32_t USERConfig)
{
  MODIFY_REG(FLASHx->OPTR,USERType,USERConfig);
}

/**
  * @brief Get BOOT Lock
  * @rmtoll OPTR        BOOT_LOCK          LL_FLASH_GetBOOTLock
  * @param  FLASHx FLASH Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_BOOT_FROM_OB
  *         @arg @ref LL_FLASH_BOOT_FROM_MAINFLASH
  */
__STATIC_INLINE uint32_t LL_FLASH_GetBOOTLock(FLASH_TypeDef *FLASHx)
{
  return READ_BIT(FLASHx->OPTR, FLASH_OPTR_BOOT_LOCK);
}

/**
  * @brief Get SWD Mode
  * @rmtoll OPTR        SWD_MODE          LL_FLASH_GetSWDMode
  * @param  FLASHx FLASH Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_SWDIO_PA13_SWCLK_PA14
  *         @arg @ref LL_FLASH_SWDIO_PF1_SWCLK_PF0
  *         @arg @ref LL_FLASH_SWDIO_PF1_SWCLK_PA14
  *         @arg @ref LL_FLASH_SWDIO_PA13_SWCLK_PF0
  */
__STATIC_INLINE uint32_t LL_FLASH_GetSWDMode(FLASH_TypeDef *FLASHx)
{
  return READ_BIT(FLASHx->OPTR, FLASH_OPTR_SWD_MODE);
}

/**
  * @brief Get BOR Level
  * @rmtoll OPTR        BOR_LEV          LL_FLASH_GetBORLevel
  * @param  FLASHx FLASH Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_BOR_LEV0
  *         @arg @ref LL_FLASH_BOR_LEV1
  *         @arg @ref LL_FLASH_BOR_LEV2
  *         @arg @ref LL_FLASH_BOR_LEV3
  *         @arg @ref LL_FLASH_BOR_LEV4
  *         @arg @ref LL_FLASH_BOR_LEV5
  *         @arg @ref LL_FLASH_BOR_LEV6
  *         @arg @ref LL_FLASH_BOR_LEV7
  */
__STATIC_INLINE uint32_t LL_FLASH_GetBORLevel(FLASH_TypeDef *FLASHx)
{
  return READ_BIT(FLASHx->OPTR, FLASH_OPTR_BOR_OPCR);
}

/**
  * @brief Get BOR Enable
  * @rmtoll OPTR        BOR_EN          LL_FLASH_GetBOREnable
  * @param  FLASHx FLASH Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_BOR_DISABLE
  *         @arg @ref LL_FLASH_BOR_ENABLE
  */
__STATIC_INLINE uint32_t LL_FLASH_GetBOREnable(FLASH_TypeDef *FLASHx)
{
  return READ_BIT(FLASHx->OPTR, FLASH_OPTR_BOR_EN);
}

/**
  * @brief Get NBoot1 Mode
  * @rmtoll OPTR        NBOOT1          LL_FLASH_GetnBOOT1Mode
  * @param  FLASHx FLASH Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_NBOOT1_SRAM
  *         @arg @ref LL_FLASH_NBOOT1_SYSTEM
  */
__STATIC_INLINE uint32_t LL_FLASH_GetnBOOT1Mode(FLASH_TypeDef *FLASHx)
{
  return READ_BIT(FLASHx->OPTR, FLASH_OPTR_NBOOT1);
}

/**
  * @brief Get NRST Mode
  * @rmtoll OPTR        NRST_MODE          LL_FLASH_GetNrstMode
  * @param  FLASHx FLASH Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_NRST_MODE_RESET
  *         @arg @ref LL_FLASH_NRST_MODE_GPIO
  */
__STATIC_INLINE uint32_t LL_FLASH_GetNrstMode(FLASH_TypeDef *FLASHx)
{
  return READ_BIT(FLASHx->OPTR, FLASH_OPTR_NRST_MODE);
}

/**
  * @brief Get WWDG Mode
  * @rmtoll OPTR        WWDG_SW          LL_FLASH_GetWWDGMode
  * @param  FLASHx FLASH Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_WWDG_MODE_HW
  *         @arg @ref LL_FLASH_WWDG_MODE_SW
  */
__STATIC_INLINE uint32_t LL_FLASH_GetWWDGMode(FLASH_TypeDef *FLASHx)
{
  return READ_BIT(FLASHx->OPTR, FLASH_OPTR_WWDG_SW);
}

/**
  * @brief Get IWDG Mode
  * @rmtoll OPTR        IWDG_SW          LL_FLASH_GetIWDGMode
  * @param  FLASHx FLASH Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_IWDG_MODE_HW
  *         @arg @ref LL_FLASH_IWDG_MODE_SW
  */
__STATIC_INLINE uint32_t LL_FLASH_GetIWDGMode(FLASH_TypeDef *FLASHx)
{
  return READ_BIT(FLASHx->OPTR, FLASH_OPTR_IWDG_SW);
}

/**
  * @brief Get IWDG In Stop
  * @rmtoll OPTR        IWDG_STOP          LL_FLASH_GetIWDGInStop
  * @param  FLASHx FLASH Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_IWDG_INSTOP_FREEZE
  *         @arg @ref LL_FLASH_IWDG_INSTOP_ACTIVE
  */
__STATIC_INLINE uint32_t LL_FLASH_GetIWDGInStop(FLASH_TypeDef *FLASHx)
{
  return READ_BIT(FLASHx->OPTR, FLASH_OPTR_IWDG_STOP);
}

/**
  * @brief Get RDP Level
  * @rmtoll OPTR        RDP          LL_FLASH_GetRDP
  * @param  FLASHx FLASH Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_RDP_LEVEL_0
  *         @arg @ref LL_FLASH_RDP_LEVEL_1
  *         @arg @ref LL_FLASH_RDP_LEVEL_2
  */
__STATIC_INLINE uint32_t LL_FLASH_GetRDP(FLASH_TypeDef *FLASHx)
{
  return READ_BIT(FLASHx->OPTR, FLASH_OPTR_RDP);
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
#endif /* defined (FLASH) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* PY32F032_LL_FLASH_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
