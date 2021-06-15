#include "Car.h"

Car::Car(
    float w,
    float l,
    float r,
    unsigned long wheelPeriod,
    Matrix<3> *desiredVelocity,
    Matrix<3> *feedbackPose)
    : period(wheelPeriod),
      desiredCarVelocity(desiredVelocity),
      feedbackCarPose(feedbackPose)
{
    G = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    w1 = new Wheel(1, 18, 19, false);
    w2 = new Wheel(2, 20, 21, true);
    w3 = new Wheel(3, 50, 52, true);
    w4 = new Wheel(4, 51, 53, false);
    vb.Fill(0);
    vb6.Fill(0);
    // q.Fill(0);
    // dqb.Fill(0);
    // dq.Fill(0);
    // fi_k = 0;

    float lw = l + w;
    H_0 = {-lw, 1, -1, lw, 1, 1, lw, 1, -1, -lw, 1, 1};
    H_0 /= r;
    fi = 0;
    R_fi = {1, 0, 0, 0, cos(fi), sin(fi), 0, -sin(fi), cos(fi)};
    float ilw = 1.0 / lw;
    F = {-ilw, ilw, ilw, -ilw, 1, 1, 1, 1, -1, 1, -1, 1};
    F *= r / 4;
}
Car::~Car()
{
    delete w1;
    delete w2;
    delete w3;
    delete w4;
}

void Car::setDesiredVelocity(float vFi, float vX, float vY)
{
    *desiredCarVelocity = {vFi, vX, vY};
}

void Car::findCarPose()
{
    vb = F * wheelsDisplacement * TWO_PI;

    // - Two position estimation methods
    // -- First method
    // vb6 = {0, 0, vb(0), vb(1), vb(2), 0};
    vb6(2) = vb(0);
    vb6(3) = vb(1);
    vb6(4) = vb(2);
    T = vec6_to_SE3(vb6);
    G *= T;
    // *feedbackCarPose = {atan2(G(1, 0), G(0, 0)), G(0, 3), G(1, 3)};
    *feedbackCarPose = {atan2(G(1, 0), G(0, 0)), -G(1, 3), G(0, 3)}; // reversed axes for convenient map visualization

    // -- Second method
    // if(vb(0) == 0) {
    //     dqb(0) = 0;
    //     dqb(1) = vb(1);
    //     dqb(2) = vb(2);
    // }
    // else
    // {
    //     dqb(0) = vb(0);
    //     dqb(1) = (vb(1)*sin(vb(0)) + vb(2)*(cos(vb(0))-1)) / vb(0);
    //     dqb(2) = (vb(2)*sin(vb(0)) + vb(1)*(1-cos(vb(0)))) / vb(0);
    //     fi_k += dqb(0);
    // }
    // Matrix<3, 3> R = {1, 0, 0, 0, cos(fi_k), -sin(fi_k), 0, sin(fi_k), cos(fi_k)};
    // dq = R * dqb;
    // q += dq;
    // *feedbackCarPose = {q(0), -q(2), q(1)}; // reversed axes for map visualization
}

void Car::setValues(int v1, int v2, int v3, int v4)
{
    w1->setValue(v1);
    w2->setValue(v2);
    w3->setValue(v3);
    w4->setValue(v4);
}

void Car::reachCarVelocity(Matrix<3> carVel)
{
    // === Method 1: global velocity ===
    // fi = (*feedbackCarPose)(0);
    // R_fi(1, 1) = cos(fi);
    // R_fi(1, 2) = sin(fi);
    // R_fi(2, 1) = -sin(fi);
    // R_fi(2, 2) = cos(fi);
    // wheelsVel = H_0 * R_fi * carVel;

    // === Method 2: local velocity ===
    wheelsVel = H_0 * carVel;
    
    reachWheelsAngularVelocity(wheelsVel);
}

void Car::reachWheelsAngularVelocity(Matrix<4> wheelsVel)
{
    currentMillis = millis();
    diff = currentMillis - previousMillis;
    if (diff >= period)
    {
        previousMillis = currentMillis;
        dt = (double)diff / 1000; // millis to seconds
        wheelsDisplacement(0) += w1->reachAngularVelocity(wheelsVel(0), dt);
        wheelsDisplacement(1) += w2->reachAngularVelocity(wheelsVel(1), dt);
        wheelsDisplacement(2) += w3->reachAngularVelocity(wheelsVel(2), dt);
        wheelsDisplacement(3) += w4->reachAngularVelocity(wheelsVel(3), dt);
        odomCounter++;
        if (odomCounter == 1)
        {
            findCarPose();
            wheelsDisplacement.Fill(0);
            odomCounter = 0;
        }
    }
}

void Car::update()
{
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
