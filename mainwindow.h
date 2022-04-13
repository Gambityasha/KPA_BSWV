#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <port.h>
#include <QTimer>
#include <QList>
#include "stdint.h"
#include <QFile>
#include <QSettings>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct BSWVdata //создание структуры
{
    QString name; //шифр канала
    QString namePort; //присвоенное имя порта
    float icap2; //"Суммарный ток нагрузки 2"
    float icap1;//"Суммарный ток нагрузки 1"
    float u2;//"Напряжение на силовых шинах 2"
    float u1;//"Напряжение на силовых шинах 1"
    float tcorp2;//"Температура 2 корпуса прибора"
    float tcorp1;//"Температура 1 корпуса прибора"
};

struct BSWVtarir //создание структуры
{
    QString name; //шифр канала
    QString namePort; //присвоенное имя порта
    float uref; //Опорное напряжение
    float icap2; //"Суммарный ток нагрузки 2"
    float icap1;//"Суммарный ток нагрузки 1"
    float u2;//"Напряжение на силовых шинах 2"
    float u1;//"Напряжение на силовых шинах 1"
    float tcorp2;//"Температура 2 корпуса прибора"
    float tcorp1;//"Температура 1 корпуса прибора"
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    unsigned char data [6];
    unsigned char dataT [6];
    QString name;
    int baudrate = 115200;
    int databits = 8;
    int parity = 2;              //DataToInt (QSerialPort::EvenParity)
    int stopbits = 1;            //DataToInt (QSerialPort::OneStop) , по протоколу 1
    int flowcontrol = 0;      //DataToInt (QSerialPort::NoFlowControl)
    unsigned char startByte = 170;
    unsigned char outAdr = 1; //адрес БЦУ
    unsigned char inAdr = 2; //адрес БСШ-В
    unsigned char messType = 1; // Тип сообщения, 1 - телеметрия
    unsigned char messType1 = 17; // Тип сообщения, 17 - данные АЦП для тарировки

   public:

BSWVdata BSWV;
QList <BSWVdata>ListOfBSWVData;
BSWVtarir BSWVt;
QList <BSWVtarir>ListOfBSWVt;

private:
   void LoadSettings();

public slots:
   void Vivod(); //Вывод телеметрии в таблицу
   void WritePreo ();
   void Print(QString dat);
   void Analize(QByteArray dataRead, QString comName);
   QString getPortName(QString dis, QString serial);
   void AcpVisible();

signals:
    //void savesettings(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);
   void savesettings1(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);
   void savesettings2(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);
   void savesettings3(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);
   void savesettings4(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);
   void savesettings5(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);
   void savesettings6(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);
    void writeData(QByteArray dataQ);
    void writeDataT(QByteArray dataQt);
    void con1();void con2();void con3();void con4();void con5();void con6();
};
#endif // MAINWINDOW_H
