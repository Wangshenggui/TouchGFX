/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <new>
#include <gui_generated/common/FrontendApplicationBase.hpp>
#include <gui/common/FrontendHeap.hpp>
#include <touchgfx/transitions/NoTransition.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Texts.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <platform/driver/lcd/LCD16bpp.hpp>
#include <gui/bootscreen_screen/BootScreenView.hpp>
#include <gui/bootscreen_screen/BootScreenPresenter.hpp>
#include <gui/desktopscreen_screen/DesktopScreenView.hpp>
#include <gui/desktopscreen_screen/DesktopScreenPresenter.hpp>
#include <gui/settingscreen_screen/SettingScreenView.hpp>
#include <gui/settingscreen_screen/SettingScreenPresenter.hpp>
#include <gui/paddysowingscreen_screen/PaddySowingScreenView.hpp>
#include <gui/paddysowingscreen_screen/PaddySowingScreenPresenter.hpp>
#include <gui/filemanagerscreen_screen/FileManagerScreenView.hpp>
#include <gui/filemanagerscreen_screen/FileManagerScreenPresenter.hpp>
#include <gui/usbinterconnectionscreen_screen/USBInterconnectionScreenView.hpp>
#include <gui/usbinterconnectionscreen_screen/USBInterconnectionScreenPresenter.hpp>
#include <gui/slavecontrolscreen_screen/SlaveControlScreenView.hpp>
#include <gui/slavecontrolscreen_screen/SlaveControlScreenPresenter.hpp>
#include <gui/rtkconfigurationscreen_screen/RTKConfigurationScreenView.hpp>
#include <gui/rtkconfigurationscreen_screen/RTKConfigurationScreenPresenter.hpp>
#include <gui/screen_4gmodulesetup_screen/Screen_4GModuleSetupView.hpp>
#include <gui/screen_4gmodulesetup_screen/Screen_4GModuleSetupPresenter.hpp>
#include <gui/radiosscom_screen_screen/RadioSSCOM_ScreenView.hpp>
#include <gui/radiosscom_screen_screen/RadioSSCOM_ScreenPresenter.hpp>
#include <gui/nesscreen_screen/NESScreenView.hpp>
#include <gui/nesscreen_screen/NESScreenPresenter.hpp>
#include <gui/motiontrailscreen_screen/MotionTrailScreenView.hpp>
#include <gui/motiontrailscreen_screen/MotionTrailScreenPresenter.hpp>

using namespace touchgfx;

FrontendApplicationBase::FrontendApplicationBase(Model& m, FrontendHeap& heap)
    : touchgfx::MVPApplication(),
      transitionCallback(),
      frontendHeap(heap),
      model(m)
{
    touchgfx::HAL::getInstance()->setDisplayOrientation(touchgfx::ORIENTATION_LANDSCAPE);
    touchgfx::Texts::setLanguage(GB);
    reinterpret_cast<touchgfx::LCD16bpp&>(touchgfx::HAL::lcd()).enableTextureMapperAll();
    reinterpret_cast<touchgfx::LCD16bpp&>(touchgfx::HAL::lcd()).enableDecompressorL8_All();
}

/*
 * Screen Transition Declarations
 */

// BootScreen

void FrontendApplicationBase::gotoBootScreenScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoBootScreenScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoBootScreenScreenNoTransitionImpl()
{
    touchgfx::makeTransition<BootScreenView, BootScreenPresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// DesktopScreen

void FrontendApplicationBase::gotoDesktopScreenScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoDesktopScreenScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoDesktopScreenScreenNoTransitionImpl()
{
    touchgfx::makeTransition<DesktopScreenView, DesktopScreenPresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// SettingScreen

void FrontendApplicationBase::gotoSettingScreenScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoSettingScreenScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoSettingScreenScreenNoTransitionImpl()
{
    touchgfx::makeTransition<SettingScreenView, SettingScreenPresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// PaddySowingScreen

void FrontendApplicationBase::gotoPaddySowingScreenScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoPaddySowingScreenScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoPaddySowingScreenScreenNoTransitionImpl()
{
    touchgfx::makeTransition<PaddySowingScreenView, PaddySowingScreenPresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// FileManagerScreen

void FrontendApplicationBase::gotoFileManagerScreenScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoFileManagerScreenScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoFileManagerScreenScreenNoTransitionImpl()
{
    touchgfx::makeTransition<FileManagerScreenView, FileManagerScreenPresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// USBInterconnectionScreen

void FrontendApplicationBase::gotoUSBInterconnectionScreenScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoUSBInterconnectionScreenScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoUSBInterconnectionScreenScreenNoTransitionImpl()
{
    touchgfx::makeTransition<USBInterconnectionScreenView, USBInterconnectionScreenPresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// SlaveControlScreen

void FrontendApplicationBase::gotoSlaveControlScreenScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoSlaveControlScreenScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoSlaveControlScreenScreenNoTransitionImpl()
{
    touchgfx::makeTransition<SlaveControlScreenView, SlaveControlScreenPresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// RTKConfigurationScreen

void FrontendApplicationBase::gotoRTKConfigurationScreenScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoRTKConfigurationScreenScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoRTKConfigurationScreenScreenNoTransitionImpl()
{
    touchgfx::makeTransition<RTKConfigurationScreenView, RTKConfigurationScreenPresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// Screen_4GModuleSetup

void FrontendApplicationBase::gotoScreen_4GModuleSetupScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoScreen_4GModuleSetupScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoScreen_4GModuleSetupScreenNoTransitionImpl()
{
    touchgfx::makeTransition<Screen_4GModuleSetupView, Screen_4GModuleSetupPresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// RadioSSCOM_Screen

void FrontendApplicationBase::gotoRadioSSCOM_ScreenScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoRadioSSCOM_ScreenScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoRadioSSCOM_ScreenScreenNoTransitionImpl()
{
    touchgfx::makeTransition<RadioSSCOM_ScreenView, RadioSSCOM_ScreenPresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// NESScreen

void FrontendApplicationBase::gotoNESScreenScreenBlockTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoNESScreenScreenBlockTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoNESScreenScreenBlockTransitionImpl()
{
    touchgfx::makeTransition<NESScreenView, NESScreenPresenter, touchgfx::BlockTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// MotionTrailScreen

void FrontendApplicationBase::gotoMotionTrailScreenScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoMotionTrailScreenScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoMotionTrailScreenScreenNoTransitionImpl()
{
    touchgfx::makeTransition<MotionTrailScreenView, MotionTrailScreenPresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}