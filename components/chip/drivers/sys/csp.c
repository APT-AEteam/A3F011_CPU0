/***********************************************************************//** 
 * \file  csp.c
 * \brief for debugging and using lower-level driver apis out of CSI
 * \copyright Copyright (C) 2015-2021 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-11-24 <td>V0.0  <td>WNN   <td>initial
 * <tr><td> 2021-5-13  <td>V0.0  <td>ZJY   <td>add *IWDT
 * </table>
 * *********************************************************************
*/

#include "csp.h"
#include "soc.h"

CLIC_Type  		*COREINT 	= (CLIC_Type 	*)(CLIC_BASE);
CORET_Type 		*CORETIMER  = (CORET_Type	*)(CORET_BASE);
csp_ifc_t 		*IFC   		= (csp_ifc_t 	*)(APB_IFC_BASE) ;
csp_syscon_t 	*SYSCON  	= (csp_syscon_t *)(AHB_SYSCON_BASE);
//csp_syscon1_t 	*SYSCON1  	= (csp_syscon1_t *)(AHB_SYSCON_BASE);
csp_etb_t		*ETCB 		= (csp_etb_t 	*)(APB_ETCB_BASE); 
csp_dma_t		*DMA0 		= (csp_dma_t 	*)(AHB_DMA0_BASE); 
csp_dma_t		*DMA1 		= (csp_dma_t 	*)(AHB_DMA1_BASE); 
csp_adc_t 		*ADC0    	= (csp_adc_t 	*)(AHB_ADC0_BASE);
csp_adc_t 		*ADC1    	= (csp_adc_t 	*)(AHB_ADC1_BASE);
csp_gpio_t 		*GPIOA		= (csp_gpio_t	*)(AHB_GPIOA_BASE);
csp_gpio_t 		*GPIOB		= (csp_gpio_t 	*)(AHB_GPIOB_BASE);
csp_gpio_t 		*GPIOC		= (csp_gpio_t 	*)(AHB_GPIOC_BASE);
csp_gpio_t 		*GPIOD		= (csp_gpio_t 	*)(AHB_GPIOD_BASE);
csp_exi_t 		*EXI		= (csp_exi_t 	*)(AHB_EXI_BASE);
csp_usart_t 	*USART0   	= (csp_usart_t 	*)(APB_USART0_BASE);
csp_usart_t 	*USART1   	= (csp_usart_t 	*)(APB_USART1_BASE);
csp_uart_t 		*UART0   	= (csp_uart_t 	*)(APB_UART0_BASE);
csp_uart_t 		*UART1   	= (csp_uart_t 	*)(APB_UART1_BASE);
csp_uart_t 		*UART2   	= (csp_uart_t 	*)(APB_UART2_BASE);
csp_spi_t  		*SPI0     	= (csp_spi_t 	*)(APB_SPI0_BASE);
csp_spi_t  		*SPI1     	= (csp_spi_t 	*)(APB_SPI1_BASE);
csp_qspi_t      *QSPI     	= (csp_qspi_t 	*)(AHB_QSPI_BASE);
csp_sio_t  		*SIO0     	= (csp_sio_t 	*)(APB_SIO0_BASE);
csp_cmp_t  		*CMP0     	= (csp_cmp_t 	*)(APB_CMP0_BASE);
csp_cmp_t  		*CMP1     	= (csp_cmp_t 	*)(APB_CMP1_BASE);
csp_cmp_t  		*CMP2     	= (csp_cmp_t 	*)(APB_CMP2_BASE);
csp_codec_t		*CODEC		= (csp_codec_t	*)(APB_CODEC_BASE);
csp_i2c_t  		*I2C0     	= (csp_i2c_t 	*)(APB_I2C0_BASE);
csp_can_t 		*CAN0    	= (csp_can_t 	*)(APB_CAN_BASE);	
csp_cnta_t  	*CA0      	= (csp_cnta_t 	*)(APB_CNTA_BASE);
csp_gpta_t 		*GPTA0     	= (csp_gpta_t 	*)(APB_GPTA0_BASE);
csp_gpta_t 		*GPTA1     	= (csp_gpta_t 	*)(APB_GPTA1_BASE);
csp_gpta_t 		*GPTA2     	= (csp_gpta_t 	*)(APB_GPTA2_BASE);
csp_gpta_t 		*GPTA3     	= (csp_gpta_t 	*)(APB_GPTA3_BASE);
csp_trng_t      *TRNG		= (csp_trng_t   *)(AHB_TRNG_BASE);
//csp_gptb_t 		*GPTB0     	= (csp_gptb_t 	*)(APB_GPTB0_BASE);
//csp_gptb_t 		*GPTB1     	= (csp_gptb_t 	*)(APB_GPTB1_BASE);
//csp_gptb_t 		*GPTB2     	= (csp_gptb_t 	*)(APB_GPTB2_BASE);
//csp_gptb_t 		*GPTB3     	= (csp_gptb_t 	*)(APB_GPTB3_BASE);
//csp_gptb_t 		*GPTB4     	= (csp_gptb_t 	*)(APB_GPTB4_BASE);


csp_ept_t 		*EPT     	= (csp_ept_t    *)(APB_EPT_BASE);
csp_lpt_t 		*LPT     	= (csp_lpt_t 	*)(APB_LPT_BASE) ;
csp_wwdt_t 		*WWDT      	= (csp_wwdt_t 	*)(APB_WWDT_BASE);
csp_bt_t  		*BT0 	   	= (csp_bt_t 	*)(APB_BT0_BASE) ;
csp_bt_t  		*BT1 	   	= (csp_bt_t 	*)(APB_BT1_BASE) ;
csp_bt_t  		*BT2 	   	= (csp_bt_t 	*)(APB_BT2_BASE) ;
csp_bt_t  		*BT3 	   	= (csp_bt_t 	*)(APB_BT3_BASE) ;
csp_bt_t  		*CPU1_BT    = (csp_bt_t 	*)(CPU1_APB_BT0_BASE) ;
csp_spi_t  		*CPU1_SPI    = (csp_spi_t 	*)(CPU1_APB_SPI0_BASE) ;
csp_i2s_t  		*I2S0 	   	= (csp_i2s_t 	*)(APB_I2S0_BASE) ;   
csp_i2s_t  		*I2S1 	   	= (csp_i2s_t 	*)(APB_I2S1_BASE) ;  //更新驱动后打开
csp_cordic_t  	*CORDIC	   	= (csp_cordic_t 	*)(AHB_CORDIC_BASE) ;
csp_crc_t 		*CRC      	= (csp_crc_t 	*)(AHB_CRC_BASE);
csp_rtc_t 		*RTC      	= (csp_rtc_t 	*)(APB_RTC_BASE);
csp_iwdt_t 		*IWDT		= (csp_iwdt_t 	*)(AHB_SYSCON_BASE);

csp_mbox_t      *MBOX0     =(csp_mbox_t   *)(AHB_MBOX0_BASE);
csp_mbox_t      *MBOX1     =(csp_mbox_t   *)(CPU1_AHB_MBOX1_BASE);
csp_usb_t 		*USBD		= (csp_usb_t 	*)(AHB_USB_BASE);

