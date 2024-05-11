#include "GBK_Unicode.h"
#include <string.h>


//��GBK-Unicode���
unsigned int unigbk_open(unsigned int GBK_Code)
{
	//����GBK����
	for (unsigned long i=0;i< 43586;i+=2)
	{
		if (GBK_Code== oem2uni936[i])
		{
			return oem2uni936[i+1];
		}
	}
	return 0;
}

//���ַ�GBK����Unicodeת��
unsigned int onGBK2Unicode(unsigned int GBK_Code)
{
	if (GBK_Code<0x80)/* ASCII */
	{
		return GBK_Code;//����Ҫת��
	}
	else
	{
		return unigbk_open(GBK_Code);//ת����Unicode����
	}
	return 0;
}
//�ַ���GBK����Unicodeת��
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







