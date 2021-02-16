#include "Arduino.h"
#include "Wheel.h"

Wheel::Wheel(int motorNum, int encPinA, int encPinB, bool isClockwise)
{
    // 1900 - stability limit for motor 1
    // kP = 1140; kI = 3040; kD = 107; // position PID
    kP = 1; kI = 5; kD = 0.01; // velocity PID

    this->motor = new Motor(motorNum);
    this->encoder = new Encoder(encPinA, encPinB, isClockwise);
    this->pid = new PID(&pidFeedback, &pidOutput, &pidSetpoint, kP, kI, kD, DIRECT);
    pid->SetMode(AUTOMATIC);
    pid->SetOutputLimits(-255, 255);
    // pid->SetSampleTime(intervalMillis); // in millis
    // pid->SetTunings(1, 2, 3);
    // pid->SetControllerDirection(DIRECT);
}
Wheel::~Wheel()
{
    delete motor;
    delete encoder;
    delete pid;
}

void Wheel::setValue(int value) {
    motor->setValue(value);
}

void Wheel::reachVelocity(double desiredVelocity, float dt)
{
    double revolutions = (double)encoder->getTicks() / TICKS_PER_REV;
    double linearDistance = PI * DIAMETER * revolutions;
    currentVelocity = linearDistance / dt;
    pidFeedback = currentVelocity;
    pidSetpoint = desiredVelocity;
    pid->Compute();
    motor->setValue(pidOutput);
}

void Wheel::triggerA() { encoder->triggerA(); }
void Wheel::triggerB() { encoder->triggerB(); }
void Wheel::resetEncoder() { encoder->reset(); }

double Wheel::getPidOutput() { return pidOutput; }
double Wheel::getCurrentVelocity() { return currentVelocity; }
long Wheel::getTicks() { return encoder->getTicks(); }
int Wheel::getEncPinA() { return encoder->getPinA(); }
int Wheel::getEncPinB() { return encoder->getPinB(); }