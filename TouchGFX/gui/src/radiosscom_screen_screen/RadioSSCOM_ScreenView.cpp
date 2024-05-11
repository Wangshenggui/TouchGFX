#include <gui/radiosscom_screen_screen/RadioSSCOM_ScreenView.hpp>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/Utils.hpp>
#include <stdio.h>
#include <string.h>
#include <math.h>


#ifndef SIMULATOR
#include "Radio.h"
#endif



RadioSSCOM_ScreenView::RadioSSCOM_ScreenView()
{
    textArea1.setWideTextAction(WIDE_TEXT_CHARWRAP);

#ifndef SIMULATOR
    //    HAL_UART_Transmit(&huart1, (const uint8_t*)"Read", 4, 1000);
#endif
}

void RadioSSCOM_ScreenView::setupScreen()
{
    RadioSSCOM_ScreenViewBase::setupScreen();
}

void RadioSSCOM_ScreenView::tearDownScreen()
{
    RadioSSCOM_ScreenViewBase::tearDownScreen();
}



unsigned char test_str[] =
{
0xEB ,0x04 ,0x00 ,0x04 ,0x02 ,0x02 ,0x00 ,0x02 ,0x02 ,0x2D ,0x2E ,0x0A ,0x33 ,0x57 ,0x61 ,0x13
,0x53 ,0x0C ,0x53 ,0x2B ,0x27 ,0x3F ,0x17 ,0x34 ,0x1C ,0x91 ,0xED ,0xBC ,0x3E ,0x0A ,0x11 ,0x1E
,0x00 ,0x0C ,0xE8 ,0x03 ,0x19 ,0x8A ,0x1D ,0xAE ,0xD1 ,0x42 ,0xC6 ,0xC4 ,0x40 ,0xEF ,0x00 ,0xB2
,0x84 ,0x09 ,0x7E ,0xA4 ,0x40 ,0x41 ,0x4F ,0x4B ,0x90
};

void RadioSSCOM_ScreenView::TextAreaAddStr(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, textArea1Buffer, len);
    textArea1.invalidate();
}
void RadioSSCOM_ScreenView::TextArea2AddStr(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, textArea2Buffer, len);
    textArea2.invalidate();
}
void RadioSSCOM_ScreenView::TextArea3AddStr(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, textArea3Buffer, len);
    textArea3.invalidate();
}
void RadioSSCOM_ScreenView::TextArea4AddStr(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, textArea4Buffer, len);
    textArea4.invalidate();
}
void RadioSSCOM_ScreenView::TextArea5AddStr(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, textArea5Buffer, len);
    textArea5.invalidate();
}
void RadioSSCOM_ScreenView::TextArea6AddStr(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, textArea6Buffer, len);
    textArea6.invalidate();
}


void RadioSSCOM_ScreenView::TextArea3_1AddStr(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, textArea3_1Buffer, len);
    textArea3_1.invalidate();
}
void RadioSSCOM_ScreenView::TextArea4_1AddStr(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, textArea4_1Buffer, len);
    textArea4_1.invalidate();
}
void RadioSSCOM_ScreenView::TextArea5_1AddStr(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, textArea5_1Buffer, len);
    textArea5_1.invalidate();
}

#define EARTH_RADIUS  6371.0  // 地球平均半径，单位为公里
#define my_PI    3.1415926
double RadioSSCOM_ScreenView::to_radians(double degree)
{
    return degree * my_PI / 180.0;
}
double RadioSSCOM_ScreenView::vincenty_distance(double lat1, double lon1, double lat2, double lon2) 
{
    double a = EARTH_RADIUS;
    double b = EARTH_RADIUS;
    double f = 1 / 298.257223563;  // WGS-84椭球体扁率
    double L = to_radians(lon2 - lon1);
    double U1 = atan((1 - f) * tan(to_radians(lat1)));
    double U2 = atan((1 - f) * tan(to_radians(lat2)));
    double sinU1 = sin(U1), cosU1 = cos(U1);
    double sinU2 = sin(U2), cosU2 = cos(U2);
    double lambda = L, lambdaP, iterLimit = 100;
    double sinLambda, cosLambda, sinSigma, cosSigma, sigma, sinAlpha, cosSqAlpha, cos2SigmaM;
    do
    {
        sinLambda = sin(lambda);
        cosLambda = cos(lambda);
        sinSigma = sqrt((cosU2 * sinLambda) * (cosU2 * sinLambda) + (cosU1 * sinU2 - sinU1 * cosU2 * cosLambda) * (cosU1 * sinU2 - sinU1 * cosU2 * cosLambda));
        if (sinSigma == 0) return 0;  // 两点重合
        cosSigma = sinU1 * sinU2 + cosU1 * cosU2 * cosLambda;
        sigma = atan2(sinSigma, cosSigma);
        sinAlpha = cosU1 * cosU2 * sinLambda / sinSigma;
        cosSqAlpha = 1 - sinAlpha * sinAlpha;
        cos2SigmaM = cosSigma - 2 * sinU1 * sinU2 / cosSqAlpha;
        double C = f / 16 * cosSqAlpha * (4 + f * (4 - 3 * cosSqAlpha));
        lambdaP = lambda;
        lambda = L + (1 - C) * f * sinAlpha * (sigma + C * sinSigma * (cos2SigmaM + C * cosSigma * (-1 + 2 * cos2SigmaM * cos2SigmaM)));
    } while (fabs(lambda - lambdaP) > 1e-12 && --iterLimit > 0);
    if (iterLimit == 0) return NAN;  // 迭代次数超过限制，计算失败
    double uSq = cosSqAlpha * (a * a - b * b) / (b * b);
    double A = 1 + uSq / 16384 * (4096 + uSq * (-768 + uSq * (320 - 175 * uSq)));
    double B = uSq / 1024 * (256 + uSq * (-128 + uSq * (74 - 47 * uSq)));
    double deltaSigma = B * sinSigma * (cos2SigmaM + B / 4 * (cosSigma * (-1 + 2 * cos2SigmaM * cos2SigmaM) - B / 6 * cos2SigmaM * (-3 + 4 * sinSigma * sinSigma) * (-3 + 4 * cos2SigmaM * cos2SigmaM)));
    double distance = b * A * (sigma - deltaSigma);

    return distance;
}

char str[200];
//定时器处理
void RadioSSCOM_ScreenView::handleTickEvent()
{
#ifndef SIMULATOR
    static uint8_t t1 = 0;

    t1++;
    if (t1 > 90)
    {
        t1 = 0;
        //ParsingUSART();//锟斤拷锟斤拷锟斤拷锟斤拷
    }
#endif

#ifndef SIMULATOR
    if (Radio_GlobalVariableStruct.RadioSSCOM_BuffcopyFlag == 1)
#else
    if (1)
#endif
    {
#ifndef SIMULATOR
        Radio_GlobalVariableStruct.RadioSSCOM_BuffcopyFlag = 0;
#endif
        memset(str, 0, 200);
        for (uint8_t x = 0; x < 73; x++)
        {
#ifndef SIMULATOR
            sprintf(str, "%s%02X ", str, Radio_GlobalVariableStruct.RadioSSCOM_Buff[x]);
#else
            sprintf(str, "%s%02X ", str, test_str[x]);
#endif
        }
        this->TextAreaAddStr((uint8_t*)str, sizeof(str));

        //速度
        union
        {
            float v;
            unsigned char bit[4];
        }Speed;
#ifndef SIMULATOR
        Speed.bit[0] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[25];
        Speed.bit[1] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[26];
        Speed.bit[2] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[27];
        Speed.bit[3] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[28];
#else
        Speed.bit[0] = test_str[25];
        Speed.bit[1] = test_str[26];
        Speed.bit[2] = test_str[27];
        Speed.bit[3] = test_str[28];
#endif
        sprintf(str, "%0.4f km/h", Speed.v * 0.5144f * 3.6f);
        this->TextArea2AddStr((uint8_t*)str, sizeof(str));



        //经度
        union
        {
            double v;
            unsigned char bit[8];
        }Longitude;
#ifndef SIMULATOR
        Longitude.bit[0] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[37];
        Longitude.bit[1] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[38];
        Longitude.bit[2] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[39];
        Longitude.bit[3] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[40];
        Longitude.bit[4] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[41];
        Longitude.bit[5] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[42];
        Longitude.bit[6] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[43];
        Longitude.bit[7] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[44];
#else
        Longitude.bit[0] = test_str[37];
        Longitude.bit[1] = test_str[38];
        Longitude.bit[2] = test_str[39];
        Longitude.bit[3] = test_str[40];
        Longitude.bit[4] = test_str[41];
        Longitude.bit[5] = test_str[42];
        Longitude.bit[6] = test_str[43];
        Longitude.bit[7] = test_str[44];
#endif
        double Longitude1 = Longitude.v / 100.0;
        sprintf(str, "%0.8lf", Longitude.v);
        this->TextArea3AddStr((uint8_t*)str, sizeof(str));


        //纬度
        union
        {
            double v;
            unsigned char bit[8];
        }Latitude;
#ifndef SIMULATOR
        Latitude.bit[0] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[45];
        Latitude.bit[1] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[46];
        Latitude.bit[2] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[47];
        Latitude.bit[3] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[48];
        Latitude.bit[4] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[49];
        Latitude.bit[5] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[50];
        Latitude.bit[6] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[51];
        Latitude.bit[7] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[52];
#else
        Latitude.bit[0] = test_str[45];
        Latitude.bit[1] = test_str[46];
        Latitude.bit[2] = test_str[47];
        Latitude.bit[3] = test_str[48];
        Latitude.bit[4] = test_str[49];
        Latitude.bit[5] = test_str[50];
        Latitude.bit[6] = test_str[51];
        Latitude.bit[7] = test_str[52];
#endif
        double Latitude1 = Latitude.v / 100.0;
        sprintf(str, "%0.8lf", Latitude.v);
        this->TextArea4AddStr((uint8_t*)str, sizeof(str));

        //定位模式
#ifndef SIMULATOR
        sprintf(str, "%c", Radio_GlobalVariableStruct.RadioSSCOM_Buff[53]);
#else
        sprintf(str, "%c", (char)test_str[53]);
#endif
        this->TextArea5AddStr((uint8_t*)str, sizeof(str));

//        //经度
//        union
//        {
//            double v;
//            unsigned char bit[8];
//        }Longitude;
#ifndef SIMULATOR
        Longitude.bit[0] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[54];
        Longitude.bit[1] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[55];
        Longitude.bit[2] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[56];
        Longitude.bit[3] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[57];
        Longitude.bit[4] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[58];
        Longitude.bit[5] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[59];
        Longitude.bit[6] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[60];
        Longitude.bit[7] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[61];
#else
        Longitude.bit[0] = test_str[37];
        Longitude.bit[1] = test_str[38];
        Longitude.bit[2] = test_str[39];
        Longitude.bit[3] = test_str[40];
        Longitude.bit[4] = test_str[41];
        Longitude.bit[5] = test_str[42];
        Longitude.bit[6] = test_str[43];
        Longitude.bit[7] = test_str[44];
#endif
        double Longitude2 = Longitude.v / 100.0;
        sprintf(str, "%0.8lf", Longitude.v);
        this->TextArea3_1AddStr((uint8_t*)str, sizeof(str));


//        //纬度
//        union
//        {
//            double v;
//            unsigned char bit[8];
//        }Latitude;
#ifndef SIMULATOR
        Latitude.bit[0] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[62];
        Latitude.bit[1] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[63];
        Latitude.bit[2] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[64];
        Latitude.bit[3] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[65];
        Latitude.bit[4] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[66];
        Latitude.bit[5] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[67];
        Latitude.bit[6] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[68];
        Latitude.bit[7] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[69];
#else
        Latitude.bit[0] = test_str[45];
        Latitude.bit[1] = test_str[46];
        Latitude.bit[2] = test_str[47];
        Latitude.bit[3] = test_str[48];
        Latitude.bit[4] = test_str[49];
        Latitude.bit[5] = test_str[50];
        Latitude.bit[6] = test_str[51];
        Latitude.bit[7] = test_str[52];
#endif
        double Latitude2 = Latitude.v / 100.0;
        sprintf(str, "%0.8lf", Latitude.v);
        this->TextArea4_1AddStr((uint8_t*)str, sizeof(str));
        
        
        double Dist = vincenty_distance(Latitude1,Longitude1,Latitude2,Longitude2) * 1000.0;
        sprintf(str, "%0.8lf", Dist);
        this->TextArea5_1AddStr((uint8_t*)str, sizeof(str));

        //时间
#ifndef SIMULATOR
        sprintf(str, "%d:%d:%d", Radio_GlobalVariableStruct.RadioSSCOM_Buff[29], Radio_GlobalVariableStruct.RadioSSCOM_Buff[30], Radio_GlobalVariableStruct.RadioSSCOM_Buff[31]);
#else
        sprintf(str, "%d:%d:%d", test_str[29], test_str[30], test_str[31]);
#endif
        this->TextArea6AddStr((uint8_t*)str, sizeof(str));

#ifndef SIMULATOR
        memset(Radio_GlobalVariableStruct.RadioSSCOM_Buff, 0, sizeof Radio_GlobalVariableStruct.RadioSSCOM_Buff);
#endif
    }
}









