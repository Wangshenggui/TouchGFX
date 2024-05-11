#ifndef _SDRAM_H
#define _SDRAM_H
#include "sys.h"
#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

	//////////////////////////////////////////////////////////////////////////////////	 
	//本程序只供学习使用，未经作者许可，不得用于其它任何用途
	//ALIENTEK STM32H7开发板
	//SDRAM 驱动代码	   
	//正点原子@ALIENTEK
	//技术论坛:www.openedv.com
	//创建日期:2019/4/21
	//版本：V1.1
	//版权所有，盗版必究。
	//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
	//All rights reserved									  
	//********************************************************************************
	//修改说明
	//20190524 V1.1
	//修改CAS为2,提高SDRAM访问性能
	//////////////////////////////////////////////////////////////////////////////////  


#define Bank5_SDRAM_ADDR    ((u32)(0XC0000000)) 			//SDRAM开始地址
#define SDRAM_START_ADDR		Bank5_SDRAM_ADDR

//	u8 SDRAM_Send_Cmd(u8 bankx, u8 cmd, u8 refresh, u16 regval);
	void SDRAM_Init(void);
	void FMC_SDRAM_WriteBuffer(u8* pBuffer, u32 WriteAddr, u32 n);
	void FMC_SDRAM_ReadBuffer(u8* pBuffer, u32 ReadAddr, u32 n);

#ifdef __cplusplus
}
#endif

#endif



































