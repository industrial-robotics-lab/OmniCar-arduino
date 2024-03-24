#include "Pid.h"

PID::PID(float kP, float kD, float kI, float dt)
:kP(kP), kD(kD), kI(kI), dt(dt) {
    // AntiWindUp
    maxIntegralValue = -1;

    minOutput = -1;
    maxOutput = -1;
    reset();
}

void PID::update(float desiredValue, float currentValue){
    lastlastError = lastError;
    lastError = currentError;
    currentError = desiredValue - currentValue;
    integralValue += (currentError+lastError)/2.0*dt*kI;
    if(maxIntegralValue != -1){
        integralValue = constrain(integralValue, -maxIntegralValue, maxIntegralValue);
    }
    // Using Lagrange 3-order polinomial 
    dError = 1.0/(2.0*dt)*(lastlastError - 4.0*lastError + 3.0*currentError);
    if (abs(currentError)<1.0e-5){
        integralValue = 0.0;
    }
    unclippedOutput = kP*currentError;
    output = constrain(unclippedOutput, minOutput, maxOutput);
}

void PID::reset(){
    integralValue = 0.0;

    currentError = 0.0;
    lastError = 0.0;
    lastlastError = 0.0;
    dError = 0.0;

    unclippedOutput = 0.0;
    output = 0.0;
}
void PID::setOutputLimits(float min, float max){
    if(max>min){
        minOutput = min;
        maxOutput = max;
    }
}
void PID::setMaxIntegralValue(float imaxIntegralValue){
    if(imaxIntegralValue > 0.0){
        maxIntegralValue = imaxIntegralValue;
    }
}
void PID::setPidParams(float ikP, float ikD, float ikI){
    if(ikP > 0.0){
        this->kP = ikP;
    }
    if(kD > 0.0){
        this->kD = ikD;
    }
    if(ikI > 0.0){
        this->kI = ikI;
    }
}