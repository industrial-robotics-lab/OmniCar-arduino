#include <PinChangeInterrupt.h>
#include "Wheel.h"

int intervalMillis = 40;
unsigned long minPeriod = 40;
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
Wheel w(1, 18, 19, false);
void triggerA() { w.triggerA(); }
void triggerB() { w.triggerB(); }

unsigned long period = 3000;
unsigned long valuesSize = 3;
double desiredValues[] = {0, 100, 0};
double desiredVelocity = 0;

void setup() {
    attachInterrupt(digitalPinToInterrupt(w.getEncPinA()), triggerA, RISING);
    attachInterrupt(digitalPinToInterrupt(w.getEncPinB()), triggerB, RISING);
    // attachPCINT(digitalPinToPCINT(w.getEncPinA()), triggerA, RISING);
    // attachPCINT(digitalPinToPCINT(w.getEncPinB()), triggerB, RISING);

  Serial.begin(115200);
  Serial.setTimeout(intervalMillis);
}

void controlDesired() {
  unsigned long step = millis() / period;
  if (step < valuesSize) {
    desiredVelocity = desiredValues[step];
  }
}

void sendData() {
  Serial.print('$');
  Serial.print(desiredVelocity);
  Serial.print(' ');
  Serial.print(w.getPidOutput());
  Serial.print(' ');
  Serial.print(w.getCurrentVelocity());
  Serial.print(';');
}


void loop() {
  controlDesired();
  currentMillis = millis();
    unsigned long diff = currentMillis - previousMillis;
    if (diff >= minPeriod)
    {
        previousMillis = currentMillis;
        float dt = (float)diff / 1000; // in seconds
        w.reachVelocity(desiredVelocity, dt);
    }
  sendData();
}