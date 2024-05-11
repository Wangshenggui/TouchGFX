#ifndef MOTIONTRAILSCREENVIEW_HPP
#define MOTIONTRAILSCREENVIEW_HPP

#include <gui_generated/motiontrailscreen_screen/MotionTrailScreenViewBase.hpp>
#include <gui/motiontrailscreen_screen/MotionTrailScreenPresenter.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>

#define CanvasWidth     480     //480
#define CanvasHeight    480     //480

#define NUM_POINTS 1000 //最多1000个点
#define COLS 2



class MotionTrailScreenView : public MotionTrailScreenViewBase
{
public:
    MotionTrailScreenView();
    virtual ~MotionTrailScreenView() {touchgfx::CanvasWidgetRenderer::resetBuffer();}
    virtual void setupScreen();
    virtual void tearDownScreen();
    
    //用户自定义类方法
    //RGB888->RGB565
    virtual unsigned short rgb888_to_rgb565(unsigned int rgb888_color);
    //绘制一个点
    virtual void DrawPoint(uint16_t x,uint16_t y,unsigned int color);
    //清屏
    virtual void Clear(unsigned int color);
    //绘制线段
    virtual void DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,unsigned int color);
    //绘制填充圆
    void DrawFilledCircle(uint16_t xc, uint16_t yc, uint16_t radius, unsigned int color);
    // 定义一个函数来绘制多边形的轮廓
    void DrawPolygonOutline(uint16_t numVertices, int vertices[NUM_POINTS][2], unsigned int color);
    // 判断一个点是否在多边形内部
    bool PointInsidePolygon(uint16_t numVertices, float vertices[NUM_POINTS][2], float x, float y);
    // 查找二维数组第n个元素的最小值
    float FindMin(float arr[NUM_POINTS][COLS], int n, int num);
    // 查找二维数组第n个元素的最大值
    float FindMax(float arr[NUM_POINTS][COLS], int n, int num);
    //地图偏移基准坐标点
    void OffsetCSysPoint(int arr[NUM_POINTS][COLS], int arr_temp[NUM_POINTS][COLS], int num, int x, int y);
    //地图缩放
    void ZoomCSysPoint(int arr[NUM_POINTS][COLS], int arr_temp[NUM_POINTS][COLS], int num, float value);
    //裁剪字符串（文件解析中使用到）
    char* substring(char* dst, char* src, int start, int len);
    //解析经纬度信息
    void ParseLonLat(const char* string, int n, int index);
    //更新地图
    void UpdateMap();
    //获取坐标数组中的经纬度组数
    int countNonEmptyElements(float array[NUM_POINTS][COLS], int size);

    /*绘制填充多边形*/
    // 辅助函数：交换两个点的位置
    void swapPoints(Point* p1, Point* p2);
    // 辅助函数：绘制水平线
    void drawHorizontalLine(int x1, int x2, int y, unsigned int color);
    void DrawFilledPolygon(uint16_t numVertices, int vertices[NUM_POINTS][2], unsigned int color);


    
    //系统自带的
    virtual void handleDragEvent(const DragEvent& event);//拖拽
    virtual void LoadMapButtonHandler();//加载地图
    virtual void ZoomInButtonHandler();//放大
    virtual void ZoomOutButtonHandler();//缩小

    virtual void flexButton5Handler();

    virtual void handleTickEvent();
    virtual void handleClickEvent(const ClickEvent& event);
    virtual void handleKeyEvent(uint8_t key);

    virtual void CoordinateDotButtonHandler();
    virtual void coorDotConBackButtonHandler();

    virtual void function1();

    virtual void CoorTextAreaAddStr(uint8_t* str1, uint32_t len1, uint8_t* str2, uint32_t len2);
protected:
    //定义动态图像
    uint16_t* bitmapPixels;
    BitmapId bmpId;

    typedef struct
    {
        bool LockMapFlag;//锁定地图标志
        int OffsetX;//x偏移
        int OffsetY;//y偏移
        int CoordinateNumber;//记录坐标数量
        float ScaleFactor;//缩放
        float CurrentCoord1[COLS];//当前坐标，显示到地图上的移动点坐标
    }FastMAP_Structure;
    FastMAP_Structure FastMAP_Struct;

    Model Model;

    //点击的起始坐标Y
    uint16_t ClickStartY, ClickEndY;
    bool N_BarFlag;//默认隐藏

    //记录打点容器的状态
    bool coordinateDotContainerFlag;

    double OutLongitude;
    double OutLatitude;
};

#endif // MOTIONTRAILSCREENVIEW_HPP
