#include "Car.h"

#define DEFAULT_SPEED 150
#define MAX_SPEED 255
#define PWM_FREQ     1000
#define PWM_RES      8  // 8-bit resolution (0–255)

// Constructor
Car::Car(int in1, int in2, int in3, int in4, int ena, int enb)
    : _in1(in1), _in2(in2), _in3(in3), _in4(in4),
      _ena(ena), _enb(enb),
      _currentSpeed(DEFAULT_SPEED),
      _direction(STOPPED) {}

// Setup pins and PWM
void Car::begin() {
    pinMode(_in1, OUTPUT);
    pinMode(_in2, OUTPUT);
    pinMode(_in3, OUTPUT);
    pinMode(_in4, OUTPUT);

    if (_ena >= 0) {
        ledcSetup(_enaChannel, PWM_FREQ, PWM_RES);
        ledcAttachPin(_ena, _enaChannel);
    }

    if (_enb >= 0) {
        ledcSetup(_enbChannel, PWM_FREQ, PWM_RES);
        ledcAttachPin(_enb, _enbChannel);
    }

    stop();
}

// Internal motor set logic
void Car::_setMotor(bool a1, bool a2, bool b1, bool b2) {
    digitalWrite(_in1, a1);
    digitalWrite(_in2, a2);
    digitalWrite(_in3, b1);
    digitalWrite(_in4, b2);
    _applyPWM();
}

// Apply speed to both motors
void Car::_applyPWM() {
    if (_ena >= 0) ledcWrite(_enaChannel, _currentSpeed);
    if (_enb >= 0) ledcWrite(_enbChannel, _currentSpeed);
}

// Movement functions
void Car::forward(int speed) {
    if (speed >= 0) setSpeed(speed);
    _direction = FORWARD;
    _setMotor(HIGH, LOW, HIGH, LOW);
}

void Car::backward(int speed) {
    if (speed >= 0) setSpeed(speed);
    _direction = BACKWARD;
    _setMotor(LOW, HIGH, LOW, HIGH);
}

void Car::turnLeft(int speed) {
    if (speed >= 0) setSpeed(speed);
    _direction = LEFT;
    _setMotor(LOW, HIGH, HIGH, LOW);
}

void Car::turnRight(int speed) {
    if (speed >= 0) setSpeed(speed);
    _direction = RIGHT;
    _setMotor(HIGH, LOW, LOW, HIGH);
}

void Car::stop() {
    _direction = STOPPED;

    // Active brake mode
    digitalWrite(_in1, HIGH);
    digitalWrite(_in2, HIGH);
    digitalWrite(_in3, HIGH);
    digitalWrite(_in4, HIGH);

    // Stop PWM
    if (_ena >= 0) ledcWrite(_enaChannel, 0);
    if (_enb >= 0) ledcWrite(_enbChannel, 0);
}


// Speed functions
void Car::setSpeed(int speed) {
    _currentSpeed = constrain(speed, 0, MAX_SPEED);
}

void Car::setMotorSpeeds(int leftSpeed, int rightSpeed) {
    leftSpeed = constrain(leftSpeed, 0, MAX_SPEED);
    rightSpeed = constrain(rightSpeed, 0, MAX_SPEED);

    if (_ena >= 0) ledcWrite(_enaChannel, leftSpeed);
    if (_enb >= 0) ledcWrite(_enbChannel, rightSpeed);
}

int Car::getSpeed() const {
    return _currentSpeed;
}

CarDirection Car::getDirection() const {
    return _direction;
}

// Brake & Coast
void Car::brake() {
    _direction = STOPPED;
    _setMotor(LOW, LOW, LOW, LOW);
    delay(50);
}

void Car::coast() {
    _direction = STOPPED;
    _setMotor(HIGH, HIGH, HIGH, HIGH);
}
