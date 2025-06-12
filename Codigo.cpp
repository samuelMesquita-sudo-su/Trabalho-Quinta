#include <Ultrasonic.h>
//precisa ter a biblioteca
//pinos do HC
#define pinoTrigger 3;
#define pinoEcho 4;

Ultrasonic ultrasonic(pinoTrigger, pinoEcho);

//velocidade
int velocidade = analogRead(A0)/4;

//PINO dO LED
int pinoLed = 6;

//sobre o ventilador
bool ventiladorLigado = false;
long tempoLigado;


void setup() {
  pinMode(pinoTrigger, OUTPUT);
  pinoMode(pinoEcho, INPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(pinoLed, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  float cmMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert (microsec, Ultraonic::CM);
  Serial.println(cmMsec);
  

  analogWrite(10, velocidade);
  analogWrite(11, 0);


}
