#include "SerialTalker.h"

SerialTalker::SerialTalker() {}

float* SerialTalker::rx() {
    Serial.readBytesUntil('\n', buffer, 17);
    for (int i = 0; i < 4; i++) {
        n1.b[i] = buffer[i];
        n2.b[i] = buffer[i + 4];
        n3.b[i] = buffer[i + 8];
        n4.b[i] = buffer[i + 12];
    }
    rpms[0] = n1.f;
    rpms[1] = n2.f;
    rpms[2] = n3.f;
    rpms[3] = n4.f;
    return rpms;
}

void SerialTalker::tx(float values[4]) {
    rpms[0] = values[0];
    rpms[1] = values[1];
    rpms[2] = values[2];
    rpms[3] = values[3];
    Serial.write((byte*)&rpms, sizeof(float)*4);
    Serial.write('\n');
}