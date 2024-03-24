#include <Arduino.h>
#include "Motor.h"

unsigned long period = 500;
int voltageValues[] = {50, 0, 60, 0, 69, 0, 70, 0, 71, 0, 80, 0, 200, 0, -255, 255, 0};
int arrayLength = sizeof(voltageValues) / sizeof(int);
Motor motor(1);

void setup() {
    Serial.begin(38400);
}

void loop() {
    unsigned long step = millis() / period;
    if (step < arrayLength) {
        motor.setValue(voltageValues[step]);
        Serial.println("Value = " + (String)voltageValues[step]);
    }
}