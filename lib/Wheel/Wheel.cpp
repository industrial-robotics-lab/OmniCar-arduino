#include "Arduino.h"
#include "Wheel.h"

Wheel::Wheel(int motorNum, int encPin, int intervalMillis, int initDelay) {
  this->motor = new Motor(motorNum);
  this->encoder = new Encoder(encPin, intervalMillis);
  this->intervalMillis = intervalMillis;
  this->initDelay = initDelay;

  kP = 1; kI = 5; kD = 0.01;
  this->pid = new PID(&pidFeedback, &pidOutput, &pidSetpoint, kP, kI, kD, DIRECT);
  pid->SetMode(AUTOMATIC);
  pid->SetOutputLimits(-255, 255);
  pid->SetSampleTime(intervalMillis); // in millis
  // pid->SetTunings(1, 2, 3);
  // pid->SetControllerDirection(DIRECT);
}
Wheel::~Wheel() { 
  delete motor;
  delete encoder;
  delete pid;
}

int Wheel::getEncPin() {
  return encoder->pin;
}

void Wheel::incEnc() {
  encoder->increment();
}

float Wheel::getRPM() {
  return encoder->getRPM();
}

double Wheel::reachVelocity(float desiredRPM) {
  currentMillis = millis();
  if (currentMillis < initDelay) {
    previousMillis = currentMillis;
    return 0;
  }
  if (currentMillis - previousMillis > intervalMillis) {
    previousMillis = currentMillis;

    encoder->isBackward = motor->isBackward;
    encoder->evaluateRPM();
    pidFeedback = encoder->getRPM();
    pidSetpoint = desiredRPM;
    pid->Compute();
    motor->setValue(pidOutput);
  }
  return pidOutput;
}