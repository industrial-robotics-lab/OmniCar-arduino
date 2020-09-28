#include "Arduino.h"
#include "Encoder.h"

Encoder::Encoder(int pin, int intervalMillis) {
  pinMode(pin, INPUT_PULLUP);
  this->pin = pin;
  this->fractOfSec = intervalMillis / 1000.0;
}

float Encoder::getRPM() {
  return rpm;
}

void Encoder::evaluateSpeed() {
  rpm = (float)value / TICKS_PER_REV * 60 / fractOfSec;
  value = 0;
}

void Encoder::increment() { value++; }
