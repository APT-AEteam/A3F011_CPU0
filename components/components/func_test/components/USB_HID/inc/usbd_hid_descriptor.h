/*
 * Copyright (C) 2017-2020 Alibaba Group Holding Limited
 */

/***********************************************************************//** 
 * \file  usbd_descriptor.h
 * \brief  csi usbd descriptor
 * \copyright Copyright (C) 2015-2021 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2023-1-30 <td>V0.0 <td>YYM    <td>initial
 * </table>
 * *********************************************************************
*/

#ifndef _DRV_USBD_DESCRIPTOR_H_
#define _DRV_USBD_DESCRIPTOR_H_

#include <drv/common.h>
#include "csp.h"

#ifdef __cplusplus
extern "C" {
#endif



/** \brief usb set interface cur
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
// [0]: byRequest Type = 0x21
// [1]: byRequest = 0x01
// [2-3]: wValue
// [4-5]: wIndex
// [6-7]: wLength
// Data
void csi_usb_set_interface_cur(csp_usb_t *ptUsbBase);

/** \brief usb get device descriptiptor
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_get_device_descriptor(csp_usb_t *ptUsbBase);

/** \brief usb get hid descriptor
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_get_hid_descriptor(csp_usb_t *ptUsbBase);

/** \brief usb get report
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_get_report(csp_usb_t *ptUsbBase);

/** \brief usb get interface cur
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_get_interface_cur(csp_usb_t *ptUsbBase);	// 0x81


/** \brief usb get interface min
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_get_interface_min(csp_usb_t *ptUsbBase);   // 0x82

/** \brief usb get interface max
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_get_interface_max(csp_usb_t *ptUsbBase);		// 0x83

/** \brief usb get interface res
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */
void csi_usb_get_interface_res(csp_usb_t *ptUsbBase);    // 0x84

#ifdef __cplusplus
}
#endif

#endif 
