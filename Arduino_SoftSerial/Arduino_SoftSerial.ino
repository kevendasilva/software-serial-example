#include <SoftwareSerial.h>

#define rxPin 10
#define txPin 11

SoftwareSerial Arduino_SoftSerial(rxPin, txPin);

void setup() {
  // LDR - Sensor de teste
  pinMode(A0, INPUT);

  Serial.begin(9600);

  Arduino_SoftSerial.begin(14400);
}

void loop() {
  Arduino_SoftSerial.listen();
  String data = getDataSerial();

  Serial.println(data);

  int indexOfDelimiter = data.indexOf(":");

  String action = data.substring(0, indexOfDelimiter);
  uint8_t pin = data.substring(indexOfDelimiter + 1).toInt();

  data = "A0=" + String(analogRead(pin));
  postDataSerial(data);

  delay(100);
}


String getDataSerial() {
  String data;

  if (Arduino_SoftSerial.available() > 0)
    data = Arduino_SoftSerial.readStringUntil('\r');

  return data;
}

void postDataSerial(String data) {
  data = data + "\r";

  Arduino_SoftSerial.print(data);
}
