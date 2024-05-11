#include "usart_it.h"
#include "Radio.h"
#include "Voice.h"
#include "usmart_cmd_input.h"


void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
    //无线电串口
    if (huart->Instance == USART1)
    {
        RadioUSARTRxHandler();
    }
    else if (huart->Instance == USART2)
    {
        USMART_RxHandler();
    }
    else if (huart->Instance == USART6)
    {
//        HAL_UART_Transmit(&huart6, (uint8_t*)'G', 1, 100);
//        HAL_UART_Receive_IT(&huart6, &VoiceRTxStru.Receive, 1);
//        VoiceUSARTRxHandler();
    }
}







