/***********************************************************************//**
 * \file  csp_iis.h
 * \brief  I2S description and static inline functions at register level
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-11-24 <td>V0.0  <td>YT   <td>initial
 * </table>
 * *********************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CSP_IIS_H
#define _CSP_IIS_H

/* Includes ------------------------------------------------------------------*/
#include <soc.h>

/// \struct csp_i2s_t
/// \brief I2S reg description     
typedef struct
{
	__IOM  uint32_t IISEN;		 //0x00	 I2S ENABLE Register
	__IOM  uint32_t FUNCMODE;    //0X04  IIS Function Mode Register
	__IOM  uint32_t IISCNF_IN;   //0X08  IIS Receive Mode Control Register
	__IOM  uint32_t FSSTA;       //0X0C  IIS Data Bitwidth Control Register
	__IOM  uint32_t IISCNF_OUT;  //0X10  IIS Transmit Mode Control Register
	__IOM  uint32_t FADTLR;      //0X14  Fs Auto Detected Threshold Level Register
	__IOM  uint32_t SCCR;        //0X18  Sample Compress Control Register
	__IOM  uint32_t TXFTLR;      //0X1C  Transmit FIFO Threshold Level Register
	__IOM  uint32_t RXFTLR;      //0X20  Receive FIFO Threshold Level Register
	__IM   uint32_t TXFLR;       //0X24  Transmit FIFO Level Register
	__IM   uint32_t RXFLR;       //0X28  Receive FIFO Level Register
	__IM   uint32_t SR;          //0X2C  Status Register Register
	__IOM  uint32_t IMCR;         //0X30  Interrupt Mask Register
	__IM   uint32_t MISR;         //0X34  Interrupt Status Register
	__IM   uint32_t RISR;        //0X38  Raw Interrupt Status Register
	__OM   uint32_t ICR;         //0X3C  Interrupt Clear Register
	__IOM  uint32_t DMACR;       //0X40  DMA Control Register
	__IOM  uint32_t DMATDLR;     //0X44  DMA Transmit Data Threshold Register
	__IOM  uint32_t DMARDLR;     //0X48  DMA Receive Data Threshold Register
	__IOM  uint32_t DR;          //0X4C  Data Register
	__IOM  uint32_t DIV0_LEVEL;  //0X50  Divide i2s_clkgensource clock, get mclk or sclk
	__IOM  uint32_t DIV3_LEVEL;  //0X54  Divide i2s_clkgen source clock, get reference clock
} csp_i2s_t;

/*****************************************************************************
* IISEN : I2S Enable Register
******************************************************************************/
#define I2S_ENABLE_POS       (0)             //I2S Enable/DISABLE
#define I2S_ENABLE_MSK      (0x01ul << I2C_ENABLE_POS) 
typedef enum
{
	I2S_DISABLE = 0,
	I2S_ENABLE
}i2s_enable_e;

/*****************************************************************************
* FUNCMODE : I2S Function Mode Register
******************************************************************************/
#define I2S_TMODE_POS       (0)             //TX mode Enable/DISABLE
#define I2S_TMODE_MSK      (0x01ul << I2S_TMODE_POS) 
typedef enum
{
	I2S_TMODE_DISABLE = 0,
	I2S_TMODE_ENABLE
}i2s_tmode_e;

#define I2S_TMODE_WEN_POS       (1)             //TX mode write enable bit
#define I2S_TMODE_WEN_MSK      (0x01ul << I2S_TMODE_WEN_POS) 
typedef enum
{
	I2S_TMODE_WEN_DISABLE = 0,
	I2S_TMODE_WEN_ENABLE
}i2s_tmode_wen_e;

#define I2S_RMODE_POS       (4)             //RX mode Enable/DISABLE
#define I2S_RMODE_MSK      (0x01ul << I2S_RMODE_POS) 
typedef enum
{
	I2S_RMODE_DISABLE = 0,
	I2S_RMODE_ENABLE
}i2s_rmode_e;

#define I2S_RMODE_WEN_POS       (5)             //RX mode write enable bit
#define I2S_RMODE_WEN_MSK      (0x01ul << I2S_RMODE_WEN_POS) 
typedef enum
{
	I2S_RMODE_WEN_DISABLE = 0,
	I2S_RMODE_WEN_ENABLE
}i2s_rmode_wen_e;

/*****************************************************************************
* IISCNF_IN : I2S Input Interface Fromat Control Register
******************************************************************************/
#define I2S_RSAFS_POS       (0)             //Receive serial audio format select
#define I2S_RSAFS_MSK      (0x03ul << I2S_RSAFS_POS) 
typedef enum
{
	I2S_RSAFS_I2S = 0,
	I2S_RSAFS_RIGHT_JUSTIFIED,
	I2S_RSAFS_LEFT_JUSTIFIED,
	I2S_RSAFS_PCM
}i2s_rsafs_e;

#define I2S_RALOLRC_POS       (2)             //Receive active level of left/right channel
#define I2S_RALOLRC_MSK      (0x01ul << I2S_RALOLRC_POS) 
typedef enum
{
	I2S_RALORC_LOW_FOR_LEFT_CHANNEL = 0,
	I2S_RALORC_HIGH_FOR_LEFT_CHANNEL
}i2s_ralolrc_e;

#define I2S_RX_VOICE_EN_POS       (4)             //Number of the receive channel select
#define I2S_RX_VOICE_EN_MSK      (0x01ul << I2S_RX_VOICE_EN_POS) 
typedef enum
{
	I2S_RX_VOICE_DUAL = 0,
	I2S_RX_VOICE_SINGLE
}i2s_rx_voice_en_e;

#define I2S_RX_CH_SEL_POS       (5)             //Receive channel select
#define I2S_RX_CH_SEL_MSK      (0x01ul << I2S_RX_CH_SEL_POS) 
typedef enum
{
	I2S_RX_CH_SEL_RIGHT_CHANNEL = 0,
	I2S_RX_CH_SEL_LEFT_CHANNEL
}i2s_rx_ch_sel_e;

#define I2S_RXMODE_POS       (8)             //IIS receive mode select signal
#define I2S_RXMODE_MSK      (0x01ul << I2S_RXMODE_POS) 
typedef enum
{
	I2S_RXMODE_SLAVE_MODE = 0,
	I2S_RXMODE_MASTER_MODE
}i2s_rxmode_e;

#define I2S_RX_CLK_SEL_POS       (9)             //IIS receive slave mode clk select
#define I2S_RX_CLK_SEL_MSK      (0x01ul << I2S_RX_CLK_SEL_POS) 
typedef enum
{
	I2S_RX_CLK_SEL_SRC_CLK = 0,
	I2S_RX_CLK_SEL_MCLK_I
}i2s_rx_clk_sel_e;

#define I2S_RDELAY_POS       (12)             //IIS receive s_sclk/s_ws internal additional delay setting
#define I2S_RDELAY_MSK      (0x03ul << I2S_RDELAY_POS) 
typedef enum
{
	I2S_RDELAY_NO_DELAY = 0,
	I2S_RDELAY_ONE_SRC_CLK,
	I2S_RDELAY_TWO_SRC_CLK,
	I2S_RDELAY_THREE_SRC_CLK
}i2s_rdelay_e;

/*****************************************************************************
* FSSTA : I2S Data Bitwidth Control Register
******************************************************************************/
#define I2S_AIRAD_POS       (0)             //RX mode audio input tate detected
#define I2S_AIRAD_MSK      (0x01ul << I2S_AIRAD_POS) 
typedef enum
{
	I2S_AIRAD_DIS = 0,
	I2S_AIRAD_EN
}i2s_airad_e;

#define I2S_AFR_POS       (4)             //RX mode audio fundamental rate
#define I2S_AFR_MSK      (0x0ful << I2S_AFR_POS) 
typedef enum
{
	I2S_AFR_Fs_88p2_kHz = 0,        //Fs=88.2 kHz
	I2S_AFR_Fs_96_kHz = 1,          //Fs=96   kHz
	I2S_AFR_Fs_64_kHz = 2,          //Fs=64   kHz
	I2S_AFR_Fs_192_kHz = 3,         //Fs=192  kHz
	I2S_AFR_Fs_44p1_kHz = 4,        //Fs=44.1 kHz
	I2S_AFR_Fs_48_kHz = 5,          //Fs=48   kHz
	I2S_AFR_Fs_32_kHz = 6,          //Fs=32   kHz
	I2S_AFR_Fs_22p05_kHz = 8,       //Fs=22.05 kHz
	I2S_AFR_Fs_24_kHz = 9,          //Fs=24   kHz
	I2S_AFR_Fs_16_kHz = 10,         //Fs=16   kHz
	I2S_AFR_Fs_ERR = 11,            //Error Fs 
	I2S_AFR_Fs_11p025_kHz = 12,     //Fs=11.025 kHz
	I2S_AFR_Fs_12_kHz = 13,         //Fs=12 kHz
	I2S_AFR_Fs_8_kHz = 14           //Fs=14 kHz
}i2s_afr_e;


#define I2S_DATAWTH_POS       (8)             //I2S data width mode
#define I2S_DATAWTH_MSK      (0x0ful << I2S_DATAWTH_POS) 
typedef enum
{
	I2S_DATAWTH_BUS16_FIFO16 = 0,        //I2S BUS transmit/receive 16-bit data, FIFO 16-bit
	I2S_DATAWTH_BUS16_FIFO24 = 1,        //I2S BUS transmit/receive 16-bit data, FIFO 24-bit
	I2S_DATAWTH_BUS16_FIFO32 = 2,        //I2S BUS transmit/receive 16-bit data, FIFO 32-bit
	I2S_DATAWTH_BUS16_FIFO32_2 = 3,
	I2S_DATAWTH_BUS24_FIFO16 = 4,        //I2S BUS transmit/receive 24-bit data, FIFO 16-bit
	I2S_DATAWTH_BUS24_FIFO24 = 5,        //I2S BUS transmit/receive 24-bit data, FIFO 24-bit
	I2S_DATAWTH_BUS24_FIFO32 = 6,        //I2S BUS transmit/receive 24-bit data, FIFO 32-bit
	I2S_DATAWTH_BUS24_FIFO32_2 = 6,
	I2S_DATAWTH_BUS32_FIFO16 = 8,        //I2S BUS transmit/receive 32-bit data, FIFO 16-bit
	I2S_DATAWTH_BUS32_FIFO24 = 9,        //I2S BUS transmit/receive 32-bit data, FIFO 24-bit
	I2S_DATAWTH_BUS32_FIFO32 = 10,        //I2S BUS transmit/receive 32-bit data, FIFO 32-bit
	I2S_DATAWTH_BUS32_FIFO32_2 = 10,
	I2S_DATAWTH_BUS8_FIFO16 = 12,        //I2S BUS transmit/receive 8-bit data, FIFO 16-bit
	I2S_DATAWTH_BUS8_FIFO24 = 13,        //I2S BUS transmit/receive 8-bit data, FIFO 24-bit
	I2S_DATAWTH_BUS8_FIFO32 = 14,        //I2S BUS transmit/receive 8-bit data, FIFO 32-bit
	I2S_DATAWTH_BUS8_FIFO8 = 15,        //I2S BUS transmit/receive 8-bit data, FIFO 8-bit

}i2s_datawth_e;

#define I2S_SCLK_SEL_POS       (12)             //Multiplication of Fs and sclk 
#define I2S_SCLK_SEL_MSK      (0x03ul << I2S_SCLK_SEL_POS) 
typedef enum
{
	I2S_SCLK_SEL_32FS = 0,        //sclk=32*Fs
	I2S_SCLK_SEL_48FS = 1,        //sclk=48*Fs
	I2S_SCLK_SEL_64FS = 2,        //sclk=64*Fs
	I2S_SCLK_SEL_16FS = 3         //sclk=16*Fs

}i2s_sclk_sel_e;

#define I2S_MCLK_SEL_POS       (16)             //Multiplication of Fs and mclk_o 
#define I2S_MCLK_SEL_MSK      (0x01ul << I2S_MCLK_SEL_POS) 
typedef enum
{
	I2S_MCLK_SEL_256FS = 0,        //sclk=256*Fs
	I2S_MCLK_SEL_384FS = 1         //sclk=384*Fs
}i2s_mclk_sel_e;

/*****************************************************************************
* IISCNF_OUT : IIS Transmit Mode Control Register
******************************************************************************/
#define I2S_TSAFS_POS       (0)             //Transmit serial audio format select 
#define I2S_TSAFS_MSK      (0x03ul << I2S_TSAFS_POS) 
typedef enum
{
	I2S_TSAFS_I2S = 0,
	I2S_TSAFS_RIGHT_JUSTIFIED,
	I2S_TSAFS_LEFT_JUSTIFIED,
	I2S_TSAFS_PCM
}i2s_tsafs_e;


#define I2S_TALOLRC_POS       (2)             //Transmit active level of left/right channel
#define I2S_TALOLRC_MSK      (0x01ul << I2S_TALOLRC_POS) 
typedef enum
{
	I2S_TALOLRC_LOW_FOR_LEFT_CHANNEL = 0,
	I2S_TALOLRC_HIGH_FOR_LEFT_CHANNEL
}i2s_talolrc_e;

#define I2S_TX_VOICE_EN_POS       (3)             //Number of the transmit channel select
#define I2S_TX_VOICE_EN_MSK      (0x01ul << I2S_TX_VOICE_EN_POS) 
typedef enum
{
	I2S_TX_VOICE_DUAL = 0,
	I2S_TX_VOICE_SINGLE
}i2s_tx_voice_en_e;

#define I2S_TXMODE_POS       (4)             //IIS transmit mode select signal
#define I2S_TXMODE_MSK      (0x01ul << I2S_TXMODE_POS) 
typedef enum
{
	I2S_TXMODE_MASTER = 0,
	I2S_TXMODE_SLAVE
}i2s_txmode_e;

#define I2S_TX_CLK_SEL_POS       (5)             //IIS transmit slave mode clk select
#define I2S_TX_CLK_SEL_MSK      (0x01ul << I2S_TX_CLK_SEL_POS) 
typedef enum
{
	I2S_TX_CLK_SEL_SRC_CLK = 0,
	I2S_TX_CLK_SEL_MCLK_I
}i2s_tx_clk_sel_e;

/*****************************************************************************
* FADTLR : Fs Auto Detected Threshold Level  Register
******************************************************************************/
#define I2S_96FTR_POS       (0)     //Multiplication of ref_clk and 96Khz，96FTR=REF_CLK/96KHz
#define I2S_96FTR_MSK       (0x1Ful << I2S_96FTR_POS) 
#define I2S_96FTR(val)      (((val) & 0x1Ful) << I2S_96FTR_POS)  

#define I2S_88FTR_POS       (8)     //Multiplication of ref_clk and 88Khz，88FTR=REF_CLK/88KHz
#define I2S_88FTR_MSK       (0x1Ful << I2S_88FTR_POS) 
#define I2S_88FTR(val)      (((val) & 0x1Ful) << I2S_88FTR_POS)  

#define I2S_64FTR_POS       (16)     //Multiplication of ref_clk and 964Khz，64FTR=REF_CLK/64KHz
#define I2S_64FTR_MSK       (0x1Ful << I2S_64FTR_POS) 
#define I2S_64FTR(val)      (((val) & 0x1Ful) << I2S_64FTR_POS)   

#define I2S_192FTR_POS       (24)     //Multiplication of ref_clk and 192Khz，192FTR=REF_CLK/192KHz
#define I2S_192FTR_MSK       (0x1Ful << I2S_192FTR_POS) 
#define I2S_192FTR(val)      (((val) & 0x1Ful) << I2S_192FTR_POS)   

/*****************************************************************************
* SCCR : Sample Compress Control Register
******************************************************************************/
#define I2S_RVCCR_POS       (0)             //RX volume compress control register
#define I2S_RVCCR_MSK      (0x1ful << I2S_RVCCR_POS) 
typedef enum
{
	I2S_RVCCR_SHIFT0 = 0,    // No compress
	I2S_RVCCR_SHIFT1 = 1,    // Right shift the sample length  from 8/16/24/32 bits to 7/15/23/31 bits
	I2S_RVCCR_SHIFT2 = 2,    // Right shift the sample length  from 8/16/24/32 bits to 6/14/22/30 bits
	I2S_RVCCR_SHIFT3 = 3,    // Right shift the sample length  from 8/16/24/32 bits to 5/13/21/29 bits
	I2S_RVCCR_SHIFT4 = 4,    // Right shift the sample length  from 8/16/24/32 bits to 4/12/20/28 bits
	I2S_RVCCR_SHIFT5 = 5,    // Right shift the sample length  from 8/16/24/32 bits to 3/11/19/27 bits
	I2S_RVCCR_SHIFT6 = 6,    // Right shift the sample length  from 8/16/24/32 bits to 2/10/18/26 bits
	I2S_RVCCR_SHIFT7 = 7,    // Right shift the sample length  from 8/16/24/32 bits to 1/9/17/25 bits
	I2S_RVCCR_SHIFT8 = 8,    // Right shift the sample length  from 8/16/24/32 bits to 0/8/16/24 bits
	I2S_RVCCR_SHIFT9 = 9,    // Right shift the sample length  from 8/16/24/32 bits to 0/7/15/23 bits
	I2S_RVCCR_SHIFT10 = 10,    // Right shift the sample length  from 8/16/24/32 bits to 0/6/14/22 bits
	I2S_RVCCR_SHIFT11 = 11,    // Right shift the sample length  from 8/16/24/32 bits to 0/5/13/21 bits
	I2S_RVCCR_SHIFT12 = 12,    // Right shift the sample length  from 8/16/24/32 bits to 0/4/12/20 bits
	I2S_RVCCR_SHIFT13 = 13,    // Right shift the sample length  from 8/16/24/32 bits to 0/3/11/19 bits
	I2S_RVCCR_SHIFT14 = 14,    // Right shift the sample length  from 8/16/24/32 bits to 0/2/10/18bits
	I2S_RVCCR_SHIFT15 = 15,    // Right shift the sample length  from 8/16/24/32 bits to 0/1/9/17 bits
	I2S_RVCCR_SHIFT16 = 16    // Right shift the sample length  from 8/16/24/32 bits to 0/0/8/16 bits
}i2s_rvccr_e;

#define I2S_SSRCR_POS       (5)             // Sub sample rate compress control register
#define I2S_SSRCR_MSK      (0x03ul << I2S_SSRCR_POS) 
typedef enum
{
	I2S_SSRCR_NO_COMPRESS = 0,
	I2S_SSRCR_ONE_COMPRESS = 1,
	I2S_SSRCR_THREE_COMPRESS = 2,
}i2s_ssrcr_e;

#define I2S_TVCCR_POS       (8)             //TX volume compress control register
#define I2S_TVCCR_MSK      (0x1ful << I2S_TVCCR_POS) 
typedef enum
{
	I2S_TVCCR_SHIFT0 = 0,    // No compress
	I2S_TVCCR_SHIFT1 = 1,    // Right shift the sample length  from 8/16/24/32 bits to 7/15/23/31 bits
	I2S_TVCCR_SHIFT2 = 2,    // Right shift the sample length  from 8/16/24/32 bits to 6/14/22/30 bits
	I2S_TVCCR_SHIFT3 = 3,    // Right shift the sample length  from 8/16/24/32 bits to 5/13/21/29 bits
	I2S_TVCCR_SHIFT4 = 4,    // Right shift the sample length  from 8/16/24/32 bits to 4/12/20/28 bits
	I2S_TVCCR_SHIFT5 = 5,    // Right shift the sample length  from 8/16/24/32 bits to 3/11/19/27 bits
	I2S_TVCCR_SHIFT6 = 6,    // Right shift the sample length  from 8/16/24/32 bits to 2/10/18/26 bits
	I2S_TVCCR_SHIFT7 = 7,    // Right shift the sample length  from 8/16/24/32 bits to 1/9/17/25 bits
	I2S_TVCCR_SHIFT8 = 8,    // Right shift the sample length  from 8/16/24/32 bits to 0/8/16/24 bits
	I2S_TVCCR_SHIFT9 = 9,    // Right shift the sample length  from 8/16/24/32 bits to 0/7/15/23 bits
	I2S_TVCCR_SHIFT10 = 10,    // Right shift the sample length  from 8/16/24/32 bits to 0/6/14/22 bits
	I2S_TVCCR_SHIFT11 = 11,    // Right shift the sample length  from 8/16/24/32 bits to 0/5/13/21 bits
	I2S_TVCCR_SHIFT12 = 12,    // Right shift the sample length  from 8/16/24/32 bits to 0/4/12/20 bits
	I2S_TVCCR_SHIFT13 = 13,    // Right shift the sample length  from 8/16/24/32 bits to 0/3/11/19 bits
	I2S_TVCCR_SHIFT14 = 14,    // Right shift the sample length  from 8/16/24/32 bits to 0/2/10/18bits
	I2S_TVCCR_SHIFT15 = 15,    // Right shift the sample length  from 8/16/24/32 bits to 0/1/9/17 bits
	I2S_TVCCR_SHIFT16 = 16    // Right shift the sample length  from 8/16/24/32 bits to 0/0/8/16 bits
}i2s_tvccr_e;

/*****************************************************************************
* TXFTLR : Transmit FIFO Threshold Level Register
******************************************************************************/
#define	I2S_TXFTLR_POS		(0)
#define	I2S_TXFTLR_MSK		(0x1ful << I2S_TXFTLR_POS)
#define I2S_TXFTLR(val)     (((val) & 0x1Ful) << I2S_TXFTLR_POS) 

/*****************************************************************************
* RXFTLR : Receive FIFO Threshold Level Register
******************************************************************************/
#define	I2S_RXFTLR_POS		(0)
#define	I2S_RXFTLR_MSK		(0x1ful << I2S_RXFTLR_POS)
#define I2S_RXFTLR(val)     (((val) & 0x1Ful) << I2S_RXFTLR_POS) 

/*****************************************************************************
* SR : Status Register
******************************************************************************/
typedef enum
{
	RX_BUSY = (0x01ul << 0),   //IIS Rx Busy Flag               	
	TX_BUSY = (0x01ul << 1),   //IIS Tx Busy Flag   
	TFNF = (0x01ul << 2),   //Transmit FIFO Not Full    	    
	TFE = (0x01ul << 3),   //Transmit FIFO Empty    
	RFNE = (0x01ul << 4),   //Receive FIFO Not Empty.          
	RFF = (0x01ul << 5)    //Receive FIFO Full.        
}i2s_status_e;

/*****************************************************************************
* RISR/MISR/IMSCR/ICR : I2S Interrupt Mask/Status Register
******************************************************************************/
typedef enum
{
	I2S_WADEM_INT = (0x01ul << 0),   //I2S Interrupt Status  
	I2S_TXUIRM_INT = (0x01ul << 1),   //I2S Interrupt Status   
	I2S_TXOIM_INT = (0x01ul << 2),   //I2S Interrupt Status         
	I2S_RXUIM_INT = (0x01ul << 3),   //I2S Interrupt Status         
	I2S_RXOIM_INT = (0x01ul << 4),   //I2S Interrupt Status         
	I2S_TXEIM_INT = (0x01ul << 5),   //I2S Interrupt Status         
	I2S_RXFIM_INT = (0x01ul << 6),   //I2S Interrupt Status         
	I2S_IRBFCM_INT = (0x01ul << 7),   //I2S Interrupt Status         
	I2S_ITBFCM_INT = (0x01ul << 8),   //I2S Interrupt Status         
	I2S_IFSCM_INT = (0x01ul << 9)    //I2S Interrupt Status                 
}i2s_int_e;

/******************************************************************************
* DMACR : DMA Control register
******************************************************************************/
#define I2S_RDMA_EN_POS       (0)             //IIS receive DMA Enable
#define I2S_RDMA_EN_MSK      (0x01ul << I2S_RDMA_EN_POS) 
typedef enum
{
	I2S_RDMA_DIS = 0,
	I2S_RDMA_EN
}i2s_rdma_en_e;

#define I2S_TDMA_EN_POS       (1)             //IIS transmit DMA Enable
#define I2S_TDMA_EN_MSK      (0x01ul << I2S_TDMA_EN_POS) 
typedef enum
{
	I2S_TDMA_DIS = 0,
	I2S_TDMA_EN
}i2s_tdma_en_e;

/******************************************************************************
* DMATDLR : DMA Transmit Data Level register
******************************************************************************/
#define I2S_DMATDLR_POS       (0)     
#define I2S_DMATDLR_MSK       (0x1ful << I2S_DMATDLR_POS) 
#define I2S_DMATDLR(val)      (((val) & 0x1ful) << I2S_DMATDLR_POS)  

/******************************************************************************
* DMARDLR : DMA Receive Data Level register
******************************************************************************/
#define I2S_DMARDLR_POS       (0)     
#define I2S_DMARDLR_MSK       (0x1ful << I2S_DMARDLR_POS) 
#define I2S_DMARDLR(val)      (((val) & 0x1ful) << I2S_DMARDLR_POS)  

/******************************************************************************
* DR : Data register
******************************************************************************/
#define	I2S_DATA_POS		(0)				//Transmit/Receive FIFO 		 
#define	I2S_DATA_MSK		(0xfffffffful << I2S_DATA_POS)

/******************************************************************************
* DIV0_LEVEL : Divide i2s_clkgensource clock, get mclk or sclk
******************************************************************************/
#define I2S_DIV0_LEVEL_POS       (0)     
#define I2S_DIV0_LEVEL_MSK       (0xfful << I2S_DIV0_LEVEL_POS) 
#define I2S_DIV0_LEVEL(val)      (((val) & 0xfful) << I2S_DIV0_LEVEL_POS) 

/******************************************************************************
* DIV3_LEVEL : Divide i2s_clkgen source clock, get reference clock
******************************************************************************/
#define I2S_DIV3_LEVEL_POS       (0)     
#define I2S_DIV3_LEVEL_MSK       (0xfful << I2S_DIV3_LEVEL_POS) 
#define I2S_DIV3_LEVEL(val)      (((val) & 0xfful) << I2S_DIV3_LEVEL_POS) 

/*****************************************************************************
 ******************** IIS inline Functions Declaration ***********************
 *****************************************************************************/


static inline void csp_i2s_enable(csp_i2s_t* ptI2sBase)
{
	ptI2sBase->IISEN = I2S_ENABLE;
}

static inline void csp_i2s_disbale(csp_i2s_t* ptI2sBase)
{
	ptI2sBase->IISEN &= I2S_DISABLE;
}

static inline void csp_i2s_set_transmit_mode(csp_i2s_t* ptI2sBase, uint32_t en)
{
	uint32_t val = ptI2sBase->FUNCMODE;

	val |= I2S_TMODE_WEN_MSK;
	val &= ~I2S_TMODE_MSK;

	if (en) {
		val |= I2S_TMODE_MSK;
	}

	ptI2sBase->FUNCMODE = val;


}

static inline void csp_i2s_set_receive_mode(csp_i2s_t* ptI2sBase, uint32_t en)
{
	uint32_t val = ptI2sBase->FUNCMODE;

	val |= I2S_RMODE_WEN_MSK;
	val &= ~I2S_RMODE_MSK;

	if (en) {
		val |= I2S_RMODE_MSK;
	}

	ptI2sBase->FUNCMODE = val;
}

static inline void csp_i2s_set_full_duplex_mode(csp_i2s_t* ptI2sBase, uint32_t en)
{
	uint32_t val = ptI2sBase->FUNCMODE;

	val |= I2S_TMODE_WEN_MSK;
	val |= I2S_RMODE_WEN_MSK;
	val &= ~I2S_TMODE_MSK;
	val &= ~I2S_RMODE_MSK;

	if (en) {
		val |= I2S_TMODE_MSK;
		val |= I2S_RMODE_MSK;
	}

	ptI2sBase->FUNCMODE = val;
}

static inline void csp_i2s_set_receive_delay(csp_i2s_t* ptI2sBase, i2s_rdelay_e eRdelay)
{
	ptI2sBase->IISCNF_IN = (ptI2sBase->IISCNF_IN & (~I2S_RDELAY_MSK)) | (eRdelay << I2S_RDELAY_POS);
}

static inline void csp_i2s_set_receive_mode_master(csp_i2s_t* ptI2sBase)
{
	ptI2sBase->IISCNF_IN = (ptI2sBase->IISCNF_IN & (~I2S_RXMODE_MSK)) | (I2S_RXMODE_MASTER_MODE << I2S_RXMODE_POS);
}

static inline void csp_i2s_set_receive_mode_slave(csp_i2s_t* ptI2sBase)
{
	ptI2sBase->IISCNF_IN = (ptI2sBase->IISCNF_IN & (~I2S_RXMODE_MSK)) | (I2S_RXMODE_SLAVE_MODE << I2S_RXMODE_POS);
}

static inline void csp_i2s_set_receive_mode_slave_clock(csp_i2s_t* ptI2sBase, i2s_rx_clk_sel_e eRxClkSel)
{
	ptI2sBase->IISCNF_IN = (ptI2sBase->IISCNF_IN & (~I2S_RX_CLK_SEL_MSK)) | (eRxClkSel << I2S_RX_CLK_SEL_POS);
}

static inline void csp_i2s_set_number_of_receive_mode_source_channel(csp_i2s_t* ptI2sBase, i2s_rx_voice_en_e eRxVoiceEn)
{
	ptI2sBase->IISCNF_IN = (ptI2sBase->IISCNF_IN & (~I2S_RX_VOICE_EN_MSK)) | (eRxVoiceEn << I2S_RX_VOICE_EN_POS);
}

static inline void csp_i2s_set_receive_mode_channel(csp_i2s_t* ptI2sBase, i2s_rx_ch_sel_e eRxChSel)
{
	ptI2sBase->IISCNF_IN = (ptI2sBase->IISCNF_IN & (~I2S_RX_CH_SEL_MSK)) | (eRxChSel << I2S_RX_CH_SEL_POS);
}

static inline void csp_i2s_set_receive_mode_channel_polarity_for_left(csp_i2s_t* ptI2sBase, i2s_ralolrc_e eRalolrc)
{
	ptI2sBase->IISCNF_IN = (ptI2sBase->IISCNF_IN & (~I2S_RALOLRC_MSK)) | (eRalolrc << I2S_RALOLRC_POS);
}

static inline void csp_i2s_set_receive_mode_format(csp_i2s_t* ptI2sBase, i2s_rsafs_e eRsafs)
{
	ptI2sBase->IISCNF_IN = (ptI2sBase->IISCNF_IN & (~I2S_RSAFS_MSK)) | (eRsafs << I2S_RSAFS_POS);
}

static inline void csp_i2s_set_receive_mode_mclk_sel_multiple_fs(csp_i2s_t* ptI2sBase, i2s_mclk_sel_e eMclkSel)
{
	ptI2sBase->FSSTA = (ptI2sBase->FSSTA & (~I2S_MCLK_SEL_MSK)) | (eMclkSel << I2S_MCLK_SEL_POS);
}

static inline void csp_i2s_set_receive_mode_sclk_sel_multiple_fs(csp_i2s_t* ptI2sBase, i2s_sclk_sel_e eSclkSel)
{
	ptI2sBase->FSSTA = (ptI2sBase->FSSTA & (~I2S_SCLK_SEL_MSK)) | (eSclkSel << I2S_SCLK_SEL_POS);
}

static inline void csp_i2s_set_data_width_mode(csp_i2s_t* ptI2sBase, i2s_datawth_e eDataWidth)
{
	ptI2sBase->FSSTA = (ptI2sBase->FSSTA & (~I2S_DATAWTH_MSK)) | (eDataWidth << I2S_DATAWTH_POS);
}

static inline uint8_t csp_i2s_get_receive_mode_audio_fundamental_rate(csp_i2s_t* ptI2sBase)
{
	return (uint8_t)((ptI2sBase->FSSTA & 0xff) >> 4);
}

static inline void csp_i2s_set_receive_mode_audio_input_rate_detected(csp_i2s_t* ptI2sBase, i2s_airad_e eAirad)
{
	ptI2sBase->FSSTA = (ptI2sBase->FSSTA & (~I2S_AIRAD_MSK)) | (eAirad << I2S_AIRAD_POS);
}

static inline void csp_i2s_set_number_of_transmit_mode_source_channel(csp_i2s_t* ptI2sBase, i2s_tx_voice_en_e eTxVoiceEn)
{
	ptI2sBase->IISCNF_OUT = (ptI2sBase->IISCNF_OUT & (~I2S_TX_VOICE_EN_MSK)) | (eTxVoiceEn << I2S_TX_VOICE_EN_POS);
}

static inline void csp_i2s_set_transmit_mode_channel_polarity_for_left(csp_i2s_t* ptI2sBase, i2s_talolrc_e eTalolrc)
{
	ptI2sBase->IISCNF_OUT = (ptI2sBase->IISCNF_OUT & (~I2S_TALOLRC_MSK)) | (eTalolrc << I2S_TALOLRC_POS);
}

static inline void csp_i2s_set_transmit_mode_format(csp_i2s_t* ptI2sBase, i2s_tsafs_e eTsafs)
{
	ptI2sBase->IISCNF_OUT = (ptI2sBase->IISCNF_OUT & (~I2S_TSAFS_MSK)) | (eTsafs << I2S_TSAFS_POS);
}

static inline void csp_i2s_set_transmit_mode_master(csp_i2s_t* ptI2sBase)
{
	ptI2sBase->IISCNF_OUT = (ptI2sBase->IISCNF_OUT & (~I2S_TXMODE_MSK)) | (I2S_TXMODE_MASTER << I2S_TXMODE_POS);
}

static inline void csp_i2s_set_transmit_mode_slave(csp_i2s_t* ptI2sBase)
{
	ptI2sBase->IISCNF_OUT = (ptI2sBase->IISCNF_OUT & (~I2S_TXMODE_MSK)) | (I2S_TXMODE_SLAVE << I2S_TXMODE_POS);
}

static inline void csp_i2s_set_transmit_mode_slave_clock(csp_i2s_t* ptI2sBase, i2s_tx_clk_sel_e eTxClkSel)
{
	ptI2sBase->IISCNF_OUT = (ptI2sBase->IISCNF_OUT & (~I2S_TX_CLK_SEL_MSK)) | (eTxClkSel << I2S_TX_CLK_SEL_POS);
}

static inline void csp_i2s_set_192k_fs_threshold(csp_i2s_t* ptI2sBase, uint32_t level)
{
	ptI2sBase->FADTLR |= level << I2S_192FTR_POS;
}

static inline void csp_i2s_set_64k_fs_threshold(csp_i2s_t* ptI2sBase, uint32_t level)
{
	ptI2sBase->FADTLR |= level << I2S_64FTR_POS;
}

static inline void csp_i2s_set_88k_fs_threshold(csp_i2s_t* ptI2sBase, uint32_t level)
{
	ptI2sBase->FADTLR |= level << I2S_88FTR_POS;
}

static inline void csp_i2s_set_96k_fs_threshold(csp_i2s_t* ptI2sBase, uint32_t level)
{
	ptI2sBase->FADTLR |= level << I2S_96FTR_POS;
}

static inline void csp_i2s_set_tx_volume_compress_bits(csp_i2s_t* ptI2sBase, uint32_t shift)
{
	ptI2sBase->SCCR = (ptI2sBase->SCCR & (~I2S_TVCCR_MSK)) | (shift << I2S_TVCCR_POS);
}

static inline void csp_i2s_set_sub_sample_rate_compress(csp_i2s_t* ptI2sBase, i2s_ssrcr_e eSsrcr)
{
	ptI2sBase->SCCR = (ptI2sBase->SCCR & (~I2S_SSRCR_MSK)) | (eSsrcr << I2S_SSRCR_POS);
}

static inline void csp_i2s_set_rx_volume_compress_bits(csp_i2s_t* ptI2sBase, uint32_t shift)
{
	ptI2sBase->SCCR = (ptI2sBase->SCCR & (~I2S_RVCCR_MSK)) | (shift << I2S_RVCCR_POS);
}

static inline void csp_i2s_set_transmit_fifo_level(csp_i2s_t* ptI2sBase, uint32_t level)
{
	ptI2sBase->TXFTLR = (ptI2sBase->TXFTLR & (~I2S_TXFTLR_MSK)) | (level << I2S_TXFTLR_POS);
}

static inline void csp_i2s_set_receive_fifo_level(csp_i2s_t* ptI2sBase, uint32_t level)
{
	ptI2sBase->RXFTLR = (ptI2sBase->RXFTLR & (~I2S_RXFTLR_MSK)) | (level << I2S_RXFTLR_POS);
}

static inline uint32_t csp_i2s_get_transmit_fifo_level(csp_i2s_t* ptI2sBase)
{
	return (uint32_t)ptI2sBase->TXFLR;
}

static inline uint32_t csp_i2s_get_receive_fifo_level(csp_i2s_t* ptI2sBase)
{
	return (uint32_t)ptI2sBase->RXFLR;
}

static inline uint32_t csp_i2s_get_i2s_status(csp_i2s_t* ptI2sBase)
{
	return (uint32_t)ptI2sBase->SR;
}

static inline uint32_t csp_i2s_get_i2s_irq_status(csp_i2s_t* ptI2sBase)
{
	return ptI2sBase->MISR;
}

static inline uint32_t csp_i2s_get_i2s_irq_raw_status(csp_i2s_t* ptI2sBase)
{
	return ptI2sBase->RISR;
}

static inline void csp_i2s_set_irq(csp_i2s_t* ptI2sBase, uint32_t val)
{
	ptI2sBase->IMCR = val;
}

static inline void csp_i2s_clear_irq(csp_i2s_t* ptI2sBase, uint32_t val)
{
	ptI2sBase->ICR = val;
}

static inline void csp_i2s_set_receive_dma(csp_i2s_t* ptI2sBase, i2s_rdma_en_e eRdmaEn)
{
	ptI2sBase->DMACR = (ptI2sBase->DMACR & (~I2S_RDMA_EN_MSK)) | (eRdmaEn << I2S_RDMA_EN_POS);
}

static inline void csp_i2s_set_transmit_dma(csp_i2s_t* ptI2sBase, i2s_tdma_en_e eTdmaEn){

ptI2sBase->DMACR = (ptI2sBase->DMACR & (~I2S_TDMA_EN_MSK)) | (eTdmaEn << I2S_TDMA_EN_POS);
}

static inline void csp_i2s_set_transmit_dma_data_num_level(csp_i2s_t* ptI2sBase, uint32_t level)
{
	ptI2sBase->DMATDLR = level;
}

static inline void csp_i2s_set_receive_dma_data_num_level(csp_i2s_t* ptI2sBase, uint32_t level)
{
	ptI2sBase->DMARDLR = level;
}

static inline void csp_i2s_transmit_data(csp_i2s_t* ptI2sBase, uint32_t data)
{
	ptI2sBase->DR = data;
}

static inline uint32_t csp_i2s_receive_data(csp_i2s_t* ptI2sBase)
{
	return (uint32_t)(ptI2sBase->DR);
}

static inline void csp_i2s_set_div_sclk(csp_i2s_t* ptI2sBase, uint32_t div)
{
	ptI2sBase->DIV0_LEVEL = div;
}

static inline void csp_i2s_set_div_ref_clk(csp_i2s_t* ptI2sBase, uint32_t div)
{
	ptI2sBase->DIV3_LEVEL = div;
}





#endif