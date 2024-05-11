#ifndef NOTIFICATIONBARCONTAINER_HPP
#define NOTIFICATIONBARCONTAINER_HPP

#include <gui_generated/containers/NotificationBarContainerBase.hpp>
#include <touchgfx/Callback.hpp>


class NotificationBarContainer : public NotificationBarContainerBase
{
public:
    NotificationBarContainer();
    virtual ~NotificationBarContainer() {}

    virtual void initialize();

    virtual void SetAlpha(uint16_t alpha);
    virtual void slider1CallbackHandler(int value);
    virtual void slider1ConfirmedCallbackHandler(int value);
    virtual void slider2CallbackHandler(int value);
    virtual void slider2ChangeCallbackHandler(int value);
    virtual bool GetSlider1ClickFlag(void);
    virtual void SetSlider1ClickFlag(bool flag);
    virtual void toggleButton1Handler();
    virtual void slider1ClickHandler(const touchgfx::Slider& slider, const touchgfx::ClickEvent& event);
    virtual void toggleButton2Handler();
        void SetFanFlag(uint8_t state);
        uint8_t GetFanFlag();
        
protected:
    

    #define volume_iconx 0xea0f
    #define volume_icon1 0xea11
    #define volume_icon2 0xea13
    #define volume_icon3 0xea12
    //box1最大不透明度
    #define Box1Alpha 180
    //滑块点击标志
    bool Slider1ClickFlag;
    Callback<NotificationBarContainer, const touchgfx::Slider&, const touchgfx::ClickEvent&> slider1ClickCallback;
};

#endif // NOTIFICATIONBARCONTAINER_HPP
