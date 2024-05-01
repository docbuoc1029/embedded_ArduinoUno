#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);	// Khai báo địa chỉ của LCD gồm 16 cột,2 dòng

void setup() {
  lcd.init();// Khởi động màn hình lCD
  lcd.backlight();// Bật đèn nền LCD
  lcd.setCursor(0,0); //Đưa con trỏ vị trí tới hàng 1 cột 1, nếu là (1,0) thì là hàng 1 cột thứ 2
  lcd.print("Hello, world!");// In ra màn hình LCD lcd.setCursor(0,1); // Đưa con trỏ tới vị trí hàng 1 cột 2 lcd.print("IoT LAB"); // In ra màn hình LCD
}

void loop() {

}
