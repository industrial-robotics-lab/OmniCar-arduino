#include <AFMotor.h>

class Motor
{
private:
  AF_DCMotor *motor;

public:
  Motor(unsigned int number);
  ~Motor();
  void setValue(int value); // [-255; 255]
};
