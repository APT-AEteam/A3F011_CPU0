/***********************************************************************//** 

 * *********************************************************************
*/

#ifndef _GPTB_H_
#define _GPTB_H_

#include "stdint.h"
#include "common.h"
#include "csp_gptb.h"
#ifdef __cplusplus
extern "C" {
#endif
extern uint32_t g_gptb0_prd;
extern uint32_t g_gptb1_prd;

typedef struct csi_gptb_config csi_gptb_config_t;
struct csi_gptb_config {
    uint8_t		byWorkmod;          //Count or capture
	uint8_t     byCountingMode;    //csi_gptb_cntmd_e
	uint8_t     byOneshotMode;     //Single or continuous
	uint8_t     byStartSrc ;
	uint8_t     byPscld;
	uint8_t		byDutyCycle;		 //TIMER PWM OUTPUT duty cycle	
	uint8_t     byCaptureCapLden;
	uint8_t     byCaptureRearm;
	uint8_t     byCaptureCapmd;
	uint8_t     byCaptureStopWrap;
	uint8_t     byCaptureLdaret;
	uint8_t     byCaptureLdbret;
	uint8_t     byCaptureLdcret;
	uint8_t     byCaptureLddret;
	uint8_t     byBurst;
    uint8_t     byCgsrc;
	uint8_t     byCgflt;
	uint32_t	wFreq;				 //TIMER PWM OUTPUT frequency 
	uint32_t    byInter;
};

typedef struct csi_gptb_pwmconfig  csi_gptb_pwmconfig_t;
struct csi_gptb_pwmconfig {
	uint8_t		byWorkmod;          //Count or capture
	uint8_t     byCountingMode;    //csi_gptb_cntmd_e
	uint8_t     byOneshotMode;     //Single or continuous
	uint8_t     byStartSrc ;
	uint8_t     byPscld;
	uint8_t		byDutyCycle;		 //TIMER PWM OUTPUT duty cycle	
	uint32_t	wFreq;				 //TIMER PWM OUTPUT frequency 
	uint32_t    byInter;
};

typedef struct csi_gptb_captureconfig  csi_gptb_captureconfig_t;
struct csi_gptb_captureconfig {
	uint8_t		byWorkmod;          //Count or capture
	uint8_t     byCountingMode;     //csi_gptb_cntmd_e
	uint8_t     byOneshotMode;      //Single or continuous
	uint8_t     byStartSrc ;
	uint8_t     byPscld;
	uint8_t		byDutyCycle;		 //TIMER PWM OUTPUT duty cycle	
 	uint8_t     byCaptureCapLden;
	uint8_t		byCapSrcMode;        //CAPMODE_SEL
	uint8_t     byCaptureRearm;
	uint8_t     byCaptureCapmd;
	uint8_t     byCaptureStopWrap;
	uint8_t     byCaptureLdaret;
	uint8_t     byCaptureLdbret;
	uint8_t     byCaptureLdcret;
	uint8_t     byCaptureLddret;
	uint32_t    byInter;
};

typedef struct csi_gptb_pwmchannel_config      csi_gptb_pwmchannel_config_t;
struct csi_gptb_pwmchannel_config {
	
    uint8_t		byActionZro;          //
	uint8_t     byActionPrd;          //
	uint8_t     byActionC1u;          //
    uint8_t     byActionC1d;          //
	uint8_t     byActionC2u;          //
	uint8_t     byActionC2d;          //
	uint8_t     byActionT1u;          //
	uint8_t     byActionT1d;          //
	uint8_t     byActionT2u;          //
	uint8_t     byActionT2d;          //	
    uint8_t     byChoiceC1sel;
	uint8_t     byChoiceC2sel;
};

typedef struct csi_gptb_deadzone_config   csi_gptb_deadzone_config_t;
struct  csi_gptb_deadzone_config
{	
	uint8_t       byChxOuselS1S0      ;   //
	uint8_t       byChxPolarityS3S2   ;   //
	uint8_t       byChxInselS5S4      ;   //
	uint8_t       byChxOutSwapS8S7    ;   //		
	uint8_t      byDcksel;
	uint8_t      byChaDedb;
	uint8_t      byChbDedb;
	uint8_t      byChcDedb;
	uint16_t      hwDpsc;                 //
	uint16_t      hwRisingEdgereGister ;  //
	uint16_t      hwFallingEdgereGister;  //
};



typedef struct csi_gptb_Chopper_config   csi_gptb_Chopper_config_t;
struct csi_gptb_Chopper_config
{
    uint8_t  byOspwth             ;                
	uint8_t  byCdiv               ;                
	uint8_t  byCduty              ;              
	uint8_t  byCasel              ;              
	uint8_t  chen            ;              

};
typedef enum{
	GPTBCHAX = 0x1,
	GPTBCHAY,
//	GPTBCHBX,
//	GPTBCHBY,
//	GPTBCHCX,
//	GPTBCHCY
}csi_gptb_chx_e;

typedef enum{
	GPTB_EMCOAX =0,
	GPTB_EMCOBX,
	GPTB_EMCOAY
}csi_gptb_osrchx_e;

typedef struct csi_gptb_emergency_config   csi_gptb_emergency_config_t;
struct csi_gptb_emergency_config
{
    uint8_t  byEpxInt ;
	uint8_t  byPolEbix;
    uint8_t	 byEpx;
	uint8_t  byEpxLckmd;
	uint8_t  byFltpace0;
	uint8_t  byFltpace1;
	uint8_t  byOrl0;
	uint8_t  byOrl1;
	
};

typedef struct  csi_gptb_Event_trigger_config   csi_gptb_Event_trigger_config_t;
struct  csi_gptb_Event_trigger_config{
	uint8_t   trg0sel  ;
	uint8_t   trg1sel  ;
	uint8_t   trg2sel  ;
	uint8_t   trg3sel  ;	
	uint8_t   trg0en   ;
	uint8_t   trg1en   ;
	uint8_t   trg2en   ;
	uint8_t   trg3en   ;	
	uint8_t   cnt0initfrc;
	uint8_t   cnt1initfrc;
	uint8_t   cnt2initfrc;
	uint8_t   cnt3initfrc;
	uint8_t   cnt0initen;
	uint8_t   cnt1initen;
	uint8_t   cnt2initen;
	uint8_t   cnt3initen;
	uint8_t   trg0prd ;
	uint8_t   trg1prd ;
	uint8_t   trg2prd ;
	uint8_t   trg3prd ;
	uint8_t   cnt0init;
	uint8_t   cnt1init;
	uint8_t   cnt2init;
	uint8_t   cnt3init;
	
	uint8_t fltipscld;
	uint8_t fltckprs;
	uint8_t srcsel;
	uint8_t blkinv;
	uint8_t alignmd;
	uint8_t crossmd;
	uint16_t offset;
	uint16_t window;
	
};

typedef struct csi_gptb_Global_load_control_config    csi_gptb_Global_load_control_config_t;
struct csi_gptb_Global_load_control_config{
	
	bool bGlden;
	bool bOstmd;
	uint8_t bGldprd;	
    uint8_t byGldmd;
	
	bool bPrdr;
	bool bCmpa;
	bool bCmpb;
	bool bAqcra;
	bool bAqcrb;
	bool bAqcsf;
};

/// \struct csi_gptb_filter_config_t
/// \brief  gptb sync trigger filter parameter configuration, open to users  
typedef struct {
	uint8_t		byFiltSrc;			//filter input signal source
	uint8_t		byWinInv;			//window inversion 
	uint8_t		byWinAlign;			//window alignment 
	uint8_t		byWinCross;			//window cross
	uint16_t	byWinOffset;		//window offset
	uint16_t 	byWinWidth;			//window width		
} csi_gptb_filter_config_t;

typedef struct {
	uint8_t		byPrdr;			
	uint8_t		byCmpa;			
	uint8_t		byCmpb;			
	uint8_t		byGld2;			
	uint8_t 	byRssr;		          
	uint8_t 	byEmslclr;
	uint8_t 	byEmhlclr;
    uint8_t 	byEmicr;
	uint8_t 	byEmfrcr;
    uint8_t 	byAqosf;
	uint8_t 	byAqcsf;		
} csi_gptb_feglk_config_t;

typedef enum
{
	GPTB_CAPTURE	= 0,		
    GPTB_WAVE 	= 1		
}csi_gptb_wave_e;


typedef enum {
	GPTB_UPCNT = 0,
	GPTB_DNCNT,
	GPTB_UPDNCNT
}csi_gptb_cntmd_e;


typedef enum{
	GPTB_OP_CONT = 0,
	GPTB_OP_OT,
}csi_gptb_opmd_e;

typedef enum{
    GPTB_CHANNEL_A=1,
	GPTB_CHANNEL_B,
//	GPTB_CHANNEL_C,
//	GPTB_CHANNEL_D
}csi_gptb_channel_e;

typedef enum{
    GPTB_DBCR =0,
	GPTB_DBDTR,
	GPTB_DBDTF,
	GPTB_DCKPSC,		
}csi_gptb_dbdldr_e;


typedef enum {
	GPTB_CH_A = 0,
	GPTB_CH_B,
}csi_gptb_chtype_e;

typedef enum {
	GPTB_SW = 0,
	GPTB_SYNC
}csi_gptb_stmd_e;

typedef enum{
	GPTB_STP_HZ = 0,
	GPTB_STP_L
}csi_gptb_stopst_e;

typedef enum {
	GPTB_POLARITY_HIGH = 0,
	GPTB_POLARITY_LOW
}csi_gptb_polarity_t;


typedef enum{
	GPTB_CAP_CONT = 0,
	GPTB_CAP_OT
}csi_gptb_capmd_e;

typedef enum{
	GPTBINT_N      = 0x0,
	GPTBINT_TRGEV0 = 0x1,
	GPTBINT_TRGEV1 = 0x2,
	GPTBINT_TRGEV2 = 0x4,
	GPTBINT_TRGEV3 = 0x8,
	GPTBINT_CAPLD0 = 0x1 << 4,
	GPTBINT_CAPLD1 = 0x1 << 5,
	GPTBINT_CAPLD2 = 0x1 << 6,
	GPTBINT_CAPLD3 = 0x1 << 7,
	GPTBINT_CAU = 0x1 << 8,
	GPTBINT_CAD = 0x1 << 9,
	GPTBINT_CBU = 0x1 << 10,
	GPTBINT_CBD = 0x1 << 11,
	
	GPTBINT_PEND = 0x1 << 16	
}csi_gptb_int_e;

typedef enum{
	GPTB_TRGO_0_SEL = 0,
	GPTB_TRGO_1_SEL
}csi_gptb_syncrout_e;

/**
 * \enum     csi_ept_trgin_e
 * \brief    EPT sync trigger input 
 */
typedef enum{
	GPTB_TRGIN_SYNCEN0	= 0,	//start	up or reset count			
	GPTB_TRGIN_SYNCEN1,			//reg updata				
	GPTB_TRGIN_SYNCEN2,			//capture				
	GPTB_TRGIN_SYNCEN3,			//			
	GPTB_TRGIN_SYNCEN4,			//	
	GPTB_TRGIN_SYNCEN5,			//
    GPTB_TRGIN_SYNCEN6					
}csi_gptb_trgin_e;

typedef enum {
	GPTB_TRGSRC_DIS		= 0,
	GPTB_TRGSRC_ZRO,
	GPTB_TRGSRC_PRD,
	GPTB_TRGSRC_ZRO_PRD,
	GPTB_TRGSRC_CAU,
	GPTB_TRGSRC_CAD,
	GPTB_TRGSRC_CBU,
	GPTB_TRGSRC_CBD,
//	GPTB_TRGSRC_CCU,
//	GPTB_TRGSRC_CCD,
//	GPTB_TRGSRC_CDU,
//	GPTB_TRGSRC_CDD,
	GPTB_TRGSRC_EX      =0x1100,
	GPTB_TRGSRC_PE0,
	GPTB_TRGSRC_PE1,
	GPTB_TRGSRC_PE2,

}csi_gptb_trgsrc_e;

/**
 * \enum	csi_gptb_trgout_e
 * \brief   gptb event trigger out port
 */
typedef enum{
	GPTB_TRG_OUT0		= 0,	
	GPTB_TRG_OUT1,				
				
}csi_gptb_trgout_e;

typedef enum {
	EM_AQCSF_NONE=0,
	EM_AQCSF_L,
	EM_AQCSF_H,
	EM_AQCSF_NONE1
}csp_gptb_aqcsf_e;

typedef enum {
	GPTB_AQCSF_NOW=0,
	GPTB_AQCSF_ZRO,
	GPTB_AQCSF_PRD,
	GPTB_AQCSF_ZRO_PRD
}csp_gptb_aqosf_e;

/**
 * \enum     csi_gptb_trgmode_e
 * \brief    gptb sync trigger mode 
 */
typedef enum{
	GPTB_TRG_CONTINU		= 0,	
	GPTB_TRG_ONCE								
}csi_gptb_trgmode_e;

/**
 * \enum     csi_gptb_arearm_e
 * \brief    v hardware auto rearm 
 */
typedef enum{
	GPTB_AUTO_REARM_DIS 	= 0,	//disable auto rearm
	GPTB_AUTO_REARM_ZRO,			//CNT = ZRO auto rearm
	GPTB_AUTO_REARM_PRD,			//CNT = PRD auto rearm
	GPTB_AUTO_REARM_ZRO_PRD		    //CNT = PRD or PRD auto rearm
}csi_gptb_arearm_e;

csi_error_t csi_gptb_config_init(csp_gptb_t *ptGptbBase, csi_gptb_config_t *ptgptbPwmCfg);
csi_error_t csi_gptb_channel_config(csp_gptb_t *ptGptbBase, csi_gptb_pwmchannel_config_t *tPwmCfg, csi_gptb_channel_e channel);
csi_error_t csi_gptb_dbldrload_config(csp_gptb_t *ptGptbBase, csi_gptb_dbdldr_e byVal,csp_gptb_shdw_e byWod,csp_gptb_lddb_e byWod2);
csi_error_t csi_gptb_dbcr_config(csp_gptb_t *ptGptbBase, csi_gptb_deadzone_config_t *tCfg);
csi_error_t csi_gptb_channelmode_config(csp_gptb_t *ptGptbBase,csi_gptb_deadzone_config_t *tCfg,csi_gptb_channel_e byCh);
csi_error_t csi_gptb_start(csp_gptb_t *ptgptbBase);
csi_error_t csi_gptb_change_ch_duty(csp_gptb_t *ptGptbBase, csi_gptb_chtype_e eCh, uint32_t wActiveTime);
csi_error_t csi_gptb_emergency_cfg(csp_gptb_t *ptGptbBase, csi_gptb_emergency_config_t *tCfg);
csi_error_t csi_gptb_emergency_pinxout(csp_gptb_t *ptGptbBase,csi_gptb_osrchx_e  byCh ,csp_gptb_emout_e byCh2);
csi_error_t csi_gptb_capture_init(csp_gptb_t *ptGptbBase, csi_gptb_captureconfig_t *ptgptbPwmCfg);
csi_error_t csi_gptb_wave_init(csp_gptb_t *ptGptbBase, csi_gptb_pwmconfig_t *ptgptbPwmCfg);
void csi_gptb_set_sync(csp_gptb_t *ptGptbBase, csi_gptb_trgin_e eTrgIn, csi_gptb_trgmode_e eTrgMode, csi_gptb_arearm_e eAutoRearm);
csi_error_t csi_gptb_dz_config(csp_gptb_t *ptGptbBase, csi_gptb_deadzone_config_t *tCfg);
csi_error_t csi_gptb_global_config(csp_gptb_t *ptGptbBase,csi_gptb_Global_load_control_config_t *Global);
csi_error_t csi_gptb_global_rearm(csp_gptb_t *ptGptbBase);
csi_error_t csi_gptb_global_sw(csp_gptb_t *ptGptbBase);
csi_error_t csi_gptb_set_extsync_chnl(csp_gptb_t *ptGptbBase, csi_gptb_trgin_e eTrgIn, csi_gptb_syncrout_e byTrgChx);
csi_error_t csi_gptb_set_evtrg(csp_gptb_t *ptGptbBase, csi_gptb_trgout_e byTrgOut, csi_gptb_trgsrc_e eTrgSrc);


#ifdef __cplusplus
}
#endif

#endif /* _DRV_PWM_H_ */