#include <Ultrasonic.h>

#define pino_trigger 5
#define pino_echo 4

Ultrasonic ultrasonic(pino_trigger, pino_echo);

int IN1 = 10;
int velocidadeA = 9;
float velocidade = 0;
 
#define kp 10
#define ki 0.01
#define kd 2
#define sp 50

float acao_anterior = 0;

float integral_error = 0;
float erro_anterior = 0;
void setup(){
pinMode(IN1,OUTPUT);
pinMode(velocidadeA,OUTPUT);
Serial.begin(9600);


}
 
void loop(){

float pv = distancia();
pv = map(pv, 46.0, 8.0, 0.0, 100.0);
Serial.print("         variavel:");
Serial.println(int(pv));
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
Serial.print(" PID:");
Serial.print(int(pi));
float velocity = map(pi, 0.0, 100.0, 0 ,255.0);

digitalWrite(IN1,HIGH);
analogWrite(velocidadeA, velocity); 
erro_anterior = erro;
}


float distancia(){   
  float cmMsec, inMsec;
  double microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  delay(30);
  return cmMsec;
  
}

