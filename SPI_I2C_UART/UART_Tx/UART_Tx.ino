#include <ArduinoJson.h> 
#include <DHT.h>

#define DHTPIN 8	// Pin Chân Digtal Uno để giao tiếp DHT
#define DHTTYPE DHT22	//Loại DHT22 trên IoT Lab dùng

DHT dht(DHTPIN, DHTTYPE);

// Tạo một đối tượng JsonDocument có dung lượng 100 byte
StaticJsonDocument<100> doc;

void setup() {
  // put your setup code here, to run once: 
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly: 
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Gán giá trị nhiệt độ và độ ẩm vào đối tượng JsonDocument
  doc["temperature"] = temperature; 
  doc["humidity"] = humidity;

  serializeJson(doc, Serial); 
  Serial.println(); delay(1000);
}
