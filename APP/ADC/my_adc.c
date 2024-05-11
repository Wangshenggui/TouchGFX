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
    ts_cal1 = *(volatile uint16_t*)(0X1FF1E820);					//获取TS_CAL1
    ts_cal2 = *(volatile uint16_t*)(0X1FF1E840);					//获取TS_CAL2
    temp = (float)((110.0 - 30.0) / (ts_cal2 - ts_cal1));	//获取比例因子
    adcx = Get_Adc3_Average(20);		//读取内部温度传感器通道,10次取平均
    adcx = HAL_ADC_GetValue(&hadc3);		//读取内部温度传感器通道,10次取平均
    temperate = (float)(temp * (adcx - ts_cal1) + 30);		//计算温度
    return temperate;
}













