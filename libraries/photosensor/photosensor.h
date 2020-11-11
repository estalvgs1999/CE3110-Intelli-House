#ifndef photosensor_h
#define photosensor_h

#include "Arduino.h"

/**
 * Photo Sensor is a library that wraps the operation of the 
 * LDR sensor, for easy use.
 */
class Photosensor{
    
  private:
    int _ldr;
    int _actuator;
    int _edgeValue = 200;

    int readSensor();
    void turnOn();
    void turnOff();
    
  public:
    Photosensor(int ldr_pin, int actuator_pin);
    void run();
    void setEdgeValue(int value);

    
};

#endif
