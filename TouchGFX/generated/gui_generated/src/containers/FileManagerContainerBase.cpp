/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/FileManagerContainerBase.hpp>
#include <images/BitmapDatabase.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>

FileManagerContainerBase::FileManagerContainerBase() :
    flexButtonCallback(this, &FileManagerContainerBase::flexButtonCallbackHandler)
{
    setWidth(750);
    setHeight(60);
    boxProgress1.setXY(283, 20);
    boxProgress1.setProgressIndicatorPosition(2, 2, 180, 16);
    boxProgress1.setRange(0, 100);
    boxProgress1.setDirection(touchgfx::AbstractDirectionProgress::RIGHT);
    boxProgress1.setBackground(touchgfx::Bitmap(BITMAP_BLUE_PROGRESSINDICATORS_BG_MEDIUM_PROGRESS_INDICATOR_BG_SQUARE_0_DEGREES_ID));
    boxProgress1.setColor(touchgfx::Color::getColorFromRGB(0, 151, 255));
    boxProgress1.setValue(60);
    boxProgress1.setAlpha(0);
    boxProgress1.setVisible(false);
    add(boxProgress1);

    box1.setPosition(0, 0, 750, 60);
    box1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    box1.setVisible(false);
    add(box1);

    flexButton1.setBoxWithBorderPosition(0, 0, 750, 60);
    flexButton1.setBorderSize(0);
    flexButton1.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(30, 30, 30), touchgfx::Color::getColorFromRGB(124, 178, 196), touchgfx::Color::getColorFromRGB(30, 30, 30), touchgfx::Color::getColorFromRGB(255, 255, 255));
    flexButton1.setBitmaps(Bitmap(BITMAP_RIGHT_ID), Bitmap(BITMAP_RIGHT_ID));
    flexButton1.setBitmapXY(715, 14);
    flexButton1.setAction(flexButtonCallback);
    flexButton1.setPosition(0, 0, 750, 60);
    add(flexButton1);

    textArea1.setPosition(61, 10, 655, 40);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea1.setLinespacing(0);
    Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_CPZ3).getText());
    textArea1.setWildcard(textArea1Buffer);
    textArea1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_14O3));
    add(textArea1);

    image1.setXY(7, 6);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_PAPER_FILE_ID));
    add(image1);
}

FileManagerContainerBase::~FileManagerContainerBase()
{

}

void FileManagerContainerBase::initialize()
{

}

void FileManagerContainerBase::flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src)
{
    if (&src == &flexButton1)
    {
        //Interaction1
        //When flexButton1 clicked call virtual function
        //Call deleteAction
        deleteAction();
    }
}
