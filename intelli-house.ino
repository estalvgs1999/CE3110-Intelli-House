// Intelli-House
// by David Alvarado & Erick Cordero

#include <photosensor.h>


Photosensor photosensor(A0,5);

void setup() {

}

void loop() {
  // put your main code here, to run repeatedly:
  photosensor.execute();
}
