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
  byte temp = 0;
  byte hum = 0;
  SimpleDHT11 sensor(_tmp);

  while(true){
    
    sensor.read(&temp, &hum, NULL);
    if(int(temp) > _tmpLimit){
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
