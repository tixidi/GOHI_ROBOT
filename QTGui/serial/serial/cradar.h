#ifndef CRADAR_H
#define CRADAR_H

/*************************************************
作者:fearlazy
博客:www.fearlazy.com
描述: 仿雷达扫描效果(Qt绘制学习实践)
**************************************************/

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
class CRadar : public QWidget
{
    Q_OBJECT
public:
    static const int PICTURE_SIZE =10;
    static const int DISTANCE =50;
    static const int P_BUTTON_ARRAY=15;
    static const int P_BUTTON_ARRAY1 =9;
    static const int P_BUTTON_ARRAY2 =9;
    static const int P_BUTTON_ARRAY3 =9;
    static const int P_BUTTON_ARRAY4 =6;
    static const int P_BUTTON_ARRAY5 =5;
    static const int P_BUTTON_ARRAY6 =4;
    static const int P_BUTTON_ARRAY7 =4;
    static const int P_BUTTON_ARRAY8 =4;
    static const int P_BUTTON_ARRAY9 =4;
    static const int P_BUTTON_ARRAY10 =4;
    static const int P_BUTTON_ARRAY11 =4;
    static const int P_BUTTON_ARRAY12 =4;
    static const int P_BUTTON_ARRAY13 =4;
    static const int P_BUTTON_ARRAY14 =4;
    static const int P_BUTTON_ARRAY15 =5;
    static const int P_EXPLAIN_NUM =6;
    static const int P_BUTTON_SUM =94;
    static const int EXPLAIN_FLAG =100;
    static const unsigned char LINE_SUM =14;

public:
    explicit CRadar(QWidget *parent = nullptr);

public:
    void timerOutFunc(void);
    void adjustButton(void);
    void randAddress(int x,int y);
    void drawPoint(int x,int y);
    void randAddress(int x,int y,int arc);
    void setFlag(int *x_temp,int *y_temp1,int *y_temp2,int *y_temp3,\
                    int *y_temp4,int *y_temp5,int *y_temp6,int *y_temp7,int *y_temp8,\
                 int *y_temp9,int *y_temp10,int *y_temp11,int *x_temp12,int *y_temp13,\
                    int *x_temp14);
protected:
    void paintEvent(QPaintEvent *event);    //绘制事件
    void resizeEvent(QResizeEvent *event);  //大小重置事件
    void timerEvent(QTimerEvent *event);    //定时器事件
    void paintFlag(QPushButton *p_button, int x,int y,QIcon button_ico,int num);
private:
    struct {
        int x;
        int y;
    }offset_add;
    int cnt =0;
    QRect         m_drawArea;      //绘制区域
    int           m_pieRotate;     //扇形旋转区域
    int           m_timerId;       //定时器ID
    int           m_pointTimerId;  //变更点定时器
    int           m_nSpeed;        //速度
     int pre_x;
     int pre_y;
     int start_x;
     int start_y;
     int test_x =0;
     int r;
     int    vertical_line_x[12][2];   //竖线位置   (存放x轴坐标)
     int    vertical_line_y[12][2];   //竖线位置   (存放y轴坐标)
     int    row_line_x[3][2];    //横线位置  （存放x轴坐标）
     int    row_line_y[3][2];   //竖线位置   (存放y轴坐标)
     unsigned char line_cnt=0;
     double  vertical_line_x_start[12];  //垂直线的起始画
     double  vertical_line_y_start[12];//水平线的起始画弧
     int arc_vertical_start_end[12][2];
     int offset[5910][2];
     int arc_row_start_end[3][2];
     double  row_line_x_start[3];
     double  row_line_y_start[3];
    QList<QPoint> m_points;        //绘制点
    QList<int>    m_pointsAlapha;  //绘制点颜色alapha值
    QPushButton *p_button1 ;
    QPushButton *p_button2 ;
    QPushButton *p_button3 ;
    QPushButton *p_button4 ;
    QPushButton *p_button5 ;
    QPushButton *p_button6 ;
    QPushButton *p_button7 ;
    QPushButton *p_button8 ;
    QPushButton *p_button9 ;
    QPushButton *p_button10 ;
    QPushButton *p_button11 ;
    QPushButton *p_button12 ;
    QPushButton *p_button13 ;
    QPushButton *p_button14 ;
    QPushButton *p_button15 ;
    QPushButton *p_button_array[P_BUTTON_ARRAY];
    QPushButton *p_button_array1[P_BUTTON_ARRAY1];
    QPushButton *p_button_array2[P_BUTTON_ARRAY2];
    QPushButton *p_button_array3[P_BUTTON_ARRAY3];
    QPushButton *p_button_array4[P_BUTTON_ARRAY4];
    QPushButton *p_button_array5[P_BUTTON_ARRAY5];
    QPushButton *p_button_array6[P_BUTTON_ARRAY6];
    QPushButton *p_button_array7[P_BUTTON_ARRAY7];
    QPushButton *p_button_array8[P_BUTTON_ARRAY8];
    QPushButton *p_button_array9[P_BUTTON_ARRAY9];
    QPushButton *p_button_array10[P_BUTTON_ARRAY10];
    QPushButton *p_button_array11[P_BUTTON_ARRAY11];
    QPushButton *p_button_array12[P_BUTTON_ARRAY12];
    QPushButton *p_button_array13[P_BUTTON_ARRAY13];
    QPushButton *p_button_array14[P_BUTTON_ARRAY14];
    QPushButton *p_button_array15[P_BUTTON_ARRAY15];
    QPushButton *p_explain_button[P_EXPLAIN_NUM];
    QLabel *p_explain_qlable[P_EXPLAIN_NUM];
    QIcon button_icon[4];
    QPushButton *p_button_all[P_BUTTON_SUM];
};

#endif // CRADAR_H
