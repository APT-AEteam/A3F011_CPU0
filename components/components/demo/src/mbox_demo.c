/***********************************************************************//** 
 * \file  mbox_demo.c
 * \brief  MBOX_DEMO description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-12-23 <td>V0.0 <td>GQQ     <td>initial
 * </table>
 * *********************************************************************
*/
/* Includes ---------------------------------------------------------------*/
#include <string.h>
#include <drv/mbox.h>
//#include <drv/pin.h>
//#include <drv/etb.h>

#include "demo.h"
/* externs function--------------------------------------------------------*/
/* externs variablesr------------------------------------------------------*/
/* Private macro-----------------------------------------------------------*/
/* Private variablesr------------------------------------------------------*/

/** \brief write CPU0_INFO0 register, and generate INT0 interrupt to notify CPU1
 *  往CPU1_INFO0寄存器写数据，并产生INT1中断告知CPU0
 *  \param[in] none
 *  \return error code
 */
int mbox_generate_int1_demo(void)
{
	int iRet = 0;
	uint32_t info0_temp = 0x55;
	csp_mbox_t *ptMboxChBase = (csp_mbox_t *)MBOX_REG_BASE(MBOX0, MBOX_INT0);
	
	iRet = mbox_generate_intx(ptMboxChBase, MBOX_INFO0_SN, info0_temp);
	

	return iRet;
}

