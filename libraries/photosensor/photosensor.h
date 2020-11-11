#ifndef photosensor_h
#define photosensor_h

#include "Arduino.h"

/**
 * Photo Sensor is a library that wraps the operation of the 
 * LDR sensor, for easy use.
 */
class Photosensor{
    
  private:
    int _ldr;                 // the pin that the sensor is atteched to
    int _led;                 // the pin that the LED is atteched to
    int _edgeValue = 200;     // edge value to turn on LED
    int _period = 1000;       // delay time period
    unsigned long t_ps = 0;   // current time measure

    int readSensor();
    void turnOn();
    void turnOff();
    
  public:
    Photosensor(int ldr_pin, int actuator_pin);
    void run();
    void setEdgeValue(int value);

    
};

#endif
