#include "Radio.h"
#include <string.h>
#include <stdio.h>


#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"


Radio_GlobalVariableStructure Radio_GlobalVariableStruct = { 0 };




RadioRTxStructure RadioRTxStru;
RadioStateStructure RadioStateStru;
SowingSysStructure SowingSysStru;


static uint8_t RxLen;
//��ȡ����״̬
uint8_t ReadRadioState(void)
{
    memcpy(Radio_GlobalVariableStruct.RadioSSCOM_Buff, RadioStateStru.Buff, sizeof(RadioStateStru.Buff));
    Radio_GlobalVariableStruct.RadioSSCOM_BuffcopyFlag = 1;
    //��ȷ
    if (RadioStateStru.Buff[0] == 0xeb
        && RadioStateStru.Buff[RxLen] == 0x90
        && RadioStateStru.Buff[RxLen - 2] == 'O'
        && RadioStateStru.Buff[RxLen - 1] == 'K')
    {
        RadioStateStru.State = 1;//������

        //ʹ�ù������
        RadioStateStru.Buff[0] = 0;
        RadioStateStru.Buff[RxLen] = 0;
        RadioStateStru.Buff[RxLen - 1] = 0;
        RadioStateStru.Buff[RxLen - 2] = 0;
    }
    else
    {
        RadioStateStru.State = 0;
    }
    

    RadioStateStru.ParsingFlag = 1;//��ǽ������

    return RadioStateStru.State;
}

extern uint8_t DateTemp;
//������λ������
void ParsingUSART(void)
{
    memset(SowingSysStru.State,0,200);
    //�������Ӳ�״̬
    for (uint8_t i = 0; i < 8; i++)
    {
        SowingSysStru.State[i]=0;
        SowingSysStru.State[i] = RadioRTxStru.DataBuff[i + 1];
    }
    //����������ٶ�
    for (uint8_t i = 0; i < 8; i++)
    {
        SowingSysStru.MainSpeed[i]=0;
        SowingSysStru.MainSpeed[i] = RadioRTxStru.DataBuff[i + 9];
    }
    //����������ٶ�
    for (uint8_t i = 0; i < 8; i++)
    {
        SowingSysStru.AsSpeed[i]=0;
        SowingSysStru.AsSpeed[i] = RadioRTxStru.DataBuff[i + 17];
    }
    //���������ٶ�
    union
    {
        float v;
        unsigned char byte[4];
    }GPS_Speed;
    GPS_Speed.v=0;
    GPS_Speed.byte[0] = RadioRTxStru.DataBuff[25];
    GPS_Speed.byte[1] = RadioRTxStru.DataBuff[26];
    GPS_Speed.byte[2] = RadioRTxStru.DataBuff[27];
    GPS_Speed.byte[3] = RadioRTxStru.DataBuff[28];
    SowingSysStru.UAVSpeed = GPS_Speed.v;

    //����GPSʱ��
    Radio_GlobalVariableStruct.GPS_Tim[0] = RadioRTxStru.DataBuff[29];
    Radio_GlobalVariableStruct.GPS_Tim[1] = RadioRTxStru.DataBuff[30];
    Radio_GlobalVariableStruct.GPS_Tim[2] = RadioRTxStru.DataBuff[31];

    //����GPS����
    DateTemp=Radio_GlobalVariableStruct.GPS_Dat[0] = RadioRTxStru.DataBuff[34];
    Radio_GlobalVariableStruct.GPS_Dat[1] = RadioRTxStru.DataBuff[35];
    Radio_GlobalVariableStruct.GPS_Dat[2] = RadioRTxStru.DataBuff[36];

    //����ʱ��
    Radio_GlobalVariableStruct.SlaveRunTime=0;
    Radio_GlobalVariableStruct.SlaveRunTime = (RadioRTxStru.DataBuff[32] << 8) | RadioRTxStru.DataBuff[33];
    
    //��λ״̬
    Radio_GlobalVariableStruct.PositionStatus=0;
    Radio_GlobalVariableStruct.PositionStatus = RadioRTxStru.DataBuff[53];

    memset(RadioRTxStru.DataBuff,0,sizeof RadioRTxStru.DataBuff);
}

//���ߵ����Ӽ���
uint8_t RadioConCounting = 0;

extern osSemaphoreId RadioUART_BinSemHandle;
void RadioUSARTRxHandler()
{
    RadioRTxStru.RxBuff[RadioRTxStru.Len] = RadioRTxStru.Receive;//�������ݵ�����
    //�յ�֡β
    if (RadioRTxStru.RxBuff[RadioRTxStru.Len] == 0x90)
    {
        RxLen = RadioRTxStru.Len;
        //�ж�֡ͷ����һ֡���ϱ���Ϣ��
        if (RadioRTxStru.RxBuff[0] == 0xeb)
        {
            //��ʼ����
            RadioConCounting = 100;
            memset(RadioStateStru.Buff, 0, 200);
            for (uint8_t i = 0; i < RadioRTxStru.Len + 1; i++)
            {
                //�����ݸ��Ƶ�������
                RadioRTxStru.DataBuff[i] = RadioRTxStru.RxBuff[i];

                RadioStateStru.Buff[i] = RadioRTxStru.RxBuff[i];

                RadioRTxStru.RxBuff[i] = 0;
            }
            //�ͷ��ź���
            osSemaphoreRelease(RadioUART_BinSemHandle);//�ͷ��ź���

            if (Radio_GlobalVariableStruct.SendButyFlag==1 && Radio_GlobalVariableStruct.Send_Num!=0)
            {
                HAL_UART_Transmit_DMA(&huart1, (const uint8_t*)"Read", 4);
                Radio_GlobalVariableStruct.Send_Num--;
            }
            else if (Radio_GlobalVariableStruct.SendButyFlag==0 && Radio_GlobalVariableStruct.Send_Num != 0)
            {
                HAL_UART_Transmit_DMA(&huart1, (const uint8_t*)"Erro", 4);
                Radio_GlobalVariableStruct.Send_Num--;
            }
        }
        //�ж�֡ͷ���ڶ�֡��RTK���÷�����Ϣ��
        if (RadioRTxStru.RxBuff[0] == 0xAC)
        {
            //���óɹ�
            if (RadioRTxStru.RxBuff[1] == 'O' && RadioRTxStru.RxBuff[2] == 'K')
            {
                //���Ϊ1�����óɹ�
                Radio_GlobalVariableStruct.RTKConfigurationState = 1;
            }
            //ʧ��
            else if (RadioRTxStru.RxBuff[1] == 'E'
                && RadioRTxStru.RxBuff[2] == 'R'
                && RadioRTxStru.RxBuff[3] == 'R')
            {
                Radio_GlobalVariableStruct.RTKConfigurationState = 0;
            }
        }
        RadioRTxStru.Len = 0;
    }
    //�س���β
    else if (RadioRTxStru.RxBuff[RadioRTxStru.Len - 2] == 'K'
        && RadioRTxStru.RxBuff[RadioRTxStru.Len - 1] == 0x0d
        && RadioRTxStru.RxBuff[RadioRTxStru.Len] == 0x0a)
    {
        if (RadioRTxStru.RxBuff[0] == '+')
        {
            memset(Radio_GlobalVariableStruct.M4GReturnBuff, 0, 200);
            memcpy(Radio_GlobalVariableStruct.M4GReturnBuff, RadioRTxStru.RxBuff, strlen((char*)RadioRTxStru.RxBuff));
            memset(RadioRTxStru.RxBuff, 0, 200);
        }
        RadioRTxStru.Len = 0;
    }
    else if (RadioRTxStru.RxBuff[0] == '+'
        && RadioRTxStru.RxBuff[RadioRTxStru.Len - 1] == 0x0d
        && RadioRTxStru.RxBuff[RadioRTxStru.Len] == 0x0a)
    {

        printf("%s", RadioRTxStru.RxBuff);
    }
    else
    {
        RadioRTxStru.Len++;
    }
    HAL_UART_Receive_IT(&huart1, &RadioRTxStru.Receive, 1);
}








