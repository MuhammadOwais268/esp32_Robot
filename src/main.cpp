#include <Arduino.h>
#include "Car.h"
#include "VLXReader.h"
#include "MOV_TRACK.h"

// Define motor and sensor setup
Car car(5, 18, 21, 33, 25, 26);  // IN1, IN2, IN3, IN4, ENA, ENB
VLXReader vlx;
MOV_TRACK tracker(vlx);

// Distance threshold in mm
const int OBSTACLE_DISTANCE = 200;

void setup() {
  Serial.begin(9600);
  car.begin();
  vlx.begin();
  tracker.begin();
}

void loop() {
  int distance = vlx.getDistance();
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > OBSTACLE_DISTANCE) {
    // Move forward
    car.forward();
    tracker.showDirection(MOVE_FORWARD);
  } else {
    // Obstacle detected
    car.stop();
    tracker.showDirection(MOVE_STOP);
    delay(500);

    // Turn randomly (left or right)
    if (random(0, 2) == 0) {
      car.turnLeft();
      tracker.showDirection(TURN_LEFT);
    } else {
      car.turnRight();
      tracker.showDirection(TURN_RIGHT);
    }

    delay(600);  // Turn duration

    // Move forward again
    car.forward();
    tracker.showDirection(MOVE_FORWARD);
    delay(800);  // Give space to escape obstacle
  }

  delay(100);  // Sensor refresh delay
}
