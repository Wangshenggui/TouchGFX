#include <gui/desktopscreen_screen/DesktopScreenView.hpp>
#include <gui/desktopscreen_screen/DesktopScreenPresenter.hpp>

DesktopScreenPresenter::DesktopScreenPresenter(DesktopScreenView& v)
    : view(v)
{

}

void DesktopScreenPresenter::activate()
{

}

void DesktopScreenPresenter::deactivate()
{

}

//��Ϣ�¼�
void DesktopScreenPresenter::TaskContGUIQueue_Event(unsigned char key)
{
    view.handleKeyEvent(key);
}







