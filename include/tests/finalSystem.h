#include <PinChangeInterrupt.h>
#include <Thread.h>
#include "Car.h"
#include "SerialTransceiver.h"
#include "config.h"

Matrix<3> desiredCarVelocity;
Matrix<4> jointAngles;
Matrix<4> jointVelocities;

Car car(WHEELBASE_LENGTH / 2, WHEELBASE_WIDTH / 2, OMNIWHEEL_DIAMETER / 2, UPDATE_STATE_DT_MS, &desiredCarVelocity, &jointAngles, &jointVelocities);
void updateW1A() { car.wheels[0]->triggerA(); }
void updateW1B() { car.wheels[0]->triggerB(); }
void updateW2A() { car.wheels[1]->triggerA(); }
void updateW2B() { car.wheels[1]->triggerB(); }
void updateW3A() { car.wheels[2]->triggerA(); }
void updateW3B() { car.wheels[2]->triggerB(); }
void updateW4A() { car.wheels[3]->triggerA(); }
void updateW4B() { car.wheels[3]->triggerB(); }

SerialTransceiver transceiver(&desiredCarVelocity, &jointAngles, &jointVelocities);

Thread carThread = Thread();
Thread serialThread = Thread();

void updateCar() { car.update(); }
void talkSerial() { transceiver.talk(); }

void setup()
{
    attachPCINT(digitalPinToPCINT(car.wheels[0]->getEncPinA()), updateW1A, RISING);
    attachPCINT(digitalPinToPCINT(car.wheels[0]->getEncPinB()), updateW1B, RISING);
    attachInterrupt(digitalPinToInterrupt(car.wheels[1]->getEncPinA()), updateW2A, RISING);
    attachInterrupt(digitalPinToInterrupt(car.wheels[1]->getEncPinB()), updateW2B, RISING);
    attachPCINT(digitalPinToPCINT(car.wheels[2]->getEncPinA()), updateW3A, RISING);
    attachPCINT(digitalPinToPCINT(car.wheels[2]->getEncPinB()), updateW3B, RISING);
    attachInterrupt(digitalPinToInterrupt(car.wheels[3]->getEncPinA()), updateW4A, RISING);
    attachInterrupt(digitalPinToInterrupt(car.wheels[3]->getEncPinB()), updateW4B, RISING);

    desiredCarVelocity.Fill(0);
    jointAngles.Fill(0);

    Serial.begin(38400);
    Serial.setTimeout(100);

    carThread.onRun(updateCar);
    serialThread.onRun(talkSerial);
}

void loop()
{
    if (carThread.shouldRun())
    {
        carThread.run();
    }
    if (serialThread.shouldRun())
    {
        serialThread.run();
    }
}
