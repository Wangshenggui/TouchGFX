/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/nesscreen_screen/NESScreenViewBase.hpp>
#include <touchgfx/Color.hpp>

NESScreenViewBase::NESScreenViewBase()
{
    __background.setPosition(0, 0, 800, 480);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    nESContainer1.setXY(0, 0);
    add(nESContainer1);
}

NESScreenViewBase::~NESScreenViewBase()
{

}

void NESScreenViewBase::setupScreen()
{
    nESContainer1.initialize();
}