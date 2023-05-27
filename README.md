# T-H-monitoring
Upload temperature and humidity to server via HTML GET method

%%%% Hardware Information %%%%
Sensor: ETH-01DV
ADC: Arduino Uno R3
Wifi module: ESP-WROOM-32
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%% Data Flow %%%%
Sensor --> Arduino --> Wifi module --> Server
Arduino is here just for ADC because linearity of arduino ADC is much better than that of ESP32 ADC.
If you use another ADC module, there is no need to use arduino
%%%%%%%%%%%%%%%%%%%

%%%% file description %%%%
TH_ArduinoUno.ino
  Convert analog sensor output to digital value
  Send it to the wifi module through I2C upon request
TH_ESP32.ino
  Request sensor value
  Convert the value to temperature or humidity
  Stringify data to HTML message
  Upload the message to the server
insertData.php
  Parse HTML message
  Insert the data to mySQL database
sqlconn.php
  mySQL user id and pw
%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%% To do %%%%
1. Upload TH_ArduinoUno.ino to your arduino
2. Upload TH_ESP32.ino to wifi module
3. Configure your mySQL database and table
4. Change insertData.php file accordingly
5. Upload insertData.php, sqlconn.php to your server
%%%%%%%%%%%%%%%

%%%% mySQL table used in this example %%%%
FIELD / TYPE
rid / int(11)
date / date
time / time
temperature / double(6,2)
humidity / double(5,2)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
