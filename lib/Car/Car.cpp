#include "Car.h"
#include "config.h"

#define TWO_PI_F 6.283185f

Car::Car(
    float w,
    float l,
    float r,
    unsigned long wheelPeriod,
    Matrix<3,1, float> *desiredVelocity,
    Matrix<3,1, float> *feedbackPose)
    : period(wheelPeriod),
      desiredCarVelocity(desiredVelocity),
      feedbackCarPose(feedbackPose)
{
    G = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    *(wheels + 0) = new Wheel(1, ENC_MOTOR1_PINA, ENC_MOTOR1_PINB, true, WHEEL_KP, WHEEL_KI, WHEEL_KD, UPDATE_STATE_DT_MS/1000.0);
    *(wheels + 1) = new Wheel(2, ENC_MOTOR2_PINA, ENC_MOTOR2_PINB, true, WHEEL_KP, WHEEL_KI, WHEEL_KD, UPDATE_STATE_DT_MS/1000.0);
    *(wheels + 2) = new Wheel(3, ENC_MOTOR3_PINA, ENC_MOTOR3_PINB, true, WHEEL_KP, WHEEL_KI, WHEEL_KD, UPDATE_STATE_DT_MS/1000.0);
    *(wheels + 3) = new Wheel(4, ENC_MOTOR4_PINA, ENC_MOTOR4_PINB, true, WHEEL_KP, WHEEL_KI, WHEEL_KD, UPDATE_STATE_DT_MS/1000.0);
    vb.Fill(0);
    vb6.Fill(0);
    // q.Fill(0);
    // dqb.Fill(0);
    // dq.Fill(0);
    // fi_k = 0;

    float lw = l + w;
    H_0 = {-lw, 1, -1, lw, 1, 1, lw, 1, -1, -lw, 1, 1};
    H_0 /= r;
    fi = 0;
    R_fi = {1, 0, 0, 0, cos(fi), sin(fi), 0, -sin(fi), cos(fi)};
    float ilw = 1.0 / lw;
    F = {-ilw, ilw, ilw, -ilw, 1, 1, 1, 1, -1, 1, -1, 1};
    F *= r / 4;
}
Car::~Car()
{
    delete wheels;
}

void Car::setDesiredVelocity(float vFi, float vX, float vY)
{
    *desiredCarVelocity = {vFi, vX, vY};
}

void Car::findCarPose()
{
    vb = F * wheelsDisplacement * TWO_PI_F;

    // - Two position estimation methods
    // -- First method
    // vb6 = {0, 0, vb(0), vb(1), vb(2), 0};
    vb6(2) = vb(0);
    vb6(3) = vb(1);
    vb6(4) = vb(2);
    T = vec6_to_SE3(vb6);
    G *= T;
    // *feedbackCarPose = {atan2(G(1, 0), G(0, 0)), G(0, 3), G(1, 3)};
    *feedbackCarPose = {atan2(G(1, 0), G(0, 0)), -G(1, 3), G(0, 3)}; // reversed axes for convenient map visualization

    // -- Second method
    // if(vb(0) == 0) {
    //     dqb(0) = 0;
    //     dqb(1) = vb(1);
    //     dqb(2) = vb(2);
    // }
    // else
    // {
    //     dqb(0) = vb(0);
    //     dqb(1) = (vb(1)*sin(vb(0)) + vb(2)*(cos(vb(0))-1)) / vb(0);
    //     dqb(2) = (vb(2)*sin(vb(0)) + vb(1)*(1-cos(vb(0)))) / vb(0);
    //     fi_k += dqb(0);
    // }
    // Matrix<3, 3> R = {1, 0, 0, 0, cos(fi_k), -sin(fi_k), 0, sin(fi_k), cos(fi_k)};
    // dq = R * dqb;
    // q += dq;
    // *feedbackCarPose = {q(0), -q(2), q(1)}; // reversed axes for map visualization
}

void Car::setMotorsPWM(Matrix<WHEELS_COUNT, 1, int> &motorsPWM)
{
    for (uint8_t i=0; i<WHEELS_COUNT; i++){
        wheels[i]->setMotorControl(motorsPWM(i));
    }
}

void Car::reachCarVelocity(Matrix<3,1, float> &carVel)
{
    // === Method 1: global velocity ===
    // fi = (*feedbackCarPose)(0);
    // R_fi(1, 1) = cos(fi);
    // R_fi(1, 2) = sin(fi);
    // R_fi(2, 1) = -sin(fi);
    // R_fi(2, 2) = cos(fi);
    // wheelsVel = H_0 * R_fi * carVel;

    // === Method 2: local velocity ===
    wheelsVel = H_0 * carVel;
    
    reachWheelsAngularVelocity(wheelsVel);
}

void Car::reachWheelsAngularVelocity(Matrix<WHEELS_COUNT, 1, float> & wheelsVel)
{
    currentMillis = millis();
    diff = currentMillis - previousMillis;
    if (diff >= period)
    {
        previousMillis = currentMillis;
        dt = (double)diff / 1000.0; // millis to seconds
        for(uint8_t wi = 0; wi < WHEELS_COUNT; wi++){
            wheelsDisplacement(wi) = wheels[wi]->reachAngularVelocity(wheelsVel(wi), dt);
        }
        odomCounter++;
        if (odomCounter == 1)
        {
            findCarPose();
            wheelsDisplacement.Fill(0);
            odomCounter = 0;
        }
    }
}

void Car::update()
{
    reachCarVelocity(*desiredCarVelocity);
}
