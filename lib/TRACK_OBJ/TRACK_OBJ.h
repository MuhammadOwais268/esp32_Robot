// TRACK_OBJ.h
#pragma once
#include <Arduino.h>
#include "Car.h"
#include "VLXReader.h"
#include "MOV_TRACK.h"

class TRACK_OBJ {
public:
  TRACK_OBJ(Car &car, MOV_TRACK &display);

  void attachSensorFront(VLXReader* reader);
  void attachSensorBack(VLXReader* reader);
  void attachSensorLeft(VLXReader* reader);
  void attachSensorRight(VLXReader* reader);

  void begin();
  void trackObject(int minRange = 100, int maxRange = 400);

private:
  Car* _car;
  MOV_TRACK* _display;

  VLXReader* _front = nullptr;
  VLXReader* _back = nullptr;
  VLXReader* _left = nullptr;
  VLXReader* _right = nullptr;

  int getDistance(VLXReader* sensor);
};

