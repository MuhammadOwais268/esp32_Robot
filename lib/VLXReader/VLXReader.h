#ifndef VLXREADER_H
#define VLXREADER_H

#include <Wire.h>
#include <VL53L0X.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1

class VLXReader {
  public:
    VLXReader();
    void begin();
    void readAndPrint();
    int getDistance();
    void displayBatteryBar(int distance);
    Adafruit_SSD1306& getDisplay();

    
  private:
    VL53L0X sensor;
    Adafruit_SSD1306 display;
};

#endif
