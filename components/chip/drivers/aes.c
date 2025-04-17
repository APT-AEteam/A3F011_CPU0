/***********************************************************************//** 
 * \file  aes.c
 * \brief  csi aes driver
 * \copyright Copyright (C) 2015-2023 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2023-11-29 <td>V0.0  <td>WNN   <td>initial
 * </table>
 * *********************************************************************
*/
//#include <csi_config.h>

//#include "csp_common.h"
//#include "aes.h"
//
///** \brief initialize AES structure
// * 
// *  \param[in] ptAesBase: pointer of aes register structure
// *  \param[in] ptAesCfg: pointer of aes parameter config structure	
// *  \return none
// */ 
//void csi_aes_init(csp_aes_t *ptAesBase, csi_aes_config_t *ptAesCfg)
//{
//	csp_aes_set_mode(ptAesBase, (aes_mode_e)ptAesCfg->eMode);
//	csp_aes_set_key(ptAesBase,ptAesCfg->pwKey);
//	csp_aes_set_key_len(ptAesBase, (aes_key_ken_e)ptAesCfg->eKeyLength);
//	csp_aes_set_endian_in(ptAesBase, (aes_endian_e)ptAesCfg->eEndianIn);
//	csp_aes_set_endian_inter(ptAesBase, (aes_endian_e)ptAesCfg->eEndianInter);
//}
//
///** \brief AES encyption, chainning mode ECB
// * 
// *  \param[in] ptAesBase: pointer of aes register structure
// *  \param[in] pwInput: Input Pointer to the input buffer (plaintext)	
// *  \param[in] InputSize: Size Length of the plaintext buffer in word
// *  \param[in] pwOutput:  Output Pointer to the output buffer(encrypted data)
// *  \return csi_error_t
// */ 
//csi_error_t csi_aes_ecb_encrypt(csp_aes_t *ptAesBase, uint32_t *pwInput, uint32_t InputSize, uint32_t *pwOutput)
//{
//	uint32_t i = 0;
//	csi_error_t ret = CSI_OK;
//	while(csp_aes_get_sr(ptAesBase)& AES_BUSY);
//	
//	csp_aes_set_mode(ptAesBase,AES_MD_ECB);
//	csp_aes_set_wkmd(ptAesBase, AES_ENCYPT);
////	csp_aes_set_iv(ptAesBase, pwIv);
//	
//	while(i < InputSize/4)
//	{
//		csp_aes_write_data(ptAesBase,pwInput);
//		csp_aes_start(ptAesBase);
//		pwOutput = csp_aes_get_result(ptAesBase);
//		while(!(csp_aes_get_sr(ptAesBase)& AES_DATA_INT));
//		pwInput += 4;
//		pwOutput += 4;
//	}
//	return ret;
//}
//
//
//csi_error_t csi_aes_ecb_decrypt(csp_aes_t *ptAesBase,uint32_t *pwInput, uint32_t InputSize, uint32_t *pwOutput)
//{
//	uint32_t i = 0;
//	csi_error_t ret = CSI_OK;
//	while(csp_aes_get_sr(ptAesBase)& AES_BUSY);
//	
//	//do key expand first
//	csp_aes_set_wkmd(ptAesBase, AES_KEYEX);
//	csp_aes_start(ptAesBase);
//	while(!(csp_aes_get_sr(ptAesBase)& AES_KEY_INT));
//	
//	//decryption 
//	csp_aes_set_mode(ptAesBase,AES_MD_ECB);
//	csp_aes_set_wkmd(ptAesBase, AES_DECYPT);
//	
//	while(i < InputSize/4)
//	{
//		csp_aes_write_data(ptAesBase,pwInput);
//		csp_aes_start(ptAesBase);
//		pwOutput = csp_aes_get_result(ptAesBase);
//		while(!(csp_aes_get_sr(ptAesBase)& AES_DATA_INT));
//		pwInput += 4;
//		pwOutput += 4;
//	}
//	return ret;
//}