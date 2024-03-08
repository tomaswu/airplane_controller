#ifndef SOCKETCOMMU_H
#define SOCKETCOMMU_H

#include <QObject>
#include <QTcpSocket>
#include <QQmlApplicationEngine>
#include <QDebug>

#define qdb qDebug()

class SocketCommu : public QObject
{
    Q_OBJECT
public:
    explicit SocketCommu(QObject *parent = nullptr,QQmlApplicationEngine *engine=nullptr);
    QTcpSocket* p_sock;
    QString HOST{"127.0.0.1"};
    quint16 PORT{61762};
    void initconnections();
    void read();
    QQmlApplicationEngine *engine{nullptr};
    bool debug{true};
    void connect2UAV();
    void dcChanged(double x,double y);
    void dealUAVerror(QTcpSocket::SocketError err);

signals:
    void infoDebug(QString s);
    void uavconnected();
    void uaverror();
    void uavdisconnected();
};

#endif // SOCKETCOMMU_H
