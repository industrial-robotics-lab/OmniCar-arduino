#include <PinChangeInterrupt.h>
#include "Wheel.h"

Wheel w1("w1", 1, 2,  50);
Wheel w2("w2", 2, 13, 50);
Wheel w3("w3", 3, 18, 50);
Wheel w4("w4", 4, 19, 50);
//Motor m1(1);
//Encoder e1(2, 50);
void updateW1() { w1.incEnc(); }
void updateW2() { w2.incEnc(); }
void updateW3() { w3.incEnc(); }
void updateW4() { w4.incEnc(); }

int vel = 0;

void setup() {
  attachInterrupt(digitalPinToInterrupt(w1.getEncPin()), updateW1, RISING);
  attachPCINT(digitalPinToPCINT(w2.getEncPin()), updateW2, RISING);
  attachInterrupt(digitalPinToInterrupt(w3.getEncPin()), updateW3, RISING);
  attachInterrupt(digitalPinToInterrupt(w4.getEncPin()), updateW4, RISING);
  
  Serial.begin(9600);
  Serial.setTimeout(1000);
}

void userInput() {
  int parsedInt = Serial.parseInt();
  if (parsedInt != 0) {
    vel = parsedInt;
    vel = constrain(vel, -255, 256);
    if (vel == 256) { vel = 0; }
    Serial.print("Set velocity: ");
    Serial.println(vel);
  }
}

void loop() {
  userInput();
  w1.update();
  w2.update();
  w3.update();
  w4.update();
  w1.setMotorValue(vel);
  w2.setMotorValue(vel);
  w3.setMotorValue(vel);
  w4.setMotorValue(vel);
//  Serial.println(w1.getRPM());
}
