/***********************************************************************//** 
 * \file  sys_clk.c
 * \brief  system clock management for cpu clock(HCLK) and peri clock(PCLK)
 * \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-8-10 <td>V0.0  <td>WNN   <td>initial
 * <tr><td> 2021-5-13 <td>V0.0  <td>ZJY   <td>initial
 * </table>
 * *********************************************************************
*/
#include <stdint.h>
#include <sys_clk.h>
#include <pin.h>
#include "board_config.h"

#include <csp.h>


//extern system_clk_config_t g_tSystemClkConfig[];

///to match the real div to reg setting
const uint32_t g_wHclkDiv[] = {
	1, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 24, 32, 36, 64, 128, 256
};

static uint32_t get_hclk(void)
{
	uint32_t tRslt;
	tRslt = g_tClkConfig.wFreq/g_tClkConfig.eSdiv;
	return (tRslt);
}
/** \brief sysctem clock (HCLK) configuration
 * 
 *  To set CPU frequence according to g_tClkConfig
 * 
 *  \param[in] none.
 *  \return csi_error_t.
 */ 
csi_error_t csi_sysclk_config_test(void)
{	csi_error_t ret = CSI_OK;
	uint8_t byFreqIdx = 0;
	uint32_t wFreq;
	uint32_t wHFreq;
	csi_clk_src_e eSrc;
	uint8_t byFlashLp = 0;
	wFreq = g_tClkConfig.wFreq;
	eSrc = g_tClkConfig.eClkSrc;
	wHFreq = get_hclk();
	
//	csp_ifc_set_speed(IFC_REG_BASE, get_hclk());
	IFC->CEDR = IFC_CLKEN;
	IFC->MR = IFC->MR & (~(HIGH_SPEED|PF_WAIT3));
	if (wHFreq > 24000000)
		IFC->MR |= HIGH_SPEED | PF_WAIT2;
    else if (wHFreq >= 16000000) 
		IFC->MR |= HIGH_SPEED | PF_WAIT1;	
	
	switch (eSrc)
	{
		case (SRC_ISOSC): 	
			ret = csi_isosc_enable();
			byFlashLp = 1;
			break;
		case (SRC_IMOSC):	
			switch (wFreq) 	
			{
				case (IMOSC_5M_VALUE):   byFreqIdx = 0;
					break;
				case (IMOSC_4M_VALUE):   byFreqIdx = 1;
					break;
				case (IMOSC_2M_VALUE):   byFreqIdx = 2;
					break;
				case (IMOSC_131K_VALUE): byFreqIdx = 3;
					break;
				default: ret = CSI_ERROR;	
					break;
			}
			ret = csi_imosc_enable(byFreqIdx);
			if (wFreq == IM_131K)
				byFlashLp = 1;
			break;
		case (SRC_EMOSC):	
			//csi_pin_set_mux(PA03, PA03_OSC_XI);
			//csi_pin_set_mux(PA04, PA04_OSC_XO);
			if (wFreq == EMOSC_32K_VALUE)
				csp_set_em_lfmd(SYSCON, 1);
			ret = csi_emosc_enable(wFreq);
			break;
		case (SRC_HFOSC):	
			switch (wFreq) 	
			{
				case (HFOSC_48M_VALUE): byFreqIdx = 0;
					break;
				case (HFOSC_24M_VALUE): byFreqIdx = 1;
					break;
				case (HFOSC_12M_VALUE): byFreqIdx = 2;
					break;
				case (HFOSC_6M_VALUE):  byFreqIdx = 3;
					break;
				default: ret = CSI_ERROR;	
					break;
			}
			ret = csi_hfosc_enable(byFreqIdx);
			break;
		default: 
			break;
	}
	
	csp_set_bc_sdiv(SYSCON, g_tClkConfig.eSdiv);
	csp_set_clksrc(SYSCON, eSrc);
	
//	csp_eflash_lpmd_enable(SYSCON, (bool)byFlashLp);
	
	csp_set_bc_pdiv(SYSCON, g_tClkConfig.ePdiv);
	
	//update wSclk and wPclk in g_tClkConfig
	g_tClkConfig.wSclk = wHFreq;
	g_tClkConfig.wPclk = g_tClkConfig.wSclk/(0x1<<g_tClkConfig.ePdiv);
	return ret;
}

/** \brief apt_pll_config: config div_m,nul,ckp_div and ckq_div
 * 
 *  \param[in] eSrc: source clock \ref  csi_clk_src_e
 *  \param[in] wFreq:  pll clk freq 
 *  \return csi_error_t.
 */	
static csi_error_t apt_pll_config(csi_clk_src_e eSrc,uint32_t wFreq)
{
	
	csi_pll_disable();
	
	if(eSrc == SRC_HF_PLL)
		csp_pll_set_clk_src(SYSCON, PLL_CLK_SEL_HFOSC);	
	else if(eSrc == SRC_EM_PLL)
		csp_pll_set_clk_src(SYSCON, PLL_CLK_SEL_EMOSC);	
	else
		 return CSI_ERROR;
		
	csp_pll_set_div_m(SYSCON, g_tPllClkConfig.byDivM);
	csp_pll_set_nul(SYSCON, g_tPllClkConfig.byNul);
	csp_pll_set_ckp_div(SYSCON, g_tPllClkConfig.byCkp_Div);
	csp_pll_set_ckq_div(SYSCON, g_tPllClkConfig.byCkq_Div);
	csp_pll_clk_enable(SYSCON);
	csi_pll_enable();
	
	return CSI_OK;
}

/** \brief sysctem clock (HCLK) configuration
 * 
 *  To set CPU frequence according to g_tClkConfig
 * 
 *  \param[in] none.
 *  \return csi_error_t.
 */ 
csi_error_t csi_sysclk_config(csi_clk_config_t tClkCfg)
{	
	csi_error_t ret = CSI_OK;
	uint8_t byFreqIdx = 0;
	uint32_t wFreq,wTargetSclk;
	csi_clk_src_e  eSrc;
	csi_sclk_sel_e eSckSel = SEL_IMOSC;
	uint8_t byFlashLp = 0;
	wFreq = tClkCfg.wFreq;
	
	wTargetSclk = wFreq/g_wHclkDiv[tClkCfg.eSdiv];
	eSrc = tClkCfg.eClkSrc;
//	csi_imosc_enable(byFreqIdx);		 //enable IM_5M
//	csp_set_clksrc(SYSCON, SEL_IMOSC);
//	csp_eflash_lpmd_disable(SYSCON);					//disable Flash LP Mode					
	
	switch (eSrc)
	{
		case (SRC_ISOSC): 
			eSckSel = SEL_ISOSC;
			csi_isosc_enable();
			byFlashLp = 1;
			break;
		case (SRC_IMOSC):	
			eSckSel = SEL_IMOSC;
			switch (wFreq) 	
			{
				case (IMOSC_5M_VALUE):   byFreqIdx = 0;
					break;
				case (IMOSC_4M_VALUE):   byFreqIdx = 1;
					break;
				case (IMOSC_2M_VALUE):   byFreqIdx = 2;
					break;
				case (IMOSC_131K_VALUE): byFreqIdx = 3;
					break;
				default: ret = CSI_ERROR;	
					break;
			}
			csi_imosc_enable(byFreqIdx);
			if (wFreq == IM_131K)
				byFlashLp = 1;
			break;
		case (SRC_EMOSC):
			eSckSel = SEL_EMOSC;
			if (wFreq == EMOSC_32K_VALUE)
				csp_set_em_lfmd(SYSCON,EM_SEL_LOWSPEED);
			ret = csi_emosc_enable(wFreq);
			break;
		case (SRC_HFOSC):	
			eSckSel = SEL_HFOSC;
			switch (wFreq) 	
			{
				case (HFOSC_24M_VALUE): byFreqIdx = 0;
					break;
				case (HFOSC_12M_VALUE): byFreqIdx = 1;
					break;
				case (HFOSC_6M_VALUE):  byFreqIdx = 2;
					break;
				case (HFOSC_3M_VALUE):  byFreqIdx = 3;
					break;
				default: ret = CSI_ERROR;
					return ret;
					break;
			}
			csi_hfosc_enable(byFreqIdx);
			break;
			
		case (SRC_HF_PLL):
			eSckSel = SEL_PLL;
			switch (g_tPllClkConfig.eClkSel) 	
			{
				case (PLL_SEL_HFOSC_24M): byFreqIdx = 0;
					wFreq = HFOSC_24M_VALUE;
					break;
				case (PLL_SEL_HFOSC_12M): byFreqIdx = 1;
					wFreq = HFOSC_12M_VALUE;
					break;
				case (PLL_SEL_HFOSC_6M):  byFreqIdx = 2;
					wFreq = HFOSC_6M_VALUE;
					break;
				default: ret = CSI_ERROR;
					return ret;
					break;
			}
			csi_hfosc_enable(byFreqIdx);
			break;
		case (SRC_EM_PLL):
			eSckSel = SEL_PLL;
			wFreq = EMOSC_24M_VALUE;
			ret = csi_emosc_enable(wFreq);
			break;
		case(SRC_ESOSC):
			eSckSel = SEL_ESOSC;
			csi_esosc_enable();
			byFlashLp = 1;
			break;
		default: 
			break;
	}
	
	if(eSrc >= SRC_HF_PLL)  //config and enable pll register
	{
		apt_pll_config(eSrc,wFreq);  
		
		wFreq = wFreq /(g_tPllClkConfig.byDivM+1) * g_tPllClkConfig.byNul / (g_tPllClkConfig.byCkp_Div+1);
		wTargetSclk = wFreq/g_wHclkDiv[tClkCfg.eSdiv];
	}

	IFC->CEDR = IFC_CLKEN;
	if (wTargetSclk > 80000000) {
		csp_ifc_flash_set_speed_wait(IFC, HIGH_SPEED,PF_WAIT4);
	}
	else if(wTargetSclk > 64000000) {
		csp_ifc_flash_set_speed_wait(IFC, HIGH_SPEED,PF_WAIT3);
	}
	else if(wTargetSclk > 48000000) {
		csp_ifc_flash_set_speed_wait(IFC, HIGH_SPEED,PF_WAIT2);
	}
	else if(wTargetSclk > 16000000) {
		csp_ifc_flash_set_speed_wait(IFC, HIGH_SPEED,PF_WAIT1);
	}
	else if(wTargetSclk > 8000000) {
		csp_ifc_flash_set_speed_wait(IFC, HIGH_SPEED,PF_WAIT0);
	}
	else{
		csp_ifc_flash_set_speed_wait(IFC, LOW_SPEED,PF_WAIT0);
	}
	csp_set_bc_sdiv(SYSCON, tClkCfg.eSdiv);
	csp_set_clksrc(SYSCON, eSckSel);
	
//	if(byFlashLp)
//		csp_eflash_lpmd_enable(SYSCON);
	
	csp_set_bc_pdiv(SYSCON, tClkCfg.ePdiv);
	
	//update wSclk and wPclk in g_tClkConfig
	g_tClkConfig.wFreq = wTargetSclk * g_wHclkDiv[tClkCfg.eSdiv];
	g_tClkConfig.wSclk = wTargetSclk;
	g_tClkConfig.wPclk = g_tClkConfig.wSclk/(0x1<<tClkCfg.ePdiv);
	return ret;
}

/** \brief Clock output configuration
 * 
 *  \param[in] eCloSrc: source to output
 *  \param[in] byCloDiv: actual clo divider  =  2*（byCloDiv+1）
 *  \param[in] tPin: output pin
 *  \return csi_error_t.
 */
csi_error_t csi_clo_config(clo_src_e eCloSrc, uint8_t byCloDiv, pin_name_e ePin)
{ 	
	csi_error_t ret = CSI_OK;
	switch (ePin)
	{
		case (PA2):
			csi_pin_set_mux(PA2, PA2_CLO);
			break;
		case (PD3):
			csi_pin_set_mux(PD3, PD3_CLO);
			break;
		case (PD4):
			csi_pin_set_mux(PD4, PD4_CLO);
			break;
		default:
			ret = CSI_ERROR;
			break;
	}
	
	csp_set_clo_src(SYSCON, eCloSrc);
	csp_set_clo_div(SYSCON, byCloDiv);
	return ret;
}

/** \brief prei clk enable in SYSCON level
 *
 *  \param[in] wModule: module name
 *  \return none
 */
void soc_clk_enable(int32_t wModule)
{
    //TODO
	if(wModule < 32U)
		csp_bc_pcerl0_clk_en(SYSCON, (uint32_t)wModule);
	else
		csp_bc_pcerh0_clk_en(SYSCON, (uint32_t)wModule - 32U);
}

/** \brief prei clk disable in SYSCON level
 *
 *  \param[in] wModule: module name
 *  \return none
 */
void soc_clk_disable(int32_t wModule)
{
    //TODO
	if(wModule < 32U)
		csp_pder0_clk_dis(SYSCON, (uint32_t)wModule);
	else
		csp_pder1_clk_dis(SYSCON, (uint32_t)wModule - 32U);
}

/** \brief to get SCLK frequence according to the current reg content
 *  g_tClkConfig.wSclk will be updated after excuting this function
 *  \param[in] none.
 *  \return csi_error_t.
 */ 
uint32_t csi_get_sclk_freq(void)
{	
	//csi_error_t ret = CSI_OK;
	csi_clk_src_e eClkSrc;
	uint8_t  byHclkDiv;
	uint32_t wHfoFreq;
	uint32_t wImoFreq;
	
    eClkSrc = ((csi_clk_src_e) csp_get_clksrc(SYSCON));
	switch(eClkSrc)
	{ 	case (SRC_ISOSC): 	
			g_tClkConfig.wSclk = ISOSC_VALUE;
			break;
		case (SRC_EMOSC): 	
			g_tClkConfig.wSclk = EMOSC_VALUE;
			break;
		case (SRC_IMOSC):	
			wImoFreq = csp_get_imosc_fre(SYSCON);
			switch (wImoFreq)
			{
				case (0): 
					g_tClkConfig.wSclk = IMOSC_5M_VALUE;
					break;
				case (1): 
					g_tClkConfig.wSclk = IMOSC_4M_VALUE;
					break;
				case (2): 
					g_tClkConfig.wSclk = IMOSC_2M_VALUE;	
					break;
				case (3): 
					g_tClkConfig.wSclk = IMOSC_131K_VALUE;	
					break;
				default: 
					return CSI_ERROR;	
					break;
			}
			break;
		case  (SRC_HFOSC):	
			wHfoFreq =  csp_get_hfosc_fre(SYSCON);
			switch (wHfoFreq)
			{
				case (0): 
					g_tClkConfig.wSclk = HFOSC_48M_VALUE;
					break;
				case (1): 
					g_tClkConfig.wSclk = HFOSC_24M_VALUE;
					break;
				case (2): 
					g_tClkConfig.wSclk = HFOSC_12M_VALUE;	
					break;
				case (3): 
					g_tClkConfig.wSclk = HFOSC_6M_VALUE;	
					break;
				default:  
					return CSI_ERROR;	
					break;
			}
			break;
		default:
			return CSI_ERROR;
			break;
	}
	byHclkDiv = csp_get_hclk_div(SYSCON);

	
	//g_wSystemClk = g_wSystemClk / g_wHclkDiv[byHclkDiv];
	g_tClkConfig.wSclk = g_tClkConfig.wSclk/g_wHclkDiv[byHclkDiv];
	
	return g_tClkConfig.wSclk;
}

/** \brief To get PCLK frequence according to the current reg content.
 *  g_tClkConfig.wPclk will be updated after excuting this function.
 *  \param[in] none.
 *  \return csi_error_t.
 */ 
uint32_t csi_get_pclk_freq(void)
{
    uint32_t wDiv, wPdiv = 1;
	wDiv = csp_get_bc_pdiv(SYSCON);
	if(wDiv == 0)
		wPdiv = 1;
	else if(wDiv == 1)
		wPdiv = 2;
	else if(wDiv & 0x08)
		wPdiv = 16;
	else if(wDiv & 0x04)
		wPdiv = 8;
	else if(wDiv & 0x02)
		wPdiv = 4;
	
	g_tClkConfig.wPclk = g_tClkConfig.wSclk / wPdiv;
	return g_tClkConfig.wPclk;
}

/** \brief To get CORET frequence.
 *  Make sure to excute soc_get_cpu_freq() after clock block changing
 *  \param[in] none.
 *  \return g_wSystemClk.
 */ 
uint32_t soc_get_coret_freq(void)
{
/*	switch ((CORETIMER->CTRL & 0x4) >> 2)
	{
		case 0: return g_tClkConfig.wSclk/8;
			break;
		case 1: return g_tClkConfig.wSclk;
			break;
		default:
			return g_tClkConfig.wSclk;
			break;
	}*/
	return g_tClkConfig.wSclk;
}
/** \brief to set clock status in PM mode 
 *  when IWDT is enabled, trying to stop ISOSC in stop mode would be invalid
 *  refer to GCER in SYSCON chapter for detailed description
 *  \param[in] eClk: clock to be configured
 *  \param[in] bEnable: enable or disable
 *  \return none.
 */ 
void soc_clk_pm_enable(clk_pm_e eClk, bool bEnable)
{
	if(bEnable)
		csp_clk_pm_enable(SYSCON, eClk);
	else
		csp_clk_pm_disable(SYSCON, eClk);
}
/** \brief       Soc get bt frequence.
 *  \param[in]   byIdx: id of bt
 *  \return      coret frequence
*/
uint32_t soc_get_bt_freq(uint8_t byIdx)
{
	csp_bt_t *bt_base  = NULL;
	switch(byIdx)
	{
		case 0:
			bt_base = (csp_bt_t *)APB_BT0_BASE;
			break;
		case 1:
			bt_base = (csp_bt_t *)APB_BT1_BASE;
			break;
		default:
			return csi_get_pclk_freq();
	}
	
	return csi_get_pclk_freq()/(csp_bt_get_pscr(bt_base) + 1);
}