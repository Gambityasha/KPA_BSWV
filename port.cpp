#include "port.h"

port::port(QObject *parent) : QObject(parent)
{
    connect(&thisPort,SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError))); // подключаем проверку ошибок порта
    //connect(&thisPort, SIGNAL(readyRead()),this,SLOT(ReadInPort()));
    thisPort.clear();

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

void port::Exchange(int messageNumber, QByteArray data, int otvetSize, int chNumber)
{
    int nextMessageChName;
    QString comName = thisPort.portName();
    int numofread = 0; //количество принятых байт
    QByteArray responseData;
    if (transactionInProgress) {
        emit error_(thisPort.portName()+": пытаемся начать новую транзакцию, хотя предыдущая не завершилась");//emit tr_answer(ChannelName, responseData, error);

        return;
        } else {
            transactionInProgress = true;
        }
    bool protocol_waiting_timeout = false;
    bool listening_timeout = false;
    int allrequiredbytes_time; //время, которое потребовалось, чтобы получить все необходимые (или даже лишние) байты

    if (thisPort.isOpen()) {
        thisPort.write(data,data.size());
        thisPort.flush();
        if (thisPort.waitForBytesWritten(30)) { //отправляем запрос //10мс выбрано "наугад", при 1 иногда получали ошибку

            QTime protocol_waiting_dieTime = QTime::currentTime().addMSecs(protocol_waiting_time); //рассчитываем время, по достижению которого мы понимаем, что нам не успели ответить по протоколу
            QTime listening_dieTime = QTime::currentTime().addMSecs(listening_time); //рассчитываем время, по достижению которого мы понимаем, что нам не отвечают даже с учетом "запасного" времени
            QTime start_transaction_time = QTime::currentTime(); //время начала всей процедуры транзакции (после того, как послали запрос)


            do {//сначала ждем ответа по протоколу (оцениваем, ответили ли нам вовремя)
                thisPort.waitForReadyRead(60); //ждем ответа
                responseData += thisPort.readAll();
                numofread = responseData.size();
                if (QTime::currentTime() >= protocol_waiting_dieTime)
                    protocol_waiting_timeout = true;
                else
                    protocol_waiting_timeout = false;
            } while ((numofread < otvetSize) && (!protocol_waiting_timeout));//пока не приняли необходимое количество байт или пока ждали слишком долго

            if (protocol_waiting_timeout) {//если в течение необходимого по протоколу времени не пришло достаточно байт
                error_(QString("не удалось за отведенное время (%1мс) принять необходимое количество байт: приняли %2 из %3").arg(protocol_waiting_time).arg(numofread).arg(otvetSize)); //начинаем формировать строку ошибки

                do {//теперь продолжаем слушать канал, но уже до истечения времени listening_time, либо до принятия необходимого количества байт
                   thisPort.waitForReadyRead(60); //ждем ответа
                   responseData += thisPort.readAll();
                   numofread = responseData.size();
                   if (QTime::currentTime() >= listening_dieTime) listening_timeout = true;
                    else  listening_timeout = false;
                } while ((numofread < otvetSize) && (!listening_timeout));//пока не приняли необходимое количество байт либо пока не наступил таймаут listening_time

                if (numofread >= otvetSize){ //если приняли данных больше либо равно, чем требовалось
                    allrequiredbytes_time = start_transaction_time.msecsTo(QTime::currentTime()); //фиксируем, сколько прошло времени с момента начала транзакции
                    emit error_ (QString(" однако впоследствии (%3мс) приняли %1 из %2").arg(numofread).arg(otvetSize).arg(allrequiredbytes_time));
                }
            } else {
                if (numofread > otvetSize)
                    emit error_(QString("почему-то приняли данных больше, чем должны были: %1 из %2").arg(numofread).arg(otvetSize));
                }
            } else {
                emit error_("не удалось за отведенное время отправиить все байты");
            }
        } else {
            emit error_("пытаемся совершать посылку в порт, который не удалось открыть");
        }

    switch (chNumber){
    case 1:
        nextMessageChName=1;
        break;
    case 2:
        nextMessageChName=1;
        break;
    case 3:
        nextMessageChName=1;
        break;
    case 4:
        nextMessageChName=1;
        break;
    case 5:
        nextMessageChName=1;
        break;
    case 6:
        nextMessageChName=1;
        break;
    }
    if (responseData!="") emit sendBSWVtm(responseData,comName);
    transactionInProgress = false;
    switch (messageNumber) {
    case 1:
        if (nextMessageChName==1){
            emit nextMessage(255,nextMessageChName);
        }else{
            emit nextMessage(1,nextMessageChName);
        }
        break;
    case 255:
        if (nextMessageChName==1){
            emit nextMessage(1,nextMessageChName);
        }else{
            emit nextMessage(255,nextMessageChName);
        }
        break;
    }
}

port::~port()
{    
    thisPort.close();
    thisPort.deleteLater();
}
