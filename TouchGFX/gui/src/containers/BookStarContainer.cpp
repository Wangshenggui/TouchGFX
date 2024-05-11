#include <gui/containers/BookStarContainer.hpp>
#include <stdio.h>

BookStarContainer::BookStarContainer()
{
    textArea1.setWideTextAction(WIDE_TEXT_CHARWRAP);
}

void BookStarContainer::initialize()
{
    BookStarContainerBase::initialize();
}


void BookStarContainer::TextAreaAddStr(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, textArea1Buffer, len);
    textArea1.invalidate();
}

