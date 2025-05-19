/***********************************************************************//** 
 * \file  usb_init.h
 * \brief  Standard protocol processing functions prototypes 
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version	<th>Author  <th>Description
 * <tr><td> 2024-6-03 <td>V0.0	<td>WNN   	<td>initial
 * </table>
 * *********************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_INIT_H
#define __USB_INIT_H

#include "soc.h"
#include "usb_core.h"

/* External variables --------------------------------------------------------*/
/*  The number of current endpoint, it will be used to specify an endpoint */
extern uint8_t	EPindex;
/*  The number of current device, it is an index to the Device_Table */
/*extern uint8_t	Device_no; */
/*  Points to the DEVICE_INFO structure of current device */
/*  The purpose of this register is to speed up the execution */
extern usb_device_info_t *	ptUsbDevInfo;
/*  Points to the DEVICE_PROP structure of current device */
/*  The purpose of this register is to speed up the execution */
extern usb_device_prop_t *	pUsbDevProp;
/*  Temporary save the state of Rx & Tx status. */
/*  Whenever the Rx or Tx state is changed, its value is saved */
/*  in this variable first and will be set to the EPRB or EPRA */
/*  at the end of interrupt process */
extern usb_user_standard_requests_t *ptUsbUserStandardReq;

extern uint16_t	SaveState ;
extern uint16_t wInterrupt_Mask;

#endif /* __USB_INIT_H */
