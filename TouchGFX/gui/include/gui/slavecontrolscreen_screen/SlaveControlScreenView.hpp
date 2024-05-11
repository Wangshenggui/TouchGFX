#ifndef SLAVECONTROLSCREENVIEW_HPP
#define SLAVECONTROLSCREENVIEW_HPP

#include <gui_generated/slavecontrolscreen_screen/SlaveControlScreenViewBase.hpp>
#include <gui/slavecontrolscreen_screen/SlaveControlScreenPresenter.hpp>

class SlaveControlScreenView : public SlaveControlScreenViewBase
{
public:
    SlaveControlScreenView();
    virtual ~SlaveControlScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
        
    virtual void flexButton1Handler();
    virtual void flexButton2Handler();
    virtual void flexButton3Handler();
    virtual void flexButton4Handler();
    virtual void flexButton5Handler();
    virtual void flexButton6Handler();
    virtual void flexButton7Handler();
    virtual void flexButton8Handler();
    virtual void flexButton9Handler();
    virtual void flexButton10Handler();
    virtual void flexButton11Handler();
    virtual void flexButton12Handler();
        
        
    virtual void handleTickEvent();
protected:
    uint8_t ButBit;
    uint8_t Buf[100];
    uint8_t UARTSend_n;
    bool Dir;
};

#endif // SLAVECONTROLSCREENVIEW_HPP
