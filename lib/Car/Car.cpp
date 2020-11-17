#include "Car.h"

Car::Car(int encoderPins[4], int intervalMillis) {
    int updateShift = intervalMillis / 4;
    w1 = new Wheel(1, encoderPins[0], intervalMillis, 0);
    w2 = new Wheel(2, encoderPins[1], intervalMillis, updateShift);
    w3 = new Wheel(3, encoderPins[2], intervalMillis, updateShift * 2);
    w4 = new Wheel(4, encoderPins[3], intervalMillis, updateShift * 3);
}
Car::~Car() {
    delete w1;
    delete w2;
    delete w3;
    delete w4;
}

float* Car::getFeedbackRpms() { return feedbackRpms; }

void Car::setDesiredRpms(float values[4]) {
    desiredRpms[0] = values[0];
    desiredRpms[1] = values[1];
    desiredRpms[2] = values[2];
    desiredRpms[3] = values[3];
}

void Car::updateFeedbackRpms() {
    feedbackRpms[0] = w1->getRPM();
    feedbackRpms[1] = w2->getRPM();
    feedbackRpms[2] = w3->getRPM();
    feedbackRpms[3] = w4->getRPM();
}

void Car::reachDesiredRpms() {
    w1->reachVelocity(desiredRpms[0]);
    w2->reachVelocity(desiredRpms[1]);
    w3->reachVelocity(desiredRpms[2]);
    w4->reachVelocity(desiredRpms[3]);
}

int Car::getEncPin1() { return w1->getEncPin(); }
int Car::getEncPin2() { return w2->getEncPin(); }
int Car::getEncPin3() { return w3->getEncPin(); }
int Car::getEncPin4() { return w4->getEncPin(); }

void Car::incEnc1() { w1->incEnc(); }
void Car::incEnc2() { w2->incEnc(); }
void Car::incEnc3() { w3->incEnc(); }
void Car::incEnc4() { w4->incEnc(); }
