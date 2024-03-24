#include <Arduino.h>
#include "omnimath.h"


Matrix<6> vec6 = {1,2,3,4,5,6};
double delta;

void setup() {
    Serial.begin(115200);
}

void loop() {
    Serial << "se3: " << vec6_to_SE3(vec6) << '\n';
}