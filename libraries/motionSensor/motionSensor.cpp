#include "motionSensor.h"

/**
 *
 */
MotionSensor::MotionSensor(int pirPin, int ledPin){
  _pir = pirPin;
  _led = ledPin;
  pinMode(_pir,INPUT);
  pinMode(_led,OUTPUT);
}

/**
 *
 */
void MotionSensor::run(struct pt *pt){
  PT_BEGIN(pt);
  static long  t = 0;
  
  while(true){
    pirState = (digitalRead(_pir) == HIGH)? true: false;
    
    if(pirState)
      digitalWrite(_led,HIGH);
    else
      digitalWrite(_led,LOW);
    
    // A little delay
    t = millis();
    PT_WAIT_WHILE(pt,((millis()-t) < 100));
    
    PT_YIELD(pt);
  }
  PT_END(pt);
}

