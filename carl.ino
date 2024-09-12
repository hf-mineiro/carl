#include<Servo.h>

#define FRENTEM1 120
#define TRASM1 60
#define FRENTEM2 120
#define TRASM2 60 

//variaveis ultrassom
int PinTrigger = 2; // Pino usado para disparar os pulsos do sensor
int PinEcho = 3; // pino usado para ler a saida do sensor
float TempoEcho = 0;
const float VelocidadeSom_mpors = 340; // em metros por segundo
const float VelocidadeSom_mporus = 0.000340; // em metros por microsegundo
int distancia = 0;

//definir distancia do sensor de disparo
int distanciaminima = 5;
int distanciamaxima = 30;

//variaveis motores
int vel_motor1 = 90;
int vel_motor2 = 90;
 
Servo motor1;
Servo motor2;

// variavel serial
char caractereLido;

void setup() {
  // put your setup code here, to run once:
  motor1.attach(9);
  motor2.attach(10);
  Serial.begin(9600);
  Serial.println(" inicio ");
  // inicia motores parados
  motor1.write(90);
  motor2.write(90);
  // Configura pino de Trigger como saída e inicializa com nível baixo
  pinMode(PinTrigger, OUTPUT);
  digitalWrite(PinTrigger, LOW);
  pinMode(PinEcho, INPUT); // configura pino ECHO como entra

  delay(100);
}

void frente (int tempo){
  Serial.println("frente");
  motor1.write (FRENTEM1);
  motor2.write (FRENTEM2);
  delay(tempo);
  motor1.write (90);
  motor2.write (90);
  delay(500);
  
}

void direita (int tempo){
  Serial.println("frente");
  motor1.write (FRENTEM1);
  motor2.write (90);
  delay(tempo);
  motor1.write (90);
  motor2.write (90);
  delay(500);
  
}

void esquerda (int tempo){
  Serial.println("frente");
  motor1.write (90);
  motor2.write (FRENTEM2);
  delay(tempo);
  motor1.write (90);
  motor2.write (90);
  delay(500);
  
}



void tras (int tempo){
  Serial.println("tras");
  motor1.write (TRASM1);
  motor2.write (TRASM2);
  delay(tempo);
  motor1.write (90);
  motor2.write (90);
  delay(500);
  
}

void DisparaPulsoUltrassonico(){
  // Para fazer o HC-SR04 enviar um pulso ultrassonico, nos temos
  // que enviar para o pino de trigger um sinal de nivel alto
  // com pelo menos 10us de duraçao
  digitalWrite(PinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(PinTrigger, LOW);
}

// Função para calcular a distancia em metros
float CalculaDistancia(float tempo_us){
  return((tempo_us*VelocidadeSom_mporus)/2);
}


void loop() {
  while((distancia < distanciaminima || distancia > distanciamaxima){  
     DisparaPulsoUltrassonico();
    // Mede o tempo de duração do sinal no pino de leitura(us)
    TempoEcho = pulseIn(PinEcho, HIGH);
    distancia = CalculaDistancia(TempoEcho)*100;
    Serial.println("Distancia em centimetros: ");
    Serial.println(distancia);
  }
  if (Serial.available()){
    // ajuste de valores dos motores
    caractereLido = Serial.read();
    if(caractereLido == 'F') vel_motor1 +=5;
    if(caractereLido == 'G') vel_motor2 +=5;
    if(caractereLido == 'T') vel_motor1 -=5;
    if(caractereLido == 'Y') vel_motor2 -=5;
    Serial.println (vel_motor1);
    Serial.println (vel_motor2);
    Serial.println ("   ");
    motor1.write(vel_motor1);
    motor2.write(vel_motor2);  
  }
  // codigo de comandos
  frente(2000);
  // fim de codigo de comandos
  
}
