#include "SerialTransceiver.h"

SerialTransceiver::SerialTransceiver(Matrix<3> *desired, Matrix<3> *feedback)
{
    maxValue = 10; // wheel can't rotate faster than 10 m/s
    desiredVelocity = desired;
    feedbackPose = feedback;
}

void SerialTransceiver::rx()
{
    Serial.readBytesUntil('\n', buffer, 13);
    for (int i = 0; i < 4; i++)
    {
        n1.b[i] = buffer[i];
        n2.b[i] = buffer[i + 4];
        n3.b[i] = buffer[i + 8];
        // n4.b[i] = buffer[i + 12];
    }
    // Check message corruption
    if (abs(n1.f) <= maxValue && abs(n2.f) <= maxValue && abs(n3.f) <= maxValue /* && abs(n4.f) <= maxValue */)
    {
        (*desiredVelocity)(0) = n1.f;
        (*desiredVelocity)(1) = n2.f;
        (*desiredVelocity)(2) = n3.f;
        // desiredVelocity(3) = n4.f;
    }
}

void SerialTransceiver::tx()
{
    // Serial.write((byte *)desiredVelocity, sizeof(float) * 3);
    Serial.write((byte *)feedbackPose, sizeof(float) * 3);
    Serial.write('\n');
}

void SerialTransceiver::talk()
{
    if (Serial.available() > 0)
    {
        rx();
        tx();
    }
}