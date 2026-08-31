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

/** @defgroup FLASH FLASH
  * @brief FLASH HAL module driver
  * @{
  */

#ifdef HAL_FLASH_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @defgroup FLASH_Private_Variables FLASH Private Variables
  * @{
  */

/**
  * @brief  Variable used for Program/Erase sectors under interruption
  */
FLASH_ProcessTypeDef pFlash  = {.Lock = HAL_UNLOCKED,
                                .ErrorCode = HAL_FLASH_ERROR_NONE,
                                .ProcedureOnGoing = 0,
                                .Address = 0U,
                                .Busy = FLASH_FLAG_BSY,
                                .Bank = FLASH_BANK_0,
                                .PageOrSector = 0U,
                                .NbPagesSectorsToErase = 0U};
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup FLASH_Exported_Functions FLASH Exported Functions
  * @{
  */

/** @defgroup FLASH_Exported_Functions_Group1 Programming operation functions
  *  @brief   Programming operation functions
  *
@verbatim
 ===============================================================================
                  ##### Programming operation functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to manage the FLASH
    program operations.

@endverbatim
  * @{
  */

/**
  * @brief  Program of a page at a specified address.
  * @param  Address Specifies the address to be programmed.
  * @param  DataAddr Page Start Address
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_PageProgram(uint32_t Address, uint32_t * DataAddr )
{
   return HAL_FLASH_Program(FLASH_TYPEPROGRAM_PAGE, Address, DataAddr);
}

/**
  * @brief  Program double word or fast program of a row at a specified address.
  * @param  TypeProgram Indicate the way to program at a specified address.
  *         This parameter can be a value of @ref FLASH_Type_Program.
  * @param  Address specifies the address to be programmed.
  * @param  DataAddr specifies the data to be programmed.
  *
  * @retval HAL_Status
  */
HAL_StatusTypeDef HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint32_t * DataAddr)
{
  HAL_StatusTypeDef status = HAL_ERROR;

  /* Check the parameters */
  assert_param(IS_FLASH_TYPEPROGRAM(TypeProgram));
  assert_param(IS_FLASH_PROGRAM_ADDRESS(Address));

  /* must be the first address of the PAGE */
  if(Address%FLASH_PAGE_SIZE)
  {
    return HAL_ERROR;
  }

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

    FLASH_Program_Page(Address, DataAddr);

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

    /* If the program operation is completed, disable the PG Bit */
    CLEAR_BIT(FLASH->CR, FLASH_CR_PG);
    
    /* In case of error, stop programming procedure */
    if (status != HAL_OK)
    {
      return status;
    }
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  /* return status */
  return status;
}


/**
  * @brief  Program the User Data.
  * @param  Address Specifies the address to be programmed.
  * @param  DataAddr Page Start Address
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_UserDataProgram(uint32_t Address, uint32_t * DataAddr )
{
  HAL_StatusTypeDef status = HAL_ERROR;

  /* Process Locked */
  __HAL_LOCK(&pFlash);
    
  assert_param(IS_FLASH_PROGRAM_USERDATA_ADDRESS(Address));

  /* must be the first address of the PAGE */
  if(Address%FLASH_PAGE_SIZE)
  {
    return HAL_ERROR;
  }

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if(status == HAL_OK)
  {
    /* Check USERLOCK Bit */
    if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_USRLOCK) != 0)
    {
       /* Process Unlocked */
       __HAL_UNLOCK(&pFlash);
       return HAL_ERROR;
    }
    
    FLASH_Program_UserData(Address, DataAddr);

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
    /* If the program operation is completed, disable the UPG Bit */
    CLEAR_BIT(FLASH->CR, FLASH_CR_UPG);
    /* In case of error, stop programming procedure */
    if (status != HAL_OK)
    {
      return status;
    }
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  return status;
}

/**
  * @brief  Program the User Data.
  * @param  Address Specifies the address to be programmed.
  * @param  DataAddr Page Start Address
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_UserDataProgram_IT(uint32_t Address, uint32_t * DataAddr )
{
  HAL_StatusTypeDef status = HAL_ERROR;

  /* Process Locked */
  __HAL_LOCK(&pFlash);
    
  assert_param(IS_FLASH_PROGRAM_USERDATA_ADDRESS(Address));

  /* must be the first address of the PAGE */
  if(Address%FLASH_PAGE_SIZE)
  {
    return HAL_ERROR;
  }

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if(status == HAL_OK)
  {
    /* Check USERLOCK Bit */
    if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_USRLOCK) != 0)
    {
       /* Process Unlocked */
       __HAL_UNLOCK(&pFlash);
       return HAL_ERROR;
    }
        /* Set internal variables used by the IRQ handler */
    pFlash.ProcedureOnGoing = FLASH_TYPEPROGRAM_USERDATA;
    pFlash.Address = Address;

    /* Enable End of Operation and Error interrupts */
    __HAL_FLASH_ENABLE_IT(FLASH_IT_EOP | FLASH_IT_OPERR);

    FLASH_Program_UserData(Address, DataAddr);
  }

  return status;
}

/**
  * @brief  Program of a page at a specified address with interrupt enabled.
  * @param  Address  Specifies the address to be programmed.
  * @param  DataAddr Specifies the buffer address to be programmed.
  *
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_PageProgram_IT(uint32_t Address, uint32_t *DataAddr)
{
  return HAL_FLASH_Program_IT(FLASH_TYPEPROGRAM_PAGE, Address, DataAddr);
}

/**
  * @brief  Program double word or fast program of a row at a specified address with interrupt enabled.
  * @param  TypeProgram Indicate the way to program at a specified address.
  *         This parameter can be a value of @ref FLASH_Type_Program.
  * @param  Address specifies the address to be programmed.
  * @param  DataAddr specifies the data to be programmed.
  *
  * @retval HAL_Status
  */
HAL_StatusTypeDef HAL_FLASH_Program_IT(uint32_t TypeProgram, uint32_t Address, uint32_t *DataAddr)
{
  HAL_StatusTypeDef status;

  /* Check the parameters */
  assert_param(IS_FLASH_TYPEPROGRAM(TypeProgram));
  assert_param(IS_FLASH_PROGRAM_ADDRESS(Address));

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Reset error code */
  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if (status != HAL_OK)
  {
    /* Process Unlocked */
    __HAL_UNLOCK(&pFlash);
  }
  else
  {
    /* Set internal variables used by the IRQ handler */
    pFlash.ProcedureOnGoing = TypeProgram;
    pFlash.Address = Address;

    /* Enable End of Operation and Error interrupts */
    __HAL_FLASH_ENABLE_IT(FLASH_IT_EOP | FLASH_IT_OPERR);

    FLASH_Program_Page(Address, DataAddr);
  }

  return status;
}

/**
  * @brief  Handle FLASH interrupt request.
  * @retval None
  */
void HAL_FLASH_IRQHandler(void)
{
  uint32_t tmp_page;
  uint32_t error;

  /* If the operation is completed, disable the PG, MER, PER, SER Bit */
  CLEAR_BIT(FLASH->CR, (FLASH_CR_PG | FLASH_CR_MER | FLASH_CR_PER | FLASH_CR_SER | FLASH_CR_UPER | FLASH_CR_UPG ));

  /* Check FLASH operation error flags */
  error = (FLASH->SR & FLASH_FLAG_SR_ERRORS);

  /* check operation was a program or erase */
  if ((pFlash.ProcedureOnGoing & (FLASH_TYPEPROGRAM_PAGE)) != 0x00U)
  {
    /* return adress being programmed */
    tmp_page = pFlash.Address;
  }
  else if ((pFlash.ProcedureOnGoing & (FLASH_TYPEPROGRAM_USERDATA)) != 0x00U)
  {
    /* return adress being programmed */
    tmp_page = pFlash.Address;
  }
  else if ((pFlash.ProcedureOnGoing &  (FLASH_TYPEERASE_SECTORERASE | FLASH_TYPEERASE_PAGEERASE )) != 0x00U)
  {
    /* return page number being erased (0 for mass erase) */
    tmp_page = pFlash.PageOrSector;
  }
  else if ((pFlash.ProcedureOnGoing &  FLASH_TYPEERASE_MASSERASE ) != 0x00U)
  {
    tmp_page = pFlash.Bank;
  }
  else if ((pFlash.ProcedureOnGoing &  FLASH_TYPEERASE_USERDATAERASE ) != 0x00U)
  {
    tmp_page = pFlash.PageOrSector;
  }
  else
  {

  }

  if (error != 0U)
  {
    /* Save the error code */
    pFlash.ErrorCode |= error;

    /* Clear error programming flags */
    __HAL_FLASH_CLEAR_FLAG(error);

    /* Stop the procedure ongoing */
    pFlash.ProcedureOnGoing = FLASH_TYPENONE;

    /* Error callback */
    HAL_FLASH_OperationErrorCallback(tmp_page);
  }

  /* Check FLASH End of Operation flag */
  if (__HAL_FLASH_GET_FLAG(FLASH_FLAG_EOP) != 0x00U)
  {
    /* Clear FLASH End of Operation pending bit */
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP);

    if (pFlash.ProcedureOnGoing == FLASH_TYPEERASE_PAGEERASE)
    {
      /* Nb of pages to erased can be decreased */
      pFlash.NbPagesSectorsToErase--;

      /* Check if there are still pages to erase*/
      if (pFlash.NbPagesSectorsToErase != 0x00U)
      {
        /* Increment page number */
        pFlash.PageOrSector += FLASH_PAGE_SIZE;
        FLASH_PageErase(pFlash.PageOrSector);
      }
      else
      {
        /* No more pages to erase: stop erase pages procedure */
        pFlash.ProcedureOnGoing = FLASH_TYPENONE;
      }
    }
    else if (pFlash.ProcedureOnGoing == FLASH_TYPEERASE_SECTORERASE)
    {
      /* Nb of sectors to erased can be decreased */
      pFlash.NbPagesSectorsToErase--;

      /* Check if there are still pages to erase*/
      if (pFlash.NbPagesSectorsToErase != 0x00U)
      {
        /* Increment page number */
        pFlash.PageOrSector += FLASH_SECTOR_SIZE;
        FLASH_SectorErase(pFlash.PageOrSector);
      }
      else
      {
        /* No more pages to erase: stop erase sectors procedure */
        pFlash.ProcedureOnGoing = FLASH_TYPENONE;
                
      }
    }
    else
    {
      /*Stop the ongoing procedure */
      pFlash.ProcedureOnGoing = FLASH_TYPENONE;
       
    }

    /* User callback */
    HAL_FLASH_EndOfOperationCallback(tmp_page);
  }

  if (pFlash.ProcedureOnGoing == FLASH_TYPENONE)
  {
    /* Disable End of Operation and Error interrupts */
    __HAL_FLASH_DISABLE_IT(FLASH_IT_EOP | FLASH_IT_OPERR);

    /* Process Unlocked */
    __HAL_UNLOCK(&pFlash);
  }
}

/**
  * @brief  FLASH end of operation interrupt callback.
  * @param  ReturnValue The value saved in this parameter depends on the ongoing procedure:
  *           @arg Mass Erase: Bank number which has been requested to erase
  *           @arg Page Erase: Page which has been erased
  *                            (if 0xFFFFFFFF, it means that all the selected pages have been erased)
  *           @arg Program: Address which was selected for data program
  * @retval None
  */
__weak void HAL_FLASH_EndOfOperationCallback(uint32_t ReturnValue)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(ReturnValue);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_FLASH_EndOfOperationCallback could be implemented in the user file
   */
}

/**
  * @brief  FLASH operation error interrupt callback.
  * @param  ReturnValue The value saved in this parameter depends on the ongoing procedure:
  *           @arg Mass Erase: Bank number which has been requested to erase
  *           @arg Page Erase: Page number which returned an error
  *           @arg Program: Address which was selected for data program
  * @retval None
  */
__weak void HAL_FLASH_OperationErrorCallback(uint32_t ReturnValue)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(ReturnValue);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_FLASH_OperationErrorCallback could be implemented in the user file
   */
}

/**
  * @}
  */

/** @defgroup FLASH_Exported_Functions_Group2 Peripheral Control functions
  * @brief   Management functions
  *
@verbatim
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the FLASH
    memory operations.

@endverbatim
  * @{
  */

/**
  * @brief  Unlock the FLASH control register access.
  * @retval HAL_Status
  */
HAL_StatusTypeDef HAL_FLASH_Unlock(void)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (READ_BIT(FLASH->CR, FLASH_CR_LOCK) != 0U)
  {
    /* Authorize the FLASH Registers access */
    WRITE_REG(FLASH->KEYR, FLASH_KEY1);
    WRITE_REG(FLASH->KEYR, FLASH_KEY2);

    /* verify Flash is unlocked */
    if (READ_BIT(FLASH->CR, FLASH_CR_LOCK) != 0U)
    {
      status = HAL_ERROR;
    }
  }

  return status;
}

/**
  * @brief  Lock the FLASH control register access.
  * @retval HAL_Status
  */
HAL_StatusTypeDef HAL_FLASH_Lock(void)
{
  HAL_StatusTypeDef status = HAL_ERROR;

  /* Set the LOCK Bit to lock the FLASH Registers access */
  SET_BIT(FLASH->CR, FLASH_CR_LOCK);

  /* verify Flash is locked */
  if (READ_BIT(FLASH->CR, FLASH_CR_LOCK) != 0U)
  {
    status = HAL_OK;
  }

  return status;
}

/**
  * @brief  Unlock the FLASH Option Bytes Registers access.
  * @retval HAL_Status
  */
HAL_StatusTypeDef HAL_FLASH_OB_Unlock(void)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (READ_BIT(FLASH->CR, FLASH_CR_OPTLOCK) != 0U)
  {
    /* Authorizes the Option Byte register programming */
    WRITE_REG(FLASH->OPTKEYR, FLASH_OPTKEY1);
    WRITE_REG(FLASH->OPTKEYR, FLASH_OPTKEY2);

    /* verify option bytes are unlocked */
    if (READ_BIT(FLASH->CR, FLASH_CR_OPTLOCK) != 0U)
    {
      status = HAL_ERROR;
    }
  }

  return status;
}

/**
  * @brief  Lock the FLASH Option Bytes Registers access.
  * @retval HAL_Status
  */
HAL_StatusTypeDef HAL_FLASH_OB_Lock(void)
{
  HAL_StatusTypeDef status = HAL_ERROR;

  /* Set the OPTLOCK Bit to lock the FLASH Option Byte Registers access */
  SET_BIT(FLASH->CR, FLASH_CR_OPTLOCK);

  /* Verify option bytes are locked */
  if (READ_BIT(FLASH->CR, FLASH_CR_OPTLOCK) != 0U)
  {
    status = HAL_OK;
  }

  return status;
}

/**
  * @brief  Launch the option byte loading.
  * @retval HAL_Status
  */
HAL_StatusTypeDef HAL_FLASH_OB_Launch(void)
{
  /* Set the bit to force the option byte reloading */
  SET_BIT(FLASH->CR, FLASH_CR_OBL_LAUNCH);

  /* Wait for last operation to be completed */
  return (FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE));
}


/**
  * @}
  */

/** @defgroup FLASH_Exported_Functions_Group3 Peripheral State and Errors functions
  * @brief   Peripheral Errors functions
  *
@verbatim
 ===============================================================================
                ##### Peripheral Errors functions #####
 ===============================================================================
    [..]
    This subsection permits to get in run-time Errors of the FLASH peripheral.

@endverbatim
  * @{
  */

/**
  * @brief  Get the specific FLASH error flag.
  * @retval FLASH_ErrorCode. The returned value can be:
  *            @arg HAL_FLASH_ERROR_NONE: No error set
  *            @arg HAL_FLASH_ERROR_WRP: FLASH Write protection error
  *            @arg HAL_FLASH_ERROR_RDERR: FLASH PCROP read error
  *            @arg HAL_FLASH_ERROR_OPTV: FLASH Option validity error
  */
uint32_t HAL_FLASH_GetError(void)
{
  return pFlash.ErrorCode;
}

/**
  * @}
  */

/**
  * @brief  Flash Enter Lpmode Delay time
  * @param  Flash_Delay The value be one of the follow:
  *           @arg Flash_EnterLpmodeDelay_1HSIDIVCLOCK: Wait 1 HSIDIV Clock
  *           @arg Flash_EnterLpmodeDelay_2HSIDIVCLOCK: Wait 2 HSIDIV Clock
  *           @arg Flash_EnterLpmodeDelay_3HSIDIVCLOCK: Wait 3 HSIDIV Clock
  *           @arg Flash_EnterLpmodeDelay_4HSIDIVCLOCK: Wait 4 HSIDIV Clock
  *           @arg Flash_EnterLpmodeDelay_5HSIDIVCLOCK: Wait 5 HSIDIV Clock
  *           @arg Flash_EnterLpmodeDelay_6HSIDIVCLOCK: Wait 6 HSIDIV Clock
  *           @arg Flash_EnterLpmodeDelay_7HSIDIVCLOCK: Wait 7 HSIDIV Clock
  * @retval None
  */
void HAL_FLASH_SetEnterLpModeDelay(uint32_t Flash_Delay)
{
  MODIFY_REG(FLASH->LPCR, FLASH_LPCR_LPRUN_ENTERT, Flash_Delay);
}

/**
  * @brief  Flash Exit Lpmode Delay time
  * @param  Flash_Delay The value be one of the follow:
  *           @arg Flash_ExitLpmodeDelay_1HSIDIVCLOCK: Wait 1 HSIDIV Clock
  *           @arg Flash_ExitLpmodeDelay_2HSIDIVCLOCK: Wait 2 HSIDIV Clock
  *           @arg Flash_ExitLpmodeDelay_3HSIDIVCLOCK: Wait 3 HSIDIV Clock
  *           @arg Flash_ExitLpmodeDelay_4HSIDIVCLOCK: Wait 4 HSIDIV Clock
  *           @arg Flash_ExitLpmodeDelay_5HSIDIVCLOCK: Wait 5 HSIDIV Clock
  *           @arg Flash_ExitLpmodeDelay_6HSIDIVCLOCK: Wait 6 HSIDIV Clock
  *           @arg Flash_ExitLpmodeDelay_7HSIDIVCLOCK: Wait 7 HSIDIV Clock
  * @retval None
  */
void HAL_FLASH_SetExitLpModeDelay(uint32_t Flash_Delay)
{
  MODIFY_REG(FLASH->LPCR, FLASH_LPCR_LPRUN_EXITT, Flash_Delay);
}

/**
  * @brief  Enable Flash Sleep
  * @retval None
  */
void HAL_FLASH_EnableFlashSleep()
{
  SET_BIT(FLASH->LPCR, FLASH_LPCR_SLEEP_EN);
}

/**
  * @brief  Disable Flash Sleep
  * @retval None
  */
void HAL_FLASH_DisableFlashSleep()
{
  CLEAR_BIT(FLASH->LPCR, FLASH_LPCR_SLEEP_EN);
}

/**
  * @brief  Set Flash Sleep Time
  * @param  Sleep_Time The value Sleep Time
  * @retval None
  */
void HAL_FLASH_SetFlashSleepTime(uint32_t Sleep_Time)
{
  MODIFY_REG(FLASH->LPCR, FLASH_LPCR_SLEEP_TIME, Sleep_Time<<FLASH_LPCR_SLEEP_TIME_Pos);
}

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/

/** @addtogroup FLASH_Private_Functions
  * @{
  */

/**
  * @brief  Wait for a FLASH operation to complete.
  * @param  Timeout maximum flash operation timeout.
  * @retval HAL_Status
  */
HAL_StatusTypeDef FLASH_WaitForLastOperation(uint32_t Timeout)
{
  /* Wait for the FLASH operation to complete by polling on BUSY flag to be reset.
     Even if the FLASH operation fails, the BUSY flag will be reset and an error
     flag will be set */

  uint32_t tickstart = HAL_GetTick();
  uint32_t error;

  while ((__HAL_FLASH_GET_FLAG(FLASH_FLAG_BSY) !=0 ) )
  {
    if ((HAL_GetTick() - tickstart) > Timeout)
    {
      return HAL_TIMEOUT;
    }
  }

  /* Check FLASH operation error flags */
  error = (FLASH->SR & FLASH_FLAG_SR_ERRORS);
  if (error != 0u)
  {
    /* Save the error code */
    pFlash.ErrorCode |= error;

    /* Clear error programming flags */
    __HAL_FLASH_CLEAR_FLAG(error);

    return HAL_ERROR;
  }

  /* Check FLASH End of Operation flag  */
  if (__HAL_FLASH_GET_FLAG(FLASH_FLAG_EOP))
  {
    /* Clear FLASH End of Operation pending bit */
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP);
  }

  /* If there is an error flag set */
  return HAL_OK;
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

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
