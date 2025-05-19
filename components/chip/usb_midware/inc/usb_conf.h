/***********************************************************************//** 
 * \file  usb_conf.h
 * \brief  Custom HID demo configuration file 
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version	<th>Author  <th>Description
 * <tr><td> 2024-6-03 <td>V0.0	<td>WNN   	<td>initial
 * </table>
 * *********************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_CONF_H
#define __USB_CONF_H


/* EP_NUM */
/* defines how many endpoints are used by the device */
/*-------------------------------------------------------------*/
#define EP_NUM     (2)


/* EP0  */
/* rx/tx buffer base address */
#define ENDP0_RXADDR        (0x20)
#define ENDP0_TXADDR        (0x40)

/* EP1  */
/* tx buffer base address */
#define ENDP1_TXADDR        (0x60)   //
#define ENDP1_RXADDR        (0x80)


#define ENPOINT_BUFSZIE 32


#endif