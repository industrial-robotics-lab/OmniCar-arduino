#include <PinChangeInterrupt.h>
const int pinA = 50;
const int pinB = 51;

volatile long position = 0;

void printPosition() {
    Serial.println("Position: " + (String)position);
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
    // attachInterrupt(digitalPinToInterrupt(pinA), triggerA, RISING);

    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
    attachPCINT(digitalPinToPCINT(pinA), triggerA, RISING);
    attachPCINT(digitalPinToPCINT(pinB), triggerB, RISING);

    Serial.begin(115200);
}

void loop() {}