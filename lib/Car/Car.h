#include "Wheel.h"
// #include "omnimath.h"
#include <BasicLinearAlgebra.h>
using namespace BLA;

#define TRACK 175.0 / 1000     // mm to m
#define WHEELBASE 165.0 / 1000 // mm to m
#define DIAMETER 60.0 / 1000   // mm to m

class Car
{
private:
    Matrix<3> *desiredCarVelocity;
    Matrix<3> *feedbackCarVelocity;
    Wheel *w1;
    Wheel *w2;
    Wheel *w3;
    Wheel *w4;
    Matrix<4, 3> H_0;
    Matrix<3, 4> F;

    // Matrix<3> carVelocity; // Vb
    // Matrix<3> desiredCarVelocity;
    Matrix<4> wheelsDisplacement;
    void findCarVelocity();
    void reachCarVelocity(Matrix<3> carVel);
    void reachWheelsVelocity(Matrix<4> wheelsVel);

    unsigned long currentMillis;
    unsigned long previousMillis;

public:
    Car(float w, float l, float r, int intervalMillis, Matrix<3> *desiredVelocity, Matrix<3> *feedbackVelocity);
    ~Car();
    void setDesiredVelocity(float vX, float vY, float vTheta);
    void setValues(double v1, double v2, double v3, double v4);
    void update();

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