#ifndef __MYCT_IIC_H
#define __MYCT_IIC_H
#include "sys.h"

#ifdef __cplusplus
extern "C" {
#endif

	//////////////////////////////////////////////////////////////////////////////////	 
	//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
	//ALIENTEK STM32H7������
	//���ݴ�����-IIC ��������	   
	//����ԭ��@ALIENTEK
	//������̳:www.openedv.com
	//��������:2019/5/5
	//�汾��V1.0
	//��Ȩ���У�����ؾ���
	//Copyright(C) �������������ӿƼ����޹�˾ 2014-2024
	//All rights reserved									  
	//********************************************************************************
	//����˵�� 
	//��
	////////////////////////////////////////////////////////////////////////////////// 	

	//IO��������
#define CT_SDA_IN()  {GPIOG->MODER&=~(3<<(2*7));GPIOG->MODER|=0<<2*7;}	//PF11����ģʽ
#define CT_SDA_OUT() {GPIOG->MODER&=~(3<<(2*7));GPIOG->MODER|=1<<2*7;} 	//PF11���ģʽ
//IO��������	 
#define CT_IIC_SCL(x)    GPIO_Pin_Set(GPIOH,PIN6,x)		//SCL
#define CT_IIC_SDA(x)    GPIO_Pin_Set(GPIOG,PIN7,x)		//SDA	 
#define CT_READ_SDA		 GPIO_Pin_Get(GPIOG,PIN7)  		//����SDA 


//IIC���в�������
	void CT_IIC_Init(void);                	//��ʼ��IIC��IO��				 
	void CT_IIC_Start(void);				//����IIC��ʼ�ź�
	void CT_IIC_Stop(void);	  				//����IICֹͣ�ź�
	void CT_IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
	u8 CT_IIC_Read_Byte(unsigned char ack);	//IIC��ȡһ���ֽ�
	u8 CT_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
	void CT_IIC_Ack(void);					//IIC����ACK�ź�
	void CT_IIC_NAck(void);					//IIC������ACK�ź�

#ifdef __cplusplus
}
#endif

#endif






