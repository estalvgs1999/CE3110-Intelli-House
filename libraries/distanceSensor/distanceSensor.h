#ifndef distancesensor_h
#define distancesensor_h

#include "Arduino.h"

/**
 * Library that allows the management of the hc-sr04 ultrasonic sensor 
 * as a distance sensor.
 */
class DistanceSensor{

  private:
    int _trig;
    int _echo;
    int _limit = 10;
    long _time;
    int _distance;

    long calculateDistance(int time);

  public:
    DistanceSensor(int trigPin, int echoPin);
    bool run();
};

#endif
