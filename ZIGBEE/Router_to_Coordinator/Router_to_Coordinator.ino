#include<SoftwareSerial.h>
#include<DHT.h>

#define DHTPIN 8
#define DHTTYPE 11

DHT dht(DHTPIN, DHTTYPE);

int group = 1;
SoftwareSerial mySerial(6, 7); //Tx, Rx 

void setup() {
// put your setup code here, to run once: 
  Serial.begin(38400); 
  mySerial.begin(38400);
  dht.begin();
}

void loop() {
  float temp = dht.readTemperature(); 
  float hum = dht.readHumidity();
  // doc[""]
  mySerial.println("Group: " + String(group)); 
  mySerial.println("Nhiet do: " + String(temp)); 
  mySerial.println("Do am: " + String(hum)); 
  delay(5000);
}
