#define red 7
#define green 8
#define blue 9

void setup() {
  pinMode(red, OUTPUT); // Cấu hình chân D7 làm OUTPUT cho led red pinMode(green, OUTPUT); // Cấu hình chân D8 làm OUTPUT cho led green pinMode(blue, OUTPUT); // Cấu hình chân D9 làm OUTPUT cho led blue
 
}

void loop() {
  digitalWrite(red,HIGH); // Chân red lên mức Cao hay Bật Đèn Led
  delay(1000); // Đèn sáng tầm 1 giây
  digitalWrite(red,LOW); // Chân red xuống mức Thấp hay Tắt Đèn Led digitalWrite(green,HIGH); // Chân green lên mức Cao hay Bật Đèn Led delay(1000); // Đèn sáng tầm 1 giây
  digitalWrite(green,LOW); // Chân green xuống mức Thấp hay Tắt Đèn Led digitalWrite(blue,HIGH); // Chân blue lên mức Cao hay Bật Đèn Led delay(1000); // Đèn sáng tầm 1 giây
  digitalWrite(blue,LOW); // Chân blue xuống mức Thấp hay Tắt Đèn Led
}

