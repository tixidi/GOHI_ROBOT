#include "cradar.h"
#include <QPainter>
#include <QTimerEvent>
#include <QConicalGradient>
#include <qDebug>
#include "QFont"

CRadar::CRadar(QWidget *parent) : QWidget(parent)
{
    //初始化
    m_pieRotate = 0;
    m_timerId = -1;
    m_nSpeed = 50;
    for(int i=0;i<5000;i++){
        m_points<<QPoint();
        m_pointsAlapha<<100;
    }
//    m_points<<QPoint()<<QPoint()<<QPoint()<<QPoint()<<QPoint();
//    m_pointsAlapha<<100<<100<<100<<100<<100;
 //   this->setAttribute(Qt::WA_PaintOutsidePaintEvent);
    //启动定时器
    m_timerId = startTimer(m_nSpeed);
    m_pointTimerId = startTimer(1200);
    p_button1 =new QPushButton(parent);
    p_button2 =new QPushButton(parent);
    p_button3 =new QPushButton(parent);
    p_button4 =new QPushButton(parent);
    p_button5 =new QPushButton(parent);
    p_button6 =new QPushButton(parent);
    p_button7 =new QPushButton(parent);
    p_button8 =new QPushButton(parent);
    p_button9 =new QPushButton(parent);
    p_button10 =new QPushButton(parent);
    p_button11 =new QPushButton(parent);
    p_button12 =new QPushButton(parent);
    p_button13 =new QPushButton(parent);
    p_button14 =new QPushButton(parent);
    p_button15 =new QPushButton(parent);
    p_button_all[82] =p_button1;
    p_button_all[89] =p_button2;
    p_button_all[5] =p_button3;
    p_button_all[72] =p_button4;
    p_button_all[66] =p_button5;
    p_button_all[56] =p_button6;
    p_button_all[46] =p_button7;
    p_button_all[36] =p_button8;
    p_button_all[26] =p_button9;
    p_button_all[61] =p_button10;
    p_button_all[51] =p_button11;
    p_button_all[41] =p_button12;
    p_button_all[31] =p_button13;
    p_button_all[21] =p_button14;
    p_button_all[15] =p_button15;
    cnt =81;
    for(int i=0;i<P_BUTTON_ARRAY1;i++){
        p_button_array1[i] =new QPushButton(parent);
        p_button_all[cnt--] =p_button_array1[i];
    }
    cnt =90;
    for(int i=0;i<P_BUTTON_ARRAY3;i++){
        p_button_array3[i] =new QPushButton(parent);
        p_button_all[cnt++] =p_button_array3[i];
        if(cnt==P_BUTTON_SUM){
           cnt=0;
        }
    }
    cnt =14;
    for(int i=0;i<P_BUTTON_ARRAY2;i++){
        p_button_array2[i] =new QPushButton(parent);
        p_button_all[cnt--] =p_button_array2[i];
    }
    cnt =83;
    for(int i=0;i<P_BUTTON_ARRAY4;i++){
        p_button_array4[i] =new QPushButton(parent);
        p_button_all[cnt++] =p_button_array4[i];
    }
    cnt =71;
    for(int i=0;i<P_BUTTON_ARRAY5;i++){
        p_button_array5[i] =new QPushButton(parent);
        p_button_all[cnt--] =p_button_array5[i];
    }
    cnt =62;
    for(int i=0;i<P_BUTTON_ARRAY6;i++){
        p_button_array6[i] =new QPushButton(parent);
        p_button_all[cnt++] =p_button_array6[i];
    }
    cnt =60;
    for(int i=0;i<P_BUTTON_ARRAY7;i++){
        p_button_array7[i] =new QPushButton(parent);
        p_button_all[cnt--] =p_button_array7[i];
    }
    cnt =52;
    for(int i=0;i<P_BUTTON_ARRAY8;i++){
        p_button_array8[i] =new QPushButton(parent);
        p_button_all[cnt++] =p_button_array8[i];
    }
    cnt =50;
    for(int i=0;i<P_BUTTON_ARRAY9;i++){
        p_button_array9[i] =new QPushButton(parent);
        p_button_all[cnt--] =p_button_array9[i];
    }
    cnt =42;
    for(int i=0;i<P_BUTTON_ARRAY10;i++){
        p_button_array10[i] =new QPushButton(parent);
        p_button_all[cnt++] =p_button_array10[i];
    }
    cnt =40;
    for(int i=0;i<P_BUTTON_ARRAY11;i++){
        p_button_array11[i] =new QPushButton(parent);
        p_button_all[cnt--] =p_button_array11[i];
    }
    cnt =32;
    for(int i=0;i<P_BUTTON_ARRAY12;i++){
        p_button_array12[i] =new QPushButton(parent);
        p_button_all[cnt++] =p_button_array12[i];
    }
    cnt =30;
    for(int i=0;i<P_BUTTON_ARRAY13;i++){
        p_button_array13[i] =new QPushButton(parent);
        p_button_all[cnt--] =p_button_array13[i];
    }
    cnt =22;
    for(int i=0;i<P_BUTTON_ARRAY14;i++){
        p_button_array14[i] =new QPushButton(parent);
        p_button_all[cnt++] =p_button_array14[i];
    }
    cnt =20;
    for(int i=0;i<P_BUTTON_ARRAY15;i++){
        p_button_array15[i] =new QPushButton(parent);
        p_button_all[cnt--] =p_button_array15[i];
    }
    for(int i=1;i<P_EXPLAIN_NUM;i++){
        p_explain_button[i] =new QPushButton(parent);
        p_explain_qlable[i] =new QLabel(parent);
    }

  QFont ft;
  ft.setPointSize(2);

  QPalette pa;
  pa.setColor(QPalette::WindowText,Qt::red);

  p_explain_button[1]->setGeometry(EXPLAIN_FLAG+20+70,400,20,20);
  p_explain_button[1]->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
  p_explain_qlable[1]->setGeometry(EXPLAIN_FLAG+40+70,370,70,70);
  p_explain_qlable[1]->setFont(ft);
  p_explain_qlable[1]->setPalette(pa);
  p_explain_qlable[1]->setText("拐弯中");

  p_explain_button[2]->setGeometry(EXPLAIN_FLAG+20+190,400,15,15);
  p_explain_button[2]->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
  QIcon button_ico(":/new/botton/img/turn.png");
  p_explain_button[2]->setMinimumSize(15,15);
  p_explain_button[2]->setMaximumSize(15,15);
  p_explain_button[2]->setIcon(button_ico);
  p_explain_button[2]->setIconSize(QSize(15,15));
  p_explain_button[2]->setFlat(true);
  p_explain_qlable[2]->setGeometry(EXPLAIN_FLAG+40+190,370,70,70);
  p_explain_qlable[2]->setFont(ft);
  p_explain_qlable[2]->setPalette(pa);
  p_explain_qlable[2]->setText("拐弯点");

  p_explain_button[3]->setGeometry(EXPLAIN_FLAG+20,450,15,15);
  p_explain_button[3]->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
  QIcon button_ico1(":/new/botton/img/forward.PNG");
  p_explain_button[3]->setMinimumSize(15,15);
  p_explain_button[3]->setMaximumSize(15,15);
  p_explain_button[3]->setIcon(button_ico1);
  p_explain_button[3]->setIconSize(QSize(15,15));
  p_explain_button[3]->setFlat(true);
  p_explain_qlable[3]->setGeometry(EXPLAIN_FLAG+40,420,70,70);
  p_explain_qlable[3]->setFont(ft);
  p_explain_qlable[3]->setPalette(pa);
  p_explain_qlable[3]->setText("直行点");

  p_explain_button[4]->setGeometry(EXPLAIN_FLAG+20+150,450,15,15);
  p_explain_button[4]->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
  QIcon button_ico2(":/new/botton/img/start.png");
  p_explain_button[4]->setMinimumSize(15,15);
  p_explain_button[4]->setMaximumSize(15,15);
  p_explain_button[4]->setIcon(button_ico2);
  p_explain_button[4]->setIconSize(QSize(15,15));
  p_explain_button[4]->setFlat(true);
  p_explain_qlable[4]->setGeometry(EXPLAIN_FLAG+40+150,420,70,70);
  p_explain_qlable[4]->setFont(ft);
  p_explain_qlable[4]->setPalette(pa);
  p_explain_qlable[4]->setText("起始点");

  p_explain_button[5]->setGeometry(EXPLAIN_FLAG+20+270,450,15,15);
  p_explain_button[5]->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
  QIcon button_ico3(":/new/botton/img/help-about.png");
  p_explain_button[5]->setMinimumSize(PICTURE_SIZE,PICTURE_SIZE);
  p_explain_button[5]->setMaximumSize(PICTURE_SIZE,PICTURE_SIZE);
  p_explain_button[5]->setIcon(button_ico3);
  p_explain_button[5]->setIconSize(QSize(PICTURE_SIZE,PICTURE_SIZE));
  p_explain_button[5]->setFlat(true);
  p_explain_qlable[5]->setGeometry(EXPLAIN_FLAG+40+270,420,70,70);
  p_explain_qlable[5]->setFont(ft);
  p_explain_qlable[5]->setPalette(pa);
  p_explain_qlable[5]->setText("校准点");
  button_icon[0]=button_ico;  //拐弯
  button_icon[1]=button_ico3;  //检验
  button_icon[2]=button_ico1;  //直行
  button_icon[3]=button_ico2;  //起始
  cnt =P_BUTTON_SUM;
}


void CRadar::timerOutFunc(void){
    if(cnt==P_BUTTON_SUM){
        cnt =0;
    }
    if(cnt==0){
        p_button_all[P_BUTTON_SUM-1]->show();
        p_button_all[cnt]->hide();
    }else{
        p_button_all[cnt]->hide();
        p_button_all[cnt-1]->show();
    }
    cnt++;
}



void CRadar::paintFlag(QPushButton *p_button, int x,int y,QIcon button_ico,int num){
    if(num == 1){
        p_button->setGeometry(x,y,10,10);
        p_button->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
        p_button->setMinimumSize(PICTURE_SIZE,PICTURE_SIZE);
        p_button->setMaximumSize(PICTURE_SIZE,PICTURE_SIZE);
        p_button->setIcon(button_ico);
        p_button->setIconSize(QSize(PICTURE_SIZE,PICTURE_SIZE));
        p_button->setFlat(true);
    }else{
        p_button->setGeometry(x,y,10,10);
        p_button->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
        p_button->setMinimumSize(15,15);
        p_button->setMaximumSize(15,15);
        p_button->setIcon(button_ico);
        p_button->setIconSize(QSize(15,15));
        p_button->setFlat(true);
    }

}
void CRadar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    //抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);

//    //背景
//    painter.fillRect(rect(),QColor(15,45,188));
    //设置背景图片
     this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
     QPalette palette = this->palette();
     palette.setBrush(QPalette::Window,
             QBrush(QPixmap(":/img/huise.jpg").scaled(// 缩放背景图.
                 this->size(),
                 Qt::IgnoreAspectRatio,
                 Qt::SmoothTransformation)));             // 使用平滑的缩放方式
     this->setPalette(palette);                           // 给widget加上背景图
    //边长
    int len = m_drawArea.width();
    int wide= m_drawArea.height();



    //底盘(x轴、y轴和3个圆)
    //-----------------------------------------------水平直线--------------------------------------------------------------
    painter.setPen(QPen(Qt::black));
//    painter.drawLine( QPoint(10,20), QPoint(20,10));
    painter.drawLine( QPoint(m_drawArea.topLeft().x()-len/10,1*len/10), QPoint(m_drawArea.topRight().x()-60,1*len/10));
    for(int i=0;i<P_BUTTON_ARRAY1;i++){
        p_button_array1[i]->setGeometry(m_drawArea.topLeft().x()-len/10+DISTANCE*i+10,1*len/10-10,10,10);
        p_button_array1[i]->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
        paintFlag(p_button_array1[i],m_drawArea.topLeft().x()-len/10+DISTANCE*i+10,1*len/10-15,button_icon[1],1);
    }
    paintFlag(p_button_array1[0],m_drawArea.topLeft().x()-len/10+10,1*len/10-15,button_icon[0],0);
    paintFlag(p_button_array1[8],m_drawArea.topLeft().x()-len/10+DISTANCE*8+10,1*len/10-15,button_icon[2],2);
    row_line_x[0][0] =m_drawArea.topLeft().x()-len/10;
    row_line_x[0][1] =m_drawArea.topRight().x()-60;
    row_line_y[0][0] =1*len/10;
    row_line_y[0][1] =1*len/10;


    painter.drawLine( QPoint(m_drawArea.topLeft().x()-len/10+28,7*len/10), QPoint(m_drawArea.topRight().x()-60,7*len/10));
    for(int i=0;i<P_BUTTON_ARRAY2;i++){
        p_button_array2[i]->setGeometry(m_drawArea.topLeft().x()-len/10+DISTANCE*i+28,7*len/10,10,10);
        p_button_array2[i]->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
        paintFlag(p_button_array2[i],m_drawArea.topLeft().x()-len/10+DISTANCE*i+28,7*len/10+5,button_icon[1],1);
    }
    paintFlag(p_button_array2[0],m_drawArea.topLeft().x()-len/10+28,7*len/10+5,button_icon[0],0);
    paintFlag(p_button_array2[8],m_drawArea.topLeft().x()-len/10+DISTANCE*8+28,7*len/10+5,button_icon[2],2);
    row_line_x[1][0] =m_drawArea.topLeft().x()-len/10+28;
    row_line_x[1][1] =m_drawArea.topRight().x()-60;
    row_line_y[1][0] =7*len/10;
    row_line_y[1][1] =7*len/10;

    painter.drawLine( QPoint(m_drawArea.topLeft().x()-len/10,8*len/10), QPoint(m_drawArea.topRight().x()-60,8*len/10));
    for(int i=0;i<P_BUTTON_ARRAY3;i++){
        p_button_array3[i]->setGeometry(m_drawArea.topLeft().x()-len/10+DISTANCE*i+20,8*len/10,10,10);
        p_button_array3[i]->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
        paintFlag(p_button_array3[i],m_drawArea.topLeft().x()-len/10+DISTANCE*i+10,8*len/10+5,button_icon[1],1);
    }
    paintFlag(p_button_array3[0],m_drawArea.topLeft().x()-len/10+10,8*len/10+5,button_icon[2],2);
    paintFlag(p_button_array3[8],m_drawArea.topLeft().x()-len/10+DISTANCE*8+10,8*len/10+5,button_icon[0],0);
    paintFlag(p_button_array3[4],m_drawArea.topLeft().x()-len/10+DISTANCE*4+10,8*len/10+5,button_icon[3],3);
    pre_x =m_drawArea.topLeft().x()-len/10+DISTANCE*4+10;
    pre_y =8*len/10;
    start_x =pre_x;
    start_y =pre_y;
    row_line_x[2][0] =m_drawArea.topLeft().x()-len/10;
    row_line_x[2][1] =m_drawArea.topRight().x()-60;
    row_line_y[2][0] =8*len/10;
    row_line_y[2][1] =8*len/10;

//    qDebug()<<"m_drawArea.topLeft().x() ="<< m_drawArea.topLeft().x();
//    qDebug()<<"m_drawArea.topRight().x() ="<< m_drawArea.topRight().x();
//    painter.drawLine( QPoint(m_drawArea.topLeft().x()+len/10,9*len/10), QPoint(m_drawArea.topRight().x()-60,9*len/10));
//    painter.drawLine( QPoint(m_drawArea.topLeft().x()+len/10,len), QPoint(m_drawArea.topRight().x()-30,len));
    //-----------------------------------------------竖直直线--------------------------------------------------------------
    painter.drawLine( QPoint(m_drawArea.topLeft().x()-3*len/20,3*len/20), QPoint(m_drawArea.topLeft().x()-3*len/20,7*len/10+len/20));
    for(int i=0;i<P_BUTTON_ARRAY4;i++){
        p_button_array4[i]->setGeometry(m_drawArea.topLeft().x()-3*len/20-10,3*len/20+DISTANCE*i,10,10);
        p_button_array4[i]->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
        paintFlag(p_button_array4[i],m_drawArea.topLeft().x()-3*len/20-20,3*len/20+DISTANCE*i,button_icon[1],1);
    }
    paintFlag(p_button_array4[0],m_drawArea.topLeft().x()-3*len/20-20,3*len/20,button_icon[2],2);
    paintFlag(p_button_array4[5],m_drawArea.topLeft().x()-3*len/20-20,3*len/20+DISTANCE*5,button_icon[0],0);
    vertical_line_x[0][0] =m_drawArea.topLeft().x()-3*len/20;
    vertical_line_x[0][1] =m_drawArea.topLeft().x()-3*len/20;
    vertical_line_y[0][0] =3*len/20;
    vertical_line_y[0][1] =7*len/10+len/20;

    painter.drawLine( QPoint(m_drawArea.topRight().x()-60+len/20,3*len/20), QPoint(m_drawArea.topRight().x()-60+len/20,6*len/10));
    for(int i=0;i<P_BUTTON_ARRAY5;i++){
        p_button_array5[i]->setGeometry(m_drawArea.topRight().x()-60+len/20-10,3*len/20+DISTANCE*i,10,10);
        p_button_array5[i]->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
          paintFlag( p_button_array5[i],m_drawArea.topRight().x()-60+len/20-15,3*len/20+DISTANCE*i,button_icon[1],1);

     }
    paintFlag(p_button_array5[4],m_drawArea.topRight().x()-60+len/20-20,3*len/20+DISTANCE*4,button_icon[2],2);
    paintFlag(p_button_array5[0],m_drawArea.topRight().x()-60+len/20-20,3*len/20,button_icon[0],0);
    vertical_line_x[11][0] =m_drawArea.topRight().x()-60+len/20;
    vertical_line_x[11][1] =m_drawArea.topRight().x()-60+len/20;
    vertical_line_y[11][0] =3*len/20;
    vertical_line_y[11][1] =6*len/10;

    painter.drawLine( QPoint(m_drawArea.topRight().x()-60+len/20-len/10,4*len/20), QPoint(m_drawArea.topRight().x()-60+len/20-len/10,6*len/10));
    for(int i=0;i<P_BUTTON_ARRAY6;i++){
        p_button_array6[i]->setGeometry(m_drawArea.topRight().x()-60+len/20-len/10-10,4*len/20+DISTANCE*i,10,10);
        p_button_array6[i]->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");

           paintFlag( p_button_array6[i],m_drawArea.topRight().x()-60+len/20-len/10-15,4*len/20+DISTANCE*i,button_icon[1],1);
    }
    paintFlag(p_button_array6[0],m_drawArea.topRight().x()-60+len/20-len/10-15,4*len/20+DISTANCE*0,button_icon[2],2);
    paintFlag(p_button_array6[3],m_drawArea.topRight().x()-60+len/20-len/10-15,4*len/20+DISTANCE*3,button_icon[0],0);
    vertical_line_x[10][0] =m_drawArea.topRight().x()-60+len/20-len/10;
    vertical_line_x[10][1] =m_drawArea.topRight().x()-60+len/20-len/10;
    vertical_line_y[10][0] =4*len/20;
    vertical_line_y[10][1] =6*len/10;

    painter.drawLine( QPoint(m_drawArea.topRight().x()-60+len/20-2*len/10,4*len/20), QPoint(m_drawArea.topRight().x()-60+len/20-2*len/10,6*len/10));
    for(int i=0;i<P_BUTTON_ARRAY7;i++){
        p_button_array7[i]->setGeometry(m_drawArea.topRight().x()-60+len/20-2*len/10-10,4*len/20+DISTANCE*i,10,10);
        p_button_array7[i]->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
        paintFlag( p_button_array7[i],m_drawArea.topRight().x()-60+len/20-2*len/10-15,4*len/20+DISTANCE*i,button_icon[1],1);
    }
    paintFlag(p_button_array7[0],m_drawArea.topRight().x()-60+len/20-2*len/10-15,4*len/20+DISTANCE*0,button_icon[0],0);
    paintFlag(p_button_array7[3],m_drawArea.topRight().x()-60+len/20-2*len/10-15,4*len/20+DISTANCE*3,button_icon[2],2);
    vertical_line_x[9][0] =m_drawArea.topRight().x()-60+len/20-2*len/10;
    vertical_line_x[9][1] =m_drawArea.topRight().x()-60+len/20-2*len/10;
    vertical_line_y[9][0] =4*len/20;
    vertical_line_y[9][1] =6*len/10;

    painter.drawLine( QPoint(m_drawArea.topRight().x()-60+len/20-3*len/10,4*len/20), QPoint(m_drawArea.topRight().x()-60+len/20-3*len/10,6*len/10));
    for(int i=0;i<P_BUTTON_ARRAY8;i++){
        p_button_array8[i]->setGeometry(m_drawArea.topRight().x()-60+len/20-3*len/10-10,4*len/20+DISTANCE*i,10,10);
        p_button_array8[i]->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
           paintFlag( p_button_array8[i],m_drawArea.topRight().x()-60+len/20-3*len/10-15,4*len/20+DISTANCE*i,button_icon[1],1);
    }
    paintFlag(p_button_array8[0],m_drawArea.topRight().x()-60+len/20-3*len/10-15,4*len/20+DISTANCE*0,button_icon[2],2);
    paintFlag(p_button_array8[3],m_drawArea.topRight().x()-60+len/20-3*len/10-15,4*len/20+DISTANCE*3,button_icon[0],0);
    vertical_line_x[8][0] =m_drawArea.topRight().x()-60+len/20-3*len/10;
    vertical_line_x[8][1] =m_drawArea.topRight().x()-60+len/20-3*len/10;
    vertical_line_y[8][0] =4*len/20;
    vertical_line_y[8][1] =6*len/10;
    //-----
    painter.drawLine( QPoint(m_drawArea.topRight().x()-60+len/20-4*len/10,4*len/20), QPoint(m_drawArea.topRight().x()-60+len/20-4*len/10,6*len/10));
    for(int i=0;i<P_BUTTON_ARRAY9;i++){
        p_button_array9[i]->setGeometry(m_drawArea.topRight().x()-60+len/20-4*len/10-10,4*len/20+DISTANCE*i,10,10);
        p_button_array9[i]->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
          paintFlag( p_button_array9[i],m_drawArea.topRight().x()-60+len/20-4*len/10-15,4*len/20+DISTANCE*i,button_icon[1],1);
    }
    paintFlag(p_button_array9[0],m_drawArea.topRight().x()-60+len/20-4*len/10-15,4*len/20+DISTANCE*0,button_icon[0],0);
    paintFlag(p_button_array9[3],m_drawArea.topRight().x()-60+len/20-4*len/10-15,4*len/20+DISTANCE*3,button_icon[2],2);
    vertical_line_x[7][0] =m_drawArea.topRight().x()-60+len/20-4*len/10;
    vertical_line_x[7][1] =m_drawArea.topRight().x()-60+len/20-4*len/10;
    vertical_line_y[7][0] =4*len/20;
    vertical_line_y[7][1] =6*len/10;

    painter.drawLine( QPoint(m_drawArea.topRight().x()-60+len/20-5*len/10,4*len/20), QPoint(m_drawArea.topRight().x()-60+len/20-5*len/10,6*len/10));
    for(int i=0;i<P_BUTTON_ARRAY10;i++){
        p_button_array10[i]->setGeometry(m_drawArea.topRight().x()-60+len/20-5*len/10-10,4*len/20+DISTANCE*i,10,10);
        p_button_array10[i]->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
          paintFlag(p_button_array10[i],m_drawArea.topRight().x()-60+len/20-5*len/10-15,4*len/20+DISTANCE*i,button_icon[1],1);
    }
    paintFlag(p_button_array10[0],m_drawArea.topRight().x()-60+len/20-5*len/10-15,4*len/20+DISTANCE*0,button_icon[2],2);
    paintFlag(p_button_array10[3],m_drawArea.topRight().x()-60+len/20-5*len/10-15,4*len/20+DISTANCE*3,button_icon[0],0);
    vertical_line_x[6][0] =m_drawArea.topRight().x()-60+len/20-5*len/10;
    vertical_line_x[6][1] =m_drawArea.topRight().x()-60+len/20-5*len/10;
    vertical_line_y[6][0] =4*len/20;
    vertical_line_y[6][1] =6*len/10;

    painter.drawLine( QPoint(m_drawArea.topRight().x()-60+len/20-6*len/10,4*len/20), QPoint(m_drawArea.topRight().x()-60+len/20-6*len/10,6*len/10));
    for(int i=0;i<P_BUTTON_ARRAY11;i++){
        p_button_array11[i]->setGeometry(m_drawArea.topRight().x()-60+len/20-6*len/10-10,4*len/20+DISTANCE*i,10,10);
        p_button_array11[i]->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
          paintFlag(p_button_array11[i],m_drawArea.topRight().x()-60+len/20-6*len/10-15,4*len/20+DISTANCE*i,button_icon[1],1);
    }
    paintFlag(p_button_array11[0],m_drawArea.topRight().x()-60+len/20-6*len/10-15,4*len/20+DISTANCE*0,button_icon[0],0);
    paintFlag(p_button_array11[3],m_drawArea.topRight().x()-60+len/20-6*len/10-15,4*len/20+DISTANCE*3,button_icon[2],2);
    vertical_line_x[5][0] =m_drawArea.topRight().x()-60+len/20-6*len/10;
    vertical_line_x[5][1] =m_drawArea.topRight().x()-60+len/20-6*len/10;
    vertical_line_y[5][0] =4*len/20;
    vertical_line_y[5][1] =6*len/10;

    painter.drawLine( QPoint(m_drawArea.topRight().x()-60+len/20-7*len/10,4*len/20), QPoint(m_drawArea.topRight().x()-60+len/20-7*len/10,6*len/10));
    for(int i=0;i<P_BUTTON_ARRAY12;i++){
        p_button_array12[i]->setGeometry(m_drawArea.topRight().x()-60+len/20-7*len/10-10,4*len/20+DISTANCE*i,10,10);
        p_button_array12[i]->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
          paintFlag(p_button_array12[i],m_drawArea.topRight().x()-60+len/20-7*len/10-15,4*len/20+DISTANCE*i,button_icon[1],1);
    }
    paintFlag(p_button_array12[0],m_drawArea.topRight().x()-60+len/20-7*len/10-15,4*len/20+DISTANCE*0,button_icon[2],2);
    paintFlag(p_button_array12[3],m_drawArea.topRight().x()-60+len/20-7*len/10-15,4*len/20+DISTANCE*3,button_icon[0],2);
    vertical_line_x[4][0] =m_drawArea.topRight().x()-60+len/20-7*len/10;
    vertical_line_x[4][1] =m_drawArea.topRight().x()-60+len/20-7*len/10;
    vertical_line_y[4][0] =4*len/20;
    vertical_line_y[4][1] =6*len/10;

    painter.drawLine( QPoint(m_drawArea.topRight().x()-60+len/20-8*len/10,4*len/20), QPoint(m_drawArea.topRight().x()-60+len/20-8*len/10,6*len/10));
    for(int i=0;i<P_BUTTON_ARRAY13;i++){
        p_button_array13[i]->setGeometry(m_drawArea.topRight().x()-60+len/20-8*len/10-10,4*len/20+DISTANCE*i,10,10);
        p_button_array13[i]->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
           paintFlag(p_button_array13[i],m_drawArea.topRight().x()-60+len/20-8*len/10-15,4*len/20+DISTANCE*i,button_icon[1],1);
    }
    paintFlag(p_button_array13[0],m_drawArea.topRight().x()-60+len/20-8*len/10-15,4*len/20+DISTANCE*0,button_icon[0],0);
    paintFlag(p_button_array13[3],m_drawArea.topRight().x()-60+len/20-8*len/10-15,4*len/20+DISTANCE*3,button_icon[2],2);
    vertical_line_x[3][0] =m_drawArea.topRight().x()-60+len/20-8*len/10;
    vertical_line_x[3][1] =m_drawArea.topRight().x()-60+len/20-8*len/10;
    vertical_line_y[3][0] =4*len/20;
    vertical_line_y[3][1] =6*len/10;

    painter.drawLine( QPoint(m_drawArea.topRight().x()-60+len/20-9*len/10,4*len/20), QPoint(m_drawArea.topRight().x()-60+len/20-9*len/10,6*len/10));
    for(int i=0;i<P_BUTTON_ARRAY14;i++){
        p_button_array14[i]->setGeometry(m_drawArea.topRight().x()-60+len/20-9*len/10-10,4*len/20+DISTANCE*i,10,10);
        p_button_array14[i]->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
           paintFlag(p_button_array14[i],m_drawArea.topRight().x()-60+len/20-9*len/10-15,4*len/20+DISTANCE*i,button_icon[1],1);
    }
    paintFlag(p_button_array14[0],m_drawArea.topRight().x()-60+len/20-9*len/10-15,4*len/20+DISTANCE*0,button_icon[2],2);
    paintFlag(p_button_array14[3],m_drawArea.topRight().x()-60+len/20-9*len/10-15,4*len/20+DISTANCE*3,button_icon[0],0);
    vertical_line_x[2][0] =m_drawArea.topRight().x()-60+len/20-9*len/10;
    vertical_line_x[2][1] =m_drawArea.topRight().x()-60+len/20-9*len/10;
    vertical_line_y[2][0] =4*len/20;
    vertical_line_y[2][1] =6*len/10;

    painter.drawLine( QPoint(m_drawArea.topRight().x()-60+len/20-10*len/10,4*len/20), QPoint(m_drawArea.topRight().x()-60+len/20-10*len/10,6*len/10+len/20));
    for(int i=0;i<P_BUTTON_ARRAY15;i++){
        p_button_array15[i]->setGeometry(m_drawArea.topRight().x()-60+len/20-10*len/10-10,4*len/20+DISTANCE*i,10,10);
        p_button_array15[i]->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
          paintFlag(p_button_array15[i],m_drawArea.topRight().x()-60+len/20-10*len/10-15,4*len/20+DISTANCE*i,button_icon[1],1);

    }
    paintFlag(p_button_array15[0],m_drawArea.topRight().x()-60+len/20-10*len/10-15,4*len/20+DISTANCE*0,button_icon[0],0);
    paintFlag(p_button_array15[4],m_drawArea.topRight().x()-60+len/20-10*len/10-15,4*len/20+DISTANCE*4,button_icon[2],2);
    vertical_line_x[1][0] =m_drawArea.topRight().x()-60+len/20-10*len/10;
    vertical_line_x[1][1] =m_drawArea.topRight().x()-60+len/20-10*len/10;
    vertical_line_y[1][0] =4*len/20;
    vertical_line_y[1][1] =6*len/10+len/20;
    //    //三个参数：rect表示弧线所在的矩形，startAngle起始角度，spanAngle跨越角度
//    painter.drawArc(rect, startAngle, spanAngle);
    painter.setPen(QPen(Qt::red));
    painter.setPen(QPen(QColor(255,0,0,255),3));
    painter.drawPoint(m_drawArea.topLeft().x()+len/20,len/10);
    painter.drawPoint(m_drawArea.topLeft().x()+len/20,0);
    painter.drawPoint(m_drawArea.topLeft().x()+0,0);

    painter.setPen(QPen(QColor(0,0,255,255),3));

 //-----------------------------------------弧线---------------------------------------------------------
    painter.setPen(QPen(Qt::black));
    QRectF rect(m_drawArea.topLeft().x()-3*len/20,1*len/10, len/10, len/10); //x,y,w,h
    int startAngle =90*16; //值为，实际角度 * 16
    int spanAngle = 90*16;
    painter.drawArc(rect, startAngle, spanAngle);
    p_button1->setGeometry(m_drawArea.topLeft().x()-3*len/20-10,1*len/10-10,20,20);
    p_button1->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;font-family:'Microsoft YaHei';font-size:8px;color:#666666;");
    p_button1->setText("82");
    row_line_x_start[2] =m_drawArea.topLeft().x()-3*len/20;
    row_line_y_start[2] =1*len/10;
    arc_row_start_end[2][0] =90;
    arc_row_start_end[2][1] =90;

    QRectF rect1(m_drawArea.topLeft().x()-3*len/20,7*len/10, len/10, len/10); //x,y,w,h
    int startAngle1 =180*16; //值为，实际角度 * 16   起始角度
    int spanAngle1 = 90*16;   //跨越角度
    painter.drawArc(rect1, startAngle1, spanAngle1);
    p_button2->setGeometry(m_drawArea.topLeft().x()-3*len/20-15,7*len/10+30,20,20);
    p_button2->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;font-family:'Microsoft YaHei';font-size:8px;color:#666666;");
    p_button2->setText("89");
    vertical_line_x_start[11] =m_drawArea.topLeft().x()-3*len/20;
    vertical_line_y_start[11] =7*len/10;
    arc_vertical_start_end[11][0] =180;
    arc_vertical_start_end[11][1] =90;

    QRectF rect2(m_drawArea.topRight().x()-60-len/20,8*len/10-len/10, len/10, len/10); //x,y,w,h
    int startAngle2 =-90*16; //值为，实际角度 * 16
    int spanAngle2 = 180*16;
    painter.drawArc(rect2, startAngle2, spanAngle2);
    p_button3->setGeometry(m_drawArea.topRight().x()-60-len/20+45,8*len/10-len/10+15,20,20);
    p_button3->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;font-family:'Microsoft YaHei';font-size:8px;color:#666666;");
    p_button3->setText("5");
    row_line_x_start[0] =m_drawArea.topRight().x()-60-len/20;
    row_line_y_start[0] =8*len/10-len/10;
    arc_row_start_end[0][0] =-90;
    arc_row_start_end[0][1] =180;

    QRectF rect3(m_drawArea.topRight().x()-60-len/20,1*len/10, len/10, len/10); //x,y,w,h
    int startAngle3 =0*16; //值为，实际角度 * 16
    int spanAngle3 = 90*16;
    painter.drawArc(rect3, startAngle3, spanAngle3);
    p_button4->setGeometry(m_drawArea.topRight().x()-60-len/20+35,1*len/10-12,20,20);
    p_button4->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;font-family:'Microsoft YaHei';font-size:8px;color:#666666;");
    p_button4->setText("72");
    vertical_line_x_start[10] =m_drawArea.topRight().x()-60-len/20;
    vertical_line_y_start[10] =1*len/10;
    arc_vertical_start_end[10][0] =0;
    arc_vertical_start_end[10][1] =90;

    QRectF rect4(m_drawArea.topRight().x()-60+len/20-len/10,6*len/10-len/20, len/10, len/10); //x,y,w,h
    int startAngle4 =0*16; //值为，实际角度 * 16
    int spanAngle4 = -180*16;
    painter.drawArc(rect4, startAngle4, spanAngle4);
    p_button5->setGeometry(m_drawArea.topRight().x()-60+len/20-len/10+10,6*len/10-len/20+45,20,20);
    p_button5->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;font-family:'Microsoft YaHei';font-size:8px;color:#666666;");
    p_button5->setText("66");
    vertical_line_x_start[9] =m_drawArea.topRight().x()-60-len/20-len/10-0.6;
    vertical_line_y_start[9] =2*len/10-len/20;
    arc_vertical_start_end[9][0] =0;
    arc_vertical_start_end[9][1] =-180;


    QRectF rect5(m_drawArea.topRight().x()-60+len/20-3*len/10,6*len/10-len/20, len/10, len/10); //x,y,w,h
    int startAngle5 =0*16; //值为，实际角度 * 16
    int spanAngle5 = -180*16;
    painter.drawArc(rect5, startAngle5, spanAngle5);
    p_button6->setGeometry(m_drawArea.topRight().x()-60+len/20-3*len/10+10,6*len/10-len/20+45,20,20);
    p_button6->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;font-family:'Microsoft YaHei';font-size:8px;color:#666666;");
    p_button6->setText("56");
    vertical_line_x_start[7] =m_drawArea.topRight().x()-60+len/20-3*len/10;
    vertical_line_y_start[7] =6*len/10-len/20;
    arc_vertical_start_end[7][0] =0;
    arc_vertical_start_end[7][1] =-180;

    QRectF rect6(m_drawArea.topRight().x()-60+len/20-5*len/10,6*len/10-len/20, len/10, len/10); //x,y,w,h
    int startAngle6 =0*16; //值为，实际角度 * 16
    int spanAngle6 = -180*16;
    painter.drawArc(rect6, startAngle6, spanAngle6);
    p_button7->setGeometry(m_drawArea.topRight().x()-60+len/20-5*len/10+10,6*len/10-len/20+45,20,20);
    p_button7->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;font-family:'Microsoft YaHei';font-size:8px;color:#666666;");
    p_button7->setText("46");
    vertical_line_x_start[5] =m_drawArea.topRight().x()-60+len/20-5*len/10;
    vertical_line_y_start[5] =6*len/10-len/20;
    arc_vertical_start_end[5][0] =0;
    arc_vertical_start_end[5][1] =-180;

    QRectF rect7(m_drawArea.topRight().x()-60+len/20-7*len/10,6*len/10-len/20, len/10, len/10); //x,y,w,h
    int startAngle7 =0*16; //值为，实际角度 * 16
    int spanAngle7 = -180*16;
    painter.drawArc(rect7, startAngle7, spanAngle7);
    p_button8->setGeometry(m_drawArea.topRight().x()-60+len/20-7*len/10+10,6*len/10-len/20+45,20,20);
    p_button8->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;font-family:'Microsoft YaHei';font-size:8px;color:#666666;");
    p_button8->setText("36");
    vertical_line_x_start[3] =m_drawArea.topRight().x()-60+len/20-7*len/10;
    vertical_line_y_start[3] =6*len/10-len/20;
    arc_vertical_start_end[3][0] =0;
    arc_vertical_start_end[3][1] =-180;

    QRectF rect8(m_drawArea.topRight().x()-60+len/20-9*len/10,6*len/10-len/20, len/10, len/10); //x,y,w,h
    int startAngle8 =0*16; //值为，实际角度 * 16
    int spanAngle8 = -180*16;
    painter.drawArc(rect8, startAngle8, spanAngle8);
    p_button9->setGeometry(m_drawArea.topRight().x()-60+len/20-9*len/10+10,6*len/10-len/20+45,20,20);
    p_button9->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;font-family:'Microsoft YaHei';font-size:8px;color:#666666;");
    p_button9->setText("26");
    vertical_line_x_start[1] =m_drawArea.topRight().x()-60+len/20-9*len/10;
    vertical_line_y_start[1] =6*len/10-len/20;
    arc_vertical_start_end[1][0] =0;
    arc_vertical_start_end[1][1] =-180;

    QRectF rect9(m_drawArea.topRight().x()-60-len/20-len/10-0.6,2*len/10-len/20, len/10, len/10); //x,y,w,h
    int startAngle9 =0*16; //值为，实际角度 * 16
    int spanAngle9 = 180*16;
    painter.drawArc(rect9, startAngle9, spanAngle9);
    p_button10->setGeometry(m_drawArea.topRight().x()-60-len/20-len/10-0.6+13,2*len/10-len/20-20,20,20);
    p_button10->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;font-family:'Microsoft YaHei';font-size:8px;color:#666666;");
    p_button10->setText("61");
    vertical_line_x_start[8] =m_drawArea.topRight().x()-60-len/20-len/10-0.6;
    vertical_line_y_start[8] =2*len/10-len/20;
    arc_vertical_start_end[8][0] =0;
    arc_vertical_start_end[8][1] =180;

    QRectF rect10(m_drawArea.topRight().x()-60-len/20-len/10-2*len/10-1.4,2*len/10-len/20, len/10, len/10); //x,y,w,h
    int startAngle10 =0*16; //值为，实际角度 * 16
    int spanAngle10 = 180*16;
    painter.drawArc(rect10, startAngle10, spanAngle10);
    p_button11->setGeometry(m_drawArea.topRight().x()-60-len/20-len/10-2*len/10-1.4+13,2*len/10-len/20-20,20,20);
    p_button11->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;font-family:'Microsoft YaHei';font-size:8px;color:#666666;");
    p_button11->setText("51");
    vertical_line_x_start[6] =m_drawArea.topRight().x()-60-len/20-len/10-2*len/10-1.4;
    vertical_line_y_start[6] =2*len/10-len/20;
    arc_vertical_start_end[6][0] =0;
    arc_vertical_start_end[6][1] =180;

    QRectF rect11(m_drawArea.topRight().x()-60-len/20-len/10-4*len/10-1.5,2*len/10-len/20, len/10, len/10); //x,y,w,h
    int startAngle11 =0*16; //值为，实际角度 * 16
    int spanAngle11 = 180*16;
    painter.drawArc(rect11, startAngle11, spanAngle11);
    p_button12->setGeometry(m_drawArea.topRight().x()-60-len/20-len/10-4*len/10-1.5+13,2*len/10-len/20-20,20,20);
    p_button12->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;font-family:'Microsoft YaHei';font-size:8px;color:#666666;");
    p_button12->setText("41");
    vertical_line_x_start[4] =m_drawArea.topRight().x()-60-len/20-len/10-4*len/10-1.5;
    vertical_line_y_start[4] =2*len/10-len/20;
    arc_vertical_start_end[4][0] =0;
    arc_vertical_start_end[4][1] =180;

    QRectF rect12(m_drawArea.topRight().x()-60-len/20-len/10-6*len/10-1.7,2*len/10-len/20, len/10, len/10); //x,y,w,h
    int startAngle12 =0*16; //值为，实际角度 * 16
    int spanAngle12 = 180*16;
    painter.drawArc(rect12, startAngle12, spanAngle12);
    p_button13->setGeometry(m_drawArea.topRight().x()-60-len/20-len/10-6*len/10-1.7+13,2*len/10-len/20-20,20,20);
    p_button13->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;font-family:'Microsoft YaHei';font-size:8px;color:#666666;");
    p_button13->setText("31");
    vertical_line_x_start[2] =m_drawArea.topRight().x()-60-len/20-len/10-6*len/10-1.7;
    vertical_line_y_start[2] =2*len/10-len/20;
    arc_vertical_start_end[2][0] =0;
    arc_vertical_start_end[2][1] =180;

    QRectF rect13(m_drawArea.topRight().x()-60-len/20-len/10-8*len/10-1.8,2*len/10-len/20, len/10, len/10); //x,y,w,h
    int startAngle13 =0*16; //值为，实际角度 * 16
    int spanAngle13 = 180*16;
    painter.drawArc(rect13, startAngle13, spanAngle13);
    p_button14->setGeometry(m_drawArea.topRight().x()-60-len/20-len/10-8*len/10-1.8+13,2*len/10-len/20-20,20,20);
    p_button14->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;font-family:'Microsoft YaHei';font-size:8px;color:#666666;");
    p_button14->setText("21");
    vertical_line_x_start[0] =m_drawArea.topRight().x()-60-len/20-len/10-8*len/10-1.8;
    vertical_line_y_start[0] =2*len/10-len/20;
    arc_vertical_start_end[0][0] =0;
    arc_vertical_start_end[0][1] =180;

    QRectF rect14(m_drawArea.topLeft().x()-3*len/20+len/20+6,6*len/10, len/10, len/10); //x,y,w,h
    int startAngle14 =180*16; //值为，实际角度 * 16
    int spanAngle14 = 90*16;
    painter.drawArc(rect14, startAngle14, spanAngle14);
    p_button15->setGeometry(m_drawArea.topLeft().x()-3*len/20+len/20+6-10,6*len/10+35,20,20);
    p_button15->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;font-family:'Microsoft YaHei';font-size:8px;color:#666666;");
    p_button15->setText("15");
    row_line_x_start[1] =m_drawArea.topLeft().x()-3*len/20+len/20+6;
    row_line_y_start[1] =6*len/10;
    arc_row_start_end[1][0] =180;
    arc_row_start_end[1][1] =90;
    r =len/10/2;
    //装饰-随机点
   for(int i = 0; i < m_points.count(); ++i)
    {
        int colorAlaph = m_pointsAlapha.at(i);
        painter.setPen(QPen(QColor(255,255,0,colorAlaph),3));
        painter.drawPoint(m_points.at(i));
    }
//    //更详细解释参考：http://fearlazy.com/index.php/post/31.html
}



void CRadar::resizeEvent(QResizeEvent *event)
{
    //以较短的边长作为绘制区域边长
    if(width() > height())
    {
        m_drawArea = QRect((width() - height())/2,0,height(),height());
    }
    else
    {
        m_drawArea = QRect(0,(height() - width())/2,width(),width());
    }

    m_drawArea.adjust(10,10,-10,-10);
}

void CRadar::drawPoint(int x,int y){
    offset[test_x][0] =x;
    offset[test_x][1] =y;
    int offsetX = offset[test_x][0];
    int offsetY = offset[test_x][1];
    int alapha = rand()%255;
    m_points.replace(test_x,QPoint(offsetX,offsetY));
    m_pointsAlapha.replace(test_x,alapha);
//    for(int i = 0; i < m_points.count(); ++i)
//    {
//        int offsetX = offset[i][0];
//        int offsetY = offset[i][1];
//        int alapha = rand()%255;
//        m_points.replace(i,QPoint(offsetX,offsetY));
//        m_pointsAlapha.replace(i,alapha);
//    }
}

void CRadar::randAddress(int x,int y,int arc){
    offset_add.x  =x+r * cos(arc*3.14/180);
    offset_add.y  =y+r* sin(arc*3.14/180);
}


void CRadar::setFlag(int *x_temp,int *y_temp1,int *y_temp2,int *y_temp3,\
                     int *y_temp4,int *y_temp5,int *y_temp6,int *y_temp7,int *y_temp8,\
                  int *y_temp9,int *y_temp10,int *y_temp11,int *x_temp12,int *y_temp13,\
                     int *x_temp14)
{
    *x_temp =row_line_x[1][1]; //第二条线  圆弧
   *y_temp1 =vertical_line_y[1][1]; //第三条线  圆弧
    *y_temp2 =vertical_line_y[2][0]; //第四条线  圆弧
    *y_temp3 =vertical_line_y[3][1]; //第五条线  圆弧
    * y_temp4 =vertical_line_y[4][0]; //第六条线  圆弧
    *y_temp5 =vertical_line_y[5][1]; //第七条线  圆弧
   *y_temp6 =vertical_line_y[6][0]; //第八条线  圆弧
   *y_temp7 =vertical_line_y[7][1]; //第九条线  圆弧
   * y_temp8 =vertical_line_y[8][0]; //第十条线  圆弧
    * y_temp9 =vertical_line_y[9][1]; //第12条线  圆弧
   *y_temp10 =vertical_line_y[10][0]; //第13条线  圆弧
    *y_temp11 =vertical_line_y[11][1]; //第14条线  圆弧
    *x_temp12 =row_line_x[0][1]; //第15条线  圆弧
    * y_temp13 =vertical_line_y[0][0]; //第16条线  圆弧
    *x_temp14 =row_line_x[2][0]; //第17条线  圆弧

}

void CRadar::randAddress(int x,int y){
    static int cnt=0;  //角度计数
    static int first_flag =1;  //用于修改角度的标志
    static int x_temp =row_line_x[1][1]; //第二条线  圆弧
    static int y_temp1 =vertical_line_y[1][1]; //第三条线  圆弧
    static int y_temp2 =vertical_line_y[2][0]; //第四条线  圆弧
    static int y_temp3 =vertical_line_y[3][1]; //第五条线  圆弧
    static int y_temp4 =vertical_line_y[4][0]; //第六条线  圆弧
    static int y_temp5 =vertical_line_y[5][1]; //第七条线  圆弧
    static int y_temp6 =vertical_line_y[6][0]; //第八条线  圆弧
    static int y_temp7 =vertical_line_y[7][1]; //第九条线  圆弧
    static int y_temp8 =vertical_line_y[8][0]; //第十条线  圆弧
    static int y_temp9 =vertical_line_y[9][1]; //第12条线  圆弧
    static int y_temp10 =vertical_line_y[10][0]; //第13条线  圆弧
    static int y_temp11 =vertical_line_y[11][1]; //第14条线  圆弧
    static int x_temp12 =row_line_x[0][1]; //第15条线  圆弧
    static int y_temp13 =vertical_line_y[0][0]; //第16条线  圆弧
    static int x_temp14 =row_line_x[2][0]; //第17条线  圆弧
    static int point_cnt=0;
    static int test_flag =0;  //调试标志
    switch(line_cnt){
        case 0:
            if(x+start_x>=row_line_x[2][1]){
                if(first_flag){
                    cnt =90;
                    first_flag =0;
                }
                if(cnt==-90){
                    cnt =0;
                    line_cnt++;
                    first_flag =1;
//                    test_x =0;
                }else{
                    y =(row_line_y[2][1]+row_line_y[1][1])/2;
                    x =row_line_x[2][1];
                    randAddress(x, y, cnt);
                    point_cnt++;
                    drawPoint(offset_add.x,offset_add.y);
                    cnt--;
                }
            }else{
                x =x+start_x;
                y =y+start_y;
                point_cnt++;
                drawPoint(x,y);
            }
            break;
        case 1:
            x =0;
            if(x+start_x>=row_line_x[2][1] || test_flag){
                if(first_flag){
                    cnt =90;
                    first_flag =0;
                }
                if(cnt==180){
                    cnt =0;
                    line_cnt++;
                    test_flag =0;
                    first_flag =1;
                }else{
                    y =vertical_line_y[1][1];
                    x =row_line_x[1][0];
                    randAddress(x, y, cnt);
                    point_cnt++;
                    drawPoint(offset_add.x,offset_add.y);
                    cnt++;
                }
            }else{
                x =x_temp--;  //先不管生成的随机坐标点
                if(x==row_line_x[1][0]){
                    test_flag =1;
                }
                y =row_line_y[1][0];
                point_cnt++;
                drawPoint(x,y);
            }
           break;
         case 2:
            x =0;
            if(x+start_x>=row_line_x[2][1] || test_flag){
                if(first_flag){
                    cnt =-179;
                    first_flag =0;
                }
                if(cnt==0){
                    cnt =0;
                    line_cnt++;
                    test_flag =0;
                    first_flag =1;
                }else{
                    y =vertical_line_y[1][0];
                    x =(vertical_line_x[2][0]+vertical_line_x[1][0])/2;
                    randAddress(x, y, cnt);
                    point_cnt++;
                    drawPoint(offset_add.x,offset_add.y);
                    cnt++;
                }
            }else{
                y =y_temp1--;  //先不管生成的随机坐标点
                if(y==vertical_line_y[1][0]){
                    test_flag =1;
                }
                x =vertical_line_x[1][0];
                point_cnt++;
                drawPoint(x,y);
            }
            break;
         case 3:
            x =0;
            if(x+start_x>=row_line_x[2][1] || test_flag){
                if(first_flag){
                    cnt =180;
                    first_flag =0;
                }
                if(cnt==0){
                    cnt =0;
                    line_cnt++;
                    test_flag =0;
                    first_flag =1;
                }else{
                    y =vertical_line_y[2][1];
                    x =(vertical_line_x[2][0]+vertical_line_x[3][0])/2;
                    randAddress(x, y, cnt);
                    point_cnt++;
                    drawPoint(offset_add.x,offset_add.y);
                    cnt--;
                }
            }else{
                y =y_temp2++;  //先不管生成的随机坐标点
                if(y==vertical_line_y[2][1]){
                    test_flag =1;
                }
                x =vertical_line_x[2][0];
                point_cnt++;
                drawPoint(x,y);
            }
            break;
           case 4:
                x =0;
                if(x+start_x>=row_line_x[2][1] || test_flag){
                    if(first_flag){
                        cnt =-179;
                        first_flag =0;
                    }
                    if(cnt==0){
                        cnt =0;
                        line_cnt++;
                        test_flag =0;
                        first_flag =1;
                    }else{
                        y =vertical_line_y[3][0];
                        x =(vertical_line_x[4][0]+vertical_line_x[3][0])/2;
                        randAddress(x, y, cnt);
                        point_cnt++;
                        drawPoint(offset_add.x,offset_add.y);
                        cnt++;
                    }
                }else{
                    y =y_temp3--;  //先不管生成的随机坐标点
                    if(y==vertical_line_y[3][0]){
                        test_flag =1;
                    }
                    x =vertical_line_x[3][0];
                    point_cnt++;
                    drawPoint(x,y);
                }
             break;
           case 5:
                x =0;
                if(x+start_x>=row_line_x[2][1] || test_flag){
                    if(first_flag){
                        cnt =180;
                        first_flag =0;
                    }
                    if(cnt==0){
                        cnt =0;
                        line_cnt++;
                        test_flag =0;
                        first_flag =1;
                    }else{
                        y =vertical_line_y[4][1];
                        x =(vertical_line_x[5][0]+vertical_line_x[4][0])/2;
                        randAddress(x, y, cnt);
                        point_cnt++;
                        drawPoint(offset_add.x,offset_add.y);
                        cnt--;
                    }
                }else{
                    y =y_temp4++;  //先不管生成的随机坐标点
                    if(y==vertical_line_y[4][1]){
                        test_flag =1;
                    }
                    x =vertical_line_x[4][0];
                    point_cnt++;
                    drawPoint(x,y);
                }
                break;
           case 6:
                x =0;
                if(x+start_x>=row_line_x[2][1] || test_flag){
                    if(first_flag){
                        cnt =-179;
                        first_flag =0;
                    }
                    if(cnt==0){
                        cnt =0;
                        line_cnt++;
                        test_flag =0;
                        first_flag =1;
                    }else{
                        y =vertical_line_y[5][0];
                        x =(vertical_line_x[5][0]+vertical_line_x[6][0])/2;
                        randAddress(x, y, cnt);
                        point_cnt++;
                        drawPoint(offset_add.x,offset_add.y);
                        cnt++;
                    }
                }else{
                    y =y_temp5--;  //先不管生成的随机坐标点
                    if(y==vertical_line_y[5][0]){
                        test_flag =1;
                    }
                    x =vertical_line_x[5][0];
                    point_cnt++;
                    drawPoint(x,y);
                }
                break;
             case 7:
                    x =0;
                    if(x+start_x>=row_line_x[2][1] || test_flag){
                        if(first_flag){
                            cnt =180;
                            first_flag =0;
                        }
                        if(cnt==0){
                            cnt =0;
                            line_cnt++;
                            test_flag =0;
                            first_flag =1;
                        }else{
                            y =vertical_line_y[6][1];
                            x =(vertical_line_x[7][0]+vertical_line_x[6][0])/2;
                            randAddress(x, y, cnt);
                            point_cnt++;
                            drawPoint(offset_add.x,offset_add.y);
                            cnt--;
                        }
                    }else{
                        y =y_temp6++;  //先不管生成的随机坐标点
                        if(y==vertical_line_y[6][1]){
                            test_flag =1;
                        }
                        x =vertical_line_x[6][0];
                        point_cnt++;
                        drawPoint(x,y);
                    }
               break;
           case 8:
                    x =0;
                    if(x+start_x>=row_line_x[2][1] || test_flag){
                        if(first_flag){
                            cnt =-179;
                            first_flag =0;
                        }
                        if(cnt==0){
                            cnt =0;
                            line_cnt++;
                            test_flag =0;
                            first_flag =1;
                        }else{
                            y =vertical_line_y[7][0];
                            x =(vertical_line_x[7][0]+vertical_line_x[8][0])/2;
                            randAddress(x, y, cnt);
                            point_cnt++;
                            drawPoint(offset_add.x,offset_add.y);
                            cnt++;
                        }
                    }else{
                        y =y_temp7--;  //先不管生成的随机坐标点
                        if(y==vertical_line_y[7][0]){
                            test_flag =1;
                        }
                        x =vertical_line_x[7][0];
                        point_cnt++;
                        drawPoint(x,y);
                    }
               break;
            case 9:
                x =0;
                if(x+start_x>=row_line_x[2][1] || test_flag){
                    if(first_flag){
                        cnt =180;
                        first_flag =0;
                    }
                    if(cnt==0){
                        cnt =0;
                        line_cnt++;
                        test_flag =0;
                        first_flag =1;
                    }else{
                        y =vertical_line_y[8][1];
                        x =(vertical_line_x[9][0]+vertical_line_x[8][0])/2;
                        randAddress(x, y, cnt);
                        point_cnt++;
                        drawPoint(offset_add.x,offset_add.y);
                        cnt--;
                    }
                }else{
                    y =y_temp8++;  //先不管生成的随机坐标点
                    if(y==vertical_line_y[8][1]){
                        test_flag =1;
                    }
                    x =vertical_line_x[8][0];
                    point_cnt++;
                    drawPoint(x,y);
                }
           break;
          case 10:
                x =0;
                if(x+start_x>=row_line_x[2][1] || test_flag){
                    if(first_flag){
                        cnt =-179;
                        first_flag =0;
                    }
                    if(cnt==0){
                        cnt =0;
                        line_cnt++;
                        test_flag =0;
                        first_flag =1;
                    }else{
                        y =vertical_line_y[9][0];
                        x =(vertical_line_x[9][0]+vertical_line_x[10][0])/2;
                        randAddress(x, y, cnt);
                        point_cnt++;
                        drawPoint(offset_add.x,offset_add.y);
                        cnt++;
                    }
                }else{
                    y =y_temp9--;  //先不管生成的随机坐标点
                    if(y==vertical_line_y[9][0]){
                        test_flag =1;
                    }
                    x =vertical_line_x[9][0];
                    point_cnt++;
                    drawPoint(x,y);
                }
           break;
        case 11:
              x =0;
              if(x+start_x>=row_line_x[2][1] || test_flag){
                  if(first_flag){
                      cnt =180;
                      first_flag =0;
                  }
                  if(cnt==0){
                      cnt =0;
                      line_cnt++;
                      test_flag =0;
                      first_flag =1;
                  }else{
                          y =vertical_line_y[10][1];
                          x =(vertical_line_x[11][0]+vertical_line_x[10][0])/2;
                            randAddress(x, y, cnt);
                            point_cnt++;
                            drawPoint(offset_add.x,offset_add.y);
                            cnt--;
                        }
                    }else{
                        y =y_temp10++;  //先不管生成的随机坐标点
                        if(y==vertical_line_y[10][1]){
                            test_flag =1;
                        }
                        x =vertical_line_x[10][0];
                        point_cnt++;
                        drawPoint(x,y);
                    }
               break;
          case 12:
              x =0;
              if(x+start_x>=row_line_x[2][1] || test_flag){
                  if(first_flag){
                      cnt =0;
                      first_flag =0;
                  }
                  if(cnt==-90){
                      cnt =0;
                      line_cnt++;
                      test_flag =0;
                      first_flag =1;
                  }else{
                              y =vertical_line_y[11][0];
                              x =row_line_x[0][1];
                             randAddress(x, y, cnt);
                             point_cnt++;
                            drawPoint(offset_add.x,offset_add.y);
                            cnt--;
                        }
                    }else{
                        y =y_temp11--;  //先不管生成的随机坐标点
                        if(y==vertical_line_y[11][0]){
                            test_flag =1;
                        }
                        x =vertical_line_x[11][0];
                        point_cnt++;
                        drawPoint(x,y);
                    }
           break;
    case 13:
        x =0;
        if(x+start_x>=row_line_x[2][1] || test_flag){
            if(first_flag){
                cnt =-90;
                first_flag =0;
            }
            if(cnt==-179){
                cnt =0;
                line_cnt++;
                test_flag =0;
                first_flag =1;
            }else{
                        y =vertical_line_y[0][0];
                        x =row_line_x[0][0];
                       randAddress(x, y, cnt);
                       point_cnt++;
                      drawPoint(offset_add.x,offset_add.y);
                      cnt--;
                  }
              }else{
                  x =x_temp12--;  //先不管生成的随机坐标点
                  if(x==row_line_x[0][0]){
                      test_flag =1;
                  }
                  y =row_line_y[0][0];
                  point_cnt++;
                  drawPoint(x,y);
              }
     break;
    case 14:
        x =0;
        if(x+start_x>=row_line_x[2][1] || test_flag){
            if(first_flag){
                cnt =180;
                first_flag =0;
            }
            if(cnt==90){
                cnt =0;
                line_cnt++;
                test_flag =0;
                first_flag =1;
            }else{
                        y =vertical_line_y[0][1];
                        x =row_line_x[2][0];
                       randAddress(x, y, cnt);
                       point_cnt++;
                      drawPoint(offset_add.x,offset_add.y);
                      cnt--;
                  }
              }else{
                  y =y_temp13++;  //先不管生成的随机坐标点
                  if(y==vertical_line_y[0][1]){
                      test_flag =1;
                  }
                  x =vertical_line_x[0][0];
                  point_cnt++;
                  drawPoint(x,y);
              }
     break;
    case 15:
          x =x_temp14++;  //先不管生成的随机坐标点
          if(x==start_x){
              qDebug()<<point_cnt;
              line_cnt =0;
              test_flag =1;
              setFlag(&x_temp,&y_temp1,&y_temp2,&y_temp3,&y_temp4,\
                            &y_temp5,&y_temp6,&y_temp7,&y_temp8,\
                             &y_temp9,&y_temp10,&y_temp11,&x_temp12,\
                              &y_temp13,&x_temp14);
          }
          y =start_y;
          point_cnt++;
          drawPoint(x,y);
     break;
    }
}
void CRadar::timerEvent(QTimerEvent *event)
{
    static int x =0;
    static int y =0;
    if(m_timerId == event->timerId())
    {
        m_pieRotate -= 10;
        update();
    }
    else if(m_pointTimerId == event->timerId())
    {
        //随机更换装饰的点
//        qDebug()<<"m_points.count()="<<m_points.count();
//        for(int i = 0; i < m_points.count(); ++i)
//        {
//            int offsetX = rand()%m_drawArea.width();
//            int offsetY = rand()%m_drawArea.width();
//            int alapha = rand()%255;
//            m_points.replace(i,QPoint(offsetX,offsetY) + m_drawArea.topLeft());
//            m_pointsAlapha.replace(i,alapha);
//        }

//        update();
    }
    timerOutFunc();
    randAddress(test_x++,0);
}


