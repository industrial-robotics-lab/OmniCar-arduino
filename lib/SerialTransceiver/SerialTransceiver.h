#include <Arduino.h>
#include <BasicLinearAlgebra.h>

using namespace BLA;

class SerialTransceiver
{
private:
    int maxValue;
    Matrix<3> *desiredVelocity;
    Matrix<3> *feedbackPose;
    byte buffer[14];
    byte checksum;
    union { float f; byte b[4]; } n1;
    union { float f; byte b[4]; } n2;
    union { float f; byte b[4]; } n3;
    void rx();
    void tx();

public:
    SerialTransceiver(Matrix<3> *desired, Matrix<3> *feedback);
    void talk();
};