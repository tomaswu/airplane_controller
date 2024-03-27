#include "tbluetooth.h"
#include "qdebug.h"
#include <QBluetoothSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QBluetoothPermission>
#include <QApplication>
#define qdb qDebug()

TBluetooth::TBluetooth(QObject *parent,std::function<void(QString)> debug)
    : QObject{parent}
{

    this->debug=debug;
    connect(&discover ,&QBluetoothDeviceDiscoveryAgent::deviceDiscovered,this,&TBluetooth::findDevice);
//    connect(&discover ,&QBluetoothDeviceDiscoveryAgent::finished,this,&TBluetooth::connectDevice);
//    connect(&local,&QBluetoothLocalDevice::pairingFinished,this,&TBluetooth::test);
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    connect(socket,&QBluetoothSocket::readyRead,this,&TBluetooth::read);
    connect(socket,&QBluetoothSocket::errorOccurred,this, &TBluetooth::error);

    // this->startScan();
    debug("start...");
    QBluetoothPermission permission{};
    qApp->requestPermission(permission,[](){});

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
    debug("find device:" + p.name());
    deviceList.append(p);
   if(p.name()=="HC-05"){
        debug("find uav discover stop!");
        discover.stop();
        emit discover.finished();
        this->connectDevice();
   }
    emit discovered(info.name());
}

void TBluetooth::connectDevice(){
    QString name = "HC-05";
    debug(QString("connect to %1").arg(name));
    for(auto &i:deviceList){
        if(i.name()==name){
            addr=i.address();
            auto uuid = QBluetoothUuid::ServiceClassUuid::SerialPort;
            socket->connectToService(addr,uuid,QIODevice::ReadWrite);
            debug("connecting...");
        }
    }

}

// void TBluetooth::test(){
//     qdb<<"hello";
//     for(auto &i:local.connectedDevices()){
//         qdb<<i;
//     }
//     auto json = QJsonObject();
//     json["cmd"] = "cmd test";
//     auto doc  = QJsonDocument(json);
//     auto str = doc.toJson(QJsonDocument::Compact);
//     qdb<<str;
//     socket->write(str);

// }

void TBluetooth::read(){
    QByteArray all = socket->readAll();
    qdb<<"get recv::"<<QString::fromUtf8(all);
    qdb<<all[*all.end()];
    if(all[*all.end()]=='\n'){
        all.remove(all.length()-1,1);
        qdb<<all;
    }
}

void TBluetooth::error(QBluetoothSocket::SocketError error){
    qdb<<"error"<<error;
}


// void TBluetooth::raise()
// {
//     auto json = QJsonObject();
//     json["cmd"] = "raise";
//     auto doc  = QJsonDocument(json);
//     auto str = doc.toJson(QJsonDocument::Compact);
//     str.append('\n');
//     qdb<<str;
//     socket->write(str);
// }















