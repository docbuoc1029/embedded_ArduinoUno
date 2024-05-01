#include <SoftwareSerial.h>
SoftwareSerial mySerial(6, 7); //TX, RX

#include <DHT.h>
#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define M0 8
#define M1 9                 

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  
  pinMode(M0, OUTPUT);        
  pinMode(M1, OUTPUT);
  digitalWrite(M0, LOW);       // Set 2 chân M0 và M1 xuống LOW 
  digitalWrite(M1, LOW);       // để hoạt động ở chế độ Normal
  dht.begin();
}

void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  mySerial.println("Do Am: " +String(t));
  mySerial.println("Nhiet Do: "+String(h));   
  mySerial.println();
  delay(2000);
}
