#include <gui/containers/KeyBoardContainer.hpp>
#include <touchgfx/Unicode.hpp>

#include <string.h>
#include <stdio.h>

#include <gui/containers/T9_Input.hpp>

KeyBoard_GlobalVariableStructure KeyBoard_GlobalVariableStruct;

KeyBoardContainer::KeyBoardContainer()
{
    KeyBoard_GlobalVariableStruct.CaseFlag = 0;//小写
    ToggleLowercase();
}

void KeyBoardContainer::initialize()
{
    KeyBoardContainerBase::initialize();
}



//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//切换大写
void KeyBoardContainer::SwitchCaps()
{
    KeyBoard_GlobalVariableStruct.CaseFlag = 1;
    ButtonQBuffer[0] = 'Q';
    ButtonQBuffer[1] = 0;
    ButtonWBuffer[0] = 'W';
    ButtonWBuffer[1] = 0;
    ButtonEBuffer[0] = 'E';
    ButtonEBuffer[1] = 0;
    ButtonRBuffer[0] = 'R';
    ButtonRBuffer[1] = 0;
    ButtonTBuffer[0] = 'T';
    ButtonTBuffer[1] = 0;
    ButtonYBuffer[0] = 'Y';
    ButtonYBuffer[1] = 0;
    ButtonUBuffer[0] = 'U';
    ButtonUBuffer[1] = 0;
    ButtonIBuffer[0] = 'I';
    ButtonIBuffer[1] = 0;
    ButtonOBuffer[0] = 'O';
    ButtonOBuffer[1] = 0;
    ButtonPBuffer[0] = 'P';
    ButtonPBuffer[1] = 0;
    containerQ_P.invalidate();

    ButtonABuffer[0] = 'A';
    ButtonABuffer[1] = 0;
    ButtonSBuffer[0] = 'S';
    ButtonSBuffer[1] = 0;
    ButtonDBuffer[0] = 'D';
    ButtonDBuffer[1] = 0;
    ButtonFBuffer[0] = 'F';
    ButtonFBuffer[1] = 0;
    ButtonGBuffer[0] = 'G';
    ButtonGBuffer[1] = 0;
    ButtonHBuffer[0] = 'H';
    ButtonHBuffer[1] = 0;
    ButtonJBuffer[0] = 'J';
    ButtonJBuffer[1] = 0;
    ButtonKBuffer[0] = 'K';
    ButtonKBuffer[1] = 0;
    ButtonLBuffer[0] = 'L';
    ButtonLBuffer[1] = 0;
    containerA_L.invalidate();

    ButtonZBuffer[0] = 'Z';
    ButtonZBuffer[1] = 0;
    ButtonXBuffer[0] = 'X';
    ButtonXBuffer[1] = 0;
    ButtonCBuffer[0] = 'C';
    ButtonCBuffer[1] = 0;
    ButtonVBuffer[0] = 'V';
    ButtonVBuffer[1] = 0;
    ButtonBBuffer[0] = 'B';
    ButtonBBuffer[1] = 0;
    ButtonNBuffer[0] = 'N';
    ButtonNBuffer[1] = 0;
    ButtonMBuffer[0] = 'N';
    ButtonMBuffer[1] = 0;
    containerZ_M.invalidate();
}

//切换小写
void KeyBoardContainer::ToggleLowercase()
{
    KeyBoard_GlobalVariableStruct.CaseFlag = 0;
    ButtonQBuffer[0] = 'q';
    ButtonQBuffer[1] = 0;
    ButtonWBuffer[0] = 'w';
    ButtonWBuffer[1] = 0;
    ButtonEBuffer[0] = 'e';
    ButtonEBuffer[1] = 0;
    ButtonRBuffer[0] = 'r';
    ButtonRBuffer[1] = 0;
    ButtonTBuffer[0] = 't';
    ButtonTBuffer[1] = 0;
    ButtonYBuffer[0] = 'y';
    ButtonYBuffer[1] = 0;
    ButtonUBuffer[0] = 'u';
    ButtonUBuffer[1] = 0;
    ButtonIBuffer[0] = 'i';
    ButtonIBuffer[1] = 0;
    ButtonOBuffer[0] = 'o';
    ButtonOBuffer[1] = 0;
    ButtonPBuffer[0] = 'p';
    ButtonPBuffer[1] = 0;
    containerQ_P.invalidate();

    ButtonABuffer[0] = 'a';
    ButtonABuffer[1] = 0;
    ButtonSBuffer[0] = 's';
    ButtonSBuffer[1] = 0;
    ButtonDBuffer[0] = 'd';
    ButtonDBuffer[1] = 0;
    ButtonFBuffer[0] = 'f';
    ButtonFBuffer[1] = 0;
    ButtonGBuffer[0] = 'g';
    ButtonGBuffer[1] = 0;
    ButtonHBuffer[0] = 'h';
    ButtonHBuffer[1] = 0;
    ButtonJBuffer[0] = 'j';
    ButtonJBuffer[1] = 0;
    ButtonKBuffer[0] = 'k';
    ButtonKBuffer[1] = 0;
    ButtonLBuffer[0] = 'l';
    ButtonLBuffer[1] = 0;
    containerA_L.invalidate();

    ButtonZBuffer[0] = 'z';
    ButtonZBuffer[1] = 0;
    ButtonXBuffer[0] = 'x';
    ButtonXBuffer[1] = 0;
    ButtonCBuffer[0] = 'c';
    ButtonCBuffer[1] = 0;
    ButtonVBuffer[0] = 'v';
    ButtonVBuffer[1] = 0;
    ButtonBBuffer[0] = 'b';
    ButtonBBuffer[1] = 0;
    ButtonNBuffer[0] = 'n';
    ButtonNBuffer[1] = 0;
    ButtonMBuffer[0] = 'm';
    ButtonMBuffer[1] = 0;
    containerZ_M.invalidate();
}

//Shift
void KeyBoardContainer::buttonShiftHandler()
{
    //小写
    if (KeyBoard_GlobalVariableStruct.CaseFlag == 0)
    {
        SwitchCaps();
    }
    else if (KeyBoard_GlobalVariableStruct.CaseFlag == 1)
    {
        ToggleLowercase();
    }
}

//显示预览
void KeyBoardContainer::SetOutText(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, OutEnglishTextAreaBuffer, len);
    OutEnglishTextArea.invalidate();
}
//处理按键通知
void KeyBoardContainer::ButtonAction1(uint8_t value)
{
    uint8_t temp;

    KeyBoard_GlobalVariableStruct.ChinaStringOffset = 0;//清空中文偏移

    if (value >= 'A' && value <= 'z')
    {
        if (value != 32)
        {
            if (KeyBoard_GlobalVariableStruct.CaseFlag == 0)
                temp = value + 32;
            else
                temp = value;
            sprintf((char*)KeyBoard_GlobalVariableStruct.String, "%s%c", (char*)KeyBoard_GlobalVariableStruct.String, temp);
        }
        else //符号做特殊处理
        {
            sprintf((char*)KeyBoard_GlobalVariableStruct.String, "%s%c", (char*)KeyBoard_GlobalVariableStruct.String, ' ');
        }
    }
    else if (value == '.')
    {
        if (flexButtonChina.getPressed())
        {
            KeyBoard_GlobalVariableStruct.String[0] = 0;
            ClearChinaText();
            flexButtonAddBuffer[0] = 0xff0c;
            flexButtonAddBuffer[1] = 0;
            flexButtonAdd.invalidate();

            flexButtonSubBuffer[0] = 0x3002;
            flexButtonSubBuffer[1] = 0;
            flexButtonSub.invalidate();

            flexButtonMulBuffer[0] = 0xff1f;
            flexButtonMulBuffer[1] = 0;
            flexButtonMul.invalidate();

            flexButtonDivBuffer[0] = 0xff01;
            flexButtonDivBuffer[1] = 0;
            flexButtonDiv.invalidate();

            flexButtonColonBuffer[0] = '~';
            flexButtonColonBuffer[1] = 0;
            flexButtonColon.invalidate();
            return;
        }
        else
        {
            temp = value;
            sprintf((char*)KeyBoard_GlobalVariableStruct.String, "%s%c", (char*)KeyBoard_GlobalVariableStruct.String, temp);
        }
    }
    else if (value == '@')
    {
        temp = value;
        sprintf((char*)KeyBoard_GlobalVariableStruct.String, "%s%c", (char*)KeyBoard_GlobalVariableStruct.String, temp);
    }
    else if (value == '+')
    {
        if (flexButtonAddBuffer[0] >= 'A' && flexButtonAddBuffer[0] <= 'z')
        {
            KeyBoard_GlobalVariableStruct.PinYinIndex = 0;
            DispChina(KeyBoard_GlobalVariableStruct.PinYinIndex);
            return;
        }
        else
        {
            temp = value;
            sprintf((char*)KeyBoard_GlobalVariableStruct.String, "%s%c", (char*)KeyBoard_GlobalVariableStruct.String, temp);
        }
    }
    else if (value == '-')
    {
        if (flexButtonSubBuffer[0] >= 'A' && flexButtonSubBuffer[0] <= 'z')
        {
            KeyBoard_GlobalVariableStruct.PinYinIndex = 1;
            DispChina(KeyBoard_GlobalVariableStruct.PinYinIndex);
            return;
        }
        else
        {
            temp = value;
            sprintf((char*)KeyBoard_GlobalVariableStruct.String, "%s%c", (char*)KeyBoard_GlobalVariableStruct.String, temp);
        }
    }
    else if (value == '*')
    {
        if (flexButtonMulBuffer[0] >= 'A' && flexButtonMulBuffer[0] <= 'z')
        {
            KeyBoard_GlobalVariableStruct.PinYinIndex = 2;
            DispChina(KeyBoard_GlobalVariableStruct.PinYinIndex);
            return;
        }
        else
        {
            temp = value;
            sprintf((char*)KeyBoard_GlobalVariableStruct.String, "%s%c", (char*)KeyBoard_GlobalVariableStruct.String, temp);
        }
    }
    else if (value == '/')
    {
        if (flexButtonDivBuffer[0] >= 'A' && flexButtonDivBuffer[0] <= 'z')
        {
            KeyBoard_GlobalVariableStruct.PinYinIndex = 3;
            DispChina(KeyBoard_GlobalVariableStruct.PinYinIndex);
            return;
        }
        else
        {
            temp = value;
            sprintf((char*)KeyBoard_GlobalVariableStruct.String, "%s%c", (char*)KeyBoard_GlobalVariableStruct.String, temp);
        }
    }
    else if (value == ':')
    {
        if (flexButtonColonBuffer[0] >= 'A' && flexButtonColonBuffer[0] <= 'z')
        {
            KeyBoard_GlobalVariableStruct.PinYinIndex = 4;
            DispChina(KeyBoard_GlobalVariableStruct.PinYinIndex);
            return;
        }
        else
        {
            temp = value;
            sprintf((char*)KeyBoard_GlobalVariableStruct.String, "%s%c", (char*)KeyBoard_GlobalVariableStruct.String, temp);
        }
    }
    else if (value >= '0' && value <= '9')
    {
        temp = value;
        sprintf((char*)KeyBoard_GlobalVariableStruct.String, "%s%c", (char*)KeyBoard_GlobalVariableStruct.String, temp);
    }

    this->SetOutText(KeyBoard_GlobalVariableStruct.String, sizeof(KeyBoard_GlobalVariableStruct.String));
    invalidate();

    DispChinaText();

    //发送按钮点击通知
    emitTouchTriggerCallback(1);
}

//退格键
void KeyBoardContainer::buttonBackspaceHandler()
{
    if (strlen((char*)KeyBoard_GlobalVariableStruct.String) > 0)
    {
        KeyBoard_GlobalVariableStruct.String[strlen((char*)KeyBoard_GlobalVariableStruct.String) - 1] = 0;
        this->SetOutText(KeyBoard_GlobalVariableStruct.String, sizeof(KeyBoard_GlobalVariableStruct.String));
        invalidate();

        DispChinaText();
    }
    else
    {
        ClearChinaText();

        if (flexButtonChina.getPressed())
        {
            flexButtonAddBuffer[0] = 0xff0c;
            flexButtonAddBuffer[1] = 0;
            flexButtonAdd.invalidate();

            flexButtonSubBuffer[0] = 0x3002;
            flexButtonSubBuffer[1] = 0;
            flexButtonSub.invalidate();

            flexButtonMulBuffer[0] = 0xff1f;
            flexButtonMulBuffer[1] = 0;
            flexButtonMul.invalidate();

            flexButtonDivBuffer[0] = 0xff01;
            flexButtonDivBuffer[1] = 0;
            flexButtonDiv.invalidate();

            flexButtonColonBuffer[0] = '~';
            flexButtonColonBuffer[1] = 0;
            flexButtonColon.invalidate();
        }
        else
        {
            flexButtonAddBuffer[0] = '+';
            flexButtonAddBuffer[1] = 0;
            flexButtonAdd.invalidate();

            flexButtonSubBuffer[0] = '-';
            flexButtonSubBuffer[1] = 0;
            flexButtonSub.invalidate();

            flexButtonMulBuffer[0] = '*';
            flexButtonMulBuffer[1] = 0;
            flexButtonMul.invalidate();

            flexButtonDivBuffer[0] = '/';
            flexButtonDivBuffer[1] = 0;
            flexButtonDiv.invalidate();

            flexButtonColonBuffer[0] = ':';
            flexButtonColonBuffer[1] = 0;
            flexButtonColon.invalidate();
        }
    }
    //发送按钮点击通知
    emitTouchTriggerCallback(1);
}

//数字-字母切换
void KeyBoardContainer::buttonNumberHandler()
{
    if (textArea_123Buffer[0] == '1')
    {
        textArea_123Buffer[0] = 'A';
        textArea_123Buffer[1] = 'B';
        textArea_123Buffer[2] = 'C';
        textArea_123Buffer[3] = 0;
        containerNumber.setVisible(true);
        buttonBackspace.setXY(428, 73 + 40);

        /*
        container2.setVisible(true);
        container2.invalidate();
        */
    }
    else
    {
        textArea_123Buffer[0] = '1';
        textArea_123Buffer[1] = '2';
        textArea_123Buffer[2] = '3';
        textArea_123Buffer[3] = 0;
        containerNumber.setVisible(false);
        buttonBackspace.setXY(440, 211 + 40);

        container2.setVisible(false);
        container2.invalidate();

        flexButtonChina.setPressed(false);
        flexButtonChina.invalidate();

        flexButtonDotBuffer[0] = '.';
        flexButtonDotBuffer[1] = 0;
        flexButtonDot.invalidate();

        container2.setVisible(false);
        container2.invalidate();

        //        flexButtonNum1Buffer[0]='1';
        //        flexButtonNum1Buffer[1]=0;
        //        flexButtonNum1.invalidate();

        flexButtonNum2Buffer[0] = '2';
        flexButtonNum2Buffer[1] = 0;
        flexButtonNum2.invalidate();

        flexButtonNum3Buffer[0] = '3';
        flexButtonNum3Buffer[1] = 0;
        flexButtonNum3.invalidate();

        flexButtonNum4Buffer[0] = '4';
        flexButtonNum4Buffer[1] = 0;
        flexButtonNum4.invalidate();

        flexButtonNum5Buffer[0] = '5';
        flexButtonNum5Buffer[1] = 0;
        flexButtonNum5.invalidate();

        flexButtonNum6Buffer[0] = '6';
        flexButtonNum6Buffer[1] = 0;
        flexButtonNum6.invalidate();

        flexButtonNum7Buffer[0] = '7';
        flexButtonNum7Buffer[1] = 0;
        flexButtonNum7.invalidate();

        flexButtonNum8Buffer[0] = '8';
        flexButtonNum8Buffer[1] = 0;
        flexButtonNum8.invalidate();

        flexButtonNum9Buffer[0] = '9';
        flexButtonNum9Buffer[1] = 0;
        flexButtonNum9.invalidate();

        flexButtonAddBuffer[0] = '+';
        flexButtonAddBuffer[1] = 0;
        flexButtonAdd.invalidate();

        flexButtonSubBuffer[0] = '-';
        flexButtonSubBuffer[1] = 0;
        flexButtonSub.invalidate();

        flexButtonMulBuffer[0] = '*';
        flexButtonMulBuffer[1] = 0;
        flexButtonMul.invalidate();

        flexButtonDivBuffer[0] = '/';
        flexButtonDivBuffer[1] = 0;
        flexButtonDiv.invalidate();

        flexButtonColonBuffer[0] = ':';
        flexButtonColonBuffer[1] = 0;
        flexButtonColon.invalidate();
    }
    containerNumber.invalidate();
    buttonBackspace.invalidate();

    //在单片机上会死机
    /*
    //恢复T9默认状态
    KeyBoardContainer().flexButtonChinaHandler();
    */
}

//切换中文
void KeyBoardContainer::flexButtonChinaHandler()
{
    uint8_t str[10];

    for (uint8_t i = 0; i < 200; i++)
    {
        KeyBoard_GlobalVariableStruct.String[i] = 0;
        KeyBoard_GlobalVariableStruct.PinYinString[i] = 0;
        KeyBoard_GlobalVariableStruct.ChinaString[i] = 0;
    }
    SetOutText(KeyBoard_GlobalVariableStruct.String, sizeof KeyBoard_GlobalVariableStruct.String);
    ClearChinaText();


    if (flexButtonChina.getPressed())
    {
        container2.setVisible(true);

        sprintf((char*)str, "%s", "重输");
        Unicode::fromUTF8((uint8_t*)str, flexButtonDotBuffer, strlen((char*)str));
        flexButtonDot.invalidate();

        container2.setVisible(true);
        container2.invalidate();

        //清空，开始输入中文
        KeyBoard_GlobalVariableStruct.String[0] = 0;
        this->SetOutText(KeyBoard_GlobalVariableStruct.String, sizeof(KeyBoard_GlobalVariableStruct.String));
        invalidate();

        //        flexButtonNum1Buffer[0]=' ';
        //        flexButtonNum1Buffer[1]=0;
        //        flexButtonNum1.invalidate();

        flexButtonNum2Buffer[0] = 'A';
        flexButtonNum2Buffer[1] = 'B';
        flexButtonNum2Buffer[2] = 'C';
        flexButtonNum2Buffer[3] = 0;
        flexButtonNum2.invalidate();

        flexButtonNum3Buffer[0] = 'D';
        flexButtonNum3Buffer[1] = 'E';
        flexButtonNum3Buffer[2] = 'F';
        flexButtonNum3Buffer[3] = 0;
        flexButtonNum3.invalidate();

        flexButtonNum4Buffer[0] = 'G';
        flexButtonNum4Buffer[1] = 'H';
        flexButtonNum4Buffer[2] = 'I';
        flexButtonNum4Buffer[3] = 0;
        flexButtonNum4.invalidate();

        flexButtonNum5Buffer[0] = 'J';
        flexButtonNum5Buffer[1] = 'K';
        flexButtonNum5Buffer[2] = 'L';
        flexButtonNum5Buffer[3] = 0;
        flexButtonNum5.invalidate();

        flexButtonNum6Buffer[0] = 'M';
        flexButtonNum6Buffer[1] = 'N';
        flexButtonNum6Buffer[2] = 'O';
        flexButtonNum6Buffer[3] = 0;
        flexButtonNum6.invalidate();

        flexButtonNum7Buffer[0] = 'P';
        flexButtonNum7Buffer[1] = 'Q';
        flexButtonNum7Buffer[2] = 'R';
        flexButtonNum7Buffer[3] = 'S';
        flexButtonNum7Buffer[4] = 0;
        flexButtonNum7.invalidate();

        flexButtonNum8Buffer[0] = 'T';
        flexButtonNum8Buffer[1] = 'U';
        flexButtonNum8Buffer[2] = 'V';
        flexButtonNum8Buffer[3] = 0;
        flexButtonNum8.invalidate();

        flexButtonNum9Buffer[0] = 'W';
        flexButtonNum9Buffer[1] = 'X';
        flexButtonNum9Buffer[2] = 'Y';
        flexButtonNum9Buffer[3] = 'Z';
        flexButtonNum9Buffer[4] = 0;
        flexButtonNum9.invalidate();

        flexButtonAddBuffer[0] = 0xff0c;
        flexButtonAddBuffer[1] = 0;
        flexButtonAdd.invalidate();

        flexButtonSubBuffer[0] = 0x3002;
        flexButtonSubBuffer[1] = 0;
        flexButtonSub.invalidate();

        flexButtonMulBuffer[0] = 0xff1f;
        flexButtonMulBuffer[1] = 0;
        flexButtonMul.invalidate();

        flexButtonDivBuffer[0] = 0xff01;
        flexButtonDivBuffer[1] = 0;
        flexButtonDiv.invalidate();

        flexButtonColonBuffer[0] = '~';
        flexButtonColonBuffer[1] = 0;
        flexButtonColon.invalidate();
    }
    else
    {
        container2.setVisible(false);

        flexButtonDotBuffer[0] = '.';
        flexButtonDotBuffer[1] = 0;
        flexButtonDot.invalidate();

        container2.setVisible(false);
        container2.invalidate();

        //        flexButtonNum1Buffer[0]='1';
        //        flexButtonNum1Buffer[1]=0;
        //        flexButtonNum1.invalidate();

        flexButtonNum2Buffer[0] = '2';
        flexButtonNum2Buffer[1] = 0;
        flexButtonNum2.invalidate();

        flexButtonNum3Buffer[0] = '3';
        flexButtonNum3Buffer[1] = 0;
        flexButtonNum3.invalidate();

        flexButtonNum4Buffer[0] = '4';
        flexButtonNum4Buffer[1] = 0;
        flexButtonNum4.invalidate();

        flexButtonNum5Buffer[0] = '5';
        flexButtonNum5Buffer[1] = 0;
        flexButtonNum5.invalidate();

        flexButtonNum6Buffer[0] = '6';
        flexButtonNum6Buffer[1] = 0;
        flexButtonNum6.invalidate();

        flexButtonNum7Buffer[0] = '7';
        flexButtonNum7Buffer[1] = 0;
        flexButtonNum7.invalidate();

        flexButtonNum8Buffer[0] = '8';
        flexButtonNum8Buffer[1] = 0;
        flexButtonNum8.invalidate();

        flexButtonNum9Buffer[0] = '9';
        flexButtonNum9Buffer[1] = 0;
        flexButtonNum9.invalidate();

        flexButtonAddBuffer[0] = '+';
        flexButtonAddBuffer[1] = 0;
        flexButtonAdd.invalidate();

        flexButtonSubBuffer[0] = '-';
        flexButtonSubBuffer[1] = 0;
        flexButtonSub.invalidate();

        flexButtonMulBuffer[0] = '*';
        flexButtonMulBuffer[1] = 0;
        flexButtonMul.invalidate();

        flexButtonDivBuffer[0] = '/';
        flexButtonDivBuffer[1] = 0;
        flexButtonDiv.invalidate();

        flexButtonColonBuffer[0] = ':';
        flexButtonColonBuffer[1] = 0;
        flexButtonColon.invalidate();
    }

    containerNum1_3.invalidate();
    containerNum4_6.invalidate();
    containerNum7_9.invalidate();
}

//显示中文预览
void KeyBoardContainer::SetOutChinaText1(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, OutChinaButton1Buffer, len);
    OutChinaButton1.invalidate();
}
void KeyBoardContainer::SetOutChinaText2(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, OutChinaButton2Buffer, len);
    OutChinaButton2.invalidate();
}
void KeyBoardContainer::SetOutChinaText3(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, OutChinaButton3Buffer, len);
    OutChinaButton3.invalidate();
}
void KeyBoardContainer::SetOutChinaText4(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, OutChinaButton4Buffer, len);
    OutChinaButton4.invalidate();
}
void KeyBoardContainer::SetOutChinaText5(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, OutChinaButton5Buffer, len);
    OutChinaButton5.invalidate();
}
void KeyBoardContainer::SetOutChinaText6(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, OutChinaButton6Buffer, len);
    OutChinaButton6.invalidate();
}

//显示拼音预览
void KeyBoardContainer::SetOutPinYinText5(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, flexButtonColonBuffer, len);
    flexButtonColon.invalidate();
}
void KeyBoardContainer::SetOutPinYinText4(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, flexButtonDivBuffer, len);
    flexButtonDiv.invalidate();
}
void KeyBoardContainer::SetOutPinYinText3(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, flexButtonMulBuffer, len);
    flexButtonMul.invalidate();
}
void KeyBoardContainer::SetOutPinYinText2(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, flexButtonSubBuffer, len);
    flexButtonSub.invalidate();
}
void KeyBoardContainer::SetOutPinYinText1(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, flexButtonAddBuffer, len);
    flexButtonAdd.invalidate();
}


//显示中文预览--显示第n个拼音的中文
void KeyBoardContainer::DispChina(uint8_t num)
{
    sprintf((char*)KeyBoard_GlobalVariableStruct.ChinaString, "%c%c%c", t9.pymb[num]->pymb[0 + KeyBoard_GlobalVariableStruct.ChinaStringOffset], t9.pymb[num]->pymb[1 + KeyBoard_GlobalVariableStruct.ChinaStringOffset], t9.pymb[num]->pymb[2 + KeyBoard_GlobalVariableStruct.ChinaStringOffset]);
    this->SetOutChinaText1(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
    if (OutChinaButton1Buffer[0] == 0)
    {
        sprintf((char*)KeyBoard_GlobalVariableStruct.ChinaString, "%c%c%c", ' ', ' ', ' ');
        this->SetOutChinaText2(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
        this->SetOutChinaText3(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
        this->SetOutChinaText4(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
        this->SetOutChinaText5(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
        this->SetOutChinaText6(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
        return;
    }

    sprintf((char*)KeyBoard_GlobalVariableStruct.ChinaString, "%c%c%c", t9.pymb[num]->pymb[3 + KeyBoard_GlobalVariableStruct.ChinaStringOffset], t9.pymb[num]->pymb[4 + KeyBoard_GlobalVariableStruct.ChinaStringOffset], t9.pymb[num]->pymb[5 + KeyBoard_GlobalVariableStruct.ChinaStringOffset]);
    this->SetOutChinaText2(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
    if (OutChinaButton2Buffer[0] == 0)
    {
        sprintf((char*)KeyBoard_GlobalVariableStruct.ChinaString, "%c%c%c", ' ', ' ', ' ');
        this->SetOutChinaText3(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
        this->SetOutChinaText4(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
        this->SetOutChinaText5(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
        this->SetOutChinaText6(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
        return;
    }

    sprintf((char*)KeyBoard_GlobalVariableStruct.ChinaString, "%c%c%c", t9.pymb[num]->pymb[6 + KeyBoard_GlobalVariableStruct.ChinaStringOffset], t9.pymb[num]->pymb[7 + KeyBoard_GlobalVariableStruct.ChinaStringOffset], t9.pymb[num]->pymb[8 + KeyBoard_GlobalVariableStruct.ChinaStringOffset]);
    this->SetOutChinaText3(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
    if (OutChinaButton3Buffer[0] == 0)
    {
        sprintf((char*)KeyBoard_GlobalVariableStruct.ChinaString, "%c%c%c", ' ', ' ', ' ');
        this->SetOutChinaText4(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
        this->SetOutChinaText5(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
        this->SetOutChinaText6(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
        return;
    }

    sprintf((char*)KeyBoard_GlobalVariableStruct.ChinaString, "%c%c%c", t9.pymb[num]->pymb[9 + KeyBoard_GlobalVariableStruct.ChinaStringOffset], t9.pymb[num]->pymb[10 + KeyBoard_GlobalVariableStruct.ChinaStringOffset], t9.pymb[num]->pymb[11 + KeyBoard_GlobalVariableStruct.ChinaStringOffset]);
    this->SetOutChinaText4(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
    if (OutChinaButton4Buffer[0] == 0)
    {
        sprintf((char*)KeyBoard_GlobalVariableStruct.ChinaString, "%c%c%c", ' ', ' ', ' ');
        this->SetOutChinaText5(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
        this->SetOutChinaText6(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
        return;
    }

    sprintf((char*)KeyBoard_GlobalVariableStruct.ChinaString, "%c%c%c", t9.pymb[num]->pymb[12 + KeyBoard_GlobalVariableStruct.ChinaStringOffset], t9.pymb[num]->pymb[13 + KeyBoard_GlobalVariableStruct.ChinaStringOffset], t9.pymb[num]->pymb[14 + KeyBoard_GlobalVariableStruct.ChinaStringOffset]);
    this->SetOutChinaText5(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
    if (OutChinaButton5Buffer[0] == 0)
    {
        sprintf((char*)KeyBoard_GlobalVariableStruct.ChinaString, "%c%c%c", ' ', ' ', ' ');
        this->SetOutChinaText6(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
        return;
    }

    sprintf((char*)KeyBoard_GlobalVariableStruct.ChinaString, "%c%c%c", t9.pymb[num]->pymb[15 + KeyBoard_GlobalVariableStruct.ChinaStringOffset], t9.pymb[num]->pymb[16 + KeyBoard_GlobalVariableStruct.ChinaStringOffset], t9.pymb[num]->pymb[17 + KeyBoard_GlobalVariableStruct.ChinaStringOffset]);
    this->SetOutChinaText6(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
    if (OutChinaButton6Buffer[0] == 0)
    {
        return;
    }

    invalidate();
}
//显示中文输入预览
void KeyBoardContainer::DispChinaText()
{
    if (flexButtonChina.getPressed())
    {
        unsigned char t = 0;

        t = t9.getpymb(KeyBoard_GlobalVariableStruct.String);
        if (t & 0X80)
        {
            sprintf((char*)KeyBoard_GlobalVariableStruct.ChinaString, "%c%c%c", ' ', ' ', ' ');
            this->SetOutChinaText1(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
            this->SetOutChinaText2(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
            this->SetOutChinaText3(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
            this->SetOutChinaText4(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
            this->SetOutChinaText5(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
            this->SetOutChinaText6(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));

            sprintf((char*)KeyBoard_GlobalVariableStruct.ChinaString, "%c%c%c", t9.pymb[0]->pymb[0 + KeyBoard_GlobalVariableStruct.ChinaStringOffset], t9.pymb[0]->pymb[1 + KeyBoard_GlobalVariableStruct.ChinaStringOffset], t9.pymb[0]->pymb[2 + KeyBoard_GlobalVariableStruct.ChinaStringOffset]);
            this->SetOutChinaText1(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));

            sprintf((char*)KeyBoard_GlobalVariableStruct.PinYinString, "%s", t9.pymb[0]->py);
            this->SetOutPinYinText1(KeyBoard_GlobalVariableStruct.PinYinString, sizeof KeyBoard_GlobalVariableStruct.PinYinString);
            sprintf((char*)KeyBoard_GlobalVariableStruct.PinYinString, "%s", " ");
            this->SetOutPinYinText2(KeyBoard_GlobalVariableStruct.PinYinString, sizeof KeyBoard_GlobalVariableStruct.PinYinString);
            sprintf((char*)KeyBoard_GlobalVariableStruct.PinYinString, "%s", " ");
            this->SetOutPinYinText3(KeyBoard_GlobalVariableStruct.PinYinString, sizeof KeyBoard_GlobalVariableStruct.PinYinString);
            sprintf((char*)KeyBoard_GlobalVariableStruct.PinYinString, "%s", " ");
            this->SetOutPinYinText4(KeyBoard_GlobalVariableStruct.PinYinString, sizeof KeyBoard_GlobalVariableStruct.PinYinString);
            sprintf((char*)KeyBoard_GlobalVariableStruct.PinYinString, "%s", " ");
            this->SetOutPinYinText5(KeyBoard_GlobalVariableStruct.PinYinString, sizeof KeyBoard_GlobalVariableStruct.PinYinString);
        }
        else if (t)
        {
            sprintf((char*)KeyBoard_GlobalVariableStruct.ChinaString, "%c%c%c", ' ', ' ', ' ');
            this->SetOutChinaText1(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
            this->SetOutChinaText2(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
            this->SetOutChinaText3(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
            this->SetOutChinaText4(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
            this->SetOutChinaText5(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
            this->SetOutChinaText6(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));

            sprintf((char*)KeyBoard_GlobalVariableStruct.PinYinString, "%s", " ");
            this->SetOutPinYinText1(KeyBoard_GlobalVariableStruct.PinYinString, sizeof KeyBoard_GlobalVariableStruct.PinYinString);
            sprintf((char*)KeyBoard_GlobalVariableStruct.PinYinString, "%s", " ");
            this->SetOutPinYinText2(KeyBoard_GlobalVariableStruct.PinYinString, sizeof KeyBoard_GlobalVariableStruct.PinYinString);
            sprintf((char*)KeyBoard_GlobalVariableStruct.PinYinString, "%s", " ");
            this->SetOutPinYinText3(KeyBoard_GlobalVariableStruct.PinYinString, sizeof KeyBoard_GlobalVariableStruct.PinYinString);
            sprintf((char*)KeyBoard_GlobalVariableStruct.PinYinString, "%s", " ");
            this->SetOutPinYinText4(KeyBoard_GlobalVariableStruct.PinYinString, sizeof KeyBoard_GlobalVariableStruct.PinYinString);
            sprintf((char*)KeyBoard_GlobalVariableStruct.PinYinString, "%s", " ");
            this->SetOutPinYinText5(KeyBoard_GlobalVariableStruct.PinYinString, sizeof KeyBoard_GlobalVariableStruct.PinYinString);

            //默认显示第一个拼音的中文
            DispChina(0);
            for (uint8_t i = 0; i < t; i++)
            {
                //显示拼音预览
                sprintf((char*)KeyBoard_GlobalVariableStruct.PinYinString, "%s", t9.pymb[i]->py);
                switch (i)
                {
                case(0):
                    this->SetOutPinYinText1(KeyBoard_GlobalVariableStruct.PinYinString, sizeof KeyBoard_GlobalVariableStruct.PinYinString);
                    break;
                case(1):
                    this->SetOutPinYinText2(KeyBoard_GlobalVariableStruct.PinYinString, sizeof KeyBoard_GlobalVariableStruct.PinYinString);
                    break;
                case(2):
                    this->SetOutPinYinText3(KeyBoard_GlobalVariableStruct.PinYinString, sizeof KeyBoard_GlobalVariableStruct.PinYinString);
                    break;
                case(3):
                    this->SetOutPinYinText4(KeyBoard_GlobalVariableStruct.PinYinString, sizeof KeyBoard_GlobalVariableStruct.PinYinString);
                    break;
                case(4):
                    this->SetOutPinYinText5(KeyBoard_GlobalVariableStruct.PinYinString, sizeof KeyBoard_GlobalVariableStruct.PinYinString);
                    break;
                }
            }
        }
        invalidate();
    }
}

//清空中文输入预览
void KeyBoardContainer::ClearChinaText()
{
    sprintf((char*)KeyBoard_GlobalVariableStruct.ChinaString, "%c%c%c", ' ', ' ', ' ');
    this->SetOutChinaText1(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
    this->SetOutChinaText2(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
    this->SetOutChinaText3(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
    this->SetOutChinaText4(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
    this->SetOutChinaText5(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));
    this->SetOutChinaText6(KeyBoard_GlobalVariableStruct.ChinaString, sizeof(KeyBoard_GlobalVariableStruct.ChinaString));

    sprintf((char*)KeyBoard_GlobalVariableStruct.PinYinString, "%s", " ");
    this->SetOutPinYinText1(KeyBoard_GlobalVariableStruct.PinYinString, sizeof KeyBoard_GlobalVariableStruct.PinYinString);
    this->SetOutPinYinText2(KeyBoard_GlobalVariableStruct.PinYinString, sizeof KeyBoard_GlobalVariableStruct.PinYinString);
    this->SetOutPinYinText3(KeyBoard_GlobalVariableStruct.PinYinString, sizeof KeyBoard_GlobalVariableStruct.PinYinString);
    this->SetOutPinYinText4(KeyBoard_GlobalVariableStruct.PinYinString, sizeof KeyBoard_GlobalVariableStruct.PinYinString);
    this->SetOutPinYinText5(KeyBoard_GlobalVariableStruct.PinYinString, sizeof KeyBoard_GlobalVariableStruct.PinYinString);
    invalidate();
}

//中文预览右偏移
void KeyBoardContainer::flexButtonRightHandler()
{
    for (uint8_t k = 0; k < 100; k++)
    {
        if (KeyBoard_GlobalVariableStruct.String[k] == '\0')
        {
            if (k < 1)
            {
                return;
            }
        }
    }

    uint16_t n = 0;
    for (uint16_t i = 0;; i++)
    {
        if (t9.pymb[KeyBoard_GlobalVariableStruct.PinYinIndex]->pymb[i] == 0)
        {
            n = i;
            break;
        }
    }

    if (KeyBoard_GlobalVariableStruct.ChinaStringOffset < (n - 18))
    {
        KeyBoard_GlobalVariableStruct.ChinaStringOffset += 3 * 6;
    }
    DispChina(KeyBoard_GlobalVariableStruct.PinYinIndex);
    if (OutChinaButton6Buffer[0] == 0 && OutChinaButton5Buffer[0] == 0 && OutChinaButton4Buffer[0] == 0 && OutChinaButton3Buffer[0] == 0 && OutChinaButton2Buffer[0] == 0 && OutChinaButton1Buffer[0] == 0)
    {
        KeyBoard_GlobalVariableStruct.ChinaStringOffset -= 3 * 5;
        DispChina(KeyBoard_GlobalVariableStruct.PinYinIndex);
    }
}
void KeyBoardContainer::flexButtonLeftHandler()
{
    for (uint8_t k = 0; k < 100; k++)
    {
        if (KeyBoard_GlobalVariableStruct.String[k] == '\0')
        {
            if (k < 1)
            {
                return;
            }
        }
    }

    KeyBoard_GlobalVariableStruct.ChinaStringOffset -= 3 * 6;
    if (KeyBoard_GlobalVariableStruct.ChinaStringOffset < 0)
    {
        KeyBoard_GlobalVariableStruct.ChinaStringOffset = 0;
    }
    DispChina(KeyBoard_GlobalVariableStruct.PinYinIndex);
}


