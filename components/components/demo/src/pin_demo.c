/***********************************************************************//** 
 * \file  pin_demo.c
 * \brief  PIN_DEMO description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-4-25 <td>V0.0 <td>ZJY     <td>initial
 * </table>
 * *********************************************************************
*/
/* Includes ---------------------------------------------------------------*/
#include <string.h>
#include "sys_clk.h"
#include <drv/gpio.h>
#include <drv/pin.h>

#include "demo.h"
/* externs function--------------------------------------------------------*/
/* externs variablesr------------------------------------------------------*/
/* Private macro-----------------------------------------------------------*/
/* Private variablesr------------------------------------------------------*/


/** \brief gpio pin output demo 
 * 
 *  \param[in] none
 *  \return error code
 */
int pin_output_demo(void)
{
	int iRet = 0;
	
	csi_pin_set_mux(PB0,PB0_OUTPUT);			//PB00 配置为输出
	csi_pin_set_high(PB0);						//PB00 输出高
	mdelay(100);								//延时100ms
	csi_pin_set_low(PB0);						//PB00 输出低
	mdelay(100);
	csi_pin_set_high(PB0);						//PB00 输出低
	mdelay(100);
	
	csi_pin_output_mode(PB0, GPIO_OPEN_DRAIN);	//PB00 配置为开漏输出
	csi_pin_set_high(PB0);						
	mdelay(100);
	csi_pin_set_low(PB0);						
	mdelay(100);
	csi_pin_set_high(PB0);						
	mdelay(100);
	
	csi_pin_output_mode(PB0, GPIO_PUSH_PULL);	//PB00 配置为推挽输出
	csi_pin_set_high(PB0);						
	mdelay(100);
	csi_pin_set_low(PB0);						
	mdelay(100);
	csi_pin_set_high(PB0);						
	mdelay(100);
	
	return iRet;
}

/** \brief gpio pin output demo 
 * 
 *  \param[in] none
 *  \return error code
 */
int pin_input_demo(void)
{
	int iRet = 0;
	
	uint32_t wStatus;
	
	csi_pin_set_mux(PA8,PA8_INPUT);			//PA08 配置为输入
	csi_pin_pull_mode(PA8,GPIO_PULLNONE);		//无上下拉
	mdelay(100);
	wStatus = csi_pin_read(PA8);				//PA08 输入状态读取(0/1 = 高/低)
	while(wStatus != 0);
	
	csi_pin_pull_mode(PA8,GPIO_PULLUP);		//上拉
	mdelay(100);
	wStatus = csi_pin_read(PA8);
	while(wStatus != (0x01 << 0x08));
	
	csi_pin_pull_mode(PA8,GPIO_PULLDOWN);		//下拉
	mdelay(100);
	wStatus = csi_pin_read(PA8);
	while(wStatus != 0);
	
	return iRet;
}

/** \brief gpio pin output demo 
 * 
 *  \param[in] none
 *  \return error code
 */
int pin_irq_demo(void)
{
	int iRet = 0;
	csi_imosc_enable(2);
	//csi_exi_flt_enable(EXI_FLT_CKDIV4, ENABLE);					//EXI 去抖滤波
	csi_pin_set_mux(PB1, PB1_INPUT);							//PB01 配置为输入
	csi_pin_pull_mode(PB1, GPIO_PULLUP);						//PB01 上拉
	csi_pin_irq_mode(PB1, EXI_GRP18, GPIO_IRQ_FALLING_EDGE);	//PB01 下降沿产生中断
	csi_pin_irq_enable(PB1, EXI_GRP18, ENABLE);				//PB01 中断使能，选择中断组5	
	
	return iRet;
}