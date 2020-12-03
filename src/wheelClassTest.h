#include <PinChangeInterrupt.h>
#include "Wheel.h"

int intervalMillis = 20;
Wheel w(1, 50, 51, false);
void triggerA() { w.triggerA(); }
void triggerB() { w.triggerB(); }

unsigned long period = 3000;
unsigned long valuesSize = 2;
double desiredValues[] = {0, 1};

double desiredPosition = 0;

void setup() {
  // attachInterrupt(digitalPinToInterrupt(w1.getEncPin()), updateW1, RISING);
    attachPCINT(digitalPinToPCINT(w.getEncPinA()), triggerA, RISING);
    attachPCINT(digitalPinToPCINT(w.getEncPinB()), triggerB, RISING);

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
  // Serial.print(w.getPidOutput());
  // Serial.print(' ');
  Serial.print(w.getPosition());
  Serial.print(';');
}


void loop() {
  controlDesired();
  w.reachPosition(desiredPosition);
  sendData();
}