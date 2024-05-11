#ifndef _BACKLIGHT_H
#define _BACKLIGHT_H

#include "main.h"
#include "tim.h"


#ifdef __cplusplus
extern "C" {
#endif

    void SetBacklight(uint16_t pwm);
    void SaveBacklight(uint16_t pwm);
    uint16_t GetBacklight(void);


#ifdef __cplusplus
}
#endif

#endif


