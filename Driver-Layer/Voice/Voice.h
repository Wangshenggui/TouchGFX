#ifndef _VOICE_H
#define _VOICE_H

#include "main.h"
#include "usart.h"


#ifdef __cplusplus
extern "C" {
#endif

#define RTx_LEN 200
    typedef struct
    {
        uint8_t Len;
        uint8_t Receive;
        uint8_t RxBuff[RTx_LEN];
        uint8_t DataBuff[RTx_LEN];
    }VoiceRTxStructure;
    extern VoiceRTxStructure VoiceRTxStru;

    void VoicePlayback(uint8_t tracks);
    void SetVoiceVolume(unsigned char volume);
    void SaveVoiceVolume(unsigned char volume);
    uint8_t GetVoiceVolume(void);
    void VoiceUSARTRxHandler(void);
    void VoiceQuery(uint8_t tracks);


#ifdef __cplusplus
}
#endif

#endif


