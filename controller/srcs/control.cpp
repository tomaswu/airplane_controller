#include "control.h"
#include <QTime>
#include <QDebug>

#define qdb qDebug()

control::control(QObject *parent) :
    QObject{parent}
{
    auto func = std::bind(&control::debug,this,std::placeholders::_1);
    _bt = new TBluetooth(nullptr,func);
    connect(_bt->socket,&QBluetoothSocket::connected,this,[=](){emit uavConnected();});
    connect(_bt->socket,&QBluetoothSocket::disconnected,this,[=](){emit uavDisconnected();_isbusy=false;});
}

control::~control()
{

}

void control::debug(QString s)
{
    auto ds = QTime::currentTime().toString("hh:mm:ss ");
    ds+=s;
    ds+="\n";
    emit log(ds);
}

void control::connectUav(QString method)
{
    if(_isbusy){
        _bt->socket->close();
    }
    _isbusy=true;
    debug(QString("connect by %1").arg(method));
    if(method=="蓝牙"){
        _bt->startScan();
    }
    else if(method=="wifi"){

    }
}

void control::switchRadio(int idx)
{

}

void control::leftSteering(double v, double h)
{
    if(_bt->socket->isOpen()){


    }
}

void control::rightSteering(double v, double h)
{
    qdb<<"right"<<v<<h;
}


