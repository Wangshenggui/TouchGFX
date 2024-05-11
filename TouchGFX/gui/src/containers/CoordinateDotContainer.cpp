#include <gui/containers/CoordinateDotContainer.hpp>
#include <touchgfx/Utils.hpp>

#include <string.h>
#include <stdio.h>

#include <gui/containers/CoordinateConversion.hpp>

#ifndef SIMULATOR
#include "ff.h"
#include "myFatFs.h"
#include "malloc.h"
#include "Radio.h"
#endif


double wgs84_lon = 0;
double wgs84_lat = 0;

double gcj02_lon = 0;
double gcj02_lat = 0;

double bd09_lon = 0;
double bd09_lat = 0;

extern unsigned char test_str[];

CoordinateDotContainer::CoordinateDotContainer()
{
    TriggerTickFlag = 0;
}

void CoordinateDotContainer::initialize()
{
    CoordinateDotContainerBase::initialize();
}

///////////////////////////////////////////////////////////////
void CoordinateDotContainer::RecordButtonHandler()
{
    char str[100];
#ifndef SIMULATOR
    uint32_t FileSize;
    //打开文件
    f_open(&FIL_GlobalVariableStruct.file, (char*)"1:MapCoords-BD09.csv", FA_WRITE);
    FileSize = FIL_GlobalVariableStruct.file.obj.objsize;
    f_lseek(&FIL_GlobalVariableStruct.file, FileSize);
    sprintf(str,"%0.8lf,%0.8lf", bd09_lat, bd09_lon);
    f_printf(&FIL_GlobalVariableStruct.file, "%s\r\n", str);
    f_close(&FIL_GlobalVariableStruct.file);
    
    //打开文件
    f_open(&FIL_GlobalVariableStruct.file, (char*)"1:MapCoords-WGS84.csv", FA_WRITE);
    FileSize = FIL_GlobalVariableStruct.file.obj.objsize;
    f_lseek(&FIL_GlobalVariableStruct.file, FileSize);
    sprintf(str,"%0.8lf,%0.8lf", OutLatitude, OutLongitude);
    f_printf(&FIL_GlobalVariableStruct.file, "%s\r\n", str);
    f_close(&FIL_GlobalVariableStruct.file);
#else
    sprintf(str, "%0.10lf,%0.10lf\r\n", bd09_lon, bd09_lat);
    touchgfx_printf("%s\r\n", str);
#endif
}


void CoordinateDotContainer::LonTextAreaAddStr(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, LonTextAreaBuffer, len);
    LonTextArea.invalidate();
}
void CoordinateDotContainer::LatTextAreaAddStr(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, LatTextAreaBuffer, len);
    LatTextArea.invalidate();
}
void CoordinateDotContainer::ModeTextAreaAddStr(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, ModeTextAreaBuffer, len);
    ModeTextArea.invalidate();
}

void CoordinateDotContainer::LonTextArea_1AddStr(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, LonTextArea_1Buffer, len);
    LonTextArea_1.invalidate();
}
void CoordinateDotContainer::LatTextArea_1AddStr(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, LatTextArea_1Buffer, len);
    LatTextArea_1.invalidate();
}
void CoordinateDotContainer::LatTextArea_1_1AddStr(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, LatTextArea_1_1Buffer, len);
    LatTextArea_1_1.invalidate();
}


void CoordinateDotContainer::TriggerTickEvent()
{
    if (TriggerTickFlag)
    {
        char str[100];

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
        OutLongitude = Longitude.v;
        sprintf(str, "%0.8lf", OutLongitude);
        this->LonTextAreaAddStr((uint8_t*)str, sizeof(str));


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
        OutLatitude = Latitude.v;
        sprintf(str, "%0.8lf", OutLatitude);
        this->LatTextAreaAddStr((uint8_t*)str, sizeof(str));

        //定位模式
#ifndef SIMULATOR
        sprintf(str, "%c", Radio_GlobalVariableStruct.RadioSSCOM_Buff[53]);
#else
        sprintf(str, "%c", (char)test_str[53]);
#endif
        this->ModeTextAreaAddStr((uint8_t*)str, sizeof(str));


        

        wgs84_lon = dms_to_degrees(OutLongitude);
        wgs84_lat = dms_to_degrees(OutLatitude);

        gcj02_lon = wgs84togcj02(wgs84_lon, wgs84_lat).longitude;
        gcj02_lat = wgs84togcj02(wgs84_lon, wgs84_lat).latitude;

        bd09_lon = gcj02tobd09(gcj02_lon, gcj02_lat).longitude;
        bd09_lat = gcj02tobd09(gcj02_lon, gcj02_lat).latitude;

        sprintf(str, "%0.10lf", bd09_lon);
        this->LonTextArea_1AddStr((uint8_t*)str, sizeof(str));

        sprintf(str, "%0.10lf", bd09_lat);
        this->LatTextArea_1AddStr((uint8_t*)str, sizeof(str));
    }
}


void CoordinateDotContainer::flexButton1Handler()
{
#ifndef SIMULATOR
    // 打开文件以进行截断
    f_open(&FIL_GlobalVariableStruct.file, (char*)"1:MapCoords-BD09.csv", FA_WRITE | FA_OPEN_ALWAYS);
    // 将文件截断为零长度
    f_truncate(&FIL_GlobalVariableStruct.file);
    // 关闭文件
    f_close(&FIL_GlobalVariableStruct.file);
    
    // 打开文件以进行截断
    f_open(&FIL_GlobalVariableStruct.file, (char*)"1:MapCoords-WGS84.csv", FA_WRITE | FA_OPEN_ALWAYS);
    // 将文件截断为零长度
    f_truncate(&FIL_GlobalVariableStruct.file);
    // 关闭文件
    f_close(&FIL_GlobalVariableStruct.file);
#else
    touchgfx_printf("Delete file content\r\n");
#endif
}


#include <math.h>
double CoordinateDotContainer::to_radians(double degree) {
    return degree * 3.1415926 / 180.0;
}
double CoordinateDotContainer::linear_distance(double lat1, double lon1, double lat2, double lon2) {
	double dlat = to_radians(lat2 - lat1);
	double dlon = to_radians(lon2 - lon1);

	// 使用简单的勾股定理计算直线距离
	double a = sin(dlat / 2) * sin(dlat / 2) + cos(to_radians(lat1)) * cos(to_radians(lat2)) * sin(dlon / 2) * sin(dlon / 2);
	double c = 2 * atan2(sqrt(a), sqrt(1 - a));
	double distance = 6371.0 * c;

	return distance;
}
void CoordinateDotContainer::flexButton2Handler()
{
#ifndef SIMULATOR
    static uint8_t i = 0;
    
    i++;
    if(i == 1)
    {
        double wgs84_lon1 = 0;
        double wgs84_lat1 = 0;
        wgs84_lon1 = dms_to_degrees(OutLongitude);
        wgs84_lat1 = dms_to_degrees(OutLatitude);
        coord1[0] = wgs84_lon1;
        coord1[1] = wgs84_lat1;
        
        char str[100];
        sprintf(str, "ready");
        this->LatTextArea_1_1AddStr((uint8_t*)str, sizeof(str));
    }
    else if(i == 2)
    {
        i = 0;
        
        double wgs84_lon2 = 0;
        double wgs84_lat2 = 0;
        wgs84_lon2 = dms_to_degrees(OutLongitude);
        wgs84_lat2 = dms_to_degrees(OutLatitude);
        coord2[0] = wgs84_lon2;
        coord2[1] = wgs84_lat2;
        
        double distance = linear_distance(coord1[1],coord1[0],coord2[1],coord2[0]);
        
        char str[100];
        sprintf(str, "%0.8lf", distance * 1000);
        this->LatTextArea_1_1AddStr((uint8_t*)str, sizeof(str));
    }
#else
    static uint8_t i = 0;
    
    i++;
    if(i == 1)
    {
        double wgs84_lon1 = 0;
        double wgs84_lat1 = 0;
        wgs84_lon1 = dms_to_degrees(10636.57314516);
        wgs84_lat1 = dms_to_degrees(2623.05964699);
        coord1[0] = wgs84_lon1;
        coord1[1] = wgs84_lat1;
        
        char str[100];
        sprintf(str, "ready");
        this->LatTextArea_1_1AddStr((uint8_t*)str, sizeof(str));
    }
    else if(i == 2)
    {
        i = 0;
        
        double wgs84_lon2 = 0;
        double wgs84_lat2 = 0;
        wgs84_lon2 = dms_to_degrees(10636.57380145);
        wgs84_lat2 = dms_to_degrees(2623.05646272);
        coord2[0] = wgs84_lon2;
        coord2[1] = wgs84_lat2;
        
        double distance = linear_distance(coord1[1],coord1[0],coord2[1],coord2[0]);
        
        char str[100];
        sprintf(str, "%0.8lf", distance * 1000);
        this->LatTextArea_1_1AddStr((uint8_t*)str, sizeof(str));
    }
#endif
}

