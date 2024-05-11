#include "usmart_cmd_input.h"
#include "string.h"
#include <stdio.h>


UART_USMART_Structure UART_USMART_Struct;

//空闲计数
uint8_t Idle_n=0;

void USMART_RxHandler()
{
    UART_USMART_Struct.Rx_Buff[UART_USMART_Struct.Rx_len++] = UART_USMART_Struct.Receive;//接收数据到缓存
    
    Idle_n=10;
    
    HAL_UART_Receive_IT(&huart2, &UART_USMART_Struct.Receive, 1);
}












