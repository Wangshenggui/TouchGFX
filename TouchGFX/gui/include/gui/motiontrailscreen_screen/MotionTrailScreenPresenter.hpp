#ifndef MOTIONTRAILSCREENPRESENTER_HPP
#define MOTIONTRAILSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class MotionTrailScreenView;

class MotionTrailScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    MotionTrailScreenPresenter(MotionTrailScreenView& v);

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

    virtual ~MotionTrailScreenPresenter() {};

    //消息事件
    virtual void TaskContGUIQueue_Event(unsigned char key);
private:
    MotionTrailScreenPresenter();

    MotionTrailScreenView& view;
};

#endif // MOTIONTRAILSCREENPRESENTER_HPP
