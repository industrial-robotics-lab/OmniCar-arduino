#include <PinChangeInterrupt.h>
// #include "Wheel.h"
#include "Car.h"

int intervalMillis = 25; // millis
Car car(1, 2, 3, 4, 2, 13, 18, 19, intervalMillis);
// Wheel w1("w1", 1, 2,  interval);
// Wheel w2("w2", 2, 13, interval);
// Wheel w3("w3", 3, 18, interval);
// Wheel w4("w4", 4, 19, interval);
void updateW1() { car.incEnc1(); }
void updateW2() { car.incEnc2(); }
void updateW3() { car.incEnc3(); }
void updateW4() { car.incEnc4(); }

int vel = 0;
int u = 0;

unsigned long now = 0;
unsigned long prev = 0;
unsigned long timer = 5000;
bool state = false;

void setup() {
  attachInterrupt(digitalPinToInterrupt(car.getEncPin1()), updateW1, RISING);
  attachPCINT(digitalPinToPCINT(car.getEncPin2()), updateW2, RISING);
  attachInterrupt(digitalPinToInterrupt(car.getEncPin3()), updateW3, RISING);
  attachInterrupt(digitalPinToInterrupt(car.getEncPin4()), updateW4, RISING);
  
  Serial.begin(9600);
  Serial.setTimeout(intervalMillis);
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
  // u = w1.reachVelocity(vel);
  // w1.setMotorValue(vel);
  car.runForward(vel);
}

void sendData() {
  Serial.print('$');
  // Serial.print(vel);
  // Serial.print(' ');
  // Serial.print(u);
  // Serial.print(' ');
  // Serial.print(w1.getRPM(), 2);
  Serial.print(car.getRPM1(), 2);
  Serial.print(' ');
  Serial.print(car.getRPM2(), 2);
  Serial.print(' ');
  Serial.print(car.getRPM3(), 2);
  Serial.print(' ');
  Serial.print(car.getRPM4(), 2);
  Serial.print(';');
}

void changeState() {
  state = !state;
  if(state) {
    vel = 100;
  } else {
    vel = -100;
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
