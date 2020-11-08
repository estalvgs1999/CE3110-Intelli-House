#include "temperatureSensor.h"

/**
 * Constructor
 * @param int tmpPin
 * @param int actuatorPin
 */
Temperature::Temperature(int tmpPin, int actuatorPin){
  _tmp = tmpPin;
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
