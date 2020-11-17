#include <PinChangeInterrupt.h>
// #include "Wheel.h"
#include "Car.h"
#include "SerialTalker.h"

SerialTalker talker;
int intervalMillis = 40;
int encoderPins[4] = {2, 13, 18, 19};
Car car(encoderPins, intervalMillis);
void updateW1() { car.incEnc1(); }
void updateW2() { car.incEnc2(); }
void updateW3() { car.incEnc3(); }
void updateW4() { car.incEnc4(); }

void setup() {
  attachInterrupt(digitalPinToInterrupt(car.getEncPin1()), updateW1, RISING);
  attachPCINT(digitalPinToPCINT(car.getEncPin2()), updateW2, RISING);
  attachInterrupt(digitalPinToInterrupt(car.getEncPin3()), updateW3, RISING);
  attachInterrupt(digitalPinToInterrupt(car.getEncPin4()), updateW4, RISING);
  
  Serial.begin(115200);
  Serial.setTimeout(intervalMillis);
}

void loop() {
  float* control_from_rpi = talker.rx();
  car.setDesiredRpms(control_from_rpi);
  car.updateFeedbackRpms();
  talker.tx(car.getFeedbackRpms());
  car.reachDesiredRpms();
}
