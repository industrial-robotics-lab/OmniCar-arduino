#include "SerialTransceiver.h"

SerialTransceiver::SerialTransceiver(Matrix<3> *desired, Matrix<3> *feedback)
    : desiredVelocity(desired), feedbackPose(feedback)
{
    maxLinSpeed = 0.1;
    maxAngSpeed = 1;
}

void SerialTransceiver::rx()
{
    // Get message
    int bytesRead = 0;
    while (bytesRead < 5)
    {
        if (Serial.available())
        {
            buffer[bytesRead] = Serial.read();
            bytesRead++;
        }
    }

    //Get vector
    if (buffer[4] == '\n')
    {
        memcpy(controlVec, buffer, 3);
        readChecksum = buffer[3];
        calcChecksum = crc8((uint8_t *)controlVec, 3);
        if (readChecksum == calcChecksum)
        {
            if (controlVec[0] == controlVec[1] == controlVec[2] == 127)
            {
                (*desiredVelocity)(0) = 0.0;
                (*desiredVelocity)(1) = 0.0;
                (*desiredVelocity)(2) = 0.0;
            }
            else
            {
                (*desiredVelocity)(0) = mapUint8ToFloat(controlVec[0], -maxAngSpeed, maxAngSpeed);
                (*desiredVelocity)(1) = mapUint8ToFloat(controlVec[1], -maxLinSpeed, maxLinSpeed);
                (*desiredVelocity)(2) = mapUint8ToFloat(controlVec[2], -maxLinSpeed, maxLinSpeed);
            }
            // memcpy(desiredVelocity, vec, 12);
        }
    }
}

void SerialTransceiver::tx()
{
    calcChecksum = crc8((uint8_t *)feedbackPose, 12);
    Serial.write((byte *)feedbackPose, 12);
    Serial.write(&calcChecksum, 1);
    Serial.write('\n');
    // Serial.flush(); // waits for the transmission to complete
}

void SerialTransceiver::talk()
{
    rx();
    tx();
}