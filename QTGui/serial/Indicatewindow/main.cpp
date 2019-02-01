#include "indicatewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IndicateWindow w;
    w.show();

    return a.exec();
}
