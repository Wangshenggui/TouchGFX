#include "ctiic.h"
#include "delay.h"	 
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

//����I2C�ٶȵ���ʱ
void CT_Delay(void)
{
	delay_us(1);
}
//���ݴ���оƬIIC�ӿڳ�ʼ��
void CT_IIC_Init(void)
{
	RCC->AHB4ENR |= 1 << 7;    		//ʹ��PORTHʱ��    
	RCC->AHB4ENR |= 1 << 6;    		//ʹ��PORTGʱ��  
	GPIO_Set(GPIOH, PIN6, GPIO_MODE_OUT, GPIO_OTYPE_PP, GPIO_SPEED_MID, GPIO_PUPD_PU); 	//PH6����Ϊ�������
	GPIO_Set(GPIOG, PIN7, GPIO_MODE_OUT, GPIO_OTYPE_PP, GPIO_SPEED_MID, GPIO_PUPD_PU); 	//PG7����Ϊ�������
	CT_IIC_SDA(1);
	CT_IIC_SCL(1);
}
//����IIC��ʼ�ź�
void CT_IIC_Start(void)
{
	CT_SDA_OUT();     //sda�����
	CT_IIC_SDA(1);
	CT_IIC_SCL(1);
	delay_us(30);
	CT_IIC_SDA(0);//START:when CLK is high,DATA change form high to low 
	CT_Delay();
	CT_IIC_SCL(0);//ǯסI2C���ߣ�׼�����ͻ�������� 
}
//����IICֹͣ�ź�
void CT_IIC_Stop(void)
{
	CT_SDA_OUT();//sda�����
	CT_IIC_SCL(0);
	CT_IIC_SDA(0);//STOP:when CLK is high DATA change form low to high
	delay_us(30);
	CT_IIC_SCL(1);
	CT_Delay();
	CT_IIC_SDA(1);//����I2C���߽����ź�  
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 CT_IIC_Wait_Ack(void)
{
	u8 ucErrTime = 0;
	CT_SDA_IN();      //SDA����Ϊ����  
	CT_IIC_SDA(1);
	CT_IIC_SCL(1);
	CT_Delay();
	while (CT_READ_SDA)
	{
		ucErrTime++;
		if (ucErrTime > 250)
		{
			CT_IIC_Stop();
			return 1;
		}
		CT_Delay();
	}
	CT_IIC_SCL(0);//ʱ�����0 	   
	return 0;
}
//����ACKӦ��
void CT_IIC_Ack(void)
{
	CT_IIC_SCL(0);
	CT_SDA_OUT();
	CT_IIC_SDA(0);
	CT_Delay();
	CT_IIC_SCL(1);
	CT_Delay();
	CT_IIC_SCL(0);
}
//������ACKӦ��		    
void CT_IIC_NAck(void)
{
	CT_IIC_SCL(0);
	CT_SDA_OUT();
	CT_IIC_SDA(1);
	CT_Delay();
	CT_IIC_SCL(1);
	CT_Delay();
	CT_IIC_SCL(0);
}
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void CT_IIC_Send_Byte(u8 txd)
{
	u8 t;
	CT_SDA_OUT();
	CT_IIC_SCL(0);//����ʱ�ӿ�ʼ���ݴ��� 
	for (t = 0; t < 8; t++)
	{
		CT_IIC_SDA((txd & 0x80) >> 7);
		txd <<= 1;
		CT_Delay();
		CT_IIC_SCL(1);
		CT_Delay();
		CT_IIC_SCL(0);
		CT_Delay();
	}
}
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 CT_IIC_Read_Byte(unsigned char ack)
{
	u8 i, receive = 0;
	CT_SDA_IN();//SDA����Ϊ���� 
	delay_us(30);
	for (i = 0; i < 8; i++)
	{
		CT_IIC_SCL(0);
		CT_Delay();
		CT_IIC_SCL(1);
		receive <<= 1;
		if (CT_READ_SDA)receive++;
		CT_Delay();
	}
	if (!ack)CT_IIC_NAck();//����nACK
	else CT_IIC_Ack(); //����ACK   
	return receive;
}



























