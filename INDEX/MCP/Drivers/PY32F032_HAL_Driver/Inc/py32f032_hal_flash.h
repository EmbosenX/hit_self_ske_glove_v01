/**
  ******************************************************************************
  * @file    py32f032_hal_flash.h
  * @author  MCU Application Team
  * @brief   Header file of FLASH HAL module.
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
#ifndef __PY32F032_HAL_FLASH_H
#define __PY32F032_HAL_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f032_hal_def.h"

/** @addtogroup PY32F032_HAL_Driver
  * @{
  */

/** @addtogroup FLASH
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup FLASH_Exported_Types FLASH Exported Types
  * @{
  */

/**
  * @brief  FLASH Erase structure definition
  */
typedef struct
{
  uint32_t TypeErase;        /*!< Mass erase or Sector erase or page erase.
                                  This parameter can be a value of @ref FLASH_Type_Erase */
  uint32_t PageAddress;      /*!< PageAdress: Initial FLASH page address to erase when mass erase /sector erase is disabled
                                  This parameter must be a number between Min_Data = FLASH_BASE and Max_Data = FLASH_END */
  uint32_t NbPages;          /*!< Number of pages to be erased.
                                  This parameter must be a value between 1 and (FLASH_PAGE_NB - value of initial page)*/
  uint32_t SectorAddress;    /*!< SectorAddress: Initial FLASH sector address to erase when mass erase /page erase is disabled
                                  This parameter must be a number between Min_Data = FLASH_BASE and Max_Data = FLASH_END */    
  uint32_t NbSectors;        /*!< Number of sectors to be erased.
                                  This parameter must be a value between 1 and (FLASH_SECTOR_NB - value of initial sector)*/ 
  uint32_t UserDataAddress;  /*!< UserDataAddress: UserDataAddress */  
} FLASH_EraseInitTypeDef;

/**
  * @brief  FLASH Option Bytes PROGRAM structure definition
  */
typedef struct
{
  uint32_t  OptionType;         /*!< OptionType: Option byte to be configured.
                                     This parameter can be a value of @ref FLASH_Option_Type */

  uint32_t  WRPSector;           /*!< WRPSector: This bitfield specifies the sector(s) which are write protected.
                                     This parameter can be a combination of @ref FLASH_Option_Bytes_Write_Protection */
      
  uint32_t  RDPLevel;           /*!< RDPLevel: Set the read protection level.
                                     This parameter can be a value of @ref FLASH_OB_Read_Protection */
  
  uint32_t  USERType;           /*!< User option byte(s) to be configured (used for OPTIONBYTE_USER).
                                     This parameter can be a combination of @ref FLASH_OB_USER_Type */

  uint32_t  USERConfig;         /*!< Value of the user option byte (used for OPTIONBYTE_USER).
                                     This parameter can be a combination of 
                                     @ref FLASH_OB_USER_NRST_MODE,
                                     @ref FLASH_OB_USER_IWDG_STOP,
                                     @ref FLASH_OB_USER_IWDG_SW,
                                     @ref FLASH_OB_USER_WWDG_SW,
                                     @ref FLASH_OB_USER_NBOOT1,
                                     @ref FLASH_OB_USER_BOOT_LOCK,
                                     @ref FLASH_OB_USER_BOR_EN,
                                     @ref FLASH_OB_USER_BOR_LEV,
                                     @ref FLASH_OB_USER_SWD_MODE  */

  uint32_t  PCROPStartAddr;     /*!< PCROP Start address (used for OPTIONBYTE_PCROP).*/
  uint32_t  PCROPEndAddr;       /*!< PCROP End address (used for OPTIONBYTE_PCROP).*/

  uint32_t  SecSize;            /*!< SECP Size PageNumbers */
} FLASH_OBProgramInitTypeDef; 

/**
* @brief  FLASH handle Structure definition
*/
typedef struct
{
  HAL_LockTypeDef   Lock;                           /* FLASH locking object */
  uint32_t          ErrorCode;                      /* FLASH error code */
  uint32_t          Busy;                           /* Internal variable to define the current Bank which is erasing or program in IT context */
  uint32_t          ProcedureOnGoing;               /* Internal variable to indicate which procedure is ongoing or not in IT context */
  uint32_t          Address;                        /* Internal variable to save address selected for program in IT context */
  uint32_t          Bank;                           /* Internal variable to save current bank selected during erase in IT context */
  uint32_t          PageOrSector;                   /* Internal variable to define the current page or sector which is erasing in IT context */
  uint32_t          NbPagesSectorsToErase;          /* Internal variable to save the remaining pages to erase in IT context */
} FLASH_ProcessTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup FLASH_Exported_Constants FLASH Exported Constants
  * @{
  */

/** @defgroup FLASH_Error FLASH Error
  * @{
  */
#define HAL_FLASH_ERROR_NONE            0x00000000U
#define HAL_FLASH_ERROR_WRP             FLASH_FLAG_WRPERR
#define HAL_FLASH_ERROR_RDERR           FLASH_FLAG_RDERR
#define HAL_FLASH_ERROR_OPTV            FLASH_FLAG_OPTVERR
/**
  * @}
  */

/** @defgroup FLASH_Type_Erase FLASH erase type
  * @{
  */
#define FLASH_TYPEERASE_MASSERASE       FLASH_CR_MER    /*!<Flash mass erase activation*/
#define FLASH_TYPEERASE_PAGEERASE       FLASH_CR_PER    /*!<Flash page erase activation*/
#define FLASH_TYPEERASE_SECTORERASE     FLASH_CR_SER    /*!<Flash sector erase activation*/ 
#define FLASH_TYPEERASE_USERDATAERASE   FLASH_CR_UPER   /*!<Flash UserData erase activation*/

/**
  * @}
  */

/** @defgroup FLASH_Banks FLASH Banks
  * @{
  */
#define FLASH_BANK_0                     0x00000001U   /*!< Bank0   */

/**
  * @}
  */

/** @defgroup FLASH_Option_Type FLASH Option Bytes Type
  * @{
  */
#define OPTIONBYTE_WRP                  0x01U     /*!< WRP option byte configuration */
#define OPTIONBYTE_RDP                  0x02U     /*!< RDP option byte configuration */
#define OPTIONBYTE_USER                 0x04U     /*!< USER option byte configuration */
#define OPTIONBYTE_PCROP                0x08U     /*!< PCROP option byte configuration */
#define OPTIONBYTE_SEC                  0x10U     /*!< Securable memory option byte configuration */
/**
  * @}
  */



/** @defgroup FLASH_OB_Read_Protection FLASH Option Bytes Read Protection
  * @{
  */
#define OB_RDP_LEVEL_0                  ((uint8_t)0xAAU)
#define OB_RDP_LEVEL_1                  ((uint8_t)0x55U)
#define OB_RDP_LEVEL_2                  ((uint8_t)0xCCU) 
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_Type FLASH User Option Type
  * @{
  */
#define OB_USER_NRST_MODE       FLASH_OPTR_NRST_MODE 
#define OB_USER_IWDG_STOP       FLASH_OPTR_IWDG_STOP
#define OB_USER_IWDG_SW         FLASH_OPTR_IWDG_SW
#define OB_USER_WWDG_SW         FLASH_OPTR_WWDG_SW
#define OB_USER_NBOOT1          FLASH_OPTR_NBOOT1  
#define OB_USER_BOOT_LOCK       FLASH_OPTR_BOOT_LOCK
#define OB_USER_BOR_EN          FLASH_OPTR_BOR_EN
#define OB_USER_BOR_LEV         FLASH_OPTR_BOR_OPCR
#define OB_USER_SWD_MODE        FLASH_OPTR_SWD_MODE


#define OB_USER_OPTR_MSK        (OB_USER_NRST_MODE | OB_USER_IWDG_STOP | OB_USER_IWDG_SW | OB_USER_WWDG_SW \
                               | OB_USER_NBOOT1 | OB_USER_BOOT_LOCK | OB_USER_BOR_EN | OB_USER_BOR_LEV | OB_USER_SWD_MODE)


/**
  * @}
  */

/** @defgroup FLASH_Option_Bytes_Write_Protection FLASH Option Bytes Write Protection
  * @{
  */
#define FLASH_WRPR_WRP_0                0x00000001U  /* Write protection of  Sector0 */
#define FLASH_WRPR_WRP_1                0x00000002U  /* Write protection of  Sector1 */
#define FLASH_WRPR_WRP_2                0x00000004U  /* Write protection of  Sector2 */
#define FLASH_WRPR_WRP_3                0x00000008U  /* Write protection of  Sector3 */
#define FLASH_WRPR_WRP_4                0x00000010U  /* Write protection of  Sector4 */
#define FLASH_WRPR_WRP_5                0x00000020U  /* Write protection of  Sector5 */
#define FLASH_WRPR_WRP_6                0x00000040U  /* Write protection of  Sector6 */
#define FLASH_WRPR_WRP_7                0x00000080U  /* Write protection of  Sector7 */
#define FLASH_WRPR_WRP_8                0x00000100U  /* Write protection of  Sector8 */
#define FLASH_WRPR_WRP_9                0x00000200U  /* Write protection of  Sector9 */
#define FLASH_WRPR_WRP_10               0x00000400U  /* Write protection of  Sector10 */
#define FLASH_WRPR_WRP_11               0x00000800U  /* Write protection of  Sector11 */
#define FLASH_WRPR_WRP_12               0x00001000U  /* Write protection of  Sector12 */
#define FLASH_WRPR_WRP_13               0x00002000U  /* Write protection of  Sector13 */
#define FLASH_WRPR_WRP_14               0x00004000U  /* Write protection of  Sector14 */
#define FLASH_WRPR_WRP_15               0x00008000U  /* Write protection of  Sector15 */
#define FLASH_WRPR_WRP                  0xFFU        /* Write protection of ALL */

#define OB_WRP_SECTOR_0                  FLASH_WRPR_WRP_0   /* Write protection of  Sector0 */
#define OB_WRP_SECTOR_1                  FLASH_WRPR_WRP_1   /* Write protection of  Sector1 */
#define OB_WRP_SECTOR_2                  FLASH_WRPR_WRP_2   /* Write protection of  Sector2 */
#define OB_WRP_SECTOR_3                  FLASH_WRPR_WRP_3   /* Write protection of  Sector3 */
#define OB_WRP_SECTOR_4                  FLASH_WRPR_WRP_4   /* Write protection of  Sector4 */
#define OB_WRP_SECTOR_5                  FLASH_WRPR_WRP_5   /* Write protection of  Sector5 */
#define OB_WRP_SECTOR_6                  FLASH_WRPR_WRP_6   /* Write protection of  Sector6 */
#define OB_WRP_SECTOR_7                  FLASH_WRPR_WRP_7   /* Write protection of  Sector7 */
#define OB_WRP_SECTOR_8                  FLASH_WRPR_WRP_8   /* Write protection of  Sector8 */
#define OB_WRP_SECTOR_9                  FLASH_WRPR_WRP_9   /* Write protection of  Sector9 */
#define OB_WRP_SECTOR_10                 FLASH_WRPR_WRP_10  /* Write protection of  Sector10 */
#define OB_WRP_SECTOR_11                 FLASH_WRPR_WRP_11  /* Write protection of  Sector11 */
#define OB_WRP_SECTOR_12                 FLASH_WRPR_WRP_12  /* Write protection of  Sector12 */
#define OB_WRP_SECTOR_13                 FLASH_WRPR_WRP_13  /* Write protection of  Sector13 */
#define OB_WRP_SECTOR_14                 FLASH_WRPR_WRP_14  /* Write protection of  Sector14 */
#define OB_WRP_SECTOR_15                 FLASH_WRPR_WRP_15  /* Write protection of  Sector15 */

#define OB_WRP_Pages0to31               FLASH_WRPR_WRP_0    /* Write protection of  Sector0 */
#define OB_WRP_Pages32to63              FLASH_WRPR_WRP_1    /* Write protection of  Sector1 */
#define OB_WRP_Pages64to95              FLASH_WRPR_WRP_2    /* Write protection of  Sector2 */
#define OB_WRP_Pages96to127             FLASH_WRPR_WRP_3    /* Write protection of  Sector3 */
#define OB_WRP_Pages128to159            FLASH_WRPR_WRP_4    /* Write protection of  Sector4 */
#define OB_WRP_Pages160to191            FLASH_WRPR_WRP_5    /* Write protection of  Sector5 */
#define OB_WRP_Pages192to223            FLASH_WRPR_WRP_6    /* Write protection of  Sector6 */
#define OB_WRP_Pages224to255            FLASH_WRPR_WRP_7    /* Write protection of  Sector7 */
#define OB_WRP_Pages256to287            FLASH_WRPR_WRP_8    /* Write protection of  Sector8 */
#define OB_WRP_Pages288to319            FLASH_WRPR_WRP_9    /* Write protection of  Sector9 */
#define OB_WRP_Pages320to351            FLASH_WRPR_WRP_10   /* Write protection of  Sector10 */
#define OB_WRP_Pages352to383            FLASH_WRPR_WRP_11   /* Write protection of  Sector11 */
#define OB_WRP_Pages384to415            FLASH_WRPR_WRP_12   /* Write protection of  Sector12 */
#define OB_WRP_Pages416to447            FLASH_WRPR_WRP_13   /* Write protection of  Sector13 */
#define OB_WRP_Pages448to479            FLASH_WRPR_WRP_14   /* Write protection of  Sector14 */
#define OB_WRP_Pages480to511            FLASH_WRPR_WRP_15   /* Write protection of  Sector15 */

#define OB_WRP_AllPages                 FLASH_WRPR_WRP    /* Write protection of all Blocks */
/** 
  * @}
  */
  
/** @defgroup FLASH_Type_Program FLASH type program
  * @{
  */
#define FLASH_TYPEPROGRAM_PAGE             FLASH_CR_PG  /*!<Program 128bytes at a specified address.*/  
#define FLASH_TYPEPROGRAM_USERDATA         FLASH_CR_UPG /*!<Program 128bytes at userdata address.*/  
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_NRST_MODE FLASH Option Bytes User NRST mode bit
  * @{
  */
#define OB_NRST_MODE_RESET             0x00000000U            /*!< Reset pin is in Reset mode */
#define OB_NRST_MODE_GPIO              FLASH_OPTR_NRST_MODE   /*!< Reset pin is in GPIO mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_IWDG_STOP FLASH Option Bytes User IWDG Mode On Stop
  * @{
  */
#define OB_IWDG_STOP_FREEZE             0x00000000U              /*!< Independent watchdog counter is frozen in Stop mode */
#define OB_IWDG_STOP_RUN                FLASH_OPTR_IWDG_STOP     /*!< Independent watchdog counter is running in Stop mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_IWDG_SW FLASH Option Bytes IWatchdog
  * @{
  */
#define OB_IWDG_HW                      0x00000000U          /*!< Hardware IWDG selected */
#define OB_IWDG_SW                      FLASH_OPTR_IWDG_SW   /*!< Software IWDG selected */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_WWDG_SW FLASH Option Bytes User WWDG Type
  * @{
  */
#define OB_WWDG_HW                      0x00000000U              /*!< Hardware window watchdog */
#define OB_WWDG_SW                      FLASH_OPTR_WWDG_SW       /*!< Software window watchdog */
/**
  * @}
  */
 
/** @defgroup FLASH_OB_USER_NBOOT1 FLASH Option Bytes User BOOT1 Type
  * @{
  */
#define OB_NBOOT1_SRAM                   0x00000000U          /*!< Embedded SRAM1 is selected as boot space (if BOOT0=1) */
#define OB_NBOOT1_SYSTEM                 (FLASH_OPTR_NBOOT1)  /*!< System memory is selected as boot space (if BOOT0=1) */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_BOOT_LOCK FLASH Option Bytes User Software BOOT0
  * @{
  */
#define OB_BOOT_FROM_OB                     0x00000000U             /*!< BOOT from IO or OB */
#define OB_BOOT_FROM_MAINFLASH              (FLASH_OPTR_BOOT_LOCK)  /*!< BOOT from MainFlash */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_BOR_EN FLASH Option Bytes BOR Enable
  * @{
  */
#define OB_BOR_DISABLE                  0x00000000U        /*!< BOR Reset set to default */
#define OB_BOR_ENABLE                   FLASH_OPTR_BOR_EN  /*!< Use option byte to define BOR thresholds */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_BOR_LEV FLASH Option Bytes BOR Level
  * @{
  */
#define OB_BOR_LEVEL_1p7_1p8    ((uint32_t)0x0000U)                                                                 /*!< BOR Reset threshold levels for 1.7V - 1.8V VDD power supply    */
#define OB_BOR_LEVEL_1p9_2p0    ((uint32_t)FLASH_OPTR_BOR_OPCR_0)                                                   /*!< BOR Reset threshold levels for 1.9V - 2.0V VDD power supply    */
#define OB_BOR_LEVEL_2p1_2p2    ((uint32_t)FLASH_OPTR_BOR_OPCR_1)                                                   /*!< BOR Reset threshold levels for 2.1V - 2.2V VDD power supply    */
#define OB_BOR_LEVEL_2p3_2p4    ((uint32_t)(FLASH_OPTR_BOR_OPCR_0 | FLASH_OPTR_BOR_OPCR_1))                         /*!< BOR Reset threshold levels for 2.3V - 2.4V VDD power supply    */
#define OB_BOR_LEVEL_2p7_2p8    ((uint32_t)FLASH_OPTR_BOR_OPCR_2)                                                   /*!< BOR Reset threshold levels for 2.7V - 2.8V VDD power supply    */
#define OB_BOR_LEVEL_3p0_3p1    ((uint32_t)(FLASH_OPTR_BOR_OPCR_0 | FLASH_OPTR_BOR_OPCR_2))                         /*!< BOR Reset threshold levels for 3.0V - 3.1V VDD power supply    */
#define OB_BOR_LEVEL_3p6_3p7    ((uint32_t)(FLASH_OPTR_BOR_OPCR_1 | FLASH_OPTR_BOR_OPCR_2))                         /*!< BOR Reset threshold levels for 3.6V - 3.7V VDD power supply    */
#define OB_BOR_LEVEL_4p1_4p2    ((uint32_t)(FLASH_OPTR_BOR_OPCR_0 | FLASH_OPTR_BOR_OPCR_1 | FLASH_OPTR_BOR_OPCR_2)) /*!< BOR Reset threshold levels for 4.1V - 4.2V VDD power supply    */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_SWD_MODE FLASH Option Bytes SWD MODE
  * @{
  */

#define OB_SWD_SWDIO_PA13_SWCLK_PA14            0x00000000U                                          /*!< PA13:SWDIO,PA14:SWCLK */
#define OB_SWD_SWDIO_PF1_SWCLK_PF0              FLASH_OPTR_SWD_MODE_0                                /*!< PF1:SWDIO,PF0:SWCLK */
#define OB_SWD_SWDIO_PF1_SWCLK_PA14             FLASH_OPTR_SWD_MODE_1                                /*!< PF1:SWDIO,PA14:SWCLK */
#define OB_SWD_SWDIO_PA13_SWCLK_PF0             (FLASH_OPTR_SWD_MODE_1 | FLASH_OPTR_SWD_MODE_0)      /*!< PA13:SWDIO,PF0:SWCLK */
/**
  * @}
  */


/** @defgroup FLASH_Latency FLASH Latency
  * @{
  */
#define FLASH_LATENCY_0                 (0x00000000UL)         /*!< FLASH 0 wait state */
#define FLASH_LATENCY_1                 (FLASH_ACR_LATENCY_0)  /*!< FLASH 1 wait state */
#define FLASH_LATENCY_2                 (FLASH_ACR_LATENCY_1)  /*!< FLASH 2 wait state */
#define FLASH_LATENCY_3                 (FLASH_ACR_LATENCY_0 | FLASH_ACR_LATENCY_1)  /*!< FLASH 3 wait state */
/**
  * @}
  */

/** @defgroup FLASH_Flags FLASH Flags Definition
  * @{
  */
#define FLASH_FLAG_EOP                  FLASH_SR_EOP       /*!< FLASH End of operation flag */
#define FLASH_FLAG_WRPERR               FLASH_SR_WRPERR    /*!< FLASH Write protection error flag */
#define FLASH_FLAG_RDERR                FLASH_SR_RDERR     /*!< FLASH PCROP error flag */
#define FLASH_FLAG_OPTVERR              FLASH_SR_OPTVERR   /*!< FLASH Option validity error flag */
#define FLASH_FLAG_BSY                  FLASH_SR_BSY       /*!< FLASH Operation Busy flag */
#define FLASH_FLAG_USRLOCK              FLASH_SR_USERLOCK  /*!< FLASH User Lock flag */

#define FLASH_FLAG_SR_ERRORS            (FLASH_FLAG_WRPERR | FLASH_FLAG_RDERR | FLASH_FLAG_OPTVERR)

#define FLASH_FLAG_ALL_ERRORS           (FLASH_FLAG_SR_ERRORS)
/**
  * @}
  */

/** @defgroup FLASH_Interrupt_definition FLASH Interrupts Definition
  * @brief FLASH Interrupt definition
  * @{
  */
#define FLASH_IT_EOP                    FLASH_CR_EOPIE                                       /*!< End of FLASH Operation Interrupt source */
#define FLASH_IT_OPERR                  FLASH_CR_ERRIE                                       /*!< Error Interrupt source */
#define FLASH_IT_RDERR                  FLASH_CR_RDERRIE                                     /*!< PCROP0 Read Error Interrupt source*/
#define FLASH_IT_ALL                    (FLASH_CR_EOPIE | FLASH_CR_ERRIE | FLASH_CR_RDERRIE)
/**
  * @}
  */

/** @defgroup FLASH_EnterLpmode_Delay FLASH Enter LpMode Delay Time 
  * @{
  */
#define Flash_EnterLpmodeDelay_1HSIDIVCLOCK         (FLASH_LPCR_LPRUN_ENTERT_0)
#define Flash_EnterLpmodeDelay_2HSIDIVCLOCK         (FLASH_LPCR_LPRUN_ENTERT_1)
#define Flash_EnterLpmodeDelay_3HSIDIVCLOCK         (FLASH_LPCR_LPRUN_ENTERT_1 | FLASH_LPCR_LPRUN_ENTERT_0)
#define Flash_EnterLpmodeDelay_4HSIDIVCLOCK         (FLASH_LPCR_LPRUN_ENTERT_2)
#define Flash_EnterLpmodeDelay_5HSIDIVCLOCK         (FLASH_LPCR_LPRUN_ENTERT_2 | FLASH_LPCR_LPRUN_ENTERT_0)
#define Flash_EnterLpmodeDelay_6HSIDIVCLOCK         (FLASH_LPCR_LPRUN_ENTERT_2 | FLASH_LPCR_LPRUN_ENTERT_1)
#define Flash_EnterLpmodeDelay_7HSIDIVCLOCK         (FLASH_LPCR_LPRUN_ENTERT_2 | FLASH_LPCR_LPRUN_ENTERT_1 | FLASH_LPCR_LPRUN_ENTERT_0) 
/**
  * @}
  */

/** @defgroup FLASH_ExitLpmode_Delay FLASH Exit LpMode Delay Time 
  * @{
  */
#define Flash_ExitLpmodeDelay_1HSIDIVCLOCK         (FLASH_LPCR_LPRUN_EXITT_0)
#define Flash_ExitLpmodeDelay_2HSIDIVCLOCK         (FLASH_LPCR_LPRUN_EXITT_1)
#define Flash_ExitLpmodeDelay_3HSIDIVCLOCK         (FLASH_LPCR_LPRUN_EXITT_1 | FLASH_LPCR_LPRUN_EXITT_0)
#define Flash_ExitLpmodeDelay_4HSIDIVCLOCK         (FLASH_LPCR_LPRUN_EXITT_2)
#define Flash_ExitLpmodeDelay_5HSIDIVCLOCK         (FLASH_LPCR_LPRUN_EXITT_2 | FLASH_LPCR_LPRUN_EXITT_0)
#define Flash_ExitLpmodeDelay_6HSIDIVCLOCK         (FLASH_LPCR_LPRUN_EXITT_2 | FLASH_LPCR_LPRUN_EXITT_1)
#define Flash_ExitLpmodeDelay_7HSIDIVCLOCK         (FLASH_LPCR_LPRUN_EXITT_2 | FLASH_LPCR_LPRUN_EXITT_1 | FLASH_LPCR_LPRUN_EXITT_0) 
/**
  * @}
  */


/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup FLASH_Exported_Macros FLASH Exported Macros
  *  @brief macros to control FLASH features
  *  @{
  */

/**
  * @brief  Set the FLASH Latency.
  * @param  __LATENCY__ FLASH Latency
  *         This parameter can be one of the following values :
  *     @arg @ref FLASH_LATENCY_0 FLASH Zero wait state
  *     @arg @ref FLASH_LATENCY_1 FLASH One wait state
  *     @arg @ref FLASH_LATENCY_2 FLASH Two wait states
  *     @arg @ref FLASH_LATENCY_3 FLASH Four wait states
  * @retval None
  */
#define __HAL_FLASH_SET_LATENCY(__LATENCY__)    MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, (__LATENCY__))

/**
  * @brief  Get the FLASH Latency.
  * @retval FLASH Latency
  *         Returned value can be one of the following values :
  *     @arg @ref FLASH_LATENCY_0 FLASH Zero wait state
  *     @arg @ref FLASH_LATENCY_1 FLASH One wait state
  *     @arg @ref FLASH_LATENCY_2 FLASH Two wait states
  *     @arg @ref FLASH_LATENCY_3 FLASH Four wait states
  */
#define __HAL_FLASH_GET_LATENCY()               READ_BIT(FLASH->ACR, FLASH_ACR_LATENCY)

/** @defgroup FLASH_Interrupt FLASH Interrupts Macros
 *  @brief macros to handle FLASH interrupts
 * @{
 */

/**
  * @brief  Enable the specified FLASH interrupt.
  * @param  __INTERRUPT__ FLASH interrupt
  *         This parameter can be any combination of the following values:
  *     @arg @ref FLASH_IT_EOP End of FLASH Operation Interrupt
  *     @arg @ref FLASH_IT_OPERR Error Interrupt
  *     @arg @ref FLASH_IT_RDERR PCROP Read Error Interrupt
  * @retval none
  */
#define __HAL_FLASH_ENABLE_IT(__INTERRUPT__)    SET_BIT(FLASH->CR, (__INTERRUPT__))

/**
  * @brief  Disable the specified FLASH interrupt.
  * @param  __INTERRUPT__ FLASH interrupt
  *         This parameter can be any combination of the following values:
  *     @arg @ref FLASH_IT_EOP End of FLASH Operation Interrupt
  *     @arg @ref FLASH_IT_OPERR Error Interrupt
  *     @arg @ref FLASH_IT_RDERR PCORP Read Error Interrupt
  * @retval none
  */
#define __HAL_FLASH_DISABLE_IT(__INTERRUPT__)   CLEAR_BIT(FLASH->CR, (__INTERRUPT__))

/**
  * @brief  Check whether the specified FLASH flag is set or not.
  * @param  __FLAG__ specifies the FLASH flag to check.
  *   This parameter can be one of the following values:
  *     @arg @ref FLASH_FLAG_EOP FLASH End of Operation flag
  *     @arg @ref FLASH_FLAG_WRPERR FLASH Write protection error flag
  *     @arg @ref FLASH_FLAG_RDERR FLASH PCROP error flag
  *     @arg @ref FLASH_FLAG_USRLOCK   User Lock flag
  *     @arg @ref FLASH_FLAG_OPTVERR FLASH Option validity error flag
  *     @arg @ref FLASH_FLAG_BSY FLASH busy
  * @retval The new state of FLASH_FLAG (SET or RESET).
  */
#define __HAL_FLASH_GET_FLAG(__FLAG__)          (READ_BIT(FLASH->SR, (__FLAG__)) == (__FLAG__))

/**
  * @brief  Clear the FLASHs pending flags.
  * @param  __FLAG__ specifies the FLASH flags to clear.
  *   This parameter can be any combination of the following values:
  *     @arg @ref FLASH_FLAG_EOP FLASH End of Operation flag
  *     @arg @ref FLASH_FLAG_WRPERR FLASH Write protection error flag
  *     @arg @ref FLASH_FLAG_RDERR   PCROP error flag
  *     @arg @ref FLASH_FLAG_OPTVERR FLASH Option validity error flag
  * @retval None
  */
#define __HAL_FLASH_CLEAR_FLAG(__FLAG__)        WRITE_REG(FLASH->SR, (__FLAG__))

/**
  * @}
  */

/**
  * @}
  */
/* Include FLASH HAL Extended module */
#include "py32f032_hal_flash_ex.h"

/* Exported variables --------------------------------------------------------*/
/** @defgroup FLASH_Exported_Variables FLASH Exported Variables
  * @{
  */
extern FLASH_ProcessTypeDef pFlash;
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup FLASH_Exported_Functions
  * @{
  */

/* Program operation functions  ***********************************************/
/** @addtogroup FLASH_Exported_Functions_Group1
  * @{
  */
HAL_StatusTypeDef  HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint32_t *DataAddr );
HAL_StatusTypeDef  HAL_FLASH_Program_IT(uint32_t TypeProgram, uint32_t Address, uint32_t *DataAddr);
HAL_StatusTypeDef  HAL_FLASH_PageProgram(uint32_t Address, uint32_t *DataAddr );
HAL_StatusTypeDef  HAL_FLASH_PageProgram_IT(uint32_t Address, uint32_t *DataAddr);
HAL_StatusTypeDef  HAL_FLASH_UserDataProgram(uint32_t Address, uint32_t * DataAddr);
/* FLASH IRQ handler method */
void               HAL_FLASH_IRQHandler(void);
/* Callbacks in non blocking modes */
void               HAL_FLASH_EndOfOperationCallback(uint32_t ReturnValue);
void               HAL_FLASH_OperationErrorCallback(uint32_t ReturnValue);

#define HAL_FLASH_Erase        HAL_FLASHEx_Erase
#define HAL_FLASH_Erase_IT     HAL_FLASHEx_Erase_IT
#define HAL_FLASH_OBProgram    HAL_FLASHEx_OBProgram
/**
  * @}
  */

/* Peripheral Control functions  **********************************************/
/** @addtogroup FLASH_Exported_Functions_Group2
  * @{
  */
HAL_StatusTypeDef  HAL_FLASH_Unlock(void);
HAL_StatusTypeDef  HAL_FLASH_Lock(void);
/* Option bytes control */
HAL_StatusTypeDef  HAL_FLASH_OB_Unlock(void);
HAL_StatusTypeDef  HAL_FLASH_OB_Lock(void);
HAL_StatusTypeDef  HAL_FLASH_OB_Launch(void);

void               HAL_FLASH_OBGetConfig(FLASH_OBProgramInitTypeDef *pOBInit);
HAL_StatusTypeDef  HAL_FLASH_OB_RDP_LevelConfig(uint8_t ReadProtectLevel);
HAL_StatusTypeDef  HAL_FLASHEx_OBProgram(FLASH_OBProgramInitTypeDef *pOBInit);
HAL_StatusTypeDef  HAL_FLASH_OB_RDPConfig(uint32_t RDPLevel);

HAL_StatusTypeDef HAL_FLASH_EnableSecureProtection(void);
/**
  * @}
  */

/* Peripheral State functions  ************************************************/
/** @addtogroup FLASH_Exported_Functions_Group3
  * @{
  */
uint32_t HAL_FLASH_GetError(void);
uint32_t HAL_FLASH_ECCCheckStatus(void);
void HAL_FLASH_SetEnterLpModeDelay(uint32_t Flash_Delay);
void HAL_FLASH_SetExitLpModeDelay(uint32_t Flash_Delay);
void HAL_FLASH_EnableFlashSleep(void);
void HAL_FLASH_DisableFlashSleep(void);
void HAL_FLASH_SetFlashSleepTime(uint32_t Sleep_Time);
/**
  * @}
  */

/**
  * @}
  */

/* Private types --------------------------------------------------------*/
/** @defgroup FLASH_Private_types FLASH Private Types
  * @{
  */
HAL_StatusTypeDef  FLASH_WaitForLastOperation(uint32_t Timeout);

/**
  * @}
  */

/* Private constants --------------------------------------------------------*/
/** @defgroup FLASH_Private_Constants FLASH Private Constants
  * @{
  */
#define FLASH_TIMEOUT_VALUE             1000U          /*!< FLASH Execution Timeout, 1 s */

#define FLASH_TYPENONE                  0x00000000U    /*!< No Programmation Procedure On Going */

#define FLASH_FLAG_SR_CLEAR             (FLASH_FLAG_SR_ERRORS | FLASH_SR_EOP)
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup FLASH_Private_Macros FLASH Private Macros
 *  @{
 */
#define IS_FLASH_TYPEERASE(__VALUE__)                 (((__VALUE__) == FLASH_TYPEERASE_PAGEERASE)   || \
                                                       ((__VALUE__) == FLASH_TYPEERASE_SECTORERASE) || \
                                                       ((__VALUE__) == FLASH_TYPEERASE_MASSERASE)   || \
                                                       ((__VALUE__) == FLASH_TYPEERASE_USERDATAERASE))

                                            
#define IS_FLASH_MAIN_MEM_ADDRESS(__ADDRESS__)        (((__ADDRESS__) >= (FLASH_BASE)) && ((__ADDRESS__) <= (FLASH_BASE + FLASH_SIZE - 1UL)))

#define IS_FLASH_PROGRAM_MAIN_MEM_ADDRESS(__ADDRESS__) (((__ADDRESS__) >= (FLASH_BASE)) && ((__ADDRESS__) <= (FLASH_BASE + FLASH_SIZE - 256UL)))

#define IS_FLASH_PROGRAM_ADDRESS(__ADDRESS__)         (IS_FLASH_PROGRAM_MAIN_MEM_ADDRESS(__ADDRESS__))

#define  IS_FLASH_PROGRAM_USERDATA_ADDRESS(__ADDRESS__)  (((__ADDRESS__) >= (0x1fff0e00)) && ((__ADDRESS__) <= 0x1fff0e7c))


#define IS_FLASH_NB_PAGES(__ADDRESS__, __VALUE__)     (((__ADDRESS__) >= (FLASH_BASE)) && ((__ADDRESS__ + ((__VALUE__*FLASH_PAGE_SIZE)) - 1) <= (FLASH_BASE + FLASH_SIZE - 1UL))&&(__VALUE__ >0 ))

#define IS_FLASH_NB_SECTORS(__ADDRESS__, __VALUE__)   (((__ADDRESS__) >= (FLASH_BASE)) && ((__ADDRESS__ + ((__VALUE__*FLASH_SECTOR_SIZE)) - 1) <= (FLASH_BASE + FLASH_SIZE - 1UL))&&(__VALUE__>0 ))

#define IS_FLASH_NB_BLOCKS(__ADDRESS__, __VALUE__)    (((__ADDRESS__) >= (FLASH_BASE)) && ((__ADDRESS__ + ((__VALUE__*FLASH_BLOCK_SIZE)) - 1) <= (FLASH_BASE + FLASH_SIZE - 1UL)) &&(__VALUE__ >0 ))

#define IS_FLASH_PAGE(__PAGE__)                       ((__PAGE__) < FLASH_PAGE_NB)

#define IS_OPTIONBYTE(__VALUE__)                      (((__VALUE__) <= (OPTIONBYTE_WRP | OPTIONBYTE_RDP | OPTIONBYTE_USER | OPTIONBYTE_PCROP | OPTIONBYTE_SEC)))

#define IS_FLASH_TYPEPROGRAM(__VALUE__)               ((__VALUE__) == FLASH_TYPEPROGRAM_PAGE)

#define IS_OB_WRPAREA(__VALUE__)                      (((__VALUE__) == OB_WRP_SECTOR_0) || \
                                                       ((__VALUE__) == OB_WRP_SECTOR_1) || \
                                                       ((__VALUE__) == OB_WRP_SECTOR_2) || \
                                                       ((__VALUE__) == OB_WRP_SECTOR_3) || \
                                                       ((__VALUE__) == OB_WRP_SECTOR_4) || \
                                                       ((__VALUE__) == OB_WRP_SECTOR_5) || \
                                                       ((__VALUE__) == OB_WRP_SECTOR_6) || \
                                                       ((__VALUE__) == OB_WRP_SECTOR_7) || \
                                                       ((__VALUE__) == OB_WRP_SECTOR_8) || \
                                                       ((__VALUE__) == OB_WRP_SECTOR_9) || \
                                                       ((__VALUE__) == OB_WRP_SECTOR_10) || \
                                                       ((__VALUE__) == OB_WRP_SECTOR_11) || \
                                                       ((__VALUE__) == OB_WRP_SECTOR_12) || \
                                                       ((__VALUE__) == OB_WRP_SECTOR_13) || \
                                                       ((__VALUE__) == OB_WRP_SECTOR_14) || \
                                                       ((__VALUE__) == OB_WRP_SECTOR_15))

#define IS_OB_RDP_LEVEL(LEVEL)                         (((LEVEL) == OB_RDP_LEVEL_0) ||\
                                                        ((LEVEL) == OB_RDP_LEVEL_1) ||\
                                                        ((LEVEL) == OB_RDP_LEVEL_2))

#define IS_OB_USER_TYPE(__TYPE__)                     ((((__TYPE__) & OB_USER_OPTR_MSK) != 0x00U) && \
                                                       (((__TYPE__) & ~OB_USER_OPTR_MSK) == 0x00U))

#define IS_OB_USER_CONFIG(__TYPE__,__CONFIG__)         ((~(__TYPE__) & (__CONFIG__)) == 0x00U)

#define IS_OB_USER_STOP(__VALUE__)                    (((__VALUE__) == OB_STOP_RST) || \
                                                       ((__VALUE__) == OB_STOP_NORST))

#define IS_OB_USER_IWDG(__VALUE__)                    (((__VALUE__) == OB_IWDG_HW) || \
                                                       ((__VALUE__) == OB_IWDG_SW))

#define IS_OB_USER_IWDG_STOP(__VALUE__)               (((__VALUE__) == OB_IWDG_STOP_FREEZE) || \
                                                       ((__VALUE__) == OB_IWDG_STOP_RUN))

#define IS_OB_USER_WWDG(__VALUE__)                    (((__VALUE__) == OB_WWDG_HW) || \
                                                       ((__VALUE__) == OB_WWDG_SW))
                                                       
#define IS_OB_USER_BOOT1(__VALUE__)                   (((__VALUE__) == OB_BOOT1_SRAM) || \
                                                       ((__VALUE__) == OB_BOOT1_SYSTEM))

#define IS_OB_USER_BOOT0(__VALUE__)                   (((__VALUE__) == OB_NBOOT0_RESET) || \
                                                       ((__VALUE__) == OB_NBOOT0_SET))

#define IS_OB_USER_NRST_MODE(__VALUE__)               (((__VALUE__) == OB_NRST_MODE_RESET) || \
                                                       ((__VALUE__) == OB_NRST_MODE_GPIO))

#define IS_OB_USER_BOR(__VALUE__)                     (((__VALUE__) == OB_BOR_DISABLE) || \
                                                       ((__VALUE__) == OB_BOR_ENABLE))

#define IS_OB_USER_BOR_LEVEL(__LEVEL__)               (((__LEVEL__) == OB_BOR_LEVEL_1p7_1p8) || \
                                                       ((__LEVEL__) == OB_BOR_LEVEL_1p9_2p0) || \
                                                       ((__LEVEL__) == OB_BOR_LEVEL_2p1_2p2) || \
                                                       ((__LEVEL__) == OB_BOR_LEVEL_2p3_2p4) || \
                                                       ((__LEVEL__) == OB_BOR_LEVEL_2p7_2p8) || \
                                                       ((__LEVEL__) == OB_BOR_LEVEL_3p0_3p1) || \
                                                       ((__LEVEL__) == OB_BOR_LEVEL_3p6_3p7) || \
                                                       ((__LEVEL__) == OB_BOR_LEVEL_4p1_4p2))


#define IS_OB_USER_SWD_MODE(__MODE__)                 (((__MODE__) == OB_SWD_SWDIO_PA13_SWCLK_PA14) || \
                                                       ((__MODE__) == OB_SWD_SWDIO_PF1_SWCLK_PF0) || \
                                                       ((__MODE__) == OB_SWD_SWDIO_PF1_SWCLK_PA14) || \
                                                       ((__MODE__) == OB_SWD_SWDIO_PA13_SWCLK_PF0))

#define IS_OB_USER_BOOT(__BOOT__)                     (((__BOOT__) == OB_BOOT_FROM_OB) || \
                                                       ((__BOOT__) == OB_BOOT_FROM_MAINFLASH))

#define IS_OB_SECMEM_SIZE(VALUE)                      ((VALUE) <= FLASH_PAGE_NB)

#define IS_FLASH_LATENCY(__LATENCY__)                  (((__LATENCY__) == FLASH_LATENCY_0)  || \
                                                        ((__LATENCY__) == FLASH_LATENCY_1)  || \
                                                        ((__LATENCY__) == FLASH_LATENCY_2)  || \
                                                        ((__LATENCY__) == FLASH_LATENCY_3))

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

#endif /* __PY32F032_HAL_FLASH_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
