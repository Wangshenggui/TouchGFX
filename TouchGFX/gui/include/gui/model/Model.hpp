#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

typedef struct
{
    //���ڼ���FPS
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
    //�����ṹ����෽��
    public_variable_Structure public_var;
    unsigned int getLCDfps();

    //�������ȷ���
    void set_fan_onoff(bool data);
    //����NES
    void start_nes(bool data);
protected:
    ModelListener* modelListener;
};

#endif // MODEL_HPP
