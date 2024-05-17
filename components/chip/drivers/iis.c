/***********************************************************************//** 
 * \file  iis.c   csi2 https://yoc.docs.t-head.cn/yocbook/Chapter3-AliOS/CSI%E8%AE%BE%E5%A4%87%E9%A9%B1%E5%8A%A8%E6%8E%A5%E5%8F%A3/CSI2/I2S.html#csii2stxsetbuffer
 * \brief  IIS description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-12-9 <td>V0.0  <td>YT   <td>initial
 * </table>
 * *********************************************************************/
 
#include <sys_clk.h> 
#include <clk.h>
#include <drv/iis.h> 
#include <drv/irq.h>
#include <drv/gpio.h> 
#include <drv/pin.h>
#include <stdbool.h> 
#include <drv/dma.h>
#include <drv/etb.h>
#include <drv/tick.h>

typedef struct 
{
    uint16_t len;
    uint32_t *data;
    iis_cb_t cb;
    uint8_t en;
    uint8_t trx;      //tx:0; rx:1
}drv_iis_handle_t;

#define CONFIG_I2S_NUM 2

drv_iis_handle_t drv_iis_handle[CONFIG_I2S_NUM];



/** \brief config iis div0 div1
 * 
 *  \param[in] ptI2sBase: pointer of iis register structure
 *  \param[in] iis_config: iis configuration
 *  \return  
 */ 
static int32_t config_iis_div(csp_i2s_t *ptI2sBase,csi_iis_config_t *iis_config)
{
    uint32_t sample_rate;

    switch(iis_config->eSampleRate)
    {
        case IIS_SAMPLERATE_8K:
		sample_rate=8000;
		break;
        case IIS_SAMPLERATE_16K:
		sample_rate=16000;
		break;
        case IIS_SAMPLERATE_24K:
		sample_rate=24000;
		break;
        case IIS_SAMPLERATE_32K:
        sample_rate=32000;
        break;
        case IIS_SAMPLERATE_441K:
        sample_rate=44100;
        break;
        case IIS_SAMPLERATE_48K:
        sample_rate=48000;
        break;
        case IIS_SAMPLERATE_96K:
        sample_rate=96000;
        break;
        case IIS_SAMPLERATE_192K:
        sample_rate = 192000;
        break;
        default:
        return -1;
        break;

    }
	
//    uint32_t div0_coefficient = 0;
     uint32_t div0 = 0;
	
    if (iis_config->eMclkFreq != I2S_MCLK_256FS && iis_config->eMclkFreq != I2S_MCLK_384FS) {
        return -1;
    }
	
	uint32_t mclkfreq;
	switch (iis_config->eMclkFreq) 
	{
		case I2S_MCLK_256FS:
		mclkfreq=256 * sample_rate;
		break;
        case I2S_MCLK_384FS:
		mclkfreq=384 * sample_rate;
		break;
        default:
        return -1;
        break;
	}

	div0 = I2S_SRC_CLK_FREQ/mclkfreq;  //div0 = scr_clk /mclkfreq
//    div0_coefficient = I2S_SRC_CLK_FREQ / mclkfreq;      //   怎么获取i2s的src_clk呢？  
//    div0 = (div0_coefficient + div0_coefficient % sample_rate) / sample_rate;    // div0=1

    if (div0 > 255) {
        return -1;
    }
	 

    csp_i2s_set_div_sclk(ptI2sBase, div0);   //DIV0: 0x0 or 0x1不分频
    csp_i2s_set_div_ref_clk(ptI2sBase, 0);

//    csp_i2s_set_div_sclk(ptI2sBase, 6);   //DIV0: 0x0 or 0x1不分频
//    csp_i2s_set_div_ref_clk(ptI2sBase, 2);
	
    return 0;
}


/** \brief config iis datawidth
 * 
 *  \param[in] ptI2sBase: pointer of iis register structure
 *  \param[in] sample_width: iis datawidth
 *  \return  
 */ 
static int32_t csi_i2s_data_width_config(csp_i2s_t *ptI2sBase, csi_iis_datawidth_e sample_width)
{
    uint8_t bit_mode = 0;


    if (sample_width == IIS_DATAWIDTH_16BIT) {
        bit_mode = I2S_DATAWTH_BUS16_FIFO16;
    } else if (sample_width == IIS_DATAWIDTH_24BIT) {
        bit_mode = I2S_DATAWTH_BUS24_FIFO24;
    } else if (sample_width == IIS_DATAWIDTH_32BIT) {
        bit_mode = I2S_DATAWTH_BUS32_FIFO32;
    } else if (sample_width == IIS_DATAWIDTH_8BIT) {
        bit_mode = I2S_DATAWTH_BUS8_FIFO8;
    }
	else {
        return -1;
    }
	csp_i2s_set_data_width_mode(ptI2sBase, bit_mode);
    return 0;
}

/** \brief get iis idx 
 * 
 *  \param[in] ptI2sBase: pointer of iis register structure
 *  \return iis id number(0~1) or error(0xff)
 */ 
static uint8_t apt_get_iis_idx(csp_i2s_t *ptI2sBase)
{
	switch((uint32_t)ptI2sBase)
	{
		case APB_I2S0_BASE :
			return 0;
		case APB_I2S1_BASE :
			return 1;
		default:
			return 0xff;		//error
	}
}


csi_error_t csi_iis_init(csp_i2s_t *ptI2sBase,csi_iis_config_t *iis_config)
{

	if((ptI2sBase == NULL)||(iis_config == NULL))
		{
			return CSI_ERROR;
		}
	
	csp_i2s_disbale(ptI2sBase);   //ptI2sBase->IISEN=0
	
	//I2S  mode setting
	if (iis_config->eMode == IIS_TX )
	{
		csp_i2s_set_transmit_mode(ptI2sBase);   //mode : tx 

		if(iis_config->eWorkMode == IIS_MASTER)
		{
			csp_i2s_set_transmit_mode_master(ptI2sBase); //workmode :  master
			config_iis_div(ptI2sBase,iis_config);   // DIV0,DIV3: MASTER模式时，更具采样频率配置DIV0,DIV3
		}
		else {
			csp_i2s_set_transmit_mode_slave(ptI2sBase); //workmode :  slave
//			csp_i2s_set_receive_mode_audio_input_rate_detected(ptI2sBase, I2S_AIRAD_EN);   //rx rate auto detect
		}
		
		csp_i2s_set_transmit_data_format(ptI2sBase, iis_config->eDataAlign);  //data format
		
		//DMATDLR：TX FIFO DMA 阈值设置,当TX FIFO 中数据量小于或等于该值，产生DMA发送请求 dma_tx_req 
		csp_i2s_set_transmit_dma_data_num_level(ptI2sBase, 16);   // 8：参照wn 8032 drv得来
		// DMACR: Transmit DMA enabled， tx dma 使能
		csp_i2s_set_transmit_dma(ptI2sBase, I2S_TDMA_EN);
	}
	else {//IIS_RX
		
	csp_i2s_set_receive_mode(ptI2sBase);  //mode : rx 	
		
				// DIV0,DIV3: MASTER模式时，更具采样频率配置DIV0,DIV3
	if(iis_config->eWorkMode == IIS_MASTER)
	{
		config_iis_div(ptI2sBase,iis_config);   
		csp_i2s_set_receive_mode_master(ptI2sBase); //workmode :master
	}
	else {
		csp_i2s_set_receive_mode_slave(ptI2sBase); //workmode :slave
//		csp_i2s_set_receive_mode_audio_input_rate_detected(ptI2sBase, I2S_AIRAD_EN);   //rx rate auto detect
	}
		
	csp_i2s_set_receive_data_format(ptI2sBase, iis_config->eDataAlign); //data format
	
		
		//DMARDLR: 当RX FIFO 中数据量大于或等于该值，产生DMA接收请求 dma_rx_req 
	csp_i2s_set_receive_dma_data_num_level(ptI2sBase, 24);  // 24：参照wn 8032 drv得来
		// DMACR: Receive DMA enabled， rx dma 使能
	csp_i2s_set_receive_dma(ptI2sBase, I2S_RDMA_EN);
		
	}
	
	csp_i2s_set_receive_mode_mclk_sel_multiple_fs(ptI2sBase,iis_config->eMclkFreq); //FSSTA:MCLK_SEL
	csp_i2s_set_receive_mode_sclk_sel_multiple_fs(ptI2sBase,iis_config->eSclkFreq); //FSSTA:SCLK_SEL
	csi_i2s_data_width_config(ptI2sBase, iis_config->eDataWidth); //FSSTA:DATAWTH
	
	csp_i2s_enable(ptI2sBase);	

	// 中断配置
	csp_i2s_set_irq(ptI2sBase, iis_config->eInt); 
	
		
	return CSI_OK;
	
}


/** \brief iis dma send mode init
 * 
 *  \param[in] ptI2sBase: pointer of iis register structure
 *  \param[in] ptDmaBase: pointer of dma register structure
 *  \param[in] eDmaCh: channel number of dma, eDmaCh: DMA_CH0` DMA_CH3
 *  \param[in] eEtbCh: channel id number of etb, eEtbCh >= ETB_CH8
 *  \return  error code \ref csi_error_t
 */
csi_error_t csi_iis_dma_tx_init(csp_i2s_t *ptI2sBase, csi_dma_ch_e eDmaCh, csi_etb_ch_e eEtbCh)
{
	csi_error_t ret = CSI_OK;
	csi_dma_ch_config_t tDmaConfig;				
	csi_etb_config_t 	tEtbConfig;	
	uint8_t byIisIdx = apt_get_iis_idx(ptI2sBase);				

	//dma config
	tDmaConfig.bySrcLinc 	= DMA_ADDR_CONSTANT;		//低位传输原地址固定不变
	tDmaConfig.bySrcHinc 	= DMA_ADDR_INC;				//高位传输原地址自增
	tDmaConfig.byDetLinc 	= DMA_ADDR_CONSTANT;		//低位传输目标地址固定不变
	tDmaConfig.byDetHinc 	= DMA_ADDR_CONSTANT;		//高位传输目标地址固定不变
	tDmaConfig.byDataWidth 	= DMA_DSIZE_32_BITS;		//传输数据宽度32bit
	tDmaConfig.byReload 	= DMA_RELOAD_DISABLE;		//禁止自动重载
	tDmaConfig.byTransMode 	= DMA_TRANS_ONCE;			//DMA服务模式(传输模式)，连续服务
	tDmaConfig.byTsizeMode  = DMA_TSIZE_ONE_DSIZE;		//传输数据大小，一个 DSIZE , 即DSIZE定义大小
	tDmaConfig.byReqMode	= DMA_REQ_HARDWARE;			//DMA请求模式，硬件请求（硬件触发）
	tDmaConfig.wInt			= DMA_INTSRC_TCIT;			//使用TCIT中断
	
	
	//etb config
	tEtbConfig.byChType = ETB_ONE_TRG_ONE_DMA;					//单个源触发单个目标，DMA方式
//	tEtbConfig.bySrcIp 	= ETB_I2S0_TXSRC+ (byIisIdx << 1);	    //I2S TXSRC作为触发源
	tEtbConfig.bySrcIp 	= ETB_I2S0_TXSRC+ (byIisIdx << 1);	    //I2S TXSRC作为触发源
	tEtbConfig.byDstIp 	= ETB_DMA0_CH0 + eDmaCh;			    //ETB DMA通道 作为目标事件
	tEtbConfig.byTrgMode = ETB_HARDWARE_TRG;					//通道触发模式采样硬件触发
	
	ret = csi_etb_ch_config(eEtbCh, &tEtbConfig);				//初始化ETB，DMA ETB CHANNEL > ETB_CH9_ID
	if(ret < CSI_OK)
		return CSI_ERROR;
	ret = csi_dma_ch_init(DMA0, eDmaCh, &tDmaConfig);			//初始化DMA
	
	return ret;
}



/** \brief send data from iis, this function is dma mode
 * 
 *  \param[in] ptI2sBase: pointer of iis register structure
 *  \param[in] ptDmaBase: pointer of dma register structure
 *  \param[in] eDmaCh: channel number of dma, eDmaCh: DMA_CH0` DMA_CH3
 *  \param[in] pData: pointer to buffer with data to send to iis transmitter.
 *  \param[in] hwSize: number of data to send (byte); hwSize <= 0xfff
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_iis_send_dma(csp_i2s_t *ptI2sBase, csi_dma_ch_e eDmaCh, const void *pData, uint16_t hwSize)
{
	if(hwSize > 0xfff)
		return CSI_ERROR;

	csi_dma_ch_start(DMA0, eDmaCh, (void *)pData, (void *)&(ptI2sBase->DR), hwSize);
	
	return CSI_OK;
}



/** \brief iis dma receive mode init
 * 
 *  \param[in] ptI2sBase: pointer of iis register structure
 *  \param[in] eDmaCh: channel number of dma, eDmaCh: DMA_CH0` DMA_CH3
 *  \param[in] eEtbCh: channel id number of etb, eEtbCh >= ETB_CH20
 *  \return  error code \ref csi_error_t
 */
csi_error_t csi_iis_dma_rx_init(csp_i2s_t *ptI2sBase, csi_dma_ch_e eDmaCh, csi_etb_ch_e eEtbCh)
{
	csi_error_t ret = CSI_OK;
	csi_dma_ch_config_t tDmaConfig;				
	csi_etb_config_t 	tEtbConfig;				
	uint8_t byIisIdx = apt_get_iis_idx(ptI2sBase);		
	
	//dma config
	tDmaConfig.bySrcLinc 	= DMA_ADDR_CONSTANT;		//低位传输原地址固定不变
	tDmaConfig.bySrcHinc 	= DMA_ADDR_CONSTANT;		//高位传输原地址固定不变
	tDmaConfig.byDetLinc 	= DMA_ADDR_CONSTANT;		//低位传输目标地址固定不变
	tDmaConfig.byDetHinc 	= DMA_ADDR_INC;				//高位传输目标地址自增
	tDmaConfig.byDataWidth 	= DMA_DSIZE_32_BITS;			//传输数据宽度8bit
	tDmaConfig.byReload 	= DMA_RELOAD_DISABLE;		//禁止自动重载
	tDmaConfig.byTransMode 	= DMA_TRANS_ONCE;			//DMA服务模式(传输模式)，连续服务
	tDmaConfig.byTsizeMode  = DMA_TSIZE_ONE_DSIZE;		//传输数据大小，一个 DSIZE , 即DSIZE定义大小
	tDmaConfig.byReqMode	= DMA_REQ_HARDWARE;			//DMA请求模式，硬件请求
	tDmaConfig.wInt		=	 DMA_INTSRC_TCIT;			//使用TCIT中断
	
	//etb config
	tEtbConfig.byChType = ETB_ONE_TRG_ONE_DMA;					//单个源触发单个目标，DMA方式
//	tEtbConfig.bySrcIp 	= ETB_I2S0_RXSRC+ (byIisIdx << 1);	//UART TXSRC作为触发源
	tEtbConfig.bySrcIp 	= ETB_I2S0_RXSRC+ (byIisIdx << 1);
	tEtbConfig.byDstIp 	= ETB_DMA0_CH0 + eDmaCh;					//ETB DMA通道 作为目标实际
	tEtbConfig.byTrgMode = ETB_HARDWARE_TRG;					//通道触发模式采样硬件触发
	
	ret = csi_etb_ch_config(eEtbCh, &tEtbConfig);				//初始化ETB，DMA ETB CHANNEL > ETB_CH19_ID
	if(ret < CSI_OK)
		return CSI_ERROR;
	ret = csi_dma_ch_init(DMA0, eDmaCh, &tDmaConfig);			//初始化DMA
	
	return ret;
}




/** \brief receive data from iis, this function is dma mode
 * 
 *  \param[in] ptI2sBase: pointer of iis register structure
 *  \param[in] ptDmaBase: pointer of dma register structure
 *  \param[in] eDmaCh: channel number of dma, eDmaCh: DMA_CH0` DMA_CH3
 *  \param[in] pData: pointer to buffer with data to receive to iis transmitter.
 *  \param[in] hwSize: number of data to receive (byte), hwSize <= 0xfff
 *  \return  error code \ref csi_error_t
 */
csi_error_t csi_iis_recv_dma(csp_i2s_t *ptI2sBase, csi_dma_ch_e eDmaCh, void *pData, uint16_t hwSize)
{
	if(hwSize > 0xfff)
		return CSI_ERROR;

//	csp_i2s_set_receive_dma(ptI2sBase, I2S_RDMA_EN);   // enable RX DMA
//	csp_i2s_set_receive_dma_data_num_level(ptI2sBase,0);  // DMARDLR: default configure 0(0x00)
	csi_dma_ch_start(DMA0, eDmaCh, (void *)&(ptI2sBase->DR), (void *)pData, hwSize);
	

	return CSI_OK;
}



static uint32_t cnt =0;
static uint32_t txcnt =0;

/** \brief iis interrupt handle 
 * 
 *  \param[in] ptI2sBase: pointer of iis register structure
 *  \return none
 */
void iis_irqhandler(csp_i2s_t *ptI2sBase)
{
	uint32_t IISRxBuffer[512];
	uint32_t wIsq = csp_i2s_get_i2s_irq_status(ptI2sBase) & 0x3ff;
	
	if(  (wIsq & IIS_INTSRC_RXFIM )== IIS_INTSRC_RXFIM)
	{
		if(cnt <512)
		{
			IISRxBuffer[cnt++] = ptI2sBase->DR;
			IISRxBuffer[cnt++] = ptI2sBase->DR;
			IISRxBuffer[cnt++] = ptI2sBase->DR;
			IISRxBuffer[cnt++] = ptI2sBase->DR;
			IISRxBuffer[cnt++] = ptI2sBase->DR;
			IISRxBuffer[cnt++] = ptI2sBase->DR;
			IISRxBuffer[cnt++] = ptI2sBase->DR;
			IISRxBuffer[cnt++] = ptI2sBase->DR;
			IISRxBuffer[cnt++] = ptI2sBase->DR;
			IISRxBuffer[cnt++] = ptI2sBase->DR;
			IISRxBuffer[cnt++] = ptI2sBase->DR;
			IISRxBuffer[cnt++] = ptI2sBase->DR;
			IISRxBuffer[cnt++] = ptI2sBase->DR;
			IISRxBuffer[cnt++] = ptI2sBase->DR;
			IISRxBuffer[cnt++] = ptI2sBase->DR;
			IISRxBuffer[cnt++] = ptI2sBase->DR;
		}
	}
	if(  (wIsq & IIS_INTSRC_TXEIM )== IIS_INTSRC_TXEIM)
	{
	
		if(txcnt<512)
		{
			ptI2sBase->DR = txcnt++;
			ptI2sBase->DR = txcnt++;
			ptI2sBase->DR = txcnt++;
			ptI2sBase->DR = txcnt++;
			ptI2sBase->DR = txcnt++;
			ptI2sBase->DR = txcnt++;
			ptI2sBase->DR = txcnt++;
			ptI2sBase->DR = txcnt++;
			ptI2sBase->DR = txcnt++;
			ptI2sBase->DR = txcnt++;
			ptI2sBase->DR = txcnt++;
			ptI2sBase->DR = txcnt++;
			ptI2sBase->DR = txcnt++;
			ptI2sBase->DR = txcnt++;
			ptI2sBase->DR = txcnt++;
			ptI2sBase->DR = txcnt++;
		
		}
		
	}
	
	csi_iis_clr_isr(ptI2sBase);
	if(cnt == 512)
	{
//		CODEC->CLKCR = (0x0<<31  | 0x1<<0 | 0x1<<8); //接收完成关闭时钟，防止一直进中断
		csi_irq_disable((uint32_t *)ptI2sBase);
	}
	
}



/** \brief iis clear interrupt
 * 
 *  \param[in] ptI2sBase: pointer of iis register structure
 *  \return none
 */
void csi_iis_clr_isr(csp_i2s_t *ptI2sBase)
{
	csp_i2s_clear_irq(ptI2sBase, 0xffffffff);   //  clean all interrupt
}