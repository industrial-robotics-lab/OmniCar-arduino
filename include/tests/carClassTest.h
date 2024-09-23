#include <PinChangeInterrupt.h>
#include "Car.h"
#include "config.h"

Matrix<3> desiredCarVelocity;
Matrix<3> odomPose;
Matrix<WHEELS_COUNT> jointAngles;
Matrix<WHEELS_COUNT> jointVelocities;

unsigned long wheelPeriod = UPDATE_STATE_DT_MS; // millis
Car car(WHEELBASE_LENGTH / 2, WHEELBASE_WIDTH / 2, OMNIWHEEL_DIAMETER / 2, UPDATE_STATE_DT_MS, &desiredCarVelocity, &jointAngles, &jointVelocities, &odomPose);
void updateW1A() { car.wheels[0]->triggerA(); }
void updateW1B() { car.wheels[0]->triggerB(); }
void updateW2A() { car.wheels[1]->triggerA(); }
void updateW2B() { car.wheels[1]->triggerB(); }


void setup()
{
    attachPCINT(digitalPinToPCINT(car.wheels[0]->getEncPinA()), updateW1A, RISING);
    attachPCINT(digitalPinToPCINT(car.wheels[0]->getEncPinB()), updateW1B, RISING);
    attachInterrupt(digitalPinToInterrupt(car.wheels[1]->getEncPinA()), updateW2A, RISING);
    attachInterrupt(digitalPinToInterrupt(car.wheels[1]->getEncPinB()), updateW2B, RISING);
    //attachPCINT(digitalPinToPCINT(car.wheels[2]->getEncPinA()), updateW3A, RISING);
    //attachPCINT(digitalPinToPCINT(car.wheels[2]->getEncPinB()), updateW3B, RISING);
    //attachInterrupt(digitalPinToInterrupt(car.wheels[3]->getEncPinA()), updateW4A, RISING);
    //attachInterrupt(digitalPinToInterrupt(car.wheels[3]->getEncPinB()), updateW4B, RISING);

    Serial.begin(38400);
    Serial.setTimeout(100);
}

void loop()
{
    //                     t  x  y
    car.setDesiredVelocity(0.0, 0.2, 0); // 5, 1, 1
    auto t1 = millis();
    car.update();
    auto t2 = millis();
   // Serial.print("Time for car update: ");
    //Serial.println(t2-t1);
    Serial.print("Odom pose: ");
    Serial.print(jointVelocities(0));
    Serial.print(" ");
    Serial.println(jointVelocities(1));
    // delay(1000);
}
