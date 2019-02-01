#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include<QPainter>
#include <QPoint>
#include <vector>

//线段
typedef struct myLine{
    QPoint startPnt;
    QPoint endPnt;
}myLine;



class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = 0);

signals:

public slots:

protected:
        void paintEvent(QPaintEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);

public:
        QPoint startPnt;   //起点
         QPoint endPnt;     //终点
         bool isPressed;    //鼠标是否按下

         QVector<myLine*> lines; //存放所有的线段
private:


//        QList<Shape*> shapeList;
};

#endif // PAINTWIDGET_H
