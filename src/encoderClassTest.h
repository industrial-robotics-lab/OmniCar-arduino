#include <PinChangeInterrupt.h>
#include "Encoder.h"

int pinA = 51;
int pinB = 53;
Encoder encoder(pinA, pinB, false);
void triggerA() { encoder.triggerA(); }
void triggerB() { encoder.triggerB(); }

void setup() {
    // attachInterrupt(digitalPinToInterrupt(pinA), triggerA, RISING);
    // attachInterrupt(digitalPinToInterrupt(pinB), triggerB, RISING);
    attachPCINT(digitalPinToPCINT(pinA), triggerA, RISING);
    attachPCINT(digitalPinToPCINT(pinB), triggerB, RISING);

    Serial.begin(115200);
}

void loop() {
    Serial.println("Position " + (String)encoder.getTicks());
}