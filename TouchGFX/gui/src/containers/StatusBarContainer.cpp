#include <gui/containers/StatusBarContainer.hpp>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/Utils.hpp>

#include <gui/bootscreen_screen/BootScreenView.hpp>
#include <BitmapDatabase.hpp>
#include <gui/containers/NotificationBarContainer.hpp>


#ifndef SIMULATOR
#include "Voice.h"
#include "Radio.h"
#endif

StatusBarContainer::StatusBarContainer()
{
//    touchgfx_printf("StatusBarContainer\r\n");
    
    VoiceVolume = 0;

    //��ʾ���ߵ�ͼ��
    textArea2Buffer[0] = RadioIcon;
    textArea2Buffer[1] = 0;
    //    //��ȡ����״̬
    //    SetRadioColor(GetRadioState());
    //    textArea2.setVisible(true);
    //    textArea2.invalidate();

#ifndef SIMULATOR
    VoiceVolume = GetVoiceVolume();

    Unicode::snprintf(textArea1Buffer1, TEXTAREA1BUFFER1_SIZE, "%02d", Radio_GlobalVariableStruct.GPS_Tim[0]);
    Unicode::snprintf(textArea1Buffer2, TEXTAREA1BUFFER2_SIZE, "%02d", Radio_GlobalVariableStruct.GPS_Tim[1]);
    textArea1.invalidate();
#endif
    SetVolumeIconColor(VoiceVolume, 255, 0, 0);

    
    if(NotificationBarContainer().GetFanFlag() == 1 
        || NotificationBarContainer().GetFanFlag() == 11)
    {
        FantextureMapper.setBitmap(touchgfx::Bitmap(BITMAP_VENTILATINGFANON_ID));
    }
    else
    {
        FantextureMapper.setBitmap(touchgfx::Bitmap(BITMAP_VENTILATINGFANOFF_ID));
    }
    
    FantextureMapper.setZAngle(FanAngle);
    FantextureMapper.setVisible(true);
    FantextureMapper.invalidate();
    
}

void StatusBarContainer::initialize()
{
    StatusBarContainerBase::initialize();
}

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
//��������ͼ���������ɫ
void StatusBarContainer::SetVolumeIconColor(uint8_t Volume, uint8_t r, uint8_t g, uint8_t b)
{
    if (Volume == 0)
    {
        textArea3Buffer[0] = volume_iconx;
    }
    else if (Volume <= 8)
    {
        textArea3Buffer[0] = volume_icon1;
    }
    else if (Volume > 8 && Volume <= 16)
    {
        textArea3Buffer[0] = volume_icon2;
    }
    else if (Volume > 16 && Volume <= 24)
    {
        textArea3Buffer[0] = volume_icon2;
    }
    else if (Volume > 24)
    {
        textArea3Buffer[0] = volume_icon3;
    }
    //��ʾ����ͼ��
    textArea3Buffer[1] = 0;
    textArea3.setColor(touchgfx::Color::getColorFromRGB(r, g, b));
    textArea3.invalidate();
}

//��������ʱ�Ӻ�����������ɫ
void StatusBarContainer::SetDigClockColor(uint8_t r, uint8_t g, uint8_t b)
{
    textArea1.setColor(touchgfx::Color::getColorFromRGB(r, g, b));
    textArea1.invalidate();
    FPStextArea.setColor(touchgfx::Color::getColorFromRGB(r, g, b));
    FPStextArea.invalidate();
    CPUtextArea.setColor(touchgfx::Color::getColorFromRGB(r, g, b));
    CPUtextArea.invalidate();
}



//�������ߵ�ͼ����ɫ
void StatusBarContainer::SetRadioColor(uint8_t state)
{
    if (state == 1)
    {
        textArea2.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
    }
    else
    {
        textArea2.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    textArea2.invalidate();
}

//��������״̬
bool StatusBarContainer::GetRadioState()
{
    return RadioState;
}
void StatusBarContainer::SetRadioState(bool state)
{
    RadioState = state;
}
//������ʾ
void StatusBarContainer::SetRadioVisible(bool state)
{
    textArea2.setVisible(state);
    textArea2.invalidate();
}


//��ʾCPUռ�ú��¶�
void StatusBarContainer::SetCPU(uint8_t cpu, uint8_t temp)
{
    Unicode::snprintf(CPUtextAreaBuffer1, CPUTEXTAREABUFFER1_SIZE, "%d", cpu);
    Unicode::snprintf(CPUtextAreaBuffer2, CPUTEXTAREABUFFER2_SIZE, "%d", temp);
    CPUtextArea.invalidate();
}
//��ʾ֡��
void StatusBarContainer::SetFPS(uint8_t fps)
{
    Unicode::snprintf(FPStextAreaBuffer, FPSTEXTAREA_SIZE, "%d", fps);
    FPStextArea.invalidate();
}

//����ʱ��
void StatusBarContainer::UpdateTime()
{
#ifndef SIMULATOR
    Unicode::snprintf(textArea1Buffer1, TEXTAREA1BUFFER1_SIZE, "%02d", Radio_GlobalVariableStruct.GPS_Tim[0]);
    textArea1.invalidate();
    Unicode::snprintf(textArea1Buffer2, TEXTAREA1BUFFER2_SIZE, "%02d", Radio_GlobalVariableStruct.GPS_Tim[1]);
    textArea1.invalidate();
#endif
}


void StatusBarContainer::RadialFan()
{
    FantextureMapper.setZAngle(FanAngle += 0.07f);
    FantextureMapper.invalidate();
}

extern //С����ת����־
bool StatusFanRotateFlag;
void StatusBarContainer::TickTrigger()
{
    if(StatusFanRotateFlag == 0)
    {
        uint8_t num = NotificationBarContainer().GetFanFlag();
        if (num == 1)
        {
            FantextureMapper.setBitmap(touchgfx::Bitmap(BITMAP_VENTILATINGFANON_ID));
            NotificationBarContainer().SetFanFlag(11);
            
            RadialFan();
        }
        else if(num == 11)
        {
            RadialFan();
        }
        else if (num == 0)
        {
            NotificationBarContainer().SetFanFlag(2);
            FantextureMapper.setBitmap(touchgfx::Bitmap(BITMAP_VENTILATINGFANOFF_ID));
            FantextureMapper.invalidate();
        }
    }
}




