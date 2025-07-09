// MOV_TRACK.cpp
#include "MOV_TRACK.h"

MOV_TRACK::MOV_TRACK() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1) {}

void MOV_TRACK::begin() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED init failed"));
    return;
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();
}

void MOV_TRACK::drawRadarGrid() {
  display.clearDisplay();
  display.drawCircle(64, 32, 30, SSD1306_WHITE); // Outer ring
  display.drawCircle(64, 32, 20, SSD1306_WHITE); // Middle ring
  display.drawCircle(64, 32, 10, SSD1306_WHITE); // Inner ring
  display.drawLine(64, 0, 64, 64, SSD1306_WHITE); // Vertical
  display.drawLine(0, 32, 128, 32, SSD1306_WHITE); // Horizontal
}

void MOV_TRACK::showRadar(int front, int back, int left, int right) {
  drawRadarGrid();

  // Map distance (max 300mm) to radius
  int f = map(constrain(front, 0, 300), 0, 300, 2, 30);
  int b = map(constrain(back, 0, 300), 0, 300, 2, 30);
  int l = map(constrain(left, 0, 300), 0, 300, 2, 30);
  int r = map(constrain(right, 0, 300), 0, 300, 2, 30);

  // Dots: front (top), back (bottom), left, right
  display.fillCircle(64, 32 - f, 2, SSD1306_WHITE); // Front
  display.fillCircle(64, 32 + b, 2, SSD1306_WHITE); // Back
  display.fillCircle(64 - l, 32, 2, SSD1306_WHITE); // Left
  display.fillCircle(64 + r, 32, 2, SSD1306_WHITE); // Right

  display.display();
}

void MOV_TRACK::showDirection(CarDirection dir) {
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.fillRect(0, 0, 60, 10, SSD1306_BLACK);

  switch (dir) {
    case FORWARD: display.print("FWD"); break;
    case BACKWARD: display.print("BACK"); break;
    case LEFT: display.print("LEFT"); break;
    case RIGHT: display.print("RIGHT"); break;
    case STOPPED: default: display.print("STOP"); break;
  }

  display.display();
}