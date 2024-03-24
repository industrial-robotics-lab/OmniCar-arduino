#include <PinChangeInterrupt.h>
#include "Encoder.h"
#include "config.h"

int pinA = ENC_MOTOR2_PINA;
int pinB = ENC_MOTOR2_PINB;
Encoder encoder(pinA, pinB, false);
void triggerA() { encoder.triggerA(); }
void triggerB() { encoder.triggerB(); }

void setup() {
    encoder.reset();
    if(digitalPinToInterrupt(pinA) == -1){
        attachPCINT(digitalPinToPCINT(pinA), triggerA, RISING);
    } else{
        attachInterrupt(digitalPinToInterrupt(pinA), triggerA, RISING);
    }
    if(digitalPinToInterrupt(pinB) == -1){
        attachPCINT(digitalPinToPCINT(pinB), triggerB, RISING);
    } else{
        attachInterrupt(digitalPinToInterrupt(pinB), triggerB, RISING);
    }

    Serial.begin(38400);
}

void loop() {
    Serial.println("Position " + (String)encoder.getAngle()+" Ticks " + (String)encoder.getTicks());
}