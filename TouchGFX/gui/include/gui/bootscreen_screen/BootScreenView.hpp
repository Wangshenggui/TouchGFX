#ifndef BOOTSCREENVIEW_HPP
#define BOOTSCREENVIEW_HPP

#include <gui_generated/bootscreen_screen/BootScreenViewBase.hpp>
#include <gui/bootscreen_screen/BootScreenPresenter.hpp>

#ifndef SIMULATOR
#include "myFatFs.h"
#include "Radio.h"
#include "usbd_storage.h"
#include <STM32TouchController.hpp>
#endif

#include <gui/desktopscreen_screen/DesktopScreenView.hpp>
#include <gui/paddysowingscreen_screen/PaddySowingScreenView.hpp>
#include <gui/containers/FileManagerContainer.hpp>
#include <gui/containers/KeyBoardContainer.hpp>



class BootScreenView : public BootScreenViewBase
{
public:
    BootScreenView();
    virtual ~BootScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    //////////////////////////////////////////////
    //���������ص�����
    void BoxFadeEndHandler(const touchgfx::FadeAnimator<touchgfx::Box>& obj);
    //���������ص�����
    void TiledImageFadeEndHandler(const touchgfx::FadeAnimator<touchgfx::TiledImage>& obj);
protected:
    //����ص�
    Callback<BootScreenView, const touchgfx::FadeAnimator<touchgfx::Box>&> BoxFadeEndCallback;
    //����ص�
    Callback<BootScreenView, const touchgfx::FadeAnimator<touchgfx::TiledImage>&> TiledImageFadeEndCallback;
};

#endif // BOOTSCREENVIEW_HPP
