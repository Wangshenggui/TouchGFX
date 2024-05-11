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
    slider1.setClickAction(slider1ClickCallback);//设置点击回调

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
    //获取背光，并设置
    slider1.setValue(GetBacklight());
    slider1.invalidate();

    //获取音量，并设置
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
    //显示音量图标
    textArea1Buffer[1] = 0;
    textArea1.invalidate();
#endif
}

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
//呼出/隐藏通知栏
void NotificationBarContainer::SetAlpha(uint16_t alpha)
{
    if (alpha > Box1Alpha)
        box1.setAlpha(Box1Alpha);
    else
        box1.setAlpha(alpha);
    box1.invalidate();

    if (alpha == 0)//完全透明
        //隐藏容器
        NotificationBarContainer::setVisible(false);
    else
        NotificationBarContainer::setVisible(true);
}

//滑块回调函数
void NotificationBarContainer::slider1CallbackHandler(int value)
{
#ifndef SIMULATOR
    //调节背光
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
    //调节音量
    SetVoiceVolume(value);
    //调节音量
    SetVoiceVolume(value);
    //保存音量
    SaveVoiceVolume(value);
#endif
}
void NotificationBarContainer::slider2ChangeCallbackHandler(int value)
{
#ifndef SIMULATOR
    //调节音量
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
    //显示音量图标
    textArea1Buffer[1] = 0;
    textArea1.invalidate();
    //发送触发值
    emitVolume_Trigger1Callback(value);
}

//滑块触摸标志，防止意外退出通知栏
bool NotificationBarContainer::GetSlider1ClickFlag(void)
{
    return Slider1ClickFlag;
}
void NotificationBarContainer::SetSlider1ClickFlag(bool flag)
{
    Slider1ClickFlag = flag;
}

//小风扇转动标志
bool StatusFanRotateFlag = 0;
//滑块Click回调
void NotificationBarContainer::slider1ClickHandler(const touchgfx::Slider& slider, const touchgfx::ClickEvent& event)
{
    touchgfx::ClickEvent::ClickEventType type = event.getType();

    if (type == touchgfx::ClickEvent::PRESSED)
    {
        //调节滑块
        SetSlider1ClickFlag(1);
        box1.setAlpha(0);
        box1.invalidate();
        
        StatusFanRotateFlag = 1;
    }
    else if (type == touchgfx::ClickEvent::RELEASED)
    {
        //松开滑块
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



//无线电连接按钮
void NotificationBarContainer::toggleButton1Handler()
{
#ifndef SIMULATOR
    if (toggleButton1.getState())
    {
        Radio_GlobalVariableStruct.SendButyFlag = 1;
        //发送读取命令
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
//风扇状态设置
void NotificationBarContainer::SetFanFlag(uint8_t state)
{
    FanRunFlag = state;
}
//风扇状态获取
uint8_t NotificationBarContainer::GetFanFlag()
{
    return FanRunFlag;
}
//风扇开关按钮
void NotificationBarContainer::toggleButton2Handler()
{
    bool state = toggleButton2.getState();

    SetFanFlag(state);
    emitFan_TriggerCallback(state);
}



