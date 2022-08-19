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
               emit error_((SettingsPort.name.toLocal8Bit()+ " >> Открыт! "));
            }
        } else
        {
            thisPort.close();
            emit finished_Port();
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

void port::DisconnectPort()//Отключаем порт.
{
    if(thisPort.isOpen()){
       thisPort.close();
       emit finished_Port();
       emit error_(SettingsPort.name.toLocal8Bit() + " >> Закрыт!\r");
    }
}

void port :: WriteToPort(QByteArray data){//Запись данных в порт
    if(thisPort.isOpen()){
    thisPort.write(data,6);
    thisPort.flush();
    //thisPort.waitForBytesWritten(1);
    }
}

void port::WriteToPortTestRS(QByteArray data)
{
    if(thisPort.isOpen()){
    thisPort.write(data,8);
    thisPort.flush();
    //thisPort.waitForBytesWritten(1);
    }
}

void port :: ReadInPort(){//Чтение данных из порта
    QByteArray dataRead;
    dataRead.append(thisPort.readAll());
    QString comName = thisPort.portName();
    //QThread::sleep(2);
    emit sendBSWVtm(dataRead,comName);

    //((QString)(adr.toInt())).toLatin1().toHex()
}

void port::Exchange(QByteArray data, int otvetSize, int numberRequest)
{
    if (transactionInProgress){
        emit error_("Попытка начать новую передачу данных, пока не закончилась предыдущая");
        return;
    }else{
        transactionInProgress = true;
    }
    QByteArray responseData;
    responseData.clear();
    int sizeRead = 0;
    bool protocol_waiting_timeout = false;
    bool listening_timeout = false;
    int allrequiredbytes_time; //время, которое потребовалось, чтобы получить все необходимые (или даже лишние) байты
    if(thisPort.isOpen()){
    thisPort.write(data,otvetSize);
    thisPort.flush();
    if (thisPort.waitForBytesWritten(10)){
        QTime protocol_waiting_dieTime = QTime::currentTime().addMSecs(protocol_waiting_time); //рассчитываем время, по достижению которого мы понимаем, что нам не успели ответить по протоколу
        QTime listening_dieTime = QTime::currentTime().addMSecs(listening_time); //рассчитываем время, по достижению которого мы понимаем, что нам не отвечают даже с учетом "запасного" времени
        QTime start_transaction_time = QTime::currentTime();
        do {
            thisPort.waitForReadyRead(1);
            responseData += thisPort.readAll();
            sizeRead=responseData.size();
            if (QTime::currentTime() >= protocol_waiting_dieTime){
                protocol_waiting_timeout = true;
            }else{
                protocol_waiting_timeout = false;
            }
        }while ((sizeRead < otvetSize) && (!protocol_waiting_timeout));//пока не приняли необходимое количество байт или пока ждали слишком долго
        if (protocol_waiting_timeout){ //если в течение необходимого по протоколу времени не пришло достаточно байт
            emit error_(QString("не удалось за отведенное время (%1мс) принять необходимое количество байт: приняли %2 из %3").arg(protocol_waiting_time).arg(sizeRead).arg(otvetSize));
            do {
                thisPort.waitForReadyRead(1);
                responseData += thisPort.readAll();
                sizeRead=responseData.size();
                if (QTime::currentTime() >= listening_dieTime){
                    listening_timeout = true;
                } else {
                    listening_timeout = false;
                    }
            } while ((sizeRead < otvetSize) && (!listening_timeout));//пока не приняли необходимое количество байт либо пока не наступил таймаут listening_time
              if (sizeRead >= otvetSize){ //если приняли данных больше либо равно, чем требовалось
                  allrequiredbytes_time = start_transaction_time.msecsTo(QTime::currentTime()); //фиксируем, сколько прошло времени с момента начала транзакции
                  emit error_(QString(" однако за (%3мс) приняли %1 из %2").arg(sizeRead).arg(otvetSize).arg(allrequiredbytes_time));
              }
        }else {
             if (sizeRead > otvetSize){
                 emit error_(QString("приняли данных больше, чем должны были: %1 из %2").arg(sizeRead).arg(otvetSize));
             }
        }
        }else {
             emit error_("не удалось за отведенное время отправиить все байты");
        }
    } else {
          emit error_ ("пытаемся совершать посылку в порт, который не удалось открыть");
    }
      emit sendBSWVtm(responseData,thisPort.portName());
      transactionInProgress = false;
      switch (numberRequest){
          case 1:
              emit nextRequest(255,thisPort.portName());
          break;
          case 255:
          emit nextRequest(1,thisPort.portName());
          break;
      }
}

port::~port()
{
    thisPort.close();    
}
