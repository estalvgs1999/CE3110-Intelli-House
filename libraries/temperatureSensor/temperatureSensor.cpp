#include "temperatureSensor.h"

/**
 * Constructor
 * @param int tmpPin
 * @param int actuatorPin
 */
Temperature::Temperature(int tmpPin, int actuatorPin){
  _pin = tmpPin;
  _actuator = actuatorPin;
  pinMode(_actuator,OUTPUT);
}

/**
 * Turns on or off an actuator, it can be a control 
 * for a motor or a relay
 */
void Temperature::turnOn(){
  digitalWrite(_actuator,HIGH);
}

void Temperature::turnOff(){
  digitalWrite(_actuator,LOW);
}

/**
 * Allows you to customize the limit temperature value
 * @param int newLimit
 */
void Temperature::setTemperatureLimit(int newLimit){
  _tmpLimit = newLimit;
}

/**
 * Sensor main routine. Check the temperature periodically, if a
 * read value exceeds the limit temperature an actuator will turn 
 * on to activate a cooling mechanism.
 */
void Temperature::run(){
  SimpleDHT11 _sensor(_pin);
    
  _sensor.read(&_tmp, &_hum, NULL);
  Serial.println(int(_tmp));
  Serial.println(int(_hum));

  if(int(_hum) >= 80){
    turnOn();
  }else{
    turnOff();
  }

  delay(200);
}
