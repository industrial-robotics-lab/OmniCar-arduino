#include "Arduino.h"
#include "Wheel.h"

Wheel::Wheel(String wheelName, int motorNum, int encPin, int intervalMillis) {
  this->wheelName = wheelName;
  this->motor = new Motor(motorNum);
  this->encoder = new Encoder(encPin, intervalMillis);
}
Wheel::~Wheel() { 
  delete motor;
  delete encoder;
}

void Wheel::update() {
  encoder->update();
}

int Wheel::getEncPin() {
  return encoder->pin;
}

float Wheel::getRPM() {
  return encoder->getRPM();
}

void Wheel::incEnc() {
  encoder->increment();
}

void Wheel::setMotorValue(int value) {
  motor->setValue(value);
}

void Wheel::reachVelocity(int desiredRPM) {
  int measuredRPM = getRPM();
  Serial.println(measuredRPM);
  int gain = (int)(desiredRPM - measuredRPM);
  motor->setValue(gain);
}
