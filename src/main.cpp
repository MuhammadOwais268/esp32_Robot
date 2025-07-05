#include <Arduino.h>
#include "Car.h"
#include "VLXReader.h"
#include "AT_MOV.h"

Car car(5, 18, 21, 33, 25, 26);
VLXReader vlx;
AT_MOV mover(car, vlx);

void setup() {
  Serial.begin(9600);
  car.begin();
  vlx.begin();
  mover.begin();

  mover.runAutonomous(100, 150);  // Safe distance: 100 mm, Speed: 150
}

void loop() {
  // runAutonomous has its own loop
}
