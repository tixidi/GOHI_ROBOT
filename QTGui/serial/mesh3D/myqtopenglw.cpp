#include "myqtopenglw.h"
#include "ui_myqtopenglw.h"

myqtopenglw::myqtopenglw(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::myqtopenglw)
{
    ui->setupUi(this);

    myOpengl *poglwindow = new myOpengl();

    poglwindow->show();


}

myqtopenglw::~myqtopenglw()
{
    delete ui;
}
