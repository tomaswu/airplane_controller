#include "tprocotol.h"
namespace procotol {
TProcotol::TProcotol() {

    sender["name"]="Admin";
    sender["id"]="001";
    sender["type"]="conller";

    recipient["id"]="001";
    recipient["type"]="uav";
    recipient["name"]="uav 001";

    obj["cmd"]=0x01;
    obj["data"]="";

}

QString TProcotol::dump()
{
    // obj["s"]=sender;
    // obj["r"]=recipient;
    // obj["type"]="cmd";
    // obj["stamp"]="0";

    doc.setObject(obj);
    return QString(doc.toJson(QJsonDocument::JsonFormat::Compact));
}

QString syscheck(){
    TProcotol p;
    p.obj["cmd"]=0x00;
    p.obj["data"]="syscheck";
    return p.dump();
}

QString getUavList()
{
    TProcotol p;
    p.obj["cmd"]=0x01;
    p.obj["data"]="";
    return p.dump();
}

QString changePosition(uchar lv, uchar lh, uchar rv, uchar rh)
{
    TProcotol p;
    p.obj["cmd"]=0x00;
    QJsonArray data={lv,lh,rv,rh};
    p.obj["data"] = data;
    return p.dump();
}

QString switchRatio(uchar channel,uchar open)
{
    TProcotol p;
    p.obj["cmd"]=0x00;
    QJsonArray data={channel,open};
    p.obj["data"] = data;
    return p.dump();
}




}//end namespace
