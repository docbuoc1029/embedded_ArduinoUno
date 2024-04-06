#include "DHT.h" //khai báo thư viện DHT

const int DHTPIN = 7;	//khai báo chân dữ liệu DHT
const int DHTTYPE = DHT22; //khai báo kiểu DHT, có 3 loại DHT11, DHT21, DHT22 tùy kết quả có thể thay loại

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  dht.begin(); // Khởi động cảm biến.
  Serial.begin(9600);
}

void loop() {
  float h = dht.readHumidity(); //Đọc độ ẩm float 
  t = dht.readTemperature(); //Đọc nhiệt độ 
  delay(1000); //Đợi 1 giây
  Serial.print("Nhiet do: "); 
  Serial.println(t); 
  Serial.print("Do am: "); 
  Serial.println(h);
}

