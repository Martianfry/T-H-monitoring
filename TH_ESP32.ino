#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <Wire.h>

WiFiMulti wiFiMulti;
const int ARDADD = 0x13; // Arduino address
const int ARDLEN = 6; // Data length (6 bytes)

void setup() {
  Serial.begin(115200);
  Wire.begin(); // Join I2C as master
  
  Serial.println("Flushing...");
  Serial.flush();

  //launch WIFI
  WiFi.mode(WIFI_STA);
  wiFiMulti.addAP("YourWifiName1", "YourWifiPW1");
  wiFiMulti.addAP("YourWifiName2", "YourWifiPW2");

  delay(1000);
}

void loop() {
  if ((wiFiMulti.run() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;
    char* serverName = "Server address"; // ex) http://111.111.111.111/helloworld.php
    int devkey = 100; // variable to distinguish between multiple sensor inputs
    char datastr[100]; // data containing part of message
    char msg[200]; // entire message, make sure this is long enough for you
    int httpCode = -1;
    
    //Read H&T
    byte sValTb[2];
    byte sValHb[2];
    Wire.requestFrom(ARDADD,ARDLEN); // request data from arduino
    while(Wire.available()){
      switch(Wire.available()){
        case 5:
          sValTb[0] = Wire.read();
          break;
        case 4:
          sValTb[1] = Wire.read();
          break;
        case 2:
          sValHb[0] = Wire.read();
          break;
        case 1:
          sValHb[1] = Wire.read();
          break;
        default:
          Wire.read();
          break;
      }
    }
    
    int sValT = sValTb[0]*256 + sValTb[1];
    int sValH = sValHb[0]*256 + sValHb[1];
    float aTemp = -66.875 + 218.75*(float)sValT/1023; // formula from ETH-01DV sensor manual 
    float aHum = -12.5 + 125*(float)sValH/1023;
    
    sprintf(datastr,"%.2f C, %.2f %%\n",aTemp,aHum);
    Serial.printf("Converted to... ");
    Serial.println(datastr);
    
    sprintf(msg,"%s?devkey=%d&temperature=%.2f&humidity=%.2f",serverName,devkey,aTemp,aHum); // message to send via HTTP
    Serial.printf("message:");
    Serial.println(msg);
    Serial.flush();
    
    if(http.begin(msg)){ // send message and receive server response
      httpCode = http.GET();
      Serial.printf("Server response:");
      Serial.println(httpCode);
    }else{
      Serial.println("HTTP failed");
    }

  }else{
    Serial.println("WiFi failed");
  }
  Serial.println("Waiting 60 seconds before next round...");
  delay(60000); // upload once in a minute
}