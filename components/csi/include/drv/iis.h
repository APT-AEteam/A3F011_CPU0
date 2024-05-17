/***********************************************************************//** 
 * \file  iis.h
 * \brief  IIS head file 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-12-12 <td>V0.0  <td>YT   <td>initial
 * </table>
 * *********************************************************************
*/

#ifndef _DRV_IIS_H_
#define _DRV_IIS_H_
#include <stdint.h>
#include <stdbool.h>
#include <drv/common.h>
#include <drv/dma.h>
#include "csp.h"


#define I2S_SRC_CLK_FREQ  12288000
//#define I2S_SRC_CLK_FREQ  49152000


typedef enum
{
	IIS_INTSRC_NONE       = (0x00ul << 0),
	IIS_INTSRC_WADEM	  = (0x01ul << 0),   //IIS Interrupt Status  
	IIS_INTSRC_TXUIRM     = (0x01ul << 1),   //IIS Interrupt Status   
	IIS_INTSRC_TXOIM      = (0x01ul << 2),   //IIS Interrupt Status         
	IIS_INTSRC_RXUIM      = (0x01ul << 3),   //IIS Interrupt Status         
	IIS_INTSRC_RXOIM      = (0x01ul << 4),   //IIS Interrupt Status         
	IIS_INTSRC_TXEIM      = (0x01ul << 5),   //IIS Interrupt Status         
	IIS_INTSRC_RXFIM      = (0x01ul << 6),   //IIS Interrupt Status         
	IIS_INTSRC_IRBFCM     = (0x01ul << 7),   //IIS Interrupt Status         
	IIS_INTSRC_ITBFCM     = (0x01ul << 8),   //IIS Interrupt Status         
	IIS_INTSRC_IFSCM      = (0x01ul << 9)    //IIS Interrupt Status 
} csi_iis_intsrc_e;


typedef enum
{
    IIS_TX,   // I2S transmitter mode
    IIS_RX,    // I2S receiver mode
} csi_iis_mode_e;	 //IIS_MODE_E;

typedef enum
{
    IIS_MASTER,   // I2S  master mode
    IIS_SLAVE,    // I2S r slave mode
} csi_iis_workmode_e;	 //IIS_workMODE_E;

typedef enum
{
    IIS_SAMPLERATE_8K,
    IIS_SAMPLERATE_16K,
	IIS_SAMPLERATE_24K,
    IIS_SAMPLERATE_32K,
    IIS_SAMPLERATE_441K,
    IIS_SAMPLERATE_48K,
    IIS_SAMPLERATE_96K,
    IIS_SAMPLERATE_192K,
} csi_iis_samplerate_e;   //IIS_SAMPLERATE_E;

typedef enum
{
	IIS_DATAWIDTH_8BIT,
    IIS_DATAWIDTH_16BIT,
    IIS_DATAWIDTH_24BIT,
	IIS_DATAWIDTH_32BIT,
} csi_iis_datawidth_e;   //IIS_DATA_WIDTH;

typedef enum
{
    IIS,           
    RIGHT_JUSTIFY,
    LEFT_JUSTIFY,
	PCM,
} csi_iis_data_align_e;  //IIS_DATA_ALIGN_E;

typedef enum {
    I2S_MCLK_256FS ,
    I2S_MCLK_384FS ,
} csi_i2s_mclk_freq_e;

typedef enum {
    I2S_SCLK_32FS,      ///< SCLK Freq = 32 * sample_rate, freq must >= sample_rate * sample_witch
    I2S_SCLK_48FS,
    I2S_SCLK_64FS,
    I2S_SCLK_16FS,
} csi_i2s_sclk_freq_e;



typedef void (*iis_cb_t)(uint32_t *pdata);      //I2S function pointer, used for callback function

typedef struct 
{
	/*
    GPIO_IDX_E iis_mclk;
    GPIO_IDX_E iis_lrck;
    GPIO_IDX_E iis_bclk;
    GPIO_IDX_E iis_data;*/  //GPIO放到demo里设置
	csi_iis_mode_e eMode; //IIS MODE : tx or rx
    csi_iis_workmode_e eWorkMode;    //work mode  : slave or master
    csi_iis_samplerate_e eSampleRate;  //IIS samplerate
    csi_iis_datawidth_e eDataWidth;    //IIS datawidth
    csi_iis_data_align_e eDataAlign;  //IIS data align 
    //uint32_t sys_mclk;     // system clock

    csi_i2s_sclk_freq_e eSclkFreq;                  ///< I2S sclk freq select. example:32fs = 32 * sample_rate
    csi_i2s_mclk_freq_e eMclkFreq;                  ///< I2S mclk freq select. example:256fs = 256 * sample_rate

	csi_iis_intsrc_e eInt;  	  //IIS INTERRPUT SET
    uint16_t len;         //sizeof(data)
    uint32_t *pdata;      // pointer of i2s data 
    //dma_cb_t cb;   //??dma回调函数指针，不要回调函数了，不在中断中用DMA收发数据
} csi_iis_config_t;

/** \brief initialize iis 
 * 
 *  \param[in] ptI2sBase: pointer of iis register structure   I2S0/I2S1
 *  \param[in] iis_config: pointer of iis config structure
 *  \return none
 */ 
csi_error_t csi_iis_init(csp_i2s_t *ptI2sBase,csi_iis_config_t *iis_config);

/** \brief start iis 
 * 
 *  \param[in] ptI2sBase: pointer of iis register structure
 *  \return none
 */ 
uint32_t csi_iis_start(csp_i2s_t *ptI2sBase);

/** \brief stop iis 
 * 
 *  \param[in] ptI2sBase: pointer of iis register structure
 *  \return none
 */ 
uint32_t csi_iis_stop(csp_i2s_t *ptI2sBase);



/** \brief iis dma send mode init
 * 
 *  \param[in] ptI2sBase: pointer of iis register structure
 *  \param[in] ptDmaBase: pointer of dma register structure
 *  \param[in] eDmaCh: channel number of dma, eDmaCh: DMA_CH0` DMA_CH3
 *  \param[in] eEtbCh: channel id number of etb, eEtbCh >= ETB_CH8
 *  \return  error code \ref csi_error_t
 */
csi_error_t csi_iis_dma_tx_init(csp_i2s_t *ptI2sBase, csi_dma_ch_e eDmaCh, csi_etb_ch_e eEtbCh);


/*
 *  功能描述：设置I2S输出左右声道对应的LRCk高低电平
 *  参数说明：
 *        idx: i2S序号
 *        flag:  
 *              true : Low for left channel , default
 *              flash : High for left channel
 */
 /** \brief enable iic 
 * 
 *  \param[in] ptI2sBase: pointer of iis register structure
 *  \return none
 */ 
void iis_set_out_letf_right_channel(csp_i2s_t *ptI2sBase,bool flag);


/** \brief send data from iis, this function is dma mode
 * 
 *  \param[in] ptI2sBase: pointer of iis register structure
 *  \param[in] ptDmaBase: pointer of dma register structure
 *  \param[in] eDmaCh: channel number of dma, eDmaCh: DMA_CH0` DMA_CH3
 *  \param[in] pData: pointer to buffer with data to send to iis transmitter.
 *  \param[in] hwSize: number of data to send (byte); hwSize <= 0xfff
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_iis_send_dma(csp_i2s_t *ptI2sBase, csi_dma_ch_e eDmaCh, const void *pData, uint16_t hwSize);

/** \brief iis dma receive mode init
 * 
 *  \param[in] ptI2sBase: pointer of iis register structure
 *  \param[in] eDmaCh: channel number of dma, eDmaCh: DMA_CH0` DMA_CH3
 *  \param[in] eEtbCh: channel id number of etb, eEtbCh >= ETB_CH8
 *  \return  error code \ref csi_error_t
 */
csi_error_t csi_iis_dma_rx_init(csp_i2s_t *ptI2sBase, csi_dma_ch_e eDmaCh, csi_etb_ch_e eEtbCh);

csi_error_t csi_iis_recv_dma(csp_i2s_t *ptI2sBase, csi_dma_ch_e eDmaCh, void *pData, uint16_t hwSize);

/** \brief iis interrupt handle 
 * 
 *  \param[in] ptI2sBase: pointer of iis register structure
 *  \return none
 */
void iis_irqhandler(csp_i2s_t *ptI2sBase);




/** \brief iis clear interrupt
 * 
 *  \param[in] ptI2sBase: pointer of iis register structure
 *  \return none
 */
void csi_iis_clr_isr(csp_i2s_t *ptI2sBase);

#endif