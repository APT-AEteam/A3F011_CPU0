/***********************************************************************//** 
 * \file  rtc.c
 * \brief  rtc driver
 * \copyright Copyright (C) 2015-2021 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-6-2 <td>V2.0 <td>WNN    <td>initial
 * </table>
 * *********************************************************************
*/

/* include ----------------------------------------------------------------*/
#include "csp.h"
#include "rtc.h"
#include "rtc_alg.h"
#include "irq.h"
#include "soc.h"
#include "board_config.h"

/* externs function--------------------------------------------------------*/
/* private function--------------------------------------------------------*/
static void apt_rtc_alm_set_time(csp_rtc_t *ptRtc, uint8_t byAlm, uint8_t byDay, bool byPm, uint8_t byHor, uint8_t byMin,uint8_t bySec);
static csp_error_t apt_rtc_set_time(csp_rtc_t *ptRtc, bool bPm, uint8_t byHor, uint8_t byMin,uint8_t bySec);
static csp_error_t apt_rtc_set_date(csp_rtc_t *ptRtc, uint8_t byYear, uint8_t byMon, uint8_t byWday, uint8_t byDay);
csp_error_t apt_rtc_set_trgsrc(csp_rtc_t *ptRtc, uint8_t byTrg, csp_rtc_trgsel_e eSrc);
csp_error_t apt_rtc_set_trgprd(csp_rtc_t *ptRtc, uint8_t byTrg, uint8_t byPrd);
/* externs variablesr------------------------------------------------------*/
/* Private variablesr------------------------------------------------------*/

uint32_t wFlag1,wFlag2,wFlag3,wFlag4,wFlag5,wFlag6;
csi_rtc_time_t tRtcTime,tRtcTimeRdbk1;
void csi_rtc_init(csp_rtc_t *ptRtc, csi_rtc_config_t *tConfig)
{
    uint8_t byDiva = 0;
	uint16_t hwDivs = 0;
	uint32_t flash_err;
	
	switch (tConfig->byClkSrc)
	{ 
		case (RTC_ISOSC):
//			csi_isosc_enable();
			*(unsigned int *)(0x80000004) |=  0x1 <<2; 
			while((*(unsigned int *)(0x80000010)&0x4) != 0x4);
			byDiva = 49;
			hwDivs = 269;
			break;
		case (RTC_EMOSC):
			csi_esosc_enable();
			byDiva = 3;//63;
			hwDivs = 4095;//31;
			break;
		case (RTC_IMOSC_DIV4):
			byDiva = 99;
			hwDivs = 9999;
			break;
		case (RTC_EMOSC_DIV4):
			csi_emosc_enable(EMOSC_24M_VALUE);
//			*(unsigned int *)(0x80000004) |=  0x1 <<4; 
//			while((*(unsigned int *)(0x80000010)&0x10) != 0x10);
			byDiva = 99;//3;
			hwDivs = 29999;//4095;
			break;
		default:
			break;
	}
	
	ptRtc->KEY = 0xCA53;
	ptRtc->CCR |= (tConfig->byClkSrc << RTC_CLKSRC_POS)|(byDiva << RTC_DIVA_POS)| (hwDivs << RTC_DIVS_POS) | RTC_CLKEN ;
	while(ptRtc->CCR &RTC_CCR_BSY);
	ptRtc->KEY = 0x0;
	
	while((ptRtc->CCR & RTC_CLK_STABLE) == 0);
	
	csp_rtc_stop(ptRtc);

	csp_rtc_rb_enable(ptRtc, ENABLE);
	//csp_rtc_debug_enable(ptRtc, ENABLE);
	csp_rtc_set_fmt(ptRtc, tConfig->byFmt);
	csp_rtc_alm_enable(ptRtc, RTC_ALMB, DISABLE);
	csp_rtc_alm_enable(ptRtc, RTC_ALMA, DISABLE);
	
	csp_rtc_int_enable(ptRtc, RTC_INT_ALMA|RTC_INT_ALMB|RTC_INT_CPRD|RTC_INT_TRGEV0|RTC_INT_TRGEV1, DISABLE);
	csp_rtc_int_clr(ptRtc, RTC_INT_ALMA|RTC_INT_ALMB|RTC_INT_CPRD|RTC_INT_TRGEV0|RTC_INT_TRGEV1);
}

/**
  \brief       Read back function enable control. To save current, disable read back.
  \param       rtc        handle pointer of rtc register structure to operate
  \param       bEnable    
  \return      none
*/
void csi_rtc_rb_enable(csp_rtc_t *ptRtc, bool bEnable)
{
	csp_rtc_rb_enable(ptRtc, bEnable);
}

/**
  \brief       To set/change RTC format
  \param       pointer of rtc register structure pointer of rtc register structure to operate
  \param       eFmt \ref rtc_fmt_e    
  \return      none
*/
void csi_rtc_change_fmt(csp_rtc_t *ptRtc,  rtc_fmt_e eFmt)
{
	csp_rtc_set_fmt(ptRtc, eFmt);
}

/**
  \brief       To start RTC 
  \param       pointer of rtc register structure pointer of rtc register structure to operate
  \return      none
*/
void csi_rtc_start(csp_rtc_t *ptRtc)
{
	csp_rtc_run(ptRtc);
}

/**
  \brief       To stop RTC 
  \param       pointer of rtc register structure pointer of rtc register structure to operate
  \return      none
*/
void csi_rtc_stop(csp_rtc_t *ptRtc)
{
	csp_rtc_stop(ptRtc);
}

/**
  \brief       Set system date and run after setting
   * 				week day will be calculated in this function
  \param       rtc        handle pointer of rtc register structure to operate
  \param       rtctime    pointer to rtc time
  \return      error code \ref csi_error_t
*/
csi_error_t csi_rtc_set_time(csp_rtc_t *ptRtc, csi_rtc_time_t *ptRtcTime)
{   
    csi_error_t ret = CSI_OK;
		
	do {
//		if (csp_rtc_get_fmt(ptRtc) == RTC_12FMT && ptRtcTime->tm_hour>12) {
//			ret = CSI_ERROR;
//			break;
//		}
		
		ret = (csi_error_t) clock_check_tm_ok((const struct tm *)ptRtcTime);
        if (ret < CSI_OK) {
            break;
		
        }
		csp_rtc_stop(ptRtc);
		
	
		
		ptRtcTime->tm_wday = get_week_by_date((struct tm *)ptRtcTime);
		
		
		apt_rtc_set_date(ptRtc, ptRtcTime->tm_year, ptRtcTime->tm_mon, ptRtcTime->tm_wday, ptRtcTime->tm_mday);
		
	
		if ((ptRtcTime->tm_hour == 12) && (csp_rtc_get_fmt(ptRtc) == RTC_24FMT))
			ret =  apt_rtc_set_time(ptRtc, RTC_PM, ptRtcTime->tm_hour, ptRtcTime->tm_min,ptRtcTime->tm_sec);
		else
			ret =  apt_rtc_set_time(ptRtc, ptRtcTime->tm_pm, ptRtcTime->tm_hour, ptRtcTime->tm_min,ptRtcTime->tm_sec);
		
		
		if (ret < CSI_OK) {
            break;
        }
	}while(0);
	
	//csp_rtc_run(ptRtc);

	return ret;
}

/**
  \brief   Config RTC alarm
  \param   ptRtc      handle pointer of rtc register structure to operate
  \param   byAlm	  RTC_ALMA/RTC_ALMB
  \param   ptAlmTime    alarm time(s) 
  \param   byMode	  	0: day       hour min sec
						1: weekday   hour min sec
						2:           hour min sec

  \return  error code \ref csi_error_t
*/
csi_error_t csi_rtc_set_alarm(csp_rtc_t *ptRtc, uint8_t byAlm, uint8_t byMode, csi_rtc_time_t *ptAlmTime)
{ 	
	bool bDmsk = 0;
	bool bWdsel = 0;
	bool bHmsk = 0;
	bool bMmsk = 0;
	bool bSmsk = 0;
	bool bFmt = 0;
	
	if(byAlm > 1)
		return CSI_ERROR;

	if (ptAlmTime -> tm_yday == 0xff || byMode == 2) {
		bDmsk = 1;
		ptAlmTime->tm_mday = 0;			
	}
	if (ptAlmTime -> tm_hour == 0xff) {
		bHmsk = 1;
		ptAlmTime->tm_hour = 0;
	}
	if (ptAlmTime -> tm_min == 0xff) {
		bMmsk = 1;
		ptAlmTime->tm_min = 0;
	}
	if (ptAlmTime -> tm_sec == 0xff) {
		bSmsk = 1;	
		ptAlmTime->tm_sec = 0;
	}
	switch (byMode)
	{
		case 0:	bDmsk = 0;
				bWdsel = 0;
			break;
		case 1: bDmsk = 0;
				bWdsel = 1;
			break;
		case 2: bDmsk = 1;
				bWdsel = 0;
			break;
	}
	
	if(csp_rtc_get_fmt(RTC) == RTC_24FMT) {
		if (ptAlmTime -> tm_hour == 12) 
			bFmt = RTC_PM;
		else
			bFmt = RTC_AM;
	}
	switch (byAlm)
	{
		case (RTC_ALMA): 	csp_rtc_int_clr(ptRtc, RTC_INT_ALMA);
							csp_rtc_int_enable(ptRtc, RTC_INT_ALMA, ENABLE);
							break;
		case (RTC_ALMB):	csp_rtc_int_clr(ptRtc, RTC_INT_ALMB);
							csp_rtc_int_enable(ptRtc, RTC_INT_ALMB, ENABLE);
							break;
		default:
			return CSI_ERROR;
	}
	
	csi_rtc_int_enable(RTC, RTC_INT_ALMA, ENABLE);
	csp_rtc_alm_enable(ptRtc, byAlm, DISABLE);
	apt_rtc_alm_set_time(ptRtc, byAlm, ptAlmTime->tm_mday, bFmt,  ptAlmTime->tm_hour, ptAlmTime->tm_min,ptAlmTime->tm_sec);
	csp_rtc_alm_set_mode(ptRtc, byAlm, bWdsel, bDmsk, bHmsk, bMmsk, bSmsk);
	csp_rtc_alm_enable(ptRtc, byAlm, ENABLE);
	
	return CSI_OK;
}

/**
  \brief       Cancel the rtc alarm, keep last alarm time and mode setting
  \param       ptRtc    pointer of rtc register structure to operate
  \param       byAlm	RTC_ALMA/RTC_ALMB
  \return      none
*/
void csi_rtc_cancel_alarm(csp_rtc_t *ptRtc, uint8_t byAlm)
{
    
	csp_rtc_alm_enable(ptRtc, byAlm, DISABLE);
	switch (byAlm)
	{
		case (RTC_ALMA): 	csi_rtc_int_enable(ptRtc, RTC_INT_ALMA, DISABLE);
							csp_rtc_int_clr(ptRtc, RTC_INT_ALMA);
							break;
		case (RTC_ALMB):	csi_rtc_int_enable(ptRtc, RTC_INT_ALMB, DISABLE);
							csp_rtc_int_clr(ptRtc, RTC_INT_ALMB);
							break;
		default: break;
	}
}

/**
  \brief       Config RTC alarm ture timer
  \param[in]   ptRtc      handle pointer of rtc register structure to operate
  \param[in]   eOut     rtc output
  \return      none
*/
void csi_rtc_set_alarm_out(csp_rtc_t *ptRtc, csi_rtc_osel_e eOut)
{	
	csp_rtc_set_osel(ptRtc, eOut);
}



/**
  \brief    use rtc as a timer
  \param	callback  callback function to be called when time = ePrd
  \param 	ePrd    time interval of the timer.
  \param[in]   rtc    pointer of rtc register structure to operate
*/
void csi_rtc_start_as_timer(csp_rtc_t *ptRtc, csi_rtc_timer_e ePrd)
{	
	
	csp_rtc_set_cprd(ptRtc, ePrd);
	csi_rtc_int_enable(ptRtc, RTC_INT_CPRD , ENABLE);
	//csp_rtc_run(ptRtc);
}

/**
  \brief   RTC interrupt enable/disable
  \param   ptRtc      handle pointer of rtc register structure to operate
  \param   eIntSrc	  interrupt source	
  \param   bEnable    ENABLE/DISABLE 
  \return  none
*/
void csi_rtc_int_enable(csp_rtc_t *ptRtc, rtc_int_e eIntSrc, bool bEnable)
{
	csp_rtc_int_enable(ptRtc, eIntSrc, bEnable);	
	
	if (bEnable) {
		csi_irq_enable((uint32_t *)ptRtc);
	}
	else {
		if (eIntSrc == csp_rtc_get_imcr(ptRtc)) {
			csi_irq_disable((uint32_t *)ptRtc);
		}
	}
}

/**
  \brief       Get system time
  \param[in]   rtc        handle pointer of rtc register structure to operate
  \param[out]  rtctime    pointer to rtc time
  \return      none
*/
void csi_rtc_get_time(csp_rtc_t *ptRtc, csi_rtc_time_t *rtctime)
{
	//csp_rtc_rb_enable(ptRtc, ENABLE);
	rtctime->tm_year = csp_rtc_read_year(ptRtc);
	rtctime->tm_mon = csp_rtc_read_mon(ptRtc);
	rtctime->tm_wday = csp_rtc_read_wday(ptRtc);
	rtctime->tm_mday = csp_rtc_read_mday(ptRtc);
	rtctime->tm_hour = csp_rtc_read_hour(ptRtc);
	rtctime->tm_min = csp_rtc_read_min(ptRtc);
	rtctime->tm_sec = csp_rtc_read_sec(ptRtc);
	rtctime->tm_pm = csp_rtc_read_pm(ptRtc);
	//csp_rtc_rb_enable(ptRtc, DISABLE);
}

/**
  \brief       Get alarm remaining time
  \param[in]   rtc    pointer of rtc register structure to operate
  \param	   byAlm  RTC_ALMA/RTC_ALMB
  \return      the remaining time(s)
*/
uint32_t csi_rtc_get_alarm_remaining_time(csp_rtc_t *ptRtc, uint8_t byAlm)
{
    volatile csi_rtc_time_t tCurrentTime ;
	volatile csi_rtc_time_t tAlmTime;
	uint32_t wCurrentTime, wAlmTime;

	tCurrentTime.tm_mday = csp_rtc_read_mday(ptRtc); 
	tCurrentTime.tm_wday = csp_rtc_read_wday(ptRtc); 
	tCurrentTime.tm_hour = csp_rtc_read_hour(ptRtc);
	tCurrentTime.tm_min = csp_rtc_read_min(ptRtc); 
	tCurrentTime.tm_sec = csp_rtc_read_sec(ptRtc); 
	

	tAlmTime.tm_mday = csp_rtc_alm_read_mday(ptRtc, byAlm); 
	tAlmTime.tm_wday = csp_rtc_alm_read_wday(ptRtc, byAlm); 
	tAlmTime.tm_hour = csp_rtc_alm_read_hour(ptRtc, byAlm);
	tAlmTime.tm_min = csp_rtc_alm_read_min(ptRtc, byAlm); 
	tAlmTime.tm_sec = csp_rtc_alm_read_sec(ptRtc, byAlm); 
	

	
	if (csp_rtc_alm_read_dmsk(ptRtc, byAlm) == 1) {
		wCurrentTime = tCurrentTime.tm_hour * 3600 + tCurrentTime.tm_min * 60 + tCurrentTime.tm_sec;
		wAlmTime = tAlmTime.tm_hour * 3600 + tAlmTime.tm_min * 60 + tAlmTime.tm_sec;
		if(wAlmTime < wCurrentTime)
			return (24*3600 - wCurrentTime + wAlmTime);
	
	}
	else {
		if (csp_rtc_alm_read_wdsel(ptRtc, byAlm) == 1) {
			wCurrentTime = tCurrentTime.tm_wday * 86400 + tCurrentTime.tm_hour * 3600 + tCurrentTime.tm_min * 60 + tCurrentTime.tm_sec;
			wAlmTime = tAlmTime.tm_wday * 86400 + tAlmTime.tm_hour * 3600 + tAlmTime.tm_min * 60 + tAlmTime.tm_sec;
			if(wAlmTime < wCurrentTime)
				return (7*24*3600 - wCurrentTime + wAlmTime);
		}
		else {
			wCurrentTime = tCurrentTime.tm_mday * 86400 + tCurrentTime.tm_hour * 3600 + tCurrentTime.tm_min * 60 + tCurrentTime.tm_sec;
			wAlmTime = tAlmTime.tm_mday * 86400 + tAlmTime.tm_hour * 3600 + tAlmTime.tm_min * 60 + tAlmTime.tm_sec;
			if(wAlmTime < wCurrentTime)
				return CSI_UNSUPPORTED;	
		}
		
	}
	
	
	return (wAlmTime - wCurrentTime);
}


/** \brief evtrg source output config  
 * 
 *  \param[in] ptRtc: RTC handle to operate
 *  \param[in] byEvtrg: rtc evtrg channel(1~4) 
 *  \param[in] eTrgSrc: rtc evtrg source
 *  \param[in] trg_prd: event count period 
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_rtc_set_evtrg(csp_rtc_t *ptRtc, uint8_t byEvtrg, csi_rtc_trgsrc_e eTrgSrc, uint8_t byTrgPrd)
{
	
	csi_error_t ret = CSI_OK;
	
	if (apt_rtc_set_trgsrc(ptRtc, byEvtrg, eTrgSrc)<0)
		return CSI_ERROR;
	if (apt_rtc_set_trgprd(ptRtc, byEvtrg, byTrgPrd)<0)
		return CSI_ERROR;
	return ret;
}


//*****************************************************************************//


uint8_t  apt_dec2bcd(uint32_t wData)
{	
	return (((wData / 10) << 4) | (wData % 10));
}


static csp_error_t apt_rtc_set_date(csp_rtc_t *ptRtc, uint8_t byYear, uint8_t byMon, uint8_t byWday, uint8_t byDay)
{
	uint8_t byVal;
	csp_error_t ret = CSP_SUCCESS;
	if (csp_rtc_is_running(ptRtc))
		return CSP_FAIL;
		
	csp_rtc_wr_key(ptRtc);
	byVal = apt_dec2bcd(byYear);
	csp_rtc_set_date_year(ptRtc, byVal);
	byVal = apt_dec2bcd(byMon);
	csp_rtc_set_date_mon(ptRtc, byVal);
	byVal = apt_dec2bcd(byWday);
	csp_rtc_set_date_wday(ptRtc, byVal);
	byVal = apt_dec2bcd(byDay);
	csp_rtc_set_date_day(ptRtc, byVal);	
	csp_rtc_ers_key(ptRtc);
	
	return ret;
}


static csp_error_t apt_rtc_set_time(csp_rtc_t *ptRtc, bool bPm, uint8_t byHor, uint8_t byMin,uint8_t bySec)
{
	uint8_t byVal;
	csp_error_t ret = CSP_SUCCESS;

	if (csp_rtc_is_running(ptRtc))
		return CSP_FAIL;
			
//	if (bPm == RTC_AM && byHor > 12)
//		ret = CSP_FAIL;
//	else {
	
		csp_rtc_wr_key(ptRtc);
		byVal = apt_dec2bcd(byHor);
		csp_rtc_set_time_hour(ptRtc, bPm, byVal);
		byVal = apt_dec2bcd(byMin);
		csp_rtc_set_time_min(ptRtc, byVal);
		byVal = apt_dec2bcd(bySec);
		csp_rtc_set_time_sec(ptRtc, byVal);
		csp_rtc_ers_key(ptRtc);
//	}
	
	return ret;
}


static void apt_rtc_alm_set_time(csp_rtc_t *ptRtc, uint8_t byAlm, uint8_t byDay, bool byPm, uint8_t byHor, uint8_t byMin,uint8_t bySec)
{
	uint8_t byVal;
		
	csp_rtc_wr_key(ptRtc);
		
	byVal = apt_dec2bcd(byDay);
	csp_rtc_alm_set_day(ptRtc, byAlm, byVal);
	byVal = apt_dec2bcd(byHor);
	csp_rtc_alm_set_hour(ptRtc, byAlm, byPm, byVal);
	byVal = apt_dec2bcd(byMin);
	csp_rtc_alm_set_min(ptRtc, byAlm, byVal);
	byVal = apt_dec2bcd(bySec);
	csp_rtc_alm_set_sec(ptRtc, byAlm, byVal);
	
	csp_rtc_ers_key(ptRtc);
}



csp_error_t apt_rtc_set_trgsrc(csp_rtc_t *ptRtc, uint8_t byTrg, csp_rtc_trgsel_e eSrc)
{
	if (byTrg > 1)
		return CSP_FAIL;
	ptRtc -> EVTRG = (ptRtc->EVTRG & ~(RTC_TRGSEL0_MSK << (byTrg<<2) )) | (eSrc << (RTC_TRGSEL0_POS+ (byTrg<<2)));
	return CSP_SUCCESS;
}


csp_error_t apt_rtc_set_trgprd(csp_rtc_t *ptRtc, uint8_t byTrg, uint8_t byPrd)
{
	if (byTrg > 1)
		return CSP_FAIL;
	ptRtc -> EVPS = (ptRtc->EVPS & ~(RTC_TRGEV0PRD_MSK << (byTrg<<2))) | (((byPrd-1) & 0xf) << (RTC_TRGEV0PRD_POS + (byTrg<<2)));
	return CSP_SUCCESS;
}
