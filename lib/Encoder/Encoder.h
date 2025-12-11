#pragma once
#include "Arduino.h"

#define ENC_TICKS_PER_REV 660

class Encoder
{
private:
  unsigned int pinA;
  unsigned int pinB;
  volatile long ticks = 0;
  int increment = 0;
  
public:

  Encoder(
      unsigned int pinA,
      unsigned int pinB,
      bool isClockwise = false);
  void triggerA();
  void triggerB();
  volatile long getTicks();
  void reset();
  int getPinA();
  int getPinB();
  double getAngle();
};
