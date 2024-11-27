#include <SparkFunLSM6DSO.h>
#include <Arduino.h>

//Constant Values
LSM6DSO myIMU;

//Function Declarations
float gyroscopeSensorTick(Servo servo, const int servoPin);
int convertAnalogToDegrees(int analogValue);
int convertAnalogToIntensity(int analogueValue);
