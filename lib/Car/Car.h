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
    void updateFeedbackRpms();
    void reachDesiredRpms();

public:
    Car(int encoderPins[4], int intervalMillis, float *desired, float *feedback);
    ~Car();
    void update();

    int getEncPin1();
    int getEncPin2();
    int getEncPin3();
    int getEncPin4();

    void incEnc1();
    void incEnc2();
    void incEnc3();
    void incEnc4();
};