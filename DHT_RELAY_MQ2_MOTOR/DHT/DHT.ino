#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include "DHT.h" //khai báo thư viện DHT

const int DHTPIN = 7;	//khai báo chân dữ liệu DHT
const int DHTTYPE = DHT22; //khai báo kiểu DHT, có 3 loại DHT11, DHT21, DHT22 tùy kết quả có thể thay loại
DHT dht(DHTPIN, DHTTYPE);

void setup() { 
  Serial.begin(9600);
  dht.begin(); // Khởi động cảm biến 
  lcd.init(); // Khởi tạo LCD 
  lcd.backlight(); // Bật đèn LCD
}
void loop() {
  float h = dht.readHumidity(); //Đọc độ ẩm
  float t = dht.readTemperature(); //Đọc nhiệt độ 
  lcd.setCursor(0,0); // Đặt con trỏ hàng 1 cột 1 
  lcd.print("Do Am:"); // In ra chữ Độ ẩm 
  lcd.print(h); // In ra giá trị Độ ẩm 
  lcd.setCursor(0,1); // Đặt con trỏ hàng 2 cột 1 
  lcd.print("Nhiet Do:"); // In ra chữ Nhiệt độ 
  lcd.print(t); // In ra giá trị Nhiệt độ 
  delay(1000); //Đợi 1 giây
}
