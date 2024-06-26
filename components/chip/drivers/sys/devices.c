/***********************************************************************//** 
 * \file  devices.c
 * \brief  source file for the devices
 * \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-5-13 <td>V0.0  <td>ZJY    <td>initial
 * </table>
 * *********************************************************************
*/
//#include <csi_config.h>
#include <stdio.h>
#include <soc.h>
#include <sys_clk.h>
#include <drv/uart.h>
#include <drv/bt.h>
#include <drv/dma.h>
#include <drv/iic.h>
#include <drv/rtc.h>
#include <drv/spi.h>
#include <drv/adc.h>
#include <drv/gpio.h>
#include <drv/irq.h>
#include <drv/pin.h>


const csi_irqmap_t irq_map[] = {
	
	{CORE_ADDR_BASE,			CORET_IRQn		},
	{AHB_SYSCON_BASE,			SYSCON_IRQ_NUM	},
	{APB_IFC_BASE,				IFC_IRQn		},
    {AHB_ADC0_BASE,             ADC0_IRQn		},
    {AHB_ADC1_BASE,             ADC1_IRQn		},
	{AHB_DMA0_BASE,             DMA0_IRQn		},
    {AHB_DMA1_BASE,             DMA1_IRQn		},
    {APB_GPTA0_BASE,           	GPTA0_IRQn		},
	{APB_GPTA1_BASE,           	GPTA1_IRQn		},
	{APB_GPTA2_BASE,           	GPTA2_IRQn		},
	{APB_GPTA3_BASE,           	GPTA3_IRQn		},
//	{APB_GPTB0_BASE,           	GPTB0_IRQn		},
//	{APB_GPTB1_BASE,           	GPTB1_IRQn		},
//	{APB_GPTB2_BASE,           	GPTB2_IRQn		},
//	{APB_GPTB3_BASE,           	GPTB3_IRQn		},
	{APB_TKEY_BASE,           	TKEY_IRQn		},
	{AHB_DAC_BASE,           	DAC0_IRQn		},
	{APB_EPT_BASE,      	    EPT_IRQn		},
	{APB_USART0_BASE,           USART0_IRQn		},
    {APB_USART1_BASE,           USART1_IRQn		},
	{APB_UART0_BASE,           	UART0_IRQn		},
	{APB_UART1_BASE,           	UART1_IRQn		},
	{APB_UART2_BASE,           	UART2_IRQn		},
	{AHB_QSPI_BASE,           	QSPI_IRQn		},
	{APB_SIO0_BASE,             SIO0_IRQn		},
	{APB_SIO1_BASE,             SIO1_IRQn		},
	{APB_I2C0_BASE,             I2C_IRQn		},
	{APB_SPI0_BASE,             SPI0_IRQn		},
	{APB_SPI1_BASE,             SPI1_IRQn		},
	{APB_CAN_BASE,              CAN_IRQn		},
	{APB_CNTA_BASE,            	CNTA_IRQn		},
	{APB_LPT_BASE,            	LPT_IRQn		},
    {APB_WWDT_BASE,           	WWDT_IRQn		},
	{APB_RTC_BASE,           	RTC_IRQn		},
    {APB_CMP0_BASE,           	CMP0_IRQn		},
    {APB_CMP1_BASE,             CMP1_IRQn		},
	{APB_CMP2_BASE,           	CMP2_IRQn		},
	{AHB_CORDIC_BASE,           CORDIC_IRQn		},
    {APB_BT0_BASE,              BT0_IRQn		},
    {APB_BT1_BASE,              BT1_IRQn		},
    {APB_BT2_BASE,              BT2_IRQn		},
    {APB_BT3_BASE,            	BT3_IRQn		},
	{APB_I2S0_BASE,             I2S0_IRQn		},
    {APB_I2S1_BASE,            	I2S1_IRQn		},
	{CPU1_AHB_MBOX1_BASE,       MBOX1_INT1_IRQn	},
    {AHB_TRNG_BASE,            	TRNG_IRQn		},
	{AHB_AES_BASE,      		AES_IRQn		},
    {AHB_RSA_BASE,            	RSA_IRQn		},
	{AHB_SHA_BASE,      		SHA_IRQn		},
    {AHB_USB_BASE,            	USB_IRQn		},
	{CPU1_APB_BT0_BASE,      	CPU1_BT_IRQn	},
    {CPU1_APB_SPI0_BASE,        CPU1_SPI_IRQn	},
    {0,  						0				}
};

const csi_clkmap_t clk_map[] = {
    {APB_IFC_BASE,				IFC_SYS_CLK		},
    {AHB_ADC0_BASE,				ADC_SYS_CLK		},
    {APB_TKEY_BASE,				TKEY_SYS_CLK	},
    {APB_ETCB_BASE,				ETCB_SYS_CLK	},
    {APB_UART0_BASE,			UART0_SYS_CLK	},
    {APB_UART1_BASE,			UART1_SYS_CLK	},
    {APB_UART2_BASE,			UART2_SYS_CLK	},
	{APB_USART0_BASE,			USART0_SYS_CLK	},
    {APB_USART1_BASE,			USART1_SYS_CLK	},
    {APB_SPI0_BASE,				SPI0_SYS_CLK	},
	{APB_SPI1_BASE,				SPI1_SYS_CLK	},
    {APB_SIO0_BASE,				SIO0_SYS_CLK	},
	{APB_SIO1_BASE,				SIO1_SYS_CLK	},
    {APB_I2C0_BASE,				I2C_SYS_CLK		},
    {APB_WWDT_BASE,				WWDT_SYS_CLK	},
    {APB_RTC_BASE,				RTC_SYS_CLK		},
    {APB_LPT_BASE,				LPT_SYS_CLK		},
    {APB_CNTA_BASE,				CNTA_SYS_CLK	},
    {APB_BT0_BASE,				BTx_SYS_CLK		},
    {APB_BT1_BASE,				BTx_SYS_CLK		},
    {APB_GPTA0_BASE,			GPTA0_SYS_CLK		},
    {APB_EPT_BASE,				EPT_SYS_CLK		},
    {0x00U, 					0xFFFFFFFFU		}
};

