#include <SoftwareSerial.h>

#define rxPin D4
#define txPin D3

SoftwareSerial NodeMcu_SoftSerial(rxPin, txPin);

void setup() {
  Serial.begin(115200);

  NodeMcu_SoftSerial.begin(14400);
}

void loop() {
  postDataSerial("value:A0");

  NodeMcu_SoftSerial.listen();
  String value = getDataSerial();

  Serial.print("Value read by LDR is: ");
  Serial.println(value);

  delay(100);
}

String getDataSerial() {
  String data;

  if (NodeMcu_SoftSerial.available() > 0)
    data = NodeMcu_SoftSerial.readStringUntil('\r');

  return data;
}

void postDataSerial(String data) {
  data = data + "\r";

  NodeMcu_SoftSerial.print(data);
}
