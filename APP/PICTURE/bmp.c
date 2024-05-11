#include "bmp.h"
#include "ff.h"
#include <string.h>
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板 
//图片解码 驱动代码-bmp解码部分	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2016/1/7
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved
//********************************************************************************
//升级说明 
//20160325 V1.1
//修改bmp_encode函数,以支持1024宽度的bmp编码
//////////////////////////////////////////////////////////////////////////////////

//不使用内存分配

static FIL file;
//u8 bmpreadbuf[BMP_DBUF_SIZE];


//BMP编码函数
//将当前LCD屏幕的指定区域截图,存为16位格式的BMP文件 RGB565格式.
//保存为rgb565则需要掩码,需要利用原来的调色板位置增加掩码.这里我们已经增加了掩码.
//保存为rgb555格式则需要颜色转换,耗时间比较久,所以保存为565是最快速的办法.
//filename:存放路径
//x,y:在屏幕上的起始坐标  
//mode:模式.0,仅仅创建新文件的方式编码;1,如果之前存在文件,则覆盖之前的文件.如果没有,则创建新的文件.
//返回值:0,成功;其他,错误码.  
u8 bmp_encode(u8* filename, u8* databuf, u16 width, u16 height, u8 mode)
{
	FIL* f_bmp = &file;
	u16 bmpheadsize;			//bmp头大小	   	
	BITMAPINFO hbmp;			//bmp头	 
	u8 res = 0;
	UINT bw;

	bmpheadsize = sizeof(hbmp);//得到bmp文件头的大小   
	memset((u8*)&hbmp, 0, sizeof(hbmp));//置零空申请到的内存.	    
	hbmp.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);//信息头大小
	hbmp.bmiHeader.biWidth = width;	 	//bmp的宽度
	hbmp.bmiHeader.biHeight = height; 	//bmp的高度
	hbmp.bmiHeader.biPlanes = 1;	 		//恒为1
	hbmp.bmiHeader.biBitCount = 16;	 	//bmp为16位色bmp
	hbmp.bmiHeader.biCompression = BI_BITFIELDS;//每个象素的比特由指定的掩码决定。
	hbmp.bmiHeader.biSizeImage = hbmp.bmiHeader.biHeight * hbmp.bmiHeader.biWidth * hbmp.bmiHeader.biBitCount / 8;//bmp数据区大小

	hbmp.bmfHeader.bfType = ((u16)'M' << 8) + 'B';//BM格式标志
	hbmp.bmfHeader.bfSize = bmpheadsize + hbmp.bmiHeader.biSizeImage;//整个bmp的大小
	hbmp.bmfHeader.bfOffBits = bmpheadsize;//到数据区的偏移

	hbmp.RGB_MASK[0] = 0X00F800;	 		//红色掩码
	hbmp.RGB_MASK[1] = 0X0007E0;	 		//绿色掩码
	hbmp.RGB_MASK[2] = 0X00001F;	 		//蓝色掩码

	if (mode == 1)res = f_open(f_bmp, (const TCHAR*)filename, FA_READ | FA_WRITE);//尝试打开之前的文件
	if (mode == 0 || res == 0x04)res = f_open(f_bmp, (const TCHAR*)filename, FA_WRITE | FA_CREATE_NEW);//模式0,或者尝试打开失败,则创建新文件		   

	if (res == FR_OK)//创建成功
	{
		res = f_write(f_bmp, (u8*)&hbmp, bmpheadsize, &bw);//写入BMP首部  
		if (!res)
			res = f_write(f_bmp, (u8*)databuf, width * height * 2, &bw);//写入数据

		f_close(f_bmp);
	}

	return res;
}



















