#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include "tbluetooth.h"

class control:public QObject
{
    Q_OBJECT
public:
    control(QObject *parent=nullptr);
    ~control();

    void debug(QString s);

    Q_INVOKABLE void connectUav(QString method);
    Q_INVOKABLE void switchRadio(uchar idx,bool open);
    Q_INVOKABLE void steering(double lv,double lh,double rv,double rh);

signals:

    void log(QString s);
    void uavConnected();
    void uavDisconnected();

private:
    TBluetooth *_bt;
    bool _isbusy{false};
    int _method{0};

};

#endif // CONTROL_H
