#pragma once
// COMMON PARAMETERS
#define UPDATE_STATE_DT_MS 20

// CAR KINEMATIC PARAMETERS
#define WHEELBASE_LENGTH 175.0 / 1000     // mm to m by x-axis
#define WHEELBASE_WIDTH 165.0 / 1000 // mm to m by y-axis
#define OMNIWHEEL_DIAMETER 60.0 / 1000   // mm to m

// ENC_MOTORODERS SETTINGS
#define ENC_MOTOR1_PINA 51
#define ENC_MOTOR1_PINB 53
#define ENC_MOTOR2_PINA 21
#define ENC_MOTOR2_PINB 20
#define ENC_MOTOR3_PINA 52
#define ENC_MOTOR3_PINB 50
#define ENC_MOTOR4_PINA 18
#define ENC_MOTOR4_PINB 19

// PID_PARAMETERS
#define WHEEL_KP 0.22
#define WHEEL_KI 0.075
#define WHEEL_KD 0.002
