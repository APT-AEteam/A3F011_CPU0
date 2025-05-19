/***********************************************************************
 * \file  usb_prop.c
 * \brief  Processings related to Custom HID demo
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version	<th>Author  <th>Description
 * <tr><td> 2024-6-03 <td>V0.0	<td>WNN   	<td>initial
 * </table>
 * *********************************************************************
*/

#include "usb_lib.h"
#include "usb_conf.h"
#include "usb_pwr.h"
#include "usb_desc.h"


#include "csp.h"

usb_device_t Device_Table =
  {
    EP_NUM,
    1
  };



/** \brief Custom HID init routine
 * 
 *  \param[in] none
 *  \return none
 */   
void CustomHID_init(void)
{
  /* Update the serial number string descriptor with the data from the unique ID*/
  //Get_SerialNum();
	
	/* Connect the device */
	csi_usb_poweron();
    
	ptUsbDevInfo->Current_Configuration = 0;
	
	/* Perform basic device initialization operations */
	csi_usb_sil_init();
	


	wUsbDeviceState = UNCONNECTED;
	
	/*** cable plugged-in  **/
//	USB_Cable_Config(ENABLE);

}

/** \brief Custom HID reset routine
 * 
 *  \param[in] none
 *  \return none
 */  
void CustomHID_Reset(void)
{
	/* Set CustomHID_DEVICE as not configured */
	ptUsbDevInfo ->Current_Configuration = 0;
	ptUsbDevInfo->Current_Interface = 0;		/*the default Interface*/
	
	/* Current Feature initialization */
	ptUsbDevInfo->Current_Feature = g_byCustomHidConfigDescriptor[7];
	
	csp_usb_set_pma_addr(USBD, 0x44000000);
	/* Initialize Endpoint 0 */
	
	csp_usb_set_ep(USBD,USB_EP_0,USB_EP_IN);	
	csp_usb_set_fifo(USBD,ENDP0_TXADDR);	
	csp_usb_set_ep(USBD,USB_EP_0,USB_EP_OUT);	
	csp_usb_set_fifo(USBD,ENDP0_RXADDR);
	
	csp_usb_ep_rx_set_stall(USBD, USB_EP_0);
	csp_usb_ep_set_rxcnt(USBD, USB_EP_0, tUsbDeviceProp.byMaxPacketSize);
	csp_usb_ep_rx_enable(USBD,USB_EP_0);
	
	/* Initialize Endpoint 1 */
	csp_usb_set_ep(USBD,USB_EP_1,USB_EP_IN);
	csp_usb_set_fifo(USBD,ENDP1_TXADDR);
	csp_usb_set_ep(USBD,USB_EP_1,USB_EP_OUT);
	csp_usb_set_fifo(USBD,ENDP1_RXADDR);
	
	csp_usb_ep_set_rxcnt(USBD, USB_EP_1, 2);
	csp_usb_ep_set_txcnt(USBD, USB_EP_1, 2);
	csp_usb_ep_rx_enable(USBD, USB_EP_1);
	csp_usb_ep_tx_disable(USBD, USB_EP_1);
	
	/* Set the device to response on default address*/
	csp_usb_set_addr(USBD, 0);
	wUsbDeviceState = ATTACHED;
	
}

void CustomHID_Status_In(void)
{
	
}

void CustomHID_Status_Out(void)
{
	
}

void CustomHID_Data_Setup(void)
{
	
}

void CustomHID_NoData_Setup(void)
{
	
}

void CustomHID_Get_Interface_Setting(void)
{
	
}

void CustomHID_GetDeviceDescriptor(void)
{
	
}

void CustomHID_GetConfigDescriptor(void)
{
	
}

void CustomHID_GetStringDescriptor(void)
{
	
}

void CustomHID_SetConfiguration(void)
{
	
}

void CustomHID_SetDeviceAddress(void)
{
	
}

usb_device_prop_t tUsbDeviceProp =
  {
    CustomHID_init,
    CustomHID_Reset,
    CustomHID_Status_In,
    CustomHID_Status_Out,
    CustomHID_Data_Setup,
    CustomHID_NoData_Setup,
    CustomHID_Get_Interface_Setting,
    CustomHID_GetDeviceDescriptor,
    CustomHID_GetConfigDescriptor,
    CustomHID_GetStringDescriptor,
    0,
    0x40 /*MAX PACKET SIZE*/
  };
  
usb_user_standard_requests_t tUsbUserStandardReq =
  {
   
    CustomHID_SetConfiguration,
    CustomHID_SetDeviceAddress
  };
  
  