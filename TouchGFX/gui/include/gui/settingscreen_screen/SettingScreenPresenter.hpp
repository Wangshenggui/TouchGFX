#ifndef SETTINGSCREENPRESENTER_HPP
#define SETTINGSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class SettingScreenView;

class SettingScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    SettingScreenPresenter(SettingScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~SettingScreenPresenter() {};

    //��Ϣ�¼�
    virtual void TaskContGUIQueue_Event(unsigned char key);
        
        //���÷���
    void set_fan_onoff(bool data)
    {
        model->set_fan_onoff(data);
    }
private:
    SettingScreenPresenter();

    SettingScreenView& view;
};

#endif // SETTINGSCREENPRESENTER_HPP
