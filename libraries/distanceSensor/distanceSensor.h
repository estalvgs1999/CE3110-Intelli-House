#ifndef distancesensor_h
#define distancesensor_h

#include "Arduino.h"
#include <Servo.h>

/**
 * Library that allows the management of the hc-sr04 ultrasonic sensor 
 * as a distance sensor.
 */
class DistanceSensor{

  private:
    int _trig;
    int _echo;
    Servo _servo;
    
    void moveServo(int angle);
    void startTimer();
    void isTimerReady(int time);
    long calculateDistance(int time);

  public:
    DistanceSensor(int trigPin, int echoPin, int servo);
    void run();
};

#endif
