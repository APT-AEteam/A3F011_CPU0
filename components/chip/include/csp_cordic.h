/***********************************************************************//** 
 * \file  csp_cordic.h
 * \brief  I2S description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-12-14 <td>V0.0  <td>YT   <td>initial
 * </table>
 * *********************************************************************
*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CSP_CORDIC_H
#define _CSP_CORDIC_H

/* Includes ------------------------------------------------------------------*/
#include <soc.h>

typedef struct
{
	__IOM  uint32_t CORDICCTRL;		 //0x00	 CORDIC CONTROL Register
	__OM   uint32_t CORDICINDATA1;   //0X04  CORDIC INPUT DATA 1 Register
	__OM   uint32_t CORDICINDATA2;   //0X08  CORDIC INPUT DATA 2 Register
	__IM   uint32_t CORDICOUTDATA;   //0X0C  CORDIC OUTPUT DATA Register
	__IOM   uint32_t CORDICSTATE;     //0X10  CORDIC STATE Register
	__IM   uint32_t CORDICMISR;      //0X14  CORDIC Interrupt Status 
	__IOM  uint32_t CORDICIMCR;      //0X18  CORDIC Interrupt Enable 
	__IM   uint32_t CORDICRISR;      //0X1C  CORDIC Raw Interrupt Status
	__OM   uint32_t CORDICICR;       //0X20  CORDIC Interrupt Status Clear
	__IOM  uint32_t CORDICSHADOW;    //0X24  CORDIC STATE Register,for debug
} csp_cordic_t;

/*****************************************************************************
* CORDICCTRL : CORDIC Control Register
******************************************************************************/  
#define CORDIC_FUNC_POS       (0)             //CORDIC Function
#define CORDIC_FUNC_MSK      (0x0ful << CORDIC_FUNC_POS) 
typedef enum
{
	CORDIC_FUNCTION_SIN = 0,
	CORDIC_FUNCTION_COS,
	CORDIC_FUNCTION_SINH,
	CORDIC_FUNCTION_COSH,
	CORDIC_FUNCTION_MULTIPLE,
	CORDIC_FUNCTION_PHASE,
	CORDIC_FUNCTION_ATAN,
	CORDIC_FUNCTION_MODULUS,
	CORDIC_FUNCTION_ATANH,
	CORDIC_FUNCTION_DIVISION,
	CORDIC_FUNCTION_COS_SIN,
	CORDIC_FUNCTION_ATAN_MODULE,
	CORDIC_FUNCTION_COSH_SINH,
	CORDIC_FUNCTION_ATANH_SQRT_SQUARE_MINUS,   //CORDIC_FUNCTION_ATANH_(x^2-y^2)^(1/2),
}cordic_func_e;

#define CORDIC_PERCISION_POS       (4)             //CORDIC Precision
#define CORDIC_PERCISION_MSK      (0x0ful << CORDIC_PERCISION_POS) 
typedef enum
{
	CORDIC_PRECISION_4CYCLES			= 0,
	CORDIC_PRECISION_8CYCLES,
	CORDIC_PRECISION_12CYCLES,
	CORDIC_PRECISION_16CYCLES,
	CORDIC_PRECISION_20CYCLES,
	CORDIC_PRECISION_24CYCLES,
	CORDIC_PRECISION_28CYCLES
}cordic_precision_e;

#define CORDIC_SCALE_POS       (8)             //CORDIC Scaling factor. Scale factor value 'n' implies that the input data have been multiplied  by a factor 2exp(-n), and/or the output data need to be multiplied by 2exp(n)
#define CORDIC_SCALE_MSK      (0x07ul << CORDIC_SCALE_POS) 
typedef enum
{
	CORDIC_SCALE_0			= 0,
	CORDIC_SCALE_1,
	CORDIC_SCALE_2,
	CORDIC_SCALE_3,
	CORDIC_SCALE_4,
	CORDIC_SCALE_5,
	CORDIC_SCALE_6,
	CORDIC_SCALE_7,
}cordic_scale_e;

#define CORDIC_INTEN_POS       (12)             //CORDIC Interupt Enable
#define CORDIC_INTEN_MSK      (0x01ul << CORDIC_INTEN_POS) 
typedef enum
{
	CORDIC_INTDIS			= 0,
	CORDIC_INTEN,
}cordic_inten_e;

#define CORDIC_OUTSIZE_POS       (17)             //CORDIC Output Size
#define CORDIC_OUTSIZE_MSK      (0x01ul << CORDIC_OUTSIZE_POS) 
typedef enum
{
	CORDIC_OUTSIZE_32BIT			= 0,
	CORDIC_OUTSIZE_16BIT,
}cordic_outsize_e;

#define CORDIC_INSIZE_POS       (18)             //CORDIC Input Size
#define CORDIC_INSIZE_MSK      (0x01ul << CORDIC_INSIZE_POS) 
typedef enum
{
	CORDIC_INSIZE_32BIT			= 0,
	CORDIC_INSIZE_16BIT,
}cordic_insize_e;

#define CORDIC_OV_POS       (25)             //CORDIC Overflow Flag
#define CORDIC_OV_MSK      (0x01ul << CORDIC_OV_POS) 

#define CORDIC_STACKLEVEL_POS       (26)             //CORDIC Stacklevel
#define CORDIC_STACKLEVEL_MSK      (0x0ful << CORDIC_STACKLEVEL_POS) 

#define CORDIC_RRDYTRGOE_POS       (30)             //CORDIC Result Ready Triger Output Enable
#define CORDIC_RRDYTRGOE_MSK      (0x01ul << CORDIC_RRDYTRGOE_POS) 
typedef enum
{
	CORDIC_RRDYTRGOE_DIS			= 0,
	CORDIC_RRDYTRGOE_EN,
}cordic_rrdytrgoe_e;

#define CORDIC_RRDY_POS       (31)             //CORDIC Result Ready Triger Output Enable
#define CORDIC_RRDY_MSK      (0x01ul << CORDIC_RRDY_POS) 

/*****************************************************************************
* CORDICINDATA1 : CORDIC Input Data 1 Register
******************************************************************************/  
#define CORDIC_INPUTD1_POS       (0)     
#define CORDIC_INPUTD1_MSK       (0xfffffffful << CORDIC_INPUTD1_POS) 
#define CORDIC_INPUTD1(val)      (((val) & 0xfffffffful) << CORDIC_INPUTD1_POS)  

/*****************************************************************************
* CORDICINDATA2 : CORDIC Input Data 2 Register
******************************************************************************/ 
#define CORDIC_INPUTD2_POS       (0)     
#define CORDIC_INPUTD2_MSK       (0xfffffffful << CORDIC_INPUTD2_POS) 
#define CORDIC_INPUTD2(val)      (((val) & 0xfffffffful) << CORDIC_INPUTD2_POS) 
 
/*****************************************************************************
* CORDICOUTDATA : CORDIC Output Data Register
******************************************************************************/ 
#define CORDIC_OUTPUTD_POS       (0)     
#define CORDIC_OUTPUTD_MSK       (0xfffffffful << CORDIC_OUTPUTD_POS) 

/*****************************************************************************
* CORDICSTATE : CORDIC State Register
******************************************************************************/ 
#define CORDIC_START_POS       (0)             //CORDIC Start Computing Control 
#define CORDIC_START_MSK      (0x01ul << CORDIC_START_POS) 
typedef enum
{
	CORDIC_START_DIS			= 0,
	CORDIC_START_EN,
}cordic_start_e;

#define CORDIC_STOP_POS       (1)             //CORDIC Stop Computing Control 
#define CORDIC_STOP_MSK      (0x01ul << CORDIC_STOP_POS) 
typedef enum
{
	CORDIC_STOP_DIS			= 0,
	CORDIC_STOP_EN,
}cordic_stop_e;

#define CORDIC_BUSY_POS       (2)             //CORDIC Busy state flag 
#define CORDIC_BUSY_MSK      (0x01ul << CORDIC_BUSY_POS) 


/*****************************************************************************
 ******************** CORDIC inline Functions Declaration ***********************
 *****************************************************************************/
 
static inline void csp_cordic_set_function(csp_cordic_t *ptCordicBase, cordic_func_e eFunc)
{
	ptCordicBase->CORDICCTRL = (ptCordicBase->CORDICCTRL & (~CORDIC_FUNC_MSK)) | (eFunc << CORDIC_FUNC_POS);
}

static inline void csp_cordic_set_precision(csp_cordic_t *ptCordicBase, cordic_precision_e ePrecision)
{
	ptCordicBase->CORDICCTRL = (ptCordicBase->CORDICCTRL & (~CORDIC_PERCISION_MSK)) | (ePrecision << CORDIC_PERCISION_POS);	
}

static inline void csp_cordic_set_scale(csp_cordic_t *ptCordicBase, cordic_scale_e eScale)
{
	ptCordicBase->CORDICCTRL = (ptCordicBase->CORDICCTRL & (~CORDIC_SCALE_MSK)) | (eScale << CORDIC_SCALE_POS);
}

//static inline void csp_cordic_interrupt_enable(csp_cordic_t *ptCordicBase)
//{
//	ptCordicBase->CORDICCTRL = (ptCordicBase->CORDICCTRL & (~CORDIC_INTEN_MSK)) | (CORDIC_INTEN << CORDIC_INTEN_POS);
//}

static inline void csp_cordic_interrupt_disable(csp_cordic_t *ptCordicBase)
{
	ptCordicBase->CORDICCTRL = (ptCordicBase->CORDICCTRL & (~CORDIC_INTEN_MSK)) | (CORDIC_INTDIS << CORDIC_INTEN_POS);
}

static inline void csp_cordic_set_output_data_size(csp_cordic_t *ptCordicBase, cordic_outsize_e eOutsize)
{
	ptCordicBase->CORDICCTRL = (ptCordicBase->CORDICCTRL & (~CORDIC_OUTSIZE_MSK)) | (eOutsize << CORDIC_OUTSIZE_POS);
}

static inline void csp_cordic_set_input_data_size(csp_cordic_t *ptCordicBase, cordic_insize_e eInsize)
{
	ptCordicBase->CORDICCTRL = (ptCordicBase->CORDICCTRL & (~CORDIC_INSIZE_MSK)) | (eInsize << CORDIC_INSIZE_POS);
}

static inline uint8_t csp_cordic_get_stack_overflow_flag(csp_cordic_t *ptCordicBase)
{
	return (uint8_t)(ptCordicBase->CORDICCTRL & CORDIC_OV_MSK);
}

static inline uint8_t csp_cordic_get_stack_level(csp_cordic_t *ptCordicBase)
{
	return (uint8_t)(ptCordicBase->CORDICCTRL & CORDIC_STACKLEVEL_MSK);
}

static inline void csp_cordic_result_ready_triger_output_enable(csp_cordic_t *ptCordicBase)
{
	ptCordicBase->CORDICCTRL = (ptCordicBase->CORDICCTRL & (~CORDIC_RRDYTRGOE_MSK)) | (CORDIC_RRDYTRGOE_EN << CORDIC_RRDYTRGOE_POS);
}

static inline void csp_cordic_result_ready_triger_output_disable(csp_cordic_t *ptCordicBase)
{
	ptCordicBase->CORDICCTRL = (ptCordicBase->CORDICCTRL & (~CORDIC_RRDYTRGOE_MSK)) | (CORDIC_RRDYTRGOE_DIS << CORDIC_RRDYTRGOE_POS);
}

static inline uint8_t csp_cordic_get_result_ready_flag(csp_cordic_t *ptCordicBase)
{
	return (uint8_t)(ptCordicBase->CORDICCTRL & CORDIC_RRDY_MSK);
}

static inline void csp_cordic_set_input_data_1(csp_cordic_t *ptCordicBase, uint32_t wInputData1)
{
	ptCordicBase->CORDICINDATA1 = wInputData1; 
}

static inline void csp_cordic_set_input_data_2(csp_cordic_t *ptCordicBase, uint32_t wInputData2)
{
	ptCordicBase->CORDICINDATA2 = wInputData2; 
}

static inline int32_t csp_cordic_get_output_data(csp_cordic_t *ptCordicBase)
{
	return (int32_t)ptCordicBase->CORDICOUTDATA; 
}

static inline void csp_cordic_set_start(csp_cordic_t *ptCordicBase, cordic_start_e eStart)
{
	ptCordicBase->CORDICSTATE = (ptCordicBase->CORDICSTATE & (~CORDIC_START_MSK)) | (eStart << CORDIC_START_POS);
}

static inline void csp_cordic_set_stop(csp_cordic_t *ptCordicBase, cordic_stop_e eStop)
{
	ptCordicBase->CORDICSTATE = (ptCordicBase->CORDICSTATE & (~CORDIC_STOP_MSK)) | (eStop << CORDIC_STOP_POS);
}

static inline uint8_t csp_cordic_get_busy_flag(csp_cordic_t *ptCordicBase)
{
	return (uint8_t)(ptCordicBase->CORDICSTATE & CORDIC_BUSY_MSK);
}

static inline void csp_cordic_clr_isr(csp_cordic_t *ptCordicBase,uint32_t wIntNum)
{
	ptCordicBase->CORDICICR = wIntNum;
}
static inline void csp_cordic_clr_all_isr(csp_cordic_t *ptCordicBase)
{
	ptCordicBase->CORDICICR = 0x7fff;
}

static inline void csp_cordic_imcr_enable(csp_cordic_t *ptCordicBase,uint32_t wIntNum)
{
	ptCordicBase->CORDICIMCR |= wIntNum;
}

static inline void csp_cordic_imcr_disable(csp_cordic_t *ptCordicBase,uint32_t wIntNum)
{
	ptCordicBase->CORDICIMCR &= (~wIntNum);
}


#endif