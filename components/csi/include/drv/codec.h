/*
 * Copyright (C) 2017-2020 Alibaba Group Holding Limited
 */

/******************************************************************************
 * @file     drv_codec.h
 * @brief    head file for codec
 * @version  V1.0
 * @date     17. Mar 2020
 * @model    codec
 ******************************************************************************/
#ifndef _DRV_CODEC_H_
#define _DRV_CODEC_H_

#include <stdint.h>
#include <stdbool.h>
#include <drv/common.h>
#include <drv/dma.h>
#include "drv/ringbuffer.h"
#include "csp_codec.h"

typedef enum {
    CODEC_EVENT_PERIOD_READ_COMPLETE        = 0U,  ///< A peroid data read complete
    CODEC_EVENT_PERIOD_WRITE_COMPLETE       = 1U,  ///< A peroid data write complete
    CODEC_EVENT_WRITE_BUFFER_EMPTY          = 2U,  ///< Fifo is empty
    CODEC_EVENT_READ_BUFFER_FULL            = 3U,  ///< Fifo is full
    CODEC_EVENT_ERROR_OVERFLOW              = 4U,  ///< Fifo overflow error
    CODEC_EVENT_ERROR_UNDERFLOW             = 5U,  ///< Fifo underflow error
    CODEC_EVENT_ERROR                       = 6U,  ///< Transfer error
} csi_codec_event_t;

typedef enum{
	SRCCLK_PCLK,
	SRCCLK_EXCLK,
} csi_codec_clksrc_e;

typedef enum{
	INPUT_MIC,
	INPUT_LINE,
	INPUT_I2SPCM,
}csi_codec_insrc_e;

typedef enum{
	OUTPUT_HEADPHONE,
	OUTPUT_I2SPCM,	
} csi_codec_out_e;

typedef enum{
	HPMD_SEND_GND,
	HPMD_DIFF,
} csi_codec_hpmd_e;

typedef enum {
	CLK_DIV1,
	CLK_DIV2,
	CLK_DIV4,
	CLK_DIV6,
	CLK_DIV8,
	CLK_DIV10,
	CLK_DIV12,
	CLK_DIV14,
	CLK_DIV16,
	CLK_DIV18,
	CLK_DIV20,
	CLK_DIV22,
	CLK_DIV24,
	CLK_DIV26,
	CLK_DIV28,
	CLK_DIV30,
	CLK_DIV32,
	CLK_DIV34,
	CLK_DIV36,
	CLK_DIV38,
	CLK_DIV40,
	CLK_DIV42,
	CLK_DIV44,
	CLK_DIV46,
	CLK_DIV48,
	CLK_DIV50,
	CLK_DIV52,
	CLK_DIV54,
	CLK_DIV56,
	CLK_DIV58,
	CLK_DIV60,
	CLK_DIV62,
} csi_codec_clkdiv_e;

typedef struct {
	csi_codec_clksrc_e	eClkSrc;		//codec clock source,PCLK/External Clock
	csi_codec_insrc_e 	eInput;			//codec input source select, Mic OR lINE or I2S PCM
	csi_codec_out_e		eOutput;		//codec output select headphone or I2S PCM
	csi_codec_hpmd_e	eHpmode;		//codec headphone mode, single end / diffrential output
	csi_codec_clkdiv_e	eAdcClkDiv;		//when adc module enable , adc clk div ,range(0~1fh) div(1~62)
	csi_codec_clkdiv_e	eDacClkDiv;		//when dac module enable , dac clk div ,range(0~1fh) div(1~62)		
} csi_codec_config_t;



typedef enum{
	MICBST_GAIN_0DB,
	MICBST_GAIN_20DB
} csi_codec_micgain_e;				//mic boost gain enum


typedef enum {
	MICBIAS_LVL_1V57,
	MICBIAS_LVL_1V8,
	MICBIAS_LVL_2V,
	MICBIAS_LVL_2V4,
} csi_micbias_lvl_e;

typedef enum {
	GAINSTEP_NORMALPGA_64DIVFS = 	0,	//NORMAL PGA ENUM
	GAINSTEP_NORMALPGA_96DIVFS = 	1,
	GAINSTEP_NORMALPGA_127DIVFS = 	2,
	GAINSTEP_NORMALPGA_192DIVFS = 	3,
	GAINSTEP_NORMALPGA_256DIVFS = 	4,
	GAINSTEP_NORMALPGA_384DIVFS = 	5,
	GAINSTEP_NORMALPGA_512DIVFS = 	6,
	GAINSTEP_NORMALPGA_1024DIVFS = 	7,
	
	
	GAINSTEP_SOFTMUTE_32DIVFS = 	0,	//SOFT MUTE ENUM
	GAINSTEP_SOFTMUTE_64DIVFS = 	1,	
	GAINSTEP_SOFTMUTE_96DIVFS = 	2,
	GAINSTEP_SOFTMUTE_127DIVFS = 	3,
	GAINSTEP_SOFTMUTE_192DIVFS = 	4,
	GAINSTEP_SOFTMUTE_256DIVFS = 	5,
	GAINSTEP_SOFTMUTE_384DIVFS = 	6,
	GAINSTEP_SOFTMUTE_512DIVFS = 	7,
	
} csi_pga_gainstep_e;

typedef enum{
	AGC_MODE_PEAKLIMIT,
	AGC_MODE_NORMAL,
} csi_agc_md_e;

typedef enum{
	LVL_N24DBFS,
	LVL_N22DBFS5,
	LVL_N21DBFS,
	LVL_N19DBFS5,
	LVL_N18DBFS,
	LVL_N16DBFS5,
	LVL_N15DBFS,
	LVL_N13DBFS5,
	LVL_N12DBFS,
	LVL_N10DBFS5,
	LVL_N9DBFS,
	LVL_N7DBFS5,
	LVL_N6DBFS,
	LVL_N4DBFS5,
	LVL_N3DBFS,
	LVL_N1DBFS5
} csi_agc_lvl_e; //

typedef enum{
	HIST_LVL_0DB,
	HIST_LVL_1DB5,
	HIST_LVL_3DB,
	HIST_LVL_4DB5
} csi_agc_hist_e;

typedef enum{
	AGC_GAIN_N12DB,
	AGC_GAIN_N6DB,
	AGC_GAIN_0DB,
	AGC_GAIN_P6DB,
	AGC_GAIN_P12DB,
}csi_agc_gain_e;


typedef enum{
	HOLD_TIME_1DIVFS,
	HOLD_TIME_4DIVFS,
	HOLD_TIME_16DIVFS,
	HOLD_TIME_64DIVFS,
	HOLD_TIME_256DIVFS,
	HOLD_TIME_1024DIVFS,
	HOLD_TIME_4096DIVFS,
	HOLD_TIME_16384DIVFS,
} csi_agc_hodtime_e;

typedef enum {
	AGC_NMDN_4DIVFS 	= 0,		//AGC NOrmal mode AGC DOWN STEP
	AGC_NMDN_8DIVFS		= 1,
	AGC_NMDN_16DIVFS	= 2,
	AGC_NMDN_32DIVFS	= 3,
	AGC_NMDN_64DIVFS	= 4,
	AGC_NMDN_128DIVFS	= 5,
	AGC_NMDN_256DIVFS	= 6,
	AGC_NMDN_512DIVFS	= 7,
	AGC_NMDN_1024DIVFS	= 8,
	AGC_NMDN_2048DIVFS	= 9,
	AGC_NMDN_4096DIVFS	= 10,

	AGC_PLDN_1DIVFS		= 0,		//AGC NOrmal mode AGC DOWN STEP
	AGC_PLDN_2DIVFS		= 1,
	AGC_PLDN_4DIVFS		= 2,
	AGC_PLDN_8DIVFS		= 3,
	AGC_PLDN_16DIVFS	= 4,
	AGC_PLDN_32DIVFS	= 5,
	AGC_PLDN_64DIVFS	= 6,
	AGC_PLDN_128DIVFS	= 7,
	AGC_PLDN_256DIVFS	= 8,
	AGC_PLDN_512DIVFS	= 9,
	AGC_PLDN_1024DIVFS	= 10,
} csi_agc_dnstep_e;

typedef enum {
	AGC_NMUP_1PLUS24DIVFS 		= 0,		//AGC NOrmal mode AGC UP STEP
	AGC_NMUP_2PLUS24DIVFS		= 1,
	AGC_NMUP_4PLUS24DIVFS 		= 2,
	AGC_NMUP_8PLUS24DIVFS 		= 3,
	AGC_NMUP_16PLUS24DIVFS 		= 4,
	AGC_NMUP_32PLUS24DIVFS 		= 5,
	AGC_NMUP_64PLUS24DIVFS		= 6,
	AGC_NMUP_128PLUS24DIVFS 	= 7,
	AGC_NMUP_256PLUS24DIVFS 	= 8,
	AGC_NMUP_512PLUS24DIVFS 	= 9,
	AGC_NMUP_1024PLUS24DIVFS 	= 10,

	AGC_PLUP_1PLUS6DIVFS 		= 0,		//AGC NOrmal mode AGC UP STEP
	AGC_PLUP_2PLUS6DIVFS		= 1,
	AGC_PLUP_4PLUS6DIVFS 		= 2,
	AGC_PLUP_8PLUS6DIVFS 		= 3,
	AGC_PLUP_16PLUS6DIVFS 		= 4,
	AGC_PLUP_32PLUS6DIVFS 		= 5,
	AGC_PLUP_64PLUS6DIVFS		= 6,
	AGC_PLUP_128PLUS6DIVFS 		= 7,
	AGC_PLUP_256PLUS6DIVFS 		= 8,
	AGC_PLUP_512PLUS6DIVFS 		= 9,
	AGC_PLUP_1024PLUS6DIVFS 	= 10,
} csi_agc_upstep_e;

typedef struct{

	csi_agc_md_e    	eMode; //codec agc mode: peak limit control/normal mode
	csi_agc_lvl_e  		eLvl; //codec agc gain peak select
	csi_agc_hist_e		eHist; //codec agc gain hist select
	csi_agc_gain_e		eGainMax;//codec agc gain max select
	csi_agc_gain_e		eGainMin;//codec agc gain min select
	csi_agc_hodtime_e	eHoldTime; //codec agc hole time select
	csi_agc_dnstep_e	eDownStep;	//codec agc gain down step config
	csi_agc_upstep_e	eUpStep;	//codec agc gain up step config
	
	bool 				bLeftEn;	//left channel AGC enable or disable
	bool 				bRightEn;	//right channel AGC enable or disable
	bool 				bZeroCEn;	//Zero Cross function enable or disable
	bool				bZeroCTOEn; //zero cross time out enable or disable
	
} csi_agccfg_t;


typedef enum{
	VADTH_N36DBFS,
	VADTH_N42DBFS,
	VADTH_N48DBFS,
	VADTH_N54DBFS,
	VADTH_N60DBFS,
	VADTH_N66DBFS,
	VADTH_N72DBFS,
	VADTH_N78DBFS,
} csi_vadth_e;

typedef enum{
	VAD_HIST_0DB,
	VAD_HIST_1DB5,
	VAD_HIST_3DB,
	VAD_HIST_4DB5,
	VAD_HIST_6DB,
	VAD_HIST_7DB5,
	VAD_HIST_9DB,
	VAD_HIST_10DB5,
	VAD_HIST_12DB,
	VAD_HIST_13DB5,
	VAD_HIST_15DB,
	VAD_HIST_16DB5,
	VAD_HIST_18DB,
	VAD_HIST_19DB5,
	VAD_HIST_21DB,
	VAD_HIST_22DB5
} csi_vadhist_e;

typedef enum{
	VAD_TO_2048DIVFS,
	VAD_TO_4096DIVFS,
	VAD_TO_6143DIVFS,
	VAD_TO_11289DIVFS,
	VAD_TO_12288DIVFS,
} csi_vadto_e;

typedef struct {
	csi_vadth_e 	eVadTh; 		//VAD TH
	csi_vadhist_e	eLeftVadHist; 	//left channel VAD HIST
	csi_vadhist_e	eRightVadHist; 	//right channel VAD HIST
	uint8_t			byLeftVadOff;	//left channel vad offset
	uint8_t			byRightVadOff;	//right channel vad offset
	csi_vadto_e		eVadTo;			//vad timeout 
	bool 			bVadEn;			//vad enable or disable	
} csi_vadcfg_t;

typedef enum{
	ADCDATA_WR_RXFIFO,
	ADCDATA_WR_TXFIFO,
	ADCDATA_WR_NOFIFO,
} csi_adcwr_e;

typedef enum{
	DACDATA_RD_TXFIFO,
	DACDATA_RD_RXFIFO,
	DACDATA_NORD,
} csi_dacrd_e;

typedef enum{
	DAC_GAIN_1DB3 = 1,
	DAC_GAIN_2DB5 = 2,
	DAC_GAIN_6DB  = 4,
} csi_dacgain_e;


typedef enum{
	VCMPD_TRI,
	VCMPD_GND,
} csi_vcmpds_e;

typedef enum{
	VCM_CHRG_CURRENT_MIN,
	VCM_CHRG_CURRENT_SEC,
	VCM_CHRG_CURRENT_THR,
	VCM_CHRG_CURRENT_MAX,
} csi_vcmchrg_e;

typedef struct
{
	csi_vcmpds_e 	 eState; //VCM PD state control
	csi_vcmchrg_e 	 eChrgCur; //vcm charge current
//	bool 			 bVcmEn;   //vcm enable
	bool			 bVcmChrgEn; //vcm charge enable
	bool		 	 bBspEn;	//vcm high drive enable
	bool		 	 bAutoBps;  //vcm auto high drive enable
}csi_vcmcfg_t;


typedef enum{
	REF_LVL_1V,
	REF_LVL_1V2,
	REF_LVL_1V5,
	REF_LVL_1V8
} csi_codecref_e;

/**
  \brief       Init the codec according to the specified
  \param[in]   ptCodecBase  Codec handle to operate
  \param[in]   ptCodecCfg    Codec config handle 
  \return      error code \ref csi_error_t
*/
csi_error_t csi_codec_init(csp_codec_t *ptCodecBase, csi_codec_config_t *ptCodecCfg);

/**
  \brief       set left channel & right channel mic gain
  \param[in]   ptCodecBase  Codec handle to operate
  \param[in]   eLGain    Codec left channel mic gain \ref csi_codec_micgain_e
  \param[in]   eRGain    Codec right channel mic gain  \ref csi_codec_micgain_e
  \return      none
*/
void csi_codec_set_mic_boost(csp_codec_t *ptCodecBase, csi_codec_micgain_e eLGain,csi_codec_micgain_e eRGain);

/**
  \brief       set mic bias level and enable mic bias output
  \param[in]   ptCodecBase  Codec handle to operate
  \param[in]   eLvl    Codec mic bias level  \ref csi_micbias_lvl_e
  \return      none
*/
void csi_codec_set_mic_biaslvl(csp_codec_t *ptCodecBase, csi_micbias_lvl_e eLvl);

/**
  \brief       set pga gain TRANS STEP
  \param[in]   ptCodecBase  Codec handle to operate
  \param[in]   eStep codec pga gain trans step \ref csi_pga_gainstep_e
				-normal pga mode,gain trans rate 1.5db/step
				-soft mute mode ,gain trans rate 0.5db/step
  \return      none
*/
void csi_codec_set_pgagain_trans_step(csp_codec_t *ptCodecBase, csi_pga_gainstep_e eStep);

/**
  \brief       enable codec adc high pass filter offset record 
  \param[in]   ptCodecBase  Codec handle to operate
  \return      none
*/
void csi_codec_adhpf_offset_record_enable(csp_codec_t *ptCodecBase);

/**
  \brief       disable codec adc high pass filter offset record
  \param[in]   ptCodecBase  Codec handle to operate
  \return      none
*/
void csi_codec_adhpf_offset_record_disable(csp_codec_t *ptCodecBase);

/**
  \brief       enable codec adc high pass filter 
  \param[in]   ptCodecBase  Codec handle to operate
  \return      none
*/
void csi_codec_adhpf_enable(csp_codec_t *ptCodecBase);

/**
  \brief       disable codec adc high pass filter 
  \param[in]   ptCodecBase  Codec handle to operate
  \return      none
*/
void csi_codec_adhpf_disable(csp_codec_t *ptCodecBase);

/**
  \brief       set codec adc high pass filter cutoff frequency
  \param[in]   ptCodecBase  Codec handle to operate
  \param[in]   wFreq  Codec adc high pass filter cutoff freq	
  \return      CSI_ERROR/CSI_OK
*/
csi_error_t csi_codec_set_adhpf_cutoff(csp_codec_t *ptCodecBase, uint32_t wFreq);

/**
  \brief       enable codec adc dither 
  \param[in]   ptCodecBase  Codec handle to operate
  \return      none
*/
void csi_codec_adc_dither_enable(csp_codec_t *ptCodecBase);

/**
  \brief       disable codec adc dither 
  \param[in]   ptCodecBase  Codec handle to operate
  \return      none
*/
void csi_codec_adc_dither_disable(csp_codec_t *ptCodecBase);

/**
  \brief      enable codec adc output bypass to DAC  
  \param[in]   ptCodecBase  Codec handle to operate
  \return      none
*/
void csi_codec_adc_bypass_todac(csp_codec_t *ptCodecBase);

/**
  \brief       set codec adc high pass filter cutoff frequency
  \param[in]   ptCodecBase  Codec handle to operate
  \param[in]   ptAgcCfg  	pointor to  stucture of Codec auto gain control 	
  \return      CSI_ERROR/CSI_OK
*/
csi_error_t csi_codec_set_agc(csp_codec_t *ptCodecBase, csi_agccfg_t *ptAgcCfg);

/**
  \brief       set codec vad
  \param[in]   ptCodecBase  Codec handle to operate
  \param[in]   ptVadCfg  	pointor to  stucture of Codec voice activity detect 	
  \return      CSI_ERROR/CSI_OK
*/
csi_error_t csi_codec_set_vad(csp_codec_t *ptCodecBase, csi_vadcfg_t *ptVadCfg);

/**
  \brief       ADC LEFT & RIGHT channel soft mute control
  \param[in]   ptCodecBase  Codec handle to operate
  \param[in]   bLeftMute    Codec ADC LEFT channel mute control,ENABLE/DISABLE	
  \param[in]   bRightMute    Codec ADC right channel mute control,ENABLE/DISABLE	
  \return      none
*/
void csi_codec_adcout_softmute(csp_codec_t *ptCodecBase, bool bLeftMute, bool bRightMute);

/**
  \brief       ADC out data write control
  \param[in]   ptCodecBase  Codec handle to operate
  \param[in]   eWrCtrl    	Codec ADC data write control \ref csi_adcwr_e		
  \return      none
*/
void csi_codec_adcdata_wrctrl(csp_codec_t *ptCodecBase, csi_adcwr_e eWrCtrl);

/**
  \brief       DAC in data read control
  \param[in]   ptCodecBase  Codec handle to operate
  \param[in]   eRdCtrl    	Codec dac data read control \ref csi_dacrd_e		
  \return      none
*/
void csi_codec_dacdata_rdctrl(csp_codec_t *ptCodecBase, csi_dacrd_e eRdCtrl);

/**
  \brief       DAC soft mute 
  \param[in]   ptCodecBase  Codec handle to operate		
  \return      none
*/
void csi_codec_dacmute_enable(csp_codec_t *ptCodecBase);

/**
  \brief       disable DAC soft mute 
  \param[in]   ptCodecBase  Codec handle to operate		
  \return      none
*/
void csi_codec_dacmute_disable(csp_codec_t *ptCodecBase);

/**
  \brief       enable DAC high pass filter
  \param[in]   ptCodecBase  Codec handle to operate		
  \return      none
*/
void csi_codec_dachpf_enable(csp_codec_t *ptCodecBase);

/**
  \brief       disable DAC high pass filter
  \param[in]   ptCodecBase  Codec handle to operate		
  \return      none
*/
void csi_codec_dachpf_disable(csp_codec_t *ptCodecBase);

/**
  \brief       codec dac left channel and right channel reset control
  \param[in]   ptCodecBase  Codec handle to operate	
  \param[in]   bLeftRst DAC left channel reset control ,ENABLE/DISABLE	
  \param[in]   bRightRst DAC right channel reset control ,ENABLE/DISABLE	
  \return      none
*/
void csi_codec_dac_softrst(csp_codec_t *ptCodecBase, bool bLeftRst, bool bRightRst);

/**
  \brief       codec dac high pass filter cutoff frequency
  \param[in]   ptCodecBase  Codec handle to operate	
  \param[in]   wFreq		Codec dac high pass filter cutoff freq	 
  \return      CSI_OK/CSI_ERROR
*/
csi_error_t csi_codec_set_dachpf_cutoff(csp_codec_t *ptCodecBase, uint32_t wFreq);

/**
  \brief       codec set dac left channel and right channel gain
  \param[in]   ptCodecBase  Codec handle to operate	
  \param[in]   eLeftGain	Codec dac left channel gain \ref csi_dacgain_e	 
  \param[in]   eRightGain	Codec dac right channel gain \ref csi_dacgain_e	
  \return      none
*/
void csi_codec_set_dacgain(csp_codec_t *ptCodecBase, csi_dacgain_e eLeftGain,csi_dacgain_e eRightGain);

/**
  \brief       codec set headphone left channel and right channel gain
  \param[in]   ptCodecBase  Codec handle to operate	
  \param[in]   byLeft	Codec headphone left channel gain  byLeft~(0,3fh)	gain~(-32.25dB, 15dB) STEP 0.75dB
  \param[in]   byRight	Codec headphone right channel gain byRight~(0,3fh)	gain~(-32.25dB, 15dB) STEP 0.75dB
  \return      CSI_ERROR/CSI_OK
*/
csi_error_t csi_codec_set_hpgain(csp_codec_t *ptCodecBase, uint8_t byLeft,uint8_t byRight);

/**
  \brief       codec set headphone left channel and right channel gain
  \param[in]   ptCodecBase  Codec handle to operate	
  \param[in]   ptVcmCfg 	Pointor to vcm config 
  \return      none
*/
void csi_codec_vcm_cofig(csp_codec_t *ptCodecBase, csi_vcmcfg_t* ptVcmCfg);

/**
  \brief       config codec reference level,and enable
  \param[in]   ptCodecBase  Codec handle to operate	
  \param[in]   eRefLvl 	Codec reference level \ref  csi_codecref_e
  \return      none
*/
void csi_codec_ref_config(csp_codec_t *ptCodecBase, csi_codecref_e eRefLvl);




///**
//  \brief       Codec uninit
//  \param[in]   codec    Codec handle to operate
//  \return      Non
//*/
//void csi_codec_uninit(csp_codec_t *codec);
//
///**
//  \brief       Open a codec output channel
//  \param[in]   codec     Codec handle to operate
//  \param[in]   ch        Codec output channel handle
//  \param[in]   ch_idx    Codec output channel idx
//  \return      error code \ref csi_error_t
//*/
//csi_error_t csi_codec_output_open(csp_codec_t *codec, csi_codec_output_t *ch, uint32_t ch_idx);
//
///**
//  \brief       Config codec output channel
//  \param[in]   ch        Codec output channel handle
//  \param[in]   config    Codec channel param. \ref csi_codec_output_config_t
//  \return      error code \ref csi_error_t
//*/
//csi_error_t csi_codec_output_config(csi_codec_output_t *ch, csi_codec_output_config_t *config);
//
///**
//  \brief       Attach the callback handler to codec output
//  \param[in]   ch     Codec output channel handle
//  \param[in]   cb     Callback function
//  \param[in]   arg    User private param
//  \return      error code \ref csi_error_t
//*/
//csi_error_t csi_codec_output_attach_callback(csi_codec_output_t *ch, void *callback, void *arg);
//
///**
//  \brief       Detach the callback handler
//  \param[in]   ch    Codec output channel handle
//  \return      None
//*/
//void csi_codec_output_detach_callback(csi_codec_output_t *ch);
//
///**
//  \brief       Close a codec output channel
//  \param[in]   ch    Codec output channel handle
//  \return      error code \ref csi_error_t
//*/
//void csi_codec_output_close(csi_codec_output_t *ch);
//
///**
//  \brief       Link DMA channel to codec output channel
//  \param[in]   ch     Codec output channel handle
//  \param[in]   dma    The codec output DMA channel handle, when it is NULL means to unlink the channel
//  \return      error code \ref csi_error_t
//*/
//csi_error_t csi_codec_output_link_dma(csi_codec_output_t *ch, csi_dma_ch_e *dma);
//
///**
//  \brief       Send an amount of data to buffer in blocking mode
//  \param[in]   ch      The codec output channel
//  \param[in]   data    Pointer to send data buffer
//  \param[in]   size    Send data size
//  \return      the num of data witch is send successful
//*/
//uint32_t csi_codec_output_write(csi_codec_output_t *ch, const void *data, uint32_t size);
//
///**
//  \brief       Send data to the buffer with asynchronous sending
//               The data is first written to the buffer and then output through the codec interface
//               This function does not block, and the return value is the number
//               Of data that was successfully written to the buffer
//  \param[in]   ch      The codec output channel
//  \param[in]   data    Pointer to send data buffer
//  \param[in]   size    Send data size
//  \return      The data size that send to buffer
//*/
//uint32_t csi_codec_output_write_async(csi_codec_output_t *ch, const void *data, uint32_t size);
//
///**
//  \brief       Start sending data from the buffer
//  \param[in]   ch    Codec output channel handle
//  \return      error code \ref csi_error_t
//*/
//csi_error_t csi_codec_output_start(csi_codec_output_t *ch);
//
///**
//  \brief       Stop sending data from the buffer
//  \param[in]   ch    Codec output channel handle
//  \return      None
//*/
//void csi_codec_output_stop(csi_codec_output_t *ch);
//
///**
//  \brief       Pause sending data from the buffer
//  \param[in]   ch    Codec output channel handle
//  \return      error code \ref csi_error_t
//*/
//csi_error_t csi_codec_output_pause(csi_codec_output_t *ch);
//
///**
//  \brief       Resume sending data from the buffer
//  \param[in]   ch    Codec output channel handle
//  \return      error code \ref csi_error_t
//*/
//csi_error_t csi_codec_output_resume(csi_codec_output_t *ch);
//
///**
//  \brief       Get buffer free space
//  \param[in]   ch    Codec output channel handle
//  \return      Buffer free space (bytes)
//*/
//uint32_t csi_codec_output_buffer_avail(csi_codec_output_t *ch);
//
///**
//  \brief       Reset the buf, discard all data in the buffer
//  \param[in]   ch    Codec output channel handle
//  \return      error code \ref csi_error_t
//*/
//csi_error_t csi_codec_output_buffer_reset(csi_codec_output_t *ch);
//
///**
//  \brief       Mute codec ouput channel
//  \param[in]   ch    Codec output channel handle
//  \param[in]   en    True enable codec mute. false disable codec mute
//  \return      error code \ref csi_error_t
//*/
//csi_error_t csi_codec_output_mute(csi_codec_output_t *ch, bool enable);
//
///**
//  \brief       Set codec ouput channel digital gain
//  \param[in]   ch     Codec output channel handle
//  \param[in]   val    Gain val
//  \return      error code \ref csi_error_t
//*/
//csi_error_t csi_codec_output_digital_gain(csi_codec_output_t *ch, uint32_t val);
//
///**
//  \brief       Set codec ouput channel analog gain
//  \param[in]   ch     Codec output channel handle
//  \param[in]   val    Gain val
//  \return      error code \ref csi_error_t
//*/
//csi_error_t csi_codec_output_analog_gain(csi_codec_output_t *ch, uint32_t val);
//
///**
//  \brief       Set codec ouput channel mix gain
//  \param[in]   ch     Codec output channel handle
//  \param[in]   val    Gain val
//  \return      error code \ref csi_error_t
//*/
//csi_error_t csi_codec_output_mix_gain(csi_codec_output_t *ch, uint32_t val);
//
///**
//  \brief       Get codec output channel state
//  \param[in]   ch       Codec output channel handle
//  \param[out]  state    Channel state. \ref csi_state_t
//  \return      channel state
//*/
//csi_error_t csi_codec_output_get_state(csi_codec_output_t *ch, csi_state_t *state);
//
///**
//  \brief       Open a codec input channel
//  \param[in]   codec     Codec handle to operate
//  \param[in]   ch        Codec input channel handle
//  \param[in]   ch_idx    Codec input channel idx
//  \return      error code \ref csi_error_t
//*/
//csi_error_t csi_codec_input_open(csp_codec_t *codec, csi_codec_input_t *ch, uint32_t ch_idx);
//
///**
//  \brief       Config codec input channel
//  \param[in]   ch        Codec input channel handle
//  \param[in]   config    Codec channel prarm. \ref csi_codec_input_config_t
//  \return      error code \ref csi_error_t
//*/
//csi_error_t csi_codec_input_config(csi_codec_input_t *ch, csi_codec_input_config_t *config);
//
///**
//  \brief       Attach the callback handler to codec output
//  \param[in]   ch     Codec input channel handle
//  \param[in]   cb     Callback function
//  \param[in]   arg    User private param for event callback
//  \return      error code \ref csi_error_t
//*/
//csi_error_t csi_codec_input_attach_callback(csi_codec_input_t *ch, void *callback, void *arg);
//
///**
//  \brief       Detach the callback handler
//  \param[in]   ch    Codec input channel handle
//  \return      None
//*/
//void csi_codec_input_detach_callback(csi_codec_input_t *ch);
//
///**
//  \brief       Close a codec input channel
//  \param[in]   ch    Codec input channel handle
//  \return      None
//*/
//void csi_codec_input_close(csi_codec_input_t *ch);
//
///**
//  \brief       Link DMA channel to codec input channel
//  \param[in]   ch     Codec input channel handle
//  \param[in]   dma    The codec input DMA channel handle, when it is NULL means to unlink the channel
//  \return      error code \ref csi_error_t
//*/
//csi_error_t csi_codec_input_link_dma(csi_codec_input_t *ch, csi_dma_ch_e *dma);
//
///**
//  \brief       Read an amount of data in blocking mode
//  \param[in]   ch      Codec input channel handle
//  \param[in]   data    Pointer to receive data buffer
//  \param[in]   size    Receive data size
//  \return      The size of data read successfully
//*/
//uint32_t csi_codec_input_read(csi_codec_input_t *ch, void *data, uint32_t size);
//
///**
//  \brief       Read data from the buffer
//               using asynchronous receive
//               this function read data from the buffer, returns the number of successful receive
//               and returns 0 if there is no data in the buffer
//  \param[in]   ch      Codec input channel handle
//  \param[in]   data    Pointer to receive data buffer
//  \param[in]   size    Receive data size
//  \return      The size of data read successfully
//*/
//uint32_t csi_codec_input_read_async(csi_codec_input_t *ch, void *data, uint32_t size);
//
///**
//  \brief       Start receive data to the buffer
//  \param[in]   ch    Codec input channel handle
//  \return      error code \ref csi_error_t
//*/
//csi_error_t csi_codec_input_start(csi_codec_input_t *ch);
//
///**
//  \brief       Stop receive data
//  \param[in]   ch    Codec input channel handle
//  \return      None
//*/
//void csi_codec_input_stop(csi_codec_input_t *ch);
//
///**
//  \brief       Mute codec input channel
//  \param[in]   ch    Codec input channel handle
//  \param[in]   en    True enable codec mute. false disable codec mute
//  \return      error code \ref csi_error_t
//*/
//csi_error_t csi_codec_input_mute(csi_codec_input_t *ch, bool en);
//
///**
//  \brief       Set codec input channel digital gain
//  \param[in]   ch     Codec input channel handle
//  \param[in]   val    Gain val
//  \return      error code \ref csi_error_t
//*/
//csi_error_t csi_codec_input_digital_gain(csi_codec_input_t *ch, uint32_t val);
//
///**
//  \brief       Set codec input channel analog gain
//  \param[in]   ch     Codec input channel handle
//  \param[in]   val    Gain val
//  \return      error code \ref csi_error_t
//*/
//csi_error_t csi_codec_input_analog_gain(csi_codec_input_t *ch, uint32_t val);
//
///**
//  \brief       Set codec input channel mix gain
//  \param[in]   ch     Codec input channel handle
//  \param[in]   val    Gain val
//  \return      error code \ref csi_error_t
//*/
//csi_error_t csi_codec_input_mix_gain(csi_codec_input_t *ch, uint32_t val);
//
///**
//  \brief       Get codec input channel state
//  \param[in]   ch       Codec input channel handle
//  \param[out]  state    Channel state
//  \return      Channel state
//*/
//csi_error_t csi_codec_input_get_state(csi_codec_input_t *ch, csi_state_t *state);
//
///**
//  \brief       Enable codec power manage
//  \param[in]   codec    Codec handle to operate
//  \return      error code \ref csi_error_t
//*/
//csi_error_t csi_codec_enable_pm(csp_codec_t *codec);
//
///**
//  \brief       Disable codec power manage
//  \param[in]   codec    Codec handle to operate
//  \return      None
//*/
//void csi_codec_disable_pm(csp_codec_t *codec);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_CODEC_H_  */

