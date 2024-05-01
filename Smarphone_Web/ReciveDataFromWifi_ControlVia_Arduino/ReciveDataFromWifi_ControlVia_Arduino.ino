#include <DHT.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#define LED 7        // Data LED
#define Buzzer 8    // Data Buzzer
#define Fan 9      // Data Fan

DHT dht(DHT_Data, DHT22);  // DHT11

#define RX_PIN 10
#define TX_PIN 11
SoftwareSerial mySerial(RX_PIN, TX_PIN);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  while (!Serial) delay(1);

  pinMode(LED, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(Fan, OUTPUT);

  dht.begin();
}

unsigned long timeUpdata = millis();

DynamicJsonDocument doc(1024);
DynamicJsonDocument docBtn(1024);

void loop() {
  if (millis() - timeUpdata > 2000) {
    doc["led"] = digitalRead(LED);
    doc["buzzer"] = digitalRead(Buzzer);
    doc["fan"] = digitalRead(Fan);

    // gửi data thông qua cổng giao tiếp mềm cho Chip WiFi
    serializeJson(doc, mySerial);
    mySerial.println();

    // In ra màn hình Serial
    serializeJson(doc, Serial);
    Serial.println();

    timeUpdata = millis();
  }
  if (mySerial.available()) {
    String data = mySerial.readStringUntil('\n');
    DeserializationError error = deserializeJson(docBtn, data);

    serializeJson(docBtn, Serial);
    Serial.println();

    if (!error) {
      String topic = docBtn["topic"];
      String message = docBtn["message"];

      if (topic == "Ví dụ button1/led") {   //  ta sửa theo  topic sub bên code cho chip WiFi
        if (message == "1") {
          // Thực hiện hành động bật đèn LED
          digitalWrite(LED, HIGH);
        } else if (message == "0") {
          // Thực hiện hành động tắt đèn LED
          digitalWrite(LED, LOW);
        }
        Serial.println("Bật/tắt đèn LED: " + String(message));
      }
      if (topic == "Ví dụ button1/buzzer") {  //  ta sửa theo  topic sub bên code cho chip WiFi
        if (message == "1") {
          // Thực hiện hành động bật còi
          digitalWrite(Buzzer, HIGH);
        } else if (message == "0") {
          // Thực hiện hành động tắt còi
          digitalWrite(Buzzer, LOW);
        }
        Serial.println("Bật/tắt buzzer: " + String(message));
      }

      if (topic == "Ví dụ button1/fan") {   //  ta sửa theo  topic sub bên code cho chip WiFi
        if (message == "1") {
          // Thực hiện hành động bật còi
          digitalWrite(Fan, HIGH);
        } else if (message == "0") {
          // Thực hiện hành động tắt còi
          digitalWrite(Fan, LOW);
        }
        Serial.println("Bật/tắt fan: " + String(message));
      }
    } else {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
    }
  }
}