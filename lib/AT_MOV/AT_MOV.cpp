// AT_MOV.cpp
#include <AT_MOV.h>

AT_MOV::AT_MOV(Car &car, VLXReader &vlx) {
  _car = &car;
  _vlx = &vlx;
  _tracker = new MOV_TRACK(vlx);
}
void AT_MOV::showDirection(CarMove move) {
  if (_tracker) {
    _tracker->showDirection(move);
  }
}

String AT_MOV::getMoveName(CarMove move) {
  if (_tracker) {
    return _tracker->getMoveName(move);
  }
  return "Unknown";
}


void AT_MOV::begin() {
  // Reserved for future setup
}

void AT_MOV::setSpeed(int speed) {
  speed = constrain(speed, 0, 255);
  analogWrite(25, speed); // Use actual ENA pin
  analogWrite(26, speed); // Use actual ENB pin
}

void AT_MOV::avoidObstacle() {
  Serial.println("Obstacle detected, avoiding...");
  showDirection(MOVE_BACKWARD);
  _car->backward(100); // Move backward to avoid obstacle
  delay(1000);
  _car->stop();
   delay(500);
  _car->turnLeft(80); // Turn left to avoid obstacle
  showDirection(TURN_RIGHT);
  Serial.println("Avoiding obstacle by turning right...");
   delay(500); // Turn for a short while
  _car->stop();
  delay(1000);
}

void AT_MOV::runAutonomous(int safeDistance, int speed, int duration) {
  setSpeed(speed);
  showDirection(MOVE_FORWARD);
  Serial.println("Starting moving in forward direction...");
  _car->forward(speed);

  for(int i = 0; i < duration;  i++) { // Run for a limited time
    int distance = _vlx->getDistance();
    Serial.print("Distance: ");
    Serial.println(distance);

    if (distance <= safeDistance) {
      showDirection(MOVE_STOP);
      Serial.println("Obstacle detected, stopping car.");
      _car->stop();
      delay(1000); // Wait for a moment before avoiding
      avoidObstacle();
      Serial.println("Starting moving in forward direction...");
      _car->forward();
      showDirection(MOVE_FORWARD);  // Resume after avoiding
    }

    delay(50);
  }
  _car->stop();
  showDirection(MOVE_STOP);
  Serial.println("Autonomous run completed, car stopped.");
}
