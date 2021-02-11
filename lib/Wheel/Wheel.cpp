#include "Arduino.h"
#include "Wheel.h"

Wheel::Wheel(int motorNum, int encPinA, int encPinB, bool isClockwise)
{
    // 1900 - stability limit for motor 1
    kP = 1140;
    kI = 3040;
    kD = 107;

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

void Wheel::updatePosition() {
    long encTicks = encoder->getTicks();
    position = TWO_PI * radius * ((double)encTicks / TICKS_PER_REV);
}

void Wheel::reachPosition(double desiredPosition)
{
    updatePosition();
    pidFeedback = position;
    pidSetpoint = desiredPosition;
    pid->Compute();
    motor->setValue(pidOutput);
}

void Wheel::triggerA() { encoder->triggerA(); }
void Wheel::triggerB() { encoder->triggerB(); }

double Wheel::getPidOutput() { return pidOutput; }
double Wheel::getPosition() { return position; }
int Wheel::getEncPinA() { return encoder->getPinA(); }
int Wheel::getEncPinB() { return encoder->getPinB(); }