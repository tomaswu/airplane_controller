#include "buffer.h"

// {3,5,6,9,10,11}; uno
uchar PWM[6] = {3,5,6,9,10,11};//{ 2, 3, 4, 5, 6, 7 };
uchar PWMVALUE[6] = { 0, 128, 0, 128, 128, 128 };
CycleBuff buff(1024);


void decodeCmd(int begin, int end) {
  bool flag = buff[begin + 2] == 0x00;
  if (flag) {
    Serial.print("set ");
    for (uchar i = 0; i < 4; i++) {
      analogWrite(PWM[i], buff[i + 3 + begin]);
      PWMVALUE[i] = buff[i + 3 + begin];
      Serial.print(i);
      Serial.print(": ");
      Serial.print(PWMVALUE[i]);
      Serial.print(" # ");
    }
    Serial.println();
    // analogWrite(3, 255);
  }
}


void setup() {
  // start serial port at 9600 bps:
  Serial.begin(115200);
  // Serial1.begin(115200);
  for (uchar i = 0; i < 6; i++) {
    analogWrite(PWM[i], PWMVALUE[i]);
  }
}

void loop() {
  // analogWrite(PWM[0],255);
  int sn = Serial.available();
  if (sn > 0) {
    uchar* recvbuf = new uchar[sn];
    Serial.readBytes(recvbuf, sn);
    buff.push_back(recvbuf, sn);
    delete[] recvbuf;
    int begin = 0;
    int end = 0;
    if (buff.length() > 0) {
      for (int i = 0; i < buff.length() - 9; i++) {
        if (buff[i] == 0xaa && buff[i + 1] == 0xbb && buff[i + 7] == 0xbb && buff[i + 8] == 0xaa) {
          begin = i;
          end = i + 9;
          decodeCmd(begin, end);
          // Serial.println("decode");
        }
      }
      buff.moveEntry(end);
    }
  }
}
