int sp = 30;
int kp = 10;
int kd = 10;
int ki = 10;


bool ultimoEstado = 0;

long ultimoDeboucingTempo = 0;
long deboucingDelay = 50;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); 
pinMode(6, INPUT);
pinMode(5, INPUT);
pinMode(4, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool estadoBotao1 = digitalRead(6);
  bool estadoBotao2 = digitalRead(5);
  bool estadoBotao3 = digitalRead(4);

  if(estadoBotao1 != ultimoEstado){
    ultimoDeboucingTempo = millis();
    if((millis() - ultimoDeboucingTempo) > deboucingDelay){
      Serial.println("SAI");
    }
    
  }

  ultimoEstado = digitalRead(6);
  Serial.println(ultimoEstado);

}
