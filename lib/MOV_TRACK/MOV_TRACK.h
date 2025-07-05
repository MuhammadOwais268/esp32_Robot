// MOV_TRACK.h
#ifndef MOV_TRACK_H
#define MOV_TRACK_H

#include <Arduino.h>
#include "VLXReader.h"
#include "Car.h"

enum CarMove {
  MOVE_FORWARD,
  MOVE_BACKWARD,
  TURN_LEFT,
  TURN_RIGHT,
  MOVE_STOP
};

class MOV_TRACK {
public:
  MOV_TRACK(VLXReader &vlx);
  void begin();
  void showDirection(CarMove move);
  String getMoveName(CarMove move);
 

private:
  VLXReader* vlx;
};

#endif
