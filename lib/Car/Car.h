#pragma once

#include "Wheel.h"
#include "omnimath.h"

#define WHEELS_COUNT 4

class Car
{
private:
    unsigned long updatePeriod;
    unsigned long currentMillis;
    unsigned long previousMillis;
    unsigned long diff;
    unsigned int odomCounter;

    float wheelRadius;

    double dt;
    Matrix<3, 1, float> *desiredCarVelocity;
    Matrix<WHEELS_COUNT, 1, float> *jointAngles;
    Matrix<WHEELS_COUNT, 1, float> *jointVelocities;

    Matrix<WHEELS_COUNT, 1, float> lastJointAngles;

    Matrix<4, 3, float> Jac;
    Matrix<3, 4, float> invJac;

    // For odometry estimation
    Matrix<6, 1, float> vb6;
    Matrix<4, 4, float> currentTf;
    Matrix<4, 4, float> displacementTf;


    void estimateOdomPose(); // forward kinematics
    void reachCarVelocity(Matrix<3, 1, float> &carVel); // inverse kinematics
    void reachWheelsAngularVelocity(Matrix<WHEELS_COUNT, 1, float> &wheelsVel);

public:
    Wheel * wheels[WHEELS_COUNT];
    Matrix<3, 1, float> odomPose;

    Car(
        float w,
        float l,
        float r,
        unsigned long wheelPeriod,
        Matrix<3, 1, float> *desiredVelocity,
        Matrix<4, 1, float> *jointAngles,
        Matrix<4, 1, float> *jointVelocities);
    ~Car();
    void setDesiredVelocity(float vX, float vY, float vTheta);
    void setMotorsPWM(Matrix<WHEELS_COUNT, 1, float> &motorsPwm);
    void update();
    void resetOdom();

};