#include <gui/common/ScrollingWheels/ClickableContainer.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/hal/HAL.hpp>

namespace touchgfx
{
ClickableContainer::ClickableContainer()
    : Container(),
      accelDirection(GestureEvent::SWIPE_HORIZONTAL),
      pressedDrawable(0),
      lastDraggableChild(0),
      scrolledXDistance(0),
      scrolledYDistance(0),
      scrollThreshold(5),
      pressedX(0),
      pressedY(0),
      isPressed(false),
      isScrolling(false),
      draggableX(false),
      draggableY(false),
      fingerAdjustmentX(0),
      fingerAdjustmentY(0),
      hasIssuedCancelEvent(false)
{
    setTouchable(true);
}

void ClickableContainer::handleClickEvent(const ClickEvent& evt)
{
    if (evt.getType() == ClickEvent::PRESSED)
    {
        const int fingerSize = HAL::getInstance()->getFingerSize();
        fingerAdjustmentX = 0;
        fingerAdjustmentY = 0;

        const int minimumDistance = 3;
        if ((fingerSize - 1) >= minimumDistance)
        {
            pressedDrawable = 0;

            const int maximumSquares = 3;
            const int numberOfSquares = MIN(maximumSquares, (fingerSize - 1) / minimumDistance);
            uint32_t bestDistance = 0xFFFFFFFF;
            Drawable* last = 0;

            Rect me(0, 0, getWidth(), getHeight());
            Rect meAbs = me;
            translateRectToAbsolute(meAbs);

            for (int squareNumber = 1; squareNumber <= numberOfSquares; squareNumber++)
            {
                int distance = ((squareNumber * fingerSize) / numberOfSquares);
                const int samplePoints[10][2] = { { 0, 0 }, { -1, -1 }, { 0, -1 }, { 1, -1 }, { -1, 0 }, { 0, 0 }, { 1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 } };

                for (int sampleIndex = squareNumber - 1; sampleIndex < 10; sampleIndex += 2)
                {
                    Drawable* d = 0;
                    int16_t deltaX = samplePoints[sampleIndex][0] * distance;
                    int16_t deltaY = samplePoints[sampleIndex][1] * distance;
                    if (me.intersect(evt.getX() + deltaX, evt.getY() + deltaY))
                    {
                        Container::getLastChild(evt.getX() + deltaX, evt.getY() + deltaY, &d);
                        if (d && d != last && d != this)
                        {
                            Rect absRect = d->getAbsoluteRect();
                            int x = meAbs.x + evt.getX() - (absRect.x + (absRect.width / 2));
                            int y = meAbs.y + evt.getY() - (absRect.y + (absRect.height / 2));
                            uint32_t dist = x * x + y * y;
                            if (dist < bestDistance)
                            {
                                last = d;
                                bestDistance = dist;
                                pressedDrawable = d;
                                fingerAdjustmentX = deltaX;
                                fingerAdjustmentY = deltaY;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            Container::getLastChild(evt.getX(), evt.getY(), &pressedDrawable);
        }

        if (pressedDrawable == this)
        {
            pressedDrawable = 0;
        }

        if (pressedDrawable)
        {
            hasIssuedCancelEvent = false;
            pressedX = evt.getX();
            pressedY = evt.getY();
            Rect r = pressedDrawable->getAbsoluteRect();
            ClickEvent relative(evt.getType(), evt.getX() + rect.x + fingerAdjustmentX - r.x, evt.getY() + rect.y + fingerAdjustmentY - r.y);
            pressedDrawable->handleClickEvent(relative);
            lastDraggableChild = pressedDrawable;
        }
    }
    else if (evt.getType() == ClickEvent::CANCEL)
    {
        return;
    }
    else // if (evt.getType() == ClickEvent::RELEASED)
    {
        if (pressedDrawable)
        {
            Rect r = pressedDrawable->getAbsoluteRect();
            ClickEvent relative(evt.getType(), evt.getX() + rect.x + fingerAdjustmentX - r.x, evt.getY() + rect.y + fingerAdjustmentY - r.y);
            pressedDrawable->handleClickEvent(relative);
        }

        pressedDrawable = 0;
        lastDraggableChild = 0;
        isPressed = false;
    }
}

void ClickableContainer::handleDragEvent(const DragEvent& evt)
{
    DragEvent actualDrag = evt;

    if ((pressedDrawable != 0) && (pressedDrawable != this))
    {
        // Also send this drag event to the appropriate child widget
        // but only in the direction(s) where allowed.
        if (draggableX || draggableY)
        {
            Rect r = pressedDrawable->getAbsoluteRect();
            DragEvent relative(DragEvent::DRAGGED,
                               evt.getOldX() + rect.x + fingerAdjustmentX - r.x,
                               evt.getOldY() + rect.y + fingerAdjustmentY - r.y,
                               evt.getNewX() + rect.x + fingerAdjustmentX - r.x,
                               evt.getNewY() + rect.y + fingerAdjustmentY - r.y);

            pressedDrawable->handleDragEvent(relative);
        }
    }

    // Send cancel events to child in focus
    if (pressedDrawable && !hasIssuedCancelEvent)
    {
        ClickEvent ce(ClickEvent::CANCEL, 0, 0);
        pressedDrawable->handleClickEvent(ce);
        hasIssuedCancelEvent = true;
    }
}

void ClickableContainer::handleGestureEvent(const GestureEvent& evt)
{
    if ((!draggableX && (evt.getType() == GestureEvent::SWIPE_HORIZONTAL)) ||
            (!draggableY && (evt.getType() == GestureEvent::SWIPE_VERTICAL)))
    {
        if (pressedDrawable && !hasIssuedCancelEvent)
        {
            ClickEvent ce(ClickEvent::CANCEL, 0, 0);
            pressedDrawable->handleClickEvent(ce);
            hasIssuedCancelEvent = true;
        }
    }
}
} // namespace touchgfx
