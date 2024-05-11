#include "GBK_Unicode.h"
#include <string.h>


//打开GBK-Unicode码表
unsigned int unigbk_open(unsigned int GBK_Code)
{
	//查找GBK编码
	for (unsigned long i=0;i< 43586;i+=2)
	{
		if (GBK_Code== oem2uni936[i])
		{
			return oem2uni936[i+1];
		}
	}
	return 0;
}

//单字符GBK——Unicode转换
unsigned int onGBK2Unicode(unsigned int GBK_Code)
{
	if (GBK_Code<0x80)/* ASCII */
	{
		return GBK_Code;//不需要转换
	}
	else
	{
		return unigbk_open(GBK_Code);//转换成Unicode编码
	}
	return 0;
}
//字符串GBK——Unicode转换
void StringGBK2Unicode(char str[],char *un_str)
{
	unsigned char len= strlen(str);
	for (unsigned char i=0;i<len;i++)
	{
		if (str[i] < 0x80)/* ASCII */
		{
			un_str[i] = str[i];
		}
		else
		{
			un_str[i] = unigbk_open(str[i]);
		}
	}
}







