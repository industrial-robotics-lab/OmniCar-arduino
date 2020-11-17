#include "Wheel.h"

class Car
{
private:
    float desiredRpms[4] = {}; // init with zeros
    float feedbackRpms[4] = {}; // init with zeros
    Wheel *w1;
    Wheel *w2;
    Wheel *w3;
    Wheel *w4;

public:
    Car(int encoderPins[4], int intervalMillis);
    ~Car();
    float* getFeedbackRpms();
    void setDesiredRpms(float[4]);
    void updateFeedbackRpms();
    void reachDesiredRpms();

    int getEncPin1();
    int getEncPin2();
    int getEncPin3();
    int getEncPin4();

    void incEnc1();
    void incEnc2();
    void incEnc3();
    void incEnc4();
};