#ifndef temperaturesensor_h
#define temperaturesensor_h

#include "Arduino.h"
#include <SimpleDHT.h>
#include <pt.h>

/**
 * DHT11 Humidity and temperature sensor handler.
 */
class Temperature{
  private:
    int _tmp;
    int _actuator;
    int _tmpLimit;
    
    void turnOn();
    void turnOff();

  public:
    Temperature(int tmpPin, int actuatorPin);
    void run(struct pt *pt);
    void setTemperatureLimit(int limit);
};

#endif
