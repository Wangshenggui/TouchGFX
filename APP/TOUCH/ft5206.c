#include "ft5206.h"
#include "touch.h"
#include "ctiic.h"
//#include "usart.h"
#include "delay.h" 
#include "string.h" 
//#include "lcd.h"
#include "gt9147.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//7寸电容触摸屏-FT5206 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/12/28
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

//向FT5206写入一次数据
//reg:起始寄存器地址
//buf:数据缓缓存区
//len:写数据长度
//返回值:0,成功;1,失败.
u8 FT5206_WR_Reg(u16 reg, u8* buf, u8 len)
{
	u8 i;
	u8 ret = 0;
	CT_IIC_Start();
	CT_IIC_Send_Byte(FT_CMD_WR);	//发送写命令 	 
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte(reg & 0XFF);   	//发送低8位地址
	CT_IIC_Wait_Ack();
	for (i = 0; i < len; i++)
	{
		CT_IIC_Send_Byte(buf[i]);  	//发数据
		ret = CT_IIC_Wait_Ack();
		if (ret)break;
	}
	CT_IIC_Stop();					//产生一个停止条件	    
	return ret;
}
//从FT5206读出一次数据
//reg:起始寄存器地址
//buf:数据缓缓存区
//len:读数据长度			  
void FT5206_RD_Reg(u16 reg, u8* buf, u8 len)
{
	u8 i;
	CT_IIC_Start();
	CT_IIC_Send_Byte(FT_CMD_WR);   	//发送写命令 	 
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte(reg & 0XFF);   	//发送低8位地址
	CT_IIC_Wait_Ack();
	CT_IIC_Start();
	CT_IIC_Send_Byte(FT_CMD_RD);   	//发送读命令		   
	CT_IIC_Wait_Ack();
	for (i = 0; i < len; i++)
	{
		buf[i] = CT_IIC_Read_Byte(i == (len - 1) ? 0 : 1); //发数据	  
	}
	CT_IIC_Stop();//产生一个停止条件     
}
//初始化FT5206触摸屏
//返回值:0,初始化成功;1,初始化失败 
u8 FT5206_Init(void)
{
	u8 temp[5];
	u8 res = 1;
	GPIO_InitTypeDef GPIO_Initure;

	__HAL_RCC_GPIOH_CLK_ENABLE();			//开启GPIOH时钟
	__HAL_RCC_GPIOI_CLK_ENABLE();			//开启GPIOI时钟

	//PH7
	GPIO_Initure.Pin = GPIO_PIN_7;            //PH7
	GPIO_Initure.Mode = GPIO_MODE_INPUT;      //输入
	GPIO_Initure.Pull = GPIO_PULLUP;          //上拉
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;     //高速
	HAL_GPIO_Init(GPIOH, &GPIO_Initure);     //初始化

	//PI8
	GPIO_Initure.Pin = GPIO_PIN_8;            //PI8
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;  //推挽输出
	HAL_GPIO_Init(GPIOI, &GPIO_Initure);     //初始化

	CT_IIC_Init();      	//初始化电容屏的I2C总线  
	FT_RST(0);				//复位
	delay_ms(20);
	FT_RST(1);				//释放复位		    
	delay_ms(50);
	temp[0] = 0;
	//读取版本号，参考值：0x3003
	FT5206_RD_Reg(FT_ID_G_LIB_VERSION, &temp[0], 2);
	if ((temp[0] == 0X30 && temp[1] == 0X03) || temp[1] == 0X01 || temp[1] == 0X02)//版本:0X3003/0X0001/0X0002
	{
		//		printf("CTP ID:%x\r\n",((u16)temp[0]<<8)+temp[1]);
		FT5206_WR_Reg(FT_DEVIDE_MODE, temp, 1);	//进入正常操作模式 
		FT5206_WR_Reg(FT_ID_G_MODE, temp, 1);		//查询模式 
		temp[0] = 22;								//触摸有效值，22，越小越灵敏	
		FT5206_WR_Reg(FT_ID_G_THGROUP, temp, 1);	//设置触摸有效值
		temp[0] = 12;								//激活周期，不能小于12，最大14
		FT5206_WR_Reg(FT_ID_G_PERIODACTIVE, temp, 1);
		res = 0;
	}
	return res;
}

const u16 FT5206_TPX_TBL[5] = { FT_TP1_REG,FT_TP2_REG,FT_TP3_REG,FT_TP4_REG,FT_TP5_REG };
// 扫描
uint8_t ft5206_scan(TouchTypedef* touch)
{
	uint8_t buf[4];
	uint8_t touch_num;
	//	uint8_t i = 0;
	//	uint8_t touch_state = 0;
	FT5206_RD_Reg(FT_REG_NUM_FINGER, &touch_num, 1);//读取触摸点的状态  
	touch->touch_num = touch_num;
	if ((touch_num & 0XF) && ((touch_num & 0XF) < 6))
	{
		for (int i = 0; i < touch_num; i++) {
			FT5206_RD_Reg(FT5206_TPX_TBL[i], buf, 4);
			uint16_t x = 0;
			uint16_t y = 0;

			if (touch->dir) {
				y = ((uint16_t)(buf[0] & 0X0F) << 8) + buf[1];
				x = ((uint16_t)(buf[2] & 0X0F) << 8) + buf[3];
			}
			else {
				x = touch->pix_h - (((uint16_t)(buf[0] & 0X0F) << 8) + buf[1]);
				y = ((uint16_t)(buf[2] & 0X0F) << 8) + buf[3];
			}
			touch->x[i] = x;
			touch->y[i] = y;
		}
       for (int i = touch_num; i < 5-touch_num; i++) {
			touch->x[i] = 0;
			touch->y[i] = 0;
		}
	}
	else {
		touch->touch_num = 0;
        for (int i = 0; i < 5; i++) {
			touch->x[i] = 0;
			touch->y[i] = 0;
		}
		return 0;
	}
	return touch_num;
}


