#ifndef RADIOSSCOM_SCREENVIEW_HPP
#define RADIOSSCOM_SCREENVIEW_HPP

#include <gui_generated/radiosscom_screen_screen/RadioSSCOM_ScreenViewBase.hpp>
#include <gui/radiosscom_screen_screen/RadioSSCOM_ScreenPresenter.hpp>

class RadioSSCOM_ScreenView : public RadioSSCOM_ScreenViewBase
{
public:
    RadioSSCOM_ScreenView();
    virtual ~RadioSSCOM_ScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
        
    virtual void TextAreaAddStr(uint8_t* str, uint32_t len);
        virtual void TextArea2AddStr(uint8_t* str, uint32_t len);
        virtual void TextArea3AddStr(uint8_t* str, uint32_t len);
        virtual void TextArea4AddStr(uint8_t* str, uint32_t len);
        virtual void TextArea5AddStr(uint8_t* str, uint32_t len);
        virtual void TextArea6AddStr(uint8_t* str, uint32_t len);
        
        virtual void TextArea3_1AddStr(uint8_t* str, uint32_t len);
        virtual void TextArea4_1AddStr(uint8_t* str, uint32_t len);
        virtual void TextArea5_1AddStr(uint8_t* str, uint32_t len);
        
        double to_radians(double degree);
        double vincenty_distance(double lat1, double lon1, double lat2, double lon2);
        
    virtual void handleTickEvent();
protected:
};

#endif // RADIOSSCOM_SCREENVIEW_HPP
