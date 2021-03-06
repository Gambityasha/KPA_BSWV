#include "port.h"

port::port(QObject *parent) : QObject(parent)
{
    connect(&thisPort,SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError))); // подключаем проверку ошибок порта
    connect(&thisPort, SIGNAL(readyRead()),this,SLOT(ReadInPort()));

}


void port :: Write_Settings_Port(QString name, int baudrate,int DataBits,int Parity,int StopBits, int FlowControl){//заносим параметры порта в структуру данных
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
               emit error_((SettingsPort.name.toLocal8Bit()+ " >> Открыт! \r"));
            }
        } else
        {
            thisPort.close();
            //emit error_(thisPort.errorString().toLocal8Bit());

        }
    }
    else
    {
        thisPort.close();
        //emit error_(thisPort.errorString().toLocal8Bit());
    }
}
void port::handleError(QSerialPort::SerialPortError error)//проверка ошибок при работе
{

    emit errorMessage(error,thisPort.portName());
    if ( (thisPort.isOpen()) && (error == QSerialPort::ResourceError))
    {
        //emit error_(thisPort.errorString().toLocal8Bit());
        DisconnectPort();
    }
    QString errorDiscription;
    switch (error){
    case 1://DeviceNotFoundError
          errorDiscription=SettingsPort.name+" Ошибка: попытка открыть несуществующее устройство";
    break;
    case 2://PermissionError
        errorDiscription=SettingsPort.name+" Ошибка: попытка открыть уже занятое устройство другим процессом или отсутствуют права для открытия";
    break;
    case 3://OpenError
        errorDiscription=SettingsPort.name+" Ошибка: попытка открыть уже занятое устройство";
    break;
    case 4://ParityError
        errorDiscription=SettingsPort.name+" Ошибка четности";
    break;
    case 5://FramingError
        errorDiscription=SettingsPort.name+" Framing ошибка";
    break;
    case 6://BreakConditionError
        errorDiscription=SettingsPort.name+" BreakConditionError";
    break;
    case 7://WriteError
        errorDiscription=SettingsPort.name+" Ошибка записи данных в порт";
    break;
    case 8://ReadError
        errorDiscription=SettingsPort.name+" Ошибка чтения данных из порта";
    break;
    case 9://ResourceError
        errorDiscription=SettingsPort.name+" Ошибка: устройство стало недоступно";
    break;
    case 10://UnsupportedOperationError
        errorDiscription=SettingsPort.name+" Ошибка: запрашиваемая операция не поддерживается";
    break;
    case 11://UnknownError
        errorDiscription=SettingsPort.name+" Неизвестная ошибка";
    break;
    case 12://TimeoutError
        errorDiscription=SettingsPort.name+" Ошибка: не получен ответ от устройства";
    break;
    case 13://TimeoutError
        errorDiscription=SettingsPort.name+" Ошибка: устройство не открыто";
    break;
    }
    emit error_(errorDiscription);
}

void port::DisconnectPort()//Отключаем порт
{
    if(thisPort.isOpen()){
       thisPort.close();
       emit error_(SettingsPort.name.toLocal8Bit() + " >> Закрыт!\r");
    }
}

void port :: WriteToPort(QByteArray data){//Запись данных в порт
    if(thisPort.isOpen()){
    thisPort.write(data,6);
    }
}

void port::WriteToPortTestRS(QByteArray data)
{
    if(thisPort.isOpen()){
    thisPort.write(data,8);
    }
}

void port :: ReadInPort(){//Чтение данных из порта
    QByteArray dataRead;
    dataRead.append(thisPort.readAll());
    QString comName = thisPort.portName();
    emit sendBSWVtm(dataRead,comName);

    //((QString)(adr.toInt())).toLatin1().toHex()
}

port::~port()
{
    thisPort.close();
}
