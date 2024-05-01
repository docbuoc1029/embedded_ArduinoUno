#include <DHT.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#define MQ_Data A1     // Data Gas
#define DHT_Data 8    // Data DHT

DHT dht(DHT_Data, DHT22);  // DHT11

#define RX_PIN 10
#define TX_PIN 11

SoftwareSerial mySerial(RX_PIN, TX_PIN);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  while (!Serial) delay(1);

  dht.begin();
}

unsigned long timeUpdata = millis();

DynamicJsonDocument doc(1024);
DynamicJsonDocument docBtn(1024);

void loop() {
  if (millis() - timeUpdata > 2000) {
    float hum = dht.readHumidity();
    float temp = dht.readTemperature();
    float gas = analogRead(MQ_Data);

    doc["temperature"] = temp;
    doc["humidity"] = hum;
    doc["gas"] = gas;

    // gửi data thông qua cổng giao tiếp mềm cho Chip WiFi
    serializeJson(doc, mySerial);
    mySerial.println();

    // In ra màn hình Serial
    serializeJson(doc, Serial);
    Serial.println();

    timeUpdata = millis();
  }
}
