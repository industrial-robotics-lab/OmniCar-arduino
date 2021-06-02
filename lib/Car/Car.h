#include "Wheel.h"
#include "omnimath.h"

#define TRACK 175.0 / 1000     // mm to m
#define WHEELBASE 165.0 / 1000 // mm to m
#define DIAMETER 60.0 / 1000   // mm to m

class Car
{
private:
    unsigned long period;
    unsigned long currentMillis;
    unsigned long previousMillis;
    unsigned long diff;
    unsigned int odomCounter;
    float fi;
    double dt;
    Matrix<3> *desiredCarVelocity;
    Matrix<3> *feedbackCarPose;
    Matrix<4, 4> G; // global transformation
    Wheel *w1;
    Wheel *w2;
    Wheel *w3;
    Wheel *w4;
    Matrix<3> vb;
    Matrix<6> vb6;
    Matrix<4, 4> prevToCurrPose;
    Matrix<4> wheelsVel;
    Matrix<3, 3> R_fi;
    Matrix<4, 3> H_0;
    Matrix<3, 4> F;
    Matrix<4> wheelsDisplacement;

    void findCarPose(); // forward kinematics
    void reachCarVelocity(Matrix<3> carVel); // inverse kinematics
    void reachWheelsAngularVelocity(Matrix<4> wheelsVel);

public:
    Car(
        float w,
        float l,
        float r,
        unsigned long wheelPeriod,
        Matrix<3> *desiredVelocity,
        Matrix<3> *feedbackPose);
    ~Car();
    void setDesiredVelocity(float vX, float vY, float vTheta);
    void setValues(int v1, int v2, int v3, int v4);
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