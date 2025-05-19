/***********************************************************************
 * \file  usb_mem.h
 * \brief  Utility prototypes functions for memory/PMA transfers
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version	<th>Author  <th>Description
 * <tr><td> 2024-6-03 <td>V0.0	<td>WNN   	<td>initial
 * </table>
 * *********************************************************************
*/

#ifndef __USB_MEM_H
#define __USB_MEM_H

#include <stdint.h>

/** \brief Copy a buffer from user memory area to packet memory area (PMA)
 * 
 *  \param[in] pbyUsrBuf: pointer to user memory area
 *  \param[in] hwPMABufAddr: PMA address
 *  \param[in] hwNBytes: number of bytes to be copied
 *  \return none
 */   
void csi_usb_copy_data_to_pma(uint8_t *pbyUsrBuf, uint16_t hwPMABufAddr, uint16_t hwNBytes);


#endif  /*__USB_MEM_H*/