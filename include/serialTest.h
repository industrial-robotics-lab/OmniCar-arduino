#include "SerialTransceiver.h"

Matrix<3> desiredCarVelocity;
Matrix<3> feedbackCarPose;

SerialTransceiver transceiver(&desiredCarVelocity, &feedbackCarPose);

void setup()
{
    Serial.begin(115200);
    Serial.setTimeout(1000);
}

void loop()
{
    transceiver.talk();
}
