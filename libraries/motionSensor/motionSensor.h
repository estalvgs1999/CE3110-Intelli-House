#ifndef motionsensor_h
#define motionsensor_h

#include "Arduino.h"

/**
 * Library that manages a PIR motion sensor to control 
 * a led as an indicator.
 */
class MotionSensor{
  private:
    int _pir;             // the pin that the sensor is atteched to
    int _led;             // the pin that the LED is atteched to
    int _val = 0;         // variable to store the sensor status (value)
    bool _pirState = LOW;  // by default, no motion detected
    int _period = 1000;       // delay time period
    unsigned long t_ms = 0;   // current time measure

    void turnOn();
    void turnOff();

  public:
    MotionSensor(int pirPin, int ledPin);
    void run();
};

#endif
