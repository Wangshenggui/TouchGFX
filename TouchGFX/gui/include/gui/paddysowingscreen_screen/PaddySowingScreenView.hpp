#ifndef PADDYSOWINGSCREENVIEW_HPP
#define PADDYSOWINGSCREENVIEW_HPP

#include <gui_generated/paddysowingscreen_screen/PaddySowingScreenViewBase.hpp>
#include <gui/paddysowingscreen_screen/PaddySowingScreenPresenter.hpp>

#include <gui_generated/paddysowingscreen_screen/PaddySowingScreenViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>



//typedef struct
//{
//    //运行时长
//    uint16_t SlaveRunTime;
//}PaddySowing_ScreenGlobalVariableStructure;
//extern PaddySowing_ScreenGlobalVariableStructure PaddySowing_ScreenGlobalVariableStruct;


class PaddySowingScreenView : public PaddySowingScreenViewBase
{
public:
    PaddySowingScreenView();
    virtual ~PaddySowingScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void SetTotality(uint8_t Totality);
    virtual void SetRunNum(uint8_t n);
    virtual void SetMalfunctionNum(uint8_t n);
    virtual void RunningTime(uint16_t n);
    virtual void DisplayPositioningStatus(char s);

    virtual void handleTickEvent();

    virtual void flexButton1ClickBackHandler();
    virtual void flexButton2ClickBackHandler();
    virtual void flexButton3ClickBackHandler();
    virtual void flexButton4ClickBackHandler();
    virtual void flexButton5ClickBackHandler();
    virtual void flexButton6ClickBackHandler();
    virtual void flexButton7ClickBackHandler();
    virtual void flexButton8ClickBackHandler();
    virtual void ErrBackButtonHandler();
    virtual void BackFlexButtonHandler();
        
    virtual void flexButton9Handler();

    virtual void handleKeyEvent(uint8_t key);

protected:
    //选择显示曲线的按钮索引
    uint8_t ButtonGraph_n;
    uint8_t GraphData[8][200];
    //检测是否进入曲线显示
    bool GraphFlag;
    //用按钮开启界面更新
    bool StartFlag;
};

#endif // PADDYSOWINGSCREENVIEW_HPP
