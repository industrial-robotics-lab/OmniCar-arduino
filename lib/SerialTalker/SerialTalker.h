#include <Arduino.h>

class SerialTalker
{
private:
    byte buffer[17];
    union { float f; byte b[4]; } n1;
    union { float f; byte b[4]; } n2;
    union { float f; byte b[4]; } n3;
    union { float f; byte b[4]; } n4;
    float rpms[4];

public:
    SerialTalker();
    float* rx();
    void tx(float rpms[4]);

};