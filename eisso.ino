#include <Ultrasonic.h>

#define pino_trigger 7
#define pino_echo 4

Ultrasonic ultrasonic(pino_trigger, pino_echo);

int IN1 = 9;
int velocidadeA = 10;
float velocidade = 0;
 
int kp = 5;
int ki = 0.01;
int kd = 2;
int sp = 75;

float acao_anterior = 0;

float integral_error = 0;
float erro_anterior = 0;

int serial = 0;
void setup(){
pinMode(IN1,OUTPUT);
pinMode(velocidadeA,OUTPUT);
Serial.begin(9600);
Serial.println("INICIEI");


}
 
void loop(){
  serial = Serial.available();
  if (serial > 0){
    if (Serial.find("sp")){
      Serial.println("ACHEI o sp");
      String valorLido = Serial.readString();
      sp = atoi(valorLido.c_str());
      int velocity = calculoPID('s', sp);
      analogWrite(velocidadeA, velocity);
      Serial.println(sp);
    }
    if (Serial.find("kp")){
      Serial.println("ACHEI o kp");
      String kpLido = Serial.readString();
      kp = atoi(kpLido.c_str());      
      int velocity = calculoPID('p', kp);      
      analogWrite(velocidadeA, velocity);
      Serial.println(kp);
    }
    if(Serial.find("ki")){
      Serial.println("ACHEI o ki");
      String kiLido = Serial.readString();
      ki = atoi(kiLido.c_str());
      int velocity = calculoPID('i', ki);      
      analogWrite(velocidadeA, velocity);      
      Serial.println(ki);
    }
    if(Serial.find("kd")){
      Serial.println("ACHEI o kd");
      String kdLido = Serial.readString();
      kd = atoi(kdLido.c_str());
      int velocity = calculoPID('d', kd);      
      analogWrite(velocidadeA, velocity);
      Serial.println(kd);
    }
    
   }
    int velocity = calculopid();    
    analogWrite(velocidadeA, velocity);
  }


float distancia(){   
  float cmMsec, inMsec;
  double microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  delay(30);
  return cmMsec;
  
}
int calculoPID(char tipo, int valor){
  switch (tipo){
    case 's':
      sp = valor;
      break;
    case 'p':
      kp = valor;
      break;
    case 'd':
      kd = valor;
      break;
    case 'i':
      ki = valor;
      break;
      
    
  }
  
  float pv = distancia();
  pv = map(pv, 46.0, 8.0, 0.0, 100.0);
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
  float velocity = map(pi, 0.0, 100.0, 0 ,255.0);
  
  digitalWrite(IN1,HIGH); 
  erro_anterior = erro;
  return velocity;
}

int calculopid(){  
  float pv = distancia();
  pv = map(pv, 46.0, 8.0, 0.0, 100.0);
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
  float velocity = map(pi, 0.0, 100.0, 0 ,255.0);
  
  digitalWrite(IN1,HIGH); 
  erro_anterior = erro;
  return velocity;
}
