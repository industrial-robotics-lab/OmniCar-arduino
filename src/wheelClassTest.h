#include <PinChangeInterrupt.h>
#include "Wheel.h"

int intervalMillis = 20;
Wheel w(1, 18, 19, false);
void triggerA() { w.triggerA(); }
void triggerB() { w.triggerB(); }

unsigned long period = 3000;
unsigned long valuesSize = 3;
double desiredValues[] = {0, 3, 0};

double desiredPosition = 0;

void setup() {
    attachInterrupt(digitalPinToInterrupt(w.getEncPinA()), triggerA, RISING);
    attachInterrupt(digitalPinToInterrupt(w.getEncPinB()), triggerB, RISING);

  Serial.begin(115200);
  Serial.setTimeout(intervalMillis);
}

void controlDesired() {
  unsigned long step = millis() / period;
  if (step < valuesSize) {
    desiredPosition = desiredValues[step];
  }
}

void sendData() {
  Serial.print('$');
  Serial.print(desiredPosition);
  Serial.print(' ');
  Serial.print(w.getPidOutput());
  Serial.print(' ');
  Serial.print(w.getPosition());
  Serial.print(';');
}


void loop() {
  controlDesired();
  w.reachPosition(desiredPosition);
  sendData();
}