#ifndef AT_MOV_H
#define AT_MOV_H

#include <Arduino.h>
#include "Car.h"
#include "VLXReader.h"
#include "MOV_TRACK.h"

class AT_MOV {
public:
  AT_MOV(Car &car, VLXReader &vlx);
  void begin();
  void runAutonomous(int safeDistance, int speed, int duration = 10); // Added duration parameter

private:
  Car* _car;
  VLXReader* _vlx;
  MOV_TRACK* _tracker;  // 💡 Add a pointer to MOV_TRACK

  void avoidObstacle();
  void setSpeed(int speed);
  void showDirection(CarMove move);     // 💡 Declare display helper
  String getMoveName(CarMove move);     // 💡 Declare name utility
};

#endif
