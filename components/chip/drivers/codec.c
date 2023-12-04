/***********************************************************************//** 
 * \file  codec.c
 * \brief  csi codec driver
 * \copyright Copyright (C) 2015-2023 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2023-11-23 <td>V0.0  <td>GQQ   <td>initial
 * </table>
 * *********************************************************************
*/
//#include <csi_config.h>

#include "csp_common.h"
#include "drv/codec.h"

/* Private macro-----------------------------------------------------------*/


/* externs function--------------------------------------------------------*/
/* externs variablesr------------------------------------------------------*/
/* Private variablesr------------------------------------------------------*/


/**
  \brief       Init the codec according to the specified
  \param[in]   ptCodecBase  Codec handle to operate
  \param[in]   ptCodecCfg    Codec config handle 
  \return      error code \ref csi_error_t
*/
csi_error_t csi_codec_init(csp_codec_t *ptCodecBase, csi_codec_config_t *ptCodecCfg)
{
	csi_clk_enable((uint32_t *)ptCodecBase);								//adc peripheral clk enable
//	csp_codec_clk_enable(ptCodecBase); 										//enable codec clk
	csp_codec_reset(ptCodecBase);  											//reset all registers in codec
	
	csp_codec_clk_sel(ptCodecBase, (codec_clksel_e)ptCodecCfg->eClkSrc); 	//select codec source clock
	csp_codec_clk_enable(ptCodecBase); 										//enable codec clk
	
	
	if(ptCodecCfg->eInput == INPUT_MIC)								//input = MIC?
	{
		csp_codec_adcclk_div_config(ptCodecBase, ptCodecCfg->eAdcClkDiv);	//adc clk div
		csp_codec_adcclk_enable(ptCodecBase);								//enable adc clk
//		csp_codec_adc_hpf_enable(ptCodecBase);								//enable adc high pass fiter
		csp_codec_adc_analog_enable(ptCodecBase);							//enable adc analog module
		
		csp_codec_rmic_enable(ptCodecBase);									//right mic enable
		csp_codec_lmic_enable(ptCodecBase);									//left mic enable
		
		csp_codec_rpga_sel(ptCodecBase, CODEC_PGA_SEL_MIC);					//RIGHT CHANNEL PGA INPUT SELECT MIC
		csp_codec_lpga_sel(ptCodecBase, CODEC_PGA_SEL_MIC);					//LEFT CHANNEL PGA INPUT SELECT MIC
		
		csp_codec_rpga_enable(ptCodecBase);									//right channel pga enable
		csp_codec_lpga_enable(ptCodecBase);									//left channel pga enable
		
		csp_codec_set_dacinupt(ptCodecBase, CODEC_DACIN_ADC);				//codec dac input from ADC	
		
	}
	else if(ptCodecCfg->eInput == INPUT_LINE)							//input	= line?
	{
		csp_codec_adcclk_div_config(ptCodecBase, ptCodecCfg->eAdcClkDiv);	//adc clk div
		csp_codec_adcclk_enable(ptCodecBase);								//enable adc clk
//		csp_codec_adc_hpf_enable(ptCodecBase);								//enable adc high pass fiter
		csp_codec_adc_analog_enable(ptCodecBase);							//enable adc analog module
		
		csp_codec_rpga_sel(ptCodecBase, CODEC_PGA_SEL_LINE);				//RIGHT CHANNEL PGA INPUT SELECT LINE
		csp_codec_lpga_sel(ptCodecBase, CODEC_PGA_SEL_LINE);				//LEFT CHANNEL PGA INPUT SELECT LINE
		
		csp_codec_rpga_enable(ptCodecBase);									//right channel pga enable
		csp_codec_lpga_enable(ptCodecBase);									//left channel pga enable	
		
		csp_codec_set_dacinupt(ptCodecBase, CODEC_DACIN_ADC);				//codec dac input from ADC	

	}
	else {
		//I2S PCM no need to config PGA
		csp_codec_adc_rmute_enable(ptCodecBase);							//I2S  AS INPUT , mute adc right channel
		csp_codec_adc_lmute_enable(ptCodecBase);							//I2S  AS INPUT , mute adc left channel
		
		csp_codec_set_dacinupt(ptCodecBase, CODEC_DACIN_DAI);				//codec dac input from DAI
	}
	
	
	//output settings
	if(ptCodecCfg->eOutput == OUTPUT_I2SPCM)							//ONLY USE ADC module！！！
	{
		csp_codec_dac_right_disable(ptCodecBase);							//codec disable right channel dac analog 
		csp_codec_dac_left_disable(ptCodecBase);							//codec disable left channel dac analog 
		csp_codec_dac_mute_enable(ptCodecBase);								//codec dac output disable 
		
	}
	else if(ptCodecCfg->eOutput == OUTPUT_HEADPHONE)
	{
		csp_codec_dacclk_div_config(ptCodecBase, ptCodecCfg->eDacClkDiv);	//dac clk div
		csp_codec_dacclk_enable(ptCodecBase);								//enable dac clk
//		csp_codec_dac_hpf_enable(ptCodecBase);								//enable dac high pass fiter


		csp_codec_dac_right_enable(ptCodecBase);							//codec enable right channel dac analog 
		csp_codec_dac_left_enable(ptCodecBase);								//codec enable left channel dac analog 
		
		csp_codec_dac_mute_disable(ptCodecBase);							//enable dac output
		
		if(ptCodecCfg->eHpmode == HPMD_DIFF)  //differential output
		{
			csp_codec_hp_lneg_enable(ptCodecBase);							//headphone left channel negtive enable
			csp_codec_hp_rneg_enable(ptCodecBase);							//headphone right channel negtive enable
		}
		
		csp_codec_hp_lpos_enable(ptCodecBase);							//headphone left channel positive enable
		csp_codec_hp_rpos_enable(ptCodecBase);							//headphone right channel positive enable
		
	}					

	
	return CSI_OK;
}

/**
  \brief       set left channel & right channel mic gain
  \param[in]   ptCodecBase  Codec handle to operate
  \param[in]   eLGain    Codec left channel mic gain \ref csi_codec_micgain_e
  \param[in]   eRGain    Codec right channel mic gain  \ref csi_codec_micgain_e
  \return      none
*/
void csi_codec_set_mic_boost(csp_codec_t *ptCodecBase, csi_codec_micgain_e eLGain,csi_codec_micgain_e eRGain)
{
	csp_codec_lmic_boostgain_config(ptCodecBase, (codec_mic_gcon_e)eLGain);
	csp_codec_rmic_boostgain_config(ptCodecBase, (codec_mic_gcon_e)eRGain);
}

/**
  \brief       set mic bias level and enable mic bias output
  \param[in]   ptCodecBase  Codec handle to operate
  \param[in]   eLvl    Codec mic bias level  \ref csi_micbias_lvl_e
  \return      none
*/
void csi_codec_set_mic_biaslvl(csp_codec_t *ptCodecBase, csi_micbias_lvl_e eLvl)
{
	csp_codec_micbias_lvl_config(ptCodecBase, (codec_micbias_lvl_e)eLvl); 	//set mic bias level
	csp_codec_micbias_enable(ptCodecBase);									//enable mic bias 
}


/**
  \brief       set pga gain 
  \param[in]   ptCodecBase  Codec handle to operate
  \param[in]   byLGain  Codec left channel pga gain   range(0~3fh) Actual gain(-15dB~32.25dB) STEP :0.75dB
  \param[in]   byRGain  Codec right channel pga gain   range(0~3fh) Actual gain(-15dB~32.25dB) STEP :0.75dB
  \return      CSI_ERROR/CSI_OK
*/
csi_error_t csi_codec_set_pga_gain(csp_codec_t *ptCodecBase, uint8_t byLGain, uint8_t byRGain)
{
	if((byLGain > 0x3f)||(byLGain > 0x3f))
	{
		return CSI_ERROR;
	}
	
	csp_codec_lgain_config(ptCodecBase,byLGain);
	csp_codec_rgain_config(ptCodecBase,byRGain);
	
	return CSI_OK;
}

/**
  \brief       set pga gain TRANS STEP
  \param[in]   ptCodecBase  Codec handle to operate
  \param[in]   eStep codec pga gain trans step \ref csi_pga_gainstep_e
				-normal pga mode,gain trans rate 1.5db/step
				-soft mute mode ,gain trans rate 0.5db/step
  \return      none
*/
void csi_codec_set_pgagain_trans_step(csp_codec_t *ptCodecBase, csi_pga_gainstep_e eStep)
{
	csp_codec_gtranstep_config(ptCodecBase,(codec_transtep_e)eStep);
}

/**
  \brief       enable codec adc high pass filter offset record 
  \param[in]   ptCodecBase  Codec handle to operate
  \return      none
*/
void csi_codec_adhpf_offset_record_enable(csp_codec_t *ptCodecBase)
{
	csp_codec_adchpf_record_enable(ptCodecBase);
}

/**
  \brief       disable codec adc high pass filter offset record
  \param[in]   ptCodecBase  Codec handle to operate
  \return      none
*/
void csi_codec_adhpf_offset_record_disable(csp_codec_t *ptCodecBase)
{
	csp_codec_adchpf_record_disable(ptCodecBase);
}

/**
  \brief       enable codec adc high pass filter 
  \param[in]   ptCodecBase  Codec handle to operate
  \return      none
*/
void csi_codec_adhpf_enable(csp_codec_t *ptCodecBase)
{
	csp_codec_adc_hpf_enable(ptCodecBase);
}

/**
  \brief       disable codec adc high pass filter 
  \param[in]   ptCodecBase  Codec handle to operate
  \return      none
*/
void csi_codec_adhpf_disable(csp_codec_t *ptCodecBase)
{
	csp_codec_adc_hpf_disable(ptCodecBase);
}

/**
  \brief       set codec adc high pass filter cutoff frequency
  \param[in]   ptCodecBase  Codec handle to operate
  \param[in]   wFreq  Codec adc high pass filter cutoff freq	
  \return      CSI_ERROR/CSI_OK
*/
csi_error_t csi_codec_set_adhpf_cutoff(csp_codec_t *ptCodecBase, uint32_t wFreq)
{
	if(wFreq > 0xffffff)
	{
		return CSI_ERROR;
	}
	
	csp_codec_adhpf_cutoff_config(ptCodecBase, wFreq);
	
	return CSI_OK;
}

/**
  \brief       enable codec adc dither 
  \param[in]   ptCodecBase  Codec handle to operate
  \return      none
*/
void csi_codec_adc_dither_enable(csp_codec_t *ptCodecBase)
{
	csp_codec_adcdither_enable(ptCodecBase);
}

/**
  \brief       disable codec adc dither 
  \param[in]   ptCodecBase  Codec handle to operate
  \return      none
*/
void csi_codec_adc_dither_disable(csp_codec_t *ptCodecBase)
{
	csp_codec_adcdither_disable(ptCodecBase);
}

/**
  \brief      enable codec adc output bypass to DAC  
  \param[in]   ptCodecBase  Codec handle to operate
  \return      none
*/
void csi_codec_adc_bypass_todac(csp_codec_t *ptCodecBase)
{
	csp_codec_adc_bypass_enable(ptCodecBase);
	csp_codec_dac_bypass_enable(ptCodecBase);
}

/**
  \brief       set codec adc high pass filter cutoff frequency
  \param[in]   ptCodecBase  Codec handle to operate
  \param[in]   ptAgcCfg  	pointor to  stucture of Codec auto gain control 	
  \return      CSI_ERROR/CSI_OK
*/
csi_error_t csi_codec_set_agc(csp_codec_t *ptCodecBase, csi_agccfg_t *ptAgcCfg)
{
	if((ptAgcCfg->bLeftEn == DISABLE)&&(ptAgcCfg->bRightEn == DISABLE))
	{
		return CSI_ERROR;
	}
	
	if(ptAgcCfg->bLeftEn)  //left channel enable
	{
		csp_codec_lagc_enable(ptCodecBase); 		//enable left channel agc
	}
	else {
		csp_codec_lagc_disable(ptCodecBase);
	}
	
	if(ptAgcCfg->bRightEn)  //right channel enable
	{
		csp_codec_ragc_enable(ptCodecBase); 		//enable right channel agc
	}
	else {
		csp_codec_ragc_disable(ptCodecBase);
	}
	
	csp_codec_agcmode_config(ptCodecBase, (codec_agcmode_e)ptAgcCfg->eMode);  //set mode

	csp_codec_agclvl_config(ptCodecBase, (uint8_t)ptAgcCfg->eLvl); //set gain peak
	
	csp_codec_agchypeak_config(ptCodecBase, (codec_agchypeak_e)ptAgcCfg->eHist); //set gain peak hist
	
	csp_codec_agc_maxgain_config(ptCodecBase, (codec_agcgain_e)ptAgcCfg->eGainMax);
	
	csp_codec_agc_mingain_config(ptCodecBase, (codec_agcgain_e)ptAgcCfg->eGainMin);
	
	csp_codec_agchold_config(ptCodecBase, (codec_agchold_e)ptAgcCfg->eHoldTime);
	
	csp_codec_agc_dnstep_config(ptCodecBase, (uint8_t)ptAgcCfg->eDownStep);
	
	csp_codec_agc_upstep_config(ptCodecBase, (uint8_t) ptAgcCfg->eUpStep);
	
	if(ptAgcCfg->bZeroCEn)
	{
		csp_codec_agc_overzero_enable(ptCodecBase);
	}
	else {
		csp_codec_agc_overzero_disable(ptCodecBase);
	}
	
	if(ptAgcCfg->bZeroCTOEn)
	{
		csp_codec_agc_ovzeroto_enable(ptCodecBase);
	}
	else {
	csp_codec_agc_ovzeroto_disable(ptCodecBase);
	}
	
	
	return CSI_OK;
}

/**
  \brief       set codec vad
  \param[in]   ptCodecBase  Codec handle to operate
  \param[in]   ptVadCfg  	pointor to  stucture of Codec voice activity detect 	
  \return      CSI_ERROR/CSI_OK
*/
csi_error_t csi_codec_set_vad(csp_codec_t *ptCodecBase, csi_vadcfg_t *ptVadCfg)
{
	if((ptVadCfg->bVadEn == DISABLE)||(ptVadCfg->byLeftVadOff >0x3f)||(ptVadCfg->byRightVadOff >0x3f))
	{
		csp_codec_vad_disable(ptCodecBase);
		
		return CSI_ERROR;
	}
	
	csp_codec_set_vad_threshold(ptCodecBase,(codec_vadth_e)ptVadCfg->eVadTh);
	
	csp_codec_set_vad_lhist(ptCodecBase, ptVadCfg->eLeftVadHist);
	
	csp_codec_set_vad_rhist(ptCodecBase, ptVadCfg->eRightVadHist);
	
	csp_codec_set_vad_loffset(ptCodecBase, ptVadCfg->byLeftVadOff);
	
	csp_codec_set_vad_roffset(ptCodecBase, ptVadCfg->byRightVadOff);
	
	csp_codec_set_vad_timeout(ptCodecBase, (codec_vadto_e)ptVadCfg->eVadTo);
	
	csp_codec_adc_softmute_enable(ptCodecBase);
	
	csp_codec_vad_enable(ptCodecBase);
	
	return CSI_OK;
}

/**
  \brief       ADC LEFT & RIGHT channel soft mute control
  \param[in]   ptCodecBase  Codec handle to operate
  \param[in]   bLeftMute    Codec ADC LEFT channel mute control,ENABLE/DISABLE	
  \param[in]   bRightMute    Codec ADC right channel mute control,ENABLE/DISABLE	
  \return      none
*/
void csi_codec_adcout_softmute(csp_codec_t *ptCodecBase, bool bLeftMute, bool bRightMute)
{
	if(bLeftMute)
	{
		csp_codec_adc_lmute_enable(ptCodecBase);
	}
	else {
		csp_codec_adc_lmute_disable(ptCodecBase);
	}
	
	if(bRightMute)
	{
		csp_codec_adc_rmute_enable(ptCodecBase);
	}
	else {
		csp_codec_adc_rmute_disable(ptCodecBase);
	}
}

/**
  \brief       ADC out data write control
  \param[in]   ptCodecBase  Codec handle to operate
  \param[in]   eWrCtrl    	Codec ADC data write control \ref csi_adcwr_e		
  \return      none
*/
void csi_codec_adcdata_wrctrl(csp_codec_t *ptCodecBase, csi_adcwr_e eWrCtrl)
{
	csp_codec_set_adcwr(ptCodecBase, (codec_adcwr_e)eWrCtrl);
}

/**
  \brief       DAC in data read control
  \param[in]   ptCodecBase  Codec handle to operate
  \param[in]   eRdCtrl    	Codec dac data read control \ref csi_dacrd_e		
  \return      none
*/
void csi_codec_dacdata_rdctrl(csp_codec_t *ptCodecBase, csi_dacrd_e eRdCtrl)
{
	csp_codec_set_dacrd(ptCodecBase, (codec_dacrd_e)eRdCtrl);
}

/**
  \brief       DAC soft mute 
  \param[in]   ptCodecBase  Codec handle to operate		
  \return      none
*/
void csi_codec_dacmute_enable(csp_codec_t *ptCodecBase)
{
	csp_codec_dac_mute_enable(ptCodecBase);
}

/**
  \brief       disable DAC soft mute 
  \param[in]   ptCodecBase  Codec handle to operate		
  \return      none
*/
void csi_codec_dacmute_disable(csp_codec_t *ptCodecBase)
{
	csp_codec_dac_mute_disable(ptCodecBase);
}

/**
  \brief       enable DAC high pass filter
  \param[in]   ptCodecBase  Codec handle to operate		
  \return      none
*/
void csi_codec_dachpf_enable(csp_codec_t *ptCodecBase)
{
	csp_codec_dac_hpf_enable(ptCodecBase);
}

/**
  \brief       disable DAC high pass filter
  \param[in]   ptCodecBase  Codec handle to operate		
  \return      none
*/
void csi_codec_dachpf_disable(csp_codec_t *ptCodecBase)
{
	csp_codec_dac_hpf_disable(ptCodecBase);
}

/**
  \brief       enable DAC high pass filter offset record
  \param[in]   ptCodecBase  Codec handle to operate		
  \return      none
*/
void csi_codec_dachpf_offsetr_enable(csp_codec_t *ptCodecBase)
{
	csp_codec_dachpf_offsetr_enable(ptCodecBase);
}

/**
  \brief       disable DAC high pass filter offset record
  \param[in]   ptCodecBase  Codec handle to operate		
  \return      none
*/
void csi_codec_dachpf_offsetr_disable(csp_codec_t *ptCodecBase)
{
	csp_codec_dachpf_offsetr_disable(ptCodecBase);
}

/**
  \brief       codec dac left channel and right channel reset control
  \param[in]   ptCodecBase  Codec handle to operate	
  \param[in]   bLeftRst DAC left channel reset control ,ENABLE/DISABLE	
  \param[in]   bRightRst DAC right channel reset control ,ENABLE/DISABLE	
  \return      none
*/
void csi_codec_dac_softrst(csp_codec_t *ptCodecBase, bool bLeftRst, bool bRightRst)
{
	if(bLeftRst)
		csp_codec_ldac_softrst(ptCodecBase);
	
	if(bRightRst)
		csp_codec_rdac_softrst(ptCodecBase);
}

/**
  \brief       codec dac high pass filter cutoff frequency
  \param[in]   ptCodecBase  Codec handle to operate	
  \param[in]   wFreq		Codec dac high pass filter cutoff freq	 
  \return       CSI_OK/CSI_ERROR
*/
csi_error_t csi_codec_set_dachpf_cutoff(csp_codec_t *ptCodecBase, uint32_t wFreq)
{
	if(wFreq > 0xffffff)
		return CSI_ERROR;
	
	csp_codec_set_dahpf_cutoff(ptCodecBase, wFreq);
	
	return CSI_OK;
}

/**
  \brief       codec set dac left channel and right channel gain
  \param[in]   ptCodecBase  Codec handle to operate	
  \param[in]   eLeftGain	Codec dac left channel gain \ref csi_dacgain_e	 
  \param[in]   eRightGain	Codec dac right channel gain \ref csi_dacgain_e	
  \return      none
*/
void csi_codec_set_dacgain(csp_codec_t *ptCodecBase, csi_dacgain_e eLeftGain,csi_dacgain_e eRightGain)
{
	csp_codec_set_dac_lgain(ptCodecBase, (codec_dac_gain_e) eLeftGain);
	csp_codec_set_dac_rgain(ptCodecBase, (codec_dac_gain_e) eRightGain);
}

/**
  \brief       codec set headphone left channel and right channel gain
  \param[in]   ptCodecBase  Codec handle to operate	
  \param[in]   byLeft	Codec headphone left channel gain  byLeft~(0,3fh)	gain~(-32.25dB, 15dB) STEP 0.75dB
  \param[in]   byRight	Codec headphone right channel gain byRight~(0,3fh)	gain~(-32.25dB, 15dB) STEP 0.75dB
  \return      CSI_ERROR/CSI_OK
*/
csi_error_t csi_codec_set_hpgain(csp_codec_t *ptCodecBase, uint8_t byLeft,uint8_t byRight)
{
	if((byLeft>0x3f) || (byRight>0x3f))
		return CSI_ERROR;
	
	csp_codec_set_hpout_lvol(ptCodecBase, byLeft);
	csp_codec_set_hpout_rvol(ptCodecBase, byRight);
	
	return CSI_OK;
}

/**
  \brief       codec set headphone left channel and right channel gain
  \param[in]   ptCodecBase  Codec handle to operate	
  \param[in]   ptVcmCfg 	Pointor to vcm config 
  \return      none
*/
void csi_codec_vcm_cofig(csp_codec_t *ptCodecBase, csi_vcmcfg_t* ptVcmCfg)
{
	
	csp_codec_set_vcmpd_state(ptCodecBase, (codec_vcmpd_state_e)ptVcmCfg->eState);
	
	if(ptVcmCfg->bVcmChrgEn)
	{
		csp_codec_set_vcmcharge_current(ptCodecBase, (codec_vcm_chgcur_e)ptVcmCfg->eChrgCur);
		csp_codec_vcmcharge_enable(ptCodecBase);
	}
	else {
		csp_codec_vcmcharge_disable(ptCodecBase);
	}
	
	if(ptVcmCfg->bAutoBps)
	{
		csp_codec_vcm_autobps_enable(ptCodecBase);
	}
	else {
		csp_codec_vcm_autobps_disable(ptCodecBase);
	}
	
	if(ptVcmCfg->bBspEn)
	{
		csp_codec_vcmbps_enable(ptCodecBase);
	}
	else {
		csp_codec_vcmbps_disable(ptCodecBase);
	}
	
//	while(!csp_codec_vcm_is_ready(ptCodecBase)) //测试确定未使能前是否可以ready
	{
		csp_codec_vcm_enable(ptCodecBase);
	}
}

/**
  \brief       config codec reference level,and enable
  \param[in]   ptCodecBase  Codec handle to operate	
  \param[in]   eRefLvl 	Codec reference level \ref  csi_codecref_e
  \return      none
*/
void csi_codec_ref_config(csp_codec_t *ptCodecBase, csi_codecref_e eRefLvl)
{
	csp_codec_set_ref_lvl(ptCodecBase,(codec_reflvl_e)eRefLvl);
	
	csp_codec_ref_enable(ptCodecBase);
}
