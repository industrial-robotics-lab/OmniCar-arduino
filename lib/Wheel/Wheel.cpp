#include "Arduino.h"
#include "Wheel.h"

Wheel::Wheel(String wheelName, int motorNum, int encPin, int intervalMillis) {
  this->wheelName = wheelName;
  this->motor = new Motor(motorNum);
  this->encoder = new Encoder(encPin, intervalMillis);
  this->intervalMillis = intervalMillis;

  kP = 1; kI = 5; kD = 0;
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

// void Wheel::setMotorValue(int value) {
//   currentMillis = millis();
//   if (currentMillis - previousMillis > intervalMillis) {
//     previousMillis = currentMillis;

//     encoder->isBackward = motor->isBackward;
//     encoder->evaluateRPM();
//     motor->setValue(value);
//   }
// }

double Wheel::reachVelocity(float desiredRPM) {
  currentMillis = millis();
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