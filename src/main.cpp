#include <PinChangeInterrupt.h>
#include <Thread.h>
#include "Car.h"
#include "SerialTransceiver.h"

float desiredRpms[4] = {}; // init with zeros
float feedbackRpms[4] = {}; // init with zeros

int carPeriod = 40;
int encoderPins[4] = {2, 13, 18, 19};
Car car(encoderPins, carPeriod, desiredRpms, feedbackRpms);
void updateW1() { car.incEnc1(); }
void updateW2() { car.incEnc2(); }
void updateW3() { car.incEnc3(); }
void updateW4() { car.incEnc4(); }
SerialTransceiver transceiver(desiredRpms, feedbackRpms);

Thread carThread = Thread();
Thread serialThread = Thread();

void updateCar() {car.update();}
void talkSerial() {transceiver.talk();}

void setup() {
  attachInterrupt(digitalPinToInterrupt(car.getEncPin1()), updateW1, RISING);
  attachPCINT(digitalPinToPCINT(car.getEncPin2()), updateW2, RISING);
  attachInterrupt(digitalPinToInterrupt(car.getEncPin3()), updateW3, RISING);
  attachInterrupt(digitalPinToInterrupt(car.getEncPin4()), updateW4, RISING);
  
  Serial.begin(115200);
  Serial.setTimeout(1000);

  carThread.onRun(updateCar);
  serialThread.onRun(talkSerial);
}

void loop() {
  if (carThread.shouldRun()) {carThread.run();}
  if (serialThread.shouldRun()) {serialThread.run();}
}
