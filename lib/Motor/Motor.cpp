#include "Arduino.h"
#include "Motor.h"

Motor::Motor(uint8_t number, uint8_t pwm_moving_threshold)
:pwm_moving_threshold(pwm_moving_threshold) {
  motor = new AF_DCMotor(number);
}
Motor::~Motor() { delete motor; }

void Motor::setMotorControl(float control) {
  
  int unclipedPWM = 0;
  if(control!=0.0){
    unclipedPWM= control*(255-pwm_moving_threshold) + copysign(pwm_moving_threshold, control);
  }
  sendedPWM = constrain(unclipedPWM, -255, 255);
  if (sendedPWM == 0) {
    motor->run(RELEASE);
    motor->setSpeed(0);
  } else if (sendedPWM > 0) {
    motor->run(FORWARD);
    motor->setSpeed(abs(sendedPWM));
  } else {
    motor->run(BACKWARD);
    motor->setSpeed(abs(sendedPWM));
  }
}

uint8_t Motor::getPWMMovingThreshold(){
  return pwm_moving_threshold;
}

int Motor::getSendedPWM(){
  return sendedPWM;
}