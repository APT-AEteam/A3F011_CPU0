/***********************************************************************//** 
 * \file  csp_gpio.h
 * \brief  GPIO description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-8-12 <td>V0.0  <td>ZJY   <td>initial
 * <tr><td> 2020-12-20 <td>V0.1  <td>ZJY   <td>modify for 110
 * <tr><td> 2021-1-12 <td>V0.2  <td>ZJY   <td> adapt for 102x/003
 * </table>
 * *********************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CSP_GPIO_H
#define _CSP_GPIO_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <sys_clk.h>
#include "csp_common.h"

#define GPIO_RESET_VALUE  	(0x00000000)

/// \struct csp_gpio_t
/// \brief GPIO Reg Description
typedef struct
{
	__IOM  uint32_t  CONLR;		//0x0000	Control Low Register                
    __IOM  uint32_t  CONHR;     //0x0004	Control High Register                
    __OM   uint32_t  WODR;      //0x0008	Write Output Data Register                         
    __OM   uint32_t  SODR;      //0x000C	Set Output Data (bit-wise) Register  
    __OM   uint32_t  CODR;      //0x0010	Clear Output Data (bit-wise) Register
    __IM   uint32_t  ODSR;      //0x0014	Output Data Status Register          
    __IM   uint32_t  PSDR;      //0x0018	Pin Data Status Register                           
    __OM   uint32_t  FLTEN;     //0x001C    Filtering Enable Control Register
    __IOM  uint32_t  PUDR;      //0x0020	IO Pullup_Pulldown Register          
    __IOM  uint32_t  DSCR;      //0x0024	Output Driving Strength Register     
    __IOM  uint32_t  OMCR;      //0x0028	Slew-rate, Open-Drain Control          
    __IOM  uint32_t  IECR;      //0x002C	EXI Enable Control Register                     
	__OM   uint32_t  IEER;		//0x0030	EXI Enable Eet Register    
	__OM   uint32_t  IEDR;		//0x0034	EXI Enable Clear Register
} csp_gpio_t; 


typedef volatile struct
{
	__IOM  uint32_t  IGRPL;     //0x0000 	EXI Group Config Register L                  
    __IOM  uint32_t  IGRPH;	    //0x0004	EXI Group Config Register H                   
	__IOM  uint32_t  IGREX;		//0x0008	EXI Group Expand Config Register  
    __IOM  uint32_t  IO_CLKEN;	//0x000C 	Gpio Group Clk Enable Control Register
} csp_igrp_t; 


typedef volatile struct
{
	__IM   uint32_t  RSVD;      //0x0000 	                
    __IOM  uint32_t  LINECFG0;	//0x0004	EXI Line Config Register0                  
	__IOM  uint32_t  LINECFG1;	//0x0008	EXI Line Config Register1  
	__IOM  uint32_t  LINECFG2;	//0x000C	EXI Line Config Register2
	__IOM  uint32_t  LINECFG3;	//0x0010	EXI Line Config Register3  
	__IOM  uint32_t  LINECFG4;	//0x0014	EXI Line Config Register4  
	__IOM  uint32_t  LINECFG5;	//0x0018	EXI Line Config Register5 
	__IOM  uint32_t  LINECFG6;	//0x001C	EXI Line Config Register6   
	__IOM  uint32_t  LINECFG7;	//0x0020	EXI Line Config Register7                  
	__IOM  uint32_t  LINECFG8;	//0x0024	EXI Line Config Register8  
	__IOM  uint32_t  LINECFG9;	//0x0028	EXI Line Config Register9 
	__IOM  uint32_t  LINECFG10;	//0x002C	EXI Line Config Register10  
	__IOM  uint32_t  LINECFG11;	//0x0030	EXI Line Config Register11  
	__IOM  uint32_t  LINECFG12;	//0x0034	EXI Line Config Register12 
	__IOM  uint32_t  LINECFG13;	//0x0038	EXI Line Config Register13  
	__IOM  uint32_t  LINECFG14;	//0x003C	EXI Line Config Register14   
	__IOM  uint32_t  LINECFG15;	//0x0040	EXI Line Config Register15  
    __IOM  uint32_t  IO_CLKEN;	//0x0044 	Gpio Group Clk Enable Control Register
	__IOM  uint32_t  EXIRT;		//0x0048 	EXI Rising edge Register
	__IOM  uint32_t  EXIFT;		//0x004C 	EXI Falling edge Register
	__IOM  uint32_t  EXIMCR;	//0x0050 	EXI Interrupt Enable Register 
	__IM   uint32_t  EXIMSR;	//0x0054 	EXI Interrupt Status Register 
	__OM   uint32_t  EXICR;		//0x0058 	EXI Interrupt Status Clear Register 
	__IM   uint32_t  EXIRSR;	//0x005C 	EXI Raw Interrupt Status Register 
	__IOM  uint32_t  EXIEVTRG;	//0x0060 	EXI Trigger Config Register
} csp_exi_t; 

/******************************************************************************
* PIN_NUM: GPIO PIN Number
******************************************************************************/
/*
typedef enum
{
  PIN_NUM0    = 0,  	// Pin 0 selected 
  PIN_NUM1    = 1,  	// Pin 1 selected 
  PIN_NUM2    = 2,  	// Pin 2 selected 
  PIN_NUM3    = 3,   	// Pin 3 selected 
  PIN_NUM4    = 4,  	// Pin 4 selected 
  PIN_NUM5    = 5,  	// Pin 5 selected 
  PIN_NUM6    = 6,  	// Pin 6 selected 
  PIN_NUM7    = 7,  	// Pin 7 selected 
  PIN_NUM8    = 8,  	// Pin 8 selected 
  PIN_NUM9    = 9,  	// Pin 9 selected 
  PIN_NUM10   = 10,  	// Pin 10 selected 
  PIN_NUM11   = 11,   	// Pin 11 selected 
  PIN_NUM12   = 12,  	// Pin 12 selected 
  PIN_NUM13   = 13,  	// Pin 13 selected 
  PIN_NUM14   = 14,  	// Pin 14 selected 
  PIN_NUM15   = 15,  	// Pin 15 selected 
}gpio_pin_e;
*/
/******************************************************************************
* ODSR: PDSR: Output Data and Pin Data Status Register 
******************************************************************************/
typedef enum
{
    LOWBYTE	 = 0,
    HIGHBYTE = 1,
}gpio_byte_e;

typedef enum
{
	PIN_LOW	 = 0,
    PIN_HIGH = 1
}gpio_pin_state_e;

/******************************************************************************
* CONLR: CONHR: GPIO MUX Control  Register 
******************************************************************************/
typedef enum
{
    INPUT	= 1,
    OUTPUT	= 0,
}gpio_dir_e;
/******************************************************************************
* PUDR: DSCR: IO PULL AND Output Driving Strength Register 
******************************************************************************/


/******************************************************************************
* IECR: IEER: IEDR: GPIO EXI Control Register 
******************************************************************************/
typedef enum
{
    GPIO_INT0 	= 0,
    GPIO_INT1 	= 1,
    GPIO_INT2 	= 2,
    GPIO_INT3 	= 3,
    GPIO_INT4 	= 4,
    GPIO_INT5 	= 5,
    GPIO_INT6 	= 6,
    GPIO_INT7 	= 7,
    GPIO_INT8 	= 8,
    GPIO_INT9 	= 9,
    GPIO_INT10 	= 10,
    GPIO_INT11 	= 11,
    GPIO_INT12 	= 12,
    GPIO_INT13 	= 13,
	GPIO_INT14	= 14,
	GPIO_INT15	= 15,
}gpio_int_e;
/******************************************************************************
* IGRPL: IGRPH: IGRPH: Group Config Register
******************************************************************************/
typedef enum
{
    GRP_GPIOA0 	= 0,
    GRP_GPIOB0 	= 2,
}gpio_group_e;


typedef enum
{
	EXI_IGRP0		= (uint32_t)(0),						
	EXI_IGRP1		= (uint32_t)(1),
	EXI_IGRP2		= (uint32_t)(2),
	EXI_IGRP3		= (uint32_t)(3),
	EXI_IGRP4		= (uint32_t)(4),
	EXI_IGRP5		= (uint32_t)(5),
	EXI_IGRP6		= (uint32_t)(6),
	EXI_IGRP7		= (uint32_t)(7),
	EXI_IGRP8		= (uint32_t)(8),
	EXI_IGRP9		= (uint32_t)(9),
	EXI_IGRP10		= (uint32_t)(10),
	EXI_IGRP11		= (uint32_t)(11),
	EXI_IGRP12		= (uint32_t)(12),
	EXI_IGRP13		= (uint32_t)(13),
	EXI_IGRP14		= (uint32_t)(14),
	EXI_IGRP15		= (uint32_t)(15),
	EXI_IGRP16		= (uint32_t)(16),
	EXI_IGRP17		= (uint32_t)(17),
	EXI_IGRP18		= (uint32_t)(18),
	EXI_IGRP19		= (uint32_t)(19)
}gpio_igrp_e;

/******************************************************************************
* GPIO EXI LINECFG: 
******************************************************************************/
typedef enum
{
	EXI0_IRQ_MAP	= 0x01,			
	EXI1_IRQ_MAP	= 0x02,	
	EXI2_IRQ_MAP	= 0x0c,
	EXI3_IRQ_MAP	= 0x3f0,
	EXI4_IRQ_MAP	= 0xfc00
}exi_map_e;


typedef enum
{
	EXI_LINE_GRP0	= (0x01ul << 0),	
	EXI_LINE_GRP1	= (0x01ul << 1),	
	EXI_LINE_GRP2	= (0x01ul << 2),	
	EXI_LINE_GRP3	= (0x01ul << 3),					
}exi_line_grp_e;


#define EXI_LINE_MODE_POS	(5)
#define EXI_LINE_MODE_MSK	(0x01 << EXI_LINE_MODE_POS)
typedef enum
{
	EXI_LINE_MODE_0	 = 0,	
	EXI_LINE_MODE_1 = 1,	
}exi_line_mode_e;

#define EXI_INPUT_POS	(8)
#define EXI_INPUT_MSK	(0x0F << EXI_INPUT_POS)


typedef enum
{
	EXI_LINE_0		= (uint32_t)(0),						
	EXI_LINE_1		= (uint32_t)(1),
	EXI_LINE_2		= (uint32_t)(2),
	EXI_LINE_3		= (uint32_t)(3),
	EXI_LINE_4		= (uint32_t)(4),
	EXI_LINE_5		= (uint32_t)(5),
	EXI_LINE_6		= (uint32_t)(6),
	EXI_LINE_7		= (uint32_t)(7),
	EXI_LINE_8		= (uint32_t)(8),
	EXI_LINE_9		= (uint32_t)(9),
	EXI_LINE_10		= (uint32_t)(10),
	EXI_LINE_11		= (uint32_t)(11),
	EXI_LINE_12		= (uint32_t)(12),
	EXI_LINE_13		= (uint32_t)(13),
	EXI_LINE_14		= (uint32_t)(14),
	EXI_LINE_15		= (uint32_t)(15),
}exi_line_e;

typedef enum
{
	EXI_EDGE_IRT	= 0,
	EXI_EDGE_IFT	= 1,	
	EXI_EDGE_BOTH	= 2
}exi_trigger_e;


/******************************************************************************
************************** Exported functions ************************
******************************************************************************/
//extern void csp_gpio_default_Init(csp_gpio_t *ptGpioBase);
//extern void csp_igrp_default_Init(csp_igrp_t *igrp_base);
//extern void csp_gpio_mux_init(csp_gpio_t *ptGpioBase,gpio_byte_e eByte,uint32_t wVal);
//extern int  csp_gpio_mux_set(csp_gpio_t *ptGpioBase,uint8_t byPinNum,uint8_t af_mode);
//extern int  csp_gpio_mux_get(csp_gpio_t *ptGpioBase,uint8_t byPinNum);
//extern void csp_gpio_dir_set(csp_gpio_t *ptGpioBase, uint8_t byPinNum,gpio_dir_e eDir);
//extern void csp_gpio_inputoutput_dis(csp_gpio_t *ptGpioBase,uint8_t byPinNum);
////
//extern void csp_gpio_set_value(csp_gpio_t *ptGpioBase,uint8_t byPinNum,gpio_pin_state_e eState);
//extern void csp_gpio_toggle(csp_gpio_t *ptGpioBase,uint8_t byPinNum);
////
//extern uint32_t get_gpio_exi_intnum(gpio_igrp_e eExiGrp);
////extern void csp_gpio_set_port_irq(csp_gpio_t *ptGpioBase, uint32_t wValue, bool bEnable);
//extern void csp_gpio_intgroup_set(csp_gpio_t *ptGpioBase, uint8_t byPinNum, gpio_igrp_e eExiGrp);
//extern void csp_gpio_exi_config(csp_gpio_t *ptGpioBase,uint8_t byPinNum,gpio_igrp_e eExiGrp,exi_trigger_e eGpioTrig, bool bExiEn);
////extern void csp_exi_set_port_irq(csp_syscon_t *ptSysconBase,uint32_t wValue,bool bEnable);
//extern void csp_exi_trigger_set(csp_syscon_t *ptSysconBase,gpio_igrp_e eExiGrp, exi_trigger_e eGpioTrig);

/******************************************************************************
********************* gpio inline Functions Declaration ***********************
******************************************************************************/
/*************************************************************************
 * @brief  gpio pull set 
****************************************************************************/
static inline void csp_gpio_pullup(csp_gpio_t *ptGpioBase,uint8_t byPinNum)
{
	ptGpioBase->PUDR  = ((ptGpioBase->PUDR) & ~(0x03 << (byPinNum*2))) | (0x01 << (byPinNum*2));
}

static inline void csp_gpio_pulldown(csp_gpio_t *ptGpioBase,uint8_t byPinNum)
{
	ptGpioBase->PUDR  = ((ptGpioBase->PUDR) & ~(0x03 << (byPinNum*2))) | (0x02 << (byPinNum*2));
}

static inline void csp_gpio_pullnone(csp_gpio_t *ptGpioBase,uint8_t byPinNum)
{
	ptGpioBase->PUDR  = (ptGpioBase->PUDR) & ~(0x03 << (byPinNum*2));
}
/*************************************************************************
 * @brief  gpio exi set 
****************************************************************************/

static inline void csp_gpio_int_enable(csp_gpio_t *ptGpioBase, gpio_int_e eIoInt, bool bEnable)
{
	if(bEnable)
		ptGpioBase->IEER  =  (1 << eIoInt);
	else
		ptGpioBase->IEDR  =  (1 << eIoInt);
}

static inline void csp_gpio_port_int_enable(csp_gpio_t *ptGpioBase, uint32_t wValue, bool bEnable)
{
	if(bEnable)	
		ptGpioBase->IEER = wValue;
	else 
		ptGpioBase->IEDR = wValue;
}

//static inline void csp_gpio_irq_dis(csp_gpio_t *ptGpioBase, gpio_exi_e eExiIo)
//{
//	ptGpioBase->IEDR  =  (1 << eExiIo);
//}
//static inline void csp_gpio_irq_en(csp_gpio_t *ptGpioBase, gpio_exi_e eExiIo)
//{
//	ptGpioBase->IEER  =  (1 << eExiIo);
//}

static inline void csp_exi_set_linecfg(csp_exi_t *ptExiBase, uint8_t byLine, exi_line_grp_e eGrp, exi_line_mode_e eMode, uint8_t byInput)
{
	uint32_t *ptExiLineBase = (uint32_t *)((uint32_t)ptExiBase + (byLine + 1) * 0x04);
	
	*ptExiLineBase = eGrp | (eMode << EXI_LINE_MODE_POS) | ((byInput & 0x0f) << EXI_INPUT_POS);
}

static inline void csp_exi_line_int_enable(csp_exi_t *ptExiBase, exi_line_e eLine, bool bEnable)
{
	if(bEnable)
		ptExiBase->EXIMCR |=  (0x01ul << eLine);
	else
		ptExiBase->EXIMCR &=  ~(0x01ul << eLine);
}

static inline void csp_exi_line_port_int_enable(csp_exi_t *ptExiBase, uint32_t wValue, bool bEnable)
{
	if(bEnable)
		ptExiBase->EXIMCR =  wValue;
	else
		ptExiBase->EXIMCR &=  ~wValue;
}

static inline void csp_exi_line_clr_isr(csp_exi_t *ptExiBase, uint32_t wLine)
{
	ptExiBase->EXICR = (0x01ul << wLine);
}

static inline void csp_exi_line_port_clr_isr(csp_exi_t *ptExiBase, uint32_t wValue)
{
	ptExiBase->EXICR = wValue;
}

static inline uint32_t csp_exi_line_port_get_isr(csp_exi_t *ptExiBase)
{
    return ptExiBase->EXIMSR;
}

static inline void csp_exi_int_en(csp_syscon_t *ptSysconBase, uint32_t wIdx)
{
	ptSysconBase->EXIER =  (0x01ul << wIdx);
}

static inline void csp_exi_int_dis(csp_syscon_t *ptSysconBase, uint32_t wIdx)
{
	ptSysconBase->EXIDR = (0x01ul << wIdx);
}

static inline void csp_exi_clr_pending(csp_syscon_t *ptSysconBase, uint32_t wIdx)
{
	ptSysconBase->EXICR = (0x01ul << wIdx);
}
static inline void csp_exi_clr_port_irq(csp_syscon_t *ptSysconBase, uint32_t wValue)
{
    ptSysconBase->EXICR = wValue;
}
static inline uint32_t csp_exi_get_port_irq(csp_syscon_t *ptSysconBase)
{
    return ptSysconBase->EXICR;
}

static inline void csp_gpio_set_port_irq(csp_gpio_t *ptGpioBase, uint32_t wValue, bool bEnable)
{
	if(bEnable)	
		ptGpioBase->IEER = wValue;
	else 
		ptGpioBase->IEDR = wValue;
		
}
static inline void csp_exi_set_port_irq(csp_syscon_t *ptSysconBase,uint32_t wValue,bool bEnable)
{
   	if(bEnable)
	{
		ptSysconBase->EXIER |= wValue;				//EXI interrupt enable
//		while(!(ptSysconBase->EXIMR & wValue));		//Check EXI is enabled or not
		ptSysconBase->EXICR = wValue;				//Clear EXI status bit
	}
	else
		ptSysconBase ->EXIDR = wValue;
}

/*************************************************************************
 * @brief  gpio filtering
****************************************************************************/
static inline void csp_gpio_flt_en(csp_gpio_t *ptGpioBase,uint8_t byPinNum)
{
	ptGpioBase->FLTEN  = (ptGpioBase->FLTEN) | (0x01 << byPinNum);
}
/*************************************************************************
 * @brief  gpio output mode set 
****************************************************************************/
static inline void csp_gpio_opendrain_en(csp_gpio_t *ptGpioBase,uint8_t byPinNum)
{
	ptGpioBase->OMCR  = (ptGpioBase->OMCR) | (0x01 << byPinNum);
}
static inline void csp_gpio_opendrain_dis(csp_gpio_t *ptGpioBase,uint8_t byPinNum)
{
	ptGpioBase->OMCR  = (ptGpioBase->OMCR) & ~(0x01 << byPinNum);
}

static inline void csp_gpio_constcurr_en(csp_gpio_t *ptGpioBase,uint8_t byPinNum)
{
	ptGpioBase->OMCR  = (ptGpioBase->OMCR) | (0x01 << (byPinNum+16));
}
static inline void csp_gpio_constcurr_dis(csp_gpio_t *ptGpioBase,uint8_t byPinNum)
{
	ptGpioBase->OMCR  = (ptGpioBase->OMCR) & ~(0x01 << (byPinNum+16));
}
/*************************************************************************
 * @brief  gpio pin driver strength
****************************************************************************/

static inline void csp_gpio_ccm_ttl2(csp_gpio_t *ptGpioBase,uint8_t byPinNum)
{
	ptGpioBase->DSCR  = (ptGpioBase->DSCR) | (0x02 << (2*byPinNum));
	ptGpioBase->OMCR  = (ptGpioBase->OMCR) | (0x01 << (byPinNum+16));
}
static inline void csp_gpio_ccm_ttl1(csp_gpio_t *ptGpioBase,uint8_t byPinNum)
{
	ptGpioBase->DSCR  = (ptGpioBase->DSCR) | (0x02 << (2*byPinNum));
	ptGpioBase->OMCR  = (ptGpioBase->OMCR) & ~(0x01 << (byPinNum+16));
}
static inline void csp_gpio_ccm_cmos(csp_gpio_t *ptGpioBase,uint8_t byPinNum)
{
	ptGpioBase->DSCR  = (ptGpioBase->DSCR) & ~(0x02 << (2*byPinNum));
}

static inline void csp_gpio_drv_set(csp_gpio_t *ptGpioBase, uint8_t byPinNum, uint8_t byDrive)
{
    if(0 == byDrive)
		ptGpioBase->DSCR = (ptGpioBase->DSCR & ~(0x01ul << 2*byPinNum));
	else
		ptGpioBase->DSCR = (ptGpioBase->DSCR  | (0x01ul << 2*byPinNum));
}

static inline void csp_gpio_speed_set(csp_gpio_t *ptGpioBase, uint8_t byPinNum, uint8_t bySpeed)
{
    if(0 == bySpeed)
		ptGpioBase->DSCR = (ptGpioBase->DSCR & ~(0x02ul << 2*byPinNum));
	else
		ptGpioBase->DSCR = (ptGpioBase->DSCR  | (0x02ul << 2*byPinNum));
}

/*************************************************************************
 * @brief  gpio output or input or status handle
****************************************************************************/
static inline void csp_gpio_write_output_port(csp_gpio_t *ptGpioBase, uint32_t wValue)
{
    ptGpioBase->WODR = wValue;
}

static inline uint32_t csp_gpio_read_output_port(csp_gpio_t *ptGpioBase)
{
    return ptGpioBase->ODSR;
}

static inline uint32_t csp_gpio_read_input_port(csp_gpio_t *ptGpioBase)
{
    return ptGpioBase->PSDR;
}

static inline void csp_gpio_set_high(csp_gpio_t *ptGpioBase,uint8_t byPinNum)
{
	ptGpioBase->SODR = (0x01ul << byPinNum);
}

static inline void csp_gpio_set_low(csp_gpio_t *ptGpioBase,uint8_t byPinNum)
{
	ptGpioBase->CODR = (0x01ul << byPinNum);
}
static inline uint8_t csp_gpio_read_status(csp_gpio_t *ptGpioBase,uint8_t byPinNum)
{
    return (((ptGpioBase->PSDR) >> byPinNum) & 0x01);
}
static inline uint8_t csp_gpio_read_output(csp_gpio_t *ptGpioBase,uint8_t byPinNum)
{
    return (((ptGpioBase->ODSR) >> byPinNum) & 0x01);
}


#endif   // apt32f102_gpio_H */

/******************* (C) COPYRIGHT 2019 APT Chip *****END OF FILE****/


