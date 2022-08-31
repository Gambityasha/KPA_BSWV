#include "port.h"

port::port(QObject *parent) : QObject(parent)
{
    connect(&thisPort,SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError))); // подключаем проверку ошибок порта
    connect(&thisPort, SIGNAL(readyRead()),this,SLOT(ReadInPort()));
    connect(this, SIGNAL(dataForAnalize(QByteArray)),this,SLOT(DataAnalizer(QByteArray)));



    QSettings setting("ports.ini", QSettings::IniFormat); //ports.ini файл должен быть в одной папке с exe
    setting.beginGroup("Admin");// [Admin] в ини файле

    timerDelay=setting.value("timerDelay","1000").toInt();
    setting.endGroup();

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
               emit error_((SettingsPort.name.toLocal8Bit()+ " >> Открыт! "));
            }
        } else
        {
            thisPort.close();
            //emit finished_Port();
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
        //emit error_(thisPort.portName()+" Ошибка: устройство стало недоступно");

        DisconnectPort();
    }
    QString errorDiscription;
    switch (error){
    case 0://DeviceNotFoundError
          errorDiscription=SettingsPort.name+" Ошибка: нет ошибки";
    break;
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
    if ((error!=0)&&(error!=12)){
    emit error_(errorDiscription);
    }
}

void port::DataAnalizer(QByteArray data)
{
    if (currentOtvetSize!=0){
        QString comName = thisPort.portName();
        otvetBuffer+=data;
        if (otvetBuffer.size()==currentOtvetSize){
            emit sendBSWVtm(otvetBuffer,comName);
            otvetBuffer.clear();
            currentOtvetSize=0;            
        }else{
            if (otvetBuffer.size()>currentOtvetSize){
            errorText=QString("Принято больше данных: %1 из %2").arg(otvetBuffer.size()).arg(currentOtvetSize);
            emit error_(comName+": "+errorText);
            emit sendBSWVtm(otvetBuffer,comName);
            currentOtvetSize=0;
            errorText="";
            }else{
                if (waitingTime> QTime::currentTime()){
                    return;
                }else{
                    if (otvetBuffer!=nullptr){
                        errorText=QString("Принято меньше данных: %1 из %2, за %3 мс").arg(otvetBuffer.size()).arg(currentOtvetSize).arg(timerDelay*0.95);
                        emit error_(comName+": "+errorText);
                        emit sendBSWVtm(otvetBuffer,comName);
                        errorText="";
                        otvetBuffer.clear();
                    }
                }
            }
        }
    }
}

void port::DisconnectPort()//Отключаем порт
{
    if(thisPort.isOpen()){
       thisPort.close();
       emit finished_Port();
       emit error_(SettingsPort.name.toLocal8Bit() + " >> Закрыт!\r");
    }
}

void port :: WriteToPort(QByteArray data){//Запись данных в порт
    if(thisPort.isOpen()){        
    thisPort.write(data,data.size());
    thisPort.flush();
    //thisPort.waitForBytesWritten(1);
    }
}

void port :: WriteToPort(int messageNumber,QByteArray data, int otvetSize){//Запись данных в порт
    if(thisPort.isOpen()){

        currentOtvetSize=otvetSize;
        currentMessageNumber=messageNumber;
        waitingTime = QTime::currentTime().addMSecs(timerDelay*0.95);
        thisPort.write(data,data.size());
        thisPort.flush();
    //thisPort.waitForBytesWritten(10);
    }
}
void port::WriteToPortTestRS(QByteArray data)
{
    if(thisPort.isOpen()){
    thisPort.write(data,data.size());
    thisPort.flush();
    }
}

void port :: ReadInPort(){//Чтение данных из порта
    QByteArray dataRead;
    dataRead.append(thisPort.readAll());
    QString comName = thisPort.portName();
     emit dataForAnalize(dataRead);
}



port::~port()
{    
//   thisPort.close();
//   thisPort.deleteLater();
}
