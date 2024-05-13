/***********************************************************************//** 
 * \file  codec_demo.c
 * \brief  codec_demo description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2023 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2023-12-1 <td>V0.0 <td>GQQ     <td>initial
 * </table>
 * *********************************************************************
*/

#include "codec.h"
#include <drv/iis.h>


/** \brief codec loopback 例程
 *  \brief 从MIC引脚输入模拟信号，codec编码之后经过I2S发给MCU，MCU再由I2S 经过codec解码之后从耳机输出。
 * 
 *  \param[in] none
 *  \return error code
 */
void codec_loopback_demo(void)
{
	csi_codec_config_t tCodecCfg;
	csi_agccfg_t tAgcCfg;
	csi_vadcfg_t tVadCfg;
	uint32_t wTempData[512];
	
	//init
	tCodecCfg.eClkSrc 		= SRCCLK_PCLK;  		//codec时钟选择PCLK
	tCodecCfg.eInput 		= INPUT_MIC; 		 	//CODEC输入选择MIC输入
	tCodecCfg.eAdcClkDiv 	= CLK_DIV4;				//codec ADC div选择
	tCodecCfg.eOutput 		= OUTPUT_HEADPHONE;		//codec输出选择headphone
	tCodecCfg.eDacClkDiv	= CLK_DIV4;				//codec dacclk div 选择
	tCodecCfg.eHpmode		= HPMD_DIFF;			//codec headphone 模式选择差分输出
	
	csi_codec_init(CODEC, &tCodecCfg);				//初始化CODEC
	
	//mic bias config
	csi_codec_set_mic_biaslvl(CODEC, MICBIAS_LVL_1V8); 
	
	//mic boost config
	csi_codec_set_mic_boost(CODEC, MICBST_GAIN_20DB ,MICBST_GAIN_20DB);//MIC LEFT&right channel gain
	
	csi_codec_adhpf_enable(CODEC);	//使能adc 高通滤波器
	
	//agc config
	tAgcCfg.bLeftEn 	= ENABLE;
	tAgcCfg.bRightEn	= ENABLE;
	tAgcCfg.bZeroCEn	= DISABLE;
	tAgcCfg.bZeroCTOEn	= DISABLE;
	tAgcCfg.eMode		= AGC_MODE_PEAKLIMIT;	//AGC模式选择峰值限制模式
	tAgcCfg.eLvl		= LVL_N6DBFS;			//AGC lvl选择为-6DBFS
	tAgcCfg.eHist		= HIST_LVL_1DB5;		//AGC 增益迟滞设置为 -6dB+1.5dB
	tAgcCfg.eGainMin	= AGC_GAIN_N6DB;		//agc gain min 设置为-6DB
	tAgcCfg.eGainMax	= AGC_GAIN_P6DB;		//AGC GAIN MAX设置为+6dB
	tAgcCfg.eHoldTime	= HOLD_TIME_4DIVFS;		//agc保持时间为 4/fs
	tAgcCfg.eDownStep	= AGC_PLDN_8DIVFS;		//agc,增益减小的时间步长设置8/fs
	tAgcCfg.eUpStep		= AGC_PLUP_8PLUS6DIVFS;	//agc 增益增大的时间步长设置8*6/fs
	
	csi_codec_set_agc(CODEC,&tAgcCfg);
	
	
	//VAD config
	tVadCfg.bVadEn 			= ENABLE;	//使能vad功能
	tVadCfg.eVadTh			= VADTH_N48DBFS;
	tVadCfg.byLeftVadOff 	= 0x1e;	    //配置左声道VAD offset为22.5dBFS
	tVadCfg.byRightVadOff	= 0x1e;	    //配置右声道VAD offset为22.5dBFS
	tVadCfg.eLeftVadHist	= VAD_HIST_6DB;
	tVadCfg.eRightVadHist	= VAD_HIST_6DB;
	tVadCfg.eVadTo			= VAD_TO_4096DIVFS;
	
	csi_codec_set_vad(CODEC, &tVadCfg);
	
	csi_codec_adcdata_wrctrl(CODEC, ADCDATA_WR_TXFIFO); //配置ADC转换完成的数据写到TXFIFO
	
	
	// 1.配置master rx iis0
	csi_iis_config_t iis_config0;				//i2s master 接收到wTempData缓存
	iis_config0.eMode=IIS_RX;
	iis_config0.eWorkMode = IIS_MASTER;
	iis_config0.eSampleRate=IIS_SAMPLERATE_48K;
	iis_config0.eDataWidth=IIS_DATAWIDTH_16BIT;
	iis_config0.eDataAlign=IIS;
	iis_config0.eSclkFreq=I2S_SCLK_32FS;
	iis_config0.eMclkFreq=I2S_MCLK_256FS;   
	iis_config0.len=sizeof(wTempData);
	iis_config0.eInt=IIS_INTSRC_NONE;

	csi_iis_init(I2S0,&iis_config0); 

	
	// 2.配置slave tx iis1
	csi_iis_config_t iis_config1;			//I2s slave 将wTempData的数据发送出去
	iis_config1.eMode=IIS_TX;
	iis_config1.eWorkMode=IIS_SLAVE;
	iis_config1.eSampleRate=IIS_SAMPLERATE_48K;
	iis_config1.eDataWidth=IIS_DATAWIDTH_16BIT;
	iis_config1.eDataAlign=IIS;
	iis_config1.eSclkFreq=I2S_SCLK_32FS;
	iis_config1.eMclkFreq=I2S_MCLK_256FS;
	iis_config1.len=sizeof(wTempData);
	iis_config1.eInt=IIS_INTSRC_NONE;
	csi_iis_init(I2S1,&iis_config1);
	

	// 用DMA， TX RX data
	csi_etb_init();								//使能ETB模块
	// IIS1 DMA TX 
	csi_iis_dma_tx_init(I2S1, DMA_CH1, ETB_CH20);
	// IIS0 DMA RX
	csi_iis_dma_rx_init(I2S0, DMA_CH3, ETB_CH24);
	
	
	csi_iis_send_dma(I2S1, DMA_CH1, (void *)wTempData, 512);   // IISTxBuf搬到IIS1->DR寄存器里面
	csi_iis_recv_dma(I2S0, DMA_CH3, (void*)wTempData,512);     // IIS0->DR寄存器搬到IISRxBuf里面
	
	
	
	////DAC 配置
	csi_codec_dacdata_rdctrl(CODEC, DACDATA_RD_RXFIFO);  //配置DAC从RXFIFO中读取数据给模拟模块
	
	csi_codec_dachpf_enable(CODEC); //使能DAC高通滤波功能
	
	csi_codec_set_dacgain(CODEC, DAC_GAIN_2DB5, DAC_GAIN_2DB5); //配置DAC输出增益
	
	///耳机输出配置
	csi_codec_set_hpgain(CODEC, 0x1f, 0x1f);//设置耳机输出增,1f对应增益-9dB( 0对应-32.25dB，步长0.75dB)
	
}


/** \brief codec 录音例程
 *  \brief 从mic引脚输入模拟信号，经过codec编码之后，通过I2S存储音频数字信号。
 * 
 *  \param[in] none
 *  \return error code
 */
void codec_record_demo(void)
{
	csi_codec_config_t tCodecCfg;
	csi_agccfg_t tAgcCfg;
	csi_vadcfg_t tVadCfg;
	uint32_t wRecordData[512];
	
	
	//init
	tCodecCfg.eClkSrc 		= SRCCLK_PCLK;  		//codec时钟选择PCLK
	tCodecCfg.eInput 		= INPUT_LINE; 		 	//CODEC输入选择LINE输入
	tCodecCfg.eAdcClkDiv 	= CLK_DIV4;				//codec ADC div选择
	tCodecCfg.eOutput 		= OUTPUT_I2SPCM;		//codec输出选择i2s
	tCodecCfg.eDacClkDiv	= CLK_DIV4;				//codec dacclk div 选择
	tCodecCfg.eHpmode		= HPMD_DIFF;			//codec headphone 模式选择差分输出
	
	csi_codec_init(CODEC, &tCodecCfg);				//初始化CODEC
	
	
	csi_codec_adhpf_enable(CODEC);	//使能adc 高通滤波器
	
	//agc config
	tAgcCfg.bLeftEn 	= ENABLE;
	tAgcCfg.bRightEn	= ENABLE;
	tAgcCfg.bZeroCEn	= DISABLE;
	tAgcCfg.bZeroCTOEn	= DISABLE;
	tAgcCfg.eMode		= AGC_MODE_PEAKLIMIT;	//AGC模式选择峰值限制模式
	tAgcCfg.eLvl		= LVL_N6DBFS;			//AGC lvl选择为-6DBFS
	tAgcCfg.eHist		= HIST_LVL_1DB5;		//AGC 增益迟滞设置为 -6dB+1.5dB
	tAgcCfg.eGainMin	= AGC_GAIN_N6DB;		//agc gain min 设置为-6DB
	tAgcCfg.eGainMax	= AGC_GAIN_P6DB;		//AGC GAIN MAX设置为+6dB
	tAgcCfg.eHoldTime	= HOLD_TIME_4DIVFS;		//agc保持时间为 4/fs
	tAgcCfg.eDownStep	= AGC_PLDN_8DIVFS;		//agc,增益减小的时间步长设置8/fs
	tAgcCfg.eUpStep		= AGC_PLUP_8PLUS6DIVFS;	//agc 增益增大的时间步长设置8*6/fs
	
	csi_codec_set_agc(CODEC,&tAgcCfg);
	
	
	//VAD config
	tVadCfg.bVadEn 			= ENABLE;	//使能vad功能
	tVadCfg.eVadTh			= VADTH_N48DBFS;
	tVadCfg.byLeftVadOff 	= 0x1e;	    //配置左声道VAD offset为22.5dBFS
	tVadCfg.byRightVadOff	= 0x1e;	    //配置右声道VAD offset为22.5dBFS
	tVadCfg.eLeftVadHist	= VAD_HIST_6DB;
	tVadCfg.eRightVadHist	= VAD_HIST_6DB;
	tVadCfg.eVadTo			= VAD_TO_4096DIVFS;
	
	csi_codec_set_vad(CODEC, &tVadCfg);
	
	csi_codec_adcdata_wrctrl(CODEC, ADCDATA_WR_TXFIFO); //配置ADC转换完成的数据写到TXFIFO
	
	
	////DAC 配置
	csi_codec_dacdata_rdctrl(CODEC, DACDATA_NORD);  //配置DAC不读取数据给模拟模块
	

	// I2S 配置master rx iis0
	csi_iis_config_t iis_config0;
	iis_config0.eMode=IIS_RX;		//i2s接收ADC输出的数据
	iis_config0.eWorkMode=IIS_MASTER;
	iis_config0.eSampleRate=IIS_SAMPLERATE_48K;
	iis_config0.eDataWidth=IIS_DATAWIDTH_16BIT;
	iis_config0.eDataAlign=PCM;
	iis_config0.eSclkFreq=I2S_SCLK_32FS;
	iis_config0.eMclkFreq=I2S_MCLK_256FS;   
	iis_config0.len=sizeof(wRecordData);
	iis_config0.eInt=IIS_INTSRC_NONE;

	csi_iis_init(I2S0,&iis_config0); 

	

	// 用DMA， TX RX data
	csi_etb_init();								//使能ETB模块
	// IIS1 DMA TX 
	csi_iis_dma_tx_init(I2S1, DMA_CH1, ETB_CH20);


	csi_iis_recv_dma(I2S0, DMA_CH3, (void*)wRecordData,512);     // IIS0->DR寄存器搬到IISRxBuf里面
	
}


/** \brief codec 播放音频例程
 *  \brief 从I2S输入音频数字信号，经过codec解码之后从耳机输出。
 * 
 *  \param[in] none
 *  \return error code
 */
void codec_player_demo(void)
{
	csi_codec_config_t tCodecCfg;
	uint32_t wPlayerData[512]={0,1,2,3};//待更新，音频数据
	
	//init
	tCodecCfg.eClkSrc 		= SRCCLK_PCLK;  		//codec时钟选择PCLK
	tCodecCfg.eInput 		= INPUT_I2SPCM; 		 //CODEC输入选择I2S输入
	tCodecCfg.eAdcClkDiv 	= CLK_DIV4;				//codec ADC div选择
	tCodecCfg.eOutput 		= OUTPUT_HEADPHONE;		//codec输出选择headphone
	tCodecCfg.eDacClkDiv	= CLK_DIV4;				//codec dacclk div 选择
	tCodecCfg.eHpmode		= HPMD_DIFF;			//codec headphone 模式选择差分输出
	
	csi_codec_init(CODEC, &tCodecCfg);				//初始化CODEC
	
	
	////DAC 配置
	csi_codec_dacdata_rdctrl(CODEC, DACDATA_RD_RXFIFO);  //配置DAC从RXFIFO中读取数据给模拟模块
	
	csi_codec_dachpf_enable(CODEC); //使能DAC高通滤波功能
	
	csi_codec_set_dacgain(CODEC, DAC_GAIN_2DB5, DAC_GAIN_2DB5); //配置DAC输出增益
	
	///耳机输出配置
	csi_codec_set_hpgain(CODEC, 0x1f, 0x1f);//设置耳机输出增,1f对应增益-9dB( 0对应-32.25dB，步长0.75dB)
	
	
	
	// i2s 配置slave tx iis1
	csi_iis_config_t iis_config1;   //配置结构体
	iis_config1.eMode=IIS_TX;  //配置模式：主机发送/主机接收/从机发送/从机接收
	iis_config1.eWorkMode=IIS_SLAVE;  
	iis_config1.eSampleRate=IIS_SAMPLERATE_24K;  //配置采样频率 8/16/24/32/44.1/48/96/192kHz
	iis_config1.eDataWidth=IIS_DATAWIDTH_16BIT;  //配置数据位宽 8/16/24/32bit
	iis_config1.eDataAlign=PCM;                 //配置数据对齐格式 IIS/RIGHT_JUSTIFY/LEFT_JUSTIFY/PCM
	iis_config1.eSclkFreq=I2S_SCLK_32FS;        //配置时钟信号 SCLK频率  16/32/48/64。   SCK频率=通道数(一般是2)*量化深度(也叫采样位数)*采样频率
	iis_config1.eMclkFreq=I2S_MCLK_256FS;       //配置主时钟信号 MCLK频率  256/384
	iis_config1.len=sizeof(wPlayerData);           //配置 发送数量
	iis_config1.eInt=IIS_INTSRC_NONE;          //不用中断
	
	csi_iis_init(I2S1,&iis_config1);    //从机初始化
	
	
	// 用DMA， TX RX data
	csi_etb_init();								//使能ETB模块
	// IISO DMA TX 
	csi_iis_dma_tx_init(I2S1, DMA_CH1, ETB_CH20);

	
	csi_iis_send_dma(I2S1, DMA_CH1, (void *)wPlayerData, 512);     // IISTxBuf搬到IIS0->DR寄存器里面
	
}


/** \brief codec 卡拉OK 例程
 *  \brief 从line 引脚输入音频模拟信号，直接旁路到DAC输出级，与I2S输入的背景音混合输出到耳机。
 * 
 *  \param[in] none
 *  \return error code
 */
void codec_karaoke_demo(void)
{
	csi_codec_config_t tCodecCfg;
	uint32_t wPlayerData[512]={0,1,2,3};//待更新，音频数据
	
	//init
	tCodecCfg.eClkSrc 		= SRCCLK_PCLK;  		//codec时钟选择PCLK
	tCodecCfg.eInput 		= INPUT_LINE; 		 	//CODEC输入选择LINE输入
	tCodecCfg.eAdcClkDiv 	= CLK_DIV4;				//codec ADC div选择
	tCodecCfg.eOutput 		= OUTPUT_HEADPHONE;		//codec输出选择headphone
	tCodecCfg.eDacClkDiv	= CLK_DIV4;				//codec dacclk div 选择
	tCodecCfg.eHpmode		= HPMD_DIFF;			//codec headphone 模式选择差分输出
	
	csi_codec_init(CODEC, &tCodecCfg);				//初始化CODEC
	
	//bypass
	csi_codec_adc_bypass_todac(CODEC);				//旁路ADC和DAC
	
	////DAC 配置
	csi_codec_dacdata_rdctrl(CODEC, DACDATA_RD_RXFIFO);  //配置DAC从RXFIFO中读取数据给模拟模块
	
	csi_codec_dachpf_enable(CODEC); //使能DAC高通滤波功能
	
	csi_codec_set_dacgain(CODEC, DAC_GAIN_2DB5, DAC_GAIN_2DB5); //配置DAC输出增益
	
	///耳机输出配置
	csi_codec_set_hpgain(CODEC, 0x1f, 0x1f);//设置耳机输出增,1f对应增益-9dB( 0对应-32.25dB，步长0.75dB)
	
	
	
	// i2s 配置slave tx iis1
	csi_iis_config_t iis_config1;   			//配置结构体
	iis_config1.eMode=IIS_TX;  			//配置模式：主机发送/主机接收/从机发送/从机接收
	iis_config1.eWorkMode=IIS_SLAVE; 
	iis_config1.eSampleRate=IIS_SAMPLERATE_24K;  //配置采样频率 8/16/24/32/44.1/48/96/192kHz
	iis_config1.eDataWidth=IIS_DATAWIDTH_16BIT;  //配置数据位宽 8/16/24/32bit
	iis_config1.eDataAlign=PCM;                 //配置数据对齐格式 IIS/RIGHT_JUSTIFY/LEFT_JUSTIFY/PCM
	iis_config1.eSclkFreq=I2S_SCLK_32FS;        //配置时钟信号 SCLK频率  16/32/48/64。   SCK频率=通道数(一般是2)*量化深度(也叫采样位数)*采样频率
	iis_config1.eMclkFreq=I2S_MCLK_256FS;       //配置主时钟信号 MCLK频率  256/384
	iis_config1.len=sizeof(wPlayerData);        //配置 发送数量
	iis_config1.eInt=IIS_INTSRC_NONE;          //不用中断
	
	csi_iis_init(I2S1,&iis_config1);    		//从机初始化

	
	// 用DMA， TX RX data
	csi_etb_init();								//使能ETB模块
	// IISO DMA TX 
	csi_iis_dma_tx_init(I2S1, DMA_CH1, ETB_CH20);

	
	csi_iis_send_dma(I2S1, DMA_CH1, (void *)wPlayerData, 512);     // IISTxBuf搬到IIS0->DR寄存器里面
	
}