#include "commu.h"
// global var

unsigned char pwm[6] = {3,5,6,9,10,11};
unsigned int pwmvalue[6] = {0,0,0,0,0,0};

void setup() {
  // start serial port at 9600 bps:
  Serial.begin(115200);
}

int out = 0;

void loop() {
    // String out = Serial.readStringUntil('\n');
    // int l = out.length();
    // if (l > 0) {

    //     String tmp="recv::";
    //     tmp+=out;
    //     tmp+='\n';
    //     Serial.print(tmp);
    // }

    out+=1;
    if(out>255) out=0;
    digitalWrite(4,out%2);
    delay(2000);

}
