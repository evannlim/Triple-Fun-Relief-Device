#include <Servo.h>
#include <chrono>
#include <iostream>

// constant values
const int maxLightSensorValue = 4095;
const int minLightSensorValue = 0;

// Function declarations
int lightSensorTick(Servo servo, const int servoPin, const int lightSensorPin);
int convertAnalogToIntensity(int analogueValue);
