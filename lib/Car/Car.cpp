#include "Car.h"

Car::Car(
    float w,
    float l,
    float r,
    unsigned int wheelPeriod,
    Matrix<3> *desiredVelocity,
    Matrix<3> *feedbackPose)
    : 
    period(wheelPeriod), 
    desiredCarVelocity(desiredVelocity),
    feedbackCarPose(feedbackPose)
{
    G = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    w1 = new Wheel(1, 18, 19, false, wheelPeriod);
    w2 = new Wheel(2, 20, 21, true, wheelPeriod);
    w3 = new Wheel(3, 50, 52, true, wheelPeriod);
    w4 = new Wheel(4, 51, 53, false, wheelPeriod);

    H_0 = {-l - w, 1, -1, l + w, 1, 1, l + w, 1, -1, -l - w, 1, 1};
    H_0 /= r;
    F = {-1.0 / (l + w), 1.0 / (l + w), 1.0 / (l + w), -1.0 / (l + w), 1, 1, 1, 1, -1, 1, -1, 1};
    F *= r / 4;
}
Car::~Car()
{
    delete w1;
    delete w2;
    delete w3;
    delete w4;
}

void Car::setDesiredVelocity(float vTheta, float vX, float vY)
{
    *desiredCarVelocity = {vTheta, vX, vY};
}

void Car::findCarPose()
{
    wheelsDisplacement = {
        (double)w1->getTicks() / TICKS_PER_REV,
        (double)w2->getTicks() / TICKS_PER_REV,
        (double)w3->getTicks() / TICKS_PER_REV,
        (double)w4->getTicks() / TICKS_PER_REV};
    Matrix<3> vb = F * wheelsDisplacement;
    Matrix<6> twist = {0, 0, vb(0), vb(1), vb(2), 0};
    Matrix<4, 4> prevToCurrPose = vec6_to_SE3(twist);
    // *feedbackCarPose = {atan2(prevToCurrPose(1, 0), prevToCurrPose(0, 0)), prevToCurrPose(0, 3), prevToCurrPose(1, 3)};
    G *= prevToCurrPose;
    *feedbackCarPose = {atan2(G(1, 0), G(0, 0)), G(0, 3), G(1, 3)};
}

void Car::setValues(double v1, double v2, double v3, double v4)
{
    w1->setValue(v1);
    w2->setValue(v2);
    w3->setValue(v3);
    w4->setValue(v4);
}

void Car::reachCarVelocity(Matrix<3> carVel)
{
    Matrix<4> wheelsVel = H_0 * carVel;
    reachWheelsVelocity(wheelsVel);
}

void Car::reachWheelsVelocity(Matrix<4> wheelsVel)
{
    currentMillis = millis();
    unsigned long diff = currentMillis - previousMillis;
    if (diff > period)
    {
        previousMillis = currentMillis;

        findCarPose();
        double dt = (double)diff / 1000; // millis to seconds
        w1->reachVelocity(wheelsVel(0), dt);
        w2->reachVelocity(wheelsVel(1), dt);
        w3->reachVelocity(wheelsVel(2), dt);
        w4->reachVelocity(wheelsVel(3), dt);
    }
}

void Car::update()
{
    // findCarPose();
    reachCarVelocity(*desiredCarVelocity);
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
