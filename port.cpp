#include "port.h"

port::port(QObject *parent) : QObject(parent)
{
    connect(&thisPort,SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError))); // подключаем проверку ошибок порта
    connect(&thisPort, SIGNAL(readyRead()),this,SLOT(ReadInPort()));

}


void port :: Write_Settings_Port(QString name, int baudrate,int DataBits,
                         int Parity,int StopBits, int FlowControl){//заносим параметры порта в структуру данных
    SettingsPort.name = name;
    SettingsPort.baudRate = (QSerialPort::BaudRate) baudrate;
    SettingsPort.dataBits = (QSerialPort::DataBits) DataBits;
    SettingsPort.parity = (QSerialPort::Parity) Parity;
    SettingsPort.stopBits = (QSerialPort::StopBits) StopBits;
    SettingsPort.flowControl = (QSerialPort::FlowControl) FlowControl;
}

void port :: ConnectPort(void)//процедура подключения
{
    thisPort.setPortName(SettingsPort.name);
    if (thisPort.open(QIODevice::ReadWrite))
    {
        if (thisPort.setBaudRate(SettingsPort.baudRate)
                && thisPort.setDataBits(SettingsPort.dataBits)//DataBits
                && thisPort.setParity(SettingsPort.parity)
                && thisPort.setStopBits(SettingsPort.stopBits)
                && thisPort.setFlowControl(SettingsPort.flowControl))
        {
            if (thisPort.isOpen())
            {
                error_((SettingsPort.name.toLocal8Bit()+ " >> Открыт! \r"));
            }
        } else
        {
            thisPort.close();
            error_(thisPort.errorString().toLocal8Bit());
        }
    }
    else
    {
        thisPort.close();
        error_(thisPort.errorString().toLocal8Bit());
    }
}
void port::handleError(QSerialPort::SerialPortError error)//проверка ошибок при работе
{
    if ( (thisPort.isOpen()) && (error == QSerialPort::ResourceError))
    {
        error_(thisPort.errorString().toLocal8Bit());
        DisconnectPort();
    }
}

void port::DisconnectPort()//Отключаем порт
{
    if(thisPort.isOpen())
    {
        thisPort.close();
        error_(SettingsPort.name.toLocal8Bit() + " >> Закрыт!\r");
    }
}

void port :: WriteToPort(QByteArray data){//Запись данных в порт
    if(thisPort.isOpen()){
thisPort.write(data,6);
    }
}

void port :: ReadInPort(){//Чтение данных из порта
    QByteArray dataRead;
    dataRead.append(thisPort.readAll());
    unsigned char* buffer = new unsigned char[ dataRead.size() ];
    memcpy( buffer, dataRead.data(), dataRead.size() );
    for (int i=0;( buffer[i] !=0xAA);i++){

        dataRead.remove(i,1);
    }
    if (dataRead.size() >= 15){
    QString comName = thisPort.portName();
    dataRead.resize(15);
    emit sendBSWVtm(dataRead,comName);
    dataRead.clear();
    }
    //((QString)(adr.toInt())).toLatin1().toHex()
}

port::~port()
{
    thisPort.close();
}
