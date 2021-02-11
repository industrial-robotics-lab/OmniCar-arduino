#include "SerialTransceiver.h"

float desiredRpms[4] = {};  // init with zeros
float feedbackRpms[4] = {}; // init with zeros

SerialTransceiver transceiver(desiredRpms, feedbackRpms);

void setup()
{
    Serial.begin(115200);
    Serial.setTimeout(1000);
}

void loop()
{
    transceiver.talk();
}
