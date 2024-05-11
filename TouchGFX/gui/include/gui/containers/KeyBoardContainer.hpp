#ifndef KEYBOARDCONTAINER_HPP
#define KEYBOARDCONTAINER_HPP

#include <gui_generated/containers/KeyBoardContainerBase.hpp>

typedef struct
{
    bool CaseFlag;
    uint8_t String[200];
    uint8_t ChinaString[200];
    uint8_t PinYinString[200];
    int16_t ChinaStringOffset;
    uint8_t PinYinIndex;
}KeyBoard_GlobalVariableStructure;
extern KeyBoard_GlobalVariableStructure KeyBoard_GlobalVariableStruct;

class KeyBoardContainer : public KeyBoardContainerBase
{
public:
    KeyBoardContainer();
    virtual ~KeyBoardContainer() {}

    virtual void initialize();
        
    virtual void SwitchCaps();
    virtual void ToggleLowercase();
    virtual void buttonShiftHandler();
    virtual void SetOutText(uint8_t* str, uint32_t len);
    virtual void ButtonAction1(uint8_t value);
    virtual void buttonBackspaceHandler();
    virtual void buttonNumberHandler();
    virtual void flexButtonChinaHandler();
    virtual void SetOutChinaText1(uint8_t* str, uint32_t len);
    virtual void SetOutChinaText2(uint8_t* str, uint32_t len);
    virtual void SetOutChinaText3(uint8_t* str, uint32_t len);
    virtual void SetOutChinaText4(uint8_t* str, uint32_t len);
    virtual void SetOutChinaText5(uint8_t* str, uint32_t len);
    virtual void SetOutChinaText6(uint8_t* str, uint32_t len);
        
    virtual void SetOutPinYinText1(uint8_t* str, uint32_t len);
    virtual void SetOutPinYinText2(uint8_t* str, uint32_t len);
    virtual void SetOutPinYinText3(uint8_t* str, uint32_t len);
    virtual void SetOutPinYinText4(uint8_t* str, uint32_t len);
    virtual void SetOutPinYinText5(uint8_t* str, uint32_t len);
	
	virtual void DispChinaText();
	virtual void ClearChinaText();
    
    virtual void DispChina(uint8_t num);
    
    virtual void flexButtonRightHandler();
    virtual void flexButtonLeftHandler();
protected:
    
};

#endif // KEYBOARDCONTAINER_HPP
