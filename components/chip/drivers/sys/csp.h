/***********************************************************************//** 
 * \file  csp.h
 * \copyright Copyright (C) 2015-2021 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-11-24 <td>V0.0  <td>WNN   <td>initial
 * <tr><td> 20201-5-13 <td>V0.0  <td>ZJY   <td>add *IWDT
 * </table>
 * *********************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef _CSP_H
#define _CSP_H

/* Includes ------------------------------------------------------------------*/
#include "csp_adc.h"
#include "csp_bt.h"
#include "csp_cnta.h"
#include "csp_crc.h"
#include "csp_ept.h"
#include "csp_etb.h"
#include "csp_gpio.h"
#include "csp_gpta.h"
#include "csp_i2c.h"
#include "csp_can.h"
#include "csp_ifc.h"
#include "csp_lpt.h"
#include "csp_rtc.h"
#include "csp_sio.h"
#include "csp_spi.h"
#include "csp_qspi.h"
#include "csp_dma.h"
#include "csp_syscon.h"
#include "csp_uart.h"
#include "csp_usart.h"
#include "csp_wwdt.h"
#include "csp_led.h"
#include "csp_gptb.h"
#include "csp_can.h"
#include "csp_cmp.h"
#include "csp_usb.h"
#include "csi_core.h"
#include "csp_mbox.h"
#include "csp_cordic.h"
#include "csp_iis.h"
#include "csp_codec.h"
#include "csp_trng.h"

typedef csp_syscon_t 	csp_iwdt_t;

extern CLIC_Type  		*COREINT;
extern CORET_Type 		*CORETIMER;
extern csp_ifc_t 		*IFC;
extern csp_syscon_t 	*SYSCON;
//extern csp_syscon1_t 	*SYSCON1; 
extern csp_etb_t   		*ETCB;
extern csp_dma_t   		*DMA0, *DMA1;
extern csp_adc_t 		*ADC0,*ADC1;
extern csp_gpio_t 		*GPIOA, *GPIOB, *GPIOC, *GPIOD;
extern csp_exi_t 		*EXI;
extern csp_usart_t 		*USART0, *USART1;
extern csp_uart_t 		*UART0, *UART1, *UART2;
extern csp_spi_t  		*SPI0;
extern csp_spi_t  		*SPI1;
extern csp_qspi_t       *QSPI;
extern csp_sio_t  		*SIO0;
extern csp_cmp_t  		*CMP0;
extern csp_cmp_t  		*CMP1;
extern csp_cmp_t  		*CMP2;
extern csp_i2c_t  		*I2C0;
extern csp_can_t 		*CAN0; 
extern csp_cnta_t  		*CA0;
extern csp_gpta_t 		*GPTA0,*GPTA1,*GPTA2,*GPTA3;
extern csp_ept_t 		*EPT;
extern csp_lpt_t 		*LPT;
extern csp_wwdt_t 		*WWDT;
extern csp_led_t 		*LED;
extern csp_bt_t  		*BT0, *BT1, *BT2, *BT3, *CPU1_BT;
extern csp_crc_t 		*CRC;
extern csp_rtc_t 		*RTC;
extern csp_iwdt_t		*IWDT;
extern csp_spi_t  		*CPU1_SPI;
extern csp_mbox_t      *MBOX0,*MBOX1;
extern csp_usb_t       *USBD;
extern csp_cordic_t  	*CORDIC;
//extern csp_gptb_t       *GPTB0, *GPTB1, *GPTB2, *GPTB3, *GPTB4, *GPTB5;
extern csp_i2s_t  		*I2S0,*I2S1;
extern csp_codec_t		*CODEC;
extern csp_trng_t		*TRNG;

#endif

/******************* (C) COPYRIGHT 2020 APT Chip *****END OF FILE****/