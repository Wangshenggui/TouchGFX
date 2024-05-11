#ifndef NESCONTAINER_HPP
#define NESCONTAINER_HPP

#include <gui_generated/containers/NESContainerBase.hpp>

class NESContainer : public NESContainerBase
{
public:
    NESContainer();
    virtual ~NESContainer() {}

    virtual void initialize();
protected:
};

#endif // NESCONTAINER_HPP
