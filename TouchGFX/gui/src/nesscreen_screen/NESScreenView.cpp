#include <gui/nesscreen_screen/NESScreenView.hpp>

#ifndef SIMULATOR
#include "main.h"
#endif

NESScreenView::NESScreenView()
{

}

void NESScreenView::setupScreen()
{
    nESContainer1.setVisible(true);
    nESContainer1.invalidate();

    NESScreenViewBase::setupScreen();
}

void NESScreenView::tearDownScreen()
{
    NESScreenViewBase::tearDownScreen();
}

uint32_t i = 0;
void NESScreenView::handleTickEvent()
{
    if (i++ == 200)
    {
        i = 0;
        //Æô¶¯NESÓÎÏ·
        presenter->start_nes(1);
    }
}

