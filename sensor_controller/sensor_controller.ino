
//Bibliotecas
#include <SimpleDHT.h>
#include <photosensor.h>
#include <distanceSensor.h>
#include <motionSensor.h>
#include <temperatureSensor.h>
#include <Servo.h>

// Sensor LDR
#define LDR A0
#define LED_LDR 12

// Sensor PIR
#define PIR 2
#define LED_PIR 8 

// Sensor HC-SR04
#define HC_TRIGGER 10
#define HC_ECHO 11
#define SERVO_HC 6

// Sensor DHT11
#define DHT 4
#define LED_DHT 13

// Definir Objetos
Photosensor photosensor(LDR, LED_LDR);
DistanceSensor distanceSensor(HC_TRIGGER, HC_ECHO);
Temperature temperatureSensor(DHT, LED_DHT);
MotionSensor motionSensor(PIR, LED_PIR);

Servo servo;
// Setup
void setup(){
  Serial.begin(9600);
}

// Loop
void loop(){
  
 photosensor.run();
 motionSensor.run();
 temperatureSensor.run();

 // Distance Sensor
 if (distanceSensor.run() == true){
   moveServo();
 }
 delay(100);
}

/*
 * Mueve el Servo a 180° durante 5 s
 */
void moveServo(){
  servo.attach(SERVO_HC); // Encender el servo
  servo.write(180);
  delay(5000);
  servo.write(0);
  delay(100);
  servo.detach(); // Apagar el servo para evitar desperdicio de potencia
}
