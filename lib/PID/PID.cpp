#include "Arduino.h"
#include "PID.h"

PID::PID(float kP, float kI, float kD, float uMax, float vMax, float h) {
    this->kP = kP;
    this->kI = kI;
    this->kD = kD;

    this->uMax = uMax;
    this->vMax = vMax;
    this->h = h;
}

float PID::calc(float e) {
    float uP = kP*e;
    float uI = uIPrev + kI*h*e;
    float uD = kD * (e - ePrev)/h;
    u = uP + uI + uD;
    
    // if (u > uMax) {
    //     uI = uIPrev;
    //     u = uMax;
    // }
    // limitSpeed(u);

    ePrev = e;
    uPrev = u;
    uIPrev = uI;
    return u;
}

void PID::limitSpeed(float u) {
    v = (u - uPrev)/h;
    if (abs(v) > vMax) {
        u = uPrev + h*vMax*sign(v);
    } else {
        u = uPrev + v*h;
    }
    v = (u - uPrev)/h;
}

int PID::sign(float value) {
    return int((value > 0) - (value < 0));
}