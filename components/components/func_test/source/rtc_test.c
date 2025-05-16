/* \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2025-05-16 <td>V0.0  <td>WCH   <td>initial
 * </table>
 * *********************************************************************
*/
/* Includes ---------------------------------------------------------------*/

#include "rtc_test.h"
#include <csi_drv.h>
#include "csp.h"

//VBAT测试
//使能RTC，VDD/Vbat上电，稳压源双路电源供电
//当VDD重新上电时，观察RTC时间能否恢复计时
void rtc_vbat_test(void)
{
	csi_rtc_config_t tRtcConfig;
	csi_rtc_time_t tRtcTime,tRtcTimeRdbk;
	uint32_t wSec = 0xff;
	
	//my_printf("before:\r\nTIMR:%d\r\nDATR:%d\r\nCR:%d\r\nCCR:%d\r\n",RTC->TIMR,RTC->DATR,RTC->CR,RTC->CCR);
	//上电判断RTC是否在free running模式
	if(((RTC->CR) & RTC_INIT) == 1)
	{
		//上电后RTC在STOP模式，此时进行RTC初始化和设置时间
		tRtcConfig.byClkSrc = RTC_CLKSRC_ISOSC;//选择时钟源
		tRtcConfig.byFmt 	= RTC_24FMT;	//选择时间模式
		csi_rtc_init(RTC, &tRtcConfig);		//初始化设置

		tRtcTime.tm_year 	= 25;
		tRtcTime.tm_mon 	= 5;
		tRtcTime.tm_mday 	= 16;
		tRtcTime.tm_hour	= 15;			//如果是12小时制，回读到的hour范围为1->12；如果是24小时制，回读到的hour范围是0->23
		tRtcTime.tm_min 	= 00;
		tRtcTime.tm_sec 	= 00;	
		
		csi_rtc_set_time(RTC, &tRtcTime);	//设置时间
	}
	else 
	{
		//上电后RTC在free running模式，说明VBAT有电，使能RBEN后直接读取时间
		csp_rtc_rb_enable(RTC, ENABLE);
	}
	
	//无论上电后RTC处于什么模式，都要重新start RTC
	csi_rtc_start(RTC);							

	while(1)
	{
		//判断时间寄存器是否更新完成
		while(!((RTC->CCR & (1<<30)) == (1<<30)));
		
		csi_rtc_get_time(RTC,  &tRtcTimeRdbk);
		
		if((wSec != tRtcTimeRdbk.tm_sec) ) 
		{	
			wSec = tRtcTimeRdbk.tm_sec;
			my_printf("%d:%d:%d\n",tRtcTimeRdbk.tm_hour,tRtcTimeRdbk.tm_min,tRtcTimeRdbk.tm_sec);
		}
	}
}