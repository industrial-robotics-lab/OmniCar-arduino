#include "Car.h"

Car::Car(
    float w,
    float l,
    float r,
    int minMillis)
{
    minPeriod = minMillis;

    w1 = new Wheel(1, 18, 19, false);
    w2 = new Wheel(2, 20, 21, true);
    w3 = new Wheel(3, 50, 52, true);
    w4 = new Wheel(4, 51, 53, false);

    H_0 = {-l - w, 1, -1, l + w, 1, 1, l + w, 1, -1, -l - w, 1, 1};
    F = {-1.0 / (l + w), 1.0 / (l + w), 1.0 / (l + w), -1.0 / (l + w), 1, 1, 1, 1, -1, 1, -1, 1};
    F *=  r / 4;

    currentMillis = 0;
    previousMillis = 0;
}
Car::~Car()
{
    delete w1;
    delete w2;
    delete w3;
    delete w4;
}

void Car::setDesiredVelocity(float vX, float vY, float vTheta)
{
    desiredCarVelocity = {vX, vY, vTheta};
}

void Car::findCarVelocity()
{
    wheelsDisplacement = {w1->getTicks(), w2->getTicks(), w3->getTicks(), w4->getTicks()};
    carVelocity = F * wheelsDisplacement;
}

void Car::setValues(double v1, double v2, double v3, double v4)
{
    w1->setValue(v1);
    w2->setValue(v2);
    w3->setValue(v3);
    w4->setValue(v4);
}

void Car::reachCarVelocity(Matrix<3> carVel, float dt)
{
    Matrix<4> wheelsVel = H_0 * carVel;
    reachWheelsVelocity(wheelsVel, dt);
}

void Car::reachWheelsVelocity(Matrix<4> wheelsVel, float dt)
{
    w1->reachVelocity(wheelsVel(0), dt);
    w2->reachVelocity(wheelsVel(1), dt);
    w3->reachVelocity(wheelsVel(2), dt);
    w4->reachVelocity(wheelsVel(3), dt);
}

void Car::update()
{
    currentMillis = millis();
    unsigned long diff = currentMillis - previousMillis;
    if (diff >= minPeriod)
    {
        previousMillis = currentMillis;
        float dt = (float)diff / 1000; // in seconds
        findCarVelocity();
        reachCarVelocity(desiredCarVelocity, dt);
        resetEncoders();
    }
}

void Car::resetEncoders()
{
    w1->resetEncoder();
    w2->resetEncoder();
    w3->resetEncoder();
    w4->resetEncoder();
}

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
