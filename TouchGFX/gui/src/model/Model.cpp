#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <gui/bootscreen_screen/BootScreenView.hpp>

#ifndef SIMULATOR
#include "cmsis_os.h"
#include "main.h"

extern osMessageQId GUI_ControlTaskQueueHandle;
extern osMessageQId Task_ControlGUIQueueHandle;
extern EventGroupHandle_t IWDG_Event;//�����¼�����
#endif

Model::Model() : modelListener(0)
{

}

void Model::tick()
{
#ifndef SIMULATOR
    osEvent key;
    key = osMessageGet(Task_ControlGUIQueueHandle, 0);
    if (key.status == osEventMessage)
    {
        modelListener->TaskContGUIQueue_Event(key.value.v);
    }

    //����¼���
    xEventGroupSetBits(IWDG_Event, IWDG_Event_1);
#else
    //touchgfx_printf("+");
#endif
}

////////////////////////////////////////////////////////////////////////////////////
//���ڼ���FPS
unsigned int Model::getLCDfps()
{
    //����FPS
    (HAL::getInstance()->getLCDRefreshCount() > 1) ? public_var.frameSkippedCounter++ : public_var.frames++;
    if (public_var.frames + public_var.frameSkippedCounter >= 60)
    {
        public_var.fps = public_var.frames;
        public_var.frameSkippedCounter = 0;
        public_var.frames = 0;
    }
    return public_var.fps;
}

//�������ȷ���
void Model::set_fan_onoff(bool data)
{
    if (data == 0)
    {
#ifndef SIMULATOR
        osMessagePut(GUI_ControlTaskQueueHandle, GUIConTaskQueFanOFF, osWaitForever);//����������Ϣ����
#else
        touchgfx_printf("�رշ���\r\n");
#endif
    }
    else if (data == 1)
    {
#ifndef SIMULATOR
        osMessagePut(GUI_ControlTaskQueueHandle, GUIConTaskQueFanON, osWaitForever);//����������Ϣ����
#else
        touchgfx_printf("�򿪷���\r\n");
#endif
    }
}
//����NES
void Model::start_nes(bool data)
{
    if (data == 0)
    {

    }
    else if (data == 1)
    {
#ifndef SIMULATOR
        osMessagePut(GUI_ControlTaskQueueHandle, GUIConTaskQueNESStart, osWaitForever);//����������Ϣ����
#else
        touchgfx_printf("����NES\r\n");
#endif
    }
}






