#ifndef STATUSBARCONTAINER_HPP
#define STATUSBARCONTAINER_HPP

#include <gui_generated/containers/StatusBarContainerBase.hpp>
#include <gui/containers/NotificationBarContainer.hpp>
#include <touchgfx/Color.hpp>





class StatusBarContainer : public StatusBarContainerBase
{
public:
    StatusBarContainer();
    virtual ~StatusBarContainer() {}

    virtual void initialize();

    virtual void SetDigClockColor(uint8_t r, uint8_t g, uint8_t b);
    virtual void SetRadioColor(uint8_t state);
    virtual void SetFPS(uint8_t fps);
    virtual void SetCPU(uint8_t cpu, uint8_t temp);
    virtual void SetVolumeIconColor(uint8_t Volume, uint8_t r, uint8_t g, uint8_t b);
    virtual bool GetRadioState();
    virtual void SetRadioState(bool state);
    virtual void SetRadioVisible(bool state);
    virtual void UpdateTime();
    virtual void RadialFan();
    virtual void TickTrigger();
protected:
    #define RadioIcon 0xe636
    #define volume_iconx 0xea0f
    #define volume_icon1 0xea11
    #define volume_icon2 0xea13
    #define volume_icon3 0xea12
    uint8_t VoiceVolume;//获取音量
    bool RadioState;//保存当前连接状态
    float FanAngle;
};

#endif // STATUSBARCONTAINER_HPP
