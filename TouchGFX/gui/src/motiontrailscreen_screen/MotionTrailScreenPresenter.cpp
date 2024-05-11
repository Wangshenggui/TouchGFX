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

//��Ϣ�¼�
void MotionTrailScreenPresenter::TaskContGUIQueue_Event(unsigned char key)
{
    view.handleKeyEvent(key);
}
