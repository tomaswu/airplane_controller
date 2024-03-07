#include "socketcommu.h"

SocketCommu::SocketCommu(QObject *parent,QQmlApplicationEngine *e)
    : QObject{parent}
{
    this->engine = e;
    p_sock = new QTcpSocket;
    initconnections();
}

void SocketCommu::initconnections()
{
    connect(p_sock,&QTcpSocket::readyRead,this,&SocketCommu::read);
    connect(p_sock,&QTcpSocket::connected,this,[=](){emit this->uavconnected();});
    connect(p_sock,&QTcpSocket::disconnected,this,[=](){emit this->uavdisconnected();});
    connect(p_sock,&QTcpSocket::errorOccurred,this,&SocketCommu::dealUAVerror);

    if(engine){
        auto root = engine->rootObjects();
        auto qmlitem = root.first()->findChild<QObject*>("dc");
        connect(qmlitem,SIGNAL(controlDelta(double,double)),this,SLOT(dcChanged(double,double)));
    }
}

void SocketCommu::read()
{
    auto data = p_sock->readAll();

    QByteArray a(10,0);
    a[0]=0xff;
    p_sock->write(a);
    qdb<<QString(data);
}

void SocketCommu::connect2UAV()
{
    p_sock->connectToHost(HOST,PORT);
}

void SocketCommu::dcChanged(double x, double y)
{
    qdb<<x<<y;
}

void SocketCommu::dealUAVerror(QAbstractSocket::SocketError err)
{
    p_sock->disconnect();

}


