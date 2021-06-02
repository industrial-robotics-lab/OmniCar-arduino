#include <PinChangeInterrupt.h>
#include "Wheel.h"

unsigned long wheelPeriod = 40;
Wheel w(1, 18, 19, false); // max speed == ~0.9 m/s
// Wheel w(2, 20, 21, true); // max speed == ~0. m/s
// Wheel w(3, 50, 52, true); // max speed == ~0.85 m/s
// Wheel w(4, 51, 53, false); // max speed == ~0.9 m/s
void triggerA() { w.triggerA(); }
void triggerB() { w.triggerB(); }

unsigned long period = 2000;
double desiredLinearVelocity = 0;
unsigned long step;
unsigned long prev;

unsigned long currentMillis;
unsigned long previousMillis;

void setup()
{
  attachInterrupt(digitalPinToInterrupt(w.getEncPinA()), triggerA, RISING);
  attachInterrupt(digitalPinToInterrupt(w.getEncPinB()), triggerB, RISING);
  // attachPCINT(digitalPinToPCINT(w.getEncPinA()), triggerA, RISING);
  // attachPCINT(digitalPinToPCINT(w.getEncPinB()), triggerB, RISING);

  Serial.begin(38400);
  Serial.setTimeout(wheelPeriod);
}

void updateDesired()
{
  prev = step;
  step = millis() / period;
  if (step > prev)
  {
    if (step % 2 == 0)
    {
      desiredLinearVelocity = 0;
    }
    else
    {
      desiredLinearVelocity = 0.5;
    }

    // desiredLinearVelocity = random(-100, 100) / 100.0;
    // desiredLinearVelocity = 1;
  }
}

void sendData()
{
  Serial.print('$');
  Serial.print(desiredLinearVelocity);
  // Serial.print(' ');
  // Serial.print(w.getPidOutput() / 255); // range from [-255; 255] to [-1; 1] for good scale on plot
  Serial.print(' ');
  Serial.print(w.getCurrentLinearVelocity());
  Serial.print(';');
}

void controlWheel()
{
  currentMillis = millis();
  unsigned long diff = currentMillis - previousMillis;
  if (diff >= wheelPeriod)
  {
    previousMillis = currentMillis;

    double dt = (double)diff / 1000; // millis to seconds
    w.reachAngularVelocity(desiredLinearVelocity, dt);
    sendData();
  }
}

void loop()
{
  updateDesired();
  controlWheel();
}