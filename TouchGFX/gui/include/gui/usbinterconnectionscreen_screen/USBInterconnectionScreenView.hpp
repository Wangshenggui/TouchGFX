#ifndef USBINTERCONNECTIONSCREENVIEW_HPP
#define USBINTERCONNECTIONSCREENVIEW_HPP

#include <gui_generated/usbinterconnectionscreen_screen/USBInterconnectionScreenViewBase.hpp>
#include <gui/usbinterconnectionscreen_screen/USBInterconnectionScreenPresenter.hpp>

class USBInterconnectionScreenView : public USBInterconnectionScreenViewBase
{
public:
    USBInterconnectionScreenView();
    virtual ~USBInterconnectionScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();
    virtual void SetConnectionStatus(uint8_t m);
    virtual void USB_State(uint8_t n);
    virtual void handleClickEvent(const ClickEvent& event);
    virtual void flexButton1Handler();
protected:
    Model Model;
};

#endif // USBINTERCONNECTIONSCREENVIEW_HPP
