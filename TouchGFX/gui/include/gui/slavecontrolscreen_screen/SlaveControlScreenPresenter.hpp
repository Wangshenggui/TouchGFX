#ifndef SLAVECONTROLSCREENPRESENTER_HPP
#define SLAVECONTROLSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class SlaveControlScreenView;

class SlaveControlScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    SlaveControlScreenPresenter(SlaveControlScreenView& v);

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

    virtual ~SlaveControlScreenPresenter() {};

private:
    SlaveControlScreenPresenter();

    SlaveControlScreenView& view;
};

#endif // SLAVECONTROLSCREENPRESENTER_HPP
