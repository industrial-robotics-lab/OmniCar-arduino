#include <PinChangeInterrupt.h>
#include "config.h"
// #include "Arduino.h"

const int pinA = ENC_MOTOR3_PINA;
const int pinB = ENC_MOTOR3_PINB;

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

    // attachInterrupt(digitalPinToInterrupt(pinA), triggerA, RISING);
    // attachInterrupt(digitalPinToInterrupt(pinB), triggerB, RISING);

    // Use program interrupt
    attachPCINT(digitalPinToPCINT(pinA), triggerA, RISING);
    attachPCINT(digitalPinToPCINT(pinB), triggerB, RISING);

    Serial.begin(38400);
}

void loop() {}