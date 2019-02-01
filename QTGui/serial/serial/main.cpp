#include <QApplication>

#include <QSplashScreen>
#include <QPixmap>
#include <QPaintEvent>
#include "mainwindow.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


//    QSplashScreen *splash = new QSplashScreen;
//    splash->setPixmap(QPixmap("E:/qt/3Dmeasure/grainv1.4/serial/serial/shamo.jpg"));  //图片路径更换成自己的
//    splash->show();
//    splash->showMessage(QObject::tr("Setting up the main window..."),
//                           Qt::AlignRight | Qt::AlignCenter,Qt::blue);


    QPixmap pixmap(":/img/shamo.jpg");
    pixmap = pixmap.scaled(1371,787,Qt::KeepAspectRatio);
    QSplashScreen splash(pixmap);  //启动时会显示一个启动画面
    splash.setFont((QFont("Helvetica", 34, QFont::Bold)));//设置要显示的消息的字体属性

    splash.show();   //显示

    splash.setCursor(Qt::BlankCursor);//不显示鼠标外观
    a.processEvents();

    splash.showMessage("loading",Qt::AlignCenter,QColor::fromRgb(255,10,255));  //窗口显示信息
    for(int i=0;i<1000;i++){  //延时
       splash.repaint();   //不停地重绘，不然点一下画面就会启动画面消失   悲剧的是点击画面外的地方启动画面也会消失  待解决
    }

    splash.showMessage("Starting up ...",Qt::AlignCenter,QColor::fromRgb(255,10,255));

    for(int i=0;i<5000;i++){  //延时
       splash.repaint();   //不停地重绘，不然点一下画面就会启动画面消失   悲剧的是点击画面外的地方启动画面也会消失  待解决
    }

    QApplication::addLibraryPath("./plugins");   //插件目录
    QApplication::addLibraryPath("./");
    MainWindow w;  //创建对象
    w.show();
    splash.finish(&w);

    return a.exec();
}


