#include <gui/common/ScrollingWheels/ParticlesScrollingWheel.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>

ParticlesScrollingWheel::ParticlesScrollingWheel() : ScrollingWheel()

{
    background.setBitmap(Bitmap(BITMAP_PARTICLE10_ID));

    int textElementAreaXOffset = 20;
    int textElementAreaYOffset = 8;
    int textElementAreaWidth = background.getWidth() - (2 * textElementAreaXOffset);
    int textElementAreaHeight = background.getHeight() - (2 * textElementAreaYOffset);
    int textElementWidth = textElementAreaWidth;
    int textElementHeight = 40;

    backgroundScrollingMenu.setXY(background.getX() + textElementAreaXOffset, background.getY() + 8);
    backgroundScrollingMenu.setup(
        false,                  //horizontal
        false,                  //isCircular
        textElementAreaWidth,   //width
        textElementAreaHeight,  //height
        40,                     //selectedItemOffset
        textElementHeight,      //containerSize
        0,                      //containerSpacing
        NUMBER_OF_ITEMS,        //numItems
        5,                      //numContainers
        backgroundScrollingMenuItems.getElementCallback,
        initializeBackgroundScrollingMenuItemCallback);
    backgroundScrollingMenu.setSwipeAcceleration(60);

    shadowOverlay.setXY(0, 0);
    shadowOverlay.setBitmap(Bitmap(BITMAP_PARTICLE10_ID));

    centerScrollingMenu.setXY(backgroundScrollingMenu.getX(), shadowOverlay.getY() + 41);
    centerScrollingMenu.setup(
        false,                  //horizontal
        false,                  //isCircular
        textElementAreaWidth,   //width
        44,                     //height
        2,                      //selectedItemOffset
        textElementHeight,      //containerSize
        0,                      //containerSpacing
        NUMBER_OF_ITEMS,        //numItems
        5,                      //numContainers
        centerScrollingMenuItems.getElementCallback,
        initializeCenterScrollingMenuItemCallback);
    centerScrollingMenu.setSwipeAcceleration(60);

    setup();

    for (int i = 0; i < NUMBER_OF_ITEMS; i++)
    {
        backgroundScrollingMenuItems.element[i].setWidth(textElementWidth);
        backgroundScrollingMenuItems.element[i].setHeight(textElementHeight);
        backgroundScrollingMenuItems.element[i].setColor(Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
        backgroundScrollingMenuItems.element[i].setTypedText(TypedText(BITMAP_PARTICLE10_ID));

        centerScrollingMenuItems.element[i].setWidth(textElementWidth);
        centerScrollingMenuItems.element[i].setHeight(textElementHeight);
        centerScrollingMenuItems.element[i].setColor(Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
        centerScrollingMenuItems.element[i].setTypedText(TypedText(BITMAP_PARTICLE10_ID));
    }
}

void ParticlesScrollingWheel::initializeBackgroundScrollingMenuItem(int containerIndex, int itemIndex)
{
    Unicode::snprintf(backgroundScrollingMenuItems.element[containerIndex].textBuffer,
                      backgroundScrollingMenuItems.element[containerIndex].TEXT_SIZE, "%i", indexToValue(itemIndex));
}

void ParticlesScrollingWheel::initializeCenterScrollingMenuItem(int containerIndex, int itemIndex)
{
    Unicode::snprintf(centerScrollingMenuItems.element[containerIndex].textBuffer,
                      centerScrollingMenuItems.element[containerIndex].TEXT_SIZE, "%i", indexToValue(itemIndex));
}

int ParticlesScrollingWheel::indexToValue(int index)
{
    return (index + 1) * VALUE_INTERVAL;
}

int ParticlesScrollingWheel::valueToIndex(int value)
{
    return MAX(0, (value / VALUE_INTERVAL) - 1);
}

int ParticlesScrollingWheel::getSelectedValue()
{
    return indexToValue(centerScrollingMenu.getSelectedItem());
}

int ParticlesScrollingWheel::setSelectedValue(int value)
{
    backgroundScrollingMenu.setSelectedItem(valueToIndex(value));
    centerScrollingMenu.setSelectedItem(valueToIndex(value));

    // Return the actual value that has been set. Only
    // values as multiple of VALUE_INTERVAL is allowed
    return indexToValue(valueToIndex(value));
}

uint8_t ParticlesScrollingWheel::getAlpha()
{
    return background.getAlpha();
}

void ParticlesScrollingWheel::setAlpha(uint8_t alpha)
{
    background.setAlpha(alpha);
    shadowOverlay.setAlpha(alpha);

    for (int i = 0; i < NUMBER_OF_ITEMS; i++)
    {
        backgroundScrollingMenuItems.element[i].text.setAlpha(alpha);
        centerScrollingMenuItems.element[i].text.setAlpha(alpha);
    }
}
