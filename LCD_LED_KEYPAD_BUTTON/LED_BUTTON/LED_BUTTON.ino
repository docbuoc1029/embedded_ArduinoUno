#define led 7
#define button 6

int status = 0;

void setup() {
  pinMode(led,OUTPUT); //đặt đèn led trạng thái là đầu ra (output)
  pinMode(button,INPUT_PULLUP); //đặt nút nhấn là đầu vào PULLUP nghĩa là ban đầu nút nhấn ở trạng thái HIGH (mức cao)
}

void loop() {
  if(digitalRead(button) == LOW){ // Nếu nút nhấn đang được nhấn
    delay(20); // Bỏ qua nhiễu
    if(digitalRead(button) == LOW) {// Kiểm tra thêm lần nữa để biết chắc nút nhân đã được nhấn
      if(status == 0){ //khi nhấn nút ở trạng thái đèn tắt 
        status = 1; // Biến này để ghi nhớ trạng thái đèn
        digitalWrite(led,HIGH); // Bật đèn
      }
      else{ //Khi nhấn nút ở trạng thái đèn bật
        status = 0;
        digitalWrite(led,LOW); // Tắt Đèn
      }
    }
    while(digitalRead(button) == LOW); //Nhiệm vụ khi nào nút nhấn được thả ra thì thực tiếp
  }
}
