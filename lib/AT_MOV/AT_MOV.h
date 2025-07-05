// AT_MOV.h
#ifndef AT_MOV_H
#define AT_MOV_H

#include <Arduino.h>
#include "Car.h"
#include "VLXReader.h"

class AT_MOV {
public:
  AT_MOV(Car &car, VLXReader &vlx);
  void begin();

  void runAutonomous(int safeDistance, int speed);

private:
  Car* _car;
  VLXReader* _vlx;

  void avoidObstacle(); // left or right randomly
  void setSpeed(int speed);
};

#endif
