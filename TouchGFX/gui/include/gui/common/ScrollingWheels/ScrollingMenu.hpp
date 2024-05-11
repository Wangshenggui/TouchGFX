#ifndef SCROLLINGMENU_HPP
#define SCROLLINGMENU_HPP

#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include <touchgfx/containers/Container.hpp>
#include <gui/common/ScrollingWheels/ClickableContainer.hpp>
#include <gui/common/ScrollingWheels/SparseContainerList.hpp>
#include <touchgfx/Callback.hpp>

using namespace touchgfx;

class ScrollingMenu : public ClickableContainer
{
public:

    /**
     * @fn ScrollingMenu::ScrollingMenu();
     *
     * @brief Default constructor.
     */
    ScrollingMenu();

    /**
     * @fn void ScrollingMenu::setup(bool isHorizontal_, bool isCircular_, int16_t widgetWidth, int16_t widgetHeight, int16_t selectedItemOffset_, int16_t containerSize, int16_t containerSpacing, int16_t numItems_, int16_t numContainers, Container* containers, GenericCallback<int, int>& updateContainerCallback);
     *
     * @brief Setups the widget.
     *
     *        Setups the widget. Numerous parameters control the position of the widget, the
     *        two scroll lists inside and the values in them.
     *
     * @param isHorizontal_                true if the containers are arranged side by side,
     *                                     false if the containers are above and below each
     *                                     other.
     * @param isCircular_                  true for circular (infinite) scrolling.
     * @param widgetWidth                  Width of the entire widget.
     * @param widgetHeight                 Height of the entire widget.
     * @param selectedItemOffset_          The selected item's y coordinate.
     * @param containerSize                Height of one item in the list.
     * @param containerSpacing             The container spacing. If the number is negative it
     *                                     is the container overlap.
     * @param numItems_                    Number of string values.
     * @param numContainers                Number of item containers (only max the number of
     *                                     simultaneously visible containers).
     * @param [in] containers              The numItemContainers's item containers. These will
     *                                     be positioned and made visible during an update.
     * @param [in] updateContainerCallback Function to call when a container needs new content.
     */
    void setup(bool isHorizontal_, bool isCircular_,
               int16_t widgetWidth, int16_t widgetHeight, int16_t selectedItemOffset_,
               int16_t containerSize, int16_t containerSpacing,
               int16_t numItems_, int16_t numContainers, GenericCallback<int, Container**>& getElementCallback,
               GenericCallback<int, int>& updateContainerCallback);

    /**
     * @fn void ScrollingMenu::setWindowSize(int16_t items)
     *
     * @brief Sets window size.
     *
     *        Sets window size. This is the number of items that should always be visible. The
     *        default value is 1.
     *
     * @param items The items.
     *
     * @note This only applies to non-circular lists.
     */
    void setWindowSize(int16_t items)
    {
        windowSize = items;
    }

    /**
     * @fn void ScrollingMenu::setEasingEquation(EasingEquation equation, uint16_t steps = 50)
     *
     * @brief Sets easing equation.
     *
     *        Sets easing equation and number of steps when changing the selected item, eg. via
     *        swipe.
     *
     * @param equation The equation.
     * @param steps    The steps.
     */
    void setEasingEquation(EasingEquation equation, uint16_t steps = 50)
    {
        easingEquation = equation;
        easingSteps = steps;
    }

    /**
     * @fn void ScrollingMenu::setSwipeAcceleration(uint16_t acceleration)
     *
     * @brief Sets swipe acceleration.
     *
     *        Sets swipe acceleration (times 10).
     *
     * @param acceleration The acceleration times 10, so "60" means "6" and "75" means "7.5".
     */
    void setSwipeAcceleration(uint16_t acceleration)
    {
        swipeAcceleration = acceleration;
    }

    /**
     * @fn uint16_t ScrollingMenu::getSwipeAcceleration() const
     *
     * @brief Gets swipe acceleration.
     *
     *        Gets swipe acceleration (times 10).
     *
     * @return The swipe acceleration.
     *
     * @see setSwipeAcceleration
     */
    uint16_t getSwipeAcceleration() const
    {
        return swipeAcceleration;
    }

    /**
     * @fn void ScrollingMenu::setDragAcceleration(uint16_t acceleration)
     *
     * @brief Sets drag acceleration.
     *
     *        Sets drag acceleration times 10, so "10" means "1", "15" means "1.5".
     *
     * @param acceleration The drag acceleration. 10 makes the containers follow the finger,
     *                     higher values makes the containers move faster.
     */
    void setDragAcceleration(uint16_t acceleration)
    {
        dragAcceleration = acceleration;
    }

    /**
     * @fn uint16_t ScrollingMenu::getDragAcceleration() const
     *
     * @brief Gets drag acceleration.
     *
     *        Gets drag acceleration (times 10).
     *
     * @return The drag acceleration.
     *
     * @see setDragAcceleration
     */
    uint16_t getDragAcceleration() const
    {
        return dragAcceleration;
    }

    /**
     * @fn void ScrollingMenu::setMaxSwipeItems(uint16_t maxItems)
     *
     * @brief Sets maximum swipe items.
     *
     *        Sets maximum swipe items. Often useful when there are four visible items on the
     *        screen and a swipe action should at most swipe the next/previous four items into
     *        view.
     *
     * @param maxItems The maximum items, 0 means "no limit".
     */
    void setMaxSwipeItems(uint16_t maxItems)
    {
        maxSwipeItems = maxItems;
    }

    /**
     * @fn uint16_t ScrollingMenu::getMaxSwipeItems() const
     *
     * @brief Gets maximum swipe items.
     *
     *        Gets maximum swipe items.
     *
     * @return The maximum swipe items.
     *
     * @see setMaxSwipeItems
     */
    uint16_t getMaxSwipeItems() const
    {
        return maxSwipeItems;
    }

    /**
     * @fn void ScrollingMenu::setSnapping(bool snap)
     *
     * @brief Sets snapping.
     *
     *        Set snapping. If snapping is false, the items can flow freely. If snapping is
     *        true, the items will snap into place so an item is always in the "selected" spot.
     *
     * @param snap true to snap.
     */
    void setSnapping(bool snap)
    {
        snapping = snap;
    }

    /**
     * @fn bool ScrollingMenu::getSnapping() const
     *
     * @brief Gets the current snap stetting.
     *
     *        Gets the current snap stetting.
     *
     * @return true if snapping is set, false otherwise.
     */
    bool getSnapping() const
    {
        return snapping;
    }

    /**
     * @fn void ScrollingMenu::setSelectedItem(int index);
     *
     * @brief Sets selected item.
     *
     *        Sets selected item. This is done as an animation of the items.
     *
     * @param index Zero-based index of the item to select.
     */
    void setSelectedItem(int index);

    /**
     * @fn int ScrollingMenu::getSelectedItem() const;
     *
     * @brief Gets selected item.
     *
     *        Gets selected item. If an animation is in progress, the item that is being
     *        scrolled to is returned.
     *
     * @return The selected item.
     */
    int getSelectedItem() const;

    /**
     * @fn void ScrollingMenu::itemChanged(int index);
     *
     * @brief Item changed.
     *
     *        Inform that an item has change and force all containers with the given item index
     *        to be updated via the callback provided.
     *
     * @param index Zero-based index of the changed item.
     */
    void itemChanged(int index);

    /**
     * @fn void ScrollingMenu::setItemSelectedCallback(GenericCallback<int>& selectCallback, GenericCallback<int, int>& updateCallback);
     *
     * @brief Set functions to call when an item is clicked.
     *
     *        Set functions to call when an item is clicked. First the selectCallback is called
     *        with the item index as parameter. Next the updateCallback is called once for each
     *        occurrence of the item in a container, allowing the visual update of each of
     *        these containers.
     *
     * @param [in] selectCallback The callback called when an item is selected.
     * @param [in] updateCallback The callback called for each container with this item.
     *
     * @see setItemUpdateCallback
     */
    void setItemUpdatedCallback(GenericCallback<int, int>& updateCallback);

    void setAnimationEndedCallback(GenericCallback<int>& endedCallback);

    /**
     * @fn bool ScrollingMenu::isAnimating() const;
     *
     * @brief Query if this object is animating.
     *
     *        Query if this object is animating. This can be good to know if getSelectedItem()
     *        is called, as the result might not be as expected if isAnimating() returns true.
     *
     * @return true if animating, false if not.
     */
    bool isAnimating() const;

    int16_t getItemIndex(int16_t containerIndex) // TODO
    {
        return scList.getItemIndex(containerIndex);
    }

    virtual void handleClickEvent(const ClickEvent& evt);
    virtual void handleDragEvent(const DragEvent& evt);
    virtual void handleGestureEvent(const GestureEvent& evt);

private:
    int32_t getNormalizedOffset(int32_t offset) const;
    void setVirtualOffset(int32_t newOffset);
    int32_t getNearestAlignedOffset(int32_t offset) const;
    int32_t keepOffsetInsideLimits(int32_t newOffset, int16_t overShoot) const;

    enum AnimationState
    {
        NO_ANIMATION,      ///< No animation
        ANIMATING_GESTURE, ///< Animating a gesture
        ANIMATING_DRAG     ///< Animating a click+drag
    };

    bool isHorizontal;
    bool isCircular;
    bool snapping;
    int itemSize;
    int windowSize;
    int selectedItemOffset;
    uint16_t swipeAcceleration;
    uint16_t dragAcceleration;
    uint16_t maxSwipeItems;
    EasingEquation easingEquation;
    uint16_t easingSteps;
    SparseContainerList scList;

    GenericCallback<int, int>* itemUpdatedCallback;
    GenericCallback<int>* animationEndedCallback;

    AnimationState currentAnimationState;
    int gestureStep;
    int gestureStepsTotal;
    int32_t gestureStart;
    int32_t gestureDelta;

    virtual void handleTickEvent();

    int16_t xClick;
    int16_t yClick;
    int32_t initialSwipeOffset;
    int32_t virtualOffset;

    void animateTo(int32_t newPosition);
};

#endif // SCROLLINGMENU_HPP
