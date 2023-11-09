/***********************************************************************//** 
 * \file  cordic_demo.c
 * \brief  IIS_DEMO description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-12-16 <td>V0.0 <td>YT     <td>initial
 * </table>
 * *********************************************************************
*/
#include <sys_clk.h>
#include <drv/cordic.h>
#include <drv/irq.h>
#include <drv/gpio.h>
#include <drv/pin.h>
#include <drv/porting.h>
#include <drv/tick.h>



extern int32_t pInBuff1[];
extern int32_t pInBuff2[];
extern int32_t pOutBuff[];
extern uint32_t wNbCalc;

//void delay_ums(uint32_t t)
//{
//        volatile uint32_t i,j ,k=0;
//        j = 25* t;
//        for ( i = 0; i < j; i++ )
//        {
//                k++;
//        }
//}

  
/** \brief CORDIC start calculate
 *
 *  \param[in] ptCordicBase: pointer of cordic register structure
 *  \return none
 */
static int32_t apt_cordic_start_calculate(csp_cordic_t *ptCordicBase)
 {
	 csp_cordic_set_start(ptCordicBase, CORDIC_START_EN);
	 return 0;
 }



/** \brief Write input data for CORDIC processing
 *
 *  \param[in] ptCordicBase: pointer of cordic register structure
 *  \param[in] wInData1：Inputdata1
 *  \param[in] wInData2: Inputdata1
 *  \return none
 */
  
static void apt_cordic_write_data(csp_cordic_t *ptCordicBase, uint32_t wInData1, uint32_t wInData2)
{
  csp_cordic_set_input_data_1(ptCordicBase, wInData1);
  csp_cordic_set_input_data_2(ptCordicBase, wInData2);
}


/** \brief Read output data of CORDIC processing
 *
 *  \param[in] ptCordicBase: pointer of cordic register structure
 *  \return output data
 */
static void apt_cordic_read_data(csp_cordic_t *ptCordicBase, int32_t *pOutBuff)
{
  *pOutBuff = csp_cordic_get_output_data(ptCordicBase);
}




/** \brief Configure the CORDIC processing according to the specified
            parameters in the csi_cordic_config_t structure.
 *  \param[in] ptCordicBase: pointer of cordic register structure
 *  \param[in] ptCordicCfg: pointer of cordic config structure
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_cordic_configure(csp_cordic_t *ptCordicBase, csi_cordic_config_t *ptCordicCfg)
{
	if((ptCordicBase == NULL)||(ptCordicCfg == NULL))
		{
			return CSI_ERROR;
		}
	
	csp_cordic_set_function(ptCordicBase, ptCordicCfg->byFunction);   // configure function
	csp_cordic_set_precision(ptCordicBase, ptCordicCfg->byPrecision); // configure precision
	csp_cordic_set_scale(ptCordicBase, ptCordicCfg->byScale);         // configure scale
	csp_cordic_set_output_data_size(ptCordicBase, ptCordicCfg->byOutSize);  // configure input data size
	csp_cordic_set_input_data_size(ptCordicBase, ptCordicCfg->byInSize);   // configure output data size
	
	csp_cordic_imcr_enable(CORDIC,ptCordicCfg->hwInt); //  interrupt enable
	
	
	return CSI_OK;
}




/**
  * @brief  Carry out data of CORDIC processing in polling mode,
  *         according to the existing CORDIC configuration.
  * \param[in] ptCordicBase: pointer of cordic register structure
  * @param  pInBuff1 Pointer to buffer containing input data 1 for CORDIC processing.
  * @param  pInBuff2 Pointer to buffer containing input data 2 for CORDIC processing.
  * @param  pOutBuff Pointer to buffer where output data of CORDIC processing will be stored.
  * @param  wNbCalc Number of CORDIC calculation to process.
  *  \return error code \ref csi_error_t
  */
csi_error_t csi_cordic_calculate(csp_cordic_t *ptCordicBase, int32_t *pInBuff1, int32_t *pInBuff2,int32_t *pOutBuff,uint32_t wNbCalc)
{
//	if((ptCordicBase == NULL)||(pInBuff1 == NULL)||(pInBuff2 == NULL)||(pOutBuff == NULL)||(wNbCalc == NULL))
//		{
//			return CSI_ERROR;
//		}
	
	for(uint32_t i=0;i<wNbCalc;i++ )
	{
		
		apt_cordic_write_data(ptCordicBase, pInBuff1[i], pInBuff2[i]);// Write of input data in Write Data register, and increment input buffer pointer 
		
		apt_cordic_start_calculate(ptCordicBase);  // START=1，开始计算
		
		apt_cordic_read_data(ptCordicBase, &pOutBuff[i]);         //  Read output data from Read Data register,
		
//		delay_ums(5000);
		mdelay(5);
	}	
	
	return CSI_OK;
}




// cordic calculation interrupt mode 

/**
  * @brief  cordic calculation interrupt mode
  *       
  * \param[in] ptCordicBase: pointer of cordic register structure
  * @param  pInBuff1: Pointer to buffer containing input data 1 for CORDIC processing.
  * @param  pInBuff2: Pointer to buffer containing input data 2 for CORDIC processing.
  * @param  pOutBuff: Pointer to buffer where output data of CORDIC processing will be stored.
  * @param  wNbCalc: Number of CORDIC calculation to process.
  *  \return error code \ref csi_error_t
  */

csi_error_t csi_cordic_calculate_int(csp_cordic_t *ptCordicBase, int32_t *pInBuff1, int32_t *pInBuff2,int32_t *pOutBuff,uint32_t wNbCalc)
{
//	if((ptCordicBase == NULL)||(pInBuff1 == NULL)||(pInBuff2 == NULL)||(pOutBuff == NULL)||(wNbCalc == NULL))
//		{
//			return CSI_ERROR;
//		}

	for(uint32_t i=0;i<wNbCalc;i++ )
	{
		apt_cordic_write_data(ptCordicBase, pInBuff1[i],pInBuff2[i]);// Write of input data in Write Data register, and increment input buffer pointer 
		apt_cordic_start_calculate(ptCordicBase);  // START=1，开始计算,然后进中断
	}	
	
	return CSI_OK;	
	
	
	
}


/** \brief CORDIC interrupt handle 
 * 
 *  \param[in] ptSioBase: pointer of CORDIC register structure
 *  \return none
 */
__attribute__((weak)) void cordic_irqhandler(csp_cordic_t *ptCordicBase)
{
	
	csi_cordic_read_data(ptCordicBase);
	
}


/** \brief  CORDIC read data from CORDICOUTDATA register (to be called in CORDIC IRQhandler)
 * 
 *  \param[in] ptCordicBase: pointer of cordic register structure
 *  \return none
 */ 
void csi_cordic_read_data(csp_cordic_t *ptCordicBase)
{
	apt_cordic_read_data(ptCordicBase, &pOutBuff);         //  Read output data from Read Data register,

	csp_cordic_clr_isr(ptCordicBase,CORDIC_INTSRC_RRDY); // clear interrupt
}




/** \brief  CORDIC calculation dma mode
 * 
 *  \param[in] ptCordicBase: pointer of cordic register structure
 *  \param[in] pInBuff:  pointer of output data
 *  \param[in] pOutBuff: pointer of output data
 *  \param[in] wNbCalc: pointer of cordic register structure
 *  \return none
 */
csi_error_t csi_cordic_calculate_dma(csp_cordic_t *ptCordicBase, int32_t *pInBuff,int32_t *pOutBuff,uint32_t wNbCalc)
{
//	if((ptCordicBase == NULL)||(pInBuff == NULL)||(pOutBuff == NULL)||(wNbCalc == NULL))
//		{
//			return CSI_ERROR;
//		}
	// step 1: 使能etb	
	csi_etb_init();								// 使能ETB模块
	
	csi_cordic_dma_tx_init(DMA_CH1, ETB_CH22);  // CORDIC DMA TX init
	csi_cordic_dma_rx_init(DMA_CH3, ETB_CH20);  // CORDIC DMA RX init
	
	// step 2: DMAIN(write)/DMAOUT(read). 
	csi_cordic_recv_dma(ptCordicBase,DMA_CH3, (void*)(pOutBuff-1),wNbCalc+1);   // 由于recv dma 会多读一个，所以，dst-1，hwSize+1
	csi_cordic_send_dma(ptCordicBase,DMA_CH1, (void *)(pInBuff),wNbCalc);

	// step 3: 往CORDICINDATA1/CORDICINDATA2写数据，此时不用DMA传输 
	apt_cordic_write_data(ptCordicBase, 0x05604189, 0x03604189);// Write of input data in Write Data register ，随便写一个输入值，开始计算
	
	// step 4: START=1，开始计算
	apt_cordic_start_calculate(ptCordicBase);  
	// step 5: 计算结束，RRDY=1，且RRDYTRGOUTE=1时，CORDIC输出事件触发请求，产生ETC_CORDIC_TRGOUT信号，触发DMAIN/DMAOUT目标事件
	return CSI_OK;	
}


/** \brief cordic dma send mode init
 * 
 *  \param[in] eDmaCh: channel number of dma, eDmaCh: DMA_CH0` DMA_CH3
 *  \param[in] eEtbCh: channel id number of etb, eEtbCh >= ETB_CH8
 *  \return  error code \ref csi_error_t
 */
csi_error_t csi_cordic_dma_tx_init(csi_dma_ch_e eDmaCh, csi_etb_ch_e eEtbCh)
{
	csi_error_t ret = CSI_OK;
	csi_dma_ch_config_t tDmaConfig;				
	csi_etb_config_t 	tEtbConfig;					

	//dma config
	tDmaConfig.bySrcLinc 	= DMA_ADDR_INC;		//低位传输原地址固定不变
	tDmaConfig.bySrcHinc 	= DMA_ADDR_INC;				//高位传输原地址自增
	tDmaConfig.byDetLinc 	= DMA_ADDR_CONSTANT;		//低位传输目标地址固定不变
	tDmaConfig.byDetHinc 	= DMA_ADDR_CONSTANT;		//高位传输目标地址固定不变
	tDmaConfig.byDataWidth 	= DMA_DSIZE_32_BITS;		//传输数据宽度32bit
	tDmaConfig.byReload 	= DMA_RELOAD_DISABLE;		//禁止自动重载
	tDmaConfig.byTransMode 	= DMA_TRANS_ONCE;			//DMA服务模式(传输模式)，单次服务
	tDmaConfig.byTsizeMode  = DMA_TSIZE_FOUR_DSIZE;		//传输数据大小，四个 DSIZE , 即DSIZE定义大小
	tDmaConfig.byReqMode	= DMA_REQ_HARDWARE;			//DMA请求模式，软件请求（软件触发）
	tDmaConfig.wInt			= DMA_INTSRC_TCIT;		    //使用TCIT中断
	
	//etb config
	tEtbConfig.byChType = ETB_ONE_TRG_ONE_DMA;					//单个源触发单个目标，DMA方式
	tEtbConfig.bySrcIp 	= ETB_CORDIC_TRGOUT;	//CORDIC_TRGOUT作为触发源
	tEtbConfig.bySrcIp1 = 0xff;						
	tEtbConfig.bySrcIp2 = 0xff;
	tEtbConfig.byDstIp 	= ETB_DMA0_CH0 + eDmaCh;					//ETB DMA通道 作为目标实际
	tEtbConfig.byDstIp1 = 0xff;
	tEtbConfig.byDstIp2 = 0xff;
	tEtbConfig.byTrgMode = ETB_HARDWARE_TRG;					//通道触发模式采样硬件触发
	
	ret = csi_etb_ch_config(eEtbCh, &tEtbConfig);				//初始化ETB，DMA ETB CHANNEL > ETB_CH19_ID
	if(ret < CSI_OK)
		return CSI_ERROR;
	ret = csi_dma_ch_init(DMA0, eDmaCh, &tDmaConfig);		//初始化DMA
	
	return ret;
}



/** \brief cordic dma receive mode init
 * 
 *  \param[in] eDmaCh: channel number of dma, eDmaCh: DMA_CH0` DMA_CH3
 *  \param[in] eEtbCh: channel id number of etb, eEtbCh >= ETB_CH8
 *  \return  error code \ref csi_error_t
 */
csi_error_t csi_cordic_dma_rx_init(csi_dma_ch_e eDmaCh, csi_etb_ch_e eEtbCh)
{
	csi_error_t ret = CSI_OK;
	csi_dma_ch_config_t tDmaConfig;				
	csi_etb_config_t 	tEtbConfig;				
	
	//dma config
	tDmaConfig.bySrcLinc 	= DMA_ADDR_CONSTANT;		//低位传输原地址固定不变
	tDmaConfig.bySrcHinc 	= DMA_ADDR_CONSTANT;		//高位传输原地址固定不变
	tDmaConfig.byDetLinc 	= DMA_ADDR_CONSTANT;		//低位传输目标地址固定不变
	tDmaConfig.byDetHinc 	= DMA_ADDR_INC;				//高位传输目标地址自增
	tDmaConfig.byDataWidth 	= DMA_DSIZE_32_BITS;			//传输数据宽度32bit
	tDmaConfig.byReload 	= DMA_RELOAD_DISABLE;		//禁止自动重载
	tDmaConfig.byTransMode 	= DMA_TRANS_ONCE;			//DMA服务模式(传输模式)，单次服务
	tDmaConfig.byTsizeMode  = DMA_TSIZE_ONE_DSIZE;		//传输数据大小，一个 DSIZE , 即DSIZE定义大小
	tDmaConfig.byReqMode	= DMA_REQ_HARDWARE;			//DMA请求模式，硬件请求
	tDmaConfig.wInt		=	 DMA_INTSRC_TCIT;			//使用TCIT中断
	
	//etb config
	tEtbConfig.byChType = ETB_ONE_TRG_ONE_DMA;					//单个源触发单个目标，DMA方式
	tEtbConfig.bySrcIp 	= ETB_CORDIC_TRGOUT;	//UART TXSRC作为触发源
	tEtbConfig.bySrcIp1 = 0xff;						
	tEtbConfig.bySrcIp2 = 0xff;
	tEtbConfig.byDstIp 	= ETB_DMA0_CH0 + eDmaCh;					//ETB DMA通道 作为目标事件
	tEtbConfig.byDstIp1 = 0xff;
	tEtbConfig.byDstIp2 = 0xff;
	tEtbConfig.byTrgMode = ETB_HARDWARE_TRG;					//通道触发模式采样硬件触发
	
	ret = csi_etb_ch_config(eEtbCh, &tEtbConfig);				//初始化ETB，DMA ETB CHANNEL > ETB_CH19_ID
	if(ret < CSI_OK)
		return CSI_ERROR;
	ret = csi_dma_ch_init(DMA0, eDmaCh, &tDmaConfig);			//初始化DMA
	
	return ret;
}


/** \brief send data from cordic, this function is dma mode
 * 
 *  \param[in] ptCordicBase: pointer of CORDIC register structure
 *  \param[in] eDmaCh: channel number of dma, eDmaCh: DMA_CH0` DMA_CH3
 *  \param[in] pData1: pointer to buffer with data to send to CORDIC transmitter.
 *  \param[in] pData2: pointer to buffer with data to send to CORDIC transmitter.
 *  \param[in] hwSize: number of data to send (byte).
 *  \return  none
 */
void csi_cordic_send_dma(csp_cordic_t *ptCordicBase, csi_dma_ch_e eDmaCh, const void *pData1,uint16_t hwSize)
{
	csi_dma_ch_start(DMA0, eDmaCh, (void *)pData1, (void *)&(ptCordicBase->CORDICINDATA1), hwSize);
	
}


/** \brief receive data from cordic, this function is dma mode
 * 
 *  \param[in] ptCordicBase: pointer of CORDIC register structure
 *  \param[in] eDmaCh: channel number of dma, eDmaCh: DMA_CH0` DMA_CH3
 *  \param[in] pData: pointer to buffer with data to receive to uart transmitter.
 *  \param[in] hwSize: number of data to receive (byte).
 *  \return  none
 */
void csi_cordic_recv_dma(csp_cordic_t *ptCordicBase, csi_dma_ch_e eDmaCh, void *pData, uint16_t hwSize)
{
	csi_dma_ch_start(DMA0, eDmaCh, (void *)&(ptCordicBase->CORDICOUTDATA), (void *)pData, hwSize);
}