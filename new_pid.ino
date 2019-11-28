#include <Ultrasonic.h>

#define pino_trigger 7
#define pino_echo 4

Ultrasonic ultrasonic(pino_trigger, pino_echo);

int velocidade_maxima_motor = 200;
int velocidade_minima_motor = 50;

int IN1 = 9;
int velocidadeA = 10;
 
float kp = 8;
float ki = 0.1;
float kd = 3;
int sp = 50;

float acao_anterior = 0;

float integral_error = 0;
float erro_anterior = 0;

int serial = 0;
void setup(){
pinMode(IN1,OUTPUT);
pinMode(velocidadeA,OUTPUT);
Serial.begin(9600);
}
 
void loop(){
      if(Serial.available() > 0){
        sp = Serial.parseInt();
        Serial.println(sp);
      }

    
    int velocidade = calculopid(sp);
//    Serial.print("    ");
//    Serial.print(velocidade);
    Serial.print("    ");
    Serial.println(int(distancia()));
    analogWrite(velocidadeA, velocidade);
  }













float distancia(){   
  float cmMsec, inMsec;
  double microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  delay(30);
  return cmMsec;
  
}
int calculopid(int sp){  
  float pv = distancia();
  pv = map(pv, 44.0, 7.0, 0.0, 100.0);
  //Serial.print("         variavel:");
  int variable = map(pv, 0, 100, 0, 40);
  //Serial.println(int(variable));
  float erro = sp - pv;
  integral_error += erro * 0.03;
  float D = (erro - erro_anterior)/0.03;
  
  float pi = (kp*erro) + (integral_error*ki*kp) + (D*kd);
  
  if (pi > 100){
    pi = 100;
  }
  if (pi < 0){
    pi = 0;
  }
  //Serial.print(" PID:");
  //Serial.print(int(pi));
  float velocity = map(pi, 0.0, 100.0, velocidade_minima_motor ,velocidade_maxima_motor);
  
  digitalWrite(IN1,HIGH); 
  erro_anterior = erro;
  return velocity;
}
