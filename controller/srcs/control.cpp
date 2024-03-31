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
    qdb<<"test::"<<norm(lv)<<norm(lh)<<norm(rv)<<norm(rh);
    if(_method==0){
        if(_bt->socket->isOpen()){
            QByteArray msg;
            msg.resize(9);
            msg[0]=0xaa;
            msg[1]=0xbb;
            msg[2]=0x00;
            msg[3]=norm(lv);
            msg[4]=norm(lh);
            msg[5]=norm(rv);
            msg[6]=norm(rh);
            msg[7]=0xbb;
            msg[8]=0xaa;
            qdb<<msg.size();
            _bt->socket->write(msg);
            _bt->socket->write(msg);
            _bt->socket->waitForBytesWritten(500);
        }

    }
    else if(_method==1){

    }
}

uchar control::norm(double v, double threshold)
{
    double m = v/threshold*128+128;
    if(m<0)m=0;
    if(m>250)m=250;
    uchar n = static_cast<uchar>(m);
    return n;
}








