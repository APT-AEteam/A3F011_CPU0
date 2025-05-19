/***********************************************************************//** 
 * \file  usb_prop.h
 * \brief  Standard protocol processing functions prototypes 
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version	<th>Author  <th>Description
 * <tr><td> 2024-6-03 <td>V0.0	<td>WNN   	<td>initial
 * </table>
 * *********************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_PROP_H
#define __USB_PROP_H

#include "soc.h"
#include "usb_core.h"

void CustomHID_init(void);
void CustomHID_Reset(void);
void CustomHID_Status_In (void);
void CustomHID_Status_Out (void);
usb_result_e CustomHID_Data_Setup(uint8_t);
usb_result_e CustomHID_NoData_Setup(uint8_t);
usb_result_e CustomHID_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting);
uint8_t *CustomHID_GetDeviceDescriptor(uint16_t );
uint8_t *CustomHID_GetConfigDescriptor(uint16_t);
uint8_t *CustomHID_GetStringDescriptor(uint16_t);

void CustomHID_SetConfiguration(void);





void CustomHID_SetDeviceAddress (void);
usb_result_e CustomHID_SetProtocol(void);
uint8_t *CustomHID_GetProtocolValue(uint16_t Length);
usb_result_e CustomHID_SetProtocol(void);
uint8_t *CustomHID_GetReportDescriptor(uint16_t Length);
uint8_t *CustomHID_GetHIDDescriptor(uint16_t Length);




#endif  /* __USB_PROP_H */