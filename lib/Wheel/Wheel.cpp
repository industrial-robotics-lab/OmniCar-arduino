#include "Wheel.h"

Wheel::Wheel(
    unsigned int motorNum,
    unsigned int encPinA,
    unsigned int encPinB,
    bool isClockwise,
    double kP,
    double kI,
    double kD,
    double dt
) {
    // 1900 - stability limit for motor 1
    // kP = 1140; kI = 3040; kD = 107; // position PID

    // kP = 50; kI = 800; kD = 5; // angular velocity PID (crazy on heap to zero)


    // kP = 300;
    // kI = 800;
    // kD = 5; // Angular velocity PID

    this->motor = new Motor(motorNum, 60);
    this->encoder = new Encoder(encPinA, encPinB, isClockwise);
    this->pid = new PID(kP, kI, kD, dt);
    pid->setOutputLimits(-1.0, 1.0);
    pid->setMaxIntegralValue(0.2);

    currentMillis = 0;
    previousMillis = 0;
    currentAngularVelocity = 0.0;
    lastAngularVelocity = 0.0;
    currentAngle = encoder->getAngle();
    lastAngle = currentAngle;
    lastlastAngle = currentAngle;
}
Wheel::~Wheel()
{
    delete motor;
    delete encoder;
    delete pid;
}

void Wheel::setMotorControl(float pwm)
{
    motor->setMotorControl(pwm);
}

float Wheel::reachAngularVelocity(float desiredAngularVelocity, float dt)
{
    float currentAngle = encoder->getAngle();
    lastlastAngle = lastAngle;
    lastAngle = currentAngle;
    // Using Lagrange 3-order polinomial  interpolation
    currentAngularVelocity = 1.0/(2.0*dt)*(lastlastAngle - 4.0*lastAngle + 3.0*currentAngle);;
    pid->update(desiredAngularVelocity, currentAngularVelocity);
    pidOutput = pid->output;
    motor->setMotorControl(pidOutput);
    
    lastAngularVelocity = currentAngularVelocity;
    return currentAngularVelocity;
}


void Wheel::triggerA() { encoder->triggerA(); }
void Wheel::triggerB() { encoder->triggerB(); }
void Wheel::resetEncoder() { encoder->reset(); }

float Wheel::getPidOutput() { return pidOutput; }
float Wheel::getSendedPWM() { return motor->getSendedPWM(); }
float Wheel::getCurrentAngularVelocity() { return currentAngularVelocity; }
float Wheel::getCurrentAngle() { return encoder->getAngle(); }
int Wheel::getEncPinA() { return encoder->getPinA(); }
int Wheel::getEncPinB() { return encoder->getPinB(); }