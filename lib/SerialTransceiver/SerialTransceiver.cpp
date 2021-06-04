#include "SerialTransceiver.h"

SerialTransceiver::SerialTransceiver(Matrix<3> *desired, Matrix<3> *feedback)
    : desiredVelocity(desired), feedbackPose(feedback)
{
    maxAngSpeed = 0.5;
    maxLinSpeed = 0.1;
    threshold = 0.0001;
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
            if (controlVec[0] == 127)
            {
                fi = 0;
            }
            else
            {
                fi = mapUint8ToFloat(controlVec[0], -maxAngSpeed, maxAngSpeed);
            }

            if (controlVec[1] == 127)
            {
                x = 0;
            }
            else
            {
                x = mapUint8ToFloat(controlVec[1], -maxLinSpeed, maxLinSpeed);
            }

            if (controlVec[2] == 127)
            {
                y = 0;
            }
            else
            {
                y = mapUint8ToFloat(controlVec[2], -maxLinSpeed, maxLinSpeed);
            }
            // if (abs(fi) <= threshold) fi = 0;
            // if (abs(x) <= threshold) x = 0;
            // if (abs(y) <= threshold) y = 0;
            (*desiredVelocity)(0) = fi;
            (*desiredVelocity)(1) = x;
            (*desiredVelocity)(2) = y;
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