#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}

    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }
    ////////////////////////////////////////////////////
    //消息事件
    virtual void TaskContGUIQueue_Event(unsigned char key)
    {

    }
protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
