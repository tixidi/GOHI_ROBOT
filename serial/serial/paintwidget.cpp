#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    this->setMinimumSize(529,489);
    this->setMaximumSize(529,489);
//    this->setPalette(QPalette(Qt::white));

   //设置背景图片
    this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(":/img/caoping.jpg").scaled(// 缩放背景图.
                this->size(),
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation)));             // 使用平滑的缩放方式
    this->setPalette(palette);                           // 给widget加上背景图

    this->setMouseTracking(true);
    this->isPressed = false;

}

void PaintWidget::paintEvent(QPaintEvent *event)
{
        QPainter painter(this);
        QPen pen;                                 //创建一个画笔
            pen.setColor(Qt::darkCyan);
            pen.setWidth(5);
            painter.setPen(pen);

            for(int i = 0;i<lines.size();i++){
                myLine* pLine = lines[i];
                painter.drawLine(pLine->startPnt,pLine->endPnt);
            }

}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    setCursor(Qt::PointingHandCursor);
        startPnt = event->pos();
        endPnt = event->pos();
        this->isPressed = true;

}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(this->isPressed){
           endPnt = event->pos();

           myLine* line = new myLine;  //put the new line into vector
           line->startPnt = startPnt;
           line->endPnt = endPnt;
           this->lines.push_back(line);

           update();                                    //repainter，call paintEvent
           startPnt = endPnt;
       }

}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
    setCursor(Qt::ArrowCursor);
       this->isPressed = false;
}
