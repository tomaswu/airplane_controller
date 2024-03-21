
#pragma once
#ifndef TPROCOTOL
#define TPROCOTOL

#include <ArduinoJson.h>

class Tprocotol{
    public:
    Tprocotol();
    ~Tprocotol();

    String buff;

    void read();
    void decodeCmd();
    void dealwithCmd();
    void replyCmd();


};

#endif