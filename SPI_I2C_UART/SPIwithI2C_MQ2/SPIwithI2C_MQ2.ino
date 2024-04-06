void setup() {
  // put your setup code here, to run once: 
  Serial.begin(9600);
}

void loop() {
// put your main code here, to run repeatedly:
  int value = analogRead(A0);// Đọc giá trị analog từ chân A0 
  int threshold = 500; // Xet ngưỡng cảnh báo 
  Serial.print("AnalogRead: ");
  Serial.println(value);
  if(value < 500)// Nếu vượt quá ngưỡng
    Serial.println("An toan"); 
  else
    Serial.println("Bao Dong");
}

