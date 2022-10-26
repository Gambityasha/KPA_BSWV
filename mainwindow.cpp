#include "mainwindow.h"
#include "ui_mainwindow.h"


unsigned short Crc16(unsigned char *pcBlock, unsigned short len)
{
    const unsigned short Crc16Table[256] = {
        0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
        0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
        0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
        0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
        0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
        0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
        0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
        0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
        0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
        0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
        0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
        0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
        0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
        0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
        0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
        0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
        0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
        0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
        0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
        0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
        0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
        0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
        0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
        0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
        0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
        0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
        0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
        0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
        0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
        0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
        0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
        0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
    };
    unsigned short crc = 0xFFFF;
    while (len--)
        crc = (crc << 8) ^ Crc16Table[(crc >> 8) ^ *pcBlock++]; //^ - исключающее или
    return crc;
}

void  MainWindow::delay(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs(millisecondsToWait);
    while ((QTime::currentTime() < dieTime))
    {
        //	QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        QCoreApplication::processEvents();
    }
}

void MainWindow::LoadSettings()
{
    if (!QFile::exists("ports.ini")){
        QMessageBox::information(this, trUtf8("Внимание!"),trUtf8("Файл настроек не найден!"));
    }
    QString dis1, serial1, dis2, serial2,dis3, serial3,dis4, serial4,dis5, serial5, serial6,dis6;
    QSettings setting("ports.ini", QSettings::IniFormat); //ports.ini файл должен быть в одной папке с exe
    setting.beginGroup("Admin");// [Admin] в ини файле
    AdminTools = setting.value("AdminTools","0").toBool();
    timerDelay=setting.value("timerDelay","1000").toInt();
    if (AdminTools==1){

        stopIfError=setting.value("stopIfError","0").toBool();
    }
    setting.endGroup();
    setting.beginGroup("MK1-osn");// [MK1-osn] в ини файле
    QString status1 = setting.value("work","0").toString();    
    if ( status1 == "on") {
         dis1 = setting.value("description","0").toString();
         serial1 = setting.value("serialNumber","0").toString();
         if (ListOfSerial.contains(serial1)){
             //Ничего не делать
         }else{
             ListOfSerial.append(serial1);
         }
         QString name1 = getPortName(dis1,serial1);
         emit savesettings1(name1, baudrate, databits, parity, stopbits, flowcontrol);
         ListOfBSWVData[0].namePort = name1;
         ListOfBSWVData[0].name = "MK1-osn";
         ListOfBSWVt[0].namePort = name1;
         ListOfBSWVt[0].name = "MK1-osn";
         ListOfBSWVprov[0].namePort = name1;
         ListOfBSWVprov[0].name = "MK1-osn";
         ListOfBSWVnomer[0].namePort = name1;
         ListOfBSWVnomer[0].name = "MK1-osn";
         emit con1();
         ListOfBSWVData[0].on_off_status = 1;
    } else {
        ListOfBSWVData[0].on_off_status = 0;
    }
    setting.endGroup();
    setting.beginGroup("MK1-rez");// [MK1-rez] в ини файле
    QString status2 = setting.value("work","0").toString();
    if ( status2 == "on"){
        dis2 = setting.value("description","0").toString();
        serial2 = setting.value("serialNumber","0").toString();
        if (ListOfSerial.contains(serial2)){
            //Ничего не делать
        }else{
            ListOfSerial.append(serial2);
        }
        QString name2 = getPortName(dis2,serial2);
        emit savesettings2(name2, baudrate, databits, parity, stopbits, flowcontrol);
        ListOfBSWVData[1].namePort = name2;
        ListOfBSWVData[1].name = "MK1-rez";
        ListOfBSWVt[1].namePort = name2;
        ListOfBSWVt[1].name = "MK1-rez";
        ListOfBSWVprov[1].namePort = name2;
        ListOfBSWVprov[1].name = "MK1-rez";
        ListOfBSWVnomer[1].namePort = name2;
        ListOfBSWVnomer[1].name = "MK1-rez";
        emit con2();
        ListOfBSWVData[1].on_off_status = 1;
    }else {
        ListOfBSWVData[1].on_off_status = 0;
    }
    setting.endGroup();
    setting.beginGroup("MK2-osn");// [MK2-osn] в ини файле
    QString status3 = setting.value("work","0").toString();
    if (status3 == "on") {
        dis3 = setting.value("description","0").toString();
        serial3 = setting.value("serialNumber","0").toString();
        if (ListOfSerial.contains(serial3)){
            //Ничего не делать
        }else{
            ListOfSerial.append(serial3);
        }
        QString name3 = getPortName(dis3,serial3);
        emit savesettings3(name3, baudrate, databits, parity, stopbits, flowcontrol);
        ListOfBSWVData[2].namePort = name3;
        ListOfBSWVData[2].name = "MK2-osn";
        ListOfBSWVt[2].namePort = name3;
        ListOfBSWVt[2].name = "MK2-osn";
        ListOfBSWVprov[2].namePort = name3;
        ListOfBSWVprov[2].name = "MK2-osn";
        ListOfBSWVnomer[2].namePort = name3;
        ListOfBSWVnomer[2].name = "MK2-osn";
        emit con3();
        ListOfBSWVData[2].on_off_status = 1;
    }else {
        ListOfBSWVData[2].on_off_status = 0;
    }
    setting.endGroup();
    setting.beginGroup("MK2-rez");// [MK2-rez] в ини файле
    QString status4 = setting.value("work","0").toString();
    if ( status4 == "on"){
        dis4 = setting.value("description","0").toString();
        serial4 = setting.value("serialNumber","0").toString();
        if (ListOfSerial.contains(serial4)){
            //Ничего не делать
        }else{
            ListOfSerial.append(serial4);
        }
        QString name4 = getPortName(dis4,serial4);
        emit savesettings4(name4, baudrate, databits, parity, stopbits, flowcontrol);
        ListOfBSWVData[3].namePort = name4;
        ListOfBSWVData[3].name = "MK2-rez";
        ListOfBSWVt[3].namePort = name4;
        ListOfBSWVt[3].name = "MK2-rez";
        ListOfBSWVprov[3].namePort = name4;
        ListOfBSWVprov[3].name = "MK2-rez";
        ListOfBSWVnomer[3].namePort = name4;
        ListOfBSWVnomer[3].name = "MK2-rez";
        emit con4();
        ListOfBSWVData[3].on_off_status = 1;
    }else {
        ListOfBSWVData[3].on_off_status = 0;
    }
    setting.endGroup();
    setting.beginGroup("MK3-osn");// [MK3-osn] в ини файле
    QString status5 = setting.value("work","0").toString();
    if ( status5 == "on") {
        dis5 = setting.value("description","0").toString();
        serial5 = setting.value("serialNumber","0").toString();
        if (ListOfSerial.contains(serial5)){
            //Ничего не делать
        }else{
            ListOfSerial.append(serial5);
        }
        QString name5 = getPortName(dis5,serial5);
        emit savesettings5(name5, baudrate, databits, parity, stopbits, flowcontrol);
        ListOfBSWVData[4].namePort = name5;
        ListOfBSWVData[4].name = "MK3-osn";
        ListOfBSWVt[4].namePort = name5;
        ListOfBSWVt[4].name = "MK3-osn";
        ListOfBSWVprov[4].namePort = name5;
        ListOfBSWVprov[4].name = "MK3-osn";
        ListOfBSWVnomer[4].namePort = name5;
        ListOfBSWVnomer[4].name = "MK3-osn";
        emit con5();
        ListOfBSWVData[4].on_off_status = 1;
    }else {
        ListOfBSWVData[4].on_off_status = 0;
    }
    setting.endGroup();
    setting.beginGroup("MK3-rez");// [MK3-rez] в ини файле
    QString status6 = setting.value("work","0").toString();
    if (status6 == "on"){
        dis6 = setting.value("description","0").toString();
        serial6 = setting.value("serialNumber","0").toString();
        if (ListOfSerial.contains(serial6)){
            //Ничего не делать
        }else{
            ListOfSerial.append(serial6);
        }
        QString name6 = getPortName(dis6,serial6);
        emit savesettings6(name6, baudrate, databits, parity, stopbits, flowcontrol);
        ListOfBSWVData[5].namePort = name6;
        ListOfBSWVData[5].name = "MK3-rez";
        ListOfBSWVt[5].namePort = name6;
        ListOfBSWVt[5].name = "MK3-rez";
        ListOfBSWVprov[5].namePort = name6;
        ListOfBSWVprov[5].name = "MK3-rez";
        ListOfBSWVnomer[5].namePort = name6;
        ListOfBSWVnomer[5].name = "MK3-rez";
        emit con6();
        ListOfBSWVData[5].on_off_status = 1;
    }else {
        ListOfBSWVData[5].on_off_status = 0;
    }
    setting.endGroup();
}


void MainWindow::ErrorMessage(bool status)
{
    ui->lblError->setVisible(status);
}
//Тут добавить обработку для снятия реконнекта при отсутствии ошибок

void MainWindow::ErrorAnalyzer(QSerialPort::SerialPortError error,QString portName)
{

    if ((error!=0)&&(error!=12)){

        for (int i=0;i<ListOfBSWVData.size();i++){
            if (ListOfBSWVData[i].namePort==portName){
                ListOfBSWVData[i].errorStatus=1;
            }
        }
        if (timerReconnect->isActive()){
        //ничего не делать
        }
        else {
            timerReconnect->start();
            if (!ui->pbCancelReconnect->isVisible()){
                ui->pbCancelReconnect->setVisible(true);
            }
            if (ui->lblError->isVisible()){//ничего не делать
            }else{
                if (firstErrorOpen==true){
                    window->open();
                    firstErrorOpen=false;
                }else{
                    ui->lblError->setVisible(true);
                }
            }
        }
    }else {if ((error==0)||(error==12)) {
        for (int i=0;i<ListOfBSWVData.size();i++){
            if (ListOfBSWVData[i].namePort==portName){
                ListOfBSWVData[i].errorStatus=0;
            }
        }
        if ((ListOfBSWVData.at(0).errorStatus==0)&(ListOfBSWVData.at(1).errorStatus==0)&(ListOfBSWVData.at(2).errorStatus==0)&
           (ListOfBSWVData.at(3).errorStatus==0)& (ListOfBSWVData.at(4).errorStatus==0)&(ListOfBSWVData.at(5).errorStatus==0)){
           timerReconnect->stop();
           delay(2000);
           ui->pbCancelReconnect->setVisible(false);
           window->close();
           ui->lblError->setVisible(false);
        }
    }
}
}

void MainWindow::Reconnect( )
{    
    QString dis1, serial1, dis2, serial2,dis3, serial3,dis4, serial4,dis5, serial5,dis6, serial6;
    QSettings setting("ports.ini", QSettings::IniFormat); //ports.ini файл должен быть в одной папке с exe
    if (ListOfBSWVData[0].errorStatus==1) {
        setting.beginGroup("MK1-osn");// [MK1-osn] в ини файле
        QString status1 = setting.value("work","on").toString();
        if (status1 == "on") {
             dis1 = setting.value("description","0").toString();
             serial1 = setting.value("serialNumber","0").toString();
             QString name1 = getPortName(dis1,serial1);
             emit savesettings1(name1, baudrate, databits, parity, stopbits, flowcontrol);             
             emit con1();
             //test


             //...test
        }
        setting.endGroup();
    }
    if (ListOfBSWVData[1].errorStatus==1) {
        setting.beginGroup("MK1-rez");// [MK1-rez] в ини файле
        QString status2 = setting.value("work","on").toString();
        if (status2 == "on"){
            dis2 = setting.value("description","0").toString();
            serial2 = setting.value("serialNumber","0").toString();
            QString name2 = getPortName(dis2,serial2);
            emit savesettings2(name2, baudrate, databits, parity, stopbits, flowcontrol);
            emit con2();
        }
        setting.endGroup();
    }
    if (ListOfBSWVData[2].errorStatus==1) {
        setting.beginGroup("MK2-osn");// [MK2-osn] в ини файле
        QString status3 = setting.value("work","on").toString();
        if (status3 == "on") {
            dis3 = setting.value("description","0").toString();
            serial3 = setting.value("serialNumber","0").toString();
            QString name3 = getPortName(dis3,serial3);
            emit savesettings3(name3, baudrate, databits, parity, stopbits, flowcontrol);
            emit con3();
        }
        setting.endGroup();
    }
    if (ListOfBSWVData[3].errorStatus==1) {
        setting.beginGroup("MK2-rez");// [MK2-rez] в ини файле
        QString status4 = setting.value("work","on").toString();
        if (status4 == "on"){
            dis4 = setting.value("description","0").toString();
            serial4 = setting.value("serialNumber","0").toString();
            QString name4 = getPortName(dis4,serial4);
            emit savesettings4(name4, baudrate, databits, parity, stopbits, flowcontrol);
            emit con4();
        }
        setting.endGroup();
    }
    if (ListOfBSWVData[4].errorStatus==1) {
        setting.beginGroup("MK3-osn");// [MK3-osn] в ини файле
        QString status5 = setting.value("work","on").toString();
        if (status5 == "on") {
            dis5 = setting.value("description","0").toString();
            serial5 = setting.value("serialNumber","0").toString();
            QString name5 = getPortName(dis5,serial5);
            emit savesettings5(name5, baudrate, databits, parity, stopbits, flowcontrol);
            emit con5();
        }
        setting.endGroup();
     }
     if (ListOfBSWVData[5].errorStatus==1) {
         setting.beginGroup("MK3-rez");// [MK3-rez] в ини файле
         QString status6 = setting.value("work","on").toString();
         if (status6 == "on"){
             dis6 = setting.value("description","0").toString();
             serial6 = setting.value("serialNumber","0").toString();
             QString name6 = getPortName(dis6,serial6);
             emit savesettings6(name6, baudrate, databits, parity, stopbits, flowcontrol);
             emit con6();
         }
         setting.endGroup();
     }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{    
    ui->setupUi(this);
    qRegisterMetaType<QSerialPort::SerialPortError>();//Очень важное дополнение, чтобы при мультипотоковой работе сообщения об ошибках выдавались
    //и обрабатывались механизмами реконнекта
    ui->pbCancelReconnect->setVisible(false);
    setWindowIcon(QIcon("KPABSWV.png"));
    ui->tabWidget->setTabEnabled(0,true);
    ui->lblError->setVisible(false);
    ui->tblBSWV->setEnabled(false);
    QPixmap pix("redbtn.png");//указание расположения картинки и создание объекта класса
    QPixmap pix1("greenbtn.png");
    ui->greenMK1o->setPixmap(pix1.scaled(35,35,Qt::KeepAspectRatio));
    ui->redMK1o->setPixmap(pix.scaled(35,35,Qt::KeepAspectRatio));//присвоение лейблу этой картинки с уменьшением ее размеров
    ui->greenMK2o->setPixmap(pix1.scaled(35,35,Qt::KeepAspectRatio));
    ui->redMK2o->setPixmap(pix.scaled(35,35,Qt::KeepAspectRatio));//присвоение лейблу этой картинки с уменьшением ее размеров
    ui->greenMK3o->setPixmap(pix1.scaled(35,35,Qt::KeepAspectRatio));
    ui->redMK3o->setPixmap(pix.scaled(35,35,Qt::KeepAspectRatio));//присвоение лейблу этой картинки с уменьшением ее размеров
    ui->greenMK1r->setPixmap(pix1.scaled(35,35,Qt::KeepAspectRatio));
    ui->redMK1r->setPixmap(pix.scaled(35,35,Qt::KeepAspectRatio));//присвоение лейблу этой картинки с уменьшением ее размеров
    ui->greenMK2r->setPixmap(pix1.scaled(35,35,Qt::KeepAspectRatio));
    ui->redMK2r->setPixmap(pix.scaled(35,35,Qt::KeepAspectRatio));//присвоение лейблу этой картинки с уменьшением ее размеров
    ui->greenMK3r->setPixmap(pix1.scaled(35,35,Qt::KeepAspectRatio));
    ui->redMK3r->setPixmap(pix.scaled(35,35,Qt::KeepAspectRatio));//присвоение лейблу этой картинки с уменьшением ее размеров
    ui->greenMK1o->setVisible(false);
    ui->redMK1o->setVisible(true);
    ui->greenMK1r->setVisible(false);
    ui->redMK1r->setVisible(true);
    ui->greenMK2o->setVisible(false);
    ui->redMK2o->setVisible(true);
    ui->greenMK2r->setVisible(false);
    ui->redMK2r->setVisible(true);
    ui->greenMK3o->setVisible(false);
    ui->redMK3o->setVisible(true);
    ui->greenMK3r->setVisible(false);
    ui->redMK3r->setVisible(true);
    ui->pbReconnectRS485->setVisible(false);
    BSWV.name = "MK1-osn"; BSWV.namePort = "Com";BSWV.icap2=0; BSWV.icap1 = 0; BSWV.u2 = 0; BSWV.u1 = 0;BSWV.tcorp2 = 0; BSWV.tcorp1=0;
    ListOfBSWVData.append(BSWV);
    BSWV.name = "MK1-rez"; BSWV.namePort = "Com";BSWV.icap2=0; BSWV.icap1 = 0; BSWV.u2 = 0; BSWV.u1 = 0;BSWV.tcorp2 = 0; BSWV.tcorp1=0;
    ListOfBSWVData.append(BSWV);
    BSWV.name = "MK2-osn"; BSWV.namePort = "Com";BSWV.icap2=0; BSWV.icap1 = 0; BSWV.u2 = 0; BSWV.u1 = 0;BSWV.tcorp2 = 0; BSWV.tcorp1=0;
    ListOfBSWVData.append(BSWV);
    BSWV.name = "MK2-rez"; BSWV.namePort = "Com";BSWV.icap2=0; BSWV.icap1 = 0; BSWV.u2 = 0; BSWV.u1 = 0;BSWV.tcorp2 = 0; BSWV.tcorp1=0;
    ListOfBSWVData.append(BSWV);
    BSWV.name = "MK3-osn"; BSWV.namePort = "Com";BSWV.icap2=0; BSWV.icap1 = 0; BSWV.u2 = 0; BSWV.u1 = 0;BSWV.tcorp2 = 0; BSWV.tcorp1=0;
    ListOfBSWVData.append(BSWV);
    BSWV.name = "MK3-rez"; BSWV.namePort = "Com";BSWV.icap2=0; BSWV.icap1 = 0; BSWV.u2 = 0; BSWV.u1 = 0;BSWV.tcorp2 = 0; BSWV.tcorp1=0;
    ListOfBSWVData.append(BSWV);

    BSWVt.name = "MK1-osn"; BSWVt.namePort = "Com";BSWVt.icap2=0; BSWVt.icap1 = 0; BSWVt.u2 = 0; BSWVt.u1 = 0;BSWVt.tcorp2 = 0; BSWVt.tcorp1=0; BSWVt.uref=0;
    BSWVt.otvetPoluchen=0;
    ListOfBSWVt.append(BSWVt);
    BSWVt.name = "MK1-rez"; BSWVt.namePort = "Com";BSWVt.icap2=0; BSWVt.icap1 = 0; BSWVt.u2 = 0; BSWVt.u1 = 0;BSWVt.tcorp2 = 0; BSWVt.tcorp1=0;BSWVt.uref=0;
    BSWVt.otvetPoluchen=0;
    ListOfBSWVt.append(BSWVt);
    BSWVt.name = "MK2-osn"; BSWVt.namePort = "Com";BSWVt.icap2=0; BSWVt.icap1 = 0; BSWVt.u2 = 0; BSWVt.u1 = 0;BSWVt.tcorp2 = 0; BSWVt.tcorp1=0;BSWVt.uref=0;
    BSWVt.otvetPoluchen=0;
    ListOfBSWVt.append(BSWVt);
    BSWVt.name = "MK2-rez"; BSWVt.namePort = "Com";BSWVt.icap2=0; BSWVt.icap1 = 0; BSWVt.u2 = 0; BSWVt.u1 = 0;BSWVt.tcorp2 = 0; BSWVt.tcorp1=0;BSWVt.uref=0;
    BSWVt.otvetPoluchen=0;
    ListOfBSWVt.append(BSWVt);
    BSWVt.name = "MK3-osn"; BSWVt.namePort = "Com";BSWVt.icap2=0; BSWVt.icap1 = 0; BSWVt.u2 = 0; BSWVt.u1 = 0;BSWVt.tcorp2 = 0; BSWVt.tcorp1=0;BSWVt.uref=0;
    BSWVt.otvetPoluchen=0;
    ListOfBSWVt.append(BSWVt);
    BSWVt.name = "MK3-rez"; BSWVt.namePort = "Com";BSWVt.icap2=0; BSWVt.icap1 = 0; BSWVt.u2 = 0; BSWVt.u1 = 0;BSWVt.tcorp2 = 0; BSWVt.tcorp1=0;BSWVt.uref=0;
    BSWVt.otvetPoluchen=0;
    ListOfBSWVt.append(BSWVt);

    BSWVp.name = "MK1-osn"; BSWVp.namePort = "Com"; BSWVp.otvetPoluchen=0;
    ListOfBSWVprov.append(BSWVp);
    BSWVp.name = "MK1-rez"; BSWVp.namePort = "Com";BSWVp.otvetPoluchen=0;
    ListOfBSWVprov.append(BSWVp);
    BSWVp.name = "MK2-osn"; BSWVp.namePort = "Com";BSWVp.otvetPoluchen=0;
    ListOfBSWVprov.append(BSWVp);
    BSWVp.name = "MK2-rez"; BSWVp.namePort = "Com";BSWVp.otvetPoluchen=0;
    ListOfBSWVprov.append(BSWVp);
    BSWVp.name = "MK3-osn"; BSWVp.namePort = "Com";BSWVp.otvetPoluchen=0;
    ListOfBSWVprov.append(BSWVp);
    BSWVp.name = "MK3-rez"; BSWVp.namePort = "Com";BSWVp.otvetPoluchen=0;
    ListOfBSWVprov.append(BSWVp);

    BSWVnomer.name = "MK1-osn"; BSWVnomer.namePort = "Com";BSWVnomer.otvetPoluchen=0; BSWVnomer.nMK = "MK1";BSWVnomer.nChan = "-резервный";
    ListOfBSWVnomer.append(BSWVnomer);
    BSWVnomer.name = "MK1-rez"; BSWVnomer.namePort = "Com";BSWVnomer.otvetPoluchen=0; BSWVnomer.nMK = "MK1";BSWVnomer.nChan = "-резервный";
    ListOfBSWVnomer.append(BSWVnomer);
    BSWVnomer.name = "MK2-osn"; BSWVnomer.namePort = "Com";BSWVnomer.otvetPoluchen=0; BSWVnomer.nMK = "MK1";BSWVnomer.nChan = "-резервный";
    ListOfBSWVnomer.append(BSWVnomer);
    BSWVnomer.name = "MK2-rez"; BSWVnomer.namePort = "Com";BSWVnomer.otvetPoluchen=0; BSWVnomer.nMK = "MK1";BSWVnomer.nChan = "-резервный";
    ListOfBSWVnomer.append(BSWVnomer);
    BSWVnomer.name = "MK3-osn"; BSWVnomer.namePort = "Com";BSWVnomer.otvetPoluchen=0; BSWVnomer.nMK = "MK1";BSWVnomer.nChan = "-резервный";
    ListOfBSWVnomer.append(BSWVnomer);
    BSWVnomer.name = "MK3-rez"; BSWVnomer.namePort = "Com";BSWVnomer.otvetPoluchen=0; BSWVnomer.nMK = "MK1";BSWVnomer.nChan = "-резервный";
    ListOfBSWVnomer.append(BSWVnomer);

    ui->tblNomer->setRowCount(2);
    ui->tblNomer->setColumnCount(3);
    ui->tblNomer->setHorizontalHeaderLabels(QStringList()<<"МК1"<<"МК2"<<"МК3"); //заполнение заголовков столбцов
    ui->tblNomer->setVerticalHeaderLabels(QStringList()<<"Основной"<<"Резервный");
    ui->tblBSWV->setRowCount(6); //задание количества строк таблицы
    ui->tblBSWV->setColumnCount(6); //задание количества колонок таблицы
    ui->tblBSWV->setHorizontalHeaderLabels(QStringList()<<"МК1-осн"<<"МК1-рез"<<"МК2-осн"<<"МК2-рез"<<"МК3-осн"<<"МК3-рез"); //заполнение заголовков столбцов
    ui->tblBSWV->setVerticalHeaderLabels(QStringList()<<"Суммарный ток нагрузки 2"<<"Суммарный ток нагрузки 1"<<"Напряжение на силовых шинах 2" //заполнение заголовков строк
        <<"Напряжение на силовых шинах 1"<<"Температура 2 корпуса прибора"<<"Температура 1 корпуса прибора");
    ui->tblBSWV->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tblBSWV->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tblAcp->setRowCount(7); //задание количества строк таблицы
    ui->tblAcp->setColumnCount(6); //задание количества колонок таблицы
    ui->tblAcp->setHorizontalHeaderLabels(QStringList()<<"МК1-осн"<<"МК1-рез"<<"МК2-осн"<<"МК2-рез"<<"МК3-осн"<<"МК3-рез"); //заполнение заголовков столбцов
    ui->tblAcp->setVerticalHeaderLabels(QStringList()<<"Суммарный ток нагрузки 2"<<"Суммарный ток нагрузки 1"<<"Напряжение на силовых шинах 2" //заполнение заголовков строк
        <<"Напряжение на силовых шинах 1"<<"Температура 2 корпуса прибора"<<"Температура 1 корпуса прибора"<<"Опорное напряжение Uref ");
    ui->tblAcp->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tblAcp->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->tabWidget->setSizePolicy(QSizePolicy::Stretch);

    //-----------------Формирование исходящего сообщения для БСШ-В (тип 1 - обычный обмен)---------------------
    data[0] = startByte;
    data[1] = outAdr;
    data[2] = inAdr;
    data[3] = messType1;
    unsigned short len = 4;
    unsigned char upper = Crc16(data,len)>>8; //получение старшего байта контрольной суммы
    unsigned char lower = Crc16(data,len);
//  unsigned short lower1 = Crc16(pcBlock,len)<<8;
//  unsigned char lower = lower1>>8; //получение младшего байта контрольной суммы
    data[4] = upper;
    data[5] = lower;
    dataQ = QByteArray(reinterpret_cast<char*>(data), sizeof(data));
    //dataQ = QByteArray::fromRawData((char*)data,sizeof(data));
//  unsigned short full = (upper*256)+lower; // получение общего значения контрольной суммы из старшего и младшего байтов
// unsigned short full = (unsigned short) (upper<<8) | lower; // получение общего значения контрольной суммы из старшего и младшего байтов с помощью побитового сложения
//-----------Конец формирования исходящего сообщения для БСШ-В (тип 1 - телеметрия)-----------
//-----------Формирование исходящего сообщения для БСШ-В (тип 17 - данные АЦП для калибровки БСШ-В)--------
    dataT[0] = startByte;
    dataT[1] = outAdr;
    dataT[2] = inAdr;
    dataT[3] = messType17;
    unsigned char upperT = Crc16(dataT,len)>>8; //получение старшего байта контрольной суммы
    unsigned char lowerT = Crc16(dataT,len);
    dataT[4] = upperT;
    dataT[5] = lowerT;
    dataQt = QByteArray(reinterpret_cast<char*>(dataT), sizeof(dataT));
//-----------Конец формирования исходящего сообщения для БСШ-В (тип 17 - данные АЦП для калибровки БСШ-В)-----------
//-----------Формирование исходящего сообщения для БСШ-В (тип 255 - проверка связи)--------
    dataProv[0] = startByte;
    dataProv[1] = outAdr;
    dataProv[2] = inAdr;
    dataProv[3] = messType255;
    unsigned char upperProv = Crc16(dataProv,len)>>8; //получение старшего байта контрольной суммы
    unsigned char lowerProv = Crc16(dataProv,len);
    dataProv[4] = upperProv;
    dataProv[5] = lowerProv;
    dataQProv = QByteArray(reinterpret_cast<char*>(dataProv), sizeof(dataProv));
    //dataQProv = QByteArray::fromRawData((char*)dataProv,sizeof(dataProv));
//-----------Конец формирования исходящего сообщения для БСШ-В (тип 255 - проверка связи)-----------
//-----------Формирование исходящего сообщения для БСШ-В (тип 34 - проверка номера МУКа)--------
    dataNomer[0] = startByte;
    dataNomer[1] = outAdr;
    dataNomer[2] = inAdr;
    dataNomer[3] = messType34;
    unsigned char upperNomer = Crc16(dataNomer,len)>>8; //получение старшего байта контрольной суммы
    unsigned char lowerNomer = Crc16(dataNomer,len);
    dataNomer[4] = upperNomer;
    dataNomer[5] = lowerNomer;
    dataQNomer = QByteArray(reinterpret_cast<char*>(dataNomer), sizeof(dataNomer));
    //-----------Конец формирования исходящего сообщения для БСШ-В (тип 34 - проверка номера МУКа)-----------
    timerRequest = new QTimer();

    timerReconnect = new QTimer();
    timerReconnect->setInterval(1500);

    timerCloseErrorWindow = new QTimer();
    timerCloseErrorWindow->setInterval(5000);
    logYear = QDate::currentDate().toString("yyyy");
    logMonth = QDate::currentDate().toString("MM");
    dirName = "../logs/"+logYear+"/"+logMonth+"/";
    dir.mkdir("../logs");
    dir.mkdir("../logs/"+logYear);
    dir.mkdir("../logs/"+logYear+"/"+logMonth);
    dir.mkdir("../logs/"+logYear+"/"+logMonth+"/MK1o");
    dir.mkdir("../logs/"+logYear+"/"+logMonth+"/MK2o");
    dir.mkdir("../logs/"+logYear+"/"+logMonth+"/MK3o");
    dir.mkdir("../logs/"+logYear+"/"+logMonth+"/MK1r");
    dir.mkdir("../logs/"+logYear+"/"+logMonth+"/MK2r");
    dir.mkdir("../logs/"+logYear+"/"+logMonth+"/MK3r");
    dir.mkdir("../logs/"+logYear+"/"+logMonth+"/Errors");
    dir.mkdir("../logs/"+logYear+"/"+logMonth+"/AllChannels");
    dir.mkdir("../logs/"+logYear+"/"+logMonth+"/ACP");
    connect(timerRequest,SIGNAL(timeout()), this,SLOT(RequestSender()));
    connect(this, SIGNAL(savesettings1(QString,int,int,int,int,int)),PortMK1osn,SLOT(Write_Settings_Port(QString,int,int,int,int,int)));//Слот - ввод настроек!
    connect(this, SIGNAL(savesettings2(QString,int,int,int,int,int)),PortMK1rez,SLOT(Write_Settings_Port(QString,int,int,int,int,int)));//Слот - ввод настроек!
    connect(this, SIGNAL(savesettings3(QString,int,int,int,int,int)),PortMK2osn,SLOT(Write_Settings_Port(QString,int,int,int,int,int)));//Слот - ввод настроек!
    connect(this, SIGNAL(savesettings4(QString,int,int,int,int,int)),PortMK2rez,SLOT(Write_Settings_Port(QString,int,int,int,int,int)));//Слот - ввод настроек!
    connect(this, SIGNAL(savesettings5(QString,int,int,int,int,int)),PortMK3osn,SLOT(Write_Settings_Port(QString,int,int,int,int,int)));//Слот - ввод настроек!
    connect(this, SIGNAL(savesettings6(QString,int,int,int,int,int)),PortMK3rez,SLOT(Write_Settings_Port(QString,int,int,int,int,int)));//Слот - ввод настроек!

    connect(this, SIGNAL(writeData1(QByteArray)),PortMK1osn,SLOT(WriteToPort(QByteArray)));
    connect(this, SIGNAL(writeData2(QByteArray)),PortMK2osn,SLOT(WriteToPort(QByteArray)));
    connect(this, SIGNAL(writeData3(QByteArray)),PortMK3osn,SLOT(WriteToPort(QByteArray)));
    connect(this, SIGNAL(writeData4(QByteArray)),PortMK1rez,SLOT(WriteToPort(QByteArray)));
    connect(this, SIGNAL(writeData5(QByteArray)),PortMK2rez,SLOT(WriteToPort(QByteArray)));
    connect(this, SIGNAL(writeData6(QByteArray)),PortMK3rez,SLOT(WriteToPort(QByteArray)));

    connect(this, SIGNAL(testRSMK1o(QByteArray)),PortMK1osn,SLOT(WriteToPortTestRS(QByteArray)));
    connect(this, SIGNAL(testRSMK2o(QByteArray)),PortMK2osn,SLOT(WriteToPortTestRS(QByteArray)));
    connect(this, SIGNAL(testRSMK3o(QByteArray)),PortMK3osn,SLOT(WriteToPortTestRS(QByteArray)));
    connect(this, SIGNAL(testRSMK1r(QByteArray)),PortMK1rez,SLOT(WriteToPortTestRS(QByteArray)));
    connect(this, SIGNAL(testRSMK2r(QByteArray)),PortMK2rez,SLOT(WriteToPortTestRS(QByteArray)));
    connect(this, SIGNAL(testRSMK3r(QByteArray)),PortMK3rez,SLOT(WriteToPortTestRS(QByteArray)));
    connect(this, SIGNAL(con1()),PortMK1osn,SLOT(ConnectPort()));
    connect(this, SIGNAL(con2()),PortMK1rez,SLOT(ConnectPort()));
    connect(this, SIGNAL(con3()),PortMK2osn,SLOT(ConnectPort()));
    connect(this, SIGNAL(con4()),PortMK2rez,SLOT(ConnectPort()));
    connect(this, SIGNAL(con5()),PortMK3osn,SLOT(ConnectPort()));
    connect(this, SIGNAL(con6()),PortMK3rez,SLOT(ConnectPort()));
    connect(this, SIGNAL(discon1()),PortMK1osn,SLOT(DisconnectPort()));
    connect(this, SIGNAL(discon2()),PortMK1rez,SLOT(DisconnectPort()));
    connect(this, SIGNAL(discon3()),PortMK2osn,SLOT(DisconnectPort()));
    connect(this, SIGNAL(discon4()),PortMK2rez,SLOT(DisconnectPort()));
    connect(this, SIGNAL(discon5()),PortMK3osn,SLOT(DisconnectPort()));
    connect(this, SIGNAL(discon6()),PortMK3rez,SLOT(DisconnectPort()));

    connect(PortMK1osn, SIGNAL(error_(QString)), this, SLOT(Print(QString)));//,Qt::QueuedConnection);//Лог ошибок соединения
    connect(PortMK2osn, SIGNAL(error_(QString)), this, SLOT(Print(QString)));//,Qt::QueuedConnection);
    connect(PortMK3osn, SIGNAL(error_(QString)), this, SLOT(Print(QString)));//,Qt::QueuedConnection);
    connect(PortMK1rez, SIGNAL(error_(QString)), this, SLOT(Print(QString)));//,Qt::QueuedConnection);
    connect(PortMK2rez, SIGNAL(error_(QString)), this, SLOT(Print(QString)));//,Qt::QueuedConnection);
    connect(PortMK3rez, SIGNAL(error_(QString)), this, SLOT(Print(QString)));//,Qt::QueuedConnection);

    PortMK1osn->moveToThread(thread_MK1osn);
    PortMK2osn->moveToThread(thread_MK2osn);
    PortMK3osn->moveToThread(thread_MK3osn);
    PortMK1rez->moveToThread(thread_MK1rez);
    PortMK2rez->moveToThread(thread_MK2rez);
    PortMK3rez->moveToThread(thread_MK3rez);

    connect(PortMK1osn, SIGNAL(sendBSWVtm(QByteArray,QString)),this,SLOT(Kompanovka(QByteArray,QString)),Qt::QueuedConnection);
    connect(PortMK1rez, SIGNAL(sendBSWVtm(QByteArray,QString)),this,SLOT(Kompanovka(QByteArray,QString)),Qt::QueuedConnection);
    connect(PortMK2osn, SIGNAL(sendBSWVtm(QByteArray,QString)),this,SLOT(Kompanovka(QByteArray,QString)),Qt::QueuedConnection);
    connect(PortMK2rez, SIGNAL(sendBSWVtm(QByteArray,QString)),this,SLOT(Kompanovka(QByteArray,QString)),Qt::QueuedConnection);
    connect(PortMK3rez, SIGNAL(sendBSWVtm(QByteArray,QString)),this,SLOT(Kompanovka(QByteArray,QString)),Qt::QueuedConnection);
    connect(PortMK3osn, SIGNAL(sendBSWVtm(QByteArray,QString)),this,SLOT(Kompanovka(QByteArray,QString)),Qt::QueuedConnection);    
    connect(this, SIGNAL(readyToAnalize(QByteArray,QString)),this,SLOT(Analize(QByteArray,QString)));
    connect(this, SIGNAL(errorMessageThis(QString)), this,SLOT(Print(QString)),Qt::QueuedConnection); //Не тот же эррор месадж, что от порта
    connect(this, SIGNAL(errorMessageThis(QString)), this,SLOT(WriteInFileError(QString)));

    connect(timerReconnect, SIGNAL(timeout()), this, SLOT(Reconnect()));
    connect(window,SIGNAL(hideError(bool)),this,SLOT(ErrorMessage(bool)));

    connect(this, SIGNAL(writeToPort1(int,QByteArray,int)),PortMK1osn,SLOT(WriteToPort(int,QByteArray,int)));
    connect(this, SIGNAL(writeToPort2(int,QByteArray,int)),PortMK1rez,SLOT(WriteToPort(int,QByteArray,int)));
    connect(this, SIGNAL(writeToPort3(int,QByteArray,int)),PortMK2osn,SLOT(WriteToPort(int,QByteArray,int)));
    connect(this, SIGNAL(writeToPort4(int,QByteArray,int)),PortMK2rez,SLOT(WriteToPort(int,QByteArray,int)));
    connect(this, SIGNAL(writeToPort5(int,QByteArray,int)),PortMK3osn,SLOT(WriteToPort(int,QByteArray,int)));
    connect(this, SIGNAL(writeToPort6(int,QByteArray,int)),PortMK3rez,SLOT(WriteToPort(int,QByteArray,int)));
    connect(thread_MK1osn,SIGNAL(finished()),this,SLOT(ErrorThread()));
    connect(thread_MK2osn,SIGNAL(finished()),this,SLOT(ErrorThread()));
    connect(thread_MK3osn,SIGNAL(finished()),this,SLOT(ErrorThread()));
    connect(thread_MK1rez,SIGNAL(finished()),this,SLOT(ErrorThread()));
    connect(thread_MK2rez,SIGNAL(finished()),this,SLOT(ErrorThread()));
    connect(thread_MK3rez,SIGNAL(finished()),this,SLOT(ErrorThread()));

    connect(this,SIGNAL(destroyed()),thread_MK1osn,SLOT(quit()));
    connect(this,SIGNAL(destroyed()),thread_MK2osn,SLOT(quit()));
    connect(this,SIGNAL(destroyed()),thread_MK3osn,SLOT(quit()));
    connect(this,SIGNAL(destroyed()),thread_MK1rez,SLOT(quit()));
    connect(this,SIGNAL(destroyed()),thread_MK2rez,SLOT(quit()));
    connect(this,SIGNAL(destroyed()),thread_MK3rez,SLOT(quit()));

    thread_MK1osn->start();//(QThread::TimeCriticalPriority);//Создаем поток для порта
    thread_MK1rez->start();//(QThread::TimeCriticalPriority);
    thread_MK2osn->start();//(QThread::TimeCriticalPriority);
    thread_MK2rez->start();//(QThread::TimeCriticalPriority);
    thread_MK3osn->start();//(QThread::TimeCriticalPriority);
    thread_MK3rez->start();//(QThread::TimeCriticalPriority);
     LoadSettings();

    timerRequest->setInterval(timerDelay);
    ui->tabWidget->setCurrentIndex(0);
    if (AdminTools==0){
        ui->consolTest->setVisible(false);
        ui->tabWidget->removeTab(4);
    }else{
        ui->consolTest->setVisible(true);
    }

    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
        {
        if (ListOfSerialFact.contains(serialPortInfo.serialNumber())){
            //Ничего не делать
        }else{
            ListOfSerialFact.append(serialPortInfo.serialNumber());
        }
        if (AdminTools==1){
            Print(serialPortInfo.portName()+" Description: "+serialPortInfo.description()+" | Serial: "+serialPortInfo.serialNumber());
        }
    }

    for (int i=0;i<ListOfSerial.size();i++)  {
        if (ListOfSerialFact.indexOf(ListOfSerial.at(i))==-1){
            Print("Не подключен конвертер интерфейсов RS-485 (серийный номер "+ListOfSerial.at(i)+")");
            converterError_status=true;
            ui->pbReconnectRS485->setVisible(true);
        }
    }
    connect(PortMK1osn, SIGNAL(errorMessage(QSerialPort::SerialPortError,QString)),this,SLOT(ErrorAnalyzer(QSerialPort::SerialPortError,QString)));
    connect(PortMK2osn, SIGNAL(errorMessage(QSerialPort::SerialPortError,QString)),this,SLOT(ErrorAnalyzer(QSerialPort::SerialPortError,QString)));
    connect(PortMK3osn, SIGNAL(errorMessage(QSerialPort::SerialPortError,QString)),this,SLOT(ErrorAnalyzer(QSerialPort::SerialPortError,QString)));
    connect(PortMK1rez, SIGNAL(errorMessage(QSerialPort::SerialPortError,QString)),this,SLOT(ErrorAnalyzer(QSerialPort::SerialPortError,QString)));
    connect(PortMK2rez, SIGNAL(errorMessage(QSerialPort::SerialPortError,QString)),this,SLOT(ErrorAnalyzer(QSerialPort::SerialPortError,QString)));
    connect(PortMK3rez, SIGNAL(errorMessage(QSerialPort::SerialPortError,QString)),this,SLOT(ErrorAnalyzer(QSerialPort::SerialPortError,QString)));
}

void MainWindow::on_btnNomer_clicked()
{

    QTableWidgetItem *itm0_0 = new QTableWidgetItem("-");
    ui->tblNomer->setItem(0,0,itm0_0);
    QTableWidgetItem *itm1_0 = new QTableWidgetItem("-");
    ui->tblNomer->setItem(1,0,itm1_0);
    QTableWidgetItem *itm0_1 = new QTableWidgetItem("-");
    ui->tblNomer->setItem(0,1,itm0_1);
    QTableWidgetItem *itm1_1 = new QTableWidgetItem("-");
    ui->tblNomer->setItem(1,1,itm1_1);
    QTableWidgetItem *itm0_2 = new QTableWidgetItem("-");
    ui->tblNomer->setItem(0,2,itm0_2);
    QTableWidgetItem *itm1_2 = new QTableWidgetItem("-");
    ui->tblNomer->setItem(1,2,itm1_2);

    OtpravkaZaprosaNomer();
    QTimer::singleShot(timerDelay,this,SLOT(ProverkaNomera()));
}


void MainWindow:: OtpravkaZaprosaTarir()
{
    if (AdminTools==1){
        ui->consolTest->textCursor().insertText(QTime::currentTime().toString("HH:mm:ss")+" - "+QString::number(dataT[0])+"/"+QString::number(dataT[1])+"/"+QString::number(dataT[2])+"/"+QString::number(dataT[3])+"/"+QString::number(dataT[4])+"/"+QString::number(dataT[5])+'\r'); // Вывод текста в консоль
        ui->consolTest->moveCursor(QTextCursor::End);//Scroll
    }
    for (int j=0;j<ListOfBSWVt.size();j++){
        ListOfBSWVt[j].otvetPoluchen=0;
        ListOfBSWVt[j].otvet.clear();        
        ListOfBSWVData[j].otvetBuffer.clear();
    }
    PortMK1osn->currentOtvetSize=0;
    PortMK2osn->currentOtvetSize=0;
    PortMK3osn->currentOtvetSize=0;
    PortMK1rez->currentOtvetSize=0;
    PortMK2rez->currentOtvetSize=0;
    PortMK3rez->currentOtvetSize=0;
    emit writeToPort1 (17,dataQt,otvetTarirSize);
    emit writeToPort2 (17,dataQt,otvetTarirSize);
    emit writeToPort3 (17,dataQt,otvetTarirSize);
    emit writeToPort4 (17,dataQt,otvetTarirSize);
    emit writeToPort5 (17,dataQt,otvetTarirSize);
    emit writeToPort6 (17,dataQt,otvetTarirSize);
}

void MainWindow::OtpravkaZaprosaNomer()
{
    if (AdminTools==1){
        ui->consolTest->textCursor().insertText(QTime::currentTime().toString("HH:mm:ss")+" - "+QString::number(dataNomer[0])+"/"+QString::number(dataNomer[1])+"/"+QString::number(dataNomer[2])+"/"+QString::number(dataNomer[3])+"/"+QString::number(dataNomer[4])+"/"+QString::number(dataNomer[5])+'\r'); // Вывод текста в консоль
        ui->consolTest->moveCursor(QTextCursor::End);//Scroll
    }
    for (int f=0;f<ListOfBSWVnomer.size();f++){
        ListOfBSWVnomer[f].otvetPoluchen=0;
        ListOfBSWVnomer[f].otvet.clear();
        ListOfBSWVData[f].otvetBuffer.clear();
    }
    PortMK1osn->currentOtvetSize=0;
    PortMK2osn->currentOtvetSize=0;
    PortMK3osn->currentOtvetSize=0;
    PortMK1rez->currentOtvetSize=0;
    PortMK2rez->currentOtvetSize=0;
    PortMK3rez->currentOtvetSize=0;
    emit writeToPort1 (34,dataQNomer,otvetMKSize);
    emit writeToPort2 (34,dataQNomer,otvetMKSize);
    emit writeToPort3 (34,dataQNomer,otvetMKSize);
    emit writeToPort4 (34,dataQNomer,otvetMKSize);
    emit writeToPort5 (34,dataQNomer,otvetMKSize);
    emit writeToPort6 (34,dataQNomer,otvetMKSize);

}

void MainWindow::Kompanovka(QByteArray dataRead, QString comName)
{
    //Печать буфера в тест консоль
//    unsigned char buffer [dataRead.size()];
//    memcpy( buffer, dataRead.data(), dataRead.size());
//    if (dataRead.size()==12){
//        if (AdminTools==1){
//            ui->consolTest->textCursor().insertText(QTime::currentTime().toString("HH:mm:ss")+" - "+comName+" - "+QString::number(buffer[0])+
//            "/"+QString::number(buffer[1])+"/"+QString::number(buffer[2])+"/"+QString::number(buffer[3])+
//            "/"+QString::number(buffer[4])+"/"+QString::number(buffer[5])+"/"+QString::number(buffer[6])+
//            "/"+QString::number(buffer[7])+"/"+QString::number(buffer[8])+"/"+QString::number(buffer[9])
//            +"/"+QString::number(buffer[10])+"/"+QString::number(buffer[11])+'\r'); // Вывод текста в консоль
//            ui->consolTest->moveCursor(QTextCursor::End);//Scroll
//        }
//    }
//    //КОнец теста
//    //Печать буфера в тест консоль
//    if (dataRead.size()==6){
//    unsigned char buffer [dataRead.size()];
//    memcpy( buffer, dataRead.data(), dataRead.size());
//    if (AdminTools==1){
//        ui->consolTest->textCursor().insertText(QTime::currentTime().toString("HH:mm:ss")+" - "+comName+" - "+QString::number(buffer[0])+"/"+QString::number(buffer[1])+"/"+QString::number(buffer[2])+"/"+QString::number(buffer[3])+"/"+QString::number(buffer[4])+"/"+QString::number(buffer[5])+'\r'); // Вывод текста в консоль
//        ui->consolTest->moveCursor(QTextCursor::End);//Scroll
//    }
//}
//    //КОнец теста
//    //test start
//    if ((dataRead.size()!=6)&(dataRead.size()!=12)){
        unsigned char buffer [dataRead.size()];
        memcpy( buffer, dataRead.data(), dataRead.size());
        QString Data;
        for (int h=0;h<dataRead.size();h++){
             Data=Data+"/"+QString::number(buffer[h]);
        }
        if (AdminTools==1){
            ui->consolTest->textCursor().insertText(QTime::currentTime().toString("HH:mm:ss")+" - "+comName+" - "+Data+'\r');
        }
    //}
    //test end


    for (int i=0;i<ListOfBSWVData.size();i++){

            if (ListOfBSWVData.at(i).namePort == comName){
                ListOfBSWVData[i].otvetBuffer.append(dataRead);
                if (ListOfBSWVData[i].otvetBuffer.size()>3){
                    switch (ListOfBSWVData[i].otvetBuffer[3]){
                    case char (1):
                         if (ListOfBSWVData[i].otvetBuffer.size() == otvetTelemSize){
                             ListOfBSWVData[i].otvet = ListOfBSWVData[i].otvetBuffer;
                             ListOfBSWVData[i].otvetBuffer.clear();
                             emit readyToAnalize(ListOfBSWVData.at(i).otvet, ListOfBSWVData.at(i).namePort);

                         }
                    break;
                    case char (17):
                         if (ListOfBSWVData[i].otvetBuffer.size() == otvetTarirSize){
                             ListOfBSWVt[i].otvet = ListOfBSWVData[i].otvetBuffer;
                             emit readyToAnalize(ListOfBSWVt.at(i).otvet, ListOfBSWVt.at(i).namePort);
                             ListOfBSWVData[i].otvetBuffer.clear();
                         }
                    break;
                    case char (34):
                         if (ListOfBSWVData[i].otvetBuffer.size() == otvetMKSize){
                             ListOfBSWVnomer[i].otvet = ListOfBSWVData[i].otvetBuffer;
                             emit readyToAnalize(ListOfBSWVnomer.at(i).otvet, ListOfBSWVnomer.at(i).namePort);
                             ListOfBSWVData[i].otvetBuffer.clear();
                         }
                    break;
                    case char(255):
                         if (ListOfBSWVData[i].otvetBuffer.size() == otvetProvSize){
                             ListOfBSWVprov[i].otvet = ListOfBSWVData[i].otvetBuffer;
                             ListOfBSWVData[i].otvetBuffer.clear();
                             emit readyToAnalize(ListOfBSWVprov.at(i).otvet, ListOfBSWVprov.at(i).namePort);

                        }
                    break;
                    case char(99):
                         if (ListOfBSWVData[i].otvetBuffer.size() == otvetTestRS485Size){
                             otvet485data=ListOfBSWVData[i].otvetBuffer;
                             otvet485name=comName;
                             QTimer::singleShot(1000,this,SLOT(AnalizeRS485()));
                             ListOfBSWVData[i].otvetBuffer.clear();
                         }
                    break;
                    }
                }
            }
    }
}

void MainWindow::Analize(QByteArray otvet,QString comName)
{
    unsigned char buffer [otvet.size()];
    memcpy( buffer, otvet.data(), otvet.size());
    unsigned char upperCRC = buffer[otvet.size()-2];
    unsigned char lowerCRC = buffer[otvet.size()-1];
    unsigned short le = otvet.size()-2;
    switch (buffer[1]){
    case 2:
           switch (buffer[2]){
           case 1:
                switch (buffer[3]){
                case 1:
                    for (int i=0;i<ListOfBSWVData.size();i++){
                        if (ListOfBSWVData.at(i).namePort == comName){
                            ListOfBSWVprov[i].readyToSend=1;
                            // unsigned short fullCRC = (unsigned short) (upperCRC<<8) | lowerCRC;
                            unsigned char upperCRCR = Crc16(buffer,le)>>8;
                            unsigned char lowerCRCR = Crc16(buffer,le);
                            if ((upperCRCR==upperCRC)&&(lowerCRCR==lowerCRC)){
                                 ListOfBSWVData[i].icap2 = float(buffer[4])*1+0; //"Суммарный ток нагрузки 2"
                                 ListOfBSWVData[i].icap1 = float(buffer[5])*1+0;//"Суммарный ток нагрузки 1"
                                 ListOfBSWVData[i].u2 = float(buffer[6])*0.2+85;//"Напряжение на силовых шинах 2"
                                 ListOfBSWVData[i].u1 = float(buffer[7])*0.2+85;//"Напряжение на силовых шинах 1"
                                 ListOfBSWVData[i].tcorp2 = float(buffer[8])*0.36+0;//"Температура 2 корпуса прибора"
                                 ListOfBSWVData[i].tcorp1 = float(buffer[9])*0.36+0;//"Температура 1 корпуса прибора"
                                 ListOfBSWVData[i].otvetPoluchen=1;                                 
                                 QTableWidgetItem *itm0_0 = new QTableWidgetItem(tr("%1").arg(ListOfBSWVData.at(i).icap2)); //создание итема таблицы для заполнения
                                 ui->tblBSWV->setItem(0,i,itm0_0); //заполнение указанной ячейки (строки, столбцы,итем для заполнения)
                                 QTableWidgetItem *itm1_0 = new QTableWidgetItem(tr("%1").arg(ListOfBSWVData.at(i).icap1));
                                 ui->tblBSWV->setItem(1,i,itm1_0);
                                 QTableWidgetItem *itm2_0 = new QTableWidgetItem(tr("%1").arg(ListOfBSWVData.at(i).u2));
                                 ui->tblBSWV->setItem(2,i,itm2_0);
                                 QTableWidgetItem *itm3_0 = new QTableWidgetItem(tr("%1").arg(ListOfBSWVData.at(i).u1));
                                 ui->tblBSWV->setItem(3,i,itm3_0);
                                 QTableWidgetItem *itm4_0 = new QTableWidgetItem(tr("%1").arg(ListOfBSWVData.at(i).tcorp2));
                                 ui->tblBSWV->setItem(4,i,itm4_0);
                                 QTableWidgetItem *itm5_0 = new QTableWidgetItem(tr("%1").arg(ListOfBSWVData.at(i).tcorp1));
                                 ui->tblBSWV->setItem(5,i,itm5_0);
                                 ListOfBSWVprov[i].readyToSend=1;
                            }
                            else {ListOfBSWVData[i].otvetPoluchen=0;
                                  ListOfBSWVData[i].icap2 = 0.0;
                                  ListOfBSWVData[i].icap1 = 0.0;
                                  ListOfBSWVData[i].u2 = 0.0;
                                  ListOfBSWVData[i].u1 = 0.0;
                                  ListOfBSWVData[i].tcorp2 = 0.0;
                                  ListOfBSWVData[i].tcorp1 = 0.0;
                                  Print("Не совпала контрольная сумма пакета 1 от "+ListOfBSWVData[i].name);
                                  if (ListOfBSWVData.at(i).on_off_status == 1){
                                      if (stopIfError==1){
                                          ui->btnStart->click();
                                      }
                                      emit errorMessageThis (error);
                                      tblBSWVSetDeafault(6, i);
                                  }
                            }
                        }
                     }
                 break;
                 case 17:
                    for (int i=0;i<ListOfBSWVt.size();i++){
                        if (ListOfBSWVt.at(i).namePort == comName){
                            unsigned char upperCRCR = Crc16(buffer,le)>>8;
                            unsigned char lowerCRCR = Crc16(buffer,le);
                            if ((upperCRCR==upperCRC)&&(lowerCRCR==lowerCRC)){
                                ListOfBSWVt[i].uref = float((unsigned short) (buffer[4]<<8) | buffer[5]);
                                ListOfBSWVt[i].icap2 =  float((unsigned short) (buffer[8]<<8) | buffer[9]);//"Суммарный ток нагрузки 2"
                                ListOfBSWVt[i].icap1 = float((unsigned short) (buffer[10]<<8) | buffer[11]);//"Суммарный ток нагрузки 1"
                                ListOfBSWVt[i].u2 = float((unsigned short) (buffer[12]<<8) | buffer[13]);//"Напряжение на силовых шинах 2"
                                ListOfBSWVt[i].u1 = float((unsigned short) (buffer[14]<<8) | buffer[15]);//"Напряжение на силовых шинах 1"
                                ListOfBSWVt[i].tcorp2 =float((unsigned short) (buffer[16]<<8) | buffer[17]); //"Температура 2 корпуса прибора"
                                ListOfBSWVt[i].tcorp1 = float((unsigned short) (buffer[18]<<8) | buffer[19]);//"Температура 1 корпуса прибора"
                                ListOfBSWVt[i].otvetPoluchen=1;
                            }else{
                                ListOfBSWVt[i].otvetPoluchen=0;
                                ListOfBSWVt[i].uref = 0.0;
                                ListOfBSWVt[i].icap2 = 0.0;
                                ListOfBSWVt[i].icap1 = 0.0;
                                ListOfBSWVt[i].u2 = 0.0;
                                ListOfBSWVt[i].u1 = 0.0;
                                ListOfBSWVt[i].tcorp2 = 0.0;
                                ListOfBSWVt[i].tcorp1 = 0.0;
                                Print("Не совпала контрольная сумма пакета 17 от "+ListOfBSWVt[i].name);
                            }
                        }
                    }
                 break;
                 case 34:
                      for (int i=0;i<ListOfBSWVnomer.size();i++){
                          if (ListOfBSWVnomer.at(i).namePort == comName){
                              //ListOfBSWVnomer[i].readyToSend=1;
                              unsigned char upperCRCR = Crc16(buffer,le)>>8;
                              unsigned char lowerCRCR = Crc16(buffer,le);
                              if ((upperCRCR==upperCRC)&&(lowerCRCR==lowerCRC)){
                                   unsigned char nMK = buffer[4]>>4;
                                   switch (nMK){
                                          //case 0b0001://номер МУКа, 0b0001 - 1 МК, 0b0010- 2 МК, 0b0011 - 3 МК
                                   case 1:
                                          ListOfBSWVnomer[i].nMK = "MK1";
                                   break;
                                          //case 0b0010:
                                   case 2:
                                          ListOfBSWVnomer[i].nMK = "MK2";
                                   break;
                                          //case 0b0011:
                                   case 3:
                                          ListOfBSWVnomer[i].nMK = "MK3";
                                   break;
                                   }
                                   unsigned char bufferChan = buffer[4]<<4;
                                   unsigned char nChan = bufferChan>>4;
                                   // if ((buffer[4]>>4)==0){ //номер канала 0b0000 - основной, 0b0001 -резервный;
                                   if (nChan==0){ //номер канала 0b0000 - основной, 0b0001 -резервный;
                                       ListOfBSWVnomer[i].nChan = "-основной";
                                   }
                                    //if ((buffer[4]>>4)==1)
                                   if (nChan==1){
                                       ListOfBSWVnomer[i].nChan = "-резервный";
                                   }
                                   ListOfBSWVnomer[i].otvetPoluchen=1;
                              }else{
                                   ListOfBSWVnomer[i].otvetPoluchen=0;
                                   ListOfBSWVnomer[i].nMK = "-";
                                   ListOfBSWVnomer[i].nChan = "-";
                                   Print("Не совпала контрольная сумма пакета 34 от "+ListOfBSWVnomer[i].name);
                              }
                          }
                      }
                 break;
                 case 255:
                      for (int i=0;i<ListOfBSWVprov.size();i++){
                           if (ListOfBSWVprov.at(i).namePort == comName){
                               ListOfBSWVData[i].readyToSend=1;
                               unsigned char upperCRCR = Crc16(buffer,le)>>8;
                               unsigned char lowerCRCR = Crc16(buffer,le);
                               if ((upperCRCR==upperCRC)&&(lowerCRCR==lowerCRC)){
                                    ListOfBSWVprov[i].otvetPoluchen=1;
                                    ListOfBSWVData[i].readyToSend=1;
                               } else {
                                    ListOfBSWVprov[i].otvetPoluchen=0;

                                    if (ListOfBSWVData[i].on_off_status == 1){
                                        error = "Корректный ответ на сообщение 255 от "+ListOfBSWVprov.at(i).name + " не получен";
                                        emit errorMessageThis (error);
                                        if (stopIfError==1){
                                            ui->btnStart->click();
                                        }
                                    }

                                    Print("Не совпала контрольная сумма пакета 255 от "+ListOfBSWVprov[i].name);
                               }
                          }
                      }
                 break;
                 }
             break;
             }
   break;
    }
}


void MainWindow::ChangeColor()
{
    ui->tabWidget->tabBar()->setTabTextColor(1,Qt::black);
}

void MainWindow::Print(QString dat)
{
    ui->consol->textCursor().insertText(QTime::currentTime().toString("HH:mm:ss")+" - "+dat+'\r'); // Вывод текста в консоль
    ui->consol->moveCursor(QTextCursor::End);//Scroll
    ui->tabWidget->tabBar()->setTabTextColor(1,Qt::red);
}

void MainWindow::ProverkaNomera(){

    for (int f=0;f<ListOfBSWVnomer.size();f++){
        if (ListOfBSWVnomer.at(f).otvetPoluchen==1){
            QString nomer = ListOfBSWVnomer.at(f).nMK+ListOfBSWVnomer.at(f).nChan;
            if (ListOfBSWVnomer.at(f).name=="MK1-osn"){
               // QTableWidgetItem *itm0_0 = new QTableWidgetItem(tr("%1").arg(nomer));
                QTableWidgetItem *itm0_0 = new QTableWidgetItem(nomer);
                ui->tblNomer->setItem(0,0,itm0_0);
            }
            if (ListOfBSWVnomer.at(f).name=="MK1-rez"){
               // QTableWidgetItem *itm1_0 = new QTableWidgetItem(tr("%1").arg(nomer));
                QTableWidgetItem *itm1_0 = new QTableWidgetItem(nomer);
                ui->tblNomer->setItem(1,0,itm1_0);
            }
            if (ListOfBSWVnomer.at(f).name=="MK2-osn"){
               // QTableWidgetItem *itm0_1 = new QTableWidgetItem(tr("%1").arg(nomer));
                QTableWidgetItem *itm0_1 = new QTableWidgetItem(nomer);
                ui->tblNomer->setItem(0,1,itm0_1);
            }
            if (ListOfBSWVnomer.at(f).name=="MK2-rez"){
               // QTableWidgetItem *itm1_1 = new QTableWidgetItem(tr("%1").arg(nomer));
                QTableWidgetItem *itm1_1 = new QTableWidgetItem(nomer);
                ui->tblNomer->setItem(1,1,itm1_1);
            }
            if (ListOfBSWVnomer.at(f).name=="MK3-osn"){
               // QTableWidgetItem *itm0_2 = new QTableWidgetItem(tr("%1").arg(nomer));
                QTableWidgetItem *itm0_2 = new QTableWidgetItem(nomer);
                ui->tblNomer->setItem(0,2,itm0_2);
            }
            if (ListOfBSWVnomer.at(f).name=="MK3-rez"){
               // QTableWidgetItem *itm1_2 = new QTableWidgetItem(tr("%1").arg(nomer));
                QTableWidgetItem *itm1_2 = new QTableWidgetItem(nomer);
                ui->tblNomer->setItem(1,2,itm1_2);
            }
        //ListOfBSWVnomer[f].otvetPoluchen=0;
        }
        else {
            if (ListOfBSWVData[f].on_off_status == 1){
            error = ("Корректный ответ на сообщение 34 от "+ ListOfBSWVprov.at(f).name +" за %1 мс не получен").arg(timerDelay);
            emit errorMessageThis (error);
            }
        }        
    }
}

void MainWindow::WriteInFileTemplate(QString fnameTemplate,QFile &fileTemplate,int k)
{
    QString fnameT=QDateTime::currentDateTime().toLocalTime().toString("dd.MM.yyyy.hh")+"_BSWV_"+fnameTemplate+"_Telemetria.txt";
    fileTemplate.setFileName("../logs/"+logYear+"/"+logMonth+"/"+fnameTemplate+"/"+fnameT);
    QTextStream stream(&fileTemplate);
    stream.setFieldAlignment(QTextStream::AlignLeft);
    if (fileTemplate.exists()){//Проверка - существует ли файл
        if (fileTemplate.open(QIODevice::WriteOnly | QIODevice::Append)) { // Append - для записи в конец файла
            QString str = QTime::currentTime().toString("ss");
            int time = str.toInt();
            stream.setFieldWidth(32);
            if (time%5==0){
                stream<<QString::fromUtf8("Время")<<QString::fromUtf8(" | Канал")<<QString::fromUtf8(" | Суммарный ток нагрузки 2")<<QString::fromUtf8(" | Суммарный ток нагрузки 1");
                stream<<QString::fromUtf8(" | Напряжение на силовых шинах 2")<<QString::fromUtf8(" | Напряжение на силовых шинах 1");
                stream<<QString::fromUtf8(" | Температура 2 корпуса прибора")<<QString::fromUtf8(" | Температура 1 корпуса прибора");
                stream.setFieldWidth(0);
                //stream<<endl; - плохо отображается в блокноте, но нормально в Notepad++
                stream<<"\r\n";
                stream.setFieldWidth(32);
            }
                stream<<QTime::currentTime().toString("HH:mm:ss")<<" | "+ListOfBSWVData[k].name;
                if (ListOfBSWVData[k].otvetPoluchen==1){
                    stream<<" | "+QString::number(ListOfBSWVData[k].icap2)<<" | "+QString::number(ListOfBSWVData[k].icap1);
                    stream<<" | "+QString::number(ListOfBSWVData[k].u2)<<" | "+QString::number(ListOfBSWVData[k].u1)<<" | "+QString::number(ListOfBSWVData[k].tcorp2)<<" | "+QString::number(ListOfBSWVData[k].tcorp1);
                } else {
                    stream<<" | -"<<" | -";
                    stream<<" | -"<<" | -"<<" | -"<<" | -";
                }
                stream.setFieldWidth(0);
                //stream<<endl; - плохо отображается в блокноте, но нормально в Notepad++
                stream<<"\r\n";
                stream.setFieldWidth(32);

        }
    }
    else {
           if (fileTemplate.open(QIODevice::WriteOnly | QIODevice::Append)) {//Если файл только создается, то в первую строчку записываем название параметра
               stream.setFieldWidth(32);
               stream<<QString::fromUtf8("Время")<<QString::fromUtf8(" | Канал")<<QString::fromUtf8(" | Суммарный ток нагрузки 2")<<QString::fromUtf8(" | Суммарный ток нагрузки 1")<<
               QString::fromUtf8(" | Напряжение на силовых шинах 2")<<QString::fromUtf8(" | Напряжение на силовых шинах 1")
               <<QString::fromUtf8(" | Температура 2 корпуса прибора")<<QString::fromUtf8(" | Температура 1 корпуса прибора");
               stream.setFieldWidth(0);
               //stream<<endl; - плохо отображается в блокноте, но нормально в Notepad++
               stream<<"\r\n";
               stream.setFieldWidth(32);
               stream<<QTime::currentTime().toString("HH:mm:ss")<<" | "+ListOfBSWVData[k].name;
               if (ListOfBSWVData[k].otvetPoluchen==1){
                   stream<<" | "+QString::number(ListOfBSWVData[k].icap2)<<" | "+QString::number(ListOfBSWVData[k].icap1);
                   stream<<" | "+QString::number(ListOfBSWVData[k].u2)<<" | "+QString::number(ListOfBSWVData[k].u1)<<" | "+QString::number(ListOfBSWVData[k].tcorp2)<<" | "+QString::number(ListOfBSWVData[k].tcorp1);
               } else {
                   stream<<" | -"<<" | -";
                   stream<<" | -"<<" | -"<<" | -"<<" | -";
               }
               stream.setFieldWidth(0);
               //stream<<endl; - плохо отображается в блокноте, но нормально в Notepad++
               stream<<"\r\n";
               stream.setFieldWidth(32);
           }
    }
    fileTemplate.close();

}



void MainWindow::WriteInFile()
{
    WriteInFileTemplate("MK1o",fileMK1o,0);
    WriteInFileTemplate("MK1r",fileMK1r,1);
    WriteInFileTemplate("MK2o",fileMK2o,2);
    WriteInFileTemplate("MK2r",fileMK2r,3);
    WriteInFileTemplate("MK3o",fileMK3o,4);
    WriteInFileTemplate("MK3r",fileMK3r,5);

    fname=QDateTime::currentDateTime().toLocalTime().toString("dd.MM.yyyy.hh")+"_BSWV_Telemetria.txt";
    file.setFileName("../logs/"+logYear+"/"+logMonth+"/"+"AllChannels"+"/"+fname);
    QTextStream stream(&file);
    stream.setFieldAlignment(QTextStream::AlignLeft);

    if (file.exists()){//Проверка - существует ли файл
        if (file.open(QIODevice::WriteOnly | QIODevice::Append)) { // Append - для записи в конец файла
            QString str = QTime::currentTime().toString("ss");
            int time = str.toInt();
            stream.setFieldWidth(32);
            if (time%5==0){
                stream<<QString::fromUtf8("Время")<<QString::fromUtf8(" | Канал")<<QString::fromUtf8(" | Суммарный ток нагрузки 2")<<QString::fromUtf8(" | Суммарный ток нагрузки 1");
                stream<<QString::fromUtf8(" | Напряжение на силовых шинах 2")<<QString::fromUtf8(" | Напряжение на силовых шинах 1");
                stream<<QString::fromUtf8(" | Температура 2 корпуса прибора")<<QString::fromUtf8(" | Температура 1 корпуса прибора");
                stream.setFieldWidth(0);
                //stream<<endl; - плохо отображается в блокноте, но нормально в Notepad++
                stream<<"\r\n";
                stream.setFieldWidth(32);
            }
            for (int i=0;i<ListOfBSWVData.size();i++){
                stream<<QTime::currentTime().toString("HH:mm:ss")<<" | "+ListOfBSWVData[i].name;
                if (ListOfBSWVData[i].otvetPoluchen==1){
                    stream<<" | "+QString::number(ListOfBSWVData[i].icap2)<<" | "+QString::number(ListOfBSWVData[i].icap1);
                    stream<<" | "+QString::number(ListOfBSWVData[i].u2)<<" | "+QString::number(ListOfBSWVData[i].u1)<<" | "+QString::number(ListOfBSWVData[i].tcorp2)<<" | "+QString::number(ListOfBSWVData[i].tcorp1);
                } else {
                    stream<<" | -"<<" | -";
                    stream<<" | -"<<" | -"<<" | -"<<" | -";
                }
                stream.setFieldWidth(0);
                //stream<<endl;
                stream<<"\r\n";
                stream.setFieldWidth(32);
            }
        }
    }
    else {
           if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {//Если файл только создается, то в первую строчку записываем название параметра
               stream.setFieldWidth(32);
               stream<<QString::fromUtf8("Время")<<QString::fromUtf8(" | Канал")<<QString::fromUtf8(" | Суммарный ток нагрузки 2")<<QString::fromUtf8(" | Суммарный ток нагрузки 1")<<
               QString::fromUtf8(" | Напряжение на силовых шинах 2")<<QString::fromUtf8(" | Напряжение на силовых шинах 1")
               <<QString::fromUtf8(" | Температура 2 корпуса прибора")<<QString::fromUtf8(" | Температура 1 корпуса прибора");
               stream.setFieldWidth(0);
               //stream<<endl;
               stream<<"\r\n";
               stream.setFieldWidth(32);
               for (int i=0;i<ListOfBSWVData.size();i++){
                    stream<<QTime::currentTime().toString("HH:mm:ss")<<" | "+ListOfBSWVData[i].name;
                    if (ListOfBSWVData[i].otvetPoluchen==1){
                        stream<<" | "+QString::number(ListOfBSWVData[i].icap2)<<" | "+QString::number(ListOfBSWVData[i].icap1);
                        stream<<" | "+QString::number(ListOfBSWVData[i].u2)<<" | "+QString::number(ListOfBSWVData[i].u1)<<" | "+QString::number(ListOfBSWVData[i].tcorp2)<<" | "+QString::number(ListOfBSWVData[i].tcorp1);
                   } else {
                       stream<<" | -"<<" | -";
                       stream<<" | -"<<" | -"<<" | -"<<" | -";
                   }
                   stream.setFieldWidth(0);
                   //stream<<endl;
                   stream<<"\r\n";
                   stream.setFieldWidth(32);
               }
           }
    }
    file.close();
}

void MainWindow::WriteInFileError(QString error)
{
    QString fEname = QDateTime::currentDateTime().toLocalTime().toString("dd.MM.yyyy.hh")+"_Errors.txt";
    fileError.setFileName("../logs/"+logYear+"/"+logMonth+"/"+"Errors"+"/"+fEname);
    QTextStream stream(&fileError);
    stream.setFieldWidth(16);
    stream.setFieldAlignment(QTextStream::AlignLeft);
    if (fileError.exists()){//Проверка - существует ли файл
            if (fileError.open(QIODevice::WriteOnly | QIODevice::Append)) { // Append - для записи в конец файла               
                QString log1 = QTime::currentTime().toString("HH:mm:ss")+"  | ";
                QString log2 = error;
                stream<<log1;
                stream<<log2;
                stream.setFieldWidth(0);
                //stream<<endl;
                stream<<"\r\n";
                stream.setFieldWidth(16);
            }
    }
    else {
           if (fileError.open(QIODevice::WriteOnly | QIODevice::Append)) {//Если файл только создается, то в первую строчку записываем название параметра                     
           //stream<< QString::fromUtf8(" Время             Описание ошибки \r\n");
          // stream<<QTime::currentTime().toString("HH:mm:ss") +"  |  "+error+"\r\n";
               stream<<QString::fromUtf8("Время")+"     |"<<QString::fromUtf8("Описание ошибки")+"\r\n";
               QString log1 = QTime::currentTime().toString("HH:mm:ss")+"  | ";
               stream<<log1;
               stream<<error;
               stream.setFieldWidth(0);
               //stream<<endl;
               stream<<"\r\n";
               stream.setFieldWidth(16);
           }
    }
    fileError.close();
}

void MainWindow::VivodACP()
{
    for (int j=0;j<ListOfBSWVt.size();j++){
        if (ListOfBSWVt.at(j).otvetPoluchen==1){
            QTableWidgetItem *itm0_0 = new QTableWidgetItem(tr("%1").arg(ListOfBSWVt.at(j).icap2)); //создание итема таблицы для заполнения
            ui->tblAcp->setItem(0,j,itm0_0); //заполнение указанной ячейки (строки, столбцы,итем для заполнения)
            QTableWidgetItem *itm1_0 = new QTableWidgetItem(tr("%1").arg(ListOfBSWVt.at(j).icap1));
            ui->tblAcp->setItem(1,j,itm1_0);
            QTableWidgetItem *itm2_0 = new QTableWidgetItem(tr("%1").arg(ListOfBSWVt.at(j).u2));
            ui->tblAcp->setItem(2,j,itm2_0);
            QTableWidgetItem *itm3_0 = new QTableWidgetItem(tr("%1").arg(ListOfBSWVt.at(j).u1));
            ui->tblAcp->setItem(3,j,itm3_0);
            QTableWidgetItem *itm4_0 = new QTableWidgetItem(tr("%1").arg(ListOfBSWVt.at(j).tcorp2));
            ui->tblAcp->setItem(4,j,itm4_0);
            QTableWidgetItem *itm5_0 = new QTableWidgetItem(tr("%1").arg(ListOfBSWVt.at(j).tcorp1));
            ui->tblAcp->setItem(5,j,itm5_0);
            QTableWidgetItem *itm6_0 = new QTableWidgetItem(tr("%1").arg(ListOfBSWVt.at(j).uref));
            ui->tblAcp->setItem(6,j,itm6_0);
        }else{
            if (ListOfBSWVData[j].on_off_status == 1){
            error = ("Корректный ответ на сообщение 17 от "+ ListOfBSWVt.at(j).name +" за %1 мс не получен").arg(timerDelay);
            emit errorMessageThis (error);
            QTableWidgetItem *itm91_91 = new QTableWidgetItem("-");
            QTableWidgetItem *itm92_92 = new QTableWidgetItem("-");
            QTableWidgetItem *itm93_93 = new QTableWidgetItem("-");
            QTableWidgetItem *itm94_94 = new QTableWidgetItem("-");
            QTableWidgetItem *itm95_95 = new QTableWidgetItem("-");
            QTableWidgetItem *itm96_96 = new QTableWidgetItem("-");
            QTableWidgetItem *itm97_97 = new QTableWidgetItem("-");
            ui->tblAcp->setItem(0,j,itm91_91); //заполнение указанной ячейки (строки, столбцы,итем для заполнения)
            ui->tblAcp->setItem(1,j,itm92_92);
            ui->tblAcp->setItem(2,j,itm93_93);
            ui->tblAcp->setItem(3,j,itm94_94);
            ui->tblAcp->setItem(4,j,itm95_95);
            ui->tblAcp->setItem(5,j,itm96_96);
            ui->tblAcp->setItem(6,j,itm97_97);
            }
        }
    }


    fACPname = QDate::currentDate().toString("dd.MM.yyyy")+"_ACP.txt";
    fileACP.setFileName("../logs/"+logYear+"/"+logMonth+"/"+"ACP"+"/"+fACPname);

    QString ACPType;
    if (ui->rbTarirTypeI->isChecked()){
        ACPType=QString::fromUtf8(" | Ток");
    }
    if (ui->rbTarirTypeU->isChecked()){
        ACPType=QString::fromUtf8(" | Напряжение");
    }
    if (ui->rbTarirTypeT->isChecked()){
        ACPType=QString::fromUtf8(" | Температура");
    }
    QTextStream streamACP(&fileACP);
    streamACP.setFieldAlignment(QTextStream::AlignLeft);
    streamACP.setFieldWidth(32);

    if (fileACP.open(QIODevice::WriteOnly | QIODevice::Append)) { // Append - для записи в конец файла
        QString str = QTime::currentTime().toString("ss");
        streamACP.setFieldWidth(32);
        streamACP<<QString::fromUtf8("Время")<<QString::fromUtf8(" | Канал")<<ACPType;
        streamACP<<QString::fromUtf8(" | Суммарный ток нагрузки 2")<<QString::fromUtf8(" | Суммарный ток нагрузки 1");
        streamACP<<QString::fromUtf8(" | Напряжение на силовых шинах 2")<<QString::fromUtf8(" | Напряжение на силовых шинах 1");
        streamACP<<QString::fromUtf8(" | Температура 2 корпуса прибора")<<QString::fromUtf8(" | Температура 1 корпуса прибора")<<QString::fromUtf8(" | Опорное напряжение");
        streamACP.setFieldWidth(0);
        //streamACP<<endl;
        streamACP<<"\r\n";
        streamACP.setFieldWidth(32);
        for (int j=0;j<ListOfBSWVt.size();j++){
            if (ListOfBSWVt.at(j).otvetPoluchen==1){
                streamACP<<QTime::currentTime().toString("HH:mm:ss")<<" | "+ListOfBSWVt[j].name;
                streamACP<<" | "+ui->leTarirValue->text();
                streamACP<<" | "+QString::number(ListOfBSWVt[j].icap2)<<" | "+QString::number(ListOfBSWVt[j].icap1);
                streamACP<<" | "+QString::number(ListOfBSWVt[j].u2)<<" | "+QString::number(ListOfBSWVt[j].u1)<<" | "+QString::number(ListOfBSWVt[j].tcorp2)<<" | "+QString::number(ListOfBSWVt[j].tcorp1);
                streamACP<<" | "+QString::number(ListOfBSWVt[j].uref);
                streamACP.setFieldWidth(0);
                //streamACP<<endl;
                streamACP<<"\r\n";
                streamACP.setFieldWidth(32);
            }else{
                streamACP<<QTime::currentTime().toString("HH:mm:ss")<<" | "+ListOfBSWVt[j].name;
                streamACP<<" | "+ui->leTarirValue->text()<<" | -"<<" | -";
                streamACP<<" | -"<<" | -"<<" | -"<<" | -" <<" | -";
                streamACP.setFieldWidth(0);
                //streamACP<<endl;
                streamACP<<"\r\n";
                streamACP.setFieldWidth(32);
            }
        }
    }
    fileACP.close();
}

QString MainWindow::getPortName(QString dis, QString serial)
{
    QString namePort;
    QList<QSerialPortInfo> serialPortInfo = QSerialPortInfo::availablePorts();
    for (int i=0;i<serialPortInfo.count();i++) {
        if ((dis==serialPortInfo.at(i).description())&&(serial==serialPortInfo.at(i).serialNumber())){
           namePort = serialPortInfo.at(i).portName();
        }
    }
    return namePort;
}

void MainWindow::on_pbTestRS485_clicked()
{
    //---------Формирование исходящего сообщения для проверки конвертеров РС(тип99)----------
    dataTestRS485[6] = 0;
    dataTestRS485[7] = 0;
    otvet485data.clear();
    otvet485name.clear();
    dataTestRS485 [0] = startByte;
    unsigned short len = 6;
    if (ui->rbMK1o_r->isChecked()) {
        dataTestRS485[1] = MK1o;//2 байт - адресс отправителя
        dataTestRS485[2] = MK1r;//3 байт - адресс получателя
    }
    if (ui->rbMK1r_o->isChecked()){
        dataTestRS485[1] = MK1r;
        dataTestRS485[2] = MK1o;
    }
    if (ui->rbMK2o_r->isChecked()){
        dataTestRS485[1] = MK2o;
        dataTestRS485[2] = MK2r;
    }
    if (ui->rbMK2r_o->isChecked()){
        dataTestRS485[1] = MK2r;
        dataTestRS485[2] = MK2o;
    }
    if (ui->rbMK3o_r->isChecked()){
        dataTestRS485[1] = MK3o;
        dataTestRS485[2] = MK3r;
    }
    if (ui->rbMK3r_o->isChecked()){
        dataTestRS485[1] = MK3r;
        dataTestRS485[2] = MK3o;
    }
    dataTestRS485[3] = messType99;
    QString bufferOtpr = ListOfBSWVData.at(dataTestRS485[1]-1).namePort;
    bufferOtpr.remove(QString("com"),Qt::CaseInsensitive);
    QString bufferPol = ListOfBSWVData.at(dataTestRS485[2]-1).namePort;
    bufferPol.remove(QString("com"),Qt::CaseInsensitive);
    dataTestRS485[4] = bufferOtpr.toInt();//Com-port отправителя
    dataTestRS485[5] = bufferPol.toInt();//Com-port получателя
    unsigned char upper = Crc16(dataTestRS485,len)>>8; //получение старшего байта контрольной суммы
    unsigned char lower = Crc16(dataTestRS485,len);    
    dataTestRS485[6] = upper;
    dataTestRS485[7] = lower;
    //-----------Конец формирования исходящего сообщения для проверки конвертеров РС(тип99)
    QByteArray dataQ = QByteArray::fromRawData((char*)dataTestRS485,sizeof(dataTestRS485));
    switch (dataTestRS485[1]){
    case (MK1o):
         emit writeToPort1(99,dataQ,otvetTestRS485Size);
    break;
    case (MK1r):
        emit writeToPort2(99,dataQ,otvetTestRS485Size);
    break;
    case (MK2o):
        emit writeToPort2(99,dataQ,otvetTestRS485Size);
    break;
    case (MK2r):
        emit writeToPort3(99,dataQ,otvetTestRS485Size);
    break;
    case (MK3o):
        emit writeToPort4(99,dataQ,otvetTestRS485Size);
    break;
    case (MK3r):
        emit writeToPort5(99,dataQ,otvetTestRS485Size);
    break;
    }
    QTimer::singleShot(timerDelay,this,SLOT(AnalizeRS485()));
}

void MainWindow::AnalizeRS485()
{
    QString Otpravitel;
    QString Poluchatel;
    QString ComOtpravitel;
    QString ComPoluchatel;
    QTableWidgetItem *itmDefault1 = new QTableWidgetItem("-");
    QTableWidgetItem *itmDefault2 = new QTableWidgetItem("-");
    QTableWidgetItem *itmDefault3 = new QTableWidgetItem("-");
    QTableWidgetItem *itmDefault4 = new QTableWidgetItem("-");
    QTableWidgetItem *itmDefault5 = new QTableWidgetItem("-");
    ui->lblTest485->setText("не получен");

    ui->tblTest485->setItem(0,0,itmDefault1); //заполнение указанной ячейки (строки, столбцы,итем для заполнения)
    ui->tblTest485->setItem(0,1,itmDefault2);
    ui->tblTest485->setItem(0,2,itmDefault3);
    ui->tblTest485->setItem(0,3,itmDefault4);
    ui->tblTest485->setItem(0,4,itmDefault5);
    unsigned char buffer [otvet485data.size()];
    memcpy(buffer, otvet485data.data(), otvet485data.size());
    unsigned char upperCRC = buffer[6];
    unsigned char lowerCRC = buffer[7];
    unsigned short le = 6;
    for (int i=0;i<ListOfBSWVData.size();i++){
         if (ListOfBSWVData.at(i).namePort == otvet485name){
             // unsigned short fullCRC = (unsigned short) (upperCRC<<8) | lowerCRC;
             unsigned char upperCRCR = Crc16(buffer,le)>>8;
             unsigned char lowerCRCR = Crc16(buffer,le);
             if ((upperCRCR==upperCRC)&&(lowerCRCR==lowerCRC)){
                  ui->lblTest485->setText("получен");
                  switch (buffer[1]){
                  case 1:
                       Otpravitel="MK1-O";
                  break;
                  case 2:
                       Otpravitel="MK1-R";
                  break;
                  case 3:
                       Otpravitel="MK2-O";
                  break;
                  case 4:
                       Otpravitel="MK2-R";
                  break;
                  case 5:
                       Otpravitel="MK3-O";
                  break;
                  case 6:
                       Otpravitel="MK3-R";
                  break;
                  }
                  switch (buffer[2]){
                  case 1:
                       Poluchatel="MK1-O";
                  break;
                  case 2:
                       Poluchatel="MK1-R";
                  break;
                  case 3:
                       Poluchatel="MK2-O";
                  break;
                  case 4:
                       Poluchatel="MK2-R";
                  break;
                  case 5:
                       Poluchatel="MK3-O";
                  break;
                  case 6:
                       Poluchatel="MK3-R";
                  break;
                  }
                  ComOtpravitel="COM"+tr("%1").arg(buffer[4]);
                  ComPoluchatel = "COM"+tr("%1").arg(buffer[5]);
                  QTableWidgetItem *itm1 = new QTableWidgetItem(Otpravitel);
                  QTableWidgetItem *itm2 = new QTableWidgetItem(ComOtpravitel);
                  QTableWidgetItem *itm3 = new QTableWidgetItem(Poluchatel);
                  QTableWidgetItem *itm4 = new QTableWidgetItem(ComPoluchatel);
                  QTableWidgetItem *itm5 = new QTableWidgetItem(otvet485name);
                  ui->tblTest485->setItem(0,0,itm1); //заполнение указанной ячейки (строки, столбцы,итем для заполнения)
                  ui->tblTest485->setItem(0,1,itm2);
                  ui->tblTest485->setItem(0,2,itm3);
                  ui->tblTest485->setItem(0,3,itm4);
                  ui->tblTest485->setItem(0,4,itm5);
              }else {
                  ui->lblTest485->setText("не получен");
                  ui->tblTest485->setItem(0,0,itmDefault1); //заполнение указанной ячейки (строки, столбцы,итем для заполнения)
                  ui->tblTest485->setItem(0,1,itmDefault2);
                  ui->tblTest485->setItem(0,2,itmDefault3);
                  ui->tblTest485->setItem(0,3,itmDefault4);
                  ui->tblTest485->setItem(0,4,itmDefault5);
                }
            }
        }
}

void MainWindow::on_pbGetACPKalibr_clicked()
{
    if ((ui->leTarirValue->text().toFloat())) {
        OtpravkaZaprosaTarir();
        QTimer::singleShot(timerDelay,this,SLOT(VivodACP()));
    }else{
        QMessageBox::information(this, trUtf8("Внимание!"),trUtf8("Введите корректное значение параметра для получения калибровочных данных"));
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->consol->clear();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    switch (index){
    case 0:
         ui->tabWidget->setMinimumSize(963,358);
         ui->tabWidget->resize(963,358);
         delay(100);
         QMainWindow::resize(1280,680);

    break;
    case 1:
         ui->tabWidget->setMinimumSize(963,358);
         ui->tabWidget->resize(963,358);
         delay(100);
         QMainWindow::resize(1280,680);
    break;
    case 2:
         ui->tabWidget->setMinimumSize(963,191);
//         ui->tabWidget->setBaseSize(963,358);
        ui->tabWidget->resize(963,191);
        delay(100);
        QMainWindow::resize(1280,510);
    break;
    case 3:
         ui->tabWidget->setMinimumSize(963,191);
         ui->tabWidget->resize(963,191);
         delay(100);
         QMainWindow::resize(1280,510);

    break;
    case 4:
         ui->tabWidget->setMinimumSize(963,358);
         ui->tabWidget->resize(963,358);
         delay(100);
         QMainWindow::resize(1280,680);
    break;
    }
}

void MainWindow::on_pbReconnectRS485_clicked()
{
    ui->btnStart->setEnabled(false);
    ui->tabWidget->setTabEnabled(0,false);
    ui->tabWidget->setTabEnabled(3,false);
    ui->tabWidget->setTabEnabled(2,false);
    emit discon1(); emit discon2();emit discon3();emit discon4();emit discon5();emit discon6();
    delay(500);
    LoadSettings();
    delay(500);
    ListOfSerialFact.clear();
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
        {

        if (ListOfSerialFact.contains(serialPortInfo.serialNumber())){
            //Ничего не делать
        }else{
            ListOfSerialFact.append(serialPortInfo.serialNumber());
        }

        }
    bool minus1=false;
    for (int i=0;i<ListOfSerial.size();i++)  {
        if (ListOfSerialFact.indexOf(ListOfSerial.at(i))==-1){
            minus1=true;
            Print("Не подключен конвертер интерфейсов RS-485 (серийный номер "+ListOfSerial.at(i)+")");
            converterError_status=true;
        ui->pbReconnectRS485->setVisible(true);
        }
    }
    if (minus1==false) {
        converterError_status=false;
        ui->pbReconnectRS485->setVisible(false);
    }
    ui->tabWidget->setTabEnabled(0,true);
    ui->tabWidget->setTabEnabled(3,true);
    ui->tabWidget->setTabEnabled(2,true);
    ui->btnStart->setEnabled(true);

}

void MainWindow::tblBSWVSetDeafault(int numberOfRows, int column)
{
    for (int i=0;i<numberOfRows;i++){
        QTableWidgetItem *itm91_91 = new QTableWidgetItem("-");
        ui->tblBSWV->setItem(i,column,itm91_91); //заполнение указанной ячейки (строки, столбцы,итем для заполнения)
    }
}

void MainWindow::tblBSWVSetData(int numberOfChannel)
{
    QTableWidgetItem *itm0_0 = new QTableWidgetItem(tr("%1").arg(ListOfBSWVData.at(numberOfChannel).icap2)); //создание итема таблицы для заполнения
    ui->tblBSWV->setItem(0,numberOfChannel,itm0_0); //заполнение указанной ячейки (строки, столбцы,итем для заполнения)
    QTableWidgetItem *itm1_0 = new QTableWidgetItem(tr("%1").arg(ListOfBSWVData.at(numberOfChannel).icap1));
    ui->tblBSWV->setItem(1,numberOfChannel,itm1_0);
    QTableWidgetItem *itm2_0 = new QTableWidgetItem(tr("%1").arg(ListOfBSWVData.at(numberOfChannel).u2));
    ui->tblBSWV->setItem(2,numberOfChannel,itm2_0);
    QTableWidgetItem *itm3_0 = new QTableWidgetItem(tr("%1").arg(ListOfBSWVData.at(numberOfChannel).u1));
    ui->tblBSWV->setItem(3,numberOfChannel,itm3_0);
    QTableWidgetItem *itm4_0 = new QTableWidgetItem(tr("%1").arg(ListOfBSWVData.at(numberOfChannel).tcorp2));
    ui->tblBSWV->setItem(4,numberOfChannel,itm4_0);
    QTableWidgetItem *itm5_0 = new QTableWidgetItem(tr("%1").arg(ListOfBSWVData.at(numberOfChannel).tcorp1));
    ui->tblBSWV->setItem(5,numberOfChannel,itm5_0);
}

void MainWindow::RequestSender( )
{
     for (int i=0;i<ListOfBSWVData.size();i++){
         ListOfBSWVData[i].otvetBuffer.clear();
         ListOfBSWVData[i].otvet.clear();
     }
    int nextMessageNumber;
    switch (currentMessageNumber) {
        case 1:
            nextMessageNumber=255;
            break;
        case 255:
            nextMessageNumber=1;
            break;
        }
//    if (AdminTools==1) {
//        numberOfRowsTestConsole++;
//        if (numberOfRowsTestConsole>30){
//            ui->consolTest->clear();
//            numberOfRowsTestConsole=0;
//        }
//    }
    switch (nextMessageNumber){
            case 1:
                PortMK1osn->otvetBuffer.clear();
                PortMK1rez->otvetBuffer.clear();
                PortMK2osn->otvetBuffer.clear();
                PortMK2rez->otvetBuffer.clear();
                PortMK3osn->otvetBuffer.clear();
                PortMK3rez->otvetBuffer.clear();
                if (AdminTools==1){
                    ui->consolTest->textCursor().insertText(QTime::currentTime().toString("HH:mm:ss")+" - "+QString::number(data[0])+"/"+QString::number(data[1])+"/"+QString::number(data[2])+"/"+QString::number(data[3])+"/"+QString::number(data[4])+"/"+QString::number(data[5])+'\r'); // Вывод текста в консоль
                    ui->consolTest->moveCursor(QTextCursor::End);//Scroll
                }

                if (ListOfBSWVData.at(0).on_off_status==1){

                    if (ListOfBSWVprov.at(0).otvetPoluchen==1){
                        ui->greenMK1o->setVisible(true);
                        ui->redMK1o->setVisible(false);
                    }else{
                        if (firstStart==false){
                            QString errorMessage=QString("Не получен корректный ответ от %1 за %2 мс, код сообщения: 255").arg(ListOfBSWVData.at(0).name).arg(timerDelay);
                            WriteInFileError(errorMessage);
                            Print(errorMessage);
                            ui->greenMK1o->setVisible(false);
                            ui->redMK1o->setVisible(true);
                        }
                    }
                    ListOfBSWVprov[0].otvetPoluchen=0;
                    emit writeToPort1 (nextMessageNumber,dataQ,otvetTelemSize);
                }
                if (ListOfBSWVData.at(1).on_off_status==1){
                    if (ListOfBSWVprov.at(1).otvetPoluchen==1){
                        ui->greenMK1r->setVisible(true);
                        ui->redMK1r->setVisible(false);
                    }else{
                        if (firstStart==false){
                            QString errorMessage=QString("Не получен корректный ответ от %1 за %2 мс, код сообщения: 255").arg(ListOfBSWVData.at(1).name).arg(timerDelay);
                            WriteInFileError(errorMessage);
                            Print(errorMessage);
                            ui->greenMK1r->setVisible(false);
                            ui->redMK1r->setVisible(true);
                        }
                    }
                    ListOfBSWVprov[1].otvetPoluchen=0;
                    emit writeToPort2 (nextMessageNumber,dataQ,otvetTelemSize);
                }
                if (ListOfBSWVData.at(2).on_off_status==1){
                    if (ListOfBSWVprov.at(2).otvetPoluchen==1){
                        ui->greenMK2o->setVisible(true);
                        ui->redMK2o->setVisible(false);
                    }else{
                        if (firstStart==false){
                            QString errorMessage=QString("Не получен корректный ответ от %1 за %2 мс, код сообщения: 255").arg(ListOfBSWVData.at(2).name).arg(timerDelay);
                            WriteInFileError(errorMessage);
                            Print(errorMessage);
                            ui->greenMK2o->setVisible(false);
                            ui->redMK2o->setVisible(true);
                        }
                    }
                    ListOfBSWVprov[2].otvetPoluchen=0;
                    emit writeToPort3 (nextMessageNumber,dataQ,otvetTelemSize);
                }
                if (ListOfBSWVData.at(3).on_off_status==1){
                    if (ListOfBSWVprov.at(3).otvetPoluchen==1){
                        ui->greenMK2r->setVisible(true);
                        ui->redMK2r->setVisible(false);
                    }else{
                        if (firstStart==false){
                            ui->greenMK2r->setVisible(false);
                            ui->redMK2r->setVisible(true);
                            QString errorMessage=QString("Не получен корректный ответ от %1 за %2 мс, код сообщения: 255").arg(ListOfBSWVData.at(3).name).arg(timerDelay);
                            WriteInFileError(errorMessage);
                            Print(errorMessage);
                        }
                    }
                    ListOfBSWVprov[3].otvetPoluchen=0;
                    emit writeToPort4 (nextMessageNumber,dataQ,otvetTelemSize);
                }
                if (ListOfBSWVData.at(4).on_off_status==1){
                    if (ListOfBSWVprov.at(4).otvetPoluchen==1){
                        ui->greenMK3o->setVisible(true);
                        ui->redMK3o->setVisible(false);
                    }else{
                        if (firstStart==false){
                            ui->greenMK3o->setVisible(false);
                            ui->redMK3o->setVisible(true);
                            QString errorMessage=QString("Не получен корректный ответ от %1 за %2 мс, код сообщения: 255").arg(ListOfBSWVData.at(4).name).arg(timerDelay);
                            WriteInFileError(errorMessage);
                            Print(errorMessage);
                        }
                    }
                    ListOfBSWVprov[4].otvetPoluchen=0;
                    emit writeToPort5 (nextMessageNumber,dataQ,otvetTelemSize);
                }
                if (ListOfBSWVData.at(5).on_off_status==1){
                    if (ListOfBSWVprov.at(5).otvetPoluchen==1){
                        ui->greenMK3r->setVisible(true);
                        ui->redMK3r->setVisible(false);
                    }else{
                        if (firstStart==false){
                            ui->greenMK3r->setVisible(false);
                            ui->redMK3r->setVisible(true);
                            QString errorMessage=QString("Не получен корректный ответ от %1 за %2 мс, код сообщения: 255").arg(ListOfBSWVData.at(5).name).arg(timerDelay);
                            WriteInFileError(errorMessage);
                            Print(errorMessage);
                        }
                    }
                    ListOfBSWVprov[5].otvetPoluchen=0;
                    emit writeToPort6 (nextMessageNumber,dataQ,otvetTelemSize);
                }
                currentMessageNumber=nextMessageNumber;
            break;
            case 255:

                    PortMK1osn->otvetBuffer.clear();
                    PortMK1rez->otvetBuffer.clear();
                    PortMK2osn->otvetBuffer.clear();
                    PortMK2rez->otvetBuffer.clear();
                    PortMK3osn->otvetBuffer.clear();
                    PortMK3rez->otvetBuffer.clear();
                    if (AdminTools==1){
                        ui->consolTest->textCursor().insertText(QTime::currentTime().toString("HH:mm:ss")+" - "+QString::number(dataProv[0])+"/"+QString::number(dataProv[1])+"/"+QString::number(dataProv[2])+"/"+QString::number(dataProv[3])+"/"+QString::number(dataProv[4])+"/"+QString::number(dataProv[5])+'\r'); // Вывод текста в консоль
                        ui->consolTest->moveCursor(QTextCursor::End);//Scroll
                    }
                    if (ListOfBSWVData.at(5).on_off_status==1){
                        if (ListOfBSWVData.at(5).otvetPoluchen==1){                            
                            WriteInFileTemplate("MK3r",fileMK3r,5);
                            tblBSWVSetData(5);
                        }else{
                            tblBSWVSetDeafault(6,5);
                            QString errorMessage=QString("Не получен корректный ответ от %1 за %2 мс, код сообщения: 1").arg(ListOfBSWVData.at(5).name).arg(timerDelay);
                            WriteInFileError(errorMessage);
                            Print(errorMessage);
                        }
                        ListOfBSWVData[5].otvetPoluchen=0;
                        emit  writeToPort6(nextMessageNumber,dataQProv,otvetProvSize);
                    }
                    if (ListOfBSWVData.at(0).on_off_status==1){
                        if (ListOfBSWVData.at(0).otvetPoluchen==1){
                            WriteInFileTemplate("MK1o",fileMK1o,0);
                            tblBSWVSetData(0);
                        }else{
                            tblBSWVSetDeafault(6,0);
                            QString errorMessage=QString("Не получен корректный ответ от %1 за %2 мс, код сообщения: 1").arg(ListOfBSWVData.at(0).name).arg(timerDelay);
                            WriteInFileError(errorMessage);
                            Print(errorMessage);
                        }
                        ListOfBSWVData[0].otvetPoluchen=0;
                        emit writeToPort1 (nextMessageNumber,dataQProv,otvetProvSize);
                    }
                    if (ListOfBSWVData.at(1).on_off_status==1){
                        if (ListOfBSWVData.at(1).otvetPoluchen==1){                           
                            WriteInFileTemplate("MK1r",fileMK1r,1);
                            tblBSWVSetData(1);
                        }else{
                            tblBSWVSetDeafault(6,1);
                            QString errorMessage=QString("Не получен корректный ответ от %1 за %2 мс, код сообщения: 1").arg(ListOfBSWVData.at(1).name).arg(timerDelay);
                            WriteInFileError(errorMessage);
                            Print(errorMessage);
                        }
                        ListOfBSWVData[1].otvetPoluchen=0;
                        emit writeToPort2 (nextMessageNumber,dataQProv,otvetProvSize);
                    }
                    if (ListOfBSWVData.at(2).on_off_status==1){
                        if (ListOfBSWVData.at(2).otvetPoluchen==1){
                            tblBSWVSetData(2);                            
                            WriteInFileTemplate("MK2o",fileMK2o,2);
                        }else{
                            tblBSWVSetDeafault(6,2);
                            QString errorMessage=QString("Не получен корректный ответ от %1 за %2 мс, код сообщения: 1").arg(ListOfBSWVData.at(2).name).arg(timerDelay);
                            WriteInFileError(errorMessage);
                            Print(errorMessage);
                        }
                        ListOfBSWVData[2].otvetPoluchen=0;
                        emit writeToPort3 (nextMessageNumber,dataQProv,otvetProvSize);
                    }
                    if (ListOfBSWVData.at(3).on_off_status==1){
                        if (ListOfBSWVData.at(3).otvetPoluchen==1){                            
                            tblBSWVSetData(3);                            
                            WriteInFileTemplate("MK2r",fileMK2r,3);
                        }else{
                            QString errorMessage=QString("Не получен корректный ответ от %1 за %2 мс, код сообщения: 1").arg(ListOfBSWVData.at(3).name).arg(timerDelay);
                            tblBSWVSetDeafault(6,3);
                            WriteInFileError(errorMessage);
                            Print(errorMessage);
                        }
                        ListOfBSWVData[3].otvetPoluchen=0;
                        emit writeToPort4 (nextMessageNumber,dataQProv,otvetProvSize);
                        }
                    if (ListOfBSWVData.at(4).on_off_status==1){
                        if (ListOfBSWVData.at(4).otvetPoluchen==1){                            
                            WriteInFileTemplate("MK3o",fileMK3o,4);
                            tblBSWVSetData(4);
                        }else{
                            tblBSWVSetDeafault(6,4);
                            QString errorMessage=QString("Не получен корректный ответ от %1 за %2 мс, код сообщения: 1").arg(ListOfBSWVData.at(4).name).arg(timerDelay);
                            WriteInFileError(errorMessage);
                            Print(errorMessage);
                        }
                        ListOfBSWVData[4].otvetPoluchen=0;
                        emit writeToPort5 (nextMessageNumber,dataQProv,otvetProvSize);
                    }
                    currentMessageNumber=nextMessageNumber;
                break;
          }
    firstStart=false;
}

void MainWindow::ExchangeErrorAnalizer(QString channelName, int messageNumber, QString errorText, bool paramsNull)
{
    if (errorText!=""){
        Print(errorText);
    }
    if (paramsNull){
        switch (messageNumber){
            case 1:
                for (int i=0;i<ListOfBSWVData.size();i++){
                    if (ListOfBSWVData.at(i).namePort==channelName){
                        tblBSWVSetDeafault(6, i);
                        ListOfBSWVData[i].readyToSend=1;
                    }
                }
            break;
            case 255:
                for (int i=0;i<ListOfBSWVData.size();i++){
                    if (ListOfBSWVData.at(i).namePort==channelName){
                        switch (i){
                        case 0:
                            ui->greenMK1o->setVisible(false);
                            ui->redMK1o->setVisible(true);

                        break;
                        case 1:
                            ui->greenMK1r->setVisible(false);
                            ui->redMK1r->setVisible(true);
                        break;
                        case 2:
                            ui->greenMK2o->setVisible(false);
                            ui->redMK2o->setVisible(true);
                        break;
                        case 3:
                            ui->greenMK2r->setVisible(false);
                            ui->redMK2r->setVisible(true);
                        break;
                        case 4:
                            ui->greenMK3o->setVisible(false);
                            ui->redMK3o->setVisible(true);
                        break;
                        case 5:
                            ui->greenMK3r->setVisible(false);
                            ui->redMK3r->setVisible(true);
                        break;

                        }
                        ListOfBSWVprov[i].readyToSend=1;

                    }
                }
            break;
            }

    }
}

void MainWindow::ErrorThread()
{
    Print("Thread Error!!!");
}

void MainWindow::on_btnStart_clicked()
{    
    if (timerRequest->isActive()){
        stopRequest=true;

        timerRequest->stop();
        ui->btnStart->setEnabled(false);
        ui->tblBSWV->setEnabled(false);
        ui->tabWidget->setTabEnabled(0,true);
        ui->tabWidget->setTabEnabled(3,true);
        ui->tabWidget->setTabEnabled(2,true);
        ui->btnStart->setText("Начать обмен");
        delay(500);
        ui->greenMK1o->setVisible(false);
        ui->redMK1o->setVisible(true);
        ui->greenMK1r->setVisible(false);
        ui->redMK1r->setVisible(true);
        ui->greenMK2o->setVisible(false);
        ui->redMK2o->setVisible(true);
        ui->greenMK2r->setVisible(false);
        ui->redMK2r->setVisible(true);
        ui->greenMK3o->setVisible(false);
        ui->redMK3o->setVisible(true);
        ui->greenMK3r->setVisible(false);
        ui->redMK3r->setVisible(true);
        ui->btnStart->setEnabled(true);        
    } else {
        for (int i=0;i<ListOfBSWVData.size();i++){
            ListOfBSWVData[i].readyToSend=true;
        }
        firstStart=true;
        ui->tblBSWV->setEnabled(true);
        ui->tabWidget->setTabEnabled(0,false);
        ui->tabWidget->setTabEnabled(3,false);
        ui->tabWidget->setTabEnabled(2,false);
        ui->btnStart->setText("Закончить обмен");
        currentMessageNumber=255;
        timerRequest->start();
   }
}

MainWindow::~MainWindow()
{

    delete window;
    //window->deleteLater();
    delete timerReconnect;
    //timerReconnect->deleteLater();    

    delete timerCloseErrorWindow;
    //timerCloseErrorWindow->deleteLater();
//PortMK1osn->DisconnectPort();
//PortMK2osn->DisconnectPort();
//PortMK3osn->DisconnectPort();
//PortMK1rez->DisconnectPort();
//PortMK2rez->DisconnectPort();
//PortMK1rez->DisconnectPort();
//    PortMK1osn->deleteLater();
//    PortMK1rez->deleteLater();
//    PortMK2osn->deleteLater();
//    PortMK2rez->deleteLater();
//    PortMK3osn->deleteLater();
//    PortMK3rez->deleteLater();
//        thread_MK1osn->quit();
//         thread_MK1rez->quit();
//        thread_MK2osn->quit();
//        thread_MK2rez->quit();
//        thread_MK3osn->quit();
//        thread_MK3rez->quit();
//    thread_MK1osn->deleteLater();
//    thread_MK1rez->deleteLater();
//    thread_MK2osn->deleteLater();
//    thread_MK2rez->deleteLater();
//    thread_MK3osn->deleteLater();
//    thread_MK3rez->deleteLater();

delete PortMK1osn;
delete PortMK1rez;
delete PortMK2osn;
delete PortMK2rez;
delete PortMK3osn;
delete PortMK3rez;
delete thread_MK1osn;
delete thread_MK1rez;
delete thread_MK2osn;
delete thread_MK2rez;
delete thread_MK3osn;
delete thread_MK3rez;
delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->consolTest->clear();
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if (index==1) ChangeColor();
}

void MainWindow::on_pbCancelReconnect_clicked()
{
    if (timerReconnect->isActive()){
        //ui->pbCancelReconnect->setText("Включить автоподключение конвертеров");
        timerReconnect->disconnect();
        ui->pbCancelReconnect->setEnabled(false);
    }else{
//        ui->pbCancelReconnect->setText("Отключить автоподключение конвертеров");
//        connect(timerReconnect, SIGNAL(timeout()), this, SLOT(Reconnect()));
//        timerReconnect->start();
    }
}

