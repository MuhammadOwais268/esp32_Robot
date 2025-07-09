// TRACK_OBJ.cpp
#include "TRACK_OBJ.h"

TRACK_OBJ::TRACK_OBJ(Car &car, MOV_TRACK &display) : _car(&car), _display(&display) {}

void TRACK_OBJ::attachSensorFront(VLXReader* reader)  { _front  = reader; }
void TRACK_OBJ::attachSensorBack(VLXReader* reader)   { _back   = reader; }
void TRACK_OBJ::attachSensorLeft(VLXReader* reader)   { _left   = reader; }
void TRACK_OBJ::attachSensorRight(VLXReader* reader)  { _right  = reader; }

void TRACK_OBJ::begin() {
  if (_front)  _front->begin();
  if (_back)   _back->begin();
  if (_left)   _left->begin();
  if (_right)  _right->begin();
}

int TRACK_OBJ::getDistance(VLXReader* sensor) {
  return (sensor) ? sensor->getDistance() : 9999;
}

void TRACK_OBJ::trackObject(int minRange, int maxRange) {
  int dF = getDistance(_front);
  int dB = getDistance(_back);
  int dL = getDistance(_left);
  int dR = getDistance(_right);

  // Show on OLED
  if (_display) _display->showRadar(dF, dB, dL, dR);

  // Decide movement
  if (dF >= minRange && dF <= maxRange) {
    _car->forward(80);
    _display->showDirection(FORWARD);
  } else if (dL >= minRange && dL <= maxRange) {
    _car->turnLeft();
    _display->showDirection(LEFT);
  } else if (dR >= minRange && dR <= maxRange) {
    _car->turnRight();
    _display->showDirection(RIGHT);
  } else if (dB >= minRange && dB <= maxRange) {
    _car->backward();
    _display->showDirection(BACKWARD);
  } else {
    _car->stop();
    _display->showDirection(STOPPED);
  }

  delay(300);
  _car->stop();
}
// This function can be called in the main loop to continuously track objects
// Example usage in main loop:
// TRACK_OBJ tracker(car, display); 