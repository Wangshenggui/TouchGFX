/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/filemanagerscreen_screen/FileManagerScreenViewBase.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <images/BitmapDatabase.hpp>

FileManagerScreenViewBase::FileManagerScreenViewBase() :
    navigationBarContainerBackMenuTriggerCallback(this, &FileManagerScreenViewBase::navigationBarContainerBackMenuTriggerCallbackHandler),
    buttonCallback(this, &FileManagerScreenViewBase::buttonCallbackHandler)
{
    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);
    
    __background.setPosition(0, 0, 800, 480);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    scrollableContainer1.setPosition(0, 40, 750, 440);
    scrollableContainer1.setScrollbarsColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    scrollableContainer1.setScrollbarsAlpha(255);
    scrollableContainer1.setScrollbarsPermanentlyVisible();
    listLayout1.setPosition(0, 0, 250, 250);
    listLayout1.setDirection(touchgfx::SOUTH);
    scrollableContainer1.add(listLayout1);

    add(scrollableContainer1);

    textArea1.setXY(0, 0);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(0, 255, 225));
    textArea1.setLinespacing(0);
    textArea1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_MIRK));
    add(textArea1);

    textArea2.setPosition(120, 0, 630, 40);
    textArea2.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea2.setLinespacing(0);
    Unicode::snprintf(textArea2Buffer, TEXTAREA2_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_IDO9).getText());
    textArea2.setWildcard(textArea2Buffer);
    textArea2.setTypedText(touchgfx::TypedText(T___SINGLEUSE_D34Z));
    textArea2.setVisible(false);
    add(textArea2);

    navigationBarContainer.setXY(750, 0);
    navigationBarContainer.setBackMenuTriggerCallback(navigationBarContainerBackMenuTriggerCallback);
    add(navigationBarContainer);

    container1.setPosition(0, 0, 800, 480);
    container1.setVisible(false);
    bookStarContainer.setXY(0, 0);
    container1.add(bookStarContainer);

    button1.setXY(681, 56);
    button1.setBitmaps(touchgfx::Bitmap(BITMAP_ERROR_ID), touchgfx::Bitmap(BITMAP_ERROR_ID));
    button1.setAction(buttonCallback);
    container1.add(button1);

    add(container1);

    keyBoardContainer1.setXY(216, 140);
    keyBoardContainer1.setVisible(false);
    add(keyBoardContainer1);
}

FileManagerScreenViewBase::~FileManagerScreenViewBase()
{
    touchgfx::CanvasWidgetRenderer::resetBuffer();
}

void FileManagerScreenViewBase::setupScreen()
{
    navigationBarContainer.initialize();
    bookStarContainer.initialize();
    keyBoardContainer1.initialize();
}

void FileManagerScreenViewBase::navigationBarContainerBackMenuTriggerCallbackHandler(uint8_t value)
{
    //Interaction1
    //When navigationBarContainer BackMenuTrigger call virtual function
    //Call BackMenuHandler
    BackMenuHandler(value);
}

void FileManagerScreenViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &button1)
    {
        //Interaction2
        //When button1 clicked execute C++ code
        //Execute C++ code
        container1.setVisible(false);
        container1.invalidate();
    }
}
