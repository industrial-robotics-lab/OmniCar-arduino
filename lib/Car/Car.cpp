#include "Car.h"
#include "config.h"

#define TWO_PI_F 6.283185f

Car::Car(
    float w,
    float l,
    float r,
    unsigned long updatePeriod,
    Matrix<3,1, float> *desiredVelocity,
    Matrix<4,1, float> *jointAngles,
    Matrix<4,1, float> *jointVelocities
) : updatePeriod(updatePeriod),
      desiredCarVelocity(desiredVelocity),
      jointAngles(jointAngles),
      jointVelocities(jointVelocities),
      wheelRadius(r)
{
    *(wheels + 0) = new Wheel(1, ENC_MOTOR1_PINA, ENC_MOTOR1_PINB, true, WHEEL_KP, WHEEL_KI, WHEEL_KD, UPDATE_STATE_DT_MS/1000.0);
    *(wheels + 1) = new Wheel(2, ENC_MOTOR2_PINA, ENC_MOTOR2_PINB, true, WHEEL_KP, WHEEL_KI, WHEEL_KD, UPDATE_STATE_DT_MS/1000.0);
    *(wheels + 2) = new Wheel(3, ENC_MOTOR3_PINA, ENC_MOTOR3_PINB, true, WHEEL_KP, WHEEL_KI, WHEEL_KD, UPDATE_STATE_DT_MS/1000.0);
    *(wheels + 3) = new Wheel(4, ENC_MOTOR4_PINA, ENC_MOTOR4_PINB, true, WHEEL_KP, WHEEL_KI, WHEEL_KD, UPDATE_STATE_DT_MS/1000.0);
    
    vb6.Fill(0);
    currentTf = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

    float lw = l + w;
    float ilw = 1.0 / lw;
    Jac = {-lw, 1, -1, lw, 1, 1, lw, 1, -1, -lw, 1, 1};
    Jac /= wheelRadius;
    invJac = {-ilw, ilw, ilw, -ilw, 1, 1, 1, 1, -1, 1, -1, 1};
    invJac *= wheelRadius / 4;
    
    resetOdom();
}
Car::~Car()
{
    delete wheels;
}

void Car::setDesiredVelocity(float vFi, float vX, float vY)
{
    *desiredCarVelocity = {vFi, vX, vY};
}

void Car::estimateOdomPose()
{
    Matrix<4,1, float> jointsAngleDisplacement;
    Matrix<3,1, float> cartPoseDisplacement;
    jointsAngleDisplacement = *jointAngles - lastJointAngles;

    cartPoseDisplacement = invJac*jointsAngleDisplacement;
    vb6(5) = cartPoseDisplacement(0);
    vb6(0) = cartPoseDisplacement(1);
    vb6(1) = cartPoseDisplacement(2);
    displacementTf = vec6_to_SE3(vb6);
    currentTf *= displacementTf;
    // *feedbackCarPose = {atan2(G(1, 0), G(0, 0)), G(0, 3), G(1, 3)};
    odomPose = {atan2(currentTf(1, 0), -currentTf(0, 0)), currentTf(1), currentTf(2)};
}

void Car::setMotorsPWM(Matrix<WHEELS_COUNT, 1, float> &motorsPWM)
{
    for (uint8_t i=0; i<WHEELS_COUNT; i++){
        wheels[i]->setMotorControl(motorsPWM(i));
    }
}

void Car::reachCarVelocity(Matrix<3,1, float> &carVel)
{
    if(abs(carVel(0))>0.75){
        carVel(0) = copysignf(0.5, carVel(0));
    }
    for(uint8_t i = 1; i<3; i++){
        if(abs(carVel(i))>0.5){
            carVel(i) = copysignf(0.5, carVel(i));
        }
    }
    *jointVelocities = Jac * carVel;
    reachWheelsAngularVelocity(*jointVelocities);
}

void Car::reachWheelsAngularVelocity(Matrix<WHEELS_COUNT, 1, float> & wheelsVel)
{
    currentMillis = millis();
    diff = currentMillis - previousMillis;
    if (diff >= updatePeriod)
    {
        previousMillis = currentMillis;
        dt = (double)diff / 1000.0; // millis to seconds
        for(uint8_t wi = 0; wi < WHEELS_COUNT; wi++){
            lastJointAngles(wi) = (*jointAngles)(wi);
            (*jointAngles)(wi) = wheels[wi]->getCurrentAngle();
            (*jointVelocities)(wi) += wheels[wi]->reachAngularVelocity(wheelsVel(wi), dt);
        }
        estimateOdomPose();
    }
}

void Car::resetOdom(){
    currentTf = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    odomPose.Fill(0);
}

void Car::update()
{
    reachCarVelocity(*desiredCarVelocity);
}
