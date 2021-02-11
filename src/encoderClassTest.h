#include <PinChangeInterrupt.h>
#include "Encoder.h"

int pinA = 50;
int pinB = 51;
Encoder encoder(pinA, pinB);
void triggerA() { encoder.triggerA(); }
void triggerB() { encoder.triggerB(); }

void setup() {
    attachPCINT(digitalPinToPCINT(pinA), triggerA, RISING);
    attachPCINT(digitalPinToPCINT(pinB), triggerB, RISING);

    Serial.begin(115200);
}

void loop() {
    Serial.println("Position " + (String)encoder.getTicks());
}