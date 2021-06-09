#include "Arduino.h"
#include "Wheel.h"

Wheel::Wheel(
    unsigned int motorNum,
    unsigned int encPinA,
    unsigned int encPinB,
    bool isClockwise)
{
    // 1900 - stability limit for motor 1
    // kP = 1140; kI = 3040; kD = 107; // position PID

    // kP = 50; kI = 800; kD = 5; // angular velocity PID (crazy on heap to zero)

    kP = 50;
    kI = 500;
    kD = 0; // angular velocity PID

    // kP = 300;
    // kI = 800;
    // kD = 5; // linear velocity PID

    this->motor = new Motor(motorNum);
    this->encoder = new Encoder(encPinA, encPinB, isClockwise);
    this->pid = new PID(&pidFeedback, &pidOutput, &pidSetpoint, kP, kI, kD, DIRECT);
    pid->SetMode(AUTOMATIC);
    pid->SetOutputLimits(-255, 255);
    // pid->SetSampleTime(intervalMillis); // in millis
    // pid->SetTunings(1, 2, 3);
    // pid->SetControllerDirection(DIRECT);

    currentMillis = 0;
    previousMillis = 0;
}
Wheel::~Wheel()
{
    delete motor;
    delete encoder;
    delete pid;
}

void Wheel::setValue(int value)
{
    motor->setValue(value);
}

double Wheel::reachAngularVelocity(double desiredAngularVelocity, double dt)
{
    long rawTicks = encoder->getTicks();
    if (abs(rawTicks) < 150) // max ticks for 40 millis period = ~130-140
    {
        ticks = rawTicks;
    }
    resetEncoder();
    revolutions = (double)ticks / TICKS_PER_REV;
    currentAngularVelocity = revolutions / dt;
    pidFeedback = currentAngularVelocity;
    pidSetpoint = desiredAngularVelocity;
    pid->Compute();
    motor->setValue((int)pidOutput);
    return revolutions;
}

void Wheel::triggerA() { encoder->triggerA(); }
void Wheel::triggerB() { encoder->triggerB(); }
void Wheel::resetEncoder() { encoder->reset(); }

double Wheel::getPidOutput() { return pidOutput; }
double Wheel::getCurrentLinearVelocity() { return currentAngularVelocity; }
int Wheel::getEncPinA() { return encoder->getPinA(); }
int Wheel::getEncPinB() { return encoder->getPinB(); }