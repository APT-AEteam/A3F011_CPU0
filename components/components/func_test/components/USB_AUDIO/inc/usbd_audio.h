/***********************************************************************//** 
 * \file  usb_audio.h
 * \brief  csi usb  audio
 * \copyright Copyright (C) 2015-2021 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2023-1-30 <td>V0.0 <td>YYM    <td>initial
 * </table>
 * *********************************************************************
*/
#ifndef __DRV_USBD_AUDIO_H__
#define __DRV_USBD_AUDIO_H__

#include <stdbool.h>


//--------------------------------------------------------------------
#define   USB_ENUM_STAU_SETADDR						0x01
#define   USB_ENUM_STAU_GET_DEVDESC					0x02
#define   USB_ENUM_STAU_GET_CONFDESC				0x04
#define   USB_ENUM_STAU_GET_STRING					0x08
#define   USB_ENUM_STAU_GET_INTERFACE				0x10
#define   USB_ENUM_STAU_SET_INTERFACE				0x20
#define   USB_ENUM_STAU_GET_HID_CLASS				0x40
//--------------------------------------------------------------------
#define USB_GET_STATUS      0x00
#define USB_CLR_FEATURE		0x01
#define USB_SET_FEATURE     0x03
#define USB_SET_ADDRESS     0x05
#define USB_GET_DESCRIPTOR  0x06
#define USB_SET_DESCRIPTOR 	0x07
#define USB_GET_CONFIG      0x08
#define USB_SET_CONFIG     	0x09
#define USB_GET_INTERFACE   0x0a
#define USB_SET_INTERFACE  	0x0b
#define USB_SYNC_FRAME    	0x0c

#define USB_HID                     0x21
#define USB_REPORT                  0x22
#define USB_PHYSICAL_DESCRIPTOR 	0x23

#define USB_GET_CLASS       0x01
#define USB_GET_IDLE     	0x02
#define USB_GET_PROTOCOL 	0x03
#define USB_SET_REPORT   	0x09
#define USB_SET_IDLE    	0x0A
#define USB_SET_PROTOCOL	0x0B

#define USB_SET_CUR			0x01
#define USB_GET_CUR			0x81
#define USB_SET_MIN			0x02
#define USB_GET_MIN			0x82
#define USB_SET_MAX			0x03
#define USB_GET_MAX			0x83
#define USB_SET_RES			0x04
#define USB_GET_RES			0x84
#define USB_SET_MEM			0x05
#define USB_GET_MEM			0x85


#define USB_BIT0 0x01
#define USB_BIT1 0x02
#define USB_BIT2 0x04
#define USB_BIT3 0x08
#define USB_BIT4 0x10
#define USB_BIT5 0x20
#define USB_BIT6 0x40
#define USB_BIT7 0x80

/** \brief USB start enum  
 * 
 *  \param[in] none
 *  \return error code \ref csi_error_t
 */
csi_error_t  csi_usb_start_enum(void);

/** \brief USB enum complete
 * 
 *  \param[in] none
 *  \return error code \ref csi_error_t
 */ 
csi_error_t  csi_usb_enum_complete(void);

/** \brief USB get sof interrupt state
 * 
 *  \param[in] none
 *  \return error code \ref csi_error_t
 */ 
csi_error_t  csi_usb_get_sof_interrupt_state(void);

/** \brief USB clear sof interrupt state
 * 
 *  \param[in] none
 *  \return none
 */ 
void  csi_usb_clear_sof_interrupt_state(void);

/** \brief USB get vendor interrupt state
 * 
 *  \param[in] none
 *  \return error code \ref csi_error_t
 */
csi_error_t  csi_usb_get_vendor_interrupt_state(void);

/** \brief USB clear vendor interrupt state
 * 
 *  \param[in] none
 *  \return none
 */ 
void  csi_usb_clear_vendor_interrupt_state(void);

/** \brief USB get mic interrupt state
 * 
 *  \param[in] none
 *  \return error code \ref csi_error_t
 */
csi_error_t  csi_usb_get_mic_interrupt_state(void);

/** \brief USB get hp interrupt state
 * 
 *  \param[in] none
 *  \return error code \ref csi_error_t
 */
csi_error_t  csi_usb_get_hp_interrupt_state(void);

/** \brief USB clear mic interrupt state
 * 
 *  \param[in] none
 *  \return none
 */ 
void  csi_usb_clear_mic_interrupt_state(void);

/** \brief USB clear hp interrupt state
 * 
 *  \param[in] none
 *  \return none
 */ 
void  csi_usb_clear_hp_interrupt_state(void);

/** \brief USB get set hp volume state
 * 
 *  \param[in] none
 *  \return error code \ref csi_error_t
 */
csi_error_t  csi_usb_get_set_hp_volume_state(void);

/** \brief USB get set mic volume state
 * 
 *  \param[in] none
 *  \return error code \ref csi_error_t
 */
csi_error_t  csi_usb_get_set_mic_volume_state(void);

/** \brief USB get hp mute state
 * 
 *  \param[in] none
 *  \return error code \ref csi_error_t
 */
csi_error_t  csi_usb_get_hp_mute_state(void);

/** \brief USB get mic mute state
 * 
 *  \param[in] none
 *  \return error code \ref csi_error_t
 */
csi_error_t  csi_usb_get_mic_mute_state(void);

/** \brief USB clear hp volume state
 * 
 *  \param[in] none
 *  \return none
 */ 
void  csi_usb_clear_set_hp_volume_state(void);

/** \brief USB clear mic volume state
 * 
 *  \param[in] none
 *  \return none
 */ 
void  csi_usb_clear_mic_volume_state(void);

/** \brief USB get hp volume 
 * 
 *  \param[in] none
 *  \return hp volume
 */ 
uint16_t  csi_usb_get_hp_volume(void);

/** \brief USB get mic volume 
 * 
 *  \param[in] none
 *  \return mic volume
 */ 
uint16_t  csi_usb_get_mic_volume(void);

/** \brief USB set product string 
 * 
 *  \param[in] pbuf: pointer of usb string buf
 *  \param[in] byLength: string leng
 *  \return none
 */ 
void csi_usb_set_product_string(char * pbuf,uint8_t byLength);

/** \brief  report ep1 data
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \param[in] pbyBuf: pointer of report ep1 data buf
 *  \param[in] wLength: report ep1 data leng
 *  \return flag status
 */ 
uint32_t csi_usb_report_ep1_data(csp_usb_t *ptUsbBase,uint8_t * pbyBuf,uint32_t wLength);

/** \brief  read ep1 data
 * 
 *  \param[in] pwBuf: pointer of read ep1 data buf
 *  \param[in] wMaxLen: read ep1 data max leng
 *  \return one packet leng
 */ 
uint32_t csi_usb_read_ep1_data(uint32_t * pwBuf,uint32_t wMaxLen);

/** \brief usb report ep4 data
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \param[in] pbyBuf: pointer of report ep4 data buf
 *  \param[in] byLeng: report ep4 data leng
 *  \return error code \ref csi_error_t
 */  
csi_error_t csi_usb_report_ep4_data(csp_usb_t *ptUsbBase,uint8_t * pbyBuf,uint8_t byLeng);

 /** \brief usb ep4 free
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return error code  CSI_OK:free  CSI_ERROR:busy
 */ 
csi_error_t csi_usb_ep4_is_free(csp_usb_t *ptUsbBase);

 /** \brief usb receive ep4 data
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \param[in] pbyBuf: pointer of receive ep4 data buf
 *  \param[in] hwMaxLen: receive ep4 data max leng
 *  \return receive data leng
 */
uint16_t csi_usb_receive_ep4_data(csp_usb_t *ptUsbBase,uint8_t * pbyBuf,uint16_t hwMaxLen);

 /** \brief usb report ep3 data
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \param[in] pbyBuf: pointer of report ep3 data buf
 *  \param[in] byLeng: report ep3 data  leng
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_usb_report_ep3_data(csp_usb_t *ptUsbBase,uint8_t * pbyBuf,uint8_t byLeng);

#endif