#include "photosensor.h"

/**
 * Constructor
 * @param int ldr_pin
 * @param int led_pin
 */
Photosensor::Photosensor(int ldr_pin, int led_pin){
  _ldr = ldr_pin;
  _led = led_pin;
  pinMode(_led, OUTPUT);
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

// led events, turn digital output on and off
void Photosensor::turnOn(){
  digitalWrite(_led, HIGH);
}

void Photosensor::turnOff(){
  digitalWrite(_led, LOW);
}

/**
 * Main routine controller, reads sensor and turns 
 * on led if value is less than allowable value.
 */
void Photosensor::run(){
  turnOff();
  int value = readSensor();
  if(value < _edgeValue)
    turnOn();
  
  // delay
  if(millis() > t_ps + _period){
    t_ps = millis();
  }
}
