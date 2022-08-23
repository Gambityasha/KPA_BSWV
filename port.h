#ifndef PORT_H
#define PORT_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "stdint.h"
#include <QObject>
//#include "mainwindow.h"
#include <QThread>
#include <QTime>
#pragma once //еще одна защита от повторного включения

struct Settings
{
    QString name;
    qint32 baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopBits;
    QSerialPort::FlowControl flowControl;
};

class port : public QObject
{
    Q_OBJECT
public:
    explicit port(QObject *parent = nullptr);
     Settings SettingsPort;
    QSerialPort thisPort;
    bool transactionInProgress=false;
    int protocol_waiting_time=60;
    int listening_time=100;
     ~port();

 public slots:
     void  DisconnectPort();
     void ConnectPort(void);
     void Write_Settings_Port(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);
     void WriteToPort(QByteArray data);
     void WriteToPortTestRS(QByteArray data);
     void ReadInPort(); //Слот чтения из порта по ReadyRead

    // void Exchange(int messageNumber,QByteArray data, int otvetSize, int chNumber);
void Exchange(int messageNumber,QByteArray data, int otvetSize);

 private slots:
     void handleError(QSerialPort::SerialPortError error);//Слот обработки ошибок

signals:
   void finished_Port(); //Сигнал закрытия класса
   void sendBSWVtm(QByteArray,QString);
   void error_(QString err);//Сигнал ошибок порта
   void outPort (QString data); //Сигнал вывода полученных данных
   void errorMessage(QSerialPort::SerialPortError error,QString);
   //void nextMessage(int messageNumber, int chNumber);
void nextMessage(int messageNumber, QString comName);
};

#endif // PORT_H
