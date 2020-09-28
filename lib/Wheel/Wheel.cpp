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

float Wheel::getDirectedRPM() {
  float rpm = encoder->getRPM();
  if (isDirectionSwitched) {
    return -rpm;
  } else {
    return rpm;
  }
}

void Wheel::incEnc() {
  encoder->increment();
}

// void Wheel::setMotorValue(int value) {
//   // isBackward = value < 0;
//   motor->setValue(value);
// }

double Wheel::reachVelocity(float desiredRPM) {
  currentMillis = millis();
  if (currentMillis - previousMillis > intervalMillis) {
    previousMillis = currentMillis;

    encoder->evaluateSpeed();
    isDirectionSwitched = (desiredRPM < 0) != (prevRPM < 0);
    pidFeedback = getDirectedRPM();
    pidSetpoint = desiredRPM;
    pid->Compute();
    motor->setValue(pidOutput);

    prevRPM = desiredRPM;

    return pidOutput;
  }
}