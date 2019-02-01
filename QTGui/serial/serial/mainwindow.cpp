#include "mainwindow.h"
#include "ui_mainwindow.h"




static const char blankString[] = QT_TRANSLATE_NOOP("SettingsDialog", "N/A");
static const char blankString1[] = QT_TRANSLATE_NOOP("SettingsDialog", "");


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("智能粮食平仓机监测界面");

    this->move(200,0);
    this->setMaximumSize(1418,1033);//窗体大小固定
    this->setMinimumSize(1418,1033);
    loadStyle();   //加载样式表文件

    ui->OpenButton->setEnabled(true);
    ui->closeButton->setEnabled(false);
    status = new QLabel(this);
    ui->statusBar->addWidget(status);
    CRadar* radar = new CRadar(ui->paintwidget);
    radar->setFixedSize(649,469);

     fillPortsInfo();

     serial = new QSerialPort(this);
     mmrtu=new McModbusRTU(serial);

     datatablewin = new datatablewindow();


     //信号连接槽
     connect(this,SIGNAL(signalThis(MainWindow*)),datatablewin,SLOT(slotGetPoint(MainWindow*)));
     connect(this,SIGNAL(testPointNum(QList<int>)),datatablewin,SLOT(PointNum(QList<int>)));
     connect(this,SIGNAL(testPointValue(QList<RowData>)),datatablewin,SLOT(PointValue(QList<RowData>)));



     connect(ui->OpenButton, &QPushButton::clicked, this, &MainWindow::openSerialPort);
     connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::closeSerialPort);
     connect(serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),this, &MainWindow::handleError);

     connect(time,SIGNAL(timeout()),this,SLOT(timeToReadSensor()));
  //   time->start(1000);
     connect(timer1,SIGNAL(timeout()),this,SLOT(timeToReadLaser()));
     timer1->start(2000);   //定时2000ms   超时执行timeToReadLaser（）函数    周期性的


     connect(mmrtu, &McModbusRTU::response , this, &MainWindow::showResponse);  //modbus协议
     connect(mmrtu, &McModbusRTU::response1, this, &MainWindow::showResponseToUI);


     connect(ui->forwardPushButton, &QPushButton::clicked,       this,  &MainWindow::sendCar1ControlCommand);
     connect(ui->backwardPushButton, &QPushButton::clicked,       this,  &MainWindow::sendCar1ControlCommand);
     connect(ui->turnleftPushButton, &QPushButton::clicked,       this,  &MainWindow::sendCar1ControlCommand);
     connect(ui->turnrightPushButton, &QPushButton::clicked,       this,  &MainWindow::sendCar1ControlCommand);
     connect(ui->stopcarPushButton, &QPushButton::clicked,            this,  &MainWindow::sendCar1ControlCommand);
     connect(ui->startNaviPushButton, &QPushButton::clicked,       this,  &MainWindow::sendCar1ControlCommand);


     connect(ui->upstairPushButton, &QPushButton::clicked,       this,  &MainWindow::sendCar3ControlCommand);
     connect(ui->downstairPushButton, &QPushButton::clicked,       this,  &MainWindow::sendCar3ControlCommand);
     connect(ui->startstairPushButton, &QPushButton::clicked,       this,  &MainWindow::sendCar3ControlCommand);
     connect(ui->stopStairPushButton, &QPushButton::clicked,       this,  &MainWindow::sendCar3ControlCommand);


     connect(ui->rollleftPushButton, &QPushButton::clicked,       this,  &MainWindow::sendCar4ControlCommand);
     connect(ui->rollrightPushButton, &QPushButton::clicked,       this,  &MainWindow::sendCar4ControlCommand);
     connect(ui->stoprollPushButton, &QPushButton::clicked,       this,  &MainWindow::sendCar4ControlCommand);



     connect(ui->writeIDpushButton, &QPushButton::clicked,       this,  &MainWindow::sendWriteIDControlCommand);
     connect(ui->setLaserRangepushButton, &QPushButton::clicked,       this,  &MainWindow::sendLaserRangeControlCommand);


     ui->readIDReg1->setText("5645");  //对应句柄设置文本内容
//     ui->readIDReg2->setText("565");

}


//析构函数用于在销毁对象时进行清理工作
MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::loadStyle()
{
    /*
        加载样式表文件
        使用资源源文件添加到工程
    */
    QFile file(":/style.qss");
    if(!file.open(QFile::ReadOnly)) {  //以只读的形式打开
        qDebug() << file.errorString();
        file.close();
        return;
    }
    QString styleSheet = file.readAll();
    // 为QApplication设置样式表
    qApp->setStyleSheet(styleSheet);
    file.close();
}


void MainWindow::FillBuf(uint8_t* buf,uint8_t Code)
{
  uint16_t i = 0;
  uint16_t j = 1;
  switch(Code)
  {
    case CC01:
    case CC02:
    case CC05:
      for(i= 0;i<0x200;i++)
        buf[i] = j = !j;
    break;
    case CC03:
    case CC06:
    case CC10:
      j = 0x000F;
      for(i= 0;i<0x250;i++)
      buf[i] = j++;
    break;
  }
}

/***********************************************/




void MainWindow::fillPortsInfo()
{
    ui->serialPortComboBox->clear();
    QString description;
    QString manufacturer;
    QString serialNumber;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)  //扫描每一个串口
    {
        QStringList list;
        description = info.description();
        manufacturer = info.manufacturer();
        serialNumber = info.serialNumber();

        list << info.portName()
             << (!description.isEmpty() ? description : blankString)
             << (!manufacturer.isEmpty() ? manufacturer : blankString)
             << (!serialNumber.isEmpty() ? serialNumber : blankString)
             << info.systemLocation()
             << (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : blankString)
             << (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : blankString);


        ui->serialPortComboBox->addItem(list.first(), list);
    }
}






/******************************************/
void MainWindow::openSerialPort()
{

    serial->setPortName(ui->serialPortComboBox->currentText());
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::TwoStop);


    if (serial->open(QIODevice::ReadWrite))
    {

        ui->OpenButton->setEnabled(false);
        ui->OpenButton->hide();
        ui->closeButton->show();
        ui->closeButton->setEnabled(true);

        showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5")
                          .arg(currentSettings.name).arg(currentSettings.stringBaudRate).arg(currentSettings.stringDataBits)
                          .arg(currentSettings.stringParity).arg(currentSettings.stringStopBits));
     }
   else
     {
        //消息框提示
        QMessageBox::critical(this, tr("Error"), serial->errorString());
        showStatusMessage(tr("Open error"));
    }

}

void MainWindow::closeSerialPort()
{
    if (serial->isOpen())
    {
        mmrtu->CloseUart();
    }

    ui->OpenButton->setEnabled(true);
    ui->OpenButton->show();
    ui->closeButton->hide();
    ui->closeButton->setEnabled(false);

    timer1->stop();
    showStatusMessage(tr("Disconnected"));
}
void MainWindow::showStatusMessage(const QString &message)
{
    status->setText(message);
}
void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}


void MainWindow::clearReceiveArea()
{
  ui->receivetextBrowser->clear();
}



char MainWindow::ConvertHexChar(char ch)
{
    if((ch >= '0') && (ch <= '9'))
        return ch-0x30;
    else if((ch >= 'A') && (ch <= 'F'))
        return ch-'A'+10;
    else if((ch >= 'a') && (ch <= 'f'))
        return ch-'a'+10;
    else return (-1);
}


QByteArray MainWindow::QString2Hex(QString str)
{
    QByteArray senddata;
    int hexdata,lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    senddata.resize(len/2);
    char lstr,hstr;
    for(int i=0; i<len; )
    {
        hstr=str[i].toLatin1();
        if(hstr == ' ')
        {
            i++;
            continue;
        }
        i++;
        if(i >= len)
            break;
        lstr = str[i].toLatin1();
        hexdata = ConvertHexChar(hstr);
        lowhexdata = ConvertHexChar(lstr);
        if((hexdata == 16) || (lowhexdata == 16))
            break;
        else
            hexdata = hexdata*16+lowhexdata;
        i++;
        senddata[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    senddata.resize(hexdatalen);
    return senddata;
}




void MainWindow::on_dataTablePushButton_clicked()
{
    emit signalThis(this);
    datatablewin->showNormal();
    testPNum.clear();

    PNum=100000;//设置为30
    testPNum.append(PNum);//

    testPValue.clear();
    RowData rowData;

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));


    for(int i=0; i<PNum; i++){
            rowData.tableRow = i+1;
            rowData.Pos_X = i*2;
            rowData.Pos_Y = i*2;
            rowData.Pos_Z = qrand()%200;
            testPValue.append(rowData);

    }


    emit testPointNum(testPNum);
    emit testPointValue(testPValue);


    this->hide();  //窗口隐藏
}

void MainWindow::exitApp(bool click)
{
    exit = click;
}


void MainWindow::on_dataTablePushButton_2_clicked()
{
    IndicateWindow *indicatewindow = new IndicateWindow();
    connect(indicatewindow,SIGNAL(sigOKBtnClicked(bool)),this,SLOT(exitApp(bool)));
    indicatewindow->setTitle("提示");
    indicatewindow->setIndicate("是否退出系统！");
    indicatewindow->exec();
    if(exit){
//        this->close();
//        indicatewindow->setIndicate("退出系统中...");
//        indicatewindow->show();
        qApp->exit();
        qDebug() << ".......................";
    }

//    qApp->exit();
}
/*
  位置1 控制目标标识符
  位置2 上下左右标识符
  位置3 x
  位置4 y
  位置5 z

*/
void MainWindow::sendCar1ControlCommand()
{
    QStringList temp_request_list;

    temp_request_list.clear();  //清空字符串列表
    temp_request_list.append("1");
    QPushButton *pButton = qobject_cast<QPushButton*>(sender());
    //判断哪一个按钮按下，对应执行哪一个句柄中的内容
    if(pButton==ui->forwardPushButton)
    {
        temp_request_list.append("0");
        temp_request_list.append(ui->carXSpeedlineEdit->text());
        temp_request_list.append(ui->carYSpeedlineEdit->text());
        temp_request_list.append(ui->carZSpeedlineEdit->text());
        /*
        //打印
        qDebug()<< "list ="<< temp_request_list;
        //遍历
        for(int i = 0; i< temp_request_list.size();++i)
        {
            QString tmp = temp_request_list.at(i);
            qDebug()<<"tmp ="<< tmp;
        }
        */

    }
    else if(pButton==ui->backwardPushButton)
    {
        temp_request_list.append("1");
        temp_request_list.append(ui->carXSpeedlineEdit->text());
        temp_request_list.append(ui->carYSpeedlineEdit->text());
        temp_request_list.append(ui->carZSpeedlineEdit->text());
    }
    else if(pButton==ui->turnleftPushButton)
    {
        temp_request_list.append("2");
        temp_request_list.append(ui->carXSpeedlineEdit->text());
        temp_request_list.append(ui->carYSpeedlineEdit->text());
        temp_request_list.append(ui->carZSpeedlineEdit->text());
    }
    else if(pButton==ui->turnrightPushButton)
    {
        temp_request_list.append("3");
        temp_request_list.append(ui->carXSpeedlineEdit->text());
        temp_request_list.append(ui->carYSpeedlineEdit->text());
        temp_request_list.append(ui->carZSpeedlineEdit->text());
    }
    else if(pButton==ui->stopcarPushButton)
    {
        temp_request_list.append("4");
        temp_request_list.append("0");
        temp_request_list.append("0");
        temp_request_list.append("0");
    }
    else if(pButton==ui->startNaviPushButton)
    {
        temp_request_list.append("5");
        temp_request_list.append(ui->expectXPositionlineEdit->text());
        temp_request_list.append(ui->expectYPositionlineEdit->text());
        temp_request_list.append(ui->expectZPositionlineEdit->text());
    }



    mmrtu->ResponseTOCar(temp_request_list);



}

/*

1、第一个int ，代表位置
2、第二个int ,代表类型
3、第三个int ,代表速度

4、如果点击 开始升降        将发送的绝对位置
   如果点击 上升、下降、停止 将发送相对位置

*/
/*
  位置1 控制目标标识符
  位置2 上升下降标识符
  位置3 速度标识符
  位置4 位置类型标识符
  位置5 位置标识符

*/
void MainWindow::sendCar3ControlCommand()
{
    QStringList temp_request_list;

    temp_request_list.clear();
    temp_request_list.append("3");
     QPushButton *pButton = qobject_cast<QPushButton*>(sender());


     if(pButton==ui->startstairPushButton)
     {
             temp_request_list.append("0");
             temp_request_list.append(ui->upstairSpeedlineEdit->text());
             temp_request_list.append("0");
             temp_request_list.append(ui->expectliftheightlineEdit->text());
     }
     else  if(pButton==ui->upstairPushButton)
     {
            temp_request_list.append("1");
            temp_request_list.append(ui->upstairSpeedlineEdit->text());
            temp_request_list.append("1");
            temp_request_list.append(ui->stairstepPositionlineEdit->text());
     }
     else if(pButton==ui->downstairPushButton)
     {
             temp_request_list.append("2");
             temp_request_list.append(ui->upstairSpeedlineEdit->text());
             temp_request_list.append("1");
             temp_request_list.append(ui->stairstepPositionlineEdit->text());
     }
     else if(pButton==ui->stopStairPushButton)
     {
             temp_request_list.append("3");
             temp_request_list.append("0");
             temp_request_list.append("0");
             temp_request_list.append("0");
     }




    mmrtu->ResponseTOCar(temp_request_list);


}
/*
  位置1 控制目标标识符
  位置2 左旋\右旋标识符
  位置3 速度标识符
  位置4 速度标识符
  位置5 速度标识符

*/
void MainWindow::sendCar4ControlCommand()
{
    QStringList temp_request_list;

    temp_request_list.clear();
    temp_request_list.append("4");

     QPushButton *pButton = qobject_cast<QPushButton*>(sender());

     if(pButton==ui->rollleftPushButton)
     {
         temp_request_list.append("0");
         temp_request_list.append(ui->rollSpeedlineEdit->text());
         temp_request_list.append(ui->rollSpeedlineEdit->text());
         temp_request_list.append(ui->rollSpeedlineEdit->text());
     }
     else if(pButton==ui->rollrightPushButton)
     {
         temp_request_list.append("1");
         temp_request_list.append(ui->rollSpeedlineEdit->text());
         temp_request_list.append(ui->rollSpeedlineEdit->text());
         temp_request_list.append(ui->rollSpeedlineEdit->text());
     }
     else if(pButton==ui->stoprollPushButton)
     {
         temp_request_list.append("1");
         temp_request_list.append("0");
         temp_request_list.append("0");
         temp_request_list.append("0");
     }


    mmrtu->ResponseTOCar(temp_request_list);

}




 void MainWindow::sendWriteIDControlCommand()
 {
     QStringList temp_request_list;

     temp_request_list.clear();
     temp_request_list.append("5");
     temp_request_list.append("0");

      temp_request_list.append(ui->writeIDReg1->text());
      temp_request_list.append(ui->writeIDReg2->text());

      temp_request_list.append(ui->writeIDReg3->text());
      temp_request_list.append(ui->writeIDReg4->text());
      temp_request_list.append(ui->writeIDReg5->text());

      temp_request_list.append(ui->writeIDReg6->text());
      temp_request_list.append(ui->writeIDReg7->text());
      temp_request_list.append(ui->writeIDReg8->text());

     mmrtu->ResponseTOCar(temp_request_list);
 }
 void MainWindow::sendLaserRangeControlCommand()
 {
     QStringList temp_request_list;

     temp_request_list.clear();
     temp_request_list.append("6");
     temp_request_list.append("0");


      temp_request_list.append(ui->leftlaserrange->text());
      temp_request_list.append(ui->rightlaserrange->text());



     mmrtu->ResponseTOCar(temp_request_list);
 }


 //定时时间一到就执行
 void MainWindow::timeToReadSensor()
 {
     QStringList temp_request_list;

     temp_request_list.clear();
     temp_request_list.append("7");
     temp_request_list.append("0");


     mmrtu->ResponseTOCar(temp_request_list);
 }

  //定时时间一到就执行
 void MainWindow::timeToReadLaser()
 {
     QStringList temp_request_list;

     temp_request_list.clear();
     temp_request_list.append("8");
     temp_request_list.append("0");


     mmrtu->ResponseTOCar(temp_request_list);
 }

 void MainWindow::showResponse(const QString &s)
 {
     //ui->readIDReg2->setText("565");
     //bool ok;
     //int int_head=str_head.toInt(&ok,2);
     //ui->receivetextBrowser->append("R:"+QTime::currentTime().toString("AP hh:mm:ss:zzz")+":"+s);
     ui->readIDReg2->setText(s);
 }

 void MainWindow::showResponseToUI(QByteArray s)
 {
     //ui->receivetextBrowser->setText(s);
    // ui->readIDReg2->setText(s);
 }

