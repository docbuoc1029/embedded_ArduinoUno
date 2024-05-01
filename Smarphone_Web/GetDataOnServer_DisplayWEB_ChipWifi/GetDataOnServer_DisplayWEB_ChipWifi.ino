#ifdef ESP8266
#include <ESP8266WiFi.h> /* WiFi library for ESP8266 */
#else
#include <WiFi.h> /* WiFi library for ESP32 */
#endif

#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

// Khai báo các chân RX và TX cho espsoftwareserial
#define RX_PIN D3
#define TX_PIN D4

// Tạo một đối tượng espsoftwareserial với tốc độ baud là 9600
SoftwareSerial mySerial(RX_PIN, TX_PIN);

#define wifi_ssid "IoT LAB"
#define wifi_password "kvt1ptit"
#define mqtt_server "10.170.69.245"
#define mqtt_port 1883

WiFiClient espClient;
PubSubClient client(espClient);

// Kết nối tới WiFi
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// Kết nối tới MQTT Broker
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("IoTLABClient")) {  // tự đặt ID name cho Client . Ví dụ "Client1"
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

//-----Method for Publishing MQTT Messages---------
void publishMessage(const char* topic, String payload, boolean retained) {
  if (client.publish(topic, payload.c_str(), true))
    Serial.println("Message published [" + String(topic) + "]: " + payload);
}

void setup() {
  // Khởi tạo cổng nối tiếp phần cứng với tốc độ baud là 115200 (đây là Baudrate của cổng Serial trên Arduino IDE)
  Serial.begin(115200);

  // Khởi tạo cổng nối tiếp phần mềm với tốc độ baud là 9600 ( đây là Baudrate của cổng mySerial để giao tiếp với board Arduino Uno)
  mySerial.begin(9600);

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

DynamicJsonDocument doc(1024);

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  // nhận data từ Arduino thông qua Tx-Rx và sau đó publish data lên MQTT Broker
  if (mySerial.available()) {
    String data = mySerial.readStringUntil('\n');
    DeserializationError error = deserializeJson(doc, data);
    char mqtt_message[1024];

    serializeJson(doc, mqtt_message);
    publishMessage("Ví dụ Group1", mqtt_message, true);  // tự đặt topic Pub theo nhóm của bạn. Ví dụ "Group1". 
  }
}

