#include "photosensor.h"

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
void Photosensor::run(struct pt *pt){
  PT_BEGIN(pt);
  static long t = 0;

  while(true){
    int value = readSensor();
    t = millis();
    PT_WAIT_WHILE(pt,((millis()-t) < 100));

    if(value < _edgeValue){
      turnOn();
    }else{
      turnOff();
    }
    PT_YIELD(pt);
  }
  PT_END(pt);
}
