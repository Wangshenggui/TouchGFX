#ifndef PADDYSOWINGSCREENPRESENTER_HPP
#define PADDYSOWINGSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class PaddySowingScreenView;

class PaddySowingScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    PaddySowingScreenPresenter(PaddySowingScreenView& v);

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

    virtual ~PaddySowingScreenPresenter() {};

    //消息事件
    virtual void TaskContGUIQueue_Event(unsigned char key);
private:
    PaddySowingScreenPresenter();

    PaddySowingScreenView& view;
};

#endif // PADDYSOWINGSCREENPRESENTER_HPP
