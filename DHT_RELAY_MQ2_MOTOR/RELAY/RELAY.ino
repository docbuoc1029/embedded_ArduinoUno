int Relay = 8;

void setup() {
  pinMode(Relay, OUTPUT); 
  digitalWrite(Relay, HIGH);
}
void loop() { 
  digitalWrite(Relay, LOW); 
  delay(1000);
  digitalWrite(Relay, HIGH); 
  delay(1000);
}

