#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <gui/bootscreen_screen/BootScreenView.hpp>

#ifndef SIMULATOR
#include "cmsis_os.h"
#include "main.h"

extern osMessageQId GUI_ControlTaskQueueHandle;
extern osMessageQId Task_ControlGUIQueueHandle;
extern EventGroupHandle_t IWDG_Event;//创建事件组句柄
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

    //标记事件组
    xEventGroupSetBits(IWDG_Event, IWDG_Event_1);
#else
    //touchgfx_printf("+");
#endif
}

////////////////////////////////////////////////////////////////////////////////////
//用于计算FPS
unsigned int Model::getLCDfps()
{
    //计算FPS
    (HAL::getInstance()->getLCDRefreshCount() > 1) ? public_var.frameSkippedCounter++ : public_var.frames++;
    if (public_var.frames + public_var.frameSkippedCounter >= 60)
    {
        public_var.fps = public_var.frames;
        public_var.frameSkippedCounter = 0;
        public_var.frames = 0;
    }
    return public_var.fps;
}

//控制扇热风扇
void Model::set_fan_onoff(bool data)
{
    if (data == 0)
    {
#ifndef SIMULATOR
        osMessagePut(GUI_ControlTaskQueueHandle, GUIConTaskQueFanOFF, osWaitForever);//阻塞发送消息队列
#else
        touchgfx_printf("关闭风扇\r\n");
#endif
    }
    else if (data == 1)
    {
#ifndef SIMULATOR
        osMessagePut(GUI_ControlTaskQueueHandle, GUIConTaskQueFanON, osWaitForever);//阻塞发送消息队列
#else
        touchgfx_printf("打开风扇\r\n");
#endif
    }
}
//启动NES
void Model::start_nes(bool data)
{
    if (data == 0)
    {

    }
    else if (data == 1)
    {
#ifndef SIMULATOR
        osMessagePut(GUI_ControlTaskQueueHandle, GUIConTaskQueNESStart, osWaitForever);//阻塞发送消息队列
#else
        touchgfx_printf("启动NES\r\n");
#endif
    }
}






