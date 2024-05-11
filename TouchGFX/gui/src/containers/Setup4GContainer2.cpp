#include <gui/containers/Setup4GContainer2.hpp>
#include <touchgfx/Utils.hpp>
#include <touchgfx/Unicode.hpp>

Setup4GContainer2::Setup4GContainer2()
{

}

void Setup4GContainer2::initialize()
{
    Setup4GContainer2Base::initialize();
}


void Setup4GContainer2::setText1(int n)
{
    const uint8_t data[3][90] LOCATION_PRAGMA("ExtFlashSection") = { "GPGGA","GPGSV","GPRMC" };

    Unicode::fromUTF8((const uint8_t*)data[n % 3], textArea1Buffer, sizeof data[n % 3]);
    textArea1.invalidate();
}

void Setup4GContainer2::setText2(int n)
{
    const uint8_t data[4][20] LOCATION_PRAGMA("ExtFlashSection") = { "Disable","1Hz","5Hz","10Hz" };

    Unicode::fromUTF8((const uint8_t*)data[n % 4], textArea1Buffer, sizeof data[n % 4]);
    textArea1.invalidate();
}

void Setup4GContainer2::setText3(int n)
{
    const uint8_t data[2][90] LOCATION_PRAGMA("ExtFlashSection") = { "COM1","COM2" };

    Unicode::fromUTF8((const uint8_t*)data[n % 2], textArea1Buffer, sizeof data[n % 2]);
    textArea1.invalidate();
}
