#ifndef NESSCREENPRESENTER_HPP
#define NESSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class NESScreenView;

class NESScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    NESScreenPresenter(NESScreenView& v);

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

    virtual ~NESScreenPresenter() {};

    //启动NES
    void start_nes(bool data)
    {
        model->start_nes(data);
    }

    //消息事件
    virtual void TaskContGUIQueue_Event(unsigned char key);
private:
    NESScreenPresenter();

    NESScreenView& view;
};

#endif // NESSCREENPRESENTER_HPP
