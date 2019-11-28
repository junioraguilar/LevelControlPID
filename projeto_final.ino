#include <Ultrasonic.h>

#define pino_trigger 7
#define pino_echo 4

Ultrasonic ultrasonic(pino_trigger, pino_echo);

int velocidade_maxima_motor = 255;
int velocidade_minima_motor = 0;

int IN1 = 9;
int velocidadeA = 10;
 
float kp = 10;
float ki = 0.001;
float kd = 2;
int sp = 50;

float acao_anterior = 0;

float integral_error = 0;
float erro_anterior = 0;

int serial = 0;


int i = 0;
bool ultimoEstado = HIGH;
bool botaoEstado = LOW;
long ultimoDeboucingTempo = 0;
long deboucingDelay = 10;


void setup(){
pinMode(IN1,OUTPUT);
pinMode(velocidadeA,OUTPUT);

pinMode(2, INPUT);
pinMode(12, INPUT);
pinMode(11, INPUT);
Serial.begin(9600);
}
 
void loop(){
  bool estadoBotao1 = digitalRead(2);
  bool estadoBotao2 = digitalRead(12);
  bool estadoBotao3 = digitalRead(11);

  if(estadoBotao1 != ultimoEstado){
    ultimoDeboucingTempo = millis();
    if((millis() - ultimoDeboucingTempo) > deboucingDelay){
      if(estadoBotao1 != botaoEstado){
        estadoBotao1 = botaoEstado;
      }
    }
    
    while(estadoBotao1){
      i++;
      break;
    }
  }

  ultimoEstado = digitalRead(2);
  if (i > 3){
    i = 0;
    }

    
   if(i == 0){
    if(estadoBotao2){
      kd+= 0.5;
    }
    if(estadoBotao3){
      kd-=0.5;
    }
   }

   if(i == 1){
    if(estadoBotao2){
      ki = ki + 0.01;
    }
    if(estadoBotao3){
      ki = ki - 0.01;
    }
   }


    if(i == 3){
    if(estadoBotao2){
      kp++;
    }
    if(estadoBotao3){
      kp--;
    }
   }

   if(i == 2){
    if(estadoBotao2){
      sp++;
    }
    if(estadoBotao3){
      sp--;
    }
   }




   if (kd > 10){
    kd = 10;
   }
   if (kd < 0){
    kd = 0;
   }


   if (kd > 10){
    kd = 10;
   }
   if (kd < 0){
    kd = 0;
   }

   if (ki > 1){
    ki = 1;
   }
   if (ki < 0.001){
    ki = 0.000;
   }


   if (sp > 99){
    sp = 99;
   }
   if (sp < 0){
    sp = 0;
   }


   if (kp > 20){
    kp = 20;
   }
   if (kp < 0){
    kp = 0;
   }

   

   Serial.print("variavel:  ");
   Serial.print(i);
   
   Serial.print("    KD:");
   Serial.print(kd);
   
   Serial.print("    ki:");
   Serial.print(ki);
   
   Serial.print("    sp:");
   Serial.print(sp);
   
   Serial.print("    kp:");
   Serial.println(kp);
   

   
   Serial.print("variavel:  ");
   Serial.print(i);
   
   Serial.print("    KD:");
   Serial.print(kd);
   
   Serial.print("    ki:");
   Serial.print(ki, 4);
   
   Serial.print("    sp:");
   Serial.print(sp);
   
   Serial.print("    kp:");
   Serial.print(kp);

   

   










  
    
    int velocidade = calculopid(sp, kp, ki, kd);
    Serial.print("    PID:");
    Serial.print(velocidade);
    Serial.print("   distancia:");
    Serial.println(distancia()); 
//    Serial.print("    ");
//    Serial.print(velocidade);
    digitalWrite(IN1,HIGH); 
    analogWrite(velocidadeA, velocidade);
  }













float distancia(){   
  float cmMsec, inMsec;
  double microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  delay(10);
  return cmMsec;
  
}
int calculopid(int sp, int kp, int ki, int kd){  
  float pv = distancia();
  pv = map(pv, 38.0, 7.0, 0.0, 100.0);
  //Serial.print("         variavel:");
  int variable = map(pv, 0, 100, 0, 40);
  //Serial.println(int(variable));
  float erro = sp - pv;
  integral_error += erro * 0.01;
  float D = (erro - erro_anterior)/0.01;
  
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
  
  erro_anterior = erro;
  return velocity;
}
