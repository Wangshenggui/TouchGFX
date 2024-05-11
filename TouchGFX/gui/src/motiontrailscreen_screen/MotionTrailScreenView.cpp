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
int32_t dat[NUM_POINTS][COLS] __attribute__((at(/*��ʼ��ַ*/0XC0000000
    + /*TouchGFX�����ַ*/0x00232800
    + /*��̬ͼƬ�����ַ*/0x100000))) = { 0 };
int32_t dat_temp[NUM_POINTS][COLS] __attribute__((at(/*��ʼ��ַ*/0XC0000000
    + /*TouchGFX�����ַ*/0x00232800
    + /*��̬ͼƬ�����ַ*/0x100000
    + /*dat�����ַ*/NUM_POINTS * COLS * 4))) = { 0 };//0xC033 6680

//ֱ�ӷ����ڴ�
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
    //�������ʼ����Y
    ClickStartY = 0, ClickEndY = 0;
    N_BarFlag = 0;//Ĭ������

    //��������
    coordinateDotContainerFlag = 0;

    ////����������ɫ
    //statusBarContainer.SetDigClockColor(0, 0, 0);

    FastMAP_Struct.LockMapFlag = 0;
    FastMAP_Struct.CurrentCoord1[0] = 26.37618f;
    FastMAP_Struct.CurrentCoord1[1] = 106.616527f;
    FastMAP_Struct.OffsetX = 0;
    FastMAP_Struct.OffsetY = 0;
    FastMAP_Struct.ScaleFactor = 1.0f;
    FastMAP_Struct.CoordinateNumber = 0;

#ifndef SIMULATOR

    uint32_t br;//��ȡ�ļ���С
    uint8_t* p;//��ȡ�ļ�������
    unsigned long long FileSize;//�ļ��ܴ�С

    //���ļ�
    f_open(&FIL_GlobalVariableStruct.file, (char*)"1:MapCoords-BD09.csv", FA_READ);
    //�����ļ���С
    FileSize = FIL_GlobalVariableStruct.file.obj.objsize;

    //�����ڴ� SRAMEX SRAMIN
    p = (uint8_t*)mymalloc(SRAMIN, FileSize);
    if (p != NULL)printf("��̬�ڴ��ַ : 0x%08X\r\n", (u32)p);

    //��ȡ�ļ�
    f_read(&FIL_GlobalVariableStruct.file, (void*)p, FileSize, &br);
    p[br] = '\0';
    printf("��ȡ���ļ����� : %s", p);

    //�������ݴ���
    char* token;
    const char* delimiter = "\r\n";

    int index = 0; // ��¼��ǰ����������
    // ʹ�� strtok �����ָ��ַ���
    token = strtok((char*)p, delimiter);
    while (token != NULL) {

        printf(" ---> %s\r\n", token);

        ParseLonLat(token, 0, index); // ��ȡγ�Ȳ����浽����
        ParseLonLat(token, 1, index); // ��ȡ���Ȳ����浽����

        // �����ָ���һ�������
        token = strtok(NULL, delimiter);
        index++; // ��������
    }
    FastMAP_Struct.CoordinateNumber = index;
    // ��ӡ����ľ�γ������
    for (int i = 0; i < index; i++) {
        printf("γ�ȣ�%0.8f, ���ȣ�%0.8f\n", Coordinate[i][0], Coordinate[i][1]);
    }

    //�ر��ļ�
    f_close(&FIL_GlobalVariableStruct.file);
    //�ͷ��ڴ�
    myfree(SRAMIN, p);
    p = NULL;
#else
    int size = sizeof(Coordinate) / sizeof(Coordinate[0]); // �������鳤��
    int nonEmptyCount = countNonEmptyElements(Coordinate, size); // ����ǿ�Ԫ�ظ���
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


    // ���������ε�����
    unsigned int outlineColor = 0xFFFFFF; // ���磬��ɫ
    DrawPolygonOutline(3, dat, outlineColor);
}

void MotionTrailScreenView::tearDownScreen()
{
    MotionTrailScreenViewBase::tearDownScreen();
}


////////////////////////////////////////////////////////
//����һ����
void MotionTrailScreenView::DrawPoint(
    uint16_t x, uint16_t y, unsigned int color
)
{
    if (x >= CanvasWidth || y >= CanvasHeight)
        return;
    bitmapPixels[CanvasHeight * (CanvasWidth - x) - (CanvasHeight - 0 - y)] = rgb888_to_rgb565(color);
}
//������
void MotionTrailScreenView::DrawLine(
    uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, unsigned int color
)
{
    uint16_t t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    delta_x = x2 - x1; //������������
    delta_y = y2 - y1;
    uRow = x1;
    uCol = y1;

    if (delta_x > 0)incx = 1; //���õ�������
    else if (delta_x == 0)incx = 0; //��ֱ��
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }

    if (delta_y > 0)incy = 1;
    else if (delta_y == 0)incy = 0; //ˮƽ��
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }

    if (delta_x > delta_y)distance = delta_x; //ѡȡ��������������
    else distance = delta_y;

    for (t = 0; t <= distance + 1; t++) //�������
    {
        DrawPoint(uRow, uCol, color); //����
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

// �ж�һ�����Ƿ��ڶ�����ڲ�
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
// ����һ�����������ƶ���ε�����
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
    // �պ϶����
    DrawLine(vertices[numVertices - 1][0], CanvasHeight - vertices[numVertices - 1][1],
        vertices[0][0], CanvasHeight - vertices[0][1], color);
}


//�������Բ
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
                DrawPoint(x, y, color); // DrawPixel�������ڻ�һ����
            }
        }
    }
}
// ���������������������λ��
void MotionTrailScreenView::swapPoints(Point* p1, Point* p2) 
{
    Point temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

// ��������������ˮƽ��
void MotionTrailScreenView::drawHorizontalLine(int x1, int x2, int y, unsigned int color) 
{
    for (int x = x1; x <= x2; x++) 
    {
        DrawPoint(x, y, color);
    }
}

void MotionTrailScreenView::DrawFilledPolygon(uint16_t numVertices, int vertices[NUM_POINTS][2], unsigned int color) 
{
    // �ҵ�����εı߽��
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

    // ��ÿ��ɨ���߽��д���
    for (int scanlineY = minY; scanlineY <= maxY; scanlineY++) 
    {
        int intersections = 0;
        int intersectionX[NUM_POINTS]; // ��������� NUM_POINTS ������

        // �ҵ��뵱ǰɨ�����ཻ�ĵ�
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

        // ���� x ��������
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

        // ����ɨ�����ϵ�ˮƽ�߶�
        for (int i = 0; i < intersections; i += 2) 
        {
            DrawLine(intersectionX[i], 480 - scanlineY, intersectionX[i + 1], 480 - scanlineY, color);
        }
    }
}

//����
void MotionTrailScreenView::Clear(
    unsigned int color
)
{
    for (uint32_t i = 0; i < CanvasWidth * CanvasHeight; i++)
    {
        bitmapPixels[i] = rgb888_to_rgb565(color);
    }
}

// ��������RGB888��ɫת��ΪRGB565��ʽ
unsigned short MotionTrailScreenView::rgb888_to_rgb565(
    unsigned int rgb888_color
)
{
    // ��RGB888��ɫֵ����ȡÿ��ͨ����ֵ
    unsigned char r = (rgb888_color >> 16) & 0xFF;
    unsigned char g = (rgb888_color >> 8) & 0xFF;
    unsigned char b = rgb888_color & 0xFF;

    // ��RGB888�е�ÿ��ͨ��ֵӳ�䵽RGB565��ʽ��
    unsigned short r565 = (r >> 3) & 0x1F;
    unsigned short g565 = (g >> 2) & 0x3F;
    unsigned short b565 = (b >> 3) & 0x1F;

    // ���RGB565�еĺ�ɫ����ɫ����ɫͨ��ֵ
    return (r565 << 11) | (g565 << 5) | b565;
}

//��ק
void MotionTrailScreenView::handleDragEvent(const DragEvent& event)
{
    static uint16_t NewY = 0;

    MotionTrailScreenViewBase::handleDragEvent(event);

    if (event.getType() == DragEvent::DRAGGED)
    {
        //��ʾ����֪ͨ��
        if (ClickStartY < 20 && N_BarFlag == 0)
        {
            NewY = event.getNewY();
            notificationBarContainer.SetAlpha(NewY * 2.2);
            //����״̬��ʱ��������ɫ
            static uint16_t color;
            color = NewY * 3.5;
            if (color > 255)color = 255;
            //���ı�������ɫ
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


// ���Ҷ�ά�����n��Ԫ�ص���Сֵ
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
// ���Ҷ�ά�����n��Ԫ�ص����ֵ
float MotionTrailScreenView::FindMax(
    float arr[NUM_POINTS][COLS], int n, int num
)
{
    float max = arr[0][n];; // ����ʼֵ��Ϊ��С��ֵ
    for (int i = 0; i < num; i++)
    {
        if (arr[i][n] > max && arr[i][n] > 0) // ��鵱ǰԪ���Ƿ���� max
            max = arr[i][n]; // ����ǣ������ max ��ֵ
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
    ZoomCSysPoint(dat, dat_temp, FastMAP_Struct.CoordinateNumber, FastMAP_Struct.ScaleFactor);//����
    OffsetCSysPoint(dat_temp, dat_temp, FastMAP_Struct.CoordinateNumber, FastMAP_Struct.OffsetX, FastMAP_Struct.OffsetY);//ƫ��

    if (!FastMAP_Struct.LockMapFlag)
    {
        Clear(0x0);
        // ��������
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

//�ü��ַ���
char* MotionTrailScreenView::substring(
    char* dst, char* src, int start, int len
)
{
    int length = 100;//��󳤶�
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

    // ��λ����n������
    for (int i = 0; i < n; i++) 
    {
        start = strchr(start, ',');
        if (!start) 
        {
            // ������Ų���n�����������Ϊ���ַ���
            result[0] = '\0';
            return;
        }

        // �ƶ�����һ���ַ�
        start++;
    }

    // ���㶺�ź��ַ����ĳ���
    const char* end = strchr(start, ',');
    size_t length = end ? (size_t)(end - start) : strlen(start);

    // ��ȡ�ַ��������Ƶ����
    if (length < 200 - 1) 
    {
        strncpy(result, start, length);
        // �ֶ���� null ��β
        result[length] = '\0';
    }
    else 
    {
        // Ŀ�곤�Ȳ��㣬�ض��ַ���
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
        Coordinate[index][0] = out; // ����γ�ȵ���ά����
        break;
    case(1):
        substring(temp, result, 0, length);
        out = atof(temp);
        Coordinate[index][1] = out; // ���澭�ȵ���ά����
        break;
    }
}
//��ȡ���������еľ�γ������
int MotionTrailScreenView::countNonEmptyElements(
    float array[NUM_POINTS][COLS], int size
)
{
    int count = 0;
    for (int i = 0; i < NUM_POINTS; i++) 
    {
        for (int j = 0; j < COLS; j++) 
        {
            if (array[i][j] != 0.0f) // ������ж��������Ը���ʵ������޸�
            { 
                count++;
            }
        }
    }
    return count;
}

//������ͼ
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
            //����
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

            //γ��
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
    

    //����֡��
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
        //����CPU�¶Ⱥ�ʹ����
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
        //�������ߵ�����
        statusBarContainer.SetRadioState(RadioStateStru.State);
        statusBarContainer.SetRadioColor(statusBarContainer.GetRadioState());
        statusBarContainer.SetRadioVisible(true);

        //����ʱ��
        statusBarContainer.UpdateTime();
#else
        touchgfx_printf("%c\r\n", TaskConGUIQueUpRadio);
#endif
    }
}

//��д����¼�
void MotionTrailScreenView::handleClickEvent(const ClickEvent& event)
{
    MotionTrailScreenViewBase::handleClickEvent(event);//��ֹ����ʧЧ
    //��ȡ�¼�
    ClickEvent::ClickEventType type = event.getType();

    if (type == ClickEvent::PRESSED)
    {
        //��ȡ�������
        ClickStartY = event.getY();

        if (notificationBarContainer.GetSlider1ClickFlag() == 1)
            statusBarContainer.SetDigClockColor(255, 255, 255);
    }
    else if (type == ClickEvent::RELEASED)
    {
        //��ȡ�ɿ�����
        ClickEndY = event.getY();

        if (ClickStartY < 20)
        {
            if (ClickEndY < 70)
            {
                N_BarFlag = 0;
                //����֪ͨ��
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
            //����״̬��ʱ��������ɫ
            statusBarContainer.SetDigClockColor(255, 255, 255);
            N_BarFlag = 0;
            //����֪ͨ��
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

//��ʾ������
void MotionTrailScreenView::CoordinateDotButtonHandler()
{
    coordinateDotContainer.setVisible(true);
    coorDotConBackButton.setVisible(true);
    coorDotConBackButton.invalidate();
    coordinateDotContainer.invalidate();

    coordinateDotContainerFlag = 1;
    coordinateDotContainer.SetTriggerTickState(1);
}
//���ش�����
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
    //�����ڴ�
    p = (uint8_t*)mymalloc(SRAMEX, 1 * 1024 * 1024);
    if (p != NULL)printf("��̬�ڴ��ַ : 0x%08X\r\n", (u32)p);
    sprintf((char*)p, "Memory Malloc Test %d\r\n",i++);
    printf("%s",p);
    myfree(SRAMEX,p);
    printf("��̬�ڴ��ַ : 0x%08X\r\n", (u32)p);
    p = NULL;
    printf("��̬�ڴ��ַ : 0x%08X\r\n", (u32)p);
    sprintf((char*)p, "Memory Malloc Test %d\r\n", i++);
    printf("%s", p);
    printf("��̬�ڴ��ַ : 0x%08X\r\n", (u32)p);
#endif
}


