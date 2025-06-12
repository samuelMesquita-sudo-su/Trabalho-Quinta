void setup() {
  
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {

  int velocidade = analogRead(A0)/4;
  analogWrite(10, velocidade);
  analogWrite(11, 0);
}
