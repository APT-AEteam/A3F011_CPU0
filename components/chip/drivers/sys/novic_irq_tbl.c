/*
 * Copyright (C) 2016 YunOS Project. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//#include <csi_config.h>
#include <soc.h>

extern void Default_Handler(void);

void (*g_irqvector[64])(void);
void (*g_nmivector)(void);

void irq_vectors_init(void)
{
    int i;

    for (i = 0; i < 64; i++) {
        g_irqvector[i] = Default_Handler;
    }
	
//#ifdef	CONFIG_IRQ_LOOKUP		//Table lookup method for interrupt processing 
	//init all irq table
    g_irqvector[CORET_IRQn] 	= coret_int_handler;
	g_irqvector[SYSCON_IRQ_NUM] 	= syscon_int_handler;
	g_irqvector[ADC0_IRQn] 		= adc0_int_handler;
	g_irqvector[ADC1_IRQn] 		= adc1_int_handler;
	g_irqvector[DMA0_IRQn] 		= dma0_int_handler;
	g_irqvector[DMA1_IRQn] 		= dma1_int_handler;
	
	g_irqvector[GPTA0_IRQn] 	= gpta0_int_handler;
	g_irqvector[GPTA1_IRQn] 	= gpta1_int_handler;
	g_irqvector[GPTA2_IRQn] 	= gpta2_int_handler;
	g_irqvector[GPTA3_IRQn] 	= gpta3_int_handler;
//	g_irqvector[GPTB0_IRQn] 	= gptb0_int_handler;
//	g_irqvector[GPTB1_IRQn] 	= gptb1_int_handler;
//	g_irqvector[GPTB2_IRQn] 	= gptb2_int_handler;
//	g_irqvector[GPTB3_IRQn] 	= gptb3_int_handler;
//	g_irqvector[GPTB4_IRQn] 	= gptb4_int_handler;
	g_irqvector[TKEY_IRQn] 		= tkey_int_handler;
	g_irqvector[DAC0_IRQn] 		= dac0_int_handler;
	
	g_irqvector[EPT_IRQn] 		= ept_int_handler;
	g_irqvector[USART0_IRQn] 	= usart0_int_handler;
	g_irqvector[USART1_IRQn] 	= usart1_int_handler;
	g_irqvector[UART0_IRQn] 	= uart0_int_handler;
	g_irqvector[UART1_IRQn] 	= uart1_int_handler;
	g_irqvector[UART2_IRQn] 	= uart2_int_handler;
	g_irqvector[QSPI_IRQn] 		= qspi_int_handler;
	g_irqvector[SIO0_IRQn] 		= sio0_int_handler;
	g_irqvector[SIO1_IRQn] 		= sio1_int_handler;
	g_irqvector[I2C_IRQn] 		= i2c_int_handler;
	g_irqvector[SPI0_IRQn] 		= spi0_int_handler;
	g_irqvector[SPI1_IRQn] 		= spi0_int_handler;
	g_irqvector[CAN_IRQn] 		= can_int_handler;
	
	g_irqvector[EXILINE0_IRQ_NUM] 	= exiline0_int_handler;
	g_irqvector[EXILINE1_IRQ_NUM] 	= exiline1_int_handler;
	g_irqvector[EXILINE2_IRQ_NUM] 	= exiline2_int_handler;
	g_irqvector[EXILINE3_IRQ_NUM] 	= exiline3_int_handler;
	g_irqvector[EXILINE4_IRQ_NUM] 	= exiline4_int_handler;
	
	g_irqvector[CNTA_IRQn] 			= cnta_int_handler;
	g_irqvector[LPT_IRQn] 			= lpt_int_handler;
	g_irqvector[WWDT_IRQn] 			= wwdt_int_handler;
	g_irqvector[RTC_IRQn] 			= rtc_int_handler;
	g_irqvector[CMP0_IRQn] 			= cmp0_int_handler;
	g_irqvector[CMP1_IRQn] 			= cmp1_int_handler;
	g_irqvector[CMP2_IRQn] 			= cmp2_int_handler;
//	g_irqvector[LED_IRQn] 			= led_int_handler;
	g_irqvector[CORDIC_IRQn] 		= cordic_int_handler;
	g_irqvector[BT0_IRQn] 			= bt0_int_handler;
	g_irqvector[BT1_IRQn] 			= bt1_int_handler;
	g_irqvector[BT2_IRQn] 			= bt2_int_handler;
	g_irqvector[BT3_IRQn] 			= bt3_int_handler;
	
	g_irqvector[I2S0_IRQn] 			= i2s0_int_handler;
	g_irqvector[I2S1_IRQn] 			= i2s1_int_handler;
	
	g_irqvector[MBOX1_INT1_IRQn] 	= mbox1_int1_int_handler; //CPU1 generate
//	g_irqvector[MBOX1_IRQn] 		= mbox1_int_handler;		
	
	g_irqvector[TRNG_IRQn] 			= trng_int_handler;
	g_irqvector[AES_IRQn] 			= aes_int_handler;
	g_irqvector[RSA_IRQn] 			= rsa_int_handler;
	g_irqvector[SHA_IRQn] 			= sha_int_handler;
	
	g_irqvector[USB_IRQn] 			= usb_int_handler;
	
//	g_irqvector[CPU1_MBOX0_IRQn] 	= cpu1_mbox0_int_handler;
//	g_irqvector[CPU1_MBOX1_IRQn] 	= cpu1_mbox1_int_handler;
	g_irqvector[CPU1_BT_IRQn] 		= cpu1_bt_int_handler;  //CPU1 generate
	g_irqvector[CPU1_SPI_IRQn] 		= cpu1_spi_int_handler; //CPU1 generate
	
	g_irqvector[EXILINE5_IRQ_NUM] 	= exiline5_int_handler;
	g_irqvector[EXILINE6_IRQ_NUM] 	= exiline6_int_handler;
	g_irqvector[EXILINE7_IRQ_NUM] 	= exiline7_int_handler;
	g_irqvector[EXILINE8_IRQ_NUM] 	= exiline8_int_handler;
	g_irqvector[EXILINE9_IRQ_NUM] 	= exiline9_int_handler;
	g_irqvector[EXILINE10_IRQ_NUM] 	= exiline10_int_handler;
	g_irqvector[EXILINE11_IRQ_NUM] 	= exiline11_int_handler;
	g_irqvector[EXILINE12_IRQ_NUM] 	= exiline12_int_handler;
	g_irqvector[EXILINE13_IRQ_NUM] 	= exiline13_int_handler;
	g_irqvector[EXILINE14_IRQ_NUM] 	= exiline14_int_handler;
	g_irqvector[EXILINE15_IRQ_NUM] 	= exiline15_int_handler;

//#endif

}
