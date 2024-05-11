/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef NESSCREENVIEWBASE_HPP
#define NESSCREENVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/nesscreen_screen/NESScreenPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <gui/containers/NESContainer.hpp>

class NESScreenViewBase : public touchgfx::View<NESScreenPresenter>
{
public:
    NESScreenViewBase();
    virtual ~NESScreenViewBase();
    virtual void setupScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    NESContainer nESContainer1;

private:

};

#endif // NESSCREENVIEWBASE_HPP