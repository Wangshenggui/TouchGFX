#ifndef COORDINATECONVERSION_HPP
#define COORDINATECONVERSION_HPP

#include <touchgfx/Utils.hpp>

typedef struct _POSITION
{
    double longitude;
    double latitude;
}POSITION;

bool outof_China(double lon, double lat);
double translate_lon(double lon, double lat);
double translate_lat(double lon, double lat);
POSITION wgs84togcj02(double wgs_lon, double wgs_lat);
POSITION gcj02tobd09(double gcj_lon, double gcj_lat);
double dms_to_degrees(double dms);
//long long format_time_to_timestamp(uint16_t Y, uint16_t M, uint16_t D, uint16_t h, uint16_t m, uint16_t s);




#endif // KEYBOARDCONTAINER_HPP
