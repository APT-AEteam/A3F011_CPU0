/***********************************************************************
 * \file  usb_desc.c
 * \brief  Descriptors for Custom HID Demo
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version	<th>Author  <th>Description
 * <tr><td> 2024-6-03 <td>V0.0	<td>WNN   	<td>initial
 * </table>
 * *********************************************************************
*/



#include "soc.h"
#include "usb_lib.h"
#include "usb_desc.h"


/* USB Standard Device Descriptor */
const uint8_t g_byCustomHidDeviceDescriptor[CUSTOMHID_SIZ_DEVICE_DESC] =
  {
    0x12,                       /*bLength */
    USB_DEVICE_DESCRIPTOR_TYPE, /*bDescriptorType*/
    0x00,                       /*bcdUSB */
    0x02,
    0x00,                       /*bDeviceClass*/
    0x00,                       /*bDeviceSubClass*/
    0x00,                       /*bDeviceProtocol*/
    0x40,                       /*bMaxPacketSize*/
    VEND_ID0,                   /*idVendor (0x0483)*/
    VEND_ID1,
    PROD_ID0,                   /*idProduct = 0x5750*/
    PROD_ID1,
    0x00,                       /*bcdDevice rel. 2.00*/
    0x02,
    1,                          /*Index of string descriptor describing
                                              manufacturer */
    2,                          /*Index of string descriptor describing
                                             product*/
    3,                          /*Index of string descriptor describing the
                                             device serial number */
    0x01                        /*bNumConfigurations*/
  }
  ; /* CustomHID_DeviceDescriptor */


/* USB Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
const uint8_t g_byCustomHidConfigDescriptor[CUSTOMHID_SIZ_CONFIG_DESC] =
  {
    0x09, /* bLength: Configuration Descriptor size */
    USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType: Configuration */
    CUSTOMHID_SIZ_CONFIG_DESC,
    /* wTotalLength: Bytes returned */
    0x00,
    0x01,         /* bNumInterfaces: 1 interface */
    0x01,         /* bConfigurationValue: Configuration value */
    0x00,         /* iConfiguration: Index of string descriptor describing
                                 the configuration*/
    0xC0,         /* bmAttributes: Self powered */
    0x32,         /* MaxPower 100 mA: this current is used for detecting Vbus  50*2mA=100mA */

    /************** Descriptor of Custom HID interface ****************/
    /* 09 */
    0x09,         /* bLength: Interface Descriptor size */
    USB_INTERFACE_DESCRIPTOR_TYPE,/* bDescriptorType: Interface descriptor type */
    0x00,         /* bInterfaceNumber: Number of Interface */
    0x00,         /* bAlternateSetting: Alternate setting */
    0x02,         /* bNumEndpoints */
    0x03,         /* bInterfaceClass: HID */
    0x00,         /* bInterfaceSubClass : 1=BOOT, 0=no boot */
    0x00,         /* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */
    0,            /* iInterface: Index of string descriptor */
    /******************** Descriptor of Custom HID HID ********************/
    /* 18 */
    0x09,         /* bLength: HID Descriptor size */
    HID_DESCRIPTOR_TYPE, /* bDescriptorType: HID */
    0x10,         /* bcdHID: HID Class Spec release number */
    0x01,
    0x00,         /* bCountryCode: Hardware target country */
    0x01,         /* bNumDescriptors: Number of HID class descriptors to follow */
    0x22,         /* bDescriptorType */
    CUSTOMHID_SIZ_REPORT_DESC,/* wItemLength: Total length of Report descriptor */
    0x00,
    /******************** Descriptor of Custom HID endpoints ******************/
    /* 27 */
    0x07,          /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE, /* bDescriptorType: */
    0x81,          /* bEndpointAddress: Endpoint Address (IN) */
    0x03,          /* bmAttributes: Interrupt endpoint */
    ENPOINT_BUFSZIE,          /* wMaxPacketSize: 64 Bytes max */
    0x00,
    0x0a,          /* bInterval: Polling Interval (unit: ms	·) */
    /* 34 */
    	
    0x07,	/* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,	/* bDescriptorType: Endpoint descriptor type */
    0x01,	/* bEndpointAddress: Endpoint Address (OUT) */
    0x03,	/* bmAttributes: Interrupt endpoint */
    ENPOINT_BUFSZIE,	/* wMaxPacketSize: 64 Bytes max  */
    0x00,
    0x02,	/* bInterval: Polling Interval (unit: ms) */
    /* 41 */
  }
  ; /* CustomHID_ConfigDescriptor */
const uint8_t g_byCustomHidReportDescriptor[CUSTOMHID_SIZ_REPORT_DESC] =
  {

    0x05, 0xFF, // USAGE_PAGE(User define)
    0x09, 0xFF, // USAGE(User define)
    0xa1, 0x01, // COLLECTION (Application)
    0x05, 0x01, // USAGE_PAGE(1)
    0x19, 0x00, // USAGE_MINIMUM(0)
    0x29, 0xFF, // USAGE_MAXIMUM(255)
    0x15, 0x00, // LOGICAL_MINIMUM (0)
    0x25, 0xFF, // LOGICAL_MAXIMUM (255)
    0x75, 0x08, // REPORT_SIZE (8)
    0x95, 0x40, // REPORT_COUNT (64)
    0x81, 0x02, // INPUT (Data,Var,Abs)
    0x05, 0x02, // USAGE_PAGE(2)
    0x19, 0x00, // USAGE_MINIMUM (0)
    0x29, 0xFF, // USAGE_MAXIMUM (255)
    0x15, 0x00, // LOGICAL_MINIMUM (0)
    0x25, 0xFF, // LOGICAL_MAXIMUM (255)
    0x95, 0x08, // REPORT_COUNT (8)
    0x75, 0x40, // REPORT_SIZE (64)
    0x91, 0x02, // OUTPUT (Data,Var,Abs)
    0xc0 // END_COLLECTION
 }; /* ReportDescriptor */


/* USB String Descriptors (optional) */
const uint8_t g_byCustomHidStringLangID[CUSTOMHID_SIZ_STRING_LANGID] =
  {
    CUSTOMHID_SIZ_STRING_LANGID,
    USB_STRING_DESCRIPTOR_TYPE,
    0x09,
    0x04
  }
  ; /* LangID = 0x0409: U.S. English */

const uint8_t CustomHID_StringVendor[CUSTOMHID_SIZ_STRING_VENDOR] =
  {
    CUSTOMHID_SIZ_STRING_VENDOR, /* Size of Vendor string */
    USB_STRING_DESCRIPTOR_TYPE,  /* bDescriptorType*/
    /* Manufacturer: "STMicroelectronics" */
    'A', 0, 'P', 0, 'T', 0, 'C', 0, 'h', 0, 'i', 0, 'p', 0, 'U', 0,
    'S', 0, 'B', 0, 'W', 0, 'r', 0, 'i', 0, 't', 0, 'e', 0, 'r', 0,
    'V', 0, '1', 0
  };

const uint8_t CustomHID_StringProduct[CUSTOMHID_SIZ_STRING_PRODUCT] =
  {
    CUSTOMHID_SIZ_STRING_PRODUCT,          /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'A', 0, 'P', 0, 'T', 0, 'C', 0, 'h', 0, 'i', 0, 'p', 0,
    'U', 0, 'S', 0, 'B', 0, 'W', 0, 'r', 0, 'i', 0, 't', 0,
    'e', 0, 'r', 0
  };
uint8_t CustomHID_StringSerial[CUSTOMHID_SIZ_STRING_SERIAL] =
  {
    CUSTOMHID_SIZ_STRING_SERIAL,           /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'A', 0, 'P', 0, 'T', 0,'3', 0,'2', 0
  };