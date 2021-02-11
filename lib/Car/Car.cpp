#include "Car.h"

Car::Car(int encoderPins[8], int intervalMillis, float *desired, float *feedback)
{
    desiredPtr = desired;
    feedbackPtr = feedback;
    // int updateShift = intervalMillis / 4;
    w1 = new Wheel(1, encoderPins[0], encoderPins[1], false);
    w2 = new Wheel(2, encoderPins[2], encoderPins[3], false);
    w3 = new Wheel(3, encoderPins[4], encoderPins[5], false);
    w4 = new Wheel(4, encoderPins[6], encoderPins[7], false);
}
Car::~Car()
{
    delete w1;
    delete w2;
    delete w3;
    delete w4;
}

void Car::update() {}

int Car::getEncPin1A() { return w1->getEncPinA(); }
int Car::getEncPin1B() { return w1->getEncPinB(); }
int Car::getEncPin2A() { return w2->getEncPinA(); }
int Car::getEncPin2B() { return w2->getEncPinB(); }
int Car::getEncPin3A() { return w3->getEncPinA(); }
int Car::getEncPin3B() { return w3->getEncPinB(); }
int Car::getEncPin4A() { return w4->getEncPinA(); }
int Car::getEncPin4B() { return w4->getEncPinB(); }

void Car::incEnc1A() { w1->triggerA(); }
void Car::incEnc1B() { w1->triggerB(); }
void Car::incEnc2A() { w2->triggerA(); }
void Car::incEnc2B() { w2->triggerB(); }
void Car::incEnc3A() { w3->triggerA(); }
void Car::incEnc3B() { w3->triggerB(); }
void Car::incEnc4A() { w4->triggerA(); }
void Car::incEnc4B() { w4->triggerB(); }
