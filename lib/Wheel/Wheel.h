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

  unsigned int interval = 0;
  unsigned long currentMillis = 0;
  unsigned long previousMillis = 0;

public:
  Wheel(int motorNum, int encPinA, int encPinB, bool isClockwise, unsigned int intervalMillis);
  ~Wheel();
  void setValue(int value);
  void reachVelocity(double desiredVelocity);
  void triggerA();
  void triggerB();
  void resetEncoder();

  double getPidOutput();
  double getCurrentVelocity();
  long getTicks();
  int getEncPinA();
  int getEncPinB();
};
