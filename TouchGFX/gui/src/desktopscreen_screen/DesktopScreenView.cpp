#include <gui/desktopscreen_screen/DesktopScreenView.hpp>
#include <touchgfx/Utils.hpp>
#include <BitmapDatabase.hpp>
#include <gui/paddysowingscreen_screen/PaddySowingScreenView.hpp>
#include <gui/bootscreen_screen/BootScreenView.hpp>
#include <stdio.h>
#include <touchgfx/hal/HAL.hpp>

Desktopscreen_ScreenGlobalVariableStructure Desktopscreen_ScreenGlobalVariableStruct;


#ifndef SIMULATOR
#include "Backlight.h"
#include "Radio.h"
#include "ft5206.h"

#include "ff.h"
#include "usmart.h"


#endif


extern "C" void gotoSettingScreen();

DesktopScreenView* screen1 = NULL;

void DesktopScreenView::addNum()
{
    application().gotoSettingScreenScreenNoTransition();
}

extern "C" void gotoSettingScreen()
{
    if (screen1)
        screen1->addNum();
}


DesktopScreenView::DesktopScreenView()
{
    HAL::getInstance()->setFrameRateCompensation(true);
    
    orientation1 = 0;//锟斤拷锟斤拷
    Y1 = 0;
    orientation2 = 0;//锟斤拷锟斤拷
    Y2 = 0;

    ClickStartY = 0, ClickEndY = 0;
    N_BarFlag = 0;//默锟斤拷锟斤拷锟斤拷

    RadioStateTIM_n = 0;
    statusBarContainer.SetRadioVisible(false);
    //锟斤拷锟斤拷状态锟斤拷时锟斤拷锟斤拷锟斤拷锟斤拷色
    statusBarContainer.SetDigClockColor(0, 0, 0);

    //锟斤拷锟芥当前锟斤拷Page
//    Desktopscreen_ScreenGlobalVariableStruct.swipe_Index=swipeContainer1.getNumberOfPages();
    swipeContainer1.setSelectedPage(Desktopscreen_ScreenGlobalVariableStruct.swipe_Index);

    //    loadImageFromSDCard1("1:/image_Desktop1.bin",800,481);
    //    loadImageFromSDCard2("1:/image_Desktop1.bin",800,480);


#ifndef SIMULATOR

    static uint8_t Buf[10];
    Buf[0] = 0xeb;
    Buf[1] = 0xff;//锟斤拷址位
    Buf[2] = 0xc1;
    Buf[3] = 0;//锟劫讹拷
    Buf[4] = 0x90;
    HAL_UART_Transmit_DMA(&huart1, Buf, 5);
#endif
}

void DesktopScreenView::setupScreen()
{
    //particleEffect.setPosition(0, 0, HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT);
    //particleEffect.setSnapToOrigin(false);
    //particleEffect.setNumberOfParticles(100);
    //particleEffect.setOrigin(particleEffect.getWidth() / 2, particleEffect.getHeight() / 2);
    //particleEffect.setCenter(particleEffect.getWidth() / 2, particleEffect.getHeight() / 2);
    //// Insert particleEffect jut on top of the background (z-order)
    //container.insert(&tiledImage2, particleEffect);
    //add(particlesScrollingWheel);

    
    DesktopScreenViewBase::setupScreen();
    //锟斤拷全锟斤拷锟斤拷Bar
    notificationBarContainer.SetAlpha(0);

    //锟睫革拷锟斤拷锟杰伙拷锟斤拷
    flexButton1.setTouchable(false);
    flexButton2.setTouchable(false);
    flexButton3.setTouchable(false);
    flexButton4.setTouchable(false);
    flexButton5.setTouchable(false);
    flexButton6.setTouchable(false);
    flexButton7.setTouchable(false);
    flexButton8.setTouchable(false);
    flexButton9.setTouchable(false);
    flexButton10.setTouchable(false);
    flexButton11.setTouchable(false);
    flexButton12.setTouchable(false);

    screen1 = this;
}

void DesktopScreenView::tearDownScreen()
{
    DesktopScreenViewBase::tearDownScreen();
    screen1 = NULL;
}

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/

//锟斤拷写锟斤拷锟斤拷录锟�
void DesktopScreenView::handleClickEvent(const ClickEvent& event)
{
    DesktopScreenViewBase::handleClickEvent(event);//锟斤拷止锟斤拷锟斤拷失效
    //锟斤拷取锟铰硷拷
    ClickEvent::ClickEventType type = event.getType();

    if (type == ClickEvent::PRESSED)
    {
        //锟斤拷取锟斤拷锟斤拷锟斤拷锟�
        ClickStartY = event.getY();

        if (notificationBarContainer.GetSlider1ClickFlag() == 1)
            statusBarContainer.SetDigClockColor(0, 0, 0);

        ButtonClickStartX = event.getX();
        ButtonClickStartY = event.getY();
    }
    else if (type == ClickEvent::RELEASED)
    {
        //锟斤拷取锟缴匡拷锟斤拷锟斤拷
        ClickEndY = event.getY();

        if (ClickStartY < 20)
        {
            if (ClickEndY < 70)
            {
                N_BarFlag = 0;
                //锟斤拷锟斤拷通知锟斤拷过来
                notificationBarContainer.SetAlpha(0);
            }
            else
            {
                notificationBarContainer.SetAlpha(255);
                N_BarFlag = 1;
            }
        }
        else if (ClickEndY < 40 && notificationBarContainer.GetSlider1ClickFlag() == 1)
        {
            //锟斤拷锟斤拷状态锟斤拷时锟斤拷锟斤拷锟斤拷锟斤拷色
            statusBarContainer.SetDigClockColor(0, 0, 0);
            N_BarFlag = 0;
            //锟斤拷锟斤拷通知锟斤拷
            notificationBarContainer.SetAlpha(0);
        }
        if (N_BarFlag == 0)
            statusBarContainer.SetDigClockColor(0, 0, 0);
        else
            statusBarContainer.SetDigClockColor(255, 255, 255);

        ButtonClickEndX = event.getX();
        ButtonClickEndY = event.getY();

        if (ButtonClickStartX != 0 && ButtonClickStartY != 0 && !N_BarFlag)
        {
            if (ButtonClickEndX > flexButton1.getX() && ButtonClickEndX < flexButton1.getX() + flexButton1.getWidth())
            {
                if (ButtonClickEndY > flexButton1.getY() && ButtonClickEndY < flexButton1.getY() + flexButton1.getHeight())
                {
                    if (swipeContainer1.getSelectedPage() == 0)//锟斤拷一页
                    {
                        //锟斤拷录锟斤拷一页锟斤拷
                        Desktopscreen_ScreenGlobalVariableStruct.swipe_Index = 0;
                        application().gotoRTKConfigurationScreenScreenNoTransition();
                    }
                    else if (swipeContainer1.getSelectedPage() == 1)//锟节讹拷页
                    {
                        //锟斤拷录锟节讹拷页锟斤拷
                        Desktopscreen_ScreenGlobalVariableStruct.swipe_Index = 1;
                        application().gotoUSBInterconnectionScreenScreenNoTransition();
                    }
                    else if (swipeContainer1.getSelectedPage() == 2)//第三页
                    {
                        //锟斤拷录锟节讹拷页锟斤拷
                        Desktopscreen_ScreenGlobalVariableStruct.swipe_Index = 2;
                        application().gotoRadioSSCOM_ScreenScreenNoTransition();
                    }
                }
            }
            else if (ButtonClickEndX > flexButton2.getX() && ButtonClickEndX < flexButton2.getX() + flexButton2.getWidth())
            {
                if (ButtonClickEndY > flexButton2.getY() && ButtonClickEndY < flexButton2.getY() + flexButton2.getHeight())
                {
                    if (swipeContainer1.getSelectedPage() == 0)//锟斤拷一页
                    {
                        //锟斤拷录锟斤拷一页锟斤拷
                        Desktopscreen_ScreenGlobalVariableStruct.swipe_Index = 0;
                        application().gotoSettingScreenScreenNoTransition();
                    }
                    else if (swipeContainer1.getSelectedPage() == 1)//锟节讹拷页
                    {
                        //锟斤拷录锟节讹拷页锟斤拷
                        Desktopscreen_ScreenGlobalVariableStruct.swipe_Index = 1;
                        application().gotoSlaveControlScreenScreenNoTransition();
                    }
                    else if (swipeContainer1.getSelectedPage() == 2)//锟节讹拷页
                    {
                        //锟斤拷录锟节讹拷页锟斤拷
                        Desktopscreen_ScreenGlobalVariableStruct.swipe_Index = 2;
                        application().gotoNESScreenScreenBlockTransition();
                    }
                }
            }
            else if (ButtonClickEndX > flexButton3.getX() && ButtonClickEndX < flexButton3.getX() + flexButton3.getWidth())
            {
                if (ButtonClickEndY > flexButton3.getY() && ButtonClickEndY < flexButton3.getY() + flexButton3.getHeight())
                {
                    if (swipeContainer1.getSelectedPage() == 0)//锟斤拷一页
                    {
                        //锟斤拷录锟斤拷一页锟斤拷
                        Desktopscreen_ScreenGlobalVariableStruct.swipe_Index = 0;

                        application().gotoPaddySowingScreenScreenNoTransition();
                    }
                    else if (swipeContainer1.getSelectedPage() == 1)//锟节讹拷页
                    {
                        //锟斤拷录锟节讹拷页锟斤拷
                        Desktopscreen_ScreenGlobalVariableStruct.swipe_Index = 1;
#ifndef SIMULATOR
                        //进入RTK调试，关闭数据上传
                        Radio_GlobalVariableStruct.SendButyFlag = 0;
                        HAL_UART_Transmit(&huart1, (const uint8_t*)"Erro", 4, 100);
                        Radio_GlobalVariableStruct.Send_Num = 5;
#endif
                        application().gotoScreen_4GModuleSetupScreenNoTransition();
                    }
                    else if (swipeContainer1.getSelectedPage() == 2)
                    {
                        //锟斤拷录锟斤拷一页锟斤拷
                        Desktopscreen_ScreenGlobalVariableStruct.swipe_Index = 2;

                        application().gotoMotionTrailScreenScreenNoTransition();
                    }
                }
            }
            else if (ButtonClickEndX > flexButton4.getX() && ButtonClickEndX < flexButton4.getX() + flexButton4.getWidth())
            {
                if (ButtonClickEndY > flexButton4.getY() && ButtonClickEndY < flexButton4.getY() + flexButton4.getHeight())
                {
                    if (swipeContainer1.getSelectedPage() == 0)//锟斤拷一页
                    {
                        //锟斤拷录锟斤拷一页锟斤拷
                        Desktopscreen_ScreenGlobalVariableStruct.swipe_Index = 0;
                        application().gotoFileManagerScreenScreenNoTransition();
                    }
                    else if (swipeContainer1.getSelectedPage() == 1)//锟节讹拷页
                    {
                        
                    }
                    else if (swipeContainer1.getSelectedPage() == 2)//锟节讹拷页
                    {
                        
                    }
                }
            }
        }
    }
    else if (type == ClickEvent::CANCEL)
    {

    }
}

//锟斤拷写锟斤拷拽锟铰硷拷
void DesktopScreenView::handleDragEvent(const DragEvent& event)
{
    static uint16_t NewY = 0;

    DesktopScreenViewBase::handleDragEvent(event);//锟斤拷止锟斤拷锟斤拷失效

    if (event.getType() == DragEvent::DRAGGED)
    {
        //锟斤拷示锟斤拷锟斤拷通知锟斤拷
        if (ClickStartY < 20 && N_BarFlag == 0)
        {
            NewY = event.getNewY();
            notificationBarContainer.SetAlpha(NewY * 2.2);
            //锟斤拷锟斤拷状态锟斤拷时锟斤拷锟斤拷锟斤拷锟斤拷色
            static uint16_t color;
            color = NewY * 3.5;
            if (color > 255)color = 255;
            statusBarContainer.SetDigClockColor(color, color, color);
        }

        //锟斤拷锟斤拷隙锟斤拷锟斤拷锟饺★拷锟斤拷锟脚ワ拷锟斤拷锟斤拷锟斤拷
        ButtonClickStartX = ButtonClickStartY = 0;

        //三指下滑手势
#ifndef SIMULATOR
        if (event.getDeltaY() > 15 &&
            (TouchController_GlobalVariableStruct.mtouch.x[0] > 0 \
                && TouchController_GlobalVariableStruct.mtouch.x[1] > 0 \
                && TouchController_GlobalVariableStruct.mtouch.x[2] > 0))
        {

        }
#endif
    }
}
//手势识别
void DesktopScreenView::handleGestureEvent(const GestureEvent& event)
{
    //    GestureEvent::GestureEventType type=event.getType();

    //    if(type==GestureEvent::SWIPE_HORIZONTAL)
    //    {
    //        touchgfx_printf("水平\r\n");
    //    }
    //    else if(type==GestureEvent::SWIPE_VERTICAL)
    //    {
    //        touchgfx_printf("锟斤拷直\r\n");
    //    }
}
//锟斤拷锟斤拷通锟斤拷
void DesktopScreenView::Volume_Trigger1Handler(uint8_t value)
{
    statusBarContainer.SetVolumeIconColor(value, 255, 0, 0);
}
//风扇通知
void DesktopScreenView::Fan_TriggerHandler(bool value)
{
    presenter->set_fan_onoff(value);
}


bool DesktopScreenView::loadImageFromSDCard1(const char* imgPath, uint16_t imgWidth, uint16_t imgHeight)
{
#ifndef SIMULATOR
    uint8_t res = 1;
    uint8_t* bitmapBuff = NULL;
    uint32_t fileSize = 0;
    UINT readNum;

    if (bitmapId1 != BITMAP_INVALID)
    {
        Bitmap::dynamicBitmapDelete(bitmapId1);
        bitmapId1 = BITMAP_INVALID;
    }
    Bitmap::cache(bitmapId1);
    bitmapId1 = Bitmap::dynamicBitmapCreate(imgWidth, imgHeight, Bitmap::RGB565);
    if (bitmapId1 != BITMAP_INVALID)
    {
        fileSize = imgWidth * imgHeight * 2;
        bitmapBuff = (uint8_t*)Bitmap::dynamicBitmapGetAddress(bitmapId1);

        //锟斤拷sd锟斤拷锟较碉拷图片锟侥硷拷锟斤拷
        res = f_open(&FIL_GlobalVariableStruct.file, imgPath, FA_READ | FA_OPEN_EXISTING);
        if (!res)
        {
            res = f_read(&FIL_GlobalVariableStruct.file, bitmapBuff, fileSize, &readNum);
            if (!res && (readNum == fileSize))
            {
                //				image2.setBitmap(bitmapId1);//锟斤拷示图片
                //				image2.invalidate();
            }
            else
                res = 1;
        }
        f_close(&FIL_GlobalVariableStruct.file);
    }


    return !res;
#else
    imgPath = imgPath;
    imgWidth = imgWidth;
    imgHeight = imgHeight;
    return true;
#endif
}

bool DesktopScreenView::loadImageFromSDCard2(const char* imgPath, uint16_t imgWidth, uint16_t imgHeight)
{
#ifndef SIMULATOR
    uint8_t res = 1;
    uint8_t* bitmapBuff = NULL;
    uint32_t fileSize = 0;
    UINT readNum;

    if (bitmapId2 != BITMAP_INVALID)
    {
        Bitmap::dynamicBitmapDelete(bitmapId2);
        bitmapId2 = BITMAP_INVALID;
    }
    Bitmap::cache(bitmapId2);
    bitmapId2 = Bitmap::dynamicBitmapCreate(imgWidth, imgHeight, Bitmap::RGB565);
    if (bitmapId2 != BITMAP_INVALID)
    {
        fileSize = imgWidth * imgHeight * 2;
        bitmapBuff = (uint8_t*)Bitmap::dynamicBitmapGetAddress(bitmapId2);

        //锟斤拷sd锟斤拷锟较碉拷图片锟侥硷拷锟斤拷
        res = f_open(&FIL_GlobalVariableStruct.file, imgPath, FA_READ | FA_OPEN_EXISTING);
        if (!res)
        {
            res = f_read(&FIL_GlobalVariableStruct.file, bitmapBuff, fileSize, &readNum);
            if (!res && (readNum == fileSize))
            {
                //				image3.setBitmap(bitmapId2);//锟斤拷示图片
                //				image3.invalidate();
            }
            else
                res = 1;
        }
        f_close(&FIL_GlobalVariableStruct.file);
    }


    return !res;
#else
    imgPath = imgPath;
    imgWidth = imgWidth;
    imgHeight = imgHeight;
    return true;
#endif
}




//锟斤拷时
void DesktopScreenView::handleTickEvent()
{
#ifndef SIMULATOR
    static uint16_t usmart_n = 0;
    usmart_n++;
    if (usmart_n == 10)
    {
        usmart_n = 0;
        //扫描USMART
        usmart_dev.scan();
    }
#endif

    //计算帧率
    statusBarContainer.SetFPS(Model.getLCDfps());
}


void DesktopScreenView::flexButton10Handler()
{
    application().gotoNESScreenScreenBlockTransition();
}

//RTOS-GUI
void DesktopScreenView::handleKeyEvent(uint8_t key)
{
#ifndef SIMULATOR
    if (key == TaskConGUIQueRenTemp)
#else
#define TaskConGUIQueRenTemp '0'
    if (key == TaskConGUIQueRenTemp)
#endif
    {
#ifndef SIMULATOR
        //更新CPU温度和使用率
        statusBarContainer.SetCPU(MAIN_FREERTOS_GlobalVariableStruct.cpu_usage, MAIN_FREERTOS_GlobalVariableStruct.CPUtemperature);
#else
        touchgfx_printf("%c\r\n", TaskConGUIQueRenTemp);
#endif
    }
#ifndef SIMULATOR
    else if (key == TaskConGUIQueUpRadio)
#else
#define TaskConGUIQueUpRadio '1'
    else if (key == TaskConGUIQueUpRadio)
#endif
    {
#ifndef SIMULATOR
        //更新无线电数据
        statusBarContainer.SetRadioState(RadioStateStru.State);
        statusBarContainer.SetRadioColor(statusBarContainer.GetRadioState());
        statusBarContainer.SetRadioVisible(true);

        //更新时间
        statusBarContainer.UpdateTime();
        digitalClock1.setTime24Hour(Radio_GlobalVariableStruct.GPS_Tim[0], \
            Radio_GlobalVariableStruct.GPS_Tim[1], \
            Radio_GlobalVariableStruct.GPS_Tim[2]);
        digitalClock1.invalidate();
#else
        touchgfx_printf("%c\r\n", TaskConGUIQueUpRadio);
#endif
    }
}




