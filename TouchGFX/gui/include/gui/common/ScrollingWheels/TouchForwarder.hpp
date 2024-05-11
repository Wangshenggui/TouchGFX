#ifndef TOUCHFORWARDER_HPP
#define TOUCHFORWARDER_HPP

#include <touchgfx/widgets/TouchArea.hpp>
using namespace touchgfx;

class TouchForwarder : public TouchArea
{
public:
    TouchForwarder(Drawable& d1, Drawable& d2)
        : first(d1), second(d2), isDown(false), draggable(true)
    {
        setTouchable(true);
    }

    virtual void handleClickEvent(const ClickEvent& evt);
    virtual void handleDragEvent(const DragEvent& evt);
    virtual void handleGestureEvent(const GestureEvent& evt);

    void setDragable(const bool d)
    {
        draggable = d;
    }
    bool touchIsDown() const
    {
        return isDown;
    }
private:
    Drawable& first;
    Drawable& second;
    bool isDown;
    bool draggable;
};

#endif
