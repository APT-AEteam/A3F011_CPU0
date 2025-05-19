/***********************************************************************
 * \file  usb_mem.c
 * \brief  Utility functions for memory transfers to/from PMA
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version	<th>Author  <th>Description
 * <tr><td> 2024-6-03 <td>V0.0	<td>WNN   	<td>initial
 * </table>
 * *********************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
#include "csp.h"


/** \brief Copy a buffer from user memory area to packet memory area (PMA)
 * 
 *  \param[in] pbyUsrBuf: pointer to user memory area
 *  \param[in] hwPMABufAddr: PMA address
 *  \param[in] hwNBytes: number of bytes to be copied
 *  \return none
 */   
void csi_usb_copy_data_to_pma(uint8_t *pbyUsrBuf, uint16_t hwPMABufAddr, uint16_t hwNBytes)
{
#if defined STM32F303xE || defined STM32F302x8 
  uint32_t n = (wNBytes + 1) >> 1;   /* n = (wNBytes + 1) / 2 */
  uint32_t i;
  uint16_t *pdwVal;
  pdwVal = (uint16_t *)(wPMABufAddr + PMAAddr);
  
  for (i = n; i != 0; i--)
  {
    *pdwVal++ = *(uint16_t*)pbUsrBuf++;
    pbUsrBuf++;
  }
#else
  uint32_t n = (hwNBytes + 1) >> 1;   /* n = (wNBytes + 1) / 2 */
  uint32_t i, temp1, temp2;
  uint16_t *pdwVal;
  pdwVal = (uint16_t *)(hwPMABufAddr * 2 + csp_usb_get_pma_addr(USBD));
  for (i = n; i != 0; i--)
  {
    temp1 = (uint16_t) * pbyUsrBuf;
    pbyUsrBuf++;
    temp2 = temp1 | (uint16_t) * pbyUsrBuf << 8;
    *pdwVal++ = temp2;
    pdwVal++;
    pbyUsrBuf++;
  }
#endif
}