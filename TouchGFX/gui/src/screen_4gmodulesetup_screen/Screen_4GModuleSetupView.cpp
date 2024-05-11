#include <gui/screen_4gmodulesetup_screen/Screen_4GModuleSetupView.hpp>
#include <string.h>
#include <stdio.h>

#ifndef SIMULATOR
#include "usart.h"
#include "ff.h"
#include "myFatFs.h"
#include "Radio.h"
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


Screen_4GModuleSetupView::Screen_4GModuleSetupView() :
    scrollWheel1AnimateToCallback(this, &Screen_4GModuleSetupView::scrollWheel1AnimateToHandler),
    scrollWheel2AnimateToCallback(this, &Screen_4GModuleSetupView::scrollWheel2AnimateToHandler),
    scrollWheel3AnimateToCallback(this, &Screen_4GModuleSetupView::scrollWheel3AnimateToHandler)
{
    item_x[0] = 0;
    item_x[1] = 1;
    item_x[2] = 0;

    sprintf(Wheel_str[0], "GPGGA");
    sprintf(Wheel_str[1], "1");
    sprintf(Wheel_str[2], "COM1");
}

void Screen_4GModuleSetupView::setupScreen()
{
    Screen_4GModuleSetupViewBase::setupScreen();


    scrollWheel1.setAnimateToCallback(scrollWheel1AnimateToCallback);
    scrollWheel1.animateToItem(0);
    scrollWheel2.setAnimateToCallback(scrollWheel2AnimateToCallback);
    scrollWheel2.animateToItem(1);
    scrollWheel3.setAnimateToCallback(scrollWheel3AnimateToCallback);
    scrollWheel3.animateToItem(0);
}

void Screen_4GModuleSetupView::tearDownScreen()
{
#ifndef SIMULATOR
    Radio_GlobalVariableStruct.SendButyFlag = 1;
    //发送读取命令
    HAL_UART_Transmit(&huart1, (const uint8_t*)"Read", 4, 100);
    Radio_GlobalVariableStruct.Send_Num = 5;
#endif
    Screen_4GModuleSetupViewBase::tearDownScreen();
}


//滚轮更新时调用
void Screen_4GModuleSetupView::scrollWheel1UpdateItem(Setup4GContainer1& item, int16_t itemIndex)
{
    item.setText1(itemIndex);
}

//滚轮选中时调用
void Screen_4GModuleSetupView::scrollWheel1UpdateCenterItem(Setup4GContainer2& item, int16_t itemIndex)
{
    item.setText1(itemIndex);
}


//滚轮更新时调用
void Screen_4GModuleSetupView::scrollWheel2UpdateItem(Setup4GContainer1& item, int16_t itemIndex)
{
    item.setText2(itemIndex);
}

//滚轮选中时调用
void Screen_4GModuleSetupView::scrollWheel2UpdateCenterItem(Setup4GContainer2& item, int16_t itemIndex)
{
    item.setText2(itemIndex);
}






//滚轮更新时调用
void Screen_4GModuleSetupView::scrollWheel3UpdateItem(Setup4GContainer1& item, int16_t itemIndex)
{
    item.setText3(itemIndex);
}

//滚轮选中时调用
void Screen_4GModuleSetupView::scrollWheel3UpdateCenterItem(Setup4GContainer2& item, int16_t itemIndex)
{
    item.setText3(itemIndex);
}



// The callback updates the selectedVal on the itemSelected parameter
void Screen_4GModuleSetupView::scrollWheel1AnimateToHandler(int16_t itemSelected)
{
    uint8_t data[3][20] LOCATION_PRAGMA("ExtFlashSection") = { "GPGGA","GPGSV","GPRMC" };



    item_x[0] = itemSelected;

    if (item_x[0] == 1 && item_x[1] != 0 && item_x[2] == 0)
    {
        flexButton3.setAlpha(128);
        flexButton3.setTouchable(false);
        flexButton3.invalidate();
    }
    else
    {
        flexButton3.setAlpha(255);
        flexButton3.setTouchable(true);
        flexButton3.invalidate();
    }

    sprintf((char*)Wheel_str[0], "%s", data[itemSelected]);
    sprintf(Str, "%s %s %s\r\n", Wheel_str[0], Wheel_str[2], Wheel_str[1]);
    if (item_x[1] == 0)
    {
        sprintf(Str, "unlog %s %s\r\n", Wheel_str[2], Wheel_str[0]);

        //        #ifndef SIMULATOR
        //        HAL_UART_Transmit_IT(&huart1, (uint8_t*)Str, strlen(Str));
        //        printf("%s",Str);
        //        #endif
        //        touchgfx_printf("%s\r\n",Str);
    }
    else
    {
        //        #ifndef SIMULATOR
        //        HAL_UART_Transmit_IT(&huart1, (uint8_t*)Str, strlen(Str));
        //        printf("%s",Str);
        //        #endif
        //        touchgfx_printf("%s\r\n",Str);
    }
}
// The callback updates the selectedVal on the itemSelected parameter
void Screen_4GModuleSetupView::scrollWheel2AnimateToHandler(int16_t itemSelected)
{
    const uint8_t data[4][20] LOCATION_PRAGMA("ExtFlashSection") = { "0","1","0.2","0.1" };

    item_x[1] = itemSelected;

    if (item_x[0] == 1 && item_x[1] != 0 && item_x[2] == 0)
    {
        flexButton3.setAlpha(128);
        flexButton3.setTouchable(false);
        flexButton3.invalidate();
    }
    else
    {
        flexButton3.setAlpha(255);
        flexButton3.setTouchable(true);
        flexButton3.invalidate();
    }

    sprintf((char*)Wheel_str[1], "%s", data[itemSelected]);
    sprintf(Str, "%s %s %s\r\n", Wheel_str[0], Wheel_str[2], Wheel_str[1]);

    if (itemSelected == 0)
    {
        sprintf(Str, "unlog %s %s\r\n", Wheel_str[2], Wheel_str[0]);

        //        #ifndef SIMULATOR
        //        HAL_UART_Transmit_IT(&huart1, (uint8_t*)Str, strlen(Str));
        //        printf("%s",Str);
        //        #endif
        //        touchgfx_printf("%s\r\n",Str);
    }
    else
    {
        //        #ifndef SIMULATOR
        //        HAL_UART_Transmit_IT(&huart1, (uint8_t*)Str, strlen(Str));
        //        printf("%s",Str);
        //        #endif
        //        touchgfx_printf("%s\r\n",Str);
    }

}
// The callback updates the selectedVal on the itemSelected parameter
void Screen_4GModuleSetupView::scrollWheel3AnimateToHandler(int16_t itemSelected)
{
    const uint8_t data[2][90] LOCATION_PRAGMA("ExtFlashSection") = { "COM1","COM2" };

    item_x[2] = itemSelected;

    if (item_x[0] == 1 && item_x[1] != 0 && item_x[2] == 0)
    {
        flexButton3.setAlpha(128);
        flexButton3.setTouchable(false);
        flexButton3.invalidate();
    }
    else
    {
        flexButton3.setAlpha(255);
        flexButton3.setTouchable(true);
        flexButton3.invalidate();
    }

    sprintf((char*)Wheel_str[2], "%s", data[itemSelected]);
    sprintf(Str, "%s %s %s\r\n", Wheel_str[0], Wheel_str[2], Wheel_str[1]);
    if (item_x[1] == 0)
    {
        sprintf(Str, "unlog %s %s\r\n", Wheel_str[2], Wheel_str[0]);

        //        #ifndef SIMULATOR
        //        HAL_UART_Transmit_IT(&huart1, (uint8_t*)Str, strlen(Str));
        //        printf("%s",Str);
        //        #endif
        //        touchgfx_printf("%s\r\n",Str);
    }
    else
    {
        //        #ifndef SIMULATOR
        //        HAL_UART_Transmit_IT(&huart1, (uint8_t*)Str, strlen(Str));
        //        printf("%s",Str);
        //        #endif
        //        touchgfx_printf("%s\r\n",Str);
    }
}


//保存设置按钮
void Screen_4GModuleSetupView::flexButton1Handler()
{
#ifndef SIMULATOR
    HAL_UART_Transmit_IT(&huart1, (uint8_t*)"saveconfig\r\n", strlen("saveconfig\r\n"));
    printf("%s", "saveconfig\r\n");
#endif
    touchgfx_printf("saveconfig\r\n");
}

//恢复设置按钮
void Screen_4GModuleSetupView::flexButton2Handler()
{
    container4.setVisible(true);
    container4.invalidate();
}

//发送设置命令
void Screen_4GModuleSetupView::flexButton3Handler()
{
#ifndef SIMULATOR
    HAL_UART_Transmit_IT(&huart1, (uint8_t*)Str, strlen(Str));
    printf("%s", Str);
#endif
    touchgfx_printf("%s\r\n", Str);
}

//禁用COM1按钮
void Screen_4GModuleSetupView::flexButton4Handler()
{
#ifndef SIMULATOR
    HAL_UART_Transmit_IT(&huart1, (uint8_t*)"unlog com1\r\n", strlen("unlog com1\r\n"));
    printf("%s", "unlog com1\r\n");
#endif
    touchgfx_printf("unlog com1\r\n");
}

//禁用卫星按钮
void Screen_4GModuleSetupView::flexButton5Handler()
{
    container2.setVisible(true);
    container2.invalidate();
}

//禁用BDS按钮
void Screen_4GModuleSetupView::flexButton6Handler()
{
#ifndef SIMULATOR
    HAL_UART_Transmit_IT(&huart1, (uint8_t*)"mask BDS\r\n", strlen("mask BDS\r\n"));
    printf("%s", "mask BDS\r\n");
#endif
    touchgfx_printf("mask BDS\r\n");
    container2.setVisible(false);
    container2.invalidate();
}

//禁用GPS按钮
void Screen_4GModuleSetupView::flexButton7Handler()
{
#ifndef SIMULATOR
    HAL_UART_Transmit_IT(&huart1, (uint8_t*)"mask GPS\r\n", strlen("mask GPS\r\n"));
    printf("%s", "mask GPS\r\n");
#endif
    touchgfx_printf("mask GPS\r\n");
    container2.setVisible(false);
    container2.invalidate();
}

//禁用GLO按钮
void Screen_4GModuleSetupView::flexButton8Handler()
{
#ifndef SIMULATOR
    HAL_UART_Transmit_IT(&huart1, (uint8_t*)"mask GLO\r\n", strlen("mask GLO\r\n"));
    printf("%s", "mask GLO\r\n");
#endif
    touchgfx_printf("mask GLO\r\n");
    container2.setVisible(false);
    container2.invalidate();
}

//禁用GAL按钮
void Screen_4GModuleSetupView::flexButton9Handler()
{
#ifndef SIMULATOR
    HAL_UART_Transmit_IT(&huart1, (uint8_t*)"mask GAL\r\n", strlen("mask GAL\r\n"));
    printf("%s", "mask GAL\r\n");
#endif
    touchgfx_printf("mask GAL\r\n");
    container2.setVisible(false);
    container2.invalidate();
}

//启用卫星按钮
void Screen_4GModuleSetupView::flexButton10Handler()
{
    container3.setVisible(true);
    container3.invalidate();
}

//启用BDS按钮
void Screen_4GModuleSetupView::flexButton11Handler()
{
#ifndef SIMULATOR
    HAL_UART_Transmit_IT(&huart1, (uint8_t*)"unmask BDS\r\n", strlen("unmask BDS\r\n"));
    printf("%s", "unmask BDS\r\n");
#endif
    touchgfx_printf("unmask BDS\r\n");
    container3.setVisible(false);
    container3.invalidate();
}

//启用GPS按钮
void Screen_4GModuleSetupView::flexButton12Handler()
{
#ifndef SIMULATOR
    HAL_UART_Transmit_IT(&huart1, (uint8_t*)"unmask GPS\r\n", strlen("unmask GPS\r\n"));
    printf("%s", "unmask GPS\r\n");
#endif
    touchgfx_printf("unmask GPS\r\n");
    container3.setVisible(false);
    container3.invalidate();
}

//启用GLO按钮
void Screen_4GModuleSetupView::flexButton13Handler()
{
#ifndef SIMULATOR
    HAL_UART_Transmit_IT(&huart1, (uint8_t*)"unmask GPS\r\n", strlen("unmask GPS\r\n"));
    printf("%s", "unmask GPS\r\n");
#endif
    touchgfx_printf("unmask GPS\r\n");
    container3.setVisible(false);
    container3.invalidate();
}

//启用GAL按钮
void Screen_4GModuleSetupView::flexButton14Handler()
{
#ifndef SIMULATOR
    HAL_UART_Transmit_IT(&huart1, (uint8_t*)"unmask GAL\r\n", strlen("unmask GAL\r\n"));
    printf("%s", "unmask GAL\r\n");
#endif
    touchgfx_printf("unmask GAL\r\n");
    container3.setVisible(false);
    container3.invalidate();
}

//启用从天线按钮
void Screen_4GModuleSetupView::flexButton15Handler()
{
#ifndef SIMULATOR
    HAL_UART_Transmit_IT(&huart1, (uint8_t*)"CONFIG ANTENNA2 ENABLE\r\n", strlen("CONFIG ANTENNA2 ENABLE\r\n"));
    printf("%s", "CONFIG ANTENNA2 ENABLE\r\n");
#endif
    touchgfx_printf("CONFIG ANTENNA2 ENABLE\r\n");
    container3.setVisible(false);
    container3.invalidate();
}

//禁用从天线按钮
void Screen_4GModuleSetupView::flexButton16Handler()
{
#ifndef SIMULATOR
    HAL_UART_Transmit_IT(&huart1, (uint8_t*)"CONFIG ANTENNA2 DISABLE\r\n", strlen("CONFIG ANTENNA2 DISABLE\r\n"));
    printf("%s", "CONFIG ANTENNA2 DISABLE\r\n");
#endif
    touchgfx_printf("CONFIG ANTENNA2 DISABLE\r\n");
    container3.setVisible(false);
    container3.invalidate();
}

//从天线低功耗按钮
void Screen_4GModuleSetupView::flexButton17Handler()
{
#ifndef SIMULATOR
    HAL_UART_Transmit_IT(&huart1, (uint8_t*)"CONIFG ANTENNA2 DISABLE Lowpower\r\n", strlen("CONIFG ANTENNA2 DISABLE Lowpower\r\n"));
    printf("%s", "CONIFG ANTENNA2 DISABLE Lowpower\r\n");
#endif
    touchgfx_printf("CONIFG ANTENNA2 DISABLE Lowpower\r\n");
}

//禁用COM2按钮
void Screen_4GModuleSetupView::flexButton18Handler()
{
#ifndef SIMULATOR
    HAL_UART_Transmit_IT(&huart1, (uint8_t*)"unlog com2\r\n", strlen("unlog com2\r\n"));
    printf("%s", "unlog com2\r\n");
#endif
    touchgfx_printf("unlog com2\r\n");
}

//确认出厂设置
void Screen_4GModuleSetupView::flexButton19Handler()
{
#ifndef SIMULATOR
    HAL_UART_Transmit_IT(&huart1, (uint8_t*)"freset\r\n", strlen("freset\r\n"));
    printf("%s", "freset\r\n");
#endif
    touchgfx_printf("freset\r\n");

    container4.setVisible(false);
    container4.invalidate();
}

//取消出厂设置
void Screen_4GModuleSetupView::flexButton20Handler()
{
    container4.setVisible(false);
    container4.invalidate();
}

//重写点击事件
void Screen_4GModuleSetupView::handleClickEvent(const ClickEvent& event)
{
    uint16_t StartX = 0, StartY = 0;
    uint16_t StopX = 0, StopY = 0;
    static bool Flag = 0;

    Screen_4GModuleSetupViewBase::handleClickEvent(event);//防止触摸失效
    //获取事件
    ClickEvent::ClickEventType type = event.getType();

    if (type == ClickEvent::PRESSED)
    {
        //获取点击坐标
        StartX = event.getX();
        StartY = event.getY();

        if (!((StartX > box4.getX() && (StartX < box4.getX() + box4.getWidth()))
            && (StartY > box4.getY() && (StartY < box4.getY() + box4.getHeight()))))
        {
            Flag = 1;
        }
    }
    else if (type == ClickEvent::RELEASED)
    {
        //获取点击坐标
        StopX = event.getX();
        StopY = event.getY();

        if (!((StopX > box4.getX() && (StopX < box4.getX() + box4.getWidth()))
            && (StopY > box4.getY() && (StopY < box4.getY() + box4.getHeight()))))
        {
            if (Flag)
            {
                Flag = 0;

                container2.setVisible(false);
                container2.invalidate();

                container3.setVisible(false);
                container3.invalidate();
            }
        }
    }
}





