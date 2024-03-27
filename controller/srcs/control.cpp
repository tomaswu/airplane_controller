#include "control.h"
#include <QTime>
#include <QDebug>
#include "tprocotol.h"

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
        _method=0;
    }
    else if(method=="wifi"){
        _method=1;
    }

}

void control::switchRadio(uchar idx,bool open)
{
    auto s = procotol::switchRatio(idx,open? 1:0);
    qdb<<s;
}

void control::steering(double lv, double lh, double rv, double rh)
{
    auto s = procotol::changePosition(lv,lh,rv,rh)+"\n";
    if(_method==0){
        if(_bt->socket->isOpen()){
            debug(s);
            _bt->socket->write(s.toLatin1());
        }

    }
    else if(_method==1){

    }
}






