#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once //еще одна защита от повторного включения


#include <QMainWindow>
#include <port.h>
#include <QTimer>
#include <QList>
#include "stdint.h"
#include <QFile>
#include <QSettings>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QPixmap>
#include <QDate>
#include <QDateTime>
#include <QTime>
#include <QTextStream>
#include <QDir>
#include <QMessageBox>
#include <errorform.h>
#include <QThread>
#include <stdio.h>
#include <QProcess>
#define errorDelay 100

//размеры пакетов данных (первые четыре байта всегда содержат начальный, адрес отправителя, адрес получателя и код сообщения, последние два байта - контрольная сумма)
//тип сообщения 1 - 6 байт, 17 - 16 байт, 34 - 1 байт, 255 - 0 байт
//итого весь пакет ответа: 1 - 12 байт, 17 - 22 байт, 34 - 7 байт, 255 - 6 байт

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum MKvse{
    MK1o = 1, MK1r = 2, MK2o=3, MK2r=4, MK3o = 5, MK3r = 6
};

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
    QByteArray otvet;
    QByteArray otvetBuffer;
    short otvetPoluchen; //0 - не получен, 1 - получен
    short errorStatus;//0 - нет ошибок порта, 1 - есть ошибки порта    
    bool on_off_status;
    bool readyToSend = false;
    QTime sendTime;
    int ping;

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
    QByteArray otvet;
    short otvetPoluchen; //0 - не получен, 1 - получен
    bool readyToSend = false;

};
struct BSWVprov //создание структуры
{
    QString name; //шифр канала
    QString namePort; //присвоенное имя порта
    QByteArray otvet;
    short otvetPoluchen; //0 - не получен, 1 - получен
    bool readyToSend = false;

};
struct BSWVnomerMK //создание структуры
{
    QString name; //шифр канала
    QString namePort; //присвоенное имя порта
    QString nMK; //номер МУКа, 1 - 1 МК, 2- 2 МК, 3 - 3 MK
    QString nChan;//номер канала, 0 - основной, 1 - резервный
    QByteArray otvet;
    short otvetPoluchen; //0 - не получен, 1 - получен
    bool readyToSend = false;

};



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    ErrorForm *window = new ErrorForm(this);

    bool AdminTools=true;
    int timerDelay = 1000;
    bool stopIfError = 0;
    int numberOfRowsTestConsole=0;

    unsigned char data [6];
    unsigned char dataT [6];
    unsigned char dataProv [6];
    unsigned char dataNomer [6];
    unsigned char dataTestRS485 [8];
    QByteArray dataQ;
    QByteArray dataQProv;
    QByteArray dataQNomer;
    QByteArray dataQt;
    QString name;
    QString fname;    
    QString fACPname;
    QString logYear;
    QString logMonth;
    QString dirName;
    QList<QString>ListOfSerial;
    QList<QString>ListOfSerialFact;
    int baudrate = 115200; //скорость обмена, по протоколу 115200
    int databits = 8;
    int parity = 2;              //DataToInt (QSerialPort::EvenParity)
    int stopbits = 1;            //DataToInt (QSerialPort::OneStop) , по протоколу 1
    int flowcontrol = 0;      //DataToInt (QSerialPort::NoFlowControl)
    unsigned char startByte = 170;
    unsigned char outAdr = 1; //адрес БЦУ
    unsigned char inAdr = 2; //адрес БСШ-В
    unsigned char messType1 = 1; // Тип сообщения, 1 - телеметрия
    unsigned char messType17 = 17; // Тип сообщения, 17 - данные АЦП для тарировки
    unsigned char messType34 = 34;//Тип сообщения, 34 - данные о номере мука и номере канала
    unsigned char messType255 = 255;//Тип сообщения, 255 - проверка связи
    unsigned char messType99 = 99;//Тип сообщения, 99 - проверка RS485
    int otvetTelemSize = 12;
    int otvetTarirSize = 22;
    int otvetMKSize = 7;
    int otvetProvSize = 6;
    int otvetTestRS485Size = 8;    
    QString error;
    QString a;
    QByteArray otvet485data;
    QString otvet485name;

    int currentMessageNumber=0;
    bool stopRequest=false;
    bool firstStart=true;
    bool firstErrorOpen=true;


public:
    port *PortMK1osn = new port;
    port *PortMK1rez = new port;
    port *PortMK2osn = new port;
    port *PortMK2rez = new port;
    port *PortMK3osn = new port;
    port *PortMK3rez = new port;
    QThread* thread_MK1osn = new QThread;//Создаем поток для порта
    QThread* thread_MK1rez = new QThread;
    QThread* thread_MK2osn = new QThread;
    QThread* thread_MK2rez = new QThread;
    QThread* thread_MK3osn = new QThread;
    QThread* thread_MK3rez = new QThread;
    QTimer *timerRequest;   

    QTimer *timerReconnect;
    QTimer *timerCloseErrorWindow;
    QByteArray otvet;
    BSWVdata BSWV;
    QList <BSWVdata>ListOfBSWVData;
    BSWVtarir BSWVt;
    QList <BSWVtarir>ListOfBSWVt;
    BSWVprov BSWVp;
    QList <BSWVprov>ListOfBSWVprov;
    BSWVnomerMK BSWVnomer;
    QList <BSWVnomerMK>ListOfBSWVnomer;
    QFile file;
    QFile fileACP;
    QFile fileMK1o;
    QFile fileMK1r;
    QFile fileMK2o;
    QFile fileMK2r;
    QFile fileMK3o;
    QFile fileMK3r;
    QTime time;
    QFile fileError;
    QDir dir;
    bool converterError_status;

public slots:

   void VivodACP();
   void OtpravkaZaprosaTarir ();
   void OtpravkaZaprosaNomer();
   void Print(QString dat);
   void Analize(QByteArray otvet, QString comName);
   void Kompanovka(QByteArray dataRead, QString comName);
   QString getPortName(QString dis, QString serial);
   void ChangeColor();
   void ProverkaNomera();
   void WriteInFileError(QString error);
    void LoadSettings();
    void ErrorAnalyzer(QSerialPort::SerialPortError error,QString portName);
    void Reconnect( );
    void ErrorMessage(bool status);
    void AnalizeRS485();
    void delay(int millisecondsToWait);
    void WriteInFileTemplate(QString fnameTemplate,QFile &fileTemplate,int k);
    void ExchangeErrorAnalizer(QString channelName, int messageNumber, QString errorText,bool paramsNull);
    void ErrorThread();
    void WriteInFile();


private slots:
   void on_btnNomer_clicked();
   void on_btnStart_clicked();
   void on_pbTestRS485_clicked();
   void on_pbGetACPKalibr_clicked();
   void on_pushButton_clicked();   
   void on_tabWidget_currentChanged(int index);
   void on_pbReconnectRS485_clicked();
   void tblBSWVSetDeafault(int numberOfRows, int column);
   void tblBSWVSetData(int numberOfChannel);
   void on_pushButton_2_clicked();
   void RequestSender();
   void on_tabWidget_tabBarClicked(int index);
   void on_pbCancelReconnect_clicked();

   void on_pushButton_3_clicked();

signals:
   void savesettings1(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);
   void savesettings2(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);
   void savesettings3(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);
   void savesettings4(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);
   void savesettings5(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);
   void savesettings6(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);
   void writeData1(QByteArray dataQ);
   void writeData2(QByteArray dataQ);
   void writeData3(QByteArray dataQ);
   void writeData4(QByteArray dataQ);
   void writeData5(QByteArray dataQ);
   void writeData6(QByteArray dataQ);
   void writeToPort1(int messageNumber,QByteArray data, int otvetSize);
   void writeToPort2(int messageNumber,QByteArray data, int otvetSize);
   void writeToPort3(int messageNumber,QByteArray data, int otvetSize);
   void writeToPort4(int messageNumber,QByteArray data, int otvetSize);
   void writeToPort5(int messageNumber,QByteArray data, int otvetSize);
   void writeToPort6(int messageNumber,QByteArray data, int otvetSize);

   void con1();void con2();void con3();void con4();void con5();void con6();
   void discon1();void discon2();void discon3();void discon4();void discon5();void discon6();
   void readyToAnalize(QByteArray otvet, QString comName);
   void errorMessageThis(QString);
   //void errorReconnect(QString);
   void msgTestRS485(QByteArray data, QString comName);
   void testRSMK1o(QByteArray);void testRSMK1r(QByteArray);void testRSMK2o(QByteArray);
   void testRSMK2r(QByteArray);void testRSMK3o(QByteArray);void testRSMK3r(QByteArray);

};
#endif // MAINWINDOW_H
