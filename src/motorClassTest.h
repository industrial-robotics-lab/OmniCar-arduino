#include <Arduino.h>
#include "Motor.h"

unsigned long period = 2000;
unsigned long size = 13;
int values[] = {32, 64, 128, 256, 128, 64, 32, 0, -32, -64, -128, -256, 0};
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