#include "myopengl.h"
#include <GL/glu.h>
#include <QDebug>


myOpengl::myOpengl(QWidget* parent, const char* name, bool fs)
    :QGLWidget(parent)
{
    //保存窗口是否为全屏的状态。
    fullScreen = fs;

    //设置窗口的位置，即左上角为(0,0)点，大小为640*480。
    setGeometry(20,30, 640, 480);

    // 设置窗口的标题为“My's OpenGL Framework”。
    setWindowTitle( "My's OpenGL Framework");

    // 如果fullscreen为真，那么就全屏显示这个窗口。
    if (fullScreen)
    {
        showFullScreen();

    }
     map=new T3dMap();

}

myOpengl::~myOpengl()
{

}

void myOpengl::initializeGL()
{
    glShadeModel(GL_FLAT);//SMOOTH//GL_FLAT // 用于控制openGL绘制指定两点间其他点颜色的过渡方式
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);   //改变窗口的背景颜色
    glClearDepth(1.0f);                    //将缓存清除为预先的设置值,设置深度缓存
    glEnable(GL_NORMALIZE);               //设置自动化单位法向量
    glEnable ( GL_DEPTH_TEST );           //允许深度测试
    glAlphaFunc(GL_GREATER,0);            //设置图形透明度的显示规则
    glDepthFunc(GL_LEQUAL);  //  指定“目标像素与当前像素在z方向上值大小比较”的函数，符合该函数关系的目标像素才进行绘制，否则对目标像素不予绘制
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);//如果OpenGL不能有效的支持透视修正参数差值，那么GL_DONT_CARE 和 GL_FASTEST可以执行颜色、纹理坐标的简单线性差值计算。

    glEnable( GL_BLEND);    //使能混色功能
    //OpenGL 会把源颜色和目标颜色各自取出，并乘以一个系数（源颜色乘以的系数称为“源因子”，目标颜色乘以的系数称为“目标因子”），然后相加，这样就得到了新的颜色
    //GL_ONE_MINUS_SRC_ALPHA：表示用1.0减去源颜色的alpha值来作为因子（1-alpha）。
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable (GL_POLYGON_SMOOTH);

    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); // Make round points, not square points
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);  // Antialias the lines
    glHint (GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    // glMatrixMode ( ) 与glLoadIdentity ( )一同使用。glLoadIdentity ( )重置当前指定的矩阵为单位矩阵。
    glMatrixMode(GL_MODELVIEW); //设置当前矩阵模式-对模型视景矩阵堆栈应用随后的矩阵操

    glEnable( GL_COLOR_MATERIAL) ;
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);

    map->initMap();

    return;
}

void myOpengl::meshPointValue(QList<RowData> mesh3D_value)
{
    glShadeModel(GL_FLAT);//SMOOTH//GL_FLAT // 用于控制openGL绘制指定两点间其他点颜色的过渡方式
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);   //改变窗口的背景颜色
    glClearDepth(1.0f);                    //将缓存清除为预先的设置值,设置深度缓存
    glEnable(GL_NORMALIZE);               //设置自动化单位法向量
    glEnable ( GL_DEPTH_TEST );           //允许深度测试
    glAlphaFunc(GL_GREATER,0);            //设置图形透明度的显示规则
    glDepthFunc(GL_LEQUAL);  //  指定“目标像素与当前像素在z方向上值大小比较”的函数，符合该函数关系的目标像素才进行绘制，否则对目标像素不予绘制
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);//如果OpenGL不能有效的支持透视修正参数差值，那么GL_DONT_CARE 和 GL_FASTEST可以执行颜色、纹理坐标的简单线性差值计算。

    glEnable( GL_BLEND);    //使能混色功能
    //OpenGL 会把源颜色和目标颜色各自取出，并乘以一个系数（源颜色乘以的系数称为“源因子”，目标颜色乘以的系数称为“目标因子”），然后相加，这样就得到了新的颜色
    //GL_ONE_MINUS_SRC_ALPHA：表示用1.0减去源颜色的alpha值来作为因子（1-alpha）。
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable (GL_POLYGON_SMOOTH);

    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); // Make round points, not square points
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);  // Antialias the lines
    glHint (GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    // glMatrixMode ( ) 与glLoadIdentity ( )一同使用。glLoadIdentity ( )重置当前指定的矩阵为单位矩阵。
    glMatrixMode(GL_MODELVIEW); //设置当前矩阵模式-对模型视景矩阵堆栈应用随后的矩阵操

    glEnable( GL_COLOR_MATERIAL) ;
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    int i;

    int num=mesh3D_value.count();
    int data0[num];
    for(i=0;i<num;i++)
    {

      data0[i]=mesh3D_value.at(i).Pos_Z;
    }
    map->laserScanData(data0);
    return;
}


void myOpengl::paintGL()
{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glLoadIdentity();
//    glTranslatef(-1.5, 0.0, -6.0);

//    glBegin(GL_TRIANGLES);
//    glVertex3f(0.0, 1.0, 0.0);
//    glVertex3f(-1.0, -1.0, 0.0);
//    glVertex3f(1.0, -1.0, 0.0);
//    glEnd();

    //glClearColor函数设置好清除颜色，glClear利用glClearColor函数设置好的当前清除颜色设置窗口颜色
    glClearColor(0, 0, 0.1f, 1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(xFar, yFar,zFar);

    trackball.makeRolate();
    map->drawMap();

    glFlush();
    return;
}

void myOpengl::resizeGL(int w, int h)
{
//    //防止height为0
//    if (height == 0)
//    {
//        height = 1;
//    }
//    //重置当前的视口（Viewport）
//    glViewport(0, 0, (GLint)width, (GLint)height);
//    glClearColor(1.0f, 1.0f, 0.5f, 0.0f);
//    //选择投影矩阵。
//    glMatrixMode(GL_PROJECTION);

//    //重置投影矩阵
//    glLoadIdentity();

//    //建立透视投影矩阵
//    gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
//    //gluPerspective(45.0,(GLfloat)width() / (GLfloat)height(),0.1,100.0);
//    // 选择模型观察矩阵
//    glMatrixMode(GL_MODELVIEW);

//    // 重置模型观察矩阵。
//    glLoadIdentity();

    wWidth=w;
    wHeight=h;
    zFar=0.0f;
    xFar=0.0f;
    yFar=0.0f;
    glViewport(0,0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    h = h > 0 ? h : 1;
    float aspect = (float)w / (float)h;
    gluPerspective(45,aspect,1.0,1500.0);
    glTranslatef(0,0,-300.0f);

    trackball.resize();


    updateGL();

    return;
}


void myOpengl::keyPressEvent(QKeyEvent * e)
{
    switch (e->key())
    {
        //如果按下了F2键，那么屏幕是否全屏的状态就切换一次。然后再根据需要，显示所要的全屏窗口或者普通窗口。
    case Qt::Key_F2:
        fullScreen = !fullScreen;

        if (fullScreen)
        {
            showFullScreen();
        }
        else
        {
            showNormal();
            setGeometry(0, 0, 640, 480);
        }

        updateGL();
        break;

        //如果按下了Escape键，程序退出。
    case Qt::Key_Escape:
        close();
        break;
    }
    return;
}


void myOpengl::mousePressEvent(QMouseEvent *e)
{
//    GLfloat dx = GLfloat(e->x() - lastPos.x()) / width();
//    GLfloat dy = GLfloat(e->y() - lastPos.y()) / height();
//    if (e->buttons() & Qt::LeftButton) {
//        xrot -= 180 * dy;
//        yrot -= 180 * dx;
//        updateGL();
//    } else if (e->buttons() & Qt::RightButton) {
//        xrot += 180 * dy;
//        zrot += 180 * dx;
//        updateGL();
//    }
//    lastPos = e->pos();



        if (e->buttons() & Qt::LeftButton) {
            oldX=e->x();
            oldY=e->y();
            trackball.setXY(e->x(),e->y());
            gIsStartTrackBall = true;
            updateGL();

            qDebug() << "left down";
            qDebug()<<this->width();
            qDebug()<<this->height();

        }

        if(e->buttons() & Qt::MidButton)
        {
            map->setLineOrFill();
            updateGL();
        }

        if (e->buttons() & Qt::RightButton) {
            oldX=e->x();
            oldY=e->y();
            gIsMoveMap=true;
            updateGL();
            qDebug() << "right down";
        }

}

void myOpengl::mouseReleaseEvent(QMouseEvent *e)
{

    if(gIsStartTrackBall)
    {
        oldX=e->x();
        oldY=e->y();
        gIsStartTrackBall = false;
        qDebug() << "left up";
    }

    if (gIsMoveMap) {
        oldX=e->x();
        oldY=e->y();
        gIsMoveMap = false;

        qDebug() << "right up";
    }


}

void myOpengl::mouseMoveEvent(QMouseEvent *e)
{
//    GLfloat dx = GLfloat(e->x() - lastPos.x()) / width();
//    GLfloat dy = GLfloat(e->y() - lastPos.y()) / height();
//    if (e->buttons() & Qt::LeftButton) {
//        xrot -= 180 * dy;
//        yrot -= 180 * dx;
//        updateGL();
//    } else if (e->buttons() & Qt::RightButton) {
//        xrot += 180 * dy;
//        zrot += 180 * dx;
//        updateGL();
//    }
//    lastPos = e->pos();


    if(gIsStartTrackBall)
    {
        trackball.MouseMove(e->x(),e->y(),this->width(),this->height());
        updateGL();
    }
    if(gIsMoveMap)
    {
        xFar-=oldX-e->x();
        yFar+=oldY-e->y();
        oldX=e->x();
        oldY=e->y();
        updateGL();
    }
}

void myOpengl::wheelEvent(QWheelEvent *e)
{
    if(e->delta()>0){//如果滚轮往上滚
        zFar+=4;
    }else{
        zFar-=4;
}
   updateGL();
}

//--s鼠标双击事件
void myOpengl::mouseDoubleClickEvent(QMouseEvent *e)
{
    //---没有实现功能
}
