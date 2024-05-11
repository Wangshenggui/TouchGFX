#include <gui/containers/NavigationBarContainer.hpp>
#include <touchgfx/Color.hpp>

NavigationBarContainer::NavigationBarContainer()
{
    flexButton1Buffer[0] = 0xe625;//房子
    flexButton1Buffer[1] = 0;
    flexButton1.invalidate();
    flexButton2Buffer[0] = 0xe633;//返回
    flexButton2Buffer[1] = 0;
    flexButton2.invalidate();
    flexButton3Buffer[0] = 0xe6be;//菜单
    flexButton3Buffer[1] = 0;
    flexButton3.invalidate();
}

void NavigationBarContainer::initialize()
{
    NavigationBarContainerBase::initialize();
}

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
//设置图标颜色
void NavigationBarContainer::SetButtonColor(uint8_t r, uint8_t g, uint8_t b)
{
    flexButton1.setWildcardTextColors(touchgfx::Color::getColorFromRGB(r, g, b), touchgfx::Color::getColorFromRGB(r, g, b));
    flexButton1.invalidate();
    flexButton2.setWildcardTextColors(touchgfx::Color::getColorFromRGB(r, g, b), touchgfx::Color::getColorFromRGB(r, g, b));
    flexButton2.invalidate();
    flexButton3.setWildcardTextColors(touchgfx::Color::getColorFromRGB(r, g, b), touchgfx::Color::getColorFromRGB(r, g, b));
    flexButton3.invalidate();
}
//返回按钮
void NavigationBarContainer::BackClickHandler()
{
    //对外发送事件
    emitBackMenuTriggerCallback(1);
}
//菜单按钮
void NavigationBarContainer::MenuClickHandler()
{
    //对外发送事件
    emitBackMenuTriggerCallback(2);
}


