#define led 6 
void setup() {
  Serial.begin(9600); //Mở cổng Serial để giao tiếp | tham khảo Serial 
  pinMode(led,OUTPUT);
}
void loop() {
  int value = analogRead(A0); //đọc giá trị điện áp ở chân A0 - chân cảm biến value luôn nằm trong khoảng 0-1023
  Serial.println(value);	//xuất ra giá trị vừa đọc
  int thershold = 500 // Set một ngưỡng nào cho khí gas 
  if(value > thershold) // nếu vượt quá ngưỡng 
    digitalWrite(led,HIGH); // bật đèn cảnh báo
  else // nếu vẫn đang bình thường 
    digitalWrite(led,LOW); //Đèn tắt
}
