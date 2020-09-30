#include "Motor.h"
#include "Encoder.h"
#include <PID_v1.h>

class Wheel {
  private:
    String wheelName;
    Motor* motor;
    Encoder* encoder;
    PID* pid;

    double pidSetpoint, pidFeedback, pidOutput;
    double kP, kI, kD;

    int intervalMillis; // 10 - 20000
    long previousMillis = 0;
    long currentMillis = 0;

  public:    
    Wheel(String wheelName, int motorNum, int encPin, int intervalMillis);
    ~Wheel();
    int getEncPin();
    void incEnc();
    float getRPM();
    // void setMotorValue(int value); // TODO direct PWM on motor without any conrol
    double reachVelocity(float desiredRPM);
};
