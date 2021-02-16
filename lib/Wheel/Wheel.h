#include "Motor.h"
#include "Encoder.h"
#include <PID_v1.h>

#define DIAMETER 60.0 / 1000 // mm to m

class Wheel
{
private:
  const int TICKS_PER_REV = 360;
  double pidSetpoint, pidFeedback, pidOutput;
  double kP, kI, kD;
  double currentVelocity;
  
  Motor *motor;
  Encoder *encoder;
  PID *pid;

public:
  Wheel(int motorNum, int encPinA, int encPinB, bool isClockwise);
  ~Wheel();
  void setValue(int value);
  void reachVelocity(double desiredVelocity, float dt);
  void triggerA();
  void triggerB();
  void resetEncoder();

  double getPidOutput();
  double getCurrentVelocity();
  long getTicks();
  int getEncPinA();
  int getEncPinB();
};
