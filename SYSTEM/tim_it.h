#ifndef _TIM_IT_H
#define _TIM_IT_H

#include "main.h"
#include "tim.h"
#include "usart.h"


void HAL_TIM6_PeriodElapsedCallback(TIM_HandleTypeDef* htim);
void HAL_TIM15_PeriodElapsedCallback(TIM_HandleTypeDef* htim);
void HAL_TIM12_PeriodElapsedCallback(TIM_HandleTypeDef* htim);












#endif
