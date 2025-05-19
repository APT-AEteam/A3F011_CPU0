/***********************************************************************
 * \file  usb_sil.h
 * \brief  Simplified Interface Layer function prototypes. 
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version	<th>Author  <th>Description
 * <tr><td> 2024-6-03 <td>V0.0	<td>WNN   	<td>initial
 * </table>
 * *********************************************************************
*/

#ifndef __USB_SIL_H
#define __USB_SIL_H

#include <stdint.h>

uint32_t csi_usb_sil_init(void);
uint32_t csi_usb_sil_write(uint8_t byEpAddr, uint8_t* pbyBufferPointer, uint32_t wBufferSize);
uint32_t csi_usb_sil_read(uint8_t byEpAddr, uint8_t* pbyBufferPointer);


#endif