// MOV_TRACK.h
#pragma once
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Car.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

class MOV_TRACK {
public:
  MOV_TRACK();
  void begin();
  void showRadar(int front, int back, int left, int right);
  void showDirection(CarDirection dir);

private:
  Adafruit_SSD1306 display;
  void drawRadarGrid();
};


