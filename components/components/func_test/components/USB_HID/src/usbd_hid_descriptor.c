/***********************************************************************//** 
 * \file  usb_descriptor.c
 * \brief  csi usb descriptor driver
 * \copyright Copyright (C) 2015-2021 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2023-1-30 <td>V0.0 <td>YYM    <td>initial
 * </table>
 * *********************************************************************
*/

#include <sys_clk.h>
#include "usbd_core.h"
#include "usbd_hid_descriptor.h"
#include "usbd_hid.h"

extern csi_usb_setup_t        tUsbSetup;
extern csi_usb_ep0_ctrl_t     tUsbEp0Ctrl;
extern csi_usb_soft_ctrl_t    tUsbSoftCtrl;

const char byHidReportDescriptor[];

volatile char byHidDeviceDescriptor[18] =     //  18
{
	0x12,               	// bLength
	0x01,               	// bDescriptorType
	0x00, 0x02,         	// bcdUSB(2.00)
	0x00,               	// bDeviceClass
	0x00,               	// bDeviceSubClass
	0x00,               	// bDeviceProtocol
	EP0_MAX_PACKET_SIZE,	// bMaxPacketSize0
	0x34,0x12,//0x83, 0x04,			// idVendor
	0x78,0x56,//0x52, 0x57,			// idProduct
	0x00, 0x01,         	// bcdDevice
	0x01,               	// iManufacturer
	0x02,               	// iProduct
	0x00,               	// iSerialNumber
	0x01                	// bNumConfigurations
};

const char byHidReportDescriptor[] =
  {

//    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
//    0x09, 0x02,                    // USAGE (Mouse)
//    0xa1, 0x01,                    // COLLECTION (Application)
//    0x09, 0x01,                    //   USAGE (Pointer)
//    0xa1, 0x00,                    //   COLLECTION (Physical)
//    0x05, 0x09,                    //     USAGE_PAGE (Button)
//    0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
//    0x29, 0x03,                    //     USAGE_MAXIMUM (Button 3)
//    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
//    0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
//    0x95, 0x03,                    //     REPORT_COUNT (3)
//    0x75, 0x01,                    //     REPORT_SIZE (1)
//    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
//    0x95, 0x01,                    //     REPORT_COUNT (1)
//    0x75, 0x05,                    //     REPORT_SIZE (5)
//    0x81, 0x03,                    //     INPUT (Cnst,Var,Abs)
//    0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
//    0x09, 0x30,                    //     USAGE (X)
//    0x09, 0x31,                    //     USAGE (Y)
//    0x15, 0x81,                    //     LOGICAL_MINIMUM (-127)
//    0x25, 0x7f,                    //     LOGICAL_MAXIMUM (127)
//    0x75, 0x08,                    //     REPORT_SIZE (8)
//    0x95, 0x02,                    //     REPORT_COUNT (2)
//    0x81, 0x06,                    //     INPUT (Data,Var,Rel)
//    0xc0,                          //   END_COLLECTION
//    0xc0                           // END_COLLECTION
	

#if 0
    0x05, 0xFF, // USAGE_PAGE(User define)
    0x09, 0xFF, // USAGE(User define)
    0xa1, 0x01, // COLLECTION (Application)
    0x05, 0x01, // USAGE_PAGE(1)
    0x19, 0x00, // USAGE_MINIMUM(0)
    0x29, 0xFF, // USAGE_MAXIMUM(255)
    0x15, 0x00, // LOGICAL_MINIMUM (0)
    0x25, 0xFF, // LOGICAL_MAXIMUM (255)
    0x75, 0x08, // REPORT_SIZE (8)
    0x95, 0x40, // REPORT_COUNT (64)
    0x81, 0x02, // INPUT (Data,Var,Abs)
    0x05, 0x02, // USAGE_PAGE(2)
    0x19, 0x00, // USAGE_MINIMUM (0)
    0x29, 0xFF, // USAGE_MAXIMUM (255)
    0x15, 0x00, // LOGICAL_MINIMUM (0)
    0x25, 0xFF, // LOGICAL_MAXIMUM (255)
    0x95, 0x08, // REPORT_COUNT (8)
    0x75, 0x40, // REPORT_SIZE (64)
    0x91, 0x02, // OUTPUT (Data,Var,Abs)
    0xc0 // END_COLLECTION
#endif

0x05, 0x01, 0x09, 0x02, 0xA1, 0x01, 0x09, 0x01, 
0xA1, 0x00, 0x05, 0x09, 0x19, 0x01, 0x29, 0x03, 
0x15, 0x00, 0x25, 0x01, 0x95, 0x08, 0x75, 0x01, 
0x81, 0x02, 0x05, 0x01, 0x09, 0x30, 0x09, 0x31, 
0x09, 0x38, 0x15, 0x81, 0x25, 0x7F, 0x75, 0x08, 
0x95, 0x03, 0x81, 0x06, 0xC0, 0xC0
#if 0
//每行开始的第一字节为该条目的前缀,前缀的格式为:
//D7~D4:bTag;D3~D2:bType;D1~DO:bSize。以下分别对每个条目注释
//这是一个全局(bType为1)条目,选择用途页为普通桌面Generic Desktop Page(0x01)
//后面跟一字节数据(bSize为1),后面的字节数就不注释了,自己根据bsize来判断
0x05,0x01,
// USAGE_PAGE (Generic Desktop)
//这是一个局部(bType为2)条目,说明接下来的应用集合用途用于鼠标
0x09,0x02,
// USAGE (Mouse)
//这是一个主条目(bType为0)条目,开集合,后面跟的数据0x01表表示该集合是一个应用集合
//它的性质在前面由用途页和用途定义为普通桌面用的鼠标
0xa1,0x01,
// COLLECTION (Application)
//这是一个局部条目。说明用途为指针集合
0x09,0x01,
// USAGE (Pointer)
//这是一个主条目,开集合,后面跟的数据0x00表示该集合是一个物理集合
//用途由前面的局部条目定义为指针集合
0xa1,0x00,
// COLLECTION (Physical)
//这是一个全局条目,选择用途页为按键(ButtonPage(0x09))
0x05,0x09,
// USAGE PAGE (Button)
//这是一个局部条目,说明用途的最小值为1。实际上是鼠标左键
0x19,0x01,
// USAGE MINIMUM (Button 1)
//这是一个局部条目,说明用途的最大值为3。实际上是鼠标中键
0x29,0x03,
// USAGE MAXIMUM (Button 3)
//这是一个全局条目,说明返回的数据的逻辑值(就是我们返回的数据域的值啦)最小为
//因为这里用"位"来表示一个数据域,因此最小为0,最大为1
0x15,0x00,
// LOGICAL MINIMUM (0)
//这是一个全局条目,说明逻辑值最大为1
0x25,0x01,
// LOGICAL MAXIMUM(1)
//这是一个全局条目,说明数据域的数量为三个
0x95,0x03,
// REPORT COUNT (3)
//这是一个全局条目,说明每个数据域的长度为1个位
0x75,0x01,
// REPORT SIZE(1)
//这是一个主条目,说明有3个长度为1位的数据域(数量和长度由前面的两个全局条目所定义)
//用来作为输入,属性为:Data,Var,Abs,Data表示这些数据可以变动;Var表示这些数据域是独立的变量,
//即每个域表示一个意思;Abs表示绝对值
//这样定义的结果就是,第一个数据域位0表示按键1(左键)是否否按下,第二个数据域位
//按键2(右键)是否按下,第三个数据域位2表示按键3(中键)是否按下表示
0x81,0x02,//INPUT(Data,Var,Abs)
//这是一个全局条目,说明数据域数量为1个
0x95,0x01,
// REPORT COUNT(1)
//这是一个全局条目,说明每个数据域的长度为5位
0x75,0x05,//REPORT SIZE(5)
//这是一个主条目,输入用。由前面两个全局条目可知,长度为5位,数量为1个
//它的属性为常量(即返回的数据一直是0)
//这个只是为了凑齐1字节(前面用了3个位)而填充的一些数据而已,所以它是没有实际用途的
0x81,0x03,//INPUT(Cnst,Var,Abs)
//这是一个全局条目,选择用途页为普通桌面Generic DesktopPage(0x01)
0x05,0x01,//USAGE PAGE (Generic Desktop)
//这是一个局部条目,说明用途为X轴
0x09,0x30,//USAGE(X)
//这是一个局部条目,说明用途为Y轴
0x09,0x31,//USAGE(Y)
//这是一个局部条目,说明用途为滚轮
0x09,0x38,//USAGE(Wheel)
//下面两个为全局条目,说明返回的逻辑最小和最大值。因为鼠标指针移动时,通常是用相对值来表示的,相对值的意思就是,当指针移动时,只发送移动量。
//往右移动时,X值为正;往下移动时,Y值为正。对于滚轮,当滚轮往上滚时,值为正
0x15,0x81,
0x25,0x7f,
// LOGICAL MINIMUM ( - 127)
// LOGICAL MAXIMUM (127)
//这是一个全局条目,说明数据域的长度为8位
0x75,0x08,//REPORT SIZE(8)
//这是一个全局条目,说明数据域的个数为3个
0x95,0x03,
// REPORT COUNT (3)
//这是一个主条目。它说明这三个8位的数据域是输入用的,属性为:Data,Var,Rel
//Data说明数据是可以变的,Var说明这些数据城是独立的,即第一个8位表示X轴
//第二个8位表示Y轴,第三个8位表示滚轮。Rel表示这些值是是相对值
0x81,0x06,//INPUT(Data,Var, Rel)
//下面这两个主条目用来关闭前面的集合用
//因为开了两个集合,所以要关两次。bSize为0,所以后面没数据
0xc0,
0xc0
#endif
 }; /* ReportDescriptor */
 
const char byHidConfigDescriptor[] =			// Configuration_Length
{
	0x09, /* bLength: Configuration Descriptor size */
    0x02, /* bDescriptorType: Configuration */
    34,//41,   /* CUSTOMHID_SIZ_CONFIG_DESC */
    /* wTotalLength: Bytes returned */
    0x00,
    0x01,         /* bNumInterfaces: 1 interface */
    0x01,         /* bConfigurationValue: Configuration value */
    0x00,         /* iConfiguration: Index of string descriptor describing
                                 the configuration*/
    0x80,//0xC0,         /* bmAttributes: Self powered */
    0x32,         /* MaxPower 100 mA: this current is used for detecting Vbus  50*2mA=100mA */

    /************** Descriptor of Custom HID interface ****************/
    /* 09 */
    0x09,         /* bLength: Interface Descriptor size */
    0x04,		  /* bDescriptorType: Interface descriptor type */
    0x00,         /* bInterfaceNumber: Number of Interface */
    0x00,         /* bAlternateSetting: Alternate setting */
    0x01,//0x02,         /* bNumEndpoints */
    0x03,         /* bInterfaceClass: HID */
    0x01,//0x00,         /* bInterfaceSubClass : 1=BOOT, 0=no boot */
    0x02,//0x00,         /* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */
    0,            /* iInterface: Index of string descriptor */
    /******************** Descriptor of Custom HID HID ********************/
    /* 18 */
    0x09,         /* bLength: HID Descriptor size */
    0x21, /* bDescriptorType: HID */
    0x11,//0x10,         /* bcdHID: HID Class Spec release number */
    0x01,
    0x00,         /* bCountryCode: Hardware target country */
    0x01,         /* bNumDescriptors: Number of HID class descriptors to follow */
    0x22,         /* bDescriptorType */
    sizeof(byHidReportDescriptor)&0xff,           /* wItemLength: Total length of Report descriptor */
    (sizeof(byHidReportDescriptor) >> 8) &0xff,
    /******************** Descriptor of Custom HID endpoints ******************/
    /* 27 */
    0x07,          /* bLength: Endpoint Descriptor size */
    0x05, 		   /* bDescriptorType: endpoint description */
    0x81,          /* bEndpointAddress: Endpoint Address (IN) */
    0x03,          /* bmAttributes: Interrupt endpoint */
    4,//64,            /* wMaxPacketSize: 64 Bytes max */
    0x00,
    0x0a,          /* bInterval: Polling Interval (unit: ms	·) */
    /* 34 */
    	
    //0x07,	/* bLength: Endpoint Descriptor size */
    //0x05,	/* bDescriptorType: Endpoint descriptor type */
   // 0x01,	/* bEndpointAddress: Endpoint Address (OUT) */
    //0x03,	/* bmAttributes: Interrupt endpoint */
    //64,	/* wMaxPacketSize: 64 Bytes max  */
    //0x00,
    //0x02,	/* bInterval: Polling Interval (unit: ms) */
    /* 41 */
};


 
 
 
 /*
 * DEVICE QUALIFIER
 * If a full-speed only device receives a GetDescriptor() request for a device_qualifier, 
 * it must respond with a request error. Then, 
 * the host must not make a request for an other_speed_configuration descriptor.
 */
/* const char device_qualifier_table[] = 
{
	0x0A,               	// bLength
	0x06,               	// bQualifierType
	0x00, 0x02,         	// bcdUSB(2.00)
	0x00,               	// bDeviceClass
	0x00,               	// bDeviceSubClass
	0x00,               	// bDeviceProtocol
	EP0_MAX_PACKET_SIZE,	// bMaxPacketSize0
	0x01,               	// bNumConfigurations
	0x00					// bReserved
}; */

//--------------------------------------------------------------------
// USB String Desscriptors
const char  byHidStringLangId[] =
{
	0x04, 0x03, 0x09, 0x04  /* LangID = 0x0409: U.S. English */
};
//--------------------------------------------------------------------
// Manufacturer string
const char  byHidStringVendor[] =
{
	8, /* Size of Vendor string */
    3,  /* bDescriptorType*/
    /* Manufacturer: "APT" */
    'A', 0, 'P', 0, 'T', 0
 };

//--------------------------------------------------------------------
// product string
const char byHidStringProdcut[] =     
{
	40, /* Size of Vendor string */
    3,  /* bDescriptorType*/
    /* Manufacturer: "STMicroelectronics" */
    'A', 0, '3', 0, 'F', 0, '1', 0, '0', 0, '1', 0, ' ', 0,
	'U', 0, 'S', 0, 'B', 0, 'C', 0, 'H', 0, 'I', 0, 'D', 0,' ', 0,
	'D', 0, 'E', 0, 'M', 0, 'O', 0
};


const char byHidStringSerial[] =
  {
    12,           /* bLength */
    3,        /* bDescriptorType */
    'A', 0, 'P', 0, 'T', 0,'3', 0,'2', 0
  };
/******************** ST stops here ********************/


const char os_string_desc[] =
{
	0x12,					// Length of the descriptor
	0x03,					// Descriptor type
	0x4D,0x00,0x53,0x00,	// "MSFT100"
	0x46,0x00,0x54,0x00,
	0x31,0x00,0x30,0x00,
	0x30,0x00,
	0x01,					// Vendor code
	0x00					// Pad field
};

const char hid_report_table[] =     //  18
{
	0x24,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};






//=========================================================================
const char hid0_desc_table[] =
{
};
const char hid1_desc_table[] =
{
};
const char hid2_desc_table[] =
{	
};
const char hid3_desc_table[] =
{
	0x09,0x21,0x10,0x01,0x00,0x01,0x22,40,0x00	
};
const char hid4_desc_table[] =
{
	0x09,0x21,0x10,0x01,0x00,0x01,0x22,76,0x00	
};
const char hid5_desc_table[] =
{
};



const char inf0_report_descriptor[]=
{

};
const char inf1_report_descriptor[]=
{

};
const char inf2_report_descriptor[]=
{

};
const char inf3_report_descriptor[]=
{

};
const char inf4_report_descriptor[] =
{
	//  vendor  : report id(0x23)   Id+31(Dongle -> pc)
	//  vendor  : report id(0x24)   Id+63(Dongle -> pc)
	//  vendor  : report id(0x4e)   Id+31(pc -> Dongle)
	//  vendor  : report id(0x4f)   Id+63(pc -> Dongle)
	0x06,0x00,0xff,0x09,0x00,0xa1,0x01,0xa1,

	// 0x06,0x01,0xff,0x09,0x04,0xa1,0x01,0xa1,	// 76byte
	0x02,0x85,0x23,0x09,0x14,0x15,0x80,0x25,
	0x7f,0x75,0x08,0x95,0x1F,0x81,0x22,0xc0,
	0xa1,0x02,0x85,0x24,0x09,0x14,0x15,0x80,
	0x25,0x7f,0x75,0x08,0x95,0x3F,0x81,0x22,
	0xc0,0xa1,0x02,0x85,0x4E,0x09,0x14,0x15,
	0x80,0x25,0x7f,0x75,0x08,0x95,0x1f,0x91,
	0x22,0xc0,0xa1,0x02,0x85,0x4F,0x09,0x14,
	0x15,0x80,0x25,0x7f,0x75,0x08,0x95,0x3f,
	0x91,0x22,0xc0,0xc0
};
const char inf5_report_descriptor[]=
{

};



static uint16_t apt_get_desc_leng(uint8_t byType)
{
	uint16_t len = 0;

	switch(byType)
	{
		case 0:
			len = sizeof(byHidDeviceDescriptor);
		break;
		case 1:
			len = sizeof(byHidConfigDescriptor);
		break;
		case 2:
			len = sizeof(byHidStringLangId);
		break;
		case 3:
			len = sizeof(byHidStringVendor);
		break;
		case 4:
			len = sizeof(byHidStringProdcut); 
		break;
		case 5:
			//len = sizeof(device_qualifier_table);
		break;
		case 6:
			len = sizeof(os_string_desc);
		break;
		case 7:
			len = sizeof(byHidStringSerial);
		break;
//------------------------------------------------------------
		case 0x10:
//			len = sizeof(inf0_report_descriptor);
			len = sizeof(byHidReportDescriptor);
		break;
		case 0x11:
			len = sizeof(inf1_report_descriptor);
		break;
		case 0x12:
			len = sizeof(inf2_report_descriptor);
		break;
		case 0x13:
			len = sizeof(inf3_report_descriptor);
		break;
		case 0x14:
			len = sizeof(inf4_report_descriptor);
		break;
		case 0x15:
			len = sizeof(inf5_report_descriptor);
		break;
		case 0x16:
			len = sizeof(hid_report_table);
		break;
//------------------------------------------------------------
		case 0x20:
			len = sizeof(hid0_desc_table);
		break;
		case 0x21:
			len = sizeof(hid1_desc_table);
		break;
		case 0x22:
			len = sizeof(hid2_desc_table);
		break;
		case 0x23:
			len = sizeof(hid3_desc_table);
		break;
		case 0x24:
			len = sizeof(hid4_desc_table); 
		break;
		case 0x25:
			len = sizeof(hid5_desc_table);
		break;
//------------------------------------------------------------
	}
	return len;
}

//--------------------------------------------------------------------
static uint16_t apt_usb_get_desc_length(uint16_t length,uint16_t max_len)
{
	return (length < max_len)? length:max_len;
}



/*	Descriptor Types (Table 9-5)
 *  #define USB_DT_DEVICE                0x01   
 *  #define USB_DT_CONFIG                0x02   
 *  #define USB_DT_STRING                0x03    
 *  #define USB_DT_INTERFACE             0x04     
 *  #define USB_DT_ENDPOINT              0x05    
 *  #define USB_DT_DEVICE_QUALIFIER      0x06
 *  #define USB_DT_OTHER_SPEED_CONFIG    0x07
 *  #define USB_DT_INTERFACE_POWER       0x08
*/

/** \brief usb get device descriptiptor
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_get_device_descriptor(csp_usb_t *ptUsbBase)
{
	uint16_t  ui_length;

	ui_length = (uint16_t)tUsbSetup.b.byLengthL + ((uint16_t)tUsbSetup.b.byLengthH<<8);
	switch(tUsbSetup.b.byValueH)   // buf[3]
	{
        case 1:
            tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&byHidDeviceDescriptor[0];
            tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(0));
            csi_usb_fetch_descriptor(ptUsbBase);
			tUsbSoftCtrl.hwUsbEnumStep  |= USB_ENUM_STEP_DEVICE_DESC;
//			my_printf("byHidDeviceDescriptor\n");	
            break;
		case 2:
			tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&byHidConfigDescriptor[0];
			tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(1));
			csi_usb_fetch_descriptor(ptUsbBase);
			tUsbSoftCtrl.hwUsbEnumStep  |= USB_ENUM_STEP_CONFIG_DESC;
			break;
		case 3:
			switch(tUsbSetup.b.byValueL)		// buf[2]
			{
				case 0:
					tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&byHidStringLangId[0];
					SYSCON->UREG0 = ui_length;
					tUsbEp0Ctrl.hwDescriptorWriteLength = apt_get_desc_leng(2);//apt_usb_get_desc_length(ui_length,apt_get_desc_leng(2));
					csi_usb_fetch_descriptor(ptUsbBase);
					tUsbSoftCtrl.hwUsbEnumStep  |= USB_ENUM_STEP_LANGUAGE_ID;
					break;
				case 1:
					tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&byHidStringVendor[0];
					tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(3));
					csi_usb_fetch_descriptor(ptUsbBase);
					tUsbSoftCtrl.hwUsbEnumStep  |= USB_ENUM_STEP_MANUFAC_STRING;
					break;
				case 2:
					tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&byHidStringProdcut[0];
					tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(4));
					csi_usb_fetch_descriptor(ptUsbBase);
					tUsbSoftCtrl.hwUsbEnumStep  |= USB_ENUM_STEP_PRODUCT_STRING;
					break;
				case 3:
					tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&byHidStringSerial[0];
					tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(7));
					csi_usb_fetch_descriptor(ptUsbBase);
					tUsbSoftCtrl.hwUsbEnumStep  |= USB_ENUM_STEP_SERIAL_STRING;
					break;
				case 0xee:	// String Microsoft OS
					tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&os_string_desc[0];
					tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(6));
					csi_usb_fetch_descriptor(ptUsbBase);
					break;
				default:
					csi_usb_ep0_stall(ptUsbBase);
					break;
				}
			break;
		/*
		case 6:		// DEVICE QUALIFIER	
			// 只有同时支持全速与高速的设备才需要，其它设备不允许			
			tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&device_qualifier_table[0];
			tUsbEp0Ctrl.hwDescriptorWriteLength = usb_get_desc_length(ui_length,GetDescLeng(5));
			usb_fetch_descriptor();
			break;
		*/
		case 0x0f:		// Binary Object store
			csi_usb_ep0_stall(ptUsbBase);
		break;
		default:
			csi_usb_ep0_stall(ptUsbBase);
			break;
	}
}


/** \brief usb get hid descriptor
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_get_hid_descriptor(csp_usb_t *ptUsbBase)
{
	uint16_t  ui_length;

	ui_length = (uint16_t)tUsbSetup.b.byLengthL + ((uint16_t)tUsbSetup.b.byLengthH<<8);
	switch(tUsbSetup.b.byValueH)  // byte[3]
	{
    case USB_HID:
		switch(tUsbSetup.b.byIndexL)  // byte[2]
		{
		case 0x00:// Hid0
			tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&hid0_desc_table[0];
			tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(0x20)); 
			break;
		case 0x01:// Hid1
			tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&hid1_desc_table[0];
			tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(0x21));
			break;
		case 0x02:// Hid2
			tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&hid2_desc_table[0];
			tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(0x22));
			break;
		case 0x03:// Hid3
			tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&hid3_desc_table[0];
			tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(0x23));
			break;
		case 0x04:// Hid4
			tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&hid4_desc_table[0];
			tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(0x24));
			break;
		case 0x05:// Hid5
			tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&hid5_desc_table[0];
			tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(0x25));
			break;
		default:
			csi_usb_ep0_stall(ptUsbBase);
			return;
		}
		csi_usb_fetch_descriptor(ptUsbBase);
		break;
    case USB_REPORT:
		
		tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&byHidReportDescriptor[0];
   		tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(0x10));
		tUsbSoftCtrl.hwUsbEnumStep  |= USB_ENUM_STEP_HIDREPORT_DESC;
//    	switch(tUsbSetup.b.byIndexL)  // byte[2]
//    	{
//    	case 0x00:
//    		tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&inf0_report_descriptor[0];
//    		tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(0x10));
//			tUsbSoftCtrl.hwUsbEnumStep  |= USB_ENUM_STEP_INF0_REPORT;
//    		break;
//    	case 0x01:
//    		tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&inf1_report_descriptor[0];
//    		tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(0x11));
//			tUsbSoftCtrl.hwUsbEnumStep  |= USB_ENUM_STEP_INF1_REPORT;
//    		break;
//    	case 0x02:
//    		tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&inf2_report_descriptor[0];
//    		tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(0x12));
//			tUsbSoftCtrl.hwUsbEnumStep  |= USB_ENUM_STEP_INF2_REPORT;
//    		break;
//    	case 0x03:
//    		tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&inf3_report_descriptor[0];
//    		tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(0x13));
//			tUsbSoftCtrl.hwUsbEnumStep  |= USB_ENUM_STEP_INF3_REPORT;
//    		break;
//    	case 0x04:
//    		tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&inf4_report_descriptor[0];
//    		tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(0x14));
//			tUsbSoftCtrl.hwUsbEnumStep  |= USB_ENUM_STEP_INF4_REPORT;
//    		break;
//    	case 0x05:
//    	    tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&inf5_report_descriptor[0];
//    	    tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(0x15));
//			tUsbSoftCtrl.hwUsbEnumStep  |= USB_ENUM_STEP_INF5_REPORT;
//    	    break;
//    	default:
//    		csi_usb_ep0_stall(ptUsbBase);
//    		return;
//    	}
    	csi_usb_fetch_descriptor(ptUsbBase);
		break;
    default:
    	csi_usb_ep0_stall(ptUsbBase);
    	break;
	}
}

/** \brief usb get report
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_get_report(csp_usb_t *ptUsbBase)
{
	uint8_t i;
	uint16_t  ui_length;
	uint8_t * p_ep0_tx_fifo;
	p_ep0_tx_fifo = tUsbEp0Ctrl.pbyEp0TxFifoBase; 
	ui_length = (uint16_t)tUsbSetup.b.byLengthL + ((uint16_t)tUsbSetup.b.byLengthH<<8);

	switch(tUsbSetup.b.byIndexL)
	{
#ifdef USB_USE_KEYBOARD_CHANNEL
		case 0x02:	// vendor interface
			if(tUsbSetup.b.wValueH == 0x01)
			{		// Hid rep type input
				switch(tUsbSetup.b.byValueL)
				{
					case 0x00:  // media key
						for(i=0;i<5;i++)
						{
							*p_ep0_tx_fifo++ = 0x00;
						}
						csi_usb_ep0_tx_rx_ready(ptUsbBase,4);
					break;
					case 0x01:  // keyboard
						*p_ep0_tx_fifo++ = 0x01;
						for(i=0;i<9;i++)
						{
							*p_ep0_tx_fifo++ = 0x00;
						}
						csi_usb_ep0_tx_rx_ready(ptUsbBase,9);
					break;
					case 0x02:  // media key
						*p_ep0_tx_fifo++ = 0x02;
						for(i=0;i<5;i++)
						{
							*p_ep0_tx_fifo++ = 0x00;
						}
						csi_usb_ep0_tx_rx_ready(ptUsbBase,5);
					break;
				}
			}
		break;
#endif

		case 0x04:		// Vendor interface
			if(tUsbSetup.b.byValueH == 0x01)
			{		// Hid rep type input
				switch(tUsbSetup.b.byValueL)
				{
					case 0x22:
						*p_ep0_tx_fifo++ = 0x22;
						for(i=0;i<15;i++)
						{
							*p_ep0_tx_fifo++ = 0x00;
						}
						csi_usb_ep0_tx_rx_ready(ptUsbBase,16);
					break;
					case 0x23:
						*p_ep0_tx_fifo++ = 0x23;
						for(i=0;i<31;i++)
						{
							*p_ep0_tx_fifo++ = 0x00;
						}
						csi_usb_ep0_tx_rx_ready(ptUsbBase,32);
					break;
					case 0x24:
						tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&hid_report_table[0];
						tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(0x16));
						csi_usb_fetch_descriptor(ptUsbBase);
					break;
					default:
						csi_usb_ep0_stall(ptUsbBase);
					break;
				}
			}
			else  csi_usb_ep0_stall(ptUsbBase);
		break;
		case 0x03:
			if(tUsbSetup.b.byValueH == 0x01)
			{		// Hid rep type input
				switch(tUsbSetup.b.byValueL)
				{
					case 0x02:
						*p_ep0_tx_fifo++ = 0x02;
						for(i=0;i<3;i++)
						{
							*p_ep0_tx_fifo++ = 0x00;
						}
						csi_usb_ep0_tx_rx_ready(ptUsbBase,4);
					break;
					case 0x23:
						*p_ep0_tx_fifo++ = 0x23;
						for(i=0;i<31;i++)
						{
							*p_ep0_tx_fifo++ = 0x00;
						}
						csi_usb_ep0_tx_rx_ready(ptUsbBase,32);
					break;
					case 0x24:
						tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&hid_report_table[0];
						tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(0x16));
						csi_usb_fetch_descriptor(ptUsbBase);
					break;
					default:
						csi_usb_ep0_stall(ptUsbBase);
					break;
				}
			}
			else  csi_usb_ep0_stall(ptUsbBase);
			break;
		default:
			csi_usb_ep0_stall(ptUsbBase);
		return;
	}
}




