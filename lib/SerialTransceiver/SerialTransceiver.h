#pragma once

#include <Arduino.h>
#include <BasicLinearAlgebra.h>
#include "omnimath.h"

using namespace BLA;

class SerialTransceiver
{
private:
    float maxLinSpeed;
    float maxAngSpeed;
    float threshold;
    float fi, x, y;
    uint8_t controlVec[3] = {127, 127, 127};
    Matrix<3> *desiredVelocity;
    Matrix<3> *feedbackPose;
    byte buffer[14];
    byte readChecksum;
    byte calcChecksum;
    void rx();
    void tx();

public:
    SerialTransceiver(Matrix<3> *desired, Matrix<3> *feedback);
    void talk();
};