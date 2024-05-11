/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/SeedContainerBase.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>

SeedContainerBase::SeedContainerBase()
{
    setWidth(185);
    setHeight(175);
    box1.setPosition(0, 0, 185, 175);
    box1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    add(box1);

    textArea1.setPosition(32, 7, 120, 32);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(67, 100, 247));
    textArea1.setLinespacing(0);
    Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_V804).getText());
    textArea1.setWildcard(textArea1Buffer);
    textArea1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_CAR4));
    add(textArea1);

    line1.setPosition(0, 45, 185, 1);
    line1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line1.setPainter(line1Painter);
    line1.setStart(0, 0);
    line1.setEnd(185, 0);
    line1.setLineWidth(1);
    line1.setLineEndingStyle(touchgfx::Line::ROUND_CAP_ENDING);
    add(line1);

    textArea2.setPosition(0, 52, 185, 28);
    textArea2.setColor(touchgfx::Color::getColorFromRGB(4, 130, 38));
    textArea2.setLinespacing(0);
    Unicode::snprintf(textArea2Buffer, TEXTAREA2_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_E1YW).getText());
    textArea2.setWildcard(textArea2Buffer);
    textArea2.setTypedText(touchgfx::TypedText(T___SINGLEUSE_X0ZA));
    add(textArea2);

    textArea3.setPosition(0, 85, 185, 28);
    textArea3.setColor(touchgfx::Color::getColorFromRGB(0, 104, 168));
    textArea3.setLinespacing(0);
    Unicode::snprintf(textArea3Buffer, TEXTAREA3_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_RYTC).getText());
    textArea3.setWildcard(textArea3Buffer);
    textArea3.setTypedText(touchgfx::TypedText(T___SINGLEUSE_V3E1));
    add(textArea3);

    circle1.setPosition(12, 126, 40, 40);
    circle1.setCenter(20, 20);
    circle1.setRadius(20);
    circle1.setLineWidth(0);
    circle1.setArc(0, 360);
    circle1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 255));
    circle1.setPainter(circle1Painter);
    add(circle1);

    textArea4.setPosition(58, 130, 120, 32);
    textArea4.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    textArea4.setLinespacing(0);
    Unicode::snprintf(textArea4Buffer, TEXTAREA4_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_AT5S).getText());
    textArea4.setWildcard(textArea4Buffer);
    textArea4.setTypedText(touchgfx::TypedText(T___SINGLEUSE_KDTK));
    add(textArea4);
}

SeedContainerBase::~SeedContainerBase()
{

}

void SeedContainerBase::initialize()
{

}