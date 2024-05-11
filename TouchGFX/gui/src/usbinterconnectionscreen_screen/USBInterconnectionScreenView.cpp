#include <gui/usbinterconnectionscreen_screen/USBInterconnectionScreenView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/Unicode.hpp>
#include <gui/bootscreen_screen/BootScreenView.hpp>


#ifndef SIMULATOR
#include "FreeRTOS.h"
#include "task.h"
#include "tim.h"

#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_msc.h"
#include "usbd_storage.h"
#include "w25qxx.h"
#endif


extern "C" void SetUSB_State(uint8_t n);

USBInterconnectionScreenView* USBInterconnectionScreen = NULL;


USBInterconnectionScreenView::USBInterconnectionScreenView()
{
    //����״̬��ʱ��������ɫ
    statusBarContainer.SetDigClockColor(255, 255, 255);
    //���õ�������ť��ɫ
    navigationBarContainer.SetButtonColor(255, 255, 255);


#ifndef SIMULATOR
    taskENTER_CRITICAL();
    USBD_Init(&USB_GlobalVariableStruct.USBD_Device, &MSC_Desc, 0);                        //��ʼ��USB
    USBD_RegisterClass(&USB_GlobalVariableStruct.USBD_Device, USBD_MSC_CLASS);            //�����
    USBD_MSC_RegisterStorage(&USB_GlobalVariableStruct.USBD_Device, &USBD_DISK_fops);     //ΪMSC����ӻص�����
    USBD_Start(&USB_GlobalVariableStruct.USBD_Device);                                   //����USB

    HAL_TIM_Base_Start_IT(&htim6);
    taskEXIT_CRITICAL();
#endif

}

void USBInterconnectionScreenView::setupScreen()
{
    USBInterconnectionScreenViewBase::setupScreen();
    USBInterconnectionScreen = this;
}

void USBInterconnectionScreenView::tearDownScreen()
{
    USBInterconnectionScreenViewBase::tearDownScreen();
}

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
//����USB״̬
void USBInterconnectionScreenView::USB_State(uint8_t n)
{
    SetConnectionStatus(n);
    getRootContainer().invalidate();
}

extern "C" void SetUSB_State(uint8_t n)
{
    if (USBInterconnectionScreen)
        USBInterconnectionScreen->USB_State(n);
}


void USBInterconnectionScreenView::handleTickEvent()
{
    //����֡��
    statusBarContainer.SetFPS(Model.getLCDfps());
}

//��д����¼�
void USBInterconnectionScreenView::handleClickEvent(const ClickEvent& event)
{
    static bool DeskButtonFlag = 0;

    USBInterconnectionScreenViewBase::handleClickEvent(event);//��ֹ����ʧЧ
    //��ȡ�¼�
    ClickEvent::ClickEventType type = event.getType();

    if (type == ClickEvent::PRESSED)
    {
        if (event.getY() > 180 && event.getX() > 750 && event.getY() < 120 + 180)
        {
            DeskButtonFlag = 1;
        }
    }
    else if (type == ClickEvent::RELEASED)
    {
        if (event.getY() > 180 && event.getX() > 750 && event.getY() < 120 + 180 && DeskButtonFlag)
        {
#ifndef SIMULATOR
            taskENTER_CRITICAL();
            USBD_Stop(&USB_GlobalVariableStruct.USBD_Device);
            //������ʱ��
            HAL_TIM_Base_Stop(&htim6);
            taskEXIT_CRITICAL();
#endif
        }
        DeskButtonFlag = 0;
    }
}

void USBInterconnectionScreenView::SetConnectionStatus(uint8_t m)
{
    switch (m)
    {
    case(0)://�Ͽ�
        textArea1.setTypedText(touchgfx::TypedText(T_USB_DISCONNECT));
        textArea1.invalidate();
        image1.setBitmap(touchgfx::Bitmap(BITMAP_DISCONNECT_ID));
        image1.invalidate();
        Unicode::fromUTF8((const uint8_t*)"Wait for connection...", textArea2Buffer, sizeof "Wait for connection...");
        textArea2.invalidate();
        break;
    case(1)://����
        textArea1.setTypedText(touchgfx::TypedText(T_USB_CONCATENATE));
        textArea1.invalidate();
        image1.setBitmap(touchgfx::Bitmap(BITMAP_CONCATENATE_ID));
        image1.invalidate();
        Unicode::fromUTF8((const uint8_t*)"USB Connected ", textArea2Buffer, sizeof "USB Connected");
        textArea2.invalidate();
        break;
    case(2)://д
        textArea1.setTypedText(touchgfx::TypedText(T_USB_CONCATENATE));
        textArea1.invalidate();
        image1.setBitmap(touchgfx::Bitmap(BITMAP_TRANSFER_ID));
        image1.invalidate();
        Unicode::fromUTF8((const uint8_t*)"USB Writing...", textArea2Buffer, sizeof "USB Writing...");
        textArea2.invalidate();
        break;
    case(3)://��
        textArea1.setTypedText(touchgfx::TypedText(T_USB_CONCATENATE));
        textArea1.invalidate();
        image1.setBitmap(touchgfx::Bitmap(BITMAP_TRANSFER_ID));
        image1.invalidate();
        Unicode::fromUTF8((const uint8_t*)"USB Reading...", textArea2Buffer, sizeof "USB Reading...");
        textArea2.invalidate();
        break;
    }
}


void USBInterconnectionScreenView::flexButton1Handler()
{
    #ifndef SIMULATOR
    W25QXX_Erase_Chip();
    #endif
}

