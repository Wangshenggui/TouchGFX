/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef NOTIFICATIONBARCONTAINERBASE_HPP
#define NOTIFICATIONBARCONTAINERBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/mixins/ClickListener.hpp>
#include <touchgfx/containers/CacheableContainer.hpp>
#include <touchgfx/containers/Slider.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/ToggleButton.hpp>

class NotificationBarContainerBase : public touchgfx::Container
{
public:
    NotificationBarContainerBase();
    virtual ~NotificationBarContainerBase();
    virtual void initialize();

    /*
     * Custom Trigger Callback Setters
     */
    void setVolume_Trigger1Callback(touchgfx::GenericCallback<uint8_t>& callback)
    {
        this->Volume_Trigger1Callback = &callback;
    }
    void setFan_TriggerCallback(touchgfx::GenericCallback<bool>& callback)
    {
        this->Fan_TriggerCallback = &callback;
    }

    /*
     * Virtual Action Handlers
     */
    virtual void slider1CallbackHandler(int value)
    {
        // Override and implement this function in NotificationBarContainer
    }
    virtual void slider2CallbackHandler(int value)
    {
        // Override and implement this function in NotificationBarContainer
    }
    virtual void slider2ChangeCallbackHandler(int value)
    {
        // Override and implement this function in NotificationBarContainer
    }
    virtual void slider1ConfirmedCallbackHandler(int value)
    {
        // Override and implement this function in NotificationBarContainer
    }
    virtual void toggleButton1Handler()
    {
        // Override and implement this function in NotificationBarContainer
    }
    virtual void toggleButton2Handler()
    {
        // Override and implement this function in NotificationBarContainer
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Custom Trigger Emitters
     */
    virtual void emitVolume_Trigger1Callback(uint8_t value)
    {
        if (Volume_Trigger1Callback && Volume_Trigger1Callback->isValid())
        {
            this->Volume_Trigger1Callback->execute( value);
        }
    }
    virtual void emitFan_TriggerCallback(bool value)
    {
        if (Fan_TriggerCallback && Fan_TriggerCallback->isValid())
        {
            this->Fan_TriggerCallback->execute( value);
        }
    }

    /*
     * Member Declarations
     */
    touchgfx::ClickListener< touchgfx::Box > box1;
    touchgfx::CacheableContainer container1;
    touchgfx::ClickListener< touchgfx::Slider > slider1;
    touchgfx::Image image1;
    touchgfx::CacheableContainer container2;
    touchgfx::Slider slider2;
    touchgfx::TextAreaWithOneWildcard textArea1;
    touchgfx::ToggleButton toggleButton1;
    touchgfx::ToggleButton toggleButton2;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXTAREA1_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea1Buffer[TEXTAREA1_SIZE];

private:

    /*
     * Custom Trigger Callback Declarations
     */
    touchgfx::GenericCallback<uint8_t>* Volume_Trigger1Callback;
    touchgfx::GenericCallback<bool>* Fan_TriggerCallback;

    /*
     * Callback Declarations
     */
    touchgfx::Callback<NotificationBarContainerBase, const touchgfx::Slider&, int> sliderValueChangedCallback;
    touchgfx::Callback<NotificationBarContainerBase, const touchgfx::Slider&, int> sliderValueConfirmedCallback;
    touchgfx::Callback<NotificationBarContainerBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void sliderValueChangedCallbackHandler(const touchgfx::Slider& src, int value);
    void sliderValueConfirmedCallbackHandler(const touchgfx::Slider& src, int value);
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // NOTIFICATIONBARCONTAINERBASE_HPP