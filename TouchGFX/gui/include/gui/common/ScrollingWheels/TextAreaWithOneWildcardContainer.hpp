#ifndef TEXTAREAWITHONEWILDCARDCONTAINER_HPP
#define TEXTAREAWITHONEWILDCARDCONTAINER_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

using namespace touchgfx;

// Class that wraps a TextAreaWithOneWildcard in a container.
// Used for inserting into the SparseContainerList.
class TextAreaWithOneWildcardContainer : public Container
{
public:

    TextAreaWithOneWildcardContainer()
    {
        text.setWildcard(textBuffer);
        add(text);
        setWidth(216);
        setHeight(50);
    }

    virtual void setWidth(int16_t width)
    {
        Container::setWidth(width);
        text.setWidth(width);
        invalidate();
    }
    virtual void setHeight(int16_t height)
    {
        Container::setHeight(height);
        text.setHeight(height);
        invalidate();
    }

    void setTypedText(TypedText t)
    {
        text.setTypedText(t);
        invalidate();
    }
    void setColor(colortype c)
    {
        text.setColor(c);
        invalidate();
    }

    TextAreaWithOneWildcard text;
    static const uint16_t TEXT_SIZE = 6;
    touchgfx::Unicode::UnicodeChar textBuffer[TEXT_SIZE];
};

#endif // TEXTAREAWITHONEWILDCARDCONTAINER_HPP
