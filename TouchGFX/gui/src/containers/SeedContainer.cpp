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
    //    //��ȡ���⣬������
    //    SetBacklight(GetBacklight());

    //    //��ȡ������������
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
//�������Ӳֺ���
void SeedContainer::SetTextArea1Num(uint8_t num)
{
    Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%d", num);
    textArea1.invalidate();
}
//����M1ת��
void SeedContainer::SetM1Rpm(uint16_t rpm)
{
    Unicode::snprintf(textArea2Buffer, TEXTAREA2_SIZE, "%d", rpm);
    textArea2.invalidate();
}
//����M2ת��
void SeedContainer::SetM2Rpm(uint16_t rpm)
{
    Unicode::snprintf(textArea3Buffer, TEXTAREA3_SIZE, "%d", rpm);
    textArea3.invalidate();
}


/*
0���ϵ�
1��ͨ��
2������
3������
4��û������
*/
void SeedContainer::SetRunState(uint8_t state)
{
    switch (state)
    {
    case(0):
        textArea4Buffer[0] = 0x79bb;
        textArea4Buffer[1] = 0x7ebf;
        textArea4Buffer[2] = 0;
        textArea4.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));//��ɫ
        textArea4.invalidate();
        circle1.setVisible(true);
        circle1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));//��ɫ
        circle1.invalidate();
        break;
    case(1):
        textArea4Buffer[0] = 0x7535;
        textArea4Buffer[1] = 0x6e90;
        textArea4Buffer[2] = 0;
        textArea4.setColor(touchgfx::Color::getColorFromRGB(0, 0, 255));//��ɫ
        textArea4.invalidate();
        circle1.setVisible(true);
        circle1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 255));//��ɫ
        circle1.invalidate();
        break;
    case(2):
        textArea4Buffer[0] = 0x8fd0;
        textArea4Buffer[1] = 0x884c;
        textArea4Buffer[2] = 0;
        textArea4.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));//��ɫ
        textArea4.invalidate();
        circle1.setVisible(true);
        circle1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));//��ɫ
        circle1.invalidate();
        break;
    case(3):
        textArea4Buffer[0] = 0x6545;
        textArea4Buffer[1] = 0x969c;
        textArea4Buffer[2] = 0;
        textArea4.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));//��ɫ
        textArea4.invalidate();
        circle1.setVisible(true);
        circle1Painter.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));//��ɫ
        circle1.invalidate();
        break;
    case(4):
        textArea4Buffer[0] = 0x7a7a;
        textArea4Buffer[1] = 0x4ed3;
        textArea4Buffer[2] = 0;
        textArea4.setColor(touchgfx::Color::getColorFromRGB(255, 255, 50));//��ɫ
        textArea4.invalidate();
        circle1.setVisible(true);
        circle1Painter.setColor(touchgfx::Color::getColorFromRGB(255, 255, 50));//��ɫ
        circle1.invalidate();
        break;
    }
}






