#ifndef temperaturesensor_h
#define temperaturesensor_h

#include "Arduino.h"
#include <SimpleDHT.h>

/**
 * DHT11 Humidity and temperature sensor handler.
 */
class Temperature{
  private:
    int _pin;
    int _actuator;
    byte _tmp = 0;
    byte _hum = 0;
    int _tmpLimit = 90;
    
    void turnOn();
    void turnOff();

  public:
    Temperature(int tmpPin, int actuatorPin);
    void run();
    void setTemperatureLimit(int limit);
};

#endif
