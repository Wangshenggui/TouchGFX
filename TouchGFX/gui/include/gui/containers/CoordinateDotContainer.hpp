#ifndef COORDINATEDOTCONTAINER_HPP
#define COORDINATEDOTCONTAINER_HPP

#include <gui_generated/containers/CoordinateDotContainerBase.hpp>

class CoordinateDotContainer : public CoordinateDotContainerBase
{
public:
    CoordinateDotContainer();
    virtual ~CoordinateDotContainer() {}

    virtual void initialize();

    //
    virtual void RecordButtonHandler();
    void LonTextAreaAddStr(uint8_t* str, uint32_t len);
    void LatTextAreaAddStr(uint8_t* str, uint32_t len);
    void LonTextArea_1AddStr(uint8_t* str, uint32_t len);
    void LatTextArea_1AddStr(uint8_t* str, uint32_t len);
    void LatTextArea_1_1AddStr(uint8_t* str, uint32_t len);
    void ModeTextAreaAddStr(uint8_t* str, uint32_t len);
    virtual void TriggerTickEvent();

    void SetTriggerTickState(bool s)
    {
        TriggerTickFlag = s;
    }
    bool GetTriggerTickState()
    {
        return TriggerTickFlag;
    }

    virtual void flexButton1Handler();
    virtual void flexButton2Handler();
    
    double to_radians(double degree);
    double linear_distance(double lat1, double lon1, double lat2, double lon2);
    
protected:
    double OutLongitude;
    double OutLatitude;
    bool TriggerTickFlag;
    double coord1[2];
    double coord2[2];
};

#endif // COORDINATEDOTCONTAINER_HPP
