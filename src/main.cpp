#include <Arduino.h>
#include <Wire.h>
#include "Car.h"
#include "VLXReader.h"
#include "MOV_TRACK.h"
#include "TRACK_OBJ.h"

// === Motor Pins ===
#define IN1 14
#define IN2 18
#define IN3 12
#define IN4 5
#define ENA 25
#define ENB 26

Car car(IN1, IN2, IN3, IN4, ENA, ENB);
MOV_TRACK oledRadar;
TRACK_OBJ tracker(car, oledRadar);

// === VL53L0X Front Sensor Only ===
VLXReader front; // Use default address or reassign manually

void setup() {
  Serial.begin(9600);
  Wire.begin();

  car.begin();
  oledRadar.begin();

  front.begin();  // Only use 1 sensor
  tracker.attachSensorFront(&front);
  tracker.begin();

  Serial.println("Single-sensor object tracking started!");
}

void loop() {
  tracker.trackObject(100, 400); // Will use only front sensor
  delay(100);
}
