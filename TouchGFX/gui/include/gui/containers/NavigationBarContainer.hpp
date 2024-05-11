#ifndef NAVIGATIONBARCONTAINER_HPP
#define NAVIGATIONBARCONTAINER_HPP

#include <gui_generated/containers/NavigationBarContainerBase.hpp>


class NavigationBarContainer : public NavigationBarContainerBase
{
public:
    NavigationBarContainer();
    virtual ~NavigationBarContainer() {}

    virtual void initialize();

    virtual void BackClickHandler();
    virtual void MenuClickHandler();

    virtual void SetButtonColor(uint8_t r, uint8_t g, uint8_t b);
protected:
};

#endif // NAVIGATIONBARCONTAINER_HPP
