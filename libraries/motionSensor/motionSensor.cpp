#include "motionSensor.h"

/**
 * Constructor
 * @param int pirPin
 * @param int ledPin 
 */
MotionSensor::MotionSensor(int pirPin, int ledPin){
  _pir = pirPin;
  _led = ledPin;
  pinMode(_pir, INPUT);
  pinMode(_led, OUTPUT);
}

// Actuator events, turn digital output on and off
void MotionSensor::turnOn(){
  digitalWrite(_led, HIGH);
}

void MotionSensor::turnOff(){
  digitalWrite(_led, LOW);
}

/**
 * Main routine controller, reads sensor and turns 
 * on actuator if lecture is HIGH.
 */
void MotionSensor::run(){
  _val = digitalRead(_pir);

  turnOff();
  if(_val == HIGH)
      turnOn();

  if(millis() > t_ms + _period){
    t_ms = millis();
  }
}

