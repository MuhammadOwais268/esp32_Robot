#pragma once
#include <Arduino.h>

enum CarDirection {
    STOPPED,
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Car {
public:
    Car(int in1, int in2, int in3, int in4, int ena = -1, int enb = -1);

    void begin();
    void forward(int speed = -1);
    void backward(int speed = -1);
    void turnLeft(int speed = -1);
    void turnRight(int speed = -1);
    void stop();

    void setSpeed(int speed);
    void setMotorSpeeds(int leftSpeed, int rightSpeed);
    int getSpeed() const;
    CarDirection getDirection() const;

    void brake();
    void coast();

private:
    const int _in1, _in2, _in3, _in4;
    const int _ena, _enb;
    int _currentSpeed;
    CarDirection _direction;

    void _setMotor(bool a1, bool a2, bool b1, bool b2);
    void _applyPWM();

    // ✅ Add unique PWM channels
    const int _enaChannel = 0;  // For ENA (left motor)
    const int _enbChannel = 1;  // For ENB (right motor)
};
