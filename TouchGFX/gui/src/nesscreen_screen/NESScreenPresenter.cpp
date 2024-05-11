#include <gui/nesscreen_screen/NESScreenView.hpp>
#include <gui/nesscreen_screen/NESScreenPresenter.hpp>

NESScreenPresenter::NESScreenPresenter(NESScreenView& v)
    : view(v)
{

}

void NESScreenPresenter::activate()
{

}

void NESScreenPresenter::deactivate()
{

}


//消息事件
void NESScreenPresenter::TaskContGUIQueue_Event(unsigned char key)
{
    view.handleKeyEvent(key);
}
