/*
 * Copyright (C) 2017-2020 Alibaba Group Holding Limited
 */

/******************************************************************************
 * @file     timer.h
 * @brief    header file for timer driver
 * @version  V1.0
 * @date     27. Apr 2020
 * @model    timer
 ******************************************************************************/

#ifndef _DRV_MBOX_H_
#define _DRV_MBOX_H_

#include <drv/common.h>

#include "csp.h"

#ifdef __cplusplus
extern "C" {
#endif



/**
 * \enum     csi_mbox_int_ch_e
 * \brief    Each mailbox has two interrupt,INT0& INT1
 */
typedef enum
{
	MBOX_INT0    =	0,	//mailbox_int0
	MBOX_INT1  , 		//mailbox_int1
	
}csi_mbox_int_ch_e;

/**
 * \enum     csi_mbox_info_sn_e
 * \brief    each CPU has 8 CPU_INFO registers
 */
typedef enum
{
	MBOX_INFO0_SN    =	0,	//mailbox_info0 serial num
	MBOX_INFO1_SN  , 		//mailbox_info1 serial num
	MBOX_INFO2_SN  ,		//mailbox_info2 serial num
	MBOX_INFO3_SN  ,		//mailbox_info3 serial num
	MBOX_INFO4_SN  ,		//mailbox_info4 serial num
	MBOX_INFO5_SN  ,		//mailbox_info5 serial num
	MBOX_INFO6_SN  ,		//mailbox_info6 serial num
	MBOX_INFO7_SN  ,		//mailbox_info7 serial num
	
}csi_mbox_info_sn_e;


/** \brief enable mailbox interrupt
 * 
 *  \param[in] ptMboxBase: pointer of bt register structure
 *  \param[in] bEnable: enable/disable interrupt
 *  \return none
 */ 
void csi_mbox_int_enable(csp_mbox_t *ptMboxBase, bool bEnable);


/** \brief set to generate mailbox interrupt
 * 
 *  \param[in] ptMboxBase: pointer of bt register structure
 *  \param[in] eGen: the info that generate interrupt
 *  \return none
 */ 
void csi_mbox_set_generate(csp_mbox_t *ptMboxBase, mbox_gen_e eGen);

/** \brief write CPUx_INFOx register, and generate INT0/INT1 interrupt
 *  \param[in] ptMboxChBase : pointer of csp_mbox_t
 *  \param[in] wInfoSn: CPU_INFOx serial num.  
 * 	\param[in] wData: data to write
 *  \return error code \ref csi_error_t
 */
csi_error_t mbox_generate_intx(csp_mbox_t *ptMboxChBase,csi_mbox_info_sn_e wInfoSn, uint32_t wData);


#ifdef __cplusplus
}
#endif

#endif /* _DRV_TIMER_H_ */
