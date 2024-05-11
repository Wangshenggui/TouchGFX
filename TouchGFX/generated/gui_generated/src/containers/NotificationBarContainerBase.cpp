/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/NotificationBarContainerBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

NotificationBarContainerBase::NotificationBarContainerBase() :
    Volume_Trigger1Callback(0),
    Fan_TriggerCallback(0),
    sliderValueChangedCallback(this, &NotificationBarContainerBase::sliderValueChangedCallbackHandler),
    sliderValueConfirmedCallback(this, &NotificationBarContainerBase::sliderValueConfirmedCallbackHandler),
    buttonCallback(this, &NotificationBarContainerBase::buttonCallbackHandler)
{
    setWidth(800);
    setHeight(480);
    box1.setPosition(0, 0, 800, 480);
    box1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    box1.setAlpha(200);
    add(box1);

    container1.setPosition(675, 128, 59, 302);
    slider1.setXY(0, 0);
    slider1.setBitmaps(touchgfx::Bitmap(BITMAP_BRIGHTNESS2_ID), touchgfx::Bitmap(BITMAP_BRIGHTNESS1_ID), touchgfx::Bitmap(BITMAP__BRIGHTNESS_ID));
    slider1.setupVerticalSlider(0, 0, 301, 0, 301);
    slider1.setValueRange(20, 693);
    slider1.setValue(200);
    slider1.setNewValueCallback(sliderValueChangedCallback);
    slider1.setStopValueCallback(sliderValueConfirmedCallback);
    container1.add(slider1);

    image1.setXY(5, 240);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_BACKLIGHT_ID));
    container1.add(image1);

    add(container1);

    container2.setPosition(553, 128, 59, 302);
    slider2.setXY(0, 0);
    slider2.setBitmaps(touchgfx::Bitmap(BITMAP_BRIGHTNESS2_ID), touchgfx::Bitmap(BITMAP_BRIGHTNESS1_ID), touchgfx::Bitmap(BITMAP__BRIGHTNESS_ID));
    slider2.setupVerticalSlider(0, 0, 301, 0, 301);
    slider2.setValueRange(0, 32);
    slider2.setValue(10);
    slider2.setStopValueCallback(sliderValueConfirmedCallback);
    slider2.setNewValueCallback(sliderValueChangedCallback);
    container2.add(slider2);

    textArea1.setPosition(8, 243, 42, 42);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(0, 163, 144));
    textArea1.setLinespacing(0);
    Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_GVSS).getText());
    textArea1.setWildcard(textArea1Buffer);
    textArea1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_M0OP));
    container2.add(textArea1);

    add(container2);

    toggleButton1.setXY(108, 146);
    toggleButton1.setBitmaps(touchgfx::Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_RE_SMALL_BUTTON_OFF_ID), touchgfx::Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_RE_SMALL_BUTTON_ON_ID));
    toggleButton1.setAction(buttonCallback);
    add(toggleButton1);

    toggleButton2.setXY(282, 146);
    toggleButton2.setBitmaps(touchgfx::Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_RE_SMALL_BUTTON_OFF_ID), touchgfx::Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_RE_SMALL_BUTTON_ON_ID));
    toggleButton2.setAction(buttonCallback);
    add(toggleButton2);
}

NotificationBarContainerBase::~NotificationBarContainerBase()
{

}

void NotificationBarContainerBase::initialize()
{

}

void NotificationBarContainerBase::sliderValueChangedCallbackHandler(const touchgfx::Slider& src, int value)
{
    if (&src == &slider1)
    {
        //Interaction1
        //When slider1 value changed call virtual function
        //Call slider1CallbackHandler
        slider1CallbackHandler(value);
    }
    if (&src == &slider2)
    {
        //Interaction3
        //When slider2 value changed call virtual function
        //Call slider2ChangeCallbackHandler
        slider2ChangeCallbackHandler(value);
    }
}

void NotificationBarContainerBase::sliderValueConfirmedCallbackHandler(const touchgfx::Slider& src, int value)
{
    if (&src == &slider2)
    {
        //Interaction2
        //When slider2 value confirmed call virtual function
        //Call slider2CallbackHandler
        slider2CallbackHandler(value);
    }
    if (&src == &slider1)
    {
        //Interaction4
        //When slider1 value confirmed call virtual function
        //Call slider1ConfirmedCallbackHandler
        slider1ConfirmedCallbackHandler(value);
    }
}

void NotificationBarContainerBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &toggleButton1)
    {
        //Interaction6
        //When toggleButton1 clicked call virtual function
        //Call toggleButton1Handler
        toggleButton1Handler();
    }
    if (&src == &toggleButton2)
    {
        //Interaction8
        //When toggleButton2 clicked call virtual function
        //Call toggleButton2Handler
        toggleButton2Handler();
    }
}