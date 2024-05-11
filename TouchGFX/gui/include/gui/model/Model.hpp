#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

typedef struct
{
    //用于计算FPS
    unsigned int frameSkippedCounter;
    unsigned int frames;
    unsigned int fps;
}public_variable_Structure;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    //////////////////////////////
    //创建结构体和类方法
    public_variable_Structure public_var;
    unsigned int getLCDfps();

    //设置扇热风扇
    void set_fan_onoff(bool data);
    //启动NES
    void start_nes(bool data);
protected:
    ModelListener* modelListener;
};

#endif // MODEL_HPP
