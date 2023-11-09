/***********************************************************************//** 
 * \file  cordic_demo.c
 * \brief  IIS_DEMO description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-12-16 <td>V0.0 <td>YT     <td>initial
 * </table>
 * *********************************************************************
*/

#include <string.h>
#include <drv/cordic.h>
#include <drv/pin.h>
#include <drv/irq.h>
#include "demo.h"
#include "csp.h"

// CORDIC polling/interrupt 计算输入1
int32_t pInBuff1[6]={0x08604189,0x07604189,0x06604189,0x00704189,0x00604189,0x04004189};

// CORDIC polling/interrupt 计算输入2
int32_t pInBuff2[6]={0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000};

// CORDIC计算输出数据存储Buff
int32_t pOutBuff[6]={0x00000001,0x00000002,0x00000003,0x00000004,0x00000005,0x00000006};

// CORDIC计算次数
uint32_t wNbCalc=6;   

// CORDIC DMA 输入数据存储Buff，按照CORDIC_IN1、CORDIC_IN2、CORDIC_OUT、CORDIC_SR顺序依次写入
int32_t pInBuff3[24]={0x08604189,0x00000010,0x01000000,0x1,0x07604189,0x00000020,0x02000000,0x1,0x06604189,0x00000030,0x03000000,0x1,0x00704189,0x00000040,0x04000000,0x1,0x00604189,0x00000050,0x05000000,0x1,0x04004189,0x00000060,0x06000000,0x1};


/** \brief CORDIC polling mode
 * 
 *  \param[in] none
 *  \return error code
 */
int cordic_polling_demo(void)
{
	csi_cordic_config_t ptCordicCfg;                //配置结构体
	ptCordicCfg.byFunction=CORDIC_FUNCTION_COS;     //配置运算函数
	ptCordicCfg.byInSize=CORDIC_INSIZE_32BIT;       //配置输入位数，16/32 bit可选
	ptCordicCfg.byOutSize=CORDIC_OUTSIZE_32BIT;     //配置输出位数，16/32 bit可选
	ptCordicCfg.byPrecision= CORDIC_PRECISION_16CYCLES;   //配置精度，4/8/12/16/20/24/28可选，精度越高，迭代次数越多，计算误差越小
	ptCordicCfg.byScale=CORDIC_SCALE_0;                   //配置缩放因子
	ptCordicCfg.hwInt= CORDIC_INTSRC_NONE;                //配置中断
	
	csi_cordic_configure(CORDIC, &ptCordicCfg);           //CORDIC初始化

	csi_cordic_calculate(CORDIC, pInBuff1, pInBuff2,pOutBuff,wNbCalc);    //开始轮询计算

	return 0;
}


 
 /** \brief  CORDIC interrupt mode
 * inten=1，cordic计算，rrdy置1，进中断，读取outputdata寄存器，rrdy被硬件置0
 * 在CORDIC中断里调用 cordic_irqhandler(CORDIC) 函数；
 * 
 *  \param[in] none
 *  \return error code
 */
 
int cordic_interrupt_demo(void)
{

	csi_cordic_config_t ptCordicCfg;     //配置结构体
	ptCordicCfg.byFunction=CORDIC_FUNCTION_SIN;  //配置运算函数
	ptCordicCfg.byInSize=CORDIC_INSIZE_32BIT;    //配置输入位数，16/32 bit可选
	ptCordicCfg.byOutSize=CORDIC_OUTSIZE_32BIT;  //配置输出位数，16/32 bit可选
	ptCordicCfg.byPrecision= CORDIC_PRECISION_16CYCLES;   //配置精度，4/8/12/16/20/24/28可选，精度越高，迭代次数越多，计算误差越小
	ptCordicCfg.byScale=CORDIC_SCALE_0;                   //配置缩放因子
	ptCordicCfg.hwInt= CORDIC_INTSRC_RRDY; //  interrupt enable
	csi_cordic_configure(CORDIC, &ptCordicCfg);   //CORDIC初始化
	csi_irq_enable((uint32_t *)CORDIC);      //中断打开

	csi_cordic_calculate_int(CORDIC, pInBuff1, pInBuff2,pOutBuff,wNbCalc);   //开始中断计算
	
	return 0;
}



/** \brief CORDIC dma mode
 *  CORDIC DMA write mode, SRAM -> CORDIC IP
 *  CORDIC DMA read mode, CORDIC IP -> SRAM
 *  RRDY=1且RRDYTRGOE=1时，CORDIC输出事件触发请求。单个源触发两个DMA搬移，DMA write 和DMA read
 * 
 *  \param[in] none
 *  \return none
 */
int cordic_dma_demo(void)
{
	csi_cordic_config_t ptCordicCfg;
	ptCordicCfg.byFunction=CORDIC_FUNCTION_COS;
	ptCordicCfg.byInSize=CORDIC_INSIZE_32BIT;
	ptCordicCfg.byOutSize=CORDIC_OUTSIZE_32BIT;
	ptCordicCfg.byPrecision= CORDIC_PRECISION_16CYCLES;
	ptCordicCfg.byScale=CORDIC_SCALE_0;
	ptCordicCfg.hwInt= CORDIC_INTSRC_NONE;
	csi_cordic_configure(CORDIC, &ptCordicCfg);
	csp_cordic_result_ready_triger_output_enable(CORDIC);     // enable RRDYTRGOE (result ready triger output enable)
	
	// pInBuff3: CORDIC DMA 输入数据存储Buff，按照CORDIC_IN1、CORDIC_IN2、CORDIC_OUT、CORDIC_SR顺序依次写入
	// pOutBuff: CORDIC计算输出数据存储Buff
	csi_cordic_calculate_dma(CORDIC, pInBuff3, pOutBuff,wNbCalc);
	
	return 0;
}


/** \brief TEST FOR CORDIC STOP & BUSY REGISTER

 *  \param[in] none
 *  \return error code
 */

int cordic_test_stop_busy_demo(void)
{
	csi_cordic_config_t ptCordicCfg;
	ptCordicCfg.byFunction=CORDIC_FUNCTION_ATANH;
	ptCordicCfg.byInSize=CORDIC_INSIZE_32BIT;
	ptCordicCfg.byOutSize=CORDIC_OUTSIZE_32BIT;
	ptCordicCfg.byPrecision= CORDIC_PRECISION_28CYCLES;
	ptCordicCfg.byScale=CORDIC_SCALE_0;
	ptCordicCfg.hwInt= CORDIC_INTSRC_NONE;

	csi_cordic_configure(CORDIC, &ptCordicCfg);
	csp_cordic_set_input_data_1(CORDIC, 0x8000000);
	csp_cordic_set_input_data_2(CORDIC, 0x4000000);
	*(unsigned int *)(0x53000010) = 0x00000001;  //start=1
	*(unsigned int *)(0x53000010) = 0x00000002;  //stop=1
//	*(unsigned int *)(0x53000010) = 0x00000001;  //start=1  //如果取消注释，则RRDY会置1，会出正确结果
	uint32_t result=csp_cordic_get_output_data(CORDIC);   // 断点打到这里，如果此时，RRDY没有拉高，且往下走一步，result结果是错误的，则证明stop=1起作用了;如果此时，BUSY=1,则证明BUSY起作用
	result= result-1;    // 这行代码是用来屏蔽编译产生的warning用的
	return 0;
}