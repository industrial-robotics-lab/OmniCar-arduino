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
int u = 0;

unsigned long now = 0;
unsigned long prev = 0;
unsigned long timer = 3000;
bool state = false;

void setup() {
  attachInterrupt(digitalPinToInterrupt(w1.getEncPin()), updateW1, RISING);
  attachPCINT(digitalPinToPCINT(w2.getEncPin()), updateW2, RISING);
  attachInterrupt(digitalPinToInterrupt(w3.getEncPin()), updateW3, RISING);
  attachInterrupt(digitalPinToInterrupt(w4.getEncPin()), updateW4, RISING);
  
  Serial.begin(9600);
  Serial.setTimeout(100);
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

void runMotors() {
  w1.update();
  // w2.update();
  // w3.update();
  // w4.update();
  u = w1.reachVelocity(vel);
  // w2.setMotorValue(vel);
  // w3.setMotorValue(vel);
  // w4.setMotorValue(vel);
}

void sendData() {
  Serial.print('$');
  Serial.print(vel);
  Serial.print(' ');
  Serial.print(u);
  Serial.print(' ');
  Serial.print(w1.getRPM(), 2);
  Serial.print(';');
}

void changeState() {
  state = !state;
  if(state) {
    vel = 100;
  } else {
    vel = 0;
  }
}

void loop() {
  // userInput();
  runMotors();
  sendData();

  now = millis();
  if (now - prev > timer) {
    prev = now;
    changeState();
  }
}
