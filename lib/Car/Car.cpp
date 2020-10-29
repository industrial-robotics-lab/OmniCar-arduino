#include "Car.h"

Car::Car(int mPin1, int mPin2, int mPin3, int mPin4, int ePin1, int ePin2, int ePin3, int ePin4, int intervalMillis) {
    int updateShift = intervalMillis / 4;
    w1 = new Wheel(mPin1, ePin1, intervalMillis, 0);
    w2 = new Wheel(mPin2, ePin2, intervalMillis, updateShift);
    w3 = new Wheel(mPin3, ePin3, intervalMillis, updateShift * 2);
    w4 = new Wheel(mPin4, ePin4, intervalMillis, updateShift * 3);
}
Car::~Car() {
    delete w1;
    delete w2;
    delete w3;
    delete w4;
}

void Car::runForward(float rpm) {
    w1->reachVelocity(rpm);
    w2->reachVelocity(rpm);
    w3->reachVelocity(rpm);
    w4->reachVelocity(rpm);
}

int Car::getEncPin1() { return w1->getEncPin(); }
int Car::getEncPin2() { return w2->getEncPin(); }
int Car::getEncPin3() { return w3->getEncPin(); }
int Car::getEncPin4() { return w4->getEncPin(); }

void Car::incEnc1() { w1->incEnc(); }
void Car::incEnc2() { w2->incEnc(); }
void Car::incEnc3() { w3->incEnc(); }
void Car::incEnc4() { w4->incEnc(); }

float Car::getRPM1() { return w1->getRPM(); }
float Car::getRPM2() { return w2->getRPM(); }
float Car::getRPM3() { return w3->getRPM(); }
float Car::getRPM4() { return w4->getRPM(); }