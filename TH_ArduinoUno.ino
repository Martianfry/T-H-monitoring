#include <Wire.h>

const int HPin = A0; //humidity pin number
const int TPin = A1; //temperature pin number
const int ARDADD = 0x13; // Arduino I2C Address

void setup() {
  Serial.begin(115200);
  Wire.begin(ARDADD); // join I2C as a slave
  Wire.onRequest(readTH);
}

void loop() {
  delay(5000);
}

void readTH(){
  int sValH = analogRead(HPin); // humidity sensor value
  int sValT = analogRead(TPin); // temperature sensor value
  byte sValHb[2]; // int is 16-bit (2-byte) in arduino, I2C write or read 1 byte at a time
  byte sValTb[2];
  sValHb[0] = sValH >> 8;
  sValHb[1] = sValH;
  sValTb[0] = sValT >> 8;
  sValTb[1] = sValT;

  // not necessary, to check variable values
  Serial.println("Request Received");
  Serial.print("sValTb: ");
  Serial.print(sValTb[0]);
  Serial.print(", ");
  Serial.println(sValTb[1]);
  Serial.print("sValHb: ");
  Serial.print(sValHb[0]);
  Serial.print(", ");
  Serial.println(sValHb[1]);

  // send I2C response
  Wire.write("T"); // 1 byte
  Wire.write(sValTb[0]); // 1 byte
  Wire.write(sValTb[1]); // 1 byte
  Wire.write("H"); // 1 byte
  Wire.write(sValHb[0]); // 1 byte
  Wire.write(sValHb[1]); // 1 byte
}