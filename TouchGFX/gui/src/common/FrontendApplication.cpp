#include <gui/common/FrontendApplication.hpp>



FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap)
    : FrontendApplicationBase(m, heap)
{
#ifdef SIMULATOR
    const uint32_t cacheSize = 0x300000; //3 MB, as example
    uint16_t* const cacheStartAddr = (uint16_t*)malloc(cacheSize);
    Bitmap::setCache(cacheStartAddr, cacheSize, 4);
#else
    // Place cache start address in SDRAM at address 0xC0008000;
    uint16_t* const cacheStartAddr = (uint16_t*)(0XC0000000+800*480*2*3);
    const uint32_t cacheSize = 0x800000; //3 MB, as example
    Bitmap::removeCache();
    Bitmap::setCache(cacheStartAddr, cacheSize, 4);
    Bitmap::cacheAll();//开始缓存所有的图片
#endif
    
}
