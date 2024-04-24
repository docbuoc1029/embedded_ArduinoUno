#include <DHT.h>
#include <LiquidCrystal_I2C.h> 
#include <ArduinoJson.h> 
#include <SoftwareSerial.h>

#define DHT_Data 8
DHT dht (DHT_Data, DHT22); // DHT11 
#define MQ_Data A1
#define RX_PIN 10 // Chân RX của cổng nối tiếp mềm 
#define TX_PIN 11 // Chân TX của cổng nối tiếp mềm

SoftwareSerial mySerial (RX_PIN, TX_PIN); // Tạo một đối tượng cổng nối tiếp mềm 
LiquidCrystal_I2C lcd (0x 27 , 16 , 2 ); // or set address on 0x20

void setup () {
  Serial . begin ( 9600 ); 
  mySerial . begin ( 9600 ); 
  while (!Serial) delay ( 1 );
  dht . begin ();

  lcd . init ();
  lcd . backlight ();
}

unsigned long timeUpdata = millis ();

DynamicJsonDocument doc ( 1024 ); 
DynamicJsonDocument docSub ( 1024 );

void loop () {
  if ( millis () - timeUpdata > 2000 ) { 
    float hum = dht . readHumidity (); 
    float temp = dht . readTemperature (); 
    float gas = analogRead (MQ_Data);
    doc [ "temperature" ] = temp; 
    doc [ "humidity" ] = hum; 
    doc [ "gas" ] = gas;
    // gửi data thông qua cổng giao tiếp mềm cho Chip WiFi 
    serializeJson (doc, mySerial);
    mySerial . println ();
    // In ra màn hình Serial 
    serializeJson (doc, Serial); 
    Serial . println ();
    timeUpdata = millis ();
  }
  // nhận data được gửi về từ Chip WiFi và hiển thị ra màn hình LCD 
  if ( mySerial . available ()) {
    String data = mySerial . readStringUntil (' \n '); 
    DeserializationError error = deserializeJson (docSub, data);
    float tempSub = docSub [ "temperature" ]; 
    float humSub = docSub [ "humidity" ]; 
    float gasSub = docSub [ "gas" ];
    lcd . clear ();
    lcd . setCursor ( 0 , 0 ); 
    lcd . print ( "T: " );
    lcd . print (tempSub); 
    lcd . print ( " C" );
    lcd . setCursor ( 9 , 0 ); 
    lcd . print ( "H: " );
    lcd . print (humSub); 
    lcd . print ( " %" );
    lcd . setCursor ( 0 , 1 ); 
    lcd . print ( "G: " );
    lcd . print (gasSub);
  }
}