#include <Arduino.h>
#include <PinChangeInterrupt.h>
#include "Car.h"
#include "config.h"

Motor motor1(1);
Motor motor2(2);
Motor motor3(3);
Motor motor4(4);

int pinA = ENC_MOTOR2_PINA;
int pinB = ENC_MOTOR2_PINB;
Encoder encoder1(ENC_MOTOR1_PINA, ENC_MOTOR1_PINB, false);
Encoder encoder2(ENC_MOTOR2_PINA, ENC_MOTOR2_PINB, false);
Encoder encoder3(ENC_MOTOR3_PINA, ENC_MOTOR3_PINB, false);
Encoder encoder4(ENC_MOTOR4_PINA, ENC_MOTOR4_PINB, false);

void updateW1A() { encoder1.triggerA(); }
void updateW1B() { encoder1.triggerB(); }
void updateW2A() { encoder2.triggerA(); }
void updateW2B() { encoder2.triggerB(); }
void updateW3A() { encoder3.triggerA(); }
void updateW3B() { encoder3.triggerB(); }
void updateW4A() { encoder4.triggerA(); }
void updateW4B() { encoder4.triggerB(); }

int prev_time = millis();
int dt = 0;
float prev_pos_1 = 0;
float prev_pos_2 = 0;
float prev_pos_3 = 0;
float prev_pos_4 = 0;

float pos_1 = 0;
float pos_2 = 0;
float pos_3 = 0;
float pos_4 = 0;

void setup() {
    encoder1.reset();
    encoder2.reset();
    encoder3.reset();
    encoder4.reset();

    attachPCINT(digitalPinToPCINT(ENC_MOTOR1_PINA), updateW1A, RISING);
    attachPCINT(digitalPinToPCINT(ENC_MOTOR1_PINB), updateW1B, RISING);
    attachInterrupt(digitalPinToInterrupt(ENC_MOTOR2_PINA), updateW2A, RISING);
    attachInterrupt(digitalPinToInterrupt(ENC_MOTOR2_PINB), updateW2B, RISING);
    attachPCINT(digitalPinToPCINT(ENC_MOTOR3_PINA), updateW3A, RISING);
    attachPCINT(digitalPinToPCINT(ENC_MOTOR3_PINB), updateW3B, RISING);
    attachInterrupt(digitalPinToInterrupt(ENC_MOTOR4_PINA), updateW4A, RISING);
    attachInterrupt(digitalPinToInterrupt(ENC_MOTOR4_PINB), updateW4B, RISING);

    Serial.begin(38400);
}

void loop() {
    // send control
    // 
    // motor2.setMotorControl(0.2);
    // motor3.setMotorControl(0.2);
    // motor4.setMotorControl(0.2);
    dt = millis() - prev_time;
    if (pos_1 < 50.25){
        motor1.setMotorControl(0.0);
        motor2.setMotorControl(0.0);
        motor3.setMotorControl(0.0);
        motor4.setMotorControl(0.0);
    }
    else{
        motor1.setMotorControl(0.0);
        motor2.setMotorControl(0.0);
        motor3.setMotorControl(0.0);
        motor4.setMotorControl(0.0);
    }


    prev_pos_1 = pos_1;
    pos_1 = encoder1.getAngle();


    // check encoders
    Serial.println("Position_1 = " + (String) encoder1.getAngle() + 
    " Position_2 = " + (String) encoder2.getAngle() + 
    " Position_3 = " + (String) encoder3.getAngle() +
    " Position_4 = " + (String) encoder4.getAngle());
}