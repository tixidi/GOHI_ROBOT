#include "datatablewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    datatablewindow w;
    w.show();

    return a.exec();
}
