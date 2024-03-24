#include <math.h>
#include <stdlib.h>
#include <Arduino.h>

class PID
{
private:
    float kP = 1.0;
    float kI = 0.0;
    float kD = 0.0;
    float dt;
    float maxIntegralValue;

    float integralValue;
    float lastError;
    float lastlastError;
    float currentError;
    float dError;

    float minOutput;
    float maxOutput;

    float unclippedOutput;

public:
    float output;

    PID(float kP, float kD = 0.0, float kI = 0.0, float dt = 0.05);
    void update(float desiredValue, float currentValue);
    void reset();
    void setOutputLimits(float min, float max);
    void setMaxIntegralValue(float imaxIntegralValue);
    void setPidParams(float ikP, float ikD = -1.0, float ikI = -1.0);
};
