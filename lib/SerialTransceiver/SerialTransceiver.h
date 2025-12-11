#pragma once

#include <Arduino.h>
#include <BasicLinearAlgebra.h>
#include "omnimath.h"

using namespace BLA;

class SerialTransceiver
{
private:

    Matrix<3> *desiredVelocity;
    Matrix<4> *jointAngles;
    Matrix<4> *jointVelocities;
    Matrix<3> *odomPose;

    float *stateVector;
    uint8_t bufferOutSize;

    float *controlVector;
    byte *bufferIn;
    uint8_t bufferInSize;
    
    byte readChecksum;
    byte calcChecksum;
    void rx();
    void tx();

public:
    SerialTransceiver(Matrix<3> *desiredVelocity, Matrix<4> *jointAngles, Matrix<4> *jointVelocities, Matrix<3> *odomPose);
    void talk();
};
