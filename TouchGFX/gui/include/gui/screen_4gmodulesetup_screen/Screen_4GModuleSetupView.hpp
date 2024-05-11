#ifndef SCREEN_4GMODULESETUPVIEW_HPP
#define SCREEN_4GMODULESETUPVIEW_HPP

#include <gui_generated/screen_4gmodulesetup_screen/Screen_4GModuleSetupViewBase.hpp>
#include <gui/screen_4gmodulesetup_screen/Screen_4GModuleSetupPresenter.hpp>

class Screen_4GModuleSetupView : public Screen_4GModuleSetupViewBase
{
public:
    Screen_4GModuleSetupView();
    virtual ~Screen_4GModuleSetupView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
        
    virtual void scrollWheel1UpdateItem(Setup4GContainer1& item, int16_t itemIndex);
    virtual void scrollWheel1UpdateCenterItem(Setup4GContainer2& item, int16_t itemIndex);
    
    virtual void scrollWheel2UpdateItem(Setup4GContainer1& item, int16_t itemIndex);
    virtual void scrollWheel2UpdateCenterItem(Setup4GContainer2& item, int16_t itemIndex);

    virtual void scrollWheel3UpdateItem(Setup4GContainer1& item, int16_t itemIndex);
    virtual void scrollWheel3UpdateCenterItem(Setup4GContainer2& item, int16_t itemIndex);
        
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
    virtual void flexButton13Handler();
    virtual void flexButton14Handler();
    virtual void flexButton15Handler();
    virtual void flexButton16Handler();
    virtual void flexButton17Handler();
    virtual void flexButton18Handler();
    virtual void flexButton19Handler();
    virtual void flexButton20Handler();
    

    
    
    virtual void handleClickEvent(const ClickEvent& event);
protected:
    uint8_t item_x[3];//¼ÇÂ¼¹öÂÖË÷Òý
    char Wheel_str[3][50];
    char Str[50];
    
    // Callback which is executed when a item in the scroll whell is selected to as selected style.
    // The parameter itemSelected is the selected item.
    Callback<Screen_4GModuleSetupView, int16_t> scrollWheel1AnimateToCallback;
    void scrollWheel1AnimateToHandler(int16_t itemSelected);

    // Callback which is executed when a item in the scroll whell is selected to as selected style.
    // The parameter itemSelected is the selected item.
    Callback<Screen_4GModuleSetupView, int16_t> scrollWheel2AnimateToCallback;
    void scrollWheel2AnimateToHandler(int16_t itemSelected);

    // Callback which is executed when a item in the scroll whell is selected to as selected style.
    // The parameter itemSelected is the selected item.
    Callback<Screen_4GModuleSetupView, int16_t> scrollWheel3AnimateToCallback;
    void scrollWheel3AnimateToHandler(int16_t itemSelected);
};

#endif // SCREEN_4GMODULESETUPVIEW_HPP
