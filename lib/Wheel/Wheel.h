#include "Motor.h"
#include "Encoder.h"
#include "PID.h"

class Wheel {
  private:
    String wheelName;
    Motor* motor;
    Encoder* encoder;
    PID* pid;
    bool isForward;
    
  public:    
    Wheel(String wheelName, int motorNum, int encPin, int intervalMillis);
    ~Wheel();
    void update();
    int getEncPin();
    float getRPM();
    void incEnc();
    void setMotorValue(int value); // TODO remove after controller implementation
    int reachVelocity(float desiredRPM);
};
