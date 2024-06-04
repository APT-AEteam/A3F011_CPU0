/***********************************************************************//** 
 * \file  usb.c
 * \brief  csi usb driver
 * \copyright Copyright (C) 2015-2021 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2023-1-30 <td>V0.0 <td>YYM    <td>initial
 * </table>
 * *********************************************************************
*/

#include "sys_clk.h"
#include "drv/usbd.h"
#include "drv/usbd_descriptor.h"
#include "drv/usbd_audio.h"
#include "drv/irq.h"
#include "drv/pin.h"
#include "drv/tick.h"

/* Private macro------------------------------------------------------*/
/* externs function---------------------------------------------------*/
/* externs variablesr-------------------------------------------------*/
/* Private variablesr-------------------------------------------------*/

csi_usb_setup_t        tUsbSetup;
csi_usb_ep0_ctrl_t     tUsbEp0Ctrl;
csi_usb_ep_fifo_adr_t  tUsbEpFifoAddr;
csi_usb_soft_ctrl_t    tUsbSoftCtrl;

/** \brief usb config init
 * 
 *  \param[in] none
 *  \return none
 */ 
void  csi_usb_config_init(void)
{
	memset(&tUsbSetup,0,sizeof(csi_usb_setup_t));	
	memset(&tUsbEp0Ctrl,0,sizeof(csi_usb_ep0_ctrl_t));	
	memset(&tUsbSoftCtrl,0,sizeof(csi_usb_soft_ctrl_t));	
	memset(&tUsbEpFifoAddr,0,sizeof(csi_usb_ep_fifo_adr_t));	
}

/** \brief power on init usb  
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \param[in] ptUsbCfg: pointer of usb parameter config structure
 *  \return error code \ref csi_error_t
 */  
csi_error_t  csi_usb_init(csp_usb_t *ptUsbBase,csi_usb_config_t ptUsbCfg)
{
    uint32_t i,fifo_set_val,i_temp;
	csi_error_t tRet;

	tRet = CSI_OK;
    csi_usb_config_init();
	csi_usb_clk_config(ptUsbBase,ptUsbCfg); 
	csp_usb_sram_addr(ptUsbBase, ptUsbCfg.wFifoBaseAddress);     
    tUsbEp0Ctrl.pbyEp0RxFifoBase = (uint8_t *)ptUsbCfg.wFifoBaseAddress;
	tUsbEpFifoAddr.pbyEpRxFifoStar[0] = (uint8_t *)ptUsbCfg.wFifoBaseAddress;

	csp_usb_set_ep(ptUsbBase,USB_EP_0,USB_EP_OUT);
	csp_usb_set_fifo(ptUsbBase,8);
    fifo_set_val = 0x08;    
    i_temp = fifo_set_val * 8;
	tUsbEpFifoAddr.pbyEpRxFifoStar[1] = (uint8_t *)(ptUsbCfg.wFifoBaseAddress + i_temp);
    for(i=1;i<7;i++)
    {   
		csp_usb_set_ep(ptUsbBase,i,USB_EP_OUT);
        if(ptUsbCfg.hwFifoOutLen[i] < 8)
        {
            ptUsbCfg.hwFifoOutLen[i] = 8;
        }
        fifo_set_val += ((ptUsbCfg.hwFifoOutLen[i] + 7)/8);
		csp_usb_set_fifo(ptUsbBase,fifo_set_val);
        i_temp = fifo_set_val * 8;
		if(i<6){
			tUsbEpFifoAddr.pbyEpRxFifoStar[i+1] = (uint8_t *)(ptUsbCfg.wFifoBaseAddress + i_temp);
		}
    }

    tUsbEp0Ctrl.pbyEp0TxFifoBase = (uint8_t *)(ptUsbCfg.wFifoBaseAddress + i_temp);
	tUsbEpFifoAddr.pbyEpTxFifoStar[0] = tUsbEp0Ctrl.pbyEp0TxFifoBase;
	csp_usb_set_ep(ptUsbBase,USB_EP_0,USB_EP_IN);   
    fifo_set_val += 0x08;
	csp_usb_set_fifo(ptUsbBase,fifo_set_val);
	i_temp = fifo_set_val * 8;
	tUsbEpFifoAddr.pbyEpTxFifoStar[1] = (uint8_t *)(ptUsbCfg.wFifoBaseAddress + i_temp);
    for(i=1;i<7;i++)
    {        
		csp_usb_set_ep(ptUsbBase,i,USB_EP_IN);
        if(ptUsbCfg.hwFifoInLen[i] < 8 )
        {
            ptUsbCfg.hwFifoInLen[i] = 8;
        }
        fifo_set_val += ((ptUsbCfg.hwFifoInLen[i] + 7)/8);
		csp_usb_set_fifo(ptUsbBase,fifo_set_val);
		i_temp = fifo_set_val * 8;
		if(i<6){
			tUsbEpFifoAddr.pbyEpTxFifoStar[i+1] = (uint8_t *)(ptUsbCfg.wFifoBaseAddress + i_temp);
		}
    }

	i_temp = fifo_set_val * 8;
	if(i_temp > 2048)
	{	// Fifo范围设置出错,超过2K byte
		tRet = CSI_ERROR;
	}
	
    tUsbEp0Ctrl.hwDescriptorWriteLength = 0x00;    
    tUsbEp0Ctrl.pbyWriteDescriptor = NULL;

	tUsbEp0Ctrl.bySpeakerVolValueH = 0x00;
	tUsbEp0Ctrl.bySpeakerVolValueL = ptUsbCfg.hwHpVolumeInit & 0x7f;

	tUsbEp0Ctrl.byMicVolValueH = 0x00;
	tUsbEp0Ctrl.byMicVolValueL = ptUsbCfg.hwMicVolumeInit & 0x7f;

	csp_usb_set_iso_tx0(ptUsbBase,USB_ISO_DIS,USB_ISO_EP_NONE);
	csp_usb_set_iso_rx0(ptUsbBase,USB_ISO_DIS,USB_ISO_EP_NONE);
	csp_usb_set_iso_tx1(ptUsbBase,USB_ISO_ENABLE,USB_ISO_EP_1);
	csp_usb_set_iso_rx0(ptUsbBase,USB_ISO_ENABLE,USB_ISO_EP_1);
	
	
	csp_usb_ep0rx_epie(ptUsbBase, ENABLE);
	csp_usb_ep0rx_epen(ptUsbBase, ENABLE);
	csp_usb_ep0rx_rxen(ptUsbBase);
	
	csp_usb_ep0tx_epie(ptUsbBase, ENABLE);
	csp_usb_ep0tx_epen(ptUsbBase, ENABLE);

    csp_usb_en(ptUsbBase);
	csp_usb_int_enable(ptUsbBase, USB_SOF_INT|USB_RST_INT|USB_SUS_INT|USB_SETUP_INT,ENABLE);
    ptUsbBase->EP_TX_IF =  0x00; 
    ptUsbBase->EP_RX_IF =  0x00; 
   
	csi_irq_enable((uint32_t *)ptUsbBase);
    return tRet;
}

/** \brief usb fetch descriptor
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_fetch_descriptor(csp_usb_t *ptUsbBase)
{
	uint16_t i,ui_write_len;
    uint8_t * p_ep0_tx_fifo;
  
    p_ep0_tx_fifo = tUsbEp0Ctrl.pbyEp0TxFifoBase;
    ui_write_len = tUsbEp0Ctrl.hwDescriptorWriteLength;
    if(ui_write_len > EP0_MAX_PACKET_SIZE)
    {
        ui_write_len = EP0_MAX_PACKET_SIZE ;
    }    
    for(i=0;i<ui_write_len;i++)
    {
        *p_ep0_tx_fifo ++ = *tUsbEp0Ctrl.pbyWriteDescriptor++;
    }
	csp_usb_ep0tx_cnt(ptUsbBase, ui_write_len);
    if(tUsbEp0Ctrl.hwDescriptorWriteLength >= ui_write_len)
    {
        tUsbEp0Ctrl.hwDescriptorWriteLength -= ui_write_len;
    }else{
        tUsbEp0Ctrl.hwDescriptorWriteLength = 0x00;
    }
	csp_usb_ep0tx_txen(ptUsbBase);
	csp_usb_ep0rx_rxen(ptUsbBase);
}

/** \brief usb ep0 stall
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_ep0_stall(csp_usb_t *ptUsbBase)
{
   csp_usb_ep0tx_stall(ptUsbBase);
   csp_usb_ep0rx_stall(ptUsbBase);
}

/** \brief usb tx rx ready
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \param[in] byCnt: tx cnt
 *  \return none
 */ 
void csi_usb_ep0_tx_rx_ready(csp_usb_t *ptUsbBase,uint8_t byCnt)
{
	csp_usb_ep0tx_cnt(ptUsbBase, byCnt);
	csp_usb_ep0tx_txen(ptUsbBase);
	csp_usb_ep0rx_rxen(ptUsbBase);
}

/** \brief usb read ep0 rx fifo
 * 
 *  \param[in] p_buf: pointer of fifo buf
 *  \param[in] len: fif0 read len
 *  \return none
 */ 
void csi_usb_read_ep0_rx_fifo(uint8_t *p_buf,uint8_t len)
{
    uint8_t  i;
    uint8_t * p_read_fifo;

    p_read_fifo = tUsbEp0Ctrl.pbyEp0RxFifoBase;
    for(i=0;i<len;i++)
    {
        *p_buf++ = *p_read_fifo++;
    }
}

/** \brief usb reset
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_reset(csp_usb_t *ptUsbBase)	//01
{
	csp_usb_clear_reset_flag(ptUsbBase);

	ptUsbBase->EP0TX_CTL |= 0xc0;
	ptUsbBase->EP0TX_CTL &= 0xc4;	    //  do not change toggle
	ptUsbBase->EP1TX_CTL = 0;
	ptUsbBase->EP2TX_CTL = 0;
	ptUsbBase->EP3TX_CTL = 0;
	ptUsbBase->EP4TX_CTL = 0;
	ptUsbBase->EP5TX_CTL = 0;
	ptUsbBase->EP6TX_CTL = 0;

	ptUsbBase->EP0RX_CTL |= 0xc0;
	ptUsbBase->EP0RX_CTL &= 0xc4;
	ptUsbBase->EP1RX_CTL = 0;
	ptUsbBase->EP2RX_CTL = 0;
	ptUsbBase->EP3RX_CTL = 0;
	ptUsbBase->EP4RX_CTL = 0;
	ptUsbBase->EP5RX_CTL = 0;
	ptUsbBase->EP6RX_CTL = 0;

	ptUsbBase->EP_RX_IF = 0;
	ptUsbBase->EP_TX_IF = 0;
	memset(&tUsbSoftCtrl,0,sizeof(csi_usb_soft_ctrl_t));	
}

/** \brief usb suspend
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_suspend(csp_usb_t *ptUsbBase)
{
	csp_usb_clear_suspend_flag(ptUsbBase);
	tUsbSoftCtrl.bySuspend = 0x00;    
}

/** \brief usb sof  
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_sof(csp_usb_t *ptUsbBase)	
{    
	csp_usb_sof_if(ptUsbBase);          //clear interrupt flag
	tUsbSoftCtrl.bySofIrq = 0x01;
}

/** \brief usb ep0 rx
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_ep0_rx(csp_usb_t *ptUsbBase)
{
    uint8_t  ep0_rx_buf[16];
    uint32_t ui_rx_length;
        
	csp_usb_ep_rxif(ptUsbBase, USB_EPTXIF0,DISABLE);  // clear interrupt flag

    ui_rx_length = csp_usb_ep0rx_get_cnt(ptUsbBase);
    if(ui_rx_length > 16)
    {
        ui_rx_length = 16;
    }
    csi_usb_read_ep0_rx_fifo(ep0_rx_buf,(uint8_t)ui_rx_length);

	if(tUsbEp0Ctrl.bySetReport)
	{
		tUsbEp0Ctrl.bySetReport = 0;
		if(tUsbEp0Ctrl.byReportId == 0x00)
		{
			if(tUsbEp0Ctrl.byReportInterfaceNumber == 0x04)
			{
				tUsbEp0Ctrl.byKeyLedStae = ep0_rx_buf[0];
			}
			else if(tUsbEp0Ctrl.byReportInterfaceNumber == 0x00)
			{
			}
		}
	}

	if(tUsbEp0Ctrl.bySetMicSampleFreq)
	{
		tUsbEp0Ctrl.bySetMicSampleFreq = 0;
		tUsbSoftCtrl.byMicSampleRateAdj = 1;
		tUsbEp0Ctrl.byMicSampleFreqL = ep0_rx_buf[0];
		tUsbEp0Ctrl.byMicSampleFreqM = ep0_rx_buf[1];
		tUsbEp0Ctrl.byMicSampleFreqH = ep0_rx_buf[2];	
	}
	else if(tUsbEp0Ctrl.bySetSpeakerSampleFreq)
	{
		tUsbEp0Ctrl.bySetSpeakerSampleFreq = 0;
		tUsbSoftCtrl.bySpeakerSampleRateAdj = 1;				
		tUsbEp0Ctrl.bySpeakerSampleFreqL = ep0_rx_buf[0];
		tUsbEp0Ctrl.bySpeakerSampleFreqM = ep0_rx_buf[1];
		tUsbEp0Ctrl.bySpeakerSampleFreqH = ep0_rx_buf[2];
	}
	else if(tUsbEp0Ctrl.bySetBassBoost)
	{
		tUsbEp0Ctrl.bySetBassBoost = 0;
		tUsbEp0Ctrl.byBassBoost = ep0_rx_buf[0];
	}
	else if(tUsbEp0Ctrl.bySetSelectorUnit)
	{
		tUsbEp0Ctrl.bySetSelectorUnit = 0;
		tUsbEp0Ctrl.bySelectorUnit = ep0_rx_buf[0];
	}
	else if(tUsbEp0Ctrl.bySetSpeakerVol)
	{
		tUsbEp0Ctrl.bySetSpeakerVol = 0;
		tUsbEp0Ctrl.bySpeakerVolValueL = ep0_rx_buf[0];
		tUsbEp0Ctrl.bySpeakerVolValueH = ep0_rx_buf[1];

		tUsbSoftCtrl.bySpeakerVolAdj = 1;
		tUsbSoftCtrl.hwUsbSetHpVolume = ((uint16_t)tUsbEp0Ctrl.bySpeakerVolValueH << 8)
												+ tUsbEp0Ctrl.bySpeakerVolValueL;
	}
	else if(tUsbEp0Ctrl.bySetSpeakerMute)
	{
		tUsbEp0Ctrl.bySetSpeakerMute = 0;
		tUsbEp0Ctrl.bySpeakerMuteValue = ep0_rx_buf[0];
	}
	else if(tUsbEp0Ctrl.bySetMicVol)
	{
		tUsbEp0Ctrl.bySetMicVol = 0;
		tUsbEp0Ctrl.byMicVolValueL = ep0_rx_buf[0];
		tUsbEp0Ctrl.byMicVolValueH = ep0_rx_buf[1];
		tUsbSoftCtrl.byMicVolAdj = 1;
		tUsbSoftCtrl.hwUsbSetMicVolume = ((uint16_t)tUsbEp0Ctrl.byMicVolValueH << 8)
												+ tUsbEp0Ctrl.byMicVolValueL;
	}
	else if(tUsbEp0Ctrl.bySetMicMute)
	{
		tUsbEp0Ctrl.bySetMicMute = 0;
		tUsbEp0Ctrl.byMicMuteValue = ep0_rx_buf[0];
	}
	csp_usb_ep0rx_rxen(ptUsbBase);
}

/** \brief usb ep1 rx interrupt function
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_ep1_rx(csp_usb_t *ptUsbBase)
{    
	csp_usb_ep_rxif(ptUsbBase, USB_EPTXIF1,DISABLE);

	tUsbSoftCtrl.byHpInterrupt = 1;
	tUsbSoftCtrl.hwHpFifoWrPtrBack = ptUsbBase->CFIFO3_WR_PTR;
	tUsbSoftCtrl.hwHpFifoWrCntBack = ptUsbBase->EP1RX_CNT;
}

/** \brief usb ep2 rx interrupt function
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_ep2_rx(csp_usb_t *ptUsbBase)
{    
	csp_usb_ep_rxif(ptUsbBase, USB_EPTXIF2,DISABLE);
	csp_usb_ep2rx_rxen(ptUsbBase);
}

/** \brief usb ep3 rx interrupt function
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_ep3_rx(csp_usb_t *ptUsbBase)
{    
	csp_usb_ep_rxif(ptUsbBase, USB_EPTXIF3,DISABLE);
	csp_usb_ep3rx_rxen(ptUsbBase);
}

/** \brief usb ep4 rx interrupt function
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_ep4_rx(csp_usb_t *ptUsbBase)	
{    
	csp_usb_ep_rxif(ptUsbBase, USB_EPTXIF4,DISABLE);
	tUsbSoftCtrl.byVendorReceiveOnePacket = 1;
}

/** \brief usb ep5 rx interrupt function
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_ep5_rx(csp_usb_t *ptUsbBase)	
{    
	csp_usb_ep_rxif(ptUsbBase, USB_EPTXIF5,DISABLE);
	csp_usb_ep5rx_rxen(ptUsbBase);
}

/** \brief usb ep6 rx interrupt function
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_ep6_rx(csp_usb_t *ptUsbBase)	
{    
	csp_usb_ep_rxif(ptUsbBase, USB_EPTXIF6,DISABLE);
	csp_usb_ep6rx_rxen(ptUsbBase);
}

/** \brief usb ep0 tx interrupt function
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_ep0_tx(csp_usb_t *ptUsbBase)
{
	csp_usb_ep_txif(ptUsbBase, USB_EPTXIF0,DISABLE);

	if(tUsbEp0Ctrl.bySetNewUsbAddress)
	{
		tUsbEp0Ctrl.bySetNewUsbAddress = 0;
		csp_usb_set_addr(ptUsbBase,tUsbEp0Ctrl.byNewUsbAddress);
	}
	csi_usb_fetch_descriptor(ptUsbBase);
}

/** \brief usb ep1 tx interrupt function
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_ep1_tx(csp_usb_t *ptUsbBase)
{
	csp_usb_ep_txif(ptUsbBase, USB_EPTXIF1,DISABLE);
	tUsbSoftCtrl.byMicInterrupt = 1;
	tUsbSoftCtrl.hwMicFifoRdCntBack = ptUsbBase->CFIFO2_RD_PTR;
}

/** \brief usb ep2 tx interrupt function
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_ep2_tx(csp_usb_t *ptUsbBase)
{
	csp_usb_ep_txif(ptUsbBase, USB_EPTXIF2,DISABLE);
}

/** \brief usb ep3 tx interrupt function
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_ep3_tx(csp_usb_t *ptUsbBase)
{
	csp_usb_ep_txif(ptUsbBase, USB_EPTXIF3,DISABLE);
}

/** \brief usb ep4 tx interrupt function
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_ep4_tx(csp_usb_t *ptUsbBase)
{
	csp_usb_ep_txif(ptUsbBase, USB_EPTXIF4,DISABLE);
}

/** \brief usb ep5 tx interrupt function
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_ep5_tx(csp_usb_t *ptUsbBase)
{
	csp_usb_ep_txif(ptUsbBase, USB_EPTXIF5,DISABLE);
}

/** \brief usb ep6 tx interrupt function
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_ep6_tx(csp_usb_t *ptUsbBase)
{
	csp_usb_ep_txif(ptUsbBase, USB_EPTXIF6,DISABLE);
}

/** \brief usb set device feature
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_set_device_feature(csp_usb_t *ptUsbBase)
{
	if(tUsbSetup.byBuf[2]==0x01)
	{
		tUsbEp0Ctrl.byDeviceFeature = 0x02;
		csi_usb_ep0_tx_rx_ready(ptUsbBase,0);
	}
	else
		csi_usb_ep0_stall(ptUsbBase);
}

/** \brief usb clear device feature
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_clear_device_feature(csp_usb_t *ptUsbBase)
{
	if(tUsbSetup.byBuf[2]==0x01)
	{
		tUsbEp0Ctrl.byDeviceFeature = 0x00;
		csi_usb_ep0_tx_rx_ready(ptUsbBase,0);
	}
	else
		csi_usb_ep0_stall(ptUsbBase);
}

/** \brief usb set device addr
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_set_device_address(csp_usb_t *ptUsbBase)
{
    tUsbEp0Ctrl.byNewUsbAddress = tUsbSetup.byBuf[2];
    tUsbEp0Ctrl.bySetNewUsbAddress = 1;
    csi_usb_ep0_tx_rx_ready(ptUsbBase,0);
}

/** \brief usb set device config
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_set_device_configuration(csp_usb_t *ptUsbBase)
{
	//ptUsbBase->USB_IE |= 0x04;		// USE suspend interrupt is enable
	csp_usb_int_enable(ptUsbBase, USB_SUS_INT,ENABLE);
	if(tUsbSetup.byBuf[2] == 0x01)
	{
		tUsbEp0Ctrl.byUsbConfig = 1;
		ptUsbBase->EP1TX_CTL = 0xc0;	//ep in1
		ptUsbBase->EP2TX_CTL = 0xc0;	//ep in2
		ptUsbBase->EP3TX_CTL = 0xc0;	//ep in3
		ptUsbBase->EP4TX_CTL = 0xc0;	//ep in4
		ptUsbBase->EP5TX_CTL = 0xc0;	//ep in5
		ptUsbBase->EP6TX_CTL = 0xc0;	//ep in6

		ptUsbBase->EP1RX_CTL = 0xc1;	//ep out1
		ptUsbBase->EP2RX_CTL = 0xc1;	//ep out2
		ptUsbBase->EP3RX_CTL = 0xc1;	//ep out3
		ptUsbBase->EP4RX_CTL = 0xc1;	//ep out4
		ptUsbBase->EP5RX_CTL = 0xc1;	//ep out5
		ptUsbBase->EP6RX_CTL = 0xc1;	//ep out6
		csi_usb_ep0_tx_rx_ready(ptUsbBase,0);
	}
	else if(tUsbSetup.byBuf[2] == 0x00)
	{
		tUsbEp0Ctrl.byUsbConfig = 0;
		ptUsbBase->EP1TX_CTL = 0xc0;	//ep in1
		ptUsbBase->EP2TX_CTL = 0x00;	//ep in2
		ptUsbBase->EP3TX_CTL = 0x00;	//ep in3
		ptUsbBase->EP4TX_CTL = 0x00;	//ep in4
		ptUsbBase->EP5TX_CTL = 0x00;	//ep in5
		ptUsbBase->EP6TX_CTL = 0x00;	//ep in6

		ptUsbBase->EP1RX_CTL = 0x00;	//ep out1
		ptUsbBase->EP2RX_CTL = 0x00;	//ep out2
		ptUsbBase->EP3RX_CTL = 0x00;	//ep out3
		ptUsbBase->EP4RX_CTL = 0x00;	//ep out4
		ptUsbBase->EP5RX_CTL = 0x00;	//ep out5
		ptUsbBase->EP6RX_CTL = 0x00;	//ep out6
		csi_usb_ep0_tx_rx_ready(ptUsbBase,0);
	}
	else
		csi_usb_ep0_stall(ptUsbBase);
}

/** \brief usb set interface
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_set_interface(csp_usb_t *ptUsbBase)
{
    if(tUsbSetup.b.byIndexL < 6)
    {
        tUsbEp0Ctrl.byInterface[tUsbSetup.b.byIndexL] = tUsbSetup.byBuf[2];
        csi_usb_ep0_tx_rx_ready(ptUsbBase,0);
    }else{
        csi_usb_ep0_stall(ptUsbBase);
    }
}

/** \brief usb clear endpoint feature
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_clear_endpoint_feature(csp_usb_t *ptUsbBase)
{	
	if(tUsbSetup.byBuf[2] == 0x00)
	{
		switch(tUsbSetup.b.byIndexL)
		{
		case 0x00:
			break;
		case 0x80:
			break;
		case 0x81:
			csp_usb_ep1tx_clear_stall(ptUsbBase);
			tUsbEp0Ctrl.byEpTxFeature[0] = 0;
			break;
		case 0x82:
			csp_usb_ep2tx_clear_stall(ptUsbBase);
			tUsbEp0Ctrl.byEpTxFeature[1] = 0;
			break;
		case 0x83:
			csp_usb_ep3tx_clear_stall(ptUsbBase);
			tUsbEp0Ctrl.byEpTxFeature[2] = 0;
			break;
		case 0x84:
			csp_usb_ep4tx_clear_stall(ptUsbBase);
			tUsbEp0Ctrl.byEpTxFeature[3] = 0;
			break;
		case 0x85:
			csp_usb_ep5tx_clear_stall(ptUsbBase);
			tUsbEp0Ctrl.byEpTxFeature[4] = 0;
			break;
		case 0x86:
			csp_usb_ep6tx_clear_stall(ptUsbBase);
			tUsbEp0Ctrl.byEpTxFeature[5] = 0;
			break;
		case 0x01:
			csp_usb_ep1rx_clear_stall(ptUsbBase);
			tUsbEp0Ctrl.byEpRxFeature[0] = 0;
			break;
		case 0x02:
			csp_usb_ep2rx_clear_stall(ptUsbBase);
			tUsbEp0Ctrl.byEpRxFeature[1] = 0;
			break;
		case 0x03:
			csp_usb_ep3rx_clear_stall(ptUsbBase);
			tUsbEp0Ctrl.byEpRxFeature[2] = 0;
			break;
		case 0x04:
			csp_usb_ep4rx_clear_stall(ptUsbBase);
			tUsbEp0Ctrl.byEpRxFeature[3] = 0;
			break;
		case 0x05:
			csp_usb_ep5rx_clear_stall(ptUsbBase);
			tUsbEp0Ctrl.byEpRxFeature[4] = 0;
			break;
		case 0x06:
			csp_usb_ep6rx_clear_stall(ptUsbBase);
			tUsbEp0Ctrl.byEpRxFeature[5] = 0;
			break;
		default:
			csi_usb_ep0_stall(ptUsbBase);
			return;
		}
		csi_usb_ep0_tx_rx_ready(ptUsbBase,0);
	}
}

/** \brief usb set endpoint feature
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_set_endpoint_feature(csp_usb_t *ptUsbBase)
{
	if(tUsbSetup.byBuf[2] == 0x00)
	{
		switch(tUsbSetup.b.byIndexL)
		{
		case 0x00:
			break;
		case 0x80:
			break;
		case 0x81:
			csp_usb_ep1tx_stall(ptUsbBase);
			tUsbEp0Ctrl.byEpTxFeature[0] = 1;
			break;
		case 0x82:
			csp_usb_ep2tx_stall(ptUsbBase);
			tUsbEp0Ctrl.byEpTxFeature[1] = 1;
			break;
		case 0x83:
			csp_usb_ep3tx_stall(ptUsbBase);
			tUsbEp0Ctrl.byEpTxFeature[2] = 1;
			break;
		case 0x84:
			csp_usb_ep4tx_stall(ptUsbBase);
			tUsbEp0Ctrl.byEpTxFeature[3] = 1;
			break;
		case 0x85:
			csp_usb_ep5tx_stall(ptUsbBase);
			tUsbEp0Ctrl.byEpTxFeature[4] = 1;
			break;
		case 0x86:
			csp_usb_ep6tx_stall(ptUsbBase);
			tUsbEp0Ctrl.byEpTxFeature[5] = 1;
			break;
		case 0x01:
			csp_usb_ep1rx_stall(ptUsbBase);
			tUsbEp0Ctrl.byEpRxFeature[0] = 1;
			break;
		case 0x02:
			csp_usb_ep2rx_stall(ptUsbBase);
			tUsbEp0Ctrl.byEpRxFeature[1] = 1;
			break;
		case 0x03:
			csp_usb_ep3rx_stall(ptUsbBase);
			tUsbEp0Ctrl.byEpRxFeature[2] = 1;
			break;
		case 0x04:
			csp_usb_ep4rx_stall(ptUsbBase);
			tUsbEp0Ctrl.byEpRxFeature[3] = 1;
			break;
		case 0x05:
			csp_usb_ep5rx_stall(ptUsbBase);
			tUsbEp0Ctrl.byEpRxFeature[4] = 1;
			break;
		case 0x06:
			csp_usb_ep6rx_stall(ptUsbBase);
			tUsbEp0Ctrl.byEpRxFeature[5] = 1;
			break;
		default:
			csi_usb_ep0_stall(ptUsbBase);
			return;
		}
		csi_usb_ep0_tx_rx_ready(ptUsbBase,0);
	}
}

/** \brief usb set idle
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_set_idle(csp_usb_t *ptUsbBase)
{
	if(tUsbSetup.b.byIndexL == 3)			// B[4]
	{		// interface
		if(tUsbSetup.b.byValueL == 0x00)		// B[2]
		{	// no used report id
			tUsbEp0Ctrl.byIdleTime[0] = tUsbSetup.b.byValueH;
			csi_usb_ep0_tx_rx_ready(ptUsbBase,0);
		}else if(tUsbSetup.b.byValueL == 0x02)		// B[2]
		{	// report id
			tUsbEp0Ctrl.byIdleTime[1] = tUsbSetup.b.byValueH;
			csi_usb_ep0_tx_rx_ready(ptUsbBase,0);
		}else{
			csi_usb_ep0_stall(ptUsbBase);
		}
	}else if(tUsbSetup.b.byIndexL == 4)		// B[4]
	{
		if(tUsbSetup.b.byValueL == 0x00)		// B[2]
		{	// no used report id
			tUsbEp0Ctrl.byIdleTime[2] = tUsbSetup.b.byValueH;
			csi_usb_ep0_tx_rx_ready(ptUsbBase,0);
		}else if(tUsbSetup.b.byValueL == 0x23)		// B[2]
		{	// report id
			tUsbEp0Ctrl.byIdleTime[3] = tUsbSetup.b.byValueH;
			csi_usb_ep0_tx_rx_ready(ptUsbBase,0);
		}else if(tUsbSetup.b.byValueL == 0x24)		// B[2]
		{	// report id
			tUsbEp0Ctrl.byIdleTime[4] = tUsbSetup.b.byValueH;
			csi_usb_ep0_tx_rx_ready(ptUsbBase,0);
		}else{
			csi_usb_ep0_stall(ptUsbBase);
		}
	}else{
		csi_usb_ep0_stall(ptUsbBase);
	}
}

/** \brief usb set protocol
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_set_protocol(csp_usb_t *ptUsbBase)
{
    if(tUsbSetup.b.byIndexL < 6)
    {
        tUsbEp0Ctrl.byProtocolType[tUsbSetup.b.byIndexL] = tUsbSetup.b.byValueL;
        csi_usb_ep0_tx_rx_ready(ptUsbBase,0);
    }else{
        csi_usb_ep0_stall(ptUsbBase);
    }
}

/** \brief usb get device status
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_get_device_status(csp_usb_t *ptUsbBase)
{
    uint8_t * p_ep0_tx_fifo;
    p_ep0_tx_fifo = tUsbEp0Ctrl.pbyEp0TxFifoBase;

    *p_ep0_tx_fifo++ = tUsbEp0Ctrl.byDeviceFeature;
    *p_ep0_tx_fifo++ = 0x00;
	csi_usb_ep0_tx_rx_ready(ptUsbBase,2);
}

/** \brief usb get device config
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_get_device_configuration(csp_usb_t *ptUsbBase)
{
 	uint8_t * p_ep0_tx_fifo;
    p_ep0_tx_fifo = tUsbEp0Ctrl.pbyEp0TxFifoBase;

	if(tUsbEp0Ctrl.byUsbConfig)
		*p_ep0_tx_fifo++ = 0x01;
	else
		*p_ep0_tx_fifo++ = 0x00;
	csi_usb_ep0_tx_rx_ready(ptUsbBase,1);
}

/** \brief usb get interface status
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_get_interface_status(csp_usb_t *ptUsbBase)
{
	uint8_t * p_ep0_tx_fifo;
    p_ep0_tx_fifo = tUsbEp0Ctrl.pbyEp0TxFifoBase; 

	*p_ep0_tx_fifo++ = 0x00;
	*p_ep0_tx_fifo++ = 0x00;
	csi_usb_ep0_tx_rx_ready(ptUsbBase,2);
}

/** \brief usb get intetface
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_get_interface(csp_usb_t *ptUsbBase)
{	
	uint8_t * p_ep0_tx_fifo;
	p_ep0_tx_fifo = tUsbEp0Ctrl.pbyEp0TxFifoBase; 

	switch(tUsbSetup.b.byIndexL)
	{
		case 0x00:
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byInterface[0];
			break;
		case 0x01:
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byInterface[1];
			break;
		case 0x02:
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byInterface[2];
			break;
		case 0x03:
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byInterface[3];
			break;
		case 0x04:
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byInterface[3];
			break;
		case 0x05:
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byInterface[3];
			break;
		default:
			csi_usb_ep0_stall(ptUsbBase);
			return;
	}
	csi_usb_ep0_tx_rx_ready(ptUsbBase,1);
}

/** \brief usb get end point status 
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_get_end_point_status(csp_usb_t *ptUsbBase)
{
	uint8_t * p_ep0_tx_fifo;
	p_ep0_tx_fifo = tUsbEp0Ctrl.pbyEp0TxFifoBase; 

	switch(tUsbSetup.b.byIndexL)
	{
		case 0x00:
			*p_ep0_tx_fifo++ = 0x00;
			*p_ep0_tx_fifo++ = 0x00;
			break;
		case 0x80:
			*p_ep0_tx_fifo++ = 0x00;
			*p_ep0_tx_fifo++ = 0x00;
			break;
		case 0x81:
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byEpTxFeature[0];
			*p_ep0_tx_fifo++ = 0x00;
			break;
		case 0x82:
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byEpTxFeature[1];
			*p_ep0_tx_fifo++ = 0x00;
			break;
		case 0x83:
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byEpTxFeature[2];
			*p_ep0_tx_fifo++ = 0x00;
			break;
		case 0x84:
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byEpTxFeature[3];
			*p_ep0_tx_fifo++ = 0x00;
			break;
		case 0x85:
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byEpTxFeature[4];
			*p_ep0_tx_fifo++ = 0x00;
			break;
		case 0x86:
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byEpTxFeature[5];
			*p_ep0_tx_fifo++ = 0x00;
			break;
		case 0x01:
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byEpRxFeature[0];
			*p_ep0_tx_fifo++ = 0x00;
			break;
		case 0x02:
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byEpRxFeature[1];
			*p_ep0_tx_fifo++ = 0x00;
			break;
		case 0x03:
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byEpRxFeature[2];
			*p_ep0_tx_fifo++ = 0x00;
			break;
		case 0x04:
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byEpRxFeature[3];
			*p_ep0_tx_fifo++ = 0x00;
			break;
		case 0x05:
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byEpRxFeature[4];
			*p_ep0_tx_fifo++ = 0x00;
			break;
		case 0x06:
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byEpRxFeature[5];
			*p_ep0_tx_fifo++ = 0x00;
			break;
		default:
			csi_usb_ep0_stall(ptUsbBase);
			return;
	}
	csi_usb_ep0_tx_rx_ready(ptUsbBase,2);
}

/** \brief usb get idle
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_get_idle(csp_usb_t *ptUsbBase)
{
	uint8_t * p_ep0_tx_fifo;
	p_ep0_tx_fifo = tUsbEp0Ctrl.pbyEp0TxFifoBase; 

	if(tUsbSetup.b.byIndexL == 3)			// B[4]
	{		// interface
		if(tUsbSetup.b.byValueL == 0x00)		// B[2]
		{	// no used report id
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byIdleTime[0];
			csi_usb_ep0_tx_rx_ready(ptUsbBase,1);
		}else if(tUsbSetup.b.byValueL == 0x02)		// B[2]
		{	// report id
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byIdleTime[1];
			csi_usb_ep0_tx_rx_ready(ptUsbBase,1);
		}else{
			csi_usb_ep0_stall(ptUsbBase);
		}
	}else if(tUsbSetup.b.byIndexL == 4)		// B[4]
	{
		if(tUsbSetup.b.byValueL == 0x00)		// B[2]
		{	// no used report id
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byIdleTime[2];
			csi_usb_ep0_tx_rx_ready(ptUsbBase,1);
		}else if(tUsbSetup.b.byValueL == 0x23)		// B[2]
		{	// report id
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byIdleTime[3];
			csi_usb_ep0_tx_rx_ready(ptUsbBase,1);
		}else if(tUsbSetup.b.byValueL == 0x24)		// B[2]
		{	// report id
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byIdleTime[4];
			csi_usb_ep0_tx_rx_ready(ptUsbBase,1);
		}else{
			csi_usb_ep0_stall(ptUsbBase);
		}
	}else{
		csi_usb_ep0_stall(ptUsbBase);
	}
	// if(tUsbSetup.b.wIndexL < 6)
	// {
	// 	*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byIdleTime[tUsbSetup.b.wIndexL];
	// 	 usb_ep0_tx_rx_ready(1);
	// }else{
	// 	usb_ep0_stall();
	// }
}

/** \brief usb get protocol
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
void csi_usb_get_protocol(csp_usb_t *ptUsbBase)
{
	uint8_t * p_ep0_tx_fifo;
	p_ep0_tx_fifo = tUsbEp0Ctrl.pbyEp0TxFifoBase; 

	if(tUsbSetup.b.byIndexL < 6)
	{
		*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byProtocolType[tUsbSetup.b.byIndexL];
		 csi_usb_ep0_tx_rx_ready(ptUsbBase,1);
	}else{
		csi_usb_ep0_stall(ptUsbBase);
	}
}

/** \brief usb set end point cur
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */ 
// 主机设置采样率
void csi_usb_set_endpoint_cur(csp_usb_t *ptUsbBase)
{
	if(tUsbSetup.b.byValueH == 0x01)
	{
		if(tUsbSetup.b.byIndexL == 0x01)  // byte[4]
		{
			tUsbEp0Ctrl.bySetSpeakerSampleFreq = 1;
		}
		else if(tUsbSetup.b.byIndexL == 0x81){
			tUsbEp0Ctrl.bySetMicSampleFreq = 1;
        }
		csi_usb_ep0_tx_rx_ready(ptUsbBase,0);
	}
	else
		csi_usb_ep0_stall(ptUsbBase);
}

/** \brief usb get endpoint cur
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */
void csi_usb_get_endpoint_cur(csp_usb_t *ptUsbBase)
{
	uint8_t * p_ep0_tx_fifo = tUsbEp0Ctrl.pbyEp0TxFifoBase; 
	if(tUsbSetup.b.byValueH == 0x01)
	{
		if(tUsbSetup.b.byIndexL ==0x81)
		{
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byMicSampleFreqL;
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byMicSampleFreqM;
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.byMicSampleFreqH;
			csi_usb_ep0_tx_rx_ready(ptUsbBase,3);
		}
		else if(tUsbSetup.b.byIndexL == 0x01)
		{
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.bySpeakerSampleFreqL;
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.bySpeakerSampleFreqM;
			*p_ep0_tx_fifo++ = tUsbEp0Ctrl.bySpeakerSampleFreqH;
			csi_usb_ep0_tx_rx_ready(ptUsbBase,3);
		}else
			csi_usb_ep0_stall(ptUsbBase);
	}
	else
		csi_usb_ep0_stall(ptUsbBase);
}

/** \brief usb set report
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */
void csi_usb_set_report(csp_usb_t *ptUsbBase)
{
	// uint8_t report_type = tUsbSetup.b.wValueH;
	uint8_t report_id = tUsbSetup.b.byValueL;
	uint8_t report_interface_number = tUsbSetup.b.byIndexL;
	uint16_t  ui_length = (uint16_t)tUsbSetup.b.byLengthL + ((uint16_t)tUsbSetup.b.byLengthH<<8);
	
	switch(tUsbSetup.b.byValueH)
	{
		case 0x01:		// input report
			break;
		case 0x02:		// output report
			if((report_id == 0x01) && (report_interface_number == 0x02))
			{  // 21 09 01 02 02 00 02 00
			// CapsLock Led Out
				tUsbEp0Ctrl.byKeyLedStae = 0x01;
			}

			// 21 09 00 02 02 00 04 00 : volume
			if((tUsbSetup.b.byIndexL == 0x02) && (tUsbSetup.b.byLengthL == 0x04))
			{  // wIndexL:endpoint

			}
			break;
		case 0x03:		// feature report
			break;
		default:
			csi_usb_ep0_stall(ptUsbBase);
			return;
	}
	tUsbEp0Ctrl.bySetReport = 1;
	csi_usb_ep0_tx_rx_ready(ptUsbBase,0);
	csp_usb_ep0rx_cnt(ptUsbBase, ui_length);
}

/** \brief usb set television one
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */
void csi_usb_set_television_one(csp_usb_t *ptUsbBase)
{
	// uint8_t report_type = tUsbSetup.b.byValueH;
	// uint8_t report_id = tUsbSetup.b.byValueL;
	// uint8_t report_interface_number = tUsbSetup.b.wIndexL;
	uint16_t  ui_length = (uint16_t)tUsbSetup.b.byLengthL + ((uint16_t)tUsbSetup.b.byLengthH<<8);
	
	switch(tUsbSetup.b.byValueH)
	{
		case 0x01:		// input report
			break;
		case 0x02:		// output report
			break;
		case 0x03:		// feature report
			break;
		default:
			csi_usb_ep0_stall(ptUsbBase);
			return;
	}
	tUsbEp0Ctrl.bySetReport = 1;
	csi_usb_ep0_tx_rx_ready(ptUsbBase,0);
	csp_usb_ep0rx_cnt(ptUsbBase, ui_length);
}


/** \brief usb setup handler
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */
void csi_usb_setup_handler(csp_usb_t *ptUsbBase)
{
	uint8_t i;
	// uint16_t  ui_length ;
	uint8_t * p_ep0_rx_fifo= tUsbEp0Ctrl.pbyEp0RxFifoBase; 
	
	csp_usb_clear_setup_flag(ptUsbBase);
	tUsbEp0Ctrl.bySetReport = 0;
	for(i=0;i<8;i++)
	{
		tUsbSetup.byBuf[i] = *p_ep0_rx_fifo ++;
	}
	// ui_length = (uint16_t)tUsbSetup.b.wLengthL + ((uint16_t)tUsbSetup.b.wLengthH<<8);

	switch(tUsbSetup.b.byRequestType)
	{
		case 0x00:
			switch(tUsbSetup.b.byRequest)
			{
				case USB_SET_FEATURE:
					csi_usb_set_device_feature(ptUsbBase);
					break;
				case USB_CLR_FEATURE:
					csi_usb_clear_device_feature(ptUsbBase);
					break;
				case USB_SET_ADDRESS:
					csi_usb_set_device_address(ptUsbBase);
					// fTvSetAddr = 1;
					// UsbConfFlag |= USB_ENUM_STAU_SETADDR;
					break;
				//case USB_SET_DESCRIPTOR:
					//SetDeviceDescriptor();
					//break;
				case USB_SET_CONFIG:
					csi_usb_set_device_configuration(ptUsbBase);
					break;
				default:
					csi_usb_ep0_stall(ptUsbBase);
					break;
			}
			break;
		case 0x01:
			switch(tUsbSetup.b.byRequest)
			{
				case USB_SET_INTERFACE:
					csi_usb_set_interface(ptUsbBase);
					// UsbConfFlag |=  USB_ENUM_STAU_SET_INTERFACE;
					break;
				default:
					csi_usb_ep0_stall(ptUsbBase);
					break;
			}
			break;
		case 0x02:
			switch(tUsbSetup.b.byRequest)
			{
				case USB_CLR_FEATURE:
					csi_usb_clear_endpoint_feature(ptUsbBase);
					break;
				case USB_SET_FEATURE:
					csi_usb_set_endpoint_feature(ptUsbBase);
					break;
				default:
					csi_usb_ep0_stall(ptUsbBase);
					break;
			}
			break;
		case 0x21:
			switch(tUsbSetup.b.byRequest)
			{
				case USB_SET_IDLE:
					csi_usb_set_idle(ptUsbBase);
					break;
				case USB_SET_PROTOCOL:
					csi_usb_set_protocol(ptUsbBase);
					break;
				case USB_SET_CUR:
					csi_usb_set_interface_cur(ptUsbBase);
					break;
				case 0x09:		// set report
					csi_usb_set_report(ptUsbBase);
					break;
				case 0x04:
					csi_usb_set_television_one(ptUsbBase);
					break;
				default:
					csi_usb_ep0_stall(ptUsbBase);
					break;
			}
			break;
	case 0x22:
		switch(tUsbSetup.b.byRequest)
		{
		case USB_SET_CUR:
			csi_usb_set_endpoint_cur(ptUsbBase);
			break;
		default:
			csi_usb_ep0_stall(ptUsbBase);
			break;
		}
		break;
	case 0x80:
		switch(tUsbSetup.b.byRequest)
		{
		case USB_GET_STATUS:
			csi_usb_get_device_status(ptUsbBase);
			break;
		case USB_GET_DESCRIPTOR:
			csi_usb_get_device_descriptor(ptUsbBase);			
			break;
		case USB_GET_CONFIG:
			csi_usb_get_device_configuration(ptUsbBase);
			break;
		default:
			csi_usb_ep0_stall(ptUsbBase);
			break;
		}
		break;
	case 0x81:
		switch(tUsbSetup.b.byRequest)
		{
		case USB_GET_STATUS:
			csi_usb_get_interface_status(ptUsbBase);
			break;
		case USB_GET_DESCRIPTOR:
			csi_usb_get_hid_descriptor(ptUsbBase);
			// UsbConfFlag |=  USB_ENUM_STAU_GET_HID_CLASS;

			// num = 0x00;
			// if(UsbConfFlag & 0x01){ num ++; }
			// if(UsbConfFlag & 0x02){ num ++; }
			// if(UsbConfFlag & 0x04){ num ++; }
			// if(UsbConfFlag & 0x08){ num ++; }
			// if(UsbConfFlag & 0x10){ num ++; }
			// if(UsbConfFlag & 0x20){ num ++; }
			// if(UsbConfFlag & 0x40){ num ++; }
			// if(num >= 4)
			// {			// USB ö�ٳɹ�
			// 	fUsbConfigOk = 1;
			// }
			break;
		case USB_GET_INTERFACE:
			csi_usb_get_interface(ptUsbBase);
			break;
		default:
			csi_usb_ep0_stall(ptUsbBase);
			break;
		}
		break;
		case 0x82:
			switch(tUsbSetup.b.byRequest)
			{
				case USB_GET_STATUS:
					csi_usb_get_end_point_status(ptUsbBase);
					break;
				default:
					csi_usb_ep0_stall(ptUsbBase);
					break;
			}
			break;
		case 0xA1:
			switch(tUsbSetup.b.byRequest)
			{
				case USB_GET_CLASS:
					csi_usb_get_report(ptUsbBase);
				break;
				case USB_GET_IDLE:
					csi_usb_get_idle(ptUsbBase);
					break;
				case USB_GET_PROTOCOL:
					csi_usb_get_protocol(ptUsbBase);
					break;
				case USB_GET_CUR:
					csi_usb_get_interface_cur(ptUsbBase);
					break;
				case USB_GET_MIN:
					csi_usb_get_interface_min(ptUsbBase);
					break;
				case USB_GET_MAX:
					csi_usb_get_interface_max(ptUsbBase);
					break;
				case USB_GET_RES:
					csi_usb_get_interface_res(ptUsbBase);
					break;
				default:
					csi_usb_ep0_stall(ptUsbBase);
					break;
			}
			break;
		case 0xA2:
			switch(tUsbSetup.b.byRequest)
			{
				case USB_GET_CUR:
					csi_usb_get_endpoint_cur(ptUsbBase);
					break;
				default:
					csi_usb_ep0_stall(ptUsbBase);
					break;
			}
			break;
		default:
			csi_usb_ep0_stall(ptUsbBase);
			break;
	}
}

/** \brief usb irq handler
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \param[in] idx: id num
 *  \return none
 */
uint32_t  wUsbDeviceStatus[20] = {0};
void usb_irqhandler(csp_usb_t *ptUsbBase,int32_t idx)
{
	switch(csp_usb_get_isr(ptUsbBase))
	{
		case 1:
			csi_usb_reset(ptUsbBase);
			wUsbDeviceStatus[1]++;
	//		 hal_SendDataPullUp();
			break;
		case 2:
			csi_usb_suspend(ptUsbBase);
			wUsbDeviceStatus[2]++;
			break;
		case 3:
			csi_usb_sof(ptUsbBase);
			tUsbSoftCtrl.byUsbActiv = 1;
			wUsbDeviceStatus[3]++;
			break;
		case 4:
			csi_pin_set_high(PA3);	
			csi_usb_setup_handler(ptUsbBase);
			tUsbSoftCtrl.byUsbActiv = 1;
			wUsbDeviceStatus[4]++;
			csi_pin_set_low(PA3);	
			break;
		case 5:
			csi_usb_ep0_rx(ptUsbBase);
			tUsbSoftCtrl.byUsbActiv = 1;
			wUsbDeviceStatus[5]++;
			break;
		case 6:
			csi_usb_ep1_rx(ptUsbBase);
			tUsbSoftCtrl.byUsbActiv = 1;
			wUsbDeviceStatus[6]++;
			break;
		case 7:
			csi_usb_ep2_rx(ptUsbBase);
			tUsbSoftCtrl.byUsbActiv = 1;
			wUsbDeviceStatus[7]++;
			break;
		case 8:
			csi_usb_ep3_rx(ptUsbBase);
			tUsbSoftCtrl.byUsbActiv = 1;
			wUsbDeviceStatus[8]++;
			break;
		case 9:
			csi_usb_ep4_rx(ptUsbBase);
			tUsbSoftCtrl.byUsbActiv = 1;
			wUsbDeviceStatus[9]++;
			break;
		case 10:
			csi_usb_ep5_rx(ptUsbBase);
			tUsbSoftCtrl.byUsbActiv = 1;
			wUsbDeviceStatus[10]++;
			break;
		case 11:
			csi_usb_ep6_rx(ptUsbBase);
			tUsbSoftCtrl.byUsbActiv = 1;
			break;
		case 13:
			csi_usb_ep0_tx(ptUsbBase);
			tUsbSoftCtrl.byUsbActiv = 1;
			wUsbDeviceStatus[13]++;
			break;
		case 14:
			csi_usb_ep1_tx(ptUsbBase);
			tUsbSoftCtrl.byUsbActiv = 1;
			wUsbDeviceStatus[14]++;
			break;
		case 15:
			csi_usb_ep2_tx(ptUsbBase);
			tUsbSoftCtrl.byUsbActiv = 1;
			wUsbDeviceStatus[15]++;
			break;
		case 16:
			csi_usb_ep3_tx(ptUsbBase);
			tUsbSoftCtrl.byUsbActiv = 1;
			wUsbDeviceStatus[16]++;
			break;
		case 17:
			csi_usb_ep4_tx(ptUsbBase);
			tUsbSoftCtrl.byUsbActiv = 1;
			wUsbDeviceStatus[17]++;
			break;
		case 18:
			csi_usb_ep5_tx(ptUsbBase);
			tUsbSoftCtrl.byUsbActiv = 1;
			wUsbDeviceStatus[18]++;
			break;
		case 19:
			csi_usb_ep6_tx(ptUsbBase);
			tUsbSoftCtrl.byUsbActiv = 1;
			wUsbDeviceStatus[19]++;
			break;
		default:
			break;
	}
}

/** \brief usb dp pull up enable 
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */
void csi_usb_dp_pull_up_enable(csp_usb_t *ptUsbBase)
{
	// Bit[6]:DPPU   Bit[7]:DPPU_LO
	csp_usb_set_pup(ptUsbBase);
	csp_usb_set_pullup_lo(ptUsbBase);
	tUsbSoftCtrl.hwUsbEnumStep = 0x00;
}

/** \brief usb dp pull up disable 
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return none
 */
void csi_usb_dp_pull_up_disable(csp_usb_t *ptUsbBase)
{
	ptUsbBase->USB_CTL &= 0xffffff3f;    // Bit[6]:DPPU   Bit[7]:DPPU_LO
	tUsbSoftCtrl.hwUsbEnumStep = 0x00;
}

/** \brief usb clk config
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \param[in] ptUsbCfg: pointer of usb parameter config structure
 *  \return none
 */  
void csi_usb_clk_config(csp_usb_t *ptUsbBase,csi_usb_config_t ptUsbCfg)
{
	
#if 0	
	
	uint32_t reg = REG_PMU_INSTANCE->SRC_CLKMD;

	reg |= PMU_SRC_CLKMD_USBPHY_EN;
	REG_PMU_INSTANCE->SRC_CLKMD = reg;   // Usb Phy clock enable
    REG_PMU_INSTANCE->MODE_CHG_EN = PMU_MODE_CHG_EN_SRC_CLK_CHG_EN;
	while(1){
		reg = REG_PMU_INSTANCE->MODE_CHG_EN;
		reg &= PMU_MODE_CHG_EN_SRC_CLK_CHG_EN;
		if(reg == 0){
			break;
		}
	}
	reg = REG_PMU_INSTANCE->IP_CTRL;
	// bit[2] = 0	normal opreation
	reg &= 0xfffffffb;
	REG_PMU_INSTANCE->IP_CTRL = reg ;
	// bit[2..3] = 0  USBPHY RST
	REG_PMU_INSTANCE->IP_CTRL = reg & 0xfffffff3; 
	reg |= 0x08;			// not RST
	REG_PMU_INSTANCE->IP_CTRL = reg ;

	reg &= 0xfffffffc;
	if(ptUsbCfg.eUsbPhyMode == USB_PHY_INTERNAL_OSC)
	{
		reg |= 0x02;			// 10: internal oscillator  11:external
	}else{
		reg |= 0x03;
	}
	REG_PMU_INSTANCE->IP_CTRL = reg ;
	while(1)
	{
		reg = REG_PMU_INSTANCE->IP_CTRL;
		if(reg & 0x100){
			// USBPHY PLL LOCK
			break;
		}
	}
#endif	
}






