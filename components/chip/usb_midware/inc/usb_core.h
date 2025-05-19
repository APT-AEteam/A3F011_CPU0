/***********************************************************************//** 
 * \file  usb_core.h
 * \brief  Standard protocol processing functions prototypes 
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version	<th>Author  <th>Description
 * <tr><td> 2024-6-03 <td>V0.0	<td>WNN   	<td>initial
 * </table>
 * *********************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_CORE_H
#define __USB_CORE_H

#include "soc.h"

typedef enum 
{
  WAIT_SETUP,       /* 0 */
  SETTING_UP,       /* 1 */
  IN_DATA,          /* 2 */
  OUT_DATA,         /* 3 */
  LAST_IN_DATA,     /* 4 */
  LAST_OUT_DATA,    /* 5 */
  WAIT_STATUS_IN,   /* 7 */
  WAIT_STATUS_OUT,  /* 8 */
  STALLED,          /* 9 */
  PAUSE             /* 10 */
} usb_control_status_e;    /* The state machine states of a control pipe */


typedef struct 
{
  uint8_t *Descriptor;
  uint16_t Descriptor_Size;
} usb_descriptor_t, *usb_descriptor_pt;


/* All the request process routines return a value of this type
   If the return value is not SUCCESS or NOT_READY,
   the software will STALL the correspond endpoint */
typedef enum _RESULT
{
  USB_SUCCESS = 0,    /* Process sucessfully */
  USB_ERROR,
  USB_UNSUPPORT,
  USB_NOT_READY       /* The process has not been finished, endpoint will be
                         NAK to further request */
} usb_result_e;


/*============ Definitions at endpoint level ==================*/
typedef struct _ENDPOINT_INFO
{
  /* When send data out of the device,
   CopyData() is used to get data buffer 'Length' bytes data
   if Length is 0, CopyData() returns the total length of the data
    if the request is not supported, returns 0
    if CopyData() returns -1, the calling routine should not proceed
     further and will resume the SETUP process by the class device
   if Length is not 0,
    CopyData() returns a pointer to indicate the data location
   Usb_wLength is the data remain to be sent,
   Usb_wOffset is the Offset of original data
====================================================================
  When receive data from the host,
   CopyData() is used to get user data buffer which is capable to copy Length bytes data from the endpoint buffer.
   if Length is 0, CopyData() returns the available data length,
   if Length is not 0, CopyData() returns user buffer address
   Usb_rLength is the data remain to be received,
   Usb_rPointer is the Offset of data buffer
  */
  uint16_t  Usb_wLength;
  uint16_t  Usb_wOffset;
  uint16_t  PacketSize;
  uint8_t   *(*CopyData)(uint16_t Length);
}
usb_endpoint_info_t;


/*============ Definitions at device level ==================*/
typedef struct 
{
  uint8_t Total_Endpoint;     /* Number of endpoints that are used */
  uint8_t Total_Configuration;/* Number of configuration available */
}usb_device_t;

typedef union
{
  uint16_t w;
  struct BW
  {
    uint8_t bb1;
    uint8_t bb0;
  }
  bw;
} u16_u8_u;

typedef struct _DEVICE_INFO
{
  uint8_t USBbmRequestType;       /* bmRequestType */
  uint8_t USBbRequest;            /* bRequest */
  u16_u8_u USBwValues;         /* wValue */
  u16_u8_u USBwIndexs;         /* wIndex */
  u16_u8_u USBwLengths;        /* wLength */

  uint8_t ControlState;           /* of type CONTROL_STATE */
  uint8_t Current_Feature;
  uint8_t Current_Configuration;   /* Selected configuration */
  uint8_t Current_Interface;       /* Selected interface of current configuration */
  uint8_t Current_AlternateSetting;/* Selected Alternate Setting of current
                                     interface*/

  usb_endpoint_info_t Ctrl_Info;
} usb_device_info_t;


typedef struct _DEVICE_PROP
{
  void (*Init)(void);        /* Initialize the device */
  void (*Reset)(void);       /* Reset routine of this device */

  /* Device dependent process after the status stage */
  void (*Process_Status_IN)(void);
  void (*Process_Status_OUT)(void);

  /* Procedure of process on setup stage of a class specified request with data stage */
  /* All class specified requests with data stage are processed in Class_Data_Setup
   Class_Data_Setup()
    responses to check all special requests and fills ENDPOINT_INFO
    according to the request
    If IN tokens are expected, then wLength & wOffset will be filled
    with the total transferring bytes and the starting position
    If OUT tokens are expected, then rLength & rOffset will be filled
    with the total expected bytes and the starting position in the buffer

    If the request is valid, Class_Data_Setup returns SUCCESS, else UNSUPPORT

   CAUTION:
    Since GET_CONFIGURATION & GET_INTERFACE are highly related to
    the individual classes, they will be checked and processed here.
  */
  usb_result_e (*Class_Data_Setup)(uint8_t RequestNo);

  /* Procedure of process on setup stage of a class specified request without data stage */
  /* All class specified requests without data stage are processed in Class_NoData_Setup
   Class_NoData_Setup
    responses to check all special requests and perform the request

   CAUTION:
    Since SET_CONFIGURATION & SET_INTERFACE are highly related to
    the individual classes, they will be checked and processed here.
  */
  usb_result_e (*Class_NoData_Setup)(uint8_t RequestNo);

  /*Class_Get_Interface_Setting
   This function is used by the file usb_core.c to test if the selected Interface
   and Alternate Setting (uint8_t Interface, uint8_t AlternateSetting) are supported by
   the application.
   This function is writing by user. It should return "SUCCESS" if the Interface
   and Alternate Setting are supported by the application or "UNSUPPORT" if they
   are not supported. */

  usb_result_e  (*Class_Get_Interface_Setting)(uint8_t Interface, uint8_t AlternateSetting);

  uint8_t* (*GetDeviceDescriptor)(uint16_t Length);
  uint8_t* (*GetConfigDescriptor)(uint16_t Length);
  uint8_t* (*GetStringDescriptor)(uint16_t Length);

  uint8_t* RxEP_buffer;
  uint8_t byMaxPacketSize;

} usb_device_prop_t;

typedef struct _USER_STANDARD_REQUESTS
{
  void (*User_GetConfiguration)(void);       /* Get Configuration */
  void (*User_SetConfiguration)(void);       /* Set Configuration */
  void (*User_GetInterface)(void);           /* Get Interface */
  void (*User_SetInterface)(void);           /* Set Interface */
  void (*User_GetStatus)(void);              /* Get Status */
  void (*User_ClearFeature)(void);           /* Clear Feature */
  void (*User_SetEndPointFeature)(void);     /* Set Endpoint Feature */
  void (*User_SetDeviceFeature)(void);       /* Set Device Feature */
  void (*User_SetDeviceAddress)(void);       /* Set Device Address */
}usb_user_standard_requests_t;





extern usb_device_prop_t tUsbDeviceProp;
extern usb_user_standard_requests_t tUsbUserStandardReq;

#endif /* __USB_CORE_H */