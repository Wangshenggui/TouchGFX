#ifndef _USMART_CMD_INPUT_H
#define _USMART_CMD_INPUT_H

#include "main.h"
#include "sys.h"
#include "usart.h"


extern //¿ÕÏÐ¼ÆÊý
uint8_t Idle_n;


#define USMART_UART           &huart2

#define Rx_LENG 200
typedef struct
{
    uint8_t Receive;
    uint8_t Rx_Buff[Rx_LENG];
    uint8_t Rx_len;
    uint8_t Buff[Rx_LENG];
    uint8_t Rx_State;
}UART_USMART_Structure;
extern UART_USMART_Structure UART_USMART_Struct;

void USMART_RxHandler(void);



#endif
