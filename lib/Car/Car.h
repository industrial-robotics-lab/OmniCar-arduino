#include "Wheel.h"

class Car
{
private:
    Wheel *w1;
    Wheel *w2;
    Wheel *w3;
    Wheel *w4;

public:
    Car(int mPin1, int mPin2, int mPin3, int mPin4, int ePin1, int ePin2, int ePin3, int ePin4, int intervalMillis);
    ~Car();
    void runForward(float rpm);

    int getEncPin1();
    int getEncPin2();
    int getEncPin3();
    int getEncPin4();

    void incEnc1();
    void incEnc2();
    void incEnc3();
    void incEnc4();

    float getRPM1();
    float getRPM2();
    float getRPM3();
    float getRPM4();
};