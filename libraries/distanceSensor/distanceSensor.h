#ifndef distancesensor_h
#define distancesensor_h

#include "Arduino.h"
#include "Servo.h"

/**
 * Library that allows the management of the hc-sr04 ultrasonic sensor 
 * as a distance sensor.
 */
class DistanceSensor{

  private:
    int _trig;
    int _echo;
    int _servoPin;
    Servo servo;

  public:
    DistanceSensor(int trigPin, int echoPin, int servo);
    int calculateDistance();

};

#endif
