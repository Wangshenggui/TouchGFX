#include "my_adc.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

static uint16_t Get_Adc3_Average(uint8_t times)
{
    uint32_t temp_val = 0;
    uint8_t t;
    for (t = 0; t < times; t++)
    {
        HAL_ADC_Start(&hadc3);
        HAL_ADC_PollForConversion(&hadc3, 10);
        temp_val += HAL_ADC_GetValue(&hadc3);
        osDelay(5);
    }
    return temp_val / times;
}

float GetADC_Temperate(void)
{
    uint32_t adcx;
    //	short result;
    double temperate;
    float temp = 0;
    uint16_t ts_cal1, ts_cal2;
    HAL_ADC_Start(&hadc3);
    HAL_ADC_PollForConversion(&hadc3, 5);
    ts_cal1 = *(volatile uint16_t*)(0X1FF1E820);					//��ȡTS_CAL1
    ts_cal2 = *(volatile uint16_t*)(0X1FF1E840);					//��ȡTS_CAL2
    temp = (float)((110.0 - 30.0) / (ts_cal2 - ts_cal1));	//��ȡ��������
    adcx = Get_Adc3_Average(20);		//��ȡ�ڲ��¶ȴ�����ͨ��,10��ȡƽ��
    adcx = HAL_ADC_GetValue(&hadc3);		//��ȡ�ڲ��¶ȴ�����ͨ��,10��ȡƽ��
    temperate = (float)(temp * (adcx - ts_cal1) + 30);		//�����¶�
    return temperate;
}













