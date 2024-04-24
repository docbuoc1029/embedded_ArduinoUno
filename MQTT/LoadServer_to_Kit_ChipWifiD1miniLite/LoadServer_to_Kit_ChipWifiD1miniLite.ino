#ifdef ESP8266
#include <ESP8266WiFi.h> /* WiFi library for ESP8266 */
#else
#include <WiFi.h> /* WiFi library for ESP32 */ 
#endif
#include <Wire.h>
#include <SoftwareSerial.h> 
#include <ArduinoJson.h> 
#include <PubSubClient.h> 
#include <WiFiClientSecure.h>

// Khai báo các chân RX và TX cho espsoftwareserial
// Nếu bạn dùng Chip WiFi D1 mini Lite 
#define RX_PIN D3
#define TX_PIN D4

// Nếu bạn sử dụng Esp32
// #define RX_PIN 12
// #define TX_PIN 14
// Tạo một đối tượng espsoftwareserial với tốc độ baud là 9600 
SoftwareSerial mySerial (RX_PIN, TX_PIN); 
DynamicJsonDocument doc ( 1024 );

#define wifi_ssid "IoT LAB" 
#define wifi_password "kvt1ptit"
#define mqtt_server "10.170.69.245" // địa chỉ IP của MQTT Broker

WiFiClient espClient; 
PubSubClient client (espClient);

// Kết nối tới WiFi 
void setup_wifi () { 
delay ( 10 )
  Serial . println ();
  Serial . print ( "Connecting to " ); 
  Serial . println (wifi_ssid);

  WiFi . begin (wifi_ssid, wifi_password);

  while ( WiFi . status () != WL_CONNECTED) { 
    delay ( 500 );
    Serial . print ( "." );
  }
  Serial . println ( "" );
  Serial . println ( "WiFi connected" ); 
  Serial . println ( "IP address: " ); 
  Serial . println ( WiFi . localIP ());
}

// Kết nối tới MQTT Broker 
void reconnect () {
  while (! client . connected ()) {
    Serial . print ( "Attempting MQTT connection..." );
    if ( client . connect ( "IoTLABClient" )) {
      Serial . println ( "connected" );
      client . subscribe ( "Nhóm của bạn" ); // tự đặt topic Sub theo nhóm của bạn. Ví dụ "sensor1"
    } 
    else {
      Serial . print ( "failed, rc=" ); 
      Serial . print ( client . state ());
      Serial . println ( " try again in 5 seconds" ); 
      delay ( 5000 );
    }
  }
}

//-----------Call back Method for Receiving MQTT massage and Switch LED---------
void callback ( char* topic, byte * payload, unsigned int length) {
  String incommingMessage = "" ;
  for ( int i = 0 ; i < length; i++) incommingMessage += ( char ) payload [i];
  Serial . println ( "Massage arived [" + String (topic) + "]" + incommingMessage);
  DynamicJsonDocument docSub ( 1024 );
  DeserializationError error = deserializeJson (docSub, incommingMessage)
  if (error) {
    Serial . print ( "deserializeJson() failed: " ); 
    Serial . println ( error . c_str ());
    return ;
  }
  serializeJson (docSub, mySerial); 
  mySerial . println ();
  }

//-----Method for Publishing MQTT Messages---------
void publishMessage ( const char* topic, String payload, boolean retained) { 
  if ( client . publish (topic, payload . c_str (), true ))
    Serial . println ( "Message published [" + String (topic) + "]: " + payload);
}

void setup () {
  // Khởi tạo cổng nối tiếp phần cứng với tốc độ baud là 115200 
  Serial . begin ( 115200 );
  // Khởi tạo cổng nối tiếp phần mềm với tốc độ baud là 9600 
  mySerial . begin ( 9600 );
  setup_wifi ();
  client . setServer (mqtt_server, 1883 ); 
  client . setCallback (callback);
}

void loop () {
  if (! client . connected ()) {
    reconnect ();
  }
  client . loop ();
  
  // nhận data từ Arduino thông qua Tx-Rx và sau đó publish data lên MQTT Broker 
  if ( mySerial . available ()) {
    String data = mySerial . readStringUntil (' \n '); 
    DeserializationError error = deserializeJson (doc, data); 
    char mqtt_message [ 1024 ];
    serializeJson (doc, mqtt_message);
    publishMessage ( "Nhóm của bạn" , mqtt_message, true ); // tự đặt topic Pub theonhóm của bạn. Ví dụ "sensor1"
    serializeJson (doc, Serial); 
    Serial . println ();
  }
}