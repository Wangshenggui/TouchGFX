#ifndef FILEMANAGERCONTAINER_HPP
#define FILEMANAGERCONTAINER_HPP

#include <gui_generated/containers/FileManagerContainerBase.hpp>

#include <texts/TextKeysAndLanguages.hpp>


typedef struct
{
    //È«¾Ö´«Êä
    uint8_t FileManagerContainerFileNum;
}FileManagerContainer_GlobalVariableStructure;
extern FileManagerContainer_GlobalVariableStructure FileManagerContainer_GlobalVariableStruct;

class FileManagerContainer : public FileManagerContainerBase
{
public:
    FileManagerContainer();
    virtual ~FileManagerContainer() {}

    virtual void initialize();


    /**
     * Initialize this containers widgets
     */
    void setupListElement(const Bitmap& iconBMP, const uint8_t text[]);

    /**
     * Setup the view callback
     */
    void setAction(GenericCallback< FileManagerContainer& >& callback);

    virtual void deleteAction();
    void TextAreaAddStr(uint8_t* str, uint32_t len);
    void setboxProgress1(uint8_t n);
protected:
    /**
     * Callback that that notifies the creator of the list element of an event
     */
    GenericCallback< FileManagerContainer& >* viewCallback;
};

#endif // FILEMANAGERCONTAINER_HPP
