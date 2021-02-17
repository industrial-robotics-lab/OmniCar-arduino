#include <PinChangeInterrupt.h>
#include "Wheel.h"

int intervalMillis = 40;
Wheel w(1, 18, 19, false, intervalMillis);
void triggerA() { w.triggerA(); }
void triggerB() { w.triggerB(); }

unsigned long period = 5000;
unsigned long valuesSize = 6;
double desiredValues[] = {0, 1, 4, 6, 100, 0};
double desiredVelocity = 0;

void setup()
{
  attachInterrupt(digitalPinToInterrupt(w.getEncPinA()), triggerA, RISING);
  attachInterrupt(digitalPinToInterrupt(w.getEncPinB()), triggerB, RISING);
  // attachPCINT(digitalPinToPCINT(w.getEncPinA()), triggerA, RISING);
  // attachPCINT(digitalPinToPCINT(w.getEncPinB()), triggerB, RISING);

  Serial.begin(115200);
  Serial.setTimeout(intervalMillis);
}

void controlDesired()
{
  unsigned long step = millis() / period;
  if (step < valuesSize)
  {
    desiredVelocity = desiredValues[step];
  }
}

void sendData()
{
  Serial.print('$');
  Serial.print(desiredVelocity);
  Serial.print(' ');
  Serial.print(w.getPidOutput());
  Serial.print(' ');
  Serial.print(w.getCurrentVelocity());
  Serial.print(';');
}

void loop()
{
  controlDesired();
  w.reachVelocity(desiredVelocity);
  sendData();
}