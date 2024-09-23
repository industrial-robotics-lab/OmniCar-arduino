#pragma once

#include "Wheel.h"
#include "omnimath.h"

#define WHEELS_COUNT 2

class Car
{
private:
    unsigned long updatePeriod;
    unsigned long currentMillis;
    unsigned long previousMillis;
    unsigned long diff;

    float wheelRadius;

    double dt;
    Matrix<3, 1, float> *desiredCarVelocity;
    Matrix<WHEELS_COUNT, 1, float> *jointAngles;
    Matrix<WHEELS_COUNT, 1, float> *jointVelocities;
    Matrix<3, 1, float>  *odomPose;

    Matrix<WHEELS_COUNT, 1, float> lastJointAngles;

    Matrix<3, WHEELS_COUNT, float> Jac;
    Matrix<WHEELS_COUNT, 3, float> invJac;

    // For odometry estimation
    Matrix<6, 1, float> vb6;
    Matrix<4, 4, float> currentTf;
    Matrix<4, 4, float> displacementTf;


    void estimateOdomPose(); // forward kinematics
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
        Matrix<WHEELS_COUNT, 1, float> *jointAngles,
        Matrix<WHEELS_COUNT, 1, float> *jointVelocities,
        Matrix<3, 1, float> *odomPose);
    ~Car();
    void setDesiredVelocity(float vX, float vY, float vTheta);
    void setMotorsPWM(Matrix<WHEELS_COUNT, 1, float> &motorsPwm);
    void update();
    void resetOdom();

};