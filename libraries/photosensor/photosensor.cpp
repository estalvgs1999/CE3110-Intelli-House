#include "photosensor.h"

int _period = 1000;
unsigned long t = 0;

/**
 * Constructor
 * @param int ldr_pin
 * @param int actuator_pin
 */
Photosensor::Photosensor(int ldr_pin, int actuator_pin){
  _ldr = ldr_pin;
  _actuator = actuator_pin;
  pinMode(_actuator, OUTPUT);
}

/**
 * Set a new value for the reading range
 * @param int value
 */
void Photosensor::setEdgeValue(int value){
  _edgeValue = value;
}

/**
 * Take a reading from the LDR sensor. 
 * @returns an integer between 0 and 1023
 */
int Photosensor::readSensor(){
  int value = analogRead(_ldr);
  return value;
}

// Actuator events, turn digital output on and off
void Photosensor::turnOn(){
  digitalWrite(_actuator, HIGH);
}

void Photosensor::turnOff(){
  digitalWrite(_actuator, LOW);
}

/**
 * Main routine controller, reads sensor and turns 
 * on actuator if value is less than allowable value.
 */
void Photosensor::run(){
  turnOff();
  int value = readSensor();
  if(value < _edgeValue)
    turnOn();
  
  // delay
  if(millis() > t + _period){
    t = millis();
  }
}
