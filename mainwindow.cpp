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
void MainWindow::LoadSettings()
{
    QString dis1, serial1, dis2, serial2,dis3, serial3,dis4, serial4,dis5, serial5,dis6, serial6;
    QSettings setting("ports.ini", QSettings::IniFormat); //ports.ini файл должен быть в одной папке с exe
    setting.beginGroup("MK1-osn");// [MK1-osn] в ини файле
    QString status1 = setting.value("work","0").toString();
    if ( status1 == "on") {
         dis1 = setting.value("description","0").toString();
         serial1 = setting.value("serialNumber","0").toString();
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
    }
    setting.endGroup();
    setting.beginGroup("MK1-rez");// [MK1-rez] в ини файле
    QString status2 = setting.value("work","0").toString();
    if ( status2 == "on"){
        dis2 = setting.value("description","0").toString();
        serial2 = setting.value("serialNumber","0").toString();
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
    }
    setting.endGroup();
    setting.beginGroup("MK2-osn");// [MK2-osn] в ини файле
    QString status3 = setting.value("work","0").toString();
    if ( status3 == "on") {
    dis3 = setting.value("description","0").toString();
    serial3 = setting.value("serialNumber","0").toString();
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
    }
    setting.endGroup();
    setting.beginGroup("MK2-rez");// [MK2-rez] в ини файле
    QString status4 = setting.value("work","0").toString();
    if ( status4 == "on"){
        dis4 = setting.value("description","0").toString();
        serial4 = setting.value("serialNumber","0").toString();
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
    }
    setting.endGroup();
    setting.beginGroup("MK3-osn");// [MK3-osn] в ини файле
    QString status5 = setting.value("work","0").toString();
    if ( status5 == "on") {
        dis5 = setting.value("description","0").toString();
        serial5 = setting.value("serialNumber","0").toString();
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
    }
    setting.endGroup();
    setting.beginGroup("MK3-rez");// [MK3-rez] в ини файле
    QString status6 = setting.value("work","0").toString();
    if ( status6 == "on"){
        dis6 = setting.value("description","0").toString();
        serial6 = setting.value("serialNumber","0").toString();
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
    }
    setting.endGroup();

}

void MainWindow::ErrorAnalyzer(QSerialPort::SerialPortError error,QString portName)
{
    if (error!=0){
    timerReconnect->start(1000);
    for (int i=0;i<ListOfBSWVData.size();i++){
        if (ListOfBSWVData[i].namePort==portName){
            ListOfBSWVData[i].errorStatus=1;
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
        QString status1 = setting.value("work","0").toString();
        if ( status1 == "on") {
             dis1 = setting.value("description","0").toString();
             serial1 = setting.value("serialNumber","0").toString();
             QString name1 = getPortName(dis1,serial1);
             emit savesettings1(name1, baudrate, databits, parity, stopbits, flowcontrol);
             emit con1();
        }
        setting.endGroup();
    }
    if (ListOfBSWVData[1].errorStatus==1) {
        setting.beginGroup("MK1-rez");// [MK1-rez] в ини файле
        QString status2 = setting.value("work","0").toString();
        if ( status2 == "on"){
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
        QString status3 = setting.value("work","0").toString();
        if ( status3 == "on") {
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
        QString status4 = setting.value("work","0").toString();
        if ( status4 == "on"){
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
        QString status5 = setting.value("work","0").toString();
        if ( status5 == "on") {
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
         QString status6 = setting.value("work","0").toString();
         if ( status6 == "on"){
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
   window = new ErrorForm(this);



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
    ListOfBSWVt.append(BSWVt);
    BSWVt.name = "MK1-rez"; BSWVt.namePort = "Com";BSWVt.icap2=0; BSWVt.icap1 = 0; BSWVt.u2 = 0; BSWVt.u1 = 0;BSWVt.tcorp2 = 0; BSWVt.tcorp1=0;BSWVt.uref=0;
    ListOfBSWVt.append(BSWVt);
    BSWVt.name = "MK2-osn"; BSWVt.namePort = "Com";BSWVt.icap2=0; BSWVt.icap1 = 0; BSWVt.u2 = 0; BSWVt.u1 = 0;BSWVt.tcorp2 = 0; BSWVt.tcorp1=0;BSWVt.uref=0;
    ListOfBSWVt.append(BSWVt);
    BSWVt.name = "MK2-rez"; BSWVt.namePort = "Com";BSWVt.icap2=0; BSWVt.icap1 = 0; BSWVt.u2 = 0; BSWVt.u1 = 0;BSWVt.tcorp2 = 0; BSWVt.tcorp1=0;BSWVt.uref=0;
    ListOfBSWVt.append(BSWVt);
    BSWVt.name = "MK3-osn"; BSWVt.namePort = "Com";BSWVt.icap2=0; BSWVt.icap1 = 0; BSWVt.u2 = 0; BSWVt.u1 = 0;BSWVt.tcorp2 = 0; BSWVt.tcorp1=0;BSWVt.uref=0;
    ListOfBSWVt.append(BSWVt);
    BSWVt.name = "MK3-rez"; BSWVt.namePort = "Com";BSWVt.icap2=0; BSWVt.icap1 = 0; BSWVt.u2 = 0; BSWVt.u1 = 0;BSWVt.tcorp2 = 0; BSWVt.tcorp1=0;BSWVt.uref=0;
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
    port *PortMK1osn = new port();
    port *PortMK1rez = new port();
    port *PortMK2osn = new port();
    port *PortMK2rez = new port();
    port *PortMK3osn = new port();
    port *PortMK3rez = new port();

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
    //-----------Конец формирования исходящего сообщения для БСШ-В (тип 34 - проверка номера МУКа)-----------
    timerVivod = new QTimer();
    timerReconnect = new QTimer();
    timerZaprosaTelem = new QTimer();
    timerZaprosaTarir = new QTimer();
    timerZaprosaProv = new QTimer();
    timerZaprosaTelem->start(1000);
    QString fname = QDate::currentDate().toString("dd.MM.yyyy")+".txt";
    file.setFileName(fname);
    QString fEname = QDate::currentDate().toString("dd.MM.yyyy")+"_Errors.txt";
    fileError.setFileName(fEname);
    QString fACPname = QDate::currentDate().toString("dd.MM.yyyy")+"_ACP.txt";
    fileACP.setFileName(fACPname);

    QTimer::singleShot(200,this,SLOT(TimerTarirStart()));
    QTimer::singleShot(300,this,SLOT(TimerProvStart()));
    QTimer::singleShot(500,this,SLOT(TimerVivodStart())); //старт таймера для вывода на экран данных через 50 мс после их получения
    connect(timerZaprosaTelem, SIGNAL(timeout()), this, SLOT(OtpravkaZaprosaTelem()));
    connect(timerZaprosaTarir, SIGNAL(timeout()), this, SLOT(OtpravkaZaprosaTarir()));
    connect(timerZaprosaProv,SIGNAL(timeout()), this,SLOT(OtpravkaZaprosaProv()));
    connect(timerZaprosaTelem,SIGNAL(timeout()),this, SLOT(ChangeColor()));
    connect(this, SIGNAL(savesettings1(QString,int,int,int,int,int)),PortMK1osn,SLOT(Write_Settings_Port(QString,int,int,int,int,int)));//Слот - ввод настроек!
    connect(this, SIGNAL(savesettings2(QString,int,int,int,int,int)),PortMK1rez,SLOT(Write_Settings_Port(QString,int,int,int,int,int)));//Слот - ввод настроек!
    connect(this, SIGNAL(savesettings3(QString,int,int,int,int,int)),PortMK2osn,SLOT(Write_Settings_Port(QString,int,int,int,int,int)));//Слот - ввод настроек!
    connect(this, SIGNAL(savesettings4(QString,int,int,int,int,int)),PortMK2rez,SLOT(Write_Settings_Port(QString,int,int,int,int,int)));//Слот - ввод настроек!
    connect(this, SIGNAL(savesettings5(QString,int,int,int,int,int)),PortMK3osn,SLOT(Write_Settings_Port(QString,int,int,int,int,int)));//Слот - ввод настроек!
    connect(this, SIGNAL(savesettings6(QString,int,int,int,int,int)),PortMK3rez,SLOT(Write_Settings_Port(QString,int,int,int,int,int)));//Слот - ввод настроек!
    connect(this, SIGNAL(writeData(QByteArray)),PortMK1osn,SLOT(WriteToPort(QByteArray)));
    connect(this, SIGNAL(writeData(QByteArray)),PortMK2osn,SLOT(WriteToPort(QByteArray)));
    connect(this, SIGNAL(writeData(QByteArray)),PortMK3osn,SLOT(WriteToPort(QByteArray)));
    connect(this, SIGNAL(writeData(QByteArray)),PortMK1rez,SLOT(WriteToPort(QByteArray)));
    connect(this, SIGNAL(writeData(QByteArray)),PortMK2rez,SLOT(WriteToPort(QByteArray)));
    connect(this, SIGNAL(writeData(QByteArray)),PortMK3rez,SLOT(WriteToPort(QByteArray)));
    connect(this, SIGNAL(con1()),PortMK1osn,SLOT(ConnectPort()));
    connect(this, SIGNAL(con2()),PortMK1rez,SLOT(ConnectPort()));
    connect(this, SIGNAL(con3()),PortMK2osn,SLOT(ConnectPort()));
    connect(this, SIGNAL(con4()),PortMK2rez,SLOT(ConnectPort()));
    connect(this, SIGNAL(con5()),PortMK3osn,SLOT(ConnectPort()));
    connect(this, SIGNAL(con6()),PortMK3rez,SLOT(ConnectPort()));
    connect(PortMK1osn, SIGNAL(error_(QString)), this, SLOT(Print(QString)));//Лог ошибок соединения
    connect(PortMK2osn, SIGNAL(error_(QString)), this, SLOT(Print(QString)));
    connect(PortMK3osn, SIGNAL(error_(QString)), this, SLOT(Print(QString)));
    connect(PortMK1rez, SIGNAL(error_(QString)), this, SLOT(Print(QString)));
    connect(PortMK2rez, SIGNAL(error_(QString)), this, SLOT(Print(QString)));
    connect(PortMK3rez, SIGNAL(error_(QString)), this, SLOT(Print(QString)));
    connect(ui->btnDisconnect, SIGNAL(clicked()),PortMK1osn,SLOT(DisconnectPort()));//по нажатию кнопки отключить порт
    connect(ui->btnDisconnect, SIGNAL(clicked()),PortMK2osn,SLOT(DisconnectPort()));//по нажатию кнопки отключить порт
    connect(ui->btnDisconnect, SIGNAL(clicked()),PortMK3osn,SLOT(DisconnectPort()));//по нажатию кнопки отключить порт
    connect(ui->btnDisconnect, SIGNAL(clicked()),PortMK1rez,SLOT(DisconnectPort()));//по нажатию кнопки отключить порт
    connect(ui->btnDisconnect, SIGNAL(clicked()),PortMK2rez,SLOT(DisconnectPort()));//по нажатию кнопки отключить порт
    connect(ui->btnDisconnect, SIGNAL(clicked()),PortMK3rez,SLOT(DisconnectPort()));//по нажатию кнопки отключить порт
    connect(PortMK1osn, SIGNAL(sendBSWVtm(QByteArray,QString)),this,SLOT(Kompanovka(QByteArray,QString)));
    connect(PortMK1rez, SIGNAL(sendBSWVtm(QByteArray,QString)),this,SLOT(Kompanovka(QByteArray,QString)));
    connect(PortMK2osn, SIGNAL(sendBSWVtm(QByteArray,QString)),this,SLOT(Kompanovka(QByteArray,QString)));
    connect(PortMK2rez, SIGNAL(sendBSWVtm(QByteArray,QString)),this,SLOT(Kompanovka(QByteArray,QString)));
    connect(PortMK3rez, SIGNAL(sendBSWVtm(QByteArray,QString)),this,SLOT(Kompanovka(QByteArray,QString)));
    connect(PortMK3osn, SIGNAL(sendBSWVtm(QByteArray,QString)),this,SLOT(Kompanovka(QByteArray,QString)));
    connect(timerVivod, SIGNAL(timeout()), this, SLOT(Vivod()));    
    connect(this, SIGNAL(readyToAnalize(QByteArray,QString)),this,SLOT(Analize(QByteArray,QString)));
    connect(ui->checkBox, SIGNAL(clicked()), this, SLOT(Knopka()));
    connect(this, SIGNAL(errorMessage(QString)), this,SLOT(Print(QString))); //Не тот же эррор месадж, что от порта
    connect(this, SIGNAL(errorMessage(QString)), this,SLOT(WriteInFileError(QString)));
    connect(timerVivod, SIGNAL(timeout()), this, SLOT(WriteInFile()));    
    connect(ui->pushButton, SIGNAL(clicked()),this,SLOT(LoadSettings()));
    LoadSettings();
    connect(PortMK1osn, SIGNAL(errorMessage(QSerialPort::SerialPortError,QString)),this,SLOT(ErrorAnalyzer(QSerialPort::SerialPortError,QString)));
    connect(PortMK2osn, SIGNAL(errorMessage(QSerialPort::SerialPortError,QString)),this,SLOT(ErrorAnalyzer(QSerialPort::SerialPortError,QString)));
    connect(PortMK3osn, SIGNAL(errorMessage(QSerialPort::SerialPortError,QString)),this,SLOT(ErrorAnalyzer(QSerialPort::SerialPortError,QString)));
    connect(PortMK1rez, SIGNAL(errorMessage(QSerialPort::SerialPortError,QString)),this,SLOT(ErrorAnalyzer(QSerialPort::SerialPortError,QString)));
    connect(PortMK2rez, SIGNAL(errorMessage(QSerialPort::SerialPortError,QString)),this,SLOT(ErrorAnalyzer(QSerialPort::SerialPortError,QString)));
    connect(PortMK3rez, SIGNAL(errorMessage(QSerialPort::SerialPortError,QString)),this,SLOT(ErrorAnalyzer(QSerialPort::SerialPortError,QString)));

    connect(timerReconnect, SIGNAL(timeout()), this, SLOT(Reconnect(QString)));
}

void MainWindow::TimerVivodStart()
{
    timerVivod->start(1000);

        //QString DataAsString = QString(ListOfBSWVData.at(2).otvet);
       // ui->lbl->setText(DataAsString);
}

void MainWindow::TimerProvStart()
{
    timerZaprosaProv->start(1000);
}

void MainWindow::TimerTarirStart()
{
    timerZaprosaTarir->start(1000);
}

void MainWindow::on_btnNomer_clicked()
{
    OtpravkaZaprosaNomer();
    QTimer::singleShot(5000,this,SLOT(ProverkaNomera()));
}
void MainWindow:: OtpravkaZaprosaTelem()
{
    QByteArray dataQ = QByteArray::fromRawData((char*)data,sizeof(data));
    //dataQ[0] = reinterpret_cast<QByteArray>(data[0].data());
    emit writeData (dataQ);
}

void MainWindow:: OtpravkaZaprosaTarir()
{
    QByteArray dataQt = QByteArray::fromRawData((char*)dataT,sizeof(dataT));
    emit writeData (dataQt);
}

void MainWindow::OtpravkaZaprosaNomer()
{
    QByteArray dataQNomer = QByteArray::fromRawData((char*)dataNomer,sizeof(dataNomer));
    emit writeData (dataQNomer);

}

void MainWindow::OtpravkaZaprosaProv()
{
    QByteArray dataQProv = QByteArray::fromRawData((char*)dataProv,sizeof(dataProv));
    emit writeData (dataQProv);
}


void MainWindow::Kompanovka(QByteArray dataRead, QString comName)
{
    for (int i=0;i<ListOfBSWVData.size();i++){
            if (ListOfBSWVData.at(i).namePort == comName){
                otvet.append(dataRead);
                for (int j = 0; otvet[j]!=char(0xAA);j++) {
                    otvet.remove(0,1);
                }

                if (otvet.size()>3){
                switch (otvet[3]){
                case char (1):
                   if (otvet.size() == otvetTelemSize){
                       ListOfBSWVData[i].otvet = otvet;
                       emit readyToAnalize(ListOfBSWVData.at(i).otvet, ListOfBSWVData.at(i).namePort);
                       otvet.clear();
                    }
                    break;
                case char (17):
                   if (otvet.size() == otvetTarirSize){
                       ListOfBSWVt[i].otvet = otvet;
                       emit readyToAnalize(ListOfBSWVt.at(i).otvet, ListOfBSWVt.at(i).namePort);
                       otvet.clear();
                   }
                break;
                case char (34):
                   if (otvet.size() == otvetMKSize){
                       ListOfBSWVnomer[i].otvet = otvet;
                       emit readyToAnalize(ListOfBSWVnomer.at(i).otvet, ListOfBSWVnomer.at(i).namePort);
                       otvet.clear();
                   }
                break;
                case char(255):
                    if (otvet.size() == otvetProvSize){
                        ListOfBSWVprov[i].otvet = otvet;
                        emit readyToAnalize(ListOfBSWVprov.at(i).otvet, ListOfBSWVprov.at(i).namePort);
                        otvet.clear();
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
                            }
                            else {ListOfBSWVData[i].otvetPoluchen=0;
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
                            }
                            else {ListOfBSWVt[i].otvetPoluchen=0;
                            }
                        }
                    }
                 break;
                 case 34:
                      for (int i=0;i<ListOfBSWVnomer.size();i++){
                          if (ListOfBSWVnomer.at(i).namePort == comName){
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
                                      if (nChan==1)
                                       {
                                        ListOfBSWVnomer[i].nChan = "-резервный";
                                       }
                                    ListOfBSWVnomer[i].otvetPoluchen=1;
                              }
                              else {ListOfBSWVnomer[i].otvetPoluchen=0;
                              }
                          }
                      }
                 break;
                 case 255:
                      for (int i=0;i<ListOfBSWVprov.size();i++){
                          if (ListOfBSWVprov.at(i).namePort == comName){
                             unsigned char upperCRCR = Crc16(buffer,le)>>8;
                             unsigned char lowerCRCR = Crc16(buffer,le);
                              if ((upperCRCR==upperCRC)&&(lowerCRCR==lowerCRC)){
                              ListOfBSWVprov[i].otvetPoluchen=1;
                              }
                              else {ListOfBSWVprov[i].otvetPoluchen=0;
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

void MainWindow::Knopka()
{

    if (ui->checkBox->isChecked()){
        ui->greenMK1o->setVisible(true);
        ui->redMK1o->setVisible(false);
        ui->greenMK2o->setVisible(true);
        ui->redMK2o->setVisible(false);
        ui->greenMK3o->setVisible(true);
        ui->redMK3o->setVisible(false);
        ui->greenMK1r->setVisible(true);
        ui->redMK1r->setVisible(false);
        ui->greenMK2r->setVisible(true);
        ui->redMK2r->setVisible(false);
        ui->greenMK3r->setVisible(true);
        ui->redMK3r->setVisible(false);

    }
    else{
        ui->greenMK1o->setVisible(false);
        ui->redMK1o->setVisible(true);
        ui->greenMK2o->setVisible(false);
        ui->redMK2o->setVisible(true);
        ui->greenMK3o->setVisible(false);
        ui->redMK3o->setVisible(true);
        ui->greenMK1r->setVisible(false);
        ui->redMK1r->setVisible(true);
        ui->greenMK2r->setVisible(false);
        ui->redMK2r->setVisible(true);
        ui->greenMK3r->setVisible(false);
        ui->redMK3r->setVisible(true);
    }

}

void MainWindow::ChangeColor()
{
    ui->tabWidget->tabBar()->setTabTextColor(1,Qt::black);
}

void MainWindow::Print(QString dat)
{
    ui->consol->textCursor().insertText(dat+'\r'); // Вывод текста в консоль
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
            error = "Ответ на сообщение 34 от "+ ListOfBSWVprov.at(f).name +" не получен";
            emit errorMessage (error);
        }        
    }
}

void MainWindow::WriteInFile()
{
    QTextStream streamACP(&fileACP);
    QTextStream stream(&file);
    if (file.exists()){//Проверка - существует ли файл
            if (file.open(QIODevice::WriteOnly | QIODevice::Append)) { // Append - для записи в конец файла
                QString str = QTime::currentTime().toString("ss");
                int time = str.toInt();
                if (time%5==0){
                    stream<<QString::fromUtf8("Время    |    Канал      | Суммарный ток нагрузки 2 | Суммарный ток нагрузки 1  | Напряжение на силовых шинах 2 |"
                   "Напряжение на силовых шинах 1  | Температура 2 корпуса прибора |  Температура 1 корпуса прибора\r\n");
                }
                for (int i=0;i<ListOfBSWVData.size();i++){
                    QString log =QTime::currentTime().toString("HH:mm:ss") +" |   "+ ListOfBSWVData[i].name+"\t |\t\t"+QString::number(ListOfBSWVData[i].icap2)+"\t    |\t\t"+
                            QString::number(ListOfBSWVData[i].icap1)+"\t\t|\t\t"+QString::number(ListOfBSWVData[i].u2)+"\t\t|\t\t "+QString::number(ListOfBSWVData[i].u1)
                            +"\t\t|\t\t "+ QString::number(ListOfBSWVData[i].tcorp2)+"\t\t|\t\t "+ QString::number(ListOfBSWVData[i].tcorp1)+"\r\n";
                    stream<<log;
                }                
            }
    }
    else {
           if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {//Если файл только создается, то в первую строчку записываем название параметра

                  stream<<QString::fromUtf8("Время    |    Канал      | Суммарный ток нагрузки 2 | Суммарный ток нагрузки 1  | Напряжение на силовых шинах 2 |"
                  "Напряжение на силовых шинах 1  | Температура 2 корпуса прибора |  Температура 1 корпуса прибора\r\n");
                  for (int i=0;i<ListOfBSWVData.size();i++){
                      QString log =QTime::currentTime().toString("HH:mm:ss") +" |   "+ ListOfBSWVData[i].name+"\t |\t\t"+QString::number(ListOfBSWVData[i].icap2)+"\t    |\t\t"+
                              QString::number(ListOfBSWVData[i].icap1)+"\t\t|\t\t"+QString::number(ListOfBSWVData[i].u2)+"\t\t|\t\t "+QString::number(ListOfBSWVData[i].u1)
                              +"\t\t|\t\t "+ QString::number(ListOfBSWVData[i].tcorp2)+"\t\t|\t\t "+ QString::number(ListOfBSWVData[i].tcorp1)+"\r\n";

                      stream<<log;
               }
            }
    }
    file.close();


    if (fileACP.exists()){//Проверка - существует ли файл
            if (fileACP.open(QIODevice::WriteOnly | QIODevice::Append)) { // Append - для записи в конец файла
                QString str = QTime::currentTime().toString("ss");
                int time = str.toInt();
                if (time%5==0){
                    streamACP<<QString::fromUtf8("Время    |    Канал      | Суммарный ток нагрузки 2 | Суммарный ток нагрузки 1  | Напряжение на силовых шинах 2 |"
                               "Напряжение на силовых шинах 1  | Температура 2 корпуса прибора |  Температура 1 корпуса прибора|   Опорное напряжение\r\n");
                }
                for (int i=0;i<ListOfBSWVt.size();i++){

                    QString logACP =QTime::currentTime().toString("HH:mm:ss") +" |   "+ ListOfBSWVt[i].name+"\t |\t\t"+QString::number(ListOfBSWVt[i].icap2)+"\t    |\t\t"+
                                    QString::number(ListOfBSWVt[i].icap1)+"\t\t|\t\t"+QString::number(ListOfBSWVt[i].u2)+"\t\t|\t\t "+QString::number(ListOfBSWVt[i].u1)
                                    +"\t\t|\t\t "+ QString::number(ListOfBSWVt[i].tcorp2)+"\t\t|\t\t "+ QString::number(ListOfBSWVt[i].tcorp1)+"\t\t|\t\t "+ QString::number(ListOfBSWVt[i].uref)+"\r\n";


                    streamACP<<logACP;
                }
            }
    }
    else {
           if (fileACP.open(QIODevice::WriteOnly | QIODevice::Append)) {//Если файл только создается, то в первую строчку записываем название параметра

            streamACP<<QString::fromUtf8("Время    |    Канал      | Суммарный ток нагрузки 2 | Суммарный ток нагрузки 1  | Напряжение на силовых шинах 2 |"
                       "Напряжение на силовых шинах 1  | Температура 2 корпуса прибора |  Температура 1 корпуса прибора|   Опорное напряжение\r\n");

            for (int i=0;i<ListOfBSWVt.size();i++){
                    QString logACP =QTime::currentTime().toString("HH:mm:ss") +" |   "+ ListOfBSWVt[i].name+"\t |\t\t"+QString::number(ListOfBSWVt[i].icap2)+"\t    |\t\t"+
                            QString::number(ListOfBSWVt[i].icap1)+"\t\t|\t\t"+QString::number(ListOfBSWVt[i].u2)+"\t\t|\t\t "+QString::number(ListOfBSWVt[i].u1)
                            +"\t\t|\t\t "+ QString::number(ListOfBSWVt[i].tcorp2)+"\t\t|\t\t "+ QString::number(ListOfBSWVt[i].tcorp1)+"\t\t|\t\t "+ QString::number(ListOfBSWVt[i].uref)+"\r\n";
                    streamACP<<logACP;
               }
            }
    }
    fileACP.close();
}

void MainWindow::WriteInFileError(QString error)
{
    QTextStream stream(&fileError);
    QTextStream stream1(&fileError);
    stream.setFieldWidth(16);
    stream.setFieldAlignment(QTextStream::AlignLeft);

    if (fileError.exists()){//Проверка - существует ли файл
            if (fileError.open(QIODevice::WriteOnly | QIODevice::Append)) { // Append - для записи в конец файла
               // QString log =QTime::currentTime().toString("HH:mm:ss") +"  |  "+error+"\r\n";
               // stream<<log;
               QString log1 = QTime::currentTime().toString("HH:mm:ss")+"  | ";
                QString log2 = error;
                stream<<log1<<log2+"\r\n";
            }
    }
    else {
           if (fileError.open(QIODevice::WriteOnly | QIODevice::Append)) {//Если файл только создается, то в первую строчку записываем название параметра                     
           //stream<< QString::fromUtf8(" Время             Описание ошибки \r\n");
          // stream<<QTime::currentTime().toString("HH:mm:ss") +"  |  "+error+"\r\n";
           stream<<QString::fromUtf8("Время")+"     |"<<QString::fromUtf8("Описание ошибки")+"\r\n";
           QString log1 = QTime::currentTime().toString("HH:mm:ss")+"  | ";
           QString log2 = error;
           stream<<log1<<log2+"\r\n";
           }
    }
    fileError.close();
}

void MainWindow::Vivod(){
for (int i=0;i<ListOfBSWVData.size();i++){
    if (ListOfBSWVData.at(i).otvetPoluchen==1){
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
    ListOfBSWVData[i].otvetPoluchen=0;
    }
    else {
        error = "Ответ на сообщение 1 от "+ListOfBSWVData.at(i).name+" не получен";
        emit errorMessage (error);
    }
//  itm1_2->setTextColor(Qt::red); //задание цвета у текста определенной ячейки таблицы
//  itm1_2->setBackgroundColor(Qt::black); //задание цвета самой определенной ячейки таблицы
//  QTableWidgetItem *itm1_0 = new QTableWidgetItem(tr("%1").arg(pcB[5]*0.2+0)); //перевод в QString данных из unsigned char
}
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

    }
    else {
        error = "Ответ на сообщение 17 от "+ ListOfBSWVt.at(j).name +" не получен";
        emit errorMessage (error);
    }
}

for (int k=0;k<ListOfBSWVprov.size();k++){
    if (ListOfBSWVprov.at(k).otvetPoluchen==0){
        if (ListOfBSWVprov.at(k).name=="MK1-osn"){
            ui->greenMK1o->setVisible(false);
            ui->redMK1o->setVisible(true);
        }
        if (ListOfBSWVprov.at(k).name=="MK1-rez"){
            ui->greenMK1r->setVisible(false);
            ui->redMK1r->setVisible(true);
        }
        if (ListOfBSWVprov.at(k).name=="MK2-osn"){
            ui->greenMK2o->setVisible(false);
            ui->redMK2o->setVisible(true);
        }
        if (ListOfBSWVprov.at(k).name=="MK2-rez"){
            ui->greenMK2r->setVisible(false);
            ui->redMK2r->setVisible(true);
        }
        if (ListOfBSWVprov.at(k).name=="MK3-osn"){
            ui->greenMK3o->setVisible(false);
            ui->redMK3o->setVisible(true);
        }
        if (ListOfBSWVprov.at(k).name=="MK3-rez"){
            ui->greenMK3r->setVisible(false);
            ui->redMK3r->setVisible(true);
        }
        error = "Ответ на сообщение 255 от "+ListOfBSWVprov.at(k).name + " не получен";
        emit errorMessage (error);
    }
    if (ListOfBSWVprov.at(k).otvetPoluchen==1){
        if (ListOfBSWVprov.at(k).name=="MK1-osn"){
            ui->greenMK1o->setVisible(true);
            ui->redMK1o->setVisible(false);
        }
        if (ListOfBSWVprov.at(k).name=="MK1-rez"){
            ui->greenMK1r->setVisible(true);
            ui->redMK1r->setVisible(false);
        }
        if (ListOfBSWVprov.at(k).name=="MK2-osn"){
            ui->greenMK2o->setVisible(true);
            ui->redMK2o->setVisible(false);
        }
        if (ListOfBSWVprov.at(k).name=="MK2-rez"){
            ui->greenMK2r->setVisible(true);
            ui->redMK2r->setVisible(false);
        }
        if (ListOfBSWVprov.at(k).name=="MK3-osn"){
            ui->greenMK3o->setVisible(true);
            ui->redMK3o->setVisible(false);
        }
        if (ListOfBSWVprov.at(k).name=="MK3-rez"){
            ui->greenMK3r->setVisible(true);
            ui->redMK3r->setVisible(false);
        }
        ListOfBSWVprov[k].otvetPoluchen=0;
    }

}
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

MainWindow::~MainWindow()
{
    delete ui;
}


