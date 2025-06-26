#include <Ultrasonic.h>

#define pinoTrigger 3
#define pinoEcho 4

Ultrasonic ultrasonic(pinoTrigger, pinoEcho);

int pinoLed = 6;
bool ventiladorLigado = false;
unsigned long tempo = 0;
bool podeAlternar = true; // nova variável

void setup() {
  pinMode(pinoTrigger, OUTPUT);
  pinMode(pinoEcho, INPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(pinoLed, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int velocidade = analogRead(A0) / 4;
  float cmMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);

  Serial.println(cmMsec);
  delay(50);

  // Quando a mão estiver próxima
  if (cmMsec > 0 && cmMsec <= 10) {
    if (podeAlternar && millis() - tempo > 2000) {
      ventiladorLigado = !ventiladorLigado;

      if (ventiladorLigado) {
        Serial.println("Ligando ventilador");
        digitalWrite(pinoLed, HIGH);
        analogWrite(10, velocidade);
        analogWrite(11, 0);
      } else {
        Serial.println("Desligando ventilador");
        digitalWrite(pinoLed, LOW);
        analogWrite(10, 0);
        analogWrite(11, 0);
      }

      tempo = millis();
      podeAlternar = false; // evita nova troca enquanto ainda está perto
    }
  }

  // Quando a mão se afasta
  if (cmMsec > 15) {
    podeAlternar = true;
  }

  // Se estiver ligado, atualiza a velocidade
  if (ventiladorLigado) {
    analogWrite(10, velocidade);
  }
}
