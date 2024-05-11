#include <gui/containers/CoordinateConversion.hpp>


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <math.h>




double PI = 3.1415926535897932384626;
double x_PI = 3.14159265358979323846 * 3000.0 / 180.0;
double ee = 0.00669342162296594323;
double a = 6378245.0;



POSITION bd_pos;
POSITION gcj_pos;
//POSITION wgs_pos;

bool outof_China(double lon, double lat)
{
    return(lon < 72.004 || lon>137.8374 || lat < 0.8293 || lat >55.8271 || false);
}

double translate_lon(double lon, double lat)
{
#ifndef SIMULATOR
    double ret = 300.0 + lon + 2.0 * lat + 0.1 * lon * lon + 0.1 * lon * lat + 0.1 * sqrt(fabs(lon));
    ret += (20.0 * sin(6.0 * lon * PI) + 20.0 * sin(2.0 * lon * PI)) * 2.0 / 3.0;
    ret += (20.0 * sin(lon * PI) + 40.0 * sin(lon / 3.0 * PI)) * 2.0 / 3.0;
    ret += (150 * sin(lon / 12.0 * PI) + 300.0 * sin(lon / 30.0 * PI)) * 2.0 / 3.0;
#else
    double ret = 300.0 + lon + 2.0 * lat + 0.1 * lon * lon + 0.1 * lon * lat + 0.1 * sqrt(fabs(lon));
    ret += (20.0 * sin(6.0 * lon * PI) + 20.0 * sin(2.0 * lon * PI)) * 2.0 / 3.0;
    ret += (20.0 * sin(lon * PI) + 40.0 * sin(lon / 3.0 * PI)) * 2.0 / 3.0;
    ret += (150 * sin(lon / 12.0 * PI) + 300.0 * sin(lon / 30.0 * PI)) * 2.0 / 3.0;
#endif
    return ret;
}
double translate_lat(double lon, double lat)
{
    double ret = -100 + 2.0 * lon + 3.0 * lat + 0.2 * lat * lat + 0.1 * lon * lat + 0.2 * sqrt((fabs(lon)));
    ret += (20.0 * sin(6.0 * lon * PI) + 20 * sin(2.0 * lon * PI)) * 2.0 / 3.0;
    ret += (20.0 * sin(lat * PI) + 40.0 * sin(lat / 3.0 * PI)) * 2.0 / 3.0;
    ret += (160.0 * sin(lat / 12.0 * PI) + 320.0 * sin(lat / 30.0 * PI)) * 2.0 / 3.0;
    return ret;
}

POSITION wgs84togcj02(double wgs_lon, double wgs_lat)
{
    if (outof_China(wgs_lon, wgs_lat))
    {
        gcj_pos.longitude = wgs_lon;
        gcj_pos.latitude = wgs_lat;
        return gcj_pos;
    }
    else
    {
        double dlat = translate_lat(wgs_lon - 105.0, wgs_lat - 35.0);
        double dlon = translate_lon(wgs_lon - 105.0, wgs_lat - 35.0);
        double radlat = wgs_lat / 180.0 * PI;
        double magic = sin(radlat);
        magic = 1 - ee * magic * magic;
        double squrtmagic = sqrt(magic);
        dlon = (dlon * 180.0) / (a / squrtmagic * cos(radlat) * PI);
        dlat = (dlat * 180.0) / ((a * (1 - ee)) / (magic * squrtmagic) * PI);
        gcj_pos.longitude = wgs_lon + dlon;
        gcj_pos.latitude = wgs_lat + dlat;
        return gcj_pos;
    }
}

POSITION gcj02tobd09(double gcj_lon, double gcj_lat)
{
    double z = sqrt(gcj_lon * gcj_lon + gcj_lat * gcj_lat) + 0.00002 * sin(gcj_lat * x_PI);
    double theta = atan2(gcj_lat, gcj_lon) + 0.000003 * cos(gcj_lon * x_PI);
    bd_pos.longitude = z * cos(theta) + 0.0065;
    bd_pos.latitude = z * sin(theta) + 0.006;
    return bd_pos;
}


// 将度分秒格式的经纬度转换为十进制度数
double dms_to_degrees(double dms)
{
    double degrees = (int)(dms / 100);  // 取整数部分作为度数
    double minutes = dms - degrees * 100; // 取小数部分作为分数
    double decimal_degrees = degrees + minutes / 60.0; // 转换为十进制度数
    return decimal_degrees;
}

//long long format_time_to_timestamp(uint16_t Y, uint16_t M, uint16_t D, uint16_t h, uint16_t m, uint16_t s)
//{
//    struct tm timeinfo = {  };
//    time_t timestamp;

//    timeinfo.tm_year = Y - 1900;
//    timeinfo.tm_mon = M - 1;
//    timeinfo.tm_mday = D;
//    timeinfo.tm_hour = h;
//    timeinfo.tm_min = m;
//    timeinfo.tm_sec = s;
//    // 转换为时间戳
//    timestamp = mktime(&timeinfo);
//    return timestamp;
//}






