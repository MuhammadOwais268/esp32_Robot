#include <Arduino.h>
#include <unity.h>
#include "Car.h"

// Define pins based on your hardware
#define IN1 5
#define IN2 18
#define IN3 21
#define IN4 14
#define ENA 25
#define ENB 26

Car car(IN1, IN2, IN3, IN4, ENA, ENB);

void test_backward_motor_response() {
    car.begin();
    Serial.println("Testing backward movement...");

    car.backward(200);  // move backward at medium speed
    delay(1000);        // allow motors to run for a second

    CarDirection dir = car.getDirection();
    TEST_ASSERT_EQUAL(BACKWARD, dir);

    Serial.println("Did both motors spin backward?");
    Serial.println("Observe the physical robot. Left motor (ENA) must spin.");
    
    car.stop();
    delay(500);
}

void setup() {
    delay(2000); // Wait for serial connection
    UNITY_BEGIN();
    RUN_TEST(test_backward_motor_response);
    UNITY_END();
}

void loop() {
    // Do nothing
}
