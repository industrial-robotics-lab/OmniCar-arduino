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

float Wheel::getRPM() {
  return encoder->getRPM();
}

void Wheel::reachVelocity(int desiredRPM) {
  int measuredRPM = getRPM();
  Serial.println(measuredRPM);
  int gain = (int)(desiredRPM - measuredRPM);
  motor->setValue(gain);
}
