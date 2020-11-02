#include "distanceSensor.h"
#include "Arduino.h"

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
  _servo.attacho(servo)
}

/**
 * It performs the calculation of the distance by receiving the time 
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
    throw;
  _servo.write(angle);
}



