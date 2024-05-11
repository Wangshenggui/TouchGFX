#include <gui/motiontrailscreen_screen/MotionTrailScreenView.hpp>

#include <touchgfx/widgets/canvas/CanvasWidget.hpp>
#include <touchgfx/widgets/canvas/Canvas.hpp>

#include <gui/containers/CoordinateConversion.hpp>

#include <touchgfx/Unicode.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifndef SIMULATOR
#include "rng.h"
#include "ff.h"
#include "myFatFs.h"
#include "malloc.h"
#include "ft5206.h"
extern TouchTypedef mtouch;
#include "Radio.h"
#endif

#ifndef SIMULATOR
int32_t dat[NUM_POINTS][COLS] __attribute__((at(/*起始地址*/0XC0000000
    + /*TouchGFX缓存地址*/0x00232800
    + /*动态图片缓存地址*/0x100000))) = { 0 };
int32_t dat_temp[NUM_POINTS][COLS] __attribute__((at(/*起始地址*/0XC0000000
    + /*TouchGFX缓存地址*/0x00232800
    + /*动态图片缓存地址*/0x100000
    + /*dat数组地址*/NUM_POINTS * COLS * 4))) = { 0 };//0xC033 6680

//直接分配内存
float Coordinate[NUM_POINTS][COLS] =
{
    {0}
};
#else
int32_t dat[NUM_POINTS][COLS] = { 0 };
int32_t dat_temp[NUM_POINTS][COLS] = { 0 };
float Coordinate[NUM_POINTS][COLS] =
{
    26.376401,106.616113,
    26.37639,106.616154,
    26.376415,106.616174,
    26.376252,106.616518,
    26.37623,106.616523,
    26.375887,106.616322,
    26.375878,106.616292,
    26.375925,106.616208,
    26.376008,106.616157,
    26.376181,106.616249,
    26.376212,106.616251,
    26.376295,106.616081,
    26.376318,106.616066,
    26.376404,106.616111,
    26.376401,106.616113,
};
#endif



MotionTrailScreenView::MotionTrailScreenView()
{
    //点击的起始坐标Y
    ClickStartY = 0, ClickEndY = 0;
    N_BarFlag = 0;//默认隐藏

    //容器隐藏
    coordinateDotContainerFlag = 0;

    ////设置字体颜色
    //statusBarContainer.SetDigClockColor(0, 0, 0);

    FastMAP_Struct.LockMapFlag = 0;
    FastMAP_Struct.CurrentCoord1[0] = 26.37618f;
    FastMAP_Struct.CurrentCoord1[1] = 106.616527f;
    FastMAP_Struct.OffsetX = 0;
    FastMAP_Struct.OffsetY = 0;
    FastMAP_Struct.ScaleFactor = 1.0f;
    FastMAP_Struct.CoordinateNumber = 0;

#ifndef SIMULATOR

    uint32_t br;//读取文件大小
    uint8_t* p;//读取文件缓冲区
    unsigned long long FileSize;//文件总大小

    //打开文件
    f_open(&FIL_GlobalVariableStruct.file, (char*)"1:MapCoords-BD09.csv", FA_READ);
    //保存文件大小
    FileSize = FIL_GlobalVariableStruct.file.obj.objsize;

    //申请内存 SRAMEX SRAMIN
    p = (uint8_t*)mymalloc(SRAMIN, FileSize);
    if (p != NULL)printf("动态内存地址 : 0x%08X\r\n", (u32)p);

    //读取文件
    f_read(&FIL_GlobalVariableStruct.file, (void*)p, FileSize, &br);
    p[br] = '\0';
    printf("读取的文件内容 : %s", p);

    //坐标数据处理
    char* token;
    const char* delimiter = "\r\n";

    int index = 0; // 记录当前坐标点的索引
    // 使用 strtok 函数分割字符串
    token = strtok((char*)p, delimiter);
    while (token != NULL) {

        printf(" ---> %s\r\n", token);

        ParseLonLat(token, 0, index); // 提取纬度并保存到数组
        ParseLonLat(token, 1, index); // 提取经度并保存到数组

        // 继续分割下一个坐标点
        token = strtok(NULL, delimiter);
        index++; // 更新索引
    }
    FastMAP_Struct.CoordinateNumber = index;
    // 打印保存的经纬度数据
    for (int i = 0; i < index; i++) {
        printf("纬度：%0.8f, 经度：%0.8f\n", Coordinate[i][0], Coordinate[i][1]);
    }

    //关闭文件
    f_close(&FIL_GlobalVariableStruct.file);
    //释放内存
    myfree(SRAMIN, p);
    p = NULL;
#else
    int size = sizeof(Coordinate) / sizeof(Coordinate[0]); // 计算数组长度
    int nonEmptyCount = countNonEmptyElements(Coordinate, size); // 计算非空元素个数
    FastMAP_Struct.CoordinateNumber = nonEmptyCount / 2;
#endif
}

void MotionTrailScreenView::setupScreen()
{
    for (uint32_t i = 0; i < NUM_POINTS; i++)
    {
        dat[i][0] = 0;
        dat[i][1] = 0;
    }

    MotionTrailScreenViewBase::setupScreen();


#ifdef SIMULATOR
    const uint32_t cacheSize = 0x100000; //3 MB, as example
    uint16_t* const cacheStartAddr = (uint16_t*)malloc(cacheSize);
    Bitmap::removeCache();
    Bitmap::setCache(cacheStartAddr, cacheSize, 1);
#else
    // Place cache start address in SDRAM at address 0xC0008000;
    uint16_t* const cacheStartAddr = (uint16_t*)(0XC0000000 + 800 * 480 * 2 * 3);
    const uint32_t cacheSize = 0x100000; //3 MB, as example
    Bitmap::removeCache();
    Bitmap::setCache(cacheStartAddr, cacheSize, 1);
#endif

    if (bmpId != BITMAP_INVALID)
    {
        Bitmap::dynamicBitmapDelete(bmpId);
        bmpId = BITMAP_INVALID;
    }
    Bitmap::cache(bmpId);
    bmpId = Bitmap::dynamicBitmapCreate(CanvasWidth, CanvasHeight, Bitmap::RGB565);

    if (bmpId != BITMAP_INVALID)
    {
        //set all pixels white
        bitmapPixels = (uint16_t*)Bitmap::dynamicBitmapGetAddress(bmpId);
        memset(bitmapPixels, 0x0, CanvasWidth * CanvasHeight * 2);
    }
    ScalableMapImage.setBitmap(bmpId);
    ScalableMapImage.setWidthHeight(480, 480);


    // 绘制三角形的轮廓
    unsigned int outlineColor = 0xFFFFFF; // 例如，白色
    DrawPolygonOutline(3, dat, outlineColor);
}

void MotionTrailScreenView::tearDownScreen()
{
    MotionTrailScreenViewBase::tearDownScreen();
}


////////////////////////////////////////////////////////
//绘制一个点
void MotionTrailScreenView::DrawPoint(
    uint16_t x, uint16_t y, unsigned int color
)
{
    if (x >= CanvasWidth || y >= CanvasHeight)
        return;
    bitmapPixels[CanvasHeight * (CanvasWidth - x) - (CanvasHeight - 0 - y)] = rgb888_to_rgb565(color);
}
//绘制线
void MotionTrailScreenView::DrawLine(
    uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, unsigned int color
)
{
    uint16_t t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    delta_x = x2 - x1; //计算坐标增量
    delta_y = y2 - y1;
    uRow = x1;
    uCol = y1;

    if (delta_x > 0)incx = 1; //设置单步方向
    else if (delta_x == 0)incx = 0; //垂直线
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }

    if (delta_y > 0)incy = 1;
    else if (delta_y == 0)incy = 0; //水平线
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }

    if (delta_x > delta_y)distance = delta_x; //选取基本增量坐标轴
    else distance = delta_y;

    for (t = 0; t <= distance + 1; t++) //画线输出
    {
        DrawPoint(uRow, uCol, color); //画点
        xerr += delta_x;
        yerr += delta_y;

        if (xerr > distance)
        {
            xerr -= distance;
            uRow += incx;
        }

        if (yerr > distance)
        {
            yerr -= distance;
            uCol += incy;
        }
    }
}

// 判断一个点是否在多边形内部
bool MotionTrailScreenView::PointInsidePolygon(
    uint16_t numVertices, float vertices[NUM_POINTS][2], float x, float y
)
{
    bool inside = false;
    for (int i = 0, j = numVertices - 1; i < numVertices; j = i++)
    {
        if (((vertices[i][1] > y) != (vertices[j][1] > y)) &&
            (x < (vertices[j][0] - vertices[i][0]) * (y - vertices[i][1]) / (vertices[j][1] - vertices[i][1]) + vertices[i][0]))
        {
            inside = !inside;
        }
    }
    return inside;
}
// 定义一个函数来绘制多边形的轮廓
void MotionTrailScreenView::DrawPolygonOutline(
    uint16_t numVertices, int vertices[NUM_POINTS][2], unsigned int color
)
{
    for (int i = 0; i < numVertices - 1; ++i)
    {
        if (vertices[i][0] < 0
            || vertices[i][1] > 480 
            || vertices[i + 1][0] < 0
            || vertices[i + 1][1] > 480)
        {
            continue;
        }
        else
            DrawLine(vertices[i][0], CanvasHeight - vertices[i][1], vertices[i + 1][0], CanvasHeight - vertices[i + 1][1], color);
    }
    // 闭合多边形
    DrawLine(vertices[numVertices - 1][0], CanvasHeight - vertices[numVertices - 1][1],
        vertices[0][0], CanvasHeight - vertices[0][1], color);
}


//绘制填充圆
void MotionTrailScreenView::DrawFilledCircle(
    uint16_t xc, uint16_t yc, uint16_t radius, unsigned int color
)
{
    int x, y;
    for (y = yc - radius; y <= yc + radius; y++)
    {
        for (x = xc - radius; x <= xc + radius; x++)
        {
            if ((x - xc) * (x - xc) + (y - yc) * (y - yc) <= radius * radius)
            {
                DrawPoint(x, y, color); // DrawPixel函数用于画一个点
            }
        }
    }
}
// 辅助函数：交换两个点的位置
void MotionTrailScreenView::swapPoints(Point* p1, Point* p2) 
{
    Point temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

// 辅助函数：绘制水平线
void MotionTrailScreenView::drawHorizontalLine(int x1, int x2, int y, unsigned int color) 
{
    for (int x = x1; x <= x2; x++) 
    {
        DrawPoint(x, y, color);
    }
}

void MotionTrailScreenView::DrawFilledPolygon(uint16_t numVertices, int vertices[NUM_POINTS][2], unsigned int color) 
{
    // 找到多边形的边界框
    int minY = vertices[0][1];
    int maxY = vertices[0][1];

    int minX = vertices[0][0];
    for (int i = 1; i < numVertices; i++) 
    {
        if (vertices[i][1] < minY) minY = vertices[i][1];
        if (minY > 480)
        {
            return;
        }
        if (vertices[i][1] > maxY) maxY = vertices[i][1];
        if (maxY > 480)
        {
            return;
        }

        if (vertices[i][0] < minX) minX = vertices[i][0];
        if (minX < 0)
        {
            return;
        }
    }

    // 对每条扫描线进行处理
    for (int scanlineY = minY; scanlineY <= maxY; scanlineY++) 
    {
        int intersections = 0;
        int intersectionX[NUM_POINTS]; // 假设最多有 NUM_POINTS 个交点

        // 找到与当前扫描线相交的点
        for (int i = 0; i < numVertices; i++) 
        {
            int nextIndex = (i + 1) % numVertices;
            int y1 = vertices[i][1];
            int y2 = vertices[nextIndex][1];
            if ((y1 <= scanlineY && y2 > scanlineY) || (y1 > scanlineY && y2 <= scanlineY)) 
            {
                float t = (float)(scanlineY - y1) / (y2 - y1);
                intersectionX[intersections] = vertices[i][0] + t * (vertices[nextIndex][0] - vertices[i][0]);
                intersections++;
            }
        }

        // 按照 x 坐标排序
        for (int i = 0; i < intersections - 1; i++) 
        {
            for (int j = 0; j < intersections - i - 1; j++) 
            {
                if (intersectionX[j] > intersectionX[j + 1]) 
                {
                    int temp = intersectionX[j];
                    intersectionX[j] = intersectionX[j + 1];
                    intersectionX[j + 1] = temp;
                }
            }
        }

        // 绘制扫描线上的水平线段
        for (int i = 0; i < intersections; i += 2) 
        {
            DrawLine(intersectionX[i], 480 - scanlineY, intersectionX[i + 1], 480 - scanlineY, color);
        }
    }
}

//清屏
void MotionTrailScreenView::Clear(
    unsigned int color
)
{
    for (uint32_t i = 0; i < CanvasWidth * CanvasHeight; i++)
    {
        bitmapPixels[i] = rgb888_to_rgb565(color);
    }
}

// 函数：将RGB888颜色转换为RGB565格式
unsigned short MotionTrailScreenView::rgb888_to_rgb565(
    unsigned int rgb888_color
)
{
    // 从RGB888颜色值中提取每个通道的值
    unsigned char r = (rgb888_color >> 16) & 0xFF;
    unsigned char g = (rgb888_color >> 8) & 0xFF;
    unsigned char b = rgb888_color & 0xFF;

    // 将RGB888中的每个通道值映射到RGB565格式中
    unsigned short r565 = (r >> 3) & 0x1F;
    unsigned short g565 = (g >> 2) & 0x3F;
    unsigned short b565 = (b >> 3) & 0x1F;

    // 组合RGB565中的红色、绿色和蓝色通道值
    return (r565 << 11) | (g565 << 5) | b565;
}

//拖拽
void MotionTrailScreenView::handleDragEvent(const DragEvent& event)
{
    static uint16_t NewY = 0;

    MotionTrailScreenViewBase::handleDragEvent(event);

    if (event.getType() == DragEvent::DRAGGED)
    {
        //显示渐变通知栏
        if (ClickStartY < 20 && N_BarFlag == 0)
        {
            NewY = event.getNewY();
            notificationBarContainer.SetAlpha(NewY * 2.2);
            //设置状态栏时钟字体颜色
            static uint16_t color;
            color = NewY * 3.5;
            if (color > 255)color = 255;
            //不改变字体颜色
            //statusBarContainer.SetDigClockColor(color, color, color);
        }
        else if (event.getNewX() < 480 && event.getNewY() < 480 
            && ClickStartY > 40 && !coordinateDotContainerFlag)
        {
            FastMAP_Struct.OffsetX += event.getDeltaX();
            FastMAP_Struct.OffsetY -= event.getDeltaY();

            UpdateMap();
        }
    }
}


// 查找二维数组第n个元素的最小值
float MotionTrailScreenView::FindMin(
    float arr[NUM_POINTS][COLS], int n, int num
)
{
    float min = arr[0][n];
    for (int i = 0; i < num; i++)
    {
        if (arr[i][n] < min && arr[i][n] > 0)
            min = arr[i][n];
    }
    return min;
}
// 查找二维数组第n个元素的最大值
float MotionTrailScreenView::FindMax(
    float arr[NUM_POINTS][COLS], int n, int num
)
{
    float max = arr[0][n];; // 将初始值设为较小的值
    for (int i = 0; i < num; i++)
    {
        if (arr[i][n] > max && arr[i][n] > 0) // 检查当前元素是否大于 max
            max = arr[i][n]; // 如果是，则更新 max 的值
    }
    return max;
}

void MotionTrailScreenView::OffsetCSysPoint(
    int arr[NUM_POINTS][COLS],
    int arr_temp[NUM_POINTS][COLS],
    int num,
    int x, int y
)
{
    for (int i = 0; i < num; i++)
    {
        arr_temp[i][0] = arr[i][0] + x;
        arr_temp[i][1] = arr[i][1] + y;
    }
}

void MotionTrailScreenView::ZoomCSysPoint(
    int arr[NUM_POINTS][COLS],
    int arr_temp[NUM_POINTS][COLS],
    int num,
    float value
)
{
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            arr_temp[i][j] = arr[i][j] * value;
        }
    }
}





void MotionTrailScreenView::UpdateMap()
{
    ZoomCSysPoint(dat, dat_temp, FastMAP_Struct.CoordinateNumber, FastMAP_Struct.ScaleFactor);//缩放
    OffsetCSysPoint(dat_temp, dat_temp, FastMAP_Struct.CoordinateNumber, FastMAP_Struct.OffsetX, FastMAP_Struct.OffsetY);//偏移

    if (!FastMAP_Struct.LockMapFlag)
    {
        Clear(0x0);
        // 绘制轮廓
        DrawPolygonOutline(FastMAP_Struct.CoordinateNumber, dat_temp, 0xFFFFFF);
        DrawFilledPolygon(FastMAP_Struct.CoordinateNumber, dat_temp, 0x00FFFF);
    }

    DrawFilledCircle(
        ((FastMAP_Struct.CurrentCoord1[1] - FindMin(Coordinate, 1, FastMAP_Struct.CoordinateNumber)) * 100000000) * FastMAP_Struct.ScaleFactor + FastMAP_Struct.OffsetX,
        480 - ((FastMAP_Struct.CurrentCoord1[0] - FindMin(Coordinate, 0, FastMAP_Struct.CoordinateNumber)) * 100000000) * FastMAP_Struct.ScaleFactor - FastMAP_Struct.OffsetY,
        6,
        PointInsidePolygon(FastMAP_Struct.CoordinateNumber, Coordinate, FastMAP_Struct.CurrentCoord1[0], FastMAP_Struct.CurrentCoord1[1]) ? 0xFF0000 : 0x00FF00);

    ScalableMapImage.invalidate();
}

void MotionTrailScreenView::LoadMapButtonHandler()
{
    for (uint16_t i = 0; i < FastMAP_Struct.CoordinateNumber; i++)
    {
        dat[i][0] = (Coordinate[i][1] - FindMin(Coordinate, 1, FastMAP_Struct.CoordinateNumber)) * 100000000;
        dat[i][1] = (Coordinate[i][0] - FindMin(Coordinate, 0, FastMAP_Struct.CoordinateNumber)) * 100000000;
    }

    UpdateMap();
}




void MotionTrailScreenView::ZoomInButtonHandler()
{
    FastMAP_Struct.ScaleFactor *= 1.1f;
    UpdateMap();
}

void MotionTrailScreenView::ZoomOutButtonHandler()
{
    FastMAP_Struct.ScaleFactor /= 1.1f;
    UpdateMap();
}

//裁剪字符串
char* MotionTrailScreenView::substring(
    char* dst, char* src, int start, int len
)
{
    int length = 100;//最大长度
    if (start >= length || start < 0)
        return NULL;
    if (len > length)
        len = length - start;
    src += start;
    while (len--)
    {
        *(dst++) = *(src++);
    }
    *(dst++) = '\0';
    return dst;
}

void MotionTrailScreenView::ParseLonLat(
    const char* string, int n, int index
)
{
    char result[200] = { 0 };
    const char* start = string;

    // 定位到第n个逗号
    for (int i = 0; i < n; i++) 
    {
        start = strchr(start, ',');
        if (!start) 
        {
            // 如果逗号不够n个，将结果设为空字符串
            result[0] = '\0';
            return;
        }

        // 移动到下一个字符
        start++;
    }

    // 计算逗号后字符串的长度
    const char* end = strchr(start, ',');
    size_t length = end ? (size_t)(end - start) : strlen(start);

    // 截取字符串并复制到结果
    if (length < 200 - 1) 
    {
        strncpy(result, start, length);
        // 手动添加 null 结尾
        result[length] = '\0';
    }
    else 
    {
        // 目标长度不足，截断字符串
        strncpy(result, start, 200 - 1);
        result[200 - 1] = '\0';
    }

    char temp[100];
    double out;
    switch (n)
    {
    case(0):
        substring(temp, result, 0, length);
        out = atof(temp);
        Coordinate[index][0] = out; // 保存纬度到二维数组
        break;
    case(1):
        substring(temp, result, 0, length);
        out = atof(temp);
        Coordinate[index][1] = out; // 保存经度到二维数组
        break;
    }
}
//获取坐标数组中的经纬度组数
int MotionTrailScreenView::countNonEmptyElements(
    float array[NUM_POINTS][COLS], int size
)
{
    int count = 0;
    for (int i = 0; i < NUM_POINTS; i++) 
    {
        for (int j = 0; j < COLS; j++) 
        {
            if (array[i][j] != 0.0f) // 这里的判断条件可以根据实际情况修改
            { 
                count++;
            }
        }
    }
    return count;
}

//锁定地图
void MotionTrailScreenView::flexButton5Handler()
{
    FastMAP_Struct.LockMapFlag = !FastMAP_Struct.LockMapFlag;
    if (FastMAP_Struct.LockMapFlag == 1)
    {
        LoadMapButton.setVisible(false);
        ZoomInButton.setVisible(false);
        ZoomOutButton.setVisible(false);
        getRootContainer().invalidate();
    }
    else
    {
        LoadMapButton.setVisible(true);
        ZoomInButton.setVisible(true);
        ZoomOutButton.setVisible(true);
        getRootContainer().invalidate();
    }
}

extern double wgs84_lon;
extern double wgs84_lat;
extern double gcj02_lon;
extern double gcj02_lat;
extern double bd09_lon;
extern double bd09_lat;
extern unsigned char test_str[];
void MotionTrailScreenView::handleTickEvent()
{
    static uint16_t i = 0;
    i++;
    if(i == 2)
    {
        i = 0;
        if (!coordinateDotContainer.GetTriggerTickState())
        {
            //经度
            union
            {
                double v;
                unsigned char bit[8];
            }Longitude;
#ifndef SIMULATOR
            Longitude.bit[0] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[37];
            Longitude.bit[1] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[38];
            Longitude.bit[2] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[39];
            Longitude.bit[3] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[40];
            Longitude.bit[4] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[41];
            Longitude.bit[5] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[42];
            Longitude.bit[6] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[43];
            Longitude.bit[7] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[44];
#else
            Longitude.bit[0] = test_str[37];
            Longitude.bit[1] = test_str[38];
            Longitude.bit[2] = test_str[39];
            Longitude.bit[3] = test_str[40];
            Longitude.bit[4] = test_str[41];
            Longitude.bit[5] = test_str[42];
            Longitude.bit[6] = test_str[43];
            Longitude.bit[7] = test_str[44];
#endif
            OutLongitude = Longitude.v;

            //纬度
            union
            {
                double v;
                unsigned char bit[8];
            }Latitude;
#ifndef SIMULATOR
            Latitude.bit[0] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[45];
            Latitude.bit[1] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[46];
            Latitude.bit[2] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[47];
            Latitude.bit[3] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[48];
            Latitude.bit[4] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[49];
            Latitude.bit[5] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[50];
            Latitude.bit[6] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[51];
            Latitude.bit[7] = Radio_GlobalVariableStruct.RadioSSCOM_Buff[52];
#else
            Latitude.bit[0] = test_str[45];
            Latitude.bit[1] = test_str[46];
            Latitude.bit[2] = test_str[47];
            Latitude.bit[3] = test_str[48];
            Latitude.bit[4] = test_str[49];
            Latitude.bit[5] = test_str[50];
            Latitude.bit[6] = test_str[51];
            Latitude.bit[7] = test_str[52];
#endif
            OutLatitude = Latitude.v;


            wgs84_lon = dms_to_degrees(OutLongitude);
            wgs84_lat = dms_to_degrees(OutLatitude);

            gcj02_lon = wgs84togcj02(wgs84_lon, wgs84_lat).longitude;
            gcj02_lat = wgs84togcj02(wgs84_lon, wgs84_lat).latitude;

            bd09_lon = gcj02tobd09(gcj02_lon, gcj02_lat).longitude;
            bd09_lat = gcj02tobd09(gcj02_lon, gcj02_lat).latitude;


            FastMAP_Struct.CurrentCoord1[0] = bd09_lat;
            FastMAP_Struct.CurrentCoord1[1] = bd09_lon;

            DrawFilledCircle(
                ((FastMAP_Struct.CurrentCoord1[1] - FindMin(Coordinate, 1, FastMAP_Struct.CoordinateNumber)) * 100000000)* FastMAP_Struct.ScaleFactor + FastMAP_Struct.OffsetX,
                480 - ((FastMAP_Struct.CurrentCoord1[0] - FindMin(Coordinate, 0, FastMAP_Struct.CoordinateNumber)) * 100000000) * FastMAP_Struct.ScaleFactor - FastMAP_Struct.OffsetY,
                6,
                PointInsidePolygon(FastMAP_Struct.CoordinateNumber, Coordinate, FastMAP_Struct.CurrentCoord1[0], FastMAP_Struct.CurrentCoord1[1]) ? 0xFF0000 : 0x00FF00);

            CoorTextArea.setXY(((FastMAP_Struct.CurrentCoord1[1] - FindMin(Coordinate, 1, FastMAP_Struct.CoordinateNumber)) * 100000000)* FastMAP_Struct.ScaleFactor + FastMAP_Struct.OffsetX,
                480 - ((FastMAP_Struct.CurrentCoord1[0] - FindMin(Coordinate, 0, FastMAP_Struct.CoordinateNumber)) * 100000000) * FastMAP_Struct.ScaleFactor - FastMAP_Struct.OffsetY);
            char str1[100];
            char str2[100];
            sprintf(str1, "%0.10lf", bd09_lon);
            sprintf(str2, "%0.10lf", bd09_lat);
            this->CoorTextAreaAddStr((uint8_t*)str1, sizeof(str1), (uint8_t*)str2, sizeof(str2));

            ScalableMapImage.invalidate();
        }
    }
    

    //计算帧率
    statusBarContainer.SetFPS(Model.getLCDfps());
}

void MotionTrailScreenView::handleKeyEvent(uint8_t key)
{
#ifndef SIMULATOR
    if (key == TaskConGUIQueRenTemp)
#else
#define TaskConGUIQueRenTemp '0'
    if (key == TaskConGUIQueRenTemp)
#endif
    {
#ifndef SIMULATOR
        //更新CPU温度和使用率
        statusBarContainer.SetCPU(MAIN_FREERTOS_GlobalVariableStruct.cpu_usage, MAIN_FREERTOS_GlobalVariableStruct.CPUtemperature);
#else
        touchgfx_printf("%c\r\n", TaskConGUIQueRenTemp);
#endif
    }
#ifndef SIMULATOR
    else if (key == TaskConGUIQueUpRadio)
#else
#define TaskConGUIQueUpRadio '1'
    else if (key == TaskConGUIQueUpRadio)
#endif
    {
#ifndef SIMULATOR
        //更新无线电数据
        statusBarContainer.SetRadioState(RadioStateStru.State);
        statusBarContainer.SetRadioColor(statusBarContainer.GetRadioState());
        statusBarContainer.SetRadioVisible(true);

        //更新时间
        statusBarContainer.UpdateTime();
#else
        touchgfx_printf("%c\r\n", TaskConGUIQueUpRadio);
#endif
    }
}

//重写点击事件
void MotionTrailScreenView::handleClickEvent(const ClickEvent& event)
{
    MotionTrailScreenViewBase::handleClickEvent(event);//防止触摸失效
    //获取事件
    ClickEvent::ClickEventType type = event.getType();

    if (type == ClickEvent::PRESSED)
    {
        //获取点击坐标
        ClickStartY = event.getY();

        if (notificationBarContainer.GetSlider1ClickFlag() == 1)
            statusBarContainer.SetDigClockColor(255, 255, 255);
    }
    else if (type == ClickEvent::RELEASED)
    {
        //获取松开坐标
        ClickEndY = event.getY();

        if (ClickStartY < 20)
        {
            if (ClickEndY < 70)
            {
                N_BarFlag = 0;
                //隐藏通知栏
                notificationBarContainer.SetAlpha(0);
            }
            else
            {
                notificationBarContainer.SetAlpha(255);
                N_BarFlag = 1;
            }
        }
        else if (ClickEndY < 40 && notificationBarContainer.GetSlider1ClickFlag() == 1)
        {
            //设置状态栏时钟字体颜色
            statusBarContainer.SetDigClockColor(255, 255, 255);
            N_BarFlag = 0;
            //隐藏通知栏
            notificationBarContainer.SetAlpha(0);
        }
        if (N_BarFlag == 0)
            statusBarContainer.SetDigClockColor(255, 255, 255);
        else
            statusBarContainer.SetDigClockColor(255, 255, 255);
    }
    else if (type == ClickEvent::CANCEL)
    {

    }
}

//显示打点界面
void MotionTrailScreenView::CoordinateDotButtonHandler()
{
    coordinateDotContainer.setVisible(true);
    coorDotConBackButton.setVisible(true);
    coorDotConBackButton.invalidate();
    coordinateDotContainer.invalidate();

    coordinateDotContainerFlag = 1;
    coordinateDotContainer.SetTriggerTickState(1);
}
//隐藏打点界面
void MotionTrailScreenView::coorDotConBackButtonHandler()
{
    coordinateDotContainer.setVisible(false);
    coorDotConBackButton.setVisible(false);
    coorDotConBackButton.invalidate();
    coordinateDotContainer.invalidate();

    coordinateDotContainerFlag = 0;
    coordinateDotContainer.SetTriggerTickState(0);
}

void MotionTrailScreenView::CoorTextAreaAddStr(uint8_t* str1, uint32_t len1, uint8_t* str2, uint32_t len2)
{
    Unicode::fromUTF8(str1, CoorTextAreaBuffer1, len1);
    Unicode::fromUTF8(str2, CoorTextAreaBuffer2, len2);
    CoorTextArea.invalidate();
}


/*
    SendContGUIMess	X	3	193	3
    IDLE           	R	0	102	6
    IwdgTask       	R	0	91	4
    PerDataProcess_	B	4	171	5
    GUI_MesProcess 	B	6	968	2
    touchGFX       	B	5	3070	1

    SendContGUIMess	X	3	193	3
    IDLE           	R	0	102	6
    IwdgTask       	R	0	91	4
    PerDataProcess_	B	4	171	5
    GUI_MesProcess 	B	6	968	2
    touchGFX       	B	5	3062 1
*/


void MotionTrailScreenView::function1()
{
#ifndef SIMULATOR
    static uint8_t i = 0;
    uint8_t* p = NULL;
    //申请内存
    p = (uint8_t*)mymalloc(SRAMEX, 1 * 1024 * 1024);
    if (p != NULL)printf("动态内存地址 : 0x%08X\r\n", (u32)p);
    sprintf((char*)p, "Memory Malloc Test %d\r\n",i++);
    printf("%s",p);
    myfree(SRAMEX,p);
    printf("动态内存地址 : 0x%08X\r\n", (u32)p);
    p = NULL;
    printf("动态内存地址 : 0x%08X\r\n", (u32)p);
    sprintf((char*)p, "Memory Malloc Test %d\r\n", i++);
    printf("%s", p);
    printf("动态内存地址 : 0x%08X\r\n", (u32)p);
#endif
}


