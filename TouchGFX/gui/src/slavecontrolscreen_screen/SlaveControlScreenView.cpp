#include <gui/slavecontrolscreen_screen/SlaveControlScreenView.hpp>
#include <touchgfx/Utils.hpp>

#include <gui/containers/NotificationBarContainer.hpp>
#include <gui/bootscreen_screen/BootScreenView.hpp>

#include <stdio.h>

#ifndef SIMULATOR
#include "Radio.h"


#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#endif


SlaveControlScreenView::SlaveControlScreenView() :ButBit(0)
{
    Dir = 0;//正向
    UARTSend_n = 1;
    Buf[0] = 0xeb;
    Buf[1] = 0xff;//地址位
    Buf[2] = 0xc1;
    Buf[3] = 0;//速度
    Buf[4] = 0x90;

    flexButton12Buffer[0] = 0x6b63;
    flexButton12Buffer[1] = 0;
    flexButton12.invalidate();

    navigationBarContainer1.SetButtonColor(255, 255, 255);
    navigationBarContainer1.invalidate();

#ifndef SIMULATOR
    Radio_GlobalVariableStruct.SendButyFlag = 2;
#endif
}

void SlaveControlScreenView::setupScreen()
{
    SlaveControlScreenViewBase::setupScreen();
}

void SlaveControlScreenView::tearDownScreen()
{
#ifndef SIMULATOR
    Radio_GlobalVariableStruct.SendButyFlag = 1;
#endif
    SlaveControlScreenViewBase::tearDownScreen();
}




void SlaveControlScreenView::flexButton1Handler()
{
    if (flexButton1.getPressed())
        ButBit = ButBit | (1 << 0);
    else
        ButBit = ButBit & ~(1 << 0);
}
void SlaveControlScreenView::flexButton2Handler()
{
    if (flexButton2.getPressed())
        ButBit = ButBit | (1 << 1);
    else
        ButBit = ButBit & ~(1 << 1);
}
void SlaveControlScreenView::flexButton3Handler()
{
    if (flexButton3.getPressed())
        ButBit = ButBit | (1 << 2);
    else
        ButBit = ButBit & ~(1 << 2);
}
void SlaveControlScreenView::flexButton4Handler()
{
    if (flexButton4.getPressed())
        ButBit = ButBit | (1 << 3);
    else
        ButBit = ButBit & ~(1 << 3);
}
void SlaveControlScreenView::flexButton5Handler()
{
    if (flexButton5.getPressed())
        ButBit = ButBit | (1 << 4);
    else
        ButBit = ButBit & ~(1 << 4);
}
void SlaveControlScreenView::flexButton6Handler()
{
    if (flexButton6.getPressed())
        ButBit = ButBit | (1 << 5);
    else
        ButBit = ButBit & ~(1 << 5);
}
void SlaveControlScreenView::flexButton7Handler()
{
    if (flexButton7.getPressed())
        ButBit = ButBit | (1 << 6);
    else
        ButBit = ButBit & ~(1 << 6);
}
void SlaveControlScreenView::flexButton8Handler()
{
    if (flexButton8.getPressed())
        ButBit = ButBit | (1 << 7);
    else
        ButBit = ButBit & ~(1 << 7);
}
void SlaveControlScreenView::flexButton9Handler()
{
    if (ButBit == 0)
    {
        flexButton1.setPressed(1);
        flexButton2.setPressed(1);
        flexButton3.setPressed(1);
        flexButton4.setPressed(1);
        flexButton5.setPressed(1);
        flexButton6.setPressed(1);
        flexButton7.setPressed(1);
        flexButton8.setPressed(1);
        container1.invalidate();
        ButBit = 255;
    }
    else if (ButBit != 0)
    {
        //清空
        flexButton1.setPressed(0);
        flexButton2.setPressed(0);
        flexButton3.setPressed(0);
        flexButton4.setPressed(0);
        flexButton5.setPressed(0);
        flexButton6.setPressed(0);
        flexButton7.setPressed(0);
        flexButton8.setPressed(0);
        container1.invalidate();
        ButBit = 0;
    }
}
void SlaveControlScreenView::flexButton10Handler()
{
#ifdef SIMULATOR
    for (uint8_t i = 0; i < 8; i++)
    {
        if ((ButBit >> i) & 0x01)
        {
            touchgfx_printf("%d ", 1);
        }
        else
        {
            touchgfx_printf("%d ", 0);
        }
    }
    touchgfx_printf("\n");
#endif


    static uint8_t s = 0;
    Buf[0] = 0xeb;
    Buf[1] = ButBit;//地址位

    s += 10;
    if (s > 60)
    {
        s = 0;
    }
    Buf[3] = s;//速度
    Buf[4] = 0x90;


    Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%d", s);
    textArea1.invalidate();
}

void SlaveControlScreenView::flexButton11Handler()
{

    Buf[0] = 0xeb;
    Buf[1] = ButBit;//地址位



    Buf[4] = 0x90;
#ifndef SIMULATOR
    if (Radio_GlobalVariableStruct.SendButyFlag == 2)
    {
        UARTSend_n = 1;
        //发送控制命令
        HAL_UART_Transmit_DMA(&huart1, Buf, 5);
    }
#endif
    for (uint8_t i = 0; i < 6; i++)
        printf("%02X ", Buf[i]);
    printf("\r\n");
}

void SlaveControlScreenView::flexButton12Handler()
{
    Dir = !Dir;
    Buf[2] = 0xc1 + Dir;

    if (Buf[2] == 0xc1)
    {
        flexButton12Buffer[0] = 0x6b63;
        flexButton12Buffer[1] = 0;
    }
    else if (Buf[2] == 0xc2)
    {
        flexButton12Buffer[0] = 0x53cd;
        flexButton12Buffer[1] = 0;
    }
    flexButton12.invalidate();
}

void SlaveControlScreenView::handleTickEvent()
{
    static uint8_t i = 0, j = 0;


    if (UARTSend_n == 1)
    {
        j++;
        if (j == 5)
        {
            j = 0;
            i++;
            if (i == 5)
            {
                i = 0;
                UARTSend_n = 0;
            }
#ifndef SIMULATOR
            HAL_UART_Transmit_DMA(&huart1, Buf, 5);
#endif
        }
    }
    else
    {
        i = j = 0;
    }
}




