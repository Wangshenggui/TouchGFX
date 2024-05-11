#include <gui/motiontrailscreen_screen/MotionTrailScreenView.hpp>
#include <gui/motiontrailscreen_screen/MotionTrailScreenPresenter.hpp>

MotionTrailScreenPresenter::MotionTrailScreenPresenter(MotionTrailScreenView& v)
    : view(v)
{

}

void MotionTrailScreenPresenter::activate()
{

}

void MotionTrailScreenPresenter::deactivate()
{

}

//消息事件
void MotionTrailScreenPresenter::TaskContGUIQueue_Event(unsigned char key)
{
    view.handleKeyEvent(key);
}
