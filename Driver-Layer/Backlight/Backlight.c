#include "Backlight.h"
#include "24cxx.h"

#include "ff.h"
#include "myFatFs.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//设置背光亮度
void SetBacklight(uint16_t pwm)
{
    TIM3->CCR2 = 693 - pwm;
}

//裁剪字符串
static char* substring(char* dst, char* src, int start, int len)
{
    int length = 100;//最大长度
    if (start >= length || start < 0)
        return NULL;
    if (len > length)
        len = length - start;
    src += start;
    while (len--)
    {
        *(dst++) = *(src++);
    }
    *(dst++) = '\0';
    return dst;
}

//保存背光亮度
void SaveBacklight(uint16_t pwm)
{
    TIM3->CCR2 = 693 - pwm;

    f_open(&FIL_GlobalVariableStruct.file, (char*)"1:Backlight.ini", FA_WRITE);
    /* 追加到文件的结尾 */
    f_lseek(&FIL_GlobalVariableStruct.file, f_size(&FIL_GlobalVariableStruct.file));
    f_printf(&FIL_GlobalVariableStruct.file, "<%04d-%02d-%02d %02d:%02d:%02d> 背光亮度 : %03d\r\n", \
        2024, 2, 21, \
        11, 16, 45, \
        (693 - pwm) / 10
    );
    /* 关闭文件 */
    f_close(&FIL_GlobalVariableStruct.file);
}


//获取背光亮度
uint16_t GetBacklight(void)
{
    uint8_t temp;

    f_open(&FIL_GlobalVariableStruct.file, (char*)"1:Backlight.ini", FA_READ);

    char read_buff[50];
    char dst[10];

    f_lseek(&FIL_GlobalVariableStruct.file, f_size(&FIL_GlobalVariableStruct.file) - 38);

    f_read(&FIL_GlobalVariableStruct.file, read_buff, sizeof read_buff, NULL);

    for (uint8_t i = 0; i < 34 - 2; i++)
    {
        if (read_buff[i] == ' ' && read_buff[i + 1] == ':' && read_buff[i + 2] == ' ')
        {
            substring(dst, read_buff, i + 3, 3);
            temp = atoi((const char*)dst);
        }
    }

    /* 关闭文件 */
    f_close(&FIL_GlobalVariableStruct.file);

    return 693 - temp * 10;
}




