/***********************************************************************//** 
 * \file  interrupt.c
 * \brief  source file for interrypt handlers
 * \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-8-10 <td>V0.0  <td>WNN   <td>initial
 * </table>
 * *********************************************************************
*/

/* Includes ------------------------------------------------------------------*/

#include "soc.h"
#include "gpio.h"
//#include "ept.h"
#include "adc.h"
#include "lpt.h"
#include "pin.h"
#include "spi.h"
#include "board_config.h"
#include "csp.h"

#include "rtc.h"

#include "qspi.h"
#include "irq.h"
#include "cnta.h"
#include "can.h"

/* externs function--------------------------------------------------------*/
extern void tick_irqhandler(void);
extern void uart_irqhandler(csp_uart_t *ptUartBase,uint8_t byIdx);
extern void usart_irqhandler(csp_usart_t *ptUsartBase,uint8_t byIdx);
extern void can_irqhandler(csp_can_t *ptCanBase);
extern void dma_irqhandler(csp_dma_t *ptDmaBase);						//DMA
extern void gpta0_initen_irqhandler(csp_gpta_t *ptGptaBase);
extern void gpta1_initen_irqhandler(csp_gpta_t *ptGptaBase);
extern void gpta2_initen_irqhandler(csp_gpta_t *ptGptaBase);
extern void gpta3_initen_irqhandler(csp_gpta_t *ptGptaBase);
extern void gpio_irqhandler(uint8_t byExiNum);
extern void ifc_irqhandler(void);
extern void bt_irqhandler(csp_bt_t *ptBtBase);
extern void wwdt_irqhandler(void);
extern void cmp_irqhandler(csp_cmp_t *ptCmpBase);
extern void adc_irqhandler(csp_adc_t *ptAdcBase);
extern void syscon_irqhandler(csp_syscon_t *ptSysconBase);
extern void led_irqhandler(csp_led_t *ptLedBase);
extern void i2c_irqhandler(csp_i2c_t *ptIicBase);
extern void usb_irqhandler(csp_usb_t *ptUsbBase,int32_t idx);
extern void cordic_irqhandler(csp_cordic_t *ptCordicBase);
extern void iis_irqhandler(csp_i2s_t *ptI2sBase);
extern void mbox_irqhandler(csp_mbox_t *ptMboxBase);

/* private function--------------------------------------------------------*/
/* extern variablesr------------------------------------------------------*/
/* Private variablesr------------------------------------------------------*/

/*************************************************************/
//CORET Interrupt
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void coret_int_handler(void)
{
	// ISR content ...
	tick_irqhandler();
}

void syscon_int_handler(void) 
{
    // ISR content ...

	if(csp_syscon_get_int_st(SYSCON) & LVD_ST_INT)
	{
		nop;
		csp_syscon_int_clr(SYSCON, LVD_ST_INT);
	}
	
	if(csp_syscon_get_int_st(SYSCON) & WDT_ST_INT)
	{
		nop;
		//csi_pin_toggle(PA05);
		csp_syscon_int_clr(SYSCON, WDT_ST_INT);
		//csi_iwdt_feed();
	}
}

void ifc_int_handler(void)
{
#if	IFC_INT_HANDLE_EN
	// ISR content ...
	ifc_irqhandler();
#endif
	
}
void adc0_int_handler(void) 
{	
#if	ADC0_INT_HANDLE_EN
	// ISR content ...
	adc_irqhandler(ADC0);
#endif	
}

void adc1_int_handler(void) 
{
#if	ADC1_INT_HANDLE_EN
	// ISR content ...
	adc_irqhandler(ADC1);
#endif	
}

 void dma0_int_handler(void)
{
#if DMA0_INT_HANDLE_EN	
	// ISR content ...
	dma_irqhandler(DMA0);
	//csp_qspi_set_int(QSPI, QSPI_TXE_INT,false);
#endif
}

void dma1_int_handler(void) 
{
#if DMA1_INT_HANDLE_EN	
	// ISR content ...
	dma_irqhandler(DMA1);
#endif	
}

void wwdt_int_handler(void)
{
#if WWDT_INT_HANDLE_EN
	 // ISR content ...
	wwdt_irqhandler();
	
#endif
}

void gpta0_int_handler(void)
{
#if GPTA0_INT_HANDLE_EN	
	 // ISR content ...
	gpta0_initen_irqhandler(GPTA0);
#endif
}

void gpta1_int_handler(void) 
{
#if GPTA1_INT_HANDLE_EN	
	 // ISR content ...
#endif	
}


void gpta2_int_handler(void)
{
#if GPTA2_INT_HANDLE_EN	
	 // ISR content ...
#endif
}

void gpta3_int_handler(void) 
{
#if GPTA3_INT_HANDLE_EN	
	 // ISR content ...
#endif
}

//void gptb0_int_handler(void) 
//{
//#if GPTB0_INT_HANDLE_EN		
//    // ISR content ...	
//#endif
//}
//
//void gptb1_int_handler(void) 
//{
//#if GPTB1_INT_HANDLE_EN		
//    // ISR content ...	
//#endif	
//}
//
//void gptb2_int_handler(void) 
//{
//#if GPTB2_INT_HANDLE_EN		
//    // ISR content ...	
//#endif	
//}
//
//void gptb3_int_handler(void) 
//{
//#if GPTB3_INT_HANDLE_EN		
//    // ISR content ...	
//#endif
//}
//
//void gptb4_int_handler(void) 
//{
//#if GPTB4_INT_HANDLE_EN		
//    // ISR content ...	
//#endif	
//}

void tkey_int_handler(void) 
{
#if TKEY_INT_HANDLE_EN		
    // ISR content ...
#endif
}

void dac0_int_handler(void) 
{
#if DAC0_INT_HANDLE_EN		
    // ISR content ...
#endif
}

void ept_int_handler(void) 
{
#if	EPT_INT_HANDLE_EN	

#endif	
}

void usart0_int_handler(void) 
{
#if	USART0_INT_HANDLE_EN	
	usart_irqhandler(USART0, 0);
#endif	
}

void usart1_int_handler(void) 
{
#if	USART0_INT_HANDLE_EN	
    // ISR content ...
	usart_irqhandler(USART1, 1);
#endif
}

void uart0_int_handler(void) 
{
#if	UART0_INT_HANDLE_EN
    // ISR content ...
	uart_irqhandler(UART0, 0);

#endif
}

void uart1_int_handler(void) 
{
#if	UART1_INT_HANDLE_EN
    // ISR content ...
	uart_irqhandler(UART1, 1);

#endif
}
void uart2_int_handler(void) 
{
#if	UART2_INT_HANDLE_EN
    // ISR content ...
	uart_irqhandler(UART2, 2);

#endif
}

void qspi_int_handler(void) 
{
#if	QSPI_INT_HANDLE_EN
    // ISR content ...
	//qspi_irqhandler(QSPI);
#endif
}

void sio0_int_handler(void) 
{
#if	SIO0_INT_HANDLE_EN
    // ISR content ...
#endif
}

void sio1_int_handler(void) 
{
#if	SIO1_INT_HANDLE_EN
    // ISR content ...
#endif
}

void i2c_int_handler(void) 
{
#if	I2C_INT_HANDLE_EN
    // ISR content ...
	i2c_irqhandler(I2C0);
	
#endif
}

void spi0_int_handler(void) 
{
#if	SPI0_INT_HANDLE_EN
   // ISR content ...
   spi_irqhandler(SPI0);
#endif   
}

void spi1_int_handler(void) 
{
#if	SPI1_INT_HANDLE_EN
   // ISR content ...
   spi_irqhandler(SPI1);
#endif
}

void exiline0_int_handler(void) 
{
#if	EXILINE0_INT_HANDLE_EN
    // ISR content ...
	gpio_irqhandler(0);
#endif
}
void exiline1_int_handler(void) 
{
#if	EXILINE1_INT_HANDLE_EN
    // ISR content ...
	gpio_irqhandler(1);
#endif
}
void exiline2_int_handler(void) 
{
#if	EXILINE2_INT_HANDLE_EN
    // ISR content ...
	gpio_irqhandler(2);
#endif
}
void exiline3_int_handler(void) 
{
#if	EXILINE3_INT_HANDLE_EN
    // ISR content ...
	gpio_irqhandler(3);
#endif
}
void exiline4_int_handler(void) 
{
#if	EXILINE4_INT_HANDLE_EN
    // ISR content ...
	gpio_irqhandler(4);
#endif
}


void exiline5_int_handler(void) 
{
#if	EXILINE5_INT_HANDLE_EN
    // ISR content ...
	gpio_irqhandler(5);
#endif
}

void exiline6_int_handler(void) 
{
#if	EXILINE6_INT_HANDLE_EN
    // ISR content ...
	gpio_irqhandler(6);
#endif
}

void exiline7_int_handler(void) 
{
#if	EXILINE7_INT_HANDLE_EN
    // ISR content ...
	gpio_irqhandler(7);
#endif
}

void exiline8_int_handler(void) 
{
#if	EXILINE8_INT_HANDLE_EN
    // ISR content ...
	gpio_irqhandler(8);
	
#endif
}

void exiline9_int_handler(void) 
{
#if	EXILINE9_INT_HANDLE_EN
    // ISR content ...
	gpio_irqhandler(9);
#endif
}

void exiline10_int_handler(void) 
{
#if	EXILINE10_INT_HANDLE_EN
    // ISR content ...
	gpio_irqhandler(10);
#endif
}

void exiline11_int_handler(void) 
{
#if	EXILINE11_INT_HANDLE_EN
    // ISR content ...
	gpio_irqhandler(11);
#endif
}

void exiline12_int_handler(void) 
{
#if	EXILINE12_INT_HANDLE_EN
    // ISR content ...
	gpio_irqhandler(12);
#endif
}

void exiline13_int_handler(void) 
{
#if	EXILINE13_INT_HANDLE_EN
    // ISR content ...
	gpio_irqhandler(13);
#endif
}

void exiline14_int_handler(void) 
{
#if	EXILINE14_INT_HANDLE_EN
    // ISR content ...
	gpio_irqhandler(14);
#endif
}

void exiline15_int_handler(void) 
{
#if	EXILINE15_INT_HANDLE_EN
    // ISR content ...
	gpio_irqhandler(15);
#endif
}

ATTRIBUTE_ISR void __attribute__((weak)) can_int_handler(void) 
{
    // ISR content ...
//	CSI_INTRPT_ENTER();
#if (USE_CAN_CALLBACK == 1)
	csi_can_irqhandler(CAN0, 0);
#else
	csp_can_clr_isr(CAN0, csp_can_get_isr(CAN0));
#endif
//	CSI_INTRPT_EXIT();
}

void cnta_int_handler(void)
{
#if	CNTA_INT_HANDLE_EN
	// ISR content ...
	cnta_irqhandler(CA0);
#endif
}

void lpt_int_handler(void)
{
#if	LPT_INT_HANDLE_EN
    // ISR content ...
	lpt_irqhandler(LPT);
#endif
}

void rtc_int_handler(void)
{
#if	RTC_INT_HANDLE_EN
	// ISR content ...
	csi_pin_toggle(PA6);
	csp_rtc_int_clr(RTC, RTC_INT_ALMA|RTC_INT_ALMB|RTC_INT_CPRD|RTC_INT_TRGEV0|RTC_INT_TRGEV1);
#endif
}

void cmp0_int_handler(void) 
{
#if	CMP0_INT_HANDLE_EN
    // ISR content ...
#endif
}

void cmp1_int_handler(void) 
{
#if	CMP1_INT_HANDLE_EN
    // ISR content ...
#endif
}

void cmp2_int_handler(void) 
{
#if	CMP2_INT_HANDLE_EN
    // ISR content ...
#endif
}

void cordic_int_handler(void) 
{
#if	CORDIC_INT_HANDLE_EN
    // ISR content ...

#endif
}

void bt0_int_handler(void) 
{
#if	BT0_INT_HANDLE_EN
    // ISR content ...
	bt_irqhandler(BT0);
	csi_pin_toggle(PD4);
#endif
}

void bt1_int_handler(void) 
{
#if	BT1_INT_HANDLE_EN
    // ISR content ...
	bt_irqhandler(BT1);
#endif
}

void bt2_int_handler(void) 
{
#if	BT2_INT_HANDLE_EN
    // ISR content ...
	bt_irqhandler(BT2);	
#endif
}

void bt3_int_handler(void) 
{
#if	BT3_INT_HANDLE_EN
    // ISR content ...
	bt_irqhandler(BT3);
#endif	
}


void i2s0_int_handler(void) 
{
#if	I2S0_INT_HANDLE_EN
    // ISR content ...
	iis_irqhandler(I2S0);

#endif
}

void i2s1_int_handler(void) 
{
#if	I2S1_INT_HANDLE_EN
    // ISR content ...
	iis_irqhandler(I2S1);
#endif	
}

void mbox1_int1_int_handler(void) 
{
#if	MBOX1_INT1_INT_HANDLE_EN
    // ISR content ...
	mbox_irqhandler(MBOX1);
#endif	
}

void trng_int_handler(void) 
{
#if	TRNG_INT_HANDLE_EN
    // ISR content ...
#endif	
}

void aes_int_handler(void) 
{
#if	AES_INT_HANDLE_EN
    // ISR content ...
#endif	
}

void rsa_int_handler(void) 
{
#if	RSA_INT_HANDLE_EN
    // ISR content ...
#endif	
}

void sha_int_handler(void) 
{
#if	SHA_INT_HANDLE_EN
    // ISR content ...
#endif	
}

void usb_int_handler(void) 
{
#if	USB_INT_HANDLE_EN
    // ISR content ...
	usb_irqhandler(USBD,1);	
#endif	
}

void cpu1_bt_int_handler(void) 
{
#if	CPU1_BT_INT_HANDLE_EN
    // ISR content ...
	csi_pin_toggle(PA6);
	bt_irqhandler(CPU1_BT);
#endif	
}

void cpu1_spi_int_handler(void) 
{
#if	CPU1_SPI_INT_HANDLE_EN
    // ISR content ...
#endif	
}
/*************************************************************/
/*************************************************************/
/*************************************************************/
//void PriviledgeVioHandler(void) 
//{
//    // ISR content ...
//	while(1){};
//}
//
//void SystemDesPtr(void) 
//{
//    // ISR content ...
//	while(1){};
//}
//
//void MisalignedHandler(void) 
//{
//    // ISR content ...
//	while(1){};
//}
//
//void IllegalInstrHandler(void) 
//{
//    // ISR content ...
//	while(1){};
//}
//
//void AccessErrHandler(void) 
//{
//    // ISR content ...
//	while(1){};
//}
//
//void BreakPointHandler(void) 
//{
//    // ISR content ...
//	while(1){};
//}
//
//void UnrecExecpHandler(void) 
//{
//    // ISR content ...
//	while(1){};
//}
//
//void Trap0Handler(void) 
//{
//    // ISR content ...
//	while(1){};
//}
//
//void Trap1Handler(void) 
//{
//    // ISR content ...
//	while(1){};
//}
//
//void Trap2Handler(void) 
//{
//    // ISR content ...
//	while(1){};
//}
//
//void Trap3Handler(void) 
//{
//    // ISR content ...
//	while(1){};
//
//}
//
//void PendTrapHandler(void) 
//{
//    // ISR content ...
//	while(1){};
//}

void tspend_handler(void)
{
	while(1);
}
/******************* (C) COPYRIGHT 2020 APT Chip *****END OF FILE****/

