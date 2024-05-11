#include <gui/common/ScrollingWheels/ScrollingMenu.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <touchgfx/Utils.hpp>
#include <math.h>

ScrollingMenu::ScrollingMenu() :
    windowSize(1),
    swipeAcceleration(60),
    dragAcceleration(10),
    maxSwipeItems(0),
    easingEquation(&EasingEquations::backEaseOut),
    easingSteps(50),
    itemUpdatedCallback(0),
    animationEndedCallback(0)
{
}

void ScrollingMenu::setup(bool isHorizontal_, bool isCircular_,
                          int16_t widgetWidth, int16_t widgetHeight, int16_t selectedItemOffset_, int16_t containerSize, int16_t containerSpacing,
                          int16_t numItems_, int16_t numContainers, GenericCallback<int, Container**>& getElementCallback, GenericCallback<int, int>& updateContainerCallback)
{
    snapping = true;
    isHorizontal = isHorizontal_;
    isCircular = isCircular_;
    itemSize = containerSize + containerSpacing;
    selectedItemOffset = selectedItemOffset_;
    easingEquation = easingEquation;
    currentAnimationState = NO_ANIMATION;

    setWidth(widgetWidth);
    setHeight(widgetHeight);

    setTouchable(true);

    scList.setXY(0, 0);
    ClickableContainer::removeAll();
    ClickableContainer::add(scList);

    allowVerticalDrag(isHorizontal);
    allowHorizontalDrag(!isHorizontal);

    scList.setup(isHorizontal, isCircular, widgetWidth, widgetHeight, selectedItemOffset, containerSize, containerSpacing, numItems_, numContainers, getElementCallback, updateContainerCallback);

    setVirtualOffset(0);
}

void ScrollingMenu::setSelectedItem(int index)
{
    virtualOffset = getNormalizedOffset(virtualOffset);
    int32_t newOffset = -index * itemSize;
    if (isCircular)
    {
        int32_t allItemsSize = scList.getNumItems() * itemSize;
        // Check if it is closer to scroll backwards
        int32_t otherOffset = newOffset + allItemsSize;
        if (touchgfx::abs<int32_t>(otherOffset - virtualOffset) < touchgfx::abs<int32_t>(newOffset - virtualOffset))
        {
            newOffset = otherOffset;
        }
        otherOffset = newOffset - allItemsSize;
        if (touchgfx::abs<int32_t>(otherOffset - virtualOffset) < touchgfx::abs<int32_t>(newOffset - virtualOffset))
        {
            newOffset = otherOffset;
        }
    }
    animateTo(newOffset);
}

int32_t ScrollingMenu::getNormalizedOffset(int32_t offset) const
{
    offset %= (scList.getNumItems() * itemSize);
    if (offset > 0)
    {
        offset -= scList.getNumItems() * itemSize;
    }
    return offset;
}

void ScrollingMenu::setVirtualOffset(int32_t newOffset)
{
    virtualOffset = newOffset;
    scList.setVirtualOffset(virtualOffset);
    scList.invalidate();
}

int ScrollingMenu::getSelectedItem() const
{
    if (scList.getNumItems() == 0)
    {
        return 0;
    }
    if (currentAnimationState == ANIMATING_GESTURE)
    {
        // Scroll in progress, get the destination value
        return (-getNormalizedOffset(gestureStart + gestureDelta)) / itemSize;
    }
    int index = ((-getNormalizedOffset(virtualOffset)) + itemSize / 2 - 1) / itemSize;
    return index % scList.getNumItems();
}

void ScrollingMenu::itemChanged(int index)
{
    if (itemUpdatedCallback && itemUpdatedCallback->isValid())
    {
        int16_t containerIndex = -1;
        do
        {
            containerIndex = scList.getContainerIndex(index, containerIndex);
            if (containerIndex >= 0)
            {
                itemUpdatedCallback->execute(containerIndex, index);
            }
        } while (containerIndex >= 0);
    }
}

void ScrollingMenu::setItemUpdatedCallback(GenericCallback<int, int>& updateCallback)
{
    itemUpdatedCallback = &updateCallback;
}

void ScrollingMenu::setAnimationEndedCallback(GenericCallback<int>& callback)
{
    animationEndedCallback = &callback;
}

bool ScrollingMenu::isAnimating() const
{
    return currentAnimationState != NO_ANIMATION;
}

int32_t ScrollingMenu::getNearestAlignedOffset(int32_t offset) const
{
    if (isCircular)
    {
        return snapping ? (offset < 0) ? (((offset - (itemSize / 2)) / itemSize) * itemSize) : ((offset + (itemSize / 2)) / itemSize) * itemSize : offset;
    }
    else
    {
        // Only allow negative and 0 values
        offset = MIN(offset, 0);
        offset = MAX(offset, -itemSize * (scList.getNumItems() - 1));
        offset = keepOffsetInsideLimits(offset, 0);
        return snapping ? ((offset - (itemSize / 2)) / itemSize) * itemSize : offset;
    }
}

int32_t ScrollingMenu::keepOffsetInsideLimits(int32_t newOffset, int16_t overShoot) const
{
    if (!isCircular)
    {
        newOffset = MIN(newOffset, overShoot);
        int maxOffToTheLeft = windowSize < scList.getNumItems() ? scList.getNumItems() - windowSize : 0;
        newOffset = MAX(newOffset, -(itemSize * maxOffToTheLeft) - overShoot);
    }
    return newOffset;
}

void ScrollingMenu::handleClickEvent(const ClickEvent& evt)
{
    ClickableContainer::handleClickEvent(evt);
    if (evt.getType() == ClickEvent::PRESSED)
    {
        xClick = evt.getX();
        yClick = evt.getY();
        initialSwipeOffset = virtualOffset;
    }
    else if (evt.getType() == ClickEvent::RELEASED)
    {
        if (currentAnimationState == ANIMATING_DRAG)
        {
            // click + drag + release. Find best Y to scroll to
            animateTo(virtualOffset);
        }
    }
}

void ScrollingMenu::handleDragEvent(const DragEvent& evt)
{
    ClickableContainer::handleDragEvent(evt);
    currentAnimationState = ANIMATING_DRAG;
    int32_t newOffset = virtualOffset + (isHorizontal ? evt.getDeltaX() : evt.getDeltaY()) * dragAcceleration / 10;
    newOffset = keepOffsetInsideLimits(newOffset, itemSize / 3);
    setVirtualOffset(newOffset);
}

void ScrollingMenu::handleGestureEvent(const GestureEvent& evt)
{
    ClickableContainer::handleGestureEvent(evt);
    if (evt.getType() == (isHorizontal ? GestureEvent::SWIPE_HORIZONTAL : GestureEvent::SWIPE_VERTICAL))
    {
        int32_t newOffset = virtualOffset + evt.getVelocity() * swipeAcceleration / 10;
        if (maxSwipeItems > 0)
        {
            newOffset = MIN(newOffset, initialSwipeOffset + maxSwipeItems * itemSize);
            newOffset = MAX(newOffset, initialSwipeOffset - maxSwipeItems * itemSize);
        }
        newOffset = keepOffsetInsideLimits(newOffset, 0);
        animateTo(newOffset);
    }
}

void ScrollingMenu::handleTickEvent()
{
    if (currentAnimationState == ANIMATING_GESTURE)
    {
        int delta = easingEquation(gestureStep, 0, gestureDelta, gestureStepsTotal);
        setVirtualOffset(gestureStart + delta);
        gestureStep++;
        if (gestureStep > gestureStepsTotal)
        {
            currentAnimationState = NO_ANIMATION;
            Application::getInstance()->unregisterTimerWidget(this);
            virtualOffset = getNormalizedOffset(virtualOffset);

            if (animationEndedCallback && animationEndedCallback->isValid())
            {
                animationEndedCallback->execute(getSelectedItem());
            }
        }
    }
}

void ScrollingMenu::animateTo(int32_t newPosition)
{
    if (easingSteps < 1)
    {
        setVirtualOffset(newPosition);
    }
    else
    {
        if (currentAnimationState != ANIMATING_GESTURE)
        {
            Application::getInstance()->registerTimerWidget(this);
        }
        gestureDelta = getNearestAlignedOffset(newPosition) - virtualOffset;
        currentAnimationState = ANIMATING_GESTURE;
        gestureStep = 0;
        gestureStepsTotal = MIN(easingSteps, touchgfx::abs<int32_t>(gestureDelta / 2));
        gestureStart = virtualOffset;
    }
}
