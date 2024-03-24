#pragma once

#include "Wheel.h"
#include "omnimath.h"

#define WHEELS_COUNT 4

class Car
{
private:
    unsigned long period;
    unsigned long currentMillis;
    unsigned long previousMillis;
    unsigned long diff;
    unsigned int odomCounter;
    float fi;
    double dt;
    Matrix<3, 1, float> *desiredCarVelocity;
    Matrix<3, 1, float> *feedbackCarPose;
    Matrix<4, 4> G; // global transformation
    Matrix<3, 1, float> vb;
    Matrix<6, 1, float> vb6;
    Matrix<4, 4, float> T;
    // Matrix<3> q;
    // Matrix<3> dqb;
    // Matrix<3> dq;
    // float fi_k;
    Matrix<WHEELS_COUNT, 1, float> wheelsVel;
    Matrix<3, 3, float> R_fi;
    Matrix<4, 3, float> H_0;
    Matrix<3, 4, float> F;
    Matrix<WHEELS_COUNT, 1, float> wheelsDisplacement;

    void findCarPose(); // forward kinematics
    void reachCarVelocity(Matrix<3, 1, float> &carVel); // inverse kinematics
    void reachWheelsAngularVelocity(Matrix<WHEELS_COUNT, 1, float> &wheelsVel);

public:
    Wheel * wheels[WHEELS_COUNT];

    Car(
        float w,
        float l,
        float r,
        unsigned long wheelPeriod,
        Matrix<3, 1, float> *desiredVelocity,
        Matrix<3, 1, float> *feedbackPose);
    ~Car();
    void setDesiredVelocity(float vX, float vY, float vTheta);
    void setMotorsPWM(Matrix<WHEELS_COUNT, 1, int> &motorsPwm);
    void update();
};