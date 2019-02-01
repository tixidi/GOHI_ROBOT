#ifndef INDICATEWINDOW_H
#define INDICATEWINDOW_H

#include <QDialog>
#include <QPaintEvent>

namespace Ui {
class IndicateWindow;
}

class IndicateWindow : public QDialog
{
    Q_OBJECT

public:
    explicit IndicateWindow(int width = 450, int heigth = 200, QDialog *parent = 0);
    ~IndicateWindow();

    ///
    /// \brief setTitle
    /// \param title
    /// 设置提示窗口标题
    ///
    void setTitle(QString title);

    ///
    /// \brief setIndicate
    /// \param indicate
    /// 设置提示语
    ///
    void setIndicate(QString indicate);

    ///
    /// \brief paintEvent
    /// \param e
    /// 添加窗口阴影
    ///
    void paintEvent(QPaintEvent *e);

signals:
    ///
    /// \brief sigOKBtnClicked
    /// 点击确定按钮
    ///
    void sigOKBtnClicked(bool);

    ///
    /// \brief sigCancelBtnClicked
    /// 点击取消按钮
    ///
    void sigCancelBtnClicked(bool);

public slots:
    ///
    /// \brief hideBtn
    /// 隐藏按钮
    ///
    void hideBtn();

private slots:

    ///
    /// \brief on_iwBtnOk_clicked
    /// 点击确定按钮
    ///
    void on_iwBtnOk_clicked();

    ///
    /// \brief on_iwBtnCancel_clicked
    /// 点击取消按钮
    ///
    void on_iwBtnCancel_clicked();

private:
    Ui::IndicateWindow *ui;
};

#endif // INDICATEWINDOW_H
