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
        //����ʱ��
        uint16_t SlaveRunTime;
        //����GPSʱ��
        uint8_t GPS_Tim[3];
        //����GPS����
        uint8_t GPS_Dat[3];
        //RTK���õ�״̬������֮�󽫷�������״̬
        uint8_t RTKConfigurationState;
        //4Gģ�鷵����Ϣ
        uint8_t M4GReturnBuff[200];
        uint8_t SendButyFlag;
        uint8_t Send_Num;
        uint8_t RadioSSCOM_Buff[200];//�������ߵ紮��
        bool RadioSSCOM_BuffcopyFlag;//������ɱ�־λ
        char PositionStatus;//��λ״̬
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

    //����״̬�ṹ��
    typedef struct
    {
        uint8_t Buff[RTx_LEN];
        uint8_t State;
        bool ParsingFlag;//������־��ĳЩ�ط���Ҫ����
    }RadioStateStructure;
    extern RadioStateStructure RadioStateStru;

    //����ϵͳ��Ϣ�ṹ��
    typedef struct
    {
        uint8_t State[8];//���Ӳ�״̬
        uint8_t MainSpeed[8];//����������ٶ�
        uint8_t AsSpeed[8];//����������ٶ�
        float UAVSpeed;//�����ٶ�
    }SowingSysStructure;
    extern SowingSysStructure SowingSysStru;

    uint8_t ReadRadioState(void);

    void RadioUSARTRxHandler(void);
    void ParsingUSART(void);





#ifdef __cplusplus
}
#endif


#endif
