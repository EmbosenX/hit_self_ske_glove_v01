/* ==================== 用户代码开始 ==================== */
/**
  ******************************************************************************
  * @file           : usb_device.c
  * @version        : v1.0_Cube
  * @brief          : This file implements the USB Device
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* ==================== 用户代码结束 ==================== */

/* Includes ------------------------------------------------------------------*/

#include "usb_device.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"

/* ==================== 用户代码开始 ==================== */

/* ==================== 用户代码结束 ==================== */

/* ==================== 用户代码开始 ==================== */
/* ==================== 私有变量 ==================== */

/* ==================== 用户代码结束 ==================== */

/* ==================== 用户代码开始 ==================== */
/* ==================== 私有函数声明 ==================== */

/* ==================== 用户代码结束 ==================== */

/* USB Device Core handle declaration. */
USBD_HandleTypeDef hUsbDeviceFS;

/*
 * -- Insert your variables declaration here --
 */
/* ==================== 用户代码开始 ==================== */

/* ==================== 用户代码结束 ==================== */

/*
 * -- Insert your external function declaration here --
 */
/* ==================== 用户代码开始 ==================== */

/* ==================== 用户代码结束 ==================== */

/**
  * Init USB device Library, add supported class and start the library
  * @retval None
  */
void MX_USB_DEVICE_Init(void)
{
  /* ==================== 用户代码开始 ==================== */

  /* ==================== 用户代码结束 ==================== */

  /* Init Device Library, add supported class and start the library. */
  if (USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS) != USBD_OK)
  {
    Error_Handler();
  }
  if (USBD_RegisterClass(&hUsbDeviceFS, &USBD_CDC) != USBD_OK)
  {
    Error_Handler();
  }
  if (USBD_CDC_RegisterInterface(&hUsbDeviceFS, &USBD_Interface_fops_FS) != USBD_OK)
  {
    Error_Handler();
  }
  if (USBD_Start(&hUsbDeviceFS) != USBD_OK)
  {
    Error_Handler();
  }

  /* ==================== 用户代码开始 ==================== */
  HAL_PWREx_EnableUSBVoltageDetector();

  /* ==================== 用户代码结束 ==================== */
}

/**
  * @}
  */

/**
  * @}
  */

