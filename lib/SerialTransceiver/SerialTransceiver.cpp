#include "SerialTransceiver.h"

SerialTransceiver::SerialTransceiver(Matrix<3> *desiredVelocity, Matrix<4> *jointAngles, Matrix<4> *jointVelocities, Matrix<4> *jointTicks, Matrix<3> *odomPose)
    :desiredVelocity(desiredVelocity), jointAngles(jointAngles), jointVelocities(jointVelocities), jointTicks(jointTicks), odomPose(odomPose)
{
    // Text-based protocol, no buffers needed
}

void SerialTransceiver::rx()
{
    if (!Serial.available())
        return;

    String line = Serial.readStringUntil('\n');
    line.trim();  // Remove whitespace and \r

    if (line.length() == 0)
        return;

    // DEBUG: see what we got
    Serial.print("RX_LINE: '");
    Serial.print(line);
    Serial.println("'");

    if (!line.startsWith("SET "))
        return;

    // Copy to a plain C string for strtok/atof
    char buf[64];
    line.toCharArray(buf, sizeof(buf));
    buf[sizeof(buf) - 1] = '\0';

    // Tokenize: "SET v_fl v_fr v_rr v_rl"
    char *token = strtok(buf, " ");  // first token ("SET")
    if (!token || strcmp(token, "SET") != 0)
        return;

    float v[4] = {0, 0, 0, 0};

    for (int i = 0; i < 4; ++i)
    {
        token = strtok(nullptr, " ");
        if (!token)
        {
            // missing value → abort
            Serial.println("PARSE ERROR: missing values");
            return;
        }
        v[i] = atof(token);
    }

    // DEBUG
    Serial.print("PARSED: [");
    Serial.print(v[0]); Serial.print(", ");
    Serial.print(v[1]); Serial.print(", ");
    Serial.print(v[2]); Serial.print(", ");
    Serial.print(v[3]); Serial.println("]");

    // Optional sanity check – but don't use abs() on float, use fabsf
    // if (fabsf(v[0]) < 100 && fabsf(v[1]) < 100 && fabsf(v[2]) < 100 && fabsf(v[3]) < 100)
    {
        (*jointVelocities)(0, 0) = v[0];
        (*jointVelocities)(1, 0) = v[1];
        (*jointVelocities)(2, 0) = v[2];
        (*jointVelocities)(3, 0) = v[3];
    }
}



void SerialTransceiver::tx()
{
    long t_fl = (long)(*jointTicks)(0, 0);
    long t_fr = (long)(*jointTicks)(1, 0);
    long t_rr = (long)(*jointTicks)(2, 0);
    long t_rl = (long)(*jointTicks)(3, 0);

    // if (t_fl != 0 || t_fr != 0 || t_rr != 0 || t_rl != 0)
    
        Serial.print("ENC ");
        Serial.print(t_fl);
        Serial.print(" ");
        Serial.print(t_fr);
        Serial.print(" ");
        Serial.print(t_rr);
        Serial.print(" ");
        Serial.println(t_rl);
}

void SerialTransceiver::talk()
{
    rx();
    tx();
}