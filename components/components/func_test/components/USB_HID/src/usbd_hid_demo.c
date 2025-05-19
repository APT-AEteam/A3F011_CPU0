

/***********************************************************************//** 
 * \file  usb_hid_demo.c
 * \brief  USB Customer HID demo
 * \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-05-19 <td>V0.0  <td>WNN   <td>initial
 * </table>
 * *********************************************************************
*/


#include "soc.h"
#include "usbd_core.h"
#include "usbd_hid.h"
#include <drv/pin.h>

volatile uint32_t  usb_write_to_buf_err = 0;
volatile uint32_t  usb_temp_rxbuf[64];
volatile uint8_t  usb_temp_txbuf[64];
volatile uint16_t usb_temp_len;

uint8_t g_byRcvFlag = 0;

void app_usb_send_data_to_host(uint32_t * pwData, uint16_t hwNum);
void app_usb_process(void);

//key scan
#define KEY_LEFT_PIN			PC0
#define KEY_MIDDLE_PIN			PC1
#define KEY_RIGHT_PIN			PC2

#define KEY_LEFT_READ			csi_pin_read(KEY_LEFT_PIN)
#define KEY_MIDDLE_READ			csi_pin_read(KEY_MIDDLE_PIN)
#define KEY_RIGHT_READ			csi_pin_read(KEY_RIGHT_PIN)

volatile uint8_t byKeyNewValue; //按键旧值
volatile uint8_t byKeyOldValue;  //按键新值
//byKeyBuf[0]:bit0:鼠标左键，bit1:鼠标右键，bit2:鼠标滚轮
//byKeyBuf[1]:X轴偏移量，本例中未使用
//byKeyBuf[2]:Y轴偏移量，本例中未使用
//byKeyBuf[3]:保留值
volatile uint8_t byKeyBuf[4] = {0};

void usb_hid_demo(csp_usb_t *ptUsbBase)
{
	csi_error_t tRet;  
    char  usb_dev_name[20] = "A3F011 USB CHIP Demo";
	csi_usb_config_t       tUsbCtrl;

    tUsbCtrl.wFifoBaseAddress = 0x44000000; 
	// ep out fifo length,byte
    tUsbCtrl.hwFifoOutLen[0] = 64;    
    tUsbCtrl.hwFifoOutLen[1] = 4;    
    tUsbCtrl.hwFifoOutLen[2] = 8;    
    tUsbCtrl.hwFifoOutLen[3] = 8;    
    tUsbCtrl.hwFifoOutLen[4] = 8;    
    tUsbCtrl.hwFifoOutLen[5] = 8;    
    tUsbCtrl.hwFifoOutLen[6] = 8;    

    // ep in fifo length,byte
    tUsbCtrl.hwFifoInLen[0] = 64;      
    tUsbCtrl.hwFifoInLen[1] = 4;   
    tUsbCtrl.hwFifoInLen[2] = 8;   
    tUsbCtrl.hwFifoInLen[3] = 16;   
    tUsbCtrl.hwFifoInLen[4] = 16;   
    tUsbCtrl.hwFifoInLen[5] = 16;   
    tUsbCtrl.hwFifoInLen[6] = 16;   
    tUsbCtrl.eUsbPhyMode = USB_PHY_EXTERN_OSC;

//    csi_usb_set_product_string(usb_dev_name,sizeof(usb_dev_name));	
    tRet = csi_usb_hid_init(ptUsbBase,tUsbCtrl);
    if(tRet == CSI_ERROR){
        // Err
    }
	
	//按键初始化
	csi_pin_set_mux(KEY_LEFT_PIN, 	1);
	csi_pin_set_mux(KEY_MIDDLE_PIN, 1);
	csi_pin_set_mux(KEY_RIGHT_PIN, 	1);
	csi_pin_pull_mode(KEY_LEFT_PIN,GPIO_PULLUP);
	csi_pin_pull_mode(KEY_MIDDLE_PIN,GPIO_PULLUP);
	csi_pin_pull_mode(KEY_RIGHT_PIN,GPIO_PULLUP);
	
//	while(csi_usb_enum_complete() != CSI_OK);
	mdelay(2000);
	
	while(1){
		app_usb_process();
		//my_printf("~~~~~~~\n");	
		mdelay(20);
	}
}
 
void app_usb_process(void)
{
	uint8_t i,temp;
	
	//key scan
	byKeyNewValue = KEY_LEFT_READ + KEY_MIDDLE_READ + KEY_RIGHT_READ; //任何一个按键状态发生改变，就准备重新开始扫描按键

	if(byKeyNewValue != byKeyOldValue)                           //按键消抖
	{
		byKeyOldValue = byKeyNewValue;
		return;
	}
	else
	{
		if(!KEY_LEFT_READ)			//左键按下
		{
			byKeyBuf[0] = 1;
		}
		else if(!KEY_RIGHT_READ)	//右键按下
		{
			byKeyBuf[0] = 2;
		}
		else if(!KEY_MIDDLE_READ)	//滚轮按下
		{
			byKeyBuf[0] = 4;
		}
		else						//无按键按下
			byKeyBuf[0] = 0;
	}
	
	//通过EP1端点上报数据
	csi_usb_report_ep1_data(USBD,(uint8_t *)&byKeyBuf[0],4);
	
	//判断EP1数据是否发送成功，翻转EP1的数据包DATA0/DATA1
	//否则如果一直以同一个数据包发送，会引发错误，端点stall，主机会复位设备
	if((USBD->EP_TXISR) & 0x02)
	{
		temp = USBD->EP1TX_CTL & 0x04;
		if(temp) 
			USBD->EP1TX_CTL &= ~(1ul << 2);
		else
			USBD->EP1TX_CTL |= (1ul << 2);
	}
	
    // 接收到自主机的数据，放到vendor_data_from_host_loop队列中
//    if(csi_usb_get_vendor_interrupt_state() == CSI_OK)
//	if(g_byRcvFlag)
//    {
//        csi_usb_clear_vendor_interrupt_state();
//        usb_temp_len = csi_usb_read_ep1_data((uint32_t *)&usb_temp_rxbuf[0],64);
//		csi_usb_report_ep1_data(USBD,(uint8_t *)&usb_temp_rxbuf[0],usb_temp_len);
//		g_byRcvFlag = 0;
//
//       
//    }
//	else {
//		for(i = 0; i<4; i++){ 
//			usb_temp_rxbuf[0] |= i<<(i*8);
//		}
//		csi_usb_report_ep1_data(USBD,(uint8_t *)&usb_temp_rxbuf[0],4);
//	}
	
	
	
   
    
}

