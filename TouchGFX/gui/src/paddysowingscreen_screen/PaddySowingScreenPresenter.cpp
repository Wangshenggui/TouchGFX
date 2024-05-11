#include <gui/paddysowingscreen_screen/PaddySowingScreenView.hpp>
#include <gui/paddysowingscreen_screen/PaddySowingScreenPresenter.hpp>

PaddySowingScreenPresenter::PaddySowingScreenPresenter(PaddySowingScreenView& v)
    : view(v)
{

}

void PaddySowingScreenPresenter::activate()
{

}

void PaddySowingScreenPresenter::deactivate()
{

}


//消息事件
void PaddySowingScreenPresenter::TaskContGUIQueue_Event(unsigned char key)
{
    view.handleKeyEvent(key);
}
