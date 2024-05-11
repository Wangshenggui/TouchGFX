/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SLAVECONTROLSCREENVIEWBASE_HPP
#define SLAVECONTROLSCREENVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/slavecontrolscreen_screen/SlaveControlScreenPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/containers/buttons/Buttons.hpp>
#include <gui/containers/NavigationBarContainer.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

class SlaveControlScreenViewBase : public touchgfx::View<SlaveControlScreenPresenter>
{
public:
    SlaveControlScreenViewBase();
    virtual ~SlaveControlScreenViewBase();
    virtual void setupScreen();

    /*
     * Virtual Action Handlers
     */
    virtual void flexButton1Handler()
    {
        // Override and implement this function in SlaveControlScreen
    }
    virtual void flexButton2Handler()
    {
        // Override and implement this function in SlaveControlScreen
    }
    virtual void flexButton3Handler()
    {
        // Override and implement this function in SlaveControlScreen
    }
    virtual void flexButton4Handler()
    {
        // Override and implement this function in SlaveControlScreen
    }
    virtual void flexButton5Handler()
    {
        // Override and implement this function in SlaveControlScreen
    }
    virtual void flexButton6Handler()
    {
        // Override and implement this function in SlaveControlScreen
    }
    virtual void flexButton7Handler()
    {
        // Override and implement this function in SlaveControlScreen
    }
    virtual void flexButton8Handler()
    {
        // Override and implement this function in SlaveControlScreen
    }
    virtual void flexButton9Handler()
    {
        // Override and implement this function in SlaveControlScreen
    }
    virtual void flexButton10Handler()
    {
        // Override and implement this function in SlaveControlScreen
    }
    virtual void flexButton11Handler()
    {
        // Override and implement this function in SlaveControlScreen
    }
    virtual void flexButton12Handler()
    {
        // Override and implement this function in SlaveControlScreen
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Box box1;
    touchgfx::Container container1;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ToggleButtonTrigger >  flexButton1;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ToggleButtonTrigger >  flexButton2;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ToggleButtonTrigger >  flexButton3;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ToggleButtonTrigger >  flexButton4;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ToggleButtonTrigger >  flexButton5;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ToggleButtonTrigger >  flexButton6;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ToggleButtonTrigger >  flexButton7;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ToggleButtonTrigger >  flexButton8;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  flexButton9;
    NavigationBarContainer navigationBarContainer1;
    touchgfx::Container container2;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::RepeatButtonTrigger >  flexButton10;
    touchgfx::TextAreaWithOneWildcard textArea1;
    touchgfx::TextButtonStyle< touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  >  flexButton11;
    touchgfx::WildcardTextButtonStyle< touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  >  flexButton12;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXTAREA1_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea1Buffer[TEXTAREA1_SIZE];
    static const uint16_t FLEXBUTTON12_SIZE = 10;
    touchgfx::Unicode::UnicodeChar flexButton12Buffer[FLEXBUTTON12_SIZE];

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<SlaveControlScreenViewBase, const touchgfx::AbstractButtonContainer&> flexButtonCallback;

    /*
     * Callback Handler Declarations
     */
    void flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src);

};

#endif // SLAVECONTROLSCREENVIEWBASE_HPP