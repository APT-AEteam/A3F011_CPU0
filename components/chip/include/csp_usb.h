/***********************************************************************//** 
 * \file  csp_usb.h
 * \brief BT description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-12-13 <td>V0.0  <td>YYM   <td>initial
 * </table>
 * *********************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CSP_USB_H
#define _CSP_USB_H

/* Includes ------------------------------------------------------------------*/
#include <soc.h>
#include "csp_common.h"
/// \struct csp_bt_t
/// \brief BT reg description      
 typedef struct
 {
	 __IOM uint32_t USB_CR;	    //0x0000	Configure and enable USB Device.
	 __IOM uint32_t USB_ADDR;	//0x0004	USB base address.
	 __IOM uint32_t USB_EPSEL;	//0x0008	Endpoint selection.
	 __IOM uint32_t USB_IDLE;	//0x000C	Select delay time of ACK.
	 __IOM uint32_t FIFO_OFFSETL;	//0x0010	Pointer of endpoint ,Low 8 bit.
	 __IOM uint32_t FIFO_OFFSETH;	//0x0014	Pointer of endpoint ,High 2 bit.
	 __IOM uint32_t FIFO_BASEADDR;	//0x0018	Base address and size of Endpoint.
	 __IOM uint32_t USB_ISO;    //0x001C	Configuration of Endpoint for isochronous transfer.
	 __IOM uint32_t USB_IMR;	    //0x0020	USBD interrupt enable.
	 __IOM uint32_t EP_TXISR;	//0x0024	Transmit endpoint interrupt flag.
	 __IOM uint32_t EP_RXISR;	//0x0028	Receive endpoint interrupt flag.
	 __IM uint32_t 	USB_ISR;	    //0x002C	USBD interrupt vector.
	 __IM uint32_t USB_FRAMEL;	//0x0030	SOF frame number ,low 8 bit.
	 __IM uint32_t USB_FRAMEH;	//0x0034	SOF frame number ,high 2 bit.
	 __IOM uint32_t EP0RX_CTL;	//0x0038	Receive control for Endpoint 0.
	 __IOM uint32_t EP0RX_CNT;	//0x003C	Receive data count for Endpoint 0, unit is byte.
	 __IOM uint32_t EP1RX_CTL;	//0x0040	Receive control for Endpoint 1.
	 __IOM uint32_t EP1RX_CNT;	//0x0044	Receive data count for Endpoint 1, unit is byte.
	 __IOM uint32_t EP2RX_CTL;	//0x0048	Receive control for Endpoint 2.
	 __IOM uint32_t EP2RX_CNT;	//0x004C	Receive data count for Endpoint 2, unit is byte.
	 __IOM uint32_t EP3RX_CTL;	//0x0050	Receive control for Endpoint 3.
	 __IOM uint32_t EP3RX_CNT;	//0x0054	Receive data count for Endpoint 3, unit is byte.
	 __IOM uint32_t EP4RX_CTL;	//0x0058	Receive control for Endpoint 4.
	 __IOM uint32_t EP4RX_CNT;	//0x005C	Receive data count for Endpoint 4, unit is byte.
	 __IOM uint32_t EP5RX_CTL;	//0x0060	Receive control for Endpoint 5.
	 __IOM uint32_t EP5RX_CNT;	//0x0064	Receive data count for Endpoint 5, unit is byte.
	 __IOM uint32_t EP6RX_CTL;	//0x0068	Receive control for Endpoint 6.
	 __IOM uint32_t EP6RX_CNT;	//0x006C	Receive data count for Endpoint 6, unit is byte.
	 __IOM uint32_t EP0TX_CTL;	//0x0070	Transmit control for Endpoint 0.
	 __IOM uint32_t EP0TX_CNT;	//0x0074	Transmit data count for Endpoint 0, unit is byte.
	 __IOM uint32_t EP1TX_CTL;	//0x0078	Transmit control for Endpoint 1.
	 __IOM uint32_t EP1TX_CNT;	//0x007C	Transmit data count for Endpoint 1, unit is byte.
	 __IOM uint32_t EP2TX_CTL;	//0x0080	Transmit control for Endpoint 2.
	 __IOM uint32_t EP2TX_CNT;	//0x0084	Transmit data count for Endpoint 2, unit is byte.
	 __IOM uint32_t EP3TX_CTL;	//0x0088	Transmit control for Endpoint 3.
	 __IOM uint32_t EP3TX_CNT;	//0x008C	Transmit data count for Endpoint 3, unit is byte.
	 __IOM uint32_t EP4TX_CTL;	//0x0090	Transmit control for Endpoint 4.
	 __IOM uint32_t EP4TX_CNT;	//0x0094	Transmit data count for Endpoint 4, unit is byte.
	 __IOM uint32_t EP5TX_CTL;	//0x0098	Transmit control for Endpoint 5.
	 __IOM uint32_t EP5TX_CNT;	//0x009C	Transmit data count for Endpoint 5, unit is byte.
	 __IOM uint32_t EP6TX_CTL;	//0x00A0	Transmit control for Endpoint 6.
	 __IOM uint32_t EP6TX_CNT;	//0x00A4	Transmit data count for Endpoint 6, unit is byte.
	 __IOM uint32_t PMA_ADDR;	//0x00A8	SRAM base address for all the endpoints.
	 __IM uint32_t CFIFO0_RD_PTR;	//0x00AC	Read pointer of Circular FIFO0 for TX endpoint.
	 __IM uint32_t CFIFO1_WR_PTR;	//0x00B0	Write pointer of Circular FIFO1 for RX endpoint.
	 __IM uint32_t CFIFO2_RD_PTR;	//0x00B4	Read pointer of Circular FIFO2 for TX endpoint.
	 __IM uint32_t CFIFO3_WR_PTR;	//0x00B8	Write pointer of Circular FIFO3 for RX endpoint.

} csp_usb_t; 

/******************************************************************************
* CR : USB Control Register
******************************************************************************/

#define USB_SETUP_FLAG_POS		      (0)
#define USB_SETUP_FLAG_MSK		  (0x01ul << USB_SETUP_FLAG_POS)

#define USB_RESUME_FLAG_POS		      (1)
#define USB_RESUME_FLAG_MSK		  (0x01ul << USB_RESUME_FLAG_POS)

#define USB_SUSPEND_FLAG_POS          (2)
#define USB_SUSPEND_FLAG_MSK	  (0x01ul << USB_SUSPEND_FLAG_POS)

#define USB_RESET_FLAG_POS             (3)
#define USB_RESET_FLAG_MSK	       (0x01ul << USB_RESET_FLAG_POS)

#define USB_WAKEUP_POS                 (4)
#define USB_WAKEUP_MSK	           (0x01ul << USB_WAKEUP_POS)

#define USB_SEO_GLAG_POS               (1<< 5)

#define USB_PUP_POS                    (6)
#define USB_PUP_MSK	               (0x01ul << USB_PUP_POS)
#define USB_PUP_EN                 (1) 

#define USB_PULLUP_LO_POS              (7)
#define USB_PULLUP_LO_MSK	       (0x01ul << USB_PULLUP_LO_POS)
#define USB_PULLUP_LO_EN                 (1) 

#define USB_SUSPEND_POS                (8)
#define USB_SUSPEND_MSK	           (0x01ul << USB_SUSPEND_POS)
#define USB_SUSPEND_EN                 (1) 

#define USB_CLK_POS                 (9)
#define USB_CLK_MSK	           (0x01ul << USB_CLK_POS)
#define USB_CLK_EN                 (1) 


/******************************************************************************
* ADDR : USB ADDR
******************************************************************************/
#define USB_ADDR_SET_POS                   (0)
#define USB_ADDR_SET_MSK	           (0x7Ful << USB_ADDR_SET_POS)


/******************************************************************************
* ADDR : USB EPSEL
******************************************************************************/
#define USB_EPSEL_POS                   (0)
#define USB_EPSEL_MSK	            (0xFul << USB_EPSEL_POS)

#define USB_INOUT_POS                   (4)
#define USB_INOUT_MSK	            (0x1ul << USB_INOUT_POS)

typedef enum
{
	USB_EP_0	= 0,
    USB_EP_1,
    USB_EP_2,
    USB_EP_3,
    USB_EP_4,
	USB_EP_5,
	USB_EP_6
       
}usb_USB_EPSEL_e;

typedef enum
{
	USB_EP_OUT	= 0,
    USB_EP_IN
       
}usb_ep_inout_e;


/******************************************************************************
* ADDR : USB ISO
******************************************************************************/
#define USB_EPTX0_POS                   (0)
#define USB_EPTX0_MSK	            (0x07ul << USB_EPTX0_POS)

#define USB_ISOTX0_POS                   (3)
#define USB_ISOTX0_MSK	            (0x01ul << USB_ISOTX0_POS)

#define USB_EPRX0_POS                   (4)
#define USB_EPRX0_MSK	            (0x07ul << USB_EPRX0_POS)

#define USB_ISORX0_POS                   (7)
#define USB_ISORX0_MSK	            (0x01ul << USB_ISORX0_POS)


#define USB_EPTX1_POS                   (8)
#define USB_EPTX1_MSK	            (0x07ul << USB_EPTX1_POS)

#define USB_ISOTX1_POS                   (11)
#define USB_ISOTX1_MSK	            (0x01ul << USB_ISOTX1_POS)

#define USB_EPRX1_POS                   (12)
#define USB_EPRX1_MSK	            (0x07ul << USB_EPRX1_POS)

#define USB_ISORX1_POS                   (15)
#define USB_ISORX1_MSK	            (0x01ul << USB_ISORX1_POS)

typedef enum
{
	USB_ISO_DIS	  = 0,
    USB_ISO_ENABLE
       
}usb_iso_e;

typedef enum
{
	USB_ISO_EP_NONE	  = 0,
    USB_ISO_EP_1,
	USB_ISO_EP_2,
	USB_ISO_EP_3,
	USB_ISO_EP_4,
	USB_ISO_EP_5,
	USB_ISO_EP_6
       
}usb_iso_ep_e;

/******************************************************************************
* USB IE
******************************************************************************/
typedef enum
{
	USB_SETUP_INT = (1 << 0),
	USB_RES_INT =   (1 << 1),
	USB_SUS_INT =   (1 << 2),	
	USB_RST_INT =   (1 << 3),	
	USB_SOF_INT =   (1 << 4)

}usb_int_e;

#define USB_SOFIF_POS               (7)
#define USB_SOFIF_MSK	            (0x01ul << USB_SOFIF_POS)

typedef enum
{
	USB_EPTXIF0 =   (1 << 0),
	USB_EPTXIF1 =   (1 << 1),
	USB_EPTXIF2 =   (1 << 2),	
	USB_EPTXIF3 =   (1 << 3),	
	USB_EPTXIF4 =   (1 << 4),
	USB_EPTXIF5 =   (1 << 5),	
	USB_EPTXIF6 =   (1 << 6)	

}usb_ep_txrxif_e;

/******************************************************************************
*USB EP RXCR/TXCR
******************************************************************************/
#define USB_EP_RXEN_POS             (0)
#define USB_EP_RXEN_MSK	            (0x01ul << USB_EP_EN_POS)
#define USB_EP_RXEN_EN              (1)

#define USB_EP_TXEN_POS             (0)
#define USB_EP_TXEN_MSK	            (0x01ul << USB_EP_EN_POS)
#define USB_EP_TXEN_EN              (1)


#define USB_EP_STALL_POS            (1)
#define USB_EP_STALL_MSK	        (0x01ul << USB_EP_STALL_POS)
#define USB_EP_STALL_EN              (1)

#define USB_EP_TOGGLE_POS           (2)
#define USB_EP_TOGGLE_MSK	        (0x01ul << USB_EP_TOGGLE_POS)
#define USB_EP_TOGGLE_EN              (1)

#define USB_EP_IE_POS               (6)
#define USB_EP_IE_MSK	            (0x01ul << USB_EP_IE_POS)
#define USB_EP_IE_EN                (1)

#define USB_EP_EN_POS               (7)
#define USB_EP_EN_MSK	            (0x01ul << USB_EP_EN_POS)
#define USB_EP_EN_EN                (1)

/******************************************************************************
*USB EP RXCR/TXCR
******************************************************************************/
#define USB_CNT_MSK					(0x3FF)





static inline void csp_usb_clear_all_flag(csp_usb_t *ptUsbBase)
{
	ptUsbBase->USB_CR &= ~(USB_SETUP_FLAG_MSK |USB_SUSPEND_FLAG_MSK |USB_RESET_FLAG_MSK);
}


static inline void csp_usb_clear_setup_flag(csp_usb_t *ptUsbBase)
{
	ptUsbBase->USB_CR &= ~USB_SETUP_FLAG_MSK;
}

static inline void csp_usb_clear_suspend_flag(csp_usb_t *ptUsbBase)
{
	ptUsbBase->USB_CR &= ~USB_SUSPEND_FLAG_MSK;
}

static inline void csp_usb_clear_reset_flag(csp_usb_t *ptUsbBase)
{
	ptUsbBase->USB_CR &= ~USB_RESET_FLAG_MSK;
}

static inline void csp_usb_set_pup(csp_usb_t *ptUsbBase)
{
	ptUsbBase->USB_CR = (ptUsbBase->USB_CR & ~USB_PUP_MSK)| (USB_PUP_EN<<USB_PUP_POS);
}

static inline void csp_usb_set_pullup_lo(csp_usb_t *ptUsbBase)
{
	ptUsbBase->USB_CR = (ptUsbBase->USB_CR & ~USB_PULLUP_LO_MSK)| (USB_PULLUP_LO_EN<<USB_PULLUP_LO_POS);
}

static inline void csp_usb_set_phy_suspend(csp_usb_t *ptUsbBase)
{
	ptUsbBase->USB_CR = (ptUsbBase->USB_CR & ~USB_SUSPEND_MSK)| (USB_SUSPEND_EN<<USB_SUSPEND_POS);
}

static inline void csp_usb_en(csp_usb_t *ptUsbBase)
{
	ptUsbBase->USB_CR |= (USB_CLK_EN << USB_CLK_POS);
}


static inline void csp_usb_set_addr(csp_usb_t *ptUsbBase,uint32_t wAddr)
{
	ptUsbBase->USB_ADDR = wAddr;
}


static inline void csp_usb_set_ep(csp_usb_t *ptUsbBase,usb_USB_EPSEL_e eEpSel,usb_ep_inout_e eEpInout)
{
	ptUsbBase->USB_EPSEL = (eEpSel<< USB_EPSEL_POS)|(eEpInout << USB_INOUT_POS);
}

static inline void csp_usb_set_ep_pointer(csp_usb_t *ptUsbBase,uint8_t byPointerL,uint8_t byPointerH)
{
	ptUsbBase->FIFO_OFFSETL  = byPointerL;
	ptUsbBase->FIFO_OFFSETH = byPointerH;
}

static inline void csp_usb_set_fifo(csp_usb_t *ptUsbBase,uint8_t byFifo)
{
	ptUsbBase->FIFO_BASEADDR  = byFifo;
}

static inline void csp_usb_set_iso_tx0(csp_usb_t *ptUsbBase,usb_iso_e eIsoEnable,usb_iso_ep_e eIsoEp)
{
	ptUsbBase->USB_ISO  = (ptUsbBase->USB_ISO & (~USB_EPTX0_MSK) &(~USB_ISOTX0_MSK))|(eIsoEnable << USB_ISOTX0_POS)|(eIsoEp << USB_EPTX0_POS);
}

static inline void csp_usb_set_iso_rx0(csp_usb_t *ptUsbBase,usb_iso_e eIsoEnable,usb_iso_ep_e eIsoEp)
{
	ptUsbBase->USB_ISO  = (ptUsbBase->USB_ISO & (~USB_EPRX0_MSK) &(~USB_ISORX0_MSK))|(eIsoEnable << USB_ISORX0_POS)|(eIsoEp << USB_EPRX0_POS);
}

static inline void csp_usb_set_iso_tx1(csp_usb_t *ptUsbBase,usb_iso_e eIsoEnable,usb_iso_ep_e eIsoEp)
{
	ptUsbBase->USB_ISO  = (ptUsbBase->USB_ISO & (~USB_EPTX1_MSK) &(~USB_ISOTX1_MSK))|(eIsoEnable << USB_ISOTX1_POS)|(eIsoEp << USB_EPTX1_POS);
}

static inline void csp_usb_set_iso_rx1(csp_usb_t *ptUsbBase,usb_iso_e eIsoEnable,usb_iso_ep_e eIsoEp)
{
	ptUsbBase->USB_ISO  = (ptUsbBase->USB_ISO & (~USB_EPRX1_MSK) &(~USB_ISORX1_MSK))|(eIsoEnable << USB_ISORX1_POS)|(eIsoEp << USB_EPRX1_POS);
}

static inline void csp_usb_int_enable(csp_usb_t *ptUsbBase, usb_int_e eUsbInt,bool bEnable)
{
	if(bEnable)
		ptUsbBase->USB_IMR |= eUsbInt; 
	else
		ptUsbBase->USB_IMR &= ~eUsbInt; 
}

static inline void csp_usb_sof_if(csp_usb_t *ptUsbBase)
{
	ptUsbBase->USB_IMR = (ptUsbBase->USB_IMR & (~USB_SOFIF_MSK)); 
}

static inline void csp_usb_ep_txif(csp_usb_t *ptUsbBase, usb_ep_txrxif_e eUsbEpTxIf,bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP_TXISR |= eUsbEpTxIf; 
	else
		ptUsbBase->EP_TXISR &= ~eUsbEpTxIf; 
}

static inline void csp_usb_ep_rxif(csp_usb_t *ptUsbBase, usb_ep_txrxif_e eUsbEpTxIf,bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP_RXISR |= eUsbEpTxIf; 
	else
		ptUsbBase->EP_RXISR &= ~eUsbEpTxIf; 
}

static inline uint8_t csp_usb_get_isr(csp_usb_t *ptUsbBase)
{
	return (ptUsbBase->USB_ISR&0x1f); 
}

static inline uint16_t csp_usb_get_frame_len(csp_usb_t *ptUsbBase)
{
	return  (ptUsbBase->USB_FRAMEL &0xff) | ((ptUsbBase->USB_FRAMEH &0x07)<<8); 
	
}

/*=========================================================
 *  USB_EP[x]RXCR unified control start
 * ========================================================*/
static inline void csp_usb_ep_rx_enable(csp_usb_t *ptUsbBase, uint8_t byEpNum)
{
	*(&(ptUsbBase->EP0RX_CTL) + (byEpNum*2)) |= (USB_EP_RXEN_EN << USB_EP_RXEN_POS) | USB_EP_EN_EN << USB_EP_EN_POS;
}

static inline void csp_usb_ep_rx_disable(csp_usb_t *ptUsbBase, uint8_t byEpNum)
{
	*(&(ptUsbBase->EP0RX_CTL) + (byEpNum*2)) &= (~USB_EP_RXEN_MSK);
}

static inline void csp_usb_ep_rx_set_stall(csp_usb_t *ptUsbBase, uint8_t byEpNum)
{
	*(&(ptUsbBase->EP0RX_CTL) + (byEpNum*2)) |= (USB_EP_STALL_EN << USB_EP_STALL_POS);
}

static inline void csp_usb_ep_rx_clear_stall(csp_usb_t *ptUsbBase, uint8_t byEpNum)
{
	*(&(ptUsbBase->EP0RX_CTL) + (byEpNum*2))  &= ( ~USB_EP_STALL_MSK);
}

static inline void csp_usb_ep_rx_toggle_enable(csp_usb_t *ptUsbBase, uint8_t byEpNum)
{
	*(&(ptUsbBase->EP0RX_CTL) + (byEpNum*2)) |= (USB_EP_TOGGLE_EN << USB_EP_TOGGLE_POS);
}

static inline void csp_usb_ep_rx_toggle_disable(csp_usb_t *ptUsbBase, uint8_t byEpNum)
{
	*(&(ptUsbBase->EP0RX_CTL) + (byEpNum*2)) &= (~USB_EP_TOGGLE_MSK);
}

static inline void csp_usb_ep_rx_int_enable(csp_usb_t *ptUsbBase, uint8_t byEpNum)
{
	*(&(ptUsbBase->EP0RX_CTL) + (byEpNum*2)) |= (USB_EP_IE_EN << USB_EP_IE_POS);
}

static inline void csp_usb_ep_rx_int_disable(csp_usb_t *ptUsbBase, uint8_t byEpNum)
{
	*(&(ptUsbBase->EP0RX_CTL) + (byEpNum*2))  &= (~USB_EP_IE_MSK);
}


/*=========================================================
 *  USB_EP[x]RXCR unified control end
 * ========================================================*/
 
/*=========================================================
 *  USB_EP[x]RXCNT unified control start
 * ========================================================*/
 static inline void csp_usb_ep_set_rxcnt(csp_usb_t *ptUsbBase, uint8_t byEpNum, uint8_t byCnt)
{
	*(&(ptUsbBase->EP0RX_CNT) + (byEpNum*2)) = byCnt;
}
 
static inline uint8_t csp_usb_ep_get_rxcnt(csp_usb_t *ptUsbBase, uint8_t byEpNum)
{
	return (*(&(ptUsbBase->EP0RX_CNT) + (byEpNum*2)));
}

static inline bool csp_usb_ep_increase_rxcnt(csp_usb_t *ptUsbBase, uint8_t byEpNum)
{

	uint32_t wRxCnt = csp_usb_ep_get_rxcnt(ptUsbBase, byEpNum);
	if (wRxCnt< USB_CNT_MSK)
		*(&(ptUsbBase->EP0TX_CNT) + (byEpNum*2)) = wRxCnt +1 ;
	else
		 return FALSE;
	return TRUE;
}

static inline bool csp_usb_ep_decrease_rxcnt(csp_usb_t *ptUsbBase, uint8_t byEpNum)
{
	uint32_t wRxCnt = csp_usb_ep_get_rxcnt(ptUsbBase, byEpNum);
	if (wRxCnt> 0)
		*(&(ptUsbBase->EP0TX_CNT) + (byEpNum*2)) = wRxCnt - 1 ;
	else
		 return FALSE;
	return TRUE;
}
/*=========================================================
 *  USB_EP[x]RXCNT unified control end
 * ========================================================*/
 
 /*=========================================================
 *  USB_EP[x]TXCR unified control start
 * ========================================================*/
static inline void csp_usb_ep_tx_enable(csp_usb_t *ptUsbBase, uint8_t byEpNum)
{
	*(&(ptUsbBase->EP0RX_CTL) + (byEpNum*2)) |= (USB_EP_TXEN_EN << USB_EP_TXEN_POS) | USB_EP_EN_EN << USB_EP_EN_POS;
}

static inline void csp_usb_ep_tx_disable(csp_usb_t *ptUsbBase, uint8_t byEpNum)
{
	*(&(ptUsbBase->EP0RX_CTL) + (byEpNum*2)) &= (~USB_EP_TXEN_MSK);
}

static inline void csp_usb_ep_tx_set_stall(csp_usb_t *ptUsbBase, uint8_t byEpNum)
{
	*(&(ptUsbBase->EP0TX_CTL) + (byEpNum*2)) |= (USB_EP_STALL_EN << USB_EP_STALL_POS);
}

static inline void csp_usb_ep_tx_clear_stall(csp_usb_t *ptUsbBase, uint8_t byEpNum)
{
	*(&(ptUsbBase->EP0TX_CTL) + (byEpNum*2))  &= ( ~USB_EP_STALL_MSK);
}

static inline void csp_usb_ep_tx_toggle_enable(csp_usb_t *ptUsbBase, uint8_t byEpNum)
{
	*(&(ptUsbBase->EP0TX_CTL) + (byEpNum*2)) |= (USB_EP_TOGGLE_EN << USB_EP_TOGGLE_POS);
}

static inline void csp_usb_ep_tx_toggle_disable(csp_usb_t *ptUsbBase, uint8_t byEpNum)
{
	*(&(ptUsbBase->EP0TX_CTL) + (byEpNum*2)) &= (~USB_EP_TOGGLE_MSK);
}

static inline void csp_usb_ep_tx_int_enable(csp_usb_t *ptUsbBase, uint8_t byEpNum)
{
	*(&(ptUsbBase->EP0TX_CTL) + (byEpNum*2)) |= (USB_EP_IE_EN << USB_EP_IE_POS);
}

static inline void csp_usb_ep_tx_int_disable(csp_usb_t *ptUsbBase, uint8_t byEpNum)
{
	*(&(ptUsbBase->EP0TX_CTL) + (byEpNum*2))  &= (~USB_EP_IE_MSK);
}


 /*=========================================================
 *  USB_EP[x]TXCR unified control end
 * ========================================================*/ 
 
/*=========================================================
 *  USB_EP[x]TXCNT unified control start
 * ========================================================*/
 static inline void csp_usb_ep_set_txcnt(csp_usb_t *ptUsbBase, uint8_t byEpNum, uint16_t hwCnt)
{
	*(&(ptUsbBase->EP0TX_CNT) + (byEpNum*2)) = hwCnt;
}
 
static inline uint8_t csp_usb_ep_get_txcnt(csp_usb_t *ptUsbBase, uint16_t byEpNum)
{
	return (*(&(ptUsbBase->EP0TX_CNT) + (byEpNum*2)));
}

static inline bool csp_usb_ep_increase_txcnt(csp_usb_t *ptUsbBase, uint8_t byEpNum)
{
	uint32_t wTxCnt = csp_usb_ep_get_txcnt(ptUsbBase, byEpNum);
	if (wTxCnt< USB_CNT_MSK)
		*(&(ptUsbBase->EP0TX_CNT) + (byEpNum*2)) = wTxCnt +1 ;
	else
		 return FALSE;
	return TRUE;
}

static inline bool csp_usb_ep_decrease_txcnt(csp_usb_t *ptUsbBase, uint8_t byEpNum)
{
	uint32_t wTxCnt = csp_usb_ep_get_txcnt(ptUsbBase, byEpNum);
	if (wTxCnt> 0)
		*(&(ptUsbBase->EP0TX_CNT) + (byEpNum*2)) = wTxCnt -1 ;
	else
		 return FALSE;
	return TRUE;
}
/*=========================================================
 *  USB_EP[x]RXCNT unified control end
 * ========================================================*/
 
 

static inline void csp_usb_set_pma_addr(csp_usb_t *ptUsbBase, uint32_t wAddr)
{
	ptUsbBase->PMA_ADDR = wAddr; 
}

static inline uint32_t csp_usb_get_pma_addr(csp_usb_t *ptUsbBase)
{
	return (ptUsbBase->PMA_ADDR);
}


static inline uint16_t csp_usb_get_cfifo0_rdptr(csp_usb_t *ptUsbBase)
{
	return ptUsbBase->CFIFO0_RD_PTR; 
}


static inline uint16_t csp_usb_get_cfifo1_wrptr(csp_usb_t *ptUsbBase)
{
	return ptUsbBase->CFIFO1_WR_PTR; 
}

static inline uint16_t csp_usb_get_cfifo2_rdptr(csp_usb_t *ptUsbBase)
{
	return ptUsbBase->CFIFO2_RD_PTR; 
}

static inline uint16_t csp_usb_get_cfifo3_wrptr(csp_usb_t *ptUsbBase)
{
	return ptUsbBase->CFIFO3_WR_PTR; 
}
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 /*以下为第一版驱动中对EPxRX_CTRL/CNT，EPxTX_CTRL/CNT的支持，不够简洁*/
 

//ep0rx 
static inline void csp_usb_ep0rx_rxen(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP0RX_CTL |= (USB_EP_RXEN_EN << USB_EP_RXEN_POS); 
}

static inline void csp_usb_ep0rx_stall(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP0RX_CTL |= (USB_EP_STALL_EN << USB_EP_STALL_POS); 
}

static inline void csp_usb_ep0rx_clear_stall(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP0RX_CTL &= ( ~USB_EP_STALL_MSK); 
}

static inline void csp_usb_ep0rx_toggle(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP0RX_CTL |= (USB_EP_TOGGLE_EN << USB_EP_TOGGLE_POS); 
	else
		ptUsbBase->EP0RX_CTL &= (~USB_EP_TOGGLE_MSK); 
}

static inline void csp_usb_ep0rx_epie(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP0RX_CTL |= (USB_EP_IE_EN << USB_EP_IE_POS); 
	else
		ptUsbBase->EP0RX_CTL &= (~USB_EP_IE_MSK); 
}

static inline void csp_usb_ep0rx_epen(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP0RX_CTL |= (USB_EP_EN_EN << USB_EP_EN_POS); 
	else
		ptUsbBase->EP0RX_CTL &= (~USB_EP_EN_MSK); 
}

static inline void csp_usb_set_ep0rx_cnt(csp_usb_t *ptUsbBase, uint16_t hwCnt)
{
	ptUsbBase->EP0RX_CNT = hwCnt; 
}

static inline uint16_t csp_usb_get_ep0rx_cnt(csp_usb_t *ptUsbBase)
{
	return ptUsbBase->EP0RX_CNT; 
}

//ep1rx 
static inline void csp_usb_ep1rx_rxen(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP1RX_CTL |= (USB_EP_RXEN_EN << USB_EP_RXEN_POS); 
}

static inline void csp_usb_ep1rx_stall(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP1RX_CTL |= (USB_EP_STALL_EN << USB_EP_STALL_POS); 
}

static inline void csp_usb_ep1rx_clear_stall(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP1RX_CTL &= ( ~USB_EP_STALL_MSK); 
}

static inline void csp_usb_ep1rx_toggle(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP1RX_CTL |= (USB_EP_TOGGLE_EN << USB_EP_TOGGLE_POS); 
	else
		ptUsbBase->EP1RX_CTL &= (~USB_EP_TOGGLE_MSK); 
}

static inline void csp_usb_ep1rx_epie(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP1RX_CTL |= (USB_EP_IE_EN << USB_EP_IE_POS); 
	else
		ptUsbBase->EP1RX_CTL &= (~USB_EP_IE_MSK); 
}

static inline void csp_usb_ep1rx_epen(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP1RX_CTL |= (USB_EP_EN_EN << USB_EP_EN_POS); 
	else
		ptUsbBase->EP1RX_CTL &= (~USB_EP_EN_MSK); 
}

static inline void csp_usb_set_ep1rx_cnt(csp_usb_t *ptUsbBase, uint16_t hwCnt)
{
	ptUsbBase->EP1RX_CNT = hwCnt; 
}

static inline uint16_t csp_usb_get_ep1rx_cnt(csp_usb_t *ptUsbBase)
{
	return ptUsbBase->EP1RX_CNT; 
}

//ep2rx 
static inline void csp_usb_ep2rx_rxen(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP2RX_CTL |= (USB_EP_RXEN_EN << USB_EP_RXEN_POS); 
}

static inline void csp_usb_ep2rx_stall(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP2RX_CTL |= (USB_EP_STALL_EN << USB_EP_STALL_POS); 
}

static inline void csp_usb_ep2rx_clear_stall(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP2RX_CTL &= ( ~USB_EP_STALL_MSK); 
}

static inline void csp_usb_ep2rx_toggle(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP2RX_CTL |= (USB_EP_TOGGLE_EN << USB_EP_TOGGLE_POS); 
	else
		ptUsbBase->EP2RX_CTL &= (~USB_EP_TOGGLE_MSK); 
}

static inline void csp_usb_ep2rx_epie(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP2RX_CTL |= (USB_EP_IE_EN << USB_EP_IE_POS); 
	else
		ptUsbBase->EP2RX_CTL &= (~USB_EP_IE_MSK); 
}

static inline void csp_usb_ep2rx_epen(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP2RX_CTL |= (USB_EP_EN_EN << USB_EP_EN_POS); 
	else
		ptUsbBase->EP2RX_CTL &= (~USB_EP_EN_MSK); 
}

static inline void csp_usb_set_ep2rx_cnt(csp_usb_t *ptUsbBase, uint16_t hwCnt)
{
	ptUsbBase->EP2RX_CNT = hwCnt; 
}

static inline uint16_t csp_usb_get_ep2rx_cnt(csp_usb_t *ptUsbBase)
{
	return ptUsbBase->EP2RX_CNT; 
}

//ep3rx 
static inline void csp_usb_ep3rx_rxen(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP3RX_CTL |= (USB_EP_RXEN_EN << USB_EP_RXEN_POS); 
}

static inline void csp_usb_ep3rx_stall(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP3RX_CTL |= (USB_EP_STALL_EN << USB_EP_STALL_POS); 
}

static inline void csp_usb_ep3rx_clear_stall(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP3RX_CTL &= ( ~USB_EP_STALL_MSK); 
}

static inline void csp_usb_ep3rx_toggle(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP3RX_CTL |= (USB_EP_TOGGLE_EN << USB_EP_TOGGLE_POS); 
	else
		ptUsbBase->EP3RX_CTL &= (~USB_EP_TOGGLE_MSK); 
}

static inline void csp_usb_ep3rx_epie(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP3RX_CTL |= (USB_EP_IE_EN << USB_EP_IE_POS); 
	else
		ptUsbBase->EP3RX_CTL &= (~USB_EP_IE_MSK); 
}

static inline void csp_usb_ep3rx_epen(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP3RX_CTL |= (USB_EP_EN_EN << USB_EP_EN_POS); 
	else
		ptUsbBase->EP3RX_CTL &= (~USB_EP_EN_MSK); 
}

static inline void csp_usb_set_ep3rx_cnt(csp_usb_t *ptUsbBase, uint16_t hwCnt)
{
	ptUsbBase->EP3RX_CNT = hwCnt; 
}

static inline uint16_t csp_usb_get_ep3rx_cnt(csp_usb_t *ptUsbBase)
{
	return ptUsbBase->EP3RX_CNT; 
}

//ep4rx 
static inline void csp_usb_ep4rx_rxen(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP4RX_CTL |= (USB_EP_RXEN_EN << USB_EP_RXEN_POS); 
}

static inline void csp_usb_ep4rx_stall(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP4RX_CTL |= (USB_EP_STALL_EN << USB_EP_STALL_POS); 
}

static inline void csp_usb_ep4rx_clear_stall(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP4RX_CTL &= ( ~USB_EP_STALL_MSK); 
}

static inline void csp_usb_ep4rx_toggle(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP4RX_CTL |= (USB_EP_TOGGLE_EN << USB_EP_TOGGLE_POS); 
	else
		ptUsbBase->EP4RX_CTL &= (~USB_EP_TOGGLE_MSK); 
}

static inline void csp_usb_ep4rx_epie(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP4RX_CTL |= (USB_EP_IE_EN << USB_EP_IE_POS); 
	else
		ptUsbBase->EP4RX_CTL &= (~USB_EP_IE_MSK); 
}

static inline void csp_usb_ep4rx_epen(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP4RX_CTL |= (USB_EP_EN_EN << USB_EP_EN_POS); 
	else
		ptUsbBase->EP4RX_CTL &= (~USB_EP_EN_MSK); 
}

static inline void csp_usb_ep4rx_cnt(csp_usb_t *ptUsbBase, uint16_t hwCnt)
{
	ptUsbBase->EP4RX_CNT = hwCnt; 
}

static inline uint16_t csp_usb_ep4rx_get_cnt(csp_usb_t *ptUsbBase)
{
	return ptUsbBase->EP4RX_CNT; 
}

//ep5rx 
static inline void csp_usb_ep5rx_rxen(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP5RX_CTL |= (USB_EP_RXEN_EN << USB_EP_RXEN_POS); 
}

static inline void csp_usb_ep5rx_stall(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP5RX_CTL |= (USB_EP_STALL_EN << USB_EP_STALL_POS); 
}

static inline void csp_usb_ep5rx_clear_stall(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP5RX_CTL &= ( ~USB_EP_STALL_MSK); 
}

static inline void csp_usb_ep5rx_toggle(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP5RX_CTL |= (USB_EP_TOGGLE_EN << USB_EP_TOGGLE_POS); 
	else
		ptUsbBase->EP5RX_CTL &= (~USB_EP_TOGGLE_MSK); 
}

static inline void csp_usb_ep5rx_epie(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP5RX_CTL |= (USB_EP_IE_EN << USB_EP_IE_POS); 
	else
		ptUsbBase->EP5RX_CTL &= (~USB_EP_IE_MSK); 
}

static inline void csp_usb_ep5rx_epen(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP5RX_CTL |= (USB_EP_EN_EN << USB_EP_EN_POS); 
	else
		ptUsbBase->EP5RX_CTL &= (~USB_EP_EN_MSK); 
}

static inline void csp_usb_ep5rx_cnt(csp_usb_t *ptUsbBase, uint16_t hwCnt)
{
	ptUsbBase->EP5RX_CNT = hwCnt; 
}

static inline uint16_t csp_usb_ep5rx_get_cnt(csp_usb_t *ptUsbBase)
{
	return ptUsbBase->EP5RX_CNT; 
}

//ep6rx 
static inline void csp_usb_ep6rx_rxen(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP6RX_CTL |= (USB_EP_RXEN_EN << USB_EP_RXEN_POS); 
}

static inline void csp_usb_ep6rx_stall(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP6RX_CTL |= (USB_EP_STALL_EN << USB_EP_STALL_POS); 
}

static inline void csp_usb_ep6rx_clear_stall(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP6RX_CTL &= ( ~USB_EP_STALL_MSK); 
}

static inline void csp_usb_ep6rx_toggle(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP6RX_CTL |= (USB_EP_TOGGLE_EN << USB_EP_TOGGLE_POS); 
	else
		ptUsbBase->EP6RX_CTL &= (~USB_EP_TOGGLE_MSK); 
}

static inline void csp_usb_ep6rx_epie(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP6RX_CTL |= (USB_EP_IE_EN << USB_EP_IE_POS); 
	else
		ptUsbBase->EP6RX_CTL &= (~USB_EP_IE_MSK); 
}

static inline void csp_usb_ep6rx_epen(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP6RX_CTL |= (USB_EP_EN_EN << USB_EP_EN_POS); 
	else
		ptUsbBase->EP6RX_CTL &= (~USB_EP_EN_MSK); 
}

static inline void csp_usb_ep6rx_cnt(csp_usb_t *ptUsbBase, uint16_t hwCnt)
{
	ptUsbBase->EP6RX_CNT = hwCnt; 
}

static inline uint16_t csp_usb_ep6rx_get_cnt(csp_usb_t *ptUsbBase)
{
	return ptUsbBase->EP6RX_CNT; 
}


//ep0tx 
static inline void csp_usb_ep0tx_txen(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP0TX_CTL |= (USB_EP_RXEN_EN << USB_EP_RXEN_POS); 
}

static inline void csp_usb_ep0tx_stall(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP0TX_CTL |= (USB_EP_STALL_EN << USB_EP_STALL_POS); 
}

static inline void csp_usb_ep0tx_clear_stall(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP0TX_CTL &= ( ~USB_EP_STALL_MSK); 
}

static inline void csp_usb_ep0tx_toggle(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP0TX_CTL |= (USB_EP_TOGGLE_EN << USB_EP_TOGGLE_POS); 
	else
		ptUsbBase->EP0TX_CTL &= (~USB_EP_TOGGLE_MSK); 
}

static inline void csp_usb_ep0tx_epie(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP0TX_CTL |= (USB_EP_IE_EN << USB_EP_IE_POS); 
	else
		ptUsbBase->EP0TX_CTL &= (~USB_EP_IE_MSK); 
}

static inline void csp_usb_ep0tx_epen(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP0TX_CTL |= (USB_EP_EN_EN << USB_EP_EN_POS); 
	else
		ptUsbBase->EP0TX_CTL &= (~USB_EP_EN_MSK); 
}

static inline void csp_usb_ep0tx_cnt(csp_usb_t *ptUsbBase, uint16_t hwCnt)
{
	ptUsbBase->EP0TX_CNT = hwCnt; 
}

static inline uint16_t csp_usb_ep0tx_get_cnt(csp_usb_t *ptUsbBase)
{
	return ptUsbBase->EP0TX_CNT; 
}

//ep1tx 
static inline void csp_usb_ep1tx_txen(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP1TX_CTL |= (USB_EP_RXEN_EN << USB_EP_RXEN_POS); 
}

static inline void csp_usb_ep1tx_stall(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP1TX_CTL |= (USB_EP_STALL_EN << USB_EP_STALL_POS); 
}

static inline void csp_usb_ep1tx_clear_stall(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP1TX_CTL &= ( ~USB_EP_STALL_MSK); 
}

static inline void csp_usb_ep1tx_toggle(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP1TX_CTL |= (USB_EP_TOGGLE_EN << USB_EP_TOGGLE_POS); 
	else
		ptUsbBase->EP1TX_CTL &= (~USB_EP_TOGGLE_MSK); 
}

static inline void csp_usb_ep1tx_epie(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP1TX_CTL |= (USB_EP_IE_EN << USB_EP_IE_POS); 
	else
		ptUsbBase->EP1TX_CTL &= (~USB_EP_IE_MSK); 
}

static inline void csp_usb_ep1tx_epen(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP1TX_CTL |= (USB_EP_EN_EN << USB_EP_EN_POS); 
	else
		ptUsbBase->EP1TX_CTL &= (~USB_EP_EN_MSK); 
}

static inline void csp_usb_ep1tx_cnt(csp_usb_t *ptUsbBase, uint16_t hwCnt)
{
	ptUsbBase->EP1TX_CNT = hwCnt; 
}

static inline uint16_t csp_usb_ep1tx_get_cnt(csp_usb_t *ptUsbBase)
{
	return ptUsbBase->EP1TX_CNT; 
}

//ep2tx 
static inline void csp_usb_ep2tx_txen(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP2TX_CTL |= (USB_EP_RXEN_EN << USB_EP_RXEN_POS); 
}

static inline void csp_usb_ep2tx_stall(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP2TX_CTL |= (USB_EP_STALL_EN << USB_EP_STALL_POS); 
}

static inline void csp_usb_ep2tx_clear_stall(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP2TX_CTL &= ( ~USB_EP_STALL_MSK); 
}

static inline void csp_usb_ep2tx_toggle(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP2TX_CTL |= (USB_EP_TOGGLE_EN << USB_EP_TOGGLE_POS); 
	else
		ptUsbBase->EP2TX_CTL &= (~USB_EP_TOGGLE_MSK); 
}

static inline void csp_usb_ep2tx_epie(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP2TX_CTL |= (USB_EP_IE_EN << USB_EP_IE_POS); 
	else
		ptUsbBase->EP2TX_CTL &= (~USB_EP_IE_MSK); 
}

static inline void csp_usb_ep2tx_epen(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP2TX_CTL |= (USB_EP_EN_EN << USB_EP_EN_POS); 
	else
		ptUsbBase->EP2TX_CTL &= (~USB_EP_EN_MSK); 
}

static inline void csp_usb_ep2tx_cnt(csp_usb_t *ptUsbBase, uint16_t hwCnt)
{
	ptUsbBase->EP2TX_CNT = hwCnt; 
}

static inline uint16_t csp_usb_ep2tx_get_cnt(csp_usb_t *ptUsbBase)
{
	return ptUsbBase->EP2TX_CNT; 
}

//ep3tx 
static inline void csp_usb_ep3tx_txen(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP3TX_CTL |= (USB_EP_RXEN_EN << USB_EP_RXEN_POS); 
}

static inline void csp_usb_ep3tx_stall(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP3TX_CTL |= (USB_EP_STALL_EN << USB_EP_STALL_POS); 
}

static inline void csp_usb_ep3tx_clear_stall(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP3TX_CTL &= ( ~USB_EP_STALL_MSK); 
}

static inline void csp_usb_ep3tx_toggle(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP3TX_CTL |= (USB_EP_TOGGLE_EN << USB_EP_TOGGLE_POS); 
	else
		ptUsbBase->EP3RX_CTL &= (~USB_EP_TOGGLE_MSK); 
}

static inline void csp_usb_ep3tx_epie(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP3TX_CTL |= (USB_EP_IE_EN << USB_EP_IE_POS); 
	else
		ptUsbBase->EP3TX_CTL &= (~USB_EP_IE_MSK); 
}

static inline void csp_usb_ep3tx_epen(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP3TX_CTL |= (USB_EP_EN_EN << USB_EP_EN_POS); 
	else
		ptUsbBase->EP3TX_CTL &= (~USB_EP_EN_MSK); 
}

static inline void csp_usb_ep3tx_cnt(csp_usb_t *ptUsbBase, uint16_t hwCnt)
{
	ptUsbBase->EP3TX_CNT = hwCnt; 
}

static inline uint16_t csp_usb_ep3tx_get_cnt(csp_usb_t *ptUsbBase)
{
	return ptUsbBase->EP3TX_CNT; 
}

//ep4tx 
static inline void csp_usb_ep4tx_txen(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP4TX_CTL |= (USB_EP_RXEN_EN << USB_EP_RXEN_POS); 
}

static inline void csp_usb_ep4tx_stall(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP4TX_CTL |= (USB_EP_STALL_EN << USB_EP_STALL_POS); 
}

static inline void csp_usb_ep4tx_clear_stall(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP4TX_CTL &= ( ~USB_EP_STALL_MSK); 
}

static inline void csp_usb_ep4tx_toggle(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP4TX_CTL |= (USB_EP_TOGGLE_EN << USB_EP_TOGGLE_POS); 
	else
		ptUsbBase->EP4TX_CTL &= (~USB_EP_TOGGLE_MSK); 
}

static inline void csp_usb_ep4tx_epie(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP4TX_CTL |= (USB_EP_IE_EN << USB_EP_IE_POS); 
	else
		ptUsbBase->EP4TX_CTL &= (~USB_EP_IE_MSK); 
}

static inline void csp_usb_ep4tx_epen(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP4TX_CTL |= (USB_EP_EN_EN << USB_EP_EN_POS); 
	else
		ptUsbBase->EP4TX_CTL &= (~USB_EP_EN_MSK); 
}

static inline void csp_usb_ep4tx_cnt(csp_usb_t *ptUsbBase, uint16_t hwCnt)
{
	ptUsbBase->EP4TX_CNT = hwCnt; 
}

static inline uint16_t csp_usb_ep4tx_get_cnt(csp_usb_t *ptUsbBase)
{
	return ptUsbBase->EP4TX_CNT; 
}

//ep5tx 
static inline void csp_usb_ep5tx_txen(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP5TX_CTL |= (USB_EP_RXEN_EN << USB_EP_RXEN_POS); 
}

static inline void csp_usb_ep5tx_stall(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP5TX_CTL |= (USB_EP_STALL_EN << USB_EP_STALL_POS); 
}

static inline void csp_usb_ep5tx_clear_stall(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP5TX_CTL &= ( ~USB_EP_STALL_MSK); 
}

static inline void csp_usb_ep5tx_toggle(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP5TX_CTL |= (USB_EP_TOGGLE_EN << USB_EP_TOGGLE_POS); 
	else
		ptUsbBase->EP5TX_CTL &= (~USB_EP_TOGGLE_MSK); 
}

static inline void csp_usb_ep5tx_epie(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP5TX_CTL |= (USB_EP_IE_EN << USB_EP_IE_POS); 
	else
		ptUsbBase->EP5TX_CTL &= (~USB_EP_IE_MSK); 
}

static inline void csp_usb_ep5tx_epen(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP5TX_CTL |= (USB_EP_EN_EN << USB_EP_EN_POS); 
	else
		ptUsbBase->EP5TX_CTL &= (~USB_EP_EN_MSK); 
}

static inline void csp_usb_ep5tx_cnt(csp_usb_t *ptUsbBase, uint16_t hwCnt)
{
	ptUsbBase->EP5TX_CNT = hwCnt; 
}

static inline uint16_t csp_usb_ep5tx_get_cnt(csp_usb_t *ptUsbBase)
{
	return ptUsbBase->EP5TX_CNT; 
}

//ep6tx 
static inline void csp_usb_ep6tx_txen(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP6TX_CTL |= (USB_EP_RXEN_EN << USB_EP_RXEN_POS); 
}

static inline void csp_usb_ep6tx_stall(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP6TX_CTL |= (USB_EP_STALL_EN << USB_EP_STALL_POS); 
}

static inline void csp_usb_ep6tx_clear_stall(csp_usb_t *ptUsbBase)
{
	ptUsbBase->EP6TX_CTL &= ( ~USB_EP_STALL_MSK); 
}

static inline void csp_usb_ep6tx_toggle(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP6TX_CTL |= (USB_EP_TOGGLE_EN << USB_EP_TOGGLE_POS); 
	else
		ptUsbBase->EP6TX_CTL &= (~USB_EP_TOGGLE_MSK); 
}

static inline void csp_usb_ep6tx_epie(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP6TX_CTL |= (USB_EP_IE_EN << USB_EP_IE_POS); 
	else
		ptUsbBase->EP6TX_CTL &= (~USB_EP_IE_MSK); 
}

static inline void csp_usb_ep6tx_epen(csp_usb_t *ptUsbBase, bool bEnable)
{
	if(bEnable)
		ptUsbBase->EP6TX_CTL |= (USB_EP_EN_EN << USB_EP_EN_POS); 
	else
		ptUsbBase->EP6TX_CTL &= (~USB_EP_EN_MSK); 
}

static inline void csp_usb_ep6tx_cnt(csp_usb_t *ptUsbBase, uint16_t hwCnt)
{
	ptUsbBase->EP6TX_CNT = hwCnt; 
}

static inline uint16_t csp_usb_ep6tx_get_cnt(csp_usb_t *ptUsbBase)
{
	return ptUsbBase->EP6TX_CNT; 
}




#endif
