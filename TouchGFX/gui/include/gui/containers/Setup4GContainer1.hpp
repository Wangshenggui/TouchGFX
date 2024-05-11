#ifndef SETUP4GCONTAINER1_HPP
#define SETUP4GCONTAINER1_HPP

#include <gui_generated/containers/Setup4GContainer1Base.hpp>

class Setup4GContainer1 : public Setup4GContainer1Base
{
public:
    Setup4GContainer1();
    virtual ~Setup4GContainer1() {}

    virtual void initialize();
        
    virtual void setText1(int n);
    virtual void setText2(int n);
    virtual void setText3(int n);
protected:
};

#endif // SETUP4GCONTAINER1_HPP
