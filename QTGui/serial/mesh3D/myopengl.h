#ifndef MYOPENGL_H
#define MYOPENGL_H


#include <QGLWidget>
#include <QtOpenGL>

#include <QWidget>
#include <t3dmap.h>
#include <tools.h>

#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <tabledata.h>


class myOpengl : public QGLWidget
{
    Q_OBJECT
public:
    explicit myOpengl(QWidget* parent = 0, const char* name = 0, bool fs = false);
        ~myOpengl();
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void keyPressEvent(QKeyEvent *);            //键盘按下事件
    void wheelEvent(QWheelEvent *);             //滚轮事件
    void mousePressEvent(QMouseEvent *e);		//--鼠标按下事件
    void mouseMoveEvent(QMouseEvent *e);	//--鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *e);	//--鼠标释放（松开）事件
    void mouseDoubleClickEvent(QMouseEvent *e);	//--鼠标双击事件

protected:
    bool fullScreen;
signals:
public slots :
    void meshPointValue(QList<RowData> mesh3D_value);
private:
    T3dMap  *map;
    double xFar=0.0f,yFar=0.0f,zFar=0.0f;
    int wWidth=1300,wHeight=700;
    double scaling=1.0f;
    int oldX,oldY;
    bool gIsStartTrackBall = false;
    bool gIsMoveMap=false;
    TrackBall trackball;

};

#endif // MYOPENGL_H
