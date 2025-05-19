
/***********************************************************************//** 
 * \file  usb_audio_demo.c
 * \brief  USB audio demo
 * \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-05-19 <td>V0.0  <td>WNN   <td>initial
 * </table>
 * *********************************************************************
*/




#include "soc.h"
#include "usbd.h"
#include "usbd_audio.h"

/** \brief usb_audio_samp_demo 
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */  
void usb_audio_samp_test(csp_usb_t *ptUsbBase)
{  
    csi_error_t tRet;  
    char  usb_dev_name[16] = "USB Audio Device";
	csi_usb_config_t       tUsbCtrl;

    tUsbCtrl.wFifoBaseAddress = 0x44000000;//0x20004000; 0x44000000
	// ep out fifo length,byte
    tUsbCtrl.hwFifoOutLen[0] = 64;    
    tUsbCtrl.hwFifoOutLen[1] = (48*4*2);    
    tUsbCtrl.hwFifoOutLen[2] = 8;    
    tUsbCtrl.hwFifoOutLen[3] = 8;    
    tUsbCtrl.hwFifoOutLen[4] = 64;    
    tUsbCtrl.hwFifoOutLen[5] = 8;    
    tUsbCtrl.hwFifoOutLen[6] = 8;    

    // ep in fifo length,byte
    tUsbCtrl.hwFifoInLen[0] = 64;      
    tUsbCtrl.hwFifoInLen[1] = (48*4*2);   
    tUsbCtrl.hwFifoInLen[2] = 8;   
    tUsbCtrl.hwFifoInLen[3] = 16;   
    tUsbCtrl.hwFifoInLen[4] = 64;   
    tUsbCtrl.hwFifoInLen[5] = 16;   
    tUsbCtrl.hwFifoInLen[6] = 16;   
    tUsbCtrl.eUsbPhyMode = USB_PHY_EXTERN_OSC;

    csi_usb_set_product_string(usb_dev_name,sizeof(usb_dev_name));	
    tRet = csi_usb_init(ptUsbBase,tUsbCtrl);
    if(tRet == CSI_ERROR){
	// Err
    }
}

