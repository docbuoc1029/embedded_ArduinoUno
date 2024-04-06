void setup() {
  Serial.begin(9600); // Khởi tạo Serial với tốc độ Baudrate 9600 
  pinMode(8,OUTPUT); //Trên board Uno có một con Led và nó được gắn nối thông quachân D13
}

void loop() {
// put your main code here, to run repeatedly: 
  if(Serial.available()>0){
    String str = Serial.readStringUntil('\n'); // Khởi tạo chuỗi để nó lưu từng byte data kí tự, 1 ký tự = 1 byte
    if(str == "on")
      digitalWrite(8,HIGH);// Nếu chuỗi mình gửi nó nhận là on thì đèn sáng 
    if(str == "off")
      digitalWrite(8,LOW);// Nếu chuỗi mình gửi nó nhận là off thì đèn tắt
  }
}
