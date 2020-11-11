#include "distanceSensor.h"

/**
 * Constructor
 * @param int trigPin
 * @param int echoPin
 */
DistanceSensor::DistanceSensor(int trigPin, int echoPin){
  _trig = trigPin;
  _echo = echoPin;

  pinMode(_trig,OUTPUT);
  pinMode(_echo,INPUT);
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
 * Sensor main routine. Check if there is an object in a range of 
 * distance, and if there is it activates a servo.
 */
bool DistanceSensor::run(){
    // Clears the trigPin condition
  digitalWrite(_trig, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trig, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  _time = pulseIn(_echo, HIGH);
  _distance = calculateDistance(_time);
  
  delay(100);

  return _distance < _limit;
}

