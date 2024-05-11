#ifndef SEEDCONTAINER_HPP
#define SEEDCONTAINER_HPP

#include <gui_generated/containers/SeedContainerBase.hpp>

class SeedContainer : public SeedContainerBase
{
public:
    SeedContainer();
    virtual ~SeedContainer() {}

    virtual void initialize();


    virtual void SetTextArea1Num(uint8_t num);
    virtual void SetM1Rpm(uint16_t rpm);
    virtual void SetM2Rpm(uint16_t rpm);
    virtual void SetRunState(uint8_t state);
protected:
};

#endif // SEEDCONTAINER_HPP
