#ifndef MYQTOPENGLW_H
#define MYQTOPENGLW_H

#include <QMainWindow>
#include <myopengl.h>


namespace Ui {
class myqtopenglw;
}

class myqtopenglw : public QMainWindow
{
    Q_OBJECT

public:
    explicit myqtopenglw(QWidget *parent = 0);
    ~myqtopenglw();


private:
    Ui::myqtopenglw *ui;

};

#endif // MYQTOPENGLW_H
