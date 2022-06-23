#ifndef PORT_H
#define PORT_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QObject>
#include "mainwindow.h"
#include "stdint.h"



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
     ~port();

    QSerialPort thisPort;

    Settings SettingsPort;



 signals:
    void finished_Port(); //Сигнал закрытия класса
    void sendBSWVtm(QByteArray,QString);

    void error_(QString err);//Сигнал ошибок порта

    void outPort (QString data); //Сигнал вывода полученных данных
    void errorMessage(QSerialPort::SerialPortError error,QString);
 public slots:
     void  DisconnectPort();

     void ConnectPort(void);

     void Write_Settings_Port(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);

     void WriteToPort(QByteArray data);
     void WriteToPortTestRS(QByteArray data);
     void ReadInPort(); //Слот чтения из порта по ReadyRead


 private slots:
     void handleError(QSerialPort::SerialPortError error);//Слот обработки ощибок


};

#endif // PORT_H
