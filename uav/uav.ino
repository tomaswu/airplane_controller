
void setup() {
  // start serial port at 9600 bps:
  Serial.begin(115200);
}


void loop() {
  // if we get a valid byte, read analog ins:
  String out = Serial.readStringUntil('\n');

  int l = out.length();
  if (l > 0) {
      String recv;
      recv += String(l) + ". recvs:" + out;
      Serial.print(recv);
  }
}
