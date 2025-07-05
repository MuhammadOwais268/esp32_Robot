// MOV_TRACK.cpp
#include "MOV_TRACK.h"

MOV_TRACK::MOV_TRACK(VLXReader &reader) {
  vlx = &reader;
}

void MOV_TRACK::begin() {
  // Nothing needed for now
}

String MOV_TRACK::getMoveName(CarMove move) {
  switch (move) {
    case MOVE_FORWARD: return "Forward";
    case MOVE_BACKWARD: return "Backward";
    case TURN_LEFT: return "Left";
    case TURN_RIGHT: return "Right";
    case MOVE_STOP: return "Stop";
    default: return "Unknown";
  }
}

void MOV_TRACK::showDirection(CarMove move) {
  Adafruit_SSD1306& display = vlx->getDisplay(); // getter in VLXReader
  display.clearDisplay();

  // Display move name
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Move: ");
  display.println(getMoveName(move));

  // Draw direction arrow
  int cx = SCREEN_WIDTH / 2;
  int cy = SCREEN_HEIGHT / 2;

  switch (move) {
    case MOVE_FORWARD:
      display.fillTriangle(cx, cy - 10, cx - 5, cy, cx + 5, cy, SSD1306_WHITE);
      break;
    case MOVE_BACKWARD:
      display.fillTriangle(cx, cy + 10, cx - 5, cy, cx + 5, cy, SSD1306_WHITE);
      break;
    case TURN_LEFT:
      display.fillTriangle(cx - 10, cy, cx, cy - 5, cx, cy + 5, SSD1306_WHITE);
      break;
    case TURN_RIGHT:
      display.fillTriangle(cx + 10, cy, cx, cy - 5, cx, cy + 5, SSD1306_WHITE);
      break;
    case MOVE_STOP:
      display.setCursor(cx - 10, cy);
      display.print("STOP");
      break;
  }

  display.display();
}
