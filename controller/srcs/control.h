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
    Q_INVOKABLE void switchRadio(int idx);

    Q_INVOKABLE void leftSteering(double v,double h);
    Q_INVOKABLE void rightSteering(double v,double h);

signals:

    void log(QString s);
    void uavConnected();
    void uavDisconnected();

private:
    TBluetooth *_bt;
    bool _isbusy{false};

};

#endif // CONTROL_H
