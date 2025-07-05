// AT_MOV.cpp
#include <AT_MOV.h>

AT_MOV::AT_MOV(Car &car, VLXReader &vlx) {
  _car = &car;
  _vlx = &vlx;
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
  } else {
    _car->turnRight();
  }

  delay(400); // Turn for a short while
  _car->stop();
  delay(200);
}

void AT_MOV::runAutonomous(int safeDistance, int speed) {
  setSpeed(speed);
  _car->forward();

  while (true) {
    int distance = _vlx->getDistance();
    Serial.print("Distance: ");
    Serial.println(distance);

    if (distance <= safeDistance) {
      _car->stop();
      avoidObstacle();
      _car->forward();  // Resume after avoiding
    }

    delay(50);
  }
}
