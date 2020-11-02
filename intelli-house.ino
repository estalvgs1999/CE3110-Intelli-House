
// Intelli-House
// by David Alvarado & Erick Cordero
#include <distanceSensor.h>
#include <photosensor.h>
#include <pt.h>

struct pt thread1;
struct pt thread2;

Photosensor photosensor(A0,5);
DistanceSensor distance(6,7,10);

void setup() {
  PT_INIT(&thread1);
  PT_INIT(&thread2);
}

void loop() {
  // put your main code here, to run repeatedly:
  photosensor.run(&thread1);
  distance.run(&thread2);
}
