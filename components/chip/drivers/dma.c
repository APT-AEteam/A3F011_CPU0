/***********************************************************************//** 
 * \file  dma.c
 * \brief  DMA description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-12-23 <td>V0.0  <td>ZJY   <td>initial
 * </table>
 * *********************************************************************
*/

/* Includes ---------------------------------------------------------------*/
#include <sys_clk.h>
#include <drv/irq.h>
#include <drv/dma.h>
#include "csp_dma.h"

/* Private macro-----------------------------------------------------------*/
/* externs function--------------------------------------------------------*/
/* externs variablesr------------------------------------------------------*/
/* Private variablesr------------------------------------------------------*/
static uint16_t s_hwDmaMsg[2]	= {0, 0};

/** \brief dma interrupt handle function
 * 
 *  \param[in] eIntMsg: dma interrupt message
 *  \param[in] byPost: dma interrupt message post
 *  \return none
 */ 
static uint8_t apt_dma_post_msg(csp_dma_t *ptDmaBase, csi_dma_int_msg_e eIntMsg, uint8_t byPost)
{
	uint8_t byIdx = csi_get_dma_idx(ptDmaBase);
	
	if(0 == (s_hwDmaMsg[byIdx] & eIntMsg))
	{
		if(byPost)
			s_hwDmaMsg[byIdx] |= eIntMsg;
		return true;
	}
	else
		return false;
}
/** \brief uart interrupt handle function
 * 
 *  \param[in] ptUartBas: pointer of uart register structure
 *  \param[in] byIdx: uart id number(0~2)
 *  \return none
 */ 
__attribute__((weak)) void dma_irqhandler(csp_dma_t *ptDmaBase)
{
	volatile uint32_t wIsr = csp_dma_get_isr(ptDmaBase) & 0x003f003f;
	
	switch(wIsr)
	{
		//LTCIT
		case DMA_CH0_LTCIT_SR:
		case DMA_CH1_LTCIT_SR:
		case DMA_CH2_LTCIT_SR:
		case DMA_CH3_LTCIT_SR:
		case DMA_CH4_LTCIT_SR:
		case DMA_CH5_LTCIT_SR:
			csp_dma_clr_isr(ptDmaBase, (uint8_t)wIsr);		//clear LTCIT status
			apt_dma_post_msg(ptDmaBase, wIsr, 1);			//post LTCIT interrupt message
			break;
		
		//TCIT 
		case DMA_CH0_TCIT_SR:
		case DMA_CH1_TCIT_SR:
		case DMA_CH2_TCIT_SR:
		case DMA_CH3_TCIT_SR:
		case DMA_CH4_TCIT_SR:
		case DMA_CH5_TCIT_SR:
			csp_dma_clr_isr(ptDmaBase, (wIsr >> 16));		//clear LTCIT status
			apt_dma_post_msg(ptDmaBase, (wIsr >> 10), 1);	//post TCIT interrupt message
			break;
		default:
			break;
	}
}
/** \brief get dma idx 
 * 
 *  \param[in] ptDmaBase: pointer of uart register structure
 *  \return dma id number(0~1) or error(0xff)
 */ 
uint8_t csi_get_dma_idx(csp_dma_t *ptDmaBase)
{
	switch((uint32_t)ptDmaBase)
	{
		case AHB_DMA0_BASE:
			return 0;
		case AHB_DMA1_BASE:
			return 1;
		default:
			return 0xff;		//error
	}
}
/** \brief Init dma channel parameter config structure
 * 
 *  \param[in] ptDmaBase: pointer of dma reg structure.
 *  \param[in] eDmaCh: channel num of dma(6 channel: 0->5)
 *  \param[in] ptChCfg: pointer of uart parameter config structure
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_dma_ch_init(csp_dma_t *ptDmaBase, csi_dma_ch_e eDmaCh, csi_dma_ch_config_t *ptChCfg)
{
	csp_dma_t *ptDmaChBase = (csp_dma_t *)DMA_REG_BASE(ptDmaBase, eDmaCh);
	
	if(eDmaCh >= DMA_CH_MAX_NUM)
		return CSI_ERROR;
	
	csp_dma_set_ch_saddr_mode(ptDmaChBase, ptChCfg->bySrcLinc, ptChCfg->bySrcHinc);										//Src addr control mode
	csp_dma_set_ch_daddr_mode(ptDmaChBase, ptChCfg->byDetLinc, ptChCfg->byDetHinc);										//Det addr control mode
	csp_dma_set_ch(ptDmaChBase, ptChCfg->byDataWidth, ptChCfg->byReload, ptChCfg->byTransMode, ptChCfg->byTsizeMode);	//dma ch para config
	csp_dma_set_ch_req(ptDmaChBase, ptChCfg->byReqMode);																//software or hardware request
	
	if(ptChCfg->wInt)
	{
		csp_dma_int_enable(ptDmaChBase, ptChCfg->wInt, ENABLE);		//nable dma xxx interrupt
		csi_irq_enable((uint32_t *)ptDmaBase);							//enable dma irq		
	}
	
	return CSI_OK;	
}
/** \brief dma channel transfer start
 * 
 *  \param[in] ptDmaBase: pointer of dma reg structure.
 *  \param[in] eDmaCh: channel num of dma(6 channel: 0->5)
 *  \param[in] pSrcAddr: src addr of transfer 
 *  \param[in] pDstAddr: dst addr of transfer 
 *  \param[in] wLen: length of transfer 
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_dma_ch_start(csp_dma_t *ptDmaBase, csi_dma_ch_e eDmaCh, void *pSrcAddr, void *pDstAddr, uint32_t wLen)
{
	uint32_t wTranLtc = wLen;
	uint32_t wTranHtc = 0x01;
	csp_dma_t *ptDmaChBase = (csp_dma_t *)DMA_REG_BASE(ptDmaBase, eDmaCh);
	
	if(eDmaCh >= DMA_CH_MAX_NUM)
		return CSI_ERROR;
	
	if(csp_dma_get_crx(ptDmaBase) & DMA_TSIZE_MSK)				//Tsize mode 4byte mode
	{
		if((wLen % 4) == 0)
			wTranLtc = wLen >> 2;  
		else
			wTranLtc = (wLen >> 2) + 1;
	}
	
	if(wTranLtc > 0xfff)								
	{
		wTranHtc = wTranLtc / 0xfff;							//transfer low count and high count
		wTranLtc = wTranLtc % 0xfff;
	}
	
	csp_dma_set_ch_trans_num(ptDmaChBase, wTranLtc, wTranHtc);	//data length
	csp_dma_set_ch_trans_num(ptDmaChBase, wTranHtc, wTranLtc);	//data length switch
	csp_dma_set_ch_src_addr(ptDmaChBase, (uint32_t)pSrcAddr);	//Src addr
	csp_dma_set_ch_dst_addr(ptDmaChBase, (uint32_t)pDstAddr);	//dst addr
	csp_dma_ch_en(ptDmaChBase);									//channel enable
	if(!csp_dma_get_rsrx(ptDmaChBase))
		csp_dma_ch_swtrig(ptDmaChBase);							//sw triger 
	
	return CSI_OK;
}
/** \brief enable/disable dma interrupt 
 * 
 *  \param[in] ptDmaBase: pointer of dma register structure
 *  \param[in] eDmaCh: channel num of dma(6 channel: 0->5)
 *  \param[in] eIntSrc: dma interrupt source
 *  \param[in] bEnable: enable/disable interrupt
 *  \return none
 */
void csi_dma_int_enable(csp_dma_t *ptDmaBase, csi_dma_ch_e eDmaCh, csi_dma_intsrc_e eIntSrc, bool bEnable)
{
	csp_dma_t *ptDmaChBase = (csp_dma_t *)DMA_REG_BASE(ptDmaBase, eDmaCh);
	
	csp_dma_int_enable(ptDmaChBase, eIntSrc, bEnable);
	
	if(bEnable)
		csi_irq_enable((uint32_t *)ptDmaBase);
	else
		csi_irq_disable((uint32_t *)ptDmaBase);
}
/** \brief dma channel transfer stop
 * 
 *  \param[in] ptDmaBase: pointer of dma reg structure.
 *  \param[in] eDmaCh: channel num of dma(6 channel: 0->5)
 *  \return none
 */
void csi_dma_ch_stop(csp_dma_t *ptDmaBase, csi_dma_ch_e eDmaCh)
{
	csp_dma_t *ptDmaChBase = (csp_dma_t *)DMA_REG_BASE(ptDmaBase, eDmaCh);
	csp_dma_ch_stop(ptDmaChBase);
}
/** \brief Software reset dma module
 * 
 *  \param[in] ptDmaBase: pointer of dma reg structure.
 *  \return none
 */ 
void csi_dma_soft_rst(csp_dma_t *ptDmaBase)
{
	csp_dma_soft_rst(ptDmaBase);
}

/** \brief get dma interrupt message and (D0 not)clear message
 * 
 *  \param[in] ptDmaBase: pointer of dma reg structure.
 *  \param[in] eDmaCh: channel num of dma(6 channel: 0->5)
 *  \param[in] bClrEn: clear dma interrupt message enable; ENABLE: clear , DISABLE: Do not clear
 *  \return  bool type true/false
 */ 
bool csi_dma_get_msg(csp_dma_t *ptDmaBase, csi_dma_ch_e eDmaCh, bool bClrEn)
{
	bool bRet = false;
	uint8_t byIdx = csi_get_dma_idx(ptDmaBase);
	
	if(0 != (s_hwDmaMsg[byIdx] & (0x01ul << eDmaCh))) 
	{
		if(bClrEn)
			s_hwDmaMsg[byIdx] &= ~(0x01ul << eDmaCh);
		
		bRet |= true;
	}
	
	if(0 != (s_hwDmaMsg[byIdx] & (0x01ul << (eDmaCh + 6))))
	{
		if(bClrEn)
			s_hwDmaMsg[byIdx] &= ~(0x01ul << (eDmaCh + 6));
		bRet |= true;
	}
	
	return bRet;
}

