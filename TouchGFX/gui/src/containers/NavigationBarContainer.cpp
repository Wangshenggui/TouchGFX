#include <gui/containers/NavigationBarContainer.hpp>
#include <touchgfx/Color.hpp>

NavigationBarContainer::NavigationBarContainer()
{
    flexButton1Buffer[0] = 0xe625;//����
    flexButton1Buffer[1] = 0;
    flexButton1.invalidate();
    flexButton2Buffer[0] = 0xe633;//����
    flexButton2Buffer[1] = 0;
    flexButton2.invalidate();
    flexButton3Buffer[0] = 0xe6be;//�˵�
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
//����ͼ����ɫ
void NavigationBarContainer::SetButtonColor(uint8_t r, uint8_t g, uint8_t b)
{
    flexButton1.setWildcardTextColors(touchgfx::Color::getColorFromRGB(r, g, b), touchgfx::Color::getColorFromRGB(r, g, b));
    flexButton1.invalidate();
    flexButton2.setWildcardTextColors(touchgfx::Color::getColorFromRGB(r, g, b), touchgfx::Color::getColorFromRGB(r, g, b));
    flexButton2.invalidate();
    flexButton3.setWildcardTextColors(touchgfx::Color::getColorFromRGB(r, g, b), touchgfx::Color::getColorFromRGB(r, g, b));
    flexButton3.invalidate();
}
//���ذ�ť
void NavigationBarContainer::BackClickHandler()
{
    //���ⷢ���¼�
    emitBackMenuTriggerCallback(1);
}
//�˵���ť
void NavigationBarContainer::MenuClickHandler()
{
    //���ⷢ���¼�
    emitBackMenuTriggerCallback(2);
}


