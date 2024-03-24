#include <AFMotor.h>
#include <stdlib.h>

class Motor
{
private:
  AF_DCMotor *motor;
  uint8_t pwm_moving_threshold;
  int sendedPWM;
public:
  Motor(uint8_t number, uint8_t pwm_moving_threshold=40);
  ~Motor();
  void setMotorControl(float control); // [-255; 255]
  void setPWMMovingThreshold(uint8_t pwmThreshold); // [0; 255]
  uint8_t getPWMMovingThreshold(); // [0; 255]
  int getSendedPWM();
};
