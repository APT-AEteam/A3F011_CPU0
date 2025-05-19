/***********************************************************************//** 
 * \file  usb_audio.c
 * \brief  csi usb audio driver
 * \copyright Copyright (C) 2015-2021 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2023-1-30 <td>V0.0 <td>YYM    <td>initial
 * </table>
 * *********************************************************************
*/

#include "sys_clk.h"
#include "usbd_core.h"
#include "usbd_hid.h"

extern csi_usb_ep0_ctrl_t     tUsbEp0Ctrl;
extern csi_usb_soft_ctrl_t    tUsbSoftCtrl;
extern csi_usb_ep_fifo_adr_t  tUsbEpFifoAddr;
extern volatile char byHidStringProdcut[58];

/** \brief USB start enum  
 * 
 *  \param[in] none
 *  \return error code \ref csi_error_t
 */ 
csi_error_t  csi_usb_start_enum(void)
{
	uint32_t temp;
	temp = USB_ENUM_STEP_DEVICE_DESC | USB_ENUM_STEP_CONFIG_DESC;
	if(tUsbSoftCtrl.hwUsbEnumStep & temp)
	{
		return CSI_OK;
	}else 
	{
		return CSI_ERROR;
	}
}

/** \brief USB enum complete
 * 
 *  \param[in] none
 *  \return error code \ref csi_error_t
 */ 
csi_error_t  csi_usb_enum_complete(void)
{
	uint32_t temp;
	temp = USB_ENUM_STEP_DEVICE_DESC
				| USB_ENUM_STEP_CONFIG_DESC
				| USB_ENUM_STEP_LANGUAGE_ID
				//| USB_ENUM_STEP_INF3_REPORT
				|USB_ENUM_STEP_HIDREPORT_DESC
				|USB_ENUM_STEP_SERIAL_STRING
				;
	if((tUsbSoftCtrl.hwUsbEnumStep & temp) == temp)
	{	// DEVICE_DESC,CONFIG_DESC,LANGUAGE_ID,INF0_REPORT
		return CSI_OK;
	}else
	{
		return CSI_ERROR;
	}
}

/** \brief USB get sof interrupt state
 * 
 *  \param[in] none
 *  \return error code \ref csi_error_t
 */ 
csi_error_t  csi_usb_get_sof_interrupt_state(void)
{
    return (tUsbSoftCtrl.bySofIrq == 1) ? CSI_OK:CSI_ERROR;
}

/** \brief USB clear sof interrupt state
 * 
 *  \param[in] none
 *  \return none
 */ 
void  csi_usb_clear_sof_interrupt_state(void)
{
    tUsbSoftCtrl.bySofIrq = 0;
}

/** \brief USB get vendor interrupt state
 * 
 *  \param[in] none
 *  \return error code \ref csi_error_t
 */
csi_error_t  csi_usb_get_vendor_interrupt_state(void)
{
    return (tUsbSoftCtrl.byVendorReceiveOnePacket == 1) ? CSI_OK:CSI_ERROR;
}

/** \brief USB clear vendor interrupt state
 * 
 *  \param[in] none
 *  \return none
 */ 
void  csi_usb_clear_vendor_interrupt_state(void)
{
    tUsbSoftCtrl.byVendorReceiveOnePacket = 0;
}


/** \brief USB set product string 
 * 
 *  \param[in] pbuf: pointer of usb string buf
 *  \param[in] byLength: string leng
 *  \return none
 */ 
void csi_usb_set_product_string(char * pbuf,uint8_t byLength)
{
	uint8_t i,data_len,val;
	for(i=2;i<58;i++)
	{
		byHidStringProdcut[i] = 0x00;
	}
	byHidStringProdcut[0] = 0x3a;
	byHidStringProdcut[1] = 0x03;
	if(byLength > 28)
	{
		byLength = 28;
	}
	data_len = 0;
	for(i=0;i<byLength;i++)
	{
		val = *pbuf++;
		if(val != 0x00)
		{
			data_len ++;
		}else{
			break;
		}
		byHidStringProdcut[2 + i*2] = val;
	}
	byHidStringProdcut[0] = data_len*2 + 2;

}

/** \brief  report ep1 data
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \param[in] pbyBuf: pointer of report ep1 data buf
 *  \param[in] wLength: report ep1 data leng
 *  \return flag status
 */ 
uint32_t csi_usb_report_ep1_data(csp_usb_t *ptUsbBase,uint8_t * pbyBuf,uint32_t wLength)
{
	uint32_t i , flag ;
    uint8_t *user_epdata,*star_epdata,*end_epdata;
	
	flag = 0;
	// if(!usb_config_ok) return 0;

	if(tUsbEp0Ctrl.byUsbConfig)
	{
		star_epdata = tUsbEpFifoAddr.pbyEpTxFifoStar[1] ;
		end_epdata  = tUsbEpFifoAddr.pbyEpTxFifoStar[2] ;

		if(tUsbSoftCtrl.hwMicFifoRdCntBack != ptUsbBase->CFIFO2_RD_PTR)	
		{       // err
			tUsbSoftCtrl.wMicFifoErrNum ++;
			flag |= 0x02;
		}

		if(!(ptUsbBase->EP1TX_CTL & 0x01)) // for audio
		{
			user_epdata = star_epdata;
			user_epdata += ptUsbBase->CFIFO2_RD_PTR;
			for(i=0;i<wLength;i++)
			{
				*user_epdata++ = *pbyBuf++;
				if(user_epdata >= end_epdata)
				{
					user_epdata = star_epdata;
				}
			}
			csp_usb_ep1tx_cnt(ptUsbBase, wLength);
			csp_usb_ep1tx_txen(ptUsbBase);
			flag |= 0x01;
		}
	}
	return flag;
}

/** \brief  read ep1 data
 * 
 *  \param[in] pwBuf: pointer of read ep1 data buf
 *  \param[in] wMaxLen: read ep1 data max leng
 *  \return one packet leng
 */ 
uint32_t csi_usb_read_ep1_data(uint32_t * pwBuf,uint32_t wMaxLen)
{
	uint32_t *p_user_data,*p_star_data,*p_end_data;
//	uint32_t i,one_packet_len,hp_fifo_len,hp_packet_wr_ptr;
	uint32_t i, wDataLength = 0;
	// if(!usb_config_ok) return 0;
	p_star_data = (uint32_t *)tUsbEpFifoAddr.pbyEpRxFifoStar[1] ;
	p_end_data = (uint32_t *)tUsbEpFifoAddr.pbyEpRxFifoStar[2] ;
//    hp_fifo_len = (uint32_t)(tUsbEpFifoAddr.pbyEpRxFifoStar[2] - tUsbEpFifoAddr.pbyEpRxFifoStar[1]) ;
	
	wDataLength = csp_usb_get_ep1rx_cnt(USBD);
	
	for (i = 0; i< wDataLength; i++)
	{
		 *pwBuf++ = *p_star_data++;
	}
	return wDataLength;
//    one_packet_len = tUsbSoftCtrl.hwHpFifoWrCntBack;
//    hp_packet_wr_ptr = tUsbSoftCtrl.hwHpFifoWrPtrBack;
//	
//	one_packet_len = csp_usb_get_ep1rx_cnt(USBD);
//	
//    if((one_packet_len == 0) || ((one_packet_len%4) != 0) || (one_packet_len > (wMaxLen*4)))
//    {
//        return 0;
//    }
//
//    if(hp_packet_wr_ptr < one_packet_len)
//    {
//        hp_packet_wr_ptr += hp_fifo_len ;
//    }
//    hp_packet_wr_ptr -= one_packet_len;
//
//    one_packet_len /= 4;
//    p_user_data = p_star_data + (hp_packet_wr_ptr/4);
//    for(i=0;i<one_packet_len;i++)
//    {
//        *pwBuf++ = *p_user_data++;
//        if(p_user_data >= p_end_data)
//        {
//            p_user_data = p_star_data;
//        }
//    }
//    return one_packet_len;
}

/** \brief usb report ep4 data
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \param[in] pbyBuf: pointer of report ep4 data buf
 *  \param[in] byLeng: report ep4 data leng
 *  \return error code \ref csi_error_t
 */  
csi_error_t csi_usb_report_ep4_data(csp_usb_t *ptUsbBase,uint8_t * pbyBuf,uint8_t byLeng)
{
	uint8_t i;
	csi_error_t flag;
	uint8_t * p_user_ep_data;

	flag = CSI_ERROR;
	// if(!usb_config_ok) return 0; 
	if(!(ptUsbBase->EP4TX_CTL & 0x01))
	{
		csp_usb_ep4tx_cnt(ptUsbBase, byLeng);
		p_user_ep_data = tUsbEpFifoAddr.pbyEpTxFifoStar[4] ;
		for(i=0;i<byLeng;i++)
		{
			*p_user_ep_data ++ = *pbyBuf++;
		}
		csp_usb_ep4tx_txen(ptUsbBase);
		flag = CSI_OK;
	}
	return flag;
}

 /** \brief usb ep4 free
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \return error code  CSI_OK:free  CSI_ERROR:busy
 */ 
csi_error_t csi_usb_ep4_is_free(csp_usb_t *ptUsbBase)
{
	csi_error_t flag;

	flag = CSI_ERROR;
	// if(!usb_config_ok) return 0; 
	if(!(ptUsbBase->EP4TX_CTL & 0x01))
	{
		flag = CSI_OK;
	}
	return flag;
}

 /** \brief usb receive ep4 data
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \param[in] pbyBuf: pointer of receive ep4 data buf
 *  \param[in] hwMaxLen: receive ep4 data max leng
 *  \return receive data leng
 */
uint16_t csi_usb_receive_ep4_data(csp_usb_t *ptUsbBase,uint8_t * pbyBuf,uint16_t hwMaxLen)
{
	uint16_t i,leng;
	uint8_t * p_user_ep_data;

	leng = 0;
	// if(!usb_config_ok) return 0;
	if(!(ptUsbBase->EP4RX_CTL & 0x01))		// rx enable
	{
		leng = csp_usb_ep4rx_get_cnt(ptUsbBase);
		if(leng > hwMaxLen){
			leng = hwMaxLen;
		}
		p_user_ep_data = tUsbEpFifoAddr.pbyEpRxFifoStar[4] ;
		for(i=0;i<leng;i++)
		{
			*pbyBuf++ = *p_user_ep_data++ ;
		}
		csp_usb_ep4rx_rxen(ptUsbBase);
	}
	return leng;
}

 /** \brief usb report ep3 data
 * 
 *  \param[in] ptUsbBase: pointer of usb register structure
 *  \param[in] pbyBuf: pointer of report ep3 data buf
 *  \param[in] byLeng: report ep3 data  leng
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_usb_report_ep3_data(csp_usb_t *ptUsbBase,uint8_t * pbyBuf,uint8_t byLeng)
{
	uint8_t i;
	csi_error_t flag;
	uint8_t * p_user_ep_data;

	flag = CSI_ERROR;
	// if(!usb_config_ok) return 0; 
	if(!(ptUsbBase->EP3TX_CTL & 0x01))
	{
		csp_usb_ep3tx_cnt(ptUsbBase, byLeng);
		p_user_ep_data = tUsbEpFifoAddr.pbyEpTxFifoStar[3] ;
		for(i=0;i<byLeng;i++)
		{
			*p_user_ep_data ++ = *pbyBuf++;
		}
		csp_usb_ep3tx_txen(ptUsbBase);
		flag = CSI_OK;
	}
	return flag;
}

