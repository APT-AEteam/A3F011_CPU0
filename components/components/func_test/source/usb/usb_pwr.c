/***********************************************************************
 * \file  usb_pwr.c
 * \brief  Connection/disconnection & power management
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version	<th>Author  <th>Description
 * <tr><td> 2024-6-03 <td>V0.0	<td>WNN   	<td>initial
 * </table>
 * *********************************************************************
*/

#include "usb_pwr.h"
#include "usb_lib.h"
#include "usbd.h"

#include "csp.h"

__IO uint32_t wUsbDeviceState = UNCONNECTED; /* USB device status */

/** \brief USB system power up
 * 
 *  \param[in] none
 *  \return USB_SUCCESS
 */ 
usb_result_e csi_usb_poweron(void)
{
  	
  /*** CNTR_PWDN = 0 
  hwRegVal = CNTR_FRES;
  _SetCNTR(wRegVal);***/
  
  csi_usb_reset(USBD);  //reset的同时，清除了flag

  /*** CNTR_FRES = 0 
  wInterrupt_Mask = 0;
  _SetCNTR(wInterrupt_Mask);***/
  
  /*** Clear pending interrupts ***/
  
  
  //_SetISTR(0);
  /*** Set interrupt mask 
  wInterrupt_Mask = CNTR_RESETM | CNTR_SUSPM | CNTR_WKUPM;
  _SetCNTR(wInterrupt_Mask);***/
  
  csp_usb_int_enable(USBD, USB_SOF_INT|USB_RST_INT|USB_SUS_INT|USB_SETUP_INT,ENABLE);
  
  return USB_SUCCESS;
}