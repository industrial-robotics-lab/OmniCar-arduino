#include "Arduino.h"
#include "Wheel.h"

Wheel::Wheel(String wheelName, int motorNum, int encPin, int intervalMillis) {
  this->wheelName = wheelName;
  this->motor = new Motor(motorNum);
  this->encoder = new Encoder(encPin, intervalMillis);
  this->pid = new PID(1, 0, 0, 255, 100, intervalMillis/1000.0);
}
Wheel::~Wheel() { 
  delete motor;
  delete encoder;
  delete pid;
}

void Wheel::update() {
  encoder->update();
}

int Wheel::getEncPin() {
  return encoder->pin;
}

float Wheel::getRPM() {
  float rpm = encoder->getRPM();
  if (isForward) {
    return rpm;
  } else {
    return -rpm;
  }
}

void Wheel::incEnc() {
  encoder->increment();
}

void Wheel::setMotorValue(int value) {
  isForward = value > 0;
  motor->setValue(value);
}

int Wheel::reachVelocity(float desiredRPM) {
  isForward = desiredRPM > 0;
  float measuredRPM = getRPM();
  float error = abs(desiredRPM) - measuredRPM;
  int v = int(pid->calc(error));
  // if (!isForward) { v = -v; }
  motor->setValue(v);
  return v;
}
