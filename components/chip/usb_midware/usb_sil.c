/***********************************************************************
 * \file  usb_silc
 * \brief  Simplified Interface Layer for Global Initialization and Endpoint Read/Write operations.
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version	<th>Author  <th>Description
 * <tr><td> 2024-6-03 <td>V0.0	<td>WNN   	<td>initial
 * </table>
 * *********************************************************************
*/


#include <stdint.h>
#include "csp.h"
#include "usb_lib.h"
#include "usbd.h"

extern csi_usb_ep_fifo_adr_t  tUsbEpFifoAddr;

/** \brief USB simplified interface layer initialization
 * 
 *  \param[in] none
 *  \return Satus
 */ 
uint32_t csi_usb_sil_init(void)
{
  /* USB interrupts initialization */
  /* clear pending interrupts */
	csp_usb_clear_all_flag(USBD);
	
	csp_usb_int_enable(USBD, USB_SOF_INT|USB_RST_INT|USB_SUS_INT|USB_SETUP_INT,ENABLE);
  
  return 0;
}


/** \brief USB simplified interface layer write
 * 	Write a data buffer to a selected endpoint.
 *  \param[in] byEpAddr: The address of the non control endpoint
 *  \param[in] pbyBufferPointer: The pointer to the data buffer to be written to the endpoint
 *  \param[in] wBufferSize: Number of data to be written (in bytes)
 *  \return Sattus
 */ 
uint32_t csi_usb_sil_write(uint8_t byEpAddr, uint8_t* pbyBufferPointer, uint32_t wBufferSize)
{
	 /* Use the memory interface function to write to the selected endpoint */
	csi_usb_copy_data_to_pma(pbyBufferPointer,byEpAddr, wBufferSize);
	
	 /* Update the data length in the control register */
	
//	csp_usb_set
}
