#ifndef MOTIONTRAILSCREENVIEW_HPP
#define MOTIONTRAILSCREENVIEW_HPP

#include <gui_generated/motiontrailscreen_screen/MotionTrailScreenViewBase.hpp>
#include <gui/motiontrailscreen_screen/MotionTrailScreenPresenter.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>

#define CanvasWidth     480     //480
#define CanvasHeight    480     //480

#define NUM_POINTS 1000 //���1000����
#define COLS 2



class MotionTrailScreenView : public MotionTrailScreenViewBase
{
public:
    MotionTrailScreenView();
    virtual ~MotionTrailScreenView() {touchgfx::CanvasWidgetRenderer::resetBuffer();}
    virtual void setupScreen();
    virtual void tearDownScreen();
    
    //�û��Զ����෽��
    //RGB888->RGB565
    virtual unsigned short rgb888_to_rgb565(unsigned int rgb888_color);
    //����һ����
    virtual void DrawPoint(uint16_t x,uint16_t y,unsigned int color);
    //����
    virtual void Clear(unsigned int color);
    //�����߶�
    virtual void DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,unsigned int color);
    //�������Բ
    void DrawFilledCircle(uint16_t xc, uint16_t yc, uint16_t radius, unsigned int color);
    // ����һ�����������ƶ���ε�����
    void DrawPolygonOutline(uint16_t numVertices, int vertices[NUM_POINTS][2], unsigned int color);
    // �ж�һ�����Ƿ��ڶ�����ڲ�
    bool PointInsidePolygon(uint16_t numVertices, float vertices[NUM_POINTS][2], float x, float y);
    // ���Ҷ�ά�����n��Ԫ�ص���Сֵ
    float FindMin(float arr[NUM_POINTS][COLS], int n, int num);
    // ���Ҷ�ά�����n��Ԫ�ص����ֵ
    float FindMax(float arr[NUM_POINTS][COLS], int n, int num);
    //��ͼƫ�ƻ�׼�����
    void OffsetCSysPoint(int arr[NUM_POINTS][COLS], int arr_temp[NUM_POINTS][COLS], int num, int x, int y);
    //��ͼ����
    void ZoomCSysPoint(int arr[NUM_POINTS][COLS], int arr_temp[NUM_POINTS][COLS], int num, float value);
    //�ü��ַ������ļ�������ʹ�õ���
    char* substring(char* dst, char* src, int start, int len);
    //������γ����Ϣ
    void ParseLonLat(const char* string, int n, int index);
    //���µ�ͼ
    void UpdateMap();
    //��ȡ���������еľ�γ������
    int countNonEmptyElements(float array[NUM_POINTS][COLS], int size);

    /*�����������*/
    // ���������������������λ��
    void swapPoints(Point* p1, Point* p2);
    // ��������������ˮƽ��
    void drawHorizontalLine(int x1, int x2, int y, unsigned int color);
    void DrawFilledPolygon(uint16_t numVertices, int vertices[NUM_POINTS][2], unsigned int color);


    
    //ϵͳ�Դ���
    virtual void handleDragEvent(const DragEvent& event);//��ק
    virtual void LoadMapButtonHandler();//���ص�ͼ
    virtual void ZoomInButtonHandler();//�Ŵ�
    virtual void ZoomOutButtonHandler();//��С

    virtual void flexButton5Handler();

    virtual void handleTickEvent();
    virtual void handleClickEvent(const ClickEvent& event);
    virtual void handleKeyEvent(uint8_t key);

    virtual void CoordinateDotButtonHandler();
    virtual void coorDotConBackButtonHandler();

    virtual void function1();

    virtual void CoorTextAreaAddStr(uint8_t* str1, uint32_t len1, uint8_t* str2, uint32_t len2);
protected:
    //���嶯̬ͼ��
    uint16_t* bitmapPixels;
    BitmapId bmpId;

    typedef struct
    {
        bool LockMapFlag;//������ͼ��־
        int OffsetX;//xƫ��
        int OffsetY;//yƫ��
        int CoordinateNumber;//��¼��������
        float ScaleFactor;//����
        float CurrentCoord1[COLS];//��ǰ���꣬��ʾ����ͼ�ϵ��ƶ�������
    }FastMAP_Structure;
    FastMAP_Structure FastMAP_Struct;

    Model Model;

    //�������ʼ����Y
    uint16_t ClickStartY, ClickEndY;
    bool N_BarFlag;//Ĭ������

    //��¼���������״̬
    bool coordinateDotContainerFlag;

    double OutLongitude;
    double OutLatitude;
};

#endif // MOTIONTRAILSCREENVIEW_HPP
