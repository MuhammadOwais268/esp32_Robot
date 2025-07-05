// Car.h
#pragma once
#include <Arduino.h>

class Car {
public:
    // Constructor with motor control pins
    Car(int in1, int in2, int in3, int in4, int ena = -1, int enb = -1);
    
    // Initialization
    void begin();
    
    // Movement functions (with optional speed)
    void forward(int speed = 255);
    void backward(int speed = 255);
    void turnLeft(int speed = 255);
    void turnRight(int speed = 255);
    void stop();
    
    // Speed control
    void setSpeed(int speed);
    int getSpeed() const;
    
    // Advanced motor control
    void brake();  // Active braking
    void coast();  // Free spin

private:
    // Motor pins
    const int _in1, _in2, _in3, _in4;
    const int _ena, _enb;  // PWM pins (-1 if unused)
    
    // Current speed (0-255)
    int _currentSpeed;
    
    // Core motor control
    void _setMotor(bool a1, bool a2, bool b1, bool b2);
};