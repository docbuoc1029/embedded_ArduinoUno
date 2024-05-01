#include<SoftwareSerial.h> 
#include<ArduinoJson.h>

StaticJsonDocument<100> doc;

SoftwareSerial mySerial(10, 11); //Rx, Tx

void setup() {
// put your setup code here, to run once: 
  Serial.begin(38400); 
  mySerial.begin(38400);
  pinMode(8, OUTPUT);
}

void loop() { 
  if(mySerial.available()) {
    String data = mySerial.readStringUntil('\n'); 
    data.remove(data.length()-1);
    if(data == "on") {
      digitalWrite(8, HIGH); 
      Serial.println("Led on");
    }
    if(data == "off") {
      digitalWrite(8, LOW); 
      Serial.println("Led off");
    }
  }
}
