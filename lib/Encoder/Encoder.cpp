#include "Encoder.h"

Encoder::Encoder(
    unsigned int pinA,
    unsigned int pinB,
    bool isClockwise)
    : pinA(pinA), pinB(pinB)
{
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
  increment = (2*isClockwise-1);
}

void Encoder::triggerA()
{
  if (digitalRead(pinA) != digitalRead(pinB))
  {
    ticks += increment;
  }
  else
  {
    ticks -= increment;
  }
}

void Encoder::triggerB()
{
  if (digitalRead(pinA) == digitalRead(pinB))
  {
    ticks += increment;
  }
  else
  {
    ticks -= increment;
  }

}

volatile long Encoder::getTicks()
{
  return ticks;
}

double Encoder::getAngle()
{
  return (double)ticks/ ENC_TICKS_PER_REV *TWO_PI;
}

void Encoder::reset()
{
  ticks = 0;
}

int Encoder::getPinA()
{
  return pinA;
}

int Encoder::getPinB()
{
  return pinB;
}
