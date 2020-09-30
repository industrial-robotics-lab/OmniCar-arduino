#include <PinChangeInterrupt.h>
#include "Wheel.h"

int interval = 25; // millis
Wheel w1("w1", 1, 2,  interval);
Wheel w2("w2", 2, 13, interval);
Wheel w3("w3", 3, 18, interval);
Wheel w4("w4", 4, 19, interval);
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
unsigned long timer = 5000;
bool state = false;

void setup() {
  attachInterrupt(digitalPinToInterrupt(w1.getEncPin()), updateW1, RISING);
  attachPCINT(digitalPinToPCINT(w2.getEncPin()), updateW2, RISING);
  attachInterrupt(digitalPinToInterrupt(w3.getEncPin()), updateW3, RISING);
  attachInterrupt(digitalPinToInterrupt(w4.getEncPin()), updateW4, RISING);
  
  Serial.begin(9600);
  Serial.setTimeout(interval);
}

void userInput() {
  int parsedInt = Serial.parseInt();
  if (parsedInt != 0) {
    parsedInt = constrain(parsedInt, -255, 256);
    if (parsedInt == 256) { parsedInt = 0; }
    vel = parsedInt;
    Serial.print("Set velocity: ");
    Serial.println(vel);
  }
}

void runMotors() {
  u = w1.reachVelocity(vel);
  // w1.setMotorValue(vel);
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
    vel = 255;
  } else {
    vel = -255;
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
