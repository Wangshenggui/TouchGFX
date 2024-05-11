#ifndef _RADDIO_H
#define _RADDIO_H

#include "main.h"
#include "usart.h"

#include <stdbool.h>


#ifdef __cplusplus
extern "C" {
#endif


    typedef struct
    {
        //运行时长
        uint16_t SlaveRunTime;
        //解析GPS时间
        uint8_t GPS_Tim[3];
        //解析GPS日期
        uint8_t GPS_Dat[3];
        //RTK配置的状态，配置之后将返回配置状态
        uint8_t RTKConfigurationState;
        //4G模块返回信息
        uint8_t M4GReturnBuff[200];
        uint8_t SendButyFlag;
        uint8_t Send_Num;
        uint8_t RadioSSCOM_Buff[200];//用于无线电串口
        bool RadioSSCOM_BuffcopyFlag;//复制完成标志位
        char PositionStatus;//定位状态
    }Radio_GlobalVariableStructure;
    extern Radio_GlobalVariableStructure Radio_GlobalVariableStruct;





#define RTx_LEN 200
    typedef struct
    {
        uint8_t Len;
        uint8_t Receive;
        uint8_t RxBuff[RTx_LEN];
        uint8_t DataBuff[RTx_LEN];
    }RadioRTxStructure;
    extern RadioRTxStructure RadioRTxStru;

    //连接状态结构体
    typedef struct
    {
        uint8_t Buff[RTx_LEN];
        uint8_t State;
        bool ParsingFlag;//解析标志，某些地方需要置零
    }RadioStateStructure;
    extern RadioStateStructure RadioStateStru;

    //播种系统信息结构体
    typedef struct
    {
        uint8_t State[8];//种子仓状态
        uint8_t MainSpeed[8];//主电机运行速度
        uint8_t AsSpeed[8];//副电机运行速度
        float UAVSpeed;//飞行速度
    }SowingSysStructure;
    extern SowingSysStructure SowingSysStru;

    uint8_t ReadRadioState(void);

    void RadioUSARTRxHandler(void);
    void ParsingUSART(void);





#ifdef __cplusplus
}
#endif


#endif
