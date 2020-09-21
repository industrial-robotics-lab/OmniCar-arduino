#include "Motor.h"
#include "Encoder.h"

class Wheel {
  private:
    String wheelName;
    Motor* motor;
    Encoder* encoder;
    
  public:    
    Wheel(String wheelName, int motorNum, int encPin, int intervalMillis);
    ~Wheel();
    void update();
    int getEncPin();
    float getRPM();
    void incEnc();
    void setMotorValue(int value);
    void reachVelocity(int desiredRPM);
};
