/***********************************************************************
 * \file  usb_init.c
 * \brief  Initialization routines & global variables
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version	<th>Author  <th>Description
 * <tr><td> 2024-6-03 <td>V0.0	<td>WNN   	<td>initial
 * </table>
 * *********************************************************************
*/



#include "soc.h"
#include "usb_core.h"

#include "usb_init.h"

/* Private variablesr-------------------------------------------------*/
/*  The number of current endpoint, it will be used to specify an endpoint */
uint8_t	byEPindex;

usb_device_prop_t *ptDevProp;

/*  Points to the DEVICE_INFO structure of current device for faster operation*/
usb_device_info_t *ptDevInfo;

usb_device_info_t tDevInfo;

usb_user_standard_requests_t *ptUsbUserStandardReq;


/** \brief USB system initialization
 * 
 *  \param[in] none
 *  \return none
 */ 
void csi_usb_Init(void)
{
  ptDevInfo = &tDevInfo;
  ptDevInfo->ControlState = 2;
  ptDevProp = &tUsbDeviceProp;
  ptUsbUserStandardReq = &tUsbUserStandardReq;
  /* Initialize devices one by one */
  ptDevProp->Init();
}


