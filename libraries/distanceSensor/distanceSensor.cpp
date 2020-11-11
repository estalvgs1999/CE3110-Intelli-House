#include "distanceSensor.h"

unsigned long t = 0;
int timerTriggerHigh = 10;
int timerLowHIGH = 2;
int  timerServo = 5000;  //  5 s

// States ofan ultrasonic sensor
enum SensorStates {
  TRIG_LOW,
  TRIG_HIGH,
  ECHO_HIGH,
  SERVO_ON
};

SensorStates _sensorState = TRIG_LOW;

/**
 *
 */
void DistanceSensor::startTimer(){
  t = millis();
}

/**
 *
 */
bool DistanceSensor::isTimerReady(int time){
  return (millis() - t) < time;
}


/**
 * Constructor
 * @param int trigPin
 * @param int echoPin
 * @param int servo
 */
DistanceSensor::DistanceSensor(int trigPin, int echoPin, int servo){
  _trig = trigPin;
  _echo = echoPin;

  pinMode(_trig,OUTPUT);
  pinMode(_echo,INPUT);
  _servo.attach(servo);
  Serial.begin(9600);
}

/**
 * It performs the calculation of the distance (cm) by receiving the time 
 * that the sound wave has lasted.
 * @param int time
 */
long DistanceSensor::calculateDistance(int time){
  float waveLength = 0.034;
  long distance = time * waveLength/ 2;
  return distance;
}

/**
 * Writes a value to the servo, controlling the shaft accordingly.
 * @param int angle
 */
void DistanceSensor::moveServo(int angle){
  if(angle < 0 || angle > 180)
    return;
  _servo.write(angle);
}

/**
 * Sensor main routine. Check if there is an object in a range of 
 * distance, and if there is it activates a servo.
 */
void DistanceSensor::run(){
  switch (switch_on)
  {
    // Start with LOW pulse to ensure a clean HIGH pulse
    case TRIG_LOW:
      digitalWrite(_trig, LOW);
      startTimer();
      if(isTimerReady(timerLowHIGH))
        _sensorState = TRIG_HIGH;
      break;

    // Triggered a HIGH pulse of 10 microseconds
    case TRIG_HIGH:
      digitalWrite(_trig, HIGH);
      startTimer();
      if (isTimerReady(timerTriggerHigh))
        _sensorState = ECHO_HIGH;
      break;    
    
    // Measures the time that ping took to return to the receiver
    case ECHO_HIGH:
      digitalWrite(trigPin, LOW);
      timeDuration = pulseIn(echoPin, HIGH);
      /*
           distance = time * speed of sound
           speed of sound is 340 m/s => 0.034 cm/us
      */
      int distance = calculateDistance(timeDuration);
      Serial.print("Distance measured is: ");
      Serial.print(distance);
      Serial.println(" cm");
      
      if(distance < _limit)
        _sensorState = SERVO_ON
      else
        _sensorState = TRIG_LOW;
    
    // Move servo
    case SERVO_ON:
      moveServo(90);
      startTimer();
      if(isTimerReady(timerServo)){
        moveServo(0);
        _sensorState = TRIG_LOW;
      }
      break;
    
    default:
      break;
  }
}

