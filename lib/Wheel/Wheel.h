#include "Motor.h"
#include "Encoder.h"
#include <PID_v1.h>

class Wheel {
  private:
    String wheelName;
    Motor* motor;
    Encoder* encoder;
    PID* pid;
    bool isDirectionSwitched;

    double pidSetpoint, pidFeedback, pidOutput;
    double kP, kI, kD;

    int intervalMillis; // 10 - 20000
    long previousMillis = 0;
    long currentMillis = 0;

    float prevRPM;

  public:    
    Wheel(String wheelName, int motorNum, int encPin, int intervalMillis);
    ~Wheel();
    int getEncPin();
    float getDirectedRPM();
    void incEnc();
    // void setMotorValue(int value); // TODO remove after controller implementation
    double reachVelocity(float desiredRPM);
};
