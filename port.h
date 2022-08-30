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
#include <QSettings>
#include <QFile>
#include <QMessageBox>

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
    int protocol_waiting_time;
    int listening_time=200;
    QTime waitingTime;
//    QTime gettingTime;
//    QTime gettingTime_die;
    QString errorText;
    int currentMessageNumber=0;
    int currentOtvetSize;
    int timerDelay;
    QByteArray otvetBuffer;
    //bool paramsNull=false;
 ~port();

 public slots:
     void  DisconnectPort();
     void ConnectPort(void);
     void Write_Settings_Port(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);
     void WriteToPort(QByteArray data);
     void WriteToPort(int messageNumber,QByteArray data, int otvetSize);
     void WriteToPortTestRS(QByteArray data);
     void ReadInPort(); //Слот чтения из порта по ReadyRead

    // void Exchange(int messageNumber,QByteArray data, int otvetSize, int chNumber);
void Exchange(int messageNumber,QByteArray data, int otvetSize);

 private slots:
     void handleError(QSerialPort::SerialPortError error);//Слот обработки ошибок
     void DataAnalizer(QByteArray data);

signals:
   void finished_Port(); //Сигнал закрытия класса
   void sendBSWVtm(QByteArray,QString);
   void sendBSWVtm(QByteArray,QString,int);
   void error_(QString err);//Сигнал ошибок порта
   void outPort (QString data); //Сигнал вывода полученных данных
   void errorMessage(QSerialPort::SerialPortError error,QString);
   //void nextMessage(int messageNumber, int chNumber);
    void nextMessage(int messageNumber);
    void errorExchange(QString channelName, int messageNumber, QString errorText,bool paramsNull);
    void dataForAnalize(QByteArray data);



};

#endif // PORT_H
