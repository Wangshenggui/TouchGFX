#include "Voice.h"
#include "24cxx.h"

#include "ff.h"
#include "myFatFs.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

VoiceRTxStructure VoiceRTxStru;


//播放语音，参数：曲目,最大歌曲（256首）
void VoicePlayback(uint8_t tracks)
{
    uint8_t Tx_buf[10];
    uint8_t verify;

    Tx_buf[0] = 0x7e;
    Tx_buf[1] = 0x05;
    Tx_buf[2] = 0x41;

    Tx_buf[3] = 0x00;
    Tx_buf[4] = tracks;

    //异或校验
    verify = Tx_buf[1] ^ Tx_buf[2] ^ Tx_buf[3] ^ Tx_buf[4];
    Tx_buf[5] = verify;

    Tx_buf[6] = 0xef;

    //发送音乐
    HAL_UART_Transmit(&huart6, Tx_buf, 7, 100);
}

//设置播放音量
void SetVoiceVolume(unsigned char volume)
{
    uint8_t Tx_buf[10];
    uint8_t verify;

    Tx_buf[0] = 0x7e;
    Tx_buf[1] = 0x04;
    Tx_buf[2] = 0x31;

    Tx_buf[3] = volume;

    //异或校验
    verify = Tx_buf[1] ^ Tx_buf[2] ^ Tx_buf[3];
    Tx_buf[4] = verify;
    Tx_buf[5] = 0xef;

    //发送命令
    HAL_UART_Transmit(&huart6, Tx_buf, 6, 100);
}


//保存播放音量
void SaveVoiceVolume(unsigned char volume)
{
    //保存音量

    f_open(&FIL_GlobalVariableStruct.file, (char*)"1:Voice.ini", FA_WRITE);
    /* 追加到文件的结尾 */
    f_lseek(&FIL_GlobalVariableStruct.file, f_size(&FIL_GlobalVariableStruct.file));
    f_printf(&FIL_GlobalVariableStruct.file, "<%04d-%02d-%02d %02d:%02d:%02d> 音量大小 : %03d\r\n", \
        2024, 2, 21, \
        11, 16, 45, \
        volume
    );
    /* 关闭文件 */
    f_close(&FIL_GlobalVariableStruct.file);
}


void Voice_Delay_us(uint16_t nus)
{
    while(nus--)
    {
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
    }
}

uint8_t QueryTx_buf[10]={0};
void VoiceQuery(uint8_t tracks)
{
//    const uint8_t QueryIndex[]={
//        0x20,0,0x21,0,0x22,0,0x23,0,0x24,0,
//        0x26,0,0x27,0,0x28,0,0x2a,0,0x2b,0,
//        0x2c,0,0x2d,0,0x2e,0,0x2f,0,
//    };
    
    const uint8_t QueryIndex[]={
        0x20,0x21,0x22,0x23,0x24,
        0x26,0x27,0x28,0x2a,0x2b,
        0x2c,0x2d,0x2e,0x2f,
    };
    
    
    uint8_t verify=0;

    QueryTx_buf[0] = 0x7e;
    QueryTx_buf[1] = 0x03;
    QueryTx_buf[2] = QueryIndex[tracks];

    //异或校验
    verify = QueryTx_buf[1] ^ QueryTx_buf[2];
    QueryTx_buf[3] = verify;

    QueryTx_buf[4] = 0xef;

    //发送音乐
//    taskENTER_CRITICAL();
//    HAL_UART_Transmit(&huart6, QueryTx_buf, 5,500);
//    taskEXIT_CRITICAL();
//    Voice_Delay_us(50000);
//    HAL_UART_Transmit(0, QueryTx_buf, 1,500);
    
    taskENTER_CRITICAL();
    for(uint8_t n=0;n<5;n++)
    {
        while ((USART6->ISR & 0X40) == 0);//循环发送,直到发送完毕   
        USART6->TDR = (uint8_t)QueryTx_buf[n];
    }
    taskEXIT_CRITICAL();
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

//获取播放音量
uint8_t GetVoiceVolume(void)
{
    uint8_t temp;

    f_open(&FIL_GlobalVariableStruct.file, (char*)"1:Voice.ini", FA_READ);

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


    return temp;
}



void VoiceUSARTRxHandler()
{
    VoiceRTxStru.RxBuff[VoiceRTxStru.Len] = VoiceRTxStru.Receive;//接收数据到缓存
    //收到帧尾
    if (VoiceRTxStru.RxBuff[VoiceRTxStru.Len] == 0x90)
    {

        VoiceRTxStru.Len = 0;
    }
    else
    {
        VoiceRTxStru.Len++;
    }
    printf("%c", VoiceRTxStru.Receive);
    HAL_UART_Receive_IT(&huart6, &VoiceRTxStru.Receive, 1);
}













