#ifndef SETTINGSCREENVIEW_HPP
#define SETTINGSCREENVIEW_HPP

#include <gui_generated/settingscreen_screen/SettingScreenViewBase.hpp>
#include <gui/settingscreen_screen/SettingScreenPresenter.hpp>

class SettingScreenView : public SettingScreenViewBase
{
public:
    SettingScreenView();
    virtual ~SettingScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleClickEvent(const ClickEvent& event);
    virtual void handleDragEvent(const DragEvent& event);
    virtual void BackMenuHandler(uint8_t value);
    virtual void Volume_Trigger1Handler(uint8_t value);

    virtual void handleKeyEvent(uint8_t key);

    virtual void handleTickEvent();
        
    virtual void Fan_TriggerHandler(bool value);
protected:
    Model Model;
    //点击的起始坐标Y
     uint16_t ClickStartY, ClickEndY;
     bool N_BarFlag ;//默认隐藏
};

#endif // SETTINGSCREENVIEW_HPP
