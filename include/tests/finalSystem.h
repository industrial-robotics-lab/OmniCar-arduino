#include <PinChangeInterrupt.h>
#include <Thread.h>
#include "Car.h"
#include "SerialTransceiver.h"
#include "config.h"

Matrix<3> desiredCarVelocity;
Matrix<4> jointAngles;
Matrix<4> jointTicks;
Matrix<4> jointVelocities;
Matrix<3> odomPose;

Car car(WHEELBASE_LENGTH / 2, WHEELBASE_WIDTH / 2, OMNIWHEEL_DIAMETER / 2, UPDATE_STATE_DT_MS, &desiredCarVelocity, &jointAngles, &jointVelocities, &jointTicks, &odomPose);
void updateW1A() { car.wheels[0]->triggerA(); }
void updateW1B() { car.wheels[0]->triggerB(); }
void updateW2A() { car.wheels[1]->triggerA(); }
void updateW2B() { car.wheels[1]->triggerB(); }
void updateW3A() { car.wheels[2]->triggerA(); }
void updateW3B() { car.wheels[2]->triggerB(); }
void updateW4A() { car.wheels[3]->triggerA(); }
void updateW4B() { car.wheels[3]->triggerB(); }

SerialTransceiver transceiver(&desiredCarVelocity, &jointAngles, &jointVelocities, &jointTicks, &odomPose);

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
    
    
    // car.wheels[0]->setPID(WHEEL_KP, WHEEL_KI, WHEEL_KD);
    // car.wheels[1]->setPID(WHEEL_KP, WHEEL_KI, WHEEL_KD);
    // car.wheels[2]->setPID(WHEEL_KP, WHEEL_KI, WHEEL_KD);
    // car.wheels[3]->setPID(WHEEL_KP, WHEEL_KI, WHEEL_KD);

    car.wheels[0]->setPID(0.05, 0.0, 0); // wheel1
    car.wheels[1]->setPID(0.05, 0.0, 0.0);  //  wheel2 
    car.wheels[2]->setPID(0.05, 0.0, 0.0); //  wheel3
    car.wheels[3]->setPID(0.05, 0.0, 0); //  wheel4

    desiredCarVelocity.Fill(0);
    jointAngles.Fill(0);
    jointTicks.Fill(0);
    jointVelocities.Fill(0); 

    Serial.begin(115200);
    Serial.setTimeout(100);

    // // Clear any garbage in serial buffer
    // while (Serial.available()) {
    //     Serial.read();
    // }

    carThread.onRun(updateCar);
    carThread.setInterval(UPDATE_STATE_DT_MS);

    serialThread.onRun(talkSerial);
    serialThread.setInterval(33);  // ~30Hz for serial communication
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
