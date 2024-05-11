#include <gui/settingscreen_screen/SettingScreenView.hpp>
#include <gui/settingscreen_screen/SettingScreenPresenter.hpp>

SettingScreenPresenter::SettingScreenPresenter(SettingScreenView& v)
    : view(v)
{

}

void SettingScreenPresenter::activate()
{

}

void SettingScreenPresenter::deactivate()
{

}

//��Ϣ�¼�
void SettingScreenPresenter::TaskContGUIQueue_Event(unsigned char key)
{
    view.handleKeyEvent(key);
}

