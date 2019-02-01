#include "mcmodbusrtu.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "qdebug.h"
#include <QTimer>
#include <tabcrc.h>

McModbusRTU::McModbusRTU(QSerialPort* serial,QObject *parent) : QObject(parent)
{
//     Tick=new QTimer(this);
//     connect(Tick, SIGNAL(timeout()), this, SLOT(Tick_Server()));
//     serial_enable=0;//情况连接状态
//     Read_TempLong=0;//接收数据长度备份
     myserial = serial;
     serial_enable=1;
//     qDebug()<<2<<myserial->isOpen()<<"\n";

}

/*
 * 连接设备
 * Port设备端口号或者设备地址
 * 返回 大于5则连接成功，否则连接失败
*/
int McModbusRTU::LinkUart(QString Port){
    int Err=0;
    myserial = new QSerialPort;
    //设置串口名
    myserial->setPortName(Port);
    //打开串口
    Err += myserial->open(QIODevice::ReadWrite);
    //设置波特率
    Err += myserial->setBaudRate(QSerialPort::Baud115200);
    //设置数据位数
    Err += myserial->setDataBits(QSerialPort::Data8);
     //设置奇偶校验
    Err += myserial->setParity(QSerialPort::NoParity);
    //设置停止位
    Err += myserial->setStopBits(QSerialPort::OneStop);
    //设置流控制
    Err += myserial->setFlowControl(QSerialPort::NoFlowControl);
    //连接信号量
    connect(myserial, &QSerialPort::readyRead, this, &McModbusRTU::Read_Data);

    if(Err>5){
        Tick->start(5);
        serial_enable=1;//标记当前已连接
    }
    return Err;
}


//分时处理消息
void McModbusRTU::Tick_Server(){
    int i;
    unsigned int CRCtemp,CRCtemp2;
    if(Read_Temp.length()>0){
        if(Read_Temp.length()>Read_TempLong){
            Read_TempLong=Read_Temp.length();
        }else{
            QByteArray Datatemp;
            //CRC校验
            Datatemp.clear();
            for(i=3;i<Read_Temp.length()-2;i++)Datatemp.append(Read_Temp[i]);
            emit McModbusRTUMessage(Read_Temp[0],Read_Temp[1],Datatemp);
            Read_TempLong=0;
            Read_Temp.clear();
        }
    }
}
void McModbusRTU::Request05(unsigned char id, unsigned int address, unsigned int data){
    if(serial_enable==0)return;
    unsigned char SenData[8];
    unsigned int CrcTemp;
    int i;
    SenData[0]=id;
    SenData[1]=05;
    SenData[2]=address>>8;
    SenData[3]=address&0xFF;
    SenData[4]=data>>8;
    SenData[5]=data&0xFF;
    McMBCRC16(SenData,6,&CrcTemp);
    SenData[6]=CrcTemp&0xFF;
    SenData[7]=CrcTemp>>8;
    myserial->write((const char *)SenData,8);
}
void McModbusRTU::Request06(unsigned char id, unsigned int address, unsigned int data){
    if(serial_enable==0)return;
    unsigned char SenData[8];
    unsigned int CrcTemp;
    int i;
    SenData[0]=id;
    SenData[1]=06;
    SenData[2]=address>>8;
    SenData[3]=address&0xFF;
    SenData[4]=data>>8;
    SenData[5]=data&0xFF;
    McMBCRC16(SenData,6,&CrcTemp);
    SenData[6]=CrcTemp&0xFF;
    SenData[7]=CrcTemp>>8;
    myserial->write((const char *)SenData,8);
}
void McModbusRTU::Request01(unsigned char id, unsigned int address, unsigned int dLong){
    if(serial_enable==0)return;
    unsigned char SenData[8];
    unsigned int CrcTemp;
    int i;
    SenData[0]=id;
    SenData[1]=01;
    SenData[2]=address>>8;
    SenData[3]=address&0xFF;
    SenData[4]=dLong>>8;
    SenData[5]=dLong&0xFF;
    McMBCRC16(SenData,6,&CrcTemp);
    SenData[6]=CrcTemp&0xFF;
    SenData[7]=CrcTemp>>8;

//    qDebug()<<3<<myserial->isOpen()<<"\n";
    myserial->write((const char *)SenData,8);
}
void McModbusRTU::Request02(unsigned char id, unsigned int address, unsigned int dLong){
    if(serial_enable==0)return;
    unsigned char SenData[8];
    unsigned int CrcTemp;
    int i;
    SenData[0]=id;
    SenData[1]=02;
    SenData[2]=address>>8;
    SenData[3]=address&0xFF;
    SenData[4]=dLong>>8;
    SenData[5]=dLong&0xFF;
    McMBCRC16(SenData,6,&CrcTemp);
    SenData[6]=CrcTemp&0xFF;
    SenData[7]=CrcTemp>>8;

//    qDebug()<<3<<myserial->isOpen()<<"\n";
    myserial->write((const char *)SenData,8);
}
void McModbusRTU::Request03(unsigned char id, unsigned int address, unsigned int dLong){
    if(serial_enable==0)return;
    unsigned char SenData[8];
    unsigned int CrcTemp;
    int i;
    SenData[0]=id;
    SenData[1]=03;
    SenData[2]=address>>8;
    SenData[3]=address&0xFF;
    SenData[4]=dLong>>8;
    SenData[5]=dLong&0xFF;
    McMBCRC16(SenData,6,&CrcTemp);
    SenData[6]=CrcTemp&0xFF;
    SenData[7]=CrcTemp>>8;

//    qDebug()<<3<<myserial->isOpen()<<"\n";
    myserial->write((const char *)SenData,8);
}
void McModbusRTU::Request15(unsigned char id, unsigned int address, int dLong, unsigned char *data){
    if(serial_enable==0)return;
    int i,shang,yushu;
    unsigned char LongSen;
    qDebug()<<dLong<<endl;

    shang=dLong/8;
    yushu=dLong%8;
    if(yushu!=0) LongSen=shang+1;
    else         LongSen=shang;
    qDebug()<<LongSen<<endl;

    unsigned char SenData[9+LongSen];
    unsigned int CrcTemp;

    SenData[0]=id;
    SenData[1]=15;
    SenData[2]=address>>8;
    SenData[3]=address&0xFF;

    SenData[4]=dLong>>8;
    SenData[5]=dLong&0xFF;

    SenData[6]=LongSen;


     for(i=0;i<LongSen;i++){
         SenData[7+i]=(unsigned char)data[i];
     }


    McMBCRC16(SenData,7+LongSen,&CrcTemp);
    SenData[7+LongSen]=CrcTemp&0xFF;
    SenData[8+LongSen]=CrcTemp>>8;
    myserial->write((const char *)SenData,9+LongSen);
}

 void McModbusRTU::ResponseTOCar(QStringList &response_data)
 {
     if(serial_enable==0)return;
     QByteArray responseData;
     responseData.clear();
     char SenData[25];
     unsigned int CrcTemp;
     bool ok;
     unsigned char car_kind_=response_data[0].toInt(&ok,10);
     unsigned char run_state_=response_data[1].toInt(&ok,10);


     SenData[0]=0;
     SenData[1]=0;
     SenData[2]=0;

     SenData[3]=0;
     SenData[4]=0;

     SenData[5]=0;
     SenData[6]=0;

     SenData[7]=0;
     SenData[8]=0;

     SenData[9]=0;
     SenData[10]=0;

     SenData[11]=0;
     SenData[12]=0;

     SenData[13]=0;
     SenData[14]=0;

     SenData[15]=0;
     SenData[16]=0;

     SenData[17]=0;
     SenData[18]=0;



     if(car_kind_==1)
     {
         qDebug()<<"send car1  "<<run_state_;
         SenData[0]=0x70;
         SenData[1]=0x04;
         SenData[2]=0x10;
         if(run_state_==0)
         {   qDebug()<<" car forward  "<<run_state_;
             SenData[3]=response_data[2].toInt(&ok,10)>>8;
             SenData[4]=response_data[2].toInt(&ok,10)&0xFF;
         }
         else if(run_state_==1)
         {
             qDebug()<<" car backward  "<<run_state_;
             SenData[3]=(-response_data[2].toInt(&ok,10))>>8;
             SenData[4]=(-response_data[2].toInt(&ok,10))&0xFF;

         }
         else if(run_state_==2)
         {
             qDebug()<<" car left  "<<run_state_;
             SenData[7]=(-response_data[4].toInt(&ok,10))>>8;
             SenData[8]=(-response_data[4].toInt(&ok,10))&0xFF;
         }
         else if(run_state_==3)
         {
             qDebug()<<" car right  "<<run_state_;
             SenData[7]=response_data[4].toInt(&ok,10)>>8;
             SenData[8]=response_data[4].toInt(&ok,10)&0xFF;
         }
         else if(run_state_==4)
         {
             qDebug()<<" car stop  "<<run_state_;
             SenData[3]=0;
             SenData[4]=0;
             SenData[7]=0;
             SenData[8]=0;
         }
         else if(run_state_==5)
         {
             SenData[0]=0x74;
             SenData[1]=0x04;
             SenData[2]=0x10;
             SenData[3]=response_data[2].toInt(&ok,10)>>8;
             SenData[4]=response_data[2].toInt(&ok,10)&0xFF;
             SenData[5]=(response_data[3].toInt(&ok,10))>>8;
             SenData[6]=(response_data[3].toInt(&ok,10))&0xFF;
             SenData[7]=(response_data[4].toInt(&ok,10))>>8;
             SenData[8]=(response_data[4].toInt(&ok,10))&0xFF;
         }
     }
     else if(car_kind_==3)
     {

         qDebug()<<"send car3 "<<run_state_;
         if(run_state_==0)//绝对位置
         {
             SenData[0]=0x72;
             SenData[1]=0x04;
             SenData[2]=0x10;

             SenData[3]=response_data[2].toInt(&ok,10)>>8;
             SenData[4]=response_data[2].toInt(&ok,10)&0xFF;

             SenData[5]=response_data[3].toInt(&ok,10)>>8;
             SenData[6]=response_data[3].toInt(&ok,10)&0xFF;

             SenData[7]=response_data[4].toInt(&ok,10)>>8;
             SenData[8]=response_data[4].toInt(&ok,10)&0xFF;

         }
         else if(run_state_==1)//相对位置
         {
             SenData[0]=0x72;
             SenData[1]=0x04;
             SenData[2]=0x10;
             SenData[3]=response_data[2].toInt(&ok,10)>>8;
             SenData[4]=response_data[2].toInt(&ok,10)&0xFF;
             SenData[5]=response_data[3].toInt(&ok,10)>>8;
             SenData[6]=response_data[3].toInt(&ok,10)&0xFF;
             SenData[7]=response_data[4].toInt(&ok,10)>>8;
             SenData[8]=response_data[4].toInt(&ok,10)&0xFF;

         }
         else if(run_state_==2)//相对位置
         {
             SenData[0]=0x72;
             SenData[1]=0x04;
             SenData[2]=0x10;
             SenData[3]=(response_data[2].toInt(&ok,10))>>8;
             SenData[4]=(response_data[2].toInt(&ok,10))&0xFF;
             SenData[5]=response_data[3].toInt(&ok,10)>>8;
             SenData[6]=response_data[3].toInt(&ok,10)&0xFF;
             SenData[7]=(-response_data[4].toInt(&ok,10))>>8;
             SenData[8]=(-response_data[4].toInt(&ok,10))&0xFF;
         }
         else if(run_state_==3)
         {
             SenData[0]=0x72;
             SenData[1]=0x04;
             SenData[2]=0x10;
         }
     }
     else if(car_kind_==4)
     {
         SenData[0]=0x73;
         SenData[1]=0x04;
         SenData[2]=0x10;
         qDebug()<<"send car4 "<<run_state_;
         if(run_state_==0)//绝对位置
         {
             SenData[3]=response_data[2].toInt(&ok,10)>>8;
             SenData[4]=response_data[2].toInt(&ok,10)&0xFF;
         }
         else if(run_state_==1)//相对位置
         {
             SenData[3]=(-response_data[2].toInt(&ok,10))>>8;
             SenData[4]=(-response_data[2].toInt(&ok,10))&0xFF;
         }

     }
     else if(car_kind_==5)
     {
         SenData[0]=0x75;
         SenData[1]=0x04;
         SenData[2]=0x10;
         qDebug()<<"send ID "<<run_state_;

         SenData[3]=response_data[2].toInt(&ok,10)>>8;
         SenData[4]=response_data[2].toInt(&ok,10)&0xFF;

         SenData[5]=(response_data[3].toInt(&ok,10))>>8;
         SenData[6]=(response_data[3].toInt(&ok,10))&0xFF;

         SenData[7]=(response_data[4].toInt(&ok,10))>>8;
         SenData[8]=(response_data[4].toInt(&ok,10))&0xFF;

         SenData[9]=response_data[5].toInt(&ok,10)>>8;
         SenData[10]=response_data[5].toInt(&ok,10)&0xFF;

         SenData[11]=(response_data[6].toInt(&ok,10))>>8;
         SenData[12]=(response_data[6].toInt(&ok,10))&0xFF;

         SenData[13]=(response_data[7].toInt(&ok,10))>>8;
         SenData[14]=(response_data[7].toInt(&ok,10))&0xFF;

         SenData[15]=(response_data[8].toInt(&ok,10))>>8;
         SenData[16]=(response_data[8].toInt(&ok,10))&0xFF;

         SenData[17]=(response_data[9].toInt(&ok,10))>>8;
         SenData[18]=(response_data[9].toInt(&ok,10))&0xFF;
     }
     else if(car_kind_==6)
     {
         SenData[0]=0x76;
         SenData[1]=0x04;
         SenData[2]=0x10;
         qDebug()<<"send laser "<<run_state_;

         SenData[3]=response_data[2].toInt(&ok,10)>>8;
         SenData[4]=response_data[2].toInt(&ok,10)&0xFF;

         SenData[5]=(response_data[3].toInt(&ok,10))>>8;
         SenData[6]=(response_data[3].toInt(&ok,10))&0xFF;
     }

     else if(car_kind_==7)
     {
         SenData[0]=0x80;
         SenData[1]=0x04;
         SenData[2]=0x10;

     }
     else if(car_kind_==8)
     {
         SenData[0]=0x81;
         SenData[1]=0x04;
         SenData[2]=0x10;

     }

     McMBCRC16((unsigned char *)SenData,19,&CrcTemp);
     SenData[19]=CrcTemp&0xFF;
     SenData[20]=CrcTemp>>8;
     myserial->write((const char *)SenData,21);  //串口发送数据

    if (myserial->waitForBytesWritten(200))
    {

        responseData = myserial->readAll(); //读取串口缓冲区中的数据

        qDebug()<<"receive one times";
         QByteArray temp_crc_data;
         temp_crc_data.clear();


//         QString string;
//         string.prepend(responseData);

//         QString string = responseData;
 //        emit this->response(string);
         QString string;
         string = responseData.data();
         emit this->response(string);    //发出response信号   并将数据传到信号对应的槽中

         if(McMBCRC16(responseData,temp_crc_data))  //CRC16校验数据
         {

             emit this->response(" the package is ok");
             //emit this->response1(responseData);
//                 if(response_data[0]==)
//                 {
//                     ui->readIDReg1->setText(response_data[0]);
               //  response
//                 }
             
         }
         else     emit this->response(" the package is error");


}



     response_data.clear();
 }




void McModbusRTU::Request16(unsigned char id, unsigned int address, int dLong, unsigned char *data){
    if(serial_enable==0)return;

    int i,shang,yushu;
    unsigned int LongSen;
    qDebug()<<dLong<<endl;

    LongSen=dLong*2;
    qDebug()<<LongSen<<endl;


    unsigned char SenData[9+LongSen];
    unsigned int CrcTemp;

    SenData[0]=id;
    SenData[1]=16;
    SenData[2]=address>>8;
    SenData[3]=address&0xFF;

    SenData[4]=dLong>>8;
    SenData[5]=dLong&0xFF;

    SenData[6]=(unsigned char)LongSen;

    for(i=0;i<LongSen;i++){
        SenData[7+i]=data[i];
//        SenData[8+2*i]=data[i]&0xFF;
    }

    McMBCRC16(SenData,7+LongSen,&CrcTemp);
    SenData[7+LongSen]=CrcTemp&0xFF;
    SenData[8+LongSen]=CrcTemp>>8;
    myserial->write((const char *)SenData,9+LongSen);
}
void McModbusRTU::Request04(unsigned char id, unsigned int address, unsigned int dLong){
    if(serial_enable==0)return;
    unsigned char SenData[8];
    unsigned int CrcTemp;
    int i;
    SenData[0]=id;
    SenData[1]=04;
    SenData[2]=address>>8;
    SenData[3]=address&0xFF;
    SenData[4]=dLong>>8;
    SenData[5]=dLong&0xFF;
    McMBCRC16(SenData,6,&CrcTemp);
    SenData[6]=CrcTemp&0xFF;
    SenData[7]=CrcTemp>>8;
    myserial->write((const char *)SenData,8);
}
//串口数据接收
void McModbusRTU::Read_Data(){
    Read_Temp.append(myserial->readAll());
    if(Read_Temp.length()>1000)Read_Temp.clear();
}
//关闭串口，释放资源
void McModbusRTU::CloseUart(){
    if(serial_enable){
        myserial->clear();
        myserial->close();
//        myserial->deleteLater();
//        Tick->stop();
    }
}
// CRC MODBUS 效验
// 输入参数: pDataIn: 数据地址
//           iLenIn: 数据长度
// 输出参数: pCRCOut: 2字节校验值
void McModbusRTU::McMBCRC16(unsigned char *pDataIn, int iLenIn, unsigned int *pCRCOut){
    int ucCRCHi = 0xFF;
    int ucCRCLo = 0xFF;
    int iIndex;
    while(iLenIn-- )
    {
        iIndex = ucCRCLo ^ *( pDataIn++ );
        ucCRCLo = ( int )( ucCRCHi ^ aucCRCHi[iIndex] );
        ucCRCHi = aucCRCLo[iIndex];
    }
    *pCRCOut = ( ucCRCHi << 8 | ucCRCLo );
}

unsigned char McModbusRTU::McMBCRC16(QByteArray &pDatasrc, QByteArray &pCRCOut)
{
    //将一个16位的寄存器预置全为1  将该寄存器分为高8位和低8位
    unsigned char ucCRCHi = 0xFF;
    unsigned char ucCRCLo = 0xFF;
    unsigned char ucCRCHL[2];

    int iIndex;
    int i=0;
    QByteArray pDataIn;

    pDataIn=pDatasrc;
    pDataIn.remove(pDataIn.size()-2,2);

    int j=pDataIn.size();
    while(j-- )
    {
        iIndex = ucCRCLo ^ pDataIn[i++];
        ucCRCLo = ( unsigned char )( ucCRCHi ^ aucCRCHi[iIndex] );
        ucCRCHi = aucCRCLo[iIndex];
    }

     pDataIn.clear();
     ucCRCHL[0]=(ucCRCHi);
     ucCRCHL[1]=(ucCRCLo);



    qDebug()<<"crc is"<< ucCRCHL[0]<<ucCRCHL[1];

    int temp_size= pDatasrc.size();
    for(int kk=0;kk<temp_size;kk++)
        qDebug()<<"the "<<kk<<" data is "<<(unsigned char)pDatasrc.at(kk);


    if((ucCRCHL[0]==(unsigned char)pDatasrc.at(temp_size-1))&&(ucCRCHL[1]==(unsigned char)pDatasrc.at(temp_size-2)))
    {
       return 1;

    }
    else
      return 0;

}

