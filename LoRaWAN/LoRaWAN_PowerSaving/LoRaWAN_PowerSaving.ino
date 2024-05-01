#include <SoftwareSerial.h>

SoftwareSerial mySerial(6, 7); //TX, RX

#define M0 8
#define M1 9                 

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  
  pinMode(M0, OUTPUT);        
  pinMode(M1, OUTPUT);
  digitalWrite(M0, HIGH);       // Set 2 chân M1 LOW và M0 xuống HIGH
  digitalWrite(M1, LOW);       // để hoạt động ở chế độ Power-Savin
  
}

void loop() {
  if(Serial.available() > 0){
    String input = Serial.readStringUntil('\n');
    Serial.println(input);    
  }
  if(mySerial.available() > 0){
    String input = mySerial.readStringUntil('\n');
    Serial.println(input);    
  }
  delay(20);
}
