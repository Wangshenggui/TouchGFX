#ifndef RADIOSSCOM_SCREENPRESENTER_HPP
#define RADIOSSCOM_SCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class RadioSSCOM_ScreenView;

class RadioSSCOM_ScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    RadioSSCOM_ScreenPresenter(RadioSSCOM_ScreenView& v);

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

    virtual ~RadioSSCOM_ScreenPresenter() {};

private:
    RadioSSCOM_ScreenPresenter();

    RadioSSCOM_ScreenView& view;
};

#endif // RADIOSSCOM_SCREENPRESENTER_HPP
