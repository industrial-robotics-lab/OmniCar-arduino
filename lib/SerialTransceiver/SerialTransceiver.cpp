#include "SerialTransceiver.h"

SerialTransceiver::SerialTransceiver(float *desired, float *feedback)
{
    maxRpm = 400;
    desiredPtr = desired;
    feedbackPtr = feedback;
}

void SerialTransceiver::rx()
{
    Serial.readBytesUntil('\n', buffer, 17);
    for (int i = 0; i < 4; i++)
    {
        n1.b[i] = buffer[i];
        n2.b[i] = buffer[i + 4];
        n3.b[i] = buffer[i + 8];
        n4.b[i] = buffer[i + 12];
    }
    // Check message corruption
    if (abs(n1.f) <= maxRpm && abs(n2.f) <= maxRpm && abs(n3.f) <= maxRpm && abs(n4.f) <= maxRpm)
    {
        desiredPtr[0] = n1.f;
        desiredPtr[1] = n2.f;
        desiredPtr[2] = n3.f;
        desiredPtr[3] = n4.f;
    }
}

void SerialTransceiver::tx()
{
    Serial.write((byte *)feedbackPtr, sizeof(float) * 4);
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