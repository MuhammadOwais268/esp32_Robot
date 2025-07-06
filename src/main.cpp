#include <Arduino.h>
#include <Car.h>
#include <VLXReader.h>
#include <MOV_TRACK.h>
#include <AT_MOV.h>

// Define motor and sensor setup
Car car(5, 18, 21, 33, 25, 26);  // IN1, IN2, IN3, IN4, ENA, ENB
VLXReader vlx;
MOV_TRACK tracker(vlx);
AT_MOV AT(car, vlx);

// Distance threshold in mm
const int OBSTACLE_DISTANCE = 200;

void setup() {
  Serial.begin(9600);
  car.begin();
  vlx.begin();
  tracker.begin();
   AT.begin();
}

void loop() {

  AT.runAutonomous(OBSTACLE_DISTANCE, 150, 10); // Safe distance and speed
  // Add a small delay to avoid flooding the serial output
   delay(100);

}