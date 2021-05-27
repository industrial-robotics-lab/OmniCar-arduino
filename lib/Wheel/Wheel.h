#include "Motor.h"
#include "Encoder.h"
#include <PID_v1.h>

#define TICKS_PER_REV 720
#define DIAMETER 60.0 / 1000   // mm to m

class Wheel
{
private:
  double pidSetpoint, pidFeedback, pidOutput;
  double kP, kI, kD;
  double currentLinearVelocity;
  double revolutions;
  double linearDistance;

  Motor *motor;
  Encoder *encoder;
  PID *pid;

  unsigned int interval = 0;
  unsigned long currentMillis = 0;
  unsigned long previousMillis = 0;

public:
  Wheel(
      unsigned int motorNum,
      unsigned int encPinA,
      unsigned int encPinB,
      bool isClockwise,
      unsigned int intervalMillis);
  ~Wheel();
  void setValue(int value);
  void reachLinearVelocity(double desiredVelocity, double dt);
  void triggerA();
  void triggerB();
  void resetEncoder();

  double getPidOutput();
  double getCurrentLinearVelocity();
  long getTicks();
  int getEncPinA();
  int getEncPinB();
};
