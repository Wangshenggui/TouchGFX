#ifndef PARTICLESSCROLLINGWHEELSMALL_HPP
#define PARTICLESSCROLLINGWHEELSMALL_HPP

#include <touchgfx/containers/Container.hpp>
#include <gui/common/ScrollingWheels/ScrollingWheel.hpp>
#include <gui/common/ScrollingWheels/TextAreaWithOneWildcardContainer.hpp>

using namespace touchgfx;

class ParticlesScrollingWheel : public ScrollingWheel
{
public:
    ParticlesScrollingWheel();

    static const int NUMBER_OF_ITEMS = 10;
    SparseContainerItems<TextAreaWithOneWildcardContainer, NUMBER_OF_ITEMS> backgroundScrollingMenuItems;
    SparseContainerItems<TextAreaWithOneWildcardContainer, NUMBER_OF_ITEMS> centerScrollingMenuItems;

    virtual void initializeBackgroundScrollingMenuItem(int containerIndex, int itemIndex);
    virtual void initializeCenterScrollingMenuItem(int containerIndex, int itemIndex);

    int getSelectedValue();
    int setSelectedValue(int value);

    uint8_t getAlpha();
    void setAlpha(uint8_t alpha);

private:
    static const int VALUE_INTERVAL = 25;

    int indexToValue(int index);
    int valueToIndex(int value);
};

#endif // PARTICLESSCROLLINGWHEELSMALL_HPP
