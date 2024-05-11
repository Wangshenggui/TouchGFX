#ifndef FILEMANAGERSCREENVIEW_HPP
#define FILEMANAGERSCREENVIEW_HPP

#include <gui_generated/filemanagerscreen_screen/FileManagerScreenViewBase.hpp>
#include <gui/filemanagerscreen_screen/FileManagerScreenPresenter.hpp>

#include <gui/containers/FileManagerContainer.hpp>



class FileManagerScreenView : public FileManagerScreenViewBase
{
public:
    FileManagerScreenView();
    virtual ~FileManagerScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();

    /**
     * Handler of list element clicks.
     */
    virtual void listElementClicked(FileManagerContainer& element);
    virtual void BackMenuHandler(uint8_t value);
    virtual void handleClickEvent(const ClickEvent& event);
    virtual void LoadingFileSystem(uint8_t* _path);
    virtual void pathTailor(char str[], char* p);
    virtual int GetFileType(char path[]);
protected:
    //文件个数
    uint8_t FileNum;
    //打开路径
//    uint8_t path[200];
    //保存显示的路径
    uint8_t disp_path[200][200];

    //最多显示200个文件
    static const int numberOfListElements = 200;

    static const int a=1;

    FileManagerContainer listElements[numberOfListElements];

    // Callback that is assigned to each list element
    Callback<FileManagerScreenView, FileManagerContainer&> listElementClickedCallback;

    uint8_t path[200];
    bool backFlag;
};

#endif // FILEMANAGERSCREENVIEW_HPP
