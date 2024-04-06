#include <LiquidCrystal_I2C.h> 
#include <Keypad.h> 
#include<stdio.h>

const byte ROWS = 4; //4 hàng const byte COLS = 3; //3 cột

String arr[8] = {};
String password[8] = {"1", "2", "3", "4", "5", "6", "7", "8"};

int place = 0; int input = 6;

bool value = true;

char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

LiquidCrystal_I2C lcd(0x27,16,2);	// Khai báo địa chỉ của LCD gồm 16 cột, 2 dòng

byte rowPins[ROWS] = {8, 3, 4, 6}; //nối hàng của keypad
byte colPins[COLS] = {7, 9, 5};	//nối cột keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); void setup(){
  lcd.init();// Khởi động màn hình lCD
  lcd.backlight();// Bật đèn nền LCD
  lcd.setCursor(0,0); //Đưa con trỏ vị trí tới hàng 1 cột 1, nếu là (1,0) thì
  lcd.print("pass: "); lcd.setCursor(0,1); lcd.print("status: ");
  
  Serial.begin(9600); //khởi tạo serial
}

void loop(){
  //Kiểm tra nút được nhấn
  char key = keypad.getKey();

  //in nút ra màn hình 
  if (key != NO_KEY) {
  lcd.setCursor(input,0); 
  lcd.print(key); 
  arr[place] = key; place++;
  input++;
  }
  if(place == 8) {
    for(int i = 0;i<8;i++) {
      if(arr[i] != password[i]) {
        value = false; break;
      }
    }
    if(value == true) {
      lcd.setCursor(0,1); 
      lcd.print("	Welcome!	");
    } 
    else {
      place = 0; value = true;
      lcd.setCursor(8,1); 
      lcd.print("Wrong!"); input = 6; 
      lcd.setCursor(input,0); 
      lcd.print("		"); delay(1000); 
      lcd.setCursor(8,1); 
      lcd.print("	");
    }
  }
}

