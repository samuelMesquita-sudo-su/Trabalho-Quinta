#include <Ultrasonic.h>

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
long tempoLigado = 0;


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

  if ((cmMsec <= 10) && (ventiladorLigado == false) )
  {
    Serial.println("ventiladorLigando");
    ventiladorLigado = true;
    //peguei essa parte do codigo aq;
    analogWrite(10, velocidade);
    analogWrite(11, 0);
    tempoLigado++;
  }

  if (ventiladorLigado == true && tempoLigado >= 10)
  {
    Serial.println("Desligando Ventilador");
    ventiladorLigado == false;
    analogWrite(10, 0);
    analogWrite(11, 0);
  }




}
