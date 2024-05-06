/***********************************************************************//** 
 * \file  QSPI_demo.c
 * \brief  QSPI示例代码。
 * w25q16jvsiq(32 block == 512 sector == 2M Byte)
 * 1 page = 256 bytes
 * 1 sector = 16 page (4KB)
 * 1 block = 16 sector (64KB)
 * erasable(1sector,1/2block,1block,chip)
 * Device ID: (M7->M0 = 0xEF), (ID7->ID0 = 0x14)
 * 
 * \copyright Copyright (C) 2015-2021 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version    <th>Author  <th>Description
 * <tr><td> 2021-07-02 <td>V0.0  <td>LQ     <td>initial
 * </table>
 * *********************************************************************
*/

/* include ----------------------------------------------------------------*/
#include "qspi.h"
#include "pin.h"
#include <iostring.h>
#include "dma.h"
#include "etb.h"
#include "irq.h"
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
//w25q80dvssig(16 block == 256 sector == 1M Byte)
// 1 page = 256 bytes
// 1 sector = 16 page (4KB)
// 1 block = 16 sector (64KB)
//erasable(1 sector(4k),1/2block(32k),1 block(64k),chip(all))

//register 1------------------------------------------
// S7     S6    S5   S4     S3   S2    S1    S0
//SPR0    SEC   TB   BP2    BP1  BP0   WEL   BUSY
//SPR0:Status Protect      				 read/write 
//SEC: Sector/Block Protect
//TB:  TOP/BOTTOM Block Protect			 
//BP2,BP1,BP0:FLASH Block Protect	 	 read/write 
//WEL: Write Enable Latch				 read only
//BUSY:Busy flage（1 busy：0 idle）      read only
//defualt:0x00
//register 1------------------------------------------

//register 2------------------------------------------
// S15     S14    S13   S12     S11   S10    S9    S8
// SUS     CMP    LB3   LB2     LB1   (R)    QE    SPR1
// SUS:Suspend status  	read only
// CMP:complement protect          read/write 
// LB3,LB2.LB1:security register   read/write 
// RESERVE:
// QE: quad enable    			   read/write 
// SPR1:   						   read/write 
//register 2------------------------------------------

#define W25Q80 	0XEF13 	
#define W25Q16 	0XEF14
#define W25Q32 	0XEF15
#define W25Q64 	0XEF16
#define W25Q128	0XEF17
#define W25Q256 0XEF18

#define     REG1                	0x01
#define     REG2                	0x02
#define		PAGE_SIZE				256
//flash cmd
#define		WREN_CMD				0x06		//write enable
#define		WRDI_CMD				0x04		//write disable
#define		RDSR1_CMD				0x05		//Read Status1
#define		RDSR2_CMD				0x35		//Read Status2
#define		WRSR_CMD				0x01		//Write Status(register1 and register2) 
#define		READ_CMD				0x03		//ReadData
#define     FDREAD_CMD              0x3B        //fast dual read output
#define     FDREADIO_CMD            0xBB        //fast dual read I/O 
#define		FREAD_CMD				0x0B		//FastReadData 
#define     FQREAD_CMD              0X6B        //fast quad read output 
#define     FQREADIO_CMD            0XEB        //fast quad read I/O
#define		PGPRO_CMD				0x02		//PageProgram
#define		FPGPRO_CMD				0x32		//Fast PageProgram
#define		SECTORERASE_CMD			0x20		//setor erase
#define		BKERASE0_CMD			0xD8		//block erase0(64k)
#define		BKERASE1_CMD			0x52		//block erase1(32k)
#define		CHIPERASE_CMD			0xc7		//chip erase
#define		RDDEVICEID_CMD			0x90		//STD read chip ID Read Electric Manufacturer DeviceID 
#define		DFRDDEVICEID_CMD		0x92		//DSPI read chip ID Read Electric Manufacturer DeviceID
#define		QFRDDEVICEID_CMD		0x94		//QSPI read chip ID Read Electric Manufacturer DeviceID
#define		RDCHIPID_CMD			0x9F		//read chip ID

void qspi_std_send(void)
{
	csi_qspi_config_t t_QspiConfig;
	uint8_t send[112] = 
    {0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,
	 0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,
	 0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,
	 0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,
	 0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,
	 0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,
	 0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,
	 0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,
	 0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,
	 0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,
	 0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,
	 0x55,0xaa};
	 
	t_QspiConfig.byInter 			= QSPI_NONE_INT;  //无中断
	t_QspiConfig.byRxFifoLevel 		= 0x04;    		  //接收fifo中断阈值4，大于等于4个，触发接收中断
	t_QspiConfig.byTxFifoLevel 		= 0x04;    		  //发送fifo中断阈值4，小于等于4个，触发发送中断
	t_QspiConfig.dwQspiBaud 		= 200000;    	  //传输速率
	t_QspiConfig.eQspiFrameLen 		= QSPI_DFS_8;  	  //数据8bit
	t_QspiConfig.eQspiPolarityPhase = QSPI_SPO0_SPH0; //时钟极性为0，相位为0	
	csi_qspi_init(QSPI,&t_QspiConfig);

	csi_qspi_set_cmd(QSPI,QSPI_SEND,QSPI_SPIFRF_FOUR,(QSPI_INSSTD_ADDSTD<<6 | INSTL_16<<4 | ADDRL_32),QSPI_S0EN);
	csp_qspi_en(QSPI);

	//指令单元:16bit
	uint16_t hwInst = 0x55aa;
	//地址单元:32bit
	uint32_t wAddr = 0x01234567;
	//数据单元
	uint8_t bDataSend[100] = {0x00};
	for(uint8_t bIndex = 0;bIndex < sizeof(bDataSend); bIndex++)
	{
		bDataSend[bIndex] = 0x5A;
	}

	//my_printf("qspi_begin!\n");
	while(1)
	{	
		csp_qspi_write_data( QSPI,hwInst );
		csp_qspi_write_data( QSPI,wAddr );
		for(uint8_t bIndex = 0; bIndex < sizeof(bDataSend); bIndex++ )
		{
			csi_qspi_waitflag(QSPI,QSPI_TFNF,0x01,0xffff);
			//while( !(QSPI->SR & QSPI_TNF) );
			//QSPI->DR[0] = bDataSend[bIndex];
			csp_qspi_write_data( QSPI,bDataSend[bIndex] );
		}
		while( QSPI->SR  & QSPI_BSY );
		mdelay(10);
	}	
	mdelay(10);			
	csi_qspi_set_cmd(QSPI,QSPI_SEND,QSPI_SPIFRF_FOUR,(QSPI_INSSTDX_ADDSTDX<<6 | INSTL_8<<4 | ADDRL_24),QSPI_S0EN);
	//DDR测试
	csp_qspi_set_ddre(QSPI,QSPI_DDRE_EN);//地址和数据DDR使能
	csp_qspi_set_instddre(QSPI,QSPI_INSTDDRE_EN);//指令DDR使能
	csp_qspi_en(QSPI);
	while(1)
	{	
		QSPI->DR[0] = send[0];
		QSPI->DR[0] = 0x112233;
		QSPI->DR[0] = send[2];
		QSPI->DR[0] = send[3];
		QSPI->DR[0] = send[4];
		QSPI->DR[0] = send[5];
		QSPI->DR[0] = send[6];
		QSPI->DR[0] = send[7];
		QSPI->DR[0] = send[8];
		QSPI->DR[0] = send[9];
		QSPI->DR[0] = send[10];
		QSPI->DR[0] = send[11];
		QSPI->DR[0] = send[12];
		QSPI->DR[0] = send[13];
		QSPI->DR[0] = send[14];
		QSPI->DR[0] = send[15];
		while(  QSPI->SR & QSPI_BSY );
		mdelay(100);
		nop;
	}
}

//QSPI发送中断测试
void qspi_send_interrupt_test(void)
{
	//my_
	printf("qspi_send_interrupt_test!\n");
	csi_qspi_config_t t_QspiConfig;
	int8_t send[100] = {0};
	uint32_t wLen = sizeof(send);
	
	for(uint8_t byCount = 0;byCount < wLen;byCount++)
	{
		send[byCount] = byCount + 1;
	}
	
	t_QspiConfig.byInter = QSPI_TXE_INT;   //发送空中断（相对阈值）
	t_QspiConfig.byRxFifoLevel = 0x04;     //接收fifo中断阈值4，大于等于4个，触发接收中断
	t_QspiConfig.byTxFifoLevel = 0x08;     //发送fifo中断阈值8，小于等于8个，触发发送中断
	t_QspiConfig.dwQspiBaud = 1000000;     //传输速率
	t_QspiConfig.eQspiFrameLen = QSPI_DFS_8;  //数据8bit
	t_QspiConfig.hwDataFrameNumber    = sizeof(send);             //数据帧数100
	t_QspiConfig.eQspiPolarityPhase = QSPI_SPO0_SPH0; //时钟极性为0，相位为0
	
	csi_qspi_init(QSPI,&t_QspiConfig);
	
	//QSPI指针，发送模式，四线，指令和地址均为标准spi，指令长度8，地址长度24，从机选择信号
	csi_qspi_set_cmd(QSPI,QSPI_SEND,QSPI_SPIFRF_FOUR,(QSPI_INSSTD_ADDSTD<<6 | INSTL_8<<4 | ADDRL_24),QSPI_S0EN);
	csi_qspi_asyns_send(QSPI,send,wLen);
	csp_qspi_en(QSPI);

	while(1)
	{
		nop;
	}
//	csi_vic_enable_irq(QSPI_IRQn);
//	QSPI->CR0 = 0x07;
//	QSPI->CR1 = 0x00;
//	QSPI->SER = 0x00;
//	QSPI->IMCR = 0x00;
//	
//	QSPI->TXFIFO_TLR = 0x04;
//	QSPI->RXFIFO_TLR = 0x04;
//	QSPI->CPSR = 0x30;
//	while( QSPI->SR  & QSPI_BSY );
//	
//	t_QspiConfig.byInter = QSPI_TXE_INT | QSPI_TXO_INT | QSPI_RXU_INT | QSPI_RXO_INT | QSPI_RXF_INT | QSPI_MST_INT;;   //发送空中断（相对阈值）
//	t_QspiConfig.byRxFifoLevel = 0x04;     //接收fifo中断阈值4，大于等于4个，触发接收中断
//	t_QspiConfig.byTxFifoLevel = 0x04;     //发送fifo中断阈值8，小于等于8个，触发发送中断
//	t_QspiConfig.dwQspiBaud = 1000000;     //传输速率
//	t_QspiConfig.eQspiFrameLen = QSPI_DFS_8;  //数据8bit
//	t_QspiConfig.eQspiPolarityPhase = QSPI_SPO0_SPH0; //时钟极性为0，相位为0
//	csi_qspi_init(QSPI,&t_QspiConfig);
//
//	csi_qspi_set_cmd(QSPI,QSPI_SEND,QSPI_SPIFRF_FOUR,(QSPI_INSSTD_ADDSTD<<6 | INSTL_8<<4 | ADDRL_24),QSPI_S0EN);
//	QSPI->CR1  = 0x18;
//	QSPI->IMCR = 0x3F;
//	QSPI->CR0 |= 0x20;
//	
//	for( uint8_t i=0;i<200;i++)
//	{
//		while(!( QSPI->SR  & 0x02 ))
//			nop;
//		if(i%2 == 0)
//			QSPI->DR[0] = 0x55;
//		else
//			QSPI->DR[1] = 0xAA;
//	}
	
}

//QSPI接收中断测试
void qspi_recv_interrupt_test(void)
{
	uint32_t wId2;
	//my_
	printf("qspi_recv_interrupt_test!\n");
	csi_qspi_config_t t_QspiConfig;
	uint8_t recv[200] = {0};
	t_QspiConfig.byInter = QSPI_TXO_INT | QSPI_RXU_INT | QSPI_RXO_INT | QSPI_RXF_INT | QSPI_MST_INT;   //接收满中断（相对阈值）
	t_QspiConfig.byRxFifoLevel = 0x08;    //接收fifo中断阈值4，大于等于4个，触发接收中断
	t_QspiConfig.byTxFifoLevel = 0x08;    //发送fifo中断阈值8，小于等于8个，触发发送中断
	t_QspiConfig.dwQspiBaud = 1000000;     //传输速率
	t_QspiConfig.eQspiFrameLen = QSPI_DFS_8;  //数据8bit
	t_QspiConfig.eQspiPolarityPhase = QSPI_SPO0_SPH0; //时钟极性为0，相位为0
	
	csi_qspi_init(QSPI,&t_QspiConfig);
	
	//QSPI指针，接收模式，四线，指令为标准spi，地址为增强spi，指令长度8，地址长度24，从机选择信号
//	csi_qspi_set_cmd(QSPI,QSPI_RECV,QSPI_FRF_FOUR,(QSPI_INSSTD_ADDSTDX<<6 | INSTL_8<<4 | ADDRL_24),QSPI_S0EN);
//	csi_qspi_set_waitcycle(QSPI,6);
//	csi_qspi_asyns_receive(QSPI,recv,200,0x94,0x000000);//四线循环读取w25q80的ID信息
	
	csi_qspi_set_cmd(QSPI,QSPI_RECV,QSPI_SPIFRF_TWO,(QSPI_INSSTD_ADDSTD<<6 | INSTL_8<<4 | ADDRL_24),QSPI_S0EN);//指针，接收模式，数据4线spi格式，指令标准spi，地址标准spi，指令长度8，地址长度24
	csi_qspi_set_waitcycle(QSPI,8);                 		//等待周期设置为8	
	//csi_qspi_receive(QSPI,FQREAD_CMD,wAddr,pbyBuf,hwNum);   //QSPI指针，指令，地址，接收buff，接收长度
	csi_qspi_asyns_receive(QSPI,recv,100,DFRDDEVICEID_CMD,0x000000);//四线循环读取w25q80的ID信息  
	
//	wId2 = ((recv[0] << 8) |  recv[1]);
//	printf("ID2:0x%04lx\n",wId2);
	
	while(1)
	{
		nop;
	} 
}

void qspi_recv_test(void)
{	
	my_printf("qspi_recv_test!\n");
	csi_qspi_config_t t_QspiConfig;
	uint8_t recv[17] = {0};
	t_QspiConfig.byInter = QSPI_NONE_INT; //无中断
	t_QspiConfig.byRxFifoLevel = 0x04;    //接收fifo中断阈值4，大于等于4个，触发接收中断
	t_QspiConfig.byTxFifoLevel = 0x04;    //发送fifo中断阈值4，小于等于4个，触发发送中断
	t_QspiConfig.dwQspiBaud = 1000000;    //传输速率
	t_QspiConfig.eQspiFrameLen = QSPI_DFS_8;  //数据8bit
	t_QspiConfig.eQspiPolarityPhase = QSPI_SPO0_SPH0; //时钟极性为0，相位为0
	
	csi_qspi_init(QSPI,&t_QspiConfig);
	//QSPI指针，发送模式，四线，指令和地址均为标准spi，指令长度，地址长度，从机选择信号
	csi_qspi_set_cmd(QSPI,QSPI_RECV,QSPI_SPIFRF_FOUR,(QSPI_INSSTD_ADDSTD<<6 | INSTL_8<<4 | ADDRL_24),QSPI_S0EN);
	
	while(1)
	{
		csi_qspi_receive(QSPI,0x55,0x0304aa,recv,16);//QSPI指针，指令，地址，接收buff，接收长度
		mdelay(100);
		nop;	
	
	}
}

#define DDR_TEST 0
//QSPI同步模式发送，判断发送非满，条件满足填一个数据
void qspi_send_test(void)
{
	uint8_t bCount=0;
	
	//QSPI初始化
	csi_qspi_config_t t_QspiConfig;
	t_QspiConfig.byInter              = QSPI_NONE_INT; //无中断
	t_QspiConfig.byRxFifoLevel        = 0x04;             //接收fifo中断阈值4，大于等于4个，触发接收中断
	t_QspiConfig.byTxFifoLevel 	      = 0x04;             //发送fifo中断阈值4，小于等于4个，触发发送中断
	t_QspiConfig.dwQspiBaud           = 1000000;          //传输速率
	t_QspiConfig.eQspiFrameLen        = QSPI_DFS_8;       //数据帧8bit
	t_QspiConfig.hwDataFrameNumber    = 100;             //数据帧数20
	t_QspiConfig.eQspiPolarityPhase   = QSPI_SPO0_SPH0;   //时钟极性为0，相位为0	
	csi_qspi_init(QSPI,&t_QspiConfig); 
	
	//QSPI格式设置
	//QSPI_SEND:发送模式
	//QSPI_SPIFRF_FOUR:四线
	//QSPI_INSSTD_ADDSTD:指令和地址均为标准spi
	//INSTL_16：指令16位
	//ADDRL_32：地址32位
	//QSPI_S0EN：选择从机信号0
	csi_qspi_set_cmd(QSPI,QSPI_SEND,QSPI_SPIFRF_FOUR,(QSPI_INSSTD_ADDSTD<<6 | INSTL_16<<4 | ADDRL_32),QSPI_S0EN);

	//DDR功能测试，需要测试DDR功能时打开
#if DDR_TEST
	csp_qspi_set_ddre(QSPI,QSPI_DDRE_DIS);          //地址和数据DDR使能
	csp_qspi_set_instddre(QSPI,QSPI_INSTDDRE_DIS);  //指令DDR使能
	csp_qspi_set_ddredge(QSPI,5);                   //发送边沿：时间 = 5 * Tpclk = 5 *（1/48M）= 105ns
#endif

	//指令16bit
	uint16_t hwInst = 0x55aa;
	//地址32bit
	uint32_t wAddr  = 0x01234567;
	//数据
	uint8_t bDataSend[100] = {0x00};
	for(uint8_t bIndex = 0;bIndex < sizeof(bDataSend); bIndex++)
	{
		bDataSend[bIndex] = 0x5A;
	}
	
	csp_qspi_en(QSPI);
//	printf("en SR:%d\n",QSPI->SR);
	csp_qspi_write_data( QSPI,hwInst );
	csp_qspi_write_data( QSPI,wAddr );
	while(1)
	{	
//		printf("SR before Inst:%d\n",QSPI->SR);
//		csp_qspi_write_data( QSPI,hwInst );
//		printf("SR after Inst:%d\n",QSPI->SR);
//		csp_qspi_write_data( QSPI,wAddr );
//		printf("SR after addr:%d\n",QSPI->SR);
//		if(bCount < 10)
		{
		for(uint8_t bIndex = 0; bIndex < sizeof(bDataSend); bIndex++ )
		{
			if(csi_qspi_waitflag(QSPI,QSPI_TFNF,0x01,0xffff) == 0)
			{
//				printf("SR before send:%d,bIndex=%d\n",QSPI->SR,bIndex);
				csp_qspi_write_data( QSPI,bDataSend[bIndex] );
//				printf("SR after send:%d,bIndex=%d\n",QSPI->SR,bIndex);
			}
		}
//		bCount++;
//		mdelay(10);
		}
//		printf("Send over %d!\n",bCount);
//		printf("SR after all send:%d\n",QSPI->SR);
		while( QSPI->SR & QSPI_BSY );
		mdelay(10);
		printf("Send %d times!\n",bCount++);
	}
}

//充分利用发送fifo，一次填多个
void qspi_sendfifo_test(void)
{
	csi_qspi_config_t t_QspiConfig;
	uint8_t byindex = 0;
	uint8_t byCishu = 100;
	uint8_t byZheng = byCishu >> 3;//12
	uint8_t byYu = byCishu & 0x07;//4
	byZheng = byZheng << 3;//96
	uint8_t send[100] = {0x6b,0x00,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa
						,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa};
	for(uint8_t byIndex = 2;byIndex<100;byIndex++)
	{
		send[byIndex] = byIndex - 1;
	}
	
	t_QspiConfig.byInter = QSPI_NONE_INT; //无中断
	t_QspiConfig.byRxFifoLevel = 0x04;    //接收fifo中断阈值4，大于等于4个，触发接收中断
	t_QspiConfig.byTxFifoLevel = 0x04;    //发送fifo中断阈值4，小于等于4个，触发发送中断
	t_QspiConfig.dwQspiBaud = 1500000;    //传输速率
	t_QspiConfig.eQspiFrameLen = QSPI_DFS_8;  //数据8bit
	t_QspiConfig.eQspiPolarityPhase = QSPI_SPO0_SPH0; //时钟极性为0，相位为0
	
	csi_qspi_init(QSPI,&t_QspiConfig);
		
	//QSPI指针，发送模式，四线，指令和地址均为标准spi，指令长度，地址长度，从机选择信号
	csi_qspi_set_cmd(QSPI,QSPI_SEND,QSPI_SPIFRF_FOUR,(QSPI_INSSTD_ADDSTD<<6 | INSTL_8<<4 | ADDRL_24),QSPI_S0EN);
	csp_qspi_en(QSPI);
	while(1)
	{
		if(byZheng > 0)
		{
			for(byindex = 0; byindex < byZheng; byindex++ )
			{
				//csi_qspi_waitflag(QSPI,QSPI_TNF,0x01,0xffff);
				//QSPI->DRx[0] = send[byindex];
				csp_qspi_write_data( QSPI,send[byindex+0] );
				csp_qspi_write_data( QSPI,send[byindex+1] );
				csp_qspi_write_data( QSPI,send[byindex+2] );
				csp_qspi_write_data( QSPI,send[byindex+3] );
				csp_qspi_write_data( QSPI,send[byindex+4] );
				csp_qspi_write_data( QSPI,send[byindex+5] );
				csp_qspi_write_data( QSPI,send[byindex+6] );
				csp_qspi_write_data( QSPI,send[byindex+7] );
				byindex = byindex + 8;
				while( csp_qspi_read_txflr(QSPI) > 8 )
				{
					nop;
				}
			}
		}
		 if(byYu != 0)
		 {
			 if(byYu == 1)
			 {
				csp_qspi_write_data( QSPI,send[byindex+0] ); 
			 }
			 else if(byYu == 2)
			 {
				csp_qspi_write_data( QSPI,send[byindex+0] ); csp_qspi_write_data( QSPI,send[byindex+1] );
			 }
			 else if(byYu == 3)
			 {
				csp_qspi_write_data( QSPI,send[byindex+0] ); csp_qspi_write_data( QSPI,send[byindex+1] );
				csp_qspi_write_data( QSPI,send[byindex+2] );
			 }
			 else if(byYu == 4)
			 {
				csp_qspi_write_data( QSPI,send[byindex+0] ); csp_qspi_write_data( QSPI,send[byindex+1] );
				csp_qspi_write_data( QSPI,send[byindex+2] ); csp_qspi_write_data( QSPI,send[byindex+3] );
			 }
			 else if(byYu == 5)
			 {
				csp_qspi_write_data( QSPI,send[byindex+0] ); csp_qspi_write_data( QSPI,send[byindex+1] );
				csp_qspi_write_data( QSPI,send[byindex+2] ); csp_qspi_write_data( QSPI,send[byindex+3] );
				csp_qspi_write_data( QSPI,send[byindex+4] );
			 }
			 else if(byYu == 6)
			 {
				csp_qspi_write_data( QSPI,send[byindex+0] ); csp_qspi_write_data( QSPI,send[byindex+1] );
				csp_qspi_write_data( QSPI,send[byindex+2] ); csp_qspi_write_data( QSPI,send[byindex+3] );
				csp_qspi_write_data( QSPI,send[byindex+4] ); csp_qspi_write_data( QSPI,send[byindex+5] );
			 }
			 else if(byYu == 7)
			 {
				csp_qspi_write_data( QSPI,send[byindex+0] ); csp_qspi_write_data( QSPI,send[byindex+1] );
				csp_qspi_write_data( QSPI,send[byindex+2] ); csp_qspi_write_data( QSPI,send[byindex+3] );
				csp_qspi_write_data( QSPI,send[byindex+4] ); csp_qspi_write_data( QSPI,send[byindex+5] );
				csp_qspi_write_data( QSPI,send[byindex+6] );
			 }
		 }
		
		while( QSPI->SR  & QSPI_BSY );
		mdelay(20);
		
	}
}

/** \brief read register1 or register2
 * 
 *  \param[in] byRegx: 1(register1)  2(register2)
 *  \return register value
 */	
uint8_t w25qxx_read_register(uint8_t byRegx)
{
	uint8_t bySend[2] = {RDSR1_CMD, 0x00}; //reg1 command 0x05,reg2 command 0x35
	uint8_t byRecv[2] = {0};
	
	if(1 == byRegx)
		bySend[0] = RDSR1_CMD;
	else
		bySend[0] = RDSR2_CMD;
		
	csi_qspi_set_cmd(QSPI,QSPI_SEND_RECV,QSPI_SPIFRF_STD,(QSPI_INSSTD_ADDSTD<<6 | INSTL_8<<4 | ADDRL_8),QSPI_S0EN);
	csp_qspi_en(QSPI);
	
	for(uint8_t i=0;i<2;i++)
	{
		csi_qspi_waitflag(QSPI,QSPI_TFNF,0x01,0xffff);
		csp_qspi_write_data(QSPI,bySend[i]);
	}

	csi_qspi_waitflag(QSPI,QSPI_TFE,0x01,0xffff);
	
	for(uint8_t j=0;j<2;j++)
	{
		csi_qspi_waitflag(QSPI,QSPI_RFNE,0x01,0xffff);
		byRecv[j] = csp_qspi_read_data(QSPI);
	}
	return byRecv[1];
}

/** \brief read id
 * 
 *  \param[in] none
 *  \return id value (w25q80 0xef13)
 */	
uint32_t w25qxx_read_id(void)
{
	uint8_t bySend[6] = {RDDEVICEID_CMD, 0x00, 0x00, 0x00, 0x00, 0x00};//command 0x90
	uint8_t byRecv[6] = {0};
	uint32_t wId;
		
	csi_qspi_set_cmd(QSPI,QSPI_SEND_RECV,QSPI_SPIFRF_STD,(QSPI_INSSTD_ADDSTD<<6 | INSTL_8<<4 | ADDRL_24),QSPI_S0EN);
	csp_qspi_en(QSPI);
	for(uint8_t i=0;i<6;i++)
	{
		csi_qspi_waitflag(QSPI,QSPI_TFNF,0x01,0xffff);
		csp_qspi_write_data(QSPI,bySend[i]);
	}

	csi_qspi_waitflag(QSPI,QSPI_TFE,0x01,0xffff);
	
	for(uint8_t j=0;j<6;j++)
	{
		csi_qspi_waitflag(QSPI,QSPI_RFNE,0x01,0xffff);
		byRecv[j] = csp_qspi_read_data(QSPI);
	}
	
	wId = ((byRecv[4] << 8) |  byRecv[5]);
	return wId;
}

/** \brief qspi flash write enable 
 * 
 *  \param[in] none
 *  \return none
 */
void w25qxx_write_enable(void)
{
	uint8_t bySend = WREN_CMD; //command 0x06
	csi_qspi_set_cmd(QSPI,QSPI_SEND,QSPI_SPIFRF_STD,(QSPI_INSSTD_ADDSTD<<6 | INSTL_8<<4 | ADDRL_NONE),QSPI_S0EN);
	csp_qspi_en(QSPI);
	
	csi_qspi_waitflag(QSPI,QSPI_TFNF,0x01,0xffff);
	csp_qspi_write_data(QSPI,bySend);
	csi_qspi_waitflag(QSPI,QSPI_TFE,0x01,0xffff);
	csi_qspi_waitflag(QSPI,QSPI_BSY,0x00,0xffff);
}

/** \brief flash wait idle
 * 
 *  \param[in] none
 *  \return none
 */
void w25qxx_qspi_wait_busy(void)
{
	while((w25qxx_read_register(REG1) & 0x01) == 0x01);	// 1: busy, 0: idle
}

/** \brief qspi flash write enable 
 * 
 *  \param[in] byData1:register1 data
*   \param[in] byData2:register2 data
 *  \return none
 */
void w25qxx_write_register(uint8_t byData1,uint8_t byData2)
{
	uint8_t bySend[3] = {WRSR_CMD,0x00,0x02}; //command 0x01
	//w25qxx_write_enable();
	
	bySend[1] = byData1;
	bySend[2] = byData2;
	
	csi_qspi_set_cmd(QSPI,QSPI_SEND,QSPI_SPIFRF_STD,(QSPI_INSSTD_ADDSTD<<6 | INSTL_8<<4 | ADDRL_NONE),QSPI_S0EN);
	csp_qspi_en(QSPI);
	
	for(uint8_t i=0;i<3;i++)
	{
		csi_qspi_waitflag(QSPI,QSPI_TFNF,0x01,0xffff);
		csp_qspi_write_data(QSPI,bySend[i]);
	}
	csi_qspi_waitflag(QSPI,QSPI_TFE,0x01,0xffff);
	csi_qspi_waitflag(QSPI,QSPI_BSY,0x00,0xffff);
	w25qxx_qspi_wait_busy();
}

/** \brief w25qxx flash (qspi enable)
 * 
 *  \param[in] none
 *  \return none
 */
void w25qxx_qspi_enable(void)
{
	uint8_t byReg2;
	byReg2 = w25qxx_read_register(REG2);	
	if((byReg2 & 0x02)==0)			
	{ 
		w25qxx_write_enable();
		byReg2|=1<<1;					
		w25qxx_write_register(0x00,byReg2);
	}	
}

/** \briefw25qxx flash  (sector erase,sector = 4k bytes)
 * 
 *  \param[in] wSector: which sector you want to erase(w25q80:0-255)
 *  \return none
 */
void w25qxx_qspi_sector_erase(uint32_t wSector)
{		
	uint32_t wAddr = wSector * 4096;
	wAddr = wAddr & 0xfff000;
	uint8_t bySend[4] = {SECTORERASE_CMD, (wAddr >> 16), (wAddr >> 8), wAddr};
	w25qxx_write_enable();		//write enable
	w25qxx_qspi_wait_busy();
	
	csi_qspi_set_cmd(QSPI,QSPI_SEND,QSPI_SPIFRF_STD,(QSPI_INSSTD_ADDSTD<<6 | INSTL_8<<4 | ADDRL_NONE),QSPI_S0EN);
	csp_qspi_en(QSPI);
	
	for(uint8_t i=0;i<4;i++)
	{
		csi_qspi_waitflag(QSPI,QSPI_TFNF,0x01,0xffff);
		csp_qspi_write_data(QSPI,bySend[i]);
	}
	csi_qspi_waitflag(QSPI,QSPI_TFE,0x01,0xffff);
	csi_qspi_waitflag(QSPI,QSPI_BSY,0x00,0xffff);
	w25qxx_qspi_wait_busy();
}

/** \brief w25qxx flash (write page)
 * 
 *  \param[in] pbySend: pointer of write data buf 
 *  \param[in] wAddr: start addr of write data (qspi在一页（0-4095），写入少于256个字节的数据)
 *  \param[in] hwLen: length of write data(0-256)
 *  \return none
 */
void w25qxx_qspi_write_page(uint8_t *pbySend, uint32_t wAddr, uint16_t hwLen)
{	
	//w25qxx_write_enable();
	
	csi_qspi_set_cmd(QSPI,QSPI_SEND,QSPI_SPIFRF_TWO,(QSPI_INSSTD_ADDSTD<<6 | INSTL_8<<4 | ADDRL_24),QSPI_S0EN);
	csi_qspi_send(QSPI,FPGPRO_CMD,wAddr,pbySend,hwLen);
	
	w25qxx_qspi_wait_busy();
}


/** \brief w25qxx flash (read)
 * 
 *  \param[in] pbyBuf: pointer of read data buf 
 *  \param[in] wAddr: start addr of read data
 *  \param[in] hwNum: length of read data
 *  \return none
 */
void w25qxx_qspi_read(uint8_t *pbyBuf, uint32_t wAddr, uint16_t hwNum)
{
//1线读（指令和地址用标准SPI，数据用标准SPI）	
//	csi_qspi_set_cmd(QSPI,QSPI_RECV,QSPI_FRF_STD,(QSPI_INSSTD_ADDSTD<<6 | INSTL_8<<4 | ADDRL_24),QSPI_S0EN);//指针，接收模式，数据1线spi格式，指令标准spi，地址标准spi，指令长度8，地址长度24
//	csi_qspi_set_waitcycle(QSPI,8);                 		//等待周期设置为8	
//	csi_qspi_receive(QSPI,FREAD_CMD,(wAddr << 8) | 0xff,pbyBuf,hwNum);   //QSPI指针，指令，地址，接收buff，接收长度	
	
//	uint8_t bySend[261] = {FREAD_CMD, (wAddr >> 16), (wAddr >> 8), wAddr,0XFF};
//	w25qxx_write_enable();		//write enable
//	w25qxx_qspi_wait_busy();
//	
//	csi_qspi_set_cmd(QSPI,QSPI_SEND_RECV,QSPI_FRF_STD,(QSPI_INSSTD_ADDSTD<<6 | INSTL_8<<4 | ADDRL_8),QSPI_S0EN);
//	csp_qspi_en(QSPI);
//	
//	for(uint16_t i=0;i<5;i++)
//	{
//		csi_qspi_waitflag(QSPI,QSPI_TNF,0x01,0xffff);
//		csp_qspi_write_data(QSPI,bySend[i]);
//		//csi_qspi_waitflag(QSPI,QSPI_RNE,0x01,0xffff);
//		nop;nop;nop;nop;nop;
//		bySend[i] = csp_qspi_read_data(QSPI);
//	}
//	
//	csi_qspi_waitflag(QSPI,QSPI_TFE,0x01,0xffff);
//	
//	for(uint16_t i=0;i<hwNum;i++)
//	{
//		csi_qspi_waitflag(QSPI,QSPI_TNF,0x01,0xffff);
//		csp_qspi_write_data(QSPI,0xff);
//		//csi_qspi_waitflag(QSPI,QSPI_RNE,0x01,0xffff);
//		*pbyBuf++ = csp_qspi_read_data(QSPI);
//	}
//	csi_qspi_waitflag(QSPI,QSPI_TFE,0x01,0xffff);
//	csi_qspi_waitflag(QSPI,QSPI_BSY,0x00,0xffff);
//	w25qxx_qspi_wait_busy();
	
	

	
//2线读（指令和地址用标准SPI，数据用二线）	
//	csi_qspi_set_cmd(QSPI,QSPI_RECV,QSPI_FRF_TWO,(QSPI_INSSTD_ADDSTD<<6 | INSTL_8<<4 | ADDRL_24),QSPI_S0EN);//指针，接收模式，数据2线spi格式，指令标准spi，地址标准spi，指令长度8，地址长度24
//	csi_qspi_set_waitcycle(QSPI,8);                 		//等待周期设置为8	
//	csi_qspi_receive(QSPI,FDREAD_CMD,wAddr,pbyBuf,hwNum);   //QSPI指针，指令，地址，接收buff，接收长度

//4线读（指令和地址用标准SPI，数据用四线）	
	csi_qspi_set_cmd(QSPI,QSPI_RECV,QSPI_SPIFRF_TWO,(QSPI_INSSTD_ADDSTD<<6 | INSTL_8<<4 | ADDRL_24),QSPI_S0EN);//指针，接收模式，数据4线spi格式，指令标准spi，地址标准spi，指令长度8，地址长度24
	csi_qspi_set_waitcycle(QSPI,8);                 		//等待周期设置为8	
	csi_qspi_receive(QSPI,FQREAD_CMD,wAddr,pbyBuf,hwNum);   //QSPI指针，指令，地址，接收buff，接收长度
	
//4线读（指令用标准SPI，地址和数据用四线），注意：本来在W25Q80中地址是24位，但是FQREADIO_CMD这条指令有M7-M0,合在一起正好32位，结合时序图看直观一点
//	csi_qspi_set_cmd(QSPI,QSPI_RECV,QSPI_FRF_FOUR,(QSPI_INSSTD_ADDSTDX<<6 | INSTL_8<<4 | ADDRL_32),QSPI_S0EN);//指针，接收模式，数据4线帧格式，指令标准spi，地址4线，指令长度8，地址长度32
//	csi_qspi_set_waitcycle(QSPI,4);                 		//等待周期设置为4	
//	csi_qspi_receive(QSPI, FQREADIO_CMD,(wAddr << 8) | 0xff ,pbyBuf,hwNum);   //QSPI指针，指令，地址，接收buff，接收长度
}

/** \brief test read id 
 * 
 *  \param[in] none
 *  \return chip id (chip id = 0xef13)
 */
uint32_t qspi_flash_demo1(void)
{
	volatile uint32_t wId1 = 0x0000;	
	volatile uint32_t wId2 = 0x0000;
	volatile uint32_t wId3 = 0x0000;
	uint8_t byReceive2[6];
	uint8_t byReceive3[6];
	
	csi_qspi_config_t t_QspiConfig;
	
	t_QspiConfig.byInter              = QSPI_NONE_INT;//QSPI_TXE_INT | QSPI_TXO_INT | QSPI_RXU_INT | QSPI_RXO_INT | QSPI_RXF_INT | QSPI_MST_INT; //无中断
	t_QspiConfig.byRxFifoLevel        = 0x05;             //接收fifo中断阈值4，大于等于4个，触发接收中断
	t_QspiConfig.byTxFifoLevel 	      = 0x04;             //发送fifo中断阈值4，小于等于4个，触发发送中断
	t_QspiConfig.dwQspiBaud           = 2000000;          //传输速率
	t_QspiConfig.eQspiFrameLen        = QSPI_DFS_8;       //数据帧8bit
	t_QspiConfig.eQspiPolarityPhase   = QSPI_SPO0_SPH0;   //时钟极性为0，相位为0	
	csi_qspi_init(QSPI,&t_QspiConfig);
	
	//标准读id
//	wId1 = w25qxx_read_id();
//	printf("ID1:0x%04x\n",wId1);

	//两线读id
	csi_qspi_set_cmd(QSPI,QSPI_RECV,QSPI_SPIFRF_TWO,(QSPI_INSSTD_ADDSTDX<<6 | INSTL_8<<4 | ADDRL_24),QSPI_S0EN);
	csi_qspi_set_waitcycle(QSPI,4);//等待周期设置为4
	//csp_qspi_set_rsd(QSPI,0);	
	csi_qspi_receive(QSPI,DFRDDEVICEID_CMD,0x000000,byReceive2,100);//QSPI指针，指令，地址，接收buff，接收长度
	wId2 = ((byReceive2[0] << 8) |  byReceive2[1]);
	printf("ID2:0x%04lx\n",wId2);
	
	//四线读id
//	w25qxx_qspi_enable();//使能flash的四线模式
//	csi_qspi_set_cmd(QSPI,QSPI_RECV,QSPI_SPIFRF_FOUR,(QSPI_INSSTD_ADDSTDX<<6 | INSTL_8<<4 | ADDRL_24),QSPI_S0EN);
//	csi_qspi_set_waitcycle(QSPI,6);//等待周期设置为6	
//	csi_qspi_receive(QSPI,QFRDDEVICEID_CMD,0x000000,byReceive3,6);//QSPI指针，指令，地址，接收buff，接收长度
//	wId3 = ((byReceive3[0] << 8) |  byReceive3[1]);
//	printf("ID3:0x%04x\n",wId3);
	
 	nop;
	
	return (wId1 + wId2 + wId3)/3;
}



uint32_t qspi_flash_demo2(void)
{
	volatile uint32_t wId1 = 0x0000;
	uint8_t bysend[256];
	uint8_t byReceive[256];
	
	for(uint16_t i=0;i<256;i++)
	{
		bysend[i]=i;
	}
	
	csi_qspi_config_t t_QspiConfig;
	t_QspiConfig.byInter = QSPI_NONE_INT; //无中断
	t_QspiConfig.byRxFifoLevel = 0x04;    //接收fifo中断阈值4，大于等于4个，触发接收中断
	t_QspiConfig.byTxFifoLevel = 0x04;    //发送fifo中断阈值4，小于等于4个，触发发送中断
	t_QspiConfig.dwQspiBaud = 500000;    //传输速率
	t_QspiConfig.eQspiFrameLen = QSPI_DFS_8;  //数据8bit
	t_QspiConfig.eQspiPolarityPhase = QSPI_SPO0_SPH0; //时钟极性为0，相位为0
	
	csi_qspi_init(QSPI,&t_QspiConfig);
	
	//w25qxx_qspi_enable();//使能flash的四线模式
//	w25qxx_read_register(REG2);
//	wId1 = w25qxx_read_id();//标准读id
	
	//w25qxx_qspi_sector_erase(0x00);//擦除第一个扇区
	//w25qxx_qspi_read(byReceive, 0*0x1000+0x00,256);//读第一个扇区的第一页
	
	w25qxx_qspi_write_page(bysend, 0*0x1000,256 );
	w25qxx_qspi_read(byReceive, 0*0x1000+0x00,256);//读第一个扇区的第一页
	
	while(1)
	{
		nop;
		w25qxx_qspi_read(byReceive, 0*0x1000+0x00,256);//读第一个扇区第一页
	}
	
	
	return wId1;
	
}

//qspi dma test
//qspi_etcb_dma send
void qspi_etcb_dma_send(void)
{
	uint32_t bySdData[100]={0x5A};

	csi_dma_ch_config_t tDmaConfig;		//DMA 配置初始化
	csi_etb_config_t 	tEtbConfig;		//ETB 参数配置结构体	
	csi_qspi_config_t t_QspiConfig;  	//spi初始化参数配置结构体
	
//	for(uint8_t i=0;i<100;i++)
//	{
//		bySdData[i] = i+1;
//	}
	
	//dma para config
	tDmaConfig.bySrcLinc 	= DMA_ADDR_INC;				//低位传输原地址自增
	tDmaConfig.bySrcHinc 	= DMA_ADDR_CONSTANT;		//高位传输原地址固定不变
	tDmaConfig.byDetLinc 	= DMA_ADDR_CONSTANT;		//低位传输目标地址固定不变
	tDmaConfig.byDetHinc 	= DMA_ADDR_CONSTANT;		//高位传输目标地址固定不变
	tDmaConfig.byDataWidth 	= DMA_DSIZE_8_BITS;		//传输数据宽度8bit
	tDmaConfig.byReload 	= DMA_RELOAD_DISABLE;		//禁止自动重载
	tDmaConfig.byTransMode 	= DMA_TRANS_ONCE;			//DMA服务模式(传输模式)，单次服务
	tDmaConfig.byTsizeMode  = DMA_TSIZE_ONE_DSIZE;		//传输数据大小，一个 DSIZE , 即DSIZE定义大小
	tDmaConfig.byReqMode	= DMA_REQ_HARDWARE;			//DMA请求模式，硬件请求（软件触发）
	tDmaConfig.wInt		    = DMA_INTSRC_TCIT;			//不使用中断
	
	//etcb para config
	tEtbConfig.byChType = ETB_ONE_TRG_ONE_DMA;			//单个源触发单个目标，DMA方式
	tEtbConfig.bySrcIp 	= ETB_QSPI_TXSRC;				//QSPI TXSRC作为触发源
	tEtbConfig.bySrcIp1 = 0xff;						
	tEtbConfig.bySrcIp2 = 0xff;
	tEtbConfig.byDstIp 	= ETB_DMA0_CH0;					//ETB DMA0通道0作为目标实际
	tEtbConfig.byDstIp1 = 0xff;
	tEtbConfig.byDstIp2 = 0xff;
	tEtbConfig.byTrgMode = ETB_HARDWARE_TRG;			//通道触发模式采样硬件触发
	
	//qspi para config
	t_QspiConfig.byInter = QSPI_TXE_INT; 		//发送空
	t_QspiConfig.byRxFifoLevel = 0x08;    		//接收fifo中断阈值4，大于等于4个，触发接收中断
	t_QspiConfig.byTxFifoLevel = 0x08;    		//发送fifo中断阈值15，小于等于15个，触发发送中断
	t_QspiConfig.dwQspiBaud = 1000000;    		//传输速率
	t_QspiConfig.eQspiFrameLen = QSPI_DFS_8;    //数据8bit
	t_QspiConfig.hwDataFrameNumber    = 0x64;             //数据帧数20
	t_QspiConfig.eQspiPolarityPhase = QSPI_SPO0_SPH0; //时钟极性为0，相位为0
	
	csi_etb_init();										//使能ETB模块
	csi_etb_ch_config(ETB_CH20, &tEtbConfig);		//初始化ETB，DMA ETB CHANNEL > ETB_CH19_ID
	
	csi_dma_soft_rst(DMA0);
	csi_dma_ch_init(DMA0, 0, &tDmaConfig);				//初始化DMA
	
	csi_qspi_init(QSPI,&t_QspiConfig);					//初始化并启动qspi
	csi_vic_set_prio(QSPI_IRQn,0);
	csi_qspi_set_cmd(QSPI,QSPI_SEND,QSPI_SPIFRF_FOUR,(QSPI_INSSTD_ADDSTD<<6 | INSTL_8<<4 | ADDRL_24),QSPI_S0EN);
	
	//csp_qspi_en(QSPI);
	csi_qspi_send_dma(QSPI,(void *)bySdData,100,DMA0, 0);//发送20个数据，使用DMA0的通道0
	csi_vic_set_prio(DMA0_IRQn,10);
	csp_qspi_en(QSPI);
	//ETCB->SOFTTRIG = 0X00100000;
	while(csp_qspi_get_sr(QSPI) & QSPI_BSY );		//wait for transmition finish
	//while(DMA0->MTRX & 0x02);
	nop;
	
	while(1)
	{
		mdelay(100);
		//csi_irq_enable((uint32_t *)QSPI);
		
		csi_qspi_send_dma(QSPI,(void *)bySdData,100,DMA0, 0);//发送100个数据，使用DMA0的通道0
		csp_qspi_set_int(QSPI, QSPI_TXE_INT,true);
		
		while(csp_qspi_get_sr(QSPI) & QSPI_BSY );	//wait for transmition finish
		printf("DMA send over!\n");
		nop;
	}

}

//qspi_etcb_dma send
void qspi_etcb_dma_receive(void)
{	
	uint8_t byChnl = 0;
	volatile uint8_t byData = 0;
	volatile uint8_t byDesBuf[100] = {2};
	csi_dma_ch_config_t tDmaConfig;
	csi_qspi_config_t 	t_QspiConfig;   //spi初始化参数配置结构体
	csi_etb_config_t 	tEtbConfig;		//ETB 参数配置结构体	
	
	//receive dma para config
	tDmaConfig.bySrcLinc 	= DMA_ADDR_CONSTANT;		//低位传输原地址固定不变
	tDmaConfig.bySrcHinc 	= DMA_ADDR_CONSTANT;		//高位传输原地址固定不变
	tDmaConfig.byDetLinc 	= DMA_ADDR_INC;				//低位传输目标地址固定不变
	tDmaConfig.byDetHinc 	= DMA_ADDR_CONSTANT;		//高位传输目标地址固定不变
	tDmaConfig.byDataWidth  = DMA_DSIZE_8_BITS;			//传输数据宽度8bit
	tDmaConfig.byReload 	= DMA_RELOAD_DISABLE;		//禁止自动重载
	tDmaConfig.byTransMode  = DMA_TRANS_ONCE;			//DMA服务模式(传输模式)，连续服务
	tDmaConfig.byTsizeMode  = DMA_TSIZE_ONE_DSIZE;		//传输数据大小，一个 DSIZE , 即DSIZE定义大小
	tDmaConfig.byReqMode	= DMA_REQ_HARDWARE;			//DMA请求模式，硬件请求
	tDmaConfig.wInt		= DMA_INTSRC_NONE;			//不使用中断
	

	//receive etcb para config
	tEtbConfig.byChType = ETB_ONE_TRG_ONE_DMA;			//单个源触发单个目标，DMA方式
	tEtbConfig.bySrcIp 	= ETB_QSPI_RXSRC;				//SPI0 RXSRC作为触发源
	tEtbConfig.bySrcIp1 = 0xff;						
	tEtbConfig.bySrcIp2 = 0xff;
	tEtbConfig.byDstIp 	= ETB_DMA0_CH0;					//ETB DMA0通道0作为目标实际
	tEtbConfig.byDstIp1 = 0xff;
	tEtbConfig.byDstIp2 = 0xff;
	tEtbConfig.byTrgMode =  ETB_SOFTWARE_TRG;			//通道触发模式采样硬件触发
	
	//qspi para config
	t_QspiConfig.byInter = QSPI_NONE_INT; 		//无中断
	t_QspiConfig.byRxFifoLevel = 0x04;    		//接收fifo中断阈值4，大于等于4个，触发接收中断
	t_QspiConfig.byTxFifoLevel = 0x04;    		//发送fifo中断阈值4，小于等于4个，触发发送中断
	t_QspiConfig.dwQspiBaud = 1000000;    		//传输速率
	t_QspiConfig.eQspiFrameLen = QSPI_DFS_8;    //数据8bit
	t_QspiConfig.eQspiPolarityPhase = QSPI_SPO0_SPH0; //时钟极性为0，相位为0  
	
	
	csi_etb_init();										//使能ETB模块
	csi_etb_ch_config(ETB_CH20, &tEtbConfig);		//初始化ETB，DMA ETB CHANNEL > ETB_CH19_ID
	
	csi_dma_soft_rst(DMA0);
	csi_dma_ch_init(DMA0, byChnl, &tDmaConfig);
	
	csi_qspi_init(QSPI,&t_QspiConfig);					//初始化并启动spi
	csi_qspi_dma_receive_init(QSPI,100,FQREAD_CMD,0x000000);
	
	//byData = QSPI->DRx[0];
	csi_qspi_recv_dma(QSPI,(void *)byDesBuf,100,DMA0, 0);
	
	
	while( !(QSPI->SR & QSPI_TFE) );
	//while( !(QSPI->SR & QSPI_RNE) );
	while( (QSPI->SR & QSPI_BSY) );
	nop;
	while(1)
	{
		ETCB->SOFTTRIG = 0X00100000;
		//mdelay(10);
		//csi_qspi_recv_dma(QSPI,(void *)byDesBuf,100,DMA0, 0);
		//byData = QSPI->DRx[0];
		byData=byData+1;
		if(100 == byData)
		{
			nop;
		}
		
	}

}