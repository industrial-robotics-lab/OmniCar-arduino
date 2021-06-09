#include <Arduino.h>
#include "Motor.h"

unsigned long period = 500;
unsigned long size = 17;
int values[] = {50, 0, 60, 0, 69, 0, 70, 0, 71, 0, 80, 0, 200, 0, -255, 255, 0};
Motor motor(1);

void setup() {
    Serial.begin(38400);
}

void loop() {
    unsigned long step = millis() / period;
    if (step < size) {
        motor.setValue(values[step]);
        Serial.println("Value = " + (String)values[step]);
    }
}