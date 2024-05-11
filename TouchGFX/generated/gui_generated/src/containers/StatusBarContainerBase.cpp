/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/StatusBarContainerBase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>

StatusBarContainerBase::StatusBarContainerBase()
{
    setWidth(800);
    setHeight(40);
    textArea1.setPosition(8, 8, 70, 24);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea1.setLinespacing(18);
    touchgfx::Unicode::snprintf(textArea1Buffer1, TEXTAREA1BUFFER1_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_MNB6).getText());
    textArea1.setWildcard1(textArea1Buffer1);
    touchgfx::Unicode::snprintf(textArea1Buffer2, TEXTAREA1BUFFER2_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_14IR).getText());
    textArea1.setWildcard2(textArea1Buffer2);
    textArea1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_LKQK));
    add(textArea1);

    textArea2.setPosition(87, 5, 30, 30);
    textArea2.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    textArea2.setLinespacing(0);
    Unicode::snprintf(textArea2Buffer, TEXTAREA2_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_T7GY).getText());
    textArea2.setWildcard(textArea2Buffer);
    textArea2.setTypedText(touchgfx::TypedText(T___SINGLEUSE_UTFJ));
    textArea2.setVisible(false);
    add(textArea2);

    boxProgress1.setXY(749, 10);
    boxProgress1.setProgressIndicatorPosition(2, 2, 36, 16);
    boxProgress1.setRange(0, 100);
    boxProgress1.setDirection(touchgfx::AbstractDirectionProgress::LEFT);
    boxProgress1.setBackground(touchgfx::Bitmap(BITMAP_BATTERY_BL_ID));
    boxProgress1.setColor(touchgfx::Color::getColorFromRGB(57, 189, 85));
    boxProgress1.setValue(44);
    add(boxProgress1);

    FPStextArea.setPosition(693, 8, 50, 24);
    FPStextArea.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    FPStextArea.setLinespacing(18);
    Unicode::snprintf(FPStextAreaBuffer, FPSTEXTAREA_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_0U6J).getText());
    FPStextArea.setWildcard(FPStextAreaBuffer);
    FPStextArea.setTypedText(touchgfx::TypedText(T___SINGLEUSE_B175));
    add(FPStextArea);

    textArea3.setPosition(126, 5, 30, 30);
    textArea3.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    textArea3.setLinespacing(0);
    Unicode::snprintf(textArea3Buffer, TEXTAREA3_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_JY7K).getText());
    textArea3.setWildcard(textArea3Buffer);
    textArea3.setTypedText(touchgfx::TypedText(T___SINGLEUSE_LUI0));
    add(textArea3);

    CPUtextArea.setPosition(562, 8, 125, 24);
    CPUtextArea.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    CPUtextArea.setLinespacing(18);
    touchgfx::Unicode::snprintf(CPUtextAreaBuffer1, CPUTEXTAREABUFFER1_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_TXO6).getText());
    CPUtextArea.setWildcard1(CPUtextAreaBuffer1);
    touchgfx::Unicode::snprintf(CPUtextAreaBuffer2, CPUTEXTAREABUFFER2_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_UUX3).getText());
    CPUtextArea.setWildcard2(CPUtextAreaBuffer2);
    CPUtextArea.setTypedText(touchgfx::TypedText(T___SINGLEUSE_EFTW));
    add(CPUtextArea);

    FantextureMapper.setXY(167, 4);
    FantextureMapper.setBitmap(touchgfx::Bitmap(BITMAP_VENTILATINGFANON_ID));
    FantextureMapper.setWidth(32);
    FantextureMapper.setHeight(32);
    FantextureMapper.setBitmapPosition(0.0f, 0.0f);
    FantextureMapper.setScale(1.0f);
    FantextureMapper.setCameraDistance(1000.0f);
    FantextureMapper.setOrigo(16.0f, 16.0f, 1000.0f);
    FantextureMapper.setCamera(16.0f, 16.0f);
    FantextureMapper.setAngles(0.0f, 0.0f, 11.0f);
    FantextureMapper.setRenderingAlgorithm(touchgfx::TextureMapper::BILINEAR_INTERPOLATION);
    FantextureMapper.setVisible(false);
    add(FantextureMapper);

touchgfx::Application::getInstance()->registerTimerWidget(this);
}

StatusBarContainerBase::~StatusBarContainerBase()
{
touchgfx::Application::getInstance()->unregisterTimerWidget(this);
}

void StatusBarContainerBase::initialize()
{

}

void StatusBarContainerBase::handleTickEvent()
{
    //Interaction2
    //When every N tick call virtual function
    //Call TickTrigger
    TickTrigger();
}
