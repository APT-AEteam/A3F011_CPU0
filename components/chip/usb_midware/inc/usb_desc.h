/***********************************************************************//** 
 * \file  usb_desc.h
 * \brief  Descriptor Header for Custom HID Demo
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version	<th>Author  <th>Description
 * <tr><td> 2024-6-03 <td>V0.0	<td>WNN   	<td>initial
 * </table>
 * *********************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_DESC_H
#define __USB_DESC_H

#include <stdint.h>



/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
#define USB_DEVICE_DESCRIPTOR_TYPE              0x01
#define USB_CONFIGURATION_DESCRIPTOR_TYPE       0x02
#define USB_STRING_DESCRIPTOR_TYPE              0x03
#define USB_INTERFACE_DESCRIPTOR_TYPE           0x04
#define USB_ENDPOINT_DESCRIPTOR_TYPE            0x05

#define HID_DESCRIPTOR_TYPE                     0x21
#define CUSTOMHID_SIZ_HID_DESC                  0x09
#define CUSTOMHID_OFF_HID_DESC                  0x12

#define CUSTOMHID_SIZ_DEVICE_DESC               18
#define CUSTOMHID_SIZ_CONFIG_DESC               41
#define CUSTOMHID_SIZ_REPORT_DESC               39  //163
#define CUSTOMHID_SIZ_STRING_LANGID             4
#define CUSTOMHID_SIZ_STRING_VENDOR             38
#define CUSTOMHID_SIZ_STRING_PRODUCT            34  //32
#define CUSTOMHID_SIZ_STRING_SERIAL             26

#define STANDARD_ENDPOINT_DESC_SIZE             0x09

#define VEND_ID0 0x83
#define VEND_ID1 0x04
#define PROD_ID0 0x52
#define PROD_ID1 0x57

extern const uint8_t g_byCustomHidDeviceDescriptor[CUSTOMHID_SIZ_DEVICE_DESC];
extern const uint8_t g_byCustomHidConfigDescriptor[CUSTOMHID_SIZ_CONFIG_DESC];
extern const uint8_t g_byCustomHidReportDescriptor[CUSTOMHID_SIZ_REPORT_DESC];

#endif