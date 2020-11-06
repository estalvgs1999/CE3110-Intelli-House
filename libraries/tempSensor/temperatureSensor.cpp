#include "temperatureSensor.h"

/**
 *
 */
Temperature::Temperature(int tmpPin, int actuatorPin){
  _tmp = tmpPin;
  _actuator = actuatorPin;
  pinMode(_actuator,OUTPUT);
}

/**
 *
 */
int Temperature::readSensor(){
  int value = _sensor.read(_tmp);
  return value.temperature;
}

/**
 *
 */
void Temperature::turnOn(){
  digitalWrite(_actuator,HIGH);
}

void Temperature::turnOff(){
  digitalWrite(_actuator,LOW);
}

/**
 *
 */
void Temperature::setTemperatureLimit(int limit){
  _tmpLimit = limit;
}

/**
 *
 */
void Temperature::run(struct pt *pt){
  PT_BEGIN(pt);
  static long t = 0;

  while(true){
    if(readSensor() > _tmpLimit){
      turnOn();
    }else{
      turnOff();
    }

    t = millis();
    PT_WAIT_WHILE(pt,((millis()-t) < 2000));
    
    PT_YIELD(pt);
  }
  PT_END(pt);
}
