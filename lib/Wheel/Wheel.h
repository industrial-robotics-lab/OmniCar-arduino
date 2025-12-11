#pragma once

#include "Motor.h"
#include "Encoder.h"
#include <Pid.h>

class Wheel
{
private:
  double pidSetpoint, pidFeedback, pidOutput;
  float currentAngularVelocity;
  float lastAngularVelocity;

  double currentAngle; // make private
  double lastAngle; // make private
  double lastlastAngle;

  Motor *motor;
  Encoder *encoder;
  PID *pid;

  unsigned long currentMillis = 0;
  unsigned long previousMillis = 0;

public:
  long ticks; // make private

  Wheel(
    unsigned int motorNum,
    unsigned int encPinA,
    unsigned int encPinB,
    bool isClockwise,
    double kP = 1.0,
    double kI = 0.0,
    double kD = 0.0,
    double dt = 0.05
  );
  ~Wheel();
  void setMotorControl(float pwm);
  float reachAngularVelocity(float desiredVelocity, float dt);
  void triggerA();
  void triggerB();
  void resetEncoder();

  float getPidOutput();
  float getSendedPWM();

  float getCurrentAngle();
  float getCurrentAngularVelocity();

  int getEncPinA();
  int getEncPinB();
};
