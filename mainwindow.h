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
#include <QPixmap>
#include <QDate>
#include <QTime>
#include <QTextStream>
#include <errorform.h>

//размеры пакетов данных (первые четыре байта всегда содержат начальный, адрес отправителя, адрес получателя и код сообщения, последние два байта - контрольная сумма)
//тип сообщения 1 - 6 байт, 17 - 16 байт, 34 - 1 байт, 255 - 0 байт
//итого весь пакет ответа: 1 - 12 байт, 17 - 22 байт, 34 - 7 байт, 255 - 6 байт

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
    QByteArray otvet;
    short otvetPoluchen; //0 - не получен, 1 - получен
    short errorStatus;//0 - нет ошибок порта, 1 - есть ошибки порта
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
};
struct BSWVprov //создание структуры
{
    QString name; //шифр канала
    QString namePort; //присвоенное имя порта
    QByteArray otvet;
    short otvetPoluchen; //0 - не получен, 1 - получен
};
struct BSWVnomerMK //создание структуры
{
    QString name; //шифр канала
    QString namePort; //присвоенное имя порта
    QString nMK; //номер МУКа, 1 - 1 МК, 2- 2 МК
    QString nChan;//номер канала, 0 - основной, 1 - резервный
    QByteArray otvet;
    short otvetPoluchen; //0 - не получен, 1 - получен
};



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    ErrorForm *window;
    unsigned char data [6];
    unsigned char dataT [6];
    unsigned char dataProv [6];
    unsigned char dataNomer [6];
    QString name;
    int baudrate = 115200;
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
    int otvetTelemSize = 12;
    int otvetTarirSize = 22;
    int otvetMKSize = 7;
    int otvetProvSize = 6;
    QString error;
    QString a;

public:

    QTimer *timerZaprosaTelem;
    QTimer *timerZaprosaTarir;
    QTimer *timerZaprosaProv;
    QTimer *timerVivod;
    QTimer *timerReconnect;
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
    QTime time;
    QFile fileError;


private:


public slots:
   void Vivod(); //Вывод телеметрии в таблицу
   void OtpravkaZaprosaTelem ();
   void OtpravkaZaprosaTarir ();
   void OtpravkaZaprosaNomer();
   void OtpravkaZaprosaProv();
   void Print(QString dat);
   void Analize(QByteArray otvet, QString comName);
   void Kompanovka(QByteArray dataRead, QString comName);
   QString getPortName(QString dis, QString serial);
   void TimerVivodStart();
   void TimerProvStart();
   void TimerTarirStart();
   void Knopka();
   void ChangeColor();
   void ProverkaNomera();
   void WriteInFile();
   void WriteInFileError(QString error);
    void LoadSettings();
    void ErrorAnalyzer(QSerialPort::SerialPortError error,QString portName);
    void Reconnect( );
    void ErrorMessage();
signals:
    //void savesettings(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);
   void savesettings1(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);
   void savesettings2(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);
   void savesettings3(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);
   void savesettings4(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);
   void savesettings5(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);
   void savesettings6(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);
   void writeData(QByteArray dataQ);
   void con1();void con2();void con3();void con4();void con5();void con6();
   void readyToAnalize(QByteArray otvet, QString comName);
   void errorMessage(QString);
   void errorReconnect(QString);

private slots:
   void on_btnNomer_clicked();
   void on_pushButton_2_clicked();
};
#endif // MAINWINDOW_H
