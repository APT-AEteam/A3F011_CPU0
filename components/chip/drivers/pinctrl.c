/***********************************************************************//** 
 * \file  pinmux.c
 * \brief  csi pin driver
 * \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-5-13 <td>V0.0 <td>ZJY     <td>adapt for 102x/003
 * </table>
 * *********************************************************************
*/
#include <stdint.h>
#include <stddef.h>
#include <drv/pin.h>

/* Private macro------------------------------------------------------*/
/* externs function---------------------------------------------------*/
/* externs variablesr-------------------------------------------------*/
/* Private variablesr-------------------------------------------------*/

/** \brief set gpio mux function
 * 
 *  \param[in] ePinName: gpio pin name
 *  \return pointer of pin infor
 */ 
static unsigned int *apt_get_pin_name_addr(pin_name_e ePinName)
{
	static unsigned int s_wPinInfor[2];
	
	if(ePinName > PC15)
	{
		s_wPinInfor[0] = AHB_GPIOD_BASE;				
		s_wPinInfor[1] = ePinName - PD0;			
	}
	else if(ePinName > PB15)
	{
		s_wPinInfor[0] = AHB_GPIOC_BASE;				
		s_wPinInfor[1] = ePinName - PC0;				
	}
	else if(ePinName > PA15)
	{
		s_wPinInfor[0] = AHB_GPIOB_BASE;				
		s_wPinInfor[1] = ePinName - PB0;				
	}
	else
	{
		s_wPinInfor[0] = AHB_GPIOA_BASE;				
		s_wPinInfor[1] = ePinName;					
	}	
	
	return s_wPinInfor;
}
/** \brief set gpio exi interrupt trigger 
 * 
 *  \param[in] ptExiBase: pionter of EXI reg structure.
 *  \param[in] eLine: EXI_LINE0~EXI_LINE15
 *  \param[in] eGpioTrg: EXI_IRT,EXI_IFT,
 *  \return none
 */ 
void apt_exi_line_set_edge(csp_exi_t *ptExiBase,csi_exi_line_e eLine, exi_trigger_e eGpioTrg)
{
	uint16_t hwExiLine = (0x01ul << eLine);
	
	ptExiBase->EXIRT &= (~hwExiLine);			//trig edg
	ptExiBase->EXIFT &= (~hwExiLine);
	
	switch(eGpioTrg)
	{
		case EXI_EDGE_IRT:
			ptExiBase->EXIRT |= hwExiLine;
			ptExiBase->EXIFT &= ~hwExiLine;
			break;
		case EXI_EDGE_IFT:
			ptExiBase->EXIFT |= hwExiLine;
			ptExiBase->EXIRT &= ~hwExiLine;
			break;
		case EXI_EDGE_BOTH:
			ptExiBase->EXIRT |= hwExiLine;
			ptExiBase->EXIFT |= hwExiLine;
			break;
		default:
			break;
	}
}

/** \brief set gpio mux function
 * 
 *  \param[in] ePinName: gpio pin name
 *  \param[in] ePinFunc: gpio pin function
 *  \return enone
 */  
void csi_pin_set_mux(pin_name_e ePinName, pin_func_e ePinFunc)
{
	csp_gpio_t *ptGpioBase = NULL;
	unsigned int *pwPinMess = NULL;
	
	//IO REMAP
//	if(ePinFunc == IOMAP)			
//	{
//		csp_syscon_t *ptSysBase = (csp_syscon_t *)APB_SYS_BASE;
//		if(ePinName < PA8)
//			ptSysBase->IOMAP0 = (ptSysBase->IOMAP0 & ~(0x0F << 4*ePinName)) | (ePinName << 4*ePinName);
//		else 
//		{
//			if(ePinName < PB2)
//				ptSysBase->IOMAP1 = (ptSysBase->IOMAP1 & ~(0x0F << 4*(ePinName - 6))) |  ((ePinName - 6) << 4*(ePinName - 6));
//			else 
//				ptSysBase->IOMAP1 = (ptSysBase->IOMAP1 & ~(0x0F << 4*(ePinName - 18))) |  ((ePinName - 18) << 4*(ePinName - 18));
//		}
//	}

	pwPinMess = apt_get_pin_name_addr(ePinName);
	ptGpioBase = (csp_gpio_t *)pwPinMess[0];			//pin addr
	ePinName = (pin_name_e)pwPinMess[1];				//pin
	
	if(ePinName < 8)
		ptGpioBase->CONLR =(ptGpioBase->CONLR & ~(0xF << 4*ePinName)) | (ePinFunc << 4*ePinName);
	else
		ptGpioBase->CONHR =(ptGpioBase->CONHR & ~(0xF << 4*(ePinName-8))) | (ePinFunc << 4*(ePinName-8));	
	
}
/** \brief get gpio mux function
 * 
 *  \param[in] ePinName: gpio pin name
 *  \return value of gpio mux
 */ 
pin_func_e csi_pin_get_mux(pin_name_e ePinName)
{
    uint8_t ret = 0x0f;
	csp_gpio_t *ptGpioBase = NULL;
	unsigned int *pwPinMess = apt_get_pin_name_addr(ePinName);
	
	ptGpioBase = (csp_gpio_t *)pwPinMess[0];			//pin addr
	ePinName = (pin_name_e)pwPinMess[1];				//pin
	
		
	if(ePinName < 8)
		ret = (((ptGpioBase->CONLR) >> 4 * ePinName) & 0x0Ful);
	else
		ret = (((ptGpioBase->CONHR) >> 4 * (ePinName - 8)) & 0x0Ful);
		
    return (pin_func_e)ret;
}
/** \brief set gpio pin pull mode
 * 
 *  \param[in] ePinName: gpio pin name
 *  \param[in] ePullMode: gpio pull mode; pull none/pull up/pull down
 *  \return error code \ref csi_error_t
 */  
csi_error_t csi_pin_pull_mode(pin_name_e ePinName, csi_gpio_pull_mode_e ePullMode)
{
    csi_error_t ret = CSI_OK;
	csp_gpio_t *ptGpioBase = NULL;
	unsigned int *pwPinMess = apt_get_pin_name_addr(ePinName);

	ptGpioBase = (csp_gpio_t *)pwPinMess[0];			//pin addr
	ePinName = (pin_name_e)pwPinMess[1];				//pin
		
	switch(ePullMode)
	{
		case GPIO_PULLNONE:
			csp_gpio_pullnone(ptGpioBase, ePinName);		//pull none
			break;
		case GPIO_PULLUP:
			csp_gpio_pullup(ptGpioBase, ePinName);			//pull up
			break;
		case GPIO_PULLDOWN:
			csp_gpio_pulldown(ptGpioBase, ePinName);		//pull down
			break;
		default:
			ret = CSI_ERROR;
			break;
	}
	
    return ret;
}
/** \brief set gpio pin speed
 * 
 *  \param[in] ePinName: gpio pin name
 *  \param[in] eSpeed: gpio pin speed
 *  \return none
 */  
void csi_pin_speed(pin_name_e ePinName, csi_gpio_speed_e eSpeed)
{
	csp_gpio_t *ptGpioBase = NULL;
	unsigned int *pwPinMess = apt_get_pin_name_addr(ePinName);

	ptGpioBase = (csp_gpio_t *)pwPinMess[0];			//pin addr
	ePinName = (pin_name_e)pwPinMess[1];				//pin
	
	csp_gpio_speed_set(ptGpioBase, ePinName, (uint8_t)eSpeed);
	
}

/** \brief set gpio pin drive level
 * 
 *  \param[in] ePinName: gpio pin name, defined in soc.h.
 *  \param[in] eDrive: gpio pin drive level, week/strong = 0/1
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_pin_drive(pin_name_e ePinName, csi_gpio_drive_e eDrive)
{
	csi_error_t ret = CSI_OK;
	csp_gpio_t *ptGpioBase = NULL;
	unsigned int *pwPinMess = apt_get_pin_name_addr(ePinName);
	
	ptGpioBase = (csp_gpio_t *)pwPinMess[0];			//pin addr
	ePinName = (pin_name_e)pwPinMess[1];				//pin
	
	csp_gpio_drv_set(ptGpioBase, ePinName, (uint8_t)eDrive);
		
    return ret;
}

/** \brief set gpio pin input mode
 * 
 *  \param[in] ePinName: gpio pin name, defined in soc.h.
 *  \param[in] eInputMode:  INPUT_CMOS/INPUT_TTL
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_pin_input_mode(pin_name_e ePinName, csi_gpio_input_mode_e eInputMode)
{

//	csi_error_t ret = CSI_OK;
//	csp_gpio_t *ptGpioBase = NULL;
//	unsigned int *pwPinMess = apt_get_pin_name_addr(ePinName);
//
//	ptGpioBase = (csp_gpio_t *)pwPinMess[0];			//pin addr
//	ePinName = (pin_name_e)pwPinMess[1];				//pin
//	
//	switch (eInputMode)
//	{
//		case (GPIO_INPUT_TTL2):	csp_gpio_ccm_ttl2(ptGpioBase, ePinName);
//			break;
//		case (GPIO_INPUT_TTL1): csp_gpio_ccm_ttl1(ptGpioBase, ePinName);
//			break;
//		case (GPIO_INPUT_CMOS):	csp_gpio_ccm_cmos(ptGpioBase, ePinName);
//			break;
//		default:
//			ret = CSI_ERROR;
//			break;
//	}
//		return ret;
	return CSI_UNSUPPORTED;
}
/** \brief set gpio pin input mode
 * 
 *  \param[in] ePinName: gpio pin name, defined in soc.h.
 *  \param[in] eOutMode: push-pull/open drain
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_pin_output_mode(pin_name_e ePinName, csi_gpio_output_mode_e eOutMode)
{
	csi_error_t ret = CSI_OK;
	csp_gpio_t *ptGpioBase = NULL;
	unsigned int *pwPinMess = apt_get_pin_name_addr(ePinName);

	ptGpioBase = (csp_gpio_t *)pwPinMess[0];			//pin addr
	ePinName = (pin_name_e)pwPinMess[1];				//pin
		
	switch(eOutMode)
	{
		case GPIO_PUSH_PULL:
			csp_gpio_opendrain_dis(ptGpioBase, ePinName);	//push-pull mode
			break;
		case GPIO_OPEN_DRAIN:
			csp_gpio_opendrain_en(ptGpioBase, ePinName);	//open drain mode 
			break;
		case GPIO_CONST_CURR:
			csp_gpio_constcurr_en(ptGpioBase, ePinName);	//constant current
			break;
		case GPIO_CONST_CURR_NONE:
			csp_gpio_constcurr_dis(ptGpioBase, ePinName);
			break;
		default:
			ret = CSI_ERROR;
			break;
	}
	
	return ret; 
}

/** \brief get gpio pin num
 * 
 *  \param[in] ePinName: gpio pin name, defined in soc.h.
 *  \return pin num
 */ 
uint8_t csi_pin_get_num(pin_name_e ePinName)
{
    uint8_t ret = 44;
	unsigned int *pwPinMess = NULL;
	
	pwPinMess = apt_get_pin_name_addr(ePinName);
	ret = (uint8_t)pwPinMess[1];					//gpio pin number
						
    return ret;
}
/** \brief Get the value of  selected pin 
 *  \param[in] ePinName: gpio pin name, defined in soc.h.
 *  \return According to the bit mask, the corresponding pin status is obtained
*/
uint32_t csi_pin_read(pin_name_e ePinName)
{
	csp_gpio_t *ptGpioBase = NULL;
	unsigned int *pwPinMess = apt_get_pin_name_addr(ePinName);
	
	ptGpioBase = (csp_gpio_t *)pwPinMess[0];			//pin addr
	ePinName = (pin_name_e)pwPinMess[1];				//pin
		
	return (csp_gpio_read_input_port(ptGpioBase) & (0x01ul << ePinName));
}

/** \brief Get the value of  selected pin 
 *  \param[in] ePinName: gpio pin name, defined in soc.h.
 *  \return According to the bit mask, the corresponding pin status is obtained
*/
uint8_t apt_pin_exi_line_get_input(pin_name_e ePinName, csi_exi_line_e eLine)
{
	uint8_t byInput;
	unsigned int *pwPinMess = apt_get_pin_name_addr(ePinName);
	
	if(eLine > EXI_LINE7)
	{
		
		if((ePinName == PA0) || (ePinName == PB0) || (ePinName == PA1) || (ePinName == PB1))
		{
			if(eLine < EXI_LINE12)
			{
				if(ePinName == PA0)
					byInput = 0x03;
				else if(ePinName == PB0)
					byInput = 0x01;
			}
			else
			{
				if(ePinName == PA1)
					byInput = 0x03;
				else if(ePinName == PB1)
					byInput = 0x01;
			}
		}
		else
		{
			switch(pwPinMess[0])
			{
				case AHB_GPIOA_BASE:
					byInput = 0x0b;
					break;
				case AHB_GPIOB_BASE:
					byInput = 0x09;
					break;
				case AHB_GPIOC_BASE:
					byInput = 0x07;
					break;
				case AHB_GPIOD_BASE:
					byInput = 0x05;
					break;
				default:
					byInput = 0x0f;
					break;
			}
		}
	}
	else
	{
		switch(pwPinMess[0])
		{
			case AHB_GPIOA_BASE:
				byInput = 0x07;
				break;
			case AHB_GPIOB_BASE:
				byInput = 0x05;
				break;
			case AHB_GPIOC_BASE:
				byInput = 0x03;
				break;
			case AHB_GPIOD_BASE:
				byInput = 0x01;
				break;
			default:
				byInput = 0x0f;
				break;
		}
	}
	
	return byInput;
}

/** \brief exi line group select
 * 
 *  \param[in] exi line: exi line; EXI_LINE0~15
 *  \param[in] eGroup: \ref csi_exi_line_grp_e 
 *  \param[in] ePinName: pio pin name, defined in soc.h.
 *  \return none
 */ 
csi_error_t csi_exi_line_set_group(csi_exi_line_e eLine, csi_exi_line_grp_e eGroup, pin_name_e ePinName)
{
	uint8_t byInput = 0x0f;
	
	byInput = apt_pin_exi_line_get_input(ePinName, eLine);
	if(byInput == 0x0f)
		return CSI_ERROR;
	csp_exi_line_set_grp(EXI, eLine, eGroup, byInput);

	return CSI_OK;
}

/** \brief exi line irq mode config
 * 
 *  \param[in] eLine: exi line; EXI_LINE0~15
 *  \param[in] eMode: or/and \ref csi_exi_line_mode_e
 *  \param[in] eEdge: rising/falling/both
 *  \return none
 */ 
void csi_exi_line_irq_mode(csi_exi_line_e eLine, csi_exi_line_mode_e eMode, csi_exi_line_adge_e eEdge)
{
	csp_exi_line_mode(EXI, eLine, eMode);
	apt_exi_line_set_edge(EXI, eLine, eEdge);
}

/** \brief set gpio interrupt group
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] byPinNum: pin0~15
 *  \param[in] eExiGrp:	EXI_IGRP0 ~ EXI_IGRP19
 *  \return none
 */ 
//csi_error_t csi_pin_set_exi_line(pin_name_e ePinName, csi_exi_line_e eLine, csi_exi_line_grp_e eGroup, csi_exi_line_mode_e eMode, csi_exi_line_adge_e eEdge)
//{
//	uint8_t byInput = 0x0f;
//	
//	byInput = apt_pin_exi_line_get_input(ePinName, eLine);
//	if(byInput == 0x0f)
//		return CSI_ERROR;
//	csp_exi_set_linecfg(EXI, eLine, eGroup, eMode,byInput);
//	apt_exi_line_set_edge(EXI,eLine, eEdge);
//	
//	return CSI_OK;
//}
/** \brief exi line irq enable
 * 
 *  \param[in] eLine: exi line; EXI_LINE0~15
 *  \param[in] bEnable: ENABLE OR DISABLE
 *  \return none
 */ 
void csi_exi_line_irq_enable(csi_exi_line_e eLine, bool bEnable)
{
	csp_exi_line_int_enable(EXI, eLine, bEnable);
}
/** \brief config pin irq mode(assign exi group)
 * 
 *  \param[in] ePinName: pin name
 *  \param[in] eExiGrp: exi group; EXI_GRP0 ~EXI_GRP19
 *  \param[in] eTrgEdge: rising edge; falling edge;	both edge;
 *  \return error code \ref csi_error_t
 */ 
//csi_error_t csi_pin_irq_mode(pin_name_e ePinName, csi_exi_grp_e eExiGrp, csi_gpio_irq_mode_e eTrgEdge)
//{
//	csi_error_t ret = CSI_OK;
//	csp_gpio_t *ptGpioBase = NULL;
//	unsigned int *pwPinMess = apt_get_pin_name_addr(ePinName);
//
//	ptGpioBase = (csp_gpio_t *)pwPinMess[0];			//pin addr
//	ePinName = (pin_name_e)pwPinMess[1];				//pin			
//		
//	apt_gpio_intgroup_set(ptGpioBase,ePinName,eExiGrp);					//interrupt group
//	
//	if(eTrgEdge >  GPIO_IRQ_BOTH_EDGE)
//		ret = CSI_ERROR;
//	else
//		apt_exi_trg_edge_set(SYSCON,eExiGrp, eTrgEdge);					//interrupt edge
//	
//	return ret;
//}
/** \brief pin irq enable
 * 
 *  \param[in] ePinName: pio pin name, defined in soc.h.
 *  \param[in] bEnable: ENABLE OR DISABLE
 *  \return error code \ref csi_error_t
 */ 
void csi_pin_irq_enable(pin_name_e ePinName, bool bEnable)
{
	csp_gpio_t *ptGpioBase = NULL;
	unsigned int *ptPinInfo = NULL;
	
	ptPinInfo = apt_get_pin_name_addr(ePinName);
	ptGpioBase = (csp_gpio_t *)ptPinInfo[0];	
	ePinName = (pin_name_e)ptPinInfo[1];
	
	csp_gpio_int_enable(ptGpioBase, ePinName, bEnable);
}
/** \brief pin vic irq enable
 * 
 *  \param[in] eLine: exi line, EXI_LINE0 ~EXI_LINE15
 *  \param[in] bEnable: ENABLE OR DISABLE
 *  \return none
 */ 
void csi_exi_line_vic_irq_enable(csi_exi_line_e eLine, bool bEnable)
{
	uint8_t byIrqNum;
	
	if(eLine < EXI_LINE2)
		byIrqNum = EXI0_IRQ_NUM + eLine;
	else if(eLine < EXI_LINE5)
		byIrqNum = EXI2_IRQ_NUM + eLine - EXI_LINE2;
	else if(eLine == EXI_LINE5)
		byIrqNum = EXI5_IRQ_NUM + eLine - EXI_LINE5;
	else if(eLine < EXI_LINE8)
		byIrqNum = EXI6_IRQ_NUM + eLine - EXI_LINE6;
	else
		byIrqNum = EXI8_IRQ_NUM + eLine - EXI_LINE8;
 	
	if(bEnable)
		csi_vic_enable_irq(byIrqNum);
	else
		csi_vic_disable_irq(byIrqNum);
		
}
/** \brief  gpio pin toggle
 * 
 *  \param[in] ePinName: gpio pin name
 *  \return none
 */
void csi_pin_toggle(pin_name_e ePinName)
{
	uint32_t wDat;
	csp_gpio_t *ptGpioBase = NULL;
	unsigned int *pwPinMess = apt_get_pin_name_addr(ePinName);

	ptGpioBase = (csp_gpio_t *)pwPinMess[0];			//pin addr
	ePinName = (pin_name_e)pwPinMess[1];				//pin			
	
	wDat = (ptGpioBase->ODSR >> ePinName) & 0x01;
	if(wDat) 
		ptGpioBase->CODR = (1ul << ePinName);
	else
		ptGpioBase->SODR = (1ul << ePinName);
	
}

/** \brief  gpio pin set high(output = 1)
 * 
 *  \param[in] ePinName: gpio pin name
 *  \return none
 */
void csi_pin_set_high(pin_name_e ePinName)
{
	csp_gpio_t *ptGpioBase = NULL;
	unsigned int *pwPinMess = apt_get_pin_name_addr(ePinName);

	ptGpioBase = (csp_gpio_t *)pwPinMess[0];			//pin addr
	ePinName = (pin_name_e)pwPinMess[1];				//pin			
	
	csp_gpio_set_high(ptGpioBase, (uint8_t)ePinName);
}

/** \brief   gpio pin set low(output = 0)
 * 
 *  \param[in] ePinName: gpio pin name
 *  \return none
 */
void csi_pin_set_low(pin_name_e ePinName)
{
	csp_gpio_t *ptGpioBase = NULL;
	unsigned int *pwPinMess = apt_get_pin_name_addr(ePinName);
	
	ptGpioBase = (csp_gpio_t *)pwPinMess[0];			//pin addr
	ePinName = (pin_name_e)pwPinMess[1];				//pin		
	
	csp_gpio_set_low(ptGpioBase, (uint8_t)ePinName);
}
/** \brief  set exi as trigger Event(EV0~5) 
 *  \param[in] byTrgOut: output Event select(TRGOUT0~5)
 *  \param[in] eExiTrgSrc: event source (TRGSRC_EXI0~19)
 *  \param[in] byTrgPrd: accumulated EXI events to output trigger 
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_exi_set_evtrg(csi_exi_trgout_e eTrgOut, csi_exi_trgsrc_e eTrgSrc, csi_exi_trgadge_e eTrgAdge)
{
	if(eTrgOut <= EXI_TRGOUT3)
	{
		csp_exi_set_evtrg(EXI, eTrgOut, eTrgSrc);
		
		switch(eTrgAdge)
		{
			case EXI_RISING_EDGE:
				csp_exi_set_trgadge(EXI,eTrgOut,0x02);
				break;
			case EXI_FALLING_EDGE:
				csp_exi_set_trgadge(EXI,eTrgOut,0x01);
				break;
			case EXI_BOTH_EDGE:
				csp_exi_set_trgadge(EXI,eTrgOut,0x03);
				break;
			default:
				return CSI_ERROR;
		}
	}
	else
		return CSI_ERROR;
	
	return CSI_OK;
}

/** \brief exi evtrg output enable/disable
 * 
 *  \param[in] eTrgOut: exi evtrg out port (0~5)
 *  \param[in] bEnable: ENABLE/DISABLE
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_exi_evtrg_enable(csi_exi_trgout_e eTrgOut, bool bEnable)
{
	if(eTrgOut <= EXI_TRGOUT3)
		csp_exi_evtrg_enable(EXI, eTrgOut, bEnable);
		
	return CSI_OK;
}