#ifndef temperature_sensor.h
#define temperature_sensor

#include "Arduino.h"
#include <dht11.h>
#include <pt.h>

/**
 * DHT11 Humidity and temperature sensor handler.
 */
class Temperature{
  private:
    int _tpm;
    int _actuator;
    int _tmpLimit;
    dht11 _sensor;
    
    int readSensor();
    void turnOn();
    void turnOff();

  public:
    Temperature(int tmpPin, int actuatorPin);
    void run(struct pt *pt);
    void setTemperatureLimit(int limit);
};

#endif
