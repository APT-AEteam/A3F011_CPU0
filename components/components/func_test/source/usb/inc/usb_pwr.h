/***********************************************************************//** 
 * \file  usb_pwr.h
 * \brief  Standard protocol processing functions prototypes 
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version	<th>Author  <th>Description
 * <tr><td> 2024-6-03 <td>V0.0	<td>WNN   	<td>initial
 * </table>
 * *********************************************************************
*/

#include "usb_core.h"

extern __IO uint32_t wUsbDeviceState;

typedef enum _DEVICE_STATE
{
  UNCONNECTED,
  ATTACHED,
  POWERED,
  SUSPENDED,
  ADDRESSED,
  CONFIGURED
} csi_device_state_e;

/** \brief USB system power up
 * 
 *  \param[in] none
 *  \return USB_SUCCESS
 */ 
usb_result_e csi_usb_poweron(void);