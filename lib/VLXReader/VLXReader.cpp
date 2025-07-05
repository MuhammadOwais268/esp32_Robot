#include "VLXReader.h"

VLXReader::VLXReader() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}

void VLXReader::begin() {
  Wire.begin();

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // OLED I2C address is usually 0x3C
    Serial.println(F("SSD1306 allocation failed"));
    while (1);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("VLXReader Ready");
  display.display();
  delay(1000);
  display.clearDisplay();

  // Initialize VL53L0X
  sensor.setTimeout(500);
  if (!sensor.init()) {
    Serial.println("Failed to detect and initialize VL53L0X!");
    display.print("Sensor Error");
    display.display();
    while (1);
  }
  sensor.startContinuous();
}
int VLXReader::getDistance(){
  int distance = sensor.readRangeContinuousMillimeters();
  return distance;
}
//Initializing battery Bar
void VLXReader::displayBatteryBar(int distance) {
  distance = constrain(distance, 100, 500);
  int blocks = map(distance, 500, 100, 0, 5);
  blocks = constrain(blocks, 0, 5);

  display.clearDisplay();

  display.setCursor(0, 0);
  display.print("Distance: ");
  display.print(distance);
  display.println(" mm");

  display.setCursor(0, 16);
  display.println("Battery Level:");

  // Draw battery outline
  int x = 20;
  int y = 30;
  int w = 80;
  int h = 20;
  display.drawRect(x, y, w, h, SSD1306_WHITE);
  display.drawRect(x + w, y + 5, 4, 10, SSD1306_WHITE);

  // Draw battery cells
  int cellW = (w - 10) / 5;
  for (int i = 0; i < blocks; i++) {
    display.fillRect(x + 5 + i * cellW, y + 4, cellW - 2, h - 8, SSD1306_WHITE);
  }

  display.display();
}

Adafruit_SSD1306& VLXReader::getDisplay() {
    return display;
}


void VLXReader::readAndPrint() {
  int distance = sensor.readRangeContinuousMillimeters();

  display.clearDisplay();
  display.setCursor(0, 0);

  if (sensor.timeoutOccurred()) {
    Serial.println("TIMEOUT");
    display.print("TIMEOUT");
  } else {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" mm");

    display.print("Distance: ");
    display.print(distance);
    display.println(" mm");
  }

  display.display();
}
