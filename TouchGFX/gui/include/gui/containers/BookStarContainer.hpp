#ifndef BOOKSTARCONTAINER_HPP
#define BOOKSTARCONTAINER_HPP

#include <gui_generated/containers/BookStarContainerBase.hpp>

class BookStarContainer : public BookStarContainerBase
{
public:
    BookStarContainer();
    virtual ~BookStarContainer() {}

    virtual void initialize();


    virtual void TextAreaAddStr(uint8_t* str, uint32_t len);
protected:
};

#endif // BOOKSTARCONTAINER_HPP
