#ifndef _MYFATFS_H
#define _MYFATFS_H

#include "main.h"
#include "ff.h"




#ifdef __cplusplus
extern "C" {
#endif


	FRESULT scan_files(char path[]);
    
    typedef struct
    {
        FIL file;
        FATFS fatsd_FM; //�����ļ�ϵͳ����ṹ
        FRESULT res_FM; //����������
        DIR dir_FM; //����Ŀ¼����
        FILINFO fno_FM; //���徲̬�ļ���Ϣ�ṹ����
    }FIL_GlobalVariableStructure;
    extern FIL_GlobalVariableStructure FIL_GlobalVariableStruct;


#ifdef __cplusplus
}
#endif

#endif
