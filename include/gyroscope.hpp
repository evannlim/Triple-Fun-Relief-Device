#include <SparkFunLSM6DSO.h>
#include <Arduino.h>
#include <Servo.h>

//Function Declarations
float gyroscopeSensorTick(Servo servo, const int servoPin);
int gyroscopeConvertAnalogToDegrees(int analogValue);
int gyroscopeConvertAnalogToIntensity(int analogueValue);
