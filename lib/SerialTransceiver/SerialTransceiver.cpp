#include "SerialTransceiver.h"

SerialTransceiver::SerialTransceiver(Matrix<3> *desiredVelocity, Matrix<4> *jointAngles, Matrix<4> *jointVelocities, Matrix<3> *odomPose)
    :desiredVelocity(desiredVelocity), jointAngles(jointAngles), jointVelocities(jointVelocities), odomPose(odomPose)
{

    bufferOutSize = (jointVelocities->Rows+jointAngles->Rows)*sizeof(float)+2;
    stateVector = new float[jointVelocities->Rows+jointAngles->Rows + odomPose->Rows]();

    bufferInSize = (desiredVelocity->Rows)*sizeof(float)+2;
    controlVector = new float[desiredVelocity->Rows]();
    
    bufferIn = new uint8_t[bufferInSize]();
}

void SerialTransceiver::rx()
{
    // Get message
    int bytesRead = 0;
    while (bytesRead < bufferInSize)
    {
        if (Serial.available())
        {
            bufferIn[bytesRead] = Serial.read();
            bytesRead++;
        }
    }

    //Get vector
    if (bufferIn[bufferInSize-1] == '\n')
    {
        memcpy(controlVector, bufferIn, bufferInSize-2);
        readChecksum = bufferIn[bufferInSize-2];
        calcChecksum = crc8((uint8_t *)controlVector, bufferInSize-2);
        if (readChecksum == calcChecksum)
        {
            memcpy(desiredVelocity->storage, controlVector, desiredVelocity->Rows*sizeof(float));
        }
    }
}

void SerialTransceiver::tx()
{
    memcpy(stateVector, jointAngles->storage, jointAngles->Rows*sizeof(float));
    memcpy(&(stateVector[jointAngles->Rows]), jointVelocities->storage, jointVelocities->Rows*sizeof(float));
    memcpy(&(stateVector[jointAngles->Rows+jointVelocities->Rows]), odomPose->storage, odomPose->Rows*sizeof(float));
    calcChecksum = crc8((uint8_t *)stateVector, bufferOutSize-2);
    Serial.write((byte *)stateVector, bufferOutSize-2);
    Serial.write(&calcChecksum, 1);
    Serial.write('\n');
    // Serial.flush(); // waits for the transmission to complete
}

void SerialTransceiver::talk()
{
    rx();
    tx();
}