#ifndef TBLUETOOTH_H
#define TBLUETOOTH_H

#include <QObject>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceInfo>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothSocket>
#include <QBluetoothServer>


static const QLatin1String serviceUuid("00001101-0000-1000-8000-00805f9b34fb");

class TBluetooth: public QObject
{
    Q_OBJECT

public:
    TBluetooth(QObject *parent = nullptr);
    ~TBluetooth();

    //member
    QBluetoothLocalDevice local;
    QBluetoothDeviceDiscoveryAgent discover;
    QList<QBluetoothDeviceInfo> deviceList;
    QBluetoothSocket *socket;
    QBluetoothAddress addr;

    //method
    Q_INVOKABLE void startScan();
    Q_INVOKABLE void connectDevice();
    void test();
    void read();
    void error(QBluetoothSocket::SocketError error);

signals:
    void discovered(QString s);
    void scanStarted();
    void scanFinished();

private:
    void findDevice(const QBluetoothDeviceInfo &info);


};

#endif // TBLUETOOTH_H
