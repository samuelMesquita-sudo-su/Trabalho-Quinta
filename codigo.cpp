// === Pinos do HC-SR04 ===
const int trigPin = 4;
const int echoPin = 3;

// === Pinos do motor (ponte H) ===
const int in1 = 10;
const int in2 = 11;
const int ena = 3; // PWM

// === LED indicador ===
const int ledPin = 6;

// === Potenciômetro ===
const int potPin = A0;

// Estado do sistema
bool ventiladorLigado = false;  // novo controle de presença
long tempoLigado;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  long duracao, distancia;

  // Envia pulso para medir distância
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracao = pulseIn(echoPin, HIGH);
  distancia = duracao * 0.034 / 2; // cm

  Serial.print("Distância: ");
  Serial.println(distancia);

  // Verifica presença e faz toggle só quando detecta entrada da mão
  if (distancia < 5 && ventiladorLigado == false) {
    ventiladorLigado = true;  // marca que já detectou
    tempoLigado = millis();
    Serial.println(ventiladorLigado ? "Sistema LIGADO" : "Sistema DESLIGADO");
    delay(300);  // pequena pausa pra evitar repetições
  }

  // Quando a mão sai da frente, permite nova detecção
  if (ventiladorLigado && tempoLigado >= 10000) {
    ventiladorLigado = false;
    Serial.println("Ventilador desligado ");
    
  }

  if (ventiladorLigado) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    int potValor = analogRead(potPin);
    int velocidade = map(potValor, 0, 1023, 0, 255);
    analogWrite(ena, velocidade);
  } else {
    digitalWrite(ledPin, LOW);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(ena, 0);
  }

  delay(100);
}
