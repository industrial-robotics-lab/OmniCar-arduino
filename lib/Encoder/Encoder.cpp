#include "Arduino.h"
#include "Encoder.h"

Encoder::Encoder(int pinA, int pinB, bool isClockwise)
{
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
  this->pinA = pinA;
  this->pinB = pinB;
  if (isClockwise)
  {
    increment = 1;
  }
  else
  {
    increment = -1;
  }
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
