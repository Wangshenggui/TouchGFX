#include "tim_it.h"
#include <stdio.h>
#include "Radio.h"



#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

#include "usmart_cmd_input.h"


#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_msc.h"
#include "usbd_storage.h"
extern USBD_HandleTypeDef USBD_Device;		//USB Device����ṹ��
extern vu8 bDeviceState;			//USB���� ���

void SetUSB_State(uint8_t n);

u8 led0sta = 1;
u8 offline_cnt = 0;
u8 tct = 0;
u8 USB_STA;
u8 Divece_STA;

//100ms��ʱ��
void HAL_TIM6_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
    static uint8_t t = 0;

    t++;
    if (t == 10)
    {
        t = 0;

        uint8_t StateFlag = 0;
        StateFlag = 0;
        if (USB_GlobalVariableStruct.USB_STATUS_REG & 0x01)//����д		  
        {
            SetUSB_State(2);
            StateFlag = 1;
        }
        else if (USB_GlobalVariableStruct.USB_STATUS_REG & 0x02)//���ڶ�
        {
            SetUSB_State(3);
            StateFlag = 1;
        }
        //        else if(USB_STATUS_REG==0)
        //        {
        //            StateFlag=1;
        //        }
            //    if(Divece_STA!=bDeviceState)
        {
            if (bDeviceState == 1 && !StateFlag)
            {
                SetUSB_State(1);//��������
            }
            else if (!StateFlag)
            {
                SetUSB_State(0);//�Ͽ�
            }
            Divece_STA = bDeviceState;
        }


        tct++;
        if (tct == 10)
        {
            tct = 0;
            if (USB_GlobalVariableStruct.USB_STATUS_REG & 0x10)
            {
                offline_cnt = 0;//USB������,�����offline������
                bDeviceState = 1;
            }
            else//û�еõ���ѯ 
            {
                offline_cnt++;
                if (offline_cnt > 10)bDeviceState = 0;//2s��û�յ����߱��,����USB���γ���
            }
            USB_GlobalVariableStruct.USB_STATUS_REG = 0;
        }
        delay_us(1);//�������Ļ�����UI������
    }
}


//�����жϴ��ڿ����ж�
void HAL_TIM15_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
    if (Idle_n != 0)
    {
        Idle_n--;
        if (Idle_n == 0)
        {
            memcpy(UART_USMART_Struct.Buff, UART_USMART_Struct.Rx_Buff, UART_USMART_Struct.Rx_len);
            //���У���ʾ������һ֡����
            UART_USMART_Struct.Rx_State = 1;
        }
    }
}

//���ߵ����Ӽ���
extern uint8_t RadioConCounting;

extern osSemaphoreId RadioUART_BinSemHandle;
extern osSemaphoreId UpRadioDatBinSemHandle;
//������ʱ������
void HAL_TIM12_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
    static uint16_t tim_n = 0;

    tim_n++;

    if (RadioConCounting <= 100)
    {
        if (RadioConCounting-- == 0)
        {
            //�������ߵ�״̬
            ReadRadioState();
            ParsingUSART();//��������
            osSemaphoreRelease(UpRadioDatBinSemHandle);//�ͷ����ߵ�����ź���
        }
    }
}








