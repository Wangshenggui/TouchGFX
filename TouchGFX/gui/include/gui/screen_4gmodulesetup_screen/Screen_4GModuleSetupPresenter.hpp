#ifndef SCREEN_4GMODULESETUPPRESENTER_HPP
#define SCREEN_4GMODULESETUPPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_4GModuleSetupView;

class Screen_4GModuleSetupPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen_4GModuleSetupPresenter(Screen_4GModuleSetupView& v);

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

    virtual ~Screen_4GModuleSetupPresenter() {};

private:
    Screen_4GModuleSetupPresenter();

    Screen_4GModuleSetupView& view;
};

#endif // SCREEN_4GMODULESETUPPRESENTER_HPP
