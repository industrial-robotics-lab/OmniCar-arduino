#include "Arduino.h"
#include "Motor.h"

Motor::Motor(int number) {
  motor = new AF_DCMotor(number);
}
Motor::~Motor() { delete motor; }

void Motor::setValue(int value) {
  int allowedValue = constrain(value, -255, 255);
  if (abs(allowedValue) < 50) allowedValue = 0;
  if (allowedValue == 0) {
    motor->run(RELEASE);
  } else if (allowedValue > 0) {
    motor->run(FORWARD);
    motor->setSpeed(abs(allowedValue));
  } else {
    motor->run(BACKWARD);
    motor->setSpeed(abs(allowedValue));
  }
}