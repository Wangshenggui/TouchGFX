#include <gui/common/ScrollingWheels/TouchForwarder.hpp>

void TouchForwarder::handleClickEvent(const ClickEvent& evt)
{
    isDown = (evt.getType() == ClickEvent::PRESSED);
    first.handleClickEvent(evt);
    second.handleClickEvent(evt);
}

void TouchForwarder::handleDragEvent(const DragEvent& evt)
{
    if (draggable)
    {
        first.handleDragEvent(evt);
        second.handleDragEvent(evt);
    }
}

void TouchForwarder::handleGestureEvent(const GestureEvent& evt)
{
    if (draggable)
    {
        first.handleGestureEvent(evt);
        second.handleGestureEvent(evt);
    }
}
