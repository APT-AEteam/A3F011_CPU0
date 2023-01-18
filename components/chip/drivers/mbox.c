/***********************************************************************//** 
 * \file  mailbox.c
 * \brief  csi mailbox driver
 * \copyright Copyright (C) 2022-2023 @ APTCHIP
 * <table>
 * <tr><th> Date     <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-12-19 <td>V0.0   <td>GQQ     <td>initial
 * </table>
 * *********************************************************************
*/


#include <drv/mbox.h>
#include <drv/irq.h>
#include <drv/tick.h>
#include <drv/pin.h>

/* Private macro------------------------------------------------------*/
/* externs function---------------------------------------------------*/
/* externs variablesr-------------------------------------------------*/
/* Private variablesr-------------------------------------------------*/


/** \brief mailbox interrupt handle function
 * 
 *  \param[in] ptMboxBase: pointer of mailbox register structure
 *  \return none
 */ 
__attribute__((weak)) void mbox_irqhandler(csp_mbox_t *ptMboxBase)
{
	
    // ISR content ...
	
	uint32_t gen_temp = 0;
	uint32_t info[8][2]={};
	
	if(csp_mbox_get_isr(ptMboxBase))
	{
		gen_temp = csp_mbox_get_gen(ptMboxBase);
		for(int cnt =0; cnt < 8; cnt++)
		{
			if(gen_temp &(0x01<<cnt))
			{
				info[cnt][0] = 1;    								//mark 1 when the info register is writen 
				info[cnt][1] = csp_mbox_get_info(ptMboxBase,cnt); 	//read corresponding info register
			}
		}
		
		csp_mbox_clr_isr(ptMboxBase);
		
	}

}

/** \brief enable mailbox interrupt
 * 
 *  \param[in] ptMboxBase: pointer of bt register structure
 *  \param[in] bEnable: enable/disable interrupt
 *  \return none
 */ 
void csi_mbox_int_enable(csp_mbox_t *ptMboxBase, bool bEnable)
{
	csp_mbox_int_enable(ptMboxBase, bEnable);	
	
	if (bEnable) {
		csi_irq_enable((uint32_t *)ptMboxBase);
	}
	else {
		csi_irq_disable((uint32_t *)ptMboxBase);
	}
		
}

/** \brief set to generate mailbox interrupt
 * 
 *  \param[in] ptMboxBase: pointer of bt register structure
 *  \param[in] eGen: the info that generate interrupt
 *  \return none
 */ 
void csi_mbox_set_generate(csp_mbox_t *ptMboxBase, mbox_gen_e eGen)
{
	csp_mbox_set_gen(ptMboxBase, eGen);	
		
}

/** \brief write CPUx_INFOx register, and generate INT0/INT1 interrupt
 *  \param[in] ptMboxChBase : pointer of csp_mbox_t
 *  \param[in] ch: channel of mailbox interrupt
 *  \param[in] wInfoSn: CPU_INFOx serial num.  
 * 	\param[in] wData: data to write
 *  \return error code \ref csi_error_t
 */
csi_error_t mbox_generate_intx(csp_mbox_t *ptMboxBase,csi_mbox_int_ch_e ch,csi_mbox_info_sn_e wInfoSn, uint32_t wData)
{
	csi_error_t ret = CSI_OK;
	csp_mbox_t *ptMboxChBase;
	
	csi_irq_enable(ptMboxBase); //enable mbox0/mbox1 irq
	
	
	ptMboxChBase = (csp_mbox_t *)MBOX_REG_BASE(ptMboxBase, ch);
	
	
	if(csp_mbox_get_risr(ptMboxChBase))    //Get raw interrupt status
	{
		csp_mbox_clr_isr(ptMboxChBase);    //clear interrupt 
	}
	
	csp_mbox_set_info(ptMboxChBase,wInfoSn,wData);  //write CPUx_INFOx
	
	if(wData == csp_mbox_get_info(ptMboxChBase,wInfoSn)) //Read back
	{
		csp_mbox_int_enable(ptMboxChBase, ENABLE); //Enable corresponding INTx 
		csp_mbox_set_gen(ptMboxChBase, (0x01<<wInfoSn)); //Generate corresponding INTx 
		
	}
	else 
	{
		ret = CSI_ERROR;	//return error code
	}
	
	return ret;
	
}