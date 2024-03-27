#include <PinChangeInterrupt.h>
#include "Wheel.h"
#include "config.h"

unsigned long updatePeriod = UPDATE_STATE_DT_MS;
Wheel w(1, ENC_MOTOR1_PINA, ENC_MOTOR1_PINB, true, WHEEL_KP, WHEEL_KI, WHEEL_KD, updatePeriod/1000.0); // max rot speed == ~4.72 rev/s
// Wheel w(2, 20, 21, true); // max rot speed == ~4.51 rev/s
// Wheel w(3, 50, 52, true); // max rot speed == ~4.44 rev/s
// Wheel w(4, 51, 53, false); // max rot speed == ~4.93 rev/s
void triggerA() { w.triggerA(); }
void triggerB() { w.triggerB(); }

unsigned long period = 5000;
double desiredAngularVelocity = 0;
unsigned long step;
unsigned long prev;
double dt;

unsigned long currentMillis;
unsigned long previousMillis;

void setup()
{
  if(digitalPinToInterrupt(w.getEncPinA()) == -1){
    attachPCINT(digitalPinToPCINT(w.getEncPinA()), triggerA, RISING);
  } else{
    attachInterrupt(digitalPinToInterrupt(w.getEncPinA()), triggerA, RISING);
  }
  if(digitalPinToInterrupt(w.getEncPinB()) == -1){
    attachPCINT(digitalPinToPCINT(w.getEncPinB()), triggerB, RISING);
  } else{
    attachInterrupt(digitalPinToInterrupt(w.getEncPinB()), triggerB, RISING);
  }

  Serial.begin(38400);
  Serial.setTimeout(updatePeriod);
}

void updateDesired()
{
  prev = step;
  step = millis() / period;
  if (step > prev)
  {
    if (step % 2 == 0)
    {
      desiredAngularVelocity = 0;
    }
    else
    {
      desiredAngularVelocity = 0.5;
    }

    // desiredAngularVelocity = random(-100, 100) / 100.0;
    // desiredAngularVelocity = 1;
  }
}

void sendData()
{
  Serial.print('$');
  Serial.print(desiredAngularVelocity);
  // Serial.print(' ');
  // Serial.print(w.getPidOutput() / 255); // range from [-255; 255] to [-1; 1] for good scale on plot
  Serial.print(' ');
  Serial.print(w.getCurrentAngularVelocity());
  Serial.print(' ');
  Serial.print(w.getCurrentAngle());
  Serial.print(' ');
  Serial.print(w.getPidOutput());
  Serial.print(' ');
  Serial.print(w.getSendedPWM());
  Serial.print(' ');
  Serial.println(';');
}

void controlWheel()
{
  currentMillis = millis();
  unsigned long diff = currentMillis - previousMillis;
  if (diff >= updatePeriod)
  {
    previousMillis = currentMillis;

    dt = (double)diff / 1000; // millis to seconds
    w.reachAngularVelocity(desiredAngularVelocity, dt);
    sendData();
  }
}

void loop()
{
  updateDesired();
  controlWheel();
}