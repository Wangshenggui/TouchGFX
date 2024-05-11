#include "myFatFs.h"
#include <string.h>
#include <stdio.h>

#include "ff.h"



FIL_GlobalVariableStructure FIL_GlobalVariableStruct;

FATFS fatsd; //定义文件系统对象结构
FRESULT scan_files(char path[])
{
	FRESULT res; //定义结果对象
	DIR dir; //定义目录对象
	//	UINT i; //定义变量
	static FILINFO fno; //定义静态文件信息结构对象
	res = f_opendir(&dir, path); //打开目录，返回状态 和 目录对象的指针
	//	char pathBuff[256]; //定义路径数组
	if (res == FR_OK) //打开成功
	{
		for (;;) //遍历
		{
			res = f_readdir(&dir, &fno); //读取目录，返回状态 和 文件信息的指针
			if (res != FR_OK || fno.fname[0] == 0)
			{
				break; //若打开失败 或 到结尾，则退出
			}
			if (fno.fattrib & AM_DIR) //是目录
			{
				//				printf("             %s\r\n",path);
			}
			else
			{
				//				printf("-------------%s/%s\r\n",path,fno.fname); //是文件
			}
		}
	}
	else
	{
		//		printf("失败 - %s\r\n",&res); //打开失败
	}
	f_closedir(&dir); //关闭目录
	return res; //返回状态
}














