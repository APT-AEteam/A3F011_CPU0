/***********************************************************************//** 
 * \file  csp_aes.h
 * \brief AES description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2023-11-29 <td>V0.0  <td>WNN   <td>initial
 * </table>
 * *********************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CSP_AES_H
#define _CSP_AES_H

/* Includes ------------------------------------------------------------------*/
#include <soc.h>
#include "csp_common.h"

typedef struct
{
   __IOM uint32_t	DATAIN0;  	// AES data input register 0
   __IOM uint32_t	DATAIN1;  	// AES data input register 1
   __IOM uint32_t	DATAIN2;  	// AES data input register 2
   __IOM uint32_t	DATAIN3;  	// AES data input register 3   
   __IOM uint32_t	KEY0;  		// AES key register 0
   __IOM uint32_t	KEY1;  		// AES key register 1
   __IOM uint32_t	KEY2;  		// AES key register 2
   __IOM uint32_t	KEY3;  		// AES key register 3   
   __IOM uint32_t	IV0;  		// AES initialization vector register 0
   __IOM uint32_t	IV1;  		// AES initialization vector register 1
   __IOM uint32_t	IV2;  		// AES initialization vector register 2
   __IOM uint32_t	IV3;  		// AES initialization vector register 3
   __IOM uint32_t	CR;		    // AES control register	
   __IOM uint32_t	SR;			// AES status register	
   __IOM uint32_t	DATAOUT0;  	// AES data output register 0
   __IOM uint32_t	DATAOUT1;  	// AES data output register 1
   __IOM uint32_t	DATAOUT2;  	// AES data output register 2
   __IOM uint32_t	DATAOUT3;  	// AES data output register 3
} csp_aes_t;


/******************************************************************************
* CR : AES Control Register
******************************************************************************/
#define	AES_START_POS	(0)
#define	AES_START_MSK	(0x01ul << AES_START_POS)
#define AES_START		(1)

typedef enum
{
	AES_KEY_INT    	=	(0x01ul << 1), 
	AES_DATA_INT    =	(0x01ul << 2),     
}aes_int_e;

#define AES_MODE_POS	(3)
#define	AES_MODE_MSK	(0x01ul << AES_MODE_POS)
typedef enum
{
	AES_MD_ECB    =	(0x00ul), 
	AES_MD_CBC    =	(0x01ul),     
}aes_mode_e;

#define AES_KEY_LEN_POS	(4)
#define	AES_KEY_LEN_MSK	(0x03ul << AES_KEY_LEN_POS)
typedef enum
{
	AES_K128    =	(0x00ul), 
	AES_K192    =	(0x01ul),  
	AES_K256    =	(0x02ul),
}aes_key_ken_e;

#define AES_WKMODE_POS	(6)
#define	AES_WKMODE_MSK	(0x03ul << AES_WKMODE_POS)
typedef enum
{
	AES_ENCYPT   =	(0x00ul), 
	AES_DECYPT   =	(0x01ul),  
	AES_KEYEX    =	(0x02ul),
}aes_wkmd_e;

#define AES_ENDIAN_INTER_POS	(8)
#define	AES_ENDIAN_INTER_MSK	(0x01ul << AES_ENDIAN_INTER_POS)
#define AES_ENDIAN_IN_POS	(9)
#define	AES_ENDIAN_IN_MSK	(0x01ul << AES_ENDIAN_IN_POS)
typedef enum
{
	AES_ENDIAN_L  =	(0x00ul), 
	AES_ENDIAN_B  =	(0x01ul),  
}aes_endian_e;

/******************************************************************************
* SR : AES Status Register
******************************************************************************/
#define	AES_STATUS_POS	(0)
#define	AES_STATUS_MSK	(0x01ul << AES_STATUS_POS)
typedef enum
{
	AES_IDLE  =	(0x00ul), 
	AES_BUSY  =	(0x01ul),  
}aes_status_e;

#define	AES_INT_POS	(0)
#define	AES_KEYEX_STATUS_MSK	(0x01ul << AES_KEYEX_STATUS_POS)


/*****************************************************************************
 * static inline functions
 ****************************************************************************/
static inline uint16_t csp_aes_get_sr(csp_aes_t *ptAesBase)
{
	return ptAesBase -> SR;
}

static inline void csp_aes_start(csp_aes_t *ptAesBase)
{
	ptAesBase -> CR |= AES_START;
}

static inline void csp_aes_set_mode(csp_aes_t *ptAesBase, aes_mode_e eMode)
{
	ptAesBase -> CR = (ptAesBase -> CR & (~AES_MODE_MSK)) | (eMode << AES_MODE_POS);
}

static inline void csp_aes_set_wkmd(csp_aes_t *ptAesBase, aes_wkmd_e eMode)
{
	ptAesBase -> CR = (ptAesBase -> CR & (~AES_WKMODE_MSK)) | (eMode << AES_WKMODE_POS);
}

static inline void csp_aes_set_key_len(csp_aes_t *ptAesBase, aes_key_ken_e eKeyLen)
{
	ptAesBase -> CR = (ptAesBase -> CR & (~AES_KEY_LEN_MSK)) | (eKeyLen << AES_KEY_LEN_POS);
}

static inline void csp_aes_set_endian_in(csp_aes_t *ptAesBase, aes_endian_e eEndian)
{
	ptAesBase -> CR = (ptAesBase -> CR & (~AES_ENDIAN_IN_MSK)) | (eEndian << AES_ENDIAN_IN_POS);
}

static inline void csp_aes_set_endian_inter(csp_aes_t *ptAesBase, aes_endian_e eEndian)
{
	ptAesBase -> CR = (ptAesBase -> CR & (~AES_ENDIAN_INTER_MSK)) | (eEndian << AES_ENDIAN_INTER_POS);
}

static inline void csp_aes_set_cr(csp_aes_t *ptAesBase, uint32_t wCr)
{
	ptAesBase->CR = wCr;
}

static inline void csp_aes_write_data(csp_aes_t *ptAesBase,uint32_t *pwData)
{
	ptAesBase->DATAIN0 = *(uint32_t *)pwData;
	pwData += 4;
	ptAesBase->DATAIN1 = *(uint32_t *)pwData;
	pwData += 4;
	ptAesBase->DATAIN2 = *(uint32_t *)pwData;
	pwData += 4;
	ptAesBase->DATAIN3 = *(uint32_t *)pwData;
}

static inline void csp_aes_set_key(csp_aes_t *ptAesBase,uint32_t *pwKey)
{
	ptAesBase->KEY0 = *(uint32_t *)pwKey;
	pwKey += 4;
	ptAesBase->KEY1 = *(uint32_t *)pwKey;
	pwKey += 4;
	ptAesBase->KEY2 = *(uint32_t *)pwKey;
	pwKey += 4;
	ptAesBase->KEY3 = *(uint32_t *)pwKey;
}

static inline void csp_aes_set_iv(csp_aes_t *ptAesBase,uint32_t *pwIv)
{
	ptAesBase->IV0 = *(uint32_t *)pwIv;
	pwIv += 4;
	ptAesBase->IV1 = *(uint32_t *)pwIv;
	pwIv += 4;
	ptAesBase->IV2 = *(uint32_t *)pwIv;
	pwIv += 4;
	ptAesBase->IV3 = *(uint32_t *)pwIv;
}

static inline uint32_t *csp_aes_get_result(csp_aes_t *ptAesBase)
{
	uint32_t * pwRslt;
	uint32_t wEndian = (ptAesBase->CR & AES_ENDIAN_IN_MSK) >> AES_ENDIAN_IN_POS;
	if (wEndian == AES_ENDIAN_L) {
		*(pwRslt) = ptAesBase->DATAOUT0;
		pwRslt += 4;
		*(pwRslt) = ptAesBase->DATAOUT1;
		pwRslt += 4;
		*(pwRslt) = ptAesBase->DATAOUT2;
		pwRslt += 4;
		*(pwRslt) = ptAesBase->DATAOUT3;
	}
	else {
		*(pwRslt) = ptAesBase->DATAOUT3;
		pwRslt += 4;
		*(pwRslt) = ptAesBase->DATAOUT2;
		pwRslt += 4;
		*(pwRslt) = ptAesBase->DATAOUT1;
		pwRslt += 4;
		*(pwRslt) = ptAesBase->DATAOUT0;
	}
	return pwRslt;
}

#endif