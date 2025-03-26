/***********************************************************************//** 
 * \file  trng.c
 * \brief  csi trng driver
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author	<th>Description
 * <tr><td> 2024-6-12 <td>V0.0 <td>WNN  	<td>initial
 * </table>
 * *********************************************************************
*/


#include "trng.h"

/** \brief trng initialization 
 * 
 *  \param[in] ptTrngBase: pointer of trng register structure
 *  \param[in] csi_trng_config_t: trng configuration structure
 *  \return none
 */ 
void csi_trng_init(csp_trng_t *ptTrngBase,csi_trng_config_t tConfig)
{
	csp_trng_set_seedtype(ptTrngBase, (trng_seedtyp_e) tConfig.eSeedType);
	csp_trng_set_seed(ptTrngBase, tConfig.bySeedComplex);
	if (tConfig.bSeedReverse)
		csp_trng_crossreverse_enable(ptTrngBase);
	else
		csp_trng_crossreverse_disable(ptTrngBase);
}


/** \brief trng enable/start
 * 
 *  \param[in] ptTrngBase: pointer of trng register structure
 *  \return uint32_t random number
 */ 
uint32_t csi_trng_enable(csp_trng_t *ptTrngBase)
{
	csp_trng_enable(ptTrngBase);
	csp_trng_waitfor_dataready(ptTrngBase);
	return (csp_trng_get_data(ptTrngBase));
}


/** \brief trng disable/stop
 * 
 *  \param[in] ptTrngBase: pointer of trng register structure
 *  \return none
 */ 
void csi_trng_disable(csp_trng_t *ptTrngBase)
{
	csp_trng_disable(ptTrngBase);
}


/** \brief trng get random number
 * 
 *  \param[in] ptTrngBase: pointer of trng register structure
 *  \return uint32_t random number
 */ 
uint32_t csi_trng_get_random_num(csp_trng_t *ptTrngBase)
{
	csp_trng_get_data(ptTrngBase);
}



