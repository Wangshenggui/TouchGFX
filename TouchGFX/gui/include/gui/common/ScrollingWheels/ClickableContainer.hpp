#ifndef CLICKABLECONTAINER_HPP
#define CLICKABLECONTAINER_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/Application.hpp>

namespace touchgfx
{
/**
 * @class ClickableContainer ClickableContainer.hpp touchgfx/containers/ClickableContainer.hpp
 *
 * @brief A ClickableContainer is a container that allows its contents to be scrolled.
 *
 *        A ClickableContainer is a container that allows its mouse events to be intercepted
 *        and also passed on the the children.
 *
 * @note The ClickableContainer will consume all DragEvents in the area covered by the container.
 * @note The fingersize set in HAL is handled when clicking the container.
 *
 * @see Container
 */
class ClickableContainer : public Container
{
public:

    /**
     * @fn ClickableContainer::ClickableContainer();
     *
     * @brief Default constructor.
     *
     *        Default constructor.
     */
    ClickableContainer();

    /**
     * @fn virtual ClickableContainer::~ClickableContainer()
     *
     * @brief Destructor.
     *
     *        Destructor.
     */
    virtual ~ClickableContainer() { }

    /**
     * @fn void ClickableContainer::allowHorizontalDrag(bool enable)
     *
     * @brief Enables horizontal scrolling.
     *
     *        Enables horizontal scrolling to be passed to the children. By default, scrolling
     *        in either direction is enabled. This function can be used to explicitly
     *        (dis)allow scrolling in the horizontal direction.
     *
     * @param enable If true (default), horizontal scrolling is enabled. If false, scrolling is
     *               disabled.
     */
    void allowHorizontalDrag(bool enable)
    {
        draggableX = enable;
    }

    /**
     * @fn void ClickableContainer::allowVerticalDrag(bool enable)
     *
     * @brief Enables the vertical scroll.
     *
     *        Enables the vertical scroll to be passed to the children. By default, scrolling
     *        in either direction is enabled. This function can be used to explicitly
     *        (dis)allow scrolling in the vertical direction.
     *
     * @param enable If true (default), vertical scrolling is enabled. If false, scrolling is
     *               disabled.
     */
    void allowVerticalDrag(bool enable)
    {
        draggableY = enable;
    }

    /**
     * @fn virtual void ClickableContainer::getLastChild(int16_t x, int16_t y, Drawable** last)
     *
     * @brief Gets the last child in the container.
     *
     *        Gets the last child in the container. The ClickableContainer needs to intercept
     *        click events, since the scrollbars are displayed upon reception of a PRESSED
     *        ClickEvent. The ClickableContainer will automatically re-delegate the event to
     *        the appropriate child.
     *
     * @param x          The x coordinate of the (click) event.
     * @param y          The y coordinate of the (click) event.
     * @param [out] last The last child intersecting x,y. ClickableContainer intercepts these, so
     *                   returns it self.
     */
    virtual void getLastChild(int16_t x, int16_t y, Drawable** last)
    {
        if (isVisible())
        {
            if (isTouchable())
            {
                *last = this;
            }
            else
            {
                Container::getLastChild(x, y, last);
            }
        }
    }

    /**
    * @fn virtual void ClickableContainer::handleClickEvent(const ClickEvent& evt);
    *
    * @brief Handle the click event.
    *
    *        Handle the click event. Get ready for scrolling, display scrollbars, etc. Send
    *        the click to appropriate child widget.
    *
    * @param evt The ClickEvent.
    */
    virtual void handleClickEvent(const ClickEvent& evt);

    /**
    * @fn virtual void ClickableContainer::handleDragEvent(const DragEvent& evt);
    *
    * @brief Handle the drag event.
    *
    *        Handle the drag event. Initiate a scrolling of the container. Update scrollbars.
    *
    * @param evt The DragEvent.
    */
    virtual void handleDragEvent(const DragEvent& evt);

    /**
     * @fn virtual void ClickableContainer::handleGestureEvent(const GestureEvent& evt);
     *
     * @brief Gestures generate a scroll animation so these are intercepted in the same manner as
     *        drag events.
     *
     *        Gestures generate a scroll animation so these are intercepted in the same manner
     *        as drag events.
     *
     * @param evt The GestureEvent.
     */
    virtual void handleGestureEvent(const GestureEvent& evt);

protected:
    GestureEvent::GestureEventType accelDirection; ///< The current direction (horizontal or vertical) of scroll

    Drawable* pressedDrawable;    ///< The drawable child of this container which received the last ClickEvent::PRESSED notification. When scrolling, send this drawable a CANCEL event if the new x/y coords no longer matches this drawable.
    Drawable* lastDraggableChild; ///< The drawable child of this container which should receive drag events. Note that only drag events in directions which cannot be scrolled by this ClickableContainer will be forwarded to children.

    int16_t scrolledXDistance; ///< The scrolled horizontal distance
    int16_t scrolledYDistance; ///< The scrolled vertical distance
    int16_t scrollThreshold;   ///< The threshold which the first drag event received must exceed before scrolling. Default is 5.

    int16_t pressedX; ///< The x coordinate where the last ClickEvent::PRESSED was received.
    int16_t pressedY; ///< The y coordinate where the last ClickEvent::PRESSED was received.

    bool isPressed;   ///< Is the container currently pressed (maybe show scrollbars)
    bool isScrolling; ///< Is the container scrolling (i.e. has overcome the initial larger drag that is required to initiate a scroll).

    bool draggableX; ///< Is the container draggable in the horizontal direction.
    bool draggableY; ///< Is the container draggable in the vertical direction.

    int16_t fingerAdjustmentX; ///< How much should the finger be adjusted horizontally
    int16_t fingerAdjustmentY; ///< and how much vertically

    bool hasIssuedCancelEvent; ///< true if the pressed drawable has received cancel event
};
} // namespace touchgfx

#endif // CLICKABLECONTAINER_HPP
