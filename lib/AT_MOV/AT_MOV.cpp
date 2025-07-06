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
  _car->stop();
  delay(200);

  if (random(0, 2) == 0) {
    _car->turnLeft();
    showDirection(TURN_LEFT);
    Serial.println("Turning left to avoid obstacle.");
  } else {
    _car->turnRight();
    showDirection(TURN_RIGHT);
    Serial.println("Turning right to avoid obstacle.");
  }

  delay(400); // Turn for a short while
  _car->stop();
  delay(200);
}

void AT_MOV::runAutonomous(int safeDistance, int speed, int duration) {
  setSpeed(speed);
  showDirection(MOVE_FORWARD);
  Serial.println("Starting moving in forward direction...");
  delay(1000); // Initial delay to start moving
  _car->forward();

  for(int i = 0; i < duration;  i++) { // Run for a limited time
    int distance = _vlx->getDistance();
    Serial.print("Distance: ");
    Serial.println(distance);

    if (distance <= safeDistance) {
      showDirection(MOVE_STOP);
      Serial.println("Obstacle detected, stopping car.");
      _car->stop();
      avoidObstacle();
      Serial.println("Starting moving in forward direction...");
      delay(1000);
      _car->forward();  // Resume after avoiding
    }

    delay(50);
  }
  _car->stop();
  showDirection(MOVE_STOP);
  Serial.println("Autonomous run completed, car stopped.");
}
