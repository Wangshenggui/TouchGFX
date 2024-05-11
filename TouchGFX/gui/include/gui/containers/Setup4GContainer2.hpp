#ifndef SETUP4GCONTAINER2_HPP
#define SETUP4GCONTAINER2_HPP

#include <gui_generated/containers/Setup4GContainer2Base.hpp>

class Setup4GContainer2 : public Setup4GContainer2Base
{
public:
    Setup4GContainer2();
    virtual ~Setup4GContainer2() {}

    virtual void initialize();
        
    virtual void setText1(int n);
    virtual void setText2(int n);
    virtual void setText3(int n);
protected:
};

#endif // SETUP4GCONTAINER2_HPP
