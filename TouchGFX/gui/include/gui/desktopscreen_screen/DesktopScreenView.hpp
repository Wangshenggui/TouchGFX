#ifndef DESKTOPSCREENVIEW_HPP
#define DESKTOPSCREENVIEW_HPP

#include <gui_generated/desktopscreen_screen/DesktopScreenViewBase.hpp>
#include <gui/desktopscreen_screen/DesktopScreenPresenter.hpp>

#include <gui/containers/NotificationBarContainer.hpp>
#include <gui/containers/StatusBarContainer.hpp>
#include <gui/common/ParticleEffect.hpp>
#include <gui/common/ScrollingWheels/ParticlesScrollingWheel.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>


typedef struct
{
    //桌面swipe管理
    uint8_t swipe_Index;
}Desktopscreen_ScreenGlobalVariableStructure;
extern Desktopscreen_ScreenGlobalVariableStructure Desktopscreen_ScreenGlobalVariableStruct;


class DesktopScreenView : public DesktopScreenViewBase
{
public:
    DesktopScreenView();
    virtual ~DesktopScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleClickEvent(const ClickEvent& event);
    virtual void handleDragEvent(const DragEvent& event);
    virtual void handleGestureEvent(const GestureEvent& event);
    virtual void Volume_Trigger1Handler(uint8_t value);
    virtual void handleTickEvent();

    bool loadImageFromSDCard1(const char* imgPath, uint16_t imgWidth, uint16_t imgHeight);
    bool loadImageFromSDCard2(const char* imgPath, uint16_t imgWidth, uint16_t imgHeight);
        
    
    virtual void flexButton10Handler();
        
    //消息事件
    virtual void handleKeyEvent(uint8_t key);
        
        //风扇通知
    virtual void Fan_TriggerHandler(bool value);
        
        
        
       virtual void addNum();
protected:
    Model Model;
    BitmapId  bitmapId1;
    BitmapId  bitmapId2;
    //定义全局变量，解决某些奇怪的东西
    uint16_t RadioStateTIM_n;

    bool orientation1;//向下
    uint16_t Y1;
    bool orientation2;//向下
    uint16_t Y2;

    //点击的起始坐标Y
     uint16_t ClickStartY, ClickEndY;
     bool N_BarFlag;//默认隐藏

    //按钮处理(用于解决不能滑动)
     uint16_t ButtonClickStartX,ButtonClickStartY,ButtonClickEndX,ButtonClickEndY;


    ParticleEffect particleEffect;
    int numberOfParticles;
    FadeAnimator<ParticlesScrollingWheel> particlesScrollingWheel;
};

#endif // DESKTOPSCREENVIEW_HPP
