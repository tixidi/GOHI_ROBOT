#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtCore/QtGlobal>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QGridLayout>

#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QTimer>
#include <QString>
#include <QTime>
#include <QTextCodec>
#include"QTimerEvent"
#include <QVector>

#include <cassert>
#include <QFileDialog>
#include "mcmodbusrtu.h"

#include <QWidget>
#include <tabledata.h>
#include <QList>
#include <QMap>
#include <QTableWidgetItem>
#include <QTextEdit>


#include <QTableWidget>
#include <QMenu>
#include <QHeaderView>
#include <QScrollBar>
#include <QContextMenuEvent>
#include <QMessageBox>
#include <QToolTip>
#include <QStyledItemDelegate>


#include <datatablewindow.h>
#include <indicatewindow.h>
#include <paintwidget.h>
#include <cradar.h>



#define MSG_ERR_FLAG  0xFFFF    //
#define MSG_IDLE      0x0000    //
#define MSG_RXING     0x0001    //
#define MSG_COM       0x0002    //
#define MSG_INC       0x8000    //
#define TIME_OVERRUN  100       //
#define MB_SLAVEADDR              0x01  //从机地址0x01
//#define MB_SLAVEADDR_2            0x0002
//#define MB_SLAVEADDR_3            0x0003

#define MB_ALLSLAVEADDR         0xFF


class datatablewindow;
namespace Ui {
class MainWindow;
}

class QIntValidator;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    struct Settings {
        QString name;
        qint32 baudRate;                  QString stringBaudRate;
        QSerialPort::DataBits dataBits;   QString stringDataBits;
        QSerialPort::Parity parity;       QString stringParity;
        QSerialPort::StopBits stopBits;   QString stringStopBits;


    };
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     Settings settings() const;
     void readMyCom();
     QString stringSpaceToHex(QByteArray str,char tag);
     char ConvertHexChar(char ch);
     QByteArray QString2Hex(QString str);
     QByteArray hexStringtoByteArray(QString hex);
     void FillBuf(uint8_t* buf,uint8_t Code);
//     void changeRowDataList(QList<int> num);

signals:
     void signalThis(MainWindow *);
     void testPointNum(QList<int>);
     void testPointValue(QList<RowData>);

public slots:
     ///
     /// \brief exitApp
     /// 退出应用程序
     ///
     void exitApp(bool click);

private slots:

    void openSerialPort();
    void closeSerialPort();

    void clearReceiveArea();
    void timeToReadSensor();
    void timeToReadLaser();


    void handleError(QSerialPort::SerialPortError error);

    void showResponse(const QString &s);
    void showResponseToUI(QByteArray s);

    void on_dataTablePushButton_clicked();
    void on_dataTablePushButton_2_clicked();

    void sendCar1ControlCommand();
    void sendCar3ControlCommand();
    void sendCar4ControlCommand();


    void sendWriteIDControlCommand();
    void sendLaserRangeControlCommand();




private:
    void showStatusMessage(const QString &message);
    Ui::MainWindow *ui;
    Settings currentSettings;
    QSerialPort *serial;
    QLabel *status;

   // QTimer *timer1;
    int valuePrior=0;
    int enableCount=0;
    int timeId;

    QVector<int> interval;
    QVector<int> repeatCount;
    QVector<int> sort;
    QVector<int> temp_count;

    QTimer *timer1 = new QTimer( this );


    int cntChange=0;
    QByteArray responseData;
    QByteArray receiveData;

    QByteArray requestData;

    QTimer *time=new QTimer(this);
    McModbusRTU *mmrtu;
    bool no_write_flag;

    datatablewindow *datatablewin;
    bool exit;
    QList<int> testPNum;
    QList<RowData>  testPValue;
    int PNum=0;
    int request_flag=0;


//    Table *table;

//    QList<int> probeSel;   //选择的探针
//    int probeNumber;          //探针数量
//    int tableRow;          //表格显示行数
//    int tableRowMax;       //表格最大行数
//    int lastIndex;         //单双极性combobox的索引
//    bool ok;               //提示窗口点击的确定还是取消
//    QList<int> delRecord;  //删除行记录
//    QList<RowData> rowDataList;  //显示的行数据
//    QList<RowData> delRowDataList;    //删除的数据
//    QMap<int,RowData> tableMap;           //表格数据


/***************************************/
private:
    void fillPortsParameters();
    void fillWriteAndReadParameters();
    void fillPortsInfo();
    void updateSettings();
    QString sendpriormessage();
    void makestring();

    void getValuePrior();

    void setSendTime();
    void setAutoSendTime();

    void readData(QString number);
    void test();
    void MB_Parse_Data();
    void processData();


protected:
    void loadStyle();

//    bool eventFilter(QObject *obj, QEvent *ev);
//    void timerEvent( QTimerEvent * );
//    void initTableData();
//    void addRowData();

public:
//    void timerEvent(QTimerEvent *event);
//    void closeEvent(QCloseEvent* e);
    enum CommandCode {
        CC01 = 0x01,
        CC02 = 0x02,
        CC03 = 0x03,
        CC04 = 0x04,
        CC05 = 0x05,
        CC06 = 0x06,
        CC0F = 0x0f,
        CC10 = 0x10,
        UnknownCC = -1
    };

    enum DataFormat {
        DF_HEX =    0x01,
        DF_STRING = 0x02,
        UnknownDF = -1
    };
    typedef struct {
       uint8_t  Code ;
       uint8_t Addr ;
       uint8_t _CRC_H;
       uint8_t _CRC_L;

    }PDUData_TypeDef;
    PDUData_TypeDef PduData;

    uint16_t RxCount = 0;

};


#endif // MAINWINDOW_H
