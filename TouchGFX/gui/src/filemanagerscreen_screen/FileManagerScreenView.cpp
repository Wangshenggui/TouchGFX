#include <gui/filemanagerscreen_screen/FileManagerScreenView.hpp>
#include <stdio.h>
#include <BitmapDatabase.hpp>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/Utils.hpp>
#include <gui/containers/FileManagerContainer.hpp>
#include <string.h>
#include <gui/bootscreen_screen/BootScreenView.hpp>

#include <string.h>

#ifndef SIMULATOR
#include "Radio.h"
#include "myFatFs.h"

#include "ff.h"
#include "malloc.h"
#endif

//\u4e2d\u56fd
FileManagerScreenView::FileManagerScreenView()
    : listElementClickedCallback(this, &FileManagerScreenView::listElementClicked)
{
    if (backFlag == 0)
    {
        backFlag = 1;
        sprintf((char*)path, "1:");
    }

    //设置导航栏按钮颜色
    navigationBarContainer.SetButtonColor(255, 255, 255);

    //textArea3.setWideTextAction(WIDE_TEXT_CHARWRAP);

    //文件列表初始化
    FileNum = 0;
    //    sprintf((char*)path,"%s","1:/TouchGFX_SYSTEM");



//#ifndef SIMULATOR
//    //创建一个新文件
//    uint32_t bw;
//    uint32_t br;
//
////    //创建工作目录
////    f_mkdir((char*)"1:/SYSTEM RUN LOG");
////    f_mkdir((char*)"1:/SYSTEM RUN LOG/HAL");
//
//
//    f_open(&FIL_GlobalVariableStruct.file, (char*)"1:/SYSTEM RUN LOG/HAL/Backlight.ini", FA_WRITE);
//    /* 追加到文件的结尾 */
//    f_lseek(&FIL_GlobalVariableStruct.file, f_size(&FIL_GlobalVariableStruct.file));
//    f_printf(&FIL_GlobalVariableStruct.file, "<%04d-%02d-%02d %02d:%02d:%02d> 背光亮度 : %03d\r\n", 
//        2024,2,21,
//        11,16,45,
//        657
//    );
//    /* 关闭文件 */
//    f_close(&FIL_GlobalVariableStruct.file);
//#endif
}


void FileManagerScreenView::setupScreen()
{
    FileManagerScreenViewBase::setupScreen();

    listLayout1.setHeight(0); //Compensates for the list height that is set to 200 by the designer

    FileNum = 0;
    //开始加载文件 
    LoadingFileSystem(path);
}

void FileManagerScreenView::tearDownScreen()
{
    FileManagerScreenViewBase::tearDownScreen();
}


/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
void FileManagerScreenView::LoadingFileSystem(uint8_t* _path)
{
#ifndef SIMULATOR

    FIL_GlobalVariableStruct.res_FM = f_opendir(&FIL_GlobalVariableStruct.dir_FM, (char*)_path); //打开目录，返回状态 和 目录对象的指针
    if (FIL_GlobalVariableStruct.res_FM == FR_OK) //打开成功
    {
        for (;;) //遍历
        {
            FIL_GlobalVariableStruct.res_FM = f_readdir(&FIL_GlobalVariableStruct.dir_FM, &FIL_GlobalVariableStruct.fno_FM); //读取目录，返回状态 和 文件信息的指针
            if (FIL_GlobalVariableStruct.res_FM != FR_OK || FIL_GlobalVariableStruct.fno_FM.fname[0] == 0)
            {
                break; //若打开失败 或 到结尾，则退出
            }
            if (FIL_GlobalVariableStruct.fno_FM.fattrib & AM_DIR) //是目录
            {
                FileNum++;

                if (
                    !(FIL_GlobalVariableStruct.fno_FM.fname[0] >= 0x20 && FIL_GlobalVariableStruct.fno_FM.fname[0] <= 0x7E)
                    )
                {
                    continue;
                }


                //排除系统自带文件夹
                if (strcmp(FIL_GlobalVariableStruct.fno_FM.fname, "System Volume Information") != 0)
                {
                    sprintf((char*)disp_path[FileNum], "%s", FIL_GlobalVariableStruct.fno_FM.fname);

                    listElements[FileNum].setupListElement(Bitmap(BITMAP_PAPER_FILE_ID), (uint8_t*)FIL_GlobalVariableStruct.fno_FM.fname);
                    listElements[FileNum].setAction(listElementClickedCallback);

                    listElements[FileNum].setboxProgress1(FileNum);

                    listLayout1.add(listElements[FileNum]);
                }
            }
            else
            {
                FileNum++;

                if (
                    !(FIL_GlobalVariableStruct.fno_FM.fname[0] >= 0x20 && FIL_GlobalVariableStruct.fno_FM.fname[0] <= 0x7E)
                    )
                {
                    continue;
                }

                sprintf((char*)disp_path[FileNum], "%s", FIL_GlobalVariableStruct.fno_FM.fname);

                listElements[FileNum].setupListElement(Bitmap(BITMAP_FILE_ID), (uint8_t*)FIL_GlobalVariableStruct.fno_FM.fname);
                listElements[FileNum].setAction(listElementClickedCallback);

                listElements[FileNum].setboxProgress1(FileNum);

                listLayout1.add(listElements[FileNum]);
            }
        }
    }
    else
    {
        //printf("失败 - %s\r\n",&res); //打开失败
    }
    f_closedir(&FIL_GlobalVariableStruct.dir_FM); //关闭目录

#else

    for (uint8_t i = 0; i < numberOfListElements; ++i)
    {
        char xxx[100];
        xxx[0] = i / 100 + 0x30;
        xxx[1] = i % 100 / 10 + 0x30;
        xxx[2] = i % 10 + 0x30;
        xxx[3] = '\0';


        sprintf((char*)disp_path[i], "%s", xxx);

        listElements[i].setupListElement(Bitmap(BITMAP_PAPER_FILE_ID), (const uint8_t*)xxx);
        listElements[i].setAction(listElementClickedCallback);

        listElements[i].setboxProgress1(i);

        listLayout1.add(listElements[i]);
    }
#endif
}

//定时器处理
void FileManagerScreenView::handleTickEvent()
{

}

//导航栏处理
void FileManagerScreenView::BackMenuHandler(uint8_t value)
{
    //解决无法通过返回按钮返回桌面
    static char temp_path[100];
    if (value == 1)//返回键
    {
        pathTailor((char*)path, (char*)temp_path);

        if (strlen((char*)path) == 2)
        {
            application().gotoDesktopScreenScreenNoTransition();
            return;
        }
        sprintf((char*)path, "%s", temp_path);
        application().gotoFileManagerScreenScreenNoTransition();
    }
    else//菜单键
    {

    }
}

//重写点击事件
void FileManagerScreenView::handleClickEvent(const ClickEvent& event)
{
    FileManagerScreenViewBase::handleClickEvent(event);//防止触摸失效
    //获取事件
    ClickEvent::ClickEventType type = event.getType();

    if (type == ClickEvent::PRESSED)
    {

    }
    else if (type == ClickEvent::RELEASED)
    {
        //用于处理文件系统路径问题
        if (event.getY() > 180 && event.getY() < 300)
        {
            if (event.getX() > 750)
            {
                backFlag = 0;
                sprintf((char*)path, "1:");
            }
        }
    }
    else if (type == ClickEvent::CANCEL)
    {

    }
}

//裁剪掉后面一个目录
void FileManagerScreenView::pathTailor(char str[], char* p)
{
    unsigned char k = 0;
    if (strlen((char*)str) == 2)
    {
        return;
    }
    for (uint8_t i = strlen(str) - 1; i > 0; i--)
    {
        if (str[i] == '/')
        {
            k = i;
            break;
        }
    }
    strncpy(p, str, k);
    p[k] = '\0';
}

//获取文件类型
int FileManagerScreenView::GetFileType(char path[])
{
    char p[100];
    for (uint8_t i = strlen(path); i > 0; i--)
    {
        if (path[i] == '.')
        {
            strncpy(p, path + i + 1, strlen(path) - i - 1);
            p[strlen(path) - i - 1] = '\0';
            if (strcmp("c", p) == 0)//c文件
            {
                return 1;
            }
            else if (strcmp("h", p) == 0)//h文件
            {
                return 1;
            }
            else if (strcmp("txt", p) == 0)//txt文件
            {
                return 1;
            }
            else if (strcmp("ini", p) == 0)//ini文件
            {
                return 1;
            }
            else if (strcmp("csv", p) == 0)//csv文件
            {
                return 1;
            }
            else
            {

            }
            return 0;//不支持的文件格式
        }
    }
    return -1;//文件夹
}

void FileManagerScreenView::listElementClicked(FileManagerContainer& element)
{
    // The button of the list element has been pressed

    switch (GetFileType((char*)disp_path[FileManagerContainer_GlobalVariableStruct.FileManagerContainerFileNum]))
    {
    case(0)://不支持的文件格式

        break;
    case(1)://txt文件
#ifndef SIMULATOR
        //打开路径
        sprintf((char*)path, "%s/%s", path, disp_path[FileManagerContainer_GlobalVariableStruct.FileManagerContainerFileNum]);

        //    u8 *p=(u8*)(mymalloc(SRAMIN, 10*1024));

                //读取缓冲区
        u8 str[4000];
        memset((char*)str, 0, 4000);
        uint32_t br;
        //打开文件
        f_open(&FIL_GlobalVariableStruct.file, (char*)path, FA_READ);
        //读取文件
        f_read(&FIL_GlobalVariableStruct.file, (void*)str, sizeof(str), &br);
        container1.setVisible(true);
        //显示内容
        bookStarContainer.TextAreaAddStr((uint8_t*)str, sizeof(str));

        container1.invalidate();

        f_close(&FIL_GlobalVariableStruct.file);

        pathTailor((char*)path, (char*)path);

#endif
        break;
    default:
#ifndef SIMULATOR
        //文件夹
        sprintf((char*)path, "%s/%s", path, disp_path[FileManagerContainer_GlobalVariableStruct.FileManagerContainerFileNum]);
        //重新载入（打开新的文件夹）
        application().gotoFileManagerScreenScreenNoTransition();
#endif
        break;
    }

}



