#include <gui/rtkconfigurationscreen_screen/RTKConfigurationScreenView.hpp>
#include <stdio.h>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

#include <gui/bootscreen_screen/BootScreenView.hpp>

#ifndef SIMULATOR
#include "usart.h"
#include "ff.h"
#include "myFatFs.h"
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct
{
    char NtripAddress[200];
    char Prot[10];
    char NtripUser[200];
    char NtripPassword[200];
    char MountPoint[200];

    char tempNtripAddress[200];
    char tempProt[10];
    char tempNtripUser[200];
    char tempNtripPassword[200];
    char tempMountPoint[200];
}ConfiguratioStructure;
ConfiguratioStructure ConfiguratioStruct;

#ifndef SIMULATOR
bool JudgeAlter()
{
    //没有数据改变
    if (strcmp(ConfiguratioStruct.MountPoint, ConfiguratioStruct.tempMountPoint) == 0 &&
        strcmp(ConfiguratioStruct.NtripAddress, ConfiguratioStruct.tempNtripAddress) == 0 &&
        strcmp(ConfiguratioStruct.NtripPassword, ConfiguratioStruct.tempNtripPassword) == 0 &&
        strcmp(ConfiguratioStruct.NtripUser, ConfiguratioStruct.tempNtripUser) == 0 &&
        strcmp(ConfiguratioStruct.Prot, ConfiguratioStruct.tempProt) == 0)
    {
        return 0;
    }

    return 1;
}

//裁剪字符串
static char* substring(char* dst, char* src, int start, int len)
{
    int length = 200;//最大长度
    if (start >= length || start < 0)
        return NULL;
    if (len > length)
        len = length - start;
    src += start;
    while (len--)
    {
        *(dst++) = *(src++);
    }
    *(dst++) = '\0';
    return dst;
}

void LogFileParsing(char* str, ConfiguratioStructure* Cfg)
{
    uint8_t s, p, L;
    uint8_t x = 0;

    for (uint8_t i = 0; i < strlen((char*)str); i++)
    {
        if (str[i] == '<')
        {
            s = i;
        }
        else if (str[i] == '>')
        {
            p = i;
            L = p - s - 1;

            char dst[100];

            substring(dst, (char*)str, s + 1, L);

            switch (x++)
            {
            case(1):
                sprintf(Cfg->NtripAddress, "%s", dst);
                sprintf(Cfg->tempNtripAddress, "%s", dst);
                break;
            case(2):
                sprintf(Cfg->Prot, "%s", dst);
                sprintf(Cfg->tempProt, "%s", dst);
                break;
            case(3):
                sprintf(Cfg->NtripUser, "%s", dst);
                sprintf(Cfg->tempNtripUser, "%s", dst);
                break;
            case(4):
                sprintf(Cfg->NtripPassword, "%s", dst);
                sprintf(Cfg->tempNtripPassword, "%s", dst);
                break;
            case(5):
                sprintf(Cfg->MountPoint, "%s", dst);
                sprintf(Cfg->tempMountPoint, "%s", dst);
                break;
            }
        }
    }
}





#endif

RTKConfigurationScreenView::RTKConfigurationScreenView()
{
    //配置等待时间
    RTKConfigurationTimer1 = 0;
    RTKConfigurationTimer2 = 0;
    InputFieldIndex = 0;


#ifndef SIMULATOR
    f_open(&FIL_GlobalVariableStruct.file, (char*)"1:/SYSTEM RUN LOG/APP/4G module application.ini", FA_READ);
    uint16_t num = 0;
    char text = 0;
    static char last_1 = 0, last_2 = 0;
    for (uint16_t i = f_size(&FIL_GlobalVariableStruct.file); i > 0; i--)
    {
        f_lseek(&FIL_GlobalVariableStruct.file, i);

        last_2 = last_1;
        last_1 = text;

        f_read(&FIL_GlobalVariableStruct.file, &text, 1, NULL);

        if (text == '\r' && last_1 == '\n' && last_2 == '<')
        {
            num = i;
            break;
        }
    }
    char read_buff[300];
    f_lseek(&FIL_GlobalVariableStruct.file, num + 2);
    f_read(&FIL_GlobalVariableStruct.file, read_buff, sizeof read_buff, NULL);
    printf("%s", read_buff);
    f_close(&FIL_GlobalVariableStruct.file);


    LogFileParsing(read_buff, &ConfiguratioStruct);



    printf("保存的信息---------%s\r\n", ConfiguratioStruct.NtripAddress);
    printf("---------%s\r\n", ConfiguratioStruct.Prot);
    printf("---------%s\r\n", ConfiguratioStruct.NtripUser);
    printf("---------%s\r\n", ConfiguratioStruct.NtripPassword);
    printf("---------%s\r\n", ConfiguratioStruct.MountPoint);
#endif





    for (uint8_t i = 0; i < NTRIPFLEXBUTTON_SIZE; i++)
    {
        NtripflexButtonBuffer[i] = 0;
    }

    for (uint8_t i = 0; i < PORTFLEXBUTTON_SIZE; i++)
    {
        portflexButtonBuffer[i] = 0;
    }

    /////////////////////////////////
    for (uint8_t i = 0; i < NTRIPFLEXBUTTONUSER_SIZE; i++)
    {
        NtripflexButtonUserBuffer[i] = 0;
    }

    for (uint8_t i = 0; i < NTRIPFLEXBUTTONPASSWORD_SIZE; i++)
    {
        NtripflexButtonPasswordBuffer[i] = 0;
    }



    /////////////////////////////////////////////////////////////////////////////
    for (uint8_t i = 0; i < strlen(ConfiguratioStruct.NtripAddress); i++)
    {
        NtripflexButtonBuffer[i] = 0;
        NtripflexButtonBuffer[i] = ConfiguratioStruct.NtripAddress[i];
    }

    for (uint8_t i = 0; i < strlen(ConfiguratioStruct.Prot); i++)
    {
        portflexButtonBuffer[i] = 0;
        portflexButtonBuffer[i] = ConfiguratioStruct.Prot[i];
    }

    /////////////////////////////////
    for (uint8_t i = 0; i < strlen(ConfiguratioStruct.NtripUser); i++)
    {
        NtripflexButtonUserBuffer[i] = 0;
        NtripflexButtonUserBuffer[i] = ConfiguratioStruct.NtripUser[i];
    }

    for (uint8_t i = 0; i < strlen(ConfiguratioStruct.NtripPassword); i++)
    {
        NtripflexButtonPasswordBuffer[i] = 0;
        NtripflexButtonPasswordBuffer[i] = ConfiguratioStruct.NtripPassword[i];
    }

    if (strcmp(ConfiguratioStruct.MountPoint, "RTCM33_GRCEJ") == 0)
    {
        swipeContainer1.setSelectedPage(0);
    }
    else if (strcmp(ConfiguratioStruct.MountPoint, "RTCM33_GRCEpro") == 0)
    {
        swipeContainer1.setSelectedPage(1);
    }
    else if (strcmp(ConfiguratioStruct.MountPoint, "RTCM33_GRCE") == 0)
    {
        swipeContainer1.setSelectedPage(2);
    }
    else if (strcmp(ConfiguratioStruct.MountPoint, "RTCM33_GRC") == 0)
    {
        swipeContainer1.setSelectedPage(3);
    }
    else if (strcmp(ConfiguratioStruct.MountPoint, "RTCM30_GR") == 0)
    {
        swipeContainer1.setSelectedPage(4);
    }


    NtripflexButton.invalidate();
    portflexButton.invalidate();
    NtripflexButtonUser.invalidate();
    NtripflexButtonPassword.invalidate();
    swipeContainer1.invalidate();

    touchgfx_printf("start:%s\r\n", ConfiguratioStruct.NtripAddress);
    touchgfx_printf("start:%s\r\n", ConfiguratioStruct.Prot);

    touchgfx_printf("start:%s\r\n", ConfiguratioStruct.NtripUser);
    touchgfx_printf("start:%s\r\n", ConfiguratioStruct.NtripPassword);

    touchgfx_printf("start:%s\r\n", ConfiguratioStruct.MountPoint);
}


void RTKConfigurationScreenView::setupScreen()
{
    RTKConfigurationScreenViewBase::setupScreen();
}

void RTKConfigurationScreenView::tearDownScreen()
{
    touchgfx_printf("out : %s\r\n", ConfiguratioStruct.MountPoint);
#ifndef SIMULATOR
    if (JudgeAlter())
    {
        printf("Data has changed and is being saved\r\n");
        FatFsSave();
    }
    else
    {
        printf("Data does not change, exit\r\n");
    }
#endif
    RTKConfigurationScreenViewBase::tearDownScreen();
}


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// 
#ifndef SIMULATOR
// ////////////////////////////////////////////////
//文件系统保存操作
void RTKConfigurationScreenView::FatFsSave()
{
    f_open(&FIL_GlobalVariableStruct.file, (char*)"1:/SYSTEM RUN LOG/APP/4G module application.ini", FA_WRITE);
    /* 追加到文件的结尾 */
    f_lseek(&FIL_GlobalVariableStruct.file, f_size(&FIL_GlobalVariableStruct.file));
    f_printf(&FIL_GlobalVariableStruct.file,
        "<%04d-%02d-%02d %02d:%02d:%02d>\r\n\
    Ntrip服务器地址 : <%s>\r\n\
    端口号 : <%s>\r\n\
    Ntrip用户名 : <%s>\r\n\
    Ntrip密码 : <%s>\r\n\
    挂载点 : <%s>\r\n\r\n",
        2024, 2, 21, \
        10, 21, 28, \
        ConfiguratioStruct.NtripAddress, \
        ConfiguratioStruct.Prot, \
        ConfiguratioStruct.NtripUser, \
        ConfiguratioStruct.NtripPassword, \
        ConfiguratioStruct.MountPoint
    );
    /* 关闭文件 */
    f_close(&FIL_GlobalVariableStruct.file);
}
#endif

//选择配对端口
void RTKConfigurationScreenView::portflexButtonHandler()
{
    bool state;

    state = portflexButton.getPressed();

    if (state)
    {
        Unicode::snprintf(portflexButtonBuffer, PORTFLEXBUTTON_SIZE, "%d", 8002);
    }
    else
    {
        Unicode::snprintf(portflexButtonBuffer, PORTFLEXBUTTON_SIZE, "%d", 8001);
    }

    for (uint8_t i = 0; i < PORTFLEXBUTTON_SIZE; i++)
    {
        ConfiguratioStruct.Prot[i] = portflexButtonBuffer[i];
    }

    touchgfx_printf("Changer:%s", ConfiguratioStruct.Prot);
    portflexButton.invalidate();
}

//服务器设置
void RTKConfigurationScreenView::setButton1Handler()
{
    char str_temp[100] = { 0 };
    char str[100] = { 0 };
    uint8_t i = 0, j = 0;

    for (i = 0; i < NTRIPFLEXBUTTON_SIZE; i++)
    {
        if (NtripflexButtonBuffer[i] == 0)
        {
            j = i;
            break;
        }
        str_temp[i] = NtripflexButtonBuffer[i];
    }
    str_temp[j] = ',';
    j++;
    for (i = j; i < PORTFLEXBUTTON_SIZE + j; i++)
    {
        str_temp[i] = portflexButtonBuffer[i - j];
    }

    sprintf(str, "AT*SERVER1=0,%s#\r\n", str_temp);
#ifndef SIMULATOR
    Radio_GlobalVariableStruct.RTKConfigurationState = 0;//先清空该标志
    HAL_UART_Transmit_IT(&huart1, (uint8_t*)str, strlen(str));
    printf("%s", str);
#endif
    RTKConfigurationTimer1 = 0;
    RTKConfigurationTimer2 = 0;
    container3.setVisible(true);
    container3.invalidate();
    touchgfx_printf("%s", str);
}


//服务器查询
void RTKConfigurationScreenView::inquireButton1Handler()
{
    char str[100] = { 0 };

    sprintf(str, "AT*SERVER1?\r\n");
#ifndef SIMULATOR
    Radio_GlobalVariableStruct.RTKConfigurationState = 0;//先清空该标志
    HAL_UART_Transmit_IT(&huart1, (uint8_t*)str, strlen(str));
    printf("%s", str);

    memset(Radio_GlobalVariableStruct.M4GReturnBuff, 0, 200);
#endif
    Modalcontainer.setVisible(true);
    Modalcontainer.invalidate();
    touchgfx_printf("%s", str);
}

//用户设置
void RTKConfigurationScreenView::setButton2Handler()
{
    char str_temp[200] = { 0 };
    char str[100] = { 0 };
    uint8_t i = 0, j = 0;

    for (i = 0; i < NTRIPFLEXBUTTONUSER_SIZE; i++)
    {
        if (NtripflexButtonUserBuffer[i] == 0)
        {
            j = i;
            break;
        }
        str_temp[i] = NtripflexButtonUserBuffer[i];
    }
    str_temp[j] = ',';
    j++;
    for (i = j; i < NTRIPFLEXBUTTONPASSWORD_SIZE + j; i++)
    {
        if (NtripflexButtonPasswordBuffer[i - j] == 0)
        {
            j = i;
            break;
        }
        str_temp[i] = NtripflexButtonPasswordBuffer[i - j];
    }
    str_temp[j] = ',';
    j++;
    if (swipeContainer1.getSelectedPage() == 0)//第一页
    {
        for (i = j; i < TEXTAREAMOUNTPOINT1_SIZE + j; i++)
        {
            str_temp[i] = textAreaMountPoint1Buffer[i - j];
        }
    }
    else if (swipeContainer1.getSelectedPage() == 1)//第二页
    {
        for (i = j; i < TEXTAREAMOUNTPOINT2_SIZE + j; i++)
        {
            str_temp[i] = textAreaMountPoint2Buffer[i - j];
        }
    }
    else if (swipeContainer1.getSelectedPage() == 2)//第三页
    {
        for (i = j; i < TEXTAREAMOUNTPOINT3_SIZE + j; i++)
        {
            str_temp[i] = textAreaMountPoint3Buffer[i - j];
        }
    }
    else if (swipeContainer1.getSelectedPage() == 3)//第四页
    {
        for (i = j; i < TEXTAREAMOUNTPOINT4_SIZE + j; i++)
        {
            str_temp[i] = textAreaMountPoint4Buffer[i - j];
        }
    }
    else if (swipeContainer1.getSelectedPage() == 4)//第五页
    {
        for (i = j; i < TEXTAREAMOUNTPOINT5_SIZE + j; i++)
        {
            str_temp[i] = textAreaMountPoint5Buffer[i - j];
        }
    }

    sprintf(str, "AT*NTRIP=%s#\r\n", str_temp);
#ifndef SIMULATOR
    Radio_GlobalVariableStruct.RTKConfigurationState = 0;//先清空该标志
    HAL_UART_Transmit_IT(&huart1, (uint8_t*)str, strlen(str));
    printf("%s", str);
#endif
    RTKConfigurationTimer1 = 0;
    RTKConfigurationTimer2 = 0;
    container3.setVisible(true);
    container3.invalidate();
    touchgfx_printf("%s", str);
}

//用户查询
void RTKConfigurationScreenView::inquireButton2Handler()
{
    char str[100] = { 0 };

    sprintf(str, "AT*NTRIP?\r\n");
#ifndef SIMULATOR
    Radio_GlobalVariableStruct.RTKConfigurationState = 0;//先清空该标志
    HAL_UART_Transmit_IT(&huart1, (uint8_t*)str, strlen(str));
    printf("%s", str);

    memset(Radio_GlobalVariableStruct.M4GReturnBuff, 0, 200);
#endif

    Unicode::fromUTF8((const uint8_t*)"Ntrip Server address", textArea1Buffer, sizeof "Ntrip Server address");
    textArea1.invalidate();

    Modalcontainer.setVisible(true);
    Modalcontainer.invalidate();
    touchgfx_printf("%s", str);
}



//查询按钮处理
void RTKConfigurationScreenView::ButtonAction1(uint8_t value)
{
    char str[100] = { 0 };

    const char a[12] = { T_RESOURCEID1,T_RESOURCEID2,T_RESOURCEID3,T_RESOURCEID4
            ,T_RESOURCEID5,T_RESOURCEID6,T_RESOURCEID7,T_RESOURCEID8
            ,T_RESOURCEID9,T_RESOURCEID10,T_RESOURCEID11,T_RESOURCEID12 };
    const char b[][50] = {
    "AT*GSTATE?","AT*DCFG?","AT*VERSION?","AT*DTUIP?",
        "AT*CSQ?","AT*IMEI?","AT*ICCID?","AT*REG?",
        "AT*CPIN?","AT*DSTATE?","AT*SERVER1?","AT*NTRIP?",
    };

    sprintf(str, "%s\r\n", b[value - 1]);
#ifndef SIMULATOR
    Radio_GlobalVariableStruct.RTKConfigurationState = 0;//先清空该标志
    HAL_UART_Transmit_IT(&huart1, (uint8_t*)str, strlen(str));
    printf("%s", str);

    memset(Radio_GlobalVariableStruct.M4GReturnBuff, 0, 200);
#endif
    touchgfx_printf("%s", str);

    textArea1.setTypedText(TypedText(a[value - 1]));

    Modalcontainer.setVisible(true);
    Modalcontainer.invalidate();
}


//键盘隐藏
void RTKConfigurationScreenView::BackButtonTrigger(bool Flag)
{
    switch (InputFieldIndex)
    {
    case(1)://地址输入框
        //将键盘显示框复制到输入框
        for (uint8_t i = 0; i < 200; i++)
        {
            if (KeyBoard_GlobalVariableStruct.String[i] == 0)
            {
                NtripflexButtonBuffer[i] = 0;
                break;
            }
            NtripflexButtonBuffer[i] = KeyBoard_GlobalVariableStruct.String[i];
        }
        sprintf(ConfiguratioStruct.NtripAddress, "%s", KeyBoard_GlobalVariableStruct.String);
        touchgfx_printf("Changer:%s", ConfiguratioStruct.NtripAddress);
        NtripflexButton.invalidate();
        break;
    case(2)://用户名输入框
        //将键盘显示框复制到输入框
        for (uint8_t i = 0; i < 200; i++)
        {
            if (KeyBoard_GlobalVariableStruct.String[i] == 0)
            {
                NtripflexButtonUserBuffer[i] = 0;
                break;
            }
            NtripflexButtonUserBuffer[i] = KeyBoard_GlobalVariableStruct.String[i];
        }
        sprintf(ConfiguratioStruct.NtripUser, "%s", KeyBoard_GlobalVariableStruct.String);
        touchgfx_printf("Changer:%s", ConfiguratioStruct.NtripUser);
        NtripflexButtonUser.invalidate();
        break;
    case(3)://用户密码输入框
        //将键盘显示框复制到输入框
        for (uint8_t i = 0; i < 200; i++)
        {
            if (KeyBoard_GlobalVariableStruct.String[i] == 0)
            {
                NtripflexButtonPasswordBuffer[i] = 0;
                break;
            }
            NtripflexButtonPasswordBuffer[i] = KeyBoard_GlobalVariableStruct.String[i];
        }
        sprintf(ConfiguratioStruct.NtripPassword, "%s", KeyBoard_GlobalVariableStruct.String);
        touchgfx_printf("Changer:%s", ConfiguratioStruct.NtripPassword);
        NtripflexButtonPassword.invalidate();
        break;
    }
    InputFieldIndex = 0;

    keyBoardContainer1.setVisible(false);
    keyBoardContainer1.invalidate();
}

//点击地址输入框
void RTKConfigurationScreenView::NtripflexButtonHandler()
{
    InputFieldIndex = 1;
    //将输入框现有的文本复制到键盘显示框
    for (uint8_t i = 0; i < 200; i++)
    {
        if (NtripflexButtonBuffer[i] == 0)
        {
            KeyBoard_GlobalVariableStruct.String[i] = 0;
            break;
        }
        KeyBoard_GlobalVariableStruct.String[i] = NtripflexButtonBuffer[i];
    }
    //更新键盘显示框
    keyBoardContainer1.ButtonAction1(255);
    keyBoardContainer1.invalidate();

    keyBoardContainer1.setVisible(true);
    keyBoardContainer1.invalidate();
}
//点击用户名输入框
void RTKConfigurationScreenView::NtripflexButtonUserHandler()
{
    InputFieldIndex = 2;
    //将输入框现有的文本复制到键盘显示框
    for (uint8_t i = 0; i < 200; i++)
    {
        if (NtripflexButtonUserBuffer[i] == 0)
        {
            KeyBoard_GlobalVariableStruct.String[i] = 0;
            break;
        }
        KeyBoard_GlobalVariableStruct.String[i] = NtripflexButtonUserBuffer[i];
    }
    //更新键盘显示框
    keyBoardContainer1.ButtonAction1(255);
    keyBoardContainer1.invalidate();

    keyBoardContainer1.setVisible(true);
    keyBoardContainer1.invalidate();
}
//点击密码输入框
void RTKConfigurationScreenView::NtripflexButtonPasswordHandler()
{
    InputFieldIndex = 3;
    //将输入框现有的文本复制到键盘显示框
    for (uint8_t i = 0; i < 200; i++)
    {
        if (NtripflexButtonPasswordBuffer[i] == 0)
        {
            KeyBoard_GlobalVariableStruct.String[i] = 0;
            break;
        }
        KeyBoard_GlobalVariableStruct.String[i] = NtripflexButtonPasswordBuffer[i];
    }
    //更新键盘显示框
    keyBoardContainer1.ButtonAction1(255);
    keyBoardContainer1.invalidate();

    keyBoardContainer1.setVisible(true);
    keyBoardContainer1.invalidate();
}


//点击
void RTKConfigurationScreenView::handleClickEvent(const ClickEvent& event)
{
    RTKConfigurationScreenViewBase::handleClickEvent(event);//锟斤拷止锟斤拷锟斤拷失效
    //锟斤拷取锟铰硷拷
    ClickEvent::ClickEventType type = event.getType();

    if (type == ClickEvent::PRESSED)
    {

    }
    else if (type == ClickEvent::RELEASED)
    {
        if (swipeContainer1.getSelectedPage() == 0)//第一页
        {
            for (uint8_t i = 0; i < TEXTAREAMOUNTPOINT1_SIZE; i++)
            {
                ConfiguratioStruct.MountPoint[i] = textAreaMountPoint1Buffer[i];
            }
        }
        else if (swipeContainer1.getSelectedPage() == 1)//第二页
        {
            for (uint8_t i = 0; i < TEXTAREAMOUNTPOINT2_SIZE; i++)
            {
                ConfiguratioStruct.MountPoint[i] = textAreaMountPoint2Buffer[i];
            }
        }
        else if (swipeContainer1.getSelectedPage() == 2)//第三页
        {
            for (uint8_t i = 0; i < TEXTAREAMOUNTPOINT3_SIZE; i++)
            {
                ConfiguratioStruct.MountPoint[i] = textAreaMountPoint3Buffer[i];
            }
        }
        else if (swipeContainer1.getSelectedPage() == 3)//第四页
        {
            for (uint8_t i = 0; i < TEXTAREAMOUNTPOINT4_SIZE; i++)
            {
                ConfiguratioStruct.MountPoint[i] = textAreaMountPoint4Buffer[i];
            }
        }
        else if (swipeContainer1.getSelectedPage() == 4)//第五页
        {
            for (uint8_t i = 0; i < TEXTAREAMOUNTPOINT5_SIZE; i++)
            {
                ConfiguratioStruct.MountPoint[i] = textAreaMountPoint5Buffer[i];
            }
        }

        touchgfx_printf("Changer:%s", ConfiguratioStruct.MountPoint);
    }
    else if (type == ClickEvent::CANCEL)
    {

    }
}

//定时功能
void RTKConfigurationScreenView::handleTickEvent()
{
    static uint16_t t = 0;

    if (t++ == 86)
    {
        t = 0;
        if (swipeContainer1.getSelectedPage() == 0)//第一页
        {
            for (uint8_t i = 0; i < TEXTAREAMOUNTPOINT1_SIZE; i++)
            {
                ConfiguratioStruct.MountPoint[i] = textAreaMountPoint1Buffer[i];
            }
        }
        else if (swipeContainer1.getSelectedPage() == 1)//第二页
        {
            for (uint8_t i = 0; i < TEXTAREAMOUNTPOINT2_SIZE; i++)
            {
                ConfiguratioStruct.MountPoint[i] = textAreaMountPoint2Buffer[i];
            }
        }
        else if (swipeContainer1.getSelectedPage() == 2)//第三页
        {
            for (uint8_t i = 0; i < TEXTAREAMOUNTPOINT3_SIZE; i++)
            {
                ConfiguratioStruct.MountPoint[i] = textAreaMountPoint3Buffer[i];
            }
        }
        else if (swipeContainer1.getSelectedPage() == 3)//第四页
        {
            for (uint8_t i = 0; i < TEXTAREAMOUNTPOINT4_SIZE; i++)
            {
                ConfiguratioStruct.MountPoint[i] = textAreaMountPoint4Buffer[i];
            }
        }
        else if (swipeContainer1.getSelectedPage() == 4)//第五页
        {
            for (uint8_t i = 0; i < TEXTAREAMOUNTPOINT5_SIZE; i++)
            {
                ConfiguratioStruct.MountPoint[i] = textAreaMountPoint5Buffer[i];
            }
        }
    }

#ifndef SIMULATOR
    Unicode::fromUTF8((const uint8_t*)Radio_GlobalVariableStruct.M4GReturnBuff, textArea5Buffer, sizeof Radio_GlobalVariableStruct.M4GReturnBuff);
    textArea5.invalidate();
#endif

    RTKConfigurationTimer1++;
    //超过3s
    if (RTKConfigurationTimer1 == 84)
    {
        RTKConfigurationTimer1 = 0;
        RTKConfigurationTimer2++;

#ifndef SIMULATOR
        //定时查询RTK配置状态
        if (Radio_GlobalVariableStruct.RTKConfigurationState)
        {
            //成功了
            textArea2.setVisible(false);
            textArea2.invalidate();
            textArea3.setVisible(true);
            textArea3.invalidate();
            textArea4.setVisible(false);
            textArea4.invalidate();

            RTKConfigurationTimer2 = 11;

            RTKConfigurationTimer1 = 0;

            //否则一直不能退出
            Radio_GlobalVariableStruct.RTKConfigurationState = 0;
        }
#endif

        //超时
        if (RTKConfigurationTimer2 == 10)
        {
            textArea2.setVisible(false);
            textArea2.invalidate();
            textArea3.setVisible(false);
            textArea3.invalidate();
            textArea4.setVisible(true);
            textArea4.invalidate();
        }
        //关闭
        else if (RTKConfigurationTimer2 == 12)
        {
            textArea2.setVisible(true);
            textArea2.invalidate();
            textArea3.setVisible(false);
            textArea3.invalidate();
            textArea4.setVisible(false);
            textArea4.invalidate();
            container3.setVisible(false);
            container3.invalidate();
        }
    }
}




