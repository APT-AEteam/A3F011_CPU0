/***********************************************************************//** 
 * \file  csp_bt.h
 * \brief BT description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-9-01 <td>V0.0  <td>ZJY   <td>initial
 * <tr><td> 2021-1-01 <td>V0.1  <td>ZJY   <td> macro definition style
 * </table>
 * *********************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CSP_MBOX_H
#define _CSP_MBOX_H

/* Includes ------------------------------------------------------------------*/
#include <soc.h>
#include "csp_common.h"
/// \struct csp_mbox_t
/// \brief MBOX reg description      
 typedef struct
 {
   __IM  uint32_t	INT_STRx;  		//0x0000		Mailbox INT0/INT1 Status Register
   __OM  uint32_t	INT_CLRx;		//0x0004		Mailbox INT0/INT1 Clear Register
   __IM  uint32_t	INT_RAWx;		//0x0008		Mailbox INT0/INT1 Raw status Register
   __IOM uint32_t	INT_MASKx; 		//0x000C		Mailbox INT0/INT1 Enable Register
   __IOM uint32_t	INT_GENx;		//0x0010		Mailbox INT0/INT1 Generate Register
   __IOM uint32_t	CPUx_INFO[8];	//0x0014~0x30	CPU0 Information Register0~7
   __IM  uint32_t	RSVD[13];		//0x34~0x64
  // __IOM uint32_t	CPU1_INFO[8];	//0x0048~0x64	CPU1 Information Register0~7
   __IM  uint32_t   IPCORE;			//0x0068		IPCORE Version
   
   } csp_mbox_t; 

//MBOX reg base
#define	MBOX_REG_BASE(mbox, ch)	((uint32_t)mbox + ch * 0x34)	
/*****************************************************************************
************************ mailbox Function defined ****************************
******************************************************************************/


/******************************************************************************
* INT_STRx : Mailbox INT0/INT1 Status Register
******************************************************************************/
#define	MBOX_STR_POS		(0)
#define	MBOX_STR_MSK		(0x01ul << MBOX_STR_POS)

/******************************************************************************
* INT_CLRx : Mailbox INT0/INT1 Clear Register
******************************************************************************/
#define	MBOX_CLR_POS		(0)
#define	MBOX_CLR_MSK		(0x01ul << MBOX_CLR_POS)

/******************************************************************************
* INT_RAWx : Mailbox INT0/INT1 Raw status Register
******************************************************************************/
#define	MBOX_RAW_POS		(0)
#define	MBOX_RAW_MSK		(0x01ul << MBOX_RAW_POS)

/******************************************************************************
* INT_MASKx : Mailbox INT0/INT1 Enable Register
******************************************************************************/
#define	MBOX_MASK_POS		(0)
#define	MBOX_MASK_MSK		(0x01ul << MBOX_MASK_POS)

/******************************************************************************
* INT_GENx : Mailbox INT0/INT1 Generate Register
******************************************************************************/
#define	MBOX_GEN_POS		(0)
#define	MBOX_GEN_MSK		(0xFFul << MBOX_GEN_POS)

typedef enum
{
	MBOX_INFO0    =	(0x00ul << 0), 	//MBOX_INFO0
	MBOX_INFO1    =	(0x01ul << 1),	//MBOX_INFO1
	MBOX_INFO2    =	(0x01ul << 2),	//MBOX_INFO2   
	MBOX_INFO3    =	(0x01ul << 3), 	//MBOX_INFO3
	MBOX_INFO4	  =	(0x01ul << 4),	//MBOX_INFO4
	MBOX_INFO5	  = (0x01ul << 5),	//MBOX_INFO5
	MBOX_INFO6	  = (0x01ul << 6),	//MBOX_INFO6
	MBOX_INFO7	  = (0x01ul << 7)	//MBOX_INFO7
	
}mbox_gen_e;


/******************************************************************************
* CPUx_INFO0~7 : CPU0/CPU1 Information Register0~7
******************************************************************************/
#define	MBOX_INFO_POS	(0)
#define	MBOX_INFO_MSK	(0xFFFFul << MBOX_INFO_POS)

/******************************************************************************
* IPCORE : IPCORE Version
******************************************************************************/


/******************************************************************************
********************** Mbox inline Functions Declaration ************************
******************************************************************************/
static inline uint32_t csp_mbox_get_isr(csp_mbox_t *ptMboxBase)
{
	return (ptMboxBase->INT_STRx & MBOX_STR_MSK);
}
static inline void csp_mbox_clr_isr(csp_mbox_t *ptMboxBase)
{
	ptMboxBase->INT_CLRx = 0x1;
}
static inline uint32_t csp_mbox_get_risr(csp_mbox_t *ptMboxBase)
{
	return (ptMboxBase->INT_RAWx & MBOX_RAW_MSK);
}

static inline void csp_mbox_int_enable(csp_mbox_t *ptMboxBase, bool bEnable)
{
	ptMboxBase->INT_MASKx = bEnable;
}

static inline void csp_mbox_set_gen(csp_mbox_t *ptMboxBase, mbox_gen_e eGen)
{
	ptMboxBase->INT_GENx = eGen;
}

static inline uint32_t csp_mbox_get_gen(csp_mbox_t *ptMboxBase)
{
	return (ptMboxBase->INT_GENx & MBOX_GEN_MSK);
}

static inline void csp_mbox_set_info(csp_mbox_t *ptMboxBase, uint32_t byNum, uint32_t wInfo)
{
	ptMboxBase->CPUx_INFO[byNum] = wInfo;
}

static inline uint32_t csp_mbox_get_info(csp_mbox_t *ptMboxBase, uint32_t byNum)
{
	return ptMboxBase->CPUx_INFO[byNum];
}

static inline uint32_t csp_mbox_get_ipcore(csp_mbox_t *ptMboxBase)
{
	return ptMboxBase->IPCORE;
}

#endif
