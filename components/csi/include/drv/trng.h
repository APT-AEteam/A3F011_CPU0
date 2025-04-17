 /***********************************************************************
 * \file  trng.h
 * \brief  csi trng driver head file
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-6-8  <td>V0.1  <td>WNN   <td>modify
 * </table>
 * *********************************************************************
*/
#ifndef _DRV_TRNG_H_
#define _DRV_TRNG_H_

#include <stdint.h>
#include <stdbool.h>
#include "csp.h"


typedef enum{   
	TRNG_SEED_FIX	= (0),		// fix seed      
	TRNG_SEED_ANALOG= (1),		// analog seed
}csi_trng_seedtyp_e;


/// \struct csi_trng_config_t
/// \brief  trng parameter configuration, open to users  

typedef struct {
	csi_trng_seedtyp_e	eSeedType;		//trng seed typr
	uint8_t				bySeedComplex;	//trng seed complexity
	bool				bSeedReverse;	//trng seed cross reverse

} csi_trng_config_t;


/** \brief trng initialization 
 * 
 *  \param[in] ptTrngBase: pointer of trng register structure
 *  \param[in] csi_trng_config_t: trng configuration structure
 *  \return none
 */ 
void csi_trng_init(csp_trng_t *ptTrngBase,csi_trng_config_t tConfig);

/** \brief trng enable/start
 * 
 *  \param[in] ptTrngBase: pointer of trng register structure
 *  \return uint32_t random number
 */ 
uint32_t csi_trng_enable(csp_trng_t *ptTrngBase);

/** \brief trng disable/stop
 * 
 *  \param[in] ptTrngBase: pointer of trng register structure
 *  \return none
 */ 
void csi_trng_disable(csp_trng_t *ptTrngBase);




#endif