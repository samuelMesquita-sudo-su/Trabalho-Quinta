#include <Ultrasonic.h>

//pinos do HC
#define pinoTrigger 3
#define pinoEcho 4

Ultrasonic ultrasonic(pinoTrigger, pinoEcho);

//PINO dO LED
int pinoLed = 6;

//sobre o ventilador
bool ventiladorLigado = false;
long tempoLigado = 0;
unsigned long tempo;
int batman = 0;;

void setup() {
  pinMode(pinoTrigger, OUTPUT);
  pinMode(pinoEcho, INPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(pinoLed, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //velocidade
  int velocidade = analogRead(A0)/4;


  float cmMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert (microsec, Ultrasonic::CM);
  Serial.println(cmMsec);
  Serial.println(tempoLigado);
  delay(50);

  if ((cmMsec > 0 && cmMsec <= 10) && batman == 0 && (millis() - tempo > 2000))
  {
    Serial.println("ventiladorLigando");
    ventiladorLigado = true;
    //peguei essa parte do codigo aq;
    analogWrite(10, velocidade);
    analogWrite(11, 0);
    tempo = millis();
    batman = 1;

    digitalWrite(pinoLed, HIGH);
  }

  if ((cmMsec > 0 && cmMsec <= 10) && batman == 1 && (millis() - tempo > 2000) )
  {
    Serial.println("Desligando Ventilador");
    ventiladorLigado = false;
    analogWrite(10, 0);
    analogWrite(11, 0);
    tempo = millis();
    batman = 0;

    digitalWrite(pinoLed, LOW);
  }




}