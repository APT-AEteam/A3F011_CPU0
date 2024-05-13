/***********************************************************************//** 
 * \file  iis_demo.c
 * \brief  IIS_DEMO description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-12-12 <td>V0.0 <td>YT     <td>initial
 * </table>
 * *********************************************************************
*/

#include <string.h>
#include <drv/iis.h>
#include <drv/pin.h>
#include "csp.h"
#include "demo.h"

static uint32_t IISTxBuf[512]={0x01010100,0x55555555,0x00030000,0xaaaaaaaa,0x00050002,0x00060001,0x00070002,0x00080001,0x00090002,0x000a0001,0x000b0002,0x000c0001,0x000d0002,0x000e0001};   //14个数
 uint32_t IISRxBuf[512];



/** \brief Master TX /Slave RX mode ,no interrupt
 * 
 *  \param[in] none
 *  \return error code
 */
void iis_test1_main()
{
	for(int i=14;i<512;i++)
	{
		IISTxBuf[i] = i;
	}
	
	
	
	// 1.配置master tx iis0
	csi_iis_config_t iis_config0;     //配置结构体
	iis_config0.eMode=IIS_TX;   //配置模式：主机发送/主机接收/从机发送/从机接收
	iis_config0.eWorkMode=IIS_MASTER; 
	iis_config0.eSampleRate=IIS_SAMPLERATE_24K;  //配置采样频率 8/16/24/32/44.1/48/96/192kHz
	iis_config0.eDataWidth=IIS_DATAWIDTH_16BIT;  //配置数据位宽 8/16/24/32bit
	iis_config0.eDataAlign=IIS;                 //配置数据对齐格式 IIS/RIGHT_JUSTIFY/LEFT_JUSTIFY/PCM
	iis_config0.eSclkFreq=I2S_SCLK_32FS;     //配置时钟信号 SCLK频率  16/32/48/64。   SCK频率=通道数(一般是2)*量化深度(也叫采样位数)*采样频率
	iis_config0.eMclkFreq=I2S_MCLK_256FS;    //配置主时钟信号 MCLK频率  256/384
	iis_config0.len=sizeof(IISTxBuf);        //配置 发送数量
	iis_config0.eInt=IIS_INTSRC_NONE;       //不用中断

	csi_iis_init(I2S0,&iis_config0); // 主机初始化
	
//	csp_i2s_set_tx_volume_compress_bits(I2S0, 3); //发送数据移位测试
	
//	CODEC->CLKCR |= (0x1<<31  | 0x1<<0);  //使能codec clk和ADC clk（must ！！！！）
	// 2.配置slave rx iis1
	csi_iis_config_t iis_config1;   //配置结构体
	iis_config1.eMode=IIS_RX;  //配置模式：主机发送/主机接收/从机发送/从机接收
	iis_config1.eWorkMode=IIS_SLAVE;
	iis_config1.eSampleRate=IIS_SAMPLERATE_24K;  //配置采样频率 8/16/24/32/44.1/48/96/192kHz
	iis_config1.eDataWidth=IIS_DATAWIDTH_16BIT;  //配置数据位宽 8/16/24/32bit
	iis_config1.eDataAlign=IIS;                 //配置数据对齐格式 IIS/RIGHT_JUSTIFY/LEFT_JUSTIFY/PCM
	iis_config1.eSclkFreq=I2S_SCLK_32FS;        //配置时钟信号 SCLK频率  16/32/48/64。   SCK频率=通道数(一般是2)*量化深度(也叫采样位数)*采样频率
	iis_config1.eMclkFreq=I2S_MCLK_256FS;       //配置主时钟信号 MCLK频率  256/384
	iis_config1.len=sizeof(IISRxBuf);           //配置 发送数量
	iis_config1.eInt=IIS_INTSRC_NONE;          //不用中断
	
	csi_iis_init(I2S1,&iis_config1);    //从机初始化
	
//	csp_i2s_set_rx_volume_compress_bits(I2S1, 3); //接收数据移位测试

	csp_i2s_set_sub_sample_rate_compress(I2S1,I2S_SSRCR_THREE_COMPRESS );  //接收数据压缩测试

	// 用DMA， TX RX data
	csi_etb_init();								//使能ETB模块
	// IISO DMA TX 
	csi_iis_dma_tx_init(I2S0, DMA_CH1, ETB_CH20);
	// IIS1 DMA RX
	csi_iis_dma_rx_init(I2S1, DMA_CH3, ETB_CH24);
	
	CODEC->CLKCR |= (0x1<<31  | 0x1<<0 | 0x1<<8);  //使能codec clk和ADC clk（must ！！！！）
	
		
	csi_iis_send_dma(I2S0, DMA_CH1, (void *)IISTxBuf, 512);     // IISTxBuf搬到IIS0->DR寄存器里面
	csi_iis_recv_dma(I2S1, DMA_CH3, (void*)IISRxBuf,512);       // IIS1->DR寄存器搬到IISRxBuf里面
		
	nop;
	nop;
	nop;
	

	
	while(1)
	{
		
	}

	
}


/** \brief Master RX /Slave TX mode ,no interrupt
 * 
 *  \param[in] none
 *  \return error code
 */
void iis_test2_main()
{
	for(int i=14;i<512;i++)
	{
		IISTxBuf[i] = i;
	}
	
	
	
	*(unsigned int *)(0x40450100) = 0x00000005;  //AUDIO COEDC[DAC_RD_CTRL]=2,DAC不读取数据给模拟模块
	
	// 1.配置master rx iis0
	csi_iis_config_t iis_config0;
	iis_config0.eMode=IIS_RX;
	iis_config0.eWorkMode=IIS_MASTER;
	iis_config0.eSampleRate=IIS_SAMPLERATE_24K;
	iis_config0.eDataWidth=IIS_DATAWIDTH_16BIT;
	iis_config0.eDataAlign=IIS;
	iis_config0.eSclkFreq=I2S_SCLK_32FS;
	iis_config0.eMclkFreq=I2S_MCLK_256FS;   
	iis_config0.len=sizeof(IISRxBuf);
	iis_config0.eInt=IIS_INTSRC_NONE;

	csi_iis_init(I2S0,&iis_config0); 

	
	
	// 2.配置slave tx iis1
	csi_iis_config_t iis_config1;
	iis_config1.eMode=IIS_TX;
	iis_config1.eWorkMode=IIS_SLAVE;
	iis_config1.eSampleRate=IIS_SAMPLERATE_24K;
	iis_config1.eDataWidth=IIS_DATAWIDTH_16BIT;
	iis_config1.eDataAlign=IIS;
	iis_config1.eSclkFreq=I2S_SCLK_32FS;
	iis_config1.eMclkFreq=I2S_MCLK_256FS;
	iis_config1.len=sizeof(IISTxBuf);
	iis_config1.eInt=IIS_INTSRC_NONE;
	csi_iis_init(I2S1,&iis_config1);
	

	// 用DMA， TX RX data
	csi_etb_init();								//使能ETB模块
	// IIS1 DMA TX 
	csi_iis_dma_tx_init(I2S1, DMA_CH1, ETB_CH20);
	// IIS0 DMA RX
	csi_iis_dma_rx_init(I2S0, DMA_CH3, ETB_CH24);
	
	CODEC->CLKCR |= (0x1<<31  | 0x1<<0 | 0x1<<8);  //使能codec clk和ADC clk（must ！！！！）
	
	csi_iis_send_dma(I2S1, DMA_CH1, (void *)IISTxBuf, 512);   // IISTxBuf搬到IIS1->DR寄存器里面
	csi_iis_recv_dma(I2S0, DMA_CH3, (void*)IISRxBuf,512);     // IIS0->DR寄存器搬到IISRxBuf里面
	
	while(1)
	{
		
	}
	
}


extern uint32_t i2s_rx_flag;
/** \brief Master TX /Slave RX mode ,interrupt
 * 
 *  \param[in] none
 *  \return error code
 * 在IIS 中断里调用 iis_irqhandler(IIS0 or IIS1) 函数；
 */
 void iis_test3_main()
{
	for(int i=14;i<512;i++)
	{
		IISTxBuf[i] = i;
	}
	
		
	// 1.配置master tx iis0
	csi_iis_config_t iis_config0;
	iis_config0.eMode=IIS_TX;
	iis_config0.eWorkMode=IIS_MASTER;
	iis_config0.eSampleRate=IIS_SAMPLERATE_48K;
	iis_config0.eDataWidth=IIS_DATAWIDTH_16BIT;
	iis_config0.eDataAlign=IIS;
	iis_config0.eSclkFreq=I2S_SCLK_32FS;
	iis_config0.eMclkFreq=I2S_MCLK_256FS;   
	iis_config0.len=sizeof(IISTxBuf);
	iis_config0.pdata=(uint32_t)&IISTxBuf[0];
	iis_config0.eInt=IIS_INTSRC_TXEIM;   // 中断配置

	csi_iis_init(I2S0,&iis_config0); 
	
	// 2.配置slave rx iis1
	csi_iis_config_t iis_config1;
	iis_config1.eMode=IIS_RX;
	iis_config1.eWorkMode=IIS_SLAVE;
	iis_config1.eSampleRate=IIS_SAMPLERATE_48K;
	iis_config1.eDataWidth=IIS_DATAWIDTH_16BIT;
	iis_config1.eDataAlign=IIS;
	iis_config1.eSclkFreq=I2S_SCLK_32FS;
	iis_config1.eMclkFreq=I2S_MCLK_256FS;
	iis_config1.len=sizeof(IISRxBuf);
	iis_config1.pdata=(uint32_t)&IISRxBuf[0];
	iis_config1.eInt=IIS_INTSRC_RXFIM;
	csi_iis_init(I2S1,&iis_config1);
//	
	csi_irq_enable((uint32_t *)I2S0);
	csi_irq_enable((uint32_t *)I2S1);
	

	CODEC->CLKCR |= (0x1<<31  | 0x1<<0 | 0x1<<8);  //使能codec clk和ADC clk（must ！！！！）

	while (1);
	
}






/** \brief Master TX /Slave RX mode ,x mode fs auto detecetd
 * 
 *  \param[in] none
 *  \return error code
 */
void iis_test4_main()
{
	for(int i=14;i<512;i++)
	{
		IISTxBuf[i] = i;
	}
	CODEC->CLKCR |= (0x1<<31  | 0x1<<0 | 0x1<<8);  //使能codec clk和ADC clk（must ！！！！）
	
	CODEC->DACINCR |= 0x1 <<0 ; //dac输入选择 ，从adc直接过来
	
	// 1.配置master tx iis0
	csi_iis_config_t iis_config0;
	iis_config0.eMode=IIS_TX;
	iis_config0.eWorkMode=IIS_MASTER;
	iis_config0.eSampleRate=IIS_SAMPLERATE_48K;
	iis_config0.eDataWidth=IIS_DATAWIDTH_16BIT;
	iis_config0.eDataAlign=IIS;
	iis_config0.eSclkFreq=I2S_SCLK_32FS;
	iis_config0.eMclkFreq=I2S_MCLK_256FS;   // 错了
	iis_config0.len=sizeof(IISTxBuf);
	iis_config0.pdata=(uint32_t)&IISTxBuf[0];
	iis_config0.eInt=IIS_INTSRC_NONE;

	csi_iis_init(I2S0,&iis_config0); // 配置完了以后应该mclk/sclk/bclk应该有数据

	
	// 2.配置slave rx iis1
	csi_iis_config_t iis_config1;
	iis_config1.eMode=IIS_RX;
	iis_config1.eWorkMode=IIS_SLAVE;
	iis_config1.eSampleRate=IIS_SAMPLERATE_48K;
	iis_config1.eDataWidth=IIS_DATAWIDTH_16BIT;
	iis_config1.eDataAlign=IIS;
	iis_config1.eSclkFreq=I2S_SCLK_32FS;
	iis_config1.eMclkFreq=I2S_MCLK_256FS;
	iis_config1.len=sizeof(IISRxBuf);
	iis_config1.pdata=(uint32_t)&IISRxBuf[0];
	iis_config1.eInt=IIS_INTSRC_IFSCM;
	csi_iis_init(I2S1,&iis_config1);
	
	// 配置FADTLR，AIRAD,DIV3
	csp_i2s_disbale(I2S1);
	csp_i2s_set_div_ref_clk(I2S1, 0x1f);
//	csp_i2s_set_div_sclk(I2S1, 2);  // TEST FOR IFSCM INTERRUPT
	csp_i2s_set_receive_mode_audio_input_rate_detected(I2S1, I2S_AIRAD_EN);
	csp_i2s_set_192k_fs_threshold(I2S1, 0x1);
	csp_i2s_set_64k_fs_threshold(I2S1, 0x3);
	csp_i2s_set_88k_fs_threshold(I2S1, 0x2);
	csp_i2s_set_96k_fs_threshold(I2S1, 0x2);
	
	csp_i2s_enable(I2S1);
	
	
	
	// 不用DMA， TX RX data
		for(int i=0;i<512;i++) 
	{
		
		I2S0->DR=IISTxBuf[i];  //  I2SO 发送 TX
		
		IISRxBuf[i] = I2S1->DR;  // I2S1 接收 RX
	}
	
	
	// 用DMA， TX RX data
	csi_etb_init();								//使能ETB模块
	// IISO DMA TX 
	csi_iis_dma_tx_init(I2S0, DMA_CH1, ETB_CH20);
	// IIS1 DMA RX
	csi_iis_dma_rx_init(I2S1, DMA_CH3, ETB_CH24);
	
	
	csi_iis_send_dma(I2S0, DMA_CH1, (void *)IISTxBuf, 512);
	csi_iis_recv_dma(I2S1, DMA_CH3, (void*)IISRxBuf,512);
	
	while(1)
	{
		
	}
//	return 0;
	
}