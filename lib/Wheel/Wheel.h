#include "Motor.h"
#include "Encoder.h"
#include <PID_v1.h>

class Wheel
{
private:
  const int TICKS_PER_REV = 360;
  const double radius = 0.03;
  double pidSetpoint, pidFeedback, pidOutput;
  double kP, kI, kD;
  double position;
  
  Motor *motor;
  Encoder *encoder;
  PID *pid;

  void updatePosition();

public:
  Wheel(int motorNum, int encPinA, int encPinB, bool isClockwise);
  ~Wheel();
  void reachPosition(double desiredPosition);
  void triggerA();
  void triggerB();

  double getPidOutput();
  double getPosition();
  int getEncPinA();
  int getEncPinB();
};
