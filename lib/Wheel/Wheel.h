#pragma once

#include "Motor.h"
#include "Encoder.h"
#include <Pid.h>
#include <config.h>

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
  void setPID(double kp, double ki, double kd);
  void resetPID();
  
  long ticks; // make private

  Wheel(
    unsigned int motorNum,
    unsigned int encPinA,
    unsigned int encPinB,
    bool isClockwise,
    double kP = WHEEL_KP,
    double kI = WHEEL_KI,
    double kD = WHEEL_KD,
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
  long getTicks();

  int getEncPinA();
  int getEncPinB();
};
