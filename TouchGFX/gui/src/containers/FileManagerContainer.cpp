#include <gui/containers/FileManagerContainer.hpp>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/Utils.hpp>
#include <string.h>
#include <stdio.h>
#include <BitmapDatabase.hpp>


FileManagerContainer_GlobalVariableStructure FileManagerContainer_GlobalVariableStruct = { 0 };


FileManagerContainer::FileManagerContainer() :
    viewCallback(0)
{

}

void FileManagerContainer::initialize()
{
    FileManagerContainerBase::initialize();
}

//以下是奇葩代码，看不懂
void FileManagerContainer::setupListElement(const Bitmap& iconBMP, const uint8_t text[])
{
    image1.setBitmap(iconBMP);

    uint8_t str[256];
    sprintf((char*)str, "%s", text);
    this->TextAreaAddStr(str, sizeof(str));
    invalidate();
}

void FileManagerContainer::TextAreaAddStr(uint8_t* str, uint32_t len)
{
    Unicode::fromUTF8(str, textArea1Buffer, len);
    textArea1.invalidate();
}

void FileManagerContainer::setboxProgress1(uint8_t n)
{
    boxProgress1.setValue(n);
    boxProgress1.invalidate();
}

void FileManagerContainer::setAction(GenericCallback< FileManagerContainer& >& callback)
{
    viewCallback = &callback;
}

void FileManagerContainer::deleteAction()
{
    FileManagerContainer_GlobalVariableStruct.FileManagerContainerFileNum = boxProgress1.getValue();

    // Inform the view of the event
    if (viewCallback->isValid())
    {
        viewCallback->execute(*this);
    }
}

