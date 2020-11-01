// Intelli-House
// by David Alvarado & Erick Cordero

#include <photosensor.h>
#include <pt.h>

struct pt thread1;

Photosensor photosensor(A0,5);

void setup() {
  PT_INIT(&thread1);
}

void loop() {
  // put your main code here, to run repeatedly:
  photosensor.run(&thread1);
}
