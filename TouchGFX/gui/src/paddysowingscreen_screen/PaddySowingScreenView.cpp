#include <gui/paddysowingscreen_screen/PaddySowingScreenView.hpp>
#include <gui/bootscreen_screen/BootScreenView.hpp>


//PaddySowing_ScreenGlobalVariableStructure PaddySowing_ScreenGlobalVariableStruct;



#ifndef SIMULATOR
#include "Radio.h"
#include "malloc.h"
#include <stdio.h>

#include "ff.h"
#include "main.h"

#endif

#include <stdlib.h>

PaddySowingScreenView::PaddySowingScreenView()
{
    GraphFlag = 0;
    StartFlag = 0;
    //填充0
    for (uint8_t i = 0; i < 8; i++)
    {
        for (uint8_t j = 0; j < 200; j++)
        {
            //GraphData[i][j] = rand() % 100;
            GraphData[i][j] = 0;
        }
    }

#ifndef SIMULATOR
    //创建工作目录
    //f_mkdir((char*)"1:/PaddySowingScreenView");
    char str[5000];
    sprintf(str, "1:PaddySowingScreenView/Data 20%d-%d-%d %d-%d-%d.csv", \
        Radio_GlobalVariableStruct.GPS_Dat[0], \
        Radio_GlobalVariableStruct.GPS_Dat[1], \
        Radio_GlobalVariableStruct.GPS_Dat[2], \
        Radio_GlobalVariableStruct.GPS_Tim[0], \
        Radio_GlobalVariableStruct.GPS_Tim[1], \
        Radio_GlobalVariableStruct.GPS_Tim[2]);
    f_open(&FIL_GlobalVariableStruct.file, (char*)str, FA_CREATE_ALWAYS);
    f_close(&FIL_GlobalVariableStruct.file);

    f_open(&FIL_GlobalVariableStruct.file, (char*)str, FA_WRITE);
#endif


    ButtonGraph_n = 0;//初始默认未选中
    //设置种子仓编号
    seedContainer1.SetTextArea1Num(1);
    seedContainer2.SetTextArea1Num(2);
    seedContainer3.SetTextArea1Num(3);
    seedContainer4.SetTextArea1Num(4);
    seedContainer5.SetTextArea1Num(5);
    seedContainer6.SetTextArea1Num(6);
    seedContainer7.SetTextArea1Num(7);
    seedContainer8.SetTextArea1Num(8);

}

void PaddySowingScreenView::setupScreen()
{
    PaddySowingScreenViewBase::setupScreen();
}

void PaddySowingScreenView::tearDownScreen()
{
    PaddySowingScreenViewBase::tearDownScreen();
}


/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
//显示总台数
void PaddySowingScreenView::SetTotality(uint8_t Totality)
{
    Unicode::snprintf(textArea2Buffer, TEXTAREA2_SIZE, "%d", Totality);
    textArea2.invalidate();
}
//显示正常数
void PaddySowingScreenView::SetRunNum(uint8_t n)
{
    Unicode::snprintf(textArea3Buffer, TEXTAREA3_SIZE, "%d", n);
    textArea3.invalidate();
}
//显示故障数
void PaddySowingScreenView::SetMalfunctionNum(uint8_t n)
{
    Unicode::snprintf(textArea4Buffer, TEXTAREA4_SIZE, "%d", n);
    textArea4.invalidate();
}
//显示运行时长
void PaddySowingScreenView::RunningTime(uint16_t n)
{
    Unicode::snprintf(textArea6Buffer1, TEXTAREA6BUFFER1_SIZE, "%d", n / 60);
    Unicode::snprintf(textArea6Buffer2, TEXTAREA6BUFFER2_SIZE, "%d", n % 60);
    textArea6.invalidate();
}
//显示定位状态
void PaddySowingScreenView::DisplayPositioningStatus(char s)
{
    Unicode::snprintf(textArea7Buffer, TEXTAREA7_SIZE, "%c", s);
    textArea7.invalidate();
}

//保护文件系统
void PaddySowingScreenView::BackFlexButtonHandler()
{
#ifndef SIMULATOR
    f_close(&FIL_GlobalVariableStruct.file);
#endif

    application().gotoDesktopScreenScreenNoTransition();
}

//启动按钮
void PaddySowingScreenView::flexButton9Handler()
{
    StartFlag = flexButton9.getPressed();
    //StartFlag=!StartFlag;
}

//定时器
void PaddySowingScreenView::handleTickEvent()
{

}


/*******************************************************************/
//按钮
void PaddySowingScreenView::flexButton1ClickBackHandler()
{
    ButtonGraph_n = 1;
    GraphFlag = 1;
    for (uint8_t i = 0; i < 200; i++)
        graph1.addDataPoint(i, GraphData[ButtonGraph_n - 1][i]);

    container4.setVisible(true);
    container4.invalidate();
}
void PaddySowingScreenView::flexButton2ClickBackHandler()
{
    ButtonGraph_n = 2;
    GraphFlag = 1;
    for (uint8_t i = 0; i < 200; i++)
        graph1.addDataPoint(i, GraphData[ButtonGraph_n - 1][i]);

    container4.setVisible(true);
    container4.invalidate();
}
void PaddySowingScreenView::flexButton3ClickBackHandler()
{
    ButtonGraph_n = 3;
    GraphFlag = 1;
    for (uint8_t i = 0; i < 200; i++)
        graph1.addDataPoint(i, GraphData[ButtonGraph_n - 1][i]);

    container4.setVisible(true);
    container4.invalidate();
}
void PaddySowingScreenView::flexButton4ClickBackHandler()
{
    ButtonGraph_n = 4;
    GraphFlag = 1;
    for (uint8_t i = 0; i < 200; i++)
        graph1.addDataPoint(i, GraphData[ButtonGraph_n - 1][i]);

    container4.setVisible(true);
    container4.invalidate();
}
void PaddySowingScreenView::flexButton5ClickBackHandler()
{
    ButtonGraph_n = 5;
    GraphFlag = 1;
    for (uint8_t i = 0; i < 200; i++)
        graph1.addDataPoint(i, GraphData[ButtonGraph_n - 1][i]);

    container4.setVisible(true);
    container4.invalidate();
}
void PaddySowingScreenView::flexButton6ClickBackHandler()
{
    ButtonGraph_n = 6;
    GraphFlag = 1;
    for (uint8_t i = 0; i < 200; i++)
        graph1.addDataPoint(i, GraphData[ButtonGraph_n - 1][i]);

    container4.setVisible(true);
    container4.invalidate();
}
void PaddySowingScreenView::flexButton7ClickBackHandler()
{
    ButtonGraph_n = 7;
    GraphFlag = 1;
    for (uint8_t i = 0; i < 200; i++)
        graph1.addDataPoint(i, GraphData[ButtonGraph_n - 1][i]);

    container4.setVisible(true);
    container4.invalidate();
}
void PaddySowingScreenView::flexButton8ClickBackHandler()
{
    ButtonGraph_n = 8;
    GraphFlag = 1;
    for (uint8_t i = 0; i < 200; i++)
        graph1.addDataPoint(i, GraphData[ButtonGraph_n - 1][i]);


    container4.setVisible(true);
    container4.invalidate();
}

void PaddySowingScreenView::ErrBackButtonHandler()
{
    GraphFlag = 0;
}




//RTOS-GUI
void PaddySowingScreenView::handleKeyEvent(uint8_t key)
{
#ifndef SIMULATOR
    if (key == TaskConGUIQueUpRadio)
#else
#define TaskConGUIQueUpRadio '1'
    if (key == TaskConGUIQueUpRadio)
#endif
    {
#ifndef SIMULATOR
        if (!GraphFlag && StartFlag)
        {
#ifndef SIMULATOR
            static volatile uint16_t RadioStateFalse_n = 0;
            if (RadioStateStru.ParsingFlag == 1)
            {
                RadioStateStru.ParsingFlag = 0;

                static uint32_t i = 0;

                i++;

                f_printf(&FIL_GlobalVariableStruct.file, "%d,%d,%d,%d,%d,%d,%d,%d\n",
                    SowingSysStru.MainSpeed[0],
                    SowingSysStru.MainSpeed[1],
                    SowingSysStru.MainSpeed[2],
                    SowingSysStru.MainSpeed[3],
                    SowingSysStru.MainSpeed[4],
                    SowingSysStru.MainSpeed[5],
                    SowingSysStru.MainSpeed[6],
                    SowingSysStru.MainSpeed[7]
                );

                //更新M1转速
                seedContainer1.SetM1Rpm(SowingSysStru.MainSpeed[0]);
                seedContainer2.SetM1Rpm(SowingSysStru.MainSpeed[1]);
                seedContainer3.SetM1Rpm(SowingSysStru.MainSpeed[2]);
                seedContainer4.SetM1Rpm(SowingSysStru.MainSpeed[3]);
                seedContainer5.SetM1Rpm(SowingSysStru.MainSpeed[4]);
                seedContainer6.SetM1Rpm(SowingSysStru.MainSpeed[5]);
                seedContainer7.SetM1Rpm(SowingSysStru.MainSpeed[6]);
                seedContainer8.SetM1Rpm(SowingSysStru.MainSpeed[7]);
                //更新M2转速
                seedContainer1.SetM2Rpm(SowingSysStru.AsSpeed[0]);
                seedContainer2.SetM2Rpm(SowingSysStru.AsSpeed[1]);
                seedContainer3.SetM2Rpm(SowingSysStru.AsSpeed[2]);
                seedContainer4.SetM2Rpm(SowingSysStru.AsSpeed[3]);
                seedContainer5.SetM2Rpm(SowingSysStru.AsSpeed[4]);
                seedContainer6.SetM2Rpm(SowingSysStru.AsSpeed[5]);
                seedContainer7.SetM2Rpm(SowingSysStru.AsSpeed[6]);
                seedContainer8.SetM2Rpm(SowingSysStru.AsSpeed[7]);

                //更新指示灯
                seedContainer1.SetRunState(SowingSysStru.State[0]);//断电
                seedContainer2.SetRunState(SowingSysStru.State[1]);//断电
                seedContainer3.SetRunState(SowingSysStru.State[2]);//断电
                seedContainer4.SetRunState(SowingSysStru.State[3]);//断电
                seedContainer5.SetRunState(SowingSysStru.State[4]);//断电
                seedContainer6.SetRunState(SowingSysStru.State[5]);//断电
                seedContainer7.SetRunState(SowingSysStru.State[6]);//断电
                seedContainer8.SetRunState(SowingSysStru.State[7]);//断电

                uint8_t T = 0, R = 0, M = 0;
                for (uint8_t a = 0; a < 8; a++)
                {
                    switch (SowingSysStru.State[a])
                    {
                    case(0)://离线

                        break;
                    case(1)://通电
                        T++;
                        R++;
                        break;
                    case(2)://运行
                        T++;
                        R++;
                        break;
                    case(3)://故障
                        T++;
                        M++;
                        break;
                    case(4)://没有种子
                        T++;
                        R++;
                        break;
                    }
                }

                //更新总台数
                SetTotality(T);
                //更新正常运行数
                SetRunNum(R);
                //更新故障数
                SetMalfunctionNum(M);
                //更新运行时长
                RunningTime(Radio_GlobalVariableStruct.SlaveRunTime);

                //更新定位状态
                DisplayPositioningStatus(Radio_GlobalVariableStruct.PositionStatus);

                Unicode::snprintfFloat(textArea5Buffer, TEXTAREA5_SIZE, "%0.1f", SowingSysStru.UAVSpeed);
                textArea5.invalidate();

                RadioStateFalse_n = 0;
            }
            //            else
            //            {
            //                
            //                printf("222\r\n");
            //                //RadioStateFalse_n++;
            //                //if (RadioStateFalse_n == 86 * 2)
            //                {
            //                    RadioStateFalse_n = 0;
            //                    //更新M1转速
            //                    seedContainer1.SetM1Rpm(0);
            //                    seedContainer2.SetM1Rpm(0);
            //                    seedContainer3.SetM1Rpm(0);
            //                    seedContainer4.SetM1Rpm(0);
            //                    seedContainer5.SetM1Rpm(0);
            //                    seedContainer6.SetM1Rpm(0);
            //                    seedContainer7.SetM1Rpm(0);
            //                    seedContainer8.SetM1Rpm(0);
            //                    //更新M2转速
            //                    seedContainer1.SetM2Rpm(0);
            //                    seedContainer2.SetM2Rpm(0);
            //                    seedContainer3.SetM2Rpm(0);
            //                    seedContainer4.SetM2Rpm(0);
            //                    seedContainer5.SetM2Rpm(0);
            //                    seedContainer6.SetM2Rpm(0);
            //                    seedContainer7.SetM2Rpm(0);
            //                    seedContainer8.SetM2Rpm(0);

            //                    //更新总台数
            //                    SetTotality(0);
            //                    //更新正常运行数
            //                    SetRunNum(0);
            //                    //更新故障数
            //                    SetMalfunctionNum(0);

            //                    //更新指示灯
            //                    seedContainer1.SetRunState(0);
            //                    seedContainer2.SetRunState(0);
            //                    seedContainer3.SetRunState(0);
            //                    seedContainer4.SetRunState(0);
            //                    seedContainer5.SetRunState(0);
            //                    seedContainer6.SetRunState(0);
            //                    seedContainer7.SetRunState(0);
            //                    seedContainer8.SetRunState(0);

            //                    Unicode::snprintfFloat(textArea5Buffer, TEXTAREA5_SIZE, "%0.1f", 0.0);
            //                    textArea5.invalidate();
            //                }
            //            }
#endif
        }
        else
        {
            //更新M1转速
            seedContainer1.SetM1Rpm(0);
            seedContainer2.SetM1Rpm(0);
            seedContainer3.SetM1Rpm(0);
            seedContainer4.SetM1Rpm(0);
            seedContainer5.SetM1Rpm(0);
            seedContainer6.SetM1Rpm(0);
            seedContainer7.SetM1Rpm(0);
            seedContainer8.SetM1Rpm(0);
            //更新M2转速
            seedContainer1.SetM2Rpm(0);
            seedContainer2.SetM2Rpm(0);
            seedContainer3.SetM2Rpm(0);
            seedContainer4.SetM2Rpm(0);
            seedContainer5.SetM2Rpm(0);
            seedContainer6.SetM2Rpm(0);
            seedContainer7.SetM2Rpm(0);
            seedContainer8.SetM2Rpm(0);

            //更新总台数
            SetTotality(0);
            //更新正常运行数
            SetRunNum(0);
            //更新故障数
            SetMalfunctionNum(0);

            //更新指示灯
            seedContainer1.SetRunState(0);
            seedContainer2.SetRunState(0);
            seedContainer3.SetRunState(0);
            seedContainer4.SetRunState(0);
            seedContainer5.SetRunState(0);
            seedContainer6.SetRunState(0);
            seedContainer7.SetRunState(0);
            seedContainer8.SetRunState(0);

            Unicode::snprintfFloat(textArea5Buffer, TEXTAREA5_SIZE, "%0.1f", 0.0);
            textArea5.invalidate();
        }
#else
        touchgfx_printf("NiGanMaAiYo 0\r\n");
#endif
    }
}


