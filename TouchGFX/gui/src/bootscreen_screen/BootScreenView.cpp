#include <gui/bootscreen_screen/BootScreenView.hpp>


#ifndef SIMULATOR
#include "Backlight.h"
#include "Voice.h"
#endif

BootScreenView::BootScreenView() :
    BoxFadeEndCallback(this, &BootScreenView::BoxFadeEndHandler),
    TiledImageFadeEndCallback(this, &BootScreenView::TiledImageFadeEndHandler)
{
#ifndef SIMULATOR
    SetBacklight(GetBacklight());
    SetVoiceVolume(GetVoiceVolume());
#endif
}

void BootScreenView::setupScreen()
{
    BootScreenViewBase::setupScreen();

    //����Logo
    box2.startFadeAnimation(0, 150);
    //��ӻص�
    box2.setFadeAnimationEndedAction(BoxFadeEndCallback);
}

void BootScreenView::tearDownScreen()
{
    BootScreenViewBase::tearDownScreen();
}

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
void BootScreenView::BoxFadeEndHandler(const touchgfx::FadeAnimator<touchgfx::Box>& obj)
{
    if (&box2 == &obj)
    {
        //����Desktop
        tiledImage2.startFadeAnimation(255, 120);
        //��ӻص�
        tiledImage2.setFadeAnimationEndedAction(TiledImageFadeEndCallback);
    }
}

void BootScreenView::TiledImageFadeEndHandler(const touchgfx::FadeAnimator<touchgfx::TiledImage>& obj)
{
    if (&tiledImage2 == &obj)
    {
        //��ת��DesktopScreen
        application().gotoDesktopScreenScreenNoTransition();
    }
}







