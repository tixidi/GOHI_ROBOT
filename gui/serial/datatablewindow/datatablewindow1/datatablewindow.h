#ifndef DATATABLEWINDOW_H
#define DATATABLEWINDOW_H

#include    <QWidget>
#include    <QLabel>
#include    <QTableWidgetItem>
#include    "qwintspindelegate.h"
#include     <mainwindow.h>
#include     <myopengl.h>
#include     <tabledata.h>





class MainWindow;
namespace Ui {
class datatablewindow;
}

class datatablewindow : public QWidget
{
    Q_OBJECT

private:
//  自定义单元格Type的类型，在创建单元格的Item时使用
    enum    CellType{ctName=1000,ct_X,ct_Y,ct_Z}; //各单元格的类型

//  各字段在表格中的列号
    enum    FieldColNum{colName=0, col_X,col_Y,col_Z};
//#define     colNoName   0
//#define     colNoSex    1
//#define     colNoBirth  2
//#define     colNoNation 3
//#define     colNoScore  4
//#define     colNoPartyM 5

    QLabel  *labCellIndex; //状态栏上用于显示单元格的行号、列号
    QLabel  *labCellType;//状态栏上用于显示单元格的type
    QLabel  *labStudID;//状态栏上用于显示单元格的data,

    QWIntSpinDelegate   spinDelegate; //代理组件

//    void    iniStatusBar(); //状态栏创建
    void createItemsARow(int rowNo,int P_X,int P_Y,int P_Z); //为某一行创建items
    void changeRowDataList();
    void initTableData();
public:
public:
    explicit datatablewindow(QWidget *parent = 0);
    ~datatablewindow();


signals:
     void fixPointValue(QList<RowData>);

public slots:
    void slotGetPoint(MainWindow *biPoint);
    void PointNum(QList<int> num);
    void PointValue(QList<RowData> P_value);
    ///
    /// \brief slotGetBtn
    /// \param ok
    /// 获取提示窗口点击的是确定还是取消
    ///
    bool slotGetBtn(bool ok);
    void sort(int col);

private slots:
    void on_btnSetHeader_clicked();  //设置表头 按键

    void on_btnSetRows_clicked(); //设置行数 按键

    void on_btnIniData_clicked(); //初始化数据 按键

    void on_chkBoxTabEditable_clicked(bool checked); //表格可编辑 checkbox

    void on_chkBoxHeaderH_clicked(bool checked); //显示行表头 checkbox

    void on_chkBoxHeaderV_clicked(bool checked); //显示列表头 checkbox

    void on_chkBoxRowColor_clicked(bool checked); //间隔行底色 checkbox

    void on_rBtnSelectItem_clicked();   // 行选择模式 RadioButton

    void on_rBtnSelectRow_clicked();    // 单元格选择模式 RadioButton

    void on_btnReadToEdit_clicked(); //读取表格内容到文本 按键

    void on_tableInfo_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_btnInsertRow_clicked();  //插入行 按键

    void on_btnAppendRow_clicked(); //添加行  按键

    void on_btnDelCurRow_clicked();     //删除当前行 按键


    void on_btnAutoHeght_clicked();

    void on_btnAutoWidth_clicked();

    void on_dataTableForwardPushButton_clicked();

    void on_dataTableNextPushButton_clicked();


    void on_btnDel_clicked();

    void on_btnAdd_clicked();


private:
    Ui::datatablewindow *ui;
    MainWindow *mainW;
    QList<int> testPointCounts;   //
    int pointNumber;          //点数量
    int tableRow;          //表格显示行数
    int tableRowMax;       //表格最大行数
    int lastIndex;         //单双极性combobox的索引
    bool ok;               //提示窗口点击的确定还是取消
    QList<int> delRecord;  //删除行记录
    QList<RowData> rowDataList;  //显示的行数据
    QList<RowData> delRowDataList;    //删除的数据
    QMap<int,RowData> tableMap;           //表格数据



};

#endif
