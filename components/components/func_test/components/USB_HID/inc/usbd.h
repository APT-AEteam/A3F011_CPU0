/*
 * Copyright (C) 2017-2020 Alibaba Group Holding Limited
 */

/***********************************************************************//** 
 * \file  usbd.h
 * \brief  csi usbd driver
 * \copyright Copyright (C) 2015-2021 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2023-1-30 <td>V0.0 <td>YYM    <td>initial
 * </table>
 * *********************************************************************
*/

#ifndef _DRV_USBD_H_
#define _DRV_USBD_H_

#include <drv/common.h>
#include "csp.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EP0_MAX_PACKET_SIZE  		32
#define DVIDL       0x83//0x06
#define DVIDH       0x04//0x32

#define DPIDL       0x51//0x02
#define DPIDH       0x57//0x10

#define   USB_ENUM_STEP_DEVICE_DESC			0x0001
#define   USB_ENUM_STEP_CONFIG_DESC			0x0002
#define   USB_ENUM_STEP_LANGUAGE_ID			0x0004
#define   USB_ENUM_STEP_MANUFAC_STRING		0x0008
#define   USB_ENUM_STEP_PRODUCT_STRING		0x0010
#define   USB_ENUM_STEP_INF0_REPORT		    0x0020
#define   USB_ENUM_STEP_INF1_REPORT		    0x0040
#define   USB_ENUM_STEP_INF2_REPORT		    0x0080
#define   USB_ENUM_STEP_INF3_REPORT		    0x0100
#define   USB_ENUM_STEP_INF4_REPORT		    0x0200
#define   USB_ENUM_STEP_INF5_REPORT		    0x0400

typedef union 
{
    struct {
        uint8_t byRequestType;
        uint8_t byRequest;
        uint8_t byValueL;
        uint8_t byValueH;
        uint8_t byIndexL;
        uint8_t byIndexH;
        uint8_t byLengthL;
        uint8_t byLengthH;
    }b;
    uint8_t byBuf[8];
}csi_usb_setup_t;


typedef enum {
    USB_PHY_INTERNAL_OSC = 0, 
    USB_PHY_EXTERN_OSC 
} usb_phy_osc_e;

/*
 *  USB IP正常工作相关的控制
 */
typedef struct 
{
    usb_phy_osc_e eUsbPhyMode;
    uint32_t   wFifoBaseAddress;
    uint16_t   hwFifoOutLen[7];     // ep0~6 out fifo length,byte
    uint16_t   hwFifoInLen[7];      // ep0~6 in fifo length,byte
    uint16_t   hwHpVolumeInit;
    uint16_t   hwMicVolumeInit;
}csi_usb_config_t;

/*
 *  记录USB不同endpoind fifo的基地址
 */
typedef struct 
{    
    uint8_t * pbyEpRxFifoStar[7];
    uint8_t * pbyEpTxFifoStar[7];
}csi_usb_ep_fifo_adr_t;

/*
 *  USB 枚举相关的控制
 */
typedef struct 
{    
    uint8_t * pbyEp0RxFifoBase;  
    uint8_t * pbyEp0TxFifoBase;    
    uint8_t * pbyWriteDescriptor;  
    uint16_t  hwDescriptorWriteLength;

    uint8_t  byUsbConfig;
    uint8_t  bySetNewUsbAddress;
    uint8_t  byNewUsbAddress;
    uint8_t  byDeviceFeature;
    uint8_t  byInterface[6];
    uint8_t  byEpTxFeature[6];
    uint8_t  byEpRxFeature[6];
    uint8_t  byIdleTime[6];
    uint8_t  byProtocolType[6];

    uint8_t  bySetReport;
    uint8_t  byReportId;
    uint8_t  byReportInterfaceNumber;

    uint8_t  bySetMicSampleFreq;
    uint8_t  byMicSampleFreqH;
    uint8_t  byMicSampleFreqM;
    uint8_t  byMicSampleFreqL;

    uint8_t  bySetSpeakerSampleFreq;
    uint8_t  bySpeakerSampleFreqH;
    uint8_t  bySpeakerSampleFreqM;
    uint8_t  bySpeakerSampleFreqL;

    uint8_t  bySetBassBoost;
    uint8_t  byBassBoost;

    uint8_t  bySetSelectorUnit;
    uint8_t  bySelectorUnit;

    uint8_t  bySetSpeakerVol;
    uint8_t  bySpeakerVolValueH;
    uint8_t  bySpeakerVolValueL;

    uint8_t  bySetSpeakerMute;
    uint8_t  bySpeakerMuteValue;

    uint8_t  bySetMicVol;
    uint8_t  byMicVolValueH;
    uint8_t  byMicVolValueL;

    uint8_t  bySetMicMute;
    uint8_t  byMicMuteValue;

    uint8_t  byKeyLedStae;
}csi_usb_ep0_ctrl_t;

/*
 *  USB相关的软件标志位
 */
typedef struct 
{ 
    uint32_t wMicFifoErrNum;          // 填入MIC FIFO数据出错次数
	uint16_t hwUsbEnumStep;          // USB 枚举步骤
    uint16_t hwMicFifoRdCntBack;      // 在中断中备份MIC 数据长度
    uint16_t hwHpFifoWrPtrBack;       // 在中断中备份HP Fifo状态
    uint16_t hwHpFifoWrCntBack;       // 在中断中备份HP 数据长度

    uint16_t hwUsbSetHpVolume;         // 主机设置的耳机音量
    uint16_t hwUsbSetMicVolume;        // 主机设置的麦克风音量
    

    uint8_t  bySuspend; 
    uint8_t  bySofIrq; 
    uint8_t  byMicSampleRateAdj;
    uint8_t  bySpeakerSampleRateAdj;
    uint8_t  bySpeakerVolAdj;
    uint8_t  byMicVolAdj;

    uint8_t  byVendorReceiveOnePacket;
    uint8_t  byMicInterrupt;
    uint8_t  byHpInterrupt;

    uint8_t  byUsbActiv;

}csi_usb_soft_ctrl_t;


/** \brief power on init usb  
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \param[in] ptUsbCfg: pointer of usb parameter config structure
 *  \return error code \ref csi_error_t
 */  
csi_error_t  csi_usb_init(csp_usb_t *ptUsbBase,csi_usb_config_t ptUsbCfg);


/** \brief usb reset
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_reset(csp_usb_t *ptUsbBase);

/** \brief usb dp pull up disable 
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */
void csi_usb_dp_pull_up_disable(csp_usb_t *ptUsbBase);

/** \brief usb clk config
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \param[in] ptUsbCfg: pointer of usb parameter config structure
 *  \return none
 */  
void csi_usb_clk_config(csp_usb_t *ptUsbBase,csi_usb_config_t ptUsbCfg);


/** \brief usb dp pull up enable 
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */
void csi_usb_dp_pull_up_enable(csp_usb_t *ptUsbBase);

/** \brief usb ep0 stall
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_ep0_stall(csp_usb_t *ptUsbBase);

/** \brief usb fetch descriptor
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_fetch_descriptor(csp_usb_t *ptUsbBase);

/** \brief usb tx rx ready
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \param[in] byCnt: tx cnt
 *  \return none
 */ 
void csi_usb_ep0_tx_rx_ready(csp_usb_t *ptUsbBase,uint8_t byCnt);

#ifdef __cplusplus
}
#endif

#endif
