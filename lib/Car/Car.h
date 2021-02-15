#include "Wheel.h"

class Car
{
private:
    float *desiredPtr;
    float *feedbackPtr;
    Wheel *w1;
    Wheel *w2;
    Wheel *w3;
    Wheel *w4;

public:
    Car(int encoderPins[8], int intervalMillis, float *desired, float *feedback);
    ~Car();
    void setValues(double v1, double v2, double v3, double v4);

    int getEncPin1A();
    int getEncPin1B();
    int getEncPin2A();
    int getEncPin2B();
    int getEncPin3A();
    int getEncPin3B();
    int getEncPin4A();
    int getEncPin4B();

    void incEnc1A();
    void incEnc1B();
    void incEnc2A();
    void incEnc2B();
    void incEnc3A();
    void incEnc3B();
    void incEnc4A();
    void incEnc4B();
};