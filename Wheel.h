#include "Motor.h"
#include "Encoder.h"

class Wheel {
  private:
    String wheelName;
    
  public:
    Motor* motor;
    Encoder* encoder;
    
    Wheel(String wheelName, int motorNum, int encPin, int intervalMillis);
    ~Wheel();
    void update();
    float getRPM();
    void reachVelocity(int desiredRPM);
};
