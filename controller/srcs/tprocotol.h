#ifndef TPROCOTOL_H
#define TPROCOTOL_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

namespace procotol {


class TProcotol
{
public:
    TProcotol();

    QJsonDocument doc;
    QJsonObject obj;

    QJsonObject sender;
    QJsonObject recipient;

    QString dump();

};

QString syscheck();

QString getUavList();

QString changePosition(uchar lv,uchar lh,uchar rv,uchar rh);

QString switchRatio(uchar channel,uchar open);

}// end namespace


#endif // TPROCOTOL_H
