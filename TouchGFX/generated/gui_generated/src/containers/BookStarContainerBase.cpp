/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/BookStarContainerBase.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>

BookStarContainerBase::BookStarContainerBase()
{
    setWidth(800);
    setHeight(480);
    box2.setPosition(0, 0, 800, 480);
    box2.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    box2.setAlpha(0);
    add(box2);

    container1.setPosition(0, 0, 800, 480);
    box1.setPosition(78, 56, 644, 368);
    box1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    container1.add(box1);

    boxWithBorder1.setPosition(78, 56, 644, 41);
    boxWithBorder1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    boxWithBorder1.setBorderColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    boxWithBorder1.setBorderSize(1);
    container1.add(boxWithBorder1);

    textArea2.setXY(83, 61);
    textArea2.setColor(touchgfx::Color::getColorFromRGB(0, 255, 110));
    textArea2.setLinespacing(0);
    textArea2.setTypedText(touchgfx::TypedText(T___SINGLEUSE_4Y79));
    container1.add(textArea2);

    scrollableContainer1.setPosition(83, 108, 634, 309);
    scrollableContainer1.setScrollbarsColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    scrollableContainer1.setScrollbarsAlpha(255);
    textArea1.setPosition(0, 5, 634, 5000);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea1.setLinespacing(0);
    Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_VHYM).getText());
    textArea1.setWildcard(textArea1Buffer);
    textArea1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_JURT));
    scrollableContainer1.add(textArea1);

    container1.add(scrollableContainer1);

    add(container1);
}

BookStarContainerBase::~BookStarContainerBase()
{

}

void BookStarContainerBase::initialize()
{

}