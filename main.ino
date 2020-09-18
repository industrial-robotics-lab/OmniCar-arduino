#include "Wheel.h"
//#include "Motor.h"
//#include "Encoder.h"

Wheel w1("w1", 1, 2,  50);
//Wheel w2("w2", 2, 13, 25);
//Wheel w3("w3", 3, 18, 25);
//Wheel w4("w4", 4, 19, 25);
//Motor m1(1);
//Encoder e1(2, 50);
void updateW1() { w1.encoder->increment(); }
//void updateW2() { w2.updateEncoder(); }
//void updateW3() { w3.updateEncoder(); }
//void updateW4() { w4.updateEncoder(); }
//void updateE1() { e1.increment(); }

int vel = 0;

void setup() {
  attachInterrupt(digitalPinToInterrupt(w1.encoder->pin), updateW1, RISING);
//  attachPCINT(digitalPinToPCINT(w2.encPin), updateW2, RISING);
//  attachInterrupt(digitalPinToInterrupt(w3.encPin), updateW3, RISING);
//  attachInterrupt(digitalPinToInterrupt(w4.encPin), updateW4, RISING);
  
  Serial.begin(9600);
  Serial.setTimeout(10);
}

void loop() {
  userInput();
  w1.update();
  w1.motor->setValue(vel);
//  w2.setPWM(vel);
//  w3.setPWM(vel);
//  w4.setPWM(vel);
//  w1.calcVelocity();
//  w2.calcVelocity();
//  w3.calcVelocity();
//  w4.calcVelocity();
//  w1.reachVelocity(vel);
//  m1.setValue(vel);
//  e1.calcRPM();
  Serial.println(w1.getRPM());
}

int userInput() {
  int parsedInt = Serial.parseInt();
  if (parsedInt != 0) {
    vel = parsedInt;
    vel = constrain(vel, -255, 256);
    if (vel == 256) { vel = 0; }
    Serial.print("Set velocity: ");
    Serial.println(vel);
  }
}
