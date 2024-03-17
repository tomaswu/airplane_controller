#include "tbluetooth.h"
#include "qdebug.h"
#include <QBluetoothSocket>

#define qdb qDebug()

TBluetooth::TBluetooth(QObject *parent)
    : QObject{parent}
{
    connect(&discover ,&QBluetoothDeviceDiscoveryAgent::deviceDiscovered,this,&TBluetooth::findDevice);
//    connect(&discover ,&QBluetoothDeviceDiscoveryAgent::finished,this,&TBluetooth::connectDevice);
//    connect(&local,&QBluetoothLocalDevice::pairingFinished,this,&TBluetooth::test);
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    connect(socket,&QBluetoothSocket::connected,this,&TBluetooth::test);
    connect(socket,&QBluetoothSocket::disconnected,this,&TBluetooth::test);
    connect(socket,&QBluetoothSocket::readyRead,this,&TBluetooth::read);
    connect(socket,&QBluetoothSocket::errorOccurred,this, &TBluetooth::error);


    this->startScan();

}

TBluetooth::~TBluetooth(){

}


void TBluetooth::startScan(){
    qdb<<"start scan...";
    deviceList.clear();
    emit scanStarted();
    discover.start(QBluetoothDeviceDiscoveryAgent::DiscoveryMethod::ClassicMethod);
}


void TBluetooth::findDevice(const QBluetoothDeviceInfo &info){
    QBluetoothDeviceInfo p;
    p=info;
    qdb<<p.name();
    deviceList.append(p);
   if(p.name()=="HC-05"){
       discover.stop();
       emit discover.finished();
       this->connectDevice();
   }
    emit discovered(info.name());
}

void TBluetooth::connectDevice(){
    qdb<<"connecting...";
    for(auto &i:deviceList){
        if(i.name()=="HC-05"){
            addr=i.address();
            auto uuid = QBluetoothUuid::ServiceClassUuid::SerialPort;
            qdb<<uuid;
            socket->connectToService(addr,uuid,QIODevice::ReadWrite);
            qdb<<"connecting...";
        }
    }

}

void TBluetooth::test(){
    qdb<<"hello";
    for(auto &i:local.connectedDevices()){
        qdb<<i;
    }
    socket->write("hello world");

}

void TBluetooth::read(){
    QByteArray all = socket->readAll();
    qdb<<all;
}

void TBluetooth::error(QBluetoothSocket::SocketError error){
    qdb<<"error"<<error;
}















