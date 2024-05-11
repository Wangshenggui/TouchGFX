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





    //�������ʼ����Y
    ClickStartY = 0, ClickEndY = 0;
    N_BarFlag = 0;//Ĭ������


    //����������ɫ
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
    //����֡��
    statusBarContainer.SetFPS(Model.getLCDfps());
}

//��д����¼�
void SettingScreenView::handleClickEvent(const ClickEvent& event)
{
    SettingScreenViewBase::handleClickEvent(event);//��ֹ����ʧЧ
    //��ȡ�¼�
    ClickEvent::ClickEventType type = event.getType();

    if (type == ClickEvent::PRESSED)
    {
        //��ȡ�������
        ClickStartY = event.getY();

        if (notificationBarContainer.GetSlider1ClickFlag() == 1)
            statusBarContainer.SetDigClockColor(0, 0, 0);
    }
    else if (type == ClickEvent::RELEASED)
    {
        //��ȡ�ɿ�����
        ClickEndY = event.getY();

        if (ClickStartY < 20)
        {
            if (ClickEndY < 70)
            {
                N_BarFlag = 0;
                //����֪ͨ��
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
            //����״̬��ʱ��������ɫ
            statusBarContainer.SetDigClockColor(0, 0, 0);
            N_BarFlag = 0;
            //����֪ͨ��
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
//��д��ק�¼�
void SettingScreenView::handleDragEvent(const DragEvent& event)
{
    static uint16_t NewY = 0;

    SettingScreenViewBase::handleDragEvent(event);//��ֹ����ʧЧ

    if (event.getType() == DragEvent::DRAGGED)
    {
        //��ʾ����֪ͨ��
        if (ClickStartY < 20 && N_BarFlag == 0)
        {
            NewY = event.getNewY();
            notificationBarContainer.SetAlpha(NewY * 2.2);
            //����״̬��ʱ��������ɫ
            static uint16_t color;
            color = NewY * 3.5;
            if (color > 255)color = 255;
            statusBarContainer.SetDigClockColor(color, color, color);
        }
    }
}
//����������
void SettingScreenView::BackMenuHandler(uint8_t value)
{
    if (value == 1)//���ؼ�
    {
        application().gotoDesktopScreenScreenNoTransition();
    }
    else//�˵���
    {


    }
}
//����ͨ��
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
        //����CPU�¶Ⱥ�ʹ����
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
        //�������ߵ�����
        statusBarContainer.SetRadioState(RadioStateStru.State);
        statusBarContainer.SetRadioColor(statusBarContainer.GetRadioState());
        statusBarContainer.SetRadioVisible(true);

        //����ʱ��
        statusBarContainer.UpdateTime();
#else
        touchgfx_printf("NiGanMaAiYo 0\r\n");
#endif
    }
}



//����֪ͨ
void SettingScreenView::Fan_TriggerHandler(bool value)
{
    presenter->set_fan_onoff(value);
}




