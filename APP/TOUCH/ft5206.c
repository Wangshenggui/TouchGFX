#include "ft5206.h"
#include "touch.h"
#include "ctiic.h"
//#include "usart.h"
#include "delay.h" 
#include "string.h" 
//#include "lcd.h"
#include "gt9147.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//7����ݴ�����-FT5206 ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/12/28
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

//��FT5206д��һ������
//reg:��ʼ�Ĵ�����ַ
//buf:���ݻ�������
//len:д���ݳ���
//����ֵ:0,�ɹ�;1,ʧ��.
u8 FT5206_WR_Reg(u16 reg, u8* buf, u8 len)
{
	u8 i;
	u8 ret = 0;
	CT_IIC_Start();
	CT_IIC_Send_Byte(FT_CMD_WR);	//����д���� 	 
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte(reg & 0XFF);   	//���͵�8λ��ַ
	CT_IIC_Wait_Ack();
	for (i = 0; i < len; i++)
	{
		CT_IIC_Send_Byte(buf[i]);  	//������
		ret = CT_IIC_Wait_Ack();
		if (ret)break;
	}
	CT_IIC_Stop();					//����һ��ֹͣ����	    
	return ret;
}
//��FT5206����һ������
//reg:��ʼ�Ĵ�����ַ
//buf:���ݻ�������
//len:�����ݳ���			  
void FT5206_RD_Reg(u16 reg, u8* buf, u8 len)
{
	u8 i;
	CT_IIC_Start();
	CT_IIC_Send_Byte(FT_CMD_WR);   	//����д���� 	 
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte(reg & 0XFF);   	//���͵�8λ��ַ
	CT_IIC_Wait_Ack();
	CT_IIC_Start();
	CT_IIC_Send_Byte(FT_CMD_RD);   	//���Ͷ�����		   
	CT_IIC_Wait_Ack();
	for (i = 0; i < len; i++)
	{
		buf[i] = CT_IIC_Read_Byte(i == (len - 1) ? 0 : 1); //������	  
	}
	CT_IIC_Stop();//����һ��ֹͣ����     
}
//��ʼ��FT5206������
//����ֵ:0,��ʼ���ɹ�;1,��ʼ��ʧ�� 
u8 FT5206_Init(void)
{
	u8 temp[5];
	u8 res = 1;
	GPIO_InitTypeDef GPIO_Initure;

	__HAL_RCC_GPIOH_CLK_ENABLE();			//����GPIOHʱ��
	__HAL_RCC_GPIOI_CLK_ENABLE();			//����GPIOIʱ��

	//PH7
	GPIO_Initure.Pin = GPIO_PIN_7;            //PH7
	GPIO_Initure.Mode = GPIO_MODE_INPUT;      //����
	GPIO_Initure.Pull = GPIO_PULLUP;          //����
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;     //����
	HAL_GPIO_Init(GPIOH, &GPIO_Initure);     //��ʼ��

	//PI8
	GPIO_Initure.Pin = GPIO_PIN_8;            //PI8
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;  //�������
	HAL_GPIO_Init(GPIOI, &GPIO_Initure);     //��ʼ��

	CT_IIC_Init();      	//��ʼ����������I2C����  
	FT_RST(0);				//��λ
	delay_ms(20);
	FT_RST(1);				//�ͷŸ�λ		    
	delay_ms(50);
	temp[0] = 0;
	//��ȡ�汾�ţ��ο�ֵ��0x3003
	FT5206_RD_Reg(FT_ID_G_LIB_VERSION, &temp[0], 2);
	if ((temp[0] == 0X30 && temp[1] == 0X03) || temp[1] == 0X01 || temp[1] == 0X02)//�汾:0X3003/0X0001/0X0002
	{
		//		printf("CTP ID:%x\r\n",((u16)temp[0]<<8)+temp[1]);
		FT5206_WR_Reg(FT_DEVIDE_MODE, temp, 1);	//������������ģʽ 
		FT5206_WR_Reg(FT_ID_G_MODE, temp, 1);		//��ѯģʽ 
		temp[0] = 22;								//������Чֵ��22��ԽСԽ����	
		FT5206_WR_Reg(FT_ID_G_THGROUP, temp, 1);	//���ô�����Чֵ
		temp[0] = 12;								//�������ڣ�����С��12�����14
		FT5206_WR_Reg(FT_ID_G_PERIODACTIVE, temp, 1);
		res = 0;
	}
	return res;
}

const u16 FT5206_TPX_TBL[5] = { FT_TP1_REG,FT_TP2_REG,FT_TP3_REG,FT_TP4_REG,FT_TP5_REG };
// ɨ��
uint8_t ft5206_scan(TouchTypedef* touch)
{
	uint8_t buf[4];
	uint8_t touch_num;
	//	uint8_t i = 0;
	//	uint8_t touch_state = 0;
	FT5206_RD_Reg(FT_REG_NUM_FINGER, &touch_num, 1);//��ȡ�������״̬  
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


