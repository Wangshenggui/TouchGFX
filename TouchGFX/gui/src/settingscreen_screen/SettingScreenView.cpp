#include <gui/settingscreen_screen/SettingScreenView.hpp>

#include <touchgfx/Utils.hpp>
#include <stdio.h>

#ifndef SIMULATOR
#include "main.h"
#include "Radio.h"

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"


extern osThreadId touchGFXHandle;
extern osThreadId GUI_MesProcessHandle;
#endif



SettingScreenView::SettingScreenView()
{





    //点击的起始坐标Y
    ClickStartY = 0, ClickEndY = 0;
    N_BarFlag = 0;//默认隐藏


    //设置字体颜色
    statusBarContainer.SetDigClockColor(0, 0, 0);

}

void SettingScreenView::setupScreen()
{
    SettingScreenViewBase::setupScreen();
}

void SettingScreenView::tearDownScreen()
{
    SettingScreenViewBase::tearDownScreen();
}

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/

void SettingScreenView::handleTickEvent()
{
    //计算帧率
    statusBarContainer.SetFPS(Model.getLCDfps());
}

//重写点击事件
void SettingScreenView::handleClickEvent(const ClickEvent& event)
{
    SettingScreenViewBase::handleClickEvent(event);//防止触摸失效
    //获取事件
    ClickEvent::ClickEventType type = event.getType();

    if (type == ClickEvent::PRESSED)
    {
        //获取点击坐标
        ClickStartY = event.getY();

        if (notificationBarContainer.GetSlider1ClickFlag() == 1)
            statusBarContainer.SetDigClockColor(0, 0, 0);
    }
    else if (type == ClickEvent::RELEASED)
    {
        //获取松开坐标
        ClickEndY = event.getY();

        if (ClickStartY < 20)
        {
            if (ClickEndY < 70)
            {
                N_BarFlag = 0;
                //隐藏通知栏
                notificationBarContainer.SetAlpha(0);
            }
            else
            {
                notificationBarContainer.SetAlpha(255);
                N_BarFlag = 1;
            }
        }
        else if (ClickEndY < 40 && notificationBarContainer.GetSlider1ClickFlag() == 1)
        {
            //设置状态栏时钟字体颜色
            statusBarContainer.SetDigClockColor(0, 0, 0);
            N_BarFlag = 0;
            //隐藏通知栏
            notificationBarContainer.SetAlpha(0);
        }
        if (N_BarFlag == 0)
            statusBarContainer.SetDigClockColor(0, 0, 0);
        else
            statusBarContainer.SetDigClockColor(255, 255, 255);
    }
    else if (type == ClickEvent::CANCEL)
    {

    }
}
//重写拖拽事件
void SettingScreenView::handleDragEvent(const DragEvent& event)
{
    static uint16_t NewY = 0;

    SettingScreenViewBase::handleDragEvent(event);//防止触摸失效

    if (event.getType() == DragEvent::DRAGGED)
    {
        //显示渐变通知栏
        if (ClickStartY < 20 && N_BarFlag == 0)
        {
            NewY = event.getNewY();
            notificationBarContainer.SetAlpha(NewY * 2.2);
            //设置状态栏时钟字体颜色
            static uint16_t color;
            color = NewY * 3.5;
            if (color > 255)color = 255;
            statusBarContainer.SetDigClockColor(color, color, color);
        }
    }
}
//导航栏处理
void SettingScreenView::BackMenuHandler(uint8_t value)
{
    if (value == 1)//返回键
    {
        application().gotoDesktopScreenScreenNoTransition();
    }
    else//菜单键
    {


    }
}
//容器通信
void SettingScreenView::Volume_Trigger1Handler(uint8_t value)
{
    statusBarContainer.SetVolumeIconColor(value, 255, 0, 0);
}


//RTOS-GUI
void SettingScreenView::handleKeyEvent(uint8_t key)
{
#ifndef SIMULATOR
    if (key == TaskConGUIQueRenTemp)
#else
#define TaskConGUIQueRenTemp '0'
    if (key == TaskConGUIQueRenTemp)
#endif
    {
#ifndef SIMULATOR
        //更新CPU温度和使用率
        statusBarContainer.SetCPU(MAIN_FREERTOS_GlobalVariableStruct.cpu_usage, MAIN_FREERTOS_GlobalVariableStruct.CPUtemperature);
#else
        touchgfx_printf("NiGanMaAiYo 0\r\n");
#endif
    }
#ifndef SIMULATOR
    else if (key == TaskConGUIQueUpRadio)
#else
#define TaskConGUIQueUpRadio '1'
    else if (key == TaskConGUIQueUpRadio)
#endif
    {
#ifndef SIMULATOR
        //更新无线电数据
        statusBarContainer.SetRadioState(RadioStateStru.State);
        statusBarContainer.SetRadioColor(statusBarContainer.GetRadioState());
        statusBarContainer.SetRadioVisible(true);

        //更新时间
        statusBarContainer.UpdateTime();
#else
        touchgfx_printf("NiGanMaAiYo 0\r\n");
#endif
    }
}



//风扇通知
void SettingScreenView::Fan_TriggerHandler(bool value)
{
    presenter->set_fan_onoff(value);
}




