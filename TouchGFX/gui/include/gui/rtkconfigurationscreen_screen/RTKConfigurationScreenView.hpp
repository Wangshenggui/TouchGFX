#ifndef RTKCONFIGURATIONSCREENVIEW_HPP
#define RTKCONFIGURATIONSCREENVIEW_HPP

#include <gui_generated/rtkconfigurationscreen_screen/RTKConfigurationScreenViewBase.hpp>
#include <gui/rtkconfigurationscreen_screen/RTKConfigurationScreenPresenter.hpp>




class RTKConfigurationScreenView : public RTKConfigurationScreenViewBase
{
public:
    RTKConfigurationScreenView();
    virtual ~RTKConfigurationScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
        
    virtual void portflexButtonHandler();
    virtual void setButton1Handler();
    virtual void inquireButton1Handler();
    virtual void setButton2Handler();
    virtual void inquireButton2Handler();
    virtual void ButtonAction1(uint8_t value);
    virtual void BackButtonTrigger(bool Flag);
    virtual void NtripflexButtonHandler();
    virtual void NtripflexButtonUserHandler();
    virtual void NtripflexButtonPasswordHandler();
        
    virtual void handleClickEvent(const ClickEvent& event);
    virtual void handleTickEvent();

#ifndef SIMULATOR
    virtual void FatFsSave();
#endif
protected:
    //����ʱ��
    uint16_t RTKConfigurationTimer1;
    uint16_t RTKConfigurationTimer2;
    //��¼��������������
    uint8_t InputFieldIndex;
};

#endif // RTKCONFIGURATIONSCREENVIEW_HPP
