#include "SerialTransceiver.h"

SerialTransceiver::SerialTransceiver(Matrix<3> *desired, Matrix<3> *feedback)
    : desiredVelocity(desired), feedbackPose(feedback)
{
    maxValue = 10; // wheel can't rotate faster than 10 m/s
}

void SerialTransceiver::rx()
{
    Serial.readBytesUntil('\n', buffer, 13);
    for (int i = 0; i < 4; i++)
    {
        n1.b[i] = buffer[i];
        n2.b[i] = buffer[i + 4];
        n3.b[i] = buffer[i + 8];
    }
    // Check message corruption
    checksum = crc8((uint8_t *)buffer, 12);
    if (checksum == buffer[12])
    {
        (*desiredVelocity)(0) = n1.f;
        (*desiredVelocity)(1) = n2.f;
        (*desiredVelocity)(2) = n3.f;
    }
}

void SerialTransceiver::tx()
{
    checksum = crc8((uint8_t *)feedbackPose, 12);
    Serial.write((byte *)feedbackPose, sizeof(float) * 3);
    Serial.write(&checksum, sizeof(byte));
    Serial.write('\n');
    Serial.flush(); // waits for the transmission to complete
}

void SerialTransceiver::talk()
{
    if (Serial.available() > 0)
    {
        rx();
        tx();
    }
}