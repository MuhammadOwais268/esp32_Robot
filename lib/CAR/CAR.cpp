// Car.cpp
#include "Car.h"

// Constructor: Initialize motor pins (ENA/ENB optional)
Car::Car(int in1, int in2, int in3, int in4, int ena, int enb) 
    : _in1(in1), _in2(in2), _in3(in3), _in4(in4),
      _ena(ena), _enb(enb), _currentSpeed(255) {}

// Initialize pins
void Car::begin() {
    pinMode(_in1, OUTPUT);
    pinMode(_in2, OUTPUT);
    pinMode(_in3, OUTPUT);
    pinMode(_in4, OUTPUT);
    
    if (_ena >= 0) pinMode(_ena, OUTPUT);
    if (_enb >= 0) pinMode(_enb, OUTPUT);
    
    stop();  // Safety first
}

// Private motor control core
void Car::_setMotor(bool a1, bool a2, bool b1, bool b2) {
    digitalWrite(_in1, a1);
    digitalWrite(_in2, a2);
    digitalWrite(_in3, b1);
    digitalWrite(_in4, b2);
    
    // Apply PWM if enable pins are configured
    if (_ena >= 0) analogWrite(_ena, _currentSpeed);
    if (_enb >= 0) analogWrite(_enb, _currentSpeed);
}

// Movement functions ----------------------------
void Car::forward(int speed) {
    setSpeed(speed);
    _setMotor(HIGH, LOW, HIGH, LOW);
}

void Car::backward(int speed) {
    setSpeed(speed);
    _setMotor(LOW, HIGH, LOW, HIGH);
}

void Car::turnLeft(int speed) {
    setSpeed(speed);
    _setMotor(LOW, HIGH, HIGH, LOW);  // Pivot turn
}

void Car::turnRight(int speed) {
    setSpeed(speed);
    _setMotor(HIGH, LOW, LOW, HIGH);  // Pivot turn
}

void Car::stop() {
    _setMotor(LOW, LOW, LOW, LOW);  // Brake mode
}

// Speed control --------------------------------
void Car::setSpeed(int speed) {
    _currentSpeed = constrain(speed, 0, 255);
}

int Car::getSpeed() const {
    return _currentSpeed;
}

// Advanced functions --------------------------
void Car::brake() {
    _setMotor(LOW, LOW, LOW, LOW);  // Active brake
    delay(50);  // Braking pulse
}

void Car::coast() {
    _setMotor(HIGH, HIGH, HIGH, HIGH);  // High impedance
}