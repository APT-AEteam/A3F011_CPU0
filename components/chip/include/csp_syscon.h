/***********************************************************************//** 
 * \file  csp_syscon.h
 * \brief  SYSCON description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-8-10 <td>V0.0  <td>WNN   <td>initial
 * </table>
 * *********************************************************************
*/

#include <stdint.h>
#include "csp_common.h"
#include <csi_core.h>
#include <soc.h>

#ifndef _CSP_SYSCON_H_
#define _CSP_SYSCON_H_



/// \struct csp_syscon_t
/// \brief SYSCON reg description
typedef volatile struct {                   			/*!< SYSCON Structure                         */
	volatile unsigned int IDCCR;                        /*!< 0x000: Identification & System Controller Clock Control Register */
	volatile unsigned int GCER;                         /*!< 0x004: System Controller General Control Enable Register */
	volatile unsigned int GCDR;                         /*!< 0x008: System Controller General Control Disable Register */
	volatile unsigned int GCSR;                         /*!< 0x00C: System Controller General Control Status Register */
	volatile unsigned int CKST;                         /*!< 0x010：Clock Stable Status Register*/
	volatile unsigned int SCKCR;                        /*!< 0x014: System Clock Control Register*/
	volatile unsigned int _RSVD0;                       /*!< 0x018: */
	volatile unsigned int SCKDIV;                       /*!< 0x01C: System Clock Division Register */
	volatile unsigned int PCKCR0;                       /*!< 0x020: System Controller Peripheral Clock 0 Control Register */
	volatile unsigned int IPCKERL0;                     /*!< 0x024: Big Core Peripheral Clock Enable Lower Register*/
	volatile unsigned int IPCKDRL0;                     /*!< 0x028: Big Core Peripheral Clock Disable Lower Register */
	volatile unsigned int IPCKSRL0;                     /*!< 0x02C: Big Core Peripheral Clock Status Lower Register */
	volatile unsigned int IPCKERH0;                     /*!< 0x030: Big Core Peripheral Clock Enable Higher Register */
	volatile unsigned int IPCKDRH0;                     /*!< 0x034: Big Core Peripheral Clock Disable Higher Register */
	volatile unsigned int IPCKSRH0;                     /*!< 0x038: Big Core Peripheral Clock Status Higher Register */
	volatile unsigned int IPRSTL0;                      /*!< 0x03C: Big Core Peripheral Reset Control Lower Register */
	volatile unsigned int IPRSTH0;                      /*!< 0x040: Big Core Peripheral Reset Control Higher Register */
	volatile unsigned int PCKCR1;                       /*!< 0x044: PCLK1 Control Register */
	volatile unsigned int IPCKER1;                      /*!< 0x048: Little Core Peripheral Clock Enable Control Register */
	volatile unsigned int IPCKDR1;                      /*!< 0x04C: Little Core Peripheral Clock Disable Control Register */
	volatile unsigned int IPCKSR1;                      /*!< 0x050: Little Core Peripheral Clock Status Register*/
	volatile unsigned int IPRST1;                       /*!< 0x054: Little Core Peripheral Reset Control Register */
	volatile unsigned int _RSVD1;                       /*!< 0x058: */
	volatile unsigned int _RSVD2;                       /*!< 0x05C: */
	volatile unsigned int _RSVD3;                       /*!< 0x060: */
	volatile unsigned int RAMCHK;                       /*!< 0x064: SRAM Check Control Register */
	volatile unsigned int EFLCHK;                       /*!< 0x068: EFLASH Check Control Register */
	volatile unsigned int EMCR;                         /*!< 0x06C: External Main Oscillator Control Register */
	volatile unsigned int ESCR;                         /*!< 0x070: External Sub Oscillator Control Register */
	volatile unsigned int PLLCR;                        /*!< 0x074: PLL Control Register */
	volatile unsigned int PLLOPT0;                      /*!< 0x078: PLL Options Register */
	volatile unsigned int PLLKEY;                       /*!< 0x07C: PLL Configuration Key Register */
	volatile unsigned int LVDCR;                        /*!< 0x080: Low Voltage Detect Control Register */
	volatile unsigned int GPWCR;                        /*!< 0x084: Current Power Config Register */
	volatile unsigned int LPWCR;                        /*!< 0x088: Low Power Config Register */
	volatile unsigned int PWTIM;                        /*!< 0x08C: Each Power Domain Recovery Time Config Register */
	volatile unsigned int PWRWD;                        /*!< 0x090: Each Power Domain IP Enable Control Register */
	volatile unsigned int PWKEY;                        /*!< 0x094: Power Key Register */
	volatile unsigned int OPTCR;                        /*!< 0x098: System Options Register */
	volatile unsigned int WKCR;                         /*!< 0x09C: Low Power Wake Up Control Register */
	volatile unsigned int PCAR;                         /*!< 0x0A0: Low Power CPU0 Retire PC Value Register */
	volatile unsigned int IMCR;                         /*!< 0x0A4: Interrupt Enable Control Register */
	volatile unsigned int MISR;                         /*!< 0x0A8: Interrupt Mask Status Register */
	volatile unsigned int ICR;                          /*!< 0x0AC: Interrupt Clear Status Register */
	volatile unsigned int RISR;                         /*!< 0x0B0: Raw Interrupt Status Register */
	volatile unsigned int IAR;                          /*!< 0x0B4: Interrupt Software Triggle Register */
	volatile unsigned int RSR;                          /*!< 0x0B8: Reset Source Record Status Register */
	volatile unsigned int IWDCR;                        /*!< 0x0BC: Independent Watchdog Control Register*/
	volatile unsigned int IWDCNT;                       /*!< 0x0C0: Independent Watchdog Control Counter Value*/
	volatile unsigned int IWDEDR;                       /*!< 0x0C4: Independent Watchdog Enable/Disable Register*/
	volatile unsigned int CQCR;                      	/*!< 0x0C8: Clock Quality check control register*/
	volatile unsigned int CQSR;                         /*!< 0x0CC: Clock Qualifty check counter VALUE */
	volatile unsigned int BRPKEY;                       /*!< 0x0D0: Reset Address config protection register*/
	volatile unsigned int SRBREG;                       /*!< 0x0D4: System Soft-Reset load Address Config Register*/
	volatile unsigned int ERBREG;                       /*!< 0x0D8: System Exception-Reset load Address Config Register*/
	volatile unsigned int SYSCSR;                       /*!< 0x0DC: System Reset control/Status Register */
	volatile unsigned int DBGREG0;                      /*!< 0x0E0: Debug Control Register0 */
	volatile unsigned int DBGREG1;                      /*!< 0x0E4: Debug Control Register1 */
	volatile unsigned int DBGREG2;                      /*!< 0x0E8: Debug Control Register2 */
	volatile unsigned int DBGREG3;                      /*!< 0x0EC: Debug Control Register3 */
	volatile unsigned int DBGREG4;                      /*!< 0x0F0: Debug Control Register4 */
	volatile unsigned int UREG0;                       	/*!< 0x0F4: 16-bit User Register0 */
	volatile unsigned int UREG1;                      	/*!< 0x0F8: 16-bit User Register1 */
	volatile unsigned int UREG2;                       	/*!< 0x0FC: 16-bit User Register2 */

} csp_syscon_t; 


/// IDCCR reg content
#define PMUCLK_EN		(0x01ul)
#define PMUCLK_DIS		(0x00ul)

#define SYSCON_IDKEY		(0x07E8ul << 16)

/// GCER/GCDR/GCSR/CKST reg content
#define IMOSC 		(0x01ul)
#define HFOSC 		(0x01ul << 1)
#define ISOSC 			(0x01ul << 2)
#define EMOSC 		(0x01ul << 3)
#define ESOSC 		(0x01ul << 4)
#define PLL 				(0x01ul << 5)

#define SYSCLK		(0x01ul << 8)
//#define SYSTICK 	(0x01ul << 11)

typedef enum{
	IPCK0_STP = 8,
	IHCK0_STP,
	IPCK1_STP,
	IHCK1_STP,
	ISOSC_STP = 12, 
	IMOSC_STP,
	ESOSC_STP,
	EMOSC_STP
}clk_pm_e;

#define CPU1_RST	(0x01ul << 24) // CPU1 RESET enable control

#define CPU1_SWON	(0x01ul << 25) // CPU1 START CONTROL

#define XIPEN		(0x01ul << 26) //QSPI XIP enable control

#define CRAM_PROT	(0x01ul << 27) //code ram protection

#define MEM_REMAP	(0x01ul << 28) //SRAM REMAP CONFIG

//ckst reg content
typedef enum {
	IMOSC_ST = 0,
	HFOSC_ST,
	ISOSC_ST,
	EMOSC_ST,
	ESOSC_ST,
	PLL_ST,
	CPU0CLK_ST,
	CPU1CLK_ST,
	SYSCLK_ST,
}clk_st_e;

#define PLLPWR_ST	(0x01ul << 12) //PLL Power stable status

//sckcr reg content
#define SCLK_SEL_MSK	0x7ul
typedef enum {
	SC_IMOSC = 0,
	SC_HFOSC,
	SC_ISOSC,
	SC_EMOSC,
	SC_ESOSC,
	SC_PLL,
}sclk_source_e;

#define SCLK_KEY	(0xD22D << 16)

//sclkdive content
#define MDIV0_POS 	(0) //Big Core sclk div
#define MDIV0_MSK	(0xfful << MDIV0_POS)

#define MDIV1_POS	(8) //Little Core sclk div
#define MDIV1_MSK	(0xfful << MDIV1_POS)


//PCKCR0 REG CONTENT
#define PCLK_KEY	(0xC33C << 16)
#define BC_PDIV_POS	(8) //	Big Core PCLK div 
#define BC_PDIV_MSK  (0x3f << BC_PDIV_POS)

//PCLK:pcerl0/pcdrl0/pcsrl0---IPSTL0(RESET) reg content
typedef enum{
	BC_IFC 	= 0,
	BC_CODEC	= 2,
	BC_FVR,
	BC_TKEY		= 6,
	BC_ETCB,
	BC_UART0,
	BC_UART1,
	BC_UART2,
	BC_USART0	= 13,
	BC_USART1	,
	BC_SPI0		= 16,
	BC_SPI1		= 17,
	BC_SIO0		= 20,
	BC_SIO1,
	BC_I2C,
	BC_CAN		= 22,
}bcip_lowsel_e;

//PCLK:pcerh0/pcdrh0/pcsrh0---IPSTH0(RESET) reg content
typedef enum{
	BC_EPT 	= 0,
	BC_GPTA0,
	BC_GPTA1 	= 2,
	BC_GPTA2,
	BC_GPTA3,
	BC_WDT	= 11,
	BC_LPT,
	BC_CNTA,
	BC_RTC,
	BC_BT,
	BC_LED	= 17,
	BC_CMP0,
	BC_CMP1,
	BC_CMP2,
	BC_LCD	= 22,
	BC_OPA0,
	BC_OPA1,
	BC_OPA2,
	BC_OPA3,
}bcip_highsel_e;


//pckcr1 reg content
#define LC_PDIV_POS	 (8) //	Little Core PCLK div 
#define LC_PDIV_MSK  (0x3f << LC_PDIV_POS)
//lc_pclk:1ipcker1 /ipckdr1/ipcksr1-- iprst1(reset)
typedef enum{
	LC_SPI =0,
	LC_BT,
} lcip_sel_e;


///RAMCHK
#define RAMCHK_POS	(24)
#define RAMCHK_MSK	(0xff << RAMCHK_POS)
#define RAMCHK_EN	(0x5a << RAMCHK_POS)
#define RAMCHK_DIS	(0x00 << RAMCHK_POS)
#define RAMCHK_RST_POS	(16)
#define RAMCHK_RST_MSK (0xff << RAMCHK_RST_POS)
#define RAMCHK_RST	(0x5a << RAMCHK_RST_POS)
#define RAMCHK_INT	(0x00 << RAMCHK_RST_POS)
#define RAMCHK_TIMES_MSK	(0xffff)

///EFLCHK
#define EFLCHK_POS	(24)
#define EFLCHK_MSK	(0xff << EFLCHK_POS)
#define EFLCHK_EN	(0x5a << EFLCHK_POS)
#define EFLCHK_DIS	(0x00 << EFLCHK_POS )
#define EFLCHK_TIMES_MSK	(0xffffff)


///emcr
#define EM_CNT_POS		(0)
#define EM_CNT_MSK		(0x3ff << EM_CNT_POS)

#define EM_GM_POS		(12)
#define EM_GM_MSK		(0x1Ful << EM_GM_POS)

#define EM_FLTEN_POS	(20)
#define EM_FLTEN_MSK	(0x01ul << EM_FLTEN_POS)

#define EM_FLTSEL_POS	(21)
#define EM_FLTSEL_MSK	(0x03ul << EM_FLTSEL_POS)

#define EM_LFSEL_POS	(23)
#define EM_LFSEL_MSK	(0x01ul << EM_FLTSEL_POS)

typedef enum{
	EM_SEL_NOMARL =0,
	EM_SEL_LOWSPEED,
}em_lfsel_e;

#define EM_CKMDUR_POS	(24)
#define EM_CKMDUR_MSK	(0x07ul << EM_FLTSEL_POS)

typedef enum{
	EM_CKDUR_CNT40 = 0,
	EM_CKDUR_CNT14 = 1,
	EM_CKDUR_CNT10 = 2,
	EM_CKDUR_CNT8  = 3,
	EM_CKDUR_CNT6  = 4,
	EM_CKDUR_CNT5  = 5,
	EM_CKDUR_CNT4  = 6,
	EM_CKDUR_CNT3  = 7,
}em_durcnt_e;


#define EM_RSTONFAIL_POS	(27)
#define EM_RSTONFAIL_MSK	(0x1 << EM_RSTONFAIL_POS)

//escr
#define ES_CNT_POS		(0)
#define ES_CNT_MSK		(0xff << ES_CNT_POS)

#define ES_GM_POS		(12)
#define ES_GM_MSK		(0xf << ES_GM_POS)

#define ES_SMTDIS_POS	(23)
#define ES_SMTDIS_MSK	(0x1 << ES_SMTDIS_POS)

#define ES_CKMDUR_POS	(24)
#define ES_CKMDUR_MSK	(0x7 << ES_CKMDUR_POS)

typedef enum{
	ES_CKDUR_CNT40 = 0,
	ES_CKDUR_CNT14 = 1,
	ES_CKDUR_CNT10 = 2,
	ES_CKDUR_CNT8  = 3,
	ES_CKDUR_CNT6  = 4,
	ES_CKDUR_CNT5  = 5,
	ES_CKDUR_CNT4  = 6,
	ES_CKDUR_CNT3  = 7,
}es_durcnt_e;

#define ES_RSTONFAIL_POS	(27)
#define ES_RSTONFAIL_MSK	(0x1 << ES_RSTONFAIL_POS)

#define CKM_STAT_POS		(28)
#define CKM_STAT_MSK		(0x1 << CKM_STAT_POS)


//PLLCR
#define PLL_CLK_SEL_MSK 	(0x3ul << PLL_CLK_SEL_POS)
#define PLL_CLK_SEL_POS 	(0)

typedef enum{
	PLL_CLK_SEL_NONE0 = 0,
	PLL_CLK_SEL_NONE1,
	PLL_CLK_SEL_HFOSC,
	PLL_CLK_SEL_EMOSC
}pll_clk_sel_e;

#define PLL_DIVM_MSK 		(0xful << PLL_DIVM_POS)
#define PLL_DIVM_POS 		(2)


#define PLL_NUL_MSK 		(0x7ful << PLL_NUL_POS)
#define PLL_NUL_POS 		(8)

#define PLL_UNLCKRST_MSK 	(0x1ul << PLL_UNLCKRST_POS) //UNLOCK RESET
#define PLL_UNLCKRST_POS 	(15)

#define PLL_CKPEN_MSK 		(0x1ul << PLL_CKPEN_POS)
#define PLL_CKPEN_POS 		(16)

#define PLL_CKP_DIV_MSK 	(0x3ful << PLL_CKP_DIV_POS)
#define PLL_CKP_DIV_POS 	(17)

#define PLL_CKQEN_MSK 		(0x1ul << PLL_CKQEN_POS)
#define PLL_CKQEN_POS 		(24)

#define PLL_CKQ_DIV_MSK 	(0x3ul << PLL_CKQ_DIV_POS)
#define PLL_CKQ_DIV_POS 	(25)

#define PLL_CKREN_MSK 		(0x1ul << PLL_CKREN_POS)
#define PLL_CKREN_POS 		(28)



//PLLOPT0  //todo

//PLLKEY
#define PLLKEY	0xA3F0  // relate to PLLOPT0


///LVDCR 
#define LVDEN_MSK (0xf)
#define LVD_DIS	(0xa)
#define LVDEN (0x0ul<<0)

#define LVDINT_POL_POS (0x6)
#define LVDINT_POL_MSK (0x3 << LVDINT_POL_POS)

#define LVDINT_DET_POL(r) ((r&0x3) << LVDINT_POL_POS)
#define LVD_FLAG    (0x1 << 15)

typedef enum {
	LVDINT_F = 1,
	LVDINT_R,
	LVDINT_BOTH	
}lvdint_pol_e;

#define LVD_LV_POS (0x8)
#define LVD_LV_MSK  (0x7 << LVD_LV_POS)
typedef enum{
	LVD21 = 0,
	LVD24,
	LVD27,
	LVD30,
	LVD33,
	LVD36,
	LVD39,
	LVDIN10	
}lvd_level_e;

#define LVR_SRT_POS	(4)
#define LVR_SRT_MSK	(0x01ul << LVR_SRT_POS)

#define LVR_LV_POS	(12)
#define LVR_LV_MSK  (0x7 << LVR_LV_POS)

typedef enum {
	LVR19 = 0,
	LVR22,
	LVR25,
	LVR28,
	LVR31,
	LVR34,
	LVR37,
	LVR40
}lvr_level_e;
#define LVD_KEY (0xB44Bul<<16)

//  GPWCR  --todo

//  LPWCR  --todo

//  PWTIM  --todo

//  PWRWD  --todo

//  PWKEY  --todo
#define PWRKEY		0xA676		// KEY OF CPWCR, LPWCR, PWRMD, PWRTIM


//OPTCR
///OPT1: clo/osc freq/Flash LP mode/EXI filter/EM clock monitoring config
#define IMO_MSK (0x3ul)
#define HFO_MSK (0x3ul<<4)
#define CLO_SRC_MSK (0xful << 8)
#define CLO_SRC_POS (0x8)
typedef enum{
	CLO_SYSCLK0 = 1,
	CLO_SYSCLK1,
	CLO_PLLFEEDOUT,
	CLO_PLLRCLK,
	CLO_PLLQCLK,
	CLO_PLLPCLK,
	CLO_IWDTCLK,
	CLO_AHB0CLK,
	CLO_AHB1CLK,
	CLO_RTCCLK,
	CLO_HF2CLK,
	CLO_HF1CLK,
	CLO_EMCLK,
	CLO_ESCLK,
	CLO_IMCLK
}clo_src_e;

#define CLO_DIV_MSK 	(0xFul << 12)
#define CLO_DIV_POS 	(12)

#define CLO_DIV(a)      2*(a+1)


#define EXIDFLT_POS		(16)
#define EXIDFLT_MSK 	(0x0ful << EXIFLT_DIV_POS)
typedef enum{
	EXIFILT_DISABLE = 0,
	EXIFILT_DIV_2,
	EXIFILT_DIV_3,
	EXIFILT_DIV_4,
	EXIFILT_DIV_5,
	EXIFILT_DIV_6,
	EXIFILT_DIV_7,
	EXIFILT_DIV_8,
	EXIFILT_DIV_9,
	EXIFILT_DIV_10,
	EXIFILT_DIV_11,
	EXIFILT_DIV_12,
	EXIFILT_DIV_13,
	EXIFILT_DIV_14,
	EXIFILT_DIV_15,
	EXIFILT_DIV_16
}exifilt_cr_e;

#define EXIFCNT_POS		(20)
#define EXIFCNT_MSK 	(0x0ful << EXIFLT_DIV_POS)


#define BOOTCFG_POS 	(24)
#define BOOTCFG_MSK		(0x03ul << BOOTCFG_POS)

typedef enum{
	BOOT_FROM_IFC  = 0,
	BOOT_FROM_QSPI,
	BOOT_FROM_CRAM,
}boot_sel_e;

#define RAM1PROT_MSK	(0x1ul << 26)
#define RAM1PROT_EN		(0x1ul << 26)
#define RAM1PROT_DIS	(0x0ul << 26)

#define RAMCFG_MSK		(0x1ul << 27)
typedef enum{
	SRM0_128K_SRM1_64K  = 0,
	SRM0_64K_SRM1_128K,
}ram_cfg_e;

#define SWDUNLOCK_MSK	(0x1ul << 31)
#define SWDUNLOCK		(0x1ul << 31)
#define SWDLOCK			(0x0ul << 31)


/// WKCR: wakeup(from deep-sleep) source register
#define DPSLEEP_WKSRC_MSK  0x1fff

#define WKEN0		(0x1ul << 0)
#define WKEN1		(0x1ul << 1)
#define WKEN2		(0x1ul << 2)
#define WKEN3		(0x1ul << 3)
#define LVD_WKEN	(0x1ul << 4)
#define IWDT_WKEN	(0x1ul << 5)
#define RTC_WKEN	(0x1ul << 6)
#define EXI_WKEN	(0x1ul << 7)
#define LPT_WKEN	(0x1ul << 8)
#define TKEY_WKEN	(0x1ul << 9)
#define IIC_WKEN	(0x1ul << 10)
#define CMP_WKEN	(0x1ul << 11)
#define DBG_WKEN	(0x1ul << 12)

#define GPIO_LOCK	(0x1ul << 16)

#define WKI0POL_MSK	(0x3ul << 20)
#define WKI1POL_MSK	(0x3ul << 22)

typedef enum{
	FAIL_EDGE_EN = 1,
	RAISE_EDGE_EN = 2,
} wkipol_sel_e;

#define DPSLEEP_MODE_P0S	(24)
#define DPSLEEP_MODE_MSK	(0xfful << DPSLEEP_MODE_P0S)
typedef enum{
	SHUTDOWN_MODE	= (0xA5ul),
	DPSLEEP_MODE	= (0x05ul),
}deepsleep_mode_e;

// PCAR -todo



///INTERRUPT related regs: IMCR/MISR/ICR/RISR/IAR

typedef enum{
	IMOSC_ST_INT 	= (0x1<<0),
	HFOSC_ST_INT 	= (0x1<<1),
	ISOSC_ST_INT 	= (0x1<<2),
	EMOSC_ST_INT 	= (0x1<<3),
	ESOSC_ST_INT 	= (0x1<<4),
	PLL_LOCK_INT 	= (0x1<<5),
	PLL_ULC_INT 	= (0x1<<6),
	CPU0CLK_ST_INT 	= (0x1<<7),
	CPU1CLK_ST_INT 	= (0x1<<8),
	CPU0SYS_ST_INT 	= (0x1<<9),
	CPU1SYS_ST_INT 	= (0x1<<10),
	EMLST_ST_INT 	= (0x1<<11),
	CQCDNE_INT 		= (0x1<<13),
	LVD_ST_INT 		= (0x1<<16),
	WDT_ST_INT 		= (0x1<<17),
	OPTFAIL_ST_INT 	= (0x1<<20),
	ELFFAIL_ST_INT 	= (0x1<<21),
	RAM0FAIL_ST_INT = (0x1<<22),
	RAM1FAIL_ST_INT = (0x1<<23),
	HWDER_ST_INT 	= (0x1<<24),

}syscon_int_e;


/// RSR reset register
#define RSR_MSK		(0xfffff)
typedef enum{
	PORST	= 0,
	LVRST,
	EXTRST,
	IWDTRST = 4,
	EMCMRST = 6,
	PMURST	= 8,
	PLLRST  = 10,
	RAM0RST,
	RAM1RST,
	EFLRST,
	WWDTRST,
	CPU0HRST,
	CPU0RST,
	CPU1HRST,
	CPU1RST,
	CPU0FT,
	CPU1FT,
}rst_st_e;

#define WKSRC_MSK	(0x1ful << 20)
typedef enum {
	WDT_WK = 20,
	RTC_WK,
	WK0_WK,
	WK1_WK,
	DBG_WK,
}wk_src_e;


///IWDCR

#define IWDTCR_KEY (0x8778ul << 16)

#define IWDT_INTV_POS	(2)
#define IWDT_INTV_MSK (0x7ul << IWDT_INTV_POS)

typedef enum{
	IWDT_INTW_7_8 = 0,
	IWDT_INTW_6_8,
	IWDT_INTW_5_8, 
	IWDT_INTW_4_8, 
	IWDT_INTW_3_8, 
	IWDT_INTW_2_8, 
	IWDT_INTW_1_8
}iwdt_intv_e;


#define IWDT_OVT_POS	(8)
#define IWDT_OVT_MSK (0x7 << IWDT_OVT_POS)
typedef enum{
	IWDT_TIME_0128 = 0x0,
	IWDT_TIME_0256,
	IWDT_TIME_0512,
	IWDT_TIME_1000,
	IWDT_TIME_2000,
	IWDT_TIME_3100,
	IWDT_TIME_4100,
	IWDT_TIME_8200
}iwdt_ovt_e;

#define IWDT_DBGEN_POS (11)
#define IWDT_DBGEN_MSK (0x1 << IWDT_DBGEN_POS)
#define IWDT_ST		(0x1 << 12)
#define IWDT_BUSY	(0x1 << 12)
///IWDCNT
#define IWDT_CLR_BUSY	(0x1<<31)
#define IWDT_CLR_POS	(24)
#define IWDT_CLR_MSK	(0x7f << IWDT_CLR_POS)
#define IWDT_CLR		(0x5a)
#define IWDT_CNT		(0xff)

///IWDEDR: IWDT enable control reg
#define IWDTE_KEY	(0x7887 << 16)
#define DIS_IWDT	(0x5a)
#define EN_IWDT		(0x0)


//CQCR
#define CQCR_EN_POS              (0) 
#define CQCR_EN_MSK              (0x1 << CQCR_EN_POS)  

#define CQCR_REFSEL_POS          (4) 
#define CQCR_REFSEL_MSK          (0x3 << CQCR_REFSEL_POS)  

typedef enum{
	CQCR_REFSEL_EMOSC,
	CQCR_REFSEL_ESOSC,	
}cqcr_refsel_e;

#define CQCR_SRCSEL_POS          (6) 
#define CQCR_SRCSEL_MSK          (0x3 << CQCR_SRCSEL_POS)  
typedef enum{
	CQCR_SRCSEL_IMOSC,
	CQCR_SRCSEL_ESOSC,
	CQCR_SRCSEL_ISOSC,
	CQCR_SRCSEL_HFOSC
}cqcr_srcsel_e;

#define CQCR_CQRVAL_POS         (8) 
#define CQCR_CQRVAL_MSK         (0x3FFFF << CQCR_CQRVAL_POS)  

//cqsr
#define CQSR_MSK				0xFFFFF

//brpkey
#define BRPKEY					0x9559   //srbreg erbreg key 

//srbreg
#define SRB_MSK					0xfff

//erbreg
#define ERB_MSK					0xfff

//syscr
#define CPU0FT_RTSEN_POS		(0x0ul)
#define CPU0FT_RSTEN_MSK		(0xf << CPU0FT_RTSEN_POS)

#define CPU1FT_RTSEN_POS		(0x4ul)
#define CPU1FT_RSTEN_MSK		(0xf << CPU1FT_RTSEN_POS)

typedef enum {
	CPUFT_RSTDIS = 0x0,
	CPUFT_RSTEN = 0xa,
}cpuft_rst_e;

#define CPUSR_MSK				0xfff << 8


//DBGREG0
#define SWD_AFLOCK				0x00
#define SWD_AFUNLOCK			0x5A

//DBGREG1
//DBGREG2
//DBGREG3
//DBGREG4

//ureg0
#define URG0_MSK				0xffff

//ureg1
#define URG1_MSK				0xffff


//ureg1
#define URG2_MSK				0xffff




///API to access setup of SYSCON

//IDCCR
static inline void csp_set_pmuclk_enable(csp_syscon_t *ptSysconBase)
{
	ptSysconBase->IDCCR = (SYSCON_IDKEY | PMUCLK_EN);
}

static inline void csp_set_pmuclk_disable(csp_syscon_t *ptSysconBase)
{
	ptSysconBase->IDCCR = (SYSCON_IDKEY | PMUCLK_DIS);
}

//ckst
static inline uint32_t csp_get_ckst(csp_syscon_t *ptSysconBase)
{
	return (uint32_t) ((ptSysconBase->CKST) & 0x1ff);
}

//gcsr
static inline uint32_t csp_get_gcsr(csp_syscon_t *ptSysconBase)
{
	return (uint32_t) ((ptSysconBase->GCSR) & 0x1f00ff2f);
}

//sckcr
static inline void csp_set_clksrc(csp_syscon_t *ptSysconBase, sclk_source_e eClkSrc)
{
	ptSysconBase->SCKCR = (ptSysconBase->SCKCR & (~SCLK_SEL_MSK)) | SCLK_KEY | eClkSrc;
	while((ptSysconBase->CKST & SYSCLK) == 0);
}

static inline uint32_t csp_get_clksrc(csp_syscon_t *ptSysconBase)
{
	return (uint32_t) ((ptSysconBase->SCKCR) & SCLK_SEL_MSK);
}

//SCKDIV
static inline void csp_set_bc_sdiv(csp_syscon_t *ptSysconBase, uint32_t wSdiv)
{
	ptSysconBase->SCKDIV =  (ptSysconBase->SCKDIV & (~MDIV0_MSK)) | SCLK_KEY | (wSdiv << MDIV0_POS);
}

static inline void csp_set_lc_sdiv(csp_syscon_t *ptSysconBase, uint32_t wSdiv)
{
	ptSysconBase->SCKDIV =  (ptSysconBase->SCKDIV & (~MDIV1_MSK)) | SCLK_KEY | (wSdiv << MDIV1_POS);
}

static inline  uint32_t csp_get_bc_hclk_div(csp_syscon_t *ptSysconBase)
{
	return (uint32_t) (((ptSysconBase->SCKDIV) & MDIV0_MSK) >> MDIV0_POS);
}

static inline  uint32_t csp_get_lc_hclk_div(csp_syscon_t *ptSysconBase)
{
	return (uint32_t) (((ptSysconBase->SCKDIV) & MDIV1_MSK) >> MDIV1_POS);
}


//PCKCR0
static inline void csp_set_bc_pdiv(csp_syscon_t *ptSysconBase, uint32_t wSdiv)
{
	ptSysconBase->PCKCR0 =  (ptSysconBase->PCKCR0 & (~BC_PDIV_MSK)) | PCLK_KEY | (wSdiv << BC_PDIV_POS);
}

static inline uint32_t	csp_get_bc_pdiv(csp_syscon_t *ptSysconBase)
{
	return (uint32_t ) (((ptSysconBase->PCKCR0) & BC_PDIV_MSK) >> BC_PDIV_POS);
}

//PCKCR1
static inline void csp_set_lc_pdiv(csp_syscon_t *ptSysconBase, uint32_t wSdiv)
{
	ptSysconBase->PCKCR1 =  (ptSysconBase->PCKCR1 & (~LC_PDIV_MSK)) | PCLK_KEY | (wSdiv << LC_PDIV_POS);
}

static inline uint32_t	csp_get_lc_pdiv(csp_syscon_t *ptSysconBase)
{
	return (uint32_t ) (((ptSysconBase->PCKCR1) & LC_PDIV_MSK) >> LC_PDIV_POS);
}

//optcr
static inline void csp_set_hfosc_fre(csp_syscon_t *ptSysconBase, uint32_t wFreq)
{
	ptSysconBase->OPTCR = (ptSysconBase->OPTCR & (~HFO_MSK)) | wFreq << 4;
}
static inline uint32_t csp_get_hfosc_fre(csp_syscon_t *ptSysconBase)
{
	return (uint32_t) (((ptSysconBase->OPTCR) & HFO_MSK) >> 4);
}
static inline void csp_set_imosc_fre(csp_syscon_t *ptSysconBase, uint32_t wFreq)
{
	ptSysconBase->OPTCR = (ptSysconBase->OPTCR & (~IMO_MSK)) | wFreq;
}
static inline uint32_t csp_get_imosc_fre(csp_syscon_t *ptSysconBase)
{
	return (uint32_t) ((ptSysconBase->OPTCR) & IMO_MSK);
}

static inline  uint8_t csp_get_imsrc(csp_syscon_t *ptSysconBase)
{
	return (uint8_t) (ptSysconBase->OPTCR & IMO_MSK);
}

static inline void csp_set_clo_src(csp_syscon_t *ptSysconBase, clo_src_e wCloSrc)
{
	ptSysconBase->OPTCR = (ptSysconBase->OPTCR & (~CLO_SRC_MSK)) | wCloSrc << CLO_SRC_POS;
}

static inline void csp_set_clo_div(csp_syscon_t *ptSysconBase, uint8_t byCloDiv)
{
	ptSysconBase->OPTCR = (ptSysconBase->OPTCR & (~CLO_DIV_MSK)) | byCloDiv << CLO_DIV_POS;
}


//IPCKERL0 - cpu0 ips
static inline void csp_bc_pcerl0_clk_en(csp_syscon_t *ptSysconBase, bcip_lowsel_e eIdx)
{
	ptSysconBase->IPCKERL0 = (0x01ul << eIdx);
}

//IPCKERH0 - cpu0 ips
static inline void csp_bc_pcerh0_clk_en(csp_syscon_t *ptSysconBase, bcip_highsel_e eIdx)
{
	ptSysconBase->IPCKERH0 = (0x01ul << eIdx);
}

//IPCKDRL0 - cpu0 ips
static inline void csp_bc_pcdrl0_clk_dis(csp_syscon_t *ptSysconBase, bcip_lowsel_e eIdx)
{
	ptSysconBase->IPCKDRL0 = (0x01ul << eIdx);
}

//IPCKDRH0 - cpu0 ips
static inline void csp_bc_pcdrh0_clk_dis(csp_syscon_t *ptSysconBase, bcip_lowsel_e eIdx)
{
	ptSysconBase->IPCKDRH0 = (0x01ul << eIdx);
}

//IPCKER1- cpu1 ips
static inline void csp_pcer1_clk_en(csp_syscon_t *ptSysconBase, lcip_sel_e eIdx)
{
	ptSysconBase->IPCKER1 = (0x01ul << eIdx);
}

//IPCKDR1-cpu1 ips
static inline void csp_bc_pcdr1_clk_dis(csp_syscon_t *ptSysconBase, lcip_sel_e eIdx)
{
	ptSysconBase->IPCKDR1 = (0x01ul << eIdx);
}
//PLLCR
static inline void csp_pll_set_clk_src(csp_syscon_t *ptSysconBase, pll_clk_sel_e eClkSel)
{
	ptSysconBase->PLLCR = (ptSysconBase->PLLCR & (~PLL_CLK_SEL_MSK)) | eClkSel << PLL_CLK_SEL_POS;
}

static inline uint8_t csp_pll_get_clk_src(csp_syscon_t *ptSysconBase)
{
	return (uint8_t)(ptSysconBase->PLLCR & PLL_CLK_SEL_MSK);
}

static inline void csp_pll_set_div_m(csp_syscon_t *ptSysconBase, uint8_t byDivM)
{
	ptSysconBase->PLLCR = (ptSysconBase->PLLCR & (~PLL_DIVM_MSK)) | byDivM << PLL_DIVM_POS;
}

static inline void csp_pll_set_nul(csp_syscon_t *ptSysconBase, uint8_t byNul)
{
	ptSysconBase->PLLCR = (ptSysconBase->PLLCR & (~PLL_NUL_MSK)) | byNul << PLL_NUL_POS;
}

static inline void csp_pll_set_ckp_div(csp_syscon_t *ptSysconBase, uint8_t byCkp_Div)
{
	ptSysconBase->PLLCR = (ptSysconBase->PLLCR & (~PLL_CKP_DIV_MSK)) | byCkp_Div << PLL_CKP_DIV_POS;
}

static inline void csp_pll_clk_enable(csp_syscon_t *ptSysconBase)
{
	ptSysconBase->PLLCR = (ptSysconBase->PLLCR & ~PLL_CKPEN_MSK)| (ENABLE << PLL_CKPEN_POS);
}

static inline void csp_pll_clk_disable(csp_syscon_t *ptSysconBase)
{
	ptSysconBase->PLLCR = (ptSysconBase->PLLCR & ~PLL_CKPEN_MSK)| (DISABLE << PLL_CKPEN_POS);
}

static inline void csp_pll_set_ckq_div(csp_syscon_t *ptSysconBase, uint8_t byCkp_Div)
{
	ptSysconBase->PLLCR = (ptSysconBase->PLLCR & (~PLL_CKQ_DIV_MSK)) | byCkp_Div << PLL_CKQ_DIV_POS;
}

//GCER
static inline void csp_clk_pm_enable(csp_syscon_t *ptSysconBase, clk_pm_e eClk)
{
	ptSysconBase->GCER = 0x1 << eClk;
}
static inline void csp_cpu1_rst_enable(csp_syscon_t *ptSysconBase)
{
	ptSysconBase->GCER = CPU1_RST;
}
static inline void csp_cpu1_clk_enable(csp_syscon_t *ptSysconBase)
{
	ptSysconBase->GCER = CPU1_SWON;
}
static inline void csp_xip_enable(csp_syscon_t *ptSysconBase)
{
	ptSysconBase->GCER = XIPEN;
}
static inline void csp_cram_prot_enable(csp_syscon_t *ptSysconBase)
{
	ptSysconBase->GCER = CRAM_PROT;
}
static inline void csp_sram_remap_enable(csp_syscon_t *ptSysconBase)
{
	ptSysconBase->GCER = MEM_REMAP;
}

//GCDR

static inline void csp_clk_pm_disable(csp_syscon_t *ptSysconBase, clk_pm_e eClk)
{
	ptSysconBase->GCDR = 0x1 << eClk;
}
static inline void csp_cpu1_rst_disable(csp_syscon_t *ptSysconBase)
{
	ptSysconBase->GCDR = CPU1_RST;
}
static inline void csp_cpu1_clk_disable(csp_syscon_t *ptSysconBase)
{
	ptSysconBase->GCDR = CPU1_SWON;
}
static inline void csp_xip_disable(csp_syscon_t *ptSysconBase)
{
	ptSysconBase->GCDR = XIPEN;
}
static inline void csp_cram_prot_disable(csp_syscon_t *ptSysconBase)
{
	ptSysconBase->GCDR = CRAM_PROT;
}
static inline void csp_sram_remap_disable(csp_syscon_t *ptSysconBase)
{
	ptSysconBase->GCDR = MEM_REMAP;
}

//emcr
static inline void csp_set_em_lfmd(csp_syscon_t *ptSysconBase, em_lfsel_e eMode)
{
	ptSysconBase->EMCR = (ptSysconBase->EMCR & (~EM_LFSEL_MSK))| (eMode << EM_LFSEL_POS);
}

static inline void csp_set_em_gain(csp_syscon_t *ptSysconBase, uint8_t byGn)
{
	ptSysconBase->EMCR = (ptSysconBase->EMCR & (~EM_GM_MSK)) | (byGn << EM_GM_POS);
}

static inline void csp_emfail_rst_enable(csp_syscon_t *ptSysconBase)
{
	ptSysconBase -> EMCR |= EM_RSTONFAIL_MSK;
}

static inline void csp_emfail_rst_disable(csp_syscon_t *ptSysconBase)
{
	ptSysconBase -> EMCR &= ~EM_RSTONFAIL_MSK;
}

//escr
static inline void csp_set_es_gain(csp_syscon_t *ptSysconBase, uint8_t byGn)
{
	ptSysconBase->ESCR = (ptSysconBase->ESCR & (~ES_GM_MSK)) | (byGn << ES_GM_POS);
}

static inline void csp_esfail_rst_enable(csp_syscon_t *ptSysconBase)
{
	ptSysconBase -> ESCR |= ES_RSTONFAIL_MSK;
}

static inline void csp_esfail_rst_disable(csp_syscon_t *ptSysconBase)
{
	ptSysconBase -> ESCR &= ~ES_RSTONFAIL_MSK;
}


//static inline void csp_eflash_lpmd_enable(csp_syscon_t *ptSysconBase, bool bEnable)
//{
//	ptSysconBase->OPT1 = (ptSysconBase->OPT1 & ~FLASH_LPMODE_MSK)| (bEnable << FLASH_LPMODE_POS);
//}


//lvdcr
static inline void csp_set_lvr_level(csp_syscon_t *ptSysconBase,lvr_level_e eLvl)
{
	ptSysconBase->LVDCR = (ptSysconBase->LVDCR & (~LVR_LV_MSK)) | (eLvl) << LVR_LV_POS | LVD_KEY;
}


static inline void csp_set_lvd_level(csp_syscon_t *ptSysconBase,lvd_level_e eLvl)
{
	ptSysconBase->LVDCR = (ptSysconBase->LVDCR & (~LVD_LV_MSK)) | (eLvl) << LVD_LV_POS | LVD_KEY;
}


static inline void csp_set_lvd_int_pol(csp_syscon_t *ptSysconBase, lvdint_pol_e ePol)
{
	ptSysconBase->LVDCR = (ptSysconBase->LVDCR & (~LVDINT_POL_MSK)) | ePol << LVDINT_POL_POS | LVD_KEY;
}

static inline void csp_lvd_lvr_enable(csp_syscon_t *ptSysconBase)
{
	ptSysconBase->LVDCR = (ptSysconBase->LVDCR &(~LVDEN_MSK)) | 5 | LVD_KEY; 
}

static inline void csp_lvd_lvr_disable(csp_syscon_t *ptSysconBase)
{
	ptSysconBase->LVDCR = (ptSysconBase->LVDCR &(~LVDEN_MSK))| LVD_DIS | LVD_KEY;
}

static inline void csp_lvr_rst_enable(csp_syscon_t *ptSysconBase)
{
	ptSysconBase->LVDCR = (ptSysconBase->LVDCR &(~LVR_SRT_MSK)) | LVD_KEY;
}

static inline void csp_lvr_rst_disable(csp_syscon_t *ptSysconBase)
{
	ptSysconBase->LVDCR |= LVR_SRT_MSK | LVD_KEY;
}

static inline void csp_lvd_reset_regs(csp_syscon_t *ptSysconBase)
{
	ptSysconBase -> LVDCR = LVD_KEY | LVD_DIS; 
}

static inline uint32_t csp_lvd_flag(csp_syscon_t *ptSysconBase)
{
	return ((ptSysconBase->LVDCR) & LVD_FLAG);
}

//IMCR
static inline void csp_syscon_int_enable(csp_syscon_t *ptSysconBase, syscon_int_e eInt)
{
	ptSysconBase->IMCR |= eInt; 
}

static inline void csp_syscon_int_disable(csp_syscon_t *ptSysconBase, syscon_int_e eInt)
{
	ptSysconBase->IMCR &= ~eInt;
}

//ICR
static inline void csp_syscon_int_clr(csp_syscon_t *ptSysconBase, syscon_int_e eInt)
{
	ptSysconBase->ICR = eInt; 
	
}

//MISR
static inline uint32_t csp_syscon_get_int_st(csp_syscon_t *ptSysconBase)
{
	return (ptSysconBase->MISR);
}

//IWDCR
static inline void csp_iwdt_set_ovt(csp_syscon_t *ptSysconBase, iwdt_ovt_e eLvl)
{
	ptSysconBase -> IWDCR = (ptSysconBase -> IWDCR & (~IWDT_OVT_MSK)) | eLvl << IWDT_OVT_POS | IWDTCR_KEY;
}
static inline void csp_iwdt_set_intt(csp_syscon_t *ptSysconBase, iwdt_intv_e eLvl)
{
	ptSysconBase -> IWDCR = (ptSysconBase -> IWDCR & (~IWDT_INTV_MSK)) | eLvl << IWDT_INTV_POS | IWDTCR_KEY;
}
static inline bool csp_iwdt_rd_st(csp_syscon_t *ptSysconBase)
{
	return ((ptSysconBase->IWDCR & IWDT_ST) >> 12);
}
static inline void csp_iwdt_debug_enable(csp_syscon_t *ptSysconBase, bool bEnable)
{
	ptSysconBase->IWDCR = (ptSysconBase->IWDCR & (~IWDT_DBGEN_MSK)) | (bEnable << IWDT_DBGEN_POS) |IWDTCR_KEY;
}

//IWDEDR
static inline void csp_iwdt_disable(csp_syscon_t *ptSysconBase)
{
	ptSysconBase -> IWDEDR = DIS_IWDT | IWDTE_KEY;
}

//IWDCNT
static inline void csp_iwdt_clr(csp_syscon_t *ptSysconBase)
{
	ptSysconBase -> IWDCNT = (ptSysconBase -> IWDCNT & (~IWDT_CLR_MSK)) | IWDT_CLR << IWDT_CLR_POS;
	while((ptSysconBase->IWDCNT & IWDT_CLR_BUSY) == IWDT_CLR_BUSY);
}
static inline uint32_t csp_iwdt_get_cnt(csp_syscon_t *ptSysconBase)
{
	return (ptSysconBase->IWDCNT & 0xfff);
}


//RSR
static inline void csp_rst_clr_st(csp_syscon_t *ptSysconBase)
{
	ptSysconBase->RSR = RSR_MSK;
}

static inline uint32_t csp_rst_rd_st(csp_syscon_t *ptSysconBase)
{
	return (ptSysconBase->RSR);
}

static inline void csp_rst_clr_rsr(csp_syscon_t *ptSysconBase, rst_st_e eSrcMsk)
{
	ptSysconBase->RSR = (0x1 << eSrcMsk);
}

//ramchk
static inline void csp_sramcheck_set_times(csp_syscon_t *ptSysconBase, uint32_t wVal)
{
	ptSysconBase -> RAMCHK = (ptSysconBase -> RAMCHK & (~RAMCHK_TIMES_MSK)) | wVal;
}

static inline void csp_sramcheck_enable(csp_syscon_t *ptSysconBase)
{
	ptSysconBase -> RAMCHK = (ptSysconBase -> RAMCHK & (~RAMCHK_MSK)) | RAMCHK_EN;
}

static inline void csp_sramcheck_disable(csp_syscon_t *ptSysconBase)
{
	ptSysconBase -> RAMCHK = (ptSysconBase -> RAMCHK & (~RAMCHK_MSK)) | RAMCHK_DIS;
}

static inline void csp_sramcheck_rst(csp_syscon_t *ptSysconBase)
{
	ptSysconBase -> RAMCHK = (ptSysconBase -> RAMCHK & (~RAMCHK_RST_MSK)) | RAMCHK_RST;
}

static inline void csp_sramcheck_int(csp_syscon_t *ptSysconBase)
{
	ptSysconBase -> RAMCHK = (ptSysconBase -> RAMCHK & (~RAMCHK_RST_MSK)) | RAMCHK_INT;
}

//eflchk
static inline void csp_flashcheck_set_times(csp_syscon_t *ptSysconBase, uint32_t wVal)
{
	ptSysconBase -> EFLCHK = (ptSysconBase -> EFLCHK & (~EFLCHK_TIMES_MSK)) | wVal;
}

static inline void csp_flashcheck_enable(csp_syscon_t *ptSysconBase)
{
	ptSysconBase -> EFLCHK = (ptSysconBase -> EFLCHK & (~EFLCHK_MSK)) | EFLCHK_EN;
}

static inline void csp_flashcheck_disable(csp_syscon_t *ptSysconBase)
{
	ptSysconBase -> EFLCHK = (ptSysconBase -> EFLCHK & (~EFLCHK_MSK)) | EFLCHK_DIS;
}

//wkcr 
static inline void csp_set_deepsleep_mode(csp_syscon_t *ptSysconBase, deepsleep_mode_e eDpSleep)
{
	ptSysconBase->WKCR = (ptSysconBase->WKCR & (~DPSLEEP_MODE_MSK)) | (eDpSleep  << DPSLEEP_MODE_P0S);
}
static inline void csp_set_deepsleep_wksrc(csp_syscon_t *ptSysconBase, uint16_t hwWkSrc)
{
	ptSysconBase->WKCR = (ptSysconBase->WKCR & (~DPSLEEP_WKSRC_MSK)) | hwWkSrc;
}


//UREG0/1/2/3
static inline uint32_t csp_get_ureg(csp_syscon_t *ptSysconBase, uint8_t byNum)
{
	return  *(uint32_t *)((uint32_t)&ptSysconBase->UREG0 + (byNum * 4));
}

static inline void csp_set_ureg(csp_syscon_t *ptSysconBase, uint8_t byNum, uint32_t wVal)
{
	*(uint32_t *)((uint32_t)&ptSysconBase->UREG0 + (byNum * 4)) = wVal;
}


#endif  /* _CSP_SYSCON_H*/

