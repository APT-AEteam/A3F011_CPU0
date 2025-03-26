/***********************************************************************//** 
 * \file  csp_trng.h
 * \brief  TRNG description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-5-20 <td>V0.0  <td>WNN   <td>initial
 * </table>
 * *********************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CSP_TRNG_H
#define _CSP_TRNG_H

/* Includes ------------------------------------------------------------------*/

#include <soc.h>

/// \struct csp_trng_t
/// \brief TRNG reg description
typedef struct
{
    __IOM	uint32_t 	CR;			//0x0000	Control Register 
    __IM  	uint32_t 	DR;        	//0x0004 	Data Register               
    __IOM  	uint32_t 	IMCR;      	//0x0008 	Interrupt Enable Register              
    __IM  	uint32_t  	RISR;       //0x000C 	Interrupt Status Register     
    __OM  	uint32_t  	ICR;     	//0x0010 	Interrupt Clear Register  
    __IOM  	uint32_t  	CMR;		//0x0014	Configuration Manangement Register
} csp_trng_t; 

/******************************************************************************
* CR : Control Register
******************************************************************************/											
#define TRNG_EN_POS		0x0
#define TRNG_EN			(0x1<<TRNG_EN_POS)

static inline void csp_trng_enable(csp_trng_t *ptTrngBase)
{
	ptTrngBase ->CR = TRNG_EN;
}
static inline void csp_trng_disable(csp_trng_t *ptTrngBase)
{
	ptTrngBase ->CR &= ~TRNG_EN;
}
/******************************************************************************
* DR : Data Register
******************************************************************************/	
static inline uint32_t csp_trng_get_data(csp_trng_t *ptTrngBase)
{
	return (ptTrngBase ->DR);
}
/******************************************************************************
* IMCR : Interrupt Enable Register 
******************************************************************************/	
#define TRNG_INT_EN		0x1
typedef enum{   
	TRNG_CEIE		= (0x01ul << 1),		// clock error interrupt enable        
	TRNG_SEIE     	= (0x01ul << 2),		// seed error interrupt enable
}trng_int_e;

static inline void csp_trng_int_enable(csp_trng_t *ptTrngBase, trng_int_e eInt)
{
	ptTrngBase->IMCR |= eInt | TRNG_INT_EN;						
}
static inline void csp_trng_int_disable(csp_trng_t *ptTrngBase, trng_int_e eInt)
{
	ptTrngBase->IMCR &= ~eInt;
}

/******************************************************************************
* RISR : Interrupt Status Register 
******************************************************************************/	
typedef enum{   
	TRNG_DRDY		= (0x01ul << 0),		// Data Ready status
	TRNG_CECS		= (0x01ul << 1),		// clock error status       
	TRNG_SECS     	= (0x01ul << 2),		// seed error status
	TRNG_CEIS		= (0x01ul << 1),		// clock error interrupt status       
	TRNG_SEIS     	= (0x01ul << 2),		// seed error interrupt status
}trng_isr_e;

static inline void csp_trng_waitfor_dataready(csp_trng_t *ptTrngBase)
{
	while((ptTrngBase->RISR & TRNG_DRDY) != 1);
}
/******************************************************************************
* ICR : Interrupt Clear Register 
******************************************************************************/	
typedef enum{   
	TRNG_CEIC		= (0x01ul << 0),		// clock error interrupt clear        
	TRNG_SEIC     	= (0x01ul << 1),		// seed error interrupt clear
}trng_icr_e;
/******************************************************************************
* CMR : Configuration Manangement Register 
******************************************************************************/	
#define TRNG_CMEN_POS	0
#define TRNG_CMEN_MSK	(0x1 << TRNG_CMEN_POS)

typedef enum{   
	TRNG_SEEDFIX	= (0),		// fix seed      
	TRNG_SEEDANALOG= ( 1),		// analog seed
}trng_seedtyp_e;

#define TRNG_NOSG_POS	1
#define TRNG_NOSG_MSK	(0x3f << TRNG_NOSG_POS)

#define TRNG_CREN_POS	7
#define TRNG_CREN_MSK	(0x1 << TRNG_CREN_POS)

static inline void csp_trng_set_seedtype(csp_trng_t *ptTrngBase, trng_seedtyp_e eTyp)
{
	ptTrngBase-> CMR = (ptTrngBase-> CMR & ~TRNG_CMEN_MSK) | (eTyp << TRNG_CMEN_POS);
}

static inline void csp_trng_set_seed(csp_trng_t *ptTrngBase, uint8_t byNum)
{
	ptTrngBase ->CMR = (ptTrngBase ->CMR & ~TRNG_NOSG_MSK) | (byNum << TRNG_NOSG_POS);
}

static inline void csp_trng_crossreverse_enable(csp_trng_t *ptTrngBase)
{
	ptTrngBase ->CMR |= TRNG_CREN_MSK;
}

static inline void csp_trng_crossreverse_disable(csp_trng_t *ptTrngBase)
{
	ptTrngBase ->CMR &= ~TRNG_CREN_MSK;
}



#endif