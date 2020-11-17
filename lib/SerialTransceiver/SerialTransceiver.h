#include <Arduino.h>

class SerialTransceiver
{
private:
    float *desiredPtr;
    float *feedbackPtr;
    byte buffer[17];
    union { float f; byte b[4]; } n1;
    union { float f; byte b[4]; } n2;
    union { float f; byte b[4]; } n3;
    union { float f; byte b[4]; } n4;
    void rx();
    void tx();

public:
    SerialTransceiver(float *desired, float *feedback);
    void talk();
};