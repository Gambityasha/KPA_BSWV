#include "port.h"

port::port(QObject *parent) : QObject(parent)
{
    connect(&thisPort,SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError))); // подключаем проверку ошибок порта
    connect(&thisPort, SIGNAL(readyRead()),this,SLOT(ReadInPort()));
    connect(this, SIGNAL(dataForAnalize(QByteArray)),this,SLOT(DataAnalizer(QByteArray)));

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

    int allrequiredbytes_time;
    QString comName = thisPort.portName();
    otvetBuffer+=data;
    QTime currentTime = QTime::currentTime();
    if (otvetBuffer.size()==currentOtvetSize){
       // emit sendBSWVtm(otvetBuffer,comName,currentMessageNumber);
        emit sendBSWVtm(otvetBuffer,comName);
        switch (currentMessageNumber) {
            case 1:
                emit nextMessage(255);
                break;
            case 255:
                emit nextMessage(1);
                break;
            }
        otvetBuffer.clear();
        errorText="";
        currentMessageNumber=0;
        currentOtvetSize=0;
        paramsNull=false;
        return;
    }else{
        if ((otvetBuffer.size()<currentOtvetSize)&&(currentTime<gettingTime)){//ждем дальше данные
            paramsNull=false;
            return;
        }else{
            if ((otvetBuffer.size()<currentOtvetSize)&&(currentTime>gettingTime)&&(currentTime<gettingTime_die)){
                errorText += QString("не удалось за отведенное время (%1мс) принять необходимое количество байт: приняли %2 из %3").arg(protocol_waiting_time).arg(otvetBuffer.size()).arg(currentOtvetSize);
                paramsNull=true;
                return;
            }
            if ((otvetBuffer.size()>=currentOtvetSize)&&(currentTime>gettingTime)&&(currentTime<gettingTime_die)){
                allrequiredbytes_time=sendingTime.msecsTo(QTime::currentTime());
                errorText+=QString(", однако впоследствии за (%3мс) приняли %1 из %2").arg(otvetBuffer.size()).arg(currentOtvetSize).arg(allrequiredbytes_time);
                paramsNull=false;
                emit sendBSWVtm(otvetBuffer,comName);

            }
            emit errorExchange(comName,currentMessageNumber,errorText,paramsNull);
            switch (currentMessageNumber) {
                case 1:
                    emit nextMessage(255);
                    break;
                case 255:
                    emit nextMessage(1);
                    break;
                }
            otvetBuffer.clear();
            errorText="";
            currentMessageNumber=0;
            currentOtvetSize=0;
            paramsNull=false;
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
        sendingTime=QTime::currentTime();
        gettingTime=QTime::currentTime().addMSecs(protocol_waiting_time);
        gettingTime_die=QTime::currentTime().addMSecs(listening_time);
        thisPort.write(data,data.size());
        thisPort.flush();
    //thisPort.waitForBytesWritten(1);
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
    //emit sendBSWVtm(dataRead,comName);  //((QString)(adr.toInt())).toLatin1().toHex()
}

//void port::Exchange(int messageNumber, QByteArray data, int otvetSize, int chNumber)
void port::Exchange(int messageNumber, QByteArray data, int otvetSize)
{

//    bool paramsNull = false;
//    QString errorText;
//    QString comName = thisPort.portName();
//    int numofread = 0; //количество принятых байт
//    QByteArray responseData;
//    if (transactionInProgress) {
//        emit error_(thisPort.portName()+": пытаемся начать новую транзакцию, хотя предыдущая не завершилась");//emit tr_answer(ChannelName, responseData, error);
//        paramsNull=true;
//        return;
//        } else {
//            transactionInProgress = true;
//        }
//    bool protocol_waiting_timeout = false;
//    bool listening_timeout = false;
//    int allrequiredbytes_time; //время, которое потребовалось, чтобы получить все необходимые (или даже лишние) байты

//    if (thisPort.isOpen()) {
//        thisPort.write(data,data.size());
//        thisPort.flush();
//        if (thisPort.waitForBytesWritten(10)) { //отправляем запрос //10мс выбрано "наугад", при 1 иногда получали ошибку

//            QTime protocol_waiting_dieTime = QTime::currentTime().addMSecs(protocol_waiting_time); //рассчитываем время, по достижению которого мы понимаем, что нам не успели ответить по протоколу
//            QTime listening_dieTime = QTime::currentTime().addMSecs(listening_time); //рассчитываем время, по достижению которого мы понимаем, что нам не отвечают даже с учетом "запасного" времени
//            QTime start_transaction_time = QTime::currentTime(); //время начала всей процедуры транзакции (после того, как послали запрос)


//            do {//сначала ждем ответа по протоколу (оцениваем, ответили ли нам вовремя)
//                thisPort.waitForReadyRead(10); //ждем ответа
//                responseData += thisPort.readAll();
//                numofread = responseData.size();
//                if (QTime::currentTime() >= protocol_waiting_dieTime)
//                    protocol_waiting_timeout = true;
//                else
//                    protocol_waiting_timeout = false;
//            } while ((numofread < otvetSize) && (!protocol_waiting_timeout));//пока не приняли необходимое количество байт или пока ждали слишком долго

//            if (protocol_waiting_timeout) {//если в течение необходимого по протоколу времени не пришло достаточно байт    //error_(QString("не удалось за отведенное время (%1мс) принять необходимое количество байт: приняли %2 из %3").arg(protocol_waiting_time).arg(numofread).arg(otvetSize)); //начинаем формировать строку ошибки
//                errorText+=QString("не удалось за отведенное время (%1мс) принять необходимое количество байт: приняли %2 из %3").arg(protocol_waiting_time).arg(numofread).arg(otvetSize); //начинаем формировать строку ошибки
//                paramsNull=true;

//                do {//теперь продолжаем слушать канал, но уже до истечения времени listening_time, либо до принятия необходимого количества байт
//                   thisPort.waitForReadyRead(10); //ждем ответа
//                   responseData += thisPort.readAll();
//                   numofread = responseData.size();
//                   if (QTime::currentTime() >= listening_dieTime) {listening_timeout = true;}
//                    else  {listening_timeout = false;}
//                } while ((numofread < otvetSize) && (!listening_timeout));//пока не приняли необходимое количество байт либо пока не наступил таймаут listening_time

//                if (numofread >= otvetSize){ //если приняли данных больше либо равно, чем требовалось
//                    allrequiredbytes_time = start_transaction_time.msecsTo(QTime::currentTime()); //фиксируем, сколько прошло времени с момента начала транзакции
//                    errorText+=QString(", однако впоследствии (%3мс) приняли %1 из %2").arg(numofread).arg(otvetSize).arg(allrequiredbytes_time);
//                    paramsNull=false;                    //emit error_ (QString(" однако впоследствии (%3мс) приняли %1 из %2").arg(numofread).arg(otvetSize).arg(allrequiredbytes_time));
//                }
//            } else {

//                if (numofread > otvetSize){
//                    errorText+=QString(", почему-то приняли данных больше, чем должны были: %1 из %2").arg(numofread).arg(otvetSize);
//                    paramsNull=false;                    //emit error_(QString("почему-то приняли данных больше, чем должны были: %1 из %2").arg(numofread).arg(otvetSize));
//                }
//                }
//            } else {
//                errorText+="не удалось за отведенное время отправиить все байты";
//                paramsNull=true;                //emit error_("не удалось за отведенное время отправиить все байты");
//            }
//        } else {
//                errorText+="пытаемся совершать посылку в порт, который не удалось открыть";
//                paramsNull=true;            //emit error_("пытаемся совершать посылку в порт, который не удалось открыть");
//        }

//    if (errorText!="") {
//        //emit error_(errorText);
//        errorText+=", код запроса="+QString::number(messageNumber)+" ";
//        emit errorExchange(comName,messageNumber,errorText,paramsNull);
//    }
//    if (responseData!="") emit sendBSWVtm(responseData,comName);

//    switch (messageNumber) {
//    case 1:
//        emit nextMessage(255);
//        break;
//    case 255:
//            emit nextMessage(1);
//        break;
//    }
//    transactionInProgress = false;

}

port::~port()
{    
//   thisPort.close();
//   thisPort.deleteLater();
}
