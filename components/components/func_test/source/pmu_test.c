/* \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2025-05-16 <td>V0.0  <td>WCH   <td>initial
 * </table>
 * *********************************************************************
*/
/* Includes ---------------------------------------------------------------*/

#include "pmu_test.h"
#include <csi_drv.h>
#include "csp.h"

void rtc_init(void)
{
	csi_rtc_config_t tRtcConfig;
	csi_rtc_time_t tRtcTime;
	
	//上电判断RTC是否在free running模式
	if(((RTC->CR) & RTC_INIT) == 1)
	{
		///////读写RTC特殊SRAM测试////////
//		test_delay();
//		temp = *(unsigned int *)(0x40080140);
//		my_printf("Init__TIMR:%d__SRAM:%d\r\n",RTC->TIMR,temp);	
		///////读写RTC特殊SRAM测试////////

		//上电后RTC在STOP模式，此时进行RTC初始化和设置时间
		tRtcConfig.byClkSrc = RTC_CLKSRC_ISOSC;//RTC_CLKSRC_IMOSC_DIV4;//RTC_CLKSRC_ISOSC;//选择时钟源
		tRtcConfig.byFmt 	= RTC_24FMT;	//选择时间模式
		csi_rtc_init(RTC, &tRtcConfig);		//初始化设置
		
		tRtcTime.tm_year 	= 25;
		tRtcTime.tm_mon 	= 3;
		tRtcTime.tm_mday 	= 25;
		tRtcTime.tm_hour	= 18;
		tRtcTime.tm_min 	= 00;
		tRtcTime.tm_sec 	= 00;	
		
		csi_rtc_set_time(RTC, &tRtcTime);	//设置时间
		
		///////读写RTC特殊SRAM测试////////
//		test_delay();
//		*(unsigned int *)(0x40080100 + 0x24) = 0x1234;
//		while(RTC->CR &RTC_BSY);
//		temp = *(unsigned int *)(0x40080140);
		///////读写RTC特殊SRAM测试////////
	}
	else 
	{
		//上电后RTC在free running模式，说明VBAT有电，使能RBEN后直接读取时间
		csp_rtc_rb_enable(RTC, ENABLE);
	}
	
	//无论上电后RTC处于什么模式，都要重新start RTC
	csp_rtc_set_cprd(RTC,RTC_CPRD_1MIN);
	csp_rtc_int_enable(RTC, RTC_INT_CPRD, ENABLE);
	csi_vic_enable_irq(RTC_IRQn);
	csp_rtc_int_clr(RTC, RTC_INT_CPRD);
	csi_rtc_start(RTC);						
}

//进入deepsleep模式，测量deepsleep电流
void deepsleep_mode_test(void)
{
	uint32_t hwRstSrc;
	
	delay_ums(50000);
	//开启所有时钟
	*(unsigned int *)(0x80000024) = 0xffffffff;  //PCERL0
	*(unsigned int *)(0x80000030) = 0xffffffff;  //PCERH0	
	*(unsigned int *)(0x80000048) = 0xffffffff;  //PCER1
	
	*(unsigned int *)(0x80000088) |= (3<<12) | (1<<23);	//LPWCR
	*(unsigned int *)(0x400B0008) |=  (0x1 << 16);		//TCH CON0
	
	//shutdown模式及唤醒源设置
	csi_pm_enter_sleep(PM_MODE_DEEPSLEEP);
}

//进入shutdown模式，测量shutdown电流
void shutdown_mode_test(void)
{
	uint32_t hwRstSrc;
	
	delay_ums(50000);
	//开启所有时钟
	*(unsigned int *)(0x80000024) = 0xffffffff;  //PCERL0
	*(unsigned int *)(0x80000030) = 0xffffffff;  //PCERH0	
	*(unsigned int *)(0x80000048) = 0xffffffff;  //PCER1
	
	//获取复位源信息
	hwRstSrc = csi_get_rst_reason();		//获取复位信息
	if(hwRstSrc)
	{
		my_printf("RSR:%d\r\n", hwRstSrc);	//打印mcu复位信息
		csi_clr_rst_reason(hwRstSrc);
	}
	
	//shutdown模式及唤醒源设置
	*(unsigned int *)(0x8000009c) |= (0x5<<28); 
	csi_pm_enter_sleep(PM_MODE_DEEPSLEEP);
}

//rtc唤醒shutdown模式，唤醒后过5秒再次进入shutdown
void shutdown_rtc_wakeup_test(void)
{
	uint8_t count = 0;
	uint32_t hwRstSrc;
	uint32_t wSec = 0xff;
	csi_rtc_time_t tRtcTimeRdbk;
	
	delay_ums(50000);
	//开启所有时钟
	*(unsigned int *)(0x80000024) = 0xffffffff;  //PCERL0
	*(unsigned int *)(0x80000030) = 0xffffffff;  //PCERH0	
	*(unsigned int *)(0x80000048) = 0xffffffff;  //PCER1
	
	//获取复位源信息
	hwRstSrc = csi_get_rst_reason();		//获取复位信息
	if(hwRstSrc)
	{
		my_printf("RSR:%d\r\n", hwRstSrc);	//打印mcu复位信息
		csi_clr_rst_reason(hwRstSrc);
	}
	
	rtc_init();

	while(1)
	{
		csp_rtc_rb_enable(RTC, ENABLE);
		//判断时间寄存器是否更新完成
		while(!((RTC->CCR & (1<<30)) == (1<<30)));
		
		csi_rtc_get_time(RTC,  &tRtcTimeRdbk);

		if((wSec != tRtcTimeRdbk.tm_sec) ) 
		{	
			count++;
			wSec = tRtcTimeRdbk.tm_sec;
			my_printf("Time:%d/%d %d:%d:%d\r\n",tRtcTimeRdbk.tm_mon,
												tRtcTimeRdbk.tm_mday,
												tRtcTimeRdbk.tm_hour,
												tRtcTimeRdbk.tm_min,
												tRtcTimeRdbk.tm_sec);
		}
		csp_rtc_rb_enable(RTC, DISABLE);
		
		if(count==5)
		{
			count=0;
			my_printf("Enter!\r\n");
			csp_rtc_set_cprd(RTC,RTC_CPRD_1MIN);
			csp_rtc_int_enable(RTC, RTC_INT_CPRD, ENABLE);
			csi_vic_enable_irq(RTC_IRQn);
			csp_rtc_int_clr(RTC, RTC_INT_CPRD);
			//shutdown模式及唤醒源设置
			*(unsigned int *)(0x8000009c) |= (0x5<<28) | (0x1ff << 4);
			csi_pm_enter_sleep(PM_MODE_DEEPSLEEP);
		}
	}
}

//- 测试芯片从shutdown模式唤醒后，retention SRAM的值是否会丢失
//- Retention sram地址从0x20020000开始，大小为2KB，掉电不丢失
//- 测试需写pwrmd寄存器：高四位和bit6需写为1（先写pwrkey），否则测试失败
//- 测试写三个地址作为对比：0x20020000/0x20020010 retention sram地址；0x20010000 普通sram地址
void retention_sram_test(void)
{
	uint32_t  temp1,temp2,temp3,temp4,count,hwRstSrc;
	
	delay_ums(50000);
	//开启所有时钟
	*(unsigned int *)(0x80000024) = 0xffffffff;  //PCERL0
	*(unsigned int *)(0x80000030) = 0xffffffff;  //PCERH0        
	*(unsigned int *)(0x80000048) = 0xffffffff;  //PCER1

	my_printf("A3F011 Test!\r\n");

	//获取复位源信息
	hwRstSrc = csi_get_rst_reason();                //获取复位信息
	if(hwRstSrc)
	{
		my_printf("RSR:%d\r\n", hwRstSrc);        //打印mcu复位信息
		csi_clr_rst_reason(hwRstSrc);
	}

	*(unsigned int *)(0x80000094) |= 0xa67a;
	*(unsigned int *)(0x80000090) |= 0xf<<28 | 1<<6;//写pwrmd寄存器

	///////读写RETENTION SRAM测试////////
	temp1 = *(unsigned int *)(0x20020000);
	temp2 = *(unsigned int *)(0x20020010);
	temp3 = *(unsigned int *)(0x20010000);
	my_printf("SRAM:1_%d,2_%d,3_%d\r\n",temp1,temp2,temp3);        
	///////读写RETENTION SRAM测试////////

	csi_rtc_config_t tRtcConfig;
	csi_rtc_time_t tRtcTime,tRtcTimeRdbk;
	uint32_t wSec = 0xff;

	//上电判断RTC是否在free running模式
	if(((RTC->CR) & RTC_INIT) == 1)
	{
	//上电后RTC在STOP模式，此时进行RTC初始化和设置时间
		tRtcConfig.byClkSrc = RTC_CLKSRC_ISOSC;//RTC_CLKSRC_IMOSC_DIV4;//RTC_CLKSRC_ISOSC;//选择时钟源
		tRtcConfig.byFmt    = RTC_24FMT;        //选择时间模式
		csi_rtc_init(RTC, &tRtcConfig);                //初始化设置
		
		tRtcTime.tm_year    = 25;
		tRtcTime.tm_mon     = 3;
		tRtcTime.tm_mday    = 25;
		tRtcTime.tm_hour    = 18;
		tRtcTime.tm_min     = 00;
		tRtcTime.tm_sec     = 00;        

		csi_rtc_set_time(RTC, &tRtcTime);        //设置时间
	}
	else 
	{
		//上电后RTC在free running模式，说明VBAT有电，使能RBEN后直接读取时间
		csp_rtc_rb_enable(RTC, ENABLE);
	}

	//无论上电后RTC处于什么模式，都要重新start RTC
	csp_rtc_set_cprd(RTC,RTC_CPRD_1MIN);
	csp_rtc_int_enable(RTC, RTC_INT_CPRD, ENABLE);
	csi_vic_enable_irq(RTC_IRQn);
	csp_rtc_int_clr(RTC, RTC_INT_CPRD);
	csi_rtc_start(RTC);                                                

	while(1)
	{
		csp_rtc_rb_enable(RTC, ENABLE);
     
		//判断时间寄存器是否更新完成
		while(!((RTC->CCR & (1<<30)) == (1<<30)));

		csi_rtc_get_time(RTC,  &tRtcTimeRdbk);

		///////读写RETENTION SRAM测试////////
		*(unsigned int *)(0x20020000) = tRtcTimeRdbk.tm_sec;
		*(unsigned int *)(0x20020010) = tRtcTimeRdbk.tm_sec+1;
		*(unsigned int *)(0x20010000) = tRtcTimeRdbk.tm_sec+2;
		temp1 = *(unsigned int *)(0x20020000);
		temp2 = *(unsigned int *)(0x20020010);
		temp3 = *(unsigned int *)(0x20010000);
		///////读写RETENTION SRAM测试////////

		if((wSec != tRtcTimeRdbk.tm_sec) ) 
		{        
			count++;
			wSec = tRtcTimeRdbk.tm_sec;
			my_printf("%d\r\n",SYSCON->ESCR);
			my_printf("Time:%d/%d %d:%d:%d_%d_%d_%d\r\n",tRtcTimeRdbk.tm_mon,
														tRtcTimeRdbk.tm_mday,
                                                        tRtcTimeRdbk.tm_hour,
														tRtcTimeRdbk.tm_min,
                                                        tRtcTimeRdbk.tm_sec,temp1,temp2,temp3);
		}
		csp_rtc_rb_enable(RTC, DISABLE);

		if(count==5)
		{
			count=0;
			my_printf("Enter!\r\n");
			*(unsigned int *)(0x8000009c) |= (0x55<<24) | (0x1 << 6);
			csi_pm_enter_sleep(PM_MODE_DEEPSLEEP);
		}
	}
}