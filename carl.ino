#include<Servo.h>

#define FRENTEM1 60
#define TRASM1 120
#define FRENTEM2 120
#define TRASM2 60 

int vel_motor1 = 90;
int vel_motor2 = 90;
 
Servo motor1;
Servo motor2;
char caractereLido;

void setup() {
  // put your setup code here, to run once:
  motor1.attach(9);
  motor2.attach(10);
  Serial.begin(9600);
  Serial.println(" inicio ");
  motor1.write(90);
  motor2.write(90);

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

void tras (int tempo){
  Serial.println("tras");
  motor1.write (TRASM1);
  motor2.write (TRASM2);
  delay(tempo);
  motor1.write (90);
  motor2.write (90);
  delay(500);
  
}


void loop() {
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
  tras(2000);
  // fim de codigo de comandos
  
}
