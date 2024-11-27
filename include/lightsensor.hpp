#include <Servo.h>
#include <chrono>
#include <iostream>

// constant values
const int callibrateDuration = 10;
const int maxDegree = 179;
const int minDegree = 0;
const int maxLightSensorValue = 4095;
const int minLightSensorValue = 0;

// Function declarations
int lightSensorTick(Servo servo, const int servoPin, const int lightSensorPin);
int convertAnalogToDegrees(int analogValue);
int convertAnalogToIntensity(int analogueValue);
