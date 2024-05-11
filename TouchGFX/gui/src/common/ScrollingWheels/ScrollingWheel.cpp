#include <gui/common/ScrollingWheels/ScrollingWheel.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>

ScrollingWheel::ScrollingWheel() :
    initializeBackgroundScrollingMenuItemCallback(this, &ScrollingWheel::initializeBackgroundScrollingMenuItem),
    initializeCenterScrollingMenuItemCallback(this, &ScrollingWheel::initializeCenterScrollingMenuItem),
    touchOverlay(backgroundScrollingMenu, centerScrollingMenu)
{
}

void ScrollingWheel::setup()
{
    // Background is assumed to start in 0,0 and fill the entire ScrollingWheel
    background.setXY(0, 0);

    add(background);
    add(backgroundScrollingMenu);
    add(shadowOverlay);
    add(centerScrollingMenu);

    touchOverlay.setPosition(background.getX(), background.getY(), background.getWidth(), background.getHeight());
    add(touchOverlay);

    setWidth(background.getWidth());
    setHeight(background.getHeight());
}

void ScrollingWheel::setSelectedItem(int index)
{
    backgroundScrollingMenu.setSelectedItem(index);
    centerScrollingMenu.setSelectedItem(index);
}

int ScrollingWheel::getSelectedItem()
{
    return backgroundScrollingMenu.getSelectedItem();
}

void ScrollingWheel::setTouchable(bool touchable)
{
    backgroundScrollingMenu.setTouchable(touchable);
    centerScrollingMenu.setTouchable(touchable);
    touchOverlay.setTouchable(touchable);
}
