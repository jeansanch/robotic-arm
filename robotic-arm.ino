#include <Servo.h>
#include <Ultrasonic.h>
 
#define pino_trigger 8
#define pino_echo 9
#define pino_ima 4
 
Ultrasonic ultrasonic(pino_trigger, pino_echo);

Servo servoBase, servoIma;
int x = 0, i;
float microsec;
void setup()
{
  Serial.begin(9600);
  servoBase.attach(6);
  servoIma.attach(5);  
  pinMode(13, OUTPUT); //LED
  pinMode(pino_ima, OUTPUT);
}
 
void loop()
{
  digitalWrite(pino_ima, HIGH);
  x = 0;
  servoIma.write(100);
  servoBase.write(0);
  float cmMsec;
  microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  Serial.print("Distancia em cm: ");
  Serial.println(cmMsec);
 

  do{
    microsec = ultrasonic.timing();
    cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
    Serial.print("Distancia em cm: ");
    Serial.println(cmMsec);
    if (cmMsec < 15){
      x = x + 1;
    }
    else{
      x = 40;
    }
    delay(250);
  }
  while(x < 24);
  
  if(x == 24){
    digitalWrite(13, HIGH);
    delay(4000);
    for(i = 100; i < 121; i++){
      servoIma.write(i);
      delay(80);
    }
    //Liga imã
    digitalWrite(pino_ima, LOW);
    for(i = 120; i > 100; i--){
      servoIma.write(i);
      delay(80);
    }
    for(i = 0; i < 181; i++){
      servoBase.write(i);
      delay(30);
    }
    delay(5000);
    for(i = 100; i < 131; i++){
      servoIma.write(i);
      delay(80);
    }
    //Desliga imã
    digitalWrite(pino_ima, HIGH);
    for(i = 130; i > 100; i--){
      servoIma.write(i);
      delay(80);
    }    
    for(i = 180; i > 0; i--){
      servoBase.write(i);
      delay(30);
    }
    digitalWrite(13, LOW);
    delay(500);
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
    digitalWrite(13, HIGH);
    delay(500);

  }
    digitalWrite(13, LOW);

   delay(250);
}