/**
  ******************************************************************************
  * @file    py32f032_hal_flash.c
  * @author  MCU Application Team
  * @brief   FLASH HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of the internal FLASH memory:
  *           + Program operations functions
  *           + Memory Control functions 
  *           + Peripheral State functions
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

/* Includes ------------------------------------------------------------------*/
#include "py32f0xx_hal.h"
#include "py32f032_hal_flash_ex.h"

/** @addtogroup PY32F032_HAL_Driver
  * @{
  */

/** @defgroup FLASHEx FLASHEx
  * @brief FLASH Extended HAL module driver
  * @{
  */

#ifdef HAL_FLASH_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup FLASHEx_Private_Functions FLASHEx Private Functions
  * @{
  */
static HAL_StatusTypeDef FLASH_OB_WRPConfig(uint32_t WRPArea);
static HAL_StatusTypeDef FLASH_OB_PCROPConfig(uint32_t PCROPStartAddr, uint32_t PCROPEndAddr);
static uint32_t          FLASH_OB_GetWRP(void);
static uint32_t          FLASH_OB_GetRDP(void);
static uint32_t          FLASH_OB_GetUser(void);
static void              FLASH_OB_GetPCROP(uint32_t *PCROPStartAddr, uint32_t *PCROPEndAddr);
static void              FLASH_OB_OptrConfig(uint32_t UserType, uint32_t UserConfig, uint32_t RDPLevel);
static HAL_StatusTypeDef FLASH_OB_SecMemConfig(uint32_t SecMemSize);
static void              FLASH_OB_GetSecMem(uint32_t *SecMemSize);

/**
  * @}
  */

/* Exported functions -------------------------------------------------------*/
/** @defgroup FLASHEx_Exported_Functions FLASHEx Exported Functions
  * @{
  */

/** @defgroup FLASHEx_Exported_Functions_Group1 Extended IO operation functions
  * @brief   Extended IO operation functions
  *
@verbatim
 ===============================================================================
                ##### Extended programming operation functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to manage the Extended FLASH
    programming operations Operations.

@endverbatim
  * @{
  */
/**
  * @brief  Perform a mass erase or erase the specified FLASH memory pages.
  * @param[in]  pEraseInit pointer to an FLASH_EraseInitTypeDef structure that
  *         contains the configuration information for the erasing.
  * @param[out]  PageError pointer to variable that contains the configuration
  *         information on faulty page in case of error (0xFFFFFFFF means that all
  *         the pages have been correctly erased).
  * @retval HAL_Status
  */
HAL_StatusTypeDef HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *PageError)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t address_index = 0;

  /* Check the parameters */
  assert_param(IS_FLASH_TYPEERASE(pEraseInit->TypeErase));

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

    if ((pEraseInit->TypeErase & FLASH_TYPEERASE_MASSERASE) != 0)
    {
      /* Mass erase to be done */
      FLASH_MassErase();

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

      /* If the erase operation is completed, disable the MER Bit */
      CLEAR_BIT(FLASH->CR, FLASH_CR_MER);
    }
    else if(pEraseInit->TypeErase == FLASH_TYPEERASE_PAGEERASE)
    {
      /* Page Erase is requested */
      /* Check the parameters */
      assert_param(IS_FLASH_PROGRAM_ADDRESS(pEraseInit->PageAddress));
      assert_param(IS_FLASH_NB_PAGES(pEraseInit->PageAddress, pEraseInit->NbPages));

      /*Initialization of PageSectorError variable*/
      *PageError = 0xFFFFFFFFU;

      /* Erase page by page to be done*/
      for(address_index = pEraseInit->PageAddress;
          address_index < ((pEraseInit->NbPages * FLASH_PAGE_SIZE) + pEraseInit->PageAddress);
          address_index += FLASH_PAGE_SIZE)
      {
        FLASH_PageErase(address_index);

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
        /* If the erase operation is completed, disable the PER Bit */
        CLEAR_BIT(FLASH->CR, FLASH_CR_PER);
        if (status != HAL_OK)
        {
          /* In case of error, stop erase procedure and return the faulty address */
          *PageError = address_index;
          break;
        }
      }
      
    }
    else if(pEraseInit->TypeErase == FLASH_TYPEERASE_SECTORERASE)
    {
      /* Sector Erase is requested */
      /* Check the parameters */
      assert_param(IS_FLASH_PROGRAM_ADDRESS(pEraseInit->SectorAddress));
      assert_param(IS_FLASH_NB_SECTORS(pEraseInit->SectorAddress, pEraseInit->NbSectors));


      /*Initialization of PageSectorError variable*/
      *PageError = 0xFFFFFFFFU;

      /* Erase sector by sector to be done*/
      for(address_index = pEraseInit->SectorAddress;
          address_index < ((pEraseInit->NbSectors * FLASH_SECTOR_SIZE) + pEraseInit->SectorAddress);
          address_index += FLASH_SECTOR_SIZE)
      {
        FLASH_SectorErase(address_index);

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
        /* If the erase operation is completed, disable the SER Bit */
        CLEAR_BIT(FLASH->CR, FLASH_CR_SER);
        if (status != HAL_OK)
        {
          /* In case of error, stop erase procedure and return the faulty address */
          *PageError = address_index;
          break;
        }
      }  
      
    }
    else if(pEraseInit->TypeErase == FLASH_TYPEERASE_USERDATAERASE)
    {
      address_index = pEraseInit->UserDataAddress;

      /* Check USERLOCK Bit */
      if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_USRLOCK) != 0)
      {
         *PageError = address_index;
        
         /* Process Unlocked */
         __HAL_UNLOCK(&pFlash);
         return HAL_ERROR;
      }
          
      /* Wait for last operation to be completed */
      if (FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE) == HAL_OK)
      {
        /*Initialization of PageSectorError variable*/
        *PageError = 0xFFFFFFFFU;

        FLASH_UserDataErase(pEraseInit->UserDataAddress);
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
        /* If the erase operation is completed, disable the UPER Bit */
        CLEAR_BIT(FLASH->CR, FLASH_CR_UPER);
        if (status != HAL_OK)
        {
          /* In case of error, stop erase procedure and return the faulty address */
          *PageError = address_index;
        } 
      }
    }
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  return status;
}

/**
  * @brief  Perform a mass erase or erase the specified FLASH memory pages with interrupt enabled.
  * @param  pEraseInit pointer to an FLASH_EraseInitTypeDef structure that
  *         contains the configuration information for the erasing.
  * @retval HAL_Status
  */
HAL_StatusTypeDef HAL_FLASHEx_Erase_IT(FLASH_EraseInitTypeDef *pEraseInit)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Check the parameters */
  assert_param(IS_FLASH_TYPEERASE(pEraseInit->TypeErase));

  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

  /* save procedure for interrupt treatment */
  pFlash.ProcedureOnGoing = pEraseInit->TypeErase;

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if (status != HAL_OK)
  {
    /* Process Unlocked */
    __HAL_UNLOCK(&pFlash);
  }
  else  
  {
    /* Enable End of Operation and Error interrupts */
    __HAL_FLASH_ENABLE_IT(FLASH_IT_EOP | FLASH_IT_OPERR);
  
    if(pEraseInit->TypeErase == FLASH_TYPEERASE_MASSERASE)
    {
      /* Mass erase to be done */
      FLASH_MassErase();
    }
    else if(pEraseInit->TypeErase == FLASH_TYPEERASE_PAGEERASE)
    {
      /* Erase by page to be done */
      pFlash.NbPagesSectorsToErase = pEraseInit->NbPages;
      pFlash.PageOrSector = pEraseInit->PageAddress;

      /*Erase 1st page and wait for IT */
      FLASH_PageErase(pEraseInit->PageAddress);
    }
    else if(pEraseInit->TypeErase == FLASH_TYPEERASE_SECTORERASE)
    {
      /* Erase by sector to be done */
      pFlash.NbPagesSectorsToErase = pEraseInit->NbSectors;
      pFlash.PageOrSector = pEraseInit->SectorAddress;
        
      FLASH_SectorErase(pEraseInit->SectorAddress);
    }
    else if (pEraseInit->TypeErase == FLASH_TYPEERASE_USERDATAERASE)
    {
      /* Set Page to UserDataAddress for Interrupt callback management */
      pFlash.PageOrSector = pEraseInit->UserDataAddress;
     
      FLASH_UserDataErase(pEraseInit->UserDataAddress);
    }
    else
    {
      /* nothing to do */
    }
  }
  return status;
}

/**
  * @brief  Program Option bytes.
  * @param  pOBInit pointer to an FLASH_OBInitStruct structure that
  *         contains the configuration information for the programming.
  * @retval HAL_Status
  */
HAL_StatusTypeDef HAL_FLASHEx_OBProgram(FLASH_OBProgramInitTypeDef *pOBInit)
{
  uint32_t optr = 0;
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_OPTIONBYTE(pOBInit->OptionType));

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

  /* Write protection configuration */
  if ((pOBInit->OptionType & OPTIONBYTE_WRP) != 0U)
  {
    /* Configure of Write protection on the selected area */
    if (FLASH_OB_WRPConfig(pOBInit->WRPSector) != HAL_OK)
    {
      status = HAL_ERROR;
    }
  }

  if((pOBInit->OptionType & (OPTIONBYTE_RDP | OPTIONBYTE_USER)) == (OPTIONBYTE_RDP | OPTIONBYTE_USER))
  {
    /* Configure the user option bytes */
    FLASH_OB_OptrConfig(pOBInit->USERType, pOBInit->USERConfig, pOBInit->RDPLevel);
  }
  else if ((pOBInit->OptionType & OPTIONBYTE_RDP) != 0U)
  {
    /* Only modify RDP so get current user data */
    optr = FLASH_OB_GetUser();
    /* Configure the Read protection level */
    FLASH_OB_OptrConfig(optr, optr, pOBInit->RDPLevel);
  }
  else if ((pOBInit->OptionType & OPTIONBYTE_USER) != 0U)
  {
    /* Only modify user so get current RDP level */
    optr = FLASH_OB_GetRDP();
    /* Configure the user option bytes */
    FLASH_OB_OptrConfig(pOBInit->USERType, pOBInit->USERConfig, optr);
  }
  else
  {
    /* nothing to do */
  }
  /* PCROP Configuration */
  if ((pOBInit->OptionType & OPTIONBYTE_PCROP) != 0U)
  {
    if (pOBInit->PCROPStartAddr != pOBInit->PCROPEndAddr)
    {
      /* Configure the Proprietary code readout protection */
      if (FLASH_OB_PCROPConfig( pOBInit->PCROPStartAddr, pOBInit->PCROPEndAddr) != HAL_OK)
      {
        status = HAL_ERROR;
      }
    }
  }

  /* PCROP Configuration */
  if ((pOBInit->OptionType & OPTIONBYTE_SEC) != 0U)
  {
    /* Configure the securable memory area */
    if (FLASH_OB_SecMemConfig(pOBInit->SecSize) != HAL_OK)
    {
      status = HAL_ERROR;
    }
  }

  /* starts to modify Flash Option bytes */
  FLASH->CR |= FLASH_CR_OPTSTRT;
 
  /* trigger program */
  *((__IO uint32_t *)(0x1FFF0F80)) = 0x12344321;

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  return status;
}

/**
  * @brief  Get the Option bytes configuration.
  * @param  pOBInit pointer to an FLASH_OBInitStruct structure that contains the
  *         configuration information.
  * @note   pOBInit->PCROPConfig should indicate which area is requested for PCROP, 
  *         else no information will be returned.
  * @retval None
  */
void HAL_FLASHEx_OBGetConfig(FLASH_OBProgramInitTypeDef *pOBInit)
{
  pOBInit->OptionType = (OPTIONBYTE_WRP | OPTIONBYTE_RDP | OPTIONBYTE_USER | OPTIONBYTE_PCROP | OPTIONBYTE_SEC);

  /* Get Write protection level */
  pOBInit->WRPSector = FLASH_OB_GetWRP();

  /* Get Read protection level */
  pOBInit->RDPLevel = FLASH_OB_GetRDP();

  /* Get the user option bytes */
  pOBInit->USERConfig = FLASH_OB_GetUser();

  FLASH_OB_GetPCROP(&(pOBInit->PCROPStartAddr), &(pOBInit->PCROPEndAddr));

  FLASH_OB_GetSecMem(&(pOBInit->SecSize));
}

/**
  * @brief  Enable the FLASH Securable Memory protection.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_EnableSecMemProtection()
{
  SET_BIT(FLASH->CR, FLASH_CR_SECPROT);

  return HAL_OK;
}


/**
  * @}
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/

/** @addtogroup FLASHEx_Private_Functions
  * @{
  */
/**
  * @brief  Mass erase of FLASH memory.
  * @retval None
  */
void FLASH_MassErase(void)
{
  SET_BIT(FLASH->CR, FLASH_CR_MER);
  *(__IO uint32_t *)(FLASH_BASE) = 0x12344321;
}

/**
  * @brief  Erase the specified FLASH memory page.
  * @param  PageAddress FLASH page to erase.
  *         This parameter must be a value between 0 and (max number of pages in the bank - 1).
  * @retval None
  */
void FLASH_PageErase(uint32_t PageAddress)
{
  /* Check the parameters */
  assert_param(IS_FLASH_PAGE(PageAddress));

  /* Proceed to erase the page */
  SET_BIT(FLASH->CR, FLASH_CR_PER);
  *(__IO uint32_t *)(PageAddress) = 0x12344321;
}

/**
  * @brief  Sector erase of FLASH memory
  * @param  SectorAddress sector erase address
  * @retval None
  */
void FLASH_SectorErase(uint32_t SectorAddress)
{
  SET_BIT(FLASH->CR, FLASH_CR_SER);
  *(__IO uint32_t *)(SectorAddress) = 0x12344321;
}

/**
  * @brief  Page program of FLASH memory
  * @param  Address  Specifies the address to be programmed.
  * @param  DataAddress  Specifies the data to be programmed
  * @retval None
  */
void FLASH_Program_Page(uint32_t Address, uint32_t * DataAddress)
{
  uint8_t index=0;
  uint32_t dest = Address;
  uint32_t * src = DataAddress;
  uint32_t primask_bit;

  SET_BIT(FLASH->CR, FLASH_CR_PG);
  /* Enter critical section */
  primask_bit = __get_PRIMASK();
  __disable_irq();
  /* 64 words*/
  while(index < 32U) 
  {
    *(uint32_t *)dest = *src;
    src += 1U;
    dest += 4U;
    index++;
    if(index == 31)
    {
      SET_BIT(FLASH->CR, FLASH_CR_PGSTRT);
    }
  }
  /* Exit critical section: restore previous priority mask */
  __set_PRIMASK(primask_bit);
}

/**
  * @brief  UserData erase 
  * @retval None
  */
void FLASH_UserDataErase(uint32_t UserDataAddress)
{
  SET_BIT(FLASH->CR, FLASH_CR_UPER);
  *(__IO uint32_t *)(UserDataAddress) = 0x12344321;
}

/**
  * @brief  Program the UserData
  * @retval None
  */
void FLASH_Program_UserData(uint32_t Address, uint32_t * DataAddress)
{
  uint8_t index=0;
  uint32_t dest = Address;
  uint32_t * src = DataAddress;
  uint32_t primask_bit;

  SET_BIT(FLASH->CR, FLASH_CR_UPG);
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
      SET_BIT(FLASH->CR, FLASH_CR_UPGSTRT);
    }
  }

  /* Exit critical section: restore previous priority mask */
  __set_PRIMASK(primask_bit);
}

/**
  * @brief  Configure the write protection area into Option Bytes.
  * @param  WRPArea specifies the area to be configured.
  *         This parameter can be a combination of the following values:
  *            @arg OB_WRP_SECTOR_0         : Flash Sector 0
  *            @arg OB_WRP_SECTOR_1         : Flash Sector 1
  *            @arg OB_WRP_SECTOR_2         : Flash Sector 2
  *            @arg OB_WRP_SECTOR_3         : Flash Sector 3
  *            @arg OB_WRP_SECTOR_4         : Flash Sector 4
  *            @arg OB_WRP_SECTOR_5         : Flash Sector 5
  *            @arg OB_WRP_SECTOR_6         : Flash Sector 6
  *            @arg OB_WRP_SECTOR_7         : Flash Sector 7
  *            @arg OB_WRP_SECTOR_8         : Flash Sector 8
  *            @arg OB_WRP_SECTOR_9         : Flash Sector 9
  *            @arg OB_WRP_SECTOR_10        : Flash Sector 10
  *            @arg OB_WRP_SECTOR_11        : Flash Sector 11
  *            @arg OB_WRP_SECTOR_12        : Flash Sector 12
  *            @arg OB_WRP_SECTOR_13        : Flash Sector 13
  *            @arg OB_WRP_SECTOR_14        : Flash Sector 14
  *            @arg OB_WRP_SECTOR_15        : Flash Sector 15
  *            @arg OB_WRP_Pages0to31       : Flash Sector 0
  *            @arg OB_WRP_Pages32to63      : Flash Sector 1 
  *            @arg OB_WRP_Pages64to95      : Flash Sector 2
  *            @arg OB_WRP_Pages96to127     : Flash Sector 3            
  *            @arg OB_WRP_Pages128to159    : Flash Sector 4          
  *            @arg OB_WRP_Pages160to191    : Flash Sector 5         
  *            @arg OB_WRP_Pages192to223    : Flash Sector 6          
  *            @arg OB_WRP_Pages224to255    : Flash Sector 7          
  *            @arg OB_WRP_Pages256to287    : Flash Sector 8           
  *            @arg OB_WRP_Pages288to319    : Flash Sector 9          
  *            @arg OB_WRP_Pages320to351    : Flash Sector 10           
  *            @arg OB_WRP_Pages352to383    : Flash Sector 11        
  *            @arg OB_WRP_Pages384to415    : Flash Sector 12          
  *            @arg OB_WRP_Pages416to447    : Flash Sector 13         
  *            @arg OB_WRP_Pages448to479    : Flash Sector 14           
  *            @arg OB_WRP_Pages480to511    : Flash Sector 15       
  *            @arg OB_WRP_AllPages               : ALL Pages 
  * @retval HAL_Status
  */
static HAL_StatusTypeDef FLASH_OB_WRPConfig(uint32_t WRPArea)
{
  HAL_StatusTypeDef status;

  /* Check the parameters */
  assert_param(IS_OB_WRPAREA(WRPArea));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    FLASH->WRPR = (uint32_t)(~WRPArea);
  }

  return status;
}

/**
  * @brief  Set the read protection level into Option Bytes.
  * @param  RDPLevel specifies the read protection level.
  *         This parameter can be one of the following values:
  *            @arg OB_RDP_LEVEL_0 : No protection
  *            @arg OB_RDP_LEVEL_1 : Memory Read protection
  *            @arg OB_RDP_LEVEL_2 : Full chip protection
  *
  * @retval HAL_Status
  */
HAL_StatusTypeDef HAL_FLASH_OB_RDPConfig(uint32_t RDPLevel)
{
  HAL_StatusTypeDef status;

  /* Check the parameters */
  assert_param(IS_OB_RDP_LEVEL(RDPLevel));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    /* Process Locked */
    __HAL_LOCK(&pFlash);

    /* Clean the error context */
    pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

    /* Configure the RDP level in the option bytes register */
    MODIFY_REG(FLASH->OPTR, FLASH_OPTR_RDP, RDPLevel);

    /* Set OPTSTRT Bit */
    SET_BIT(FLASH->CR, FLASH_CR_OPTSTRT);

    /* trigger program */
    *((__IO uint32_t *)(0x1FFF0F80)) = 0x12344321;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

    /* Process Unlocked */
    __HAL_UNLOCK(&pFlash);
  }

  return status;
}

/**
  * @brief  Program the FLASH User Option Bytes.
  * @param  UserType The FLASH User Option Bytes to be modified.
  *         This parameter can be a combination of @ref FLASH_OB_USER_Type.
  * @param  UserConfig The selected User Option Bytes values:
  *         This parameter can be a combination of the following values:
  *         @ref FLASH_OB_USER_NRST_MODE
  *         @ref FLASH_OB_USER_IWDG_STOP
  *         @ref FLASH_OB_USER_IWDG_SW
  *         @ref FLASH_OB_USER_WWDG_SW
  *         @ref FLASH_OB_USER_NBOOT1
  *         @ref FLASH_OB_USER_BOOT_LOCK
  *         @ref FLASH_OB_USER_BOR_EN
  *         @ref FLASH_OB_USER_BOR_LEV
  *         @ref FLASH_OB_USER_SWD_MODE
  * @param  RDPLevel The selected User RDP Level values:
  *         This parameter can be one of the following values:
  *         @ref OB_RDP_LEVEL_0: No protection
  *         @ref OB_RDP_LEVEL_1: Memory Read protection
  *         @arg OB_RDP_LEVEL_2: Full chip protection
  * @retval HAL_Status
  */
static void FLASH_OB_OptrConfig(uint32_t UserType, uint32_t UserConfig, uint32_t RDPLevel)
{
  uint32_t optr;

  /* Check the parameters */
  assert_param(IS_OB_USER_TYPE(UserType));
  assert_param(IS_OB_USER_CONFIG(UserType, UserConfig));
  assert_param(IS_OB_RDP_LEVEL(RDPLevel));

  /* Configure the RDP level in the option bytes register */
  optr = FLASH->OPTR;
  optr &= ~(UserType | FLASH_OPTR_RDP);
  FLASH->OPTR = (optr | UserConfig | RDPLevel);
}

/**
  * @brief  Configure the Proprietary code readout protection area into Option Bytes.
  * @param  PCROPStartAddr specifies the start address of the Proprietary code readout protection.
  *         This parameter can be an address between begin and end of the bank.
  * @param  PCROPEndAddr specifies the end address of the Proprietary code readout protection.
  *         This parameter can be an address between PCROPStartAddr and end of the bank.
  * @retval HAL_Status
  */
static HAL_StatusTypeDef FLASH_OB_PCROPConfig(uint32_t PCROPStartAddr, uint32_t PCROPEndAddr)
{
  HAL_StatusTypeDef status;
  uint32_t reg_value1;
  uint32_t reg_value2;

  /* Check the parameters */
  assert_param(IS_FLASH_MAIN_MEM_ADDRESS(PCROPStartAddr));
  assert_param(IS_FLASH_MAIN_MEM_ADDRESS(PCROPEndAddr));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    /* Calculate the location of the PCROPStartAddr in FLASH */
    reg_value1 = ((PCROPStartAddr - FLASH_BASE) >> 7);
    reg_value2 = (((PCROPEndAddr - FLASH_BASE) >> 7) << 16) ;

    MODIFY_REG(FLASH->PCROPR,(FLASH_PCROPR_PCROPSR | FLASH_PCROPR_PCROPER), (reg_value1 | reg_value2));
  }

  return status;
}

/**
  * @brief  Configure the Securable memory area into Option Bytes.
  * @note   To configure any option bytes, the option lock bit OPTLOCK must be
  *         cleared with the call of HAL_FLASH_OB_Unlock() function.
  * @note   New option bytes configuration will be taken into account in two cases:
  *         - after an option bytes launch through the call of HAL_FLASH_OB_Launch()
  *         - after a power reset
  * @param  SecSize specifies the number of pages of the Securable memory area,
  *         starting from first page of the bank.
  *         This parameter can be page number between 0 and (max number of pages in the bank - 1)
  * @retval HAL Status
  */
static HAL_StatusTypeDef FLASH_OB_SecMemConfig(uint32_t SecSize)
{
  HAL_StatusTypeDef status;

  assert_param(IS_OB_SECMEM_SIZE(SecSize));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    MODIFY_REG(FLASH->SECR, FLASH_SECR_SEC_SIZE, SecSize);
  }

  return status;
}

/**
  * @brief  Return the Securable memory area configuration into Option Bytes.
  * @param[out]  SecSize specifies the number of pages used in the securable
                 memory area 
  * @retval None
  */
static void FLASH_OB_GetSecMem(uint32_t *SecSize)
{
  /* Get the configuration of the securable memory area */
  *SecSize = READ_BIT(FLASH->SECR, FLASH_SECR_SEC_SIZE);
}


/**
  * @brief  Return the Write Protection configuration into Option Bytes.
  * @retval None
  */
static uint32_t FLASH_OB_GetWRP(void)
{
  return (uint32_t)(~FLASH->WRPR);
}

/**
  * @brief  Return the FLASH Read Protection level into Option Bytes.
  * @retval RDP_Level
  *         This return value can be one of the following values:
  *            @arg OB_RDP_LEVEL_0: No protection
  *            @arg OB_RDP_LEVEL_1: Read protection of the memory
  *            @arg OB_RDP_LEVEL_2: Full chip protection
  */
static uint32_t FLASH_OB_GetRDP(void)
{
  uint32_t rdp_level = READ_BIT(FLASH->OPTR, FLASH_OPTR_RDP);

  if ((rdp_level != OB_RDP_LEVEL_0) && (rdp_level != OB_RDP_LEVEL_2))
  {
    return (OB_RDP_LEVEL_1);
  }
  else
  {
    return rdp_level;
  }
}

/**
  * @brief  Return the FLASH User Option Byte value.
  * @retval OB_user_config
  *         This parameter can be a combination of the following values:
  *         @ref FLASH_OB_USER_NRST_MODE
  *         @ref FLASH_OB_USER_IWDG_STOP
  *         @ref FLASH_OB_USER_IWDG_SW
  *         @ref FLASH_OB_USER_WWDG_SW
  *         @ref FLASH_OB_USER_NBOOT1
  *         @ref FLASH_OB_USER_BOOT_LOCK
  *         @ref FLASH_OB_USER_BOR_EN
  *         @ref FLASH_OB_USER_BOR_LEV
  *         @ref FLASH_OB_USER_SWD_MODE
  */
static uint32_t FLASH_OB_GetUser(void)
{
  uint32_t user_config = READ_REG(FLASH->OPTR);
  CLEAR_BIT(user_config, FLASH_OPTR_RDP);

  return user_config;
}

/**
  * @brief  Return the FLASH PCROP configuration into Option Bytes.
  * @param[out] PCROPStartAddr specifies the address where to copied the start address
  *        of the Proprietary code readout protection.
  * @param[out] PCROPEndAddr specifies the address where to copied the end address of
  *        the Proprietary code readout protection.
  * @retval None
  */
static void FLASH_OB_GetPCROP(uint32_t *PCROPStartAddr, uint32_t *PCROPEndAddr)
{
  uint32_t reg_value;

  /* Calculate PCROPStartAddr by FLASH->PCROP0SR */
  reg_value       = ((READ_REG(FLASH->PCROPR) & FLASH_PCROPR_PCROPSR) << 7);
  *PCROPStartAddr = (reg_value) + FLASH_BASE;

  /* Calculate PCROPEndAddr by FLASH->PCROP0ER */
  reg_value     = (((READ_REG(FLASH->PCROPR) & FLASH_PCROPR_PCROPER) << 7) >> 16);
  *PCROPEndAddr = (reg_value) + FLASH_BASE;
}

/**
  * @}
  */

#endif /* HAL_FLASH_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
