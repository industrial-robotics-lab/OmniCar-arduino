#include <Arduino.h>
#include "Motor.h"

unsigned long period = 3000;
unsigned long size = 5;
int values[] = {30, 40, 50, 60, 0};
Motor motor(1);

void setup() {
    Serial.begin(115200);
}

void loop() {
    unsigned long step = millis() / period;
    if (step < size) {
        motor.setValue(values[step]);
        Serial.println("Value = " + (String)values[step]);
    }
}