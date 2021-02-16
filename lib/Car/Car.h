#include "Wheel.h"
#include "omnimath.h"

#define TRACK 175.0
#define WHEELBASE 165.0
#define DIAMETER 60

class Car
{
private:
    float *desiredPtr;
    float *feedbackPtr;
    Wheel *w1;
    Wheel *w2;
    Wheel *w3;
    Wheel *w4;
    Matrix<4,3> H_0;
    Matrix<3,4> F;

public:
    Car(float w, float l, float r, int encoderPins[8], int intervalMillis, float *desired, float *feedback);
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