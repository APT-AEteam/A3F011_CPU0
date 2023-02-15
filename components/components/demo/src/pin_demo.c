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
#include <drv/bt.h>
#include <drv/etb.h>

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
	
//	volatile uint8_t ch;
//	csi_etb_config_t tEtbConfig;				               						//ETB 参数配置结构体	
	
//	csi_pin_set_mux(PA0, PA0_INPUT);												//PA0 配置为输入;LA08N
//	csi_pin_pull_mode(PA0, GPIO_PULLUP);											//PA0 上拉
//	csi_pin_irq_enable(PA0, ENABLE);

//	csi_pin_set_mux(PB0, PB0_INPUT);												//PB0 配置为输入;LA13N
//	csi_pin_pull_mode(PB0, GPIO_PULLUP);											//PB0 上拉
//	csi_pin_irq_enable(PB0, ENABLE);
	
//	csi_pin_set_mux(PC0, PC0_INPUT);												//PC0 配置为输入;LA06N
//	csi_pin_pull_mode(PC0, GPIO_PULLUP);											//PC0 上拉
//	csi_pin_irq_enable(PC0, ENABLE);
//	
//	csi_pin_set_mux(PD0, PD0_INPUT);												//PD0 配置为输入;LA03N
//	csi_pin_pull_mode(PD0, GPIO_PULLUP);											//PD0 上拉
//	csi_pin_irq_enable(PD0, ENABLE);

//	csi_pin_set_mux(PA1, PA1_INPUT);												//PA1 配置为输入;LA09P
//	csi_pin_pull_mode(PA1, GPIO_PULLUP);											//PA1 上拉
//	csi_pin_irq_enable(PA1, ENABLE);
	
//	csi_pin_set_mux(PB1, PB1_INPUT);												//PB1 配置为输入;LA14P
//	csi_pin_pull_mode(PB1, GPIO_PULLUP);											//PB1上拉
//	csi_pin_irq_enable(PB1, ENABLE);
	
//	csi_pin_set_mux(PC1, PC1_INPUT);												//PC1 配置为输入;LA07P
//	csi_pin_pull_mode(PC1, GPIO_PULLUP);											//PC1 上拉
//	csi_pin_irq_enable(PC1, ENABLE);
	
//	csi_pin_set_mux(PD1, PD1_INPUT);												//PD1 配置为输入;LA03P
//	csi_pin_pull_mode(PD1, GPIO_PULLUP);											//PD1 上拉
//	csi_pin_irq_enable(PD1, ENABLE);
	
//	csi_pin_set_mux(PA2, PA2_INPUT);												//PA2 配置为输入;LA09N
//	csi_pin_pull_mode(PA2, GPIO_PULLUP);											//PA2 上拉
//	csi_pin_irq_enable(PA2, ENABLE);
	
//	csi_pin_set_mux(PB2, PB2_INPUT);												//PB2 配置为输入;LA14N
//	csi_pin_pull_mode(PB2, GPIO_PULLUP);											//PB2上拉
//	csi_pin_irq_enable(PB2, ENABLE);
	
//	csi_pin_set_mux(PC2, PC2_INPUT);												//PC2 配置为输入;LA07N
//	csi_pin_pull_mode(PC2, GPIO_PULLUP);											//PC2 上拉
//	csi_pin_irq_enable(PC2, ENABLE);
//	
//	csi_pin_set_mux(PD2, PD2_INPUT);												//PD2 配置为输入;LC06P
//	csi_pin_pull_mode(PD2, GPIO_PULLUP);											//PD2 上拉
//	csi_pin_irq_enable(PD2, ENABLE);
	
//	csi_pin_set_mux(PA3, PA3_INPUT);												//PB01 配置为输入
//	csi_pin_pull_mode(PA3, GPIO_PULLUP);											//PB01 上拉
//	csi_pin_irq_enable(PA3, ENABLE);
//	
//	csi_pin_set_mux(PB3, PB3_INPUT);												//PB3 配置为输入;LC05N
//	csi_pin_pull_mode(PB3, GPIO_PULLUP);											//PB3 上拉
//	csi_pin_irq_enable(PB3, ENABLE);
	
//	csi_pin_set_mux(PC3, PC3_INPUT);												//PC3 配置为输入;LA08P
//	csi_pin_pull_mode(PC3, GPIO_PULLUP);											//PC3 上拉
//	csi_pin_irq_enable(PC3, ENABLE);
	
//	csi_pin_set_mux(PD3, PD3_INPUT);												//PD3 配置为输入;LC03P
//	csi_pin_pull_mode(PD3, GPIO_PULLUP);											//PD3 上拉
//	csi_pin_irq_enable(PD3, ENABLE);
	

//	csi_exi_line_set_group(EXI_LINE0, EXI_LINE_GRP0, PA0);
//	csi_exi_line_irq_mode(EXI_LINE0, EXI_LINE_MODE_AND, EXI_BOTH_EDGE);
//	csi_exi_line_irq_enable(EXI_LINE0, ENABLE);
//	csi_exi_line_vic_irq_enable(EXI_LINE0, ENABLE);
	
//	csi_exi_line_set_group(EXI_LINE1, EXI_LINE_GRP1, PC1);
//	csi_exi_line_irq_mode(EXI_LINE1, EXI_LINE_MODE_AND, EXI_BOTH_EDGE);
//	csi_exi_line_irq_enable(EXI_LINE1, ENABLE);
//	csi_exi_line_vic_irq_enable(EXI_LINE1, ENABLE);
	
//	csi_exi_line_set_group(EXI_LINE2, EXI_LINE_GRP2, PB2);
//	csi_exi_line_irq_mode(EXI_LINE2, EXI_LINE_MODE_AND, EXI_BOTH_EDGE);
//	csi_exi_line_irq_enable(EXI_LINE2, ENABLE);
//	csi_exi_line_vic_irq_enable(EXI_LINE2, ENABLE);
	
//	csi_exi_line_set_group(EXI_LINE3, EXI_LINE_GRP3, PC3);
//	csi_exi_line_irq_mode(EXI_LINE3, EXI_LINE_MODE_AND, EXI_BOTH_EDGE);
//	csi_exi_line_irq_enable(EXI_LINE3, ENABLE);
//	csi_exi_line_vic_irq_enable(EXI_LINE3, ENABLE);
	


//	csi_pin_set_mux(PA4, PA4_INPUT);												//PA4 配置为输入;LA10N
//	csi_pin_pull_mode(PA4, GPIO_PULLUP);											//PA4 上拉
//	csi_pin_irq_enable(PA4, ENABLE);
//	
//	csi_pin_set_mux(PB4, PB4_INPUT);												//PB4 配置为输入;LC05P
//	csi_pin_pull_mode(PB4, GPIO_PULLUP);											//PB4上拉
//	csi_pin_irq_enable(PB4, ENABLE);
//	
//	csi_pin_set_mux(PC4, PC4_INPUT);												//PC4 配置为输入;LA12N
//	csi_pin_pull_mode(PC4, GPIO_PULLUP);											//PC4 上拉
//	csi_pin_irq_enable(PC4, ENABLE);
	
//	csi_pin_set_mux(PD4, PD4_INPUT);												//PD4 配置为输入;LA05N
//	csi_pin_pull_mode(PD4, GPIO_PULLUP);											//PD4 上拉
//	csi_pin_irq_enable(PD4, ENABLE);
//
//	csi_pin_set_mux(PA5, PA5_INPUT);												//PA5 配置为输入;LA11P
//	csi_pin_pull_mode(PA5, GPIO_PULLUP);											//PA5 上拉
//	csi_pin_irq_enable(PA5, ENABLE);
//	
//	csi_pin_set_mux(PB5, PB5_INPUT);												//PB5 配置为输入;LC04N
//	csi_pin_pull_mode(PB5, GPIO_PULLUP);											//PB5上拉
//	csi_pin_irq_enable(PB5, ENABLE);
//	
//	csi_pin_set_mux(PC5, PC5_INPUT);												//PC5 配置为输入;LA13P
//	csi_pin_pull_mode(PC5, GPIO_PULLUP);											//PC5 上拉
//	csi_pin_irq_enable(PC5, ENABLE);
//	
//	csi_pin_set_mux(PD5, PD5_INPUT);												//PD5 配置为输入;LA06P
//	csi_pin_pull_mode(PD5, GPIO_PULLUP);											//PD5 上拉
//	csi_pin_irq_enable(PD5, ENABLE);

//	csi_pin_set_mux(PA6, PA6_INPUT);												//PA6 配置为输入;LA11N
//	csi_pin_pull_mode(PA6, GPIO_PULLUP);											//PA6上拉
//	csi_pin_irq_enable(PA6, ENABLE);
//	
//	csi_pin_set_mux(PB6, PB6_INPUT);												//PB6 配置为输入;LC04P
//	csi_pin_pull_mode(PB6, GPIO_PULLUP);											//PB6上拉
//	csi_pin_irq_enable(PB6, ENABLE);
//	
//	csi_pin_set_mux(PC6, PC6_INPUT);												//PC6 配置为输入;LC13N
//	csi_pin_pull_mode(PC6, GPIO_PULLUP);											//PC6 上拉
//	csi_pin_irq_enable(PC6, ENABLE);
	
//	csi_pin_set_mux(PD6, PD6_INPUT);												//PD6 配置为输入;LC01N
//	csi_pin_pull_mode(PD6, GPIO_PULLUP);											//PD6 上拉
//	csi_pin_irq_enable(PD6, ENABLE);
//	
//	csi_pin_set_mux(PA7, PA7_INPUT);												//PA7 配置为输入;LA12P
//	csi_pin_pull_mode(PA7, GPIO_PULLUP);											//PA7上拉
//	csi_pin_irq_enable(PA7, ENABLE);
//	
//	csi_pin_set_mux(PB7, PB7_INPUT);												//PB7 配置为输入;LC03N
//	csi_pin_pull_mode(PB7, GPIO_PULLUP);											//PB7上拉
//	csi_pin_irq_enable(PB7, ENABLE);
//	
//	csi_pin_set_mux(PC7, PC7_INPUT);												//PC7 配置为输入;LC13P
//	csi_pin_pull_mode(PC7, GPIO_PULLUP);											//PC7 上拉
//	csi_pin_irq_enable(PC7, ENABLE);
//	
//	csi_pin_set_mux(PD7, PD7_INPUT);												//PD7 配置为输入;LC01P
//	csi_pin_pull_mode(PD7, GPIO_PULLUP);											//PD7 上拉
//	csi_pin_irq_enable(PD7, ENABLE);
	
//	csi_exi_line_set_group(EXI_LINE4, EXI_LINE_GRP0, PB4);					
//	csi_exi_line_irq_mode(EXI_LINE4, EXI_LINE_MODE_AND, EXI_BOTH_EDGE);
//	csi_exi_line_irq_enable(EXI_LINE4, ENABLE);
//	csi_exi_line_vic_irq_enable(EXI_LINE4, ENABLE);
	
//	csi_exi_line_set_group(EXI_LINE5, EXI_LINE_GRP1, PB5);
//	csi_exi_line_irq_mode(EXI_LINE5, EXI_LINE_MODE_AND, EXI_BOTH_EDGE);
//	csi_exi_line_irq_enable(EXI_LINE5, ENABLE);
//	csi_exi_line_vic_irq_enable(EXI_LINE5, ENABLE);
	
//	csi_exi_line_set_group(EXI_LINE6, EXI_LINE_GRP2, PC6);
//	csi_exi_line_irq_mode(EXI_LINE6, EXI_LINE_MODE_AND, EXI_BOTH_EDGE);
//	csi_exi_line_irq_enable(EXI_LINE6, ENABLE);
//	csi_exi_line_vic_irq_enable(EXI_LINE6, ENABLE);

//	csi_exi_line_set_group(EXI_LINE7, EXI_LINE_GRP3, PD7);
//	csi_exi_line_irq_mode(EXI_LINE7, EXI_LINE_MODE_AND, EXI_BOTH_EDGE);
//	csi_exi_line_irq_enable(EXI_LINE7, ENABLE);
//	csi_exi_line_vic_irq_enable(EXI_LINE7, ENABLE);
	
	
//	csi_pin_set_mux(PA8, PA8_INPUT);												//PA8 配置为输入;LC11N
//	csi_pin_pull_mode(PA8, GPIO_PULLUP);											//PA8上拉
//	csi_pin_irq_enable(PA8, ENABLE);
	
//	csi_pin_set_mux(PB8, PB8_INPUT);												//PB8 配置为输入;LC02N
//	csi_pin_pull_mode(PB8, GPIO_PULLUP);											//PB8上拉
//	csi_pin_irq_enable(PB8, ENABLE);
	
//	csi_pin_set_mux(PC8, PC8_INPUT);												//PC8 配置为输入;LC12N
//	csi_pin_pull_mode(PC8, GPIO_PULLUP);											//PC8 上拉
//	csi_pin_irq_enable(PC8, ENABLE);
//	
//	csi_pin_set_mux(PD8, PD8_INPUT);												//PD8 配置为输入;LC00N
//	csi_pin_pull_mode(PD8, GPIO_PULLUP);											//PD8 上拉
//	csi_pin_irq_enable(PD8, ENABLE);
	
//	csi_pin_set_mux(PA9, PA9_INPUT);												//PA9 配置为输入;LC11P
//	csi_pin_pull_mode(PA9, GPIO_PULLUP);											//PA9上拉
//	csi_pin_irq_enable(PA9, ENABLE);
//	
//	csi_pin_set_mux(PB9, PB9_INPUT);												//PB9 配置为输入;LC02P
//	csi_pin_pull_mode(PB9, GPIO_PULLUP);											//PB9上拉
//	csi_pin_irq_enable(PB9, ENABLE);

//	csi_pin_set_mux(PC9, PC9_INPUT);												//PC9 配置为输入;LC12P
//	csi_pin_pull_mode(PC9, GPIO_PULLUP);											//PC9 上拉
//	csi_pin_irq_enable(PC9, ENABLE);
	
//	csi_pin_set_mux(PA10, PA10_INPUT);												//PA10 配置为输入;LC10N
//	csi_pin_pull_mode(PA10, GPIO_PULLUP);											//PA10上拉
//	csi_pin_irq_enable(PA10, ENABLE);
//	
//	csi_pin_set_mux(PB10, PB10_INPUT);												//PB10 配置为输入;LA15P
//	csi_pin_pull_mode(PB10, GPIO_PULLUP);											//PB10上拉
//	csi_pin_irq_enable(PB10, ENABLE);
//	
//	csi_pin_set_mux(PC10, PC10_INPUT);												//PC10 配置为输入;LC07N
//	csi_pin_pull_mode(PC10, GPIO_PULLUP);											//PC10 上拉
//	csi_pin_irq_enable(PC10, ENABLE);
	
//	csi_pin_set_mux(PA11, PA11_INPUT);												//PA11 配置为输入;LC10P
//	csi_pin_pull_mode(PA11, GPIO_PULLUP);											//PA11上拉
//	csi_pin_irq_enable(PA11, ENABLE);
//	
//	csi_pin_set_mux(PB11, PB11_INPUT);												//PB11 配置为输入;LA15N
//	csi_pin_pull_mode(PB11, GPIO_PULLUP);											//PB11上拉
//	csi_pin_irq_enable(PB11, ENABLE);
//	
//	csi_pin_set_mux(PC11, PC11_INPUT);												//PC11 配置为输入;LC07P
//	csi_pin_pull_mode(PC11, GPIO_PULLUP);											//PC11 上拉
//	csi_pin_irq_enable(PC11, ENABLE);
	
//	csi_pin_set_mux(PA12, PA12_INPUT);												//PA12 配置为输入;LC09N
//	csi_pin_pull_mode(PA12, GPIO_PULLUP);											//PA12上拉
//	csi_pin_irq_enable(PA12, ENABLE);
//	
//	csi_pin_set_mux(PB12, PB12_INPUT);												//PB12 配置为输入;LC15N
//	csi_pin_pull_mode(PB12, GPIO_PULLUP);											//PB12上拉
//	csi_pin_irq_enable(PB12, ENABLE);
	
	csi_pin_set_mux(PC12, PC12_INPUT);												//PC12 配置为输入;LC06N
	csi_pin_pull_mode(PC12, GPIO_PULLUP);											//PC12 上拉
	csi_pin_irq_enable(PC12, ENABLE);
	
//	csi_pin_set_mux(PA13, PA13_INPUT);												//PA13 配置为输入;LC17P = DIO
//	csi_pin_pull_mode(PA13, GPIO_PULLUP);											//PA13上拉
//	csi_pin_irq_enable(PA13, ENABLE);
	
//	csi_pin_set_mux(PB13, PB13_INPUT);												//PB13 配置为输入;LC15P
//	csi_pin_pull_mode(PB13, GPIO_PULLUP);											//PB13上拉
//	csi_pin_irq_enable(PB13, ENABLE);

	csi_pin_set_mux(PC13, PC13_INPUT);												//PC13 配置为输入;LA05P
	csi_pin_pull_mode(PC13, GPIO_PULLUP);											//PC13 上拉
	csi_pin_irq_enable(PC13, ENABLE);
	
//	csi_pin_set_mux(PA14, PA14_INPUT);												//PA14 配置为输入;LC17N = CLK
//	csi_pin_pull_mode(PA14, GPIO_PULLUP);											//PA14上拉
//	csi_pin_irq_enable(PA14, ENABLE);
	
//	csi_pin_set_mux(PB14, PB14_INPUT);												//PB14 配置为输入;LC14N
//	csi_pin_pull_mode(PB14, GPIO_PULLUP);											//PB14上拉
//	csi_pin_irq_enable(PB14, ENABLE);
	
	csi_pin_set_mux(PC14, PC14_INPUT);												//PC14 配置为输入;LA04N
	csi_pin_pull_mode(PC14, GPIO_PULLUP);											//PC14 上拉
	csi_pin_irq_enable(PC14, ENABLE);
	
	
//	csi_pin_set_mux(PA15, PA15_INPUT);												//PA15 配置为输入;LC08P
//	csi_pin_pull_mode(PA15, GPIO_PULLUP);											//PA15上拉
//	csi_pin_irq_enable(PA15, ENABLE);
//	
//	csi_pin_set_mux(PB15, PB15_INPUT);												//PB15 配置为输入;LC14P
//	csi_pin_pull_mode(PB15, GPIO_PULLUP);											//PB15上拉
//	csi_pin_irq_enable(PB15, ENABLE);
//	
	csi_pin_set_mux(PC15, PC15_INPUT);												//PC15 配置为输入;LA04P
	csi_pin_pull_mode(PC15, GPIO_PULLUP);											//PC15 上拉
	csi_pin_irq_enable(PC15, ENABLE);
	
//	csi_exi_line_set_group(EXI_LINE8, EXI_LINE_GRP0, PB8);
//	csi_exi_line_irq_mode(EXI_LINE8, EXI_LINE_MODE_AND, EXI_BOTH_EDGE);
//	csi_exi_line_irq_enable(EXI_LINE8, ENABLE);
//	csi_exi_line_vic_irq_enable(EXI_LINE8, ENABLE);
	
//	csi_exi_line_set_group(EXI_LINE9, EXI_LINE_GRP1, PC9);
//	csi_exi_line_irq_mode(EXI_LINE9, EXI_LINE_MODE_AND, EXI_BOTH_EDGE);
//	csi_exi_line_irq_enable(EXI_LINE9, ENABLE);
//	csi_exi_line_vic_irq_enable(EXI_LINE9, ENABLE);
	
//	csi_exi_line_set_group(EXI_LINE10, EXI_LINE_GRP2, PC10);
//	csi_exi_line_irq_mode(EXI_LINE10, EXI_LINE_MODE_AND, EXI_BOTH_EDGE);
//	csi_exi_line_irq_enable(EXI_LINE10, ENABLE);
//	csi_exi_line_vic_irq_enable(EXI_LINE10, ENABLE);
	
//	csi_exi_line_set_group(EXI_LINE11, EXI_LINE_GRP3, PA11);
//	csi_exi_line_irq_mode(EXI_LINE11, EXI_LINE_MODE_AND, EXI_BOTH_EDGE);
//	csi_exi_line_irq_enable(EXI_LINE11, ENABLE);
//	csi_exi_line_vic_irq_enable(EXI_LINE11, ENABLE);
	
	csi_exi_line_set_group(EXI_LINE12, EXI_LINE_GRP_ALL, PC12);
	csi_exi_line_irq_mode(EXI_LINE12, EXI_LINE_MODE_AND, EXI_BOTH_EDGE);
	csi_exi_line_irq_enable(EXI_LINE12, ENABLE);
	csi_exi_line_vic_irq_enable(EXI_LINE12, ENABLE);
	
	csi_exi_line_set_group(EXI_LINE13, EXI_LINE_GRP1, PC13);
	csi_exi_line_irq_mode(EXI_LINE13, EXI_LINE_MODE_AND, EXI_BOTH_EDGE);
//	csi_exi_line_irq_enable(EXI_LINE13, ENABLE);
//	csi_exi_line_vic_irq_enable(EXI_LINE13, ENABLE);
	
	csi_exi_line_set_group(EXI_LINE14, EXI_LINE_GRP2, PC14);
	csi_exi_line_irq_mode(EXI_LINE14, EXI_LINE_MODE_AND, EXI_BOTH_EDGE);
//	csi_exi_line_irq_enable(EXI_LINE14, ENABLE);
//	csi_exi_line_vic_irq_enable(EXI_LINE14, ENABLE);
	
	csi_exi_line_set_group(EXI_LINE15, EXI_LINE_GRP3, PC15);
	csi_exi_line_irq_mode(EXI_LINE15, EXI_LINE_MODE_AND, EXI_BOTH_EDGE);
//	csi_exi_line_irq_enable(EXI_LINE15, ENABLE);
//	csi_exi_line_vic_irq_enable(EXI_LINE15, ENABLE);
	
//	csi_exi_set_evtrg(EXI_TRGOUT2, EXI_TRGSRC_LINE2, EXI_BOTH_EDGE);
//	
//	csi_bt_timer_init(BT0, 40000);										//初始化BT0, 定时40000us； BT定时，默认采用PEND中断
//	csi_bt_set_sync(BT0, BT_TRGIN_SYNCEN0, BT_TRG_ONCE, DISABLE);		//外部触发bt启动(SYNCIN0)
//	
//	tEtbConfig.byChType = ETB_ONE_TRG_ONE;  		//单个源触发单个目标
//	tEtbConfig.bySrcIp  = ETB_EXI_TRGOUT2;  	    //EXI_TRGOUT0作为触发源
//	tEtbConfig.byDstIp =  ETB_BT0_SYNCIN0;   	    //BT0 同步输入作为目标事件
//	tEtbConfig.byTrgMode = ETB_HARDWARE_TRG;
//   
//	csi_etb_init();
//	ch = csi_etb_ch_alloc(tEtbConfig.byChType);	    //自动获取空闲通道号,ch >= 0 获取成功
//	if(ch < 0)
//		return -1;								    //ch < 0,则获取通道号失败
//	iRet = csi_etb_ch_config(ch, &tEtbConfig);
//	
	return iRet;
}