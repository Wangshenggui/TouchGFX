#include <gui/containers/Setup4GContainer1.hpp>
#include <touchgfx/Utils.hpp>
#include <touchgfx/Unicode.hpp>

Setup4GContainer1::Setup4GContainer1()
{

}

void Setup4GContainer1::initialize()
{
    Setup4GContainer1Base::initialize();
}




void Setup4GContainer1::setText1(int n)
{
    uint8_t data[3][20] LOCATION_PRAGMA("ExtFlashSection") = { "GPGGA","GPGSV","GPRMC" };

    Unicode::fromUTF8((const uint8_t*)data[n % 3], textArea1Buffer, sizeof data[n % 3]);
    textArea1.invalidate();
}

void Setup4GContainer1::setText2(int n)
{
    const uint8_t data[4][20] LOCATION_PRAGMA("ExtFlashSection") = { "Disable","1Hz","5Hz","10Hz" };

    Unicode::fromUTF8((const uint8_t*)data[n % 4], textArea1Buffer, sizeof data[n % 4]);
    textArea1.invalidate();
}

void Setup4GContainer1::setText3(int n)
{
    const uint8_t data[2][90] LOCATION_PRAGMA("ExtFlashSection") = { "COM1","COM2" };

    Unicode::fromUTF8((const uint8_t*)data[n % 2], textArea1Buffer, sizeof data[n % 2]);
    textArea1.invalidate();
}
