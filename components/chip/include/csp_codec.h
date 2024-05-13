/***********************************************************************//** 
 * \file  csp_codec.h
 * \brief  CODEC description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2023 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2023-11-21 <td>V0.0  <td>GQQ   <td>initial
 * </table>
 * *********************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CSP_CODEC_H
#define _CSP_CODEC_H

/* Includes ------------------------------------------------------------------*/
#include <soc.h>
#include <stdint.h>

/// \struct csp_codec_t
/// \brief CODEC Reg Description
 typedef struct
 {
    __IOM   uint32_t  IDR;			//0x0000 IP information            
    __IOM   uint32_t  CLKCR;    	//0x0004 ADC Clock Control Register            
    __IOM   uint32_t  ADCINCR;  	//0x0008 ADC Input Control Register  
    __IOM   uint32_t  ADCR0;		//0x000c ADC Control register 0
    __IOM   uint32_t  ADCR1;    	//0x0010 ADC Control Register 1                 
    __IOM  	uint32_t  AGCCTR;  	 	//0x0014 Auto Gain Control Register                     
    __IOM  	uint32_t  VADCR;		//0x0018 Voice Activity Detection Control Register
    __IOM   uint32_t  ADCOUTCR; 	//0x001C ADC Output Control Register             
    __IOM   uint32_t  ADCTESTCR;	//0x0020 ADC Test Control Register    
    __IM   	uint32_t  RSVD0[55];           
    __IOM   uint32_t  DACINCR;  	//0x0100 DAC Input Control Register         
    __IOM   uint32_t  DACR0;    	//0x0104 DAC Control Register 0        
    __IOM   uint32_t  DACR1;    	//0x0108 DAC Control Register 1          
    __IOM  	uint32_t  DACOUTCR; 	//0x010C DAC Output Control Register  
    __IOM  	uint32_t  HPOUTCR;  	//0x0110 HP Gain Control Register      
    __IOM  	uint32_t  DACTESTCR;	//0x0114 DAC Test control Register    
    __IOM  	uint32_t  VCMCR;    	//0x0118 VCM control Register    
    __IOM  	uint32_t  REFCR;    	//0x011C Reference Voltage Control Register             
 } csp_codec_t;

/******************************************************************************
* IDR: IP information
******************************************************************************/
//power down control
#define CODEC_PD_POS	(1)
#define CODEC_PD_MSK	(0x1 << CODEC_PD_POS)	//power down 
#define CODEC_PO		(0x0 << CODEC_PD_POS)	//power on

//reset
#define CODEC_RESET		(1 << 0)


/******************************************************************************
* CLKCR: ADC Clock Control Register
******************************************************************************/
//adc clk en
#define CODEC_ADC_CLKEN_POS		(0)
#define CODEC_ADC_CLKEN_MSK		(0x1 << CODEC_ADC_CLKEN_POS)	//adc clk enable, only when CODEC_CLKEN = 1, ADC CLK can be enabled
#define CODEC_ADC_CLKDIS		(0x0 << CODEC_ADC_CLKEN_POS)	//adc clk disable

//ADC MCLK INVERT
#define CODEC_ADMCLK_INV_POS	(1)
#define CODEC_ADMCLK_INV_MSK	(0x1 << CODEC_ADMCLK_INV_POS)	//adc mclk invert
#define CODEC_ADMCLK_INV_DIS	(0x0 << CODEC_ADMCLK_INV_POS)	//adc mclk do not invert

//ADC DITHER CLK
#define CODEC_ADC_DITHCLK_POS	(2)
#define CODEC_ADC_DITHCLK_MSK	(0x1 << CODEC_ADC_DITHCLK_POS)	

typedef enum{
	CODEC_ADC_DITHCLK_ADCCLK_DIV2, 	//adc dither clk : ADC clock input/2
	CODEC_ADC_DITHCLK_RANDOM		//adc dither clk : random number with fixed average value
} codec_adc_dithclk_e;	

//DAC CLK en
#define CODEC_DAC_CLKEN_POS		(8)
#define CODEC_DAC_CLKEN_MSK		(0x1 << CODEC_DAC_CLKEN_POS)	//dac clk en , only when CODEC_CLKEN = 1, DAC CLK can be enabled
#define CODEC_DAC_CLKDIS		(0x0 << CODEC_DAC_CLKEN_POS)	//dac clk dis

//dac mclk invert
#define CODEC_DAMCLK_INV_POS	(9)
#define CODEC_DAMCLK_INV_MSK	(0x1 << CODEC_DAMCLK_INV_POS)	//DAC mclk invert
#define CODEC_DAMCLK_INV_DIS	(0x0 << CODEC_DAMCLK_INV_POS)	//DAC mclk do not invert

//adc clk div
#define CODEC_ADCCLK_DIV_POS	(10)
#define CODEC_ADCCLK_DIV_MSK	(0x1f << CODEC_ADCCLK_DIV_POS)

//dac clk div
#define CODEC_DACCLK_DIV_POS	(15)
#define CODEC_DACCLK_DIV_MSK	(0x1f << CODEC_DACCLK_DIV_POS)


//codec clk sel
#define CODEC_CLK_SEL_POS		(30)
#define CODEC_CLK_SEL_MSK		(0x1 << CODEC_CLK_SEL_POS)

typedef enum{
	CODEC_CLK_SEL_PCLK,
	CODEC_CLK_SEL_EMOSC		//11.2896M/12.288M due to external clock frequency
}codec_clksel_e;

//codec clk en
#define CODEC_CLKEN_POS			(31)
#define CODEC_CLKEN_MSK			(0x1 << CODEC_CLKEN_POS)
#define CODEC_CLKDIS			(0x0 << CODEC_CLKEN_POS)


/******************************************************************************
* ADCINCR: ADC Input Control Register
******************************************************************************/
//right channel PGA input sel
#define CODEC_RPGA_SEL_POS		(0)
#define CODEC_RPGA_SEL_MSK		(0x1 << CODEC_RPGA_SEL_POS)


//left channel PGA input sel
#define CODEC_LPGA_SEL_POS		(1)
#define CODEC_LPGA_SEL_MSK		(0x1 << CODEC_LPGA_SEL_POS)

typedef enum{
	CODEC_PGA_SEL_MIC,
	CODEC_PGA_SEL_LINE
}codec_pga_input_e;

//left channel mic pd
#define CODEC_LMIC_PD_POS		(2)
#define CODEC_LMIC_PD_MSK		(0x1 << CODEC_LMIC_PD_POS) 		//power down
#define CODEC_LMIC_PO			(0x0 << CODEC_LMIC_PD_POS) 		//power on

//right channel mic pd
#define CODEC_RMIC_PD_POS		(3)
#define CODEC_RMIC_PD_MSK		(0x1 << CODEC_RMIC_PD_POS) 		//power down
#define CODEC_RMIC_PO			(0x0 << CODEC_RMIC_PD_POS) 		//power on

//mic bias powerdown
#define CODEC_MICBIAS_PD_POS	(8)
#define CODEC_MICBIAS_PD_MSK	(0x1 << CODEC_MICBIAS_PD_POS) 	//mic bias power down
#define CODEC_MICBIAS_PO		(0x0 << CODEC_MICBIAS_PD_POS)	//mic bias power on

//mic bias level
#define CODEC_MICBIAS_LVL_POS	(9)
#define CODEC_MICBIAS_LVL_MSK	(0x3 << CODEC_MICBIAS_LVL_POS)

typedef enum{
	CODEC_MICBIAS_1V57,
	CODEC_MICBIAS_1V8,
	CODEC_MICBIAS_2V,
	CODEC_MICBIAS_2V4
} codec_micbias_lvl_e;

//left channel MIC boost gain control
#define CODEC_LMIC_GCON_POS		(12)
#define CODEC_LMIC_GCON_MSK		(0x1 << CODEC_LMIC_GCON_POS)

//right channel MIC boost gain control
#define CODEC_RMIC_GCON_POS		(14)
#define CODEC_RMIC_GCON_MSK		(0x1 << CODEC_RMIC_GCON_POS)

typedef enum{
	CODEC_MIC_GAIN_0DB,
	CODEC_MIC_GAIN_20DB
} codec_mic_gcon_e;

// adc left channel opa gain control  
#define CODEC_LPGA_COG_POS		(16)
#define CODEC_LPGA_COG_MSK		(0x3f << CODEC_LPGA_COG_POS)

// adc right channel opa gain control
#define CODEC_RPGA_COG_POS		(24)
#define CODEC_RPGA_COG_MSK		(0x3f << CODEC_LPGA_COG_POS)

//right channel PGA PD
#define CODEC_RPGA_PD_POS		(30)
#define CODEC_RPGA_PD_MSK		(0x1 << CODEC_RPGA_PD_POS)
#define CODEC_RPGA_PO			(0x0 << CODEC_RPGA_PD_POS)

//LEFT channel PGA PD
#define CODEC_LPGA_PD_POS		(31)
#define CODEC_LPGA_PD_MSK		(0x1 << CODEC_LPGA_PD_POS)
#define CODEC_LPGA_PO			(0x0 << CODEC_LPGA_PD_POS)

/******************************************************************************
* ADCR0: ADC  Control Register 0
******************************************************************************/
// ADC analog module poweron control
#define CODEC_ADC_PD_POS		(0)
#define CODEC_ADC_PD_MSK		(0x1 << CODEC_ADC_PD_POS)
#define CODEC_ADC_PD			(0x0 << CODEC_ADC_PD_POS)
#define CODEC_ADC_PO			(0x1 << CODEC_ADC_PD_POS)

//ADC BYPASS EN
#define CODEC_ADC_BYPASS_POS	(6)
#define CODEC_ADC_BYPASS_MSK	(0x1 << CODEC_ADC_BYPASS_POS)
#define CODEC_ADC_BYPASS_DIS	(0x0 << CODEC_ADC_BYPASS_POS)

//ADC high pass filter en control 
#define CODEC_ADHPF_EN_POS		(16)
#define CODEC_ADHPF_EN_MSK		(0x1 << CODEC_ADHPF_EN_POS)
#define CODEC_ADHPF_DIS			(0x0 << CODEC_ADHPF_EN_POS)

//ADC high pass filter offset record control
#define CODEC_ADHPF_OFR_POS		(21)
#define CODEC_ADHPF_OFR_MSK		(0x1 << CODEC_ADHPF_OFR_POS)
#define CODEC_ADHPF_OFR_DIS		(0x0 << CODEC_ADHPF_OFR_POS)

//ADC DITHER ENABLE
#define CODEC_ADCDITH_EN_POS	(25)
#define CODEC_ADCDITH_EN_MSK	(0x1 << CODEC_ADCDITH_EN_POS)
#define CODEC_ADCDITH_DIS		(0x0 << CODEC_ADCDITH_EN_POS)

//gain trans step config
#define CODEC_TRANS_STEP_POS	(27)
#define CODEC_TRANS_STEP_MSK	(0x7 << CODEC_TRANS_STEP_POS)

typedef enum {
	CODEC_GTRANS_STEP_N64_M32,
	CODEC_GTRANS_STEP_N96_M64,
	CODEC_GTRANS_STEP_N127_M96,
	CODEC_GTRANS_STEP_N192_M127,
	CODEC_GTRANS_STEP_N256_M192,
	CODEC_GTRANS_STEP_N384_M256,
	CODEC_GTRANS_STEP_N512_M384,
	CODEC_GTRANS_STEP_N1024_M512,
}codec_transtep_e;

/******************************************************************************
* ADCR1: ADC  Control Register 1
******************************************************************************/
//ADC High Pass Filter -3dB Gain Cutoff Corner
#define CODEC_ADHPF_CUTOFF_POS	(0)
#define CODEC_ADHPF_CUTOFF_MSK	(0xfff << CODEC_ADHPF_CUTOFF_POS)


/******************************************************************************
* AGCCTR: Auto gain control register
******************************************************************************/
//left channel AGC function en control
#define CODEC_LAGC_EN_POS	(0)
#define CODEC_LAGC_EN_MSK	(0x1 << CODEC_LAGC_EN_POS)
#define CODEC_LAGC_DIS		(0x0 << CODEC_LAGC_EN_POS)

//right channel AGC function en control
#define CODEC_RAGC_EN_POS	(1)
#define CODEC_RAGC_EN_MSK	(0x1 << CODEC_RAGC_EN_POS)
#define CODEC_RAGC_DIS		(0x0 << CODEC_RAGC_EN_POS)

//AGC mode config
#define CODEC_AGC_MODE_POS	(2)
#define CODEC_AGC_MODE_MSK	(0x1 << CODEC_AGC_MODE_POS)

typedef enum{
	CODEC_AGC_PEAKLIMIT_MODE,
	CODEC_AGC_NORMAL_MODE,
} codec_agcmode_e;

//AGC LEVEL SEL
#define CODEC_AGC_LVL_POS	(3)
#define CODEC_AGC_LVL_MSK	(0xf << CODEC_AGC_LVL_POS)

//AGC_LVL2 : Sets the maximum peak gain of hysteresis that exceeds the AGC_LVL setting
#define CODEC_AGC_HYPEAK_POS	(7)
#define CODEC_AGC_HYPEAK_MSK	(0x3 << CODEC_AGC_HYPEAK_POS)
 
typedef enum{
	CODEC_AGC_HYPEAK_0DB,
	CODEC_AGC_HYPEAK_1DB5,
	CODEC_AGC_HYPEAK_3DB,
	CODEC_AGC_HYPEAK_4DB5,
} codec_agchypeak_e;

//AGC min gain sel
#define CODEC_AGC_MIN_POS	(9)
#define CODEC_AGC_MIN_MSK	(0x7 << CODEC_AGC_MIN_POS)
 
//AGC min gain sel
#define CODEC_AGC_MAX_POS	(12)
#define CODEC_AGC_MAX_MSK	(0x7 << CODEC_AGC_MAX_POS)

typedef enum{
	CODEC_AGC_GAIN_N12DB,
	CODEC_AGC_GAIN_N6DB,
	CODEC_AGC_GAIN_0DB,
	CODEC_AGC_GAIN_P6DB,
	CODEC_AGC_GAIN_P12DB
} codec_agcgain_e;

//AGC hold time 
#define CODEC_AGC_HOLD_POS	(15)
#define CODEC_AGC_HOLD_MSK	(0x7 << CODEC_AGC_HOLD_POS)

typedef enum{
	CODEC_AGCHOLD_1FS,
	CODEC_AGCHOLD_4FS,
	CODEC_AGCHOLD_16FS,
	CODEC_AGCHOLD_256FS,
	CODEC_AGCHOLD_1024FS,
	CODEC_AGCHOLD_4096FS,
	CODEC_AGCHOLD_16384FS
} codec_agchold_e;

//AGC signal<AGC_LVL ,time step of gain increase
#define CODEC_AGC_UPSTEP_POS	(18)
#define CODEC_AGC_UPSTEP_MSK	(0xf << CODEC_AGC_UPSTEP_POS)

//AGC signal>AGC_LVL ,time step of gain decrease
#define CODEC_AGC_DNSTEP_POS	(22)
#define CODEC_AGC_DNSTEP_MSK	(0xf << CODEC_AGC_DNSTEP_POS)

//AGC over zero detection function control
#define CODEC_AGC_ZC_POS		(27)
#define CODEC_AGC_ZC_MSK		(0x1 << CODEC_AGC_ZC_POS)
#define CODEC_AGC_ZC_DIS		(0x0 << CODEC_AGC_ZC_POS)

//AGC over zero detection timeout control
#define CODEC_AGC_ZCTO_POS		(28)
#define CODEC_AGC_ZCTO_MSK		(0x1 << CODEC_AGC_ZCTO_POS)
#define CODEC_AGC_ZCTO_DIS		(0x0 << CODEC_AGC_ZCTO_POS)


/******************************************************************************
* VADCR: Voice Activity Detection Control Register
******************************************************************************/
//VAD EN control
#define CODEC_VAD_EN_POS		(0)
#define CODEC_VAD_EN_MSK		(0x1 << CODEC_VAD_EN_POS)
#define CODEC_VAD_DIS			(0x0 << CODEC_VAD_EN_POS)

//VAD detection threshold set
#define CODEC_VAD_TH_POS		(1)
#define CODEC_VAD_TH_MSK		(0x7 << CODEC_VAD_TH_POS)

typedef enum{
	CODEC_VADTH_N36DBFS,
	CODEC_VADTH_N42DBFS,
	CODEC_VADTH_N48DBFS,
	CODEC_VADTH_N54DBFS,
	CODEC_VADTH_N60DBFS,
	CODEC_VADTH_N66DBFS,
	CODEC_VADTH_N72DBFS,
	CODEC_VADTH_N78DBFS
} codec_vadth_e;

//VAD SET left channel noise suppression hysteresis range
#define CODEC_VAD_LHIST_POS		(4)
#define CODEC_VAD_LHIST_MSK		(0xf << CODEC_VAD_LHIST_POS)

//VAD SET right channel noise suppression hysteresis range
#define CODEC_VAD_RHIST_POS		(8)
#define CODEC_VAD_RHIST_MSK		(0xf << CODEC_VAD_RHIST_POS)

//VAD left channel offset setting
#define CODEC_VAD_LOFFSET_POS	(12)
#define CODEC_VAD_LOFFSET_MSK	(0x3f << CODEC_VAD_LOFFSET_POS)

//VAD right channel offset setting
#define CODEC_VAD_ROFFSET_POS	(18)
#define CODEC_VAD_ROFFSET_MSK	(0x3f << CODEC_VAD_ROFFSET_POS)

//VAD timeout setting
#define CODEC_VAD_TO_POS		(27)
#define CODEC_VAD_TO_MSK		(0x7 << CODEC_VAD_TO_POS)

typedef enum{
	CODEC_VADTO_2048DIVFS,  	//Recommended for Fs = 8Khz
	CODEC_VADTO_4096DIVFS,		//Recommended for Fs = 16Khz
	CODEC_VADTO_6143DIVFS,		//Recommended for Fs = 24Khz
	CODEC_VADTO_11289DIVFS,		//Recommended for Fs = 44.1Khz
	CODEC_VADTO_12288DIVFS,		//Recommended for Fs = 48Khz
} codec_vadto_e;

//ADC SOFT MUTE EN
#define CODEC_ADCMU_POS			(30)
#define CODEC_ADCMU_MSK			(0x1 << CODEC_ADCMU_POS)
#define CODEC_ADCMU_DIS			(0x0 << CODEC_ADCMU_POS)

/******************************************************************************
* ADCOUTCR: ADC Output Control Register
******************************************************************************/
//ADC right channel mute control
#define CODEC_ADC_RMUT_POS		(0)
#define CODEC_ADC_RMUT_MSK		(0x1 << CODEC_ADC_RMUT_POS)
#define CODEC_ADC_RMUT_DIS		(0x0 << CODEC_ADC_RMUT_POS)

//ADC left channel mute control
#define CODEC_ADC_LMUT_POS		(1)
#define CODEC_ADC_LMUT_MSK		(0x1 << CODEC_ADC_LMUT_POS)
#define CODEC_ADC_LMUT_DIS		(0x0 << CODEC_ADC_LMUT_POS)

//ADC transfer data write control
#define CODEC_ADC_WR_POS		(2)
#define CODEC_ADC_WR_MSK		(0x3 << CODEC_ADC_WR_POS)

typedef enum{
	COEDC_ADC_WR_RXFIFO,
	CODEC_ADC_WR_TXFIFO,
	CODEC_ADC_WR_NOFIFO,
} codec_adcwr_e;

/******************************************************************************
* ADCTESTCR: ADC TEST Control Register
******************************************************************************/
//bias mode 2 debug control
#define CODEC_ADC_IBCM2D_POS	(0)
#define CODEC_ADC_IBCM2D_MSK	(0x1 << CODEC_ADC_IBCM2D_POS)
#define CODEC_ADC_IBCM2D_DIS	(0x0 << CODEC_ADC_IBCM2D_POS)


//bias mode 1 debug control
#define CODEC_ADC_IB2D_POS		(1)
#define CODEC_ADC_IB2D_MSK		(0x1 << CODEC_ADC_IB2D_POS)
#define CODEC_ADC_IB2D_DIS		(0x0 << CODEC_ADC_IB2D_POS)


/******************************************************************************
* DACINCR: DAC Input Control Register
******************************************************************************/
//dac input select
#define CODEC_DACIN_POS			(0)
#define CODEC_DACIN_MSK			(0x1 << CODEC_DACIN_POS)

typedef enum{
	CODEC_DACIN_DAI,
	CODEC_DACIN_ADC,
} codec_dacin_e;


//dac read control
#define CODEC_DACRD_POS			(1)
#define CODEC_DACRD_MSK			(0x1 << CODEC_DACRD_POS)

typedef enum{
	CODEC_DACRD_TXFIFO,
	CODEC_DACRD_RXFIFO
} codec_dacrd_e;


/******************************************************************************
* DACR0: DAC Control Register 0
******************************************************************************/
//DAC MUTE CONTROL
#define CODEC_DAC_MUTE_POS		(5)
#define CODEC_DAC_MUTE_MSK		(0x1 << CODEC_DAC_MUTE_POS)
#define CODEC_DAC_MUTE_DIS		(0x0 << CODEC_DAC_MUTE_POS)

//DAC BYPASS EN
#define CODEC_DAC_BYPASS_POS	(6)
#define CODEC_DAC_BYPASS_MSK	(0x1 << CODEC_DAC_BYPASS_POS)
#define CODEC_DAC_BYPASS_DIS	(0x0 << CODEC_DAC_BYPASS_POS)

//left channel dac powerdown
#define CODEC_DAC_LPD_POS		(9)
#define CODEC_DAC_LPD_MSK		(0x1 << CODEC_DAC_LPD_POS)
#define CODEC_DAC_LPO			(0x1 << CODEC_DAC_LPD_POS)
#define CODEC_DAC_LPD			(0x0 << CODEC_DAC_LPD_POS)

//right channel dac powerdown
#define CODEC_DAC_RPD_POS		(10)
#define CODEC_DAC_RPD_MSK		(0x1 << CODEC_DAC_RPD_POS)
#define CODEC_DAC_RPO			(0x1 << CODEC_DAC_RPD_POS)
#define CODEC_DAC_RPD			(0x0 << CODEC_DAC_RPD_POS)

//DAC high pass filter
#define CODEC_DAHPF_POS			(16)
#define CODEC_DAHPF_MSK			(0x1 << CODEC_DAHPF_POS)
#define CODEC_DAHPF_DIS			(0x0 << CODEC_DAHPF_POS)

//DAC high pass filter offset record
#define CODEC_DAHPF_OFFR_POS	(21)
#define CODEC_DAHPF_OFFR_MSK	(0x1 << CODEC_DAHPF_POS)
#define CODEC_DAHPF_OFFR_DIS	(0x0 << CODEC_DAHPF_POS)

//DAC soft reset right channel data
#define CODEC_RST_R_POS			(30)
#define CODEC_RST_R_MSK			(0x1 << CODEC_RST_R_POS)

//DAC soft reset left channel data
#define CODEC_RST_L_POS			(30)
#define CODEC_RST_L_MSK			(0x1 << CODEC_RST_L_POS)

/******************************************************************************
* DACR1: DAC Control Register 1
******************************************************************************/
//DAC HIGH PASS FILTER CUTOFF 
#define CODEC_DAHPF_CUTOFF_POS	(0)
#define CODEC_DAHPF_CUTOFF_MSK	(0xfff << CODEC_DAHPF_CUTOFF_POS)

//test left channel dac reson
//todo1

//test right channel dac reson
//todo2

/******************************************************************************
* DACOUTCR: DAC Output Control Register 
******************************************************************************/
//DAC right channel gain control
#define CODEC_DAC_RGAIN_POS		(11)
#define CODEC_DAC_RGAIN_MSK		(0x7 << CODEC_DAC_RGAIN_POS)

//dac left channel gain control
#define CODEC_DAC_LGAIN_POS		(17)
#define CODEC_DAC_LGAIN_MSK		(0x7 << CODEC_DAC_LGAIN_POS)

typedef enum{
	CODEC_DAC_GAIN_1DB3 = 1,
	CODEC_DAC_GAIN_2DB5 = 2,
	CODEC_DAC_GAIN_6DB  = 4,	
} codec_dac_gain_e;

/******************************************************************************
* HPOUTCR: Headphone Output Control Register 
******************************************************************************/
//headphone right channel gain control
#define CODEC_HP_RVOL_POS		(0)
#define CODEC_HP_RVOL_MSK		(0x3f << CODEC_HP_RVOL_POS)

//headphone left channel gain control
#define CODEC_HP_LVOL_POS		(6)
#define CODEC_HP_LVOL_MSK		(0x3f << CODEC_HP_LVOL_POS)

//headphone right channel positive powerdown control
#define CODEC_HP_RP_POS			(12)
#define CODEC_HP_RP_MSK			(0x1 << CODEC_HP_RP_POS)
#define CODEC_HP_RP_PD			(0x0 << CODEC_HP_RP_POS)

//headphone right channel negtive powerdown control
#define CODEC_HP_RN_POS			(13)
#define CODEC_HP_RN_MSK			(0x1 << CODEC_HP_RN_POS)
#define CODEC_HP_RN_PD			(0x0 << CODEC_HP_RN_POS)

//headphone left channel positive powerdown control
#define CODEC_HP_LP_POS			(12)
#define CODEC_HP_LP_MSK			(0x1 << CODEC_HP_LP_POS)
#define CODEC_HP_LP_PD			(0x0 << CODEC_HP_LP_POS)

//headphone left channel negtive powerdown control
#define CODEC_HP_LN_POS			(13)
#define CODEC_HP_LN_MSK			(0x1 << CODEC_HP_LN_POS)
#define CODEC_HP_LN_PD			(0x0 << CODEC_HP_LN_POS)

//Headphone output mode select
#define CODEC_HP_MD_POS			(31)
#define CODEC_HP_MD_MSK			(0x1 << CODEC_HP_MD_POS)

typedef enum{
	CODEC_HPMD_SOUT_VGND,
	CODEC_HPMD_DOUT,
} codec_hpmd_e;

/******************************************************************************
* HPOUTCR: Headphone Output Control Register 
******************************************************************************/
//todo 5

/******************************************************************************
* VCMCR: VCM Control Register 
******************************************************************************/
//VCM state control when powerdown
#define CODEC_VCMPD_STA_POS		(0)
#define CODEC_VCMPD_STA_MSK		(0x1 << CODEC_VCMPD_STA_POS)

typedef enum{
	CODEC_VCMPD_TRI,
	CODEC_VCMPD_GND
} codec_vcmpd_state_e;

//VCM enable
#define CODEC_VCM_POS			(1)
#define CODEC_VCM_MSK			(0x1 << CODEC_VCM_POS)
#define CODEC_VCM_PD			(0x0 << CODEC_VCM_POS)

//VCM charge en/dis
#define CODEC_VCM_CHRG_POS		(2)
#define CODEC_VCM_CHRG_MSK		(0x1 << CODEC_VCM_CHRG_POS)
#define CODEC_VCM_CHRG_DIS		(0x0 << CODEC_VCM_CHRG_POS)

//VCM charge current config
#define CODEC_VCM_CHGON_POS		(3)
#define CODEC_VCM_CHGON_MSK		(0x3 << CODEC_VCM_CHGON_POS)

typedef enum{
	CODEC_VCM_CHGCUR_MIN,
	CODEC_VCM_CHGCUR_SEC,
	CODEC_VCM_CHGCUR_THR,
	CODEC_VCM_CHGCUR_MAX,
	
}codec_vcm_chgcur_e;

//VCM manually intensive drive
#define CODEC_VCM_BPS_POS		(5)
#define CODEC_VCM_BPS_MSK		(0x1 << CODEC_VCM_BPS_POS)
#define CODEC_VCM_BPS_DIS		(0x0 << CODEC_VCM_BPS_POS)

//VCM AUTO intensive drive
#define CODEC_VCM_AUTOBPS_POS	(6)
#define CODEC_VCM_AUTOBPS_MSK	(0x1 << CODEC_VCM_AUTOBPS_POS)
#define CODEC_VCM_AUTOBPS_DIS	(0x0 << CODEC_VCM_AUTOBPS_POS)

//VCM ready OR NOT
#define CODEC_VCM_RDY_POS		(7)
#define CODEC_VCM_RDY_MSK		(0x1 << CODEC_VCM_RDY_POS)

/******************************************************************************
* REFCR: reference Control Register 
******************************************************************************/
//reference voltage level select
#define CODEC_REFLVL_POS		(0)
#define CODEC_REFLVL_MSK		(0x3 << CODEC_REFLVL_POS)

typedef enum{
	CODEC_REFLVL_1V,
	CODEC_REFLVL_1V2,
	CODEC_REFLVL_1V5,
	CODEC_REFLVL_1V8	
} codec_reflvl_e;

//reference voltage power down control
#define CODEC_REF_PD_POS		(2)
#define CODEC_REF_PD_MSK		(0x1 << CODEC_REF_PD_POS)
#define CODEC_REF_PO			(0x0 << CODEC_REF_PD_POS)

/******************************************************************************
* static inline functions
******************************************************************************/
//IDR Register
static inline void csp_codec_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->IDR = CODEC_PO;
}

static inline void csp_codec_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->IDR = CODEC_PD_MSK;
}

static inline void csp_codec_reset(csp_codec_t* ptCodecBase)
{
	ptCodecBase->IDR = CODEC_RESET;
}

//CLKCR Register
static inline void csp_codec_adcclk_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->CLKCR = (ptCodecBase->CLKCR & (~CODEC_ADC_CLKEN_MSK)) | CODEC_ADC_CLKEN_MSK;
}

static inline void csp_codec_adcclk_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->CLKCR = (ptCodecBase->CLKCR & (~CODEC_ADC_CLKEN_MSK)) | CODEC_ADC_CLKDIS;
}

static inline void csp_codec_admclk_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->CLKCR = (ptCodecBase->CLKCR & (~CODEC_ADMCLK_INV_MSK)) | CODEC_ADMCLK_INV_MSK;
}

static inline void csp_codec_admclk_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->CLKCR = (ptCodecBase->CLKCR & (~CODEC_ADMCLK_INV_MSK)) | CODEC_ADMCLK_INV_DIS;
}

static inline void csp_codec_adc_dithclk_config(csp_codec_t* ptCodecBase,codec_adc_dithclk_e eDithClk)
{
	ptCodecBase->CLKCR = (ptCodecBase->CLKCR & (~CODEC_ADC_DITHCLK_MSK)) | (eDithClk << CODEC_ADC_DITHCLK_POS);
}

static inline void csp_codec_dacclk_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->CLKCR = (ptCodecBase->CLKCR &(~CODEC_DAC_CLKEN_MSK)) | CODEC_DAC_CLKEN_MSK;
}

static inline void csp_codec_dacclk_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->CLKCR = (ptCodecBase->CLKCR &(~CODEC_DAC_CLKEN_MSK)) | CODEC_DAC_CLKDIS;
}

static inline void csp_codec_damclk_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->CLKCR = (ptCodecBase->CLKCR & (~CODEC_DAMCLK_INV_MSK)) | CODEC_DAMCLK_INV_MSK;
}

static inline void csp_codec_damclk_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->CLKCR = (ptCodecBase->CLKCR & (~CODEC_DAMCLK_INV_MSK)) | CODEC_DAMCLK_INV_DIS;
}

static inline void csp_codec_adcclk_div_config(csp_codec_t* ptCodecBase, uint8_t byDiv) //byDiv <= 0x1f
{
	ptCodecBase->CLKCR = (ptCodecBase->CLKCR & (~CODEC_ADCCLK_DIV_MSK))|( byDiv << CODEC_ADCCLK_DIV_POS);
}

static inline void csp_codec_dacclk_div_config(csp_codec_t* ptCodecBase, uint8_t byDiv) //byDiv <= 0x1f
{
	ptCodecBase->CLKCR = (ptCodecBase->CLKCR & (~CODEC_DACCLK_DIV_MSK))|( byDiv << CODEC_DACCLK_DIV_POS);
}

static inline void csp_codec_clk_sel(csp_codec_t* ptCodecBase, codec_clksel_e eClk)
{
	ptCodecBase->CLKCR = (ptCodecBase->CLKCR &(~CODEC_CLK_SEL_MSK)) | (eClk << CODEC_CLK_SEL_POS);
}

static inline void csp_codec_clk_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->CLKCR = (ptCodecBase->CLKCR & (~CODEC_CLKEN_MSK)) | CODEC_CLKEN_MSK;
}

static inline void csp_codec_clk_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->CLKCR = (ptCodecBase->CLKCR & (~CODEC_CLKEN_MSK)) | CODEC_CLKDIS;
}

////ADCINCR
static inline void csp_codec_rpga_sel(csp_codec_t* ptCodecBase, codec_pga_input_e eInput)
{
	ptCodecBase->ADCINCR = (ptCodecBase->ADCINCR & (~CODEC_RPGA_SEL_MSK)) | (eInput <<CODEC_RPGA_SEL_POS);
}

static inline void csp_codec_lpga_sel(csp_codec_t* ptCodecBase, codec_pga_input_e eInput)
{
	ptCodecBase->ADCINCR = (ptCodecBase->ADCINCR & (~CODEC_LPGA_SEL_MSK)) | (eInput <<CODEC_LPGA_SEL_POS);
}

static inline void csp_codec_lmic_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->ADCINCR = (ptCodecBase->ADCINCR & (~CODEC_LMIC_PD_MSK)) | CODEC_LMIC_PD_MSK ;
}

static inline void csp_codec_lmic_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->ADCINCR = (ptCodecBase->ADCINCR & (~CODEC_LMIC_PD_MSK)) | CODEC_LMIC_PO ;
}

static inline void csp_codec_rmic_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->ADCINCR = (ptCodecBase->ADCINCR & (~CODEC_RMIC_PD_MSK)) | CODEC_RMIC_PD_MSK ;
}

static inline void csp_codec_rmic_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->ADCINCR = (ptCodecBase->ADCINCR & (~CODEC_RMIC_PD_MSK)) | CODEC_RMIC_PO ;
}

static inline void csp_codec_micbias_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->ADCINCR = (ptCodecBase->ADCINCR & (~CODEC_MICBIAS_PD_MSK)) | CODEC_MICBIAS_PO ;
}

static inline void csp_codec_micbias_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->ADCINCR = (ptCodecBase->ADCINCR & (~CODEC_MICBIAS_PD_MSK)) | CODEC_MICBIAS_PD_MSK ;
}

static inline void csp_codec_micbias_lvl_config(csp_codec_t* ptCodecBase, codec_micbias_lvl_e eBiasLvl)
{
	ptCodecBase->ADCINCR =(ptCodecBase->ADCINCR & (~CODEC_MICBIAS_LVL_MSK)) | (eBiasLvl << CODEC_MICBIAS_LVL_POS);
}

static inline void csp_codec_lmic_boostgain_config(csp_codec_t* ptCodecBase, codec_mic_gcon_e eGain)
{
	ptCodecBase->ADCINCR = (ptCodecBase->ADCINCR & (~CODEC_LMIC_GCON_MSK)) | (eGain << CODEC_LMIC_GCON_POS);
}

static inline void csp_codec_rmic_boostgain_config(csp_codec_t* ptCodecBase, codec_mic_gcon_e eGain)
{
	ptCodecBase->ADCINCR = (ptCodecBase->ADCINCR & (~CODEC_RMIC_GCON_MSK)) | (eGain << CODEC_RMIC_GCON_POS);
}

static inline void csp_codec_lgain_config(csp_codec_t* ptCodecBase, uint8_t byGain) //byGain <= 0x3f
{
	ptCodecBase->ADCINCR = (ptCodecBase->ADCINCR & (~CODEC_LPGA_COG_MSK)) | (byGain << CODEC_LPGA_COG_POS);
}

static inline void csp_codec_rgain_config(csp_codec_t* ptCodecBase, uint8_t byGain) //byGain <= 0x3f
{
	ptCodecBase->ADCINCR = (ptCodecBase->ADCINCR & (~CODEC_RPGA_COG_MSK)) | (byGain << CODEC_RPGA_COG_POS);
}

static inline void csp_codec_rpga_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->ADCINCR = (ptCodecBase->ADCINCR & (~CODEC_RPGA_PD_MSK)) | CODEC_RPGA_PO;
}

static inline void csp_codec_rpga_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->ADCINCR = (ptCodecBase->ADCINCR & (~CODEC_RPGA_PD_MSK)) | CODEC_RPGA_PD_MSK;
}

static inline void csp_codec_lpga_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->ADCINCR = (ptCodecBase->ADCINCR & (~CODEC_LPGA_PD_MSK)) | CODEC_LPGA_PO;
}

static inline void csp_codec_lpga_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->ADCINCR = (ptCodecBase->ADCINCR & (~CODEC_LPGA_PD_MSK)) | CODEC_LPGA_PD_MSK;
}

//ADCR0
static inline void csp_codec_adc_analog_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->ADCR0 = (ptCodecBase->ADCR0 & (~CODEC_ADC_PD_MSK)) | CODEC_ADC_PO;
}

static inline void csp_codec_adc_analog_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->ADCR0 = (ptCodecBase->ADCR0 & (~CODEC_ADC_PD_MSK)) | CODEC_ADC_PD;
}

static inline void csp_codec_adc_bypass_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->ADCR0 = (ptCodecBase->ADCR0 & (~CODEC_ADC_BYPASS_MSK)) | CODEC_ADC_BYPASS_MSK;
}

static inline void csp_codec_adc_bypass_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->ADCR0 = (ptCodecBase->ADCR0 & (~CODEC_ADC_BYPASS_MSK)) | CODEC_ADC_BYPASS_DIS;
}

static inline void csp_codec_adc_hpf_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->ADCR0 = (ptCodecBase->ADCR0 & (~CODEC_ADHPF_EN_MSK)) | CODEC_ADHPF_EN_MSK;
}

static inline void csp_codec_adc_hpf_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->ADCR0 = (ptCodecBase->ADCR0 & (~CODEC_ADHPF_EN_MSK)) | CODEC_ADHPF_DIS;
}

static inline void csp_codec_adchpf_record_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->ADCR0 = (ptCodecBase->ADCR0 & (~CODEC_ADHPF_OFR_MSK)) | CODEC_ADHPF_OFR_MSK;
}

static inline void csp_codec_adchpf_record_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->ADCR0 = (ptCodecBase->ADCR0 & (~CODEC_ADHPF_OFR_MSK)) | CODEC_ADHPF_OFR_DIS;
}

static inline void csp_codec_adcdither_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->ADCR0 = (ptCodecBase->ADCR0 & (~CODEC_ADCDITH_EN_MSK)) | CODEC_ADCDITH_EN_MSK;
}

static inline void csp_codec_adcdither_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->ADCR0 = (ptCodecBase->ADCR0 & (~CODEC_ADCDITH_EN_MSK)) | CODEC_ADCDITH_DIS;
}

static inline void csp_codec_gtranstep_config(csp_codec_t* ptCodecBase , codec_transtep_e eStep)
{
	ptCodecBase->ADCR0 = (ptCodecBase->ADCR0 &(~CODEC_TRANS_STEP_MSK)) | (eStep << CODEC_TRANS_STEP_POS);
}

///ADCR1
static inline void csp_codec_adhpf_cutoff_config(csp_codec_t* ptCodecBase, uint32_t wFreq)
{
	ptCodecBase->ADCR1 = (ptCodecBase->ADCR1 & (~CODEC_ADHPF_CUTOFF_MSK)) | (wFreq << CODEC_ADHPF_CUTOFF_POS);
}

//AGCCTR
static inline void csp_codec_lagc_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->AGCCTR = (ptCodecBase->AGCCTR & (~CODEC_LAGC_EN_MSK)) | CODEC_LAGC_EN_MSK;
}

static inline void csp_codec_lagc_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->AGCCTR = (ptCodecBase->AGCCTR & (~CODEC_LAGC_EN_MSK)) | CODEC_LAGC_DIS;
}

static inline void csp_codec_ragc_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->AGCCTR = (ptCodecBase->AGCCTR & (~CODEC_RAGC_EN_MSK)) | CODEC_RAGC_EN_MSK;
}

static inline void csp_codec_ragc_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->AGCCTR = (ptCodecBase->AGCCTR & (~CODEC_RAGC_EN_MSK)) | CODEC_RAGC_DIS;
}

static inline void csp_codec_agcmode_config(csp_codec_t* ptCodecBase, codec_agcmode_e eMode)
{
	ptCodecBase->AGCCTR = (ptCodecBase->AGCCTR & (~CODEC_AGC_MODE_MSK)) | (eMode << CODEC_AGC_MODE_POS);
}

static inline void csp_codec_agclvl_config(csp_codec_t* ptCodecBase, uint8_t byGain) //byGain <= 0xf
{
	ptCodecBase->AGCCTR = (ptCodecBase->AGCCTR &(~CODEC_AGC_LVL_MSK)) | (byGain << CODEC_AGC_LVL_POS);
}

static inline void csp_codec_agchypeak_config(csp_codec_t* ptCodecBase, codec_agchypeak_e eGain)
{
	ptCodecBase->AGCCTR = (ptCodecBase->AGCCTR & (~CODEC_AGC_HYPEAK_MSK)) | (eGain << CODEC_AGC_HYPEAK_POS);
}

static inline void csp_codec_agc_mingain_config(csp_codec_t* ptCodecBase, codec_agcgain_e eGain)
{
	ptCodecBase->AGCCTR = (ptCodecBase->AGCCTR & (~CODEC_AGC_MIN_MSK)) | (eGain << CODEC_AGC_MIN_POS);
}
static inline void csp_codec_agc_maxgain_config(csp_codec_t* ptCodecBase, codec_agcgain_e eGain)
{
	ptCodecBase->AGCCTR = (ptCodecBase->AGCCTR & (~CODEC_AGC_MAX_MSK)) | (eGain << CODEC_AGC_MAX_POS);
}

static inline void csp_codec_agchold_config(csp_codec_t* ptCodecBase, codec_agchold_e eHold)
{
	ptCodecBase->AGCCTR = (ptCodecBase->AGCCTR & (~CODEC_AGC_HOLD_MSK)) | (eHold << CODEC_AGC_HOLD_POS);
}

static inline void csp_codec_agc_upstep_config(csp_codec_t* ptCodecBade, uint8_t byStep) //byStep <= 0xa
{
	ptCodecBade->AGCCTR = (ptCodecBade->AGCCTR & (~CODEC_AGC_UPSTEP_MSK)) | (byStep << CODEC_AGC_UPSTEP_POS);
}

static inline void csp_codec_agc_dnstep_config(csp_codec_t* ptCodecBade, uint8_t byStep) //byStep <= 0xa
{
	ptCodecBade->AGCCTR = (ptCodecBade->AGCCTR & (~CODEC_AGC_DNSTEP_MSK)) | (byStep << CODEC_AGC_DNSTEP_POS);
}

static inline void csp_codec_agc_overzero_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->AGCCTR = (ptCodecBase->AGCCTR & (~CODEC_AGC_ZC_MSK)) | CODEC_AGC_ZC_MSK;
}

static inline void csp_codec_agc_overzero_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->AGCCTR = (ptCodecBase->AGCCTR & (~CODEC_AGC_ZC_MSK)) | CODEC_AGC_ZC_DIS;
}

static inline void csp_codec_agc_ovzeroto_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->AGCCTR = (ptCodecBase->AGCCTR & (~CODEC_AGC_ZCTO_MSK)) | CODEC_AGC_ZCTO_MSK;
}

static inline void csp_codec_agc_ovzeroto_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->AGCCTR = (ptCodecBase->AGCCTR & (~CODEC_AGC_ZCTO_MSK)) | CODEC_AGC_ZCTO_DIS;
}

//VADCR
static inline void csp_codec_vad_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->VADCR = (ptCodecBase->VADCR &(~CODEC_VAD_EN_MSK)) | CODEC_VAD_EN_MSK;
}

static inline void csp_codec_vad_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->VADCR = (ptCodecBase->VADCR &(~CODEC_VAD_EN_MSK)) | CODEC_VAD_DIS;
}

static inline void csp_codec_set_vad_threshold(csp_codec_t* ptCodecBase, codec_vadth_e eThreshold)
{
	ptCodecBase->VADCR = (ptCodecBase->VADCR & (~CODEC_VAD_TH_MSK)) | (eThreshold << CODEC_VAD_TH_POS);
}

static inline void csp_codec_set_vad_lhist(csp_codec_t* ptCodecBase, uint8_t byRange)
{
	ptCodecBase->VADCR = (ptCodecBase->VADCR & (~CODEC_VAD_LHIST_MSK)) | (byRange << CODEC_VAD_LHIST_POS);
}

static inline void csp_codec_set_vad_rhist(csp_codec_t* ptCodecBase, uint8_t byRange)
{
	ptCodecBase->VADCR = (ptCodecBase->VADCR & (~CODEC_VAD_RHIST_MSK)) | (byRange << CODEC_VAD_RHIST_POS);
}

static inline void csp_codec_set_vad_loffset(csp_codec_t* ptCodecBase, uint8_t byOffset)
{
	ptCodecBase->VADCR = (ptCodecBase->VADCR & (~CODEC_VAD_LOFFSET_MSK)) | (byOffset << CODEC_VAD_LOFFSET_POS);
}

static inline void csp_codec_set_vad_roffset(csp_codec_t* ptCodecBase, uint8_t byOffset)
{
	ptCodecBase->VADCR = (ptCodecBase->VADCR & (~CODEC_VAD_ROFFSET_MSK)) | (byOffset << CODEC_VAD_ROFFSET_POS);
}

static inline void csp_codec_set_vad_timeout(csp_codec_t* ptCodecBase, codec_vadto_e eTimeout)
{
	ptCodecBase->VADCR = (ptCodecBase->VADCR & (~CODEC_VAD_TO_MSK)) | (eTimeout << CODEC_VAD_TO_POS);
}

static inline void csp_codec_adc_softmute_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->VADCR = (ptCodecBase->VADCR &(~CODEC_ADCMU_MSK)) | CODEC_ADCMU_MSK;
}

static inline void csp_codec_adc_softmute_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->VADCR = (ptCodecBase->VADCR &(~CODEC_ADCMU_MSK)) | CODEC_ADCMU_DIS;
}

//ADCOUTCR
static inline void csp_codec_adc_lmute_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->ADCOUTCR = (ptCodecBase->ADCOUTCR&(~CODEC_ADC_LMUT_MSK)) | CODEC_ADC_LMUT_MSK;
}

static inline void csp_codec_adc_lmute_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->ADCOUTCR = (ptCodecBase->ADCOUTCR &(~CODEC_ADC_LMUT_MSK)) | CODEC_ADC_LMUT_DIS;
}

static inline void csp_codec_adc_rmute_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->ADCOUTCR = (ptCodecBase->ADCOUTCR &(~CODEC_ADC_RMUT_MSK)) | CODEC_ADC_RMUT_MSK;
}

static inline void csp_codec_adc_rmute_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->ADCOUTCR = (ptCodecBase->ADCOUTCR &(~CODEC_ADC_RMUT_MSK)) | CODEC_ADC_RMUT_DIS;
}

static inline void csp_codec_set_adcwr(csp_codec_t* ptCodecBase, codec_adcwr_e eWrCtrl)
{
	ptCodecBase->ADCOUTCR = (ptCodecBase->ADCOUTCR & (~CODEC_ADC_WR_MSK)) | (eWrCtrl << CODEC_ADC_WR_POS);
}

///ADCTESTCR

static inline void csp_codec_adc_testmode2_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->ADCTESTCR = (ptCodecBase->ADCTESTCR&(~CODEC_ADC_IBCM2D_MSK)) | CODEC_ADC_IBCM2D_MSK;
}

static inline void csp_codec_adc_testmode2_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->ADCTESTCR = (ptCodecBase->ADCTESTCR &(~CODEC_ADC_IBCM2D_MSK)) | CODEC_ADC_IBCM2D_DIS;
}

static inline void csp_codec_adc_testmode1_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->ADCTESTCR = (ptCodecBase->ADCTESTCR&(~CODEC_ADC_IB2D_MSK)) | CODEC_ADC_IB2D_MSK;
}

static inline void csp_codec_adc_testmode1_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->ADCTESTCR = (ptCodecBase->ADCTESTCR &(~CODEC_ADC_IB2D_MSK)) | CODEC_ADC_IB2D_DIS;
}


//DACINCR
static inline void csp_codec_set_dacinupt(csp_codec_t* ptCodecBase, codec_dacin_e eInput)
{
	ptCodecBase->DACINCR = (ptCodecBase->DACINCR & (~CODEC_DACIN_MSK)) | (eInput << CODEC_DACIN_POS);
}

static inline void csp_codec_set_dacrd(csp_codec_t* ptCodecBase, codec_dacrd_e eSource)
{
	ptCodecBase->DACINCR = (ptCodecBase->DACINCR & (~CODEC_DACRD_MSK)) | (eSource << CODEC_DACRD_POS);
}

//DACR0
static inline void csp_codec_dac_mute_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->DACR0 = (ptCodecBase->DACR0 &(~CODEC_DAC_MUTE_MSK)) | CODEC_DAC_MUTE_MSK;
}

static inline void csp_codec_dac_mute_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->DACR0 = (ptCodecBase->DACR0 &(~CODEC_DAC_MUTE_MSK)) | CODEC_DAC_MUTE_DIS;
}

static inline void csp_codec_dac_bypass_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->DACR0 = (ptCodecBase->DACR0 &(~CODEC_DAC_BYPASS_MSK)) | CODEC_DAC_BYPASS_MSK;
}

static inline void csp_codec_dac_bypass_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->DACR0 = (ptCodecBase->DACR0 &(~CODEC_DAC_BYPASS_MSK)) | CODEC_DAC_BYPASS_DIS;
}

static inline void csp_codec_dac_left_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->DACR0 = (ptCodecBase->DACR0 &(~CODEC_DAC_LPD_MSK)) | CODEC_DAC_LPO;
}

static inline void csp_codec_dac_left_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->DACR0 = (ptCodecBase->DACR0 &(~CODEC_DAC_LPD_MSK)) | CODEC_DAC_LPD;
}

static inline void csp_codec_dac_right_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->DACR0 = (ptCodecBase->DACR0 &(~CODEC_DAC_RPD_MSK)) | CODEC_DAC_RPO;
}

static inline void csp_codec_dac_right_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->DACR0 = (ptCodecBase->DACR0 &(~CODEC_DAC_RPD_MSK)) | CODEC_DAC_RPD;
}

static inline void csp_codec_dac_hpf_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->DACR0 = (ptCodecBase->DACR0 &(~CODEC_DAHPF_MSK)) | CODEC_DAHPF_MSK;
}

static inline void csp_codec_dac_hpf_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->DACR0 = (ptCodecBase->DACR0 &(~CODEC_DAHPF_MSK)) | CODEC_DAHPF_DIS;
}

static inline void csp_codec_dachpf_offsetr_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->DACR0 = (ptCodecBase->DACR0 &(~CODEC_DAHPF_OFFR_MSK)) | CODEC_DAHPF_OFFR_MSK;
}

static inline void csp_codec_dachpf_offsetr_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->DACR0 = (ptCodecBase->DACR0 &(~CODEC_DAHPF_OFFR_MSK)) | CODEC_DAHPF_OFFR_DIS;
}

static inline void csp_codec_ldac_softrst(csp_codec_t* ptCodecBase)
{
	ptCodecBase->DACR0 = (ptCodecBase->DACR0 &(~CODEC_RST_L_MSK)) | CODEC_RST_L_MSK;
}

static inline void csp_codec_rdac_softrst(csp_codec_t* ptCodecBase)
{
	ptCodecBase->DACR0 = (ptCodecBase->DACR0 &(~CODEC_RST_R_MSK)) | CODEC_RST_R_MSK;
}


//DACR1
static inline void csp_codec_set_dahpf_cutoff(csp_codec_t* ptCodecBase ,uint32_t wFreq)
{
	ptCodecBase->DACR1 = (ptCodecBase->DACR1 & (~CODEC_DAHPF_CUTOFF_MSK)) | (wFreq << CODEC_DAHPF_CUTOFF_POS);
}

//todo3 r reson
//todo4 l reson


//DACOUTCR
static inline void csp_codec_set_dac_rgain(csp_codec_t* ptCodecBase, codec_dac_gain_e eGain)
{
	ptCodecBase->DACOUTCR = (ptCodecBase->DACOUTCR & (~CODEC_DAC_RGAIN_MSK)) | (eGain << CODEC_DAC_RGAIN_POS);
}

static inline void csp_codec_set_dac_lgain(csp_codec_t* ptCodecBase, codec_dac_gain_e eGain)
{
	ptCodecBase->DACOUTCR = (ptCodecBase->DACOUTCR & (~CODEC_DAC_LGAIN_MSK)) | (eGain << CODEC_DAC_LGAIN_POS);
}

//HPOUTCR
static inline void csp_codec_set_hpout_rvol(csp_codec_t* ptCodecBase, uint8_t byVol)
{
	ptCodecBase->HPOUTCR = (ptCodecBase->HPOUTCR & (~CODEC_HP_RVOL_MSK)) | (byVol << CODEC_HP_RVOL_POS);
}

static inline void csp_codec_set_hpout_lvol(csp_codec_t* ptCodecBase, uint8_t byVol)
{
	ptCodecBase->HPOUTCR = (ptCodecBase->HPOUTCR & (~CODEC_HP_LVOL_MSK)) | (byVol << CODEC_HP_LVOL_POS);
}

static inline void csp_codec_hp_rpos_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->HPOUTCR = (ptCodecBase->HPOUTCR &(~CODEC_HP_RP_MSK)) | CODEC_HP_RP_MSK;
}

static inline void csp_codec_hp_rpos_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->HPOUTCR = (ptCodecBase->HPOUTCR &(~CODEC_HP_RP_MSK)) | CODEC_HP_RP_PD;
}

static inline void csp_codec_hp_rneg_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->HPOUTCR = (ptCodecBase->HPOUTCR &(~CODEC_HP_RN_MSK)) | CODEC_HP_RN_MSK;
}

static inline void csp_codec_hp_rneg_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->HPOUTCR = (ptCodecBase->HPOUTCR &(~CODEC_HP_RN_MSK)) | CODEC_HP_RN_PD;
}

static inline void csp_codec_hp_lpos_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->HPOUTCR = (ptCodecBase->HPOUTCR &(~CODEC_HP_LP_MSK)) | CODEC_HP_LP_MSK;
}

static inline void csp_codec_hp_lpos_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->HPOUTCR = (ptCodecBase->HPOUTCR &(~CODEC_HP_LP_MSK)) | CODEC_HP_LP_PD;
}

static inline void csp_codec_hp_lneg_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->HPOUTCR = (ptCodecBase->HPOUTCR &(~CODEC_HP_LN_MSK)) | CODEC_HP_LN_MSK;
}

static inline void csp_codec_hp_lneg_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->HPOUTCR = (ptCodecBase->HPOUTCR &(~CODEC_HP_LN_MSK)) | CODEC_HP_LN_PD;
}

static inline void csp_codec_set_hpout_mode(csp_codec_t* ptCodecBase, codec_hpmd_e eMode)
{
	ptCodecBase->HPOUTCR = (ptCodecBase->HPOUTCR & (~CODEC_HP_MD_MSK)) | (eMode << CODEC_HP_MD_POS);
}



//DACTESTCR
//todo6

//VCMCR
static inline void csp_codec_set_vcmpd_state(csp_codec_t* ptCodecBase, codec_vcmpd_state_e eState)
{
	ptCodecBase->VCMCR = (ptCodecBase->VCMCR & (~CODEC_VCMPD_STA_MSK)) | (eState << CODEC_VCMPD_STA_POS);
}

static inline void csp_codec_vcm_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->VCMCR = (ptCodecBase->VCMCR &(~CODEC_VCM_MSK)) | CODEC_VCM_MSK;
}

static inline void csp_codec_vcm_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->VCMCR = (ptCodecBase->VCMCR &(~CODEC_VCM_MSK)) | CODEC_VCM_PD;
}

static inline void csp_codec_vcmcharge_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->VCMCR = (ptCodecBase->VCMCR &(~CODEC_VCM_CHRG_MSK)) | CODEC_VCM_CHRG_MSK;
}

static inline void csp_codec_vcmcharge_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->VCMCR = (ptCodecBase->VCMCR &(~CODEC_VCM_CHRG_MSK)) | CODEC_VCM_CHRG_DIS;
}

static inline void csp_codec_set_vcmcharge_current(csp_codec_t* ptCodecBase, codec_vcm_chgcur_e eCurrent)
{
	ptCodecBase->VCMCR = (ptCodecBase->VCMCR &(~CODEC_VCM_CHGON_MSK)) | (eCurrent << CODEC_VCM_CHGON_POS);
}

static inline void csp_codec_vcmbps_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->VCMCR = (ptCodecBase->VCMCR &(~CODEC_VCM_BPS_MSK)) | CODEC_VCM_BPS_MSK;
}

static inline void csp_codec_vcmbps_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->VCMCR = (ptCodecBase->VCMCR &(~CODEC_VCM_BPS_MSK)) | CODEC_VCM_BPS_DIS;
}

static inline void csp_codec_vcm_autobps_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->VCMCR = (ptCodecBase->VCMCR &(~CODEC_VCM_AUTOBPS_MSK)) | CODEC_VCM_AUTOBPS_MSK;
}

static inline void csp_codec_vcm_autobps_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->VCMCR = (ptCodecBase->VCMCR &(~CODEC_VCM_AUTOBPS_MSK)) | CODEC_VCM_AUTOBPS_DIS;
}

static inline uint8_t csp_codec_vcm_is_ready(csp_codec_t* ptCodecBase)
{
	return  (uint8_t) (ptCodecBase->VCMCR & (~CODEC_VCM_RDY_MSK));
}

//REFCR
static inline void csp_codec_set_ref_lvl(csp_codec_t* ptCodecBase, codec_reflvl_e eLevel)
{
	ptCodecBase->REFCR = (ptCodecBase->REFCR & (~CODEC_REFLVL_MSK)) | (eLevel << CODEC_REFLVL_POS);
}

static inline void csp_codec_ref_enable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->REFCR = (ptCodecBase->REFCR &(~CODEC_REF_PD_MSK)) | CODEC_REF_PO;
}

static inline void csp_codec_ref_disable(csp_codec_t* ptCodecBase)
{
	ptCodecBase->REFCR = (ptCodecBase->REFCR &(~CODEC_REF_PD_MSK)) | CODEC_REF_PD_MSK;
}

#endif