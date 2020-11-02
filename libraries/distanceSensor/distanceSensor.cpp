#include "distanceSensor.h"

/**
 * Constructor
 * @param int trigPin
 * @param int echoPin
 * @param int servo
 */
DistanceSensor::DistanceSensor(int trigPin, int echoPin, int servo){
  _trig = trigPin;
  _echo = echoPin;

  pinMode(_trig,OUTPUT);
  pinMode(_echo,INPUT);
  _servo.attach(servo);
}

/**
 * It performs the calculation of the distance (cm) by receiving the time 
 * that the sound wave has lasted.
 * @param int time
 */
long DistanceSensor::calculateDistance(int time){
  float waveLength = 0.034;
  long distance = time * waveLength/ 2;
  return distance;
}

/**
 * Writes a value to the servo, controlling the shaft accordingly.
 * @param int angle
 */
void DistanceSensor::moveServo(int angle){
  if(angle < 0 || angle > 180)
    return;
  _servo.write(angle);
}

/**
 * Sensor main routine. Check if there is an object in a range of 
 * distance, and if there is it activates a servo.
 */
void DistanceSensor::run(struct pt *pt){
  PT_BEGIN(pt);
  static long t = 0;
  long time = 0;
  int distance = 0;

  while(true){
    // Trigger pulse
    digitalWrite(_trig, HIGH);
    t = millis();
    PT_WAIT_WHILE(pt,((millis()-t) < 200));
    digitalWrite(_trig, LOW);
    // Time taken by pulse to leave and return back
    time = pulseIn(_echo, HIGH);
    
    // Check if there is an object at the desired distance
    distance = calculateDistance(time);
    if(distance < 100){
      moveServo(90);
    } else{
      moveServo(0);
    }
    PT_YIELD(pt);
  }
  PT_END(pt);
}

