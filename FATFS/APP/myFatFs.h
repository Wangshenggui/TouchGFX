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
        FATFS fatsd_FM; //定义文件系统对象结构
        FRESULT res_FM; //定义结果对象
        DIR dir_FM; //定义目录对象
        FILINFO fno_FM; //定义静态文件信息结构对象
    }FIL_GlobalVariableStructure;
    extern FIL_GlobalVariableStructure FIL_GlobalVariableStruct;


#ifdef __cplusplus
}
#endif

#endif
