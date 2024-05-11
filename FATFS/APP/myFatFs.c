#include "myFatFs.h"
#include <string.h>
#include <stdio.h>

#include "ff.h"



FIL_GlobalVariableStructure FIL_GlobalVariableStruct;

FATFS fatsd; //�����ļ�ϵͳ����ṹ
FRESULT scan_files(char path[])
{
	FRESULT res; //����������
	DIR dir; //����Ŀ¼����
	//	UINT i; //�������
	static FILINFO fno; //���徲̬�ļ���Ϣ�ṹ����
	res = f_opendir(&dir, path); //��Ŀ¼������״̬ �� Ŀ¼�����ָ��
	//	char pathBuff[256]; //����·������
	if (res == FR_OK) //�򿪳ɹ�
	{
		for (;;) //����
		{
			res = f_readdir(&dir, &fno); //��ȡĿ¼������״̬ �� �ļ���Ϣ��ָ��
			if (res != FR_OK || fno.fname[0] == 0)
			{
				break; //����ʧ�� �� ����β�����˳�
			}
			if (fno.fattrib & AM_DIR) //��Ŀ¼
			{
				//				printf("             %s\r\n",path);
			}
			else
			{
				//				printf("-------------%s/%s\r\n",path,fno.fname); //���ļ�
			}
		}
	}
	else
	{
		//		printf("ʧ�� - %s\r\n",&res); //��ʧ��
	}
	f_closedir(&dir); //�ر�Ŀ¼
	return res; //����״̬
}














