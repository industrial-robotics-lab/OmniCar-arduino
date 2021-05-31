#include <PinChangeInterrupt.h>
#include "Wheel.h"

int intervalMillis = 40;
Wheel w(1, 18, 19, false);
void triggerA() { w.triggerA(); }
void triggerB() { w.triggerB(); }

unsigned long period = 5000;
unsigned long valuesSize = 6;
double desiredValues[] = {0, 1, 4.5, -4.5, 2, 0};
double desiredVelocity = 0;

unsigned long currentMillis;
unsigned long previousMillis;

void setup()
{
  attachInterrupt(digitalPinToInterrupt(w.getEncPinA()), triggerA, RISING);
  attachInterrupt(digitalPinToInterrupt(w.getEncPinB()), triggerB, RISING);
  // attachPCINT(digitalPinToPCINT(w.getEncPinA()), triggerA, RISING);
  // attachPCINT(digitalPinToPCINT(w.getEncPinB()), triggerB, RISING);

  Serial.begin(38400);
  Serial.setTimeout(intervalMillis);
}

void updateDesired()
{
  unsigned long step = millis() / period;
  if (step < valuesSize)
  {
    desiredVelocity = desiredValues[step];
  }
}

void controlWheel()
{
  currentMillis = millis();
    unsigned long diff = currentMillis - previousMillis;
    if (diff > period)
    {
        previousMillis = currentMillis;

        double dt = (double)diff / 1000; // millis to seconds
        w.reachLinearVelocity(desiredVelocity, dt);
        sendData();
    }
}

void sendData()
{
  Serial.print('$');
  Serial.print(desiredVelocity);
  Serial.print(' ');
  Serial.print(w.getPidOutput());
  Serial.print(' ');
  Serial.print(w.getCurrentLinearVelocity());
  Serial.print(';');
}

void loop()
{
  updateDesired();
  controlWheel();
}