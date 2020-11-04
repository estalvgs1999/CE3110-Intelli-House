#ifndef motionsensor_h
#define motionsensor_h

#include "Arduino.h"
#include <pt.h>

/**
 * Library that manages a PIR motion sensor to control 
 * a led as an indicator.
 */
class MotionSensor{
  private:
    int _pir;
    int _led;
    bool pirState = false;

  public:
    MotionSensor(int pirPin, int ledPin);
    void run(struct pt *pt);
};

#endif
