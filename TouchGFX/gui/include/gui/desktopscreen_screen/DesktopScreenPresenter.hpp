#ifndef DESKTOPSCREENPRESENTER_HPP
#define DESKTOPSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class DesktopScreenView;

class DesktopScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    DesktopScreenPresenter(DesktopScreenView& v);

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

    virtual ~DesktopScreenPresenter() {};

    //设置风扇
    void set_fan_onoff(bool data)
    {
        model->set_fan_onoff(data);
    }

    //消息事件
    virtual void TaskContGUIQueue_Event(unsigned char key);
private:
    DesktopScreenPresenter();

    DesktopScreenView& view;
};

#endif // DESKTOPSCREENPRESENTER_HPP
