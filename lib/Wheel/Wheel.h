#include "Motor.h"
#include "Encoder.h"
#include <PID_v1.h>

#define TICKS_PER_REV 720

class Wheel
{
private:
  double pidSetpoint, pidFeedback, pidOutput;
  double kP, kI, kD;
  double currentAngularVelocity;

  Motor *motor;
  Encoder *encoder;
  PID *pid;

  unsigned long currentMillis = 0;
  unsigned long previousMillis = 0;

public:
  long ticks; // make private
  double revolutions; // make private
  Wheel(
      unsigned int motorNum,
      unsigned int encPinA,
      unsigned int encPinB,
      bool isClockwise);
  ~Wheel();
  void setValue(int value);
  double reachAngularVelocity(double desiredVelocity, double dt);
  void triggerA();
  void triggerB();
  void resetEncoder();

  double getPidOutput();
  double getCurrentLinearVelocity();
  int getEncPinA();
  int getEncPinB();
};
