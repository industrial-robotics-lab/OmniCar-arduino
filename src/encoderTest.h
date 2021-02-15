#include <PinChangeInterrupt.h>
// #include "Arduino.h"

const int pinA = 18;
const int pinB = 19;

volatile long position = 0;

void printPosition() {
    // Serial.println("Position: " + (String)position);
    Serial.print('$');
    Serial.print(position);
    Serial.print(';');
}

void triggerA() {
    if (digitalRead(pinA) != digitalRead(pinB)) {
        position++;
    } else {
        position--;
    }
    printPosition();
}
void triggerB() {
    if (digitalRead(pinA) == digitalRead(pinB)) {
        position++;
    } else {
        position--;
    }
    printPosition();
}

void setup() {
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pinA), triggerA, RISING);
    attachInterrupt(digitalPinToInterrupt(pinB), triggerB, RISING);
    // attachPCINT(digitalPinToPCINT(pinA), triggerA, RISING);
    // attachPCINT(digitalPinToPCINT(pinB), triggerB, RISING);

    Serial.begin(115200);
}

void loop() {}