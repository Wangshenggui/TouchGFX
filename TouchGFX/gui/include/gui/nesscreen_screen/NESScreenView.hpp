#ifndef NESSCREENVIEW_HPP
#define NESSCREENVIEW_HPP

#include <gui_generated/nesscreen_screen/NESScreenViewBase.hpp>
#include <gui/nesscreen_screen/NESScreenPresenter.hpp>

class NESScreenView : public NESScreenViewBase
{
public:
    NESScreenView();
    virtual ~NESScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
        
    virtual void handleTickEvent();
protected:
};

#endif // NESSCREENVIEW_HPP
