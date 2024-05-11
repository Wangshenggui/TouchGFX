#include <gui/containers/NotificationBarContainer.hpp>
#include <touchgfx/Utils.hpp>

#include <gui/bootscreen_screen/BootScreenView.hpp>
#include <gui/desktopscreen_screen/DesktopScreenPresenter.hpp>

#ifndef SIMULATOR
#include "Backlight.h"
#include "Voice.h"
#endif


NotificationBarContainer::NotificationBarContainer() :
    slider1ClickCallback(this, &NotificationBarContainer::slider1ClickHandler)
{
    
}

void NotificationBarContainer::initialize()
{
    NotificationBarContainerBase::initialize();

//    touchgfx_printf("NotificationBarContainer\r\n");
    
    if (GetFanFlag() == 1 || GetFanFlag() == 11)
    {
        toggleButton2.forceState(true);
    }
    else
    {
        toggleButton2.forceState(false);
    }



    Slider1ClickFlag = 0;
    slider1.setClickAction(slider1ClickCallback);//���õ���ص�

#ifndef SIMULATOR
    if (Radio_GlobalVariableStruct.SendButyFlag == 1)
    {
        toggleButton1.forceState(true);
    }
    else
    {
        toggleButton1.forceState(false);
    }
#endif
    toggleButton1.invalidate();

#ifndef SIMULATOR
    //��ȡ���⣬������
    slider1.setValue(GetBacklight());
    slider1.invalidate();

    //��ȡ������������
    slider2.setValue(GetVoiceVolume());
    slider2.invalidate();
    if (slider2.getValue() == 0)
    {
        textArea1Buffer[0] = volume_iconx;
    }
    else if (slider2.getValue() <= 25)
    {
        textArea1Buffer[0] = volume_icon1;
    }
    else if (slider2.getValue() > 25 && slider2.getValue() <= 50)
    {
        textArea1Buffer[0] = volume_icon2;
    }
    else if (slider2.getValue() > 50 && slider2.getValue() <= 75)
    {
        textArea1Buffer[0] = volume_icon2;
    }
    else if (slider2.getValue() > 75)
    {
        textArea1Buffer[0] = volume_icon3;
    }
    //��ʾ����ͼ��
    textArea1Buffer[1] = 0;
    textArea1.invalidate();
#endif
}

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
//����/����֪ͨ��
void NotificationBarContainer::SetAlpha(uint16_t alpha)
{
    if (alpha > Box1Alpha)
        box1.setAlpha(Box1Alpha);
    else
        box1.setAlpha(alpha);
    box1.invalidate();

    if (alpha == 0)//��ȫ͸��
        //��������
        NotificationBarContainer::setVisible(false);
    else
        NotificationBarContainer::setVisible(true);
}

//����ص�����
void NotificationBarContainer::slider1CallbackHandler(int value)
{
#ifndef SIMULATOR
    //���ڱ���
    SetBacklight(value);
#endif
}
void NotificationBarContainer::slider1ConfirmedCallbackHandler(int value)
{
    touchgfx_printf("%d\r\n", value);
#ifndef SIMULATOR
    SaveBacklight(value);
#endif
}
void NotificationBarContainer::slider2CallbackHandler(int value)
{
    touchgfx_printf("%d\r\n", value);
#ifndef SIMULATOR
    //��������
    SetVoiceVolume(value);
    //��������
    SetVoiceVolume(value);
    //��������
    SaveVoiceVolume(value);
#endif
}
void NotificationBarContainer::slider2ChangeCallbackHandler(int value)
{
#ifndef SIMULATOR
    //��������
    SetVoiceVolume(value);
#endif
    if (value == 0)
    {
        textArea1Buffer[0] = volume_iconx;
    }
    else if (value <= 8)
    {
        textArea1Buffer[0] = volume_icon1;
    }
    else if (value > 8 && value <= 16)
    {
        textArea1Buffer[0] = volume_icon2;
    }
    else if (value > 16 && value <= 24)
    {
        textArea1Buffer[0] = volume_icon2;
    }
    else if (value > 24)
    {
        textArea1Buffer[0] = volume_icon3;
    }
    //��ʾ����ͼ��
    textArea1Buffer[1] = 0;
    textArea1.invalidate();
    //���ʹ���ֵ
    emitVolume_Trigger1Callback(value);
}

//���鴥����־����ֹ�����˳�֪ͨ��
bool NotificationBarContainer::GetSlider1ClickFlag(void)
{
    return Slider1ClickFlag;
}
void NotificationBarContainer::SetSlider1ClickFlag(bool flag)
{
    Slider1ClickFlag = flag;
}

//С����ת����־
bool StatusFanRotateFlag = 0;
//����Click�ص�
void NotificationBarContainer::slider1ClickHandler(const touchgfx::Slider& slider, const touchgfx::ClickEvent& event)
{
    touchgfx::ClickEvent::ClickEventType type = event.getType();

    if (type == touchgfx::ClickEvent::PRESSED)
    {
        //���ڻ���
        SetSlider1ClickFlag(1);
        box1.setAlpha(0);
        box1.invalidate();
        
        StatusFanRotateFlag = 1;
    }
    else if (type == touchgfx::ClickEvent::RELEASED)
    {
        //�ɿ�����
        SetSlider1ClickFlag(0);
        box1.setAlpha(Box1Alpha);
        box1.invalidate();
        
        StatusFanRotateFlag = 0;
    }
    else if (type == touchgfx::ClickEvent::CANCEL)
    {
        box1.setAlpha(0);
        box1.invalidate();
    }
}



//���ߵ����Ӱ�ť
void NotificationBarContainer::toggleButton1Handler()
{
#ifndef SIMULATOR
    if (toggleButton1.getState())
    {
        Radio_GlobalVariableStruct.SendButyFlag = 1;
        //���Ͷ�ȡ����
        HAL_UART_Transmit(&huart1, (const uint8_t*)"Read", 4, 100);
        Radio_GlobalVariableStruct.Send_Num = 5;
    }
    else
    {
        Radio_GlobalVariableStruct.SendButyFlag = 0;
        HAL_UART_Transmit(&huart1, (const uint8_t*)"Erro", 4, 100);
        Radio_GlobalVariableStruct.Send_Num = 5;
    }
#endif
}



uint8_t FanRunFlag = 0;
//����״̬����
void NotificationBarContainer::SetFanFlag(uint8_t state)
{
    FanRunFlag = state;
}
//����״̬��ȡ
uint8_t NotificationBarContainer::GetFanFlag()
{
    return FanRunFlag;
}
//���ȿ��ذ�ť
void NotificationBarContainer::toggleButton2Handler()
{
    bool state = toggleButton2.getState();

    SetFanFlag(state);
    emitFan_TriggerCallback(state);
}



