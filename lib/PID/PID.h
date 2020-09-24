class PID {
private:
    float kP;
    float kI;
    float kD;

    float uMax;
    float vMax;
    float h; // PID step

    float u; // control input
    float v; // speed

    float ePrev; // error from previous step
    float uPrev; // control from previous step
    float uIPrev; // interational part of control from previous step

    int sign(float value);
    void limitSpeed(float u);

public:
    PID(float kP, float kI, float kD, float uMax, float vMax, float h);
    float calc(float e);
};