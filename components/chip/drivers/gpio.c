/***********************************************************************//** 
 * \file  gpio.c
 * \brief  csi gpio driver
 * \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-5-13 <td>V0.0 <td>ZJY     <td>initial
 * </table>
 * *********************************************************************
*/

#include <drv/gpio.h>
#include <drv/irq.h>
#include <drv/pin.h>

/* Private macro------------------------------------------------------*/
/* externs function---------------------------------------------------*/
//extern void apt_gpio_intgroup_set(csp_gpio_t *ptGpioBase, uint8_t byPinNum, gpio_igrp_e eExiGrp);
//extern void apt_exi_trg_edge_set(csp_syscon_t *ptSysconBase,gpio_igrp_e eExiGrp, exi_trigger_e eGpioTrg);

extern void apt_exi_line_set_edge(csp_exi_t *ptExiBase,csi_exi_line_e eLine, exi_trigger_e eGpioTrg);

/* externs variablesr-------------------------------------------------*/
/* Private variablesr-------------------------------------------------*/


/** \brief gpio interrupt handle function
 * 
 *  \param[in] byExiLineNum: exi line num, 0~15
 *  \return none
 */ 
__attribute__((weak)) void gpio_irqhandler(uint8_t byExiLineNum)
{
	volatile uint32_t wExiSta; 
	wExiSta = csp_exi_line_port_get_isr(EXI);
	
	switch((wExiSta & (0x01ul << byExiLineNum)))
	{
		case EXI_LINE0_STATUS:
			break;
		case EXI_LINE1_STATUS:
			break;
		case EXI_LINE2_STATUS:
			break;
		case EXI_LINE3_STATUS:
			break;
		case EXI_LINE4_STATUS:
			break;
		case EXI_LINE5_STATUS:
			break;
		case EXI_LINE6_STATUS:
			break;
		case EXI_LINE7_STATUS:
			break;
		case EXI_LINE8_STATUS:
			break;
		case EXI_LINE9_STATUS:
			break;
		case EXI_LINE10_STATUS:
			break;
		case EXI_LINE11_STATUS:
			break;
		case EXI_LINE12_STATUS:
			break;
		case EXI_LINE13_STATUS:
			break;
		case EXI_LINE14_STATUS:
			break;
		case EXI_LINE15_STATUS:
			break;
		
	}
	csp_exi_line_port_clr_isr(EXI,wExiSta);		//clear interrput 
}

/** \brief get gpio port total number 
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \return gpio port total number(16/6) or error(0xff)
 */ 
static uint8_t apt_gpio_get_port_num(csp_gpio_t *ptGpioBase)
{
	switch((uint32_t)ptGpioBase)
	{
		case AHB_GPIOA_BASE:
		case AHB_GPIOB_BASE:
		case AHB_GPIOC_BASE:
			return 16;
		case AHB_GPIOD_BASE:
			return 6;
		default:
			return 0xff;		//error
	}
}
/** \brief config gpio direction
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \param[in] eDir: pin dir,ouput/input
 *  \return	error code \ref csi_error_t
 */ 
csi_error_t csi_gpio_port_dir(csp_gpio_t *ptGpioBase, uint32_t wPinMask, csi_gpio_dir_e eDir)
{
	csi_error_t ret = CSI_OK;
	uint8_t byDirData = 0x00, i;
	uint8_t byPortNum =  apt_gpio_get_port_num(ptGpioBase);
	
	if(byPortNum > 16)
		return CSI_ERROR;
	
	for(i = 0; i < byPortNum; i++)
	{
		if(wPinMask & 0x01)
		{
			switch(eDir)
			{
				case GPIO_DIR_INPUT:
					byDirData = 0x01;
					break;
				case GPIO_DIR_OUTPUT:
					byDirData = 0x02;
					break;
				case GPIO_DIR_GPD:
					byDirData = 0x00;
					break;
				default:
					ret = CSI_ERROR;
					break;
			}
			
			if(i < 8)
				ptGpioBase->CONLR =(ptGpioBase->CONLR & ~(0xF << 4*i)) | (byDirData << 4*i);
			else
				ptGpioBase->CONHR =(ptGpioBase->CONHR & ~(0xF << 4*(i-8))) | (byDirData << 4*(i-8));	
		}
		wPinMask = (wPinMask >> 1);
	}
	
	return ret;
}
/** \brief config gpio pull or output mode
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \param[in] ePullMode: pin pullnone/pullup/pulldown
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_gpio_port_pull_mode(csp_gpio_t *ptGpioBase, uint32_t wPinMask, csi_gpio_pull_mode_e ePullMode)
{
	csi_error_t	ret = CSI_OK;
	uint8_t i, byPortNum =  apt_gpio_get_port_num(ptGpioBase);	

	if(byPortNum > 16)
		return CSI_ERROR;
		
	for(i = 0; i < byPortNum; i++)
	{
		if(wPinMask & 0x01)
		{
			switch(ePullMode)
			{
				case GPIO_PULLNONE:					
					csp_gpio_pullnone(ptGpioBase, i);			//pull none
					break;
				case GPIO_PULLUP:				
					csp_gpio_pullup(ptGpioBase, i);				//pull up
					break;
				case GPIO_PULLDOWN:			
					csp_gpio_pulldown(ptGpioBase, i);			//pull down
					break;
				default:
					ret = CSI_ERROR;
					break;
			}
		}
		wPinMask = (wPinMask >> 1);
	}
	return ret;
}
 
/** \brief config gpio output mode
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \param[in] eOutMode: pin open drain/push pull(output mode) 
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_gpio_port_output_mode(csp_gpio_t *ptGpioBase, uint32_t wPinMask, csi_gpio_output_mode_e eOutMode)
{
	csi_error_t	ret = CSI_OK;
	uint32_t hwOpdVal = (wPinMask & 0xffff);
	
	switch(eOutMode)
	{
		case GPIO_PUSH_PULL:						//push pull output
			ptGpioBase->OMCR &= ~hwOpdVal;
			break;
		case GPIO_OPEN_DRAIN:						//open drain output
			ptGpioBase->OMCR = (ptGpioBase->OMCR &~hwOpdVal) | hwOpdVal;
			break;
		default:
			ret = CSI_ERROR;
			break;
	}

	return ret;
}
/** \brief config gpio output mode
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \param[in] eInputMode: pin input mode; TTL1/TTL2/COMS
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_gpio_port_input_mode(csp_gpio_t *ptGpioBase, uint32_t wPinMask, csi_gpio_input_mode_e eInputMode)
{
	csi_error_t	ret = CSI_OK;
	uint8_t i, byPortNum =  apt_gpio_get_port_num(ptGpioBase);	

	if(byPortNum > 16)
		return CSI_ERROR;
		
	for(i = 0; i < byPortNum; i++)
	{
		if(wPinMask & 0x01)
		{
			switch(eInputMode)
			{
				case (GPIO_INPUT_TTL2):	csp_gpio_ccm_ttl2(ptGpioBase, i);
					break;
				case (GPIO_INPUT_TTL1): csp_gpio_ccm_ttl1(ptGpioBase, i);
					break;
				case (GPIO_INPUT_CMOS):	csp_gpio_ccm_cmos(ptGpioBase, i);
					break;
				default:
					ret = CSI_ERROR;
				break;
			}
		}
		wPinMask = (wPinMask >> 1);
	}
	
	return ret;
}

/** \brief gpio irq enable
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \param[in] bEnable: true or false
 *  \return none
 */ 
void csi_gpio_port_irq_enable(csp_gpio_t *ptGpioBase, uint32_t wPinMask, bool bEnable)
{
	csp_gpio_port_int_enable(ptGpioBase, wPinMask, bEnable);	//GPIO INT enable Control reg(setting IEER)
}

/** \brief Get input 0f line
 *  \param[in] byLine: line0~line15(0~15)
 *  \return input 
*/
static uint8_t apt_gpio_port_exi_line_get_input(csp_gpio_t *ptGpioBase, uint8_t byLine)
{
	uint8_t byInput;
	
	if(byLine < 8)
	{
		switch((uint32_t)ptGpioBase)
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
				return 0x0f;			//error
		}
	}
	else if(byLine < 16)
	{
		switch((uint32_t)ptGpioBase)
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
				return 0x0f;			//error
		}
	}
	return byInput;
}
/** \brief Get line group config
 *  \param[in] byLine: line0~line15(0~15)
 *  \return byGroup
*/
static uint8_t apt_gpio_port_exi_line_get_group(uint8_t byLine)
{
	uint8_t byGroup;
	
	if(byLine < EXI_LINE4)
		byGroup = 0x01 << byLine;
	else if(byLine < EXI_LINE8)
		byGroup = 0x01 << (byLine - EXI_LINE4);
	else if(byLine < EXI_LINE12)
		byGroup = 0x01 << (byLine - EXI_LINE8);
	else
		byGroup = 0x01 << (byLine - EXI_LINE12);
	
	return byGroup;
}

/** \brief config gpio port exline irq mode
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \param[in] eTrgEdge: rising edge; falling edge;	both edge;
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_exi_line_port_irq_mode(csp_gpio_t *ptGpioBase, uint32_t wPinMask, csi_exi_adge_e eEdge)
{
	uint8_t i, byPortNum =  apt_gpio_get_port_num(ptGpioBase);	
	uint8_t byGroup, byInput;
	
	if((byPortNum > 16))
		return CSI_ERROR;
		
	for(i = 0; i < byPortNum; i++)
	{
		if(wPinMask & 0x01)
		{
			byGroup = apt_gpio_port_exi_line_get_group(i);
			byInput= apt_gpio_port_exi_line_get_input(ptGpioBase, i);
			
			csp_exi_line_set_grp(EXI, i, byGroup, byInput);
			apt_exi_line_set_edge(EXI,i, eEdge);
			csp_exi_line_mode(EXI, i, EXI_LINE_MODE0);
		}
		wPinMask = (wPinMask >> 1);
	}
	
	return CSI_OK;
}
/** \brief gpio port exi line irq enable
 * 
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \param[in] bEnable: ENABLE OR DISABLE
 *  \return none
 */ 
void csi_exi_line_port_irq_enable(uint32_t wPinMask, bool bEnable)
{
	csp_exi_line_port_int_enable(EXI, wPinMask, bEnable);
	csp_exi_line_port_clr_isr(EXI, wPinMask);
}
/** \brief gpio port exi line vic irq enable
 * 
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \param[in] bEnable: ENABLE OR DISABLE
 *  \return none
 */ 
void csi_exi_line_port_vic_irq_enable(uint32_t wPinMask, bool bEnable)
{
	uint8_t i, byIrqNum;
	
	for(i = 0; i < 16; i++)
	{
		if(wPinMask & 0x01)
		{
			if(i < EXI_LINE2)
				byIrqNum = EXI0_IRQ_NUM + i;
			else if(i < EXI_LINE5)
				byIrqNum = EXI2_IRQ_NUM + i - EXI_LINE2;
			else if(i == EXI_LINE5)
				byIrqNum = EXI5_IRQ_NUM + i - EXI_LINE5;
			else if(i < EXI_LINE8)
				byIrqNum = EXI6_IRQ_NUM + i - EXI_LINE6;
			else
				byIrqNum = EXI8_IRQ_NUM + i - EXI_LINE8;
				
			if(bEnable)
				csi_vic_enable_irq(byIrqNum);
			else
				csi_vic_disable_irq(byIrqNum);
			
		}
		wPinMask = (wPinMask >> 1);
	}
}

/** \brief  set gpio toggle
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \return none
 */ 
void csi_gpio_port_toggle(csp_gpio_t *ptGpioBase, uint32_t wPinMask)
{
    CSI_PARAM_CHK_NORETVAL(ptGpioBase);

	uint32_t tmp = csp_gpio_read_output_port(ptGpioBase);
	csp_gpio_write_output_port(ptGpioBase, tmp ^ wPinMask);
}

/** \brief  read gpio status value
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \return value gpio port select wPinMask
 */ 
uint32_t csi_gpio_port_read(csp_gpio_t *ptGpioBase, uint32_t wPinMask)
{
    return csp_gpio_read_input_port(ptGpioBase) & wPinMask;
}
/** \brief  write gpio ouput value
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \param[in] ePinVal: gpio output value;
 *  \return none
 */ 
void  csi_gpio_port_write(csp_gpio_t *ptGpioBase, uint32_t wPinMask, csi_gpio_pin_state_e ePinVal)
{
	uint32_t tmp = csp_gpio_read_output_port(ptGpioBase);
    if (ePinVal == 1) 
        csp_gpio_write_output_port(ptGpioBase, tmp | wPinMask);
    else 
        csp_gpio_write_output_port(ptGpioBase, tmp & (~wPinMask));
}

/** \brief  set gpio ouput high
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \return none
 */ 
void  csi_gpio_port_set_high(csp_gpio_t *ptGpioBase, uint32_t wPinMask)
{
	uint32_t tmp = csp_gpio_read_output_port(ptGpioBase);
	csp_gpio_write_output_port(ptGpioBase, tmp | wPinMask);
}
/** \brief  set gpio ouput low
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \return none
 */ 
void  csi_gpio_port_set_low(csp_gpio_t *ptGpioBase, uint32_t wPinMask)
{
	uint32_t tmp = csp_gpio_read_output_port(ptGpioBase);
	csp_gpio_write_output_port(ptGpioBase, tmp & (~wPinMask));
}


