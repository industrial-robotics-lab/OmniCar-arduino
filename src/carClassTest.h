#include <PinChangeInterrupt.h>
#include "Car.h"

Matrix<3> desiredCarVelocity;
Matrix<3> feedbackCarVelocity;

int carPeriod = 40; // millis
Car car(TRACK / 2, WHEELBASE / 2, DIAMETER / 2, carPeriod, &desiredCarVelocity, &feedbackCarVelocity);
void updateW1A() { car.incEnc1A(); }
void updateW1B() { car.incEnc1B(); }
void updateW2A() { car.incEnc2A(); }
void updateW2B() { car.incEnc2B(); }
void updateW3A() { car.incEnc3A(); }
void updateW3B() { car.incEnc3B(); }
void updateW4A() { car.incEnc4A(); }
void updateW4B() { car.incEnc4B(); }

void setup()
{
    attachInterrupt(digitalPinToInterrupt(car.getEncPin1A()), updateW1A, RISING);
    attachInterrupt(digitalPinToInterrupt(car.getEncPin1B()), updateW1B, RISING);
    attachInterrupt(digitalPinToInterrupt(car.getEncPin2A()), updateW2A, RISING);
    attachInterrupt(digitalPinToInterrupt(car.getEncPin2B()), updateW2B, RISING);
    attachPCINT(digitalPinToPCINT(car.getEncPin3A()), updateW3A, RISING);
    attachPCINT(digitalPinToPCINT(car.getEncPin3B()), updateW3B, RISING);
    attachPCINT(digitalPinToPCINT(car.getEncPin4A()), updateW4A, RISING);
    attachPCINT(digitalPinToPCINT(car.getEncPin4B()), updateW4B, RISING);

    Serial.begin(115200);
    Serial.setTimeout(1000);
}

void loop()
{
    //                     t x y
    car.setDesiredVelocity(-0.1, 0, 0);
    Serial << feedbackCarVelocity << '\n';
    car.update();
}
