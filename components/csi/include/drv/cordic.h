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
#ifndef _DRV_CORDIC_H_
#define _DRV_CORDIC_H_

#include <stdint.h>
#include <stdbool.h>
#include <drv/common.h>
#include <drv/dma.h>
#include "csp.h"

/**
  * @brief  CORDIC csi State Structure definition
  */
typedef enum
{
  CORDIC_STATE_RESET     = 0x00U,  /*!< CORDIC not yet initialized or disabled */
  CORDIC_STATE_READY     = 0x01U,  /*!< CORDIC initialized and ready for use   */
  CORDIC_STATE_BUSY      = 0x02U,  /*!< CORDIC internal process is ongoing     */
  CORDIC_STATE_ERROR     = 0x03U   /*!< CORDIC error state                     */
} csi_cordic_state_type;   // CORDIC_StateTypeDef;



/**
  * @brief  CORDIC Handle Structure definition
  */
typedef struct
{
  csp_cordic_t                *Instance;   /*!< Register base address */

  int32_t                       *pInBuff;    /*!< Pointer to CORDIC input data buffer */

  int32_t                       *pOutBuff;   /*!< Pointer to CORDIC output data buffer */

  uint32_t                      NbCalcToOrder; /*!< Remaining number of calculation to order */

  uint32_t                      NbCalcToGet; /*!< Remaining number of calculation result to get */

  //uint32_t                      DMADirection; /*!< Direction of CORDIC DMA transfers */

  //DMA_HandleTypeDef             *hdmaIn;     /*!< CORDIC peripheral input data DMA handle parameters */

  //DMA_HandleTypeDef             *hdmaOut;    /*!< CORDIC peripheral output data DMA handle parameters */

  csi_cordic_state_type  State;       /*!< CORDIC state */

   
    
} csi_cordic_handle_type;  //CORDIC_HandleTypeDef;



/**
  * @brief  CORDIC Config Structure definition
  */
typedef struct 
{
    uint8_t byFunction;    //CORDIC Function
    uint8_t byPrecision;   //CORDIC Precision
	uint8_t byScale;       //CORDIC Scale
	uint8_t byInSize;      //Width of Input Data
	uint8_t byOutSize;     //Width of Output Data
	uint16_t	hwInt;     //CORDIC INTERRPUT SET
} csi_cordic_config_t;




typedef enum
{
	CORDIC_INTSRC_NONE           = (0x00ul << 0),
	CORDIC_INTSRC_RRDY           = (0x01ul << 0)    // CORDIC Interrupt Status
} csi_cordic_intsrc_e;

/*
 ==============================================================================
              ##### Initialization and de-initialization functions #####
==============================================================================
 * /

 * \brief Initialize the CORDIC periphera
 * 
 *  \param[in] ptCordicBase: pointer of cordic register structure
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_cordic_init(csp_cordic_t *ptCordicBase);


/*
  ==============================================================================
                      ##### Peripheral Control functions #####
  ==============================================================================
*/
/** \brief Configure the CORDIC processing according to the specified
            parameters in the csi_cordic_config_t structure.
 *  \param[in] ptCordicBase: pointer of cordic register structure
 *  \param[in] ptCordicCfg: pointer of cordic config structure
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_cordic_configure(csp_cordic_t *ptCordicBase, csi_cordic_config_t *ptCordicCfg);


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

csi_error_t csi_cordic_calculate(csp_cordic_t *ptCordicBase, int32_t *pInBuff1, int32_t *pInBuff2,int32_t *pOutBuff,uint32_t wNbCalc);



/** \brief CORDIC interrupt handle 
 * 
 *  \param[in] ptCordicBase: pointer of cordic register structure
 *  \return none
 */
__attribute__((weak)) void cordic_irqhandler(csp_cordic_t *ptCordicBase);


/** \brief  CORDIC read data from CORDICOUTDATA register (to be called in CORDIC IRQhandler)
 * 
 *  \param[in] ptCordicBase: pointer of cordic register structure
 *  \return none
 */ 
void csi_cordic_read_data(csp_cordic_t *ptCordicBase);



/** \brief  CORDIC calculation dma mode
 * 
 *  \param[in] ptCordicBase: pointer of cordic register structure
 *  \param[in] pInBuff:  pointer of output data
 *  \param[in] pOutBuff: pointer of output data
 *  \param[in] wNbCalc: pointer of cordic register structure
 *  \return none
 */
csi_error_t csi_cordic_calculate_dma(csp_cordic_t *ptCordicBase, int32_t *pInBuff, int32_t *pOutBuff,uint32_t wNbCalc);




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

csi_error_t csi_cordic_calculate_int(csp_cordic_t *ptCordicBase, int32_t *pInBuff1, int32_t *pInBuff2,int32_t *pOutBuff,uint32_t wNbCalc);

/** \brief cordic dma receive mode init
 * 
 *  \param[in] eDmaCh: channel number of dma, eDmaCh: DMA_CH0` DMA_CH3
 *  \param[in] eEtbCh: channel id number of etb, eEtbCh >= ETB_CH8
 *  \return  error code \ref csi_error_t
 */
csi_error_t csi_uart_dma_rx_init(csi_dma_ch_e eDmaCh, csi_etb_ch_e eEtbCh);

/** \brief cordic dma send mode init
 * 
 *  \param[in] eDmaCh: channel number of dma, eDmaCh: DMA_CH0` DMA_CH3
 *  \param[in] eEtbCh: channel id number of etb, eEtbCh >= ETB_CH8
 *  \return  error code \ref csi_error_t
 */
csi_error_t csi_cordic_dma_tx_init(csi_dma_ch_e eDmaCh, csi_etb_ch_e eEtbCh);

/** \brief cordic dma receive mode init
 * 
 *  \param[in] eDmaCh: channel number of dma, eDmaCh: DMA_CH0` DMA_CH3
 *  \param[in] eEtbCh: channel id number of etb, eEtbCh >= ETB_CH8
 *  \return  error code \ref csi_error_t
 */
csi_error_t csi_cordic_dma_rx_init(csi_dma_ch_e eDmaCh, csi_etb_ch_e eEtbCh);

/** \brief send data from cordic, this function is dma mode
 * 
 *  \param[in] ptCordicBase: pointer of CORDIC register structure
 *  \param[in] eDmaCh: channel number of dma, eDmaCh: DMA_CH0` DMA_CH3
 *  \param[in] pData1: pointer to buffer with data to send to CORDIC transmitter.
 *  \param[in] pData2: pointer to buffer with data to send to CORDIC transmitter.
 *  \param[in] hwSize: number of data to send (byte).
 *  \return  none
 */
void csi_cordic_send_dma(csp_cordic_t *ptCordicBase, csi_dma_ch_e eDmaCh, const void *pData1, uint16_t hwSize);


/** \brief receive data from cordic, this function is dma mode
 * 
 *  \param[in] ptCordicBase: pointer of CORDIC register structure
 *  \param[in] eDmaCh: channel number of dma, eDmaCh: DMA_CH0` DMA_CH3
 *  \param[in] pData: pointer to buffer with data to receive to uart transmitter.
 *  \param[in] hwSize: number of data to receive (byte).
 *  \return  none
 */
void csi_cordic_recv_dma(csp_cordic_t *ptCordicBase, csi_dma_ch_e eDmaCh, void *pData, uint16_t hwSize);


#endif /* _DRV_CORDIC_H_ */