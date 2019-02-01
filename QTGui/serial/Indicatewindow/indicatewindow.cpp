#include "indicatewindow.h"
#include "ui_indicatewindow.h"
#include <QPainter>
#include <QColor>
#include <QtMath>

IndicateWindow::IndicateWindow(int width, int heigth, QDialog *parent) :
    QDialog(parent),
    ui(new Ui::IndicateWindow)
{
    ui->setupUi(this);
    resize(width, heigth);
    this->setWindowFlags(Qt::FramelessWindowHint);
}

IndicateWindow::~IndicateWindow()
{
    delete ui;
}

void IndicateWindow::setTitle(QString title)
{
    ui->iwLbTitle->setText(title);
}

void IndicateWindow::setIndicate(QString indicate)
{
    ui->iwLbIndicate->setText(indicate);
}

void IndicateWindow::paintEvent(QPaintEvent *e)
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRoundRect(6, 6, this->width()-12, this->height()-12,5);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(QColor(230, 200, 230)));

    QColor color(0, 0, 0, 50);
    for(int i=0; i<10; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRoundRect(6-i, 6-i, this->width()-(6-i)*2, this->height()-(6-i)*2,5);
        color.setAlpha(150 - qSqrt(i)*50);
        painter.setPen(color);
        painter.drawPath(path);
    }
    return QWidget::paintEvent(e);
}

void IndicateWindow::hideBtn()
{
    ui->iwBtnCancel->hide();
    ui->iwBtnOk->hide();
}

void IndicateWindow::on_iwBtnOk_clicked()
{
    emit sigOKBtnClicked(true);
    this->close();
}

void IndicateWindow::on_iwBtnCancel_clicked()
{
    emit sigCancelBtnClicked(false);
    this->close();
}
