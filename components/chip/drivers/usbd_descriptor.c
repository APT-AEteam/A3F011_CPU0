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
#include <drv/usbd.h>
#include <drv/usbd_descriptor.h>
#include <drv/usbd_audio.h>

extern csi_usb_setup_t        tUsbSetup;
extern csi_usb_ep0_ctrl_t     tUsbEp0Ctrl;
extern csi_usb_soft_ctrl_t    tUsbSoftCtrl;

volatile char device_desc_table[18] =     //  18
{
	0x12,               	// bLength
	0x01,               	// bDescriptorType
	0x00, 0x02,         	// bcdUSB(2.00)
	0x00,               	// bDeviceClass
	0x00,               	// bDeviceSubClass
	0x00,               	// bDeviceProtocol
	EP0_MAX_PACKET_SIZE,	// bMaxPacketSize0
	DVIDL, DVIDH,			// idVendor
	DPIDL, DPIDH,			// idProduct
	0x00, 0x01,         	// bcdDevice
	0x01,               	// iManufacturer
	0x02,               	// iProduct
	0x00,               	// iSerialNumber
	0x01                	// bNumConfigurations
};

 /*
 * DEVICE QUALIFIER
 * If a full-speed only device receives a GetDescriptor() request for a device_qualifier, 
 * it must respond with a request error. Then, 
 * the host must not make a request for an other_speed_configuration descriptor.
 */
const char device_qualifier_table[] = 
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
};

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

const char config_desc_table[] =			// Configuration_Length
{
/*
 *  Configuration:
 *  0x09: Length
 *  0x02: DescriptorType: ConfigDescriptor
 *  0xE0
 *  0xE00: TotalLength:0x00E0
 *  0x05: NumInterfaces:5
 *  0x01: ConfigurationValue: 1
 *  0x00: ConfigurationSrting
 *  0xA0: Attributes: BusPower,No RemoteWakeup
 *  0x32: 0x32*2mA = 100mA
 */
0x09,0x02,0x00,0x01,0x05,0x01,0x00,0x80,0x32,

/*
 *   Standard interface AC descriptor
 *       Interface 0,Alternate Setting 0
 *       bNumEndpoints = 0x00, bInterfaceClass=0x01(audio),
 *       bInterfaceSubClass=0x01(audio Ctl)
 *   0x09: Length
 *   0x04: DescriptorType:interface
 *   0x00: InterfaceNum:
 *   0x00: AlternateSetting
 *   0x00: NumEndpoint
 *   0x01: InterfaceClass:audio:0x01
 *   0x01: InterfaceSubClass:audio ctl:0x01
 *   0x00: InterfaceProtocol:None
 *   0x00: Interface String:0x00
 */
0x09,0x04,0x00,0x00,0x00,0x01,0x01,0x00,0x00,

/*--------------------------------------------------------------------------------------------------------
 *   Class-specific AC interface descriptor,audio interface(0x24),audio control header(0x01)
 *   Total length 0x0047,Number of streaming interface 2,interfaceNr 2,1
 *   0x0A: Length
 *   0x24: DescriptorType:audio interface descriptor:
 *   0x01: DescriptorSubType:audio control header:
 *   0x00:
 *   0x01: bcdADC:audio Device Class V1.00:0x0100
 *   0x47:
 *   0x00: TotalLength:0x0047
 *   0x02: InCollection:2 AudioStreaming interface
 *            The number of AudioStreaming and MIDIStreaming interfaces
 *   0x01: InterfaceNr(1): AudioStreaming interface 1 belongs to this AudioControl interface
 *   0x02: InterfaceNr(2): AudioStreaming interface 2 belongs to this AudioControl interface
 */
0x0A,0x24,0x01,0x00,0x01,0x47,0x00,0x02,0x01,0x02,
0x0C,0x24,0x02,0x01,0x01,0x01,0x00,0x02,0x03,0x00,0x00,0x00,

/*
 *   Input Terminal Descriptor(Microphone)
 *       Terminal id 0x02
 *       USB Microphone IT:audio interface descriptor ,audio control input terminal,
 *       Microphone(0x0201),Input Terminal(0x02),
 *       One channel:Left Front,Right Front
 *   0x0C: Length
 *   0x24: DescriptorType: audio interface descriptor
 *   0x02: DescriptorSubType: Input Terminal
 *   0x02: Terminal ID: 0x02
 *   0x01
 *   0x02: TerminalType: USB Microphone:0x0201
 *   0x00: AssocTerminal
 *   0x01: NrChannels:1 channel
 *   0x01:
 *   0x00: ChannelConfig:Left Front,Right Front 0x0001
 *   0x00: ChannelName String
 *   0x00: Terminal String
 */
#ifdef USB_LIB_MIC_ONE_CHANNEL_INPUT
  0x0C,0x24,0x02,0x02,0x01,0x02,0x00,0x01,0x01,0x00,0x00,0x00,
#endif
#ifdef USB_LIB_MIC_TWO_CHANNEL_INPUT
  0x0C,0x24,0x02,0x02,0x01,0x02,0x00,0x02,0x01,0x00,0x00,0x00,
#endif

// 0x09,0x24,0x03,0x06,0x02,0x03,0x00,0x09,0x00,		// 0x0302:headphone
0x09,0x24,0x03,0x06,0x01,0x03,0x00,0x09,0x00,		//  0x0301:speaker
0x09,0x24,0x03,0x07,0x01,0x01,0x00,0x0A,0x00,

/*
 * 0x0A: Length
 * 0x24: audio interface descriptor
 * 0x06: Audio Feature Unit
 * 0x09: Uint ID:0x09
 * 0x01: Source ID:0x01
 * 0x01: Cotrols size: 1byte
 * 0x01: Controls:Mute
 * 0x02: Controls(0):Volume
 * 0x02: Controls(1):Volume
 * 0x00: Feature string
 */
0x0A,0x24,0x06,0x09,0x01,0x01,0x01,0x02,0x02,0x00,
0x09,0x24,0x06,0x0A,0x02,0x01,0x43,0x00,0x00,
//-------------------------------------------------------------------------------------------------

0x09,0x04,0x01,0x00,0x00,0x01,0x02,0x00,0x00,
0x09,0x04,0x01,0x01,0x01,0x01,0x02,0x00,0x00,
0x07,0x24,0x01,0x01,0x01,0x01,0x00,

/*
 *   0x0E: Length:
 *   0x24: DescriptorType:audio interface descriptor:
 *   0x02: DescriptorSubType:Format_type:0x02
 *   0x01: FormatType:Format type 1
 *   0x02: NumberOfChannel:0x02
 *   0x02: SubframeSize:2 byte
 *   0x10: BitsResolution:16 bit: 0x10
 *   0x02: SampleFreqType: Two sampling frequency:0x02 
 *   0x00AC44: 44.1K:
 *   0x00BB80: 48K:
 */
// hp sample freq
#ifdef USB_AUDIO_SAMPLE_44K1_48K
0x0E,0x24,0x02,0x01,0x02,0x02,0x10,0x02,0x44,0xAC,0x00,0x80,0xBB,0x00,     // 44.1K,48K
#endif 
#ifdef USB_AUDIO_SAMPLE_44K1
0x0E,0x24,0x02,0x01,0x02,0x02,0x10,0x02,0x44,0xAC,0x00,0x80,0x3E,0x00,     // 44.1K,16K
#endif
#ifdef USB_AUDIO_SAMPLE_48K
0x0E,0x24,0x02,0x01,0x02,0x02,0x10,0x02,0x80,0xBB,0x00,0x80,0xBB,0x00,     // 48K,48K
#endif
/*
 *   0x09: Length
 *   0x05: DescriptorType:endpoint descriptor
 *   0x01: EndpointAddress: Output endpoint 1
 *   0x09: Attributes:0x09 ISOchronout
 *   0xC8:
 *   0x00: MaxPacketSize:0x00C8
 *   0x01: interval:One packet per frame:0x01
 *   0x00: Refresh:Unused
 *   0x00: bSynchAddress: Unused
 */
0x09,0x05,0x01,0x09,0xC0,0x00,0x01,0x00,0x00,
0x07,0x25,0x01,0x01,0x01,0x01,0x00,
0x09,0x04,0x02,0x00,0x00,0x01,0x02,0x00,0x00,
0x09,0x04,0x02,0x01,0x01,0x01,0x02,0x00,0x00,
0x07,0x24,0x01,0x07,0x01,0x01,0x00,

/*
 *   0x0E: Length:
 *   0x24: DescriptorType:audio interface descriptor:
 *   0x02: DescriptorSubType:Format_type:0x02
 *   0x01: FormatType:Format type 1
 *   0x02: NumberOfChannel:0x02
 *   0x02: SubframeSize:2 byte
 *   0x10: BitsResolution:16 bit: 0x10
 *   0x02: SampleFreqType: Two sampling frequency:0x02
 *   0x00AC44: 44.1K:
 *   0x00BB80: 48K:
 */
// 0x0E,0x24,0x02,0x01,0x01,0x02,0x10,0x02,0x80,0xBB,0x00,0x44,0xAC,0x00,
#ifdef USB_LIB_MIC_ONE_CHANNEL_INPUT
  0x0E,0x24,0x02,0x01,0x01,0x02,0x10,0x02,0x44,0xAC,0x00,0x80,0xBB,0x00,     // 48K,48K
#endif
#ifdef USB_LIB_MIC_TWO_CHANNEL_INPUT
	// MIC sample freq
	#ifdef USB_AUDIO_SAMPLE_44K1_48K
		0x0E,0x24,0x02,0x01,0x02,0x02,0x10,0x02,0x44,0xAC,0x00,0x80,0xBB,0x00,     // 44.1K,48K
	#endif
	#ifdef USB_AUDIO_SAMPLE_48K
		0x0E,0x24,0x02,0x01,0x02,0x02,0x10,0x02,0x80,0xBB,0x00,0x80,0xBB,0x00,     // 48K,48K
	#endif
	#ifdef USB_AUDIO_SAMPLE_44K1
		0x0E,0x24,0x02,0x01,0x02,0x02,0x10,0x02,0x44,0xAC,0x00,0x80,0x3E,0x00,     // 44.1K,16K
	#endif
#endif

/*
 *   0x09: Length
 *   0x05: DescriptorType:endpoint descriptor
 *   0x81: EndpointAddress: input endpoint 1
 *   0x05: Attributes:0x09 ISOchronout
 *   0x64:
 *   0x00: MaxPacketSize:0x0064
 *   0x01: interval:One packet per frame:0x01
 *   0x00: Refresh:Unused
 *   0x00: bSynchAddress: Unused
 */
#ifdef USB_LIB_MIC_ONE_CHANNEL_INPUT
  0x09,0x05,0x81,0x05,0x60,0x00,0x01,0x00,0x00,		// 0x60 = 96 = 48K*2
#endif
#ifdef USB_LIB_MIC_TWO_CHANNEL_INPUT
  0x09,0x05,0x81,0x05,0xC0,0x00,0x01,0x00,0x00,		// 0xC0 = 192 = 48K*4
#endif

0x07,0x25,0x01,0x01,0x00,0x00,0x00,

//--------------------------------------------------
// Media keys
0x09,0x04,0x03,0x00,0x01,0x03,0x00,0x00,0x00,
0x09,0x21,0x10,0x01,0x00,0x01,0x22,40,0x00,
0x07,0x05,0x83,0x03,0x40,0x00,0x05,
//--------------------------------------------------
// Vendor
0x09,0x04,0x04,0x00,0x02,0x03,0x00,0x00,0x00,
0x09,0x21,0x10,0x01,0x00,0x01,0x22,76,0x00,
0x07,0x05,0x84,0x03,0x40,0x00,0x05,
0x07,0x05,0x04,0x03,0x40,0x00,0x05
//===============================================================
};

//--------------------------------------------------------------------
const char  string_langid_table[] =
{
	0x04, 0x03, 0x09, 0x04
};
//--------------------------------------------------------------------
// Manufacturer string
const char  string_index1_table[] =
{
	16,0x03,
	'N',0x00,	'a',0x00,	'n',0x00,	'o',0x00,
	's',0x00,	'I',0x00,	'C',0x00
 };

//--------------------------------------------------------------------
// product string
volatile char string_index2_table[58] =     //  52
{
	0x20,0x03,
	'N', 0x00,	'A', 0x00,	'N', 0x00,	'O', 0x00,
	' ', 0x00,	'I', 0x00,	'C', 0x00,	' ', 0x00,
	'H', 0x00,	'E', 0x00,	'A', 0x00,	'D', 0x00,
	'S', 0x00,	'E', 0x00,	'T', 0x00,	0x00, 0x00,
	0x00, 0x00,	0x00, 0x00,	0x00, 0x00,	0x00, 0x00,
	0x00, 0x00,	0x00, 0x00,	0x00, 0x00,	0x00, 0x00,
	0x00, 0x00,	0x00, 0x00,	0x00, 0x00,	0x00, 0x00
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
//=========================================================================
const char inf0_report_descriptor[] =    //
{
};
const char inf1_report_descriptor[] =    //
{
};

const char inf2_report_descriptor[] =
{
};

const char inf3_report_descriptor[] =
{
	// Media Key
	// ReportID(0x02) + 6bit(Media Key) + 2bit(Rev)
	// eg. Volume Up: 0x02,0x01
	0x05 , 0x0C , 		// USAGE_PAGE (Consumer Devices)
	0x09 , 0x01 , 		// USAGE (Consumer Control)
	0xA1 , 0x01 , 		// COLLECTION (Application)
	0x85 , 0x02 , 		// REPORT_ID (0x02)
	0x15 , 0x00 ,		// LOGICAL_MINIMUM (0)
	0x25 , 0x01 , 		// LOGICAL_MAXIMUM (1)
	0x75 , 0x01 , 		// REPORT_SIZE (1)
	0x95 , 0x06 ,		// REPORT_COUNT (6) 
	0x09 , 0xE9 , 		// 1. USAGE (Volume Up)
	0x09 , 0xEA , 		// 2. USAGE (Volume Down)
	0x09 , 0x9D , 		// 3. USAGE (Mute) 		
	0x0A , 0x24 , 0x02, 		// 4. USAGE (AC Back) 
	0x0A , 0x25 , 0x02, 		// 5. USAGE (AC Forward) 
	0x0A , 0x26 , 0x02, 		// 6. USAGE (AC Stop) 				
	0x81 , 0x02 , 		// INPUT (Data,Var,Abs)
	0x95 , 0x01 , 		// REPORT_COUNT (1)
	0x75 , 0x02 ,		// REPORT_SIZE (2)
	0x81 , 0x03 , 		// INPUT (Cnst,Var,Abs)
	0xC0 			
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

//--------------------------------------------------------------------
const char mixer_unit_array1[] =
{
	0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x80,0x00,0x80,0x00,0x00
};
//--------------------------------------------------------------------
const char mixer_unit_array2[] =
{
	0x00,0x01,0x00,0x01,0x00,0x01,
	0x00,0x01,0x00,0x01,0x00,0x01
};

static uint16_t apt_get_desc_leng(uint8_t byType)
{
	uint16_t len = 0;

	switch(byType)
	{
		case 0:
			len = sizeof(device_desc_table);
		break;
		case 1:
			len = sizeof(config_desc_table);
		break;
		case 2:
			len = sizeof(string_langid_table);
		break;
		case 3:
			len = sizeof(string_index1_table);
		break;
		case 4:
			len = string_index2_table[0]; 
		break;
		case 5:
			len = sizeof(device_qualifier_table);
		break;
		case 6:
			len = sizeof(os_string_desc);
		break;

//------------------------------------------------------------
		case 0x10:
			len = sizeof(inf0_report_descriptor);
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
void csi_usb_set_interface_cur(csp_usb_t *ptUsbBase)
{
	switch(tUsbSetup.b.byValueH)		// byte[3]
	{
		// The wValue field specifies the Control Selector (CS) in the high byte
		// and the Channel Number (CN) in	the low byte.
		case 0x00:
			// Set Selector Unit Control Request Values
			tUsbEp0Ctrl.bySetSelectorUnit = 1;
			csi_usb_ep0_tx_rx_ready(ptUsbBase,0);
		break;
		//  0x01: MUTE_CONTROL
		case 0x01:
			if(tUsbSetup.b.byIndexH == 0x09){   // B[5]
				tUsbEp0Ctrl.bySetSpeakerMute = 1; 
			}
			if(tUsbSetup.b.byIndexH == 0x0A){
				tUsbEp0Ctrl.bySetMicMute = 1;
			}
			csi_usb_ep0_tx_rx_ready(ptUsbBase,0);
		break;
		// 0x02: VOLUME_CONTROL
		case 0x02:
			if(tUsbSetup.b.byIndexH == 0x09) { // Feature Unit ID = 0x09 : HeadPhone
				tUsbEp0Ctrl.bySetSpeakerVol = 1;
			}
			else if(tUsbSetup.b.byIndexH == 0x0A){   // Feature Unit ID = 0x0A : Mic
				tUsbEp0Ctrl.bySetMicVol = 1;
			}
			csi_usb_ep0_tx_rx_ready(ptUsbBase,0);
		break;
		// 0x03: BASS_CONTROL
		case 0x03:
			csi_usb_ep0_stall(ptUsbBase);
		break;
		// 0x04: MID_CONTROL
		case 0x04:
			csi_usb_ep0_stall(ptUsbBase);
		break;
		// 0x05: TREBLE_CONTROL
		case 0x05:
			csi_usb_ep0_stall(ptUsbBase);
		break;
		// 0x06: GRAPHIC_EQUALIZER_CONTROL
		case 0x06:
			csi_usb_ep0_stall(ptUsbBase);
		break;
		// 0x07: AUTOMATIC_GAIN_CONTROL
		case 0x07:
			csi_usb_ep0_stall(ptUsbBase);
		break;
		// 0x08: DELAY_CONTROL
		case 0x08:
			csi_usb_ep0_stall(ptUsbBase);
		break;
		// 0x09: BASS_BOOST_CONTROL
		case 0x09:
			tUsbEp0Ctrl.bySetBassBoost = 1;
			csi_usb_ep0_tx_rx_ready(ptUsbBase,0);
		break;
		default:
			csi_usb_ep0_stall(ptUsbBase);
		break;
	}
}

/*
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
            tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&device_desc_table[0];
            tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(0));
            csi_usb_fetch_descriptor(ptUsbBase);
			tUsbSoftCtrl.hwUsbEnumStep  |= USB_ENUM_STEP_DEVICE_DESC;
            break;
		case 2:
			tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&config_desc_table[0];
			tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(1));
			csi_usb_fetch_descriptor(ptUsbBase);
			tUsbSoftCtrl.hwUsbEnumStep  |= USB_ENUM_STEP_CONFIG_DESC;
			break;
		case 3:
			switch(tUsbSetup.b.byValueL)		// buf[2]
			{
				case 0:
					tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&string_langid_table[0];
					tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(2));
					csi_usb_fetch_descriptor(ptUsbBase);
					tUsbSoftCtrl.hwUsbEnumStep  |= USB_ENUM_STEP_LANGUAGE_ID;
					break;
				case 1:
					tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&string_index1_table[0];
					tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(3));
					csi_usb_fetch_descriptor(ptUsbBase);
					tUsbSoftCtrl.hwUsbEnumStep  |= USB_ENUM_STEP_MANUFAC_STRING;
					break;
				case 2:
					tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&string_index2_table[0];
					tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(4));
					csi_usb_fetch_descriptor(ptUsbBase);
					tUsbSoftCtrl.hwUsbEnumStep  |= USB_ENUM_STEP_PRODUCT_STRING;
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
    	switch(tUsbSetup.b.byIndexL)  // byte[2]
    	{
    	case 0x00:
    		tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&inf0_report_descriptor[0];
    		tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(0x10));
			tUsbSoftCtrl.hwUsbEnumStep  |= USB_ENUM_STEP_INF0_REPORT;
    		break;
    	case 0x01:
    		tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&inf1_report_descriptor[0];
    		tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(0x11));
			tUsbSoftCtrl.hwUsbEnumStep  |= USB_ENUM_STEP_INF1_REPORT;
    		break;
    	case 0x02:
    		tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&inf2_report_descriptor[0];
    		tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(0x12));
			tUsbSoftCtrl.hwUsbEnumStep  |= USB_ENUM_STEP_INF2_REPORT;
    		break;
    	case 0x03:
    		tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&inf3_report_descriptor[0];
    		tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(0x13));
			tUsbSoftCtrl.hwUsbEnumStep  |= USB_ENUM_STEP_INF3_REPORT;
    		break;
    	case 0x04:
    		tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&inf4_report_descriptor[0];
    		tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(0x14));
			tUsbSoftCtrl.hwUsbEnumStep  |= USB_ENUM_STEP_INF4_REPORT;
    		break;
    	case 0x05:
    	    tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&inf5_report_descriptor[0];
    	    tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,apt_get_desc_leng(0x15));
			tUsbSoftCtrl.hwUsbEnumStep  |= USB_ENUM_STEP_INF5_REPORT;
    	    break;
    	default:
    		csi_usb_ep0_stall(ptUsbBase);
    		return;
    	}
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

/** \brief usb get interface cur
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_get_interface_cur(csp_usb_t *ptUsbBase)	// 0x81
{
	uint8_t * p_ep0_tx_fifo= tUsbEp0Ctrl.pbyEp0TxFifoBase; 
	uint16_t  ui_length = (uint16_t)tUsbSetup.b.byLengthL + ((uint16_t)tUsbSetup.b.byLengthH<<8);

	switch(tUsbSetup.b.byValueH)   // byte[3]
	{
		// Get Selector Unit Control Request Values
		case 0x00: //GET_SELECTOR_UNIT
			if(tUsbSetup.b.byIndexH == 0x07)  // B[5]
			{
				*p_ep0_tx_fifo++ = tUsbEp0Ctrl.bySelectorUnit;
				csi_usb_ep0_tx_rx_ready(ptUsbBase,1);
			}
			else if(tUsbSetup.b.byIndexH == 0x09) //get mixer unit control
			{
				tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&mixer_unit_array1[0];
				tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,12);
				csi_usb_fetch_descriptor(ptUsbBase);
			}else{
				csi_usb_ep0_stall(ptUsbBase);
			}
		break;
		//  0x01: MUTE_CONTROL
		case 0x01:
			if(tUsbSetup.b.byIndexH == 0x09){   // Feature Unit ID = 0x09 : HeadPhone
				*p_ep0_tx_fifo++ = tUsbEp0Ctrl.bySpeakerMuteValue;
				csi_usb_ep0_tx_rx_ready(ptUsbBase,1);
			}
			else if(tUsbSetup.b.byIndexH == 0x0A){
				*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byMicMuteValue;
				csi_usb_ep0_tx_rx_ready(ptUsbBase,1);
			}else{
				csi_usb_ep0_stall(ptUsbBase);
			}			
		break;
		// 0x02: VOLUME_CONTROL
		case 0x02:
			if(tUsbSetup.b.byIndexH == 0x09)
			{
				*p_ep0_tx_fifo++ = tUsbEp0Ctrl.bySpeakerVolValueL;
				*p_ep0_tx_fifo++ = tUsbEp0Ctrl.bySpeakerVolValueH;
				csi_usb_ep0_tx_rx_ready(ptUsbBase,2);
			}
			else if(tUsbSetup.b.byIndexH == 0x0A)
			{
				*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byMicVolValueL;
				*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byMicVolValueH;
				csi_usb_ep0_tx_rx_ready(ptUsbBase,2);
			}
			else{
				csi_usb_ep0_stall(ptUsbBase);
			}			
		break;
		// 0x03: BASS_CONTROL
		case 0x03:
			csi_usb_ep0_stall(ptUsbBase);
		break;
		// 0x04: MID_CONTROL
		case 0x04:
			csi_usb_ep0_stall(ptUsbBase);
		break;
		// 0x05: TREBLE_CONTROL
		case 0x05:
			csi_usb_ep0_stall(ptUsbBase);
		break;
		// 0x06: GRAPHIC_EQUALIZER_CONTROL
		case 0x06:
			csi_usb_ep0_stall(ptUsbBase);
		break;
		// 0x07: AUTOMATIC_GAIN_CONTROL
		case 0x07:
			*p_ep0_tx_fifo++ = 0x00;
			csi_usb_ep0_tx_rx_ready(ptUsbBase,1);
		break;
		// 0x08: DELAY_CONTROL
		case 0x08:
			csi_usb_ep0_stall(ptUsbBase);
		break;
		// 0x09: BASS_BOOST_CONTROL
		case 0x09:
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byBassBoost;
			csi_usb_ep0_tx_rx_ready(ptUsbBase,1);
		break;
		default:
			csi_usb_ep0_stall(ptUsbBase);
		break;
	}
}

/** \brief usb get interface min
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_get_interface_min(csp_usb_t *ptUsbBase)   // 0x82
{
	uint8_t * p_ep0_tx_fifo = tUsbEp0Ctrl.pbyEp0TxFifoBase; 
	uint16_t  ui_length = (uint16_t)tUsbSetup.b.byLengthL + ((uint16_t)tUsbSetup.b.byLengthH<<8);

	switch(tUsbSetup.b.byValueH)  // B[3]
	{
		// 0x02: VOLUME_CONTROL
		case 0x02:
			if(tUsbSetup.b.byIndexH == 0x09)		// B[5] SPEAKER
			{
				*p_ep0_tx_fifo++ = 0x00;	// 0xDD = -(0x100 - 0xDD) = -35DB
				*p_ep0_tx_fifo++ = 0x00;
				csi_usb_ep0_tx_rx_ready(ptUsbBase,2);
			}
			else if(tUsbSetup.b.byIndexH == 0x0A)	// MIC
			{
				*p_ep0_tx_fifo++ = 0x00;	// 0x00 = 0DB
				*p_ep0_tx_fifo++ = 0x00;
				csi_usb_ep0_tx_rx_ready(ptUsbBase,2);
			}else{
				csi_usb_ep0_stall(ptUsbBase);
			}			
			break;
		case 0x00:
			tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&mixer_unit_array1[0];
			tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,12);
			csi_usb_fetch_descriptor(ptUsbBase);
			break;
		default:
			csi_usb_ep0_stall(ptUsbBase);
			break;
	}
}

/** \brief usb get interface max
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_get_interface_max(csp_usb_t *ptUsbBase)		// 0x83
{
	uint8_t * p_ep0_tx_fifo = tUsbEp0Ctrl.pbyEp0TxFifoBase; 
	uint16_t  ui_length = (uint16_t)tUsbSetup.b.byLengthL + ((uint16_t)tUsbSetup.b.byLengthH<<8);

	switch(tUsbSetup.b.byValueH)   // B[3]
	{
		// 0x02: VOLUME_CONTROL
		//       0x0002: 0.0078DB
		//       0x0001: 0.0039DB
		//       0x0000: 0DB
		//       0xFFFF: -0.0039DB
		//       0xFFFE: -0.0078DB
		case 0x02:
			if(tUsbSetup.b.byIndexH == 0x09)		//SPEAKER
			{
				*p_ep0_tx_fifo++ = 0x64;	// 0x1194 = 4500
				*p_ep0_tx_fifo++ = 0x00;
				csi_usb_ep0_tx_rx_ready(ptUsbBase,2);
			}
			else if(tUsbSetup.b.byIndexH == 0x0A) 
			{
				*p_ep0_tx_fifo++ = 0x64;	// 0x23: 35DB
				*p_ep0_tx_fifo++ = 0x00;
				csi_usb_ep0_tx_rx_ready(ptUsbBase,2);
			}else{
				csi_usb_ep0_stall(ptUsbBase);
			}			
			break;
		case 0x00:
			tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&mixer_unit_array1[0];
			tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,12);
			csi_usb_fetch_descriptor(ptUsbBase);
			break;
		default:
			csi_usb_ep0_stall(ptUsbBase);
			break;
    }
}

/** \brief usb get interface res
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */
void csi_usb_get_interface_res(csp_usb_t *ptUsbBase)    // 0x84
{
	uint8_t * p_ep0_tx_fifo = tUsbEp0Ctrl.pbyEp0TxFifoBase; 
	uint16_t  ui_length = (uint16_t)tUsbSetup.b.byLengthL + ((uint16_t)tUsbSetup.b.byLengthH<<8);

    switch(tUsbSetup.b.byValueH)  // B[3]
	{
    	// 0x02: VOLUME_CONTROL
		case 0x02:
			if(tUsbSetup.b.byIndexH == 0x09)  // SPEAKER
			{	// B[5]
				*p_ep0_tx_fifo++ = 0x01; 		// 0x1C2 = 450
				*p_ep0_tx_fifo++ = 0x00;
				csi_usb_ep0_tx_rx_ready(ptUsbBase,2);
			}
			else if(tUsbSetup.b.byIndexH == 0x0A)  // MIC
			{
				*p_ep0_tx_fifo++ = 0x01; 		// 0x1C2 = 450
				*p_ep0_tx_fifo++ = 0x00;
				csi_usb_ep0_tx_rx_ready(ptUsbBase,2);
			}else{
				csi_usb_ep0_stall(ptUsbBase);
			}			
			break;
		case 0x00:
			tUsbEp0Ctrl.pbyWriteDescriptor = (uint8_t *)&mixer_unit_array2[0];
			tUsbEp0Ctrl.hwDescriptorWriteLength = apt_usb_get_desc_length(ui_length,12);
			csi_usb_fetch_descriptor(ptUsbBase);
			break;
		default:
			csi_usb_ep0_stall(ptUsbBase);
			break;
	}
}
