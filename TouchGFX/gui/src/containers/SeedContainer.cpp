#include <gui/containers/SeedContainer.hpp>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/Color.hpp>

#ifndef SIMULATOR
#include "Backlight.h"
#include "Voice.h"
#endif


SeedContainer::SeedContainer()
{
#ifndef SIMULATOR
    //    //获取背光，并设置
    //    SetBacklight(GetBacklight());

    //    //获取音量，并设置
    //    SetVoiceVolume(GetVoiceVolume());
#endif
}

void SeedContainer::initialize()
{
    SeedContainerBase::initialize();
}

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
//设置种子仓号码
void SeedContainer::SetTextArea1Num(uint8_t num)
{
    Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%d", num);
    textArea1.invalidate();
}
//设置M1转速
void SeedContainer::SetM1Rpm(uint16_t rpm)
{
    Unicode::snprintf(textArea2Buffer, TEXTAREA2_SIZE, "%d", rpm);
    textArea2.invalidate();
}
//设置M2转速
void SeedContainer::SetM2Rpm(uint16_t rpm)
{
    Unicode::snprintf(textArea3Buffer, TEXTAREA3_SIZE, "%d", rpm);
    textArea3.invalidate();
}


/*
0：断电
1：通电
2：运行
3：故障
4：没有种子
*/
void SeedContainer::SetRunState(uint8_t state)
{
    switch (state)
    {
    case(0):
        textArea4Buffer[0] = 0x79bb;
        textArea4Buffer[1] = 0x7ebf;
        textArea4Buffer[2] = 0;
        textArea4.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));//黑色
        textArea4.invalidate();
        circle1.setVisible(true);
        circle1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));//黑色
        circle1.invalidate();
        break;
    case(1):
        textArea4Buffer[0] = 0x7535;
        textArea4Buffer[1] = 0x6e90;
        textArea4Buffer[2] = 0;
        textArea4.setColor(touchgfx::Color::getColorFromRGB(0, 0, 255));//蓝色
        textArea4.invalidate();
        circle1.setVisible(true);
        circle1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 255));//蓝色
        circle1.invalidate();
        break;
    case(2):
        textArea4Buffer[0] = 0x8fd0;
        textArea4Buffer[1] = 0x884c;
        textArea4Buffer[2] = 0;
        textArea4.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));//绿色
        textArea4.invalidate();
        circle1.setVisible(true);
        circle1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));//绿色
        circle1.invalidate();
        break;
    case(3):
        textArea4Buffer[0] = 0x6545;
        textArea4Buffer[1] = 0x969c;
        textArea4Buffer[2] = 0;
        textArea4.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));//红色
        textArea4.invalidate();
        circle1.setVisible(true);
        circle1Painter.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));//红色
        circle1.invalidate();
        break;
    case(4):
        textArea4Buffer[0] = 0x7a7a;
        textArea4Buffer[1] = 0x4ed3;
        textArea4Buffer[2] = 0;
        textArea4.setColor(touchgfx::Color::getColorFromRGB(255, 255, 50));//黄色
        textArea4.invalidate();
        circle1.setVisible(true);
        circle1Painter.setColor(touchgfx::Color::getColorFromRGB(255, 255, 50));//黄色
        circle1.invalidate();
        break;
    }
}






