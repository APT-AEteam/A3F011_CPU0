/***********************************************************************//** 
 * \file  aes.h
 * \brief  csi aes driver head file
 * \copyright Copyright (C) 2015-2023 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2023-11-29 <td>V0.0  <td>WNN   <td>initial
 * </table>
 * *********************************************************************
*/
#ifndef _DRV_AES_H_
#define _DRV_AES_H_

#include "common.h"
#include "csp_aes.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * \enum	csi_aes_wkmode_e
 * \brief   AES work mode
 */
typedef enum
{
	AES_ENCRYPT	= 0,	//encryption
	AES_DECRYPT ,		//decryption
	AES_KEYEXPAND,		//key expand
}csi_aes_wkmode_e;

/**
 * \enum	aes_key_ken_e
 * \brief   AES key length
 */
typedef enum
{
	AES_KEY128    =	(0x00ul), 
	AES_KEY192    =	(0x01ul),  
	AES_KEY256    =	(0x02ul),
}csi_aes_key_len_e;

/**
 * \enum	csi_aes_endian_e
 * \brief   AES endian mode, can be set independently for inner words or inter words
 */
typedef enum
{
	AES_LITTLE_ENDIAN	= 0,	
	AES_BIG_ENDIAN ,		
}csi_aes_endian_e;

typedef struct {
//	csi_aes_wkmode_e	eWkMode;        //AES work mode: encryption/decryption/keyexpand
	uint32_t *			*pwKey;			//key
	csi_aes_key_len_e 	eKeyLength;		//length of key:128/192/256
	csi_aes_endian_e	eEndianIn;		//endian in a word
	csi_aes_endian_e	eEndianInter;	//endian between words
} csi_aes_config_t;

void csi_aes_init(csp_aes_t *ptAdcBase, csi_aes_config_t *ptAdcCfg);
csi_error_t csi_aes_ecb_encrypt(csp_aes_t *ptAesBase, uint32_t *pwInput, uint32_t InputSize, uint32_t *pwOutput);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_AES_H_ */
