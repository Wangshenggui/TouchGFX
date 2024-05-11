#ifndef SCROLLINGWHEELSMALL_HPP
#define SCROLLINGWHEELSMALL_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <gui/common/ScrollingWheels/ScrollingMenu.hpp>
#include <gui/common/ScrollingWheels/TouchForwarder.hpp>
#include <gui/common/ScrollingWheels/TextAreaWithOneWildcardContainer.hpp>

using namespace touchgfx;

class ScrollingWheel : public Container
{
public:
    ScrollingWheel();
    virtual ~ScrollingWheel() {}

    virtual void setup();

    virtual void setSelectedItem(int index);
    virtual int getSelectedItem();
    virtual void setTouchable(bool touchable);

protected:
    Image background;
    Image shadowOverlay;

    ScrollingMenu backgroundScrollingMenu;
    Callback<ScrollingWheel, int, int> initializeBackgroundScrollingMenuItemCallback;
    virtual void initializeBackgroundScrollingMenuItem(int containerIndex, int itemIndex) = 0;

    ScrollingMenu centerScrollingMenu;
    Callback<ScrollingWheel, int, int> initializeCenterScrollingMenuItemCallback;
    virtual void initializeCenterScrollingMenuItem(int containerIndex, int itemIndex) = 0;

    // Propagates drag events to both ScrollingMenus
    TouchForwarder touchOverlay;
};

#endif // SCROLLINGWHEELSMALL_HPP
