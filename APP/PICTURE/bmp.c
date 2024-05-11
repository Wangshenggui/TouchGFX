#include "bmp.h"
#include "ff.h"
#include <string.h>
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������ 
//ͼƬ���� ��������-bmp���벿��	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/1/7
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved
//********************************************************************************
//����˵�� 
//20160325 V1.1
//�޸�bmp_encode����,��֧��1024��ȵ�bmp����
//////////////////////////////////////////////////////////////////////////////////

//��ʹ���ڴ����

static FIL file;
//u8 bmpreadbuf[BMP_DBUF_SIZE];


//BMP���뺯��
//����ǰLCD��Ļ��ָ�������ͼ,��Ϊ16λ��ʽ��BMP�ļ� RGB565��ʽ.
//����Ϊrgb565����Ҫ����,��Ҫ����ԭ���ĵ�ɫ��λ����������.���������Ѿ�����������.
//����Ϊrgb555��ʽ����Ҫ��ɫת��,��ʱ��ȽϾ�,���Ա���Ϊ565������ٵİ취.
//filename:���·��
//x,y:����Ļ�ϵ���ʼ����  
//mode:ģʽ.0,�����������ļ��ķ�ʽ����;1,���֮ǰ�����ļ�,�򸲸�֮ǰ���ļ�.���û��,�򴴽��µ��ļ�.
//����ֵ:0,�ɹ�;����,������.  
u8 bmp_encode(u8* filename, u8* databuf, u16 width, u16 height, u8 mode)
{
	FIL* f_bmp = &file;
	u16 bmpheadsize;			//bmpͷ��С	   	
	BITMAPINFO hbmp;			//bmpͷ	 
	u8 res = 0;
	UINT bw;

	bmpheadsize = sizeof(hbmp);//�õ�bmp�ļ�ͷ�Ĵ�С   
	memset((u8*)&hbmp, 0, sizeof(hbmp));//��������뵽���ڴ�.	    
	hbmp.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);//��Ϣͷ��С
	hbmp.bmiHeader.biWidth = width;	 	//bmp�Ŀ��
	hbmp.bmiHeader.biHeight = height; 	//bmp�ĸ߶�
	hbmp.bmiHeader.biPlanes = 1;	 		//��Ϊ1
	hbmp.bmiHeader.biBitCount = 16;	 	//bmpΪ16λɫbmp
	hbmp.bmiHeader.biCompression = BI_BITFIELDS;//ÿ�����صı�����ָ�������������
	hbmp.bmiHeader.biSizeImage = hbmp.bmiHeader.biHeight * hbmp.bmiHeader.biWidth * hbmp.bmiHeader.biBitCount / 8;//bmp��������С

	hbmp.bmfHeader.bfType = ((u16)'M' << 8) + 'B';//BM��ʽ��־
	hbmp.bmfHeader.bfSize = bmpheadsize + hbmp.bmiHeader.biSizeImage;//����bmp�Ĵ�С
	hbmp.bmfHeader.bfOffBits = bmpheadsize;//����������ƫ��

	hbmp.RGB_MASK[0] = 0X00F800;	 		//��ɫ����
	hbmp.RGB_MASK[1] = 0X0007E0;	 		//��ɫ����
	hbmp.RGB_MASK[2] = 0X00001F;	 		//��ɫ����

	if (mode == 1)res = f_open(f_bmp, (const TCHAR*)filename, FA_READ | FA_WRITE);//���Դ�֮ǰ���ļ�
	if (mode == 0 || res == 0x04)res = f_open(f_bmp, (const TCHAR*)filename, FA_WRITE | FA_CREATE_NEW);//ģʽ0,���߳��Դ�ʧ��,�򴴽����ļ�		   

	if (res == FR_OK)//�����ɹ�
	{
		res = f_write(f_bmp, (u8*)&hbmp, bmpheadsize, &bw);//д��BMP�ײ�  
		if (!res)
			res = f_write(f_bmp, (u8*)databuf, width * height * 2, &bw);//д������

		f_close(f_bmp);
	}

	return res;
}



















