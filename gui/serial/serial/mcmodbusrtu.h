#ifndef MCMODBUSRTU_H
#define MCMODBUSRTU_H

#include <QObject>
#include <QSerialPort>
#include <QVector>
#include <QTimer>
#include <tabcrc.h>

class McModbusRTU : public QObject
{
    Q_OBJECT
public:
    explicit McModbusRTU(QSerialPort* serial,QObject *parent = nullptr);
    int LinkUart(QString Port);//连接串口

    void CloseUart();//关闭串口
    void Request01(unsigned char id, unsigned int address, unsigned int dLong);//批量读保持寄存器
    void Request02(unsigned char id, unsigned int address, unsigned int dLong);//批量读保持寄存器
    void Request03(unsigned char id, unsigned int address, unsigned int dLong);//批量读保持寄存器
    void Request04(unsigned char id, unsigned int address, unsigned int dLong);//批量读输入寄存器
    void Request05(unsigned char id, unsigned int address, unsigned int data);//单个写保持寄存器
    void Request06(unsigned char id, unsigned int address, unsigned int data);//单个写保持寄存器
    void Request15(unsigned char id, unsigned int address,int dLong, unsigned char *data);//批量写多个线圈寄存器
    void Request16(unsigned char id, unsigned int address,int dLong, unsigned char *data);//批量写保持寄存器
    void ResponseTOCar(QStringList &response_data);

private:
//    void McMBCRC16(unsigned char *pDataIn, int iLenIn, unsigned int *pCRCOut);

signals:
    void McModbusRTUMessage(unsigned char mID,int mFunction,QByteArray Data);
    void response(const QString &s);
    void response1(QByteArray s);
public slots:
    void Read_Data();//串口数据读取函数
    void Tick_Server();//串口分时接收
private:
    bool serial_enable;
    QByteArray Read_Temp;
    int Read_TempLong;
    QTimer *Tick;
    int currentWaitTimeout = 100;

public:
    QSerialPort* myserial;//串口句柄
    unsigned char * s_data;
    //重载关系
    void McMBCRC16(unsigned char *pDataIn, int iLenIn, unsigned int *pCRCOut);
    unsigned char McMBCRC16(QByteArray &pDatasrc, QByteArray &pCRCOut);
};

#endif // MCMODBUSRTU_H
